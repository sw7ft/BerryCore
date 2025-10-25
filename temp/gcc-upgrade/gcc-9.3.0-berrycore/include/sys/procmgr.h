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
 *  sys/procmgr.h
 *

 */
#ifndef __PROCMGR_H_INCLUDED
#define __PROCMGR_H_INCLUDED

#if defined(__WATCOMC__) && !defined(_ENABLE_AUTODEPEND)
#pragma read_only_file;
#endif

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#if defined(__PID_T)
typedef __PID_T		pid_t;
#undef __PID_T
#endif

#define PROCMGR_SESSION_SETSID			0
#define PROCMGR_SESSION_TCSETSID		1
#define PROCMGR_SESSION_SETPGRP			2
#define PROCMGR_SESSION_SIGNAL_LEADER	3
#define PROCMGR_SESSION_SIGNAL_PGRP		4
#define PROCMGR_SESSION_SIGNAL_PID		5

#define PROCMGR_DAEMON_NOCHDIR			0x00000001
#define PROCMGR_DAEMON_NOCLOSE			0x00000002
#define PROCMGR_DAEMON_NODEVNULL		0x00000004
#define PROCMGR_DAEMON_KEEPUMASK		0x00000008

#define PROCMGR_EVENT_SYNC				0x00000001	/* sync() was called */
#define PROCMGR_EVENT_PATHSPACE			0x00000002  /* pathname space changed */
#define PROCMGR_EVENT_TOD				0x00000004  /* time-of-day changed */
#define PROCMGR_EVENT_SYSCONF			0x00010000	/* a sysconf() was changed */
#define PROCMGR_EVENT_CONFSTR			0x00020000  /* a confstr() was changed */
#define PROCMGR_EVENT_DAEMON_DEATH		0x00040000  /* a process in session 1 terminated */
#define PROCMGR_EVENT_CONTIG_ALLOC_FAIL	0x00080000  /* a contiguous allocation request failed */
#define PROCMGR_EVENT_PRIVILEGED		0xffff0000

#define PROCMGR_VALUE_FREE_MEM			0x00000000u /* 0 == total, 1 == resident */
#define PROCMGR_VALUE_PRIVATE_MEM		0x00000001u /* sub_id == pid */
#define PROCMGR_VALUE_TRIGGER_UP		0x40000000u
#define PROCMGR_VALUE_TRIGGER_DOWN		0x80000000u

__BEGIN_DECLS

extern pid_t procmgr_guardian(pid_t __pid);
extern int procmgr_session(_Uint32t __nd, pid_t __sid, int __id, unsigned __event);
extern int procmgr_daemon(int __status, unsigned __flags);
struct sigevent;
extern int procmgr_event_notify(unsigned __flags, const struct sigevent *__event);
extern int procmgr_event_notify_add(unsigned flags, const struct sigevent *event);
extern int procmgr_event_notify_delete(int __id);
extern int procmgr_event_trigger(unsigned __flags);
extern int procmgr_event_trigger_updateable(unsigned __flags, int __value);

extern int procmgr_value_notify_add(unsigned __type, int __sub_id, _Uint64t __value, const struct sigevent *__event);
extern _Uint64t procmgr_value_current(int __id);


/* Ability definitions */
#define	PROCMGR_AID_SPAWN_SETUID		0u		/* SR: uid */
#define	PROCMGR_AID_SPAWN_SETGID		1u		/* SR: gid */
#define	PROCMGR_AID_SETUID				2u		/* SR: uid */
#define	PROCMGR_AID_SETGID				3u		/* SR: gid */
#define	PROCMGR_AID_GETID				4u		/* SR: none */
#define PROCMGR_AID_PATHSPACE			5u		/* SR: none */
#define PROCMGR_AID_REBOOT				6u		/* SR: none */
#define PROCMGR_AID_CPUMODE				7u		/* SR: mode */
#define PROCMGR_AID_RUNSTATE			8u		/* SR: cpu */
#define PROCMGR_AID_CONFSET				9u		/* SR: name */
#define PROCMGR_AID_RSRCDBMGR			10u		/* SR: none */
#define PROCMGR_AID_SESSION				11u		/* SR: sid */
#define PROCMGR_AID_UMASK				12u		/* SR: none */
#define PROCMGR_AID_EVENT				13u		/* SR: trigger bits */
#define PROCMGR_AID_RLIMIT				14u		/* SR: limit */
#define PROCMGR_AID_MEM_ADD				15u		/* SR: paddr */
#define PROCMGR_AID_MEM_PHYS			16u		/* SR: paddr */
#define PROCMGR_AID_MEM_SPECIAL			17u		/* SR: none */
#define PROCMGR_AID_MEM_GLOBAL			18u		/* SR: none */
#define PROCMGR_AID_MEM_PEER			19u		/* SR: pid */
#define PROCMGR_AID_MEM_LOCK			20u		/* SR: vaddr */
#define PROCMGR_AID_SPAWN				21u		/* SR: none */
#define PROCMGR_AID_FORK				22u		/* SR: none */
#define PROCMGR_AID_PROT_EXEC			23u		/* SR: vaddr */
#define PROCMGR_AID_WAIT				24u		/* SR: pid */
#define PROCMGR_AID_V86					25u		/* SR: none */
#define PROCMGR_AID_QNET				26u		/* SR: none */
#define PROCMGR_AID_CLOCKSET			27u		/* SR: time */
#define PROCMGR_AID_CLOCKPERIOD			28u		/* SR: period */
#define PROCMGR_AID_INTERRUPT			29u		/* SR: interrupt */
#define PROCMGR_AID_KEYDATA				30u		/* SR: none */
#define PROCMGR_AID_IO					31u		/* SR: none */
#define PROCMGR_AID_TRACE				32u		/* SR: none */
#define PROCMGR_AID_PRIORITY			33u		/* SR: priority */
#define PROCMGR_AID_CONNECTION			34u		/* SR: none */
#define PROCMGR_AID_SCHEDULE			35u		/* SR: none */
#define PROCMGR_AID_SIGNAL				36u		/* SR: signal */
#define PROCMGR_AID_TIMER				37u		/* SR: timerid */
#define PROCMGR_AID_PGRP				38u		/* SR: pgid */
#define PROCMGR_AID_MAP_FIXED			39u		/* SR: vaddr */
#define PROCMGR_AID_PATH_TRUST			40u		/* SR: none */
#define PROCMGR_AID_SWAP				41u		/* SR: none */
#define PROCMGR_AID_RCONSTRAINT			42u		/* SR: none */
#define PROCMGR_AID_CHILD_NEWAPP		43u		/* SR: none */
#define PROCMGR_AID_PUBLIC_CHANNEL		44u		/* SR: none */
#define PROCMGR_AID_APS_ROOT			45u		/* SR: none */
#define PROCMGR_AID_ABLE_CREATE			46u		/* SR: none */
#define PROCMGR_AID_RUNSTATE_BURST		47u		/* SR: length */
#define PROCMGR_AID_DEFAULT_TIMER_TOLERANCE		48u		/* SR: none */
#define PROCMGR_AID_XTHREAD_THREADCTL	49u		/* SR: subcommand */
#define PROCMGR_AID_XPROCESS_QUERY		50u		/* SR: pid */
#define PROCMGR_AID_CHROOT				51u		/* SR: none */
#define PROCMGR_AID_POWER				52u		/* SR: none */
#define PROCMGR_AID_MASK				0xffffu
#define PROCMGR_AID_EOL					PROCMGR_AID_MASK

#define PROCMGR_AOP_DENY				0x00010000u
#define PROCMGR_AOP_ALLOW				0x00020000u
#define PROCMGR_AOP_SUBRANGE			0x00040000u
#define PROCMGR_AOP_LOCK				0x00080000u
#define PROCMGR_AOP_INHERIT_YES			0x00400000u
#define PROCMGR_AOP_INHERIT_NO			0x00800000u

#define PROCMGR_ADN_ROOT				0x10000000u
#define PROCMGR_ADN_NONROOT				0x20000000u

#define __PROCMGR_AIN_SKIPSR			0x80000000u
#define __PROCMGR_AIN_NOSR				0x40000000u

extern int procmgr_ability(pid_t __pid, unsigned __ability, ...);
extern int procmgr_ability_lookup(const char * name);
extern int procmgr_ability_create(const char * name, unsigned flags);

extern int procmgr_timer_tolerance( const pid_t pid, const _Uint64t *__ntime, _Uint64t *__otime);

__END_DECLS

#endif


__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/services/system/public/sys/procmgr.h $ $Rev: 717286 $" )
