/*
 * fm — Term49 FM tuner via OpenMAX AL (XA_IID_RADIO + RDS)
 *
 * Built for Passport / armle-v7. Links -lOpenMAXAL.
 * Headset wire is usually the antenna. Same BCM4339 as Wi-Fi.
 */
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <OMXAL/OpenMAXAL.h>
#include <OMXAL/OpenMAXAL_FMUtil.h>

static volatile sig_atomic_t g_stop;
static volatile sig_atomic_t g_seek_done;

static void on_sig(int sig)
{
	(void)sig;
	g_stop = 1;
}

static void usage(void)
{
	fputs(
		"fm — analog FM from Term49 (OpenMAX AL)\n"
		"\n"
		"  fm                 availability + this help\n"
		"  fm avail           fmIsRadioAvailable (no tune)\n"
		"  fm 95.1 [sec]      tune and play (default: until Ctrl-C)\n"
		"  fm on 95.1 [sec]   same\n"
		"  fm seek [up|down]  seek and print the stop\n"
		"  fm now [95.1]      frequency, strength, stereo, RDS\n"
		"  fm scan            seek up around the band once\n"
		"  fm status          range + current frequency if the radio opens\n"
		"  fm off             stop note (this CLI is process-local)\n"
		"\n"
		"Freq: 95.1 or 95100 (kHz). Headset is usually the antenna.\n"
		"Do not leave it running on the Wi-Fi hop — same combo chip.\n"
		"\n",
		stdout);
}

static const char *avail_name(int c)
{
	switch (c) {
	case FM_RADIO_AVAILABLE:
		return "available";
	case FM_RADIO_CARRIER_DISABLED:
		return "carrier_disabled";
	case FM_RADIO_MCC_DISABLED:
		return "mcc_disabled";
	case FM_RADIO_HARDWARE_NOT_SUPPORTED:
		return "hardware_not_supported";
	case FM_RADIO_IT_POLICY_DISABLED:
		return "it_policy_disabled";
	default:
		return "unknown";
	}
}

static const char *xaerr(XAresult r)
{
	switch (r) {
	case XA_RESULT_SUCCESS:
		return "SUCCESS";
	case XA_RESULT_PRECONDITIONS_VIOLATED:
		return "PRECONDITIONS_VIOLATED";
	case XA_RESULT_PARAMETER_INVALID:
		return "PARAMETER_INVALID";
	case XA_RESULT_RESOURCE_ERROR:
		return "RESOURCE_ERROR";
	case XA_RESULT_RESOURCE_LOST:
		return "RESOURCE_LOST";
	case XA_RESULT_IO_ERROR:
		return "IO_ERROR";
	case XA_RESULT_PERMISSION_DENIED:
		return "PERMISSION_DENIED";
	case XA_RESULT_FEATURE_UNSUPPORTED:
		return "FEATURE_UNSUPPORTED";
	case XA_RESULT_INTERNAL_ERROR:
		return "INTERNAL_ERROR";
	case XA_RESULT_UNKNOWN_ERROR:
		return "UNKNOWN_ERROR";
	case XA_RESULT_OPERATION_ABORTED:
		return "OPERATION_ABORTED";
	case XA_RESULT_CONTROL_LOST:
		return "CONTROL_LOST";
	default:
		return "OTHER";
	}
}

static int cmd_avail(void)
{
	int c = fmIsRadioAvailable();

	printf("fmIsRadioAvailable=%d (%s)\n", c, avail_name(c));
	if (c == FM_RADIO_AVAILABLE)
		puts("ok to try fm 95.1 / fm now / fm seek");
	else
		puts("radio blocked or missing — tune will likely fail");
	return c == FM_RADIO_AVAILABLE ? 0 : 1;
}

struct fm {
	XAObjectItf engine;
	XAObjectItf mix;
	XAObjectItf player;
	XAEngineItf eng;
	XARadioItf radio;
	XAPlayItf play;
	XARDSItf rds;
	XAuint32 min_hz;
	XAuint32 max_hz;
	XAuint32 step_hz;
	int native_is_khz;
};

static void radio_cb(XARadioItf caller, void *ctx, XAuint32 event,
		     XAuint32 eventIntData, XAboolean eventBooleanData)
{
	(void)caller;
	(void)ctx;
	(void)eventIntData;
	(void)eventBooleanData;
	if (event == XA_RADIO_EVENT_SEEK_COMPLETED)
		g_seek_done = 1;
}

static int xa_ok(const char *what, XAresult r)
{
	if (r == XA_RESULT_SUCCESS)
		return 0;
	fprintf(stderr, "fm: %s: 0x%x %s\n", what, (unsigned)r, xaerr(r));
	return -1;
}

static void fm_close(struct fm *f)
{
	if (!f)
		return;
	if (f->play)
		(*f->play)->SetPlayState(f->play, XA_PLAYSTATE_STOPPED);
	if (f->player) {
		(*f->player)->Destroy(f->player);
		f->player = NULL;
	}
	if (f->mix) {
		(*f->mix)->Destroy(f->mix);
		f->mix = NULL;
	}
	if (f->engine) {
		(*f->engine)->Destroy(f->engine);
		f->engine = NULL;
	}
	f->radio = NULL;
	f->play = NULL;
	f->rds = NULL;
	f->eng = NULL;
}

static int fm_open(struct fm *f)
{
	XADataLocator_IODevice loc_in;
	XADataSource src;
	XADataLocator_OutputMix loc_out;
	XADataSink snk;
	XAInterfaceID iids[3];
	XAboolean req[3];
	XAuint8 range = XA_FREQRANGE_FMEUROAMERICA;
	XAuint32 minf = 0, maxf = 0, step = 0;
	XAresult r;

	memset(f, 0, sizeof(*f));

	r = xaCreateEngine(&f->engine, 0, NULL, 0, NULL, NULL);
	if (xa_ok("xaCreateEngine", r))
		return -1;
	if (xa_ok("engine Realize", (*f->engine)->Realize(f->engine, XA_BOOLEAN_FALSE)))
		goto fail;
	if (xa_ok("XA_IID_ENGINE", (*f->engine)->GetInterface(f->engine, XA_IID_ENGINE, &f->eng)))
		goto fail;

	if (xa_ok("CreateOutputMix",
		  (*f->eng)->CreateOutputMix(f->eng, &f->mix, 0, NULL, NULL)))
		goto fail;
	if (xa_ok("mix Realize", (*f->mix)->Realize(f->mix, XA_BOOLEAN_FALSE)))
		goto fail;

	memset(&loc_in, 0, sizeof(loc_in));
	loc_in.locatorType = XA_DATALOCATOR_IODEVICE;
	loc_in.deviceType = XA_IODEVICE_RADIO;
	loc_in.deviceID = XA_DEFAULTDEVICEID_AUDIOINPUT;
	loc_in.device = NULL;
	src.pLocator = &loc_in;
	src.pFormat = NULL;

	memset(&loc_out, 0, sizeof(loc_out));
	loc_out.locatorType = XA_DATALOCATOR_OUTPUTMIX;
	loc_out.outputMix = f->mix;
	snk.pLocator = &loc_out;
	snk.pFormat = NULL;

	iids[0] = XA_IID_RADIO;
	iids[1] = XA_IID_PLAY;
	iids[2] = XA_IID_RDS;
	req[0] = XA_BOOLEAN_TRUE;
	req[1] = XA_BOOLEAN_TRUE;
	req[2] = XA_BOOLEAN_FALSE;

	r = (*f->eng)->CreateMediaPlayer(f->eng, &f->player, &src, NULL, &snk,
					 NULL, NULL, NULL, 3, iids, req);
	if (xa_ok("CreateMediaPlayer(RADIO)", r))
		goto fail;
	if (xa_ok("player Realize", (*f->player)->Realize(f->player, XA_BOOLEAN_FALSE)))
		goto fail;
	if (xa_ok("XA_IID_RADIO", (*f->player)->GetInterface(f->player, XA_IID_RADIO, &f->radio)))
		goto fail;
	if (xa_ok("XA_IID_PLAY", (*f->player)->GetInterface(f->player, XA_IID_PLAY, &f->play)))
		goto fail;
	r = (*f->player)->GetInterface(f->player, XA_IID_RDS, &f->rds);
	if (r != XA_RESULT_SUCCESS)
		f->rds = NULL;

	if ((*f->radio)->GetFreqRange(f->radio, &range) == XA_RESULT_SUCCESS)
		printf("range=%u\n", (unsigned)range);
	if ((*f->radio)->GetFreqRangeProperties(f->radio, range, &minf, &maxf, &step)
	    == XA_RESULT_SUCCESS) {
		f->min_hz = minf;
		f->max_hz = maxf;
		f->step_hz = step;
		/* BB10 / Khronos radio freqs are usually kHz (87500..108000). */
		f->native_is_khz = (maxf > 200 && maxf < 2000000);
		printf("band=%u..%u step=%u (%s)\n",
		       (unsigned)minf, (unsigned)maxf, (unsigned)step,
		       f->native_is_khz ? "kHz" : "Hz");
	} else {
		f->min_hz = 87500;
		f->max_hz = 108000;
		f->step_hz = 100;
		f->native_is_khz = 1;
	}

	(*f->radio)->RegisterRadioCallback(f->radio, radio_cb, NULL);
	return 0;
fail:
	fm_close(f);
	return -1;
}

/* Parse 95.1 / 95100 / 95100000 into native tuner units. */
static int parse_freq(struct fm *f, const char *s, XAuint32 *out)
{
	char *end = NULL;
	double v;
	double mhz;
	XAuint32 native;

	if (!s || !*s)
		return -1;
	v = strtod(s, &end);
	if (end == s || v <= 0)
		return -1;

	if (strchr(s, '.') != NULL || v < 200.0)
		mhz = v;
	else if (v < 200000.0)
		mhz = v / 1000.0;
	else
		mhz = v / 1000000.0;

	if (mhz < 65.0 || mhz > 110.0) {
		fprintf(stderr, "fm: frequency out of FM band: %s\n", s);
		return -1;
	}

	if (f->native_is_khz)
		native = (XAuint32)(mhz * 1000.0 + 0.5);
	else
		native = (XAuint32)(mhz * 1000000.0 + 0.5);

	if (f->step_hz > 1)
		native = (native / f->step_hz) * f->step_hz;
	if (f->min_hz && native < f->min_hz)
		native = f->min_hz;
	if (f->max_hz && native > f->max_hz)
		native = f->max_hz;
	*out = native;
	return 0;
}

static void print_freq(const char *label, XAuint32 native, int is_khz)
{
	double mhz = is_khz ? (native / 1000.0) : (native / 1000000.0);

	printf("%s=%.1f native=%u\n", label, mhz, (unsigned)native);
}

static int play_on(struct fm *f)
{
	return xa_ok("SetPlayState(PLAYING)",
		     (*f->play)->SetPlayState(f->play, XA_PLAYSTATE_PLAYING));
}

static void dump_now(struct fm *f)
{
	XAuint32 freq = 0, strength = 0, stereo = 0;
	XAboolean squelch = XA_BOOLEAN_FALSE;
	XAchar ps[16];
	XAchar rt[80];
	XAchar pty[32];
	XAuint32 ptype = 0;
	XAint16 pi = 0;
	XAboolean ta = XA_BOOLEAN_FALSE, tp = XA_BOOLEAN_FALSE;

	if ((*f->radio)->GetFrequency(f->radio, &freq) == XA_RESULT_SUCCESS)
		print_freq("freq", freq, f->native_is_khz);
	if ((*f->radio)->GetSignalStrength(f->radio, &strength) == XA_RESULT_SUCCESS)
		printf("strength=%u\n", (unsigned)strength);
	if ((*f->radio)->GetStereoMode(f->radio, &stereo) == XA_RESULT_SUCCESS)
		printf("stereo=%u (0=mono 1=stereo 2=auto)\n", (unsigned)stereo);
	if ((*f->radio)->GetSquelch(f->radio, &squelch) == XA_RESULT_SUCCESS)
		printf("squelch=%u\n", (unsigned)squelch);

	if (!f->rds) {
		puts("rds=unavailable");
		return;
	}
	memset(ps, 0, sizeof(ps));
	memset(rt, 0, sizeof(rt));
	memset(pty, 0, sizeof(pty));
	if ((*f->rds)->GetProgrammeServiceName(f->rds, ps) == XA_RESULT_SUCCESS && ps[0])
		printf("rds.ps=%s\n", (char *)ps);
	if ((*f->rds)->GetRadioText(f->rds, rt) == XA_RESULT_SUCCESS && rt[0])
		printf("rds.rt=%s\n", (char *)rt);
	if ((*f->rds)->GetProgrammeType(f->rds, &ptype) == XA_RESULT_SUCCESS)
		printf("rds.pty=%u\n", (unsigned)ptype);
	if ((*f->rds)->GetProgrammeTypeString(f->rds, XA_BOOLEAN_TRUE, pty) == XA_RESULT_SUCCESS
	    && pty[0])
		printf("rds.pty_str=%s\n", (char *)pty);
	if ((*f->rds)->GetProgrammeIdentificationCode(f->rds, &pi) == XA_RESULT_SUCCESS)
		printf("rds.pi=0x%04x\n", (unsigned)(pi & 0xffff));
	if ((*f->rds)->GetTrafficAnnouncement(f->rds, &ta) == XA_RESULT_SUCCESS)
		printf("rds.ta=%u\n", (unsigned)ta);
	if ((*f->rds)->GetTrafficProgramme(f->rds, &tp) == XA_RESULT_SUCCESS)
		printf("rds.tp=%u\n", (unsigned)tp);
}

static int wait_secs(int sec)
{
	int i;

	if (sec <= 0) {
		while (!g_stop)
			sleep(1);
		return 0;
	}
	for (i = 0; i < sec && !g_stop; i++)
		sleep(1);
	return 0;
}

static int cmd_tune(const char *freq_s, int sec)
{
	struct fm f;
	XAuint32 native;

	if (fm_open(&f) != 0)
		return 1;
	if (parse_freq(&f, freq_s, &native) != 0) {
		fm_close(&f);
		return 1;
	}
	if (xa_ok("SetFrequency", (*f.radio)->SetFrequency(f.radio, native))) {
		fm_close(&f);
		return 1;
	}
	print_freq("tune", native, f.native_is_khz);
	if (play_on(&f) != 0) {
		fm_close(&f);
		return 1;
	}
	if (sec > 0)
		printf("playing %d s (Ctrl-C stops)\n", sec);
	else
		puts("playing until Ctrl-C");
	wait_secs(sec);
	dump_now(&f);
	fm_close(&f);
	return 0;
}

static int cmd_seek(int up)
{
	struct fm f;
	int i;

	if (fm_open(&f) != 0)
		return 1;
	if (play_on(&f) != 0) {
		fm_close(&f);
		return 1;
	}
	g_seek_done = 0;
	if (xa_ok("Seek", (*f.radio)->Seek(f.radio, up ? XA_BOOLEAN_TRUE : XA_BOOLEAN_FALSE))) {
		fm_close(&f);
		return 1;
	}
	for (i = 0; i < 20 && !g_seek_done && !g_stop; i++)
		sleep(1);
	if (!g_seek_done)
		puts("seek: timeout (no SEEK_COMPLETED)");
	dump_now(&f);
	fm_close(&f);
	return 0;
}

static int cmd_now(const char *freq_s)
{
	struct fm f;
	XAuint32 native;

	if (fm_open(&f) != 0)
		return 1;
	if (freq_s) {
		if (parse_freq(&f, freq_s, &native) != 0) {
			fm_close(&f);
			return 1;
		}
		if (xa_ok("SetFrequency", (*f.radio)->SetFrequency(f.radio, native))) {
			fm_close(&f);
			return 1;
		}
	}
	play_on(&f);
	sleep(2);
	dump_now(&f);
	fm_close(&f);
	return 0;
}

static int cmd_status(void)
{
	struct fm f;
	int avail = fmIsRadioAvailable();

	printf("fmIsRadioAvailable=%d (%s)\n", avail, avail_name(avail));
	if (fm_open(&f) != 0)
		return 1;
	dump_now(&f);
	fm_close(&f);
	return 0;
}

static int cmd_scan(void)
{
	struct fm f;
	int n;

	if (fm_open(&f) != 0)
		return 1;
	if (play_on(&f) != 0) {
		fm_close(&f);
		return 1;
	}
	puts("scan: seek-up x8 (Ctrl-C abort)");
	for (n = 0; n < 8 && !g_stop; n++) {
		int i;

		g_seek_done = 0;
		if (xa_ok("Seek", (*f.radio)->Seek(f.radio, XA_BOOLEAN_TRUE)))
			break;
		for (i = 0; i < 15 && !g_seek_done && !g_stop; i++)
			sleep(1);
		printf("-- hit %d --\n", n + 1);
		dump_now(&f);
	}
	fm_close(&f);
	return 0;
}

int main(int argc, char **argv)
{
	const char *cmd;
	int sec = 0;

	signal(SIGINT, on_sig);
	signal(SIGTERM, on_sig);

	if (argc < 2) {
		cmd_avail();
		usage();
		return 0;
	}
	cmd = argv[1];

	if (strcmp(cmd, "-h") == 0 || strcmp(cmd, "--help") == 0 || strcmp(cmd, "help") == 0) {
		usage();
		return 0;
	}
	if (strcmp(cmd, "avail") == 0 || strcmp(cmd, "available") == 0)
		return cmd_avail();
	if (strcmp(cmd, "off") == 0 || strcmp(cmd, "stop") == 0) {
		puts("fm is process-local — Ctrl-C the playing fm, or it already stopped");
		return 0;
	}
	if (strcmp(cmd, "status") == 0)
		return cmd_status();
	if (strcmp(cmd, "scan") == 0)
		return cmd_scan();
	if (strcmp(cmd, "seek") == 0) {
		int up = 1;

		if (argc >= 3 && (strcmp(argv[2], "down") == 0 || strcmp(argv[2], "-") == 0))
			up = 0;
		return cmd_seek(up);
	}
	if (strcmp(cmd, "now") == 0)
		return cmd_now(argc >= 3 ? argv[2] : NULL);
	if (strcmp(cmd, "on") == 0 || strcmp(cmd, "tune") == 0) {
		if (argc < 3) {
			fputs("fm: need a frequency (fm on 95.1)\n", stderr);
			return 1;
		}
		if (argc >= 4)
			sec = atoi(argv[3]);
		return cmd_tune(argv[2], sec);
	}
	if (cmd[0] >= '0' && cmd[0] <= '9') {
		if (argc >= 3)
			sec = atoi(argv[2]);
		return cmd_tune(cmd, sec);
	}

	fprintf(stderr, "fm: unknown command: %s\n", cmd);
	usage();
	return 1;
}
