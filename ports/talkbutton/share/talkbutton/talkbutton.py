#!/usr/bin/env python3
"""Play/pause PTT: record mic, print transcript, Hub notify. No web."""
import json
import os
import sys
import threading
import time

HERE = os.path.dirname(os.path.abspath(__file__))
for _p in (HERE, os.path.abspath(os.path.join(HERE, '..', 'voice2text'))):
    if os.path.isdir(_p) and _p not in sys.path:
        sys.path.insert(0, _p)

from qsa_capture import capture_pcm
from vosk_engine import VoskEngine
from button_watch import read_buttons, is_down
from bb_clipboard import copy_text

MAX_SEC = 20
LAST_PATH = os.path.join(HERE, 'last.txt')
PPS_PATH = '/pps/services/notify/control'
PORT = 8027


def log(msg):
    sys.stdout.write(msg + '\n')
    sys.stdout.flush()


def rec_worker(stop, box):
    def note(msg):
        log('[REC] %s' % msg)

    try:
        cap = capture_pcm(MAX_SEC, log=note, stop=stop)
    except Exception as e:
        box['ok'] = False
        box['err'] = str(e)
        return
    box['ok'] = True
    box['pcm'] = cap.get('pcm') or b''
    box['rate'] = int(cap.get('rate') or 16000) or 16000
    box['err'] = cap.get('message') or ''


def save_last(text):
    try:
        with open(LAST_PATH, 'w') as f:
            f.write(text + '\n')
    except Exception:
        pass


def execute_shell_command(title, subtitle, itemid='RocketChat'):
    payload = {
        'itemid': itemid,
        'title': title,
        'subtitle': subtitle,
        'target': '',
        'targetAction': '',
        'payload': 'http://localhost:%s' % PORT,
        'payloadType': 'url',
        'payloadURI': 'http://localhost:%s' % PORT,
    }
    msg = 'msg::notify\ndat:json:%s\n' % json.dumps(payload)
    try:
        fd = os.open(PPS_PATH, os.O_WRONLY | os.O_APPEND)
        try:
            os.write(fd, msg.encode('utf-8'))
        finally:
            os.close(fd)
        print('[NOTIFY] %s' % title)
        sys.stdout.flush()
    except Exception as e:
        print('[NOTIFY] error: %s' % e)
        sys.stdout.flush()


def notify_transcribed(text):
    # Same call as rocketchat2 check_for_new_messages (app.py ~1437).
    title = '🚀 %s' % 'Transcribed'
    execute_shell_command(
        title,
        '%s: %s' % ('Talkbutton', (text or '')[:80]),
        'RocketChat-%s' % int(time.time() * 1000),
    )


def main():
    log('talkbutton — play/pause to start, play/pause to stop')
    log('warming Vosk…')
    vosk = VoskEngine(V2T)
    if not vosk.load():
        log('Vosk failed: %s' % (vosk.err or 'unknown'))
        return 1
    log('Vosk ready (%sms). Press play/pause.' % vosk.load_ms)

    prev = read_buttons()
    stop = None
    th = None
    box = None
    listening = False

    while True:
        cur = read_buttons()
        pressed = is_down(cur, 'bid_playpause') and not is_down(prev, 'bid_playpause')
        prev = cur or prev
        if pressed:
            if listening:
                log('stopping…')
                if stop:
                    stop.set()
                if th:
                    th.join(30)
                listening = False
                pcm = (box or {}).get('pcm') or b''
                rate = (box or {}).get('rate') or 16000
                if not (box or {}).get('ok'):
                    log('capture failed: %s' % ((box or {}).get('err') or '?'))
                elif len(pcm) < 64:
                    log('no audio')
                else:
                    log('decoding %s bytes…' % len(pcm))
                    decoded = vosk.decode_pcm(pcm, rate)
                    text = (decoded.get('text') or '').strip()
                    if text:
                        log('')
                        log(text)
                        log('')
                        save_last(text)
                        ok, err = copy_text(text)
                        if ok:
                            log('[CLIP] system clipboard')
                        else:
                            log('[CLIP] fail %s' % err)
                        notify_transcribed(text)
                    else:
                        log('(no words)')
                log('press play/pause to talk again')
            else:
                stop = threading.Event()
                box = {'ok': False, 'pcm': b'', 'rate': 16000, 'err': ''}
                th = threading.Thread(target=rec_worker, args=(stop, box))
                try:
                    th.daemon = True
                except Exception:
                    pass
                listening = True
                th.start()
                log('LISTENING')
        time.sleep(0.05)


if __name__ == '__main__':
    try:
        sys.exit(main() or 0)
    except KeyboardInterrupt:
        log('bye')
        sys.exit(0)
