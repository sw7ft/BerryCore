/*
 * $QNXtpLicenseC:
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

/*	$NetBSD: callout.h,v 1.31 2008/04/28 20:24:10 martin Exp $	*/

/*-
 * Copyright (c) 2000, 2003, 2006, 2007, 2008 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Jason R. Thorpe of the Numerical Aerospace Simulation Facility,
 * NASA Ames Research Center, and by Andrew Doran.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */


#ifndef __CALLOUT_H_INCLUDED
#define __CALLOUT_H_INCLUDED

#include <sys/types.h>
#include <stdbool.h>

#ifndef CALLOUT_NEW
struct callout;
struct callout_circq {
	/* next element */
	union {
		struct callout		*elem;
		struct callout_circq	*list;
	} cq_next;
	/* previous element */
	union {
		struct callout		*elem;
		struct callout_circq	*list;
	} cq_prev;
};

struct callout {
	struct callout_circq c_list;		/* linkage on queue */
	void	(*c_func)(void *);		/* function to call */
	void	*c_arg;				/* function argument */
	int	c_time;				/* when callout fires */
	int	c_flags;			/* state of this entry */
};
#endif

/*
 * The callout implementation is private to kern_timeout.c yet uses
 * caller-supplied storage, as lightweight callout operations are
 * critical to system performance.
 *
 * The size of callout_t must remain constant in order to ensure ABI
 * compatibility for kernel modules: it may become smaller, but must
 * not grow.  If more space is required, rearrange the members of
 * callout_impl_t.
 */
typedef struct callout_ext {
	void	*_c_store[14];
} callout_t;

/* Internal flags. */
#define	CALLOUT_BOUND		0x0001	/* bound to a specific CPU */
#define	CALLOUT_PENDING		0x0002	/* callout is on the queue */
#define	CALLOUT_FIRED		0x0004	/* callout has fired */
#define	CALLOUT_INVOKING	0x0008	/* callout function is being invoked */
#define CALLOUT_EXT		0x0010	/* extended callout struct */
#define CALLOUT_RANGE_EARLY	0x0020
#define CALLOUT_RANGE_LATE	0x0040

/* End-user flags. */
#define	CALLOUT_MPSAFE		0x0100	/* does not need kernel_lock */
#define	CALLOUT_FLAGMASK	0xff00

enum callout_clock_type {
	_CALLOUT_CLK_DEFAULT,
	_CALLOUT_CLK_WIFI,
	_CALLOUT_CLK_CELLULAR,
	_CALLOUT_CLK_RESERVED,
	_CALLOUT_CLK_MAX,
};

#ifdef _CALLOUT_PRIVATE

/* The following funkyness is to appease gcc3's strict aliasing. */
struct callout_circq_impl {
	/* next element */
	union {
		struct callout_impl	*elem;
		struct callout_circq	*list;
	} cq_next;
	/* previous element */
	union {
		struct callout_impl	*elem;
		struct callout_circq	*list;
	} cq_prev;
};
#define	cq_next_e	cq_next.elem
#define	cq_prev_e	cq_prev.elem
#define	cq_next_l	cq_next.list
#define	cq_prev_l	cq_prev.list

struct callout_cpu;

typedef struct callout_impl {
	struct callout c_callout;
	/* What follows is the extended section (CALLOUT_EXT set) */
	int		c_range;
	uint8_t		c_type;
	uint8_t		c_type_msk;
	int16_t		c_bkt;
	union {
		uint16_t 	c_type_each[_CALLOUT_CLK_MAX];
		uint64_t	c_type_all;
	} c_type_counts;
	void		*unused[4];
} callout_impl_t;
#define	CALLOUT_MAGIC		0x11deeba1

#endif	/* _CALLOUT_PRIVATE */


#define	CALLOUT_INITIALIZER_SETFUNC(func, arg)				\
				{ {{NULL}, {NULL}}, func, arg, 0, 0 }

#define	CALLOUT_INITIALIZER	CALLOUT_INITIALIZER_SETFUNC(NULL, NULL)

#ifdef _KERNEL
struct cpu_info;

void	callout_startup(void);
void	callout_init_cpu(struct cpu_info *);
int	callout_hardclock(int);

void	callout_init_new(callout_t *, u_int);
void	callout_destroy(callout_t *);
void	callout_setfunc_new(callout_t *, void (*)(void *), void *);
void	callout_reset_new(callout_t *, int, void (*)(void *), void *,
    enum callout_clock_type, int);
void	callout_schedule_new(callout_t *, int, enum callout_clock_type, int);
bool	callout_stop_new(callout_t *);
void	callout_runnow(callout_t *, void *);
bool	callout_halt(callout_t *, void *);
bool	callout_pending(callout_t *);
bool	callout_expired(callout_t *);
bool	callout_active_new(callout_t *);
bool	callout_invoking_new(callout_t *);
void	callout_ack_new(callout_t *);
void	callout_bind(callout_t *, struct cpu_info *);

#ifdef __QNXNTO__
void	callout_init_ext(callout_t *, u_int, enum callout_clock_type);
void	callout_group(int);
#endif

#ifndef _CALLOUT_NEW
void	callout_init(struct callout *);
void	callout_reset(struct callout *, int, void (*)(void *), void *);
#ifdef __QNXNTO__
void	callout_reset_newer(struct callout *, int, void (*)(void *), void *);
void	callout_msec(struct callout *, int, void (*)(void *), void *);
#endif
void	callout_schedule(struct callout *, int);
void	callout_stop(struct callout *);
void	timer_adjust(void);

#define	callout_setfunc(c, f, a)					\
do {									\
	(c)->c_func = (f);						\
	(c)->c_arg = (a);						\
} while (/*CONSTCOND*/0)

#define	callout_pending(c)	((c)->c_flags & CALLOUT_PENDING)
#define	callout_expired(c)	((c)->c_flags & CALLOUT_FIRED)
#define	callout_active(c)	((c)->c_flags & (CALLOUT_PENDING|CALLOUT_FIRED))
#define	callout_invoking(c)	((c)->c_flags & CALLOUT_INVOKING)
#define	callout_ack(c)		((c)->c_flags &= ~CALLOUT_INVOKING)
#else
#define callout_init(c, f) callout_init_new((c), (f))
#define callout_setfunc(c, f, p) callout_setfunc_new((c), (f), (p))
#define callout_reset(c, t, f, p) callout_reset_new((c), (t), (f), (p), _CALLOUT_CLK_DEFAULT, 0)
#define callout_schedule(c, t) callout_schedule_new((c), (t), _CALLOUT_CLK_DEFAULT, 0)
#define callout_active(c) callout_active_new((c))
#define callout_stop(c) callout_stop_new((c))
#define callout_invoking(c) callout_invoking_new((c))
#define callout_ack(c) callout_ack_new((c))
#endif
#endif /* _KERNEL */

#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/socket/public/sys/callout.h $ $Rev: 676134 $" )
#endif /* !__CALLOUT_H_INCLUDED */
