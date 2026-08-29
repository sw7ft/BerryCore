/*
 * piano — Term49 sine piano via QSA playback (play-audio fallback)
 */
#include <errno.h>
#include <math.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/asoundlib.h>
#include <sys/wait.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define RATE 22050
#ifndef SND_PCM_OPEN_PLAYBACK
#define SND_PCM_OPEN_PLAYBACK 0x0001
#endif
#ifndef SND_PCM_START_DATA
#define SND_PCM_START_DATA PCM_START_DATA
#endif

static const struct {
	const char *name;
	double hz;
} NOTES[] = {
	{ "c3", 130.81 }, { "d3", 146.83 }, { "e3", 164.81 }, { "f3", 174.61 },
	{ "g3", 196.00 }, { "a3", 220.00 }, { "b3", 246.94 },
	{ "c4", 261.63 }, { "d4", 293.66 }, { "e4", 329.63 }, { "f4", 349.23 },
	{ "g4", 392.00 }, { "a4", 440.00 }, { "b4", 493.88 }, { "c5", 523.25 },
	{ NULL, 0 }
};

static double note_hz(const char *name)
{
	int i;
	char buf[8];
	if (!name || !*name)
		return 0;
	for (i = 0; name[i] && i < 7; i++) {
		char c = name[i];
		if (c >= 'A' && c <= 'Z')
			c = (char)(c - 'A' + 'a');
		buf[i] = c;
	}
	buf[i] = '\0';
	for (i = 0; NOTES[i].name; i++) {
		if (strcmp(NOTES[i].name, buf) == 0)
			return NOTES[i].hz;
	}
	return 0;
}

static void fill_sine(int16_t *pcm, int n, double hz)
{
	int i;
	for (i = 0; i < n; i++) {
		double t = (double)i / (double)RATE;
		double env = 1.0;
		int fade = RATE / 50;
		if (i < fade)
			env = (double)i / (double)fade;
		if (i > n - fade && fade > 0)
			env = (double)(n - i) / (double)fade;
		pcm[i] = (int16_t)(16000.0 * env * sin(2.0 * M_PI * hz * t));
	}
}

static int write_wav(const char *path, const int16_t *pcm, int n)
{
	FILE *fp;
	uint32_t data = (uint32_t)(n * 2);
	uint32_t riff = 36 + data;
	uint32_t br = RATE * 2;
	uint8_t hdr[44];

	memset(hdr, 0, sizeof(hdr));
	memcpy(hdr, "RIFF", 4);
	hdr[4] = (uint8_t)riff; hdr[5] = (uint8_t)(riff >> 8);
	hdr[6] = (uint8_t)(riff >> 16); hdr[7] = (uint8_t)(riff >> 24);
	memcpy(hdr + 8, "WAVEfmt ", 8);
	hdr[16] = 16;
	hdr[20] = 1;
	hdr[22] = 1;
	hdr[24] = (uint8_t)RATE; hdr[25] = (uint8_t)(RATE >> 8);
	hdr[28] = (uint8_t)br; hdr[29] = (uint8_t)(br >> 8);
	hdr[30] = (uint8_t)(br >> 16);
	hdr[32] = 2;
	hdr[34] = 16;
	memcpy(hdr + 36, "data", 4);
	hdr[40] = (uint8_t)data; hdr[41] = (uint8_t)(data >> 8);
	hdr[42] = (uint8_t)(data >> 16); hdr[43] = (uint8_t)(data >> 24);

	fp = fopen(path, "wb");
	if (!fp)
		return -1;
	if (fwrite(hdr, 1, 44, fp) != 44 ||
	    fwrite(pcm, 2, (size_t)n, fp) != (size_t)n) {
		fclose(fp);
		return -1;
	}
	fclose(fp);
	return 0;
}

static const char *find_play_audio(void)
{
	static const char *cands[] = {
		"/accounts/1000/shared/misc/clitools/bin/play-audio",
		"/accounts/1000/shared/misc/berrycore/bin/play-audio",
		"play-audio",
		NULL
	};
	int i;
	for (i = 0; cands[i]; i++) {
		if (cands[i][0] == '/' && access(cands[i], X_OK) == 0)
			return cands[i];
	}
	return "play-audio";
}

static int play_wav(const char *path, int ms)
{
	pid_t pid = fork();
	if (pid < 0)
		return -1;
	if (pid == 0) {
		execl(find_play_audio(), "play-audio", path, (char *)NULL);
		_exit(127);
	}
	usleep((useconds_t)(ms + 80) * 1000);
	kill(pid, SIGKILL);
	waitpid(pid, NULL, 0);
	return 0;
}

static int play_qsa(const int16_t *pcm, int n)
{
	snd_pcm_t *pcm_h = NULL;
	snd_pcm_channel_params_t params;
	int rc, wrote = 0;

	rc = snd_pcm_open_preferred(&pcm_h, NULL, NULL, SND_PCM_OPEN_PLAYBACK);
	if (rc != 0)
		rc = snd_pcm_open_name(&pcm_h, "pcmPreferredp", SND_PCM_OPEN_PLAYBACK);
	if (rc != 0 || !pcm_h)
		return -1;

	memset(&params, 0, sizeof(params));
	params.channel = SND_PCM_CHANNEL_PLAYBACK;
	params.mode = SND_PCM_MODE_BLOCK;
	params.format.format = SND_PCM_SFMT_S16_LE;
	params.format.rate = RATE;
	params.format.voices = 1;
	params.start_mode = SND_PCM_START_DATA;
	params.stop_mode = SND_PCM_STOP_STOP;
	params.buf.block.frag_size = 1024;
	params.buf.block.frags_min = 1;
	params.buf.block.frags_max = 4;

	if (snd_pcm_plugin_params(pcm_h, &params) != 0 ||
	    snd_pcm_plugin_prepare(pcm_h, SND_PCM_CHANNEL_PLAYBACK) != 0) {
		snd_pcm_close(pcm_h);
		return -1;
	}
	while (wrote < n * 2) {
		int r = snd_pcm_plugin_write(pcm_h, (char *)pcm + wrote,
					     (size_t)(n * 2 - wrote));
		if (r <= 0)
			break;
		wrote += r;
	}
	snd_pcm_plugin_flush(pcm_h, SND_PCM_CHANNEL_PLAYBACK);
	snd_pcm_close(pcm_h);
	return wrote > 0 ? 0 : -1;
}

static int play_hz(double hz, int ms)
{
	int n = RATE * ms / 1000;
	int16_t *pcm;
	char path[128];
	int rc;

	if (n < 64)
		n = 64;
	pcm = malloc((size_t)n * 2);
	if (!pcm)
		return -1;
	fill_sine(pcm, n, hz);
	rc = play_qsa(pcm, n);
	if (rc != 0) {
		snprintf(path, sizeof(path), "/var/tmp/piano-%d.wav", (int)getpid());
		if (write_wav(path, pcm, n) == 0) {
			printf("piano: qsa failed, play-audio %s\n", path);
			rc = play_wav(path, ms);
			unlink(path);
		}
	}
	free(pcm);
	return rc;
}

static void usage(void)
{
	fputs(
		"piano — Term49 sine piano\n"
		"\n"
		"  piano            interactive (asdfghjkl = C4..C5, q quit)\n"
		"  piano c4 [ms]    play a note (default 350 ms)\n"
		"  piano scale      C major\n"
		"\n"
		"Notes: c3..c5 (c4 d4 e4 f4 g4 a4 b4 c5)\n",
		stdout);
}

static int interactive(int ms)
{
	const char *map = "asdfghjk";
	const char *notes[] = { "c4", "d4", "e4", "f4", "g4", "a4", "b4", "c5" };
	int c, i;

	fputs("piano  asdfghjk = C D E F G A B C   q = quit\n", stdout);
	fflush(stdout);
	system("stty -icanon -echo min 1 2>/dev/null");
	while ((c = getchar()) != EOF) {
		if (c == 'q' || c == 'Q' || c == 3)
			break;
		if (c == '\n' || c == '\r')
			continue;
		for (i = 0; map[i]; i++) {
			if (c == map[i] || c == map[i] - 32) {
				printf("%s\n", notes[i]);
				fflush(stdout);
				play_hz(note_hz(notes[i]), ms);
				break;
			}
		}
	}
	system("stty icanon echo 2>/dev/null");
	return 0;
}

int main(int argc, char **argv)
{
	int ms = 350;
	int i;

	if (argc > 1 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "help") == 0)) {
		usage();
		return 0;
	}
	if (argc < 2)
		return interactive(ms);
	if (strcmp(argv[1], "scale") == 0) {
		static const char *s[] = { "c4", "d4", "e4", "f4", "g4", "a4", "b4", "c5", NULL };
		for (i = 0; s[i]; i++) {
			printf("%s\n", s[i]);
			play_hz(note_hz(s[i]), 220);
		}
		return 0;
	}
	if (argc >= 3)
		ms = atoi(argv[2]);
	if (ms < 40)
		ms = 40;
	if (ms > 4000)
		ms = 4000;
	for (i = 1; i < argc; i++) {
		double hz;
		if (i == 2 && argv[1][0] >= 'a' && argv[2][0] >= '0' && argv[2][0] <= '9')
			break;
		hz = note_hz(argv[i]);
		if (hz <= 0) {
			fprintf(stderr, "piano: unknown note %s\n", argv[i]);
			continue;
		}
		printf("%s %.2f Hz\n", argv[i], hz);
		play_hz(hz, ms);
	}
	return 0;
}
