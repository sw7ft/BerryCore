/*
 * mem — Term49 peek of our own process address space
 *
 * Maps + seek-read /proc/<pid>/as. Will not open /dev/mem or other uids.
 */
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#ifndef _SC_PHYS_PAGES
#define _SC_PHYS_PAGES 500
#endif
#ifndef _SC_AVPHYS_PAGES
#define _SC_AVPHYS_PAGES 501
#endif

#define MAX_DUMP 65536

static void usage(void)
{
	fputs(
		"mem — read our own process memory from Term49\n"
		"\n"
		"  mem                 RAM totals (if sysconf allows) + help\n"
		"  mem free            same totals\n"
		"  mem maps [pid]      /proc/pid/mappings (default: parent)\n"
		"  mem pmap [pid]      /proc/pid/pmap (default: parent)\n"
		"  mem vmstat [pid]    /proc/pid/vmstat (default: parent)\n"
		"  mem read ADDR [len]          hex dump parent /proc/pid/as\n"
		"  mem read -p PID ADDR [len]   same for a pid we own\n"
		"                      ADDR is hex (0x1418000 or 1418000)\n"
		"                      default len=64, max 65536\n"
		"\n"
		"Only pids we own. Seek to a mapped vaddr (see maps).\n"
		"Offset 0 faults. /dev/mem is not opened.\n"
		"\n",
		stdout);
}

static pid_t parse_pid(const char *s)
{
	char *end = NULL;
	long v;

	if (!s || !*s)
		return getpid();
	v = strtol(s, &end, 10);
	if (end == s || *end || v <= 0)
		return -1;
	return (pid_t)v;
}

static unsigned long parse_addr(const char *s)
{
	char *end = NULL;
	unsigned long v;

	if (!s || !*s)
		return 0;
	v = strtoul(s, &end, 16);
	if (end == s)
		return 0;
	return v;
}

static int own_as(pid_t pid, char *path, size_t pathcap)
{
	struct stat st;

	snprintf(path, pathcap, "/proc/%d/as", (int)pid);
	if (stat(path, &st) != 0) {
		fprintf(stderr, "mem: %s: %s\n", path, strerror(errno));
		return -1;
	}
	if (st.st_uid != getuid()) {
		fprintf(stderr, "mem: pid %d is not ours (uid %u vs %u)\n",
			(int)pid, (unsigned)st.st_uid, (unsigned)getuid());
		return -1;
	}
	return 0;
}

static int cat_proc(pid_t pid, const char *leaf)
{
	char aspath[64], path[80];
	FILE *fp;
	char buf[512];
	size_t n;

	if (own_as(pid, aspath, sizeof(aspath)) != 0)
		return 1;
	snprintf(path, sizeof(path), "/proc/%d/%s", (int)pid, leaf);
	fp = fopen(path, "r");
	if (!fp) {
		fprintf(stderr, "mem: %s: %s\n", path, strerror(errno));
		return 1;
	}
	while ((n = fread(buf, 1, sizeof(buf), fp)) > 0)
		fwrite(buf, 1, n, stdout);
	if (n == 0 && ferror(fp))
		fprintf(stderr, "mem: read %s: %s\n", path, strerror(errno));
	fclose(fp);
	return 0;
}

static void hexline(unsigned long addr, const unsigned char *p, int n)
{
	int i;

	printf("%08lx:", addr);
	for (i = 0; i < 16; i++) {
		if (i == 8)
			putchar(' ');
		if (i < n)
			printf(" %02x", p[i]);
		else
			fputs("   ", stdout);
	}
	fputs("  ", stdout);
	for (i = 0; i < n; i++) {
		unsigned char c = p[i];
		putchar((c >= 32 && c < 127) ? (char)c : '.');
	}
	putchar('\n');
}

static int cmd_read(pid_t pid, unsigned long addr, size_t len)
{
	char path[64];
	int fd;
	unsigned char buf[256];
	size_t got = 0;

	if (len == 0 || len > MAX_DUMP) {
		fprintf(stderr, "mem: len must be 1..%d\n", MAX_DUMP);
		return 1;
	}
	if (own_as(pid, path, sizeof(path)) != 0)
		return 1;
	fd = open(path, O_RDONLY);
	if (fd < 0) {
		fprintf(stderr, "mem: open %s: %s\n", path, strerror(errno));
		return 1;
	}
	if (lseek(fd, (off_t)addr, SEEK_SET) == (off_t)-1) {
		fprintf(stderr, "mem: lseek 0x%lx: %s\n", addr, strerror(errno));
		close(fd);
		return 1;
	}
	printf("pid=%d as=%s vaddr=0x%lx len=%u\n",
	       (int)pid, path, addr, (unsigned)len);
	while (got < len) {
		size_t chunk = sizeof(buf);
		ssize_t n;
		size_t off;

		if (chunk > len - got)
			chunk = len - got;
		n = read(fd, buf, chunk);
		if (n < 0) {
			fprintf(stderr, "mem: read 0x%lx: %s\n",
				addr + (unsigned long)got, strerror(errno));
			close(fd);
			return 1;
		}
		if (n == 0) {
			fprintf(stderr, "mem: short read at 0x%lx (unmapped?)\n",
				addr + (unsigned long)got);
			close(fd);
			return got ? 0 : 1;
		}
		for (off = 0; off < (size_t)n; off += 16)
			hexline(addr + (unsigned long)got + (unsigned long)off,
				buf + off,
				(int)((size_t)n - off > 16 ? 16 : (size_t)n - off));
		got += (size_t)n;
	}
	close(fd);
	return 0;
}

static int cmd_free(void)
{
	long pagesz = sysconf(_SC_PAGESIZE);
	long phys = sysconf(_SC_PHYS_PAGES);
	long avail = sysconf(_SC_AVPHYS_PAGES);

	printf("pagesize=%ld\n", pagesz);
	if (pagesz > 0 && phys > 0)
		printf("phys=%ld kB (%.1f MiB)\n",
		       (phys * pagesz) / 1024,
		       (phys * pagesz) / (1024.0 * 1024.0));
	else
		puts("phys=n/a (sysconf) — try $BC/bin/free");
	if (pagesz > 0 && avail > 0)
		printf("avail=%ld kB (%.1f MiB)\n",
		       (avail * pagesz) / 1024,
		       (avail * pagesz) / (1024.0 * 1024.0));
	else
		puts("avail=n/a");
	puts("/dev/mem: not opened (root only)");
	return 0;
}

int main(int argc, char **argv)
{
	const char *cmd;
	pid_t pid;
	unsigned long addr;
	size_t len = 64;

	if (argc < 2) {
		cmd_free();
		usage();
		return 0;
	}
	cmd = argv[1];
	if (strcmp(cmd, "-h") == 0 || strcmp(cmd, "--help") == 0 || strcmp(cmd, "help") == 0) {
		usage();
		return 0;
	}
	if (strcmp(cmd, "free") == 0)
		return cmd_free();
	if (strcmp(cmd, "maps") == 0 || strcmp(cmd, "mappings") == 0) {
		pid = (argc >= 3) ? parse_pid(argv[2]) : getppid();
		if (pid < 0) {
			fputs("mem: bad pid\n", stderr);
			return 1;
		}
		return cat_proc(pid, "mappings");
	}
	if (strcmp(cmd, "pmap") == 0) {
		pid = (argc >= 3) ? parse_pid(argv[2]) : getppid();
		if (pid < 0) {
			fputs("mem: bad pid\n", stderr);
			return 1;
		}
		return cat_proc(pid, "pmap");
	}
	if (strcmp(cmd, "vmstat") == 0) {
		pid = (argc >= 3) ? parse_pid(argv[2]) : getppid();
		if (pid < 0) {
			fputs("mem: bad pid\n", stderr);
			return 1;
		}
		return cat_proc(pid, "vmstat");
	}
	if (strcmp(cmd, "read") == 0 || strcmp(cmd, "peek") == 0) {
		int i = 2;

		pid = getppid();
		if (argc >= 4 && strcmp(argv[2], "-p") == 0) {
			pid = parse_pid(argv[3]);
			i = 4;
		}
		if (pid < 0 || i >= argc) {
			fputs("mem: read [-p PID] ADDR [len]\n", stderr);
			return 1;
		}
		addr = parse_addr(argv[i]);
		if (addr == 0 && argv[i][0] != '0') {
			fprintf(stderr, "mem: bad addr %s\n", argv[i]);
			return 1;
		}
		if (argc > i + 1)
			len = (size_t)strtoul(argv[i + 1], NULL, 0);
		return cmd_read(pid, addr, len);
	}

	fprintf(stderr, "mem: unknown command: %s\n", cmd);
	usage();
	return 1;
}
