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





#ifndef _NET_NETBYTE_H_INCLUDED
#define _NET_NETBYTE_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#ifndef _INTTYPES_H_INCLUDED
#include <inttypes.h>
#endif

#ifndef _GULLIVER_H_INCLUDED
#include <gulliver.h>
#endif


__BEGIN_DECLS
/* libc */
uint16_t htons(uint16_t);
uint32_t htonl(uint32_t);
uint16_t ntohs(uint16_t);
uint32_t ntohl(uint32_t);

#ifdef __EXT_BSD
/* libsocket */
uint16_t htobe16(uint16_t);
uint32_t htobe32(uint32_t);
uint64_t htobe64(uint64_t);
uint16_t htole16(uint16_t);
uint32_t htole32(uint32_t);
uint64_t htole64(uint64_t);

uint16_t be16toh(uint16_t);
uint32_t be32toh(uint32_t);
uint64_t be64toh(uint64_t);
uint16_t le16toh(uint16_t);
uint32_t le32toh(uint32_t);
uint64_t le64toh(uint64_t);
#endif
__END_DECLS


#if defined(__LITTLEENDIAN__)
#define __NET_LE16(__x)	((__x))
#define __NET_LE32(__x)	((__x))
#define __NET_LE64(__x)	((__x))

#if defined(__CPU_ENDIAN_RET16)
#define __NET_BE16(__x)	__cpu_endian_ret16((__x))
#elif defined(__GNUC__) || defined(__INTEL_COMPILER)
#define __NET_BE16(__x)						\
	({ 							\
		_Uint16t __y = (__x);				\
		(((__y >> 8) & 0xff) | ((__y & 0xff) << 8));	\
	})
#endif

#if defined(__CPU_ENDIAN_RET32)
#define __NET_BE32(__x)	__cpu_endian_ret32((__x))
#elif defined(__GNUC__) || defined(__INTEL_COMPILER)
#define __NET_BE32(__x)						\
	({ 							\
		_Uint32t __y = (__x);				\
		(((__y >> 24) & 0xff) | ((__y >> 8) & 0xff00) |	\
		((__y & 0xff00) << 8) | ((__y & 0xff) << 24));	\
	})
#endif

#if defined(__CPU_ENDIAN_RET64)
#define __NET_BE64(__x)	__cpu_endian_ret64((__x))
#elif defined(__GNUC__) || defined(__INTEL_COMPILER)
#define __NET_BE64(__x)							\
	({ 								\
		_Uint64t __y = (__x);					\
		(((__y >> 56) & 0xff) | ((__y >> 40) & 0xff00) |	\
		((__y >> 24) & 0xff0000) | ((__y >>  8) & 0xff000000) |	\
		((__y & 0xff000000) <<  8) | ((__y & 0xff0000) << 24) |	\
		((__y & 0xff00) << 40) | ((__y & 0xff) << 56));		\
	})
#endif

#elif defined(__BIGENDIAN__)

#if defined(__CPU_ENDIAN_RET16)
#define __NET_LE16(__x)	__cpu_endian_ret16((__x))
#elif defined(__GNUC__) || defined(__INTEL_COMPILER)
#define __NET_LE16(__x)						\
	({ 							\
		_Uint16t __y = (__x);				\
		(((__y >> 8) & 0xff) | ((__y & 0xff) << 8));	\
	})
#endif

#if defined(__CPU_ENDIAN_RET32)
#define __NET_LE32(__x)	__cpu_endian_ret32((__x))
#elif defined(__GNUC__) || defined(__INTEL_COMPILER)
#define __NET_LE32(__x)						\
	({ 							\
		_Uint32t __y = (__x);				\
		(((__y >> 24) & 0xff) | ((__y >> 8) & 0xff00) |	\
		((__y & 0xff00) << 8) | ((__y & 0xff) << 24));	\
	})
#endif

#if defined(__CPU_ENDIAN_RET64)
#define __NET_LE64(__x)	__cpu_endian_ret64((__x))
#elif defined(__GNUC__) || defined(__INTEL_COMPILER)
#define __NET_LE64(__x)							\
	({ 								\
		_Uint64t __y = (__x);					\
		(((__y >> 56) & 0xff) | ((__y >> 40) & 0xff00) |	\
		((__y >> 24) & 0xff0000) | ((__y >>  8) & 0xff000000) |	\
		((__y & 0xff000000) <<  8) | ((__y & 0xff0000) << 24) |	\
		((__y & 0xff00) << 40) | ((__y & 0xff) << 56));		\
	})
#endif

#define __NET_BE16(__x)	((__x))
#define __NET_BE32(__x)	((__x))
#define __NET_BE64(__x)	((__x))

#else
#error ENDIAN Not defined for system
#endif


#ifdef __NET_BE16
#define htons(__x)	__NET_BE16((__x))
#define ntohs(__x)	__NET_BE16((__x))
#endif
#ifdef __NET_BE32
#define htonl(__x)	__NET_BE32((__x))
#define ntohl(__x)	__NET_BE32((__x))
#endif

#ifdef __EXT_BSD

#define HTONS(__x)	((__x) = htons((uint16_t)(__x)))
#define NTOHS(__x)	((__x) = ntohs((uint16_t)(__x)))
#define HTONL(__x)	((__x) = htonl((uint32_t)(__x)))
#define NTOHL(__x)	((__x) = ntohl((uint32_t)(__x)))


#ifdef __NET_BE16
#define htobe16(__x)	__NET_BE16((__x))
#define be16toh(__x)	__NET_BE16((__x))
#endif
#ifdef __NET_BE32
#define htobe32(__x)	__NET_BE32((__x))
#define be32toh(__x)	__NET_BE32((__x))
#endif
#ifdef __NET_BE64
#define htobe64(__x)	__NET_BE64((__x))
#define be64toh(__x)	__NET_BE64((__x))
#endif
#ifdef __NET_LE16
#define htole16(__x)	__NET_LE16((__x))
#define le16toh(__x)	__NET_LE16((__x))
#endif
#ifdef __NET_LE32
#define htole32(__x)	__NET_LE32((__x))
#define le32toh(__x)	__NET_LE32((__x))
#endif
#ifdef __NET_LE64
#define htole64(__x)	__NET_LE64((__x))
#define le64toh(__x)	__NET_LE64((__x))
#endif

#define HTOBE16(__x)	((__x) = htobe16((uint16_t)(__x)))
#define HTOBE32(__x)	((__x) = htobe32((uint32_t)(__x)))
#define HTOBE64(__x)	((__x) = htobe64((uint64_t)(__x)))
#define HTOLE16(__x)	((__x) = htole16((uint16_t)(__x)))
#define HTOLE32(__x)	((__x) = htole32((uint32_t)(__x)))
#define HTOLE64(__x)	((__x) = htole64((uint64_t)(__x)))

#define BE16TOH(__x)	((__x) = be16toh((uint16_t)(__x)))
#define BE32TOH(__x)	((__x) = be32toh((uint32_t)(__x)))
#define BE64TOH(__x)	((__x) = be64toh((uint64_t)(__x)))
#define LE16TOH(__x)	((__x) = le16toh((uint16_t)(__x)))
#define LE32TOH(__x)	((__x) = le32toh((uint32_t)(__x)))
#define LE64TOH(__x)	((__x) = le64toh((uint64_t)(__x)))

#endif /* __EXT_BSD */

#endif /* !_NET_NETBYTE_H_INCLUDED */

__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/socket/public/net/netbyte.h $ $Rev: 233581 $" )
