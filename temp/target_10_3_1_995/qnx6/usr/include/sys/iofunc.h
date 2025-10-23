/*
 * $QNXLicenseC:
 * Copyright 2007, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable license fees to QNX
 * Software Systems before you may reproduce, modify or distribute this software,
 * or any work that includes all or part of this software.   Free development
 * licenses are available for evaluation and non-commercial purposes.  For more
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *
 * This file may contain contributions from others.  Please review this entire
 * file for other proprietary rights or license notices, as well as the QNX
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 * $
 */



/*
 *  iofunc.h    Non-portable low-level IO definitions
 *

 */

#ifndef __IOFUNC_H_INCLUDED
#define __IOFUNC_H_INCLUDED

#ifndef _INTTYPES_H_INCLUDED
 #include <inttypes.h>
#endif

#ifndef __TYPES_H_INCLUDED
 #include <sys/types.h>
#endif

__BEGIN_DECLS

#include <_pack64.h>

struct _iofunc_attr;
struct _iofunc_ocb;

#ifndef RESMGR_HANDLE_T
 #ifndef IOFUNC_ATTR_T
  #define RESMGR_HANDLE_T		struct _iofunc_attr
 #else
  #define RESMGR_HANDLE_T		IOFUNC_ATTR_T
 #endif
#endif

#ifndef RESMGR_OCB_T
 #ifndef IOFUNC_OCB_T
  #define RESMGR_OCB_T			struct _iofunc_ocb
 #else
  #define RESMGR_OCB_T			IOFUNC_OCB_T
 #endif
#endif

#ifndef __RESMGR_H_INCLUDED
 #include <sys/resmgr.h>
#endif

#if __OFF_BITS__ != 64
#if defined(__OFF64_T)
typedef __OFF64_T	off64_t;
# undef __OFF64_T
#endif

#if defined(_IOFUNC_OFFSET_BITS) && _IOFUNC_OFFSET_BITS < __LONG_BITS__
#error _IOFUNC_OFFSET_BITS set too small
#endif

#if defined(__INO64_T)
typedef __INO64_T	ino64_t;
# undef __INO64_T
#endif
#endif

/***********************************************************************
 * Mount point definition                                              *
 ***********************************************************************/

typedef struct _iofunc_funcs		iofunc_funcs_t;

typedef struct _iofunc_mount {
    uint32_t                        flags;
    uint32_t                        conf;
    dev_t                           dev;
    int32_t                         blocksize;
    iofunc_funcs_t                  *funcs;
    void                            *power;     /* Reserved for future use */
} iofunc_mount_t;

#ifndef IOFUNC_MOUNT_T
#define IOFUNC_MOUNT_T               iofunc_mount_t
#endif

#define IOFUNC_MOUNT_FLAGS          0x000000FF  /* Bits from io_mount_t */
#define IOFUNC_MOUNT_32BIT          0x00000100  /* offset, nbytes, inode and size are always 32-bit */
#define IOFUNC_MOUNT_FLAGS_PRIVATE  0xFFFFF000  /* Bits available for */
                                                /* private implementations */

#define IOFUNC_PC_CHOWN_RESTRICTED  0x00000001  /* Filesystem is chown restricted */
#define IOFUNC_PC_NO_TRUNC          0x00000002  /* Filesystem doesn't trunc name */
#define IOFUNC_PC_SYNC_IO           0x00000004  /* Filesystem sync io supported */
#define IOFUNC_PC_LINK_DIR          0x00000008  /* Link (and unlink) on dir allowed */
#define IOFUNC_PC_ACL               0x00000010  /* Filesystem supports ACL's */


/***********************************************************************
 * File or device attributes (usually embeded within an inode)         *
 ***********************************************************************/

typedef struct _iofunc_attr {
    IOFUNC_MOUNT_T                  *mount;     /* Used to find iofunc_mount_t */
    uint32_t                        flags;      /* Dirty and invalid flags */
    int32_t                         lock_tid;   /* Thread that has attr locked */
    uint16_t                        lock_count; /* Lock count (0 == unlocked) */
    uint16_t                        count;      /* File use count */
    uint16_t                        rcount;     /* File reader count */
    uint16_t                        wcount;     /* File writer count */
    uint16_t                        rlocks;     /* Number of read locks */
    uint16_t                        wlocks;     /* Number of write locks */
    struct _iofunc_mmap_list        *mmap_list; /* List of mmap ids */
    struct _iofunc_lock_list        *lock_list; /* Lock lists */
    void                            *lockobj;   /* Attribute Locking Object */
    void                            *acl;       /* Access Control Lists */
#if !defined(_IOFUNC_OFFSET_BITS) || _IOFUNC_OFFSET_BITS == 64
 #if __OFF_BITS__ == 64
    off_t                           nbytes;     /* Always Number of bytes */
    ino_t                           inode;      /* mount point specific inode */
 #else
    off64_t                         nbytes;     /* Always Number of bytes */
    ino64_t                         inode;      /* mount point specific inode */
 #endif
#elif _IOFUNC_OFFSET_BITS - 0 == 32
 #if __OFF_BITS__ == 32
  #if defined(__LITTLEENDIAN__)
    off_t                           nbytes;     /* Always Number of bytes */
    off_t                           nbytes_hi;
    ino_t                           inode;      /* mount point specific inode */
    ino_t                           inode_hi;
  #elif defined(__BIGENDIAN__)
    off_t                           nbytes_hi;
    off_t                           nbytes;     /* Always Number of bytes */
    ino_t                           inode_hi;
    ino_t                           inode;      /* mount point specific inode */
  #else
   #error endian not configured for system
  #endif
 #else
  #if defined(__LITTLEENDIAN__)
    int32_t                         nbytes;     /* Always Number of bytes */
    int32_t                         nbytes_hi;
    int32_t                         inode;      /* mount point specific inode */
    int32_t                         inode_hi;
  #elif defined(__BIGENDIAN__)
    int32_t                         nbytes_hi;
    int32_t                         nbytes;     /* Always Number of bytes */
    int32_t                         inode_hi;
    int32_t                         inode;      /* mount point specific inode */
  #else
   #error endian not configured for system
  #endif
 #endif
#else
 #error _IOFUNC_OFFSET_BITS value is unsupported
#endif
    uid_t                           uid;        /* User id */
    gid_t                           gid;        /* Group id */
    time_t                          mtime;      /* Modification time (write updates) */
    time_t                          atime;      /* Access time (read updates */
    time_t                          ctime;      /* Change time (write/ch* updates) */
    mode_t                          mode;       /* File mode (S_* from stat.h) */
    nlink_t                         nlink;      /* Number of links to the file */
    dev_t                           rdev;       /* dev num for CHR special, rdev num for NAME special */
} iofunc_attr_t;

#ifndef IOFUNC_ATTR_T
#define IOFUNC_ATTR_T               iofunc_attr_t
#endif

#define IOFUNC_ATTR_RSVD        0x0000FFFF  /* Bits reserved for iofunc */
#define IOFUNC_ATTR_PRIVATE     0xFFFF0000  /* Bits for private implementation */
#define IOFUNC_ATTR_GROUP_OWNER	0x00004000  /* attr refers to a group owned file */
#define IOFUNC_ATTR_SYNTHETIC	0x00008000  /* attr may be modified regardless of ST_RDONLY/EROFS */

#define IOFUNC_ATTR_MTIME       0x00000001  /* File written -- mtime invalid */
#define IOFUNC_ATTR_ATIME       0x00000002  /* File read -- atime invalid */
#define IOFUNC_ATTR_CTIME       0x00000004  /* File info changed -- ctime invalid */
#define IOFUNC_ATTR_DIRTY_MASK  0x00000FF0  /* Some attributes are dirty */
#define IOFUNC_ATTR_DIRTY_SIZE  0x00000010  /* size changed */
#define IOFUNC_ATTR_DIRTY_OWNER 0x00000020  /* uid or gid changed */
#define IOFUNC_ATTR_DIRTY_TIME  0x00000040  /* mtime, atime or ctime changed */
#define IOFUNC_ATTR_DIRTY_MODE  0x00000080  /* mode changed */
#define IOFUNC_ATTR_DIRTY_NLINK 0x00000100  /* # links changed */
#define IOFUNC_ATTR_DIRTY_RDEV	0x00000200  /* dev/rdev num changed */
#define IOFUNC_ATTR_DIRTY_ACL   0x00000400  /* ACL has been changed */


/***********************************************************************
 * Open control block (usually embeded within file system ocb)         *
 ***********************************************************************/


typedef struct _iofunc_ocb {
    IOFUNC_ATTR_T                   *attr;      /* Used to find iofunc_attr_t */
    int32_t                         ioflag;     /* open's oflag + 1 */
#if !defined(_IOFUNC_OFFSET_BITS) || _IOFUNC_OFFSET_BITS == 64
 #if __OFF_BITS__ == 64
    off_t                           offset;
 #else
    off64_t                         offset;
 #endif
#elif _IOFUNC_OFFSET_BITS - 0 == 32
 #if __OFF_BITS__ == 32
  #if defined(__LITTLEENDIAN__)
    off_t                           offset;
    off_t                           offset_hi;
  #elif defined(__BIGENDIAN__)
    off_t                           offset_hi;
    off_t                           offset;
  #else
   #error endian not configured for system
  #endif
 #else
  #if defined(__LITTLEENDIAN__)
    int32_t                         offset;
    int32_t                         offset_hi;
  #elif defined(__BIGENDIAN__)
    int32_t                         offset_hi;
    int32_t                         offset;
  #else
   #error endian not configured for system
  #endif
 #endif
#else
 #error _IOFUNC_OFFSET_BITS value is unsupported
#endif
    uint16_t                        sflag; 		/* share mode flags defined as SH_DENYxx */
    uint16_t                        flags;		/* flags defined as IOFUNC_OCB_xxx */
    void                            *reserved;
} iofunc_ocb_t;

#ifndef IOFUNC_OCB_T
#define IOFUNC_OCB_T                iofunc_ocb_t
#endif

#define IOFUNC_OCB_PRIVILEGED       0x0001      /* set if ocb opened by privileged process */
#define IOFUNC_OCB_MMAP             0x0002      /* set if ocb used by mmap */
#define IOFUNC_OCB_FLAGS_PRIVATE    0xF000      /* Bits for private implementation */


/***********************************************************************
 * Other definitions used by iofunc functions                          *
 ***********************************************************************/

struct _iofunc_funcs {
	unsigned				nfuncs;
	IOFUNC_OCB_T			*(*ocb_calloc)(resmgr_context_t *ctp, IOFUNC_ATTR_T *attr);
	void					(*ocb_free)(IOFUNC_OCB_T *ocb);
	int						(*attr_lock)(IOFUNC_ATTR_T *attr);
	int						(*attr_unlock)(IOFUNC_ATTR_T *attr);
	int						(*attr_trylock)(IOFUNC_ATTR_T *attr);
};
#define _IOFUNC_NFUNCS		((sizeof(iofunc_funcs_t)-sizeof(unsigned))/sizeof(void *))

typedef struct _iofunc_mmap_list    iofunc_mmap_list_t;
typedef struct _iofunc_lock_list    iofunc_lock_list_t;


/***********************************************************************
 * Flags used by function                                              *
 ***********************************************************************/

/* returned flags from iofunc_ocb_detach */
#define IOFUNC_OCB_LAST_INUSE       0x0001
#define IOFUNC_OCB_LAST_READER      0x0002
#define IOFUNC_OCB_LAST_WRITER      0x0004
#define IOFUNC_OCB_LAST_RDLOCK      0x0008
#define IOFUNC_OCB_LAST_WRLOCK      0x0010


/***********************************************************************
 * Notify structures                                                   *
 ***********************************************************************/

typedef struct _iofunc_notify_event {
	struct _iofunc_notify_event	*next;
	int							rcvid;
	int							scoid;
	int							cnt;
	struct sigevent				event;
	unsigned					flags;
	int							coid;
} iofunc_notify_event_t;

typedef struct _iofunc_notify {
	int							cnt;
	struct _iofunc_notify_event	*list;
} iofunc_notify_t;

/* Indexes to the array of struct _iofunc_notify */
#define IOFUNC_NOTIFY_INPUT		0
#define IOFUNC_NOTIFY_OUTPUT	1
#define IOFUNC_NOTIFY_OBAND		2

#define IOFUNC_NOTIFY_RDNORM	IOFUNC_NOTIFY_INPUT
#define IOFUNC_NOTIFY_WRNORM	IOFUNC_NOTIFY_OUTPUT
#define IOFUNC_NOTIFY_RDBAND	IOFUNC_NOTIFY_OBAND
#define IOFUNC_NOTIFY_PRI		3
#define IOFUNC_NOTIFY_WRBAND	4
#define IOFUNC_NOTIFY_ERR		5
#define IOFUNC_NOTIFY_HUP		6
#define IOFUNC_NOTIFY_NVAL		12

/* POLLERR | POLLHUP | POLLNVAL */
#define IOFUNC_NOTIFY_UNMASKABLE	((1<<IOFUNC_NOTIFY_ERR) | (1<<IOFUNC_NOTIFY_HUP) | (1<<IOFUNC_NOTIFY_NVAL))


/*
 * iofunc_client_info_ext flags
 */
#define IOFUNC_CLIENTINFO_GETGROUPS _NTO_CLIENTINFO_GETGROUPS


/* Macros to be used to see if iofunc_notify_trigger should be called. */
#define IOFUNC_NOTIFY_INPUT_CHECK(__nop, __cnt, __tran)	\
	((__nop)[IOFUNC_NOTIFY_INPUT].cnt <= (__cnt) && ((__nop)[IOFUNC_NOTIFY_INPUT].cnt || (__tran)))

#define IOFUNC_NOTIFY_OUTPUT_CHECK(__nop, __cnt)	\
	((__nop)[IOFUNC_NOTIFY_OUTPUT].cnt <= (__cnt))

#define IOFUNC_NOTIFY_OBAND_CHECK(__nop, __cnt, __tran)	\
	((__nop)[IOFUNC_NOTIFY_OBAND].cnt <= (__cnt) && ((__nop)[IOFUNC_NOTIFY_OBAND].cnt || (__tran)))

#define IOFUNC_NOTIFY_DISARM(__nop, __index) \
	((__nop)[__index].cnt = (~0u) >> 1))

#define IOFUNC_NOTIFY_INIT(__nop) \
	((__nop)[0].cnt = (__nop)[1].cnt = (__nop)[2].cnt = (~0u) >> 1, \
	 (__nop)[0].list = (__nop)[1].list = (__nop)[2].list = NULL)

/***********************************************************************
 * ACL declarations                                                    *
 ***********************************************************************/

struct _iofunc_acl_funcs;
struct _iofunc_acl_ctrl {
	struct _iofunc_acl_funcs	*funcs;
	int							max_ents;
	int							max_buffsize;
	int							reserved[5];
};

struct _iofunc_acl {
	struct _iofunc_acl_funcs	*funcs;
	struct _iofunc_acl_ctrl		*ctrl;
	void						*handle;	/* for tracking acl data with attribute */
	unsigned					flags;
#define _IOFUNC_ACL_BUFF_ALLOCED		0x00000001
	int							buffsize;
	void						*buff;
};
typedef struct _iofunc_acl		iofunc_acl_t;

#ifndef IOFUNC_ACL_T
# define IOFUNC_ACL_T			iofunc_acl_t
#endif

struct _iofunc_acl_funcs {
	unsigned					nfuncs;
	int							(*init)(IOFUNC_ATTR_T *attr, struct _iofunc_acl_ctrl *ctrl);
	void						(*fini)(IOFUNC_ATTR_T *attr);
	int							(*acl)(resmgr_context_t *ctp, io_acl_t *msg, IOFUNC_OCB_T *ocb, IOFUNC_ATTR_T *attr);
	int							(*access)(resmgr_context_t *ctp, const IOFUNC_ATTR_T *attr, IOFUNC_ACL_T *acl, mode_t check, const struct _client_info *info);
	int							(*stat)(resmgr_context_t *ctp, IOFUNC_ATTR_T *attr, struct stat *pstat);
};
#define _IOFUNC_ACL_NFUNCS	((sizeof(struct _iofunc_acl_funcs)-sizeof(unsigned))/sizeof(void *))

extern struct _iofunc_acl_ctrl	*iofunc_acl_posix_ctrl;

struct _iofunc_acl_hooks {
	unsigned					nfuncs;
	int (*stat)(resmgr_context_t *ctp, iofunc_attr_t *attr, struct stat *pstat);
	int (*check_access)(resmgr_context_t *ctp, const iofunc_attr_t *attr, mode_t check, const struct _client_info * const info_p);
	int (*unlink)(iofunc_attr_t *attr);
	int (*ocb_detach)(iofunc_attr_t *attr);
};
#define _IOFUNC_ACL_HOOKS_NFUNCS	((sizeof(struct _iofunc_acl_hooks)-sizeof(unsigned))/sizeof(void *))

extern struct _iofunc_acl_hooks acl_hooks;

extern iofunc_acl_t *iofunc_acl_get(const iofunc_attr_t *attr);
extern int iofunc_acl_init(iofunc_attr_t *attr, struct _iofunc_acl_ctrl *ctrl, void *buff);
extern void iofunc_acl_fini(iofunc_attr_t *attr);


/***********************************************************************
 * Tracking declarations                                               *
 ***********************************************************************/

struct _iofunc_track_funcs {
	int							(*handle)(const IOFUNC_ATTR_T *attr, void **handle);
	void						(*cleanup)(IOFUNC_ATTR_T *attr, void *data);
};

typedef struct _iofunc_track	iofunc_track_t;

extern iofunc_track_t *iofunc_track_init(struct _iofunc_track_funcs *funcs);
extern void iofunc_track_close(iofunc_track_t *trk, iofunc_attr_t *attr, int destroy);
extern void *iofunc_track_data(iofunc_track_t *trk, const iofunc_attr_t *attr, void ***pdata);
extern void *iofunc_track_get(iofunc_track_t *trk, const iofunc_attr_t *attr);


extern int iofunc_acl_track(iofunc_attr_t *attr, struct _iofunc_acl_ctrl *ctrl);
extern iofunc_acl_t *iofunc_acl_track_get(const iofunc_attr_t *attr);
extern void iofunc_acl_track_destroy(iofunc_attr_t *attr);

/***********************************************************************
 * Functions declarations                                              *
 ***********************************************************************/

/* Default function initialization */
extern void iofunc_func_init(unsigned __nconnect, resmgr_connect_funcs_t *__connect, unsigned __nio, resmgr_io_funcs_t *__io);

/* Default resmgr functions */
extern int iofunc_chmod_default(resmgr_context_t *__ctp, io_chmod_t *__msg, iofunc_ocb_t *__ocb);
extern int iofunc_chown_default(resmgr_context_t *__ctp, io_chown_t *__msg, iofunc_ocb_t *__ocb);
extern int iofunc_close_dup_default(resmgr_context_t *__ctp, io_close_t *__msg, iofunc_ocb_t *__ocb);
extern int iofunc_close_ocb_default(resmgr_context_t *__ctp, void *__reserved, iofunc_ocb_t *__ocb);
extern int iofunc_devctl_default(resmgr_context_t *__ctp, io_devctl_t *__msg, iofunc_ocb_t *__ocb);
extern int iofunc_lock_default(resmgr_context_t *__ctp, io_lock_t *__msg, iofunc_ocb_t *__ocb);
extern int iofunc_lock_ocb_default(resmgr_context_t *__ctp, void *__reserved, iofunc_ocb_t *__ocb);
extern int iofunc_lseek_default(resmgr_context_t *__ctp, io_lseek_t *__msg, iofunc_ocb_t *__ocb);
extern int iofunc_mmap_default(resmgr_context_t *__ctp, io_mmap_t *__msg, iofunc_ocb_t *__ocb);
extern int iofunc_open_default(resmgr_context_t *__ctp, io_open_t *__msg, iofunc_attr_t *__attr, void *__extra);
extern int iofunc_openfd_default(resmgr_context_t *__ctp, io_openfd_t *__msg, iofunc_ocb_t *__ocb);
extern int iofunc_fdinfo_default(resmgr_context_t *__ctp, io_fdinfo_t *__msg, iofunc_ocb_t *__ocb);
extern int iofunc_pathconf_default(resmgr_context_t *__ctp, io_pathconf_t *__msg, iofunc_ocb_t *__ocb);
extern int iofunc_read_default(resmgr_context_t *__ctp, io_read_t *__msg, iofunc_ocb_t *__ocb);
extern int iofunc_stat_default(resmgr_context_t *__ctp, io_stat_t *__msg, iofunc_ocb_t *__ocb);
extern int iofunc_unblock_default(resmgr_context_t *__ctp, io_pulse_t *__msg, iofunc_ocb_t *__ocb);
extern int iofunc_unlock_ocb_default(resmgr_context_t *__ctp, void *__reserved, iofunc_ocb_t *__ocb);
extern int iofunc_utime_default(resmgr_context_t *__ctp, io_utime_t *__msg, iofunc_ocb_t *__ocb);
extern int iofunc_write_default(resmgr_context_t *__ctp, io_write_t *__msg, iofunc_ocb_t *__ocb);
extern int iofunc_sync_default(resmgr_context_t *__ctp, io_sync_t *__msg, iofunc_ocb_t *__ocb);
extern int iofunc_power_default(resmgr_context_t *__ctp, io_power_t *__msg, iofunc_ocb_t *__ocb);
extern int iofunc_acl_default(resmgr_context_t *__ctp, io_acl_t *__msg, iofunc_ocb_t *__ocb);
/* If iofunc_lock_default is used, iofunc_close_dup_default and iofunc_unblock_default must be used */

/* Used by iofunc's for multithread protection */
extern int iofunc_attr_lock(iofunc_attr_t *__attr);
extern int iofunc_attr_trylock(iofunc_attr_t *__attr);
extern int iofunc_attr_unlock(iofunc_attr_t *__attr);

/* used by iofuncs to allocate/deallocate an ocb */
extern IOFUNC_OCB_T *iofunc_ocb_calloc(resmgr_context_t *__ctp, IOFUNC_ATTR_T *__attr);
extern void iofunc_ocb_free(IOFUNC_OCB_T *__ocb);

/* used by iofuncs to allocate/deallocate a lock */
extern iofunc_lock_list_t *iofunc_lock_calloc(resmgr_context_t *__ctp, IOFUNC_OCB_T *__ocb, size_t __size);
extern void iofunc_lock_free(iofunc_lock_list_t *__lock, size_t __size);

/* Used by iofunc_open_default */
extern void iofunc_attr_init(iofunc_attr_t *__attr, mode_t __mode, iofunc_attr_t *__dattr, struct _client_info *__info);
extern int iofunc_check_access(resmgr_context_t *__ctp, const iofunc_attr_t *__attr, mode_t __checkmode, const struct _client_info *__info);
extern int iofunc_client_info(const resmgr_context_t * const __ctp, const int __ioflag, struct _client_info *__info);
extern int iofunc_client_info_ext(resmgr_context_t *__ctp, int __ioflag, struct _client_info **__info_pp, int __flags);
extern int iofunc_client_info_ext_free(struct _client_info **info_pp);
extern int iofunc_client_info_able(resmgr_context_t const * const __ctp, const int __ioflag, struct _client_info **__info_pp, int __flags, struct _client_able * const __abilities, const int __nable);
extern int iofunc_link(resmgr_context_t *__ctp, io_link_t *__msg, iofunc_attr_t *__attr, iofunc_attr_t *__dattr, struct _client_info *__info);
extern int iofunc_mknod(resmgr_context_t *__ctp, io_mknod_t *__msg, iofunc_attr_t *__attr, iofunc_attr_t *__dattr, struct _client_info *__info);
extern int iofunc_ocb_attach(resmgr_context_t *__ctp, io_open_t *__msg, iofunc_ocb_t *__ocb, iofunc_attr_t *__attr, const resmgr_io_funcs_t *__io_funcs);
extern int iofunc_open(resmgr_context_t *__ctp, io_open_t *__msg, iofunc_attr_t *__attr, iofunc_attr_t *__dattr, struct _client_info *__info);
extern int iofunc_readlink(resmgr_context_t *__ctp, io_readlink_t *__msg, iofunc_attr_t *__attr, struct _client_info *__info);
extern int iofunc_rename(resmgr_context_t *__ctp, io_rename_t *__msg, iofunc_attr_t *__oldattr, iofunc_attr_t *__olddattr, iofunc_attr_t *__newattr, iofunc_attr_t *__newdattr, struct _client_info *__info);
extern int iofunc_unlink(resmgr_context_t *__ctp, io_unlink_t *__msg, iofunc_attr_t *__attr, iofunc_attr_t *__dattr, struct _client_info *__info);

/* Should be at start of devctrl handler function */
extern int iofunc_devctl_verify(const resmgr_context_t * const ctp, const io_devctl_t * const msg, const iofunc_ocb_t * const ocb, const unsigned requested_checks );

/* Should be at start of read handler function */
extern int iofunc_read_verify(resmgr_context_t *__ctp, io_read_t *__msg, iofunc_ocb_t *__ocb, int *__nonblock);

/* Should be at start of write handler function */
extern int iofunc_write_verify(resmgr_context_t *__ctp, io_write_t *__msg, iofunc_ocb_t *__ocb, int *__nonblock);

/* Should be at start of space handler function */
extern int iofunc_space_verify(resmgr_context_t *__ctp, io_space_t *__msg, iofunc_ocb_t *__ocb, int *__nonblock);

/* Should be used by unlink handler function */
/*extern int iofunc_unlink(resmgr_context_t *__ctp, io_unlink_t *__msg, iofunc_attr_t *__attr, iofunc_attr_t *__dattr, struct _client_info *__info);*/

/* Used by iofunc_close_ocb_default */
extern int iofunc_ocb_detach(resmgr_context_t *__ctp, iofunc_ocb_t *__ocb);

/* Used to verify SYNC message */
extern int iofunc_sync_verify(resmgr_context_t *__ctp, io_sync_t *__msg, iofunc_ocb_t *__ocb);

/* Used by iofunc_*_default functions */
extern int iofunc_chmod(resmgr_context_t *__ctp, io_chmod_t *__msg, iofunc_ocb_t *__ocb, iofunc_attr_t *__attr);
extern int _iofunc_chmod(resmgr_context_t *__ctp, io_chmod_t *__msg, iofunc_ocb_t *__ocb, iofunc_attr_t *__attr, struct _client_info *__cred);
extern int iofunc_chown(resmgr_context_t *__ctp, io_chown_t *__msg, iofunc_ocb_t *__ocb, iofunc_attr_t *__attr);
extern int _iofunc_chown(resmgr_context_t *__ctp, io_chown_t *__msg, iofunc_ocb_t *__ocb, iofunc_attr_t *__attr, struct _client_info *__cred);
extern int iofunc_close_dup(resmgr_context_t *__ctp, io_close_t *__msg, iofunc_ocb_t *__ocb, iofunc_attr_t *__attr);
extern int iofunc_close_ocb(resmgr_context_t *__ctp, iofunc_ocb_t *__ocb, iofunc_attr_t *__attr);
extern int iofunc_devctl(resmgr_context_t *__ctp, io_devctl_t *__msg, iofunc_ocb_t *__ocb, iofunc_attr_t *__attr);
extern int iofunc_lock(resmgr_context_t *__ctp, io_lock_t *__msg, iofunc_ocb_t *__ocb, iofunc_attr_t *__attr);
extern int iofunc_lseek(resmgr_context_t *__ctp, io_lseek_t *__msg, iofunc_ocb_t *__ocb, iofunc_attr_t *__attr);
extern int iofunc_mmap(resmgr_context_t *__ctp, io_mmap_t *__msg, iofunc_ocb_t *__ocb, iofunc_attr_t *__attr);
extern int iofunc_openfd(resmgr_context_t *__ctp, io_openfd_t *__msg, iofunc_ocb_t *__ocb, iofunc_attr_t *__attr);
extern int iofunc_fdinfo(resmgr_context_t *__ctp, iofunc_ocb_t *__ocb, iofunc_attr_t *__attr, struct _fdinfo *__info);
extern int iofunc_pathconf(resmgr_context_t *__ctp, io_pathconf_t *__msg, iofunc_ocb_t *__ocb, iofunc_attr_t *__attr);
extern int iofunc_stat(resmgr_context_t *__ctp, iofunc_attr_t *__attr, struct stat *__stat);
extern int iofunc_unblock(resmgr_context_t *__ctp, iofunc_attr_t *__attr);
extern int iofunc_utime(resmgr_context_t *__ctp, io_utime_t *__msg, iofunc_ocb_t *__ocb, iofunc_attr_t *__attr);
extern int iofunc_sync(resmgr_context_t *__ctp, iofunc_ocb_t *__ocb, int __ioflag);
extern int iofunc_power(resmgr_context_t *__ctp, io_power_t *__msg, iofunc_ocb_t *__ocb, iofunc_attr_t *__attr);
extern int iofunc_acl(resmgr_context_t *__ctp, io_acl_t *__msg, iofunc_ocb_t *__ocb, iofunc_attr_t *__attr);

/* Used to force invalid times to be updated */
extern int iofunc_time_update(iofunc_attr_t *__attr);

/* notify functions */
extern int iofunc_notify(resmgr_context_t *__ctp, io_notify_t *__msg, iofunc_notify_t *__nop, int __trig, const int *__notifycnts, int *__armed);
extern void iofunc_notify_remove(resmgr_context_t *__ctp, iofunc_notify_t *__nop);
extern void iofunc_notify_remove_strict(resmgr_context_t *__ctp, iofunc_notify_t *__nop, int __lim);
extern void iofunc_notify_trigger(iofunc_notify_t *__nop, int __cnt, int __index);
extern void iofunc_notify_trigger_strict(resmgr_context_t *__ctp, iofunc_notify_t *__nop, int __cnt, int __index);


/*  Applications use procmgr_ability_lookup() with one of these paths and then
	pass that value to procmgr_ability().
*/
#define IOFUNC_ABILITY_CHOWN	"iofunc/chown"
#define IOFUNC_ABILITY_READ		"iofunc/read"
#define IOFUNC_ABILITY_EXEC		"iofunc/exec"
#define IOFUNC_ABILITY_DUP		"iofunc/dup"


/*  Supported resource manager abilities.  These are passed to iofunc_ability_check().
*/
typedef enum _iofunc_ability_e {
	IOFUNC_ABILITYID_CHOWN,		/* Allow setting the owner as if root */
	IOFUNC_ABILITYID_READ,		/* Allow access for reading */
	IOFUNC_ABILITYID_DUP,		/* Allow dup of other process handles */
	IOFUNC_ABILITYID_EXEC		/* ALLOW access for exec */
} iofunc_ability_e;

extern int iofunc_ability_check(const resmgr_context_t * const ctp, const iofunc_ability_e iofuncability);


#include <_packpop.h>

__END_DECLS

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/c/public/sys/iofunc.h $ $REV$")
#endif
