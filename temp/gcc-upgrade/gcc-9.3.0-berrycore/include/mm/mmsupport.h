/*
 * $QNXLicenseC:
 * Copyright 2009, QNX Software Systems. All Rights Reserved.
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
 * This header is used to support compilation under OSs other than Neutrino.  It is
 * not an OSAL, it simply fills in some commonly used holes. This file is somewhat
 * heavy-handed in that it includes some headers that aren't always
 * required, such as gulliver.  These are small headers though, so it shouldn't make
 * much difference.  If it is felt strongly that the headers should be broken up, it
 * could be easily done.
 */

#ifndef _H_LIB_MMSUPPORT_H_
#define _H_LIB_MMSUPPORT_H_

#if defined(__QNXNTO__)

#include <sys/platform.h>
#include <gulliver.h>
#include <sys/slog.h>
#include <sys/slogcodes.h>

#elif defined(__LINUX__)

#include <sys/cdefs.h>
#include <sys/uio.h>

typedef struct iovec iov_t;
#ifndef SETIOV
#define SETIOV(_iov, _addr, _len)	((_iov)->iov_base = (void *)(_addr), (_iov)->iov_len = (_len))
#endif
#ifndef GETIOVBASE
#define GETIOVBASE(_iov)            ((_iov)->iov_base)
#endif
#ifndef GETIOVLEN
#define GETIOVLEN(_iov)              ((_iov)->iov_len)
#endif

/* For Linux we are only little endian for now.
 */
#define ENDIAN_RET16(__x)		((((__x) >> 8) & 0xff) | \
								(((__x) & 0xff) << 8))
#define ENDIAN_RET32(__x)		((((__x) >> 24) & 0xff) | \
								(((__x) >> 8) & 0xff00) | \
								(((__x) & 0xff00) << 8) | \
								(((__x) & 0xff) << 24))
#define ENDIAN_RET64(__x)		((((__x) >> 56) & 0xff) | \
								 (((__x) >> 40) & 0xff00) | \
								 (((__x) >> 24) & 0xff0000) | \
								 (((__x) >>  8) & 0xff000000) | \
								 (((__x) & 0xff000000) <<  8) | \
								 (((__x) & 0xff0000) << 24) | \
								 (((__x) & 0xff00) << 40) | \
								 (((__x) & 0xff) << 56))
#ifndef __CPU_UNALIGNED_RET16
#define UNALIGNED_RET16(__p)	(((uint8_t volatile *)(__p))[0] | \
								(((uint8_t volatile *)(__p))[1] << 8))
#endif

#ifndef __CPU_UNALIGNED_RET32
#define UNALIGNED_RET32(__p)	(((uint8_t volatile *)(__p))[0] | \
								(((uint8_t volatile *)(__p))[1] << 8) | \
								(((uint8_t volatile *)(__p))[2] << 16) | \
								(((uint8_t volatile *)(__p))[3] << 24))
#endif

#ifndef __CPU_UNALIGNED_RET64
#define UNALIGNED_RET64(__p)	(((uint8_t volatile *)(__p))[0] | \
								(((uint8_t volatile *)(__p))[1] << 8) | \
								(((uint8_t volatile *)(__p))[2] << 16) | \
								((unsigned)(((uint8_t volatile *)(__p))[3]) << 24) | \
								(((uint64_t)((uint8_t volatile *)(__p))[4]) << 32) | \
								(((uint64_t)((uint8_t volatile *)(__p))[5]) << 40) | \
								(((uint64_t)((uint8_t volatile *)(__p))[6]) << 48) | \
								(((uint64_t)((uint8_t volatile *)(__p))[7]) << 56))
#endif
#define ENDIAN_SWAP16(__x)		(*(uint16_t *)(__x) = ENDIAN_RET16(*(uint16_t *)(__x)))
#define ENDIAN_SWAP32(__x)		(*(uint32_t *)(__x) = ENDIAN_RET32(*(uint32_t *)(__x)))
#define ENDIAN_SWAP64(__x)		(*(uint64_t *)(__x) = ENDIAN_RET64(*(uint64_t *)(__x)))
#define ENDIAN_LE16(__x)		(__x)
#define ENDIAN_LE32(__x)		(__x)
#define ENDIAN_LE64(__x)		(__x)
#define ENDIAN_BE16(__x)		ENDIAN_RET16(__x)
#define ENDIAN_BE32(__x)		ENDIAN_RET32(__x)
#define ENDIAN_BE64(__x)		ENDIAN_RET64(__x)

#define __SRCVERSION(x)
#include <syslog.h>
#define _SLOG_SHUTDOWN	LOG_ALERT
#define _SLOG_CRITICAL	LOG_CRIT
#define _SLOG_ERROR		LOG_ERR
#define _SLOG_WARNING	LOG_WARNING
#define _SLOG_NOTICE	LOG_NOTICE
#define _SLOG_INFO		LOG_INFO
#define _SLOG_DEBUG1	LOG_DEBUG
#define _SLOG_DEBUG2	LOG_DEBUG

#define _SLOG_SETCODE(ma, mi)       ((ma) | ((mi) << 20))

#define timespec2nsec(__ts) ((__ts)->tv_sec*(uint64_t)1000000000+(__ts)->tv_nsec)

#define EOK 0

#ifndef min
#define min(a,b)  (((a) < (b)) ? (a) : (b))
#endif

#define NOFD -1

/* This could eventually map to prctl(PR_SET_NAME,(y),0,0,0), but prctl needs to be called
 * from the thread to be named unlike pthread_setname_np.
 */
#define pthread_setname_np(x,y)

#endif


#endif

__SRCVERSION( "$URL$ $Rev$" )
