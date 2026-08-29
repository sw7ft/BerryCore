/*
 * sensors — Term49 CLI for BB10 motion sensors (BPS + PPS fallback)
 *
 * Built for Passport / armle-v7. Links -lbps.
 */

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#include <bps/bps.h>
#include <bps/battery.h>
#include <bps/sensor.h>

#define RATE_US 40000 /* 25 Hz */

typedef struct {
	sensor_type_t type;
	const char *name;
	int reading_code;
	int kind; /* 0=xyz 1=light 2=prox 3=holster 4=apr 5=compass 6=orient 7=pressure */
} sensor_spec_t;

static const sensor_spec_t SPECS[] = {
	{ SENSOR_TYPE_ACCELEROMETER, "accel", SENSOR_ACCELEROMETER_READING, 0 },
	{ SENSOR_TYPE_GYROSCOPE, "gyro", SENSOR_GYROSCOPE_READING, 0 },
	{ SENSOR_TYPE_MAGNETOMETER, "mag", SENSOR_MAGNETOMETER_READING, 0 },
	{ SENSOR_TYPE_GRAVITY, "gravity", SENSOR_GRAVITY_READING, 0 },
	{ SENSOR_TYPE_LINEAR_ACCEL, "linaccel", SENSOR_LINEAR_ACCEL_READING, 0 },
	{ SENSOR_TYPE_AZIMUTH_PITCH_ROLL, "apr", SENSOR_AZIMUTH_PITCH_ROLL_READING, 4 },
	{ SENSOR_TYPE_COMPASS, "compass", SENSOR_COMPASS_READING, 5 },
	{ SENSOR_TYPE_ORIENTATION, "orient", SENSOR_ORIENTATION_READING, 6 },
	{ SENSOR_TYPE_LIGHT, "light", SENSOR_LIGHT_READING, 1 },
	{ SENSOR_TYPE_PROXIMITY, "prox", SENSOR_PROXIMITY_READING, 2 },
	{ SENSOR_TYPE_HOLSTER, "holster", SENSOR_HOLSTER_READING, 3 },
	{ SENSOR_TYPE_PRESSURE, "pressure", SENSOR_PRESSURE_READING, 7 },
	{ 0, NULL, 0, 0 }
};

static void usage(void)
{
	fputs(
		"sensors — BB10 motion sensors from Term49\n"
		"\n"
		"  sensors              one sample of every supported sensor\n"
		"  sensors accel        stream accelerometer (Ctrl-C to stop)\n"
		"  sensors gyro         stream gyroscope\n"
		"  sensors mag          stream magnetometer\n"
		"  sensors all          stream accel+gyro+mag\n"
		"  sensors pps          dump PPS fusion (holster, gestures)\n"
		"  sensors battery      charge, health, charger (BPS + PPS)\n"
		"  sensors cpu          ncpu + one hogs sample\n"
		"  sensors sys          battery + cpu\n"
		"  sensors list         supported types\n"
		"  sensors -n N ...     stop after N readings (default 1 for bare)\n"
		"  sensors -r US ...    sample period in microseconds (default 40000)\n"
		"\n"
		"Names: accel gyro mag gravity linaccel apr light prox holster all pps\n",
		stdout);
}

static void dump_pps(void)
{
	static const char *paths[] = {
		"/pps/services/sensor/hub_gestures",
		"/pps/services/sensor/holster",
		"/pps/services/accelerometer/status",
		"/pps/services/sensor/orientation",
		"/pps/services/sensor/doa",
		NULL
	};
	int i;
	for (i = 0; paths[i]; i++) {
		FILE *fp = fopen(paths[i], "r");
		printf("===== %s =====\n", paths[i]);
		if (!fp) {
			printf("(unreadable: %s)\n\n", strerror(errno));
			continue;
		}
		char buf[1024];
		size_t n;
		while ((n = fread(buf, 1, sizeof(buf), fp)) > 0)
			fwrite(buf, 1, n, stdout);
		if (buf[n ? n - 1 : 0] != '\n')
			putchar('\n');
		putchar('\n');
		fclose(fp);
	}
}

static const char *charger_name(int s)
{
	switch (s) {
	case BATTERY_CHARGER_ERROR: return "error";
	case BATTERY_CHARGER_BAD: return "bad";
	case BATTERY_CHARGER_NONE: return "none";
	case BATTERY_CHARGER_PLUGGED: return "plugged";
	case BATTERY_CHARGER_CHARGING: return "charging";
	default: return "unknown";
	}
}

static const char *charging_name(int s)
{
	switch (s) {
	case BATTERY_CHARGING_NOT_CHARGING: return "not-charging";
	case BATTERY_CHARGING_TRICKLE_CHARGING: return "trickle";
	case BATTERY_CHARGING_CONSTANT_CURRENT: return "cc";
	case BATTERY_CHARGING_CONSTANT_VOLTAGE: return "cv";
	case BATTERY_CHARGING_DONE_CHARGING: return "done";
	default: return "unknown";
	}
}

static void dump_batt_pps(void)
{
	FILE *fp = fopen("/pps/system/BattMgr/status", "r");
	if (!fp) {
		printf("battery pps: %s\n", strerror(errno));
		return;
	}
	printf("===== /pps/system/BattMgr/status =====\n");
	{
		char buf[2048];
		size_t n;
		while ((n = fread(buf, 1, sizeof(buf), fp)) > 0)
			fwrite(buf, 1, n, stdout);
	}
	putchar('\n');
	fclose(fp);
}

static int cmd_battery(void)
{
	battery_info_t *info = NULL;
	int rc = 1;

	if (bps_initialize() != BPS_SUCCESS) {
		fprintf(stderr, "sensors: bps_initialize: %s\n", strerror(errno));
		dump_batt_pps();
		return 1;
	}
	if (battery_get_info(&info) != BPS_SUCCESS || !info) {
		printf("battery: bps get_info failed (%s)\n", strerror(errno));
		dump_batt_pps();
		bps_shutdown();
		return 1;
	}
	printf("battery  charge=%d%%  health=%d%%  voltage=%d mV  temp=%.1f C\n",
	       battery_info_get_state_of_charge(info),
	       battery_info_get_state_of_health(info),
	       battery_info_get_battery_voltage(info),
	       battery_info_get_battery_temperature(info));
	{
		int tte = battery_info_get_time_to_empty(info);
		int ttf = battery_info_get_time_to_full(info);
		int cycles = battery_info_get_battery_cycle_count(info);
		printf("         cycles=%d  tte=", cycles);
		if (tte == BATTERY_TIME_NA)
			fputs("n/a", stdout);
		else
			printf("%d min", tte);
		fputs("  ttf=", stdout);
		if (ttf == BATTERY_TIME_NA)
			fputs("n/a", stdout);
		else
			printf("%d min", ttf);
		printf("  alert=%s\n",
		       battery_info_get_battery_alert(info) ? "yes" : "no");
	}
	printf("         charger=%s  charging=%s  present=%s\n",
	       charger_name(battery_info_get_charger_info(info)),
	       charging_name(battery_info_get_system_charging_state(info)),
	       battery_info_is_battery_present(info) ? "yes" : "no");
	battery_free_info(&info);
	bps_shutdown();
	rc = 0;
	return rc;
}

static int cmd_cpu(void)
{
	FILE *fp;
	char line[256];
	long ncpu;
	int printed = 0;

	ncpu = sysconf(_SC_NPROCESSORS_ONLN);
	if (ncpu < 1)
		ncpu = sysconf(_SC_NPROCESSORS_CONF);
	printf("cpu  ncpu=%ld\n", ncpu);
	fp = popen("hogs -i 1 2>/dev/null", "r");
	if (!fp) {
		printf("cpu  hogs: %s\n", strerror(errno));
		return 1;
	}
	while (fgets(line, sizeof(line), fp)) {
		/* Keep the header and any row with a process name or non-zero SYS. */
		if (strstr(line, "PID") && strstr(line, "SYS")) {
			fputs(line, stdout);
			continue;
		}
		if (strstr(line, "%") && !strstr(line, "   0%   0%")) {
			fputs(line, stdout);
			printed++;
			continue;
		}
		/* named processes even at 0% */
		{
			const char *p = line;
			int digits = 0, letters = 0;
			while (*p == ' ')
				p++;
			while (*p >= '0' && *p <= '9') {
				digits++;
				p++;
			}
			while (*p == ' ')
				p++;
			while ((*p >= 'A' && *p <= 'Z') || (*p >= 'a' && *p <= 'z') || *p == '_' || *p == '/') {
				letters++;
				p++;
			}
			if (digits && letters) {
				fputs(line, stdout);
				printed++;
			}
		}
	}
	pclose(fp);
	if (!printed)
		printf("cpu  hogs: no named / busy processes (syspage may be restricted)\n");
	return 0;
}

static const sensor_spec_t *find_spec(const char *name)
{
	const sensor_spec_t *s;
	for (s = SPECS; s->name; s++) {
		if (strcmp(s->name, name) == 0)
			return s;
	}
	return NULL;
}

static int enable_one(const sensor_spec_t *s, unsigned rate_us)
{
	if (!sensor_is_supported(s->type)) {
		fprintf(stderr, "sensors: %s not supported\n", s->name);
		return -1;
	}
	if (sensor_request_events(s->type) != BPS_SUCCESS) {
		fprintf(stderr, "sensors: request %s failed: %s\n", s->name, strerror(errno));
		return -1;
	}
	/* CLI has no window — ask the service to run while "backgrounded". */
	if (sensor_set_background(s->type, true) != BPS_SUCCESS)
		fprintf(stderr, "sensors: %s background denied (%s) — live xyz may stay quiet\n",
			s->name, strerror(errno));
	sensor_set_rate(s->type, rate_us);
	sensor_set_skip_duplicates(s->type, 0);
	return 0;
}

static void print_event(bps_event_t *event)
{
	int code = bps_event_get_code(event);
	const sensor_spec_t *s;
	float x, y, z;

	for (s = SPECS; s->name; s++) {
		if (code != s->reading_code)
			continue;
		switch (s->kind) {
		case 0:
			sensor_event_get_xyz(event, &x, &y, &z);
			printf("%-8s  %10.5f  %10.5f  %10.5f\n", s->name, x, y, z);
			break;
		case 1:
			printf("%-8s  illuminance=%.3f lux\n", s->name, sensor_event_get_illuminance(event));
			break;
		case 2:
			printf("%-8s  proximity=%.3f\n", s->name, sensor_event_get_proximity(event));
			break;
		case 3: {
			bool holstered = false;
			sensor_event_is_holstered(event, &holstered);
			printf("%-8s  holstered=%s\n", s->name, holstered ? "yes" : "no");
			break;
		}
		case 4:
			sensor_event_get_apr(event, &x, &y, &z);
			printf("%-8s  azimuth=%.2f  pitch=%.2f  roll=%.2f\n", s->name, x, y, z);
			break;
		case 5:
			printf("%-8s  heading=%.1f\n", s->name, sensor_event_get_heading(event));
			break;
		case 6:
			printf("%-8s  angle=%d  face=%d\n", s->name,
			       sensor_event_get_orientation_angle(event),
			       sensor_event_get_orientation_face(event));
			break;
		case 7:
			printf("%-8s  pressure=%.1f Pa\n", s->name, sensor_event_get_pressure(event));
			break;
		default:
			break;
		}
		fflush(stdout);
		return;
	}
}

static int run_bps(char **names, int nnames, int count, unsigned rate_us)
{
	int i, got = 0, enabled = 0;

	if (bps_initialize() != BPS_SUCCESS) {
		fprintf(stderr, "sensors: bps_initialize failed: %s\n", strerror(errno));
		return 1;
	}

	for (i = 0; i < nnames; i++) {
		const sensor_spec_t *s = find_spec(names[i]);
		if (!s) {
			fprintf(stderr, "sensors: unknown %s\n", names[i]);
			continue;
		}
		if (enable_one(s, rate_us) == 0)
			enabled++;
	}

	if (!enabled) {
		fputs("sensors: no sensors enabled — try: sensors pps\n", stderr);
		bps_shutdown();
		return 1;
	}

	printf("# name             x          y          z\n");
	fflush(stdout);

	{
		int idle = 0;
		while (count < 0 || got < count) {
			bps_event_t *event = NULL;
			if (bps_get_event(&event, 1500) != BPS_SUCCESS) {
				fprintf(stderr, "sensors: bps_get_event: %s\n", strerror(errno));
				break;
			}
			if (!event) {
				idle++;
				if (count >= 0 && idle >= 4 && got == 0) {
					fputs("sensors: no readings (sensor-services not publishing — try sensors pps, or move the phone)\n",
					      stderr);
					break;
				}
				if (count >= 0 && idle >= 8)
					break;
				continue;
			}
			idle = 0;
			if (bps_event_get_domain(event) == sensor_get_domain()) {
				print_event(event);
				got++;
			}
		}
	}

	for (i = 0; i < nnames; i++) {
		const sensor_spec_t *s = find_spec(names[i]);
		if (s)
			sensor_stop_events(s->type);
	}
	bps_shutdown();
	return 0;
}

static int cmd_list(void)
{
	const sensor_spec_t *s;
	if (bps_initialize() != BPS_SUCCESS) {
		fprintf(stderr, "sensors: bps_initialize failed: %s\n", strerror(errno));
		return 1;
	}
	printf("%-10s  %s\n", "name", "supported");
	for (s = SPECS; s->name; s++)
		printf("%-10s  %s\n", s->name, sensor_is_supported(s->type) ? "yes" : "no");
	bps_shutdown();
	return 0;
}

int main(int argc, char **argv)
{
	int count = -1;
	unsigned rate_us = RATE_US;
	int opt;

	while ((opt = getopt(argc, argv, "n:r:h")) != -1) {
		switch (opt) {
		case 'n':
			count = atoi(optarg);
			break;
		case 'r':
			rate_us = (unsigned)atoi(optarg);
			if (rate_us < 5000)
				rate_us = 5000;
			break;
		case 'h':
		default:
			usage();
			return opt == 'h' ? 0 : 1;
		}
	}

	if (optind >= argc) {
		static char *ones[] = {
			"accel", "gyro", "mag", "gravity", "linaccel",
			"apr", "compass", "orient", "light", "prox", "holster"
		};
		int rc;
		if (count < 0)
			count = 1;
		rc = run_bps(ones, 11, count, rate_us);
		putchar('\n');
		cmd_battery();
		putchar('\n');
		cmd_cpu();
		return rc;
	}

	if (strcmp(argv[optind], "help") == 0) {
		usage();
		return 0;
	}
	if (strcmp(argv[optind], "pps") == 0) {
		dump_pps();
		return 0;
	}
	if (strcmp(argv[optind], "list") == 0)
		return cmd_list();
	if (strcmp(argv[optind], "battery") == 0 || strcmp(argv[optind], "batt") == 0)
		return cmd_battery();
	if (strcmp(argv[optind], "cpu") == 0)
		return cmd_cpu();
	if (strcmp(argv[optind], "sys") == 0) {
		int rc = cmd_battery();
		putchar('\n');
		return cmd_cpu() || rc;
	}

	if (strcmp(argv[optind], "all") == 0) {
		static char *all[] = { "accel", "gyro", "mag" };
		return run_bps(all, 3, count, rate_us);
	}

	return run_bps(&argv[optind], argc - optind, count, rate_us);
}
