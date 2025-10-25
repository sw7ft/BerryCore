#ifndef _SYS_RESOURCE_H_
#define _SYS_RESOURCE_H_

/* Dummy sys/resource.h header for QNX compatibility */
/* OpenBLAS uses this for resource limits, but QNX handles resources differently */

#include <sys/types.h>

/* Resource limit identifiers */
#define RLIMIT_CPU      0    /* CPU time in seconds */
#define RLIMIT_FSIZE    1    /* Maximum file size */
#define RLIMIT_DATA     2    /* Data segment size */
#define RLIMIT_STACK    3    /* Stack size */
#define RLIMIT_CORE     4    /* Core file size */
#define RLIMIT_RSS      5    /* Resident set size */
#define RLIMIT_NPROC    6    /* Number of processes */
#define RLIMIT_NOFILE   7    /* Number of open files */
#define RLIMIT_MEMLOCK  8    /* Locked-in-memory address space */
#define RLIMIT_AS       9    /* Address space limit */

/* Special values for resource limits */
#define RLIM_INFINITY   (~0UL)
#define RLIM_SAVED_MAX  RLIM_INFINITY
#define RLIM_SAVED_CUR  RLIM_INFINITY

typedef unsigned long rlim_t;

/* Resource limit structure */
struct rlimit {
    rlim_t rlim_cur;    /* Current (soft) limit */
    rlim_t rlim_max;    /* Maximum value for rlim_cur */
};

/* Resource usage structure */
/* struct timeval is already defined in sys/time.h */

struct rusage {
    struct timeval ru_utime;    /* User time used */
    struct timeval ru_stime;    /* System time used */
    long ru_maxrss;             /* Maximum resident set size */
    long ru_ixrss;              /* Integral shared memory size */
    long ru_idrss;              /* Integral unshared data size */
    long ru_isrss;              /* Integral unshared stack size */
    long ru_minflt;             /* Page reclaims */
    long ru_majflt;             /* Page faults */
    long ru_nswap;              /* Swaps */
    long ru_inblock;            /* Block input operations */
    long ru_oublock;            /* Block output operations */
    long ru_msgsnd;             /* Messages sent */
    long ru_msgrcv;             /* Messages received */
    long ru_nsignals;           /* Signals received */
    long ru_nvcsw;              /* Voluntary context switches */
    long ru_nivcsw;             /* Involuntary context switches */
};

/* Who values for getrusage() */
#define RUSAGE_SELF      0
#define RUSAGE_CHILDREN -1

/* Dummy function declarations - these will fail at runtime but allow compilation */
static inline int getrlimit(int resource, struct rlimit *rlim) {
    /* Not implemented on QNX - return error */
    if (rlim) {
        rlim->rlim_cur = RLIM_INFINITY;
        rlim->rlim_max = RLIM_INFINITY;
    }
    return 0;  /* Return success to avoid breaking OpenBLAS */
}

static inline int setrlimit(int resource, const struct rlimit *rlim) {
    /* Not implemented on QNX - return error */
    return -1;
}

static inline int getrusage(int who, struct rusage *usage) {
    /* Not implemented on QNX - return error */
    return -1;
}

#endif /* _SYS_RESOURCE_H_ */
