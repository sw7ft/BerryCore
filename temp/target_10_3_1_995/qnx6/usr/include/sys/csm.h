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
 *  csm.h    Non-portable low-level IO definitions
 *

 */

#ifndef __CSM_H_INCLUDED
#define __CSM_H_INCLUDED

#if defined(__WATCOMC__) && !defined(_ENABLE_AUTODEPEND)
 #pragma read_only_file;
#endif

#ifndef _INTTYPES_H_INCLUDED
 #include <inttypes.h>
#endif

#ifndef _ERRNO_H_INCLUDED
 #include <errno.h>
#endif

#ifndef __TYPES_H_INCLUDED
 #include <sys/types.h>
#endif

#ifndef __SIGINFO_H_INCLUDED
 #include <sys/siginfo.h>
#endif

#ifndef __NEUTRINO_H_INCLUDED
 #include <sys/neutrino.h>
#endif

#ifndef __DISPATCH_H_INCLUDED
 #include <sys/dispatch.h>
#endif

__BEGIN_DECLS

#include <_pack64.h>

/*
 *  Services message types
 */
enum _csv_bases {
	_CSM_BASE = 0x200,
	_CSM_MAX  = 0x2FF
};

enum _csm_Uint16types {
	_CSM_OPEN = _CSM_BASE,
	_CSM_CLOSE,
	_CSM_NOTIFY,
	_CSM_PUTGET,
	_CSM_PUT,
	_CSM_GET,
	_CSM_NOOP,
	_CSM_END
};

enum _csm_fd_types {
    _CSM_FD_TYPE_NAME,
    _CSM_FD_TYPE_REGULAR
};

#define CSM_NO_AUTHMAN       0x0001
/*
 * Setting the flag below causes a server to open resource /sys/csm/<server>/<instance>
 * (or /enterprise/sys/csm/<server>/<instance> if the process is running in the
 * enterprise partition [specifically getegid() or getgroups() returns a group == 1200
 * but no group==1000 is found]) if the path has no leading / (i.e. is a relative path).
 *
 * Without this flag the server will do a name_open().
 *
 * The use of this flag is recommended because it supports BS Launcher and allows centralized
 * permissions management via /etc/authman control files.
 */
#define CSM_POSIX_PERMS      0x0002
/* Set this to disable the automatic creation of the pulse handling thread.
 *
 * This would be useful if an application needed to run the thread differently or for debugging.
 * The system will work generally with this thread disabled but in various error conditions
 * the client may hang indefinitely.
 */
#define CSM_NO_PULSE_HANDLING_THREAD 0x0004
/*
 * By default, CSM sets the FD_CLOEXEC flag on its file descriptors so that they are
 * closed on a spawn/exec.  If, for some reason, an application wants the fds to be
 * open after the spawn or exec, this flag can be passed in to the msgclient_open() call.
 */
#define CSM_SUPPRESS_FD_CLOEXEC_FCNTL 0x0008

/*
 * By default, CSM releases all server resources after the close callback has been processed
 * and any outstanding messages have been replied to.  For most applications which generate a
 * single reply to each PUT (or PUTGET) this is convenient because there is no need for the
 * app developer to implement a mechanism to ensure that OSB_REPLY* is not invoked after the
 * close callback.
 *
 * For some applications (typically those which issue 0..N OSB_REPLY2() calls in response to a PUT request)
 * this default behavior is problematic because some PUT messages may never get a reply.
 * Setting this flag (on a msgserver_create()) causes the CSM system to release all resources after the close callback is
 * performed.  The application is responsible for implementing a mechanism to ensure that OSB_REPLY*
 * calls will not be made after the close callback.  If OSB_REPLY* is invoked after the close callback
 * then there is a chance that the memory will have been reused and memory corruption could occur.
 *
 */
#define CSM_RELEASE_OSB_AFTER_IMMEDIATELY_AFTER_CLOSE_CALLBACK 0x0010

#define CSM_SNAME_LEN        31
#define CSM_DEFAULT_INSTANCE "default"

/*
 * These are the prefixes for paths in to CSM servers in the personal and
 * enterprise partitions.  They can be used by appliations which need to build
 * absolute paths.
 */
#define CSM_PERSONAL_PARTITION_PATH_PREFIX "/sys/csm"
#define CSM_ENTERPRISE_PARTITION_PATH_PREFIX "/enterprise/sys/csm"


typedef struct _services_msg {
	int16_t    type;
    uint16_t   flags;
	int16_t    sidx;
	int16_t    oidx;
#if __SIZEOF_POINTER__ == 32
	void       *handle;
	void       *_handle;
#else
	void       *handle;
#endif
	int32_t    slen;
	int32_t    rlen;
	/* Unique incrementing number - used on the server to avoid replying to previously canceled msgs */
	unsigned  msg_id;
	int32_t    reserved[1];
} services_msg_t;


typedef struct _msgserver_data {
	int    rcvid;
	int    flags;
	struct _msg_info msginfo;
	struct _services_msg *msghdr;
	void   *msgdat; // User data
	int    datlen;  // Of user data
	dispatch_context_t	*ctp;
} msgserver_data_t;


typedef struct _msgserver_gets {
	struct _msgserver_gets  *next;
	void                    *handle;
	int                     len;
	int                     status;
	// Buffer follows here
} msgserver_gets_t;

struct _msgserver_service;

typedef struct _osb {
	char                      *service;
	void                      *userdata;
	pthread_mutex_t           mutex;  /* For userdata */
	int                       inuse;  /* Number of threads active on this osb */
	int                       maxgets;
	int                       numgets;
	int                       closeme;
	struct _msgserver_gets    *gets;
	struct _msgserver_control *scp;
	int                       scoid;
    struct sigevent           event;
    struct _msgserver_service *sep;
    int                       sep_index;
    int                       disconnect_rxed;
    /* List of msg_ids awaiting reply.  If the msg_id is negative then
     * we have generated a error reply for this message so we must discard
     * the reply which is eventually produced via a call to OSB_REPLY*.
     * 0 indicates a free slot.
     */
    int                       *msg_ids_awaiting_reply;
} osb_t;

/* OSB_REPLY, OSB_REPLYV and OSB_ERROR are used to reply to PUT or PUTGET messages
   from within the message handling callback. */
#define OSB_REPLY(osb, dap, buf, len) ((osb)->scp->reply(osb, dap, EOK, buf, len))
#define OSB_REPLYV(osb, dap, iov, niov) ((osb)->scp->replyv(osb, dap, EOK, iov, niov))
#define OSB_ERROR(osb, dap, err)      ((osb)->scp->reply(osb, dap, err, NULL, 0))

/* OSB_REPLY2 is used to respond to PUT messages from a client which must be handled outside
   of the message handling callback.  It does not support clients which use PUTGET. */
#define OSB_REPLY2(osb, rcvid, handle, err, iov, niov) ((osb)->scp->reply2(osb, rcvid, handle, err, iov, niov))

/* OSB_REPLY3 is used to respond to PUT or PUTGET messages from a client which must be handled outside
   of the message handling callback.  OSB_REPLY3 is recommended for use instead of OSB_REPLY2 because 
   OSB_REPLY3 supports both client interfaces (PUT+GET and PUTGET).  Note that the
   _rcvid integer and _msghdr struct must be preserved from the values referred to
   by the dap pointer passed in to the worker callback. */
#define OSB_REPLY3(osb, _rcvid, err, buf, len, _msghdr)				\
do {                                                                             \
  msgserver_data_t __da;  memset(&__da, 0, sizeof(__da));		         \
  __da.rcvid = _rcvid; __da.msghdr = _msghdr;			                 \
  ((osb)->scp->reply(osb, &__da, err, buf, len));	                         \
} while (0);


typedef struct _msgserver_control {
	unsigned        flags;
	int             authman_fd;
    int             datminlen;
    int             datmaxlen;
	int             maxgets;
	int             stop;
	int             chid;
	int             (*reply)(struct _osb *osb, struct _msgserver_data *dap, int status, void *buf, int len);
	int             (*replyv)(struct _osb *osb, struct _msgserver_data *dap, int status, iov_t *iov, int niov);
	int             (*reply2)(struct _osb *osb, int rcvid, void *handle, int status, iov_t *iov, int niov);
	dispatch_t      *dpp;
	pthread_key_t   datakey;   /* Key for per thread received msgs */
	void            *userdata;
	pthread_mutex_t mutex;     /* To protect data structures for very short periods */
	int             disconnect_pending_count; /* +1 for each disconnect rxed by pulse handling thread (needs to be processed in the msg processing loop) */
	unsigned        unblock_count; /* Count of msgs rxed on msg handling thread */
	unsigned        num_active_threads; /* count of active thread. 0 if all threads are are blocked awaiting a msg */
	struct _csm_array *arrayp;
} msgserver_control_t;


struct _iofunc_attr;
typedef struct _msgserver_service {
	char              *service;
	char              *capabilities;
	char              *userdata;
	pthread_mutex_t   mutex;  // For userdata
	int               numopens;
	void     (*worker)(struct _osb *osb, struct _msgserver_data *dap, struct _msgserver_service *sep);
	int      (*open)  (struct _osb *osb, struct _msgserver_data *dap, struct _msgserver_service *sep);
	void     (*close) (struct _osb *osb, struct _msgserver_data *dap, struct _msgserver_service *sep);
	struct _csm_array *arrayp;
	struct _iofunc_attr *attr;
	char              *instance;
} msgserver_service_t;


typedef struct _msgclient_open {
	int    fd;
	int    sidx;
	int    oidx;
	union {
		struct {
			int chid;
			int coid;
		} channel;
	} wait;
	char   service[CSM_SNAME_LEN + 1];
    int fd_type; /* whether fd opened by name_open() or open() */
    uint64_t timeout_in_ns;
    uint64_t timeout_tolerance_in_ns;
    int clock_type;  /* e.g. CLOCK_SOFTTIME or CLOCK_REALTIME */
    volatile unsigned next_msg_id; /* Incremented with atomic_add_value() */
} msgclient_open_t;


/* Protos */
msgserver_control_t *msgserver_create(const int maxlen, int maxgets, const int flags);
/*
 * By default msgserver_add() opens a path under /sys/csm or /enterprise/sys/csm as appropriate
 * (see comment for CSM_POSIX_PERMS). To override this or connect to a CSM server in another
 * folder, the service name can be the complete path to the service (i.e. starting with /),
 * including the instance.
 * For example /sys/csm/myservice/default or /enterprise/sys/csm/service2/default. Note that
 * if the service starts with "/", the instance argument is ignored.
 * See the constants CSM_PERSONAL_PARTITION_PATH_PREFIX and CSM_ENTERPRISE_PARTITION_PATH_PREFIX
 * which can be used to build absolute paths when required.
 *
 */
int                 msgserver_add(msgserver_control_t *scp, const char *service, const char *instance, const char *capabilities, int minlen,
                                  void (*workerfunc)(),
                                  int  (*openfunc)(),
                                  void (*closefunc)());
int                 msgserver_receive(msgserver_control_t *scp);
int                 msgserver_dispatch(msgserver_control_t *scp);
int                 msgserver_growmsg(const msgserver_control_t *scp, const int newlen);
int                 msgserver_event(osb_t *osb);
void                *msgserver_thread_loop(void *arg);
void                *msgserver_thread_loop_pulse_only (void *arg);


/*
 * By default msgclient_open() opens a path under /sys/csm or /enterprise/sys/csm as appropriate
 * (see comment for CSM_POSIX_PERMS). To override this or connect to a CSM server in another
 * folder, the service name can be the complete path to the service (i.e. starting with /),
 * including the instance.
 * For example /sys/csm/myservice/default or /enterprise/sys/csm/service2/default. Note that
 * if the service starts with "/", the domain argument is ignored.
 * See the constants CSM_PERSONAL_PARTITION_PATH_PREFIX and CSM_ENTERPRISE_PARTITION_PATH_PREFIX
 * which can be used to build absolute paths when required.
 */
msgclient_open_t    *msgclient_open(const char *service, const char *domain, int flags);

/* This method sets a timeout on a transaction with the server.
 * The call (e.g. msgclient_putget()) will return EINTR or ETIMEDOUT on timeout.
 * clock_type is typically CLOCK_SOFTTIME or CLOCK_REALTIME.
 * See the "Slop in timer firing" section of
 *        http://wikis.rim.net/display/BBOSPower/CPU+Power+Management
 *          for information about the timer tolerance parameter.  It can be safely set to 0.
 */
void                msgclient_set_timeout (msgclient_open_t *mop, const int clock_type, const uint64_t timeout_in_ns, const uint64_t timeout_tolerance_in_ns);
int                 msgclient_close(msgclient_open_t *mop);
int                 msgclient_putget(msgclient_open_t *mop, void *sbuf, const int slen, void *rbuf, const int rmax, int *rlen, const int flags);
int                 msgclient_putgetv(msgclient_open_t *mop, iov_t *_siov, const int nsiov, iov_t *_riov, const int nriov, int *rlen, const int flags);
int                 msgclient_put(msgclient_open_t *mop, void *handle, void *sbuf, const int slen, const int flags);
int                 msgclient_putv(msgclient_open_t *mop, void *handle, iov_t *iov, const int niov, const int flags);
int                 msgclient_get(msgclient_open_t *mop, void *handle, void *rbuf, const int rmax, int *rlen, const int flags);
int                 msgclient_getv(msgclient_open_t *mop, void *handle, iov_t *iov, const int niov, int *rlen, const int flags);
int                 msgclient_notify(msgclient_open_t *mop, int numputs, struct sigevent *event);
int                 msgclient_notify_pulse(msgclient_open_t *mop, const int numputs);
void                *msgclient_wait_pulse(msgclient_open_t *mop);

#include <_packpop.h>

__END_DECLS

#endif

#include <sys/srcversion.h>
__SRCVERSION( "$URL$ $Rev$" )
