/*
 * notify — Term49 CLI for BB10 Hub notifications (BPS + PPS compare)
 *
 * Built for Passport / armle-v7. Links -lbps.
 */
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include <bps/bps.h>
#include <bps/notification.h>

#define PPS_CTRL "/pps/services/notify/control"

static void usage(void)
{
	fputs(
		"notify — BB10 Hub notifications from Term49\n"
		"\n"
		"  notify                 BPS post: title BerryCore, subtitle test\n"
		"  notify TITLE [SUB]     BPS notification_notify\n"
		"  notify post TITLE SUB  same\n"
		"  notify rocket TITLE SUB\n"
		"                         BPS using the RocketChat2 recipe\n"
		"                         (🚀 title, itemid RocketChat-<ms>)\n"
		"  notify pps TITLE SUB   existing PPS /pps/services/notify/control\n"
		"  notify alert TITLE SUB BPS dialog (prompt: Ok)\n"
		"  notify cancel [ID]     stop LED / lingering effects\n"
		"  notify delete [ID]     remove from Hub\n"
		"  notify ppsdump         dump notify PPS objects\n"
		"  notify -i ID ...       item id (default BerryCore-<ms>)\n"
		"  notify -u URL ...      tap payload URI\n"
		"\n",
		stdout);
}

static void dump_pps(void)
{
	static const char *paths[] = {
		"/pps/services/notify/control",
		"/pps/services/notify/status",
		"/pps/services/notify",
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

static void json_escape(const char *in, char *out, size_t cap)
{
	size_t o = 0;
	while (*in && o + 2 < cap) {
		if (*in == '"' || *in == '\\') {
			out[o++] = '\\';
			out[o++] = *in;
		} else if ((unsigned char)*in < 32) {
			out[o++] = ' ';
		} else {
			out[o++] = *in;
		}
		in++;
	}
	out[o] = '\0';
}

static int pps_post(const char *itemid, const char *title, const char *sub,
		    const char *url)
{
	char et[256], es[256], eu[256], ei[128];
	char json[900];
	char msg[1024];
	int fd;
	ssize_t n;

	json_escape(itemid, ei, sizeof(ei));
	json_escape(title, et, sizeof(et));
	json_escape(sub, es, sizeof(es));
	json_escape(url, eu, sizeof(eu));
	snprintf(json, sizeof(json),
		 "{\"itemid\":\"%s\",\"title\":\"%s\",\"subtitle\":\"%s\","
		 "\"target\":\"\",\"targetAction\":\"\","
		 "\"payload\":\"%s\",\"payloadType\":\"url\",\"payloadURI\":\"%s\"}",
		 ei, et, es, eu, eu);
	snprintf(msg, sizeof(msg), "msg::notify\ndat:json:%s\n", json);

	fd = open(PPS_CTRL, O_WRONLY | O_APPEND);
	if (fd < 0) {
		fprintf(stderr, "notify: pps open: %s\n", strerror(errno));
		return 1;
	}
	n = write(fd, msg, strlen(msg));
	close(fd);
	if (n < 0) {
		fprintf(stderr, "notify: pps write: %s\n", strerror(errno));
		return 1;
	}
	printf("pps wrote %ld bytes itemid=%s\n", (long)n, itemid);
	return 0;
}

static int wait_response(int timeout_ms)
{
	int domain = notification_get_domain();
	bps_event_t *ev = NULL;
	int rc;

	rc = bps_get_event(&ev, timeout_ms);
	if (rc != BPS_SUCCESS || !ev) {
		printf("bps: no response event (%s)\n",
		       rc != BPS_SUCCESS ? strerror(errno) : "timeout");
		return 1;
	}
	if (bps_event_get_domain(ev) != domain) {
		printf("bps: other domain event code=%d\n", bps_event_get_code(ev));
		return 1;
	}
	rc = notification_event_get_response(ev);
	printf("bps response=%s request=%s item=%s\n",
	       rc == NOTIFICATION_OK ? "OK" :
	       rc == NOTIFICATION_ERROR ? "ERROR" :
	       rc == NOTIFICATION_CHOICE ? "CHOICE" : "?",
	       notification_event_get_request_id(ev) ? notification_event_get_request_id(ev) : "-",
	       notification_event_get_item_id(ev) ? notification_event_get_item_id(ev) : "-");
	return rc == NOTIFICATION_ERROR ? 1 : 0;
}

static int bps_send(int kind, const char *itemid, const char *title,
		    const char *sub, const char *url)
{
	notification_message_t *msg = NULL;
	char req[64];
	int rc;

	if (bps_initialize() != BPS_SUCCESS) {
		fprintf(stderr, "notify: bps_initialize: %s\n", strerror(errno));
		return 1;
	}
	if (notification_request_events(0) != BPS_SUCCESS)
		printf("notify: request_events: %s (continuing)\n", strerror(errno));

	if (notification_message_create(&msg) != BPS_SUCCESS) {
		fprintf(stderr, "notify: message_create: %s\n", strerror(errno));
		bps_shutdown();
		return 1;
	}
	snprintf(req, sizeof(req), "req-%ld", (long)time(NULL));
	notification_message_set_request_id(msg, req);
	notification_message_set_item_id(msg, itemid);
	if (title && title[0])
		notification_message_set_title(msg, title);
	if (sub && sub[0])
		notification_message_set_subtitle(msg, sub);
	if (url && url[0]) {
		notification_message_set_invocation_type(msg, "url");
		notification_message_set_invocation_payload(msg, url, (int)strlen(url));
		notification_message_set_invocation_payload_uri(msg, url);
	}

	if (kind == 2)
		notification_message_add_prompt_choice(msg, "Ok", "ok");

	if (kind == 0)
		rc = notification_notify(msg);
	else if (kind == 1)
		rc = notification_cancel(msg);
	else if (kind == 3)
		rc = notification_delete(msg);
	else
		rc = notification_alert(msg);

	printf("bps %s itemid=%s rc=%s errno=%s\n",
	       kind == 0 ? "notify" : kind == 1 ? "cancel" : kind == 3 ? "delete" : "alert",
	       itemid,
	       rc == BPS_SUCCESS ? "ok" : "fail",
	       rc == BPS_SUCCESS ? "-" : strerror(errno));

	if (rc == BPS_SUCCESS && (kind == 0 || kind == 2))
		wait_response(kind == 2 ? 8000 : 1500);

	notification_message_destroy(&msg);
	bps_shutdown();
	return rc == BPS_SUCCESS ? 0 : 1;
}

int main(int argc, char **argv)
{
	const char *cmd = "post";
	const char *title = "BerryCore";
	const char *sub = "BPS notify test";
	const char *itemid = NULL;
	const char *url = "http://127.0.0.1:8098/";
	char auto_id[80];
	char rocket_title[280];
	int i, rocket = 0, kind = 0;
	int pos = 0;
	const char *words[8];

	for (i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "help") == 0) {
			usage();
			return 0;
		}
		if (strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
			itemid = argv[++i];
			continue;
		}
		if (strcmp(argv[i], "-u") == 0 && i + 1 < argc) {
			url = argv[++i];
			continue;
		}
		if (pos < 8)
			words[pos++] = argv[i];
	}

	if (pos >= 1)
		cmd = words[0];

	if (strcmp(cmd, "ppsdump") == 0) {
		dump_pps();
		return 0;
	}

	if (strcmp(cmd, "post") == 0 || strcmp(cmd, "rocket") == 0 ||
	    strcmp(cmd, "pps") == 0 || strcmp(cmd, "alert") == 0 ||
	    strcmp(cmd, "cancel") == 0 || strcmp(cmd, "delete") == 0) {
		if (pos >= 2)
			title = words[1];
		if (pos >= 3)
			sub = words[2];
		rocket = (strcmp(cmd, "rocket") == 0);
	} else {
		/* notify TITLE [SUB] */
		title = words[0];
		if (pos >= 2)
			sub = words[1];
		cmd = "post";
	}

	if (!itemid) {
		snprintf(auto_id, sizeof(auto_id),
			 rocket ? "RocketChat-%ld" : "BerryCore-%ld",
			 (long)time(NULL));
		itemid = auto_id;
	}

	if (rocket) {
		snprintf(rocket_title, sizeof(rocket_title), "🚀 %s", title);
		title = rocket_title;
		url = "http://127.0.0.1:8027/";
	}

	if (strcmp(cmd, "pps") == 0)
		return pps_post(itemid, title, sub, url);
	if (strcmp(cmd, "cancel") == 0)
		kind = 1;
	else if (strcmp(cmd, "alert") == 0)
		kind = 2;
	else if (strcmp(cmd, "delete") == 0)
		kind = 3;
	else
		kind = 0;

	return bps_send(kind, itemid, title, sub, url);
}
