/*
 * $QNXLicenseC:
 * Copyright 2007, 2009, QNX Software Systems. All Rights Reserved.
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

#ifndef __NEUTRINO_H_INCLUDED
#define __NEUTRINO_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
# include <sys/platform.h>
#endif

/* We really don't need to include sys/types.h at all since nothing in neutrino.h
 * depends on it.  However, we did before so for backwards compatibility we must
 * continue to do so.
 */
#ifndef __TYPES_H_INCLUDED
# include _NTO_HDR_(sys/types.h)
#endif

#ifndef _SIGNAL_H_INCLUDED
# include _NTO_HDR_(signal.h)
#endif

#if defined(__EXT_POSIX1_199309) || defined(__EXT_POSIX1_199506) || defined(__EXT_POSIX1_200112)
/* We really shouldn't include sched.h at all since nothing in neutrino.h depends
 * on it.  However, we did before so for backwards compatibility we must continue
 * to do so.  But, sched.h is only supported in and after POSIX-1993, so in order
 * to compile in older environments we only include sched.h in those later versions.
 */
# ifndef _SCHED_H_INCLUDED
#  include _NTO_HDR_(sched.h)
# endif
#endif

#ifndef _TIME_H_INCLUDED
# include _NTO_HDR_(time.h)
#endif

#ifndef _LIMITS_H_INCLUDED
# include _NTO_HDR_(limits.h)
#endif

#ifndef __STORAGE_H_INCLUDED
# include _NTO_HDR_(sys/storage.h)
#endif

#ifndef __STATES_H_INCLUDED
# include _NTO_HDR_(sys/states.h)
#endif

#if defined(__SYNC_T)
typedef __SYNC_T		sync_t;
# undef __SYNC_T
#endif

#if defined(__SYNC_ATTR_T)
typedef __SYNC_ATTR_T	sync_attr_t;
# undef __SYNC_ATTR_T
#endif

#if defined(__SCHED_PARAM_T)
typedef __SCHED_PARAM_T	sched_param_t;
# undef __SCHED_PARAM_T
#endif

#if defined(__PTHREAD_ATTR_T)
typedef __PTHREAD_ATTR_T	pthread_attr_t;
# undef __PTHREAD_ATTR_T
#endif

// BB10 is actually qnx6 with some extras. Qt5 multimedia relies on newer alsa
//#define _NTO_VERSION	800	/* version number * 100 */
#define _NTO_VERSION	660	/* version number * 100 */

#define SYSMGR_PID		1
#define SYSMGR_CHID		1
#define SYSMGR_COID		_NTO_SIDE_CHANNEL	/* System process connection is always the first side channel */
#define SYSMGR_HANDLE	0

typedef struct intrspin {
	volatile unsigned	value;
} intrspin_t;

__BEGIN_DECLS

#include _NTO_CPU_HDR_(neutrino.h)

#include _NTO_HDR_(_pack64.h)

typedef sync_t		nto_job_t;

#define _NTO_TIMEOUT_RECEIVE		(1<<STATE_RECEIVE)
#define _NTO_TIMEOUT_SEND			(1<<STATE_SEND)
#define _NTO_TIMEOUT_REPLY			(1<<STATE_REPLY)
#define _NTO_TIMEOUT_SIGSUSPEND		(1<<STATE_SIGSUSPEND)
#define _NTO_TIMEOUT_SIGWAITINFO	(1<<STATE_SIGWAITINFO)
#define _NTO_TIMEOUT_NANOSLEEP		(1<<STATE_NANOSLEEP)
#define _NTO_TIMEOUT_MUTEX			(1<<STATE_MUTEX)
#define _NTO_TIMEOUT_CONDVAR		(1<<STATE_CONDVAR)
#define _NTO_TIMEOUT_JOIN			(1<<STATE_JOIN)
#define _NTO_TIMEOUT_INTR			(1<<STATE_INTR)
#define _NTO_TIMEOUT_SEM			(1<<STATE_SEM)

struct _msg_info {							/* _msg_info	_server_info */
	_Uint32t					nd;			/*  client      server */
	_Uint32t					srcnd;		/*  server      n/a */
	pid_t						pid;		/*	client		server */
	_Int32t						tid;		/*	thread		n/a */
	_Int32t						chid;		/*	server		server */
	_Int32t						scoid;		/*	server		server */
	_Int32t						coid;		/*	client		client */
	_Int32t						msglen;		/*	msg			n/a */
	_Int32t						srcmsglen;	/*	thread		n/a */
	_Int32t						dstmsglen;	/*	thread		n/a */
	_Int16t						priority;	/*	thread		n/a */
	_Int16t						flags;		/*	n/a			client */
	_Uint32t					reserved;
};
#define _server_info	_msg_info
#define _NTO_MI_ENDIAN_BIG		0x00000001	/* Same as _NTO_CI_ENDIAN_BIG */
#define _NTO_MI_ENDIAN_DIFF		0x00000002
#define _NTO_MI_NET_CRED_DIRTY	0x00000200
#define _NTO_MI_UNBLOCK_REQ		0x00000100
#define _NTO_MI_CONSTRAINED		0x00000400	/* Client subject to resource constraint thresholds */
#define _NTO_MI_CHROOT			0x00000800	/* Client process has been chrooted */

/*
 * _cred_info and _client_info
 *
 * These structures are defined with a fixed-sized grouplist field
 * for backwards compatibility.  However, they are often used with
 * an arbitrary-sized grouplist field.  As such, the grouplist field
 * must come at the end of the structures.
 */
struct _cred_info {
	uid_t						ruid;
	uid_t						euid;
	uid_t						suid;
	gid_t						rgid;
	gid_t						egid;
	gid_t						sgid;
	_Uint32t					ngroups;
	gid_t						grouplist[__NGROUPS_MAX];
};

struct _client_info {
	_Uint32t					nd;
	pid_t						pid;
	pid_t						sid;
	_Uint32t					flags;
	struct _cred_info			cred;
};

/*
 * See <sys/clientinfo.h>.  There you will find macros for
 * declaring and determining the size of variable-sized
 * _cred_info and _client_info structures.
 */

#define _NTO_CI_ENDIAN_BIG		0x00000001	/* Same as _NTO_MI_ENDIAN_BIG */
#define _NTO_CI_BKGND_PGRP		0x00000004
#define _NTO_CI_ORPHAN_PGRP		0x00000008
#define _NTO_CI_STOPPED			0x00000080
#define _NTO_CI_UNABLE			0x00000100 /* Failed ability check */
#define _NTO_CI_FULL_GROUPS     0x80000000 /* indicates ngroups/grouplist contain complete info */
	/* _NTO_CI_FULL_GROUPS is used in supporting backwards compatibility between pre-6.6
	 * (where everything was limited to 8 groups and _cred_info was hard-coded to 8 groups)
	 * and 6.6+ (where ngroups might be greater than 8).  This flag will be set by
	 * ConnectClientInfoExt() but not by the older ConnectClientInfo() so that any code
	 * that looks at the client info will know whether or not it can trust that the group
	 * list is complete.
	 */

struct _client_able {
    _Uint32t ability;
    _Uint32t flags;
    _Uint64t range_lo;
    _Uint64t range_hi;
};

struct _vtid_info {
	_Int32t		tid;
	_Int32t		coid;
	_Int32t		priority;
	_Int32t		srcmsglen;
	_Int32t		keydata;
	_Int32t		srcnd;
	_Int32t		dstmsglen;
	_Int32t		zero;
};

#define _NTO_TIMER_SEARCH			0x00000001
#define _NTO_TIMER_RESET_OVERRUNS	0x00000002

#if defined(__CLOCKADJUST)
struct _clockadjust __CLOCKADJUST;
#undef __CLOCKADJUST
#endif

#if defined(__ITIMER)
struct _itimer __ITIMER;
#undef __ITIMER
#endif

#ifdef __TIMER_INFO
struct _timer_info __TIMER_INFO;
#undef __TIMER_INFO
#endif

struct _sighandler_info {
	siginfo_t			siginfo;
	void				(*handler)(_SIG_ARGS);
	void				*context;
	/* void				data[] */
};

struct _sched_info {
	int					priority_min;
	int					priority_max;
	_Uint64t			interval;
	int					priority_priv;
	int					reserved[11];
};

#define _NTO_TI_ACTIVE				0x00000001u
#define _NTO_TI_ABSOLUTE			0x00000002u
#define _NTO_TI_EXPIRED				0x00000004u
#define _NTO_TI_TOD_BASED			0x00000008u
#define _NTO_TI_TARGET_PROCESS		0x00000010u
#define _NTO_TI_REPORT_TOLERANCE	0x00000020u
#define _NTO_TI_PRECISE				0x00000040u
#define _NTO_TI_TOLERANT			0x00000080u
#define _NTO_TI_WAKEUP				0x00000100u
#define _NTO_TI_PROCESS_TOLERANT	0x00000200u

/*
 * Definitions for type and subtype of any pulse.
 * We keep the codes away from the defined SI_ signal codes to prevent
 * confusion.
 */
#define _PULSE_TYPE					0
#define _PULSE_SUBTYPE				0
#define _PULSE_CODE_UNBLOCK			(-32)	/* value - rcvid */
#define _PULSE_CODE_DISCONNECT		(-33)	/* value - server connection */
#define _PULSE_CODE_THREADDEATH		(-34)	/* value - thread id */
#define _PULSE_CODE_COIDDEATH		(-35)	/* value - coid */
#define _PULSE_CODE_NET_ACK			(-36)	/* value - vtid; not in use anymore */
#define _PULSE_CODE_NET_UNBLOCK		(-37)	/* value - vtid */
#define _PULSE_CODE_NET_DETACH		(-38)	/* value - coid */
#define _PULSE_CODE_RESTART			(-39)	/* value - cookie */
#define _PULSE_CODE_NORESTART		(-40)	/* value - cookie */
#define _PULSE_CODE_UNBLOCK_RESTART	(-41)	/* value - rcvid */
#define _PULSE_CODE_UNBLOCK_TIMER	(-42)	/* value - rcvid */

#define _PULSE_CODE_MINAVAIL	0	/* QNX managers will never use this range */
#define _PULSE_CODE_MAXAVAIL	127

struct _pulse {
	_Uint16t					type;
	_Uint16t					subtype;
	_Int8t						code;
	_Uint8t						zero[3];
	union sigval				value;
	_Int32t						scoid;
};


/*
 * Define interrupt flags.
 */
#define _NTO_HARD_FLAGS_END		0x01

/*
 * Define flags which can be applied to a pulse type.
 */
#define _NTO_PULSE_IF_UNIQUE	0x1000
#define _NTO_PULSE_REPLACE		0x2000

/*
 * Define the flags of a process PROCESS.flags
 */
#define _NTO_PF_NOCLDSTOP		0x00000001u
#define _NTO_PF_LOADING			0x00000002u
#define _NTO_PF_TERMING			0x00000004u
#define _NTO_PF_ZOMBIE			0x00000008u
#define _NTO_PF_NOZOMBIE		0x00000010u
#define _NTO_PF_FORKED			0x00000020u
#define _NTO_PF_ORPHAN_PGRP		0x00000040u
#define _NTO_PF_STOPPED			0x00000080u
#define _NTO_PF_DEBUG_STOPPED	0x00000100u
#define _NTO_PF_BKGND_PGRP		0x00000200u
#define _NTO_PF_NO_LIMITS		0x00000400u
#define _NTO_PF_CONTINUED		0x00000800u
#define _NTO_PF_CHECK_INTR		0x00001000u
#define _NTO_PF_COREDUMP		0x00002000u
#define _NTO_PF_PTRACED			0x00004000u
#define _NTO_PF_RING0			0x00008000u
#define _NTO_PF_SLEADER			0x00010000u
#define _NTO_PF_WAITINFO		0x00020000u
#define _NTO_PF_VFORKED			0x00040000u
#define _NTO_PF_DESTROYALL		0x00080000u
#define _NTO_PF_NOCOREDUMP		0x00100000u
#define _NTO_PF_NOCTTY			0x00200000u
#define _NTO_PF_WAITDONE		0x00400000u
#define _NTO_PF_TERM_WAITING	0x00800000u
#define _NTO_PF_ASLR			0x01000000u
#define _NTO_PF_EXECED			0x02000000u
#define _NTO_PF_APP_STOPPED		0x04000000u
#define _NTO_PF_THREADWATCH		0x80000000u

/*
 * Define the flags of a thread THREAD.flags
 */
#define _NTO_TF_INTR_PENDING	0x00010000
#define _NTO_TF_DETACHED		0x00020000
#define _NTO_TF_SYSCALL_EMU		0x00040000
#define _NTO_TF_THREADS_HOLD	0x00100000
#define _NTO_TF_UNBLOCK_REQ		0x00400000
#define _NTO_TF_ALIGN_FAULT		0x01000000
#define _NTO_TF_SSTEP			0x02000000
#define _NTO_TF_ALLOCED_STACK	0x04000000
#define _NTO_TF_NOMULTISIG		0x08000000
#define _NTO_TF_FROZEN			0x10000000
#define _NTO_TF_IOPRIV			0x80000000

/*
 * Thread Control commands
 */
#define _NTO_TCTL_IO_PRIV				1
#define _NTO_TCTL_THREADS_HOLD			2
#define _NTO_TCTL_THREADS_CONT			3
#define _NTO_TCTL_RUNMASK				4
#define _NTO_TCTL_ALIGN_FAULT			5
#define _NTO_TCTL_RUNMASK_GET_AND_SET	6
#define _NTO_TCTL_PERFCOUNT				7
#define _NTO_TCTL_ONE_THREAD_HOLD		8
#define _NTO_TCTL_ONE_THREAD_CONT		9
#define _NTO_TCTL_RUNMASK_GET_AND_SET_INHERIT	10
#define _NTO_TCTL_NAME					11
#define _NTO_TCTL_RCM_GET_AND_SET		12
#define _NTO_TCTL_SYSCALL_EMU			13
#define _NTO_TCTL_IO					14
#define _NTO_TCTL_RESERVED				0x80000000


/*
 * Limit on the maximum number of characters for a thread name
 */
#define _NTO_THREAD_NAME_MAX			100

struct _thread_name {
	int 	new_name_len;
	int 	name_buf_len;
	__FLEXARY(char, name_buf); /* char name_buf[] */
};

/*
 * Where 'size' must be the precise value required
 * to define the number of cpus currently on the
 * system: eg. RMSK_SIZE(_syspage_ptr->num_cpu).
 */
struct _thread_runmask {
	int			size;
	/*	unsigned	runmask[size];		*/
	/*	unsigned	inherit_mask[size];	*/
};

#define RMSK_SIZE(num_cpu)	(((num_cpu) - 1) / __INT_BITS__ + 1)

/* Where 'cpu' is zero based */
#define RMSK_SET(cpu, p)	((p)[(cpu) / __INT_BITS__] |=	\
							 (1 << ((cpu) % __INT_BITS__)))

#define RMSK_CLR(cpu, p)	((p)[(cpu) / __INT_BITS__] &=		\
							 ~(1 << ((cpu) % __INT_BITS__)))

#define RMSK_ISSET(cpu, p)	((p)[(cpu) / __INT_BITS__] &	\
							 (1 << ((cpu) % __INT_BITS__)))

/*
 * Define channel flags
 */
#define _NTO_CHF_FIXED_PRIORITY		0x0001u
#define _NTO_CHF_UNBLOCK			0x0002u
#define _NTO_CHF_THREAD_DEATH		0x0004u
#define _NTO_CHF_DISCONNECT			0x0008u
#define _NTO_CHF_NET_MSG			0x0010u
#define _NTO_CHF_SENDER_LEN			0x0020u
#define _NTO_CHF_COID_DISCONNECT	0x0040u
#define _NTO_CHF_REPLY_LEN			0x0080u
#define _NTO_CHF_STICKY				0x0100u
#define _NTO_CHF_ASYNC_NONBLOCK		0x0200u
#define _NTO_CHF_ASYNC				0x0400u
#define _NTO_CHF_GLOBAL				0x0800u
#define _NTO_CHF_PRIVATE			0x1000u
#define _NTO_CHF_MSG_PAUSING		0x2000u
#define _NTO_CHF_SIG_RESTART		0x4000u
#define _NTO_CHF_UNBLOCK_TIMER		0x8000u


/*
 * Define connect flags
 */
#define _NTO_COF_CLOEXEC		0x0001
#define _NTO_COF_DEAD			0x0002
#define _NTO_COF_NOSHARE		0x0040
#define _NTO_COF_NETCON			0x0080
#define _NTO_COF_NONBLOCK		0x0100
#define _NTO_COF_ASYNC			0x0200
#define _NTO_COF_GLOBAL			0x0400
#define _NTO_COF_NOEVENT		0x0800
#define _NTO_COF_INSECURE		0x1000

/* If the 2nd from top bit is set then we don't use the fd connection vector. */
#define _NTO_SIDE_CHANNEL		((~0u ^ (~0u >> 1)) >> 1)
/* If the 2nd from top bit is set in the channel id, then it is a global channel. */
#define _NTO_GLOBAL_CHANNEL		((~0u ^ (~0u >> 1)) >> 1)


/*
 * Define flags of a timeout
 * The first n bits are reserved for (1L << thp->state)
 */
#define _NTO_TIMEOUT_MASK		((1 << STATE_MAX) - 1)
#define _NTO_TIMEOUT_ACTIVE		(1 << STATE_MAX)
#define _NTO_TIMEOUT_IMMEDIATE	(1 << (STATE_MAX+1))


/*
 * InterruptCharacteristic types
 */
#define _NTO_IC_LATENCY					0

/*
 * Flag bits for InterruptAttach[Event]
 */
#define _NTO_INTR_FLAGS_END			0x01u
#define _NTO_INTR_FLAGS_NO_UNMASK	0x02u
#define _NTO_INTR_FLAGS_PROCESS		0x04u
#define _NTO_INTR_FLAGS_TRK_MSK		0x08u

/*
 * System independent interrupt classes for InterruptAttach[Event]
 */
#define _NTO_INTR_CLASS_EXTERNAL	(0x0000UL << 16)
#define _NTO_INTR_CLASS_SYNTHETIC	(0x7fffUL << 16)

#define _NTO_INTR_SPARE			(_NTO_INTR_CLASS_SYNTHETIC|0xffffu)

#define _NTO_HOOK_TRACE			(_NTO_INTR_CLASS_SYNTHETIC|0u)
#define _NTO_HOOK_IDLE			(_NTO_INTR_CLASS_SYNTHETIC|1u)
#define _NTO_HOOK_OVERDRIVE		(_NTO_INTR_CLASS_SYNTHETIC|2u)
#define _NTO_HOOK_LAST			(_NTO_INTR_CLASS_SYNTHETIC|2u)
#define _NTO_HOOK_IDLE2_FLAG	0x8000u

/*
 * Idle Hook Control structure
 */
#define _NTO_IH_CMD_SLEEP_SETUP		0x00000001u
#define _NTO_IH_CMD_SLEEP_BLOCK		0x00000002u
#define _NTO_IH_CMD_SLEEP_WAKEUP	0x00000004u
#define _NTO_IH_CMD_SLEEP_ONLINE	0x00000008u

#define _NTO_IH_RESP_NEEDS_BLOCK		0x00000001u
#define _NTO_IH_RESP_NEEDS_WAKEUP		0x00000002u
#define _NTO_IH_RESP_NEEDS_ONLINE		0x00000004u
#define _NTO_IH_RESP_SYNC_TIME			0x00000010u
#define _NTO_IH_RESP_SYNC_TLB			0x00000020u
/*#define _NTO_IH_RESP_SYNC_ICACHE		0x00000040u not supported yet */
/*#define _NTO_IH_RESP_SYNC_DCACHE		0x00000080u not supported yet */
#define _NTO_IH_RESP_SUGGEST_OFFLINE	0x00000100u
#define _NTO_IH_RESP_SLEEP_MODE_REACHED	0x00000200u
#define _NTO_IH_RESP_DELIVER_INTRS		0x00000400u

struct _idle_hook {
	unsigned		hook_size;
	unsigned		cmd;
	unsigned		mode;
	unsigned		latency;
	_Uint64t		next_fire;
	_Uint64t		curr_time;
	_Uint64t		tod_adjust;
	unsigned		resp;
	struct {
		unsigned		length;
		unsigned		scale;
	}				time;
	struct sigevent	trigger;
	unsigned		*intrs;
	unsigned		block_stack_size;
};


/*
 * Define flags for MsgReadiov
 */
#define _NTO_READIOV_SEND		0
#define _NTO_READIOV_REPLY		1

struct _clockperiod {
	unsigned long				nsec;
	long						fract;
};

/*
 * Limits
 */
#define LIMITS_PROCESS		0
#define LIMITS_THREAD		1
#define LIMITS_TIMER		2
#define LIMITS_PULSE		3
#define LIMITS_SYNC			4
#define LIMITS_CONNECT		5
#define LIMITS_CHANNEL		6
#define LIMITS_INTERRUPT	7
#define LIMITS_SYNCEVENT	8
#define LIMITS_NUM			9

/*
 * Operation to tell MsgKeyData to verify instead of calculate
 */
#define _NTO_KEYDATA_VERIFY				0
#define _NTO_KEYDATA_CALCULATE			1
#define _NTO_KEYDATA_CALCULATE_REUSE	2

/*
 * Sync Control commands
 */
#define _NTO_SCTL_SETPRIOCEILING	1		/* mutex	const int *prioceiling */
#define _NTO_SCTL_GETPRIOCEILING	2		/* mutex	int *prioceiling */
#define _NTO_SCTL_SETEVENT			3		/* mutex	struct sigevent *event */
#define _NTO_SCTL_MUTEX_WAKEUP		4		/* mutex	wakeup thread blocking on mutex */

/*
 * ConnectClientInfoExt flags
 */
#define _NTO_CLIENTINFO_GETGROUPS 1

struct iovec;
struct _asyncmsg_connection_descriptor;
union _channel_connect_attr;

/*
 * types/macros for the Power*() calls
 */

enum nto_power_parameter_type {
    _NTO_PPT_NONE,
    _NTO_PPT_SPARE1,
    _NTO_PPT_SPARE2,
    _NTO_PPT_DEFINE_CLUSTER,
    _NTO_PPT_DEFINE_CPU,
    _NTO_PPT_DEFINE_FREQ
};

enum nto_power_freq_reason {
    _NTO_PFR_NONE,
    _NTO_PFR_UNDERFLOW,
    _NTO_PFR_OVERFLOW,
    _NTO_PFR_WAYPOINT,
    _NTO_PFR_THREAD_HISTORY,
    _NTO_PFR_JOB_HISTORY,
    _NTO_PFR_MASK = 0xffff,
};

#define _NTO_PFR_PARM_ID_SHIFT		16

struct nto_power_range {
    _Uint16t load;
    _Uint16t duration;
};

struct nto_power_parameter {
    _Uint16t parameter_type;
    _Uint16t clusterid;
    _Uint32t spare;
    union {
        struct nto_power_cluster {
            _Uint32t frequency_mask;
        } cluster;
        struct nto_power_cpu {
			_Uint32t cpuid;
            _Uint32t unloaded;
            struct {
                _Uint16t nonburst;
                _Uint16t burst;
            } loaded;
        } cpu;
        struct nto_power_freq {
            _Uint32t performance;
            struct nto_power_range low;
            struct nto_power_range high;
            struct sigevent ev;
			_Uint32t max_cores_online_hint;
        } freq;
    } u;
};

#define _NTO_PP_ID_NEXT 0x80000000u

/*
 * Function prototypes for all kernel calls.
 */
extern int ChannelCreate(unsigned __flags);
extern int ChannelCreate_r(unsigned __flags);
extern int ChannelCreateExt(unsigned __flags, mode_t __mode, size_t __bufsize, unsigned __maxnumbuf, const struct sigevent *__ev, struct _cred_info *__cred);
extern int ChannelDestroy(int __chid);
extern int ChannelDestroy_r(int __chid);
extern int ConnectAttach(_Uint32t __nd, pid_t __pid, int __chid, unsigned __index, int __flags);
extern int ConnectAttach_r(_Uint32t __nd, pid_t __pid, int __chid, unsigned __index, int __flags);
extern int ConnectAttachExt(_Uint32t __nd, pid_t __pid, int __chid, unsigned __index, int __flags, struct _asyncmsg_connection_descriptor *__cd);
extern int ConnectDetach(int __coid);
extern int ConnectDetach_r(int __coid);
extern int ConnectServerInfo(pid_t __pid, int __coid, struct _server_info *__info);
extern int ConnectServerInfo_r(pid_t __pid, int __coid, struct _server_info *__info);
extern int ConnectClientInfo(int __scoid, struct _client_info *__info, int __ngroups);
extern int ConnectClientInfo_r(int __scoid, struct _client_info *__info, int __ngroups);
extern int ConnectClientInfoExt(int __scoid, struct _client_info **__info_pp, int flags);
extern int ClientInfoExtFree(struct _client_info **__info_pp);
extern int ConnectClientInfoAble(int __scoid, struct _client_info **__info_pp, int flags, struct _client_able * const abilities, const int nable);
extern int ConnectFlags(pid_t __pid, int __coid, unsigned __mask, unsigned __bits);
extern int ConnectFlags_r(pid_t __pid, int __coid, unsigned __mask, unsigned __bits);
extern int ChannelConnectAttr(unsigned __id, union _channel_connect_attr *__old_attr, union _channel_connect_attr *__new_attr, unsigned __flags);


extern int MsgSend(int __coid, const void *__smsg, int __sbytes, void *__rmsg, int __rbytes);
extern int MsgSend_r(int __coid, const void *__smsg, int __sbytes, void *__rmsg, int __rbytes);
extern int MsgSendnc(int __coid, const void *__smsg, int __sbytes, void *__rmsg, int __rbytes);
extern int MsgSendnc_r(int __coid, const void *__smsg, int __sbytes, void *__rmsg, int __rbytes);
extern int MsgSendsv(int __coid, const void *__smsg, int __sbytes, const struct iovec *__riov, int __rparts);
extern int MsgSendsv_r(int __coid, const void *__smsg, int __sbytes, const struct iovec *__riov, int __rparts);
extern int MsgSendsvnc(int __coid, const void *__smsg, int __sbytes, const struct iovec *__riov, int __rparts);
extern int MsgSendsvnc_r(int __coid, const void *__smsg, int __sbytes, const struct iovec *__riov, int __rparts);
extern int MsgSendvs(int __coid, const struct iovec *__siov, int __sparts, void *__rmsg, int __rbytes);
extern int MsgSendvs_r(int __coid, const struct iovec *__siov, int __sparts, void *__rmsg, int __rbytes);
extern int MsgSendvsnc(int __coid, const struct iovec *__siov, int __sparts, void *__rmsg, int __rbytes);
extern int MsgSendvsnc_r(int __coid, const struct iovec *__siov, int __sparts, void *__rmsg, int __rbytes);
extern int MsgSendv(int __coid, const struct iovec *__siov, int __sparts, const struct iovec *__riov, int __rparts);
extern int MsgSendv_r(int __coid, const struct iovec *__siov, int __sparts, const struct iovec *__riov, int __rparts);
extern int MsgSendvnc(int __coid, const struct iovec *__siov, int __sparts, const struct iovec *__riov, int __rparts);
extern int MsgSendvnc_r(int __coid, const struct iovec *__siov, int __sparts, const struct iovec *__riov, int __rparts);
extern int MsgReceive(int __chid, void *__msg, int __bytes, struct _msg_info *__info);
extern int MsgReceive_r(int __chid, void *__msg, int __bytes, struct _msg_info *__info);
extern int MsgReceivev(int __chid, const struct iovec *__iov, int __parts, struct _msg_info *__info);
extern int MsgReceivev_r(int __chid, const struct iovec *__iov, int __parts, struct _msg_info *__info);
extern int MsgReceivePulse(int __chid, void *__pulse, int __bytes, struct _msg_info *__info);
extern int MsgReceivePulse_r(int __chid, void *__pulse, int __bytes, struct _msg_info *__info);
extern int MsgReceivePulsev(int __chid, const struct iovec *__iov, int __parts, struct _msg_info *__info);
extern int MsgReceivePulsev_r(int __chid, const struct iovec *__iov, int __parts, struct _msg_info *__info);
extern int MsgReply(int __rcvid, int __status, const void *__msg, int __bytes);
extern int MsgReply_r(int __rcvid, int __status, const void *__msg, int __bytes);
extern int MsgReplyv(int __rcvid, int __status, const struct iovec *__iov, int __parts);
extern int MsgReplyv_r(int __rcvid, int __status, const struct iovec *__iov, int __parts);
extern int MsgReadiov(int __rcvid, const struct iovec *__iov, int __parts, int __offset, int __flags);
extern int MsgReadiov_r(int __rcvid, const struct iovec *__iov, int __parts, int __offset, int __flags);
extern int MsgRead(int __rcvid, void *__msg, int __bytes, int __offset);
extern int MsgRead_r(int __rcvid, void *__msg, int __bytes, int __offset);
extern int MsgReadv(int __rcvid, const struct iovec *__iov, int __parts, int __offset);
extern int MsgReadv_r(int __rcvid, const struct iovec *__iov, int __parts, int __offset);
extern int MsgWrite(int __rcvid, const void *__msg, int __bytes, int __offset);
extern int MsgWrite_r(int __rcvid, const void *__msg, int __bytes, int __offset);
extern int MsgWritev(int __rcvid, const struct iovec *__iov, int __parts, int __offset);
extern int MsgWritev_r(int __rcvid, const struct iovec *__iov, int __parts, int __offset);
extern int MsgSendPulse(int __coid, int __priority, int __code, int __value);
extern int MsgSendPulse_r(int __coid, int __priority, int __code, int __value);
extern int MsgDeliverEvent(int __rcvid, const struct sigevent *__event);
extern int MsgDeliverEvent_r(int __rcvid, const struct sigevent *__event);
extern int MsgVerifyEvent(int __rcvid, const struct sigevent *__event);
extern int MsgVerifyEvent_r(int __rcvid, const struct sigevent *__event);
extern int MsgInfo(int __rcvid, struct _msg_info *__info);
extern int MsgInfo_r(int __rcvid, struct _msg_info *__info);
extern int MsgKeyData(int __rcvid, int __oper, _Uint32t __key, _Uint32t *__newkey, const struct iovec *__iov, int __parts);
extern int MsgKeyData_r(int __rcvid, int __oper, _Uint32t __key, _Uint32t *__newkey, const struct iovec *__iov, int __parts);
extern int MsgError(int __rcvid, int __err);
extern int MsgError_r(int __rcvid, int __err);
extern int MsgCurrent(int __rcvid);
extern int MsgCurrent_r(int __rcvid);
extern int MsgSendAsyncGbl(int __coid, const void *__smsg, size_t __sbytes, unsigned __msg_prio);
extern int MsgSendAsync(int __coid);
extern int MsgReceiveAsyncGbl(int __chid, void *__rmsg, size_t __rbytes, struct _msg_info *__info, int __coid);
extern int MsgReceiveAsync(int __chid, const struct iovec *__iov, unsigned __parts);
extern int MsgPause(int __rcvid, unsigned __cookie);
extern int MsgPause_r(int __rcvid, unsigned __cookie);

extern int SignalKill(_Uint32t __nd, pid_t __pid, int __tid, int __signo, int __code, int __value);
extern int SignalKill_r(_Uint32t __nd, pid_t __pid, int __tid, int __signo, int __code, int __value);
extern int SignalReturn(struct _sighandler_info *__info);
extern int SignalFault(unsigned __sigcode, void *__regs, _Uintptrt __refaddr);
extern int SignalAction(pid_t __pid, void (*__sigstub)(void), int __signo, const struct sigaction *__act, struct sigaction *__oact);
extern int SignalAction_r(pid_t __pid, void (*__sigstub)(void), int __signo, const struct sigaction *__act, struct sigaction *__oact);
extern int SignalProcmask(pid_t __pid, int __tid, int __how, const sigset_t *__set, sigset_t *__oldset);
extern int SignalProcmask_r(pid_t __pid, int __tid, int __how, const sigset_t *__set, sigset_t *__oldset);
extern int SignalSuspend(const sigset_t *__set);
extern int SignalSuspend_r(const sigset_t *__set);
extern int SignalWaitinfo(const sigset_t *__set, siginfo_t *__info);
extern int SignalWaitinfo_r(const sigset_t *__set, siginfo_t *__info);

extern int ThreadCreate(pid_t __pid, void *(*__func)(void *__arg), void *__arg, const struct _thread_attr *__attr);
extern int ThreadCreate_r(pid_t __pid, void *(*__func)(void *__arg), void *__arg, const struct _thread_attr *__attr);
extern int ThreadDestroy(int __tid, int __priority, void *__status);
extern int ThreadDestroy_r(int __tid, int __priority, void *__status);
extern int ThreadDetach(int __tid);
extern int ThreadDetach_r(int __tid);
extern int ThreadJoin(int __tid, void **__status);
extern int ThreadJoin_r(int __tid, void **__status);
extern int ThreadCancel(int __tid, void (*__canstub)(void));
extern int ThreadCancel_r(int __tid, void (*__canstub)(void));
extern int ThreadCtl(int __cmd, void *__data);
extern int ThreadCtl_r(int __cmd, void *__data);
extern int ThreadCtlExt(pid_t __pid, int __tid, int __cmd, void *__data);
extern int ThreadCtlExt_r(pid_t __pid, int __tid, int __cmd, void *__data);

struct qtime_entry;
struct syspage_entry;

extern int InterruptHookTrace(const struct sigevent *(*__handler)(int), unsigned __flags);
extern int InterruptHookIdle(void (*__handler)(_Uint64t *, struct qtime_entry *), unsigned __flags);
extern int InterruptHookIdle2(void (*__handler)(unsigned, struct syspage_entry *, struct _idle_hook *), unsigned __flags);
extern int InterruptHookOverdriveEvent(const struct sigevent *__event, unsigned __flags);
extern int InterruptAttachEvent(int __intr, const struct sigevent *__event, unsigned __flags);
extern int InterruptAttachEvent_r(int __intr, const struct sigevent *__event, unsigned __flags);
extern int InterruptAttach(int __intr, const struct sigevent *(*__handler)(void *__area, int __id), const void *__area, int __size, unsigned __flags);
extern int InterruptAttach_r(int __intr, const struct sigevent *(*__handler)(void *__area, int __id), const void *__area, int __size, unsigned __flags);
extern int InterruptDetach(int __id);
extern int InterruptDetach_r(int __id);
extern int InterruptWait(int __flags, const _Uint64t *__timeout);
extern int InterruptWait_r(int __flags, const _Uint64t *__timeout);
extern int InterruptCharacteristic(int __type, int __id, unsigned *__new, unsigned *__old);
extern int InterruptCharacteristic_r(int __type, int __id, unsigned *__new, unsigned *__old);

extern int SchedGet(pid_t __pid, int __tid, struct sched_param *__param);
extern int SchedGet_r(pid_t __pid, int __tid, struct sched_param *__param);
extern unsigned int SchedGetCpuNum(void);
extern int SchedSet(pid_t __pid, int __tid, int __algorithm, const struct sched_param *__param);
extern int SchedSet_r(pid_t __pid, int __tid, int __algorithm, const struct sched_param *__param);
extern int SchedInfo(pid_t __pid, int __algorithm, struct _sched_info *__info);
extern int SchedInfo_r(pid_t __pid, int __algorithm, struct _sched_info *__info);
extern int SchedYield(void);
extern int SchedYield_r(void);
extern int SchedCtl(int __cmd, void *__data, size_t __length);
extern int SchedCtl_r(int __cmd, void *__data, size_t __length);
extern int SchedJobCreate(nto_job_t	*__job);
extern int SchedJobCreate_r(nto_job_t	*__job);
extern int SchedJobDestroy(nto_job_t	*__job);
extern int SchedJobDestroy_r(nto_job_t	*__job);
extern int SchedWaypoint(nto_job_t *__job, const _Int64t *__new, const _Int64t *__max, _Int64t *__old);
extern int SchedWaypoint_r(nto_job_t *__job, const _Int64t *__new, const _Int64t *__max, _Int64t *__old);
/* Temp definitions */
extern int SchedWaypoint2(nto_job_t *__job, const _Int64t *__new, const _Int64t *__max, _Int64t *__old);
extern int SchedWaypoint2_r(nto_job_t *__job, const _Int64t *__new, const _Int64t *__max, _Int64t *__old);

extern int TimerCreate(clockid_t __id, const struct sigevent *__notify);
extern int TimerCreate_r(clockid_t __id, const struct sigevent *__notify);
extern int TimerDestroy(timer_t __id);
extern int TimerDestroy_r(timer_t __id);
extern int TimerSettime(timer_t __id, int __flags, const struct _itimer *__itime, struct _itimer *__oitime);
extern int TimerSettime_r(timer_t __id, int __flags, const struct _itimer *__itime, struct _itimer *__oitime);
extern int TimerInfo(pid_t __pid, timer_t __id, int __flags, struct _timer_info *__info);
extern int TimerInfo_r(pid_t __pid, timer_t __id, int __flags, struct _timer_info *__info);
extern int TimerAlarm(clockid_t __id, const struct _itimer *__itime, struct _itimer *__otime);
extern int TimerAlarm_r(clockid_t __id, const struct _itimer *__itime, struct _itimer *__otime);
extern int TimerTimeout(clockid_t __id, int __flags, const struct sigevent *__notify, const _Uint64t *__ntime,
						_Uint64t *__otime);
extern int TimerTimeout_r(clockid_t __id, int __flags, const struct sigevent *__notify, const _Uint64t *__ntime,
						  _Uint64t *__otime);

extern int SyncTypeCreate(unsigned __type, sync_t *__sync, const struct _sync_attr *__attr);
extern int SyncTypeCreate_r(unsigned __type, sync_t *__sync, const struct _sync_attr *__attr);
extern int SyncDestroy(sync_t *__sync);
extern int SyncDestroy_r(sync_t *__sync);
extern int SyncCtl(int __cmd, sync_t *__sync, void *__data);
extern int SyncCtl_r(int __cmd, sync_t *__sync, void *__data);
extern int SyncMutexEvent(sync_t *__sync, struct sigevent *event);
extern int SyncMutexEvent_r(sync_t *__sync, struct sigevent *event);
extern int SyncMutexLock(sync_t *__sync);
extern int SyncMutexLock_r(sync_t *__sync);
extern int SyncMutexUnlock(sync_t *__sync);
extern int SyncMutexUnlock_r(sync_t *__sync);
extern int SyncMutexRevive(sync_t *__sync);
extern int SyncMutexRevive_r(sync_t *__sync);
extern int SyncCondvarWait(sync_t *__sync, sync_t *__mutex);
extern int SyncCondvarWait_r(sync_t *__sync, sync_t *__mutex);
extern int SyncCondvarSignal(sync_t *__sync, int __all);
extern int SyncCondvarSignal_r(sync_t *__sync, int __all);
extern int SyncSemPost(sync_t *__sync);
extern int SyncSemPost_r(sync_t *__sync);
extern int SyncSemWait(sync_t *__sync, int __tryto);
extern int SyncSemWait_r(sync_t *__sync, int __tryto);

/* process manager private kernel interface */
extern int __Ring0(void (*func)(void *), void *__arg);
extern int __Ring0_r(void (*func)(void *), void *__arg);

extern int ClockTime(clockid_t __id, const _Uint64t *_new, _Uint64t *__old);
extern int ClockTime_r(clockid_t __id, const _Uint64t *_new, _Uint64t *__old);
extern int ClockAdjust(clockid_t __id, const struct _clockadjust *_new, struct _clockadjust *__old);
extern int ClockAdjust_r(clockid_t __id, const struct _clockadjust *_new, struct _clockadjust *__old);
extern int ClockPeriod(clockid_t __id, const struct _clockperiod *_new, struct _clockperiod *__old, int __reserved);
extern int ClockPeriod_r(clockid_t __id, const struct _clockperiod *_new, struct _clockperiod *__old, int __reserved);
extern int ClockId(pid_t __pid, int __tid);
extern int ClockId_r(pid_t __pid, int __tid);

/* QNET private kernel interface */
extern int NetCred(int __coid, const struct _client_info *__info);
extern int NetVtid(int __vtid, const struct _vtid_info *__info);
extern int NetUnblock(int __vtid);
extern int NetInfoscoid(int __local_scoid, int __remote_scoid);
extern int NetSignalKill(void *sigdata, struct _cred_info *cred);

extern int TraceEvent(int __code, ...);
extern void DebugBreak(void);
extern void DebugKDBreak(void);
extern void DebugKDOutput(const char *__text, _CSTD size_t __len);

#define DebugBreak() 			__inline_DebugBreak()
#define DebugKDBreak() 			__inline_DebugKDBreak()
#define DebugKDOutput(text,len)	__inline_DebugKDOutput(text,len)

extern void InterruptEnable(void);
extern void InterruptDisable(void);
extern int  InterruptMask(int __intr, int __id);
extern int  InterruptUnmask(int __intr, int __id);
extern void InterruptLock(struct intrspin * __spin);
extern void InterruptUnlock(struct intrspin * __spin);
extern unsigned InterruptStatus(void);

#define InterruptEnable() 		__inline_InterruptEnable()
#define InterruptDisable()		__inline_InterruptDisable()
#define InterruptLock(__spin)	__inline_InterruptLock(__spin)
#define InterruptUnlock(__spin)	__inline_InterruptUnlock(__spin)
#define InterruptStatus()		__inline_InterruptStatus()

/* For backwards compatibility only, use SyncTypeCreate[_r] instead */
extern int SyncCreate(sync_t *__sync, const struct _sync_attr *__attr);
extern int SyncCreate_r(sync_t *__sync, const struct _sync_attr *__attr);


extern int PowerParameter(unsigned __id, unsigned __struct_len,
						const struct nto_power_parameter *__new,
						      struct nto_power_parameter *__old);
extern int PowerSetActive(unsigned __id);
extern int PowerGetActive(unsigned __cpu);

__END_DECLS

#include _NTO_HDR_(_packpop.h)

#endif


__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/services/system/public/sys/neutrino.h $ $Rev: 756688 $" )
