/*
 * $QNXLicenseC:
 * Copyright 2007, 2008 QNX Software Systems. All Rights Reserved.
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
 *  malloc.h	Memory allocation functions
 *
 */
#ifndef __RCHECK_MALLOC_H_INCLUDED
#define __RCHECK_MALLOC_H_INCLUDED

/*
     * (c) Copyright 1990, 1991 Conor P. Cahill (uunet!virtech!cpcahil).
     * You may copy, distribute, and use this software as long as this
     * copyright statement is not removed.
     */

/*
 * Malloc warning/fatal error handler defines...
 */
#define M_HANDLE_DUMP	0x80  /* 128 */
#define M_HANDLE_TRACEBACK	0x40
#define M_HANDLE_IGNORE	0
#define M_HANDLE_ABORT	1
#define M_HANDLE_EXIT	2
#define M_HANDLE_CORE	3
#define M_HANDLE_STOP	4

/*
 * mallopt() commands and defaults specific to librcheck.so
 *
 * the first four settings are ignored by the debugging mallopt, but are
 * here to maintain compatibility with the system malloc.h.
 */
#define M_KEEP		4		/* ignored by mallopt		*/

#define MALLOC_WARN           100 /* set malloc warning handling */
#define MALLOC_FATAL          101 /* set malloc fatal handling */
#define MALLOC_ERRFILE        102 /* specify malloc error file */
#define MALLOC_CKCHAIN        103 /* turn on chain checking	*/
#define MALLOC_FILLAREA       104 /* turn off area filling */
#define MALLOC_CKBOUNDS       104 /* turn on/off area filling */
#define MALLOC_LOWFRAG        105 /* use best fit allocation mech */
#define MALLOC_CKACCESS       106 /* verify string and memory access */
#define MALLOC_VERBOSE        107 /* set verbosity level */
#define MALLOC_EVENTFILE      108 /* specify programatic err/output file */
#define MALLOC_TRACEFILE      110 /* turn on and specify malloc trace file */
#define MALLOC_TRACEMIN       111 /* if trace enabled, minimum size to track */
#define MALLOC_TRACEMAX       112 /* if trace enabled, maximum size to track */
#define MALLOC_USE_DLADDR     113 /* Use dladdr(3), to get more info on the address */
#define MALLOC_CKALLOC        114 /* turn on/off checks for the argument of for realloc(3) and free(3) */
#define MALLOC_TRACEBTDEPTH   115 /* if trace enabled, the backtrace depth */
#define MALLOC_EVENTBTDEPTH   116 /* if trace enabled, the backtrace depth */
#define MALLOC_HANDLE_SIGNALS 117 /* turn on abnormal termination signals handling */
#define MALLOC_TRUNCATE 	  118 /* turn on file truncation before writing to them */
#define MALLOC_TRACING 	  	  119 /* turn on or off malloc tracing without changing output file */
#define MALLOC_DUMP_LEAKS 	  120 /* dump memory leaks */
#define MALLOC_DUMP_STATS 	  121 /* dump stats */
#define MALLOC_BACKTRACE_HOOK 122 /* install backtracing hook */
#define MALLOC_CTRL_CMD       123 /* execute contol command */
#define MALLOC_CTRL_CMD_FILE  124 /* execute contol command from file */
#define MALLOC_MARKER         125 /* insert marker */

#ifdef __cplusplus
#ifndef CHECKED_PTR_T
#define CHECKED_PTR_T

extern "C" {
void _malloc_cpp_get_ptr_info(void *p, void **bp, void **cp, void **ep);
void _malloc_cpp_check_op_star(void *bp, void *cp, void *ep);
void _malloc_cpp_check_op_arrow(void *bp, void *cp, void *ep);
void _malloc_cpp_check_op_array(void *bp, void *np, void *ep);
}

template <class T> class CheckedPtr {
protected:
    T *bp;						/* beginning pointer */
    T *cp;						/* current pointer */
    T *ep;						/* end pointer */
public:
    CheckedPtr(void) {bp = 0; cp = 0; ep = 0;}
    CheckedPtr(const CheckedPtr<T> &p) {bp = p.bp; cp = p.cp; ep = p.ep; }
    CheckedPtr(T *p);
    CheckedPtr<T> &operator=(T *p);
    CheckedPtr<T> &operator++() { cp++; return *this; }
    CheckedPtr<T> &operator--() { cp--; return *this; }
    CheckedPtr<T> operator++(int)	{ CheckedPtr<T> temp(*this); cp++; return temp; }
    CheckedPtr<T> operator--(int)	{ CheckedPtr<T> temp(*this); cp--; return temp; }
    CheckedPtr<T> &operator+=(const CheckedPtr<T> &p) { cp += p.cp; }
    CheckedPtr<T> &operator-=(const CheckedPtr<T> &p) { cp -= p.cp; }
    bool operator==(const T *p) { return(cp == p); }
    bool operator==(const CheckedPtr<T> p) { return(cp == p.cp); }
    T &operator*();
    T &operator[](int i);
    T *operator->();
    operator void*() {return cp;}
};

template<class T> CheckedPtr<T>::CheckedPtr(T *p)
{
	_malloc_cpp_get_ptr_info((void*)p, &(void*)bp, &(void*)cp, &(void*)ep);
}

template<class T> CheckedPtr<T> & CheckedPtr<T>::operator =(T *p)
{
	_malloc_cpp_get_ptr_info((void*)p, &(void*)bp, &(void*)cp, &(void*)ep);
    return *this;
}

template<class T>  T & CheckedPtr<T>::operator*()
{
	_malloc_cpp_check_op_star((void*)bp, (void*)cp, (void*)ep);
    return *cp;
}

template<class T>  T * CheckedPtr<T>::operator->()
{
	_malloc_cpp_check_op_arrow(bp, cp, ep);
    return cp;
}

template<class T>  T & CheckedPtr<T>::operator[](int i)
{
	void *np = cp+i;
	_malloc_cpp_check_op_array(bp, np, ep);
    return cp[i];
}
#endif
#endif

#ifdef __QNXNTO__
#include<sys/srcversion.h>
__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/rcheck/public/rcheck/malloc.h $ $Rev: 671218 $" )
#endif
#endif
