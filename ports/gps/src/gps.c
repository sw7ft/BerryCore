/*
 * gps — Term49 CLI for BB10 geolocation (BPS + PPS fallback)
 *
 * Built for Passport / armle-v7. Links -lbps.
 */

#include <bps/bps.h>
#include <bps/geolocation.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static const char *provider_name(int p)
{
	switch (p) {
	case GEOLOCATION_PROVIDER_HYBRID: return "hybrid";
	case GEOLOCATION_PROVIDER_GNSS: return "gnss";
	case GEOLOCATION_PROVIDER_NETWORK: return "network";
	default: return "unknown";
	}
}

static const char *fix_name(int f)
{
	switch (f) {
	case GEOLOCATION_FIX_TYPE_BEST: return "best";
	case GEOLOCATION_FIX_TYPE_GPS_MS_BASED: return "ms-based";
	case GEOLOCATION_FIX_TYPE_GPS_MS_ASSISTED: return "ms-assisted";
	case GEOLOCATION_FIX_TYPE_GPS_AUTONOMOUS: return "autonomous";
	case GEOLOCATION_FIX_TYPE_CELLSITE: return "cell";
	case GEOLOCATION_FIX_TYPE_WIFI: return "wifi";
	default: return "unknown";
	}
}

static void usage(void)
{
	fputs(
		"gps — BB10 location from Term49\n"
		"\n"
		"  gps              wait for one fix (last-known, then live)\n"
		"  gps last         last known position only\n"
		"  gps watch        stream fixes (Ctrl-C)\n"
		"  gps sats         one fix plus satellite list\n"
		"  gps pps          dump readable geolocation PPS\n"
		"  gps -n N         stop after N INFO events\n"
		"  gps -t SEC       give up after SEC seconds (default 45)\n"
		"  gps -p gnss|hybrid|network   provider (default hybrid)\n"
		"\n",
		stdout);
}

static void dump_pps(void)
{
	static const char *paths[] = {
		"/pps/services/geolocation/status",
		"/pps/services/geolocation/country/status",
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
		putchar('\n');
		fclose(fp);
	}
}

static void print_info(bps_event_t *event, int sats)
{
	double lat = geolocation_event_get_latitude(event);
	double lon = geolocation_event_get_longitude(event);
	double acc = geolocation_event_get_accuracy(event);
	int prov = geolocation_event_get_provider(event);
	int fix = geolocation_event_get_fix_type(event);
	int used = geolocation_event_get_num_satellites_used(event);
	int total = geolocation_event_get_num_satellites_total(event);

	printf("fix  lat=%.6f lon=%.6f", lat, lon);
	if (geolocation_event_is_accuracy_valid(event))
		printf("  acc=%.1fm", acc);
	if (geolocation_event_is_altitude_valid(event))
		printf("  alt=%.1fm", geolocation_event_get_altitude(event));
	if (geolocation_event_is_heading_valid(event))
		printf("  hdg=%.1f", geolocation_event_get_heading(event));
	if (geolocation_event_is_speed_valid(event))
		printf("  spd=%.2f", geolocation_event_get_speed(event));
	printf("  via=%s/%s", provider_name(prov), fix_name(fix));
	if (geolocation_event_is_num_satellites_valid(event))
		printf("  sats=%d/%d", used, total);
	if (geolocation_event_is_hdop_valid(event))
		printf("  hdop=%.2f", geolocation_event_get_hdop(event));
	if (geolocation_event_is_coarse(event))
		printf("  coarse");
	putchar('\n');
	fflush(stdout);

	if (sats && geolocation_event_is_num_satellites_valid(event) && total > 0) {
		int i;
		for (i = 0; i < total; i++) {
			printf("  sat[%d] id=%d  c/n=%.1f  az=%.0f el=%.0f  %s%s\n",
			       i,
			       geolocation_event_get_satellite_id(event, i),
			       geolocation_event_get_satellite_carrier_to_noise_ratio(event, i),
			       geolocation_event_get_satellite_azimuth(event, i),
			       geolocation_event_get_satellite_elevation(event, i),
			       geolocation_event_get_satellite_is_tracked(event, i) ? "trk " : "",
			       geolocation_event_get_satellite_is_used(event, i) ? "used" : "");
		}
		fflush(stdout);
	}
}

static void print_error(bps_event_t *event)
{
	int code = geolocation_event_get_error_code(event);
	const char *msg = geolocation_event_get_error_message(event);
	const char *name = "unknown";
	switch (code) {
	case GEOLOCATION_ERROR_NONE: name = "none"; break;
	case GEOLOCATION_ERROR_FATAL_DISABLED: name = "disabled"; break;
	case GEOLOCATION_ERROR_FATAL_NO_LAST_KNOWN_POSITION: name = "no-last-known"; break;
	case GEOLOCATION_ERROR_FATAL_INSUFFICIENT_PROVIDERS: name = "no-providers"; break;
	case GEOLOCATION_ERROR_FATAL_INVALID_REQUEST: name = "invalid-request"; break;
	case GEOLOCATION_ERROR_FATAL_PERMISSION: name = "permission"; break;
	case GEOLOCATION_ERROR_WARN_TIMEOUT: name = "timeout"; break;
	case GEOLOCATION_ERROR_WARN_LOST_TRACKING: name = "lost-tracking"; break;
	case GEOLOCATION_ERROR_WARN_STATIONARY: name = "stationary"; break;
	default: break;
	}
	fprintf(stderr, "gps: error %s (%d) %s\n", name, code, msg ? msg : "");
}

static int run(int count, int timeout_s, int last_known, int sats,
	       geolocation_provider_t provider)
{
	int got = 0, idle = 0;
	int limit = timeout_s * 2; /* 500 ms polls */

	if (bps_initialize() != BPS_SUCCESS) {
		fprintf(stderr, "gps: bps_initialize failed: %s\n", strerror(errno));
		return 1;
	}

	geolocation_set_background(true);
	geolocation_set_period(1);
	geolocation_set_accuracy(50);
	geolocation_set_response_time(16);
	geolocation_set_last_known(last_known ? true : true);
	geolocation_set_provider(provider);
	if (sats)
		geolocation_set_report_satellite_info(true);

	if (geolocation_request_events(0) != BPS_SUCCESS) {
		fprintf(stderr, "gps: request_events failed: %s\n", strerror(errno));
		bps_shutdown();
		return 1;
	}
	geolocation_request_status();

	printf("# waiting for fix (timeout %ds, last-known %s)\n",
	       timeout_s, last_known ? "only" : "then live");
	fflush(stdout);

	while (count < 0 || got < count) {
		bps_event_t *event = NULL;
		if (bps_get_event(&event, 500) != BPS_SUCCESS) {
			fprintf(stderr, "gps: bps_get_event: %s\n", strerror(errno));
			break;
		}
		if (!event) {
			idle++;
			if (idle >= limit) {
				fputs("gps: no fix in time (GNSS on but no subscriber data — permission or no sky)\n",
				      stderr);
				break;
			}
			continue;
		}
		if (bps_event_get_domain(event) != geolocation_get_domain())
			continue;
		switch (bps_event_get_code(event)) {
		case GEOLOCATION_INFO:
			print_info(event, sats);
			got++;
			idle = 0;
			if (last_known && got >= 1 && count == 1)
				goto done;
			break;
		case GEOLOCATION_ERROR:
			print_error(event);
			if (geolocation_event_get_error_code(event) < 0x10000 &&
			    geolocation_event_get_error_code(event) != GEOLOCATION_ERROR_NONE)
				goto done;
			break;
		case GEOLOCATION_STATUS:
			fprintf(stderr, "gps: status active=%s background=%s\n",
				geolocation_event_get_status_active_request(event) ? "yes" : "no",
				geolocation_event_get_status_background(event) ? "yes" : "no");
			break;
		case GEOLOCATION_CANCEL:
			fputs("gps: cancelled\n", stderr);
			goto done;
		default:
			break;
		}
	}

done:
	geolocation_stop_events(0);
	bps_shutdown();
	return got > 0 ? 0 : 1;
}

int main(int argc, char **argv)
{
	int count = 1;
	int timeout_s = 45;
	int last_known = 0;
	int sats = 0;
	int watch = 0;
	geolocation_provider_t provider = GEOLOCATION_PROVIDER_HYBRID;
	int opt;

	while ((opt = getopt(argc, argv, "n:t:p:h")) != -1) {
		switch (opt) {
		case 'n':
			count = atoi(optarg);
			break;
		case 't':
			timeout_s = atoi(optarg);
			if (timeout_s < 3)
				timeout_s = 3;
			break;
		case 'p':
			if (strcmp(optarg, "gnss") == 0)
				provider = GEOLOCATION_PROVIDER_GNSS;
			else if (strcmp(optarg, "network") == 0)
				provider = GEOLOCATION_PROVIDER_NETWORK;
			else
				provider = GEOLOCATION_PROVIDER_HYBRID;
			break;
		case 'h':
		default:
			usage();
			return opt == 'h' ? 0 : 1;
		}
	}

	if (optind < argc) {
		if (strcmp(argv[optind], "help") == 0) {
			usage();
			return 0;
		}
		if (strcmp(argv[optind], "pps") == 0) {
			dump_pps();
			return 0;
		}
		if (strcmp(argv[optind], "last") == 0)
			last_known = 1;
		else if (strcmp(argv[optind], "watch") == 0) {
			watch = 1;
			count = -1;
			timeout_s = 3600;
		} else if (strcmp(argv[optind], "sats") == 0)
			sats = 1;
		else {
			fprintf(stderr, "gps: unknown command %s\n", argv[optind]);
			usage();
			return 1;
		}
	}

	(void)watch;
	return run(count, timeout_s, last_known, sats, provider);
}
