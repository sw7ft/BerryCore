#ifndef _SYS_SHM_H_
#define _SYS_SHM_H_

/* Dummy sys/shm.h header for QNX compatibility */
/* OpenBLAS uses this for shared memory, but QNX handles memory differently */

#include <sys/types.h>
#include <sys/ipc.h>

/* Shared memory operation flags */
#define SHM_R       0400    /* Read permission */
#define SHM_W       0200    /* Write permission */
#define SHM_RDONLY  010000  /* Read-only access */
#define SHM_RND     020000  /* Round address to SHMLBA */
#define SHM_REMAP   040000  /* Take-over region on attach */

/* Shared memory control commands */
#define SHM_LOCK    11      /* Lock segment (root only) */
#define SHM_UNLOCK  12      /* Unlock segment (root only) */
#define SHM_STAT    13      /* Get shmid_ds from shmid */
#define SHM_INFO    14      /* Get info on limits */

/* Shared memory segment low boundary address multiple */
#define SHMLBA      4096

/* Data structure for shared memory segment */
struct shmid_ds {
    struct ipc_perm shm_perm;   /* Operation permission structure */
    size_t shm_segsz;           /* Size of segment in bytes */
    time_t shm_atime;           /* Time of last shmat() */
    time_t shm_dtime;           /* Time of last shmdt() */
    time_t shm_ctime;           /* Time of last change by shmctl() */
    pid_t shm_cpid;             /* Process ID of creator */
    pid_t shm_lpid;             /* Process ID of last shmat/shmdt */
    unsigned short shm_nattch;  /* Current number of attached processes */
};

/* Dummy function declarations - these will fail at runtime but allow compilation */
static inline int shmget(key_t key, size_t size, int shmflg) {
    /* Not implemented on QNX - return error */
    return -1;
}

static inline void *shmat(int shmid, const void *shmaddr, int shmflg) {
    /* Not implemented on QNX - return error */
    return (void *)-1;
}

static inline int shmdt(const void *shmaddr) {
    /* Not implemented on QNX - return error */
    return -1;
}

static inline int shmctl(int shmid, int cmd, struct shmid_ds *buf) {
    /* Not implemented on QNX - return error */
    return -1;
}

#endif /* _SYS_SHM_H_ */ 