"""LCARS sound effects and computer voice.

The beeps are synthesized from the recipes in SOUNDS rather than shipped as
samples: nothing copyrighted travels in the qpkg, the whole set is a few KB of
Python, and /api/sounds hands the same recipes to the browser so lcars.js can
render them through Web Audio with no network round trip. The WAV renderer here
is the fallback for browsers without Web Audio, and both paths sound identical
because they read one recipe table.

The voice is whatever offline TTS the device has — flite's slt (female, the
closer match to the ship computer) preferred over Pico — optionally run through
an ffmpeg chain that flattens and band-limits it into the LCARS delivery.
"""

import hashlib
import io
import math
import os
import struct
import shutil
import subprocess
import threading
import wave

RATE = 22050

# Partial sets. A pure sine reads as a cheap game blip; the stacked fifth and
# octave are what give LCARS taps their short bell-like ring.
BELL = ((1.0, 1.0), (1.5, 0.42), (2.0, 0.16))
RING = ((1.0, 1.0), (1.5, 0.30), (2.99, 0.10))
PURE = ((1.0, 1.0),)
BUZZ = ((1.0, 1.0), (2.0, 0.5), (3.0, 0.28))

# Note frequencies used by the recipes.
A3, D4, A4 = 220.0, 293.7, 440.0
G5, A5, C6, D6, E6 = 784.0, 880.0, 1046.5, 1174.7, 1318.5
G6, A6, B6 = 1568.0, 1760.0, 1975.5


def blip(at, dur, f0, f1=None, wave_form="sine", gain=0.5, partials=BELL):
    return {
        "at": round(at, 4),
        "dur": round(dur, 4),
        "f0": f0,
        "f1": f0 if f1 is None else f1,
        "w": wave_form,
        "g": gain,
        "p": [list(p) for p in partials],
    }


SOUNDS = {
    # Three tap variants, picked at random per press. The show cycled a small
    # library of blips, which is why a single fixed beep sounds wrong.
    "tap": [blip(0, 0.075, C6)],
    "tap2": [blip(0, 0.075, A5)],
    "tap3": [blip(0, 0.07, E6)],
    "nav": [blip(0, 0.055, G5, gain=0.42), blip(0.05, 0.09, D6)],
    "open": [
        blip(0, 0.05, G5, gain=0.4),
        blip(0.045, 0.05, C6, gain=0.44),
        blip(0.09, 0.1, G6),
    ],
    "close": [
        blip(0, 0.05, E6, gain=0.4),
        blip(0.045, 0.05, A5, gain=0.4),
        blip(0.09, 0.11, D4 * 2, gain=0.44),
    ],
    "confirm": [blip(0, 0.045, C6, gain=0.42), blip(0.04, 0.1, G6)],
    "deny": [
        blip(0, 0.09, 233.0, wave_form="square", gain=0.34, partials=BUZZ),
        blip(0.12, 0.11, 185.0, wave_form="square", gain=0.34, partials=BUZZ),
    ],
    "error": [blip(0, 0.28, A4, 150.0, wave_form="square", gain=0.3, partials=PURE)],
    "alert": [
        blip(0, 0.12, 740.0, 880.0, wave_form="saw", gain=0.32, partials=PURE),
        blip(0.18, 0.12, 740.0, 880.0, wave_form="saw", gain=0.32, partials=PURE),
        blip(0.36, 0.14, 740.0, 880.0, wave_form="saw", gain=0.32, partials=PURE),
    ],
    # The two-tone chirp the computer gives before it speaks.
    "ack": [blip(0, 0.06, E6, gain=0.44, partials=RING), blip(0.055, 0.12, A6, partials=RING)],
    "work": [
        blip(0, 0.05, C6, gain=0.34),
        blip(0.07, 0.05, G6, gain=0.34),
        blip(0.14, 0.05, C6, gain=0.34),
        blip(0.21, 0.05, G6, gain=0.34),
        blip(0.28, 0.06, B6, gain=0.34),
    ],
    "boot": [
        blip(0, 0.45, A3 * 0.8, 1100.0, wave_form="tri", gain=0.3, partials=PURE),
        blip(0.42, 0.38, C6, gain=0.4, partials=RING),
        blip(0.42, 0.4, G6, gain=0.34, partials=RING),
    ],
    "toast": [blip(0, 0.05, G6, gain=0.36), blip(0.045, 0.06, D6, gain=0.36)],
    "key": [blip(0, 0.03, B6, gain=0.18, partials=PURE)],
}

_CACHE = {}
_CACHE_LOCK = threading.Lock()


def _wave_sample(kind, phase):
    """One cycle of the requested waveform at phase 0..1."""
    if kind == "sine":
        return math.sin(2.0 * math.pi * phase)
    if kind == "square":
        return 1.0 if (phase % 1.0) < 0.5 else -1.0
    if kind == "saw":
        return 2.0 * (phase % 1.0) - 1.0
    if kind == "tri":
        x = (phase % 1.0) * 4.0
        if x < 1.0:
            return x
        if x < 3.0:
            return 2.0 - x
        return x - 4.0
    return math.sin(2.0 * math.pi * phase)


def render(name):
    """Render a recipe to mono 16-bit WAV bytes."""
    blips = SOUNDS.get(name)
    if not blips:
        return None
    total = 0.0
    for b in blips:
        total = max(total, b["at"] + b["dur"])
    n = int((total + 0.02) * RATE) + 1
    buf = [0.0] * n

    for b in blips:
        start = int(b["at"] * RATE)
        length = int(b["dur"] * RATE)
        if length < 2:
            continue
        attack = max(2, int(0.004 * RATE))
        for mult, pgain in b["p"]:
            phase = 0.0
            peak = b["g"] * pgain
            for i in range(length):
                pos = i / float(length)
                freq = (b["f0"] + (b["f1"] - b["f0"]) * pos) * mult
                # Fast attack then exponential decay is what makes these read as
                # taps rather than tones; the tail fade kills the end click.
                if i < attack:
                    env = i / float(attack)
                else:
                    env = math.exp(-4.5 * ((i - attack) / float(length)))
                    tail = length - i
                    if tail < attack:
                        env *= tail / float(attack)
                idx = start + i
                if idx >= n:
                    break
                buf[idx] += _wave_sample(b["w"], phase) * peak * env
                phase += freq / float(RATE)

    peak = 0.0
    for v in buf:
        peak = max(peak, abs(v))
    scale = (0.89 / peak) if peak > 0.89 else 1.0
    frames = bytearray()
    for v in buf:
        s = int(max(-1.0, min(1.0, v * scale)) * 32767)
        frames += struct.pack("<h", s)

    out = io.BytesIO()
    handle = wave.open(out, "wb")
    handle.setnchannels(1)
    handle.setsampwidth(2)
    handle.setframerate(RATE)
    handle.writeframes(bytes(frames))
    handle.close()
    return out.getvalue()


def sound_wav(name):
    """Rendered WAV for a sound, cached in memory after the first request."""
    with _CACHE_LOCK:
        if name in _CACHE:
            return _CACHE[name]
    data = render(name)
    if data is None:
        return None
    with _CACHE_LOCK:
        _CACHE[name] = data
    return data


def recipes():
    """The recipe table for the browser's Web Audio renderer."""
    return {"rate": RATE, "sounds": SOUNDS}


# ── voice ─────────────────────────────────────────────────────────────────

MISC = "/accounts/1000/shared/misc"
TTS_BIN = os.path.join(MISC, "tts", "bin")
PICO_LANG = os.path.join(MISC, "tts", "share", "pico", "lang")

# flite first: its slt voice is a recorded female speaker, closer to the ship
# computer than Pico's 2011 SVOX synth. "say" only ever exists on a Mac and is
# there so the voice path can be exercised off-device.
VOICE_ORDER = ("flite", "pico", "say")
SAY = "/usr/bin/say"

# Flat, band-limited, lightly doubled — the delivery is what sells it more than
# the timbre does. Slight slow-down for the computer's measured pace.
FX_CHAIN = (
    "asetrate=16000*0.96,aresample=22050,atempo=1.02,"
    "highpass=f=100,lowpass=f=6800,"
    "acompressor=threshold=0.15:ratio=3:attack=5:release=180,"
    "aecho=0.85:0.3:18:0.12,volume=1.5"
)

MAX_SAY = 400


def _exe(*parts):
    path = os.path.join(*parts)
    return path if os.path.isfile(path) and os.access(path, os.X_OK) else ""


def ffmpeg_bin():
    found = _exe(MISC, "clitools", "bin", "ffmpeg")
    if found:
        return found
    return shutil.which("ffmpeg") or ""


def voices():
    """Which TTS engines this device actually has."""
    out = []
    if _exe(TTS_BIN, "flite"):
        out.append("flite")
    if _exe(TTS_BIN, "pico2wav") and os.path.isdir(PICO_LANG):
        out.append("pico")
    if os.path.isfile(SAY):
        out.append("say")
    return out


def clean_say(text):
    """Trim to something safe to hand an argv slot and short enough to synth."""
    text = (text or "").replace("\r", " ").replace("\n", " ").replace("\t", " ")
    out = []
    for ch in text:
        if ch == "\x00" or ord(ch) < 32:
            continue
        out.append(ch)
    text = "".join(out).strip()
    # A leading dash would be read as a flag by flite/pico2wav.
    while text[:1] == "-":
        text = text[1:].strip()
    return text[:MAX_SAY]


def voice_wav(text, engine="auto", fx=True, cache_dir=None):
    """Synthesize a line, returning (wav_bytes, engine_used) or (None, error)."""
    text = clean_say(text)
    if not text:
        return None, "empty"
    have = voices()
    if not have:
        return None, "no tts on device"
    if engine in ("auto", "", None):
        engine = have[0] if have[0] in VOICE_ORDER else have[0]
        for want in VOICE_ORDER:
            if want in have:
                engine = want
                break
    if engine not in have:
        return None, "voice %s unavailable" % engine

    key = hashlib.sha1(("%s|%s|%s" % (engine, 1 if fx else 0, text)).encode("utf-8")).hexdigest()
    cached = os.path.join(cache_dir, key + ".wav") if cache_dir else ""
    if cached and os.path.isfile(cached):
        try:
            with open(cached, "rb") as fh:
                return fh.read(), engine
        except Exception:
            pass

    raw = (cached[:-4] + ".raw.wav") if cached else "/tmp/lcars-voice-raw.wav"
    try:
        if cache_dir:
            os.makedirs(cache_dir, exist_ok=True)
        if engine == "flite":
            cmd = [_exe(TTS_BIN, "flite"), "-t", text, "-o", raw]
            env = None
        elif engine == "say":
            cmd = [SAY, "-v", "Samantha", "--file-format=WAVE",
                   "--data-format=LEI16@22050", "-o", raw, text]
            env = None
        else:
            cmd = [_exe(TTS_BIN, "pico2wav"), "-w", raw, "-l", "en-US", text]
            env = dict(os.environ)
            env["PICO_LANG_PATH"] = PICO_LANG
        subprocess.run(cmd, env=env, stdout=subprocess.DEVNULL,
                       stderr=subprocess.DEVNULL, timeout=25)
        if not os.path.isfile(raw) or os.path.getsize(raw) < 64:
            return None, "%s produced nothing" % engine

        final = raw
        ff = ffmpeg_bin()
        if fx and ff and cached:
            subprocess.run([ff, "-y", "-v", "error", "-i", raw, "-af", FX_CHAIN,
                            "-ar", str(RATE), "-ac", "1", "-c:a", "pcm_s16le", cached],
                           stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL,
                           timeout=25)
            if os.path.isfile(cached) and os.path.getsize(cached) > 64:
                final = cached
        elif cached:
            os.replace(raw, cached)
            final = cached

        with open(final, "rb") as fh:
            data = fh.read()
        if final is not raw and os.path.isfile(raw):
            try:
                os.remove(raw)
            except Exception:
                pass
        return data, engine
    except subprocess.TimeoutExpired:
        return None, "%s timed out" % engine
    except Exception as exc:
        return None, str(exc)


def trim_cache(cache_dir, keep=160):
    """Keep the voice cache from growing without bound."""
    try:
        names = []
        for name in os.listdir(cache_dir):
            if not name.endswith(".wav"):
                continue
            path = os.path.join(cache_dir, name)
            names.append((os.path.getmtime(path), path))
        if len(names) <= keep:
            return
        names.sort()
        for _, path in names[:len(names) - keep]:
            try:
                os.remove(path)
            except Exception:
                pass
    except Exception:
        pass


_sfx_counter = [0]
_sfx_lock = threading.Lock()


def speaker_play(wav_bytes):
    """Play through the device speaker, for when the browser has no audio."""
    player = _exe(MISC, "clitools", "bin", "play-audio")
    if not player:
        return False, "play-audio missing"
    # Use rotating temp files so rapid sounds don't overwrite each other
    with _sfx_lock:
        _sfx_counter[0] = (_sfx_counter[0] + 1) % 8
        slot = _sfx_counter[0]
    path = "/tmp/lcars-sfx-%d.wav" % slot
    try:
        with open(path, "wb") as fh:
            fh.write(wav_bytes)
        subprocess.Popen([player, path], stdout=subprocess.DEVNULL,
                         stderr=subprocess.DEVNULL)
        return True, ""
    except Exception as exc:
        return False, str(exc)
