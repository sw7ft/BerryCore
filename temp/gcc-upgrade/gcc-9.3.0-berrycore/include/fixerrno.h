/* Copyright 2009, QNX Software Systems. All Rights Reserved.
 * 
 * You must obtain a written license from and pay applicable license fees to 
 * QNX Software Systems before you may reproduce, modify or distribute this 
 * software, or any work that includes all or part of this software.  Free 
 * development licenses are available for evaluation and non-commercial purposes.  
 * For more information visit http://licensing.qnx.com or email licensing@qnx.com.
 * 
 * This file may contain contributions from others.  Please review this entire 
 * file for other proprietary rights or license notices, as well as the QNX 
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 */
#include <errno.h>

int mapqnxerrno(int qnxerrno);

#if defined(__QNX__)
#define mapqnxerrno( qnxerrno ) (qnxerrno)
#else

#if defined(__linux__) || defined(__CYGWIN__)
#ifndef EOK
#define EOK 0
#endif
#ifndef EINVAL
#define EINVAL -1  /*What the hell system is this anyways?*/
#endif
#ifndef ENOSYS
#define ENOSYS -2
#endif
#ifndef ENOTSUP
#define ENOTSUP ENOSYS
#endif

/*- Photon uses these qnxisms; so make them unique */
#ifndef EMORE
#define EMORE -3
#endif

#ifndef ENOMSG
#define ENOMSG -4
#endif

#endif

#ifndef EPERM
#define EPERM EINVAL
#endif
#ifndef ENOENT
#define ENOENT EINVAL
#endif
#ifndef ESRCH
#define ESRCH EINVAL
#endif
#ifndef EINTR
#define EINTR EINVAL
#endif
#ifndef EIO
#define EIO EINVAL
#endif
#ifndef ENXIO
#define ENXIO EINVAL
#endif
#ifndef E2BIG
#define E2BIG EINVAL
#endif
#ifndef ENOEXEC
#define ENOEXEC EINVAL
#endif
#ifndef EBADF
#define EBADF EINVAL
#endif
#ifndef ECHILD
#define ECHILD EINVAL
#endif
#ifndef EAGAIN
#define EAGAIN EINVAL
#endif
#ifndef ENOMEM
#define ENOMEM EINVAL
#endif
#ifndef EACCES
#define EACCES EINVAL
#endif
#ifndef EFAULT
#define EFAULT EINVAL
#endif
#ifndef ENOTBLK
#define ENOTBLK EINVAL
#endif
#ifndef EBUSY
#define EBUSY EINVAL
#endif
#ifndef EEXIST
#define EEXIST EINVAL
#endif
#ifndef EXDEV
#define EXDEV EINVAL
#endif
#ifndef ENODEV
#define ENODEV EINVAL
#endif
#ifndef ENOTDIR
#define ENOTDIR EINVAL
#endif
#ifndef EISDIR
#define EISDIR EINVAL
#endif
#ifndef EINVAL
#define EINVAL EINVAL
#endif
#ifndef ENFILE
#define ENFILE EINVAL
#endif
#ifndef EMFILE
#define EMFILE EINVAL
#endif
#ifndef ENOTTY
#define ENOTTY EINVAL
#endif
#ifndef ETXTBSY
#define ETXTBSY EINVAL
#endif
#ifndef EFBIG
#define EFBIG EINVAL
#endif
#ifndef ENOSPC
#define ENOSPC EINVAL
#endif
#ifndef EOVERFLOW
#define EOVERFLOW EINVAL
#endif
#ifndef ESPIPE
#define ESPIPE EINVAL
#endif
#ifndef EROFS
#define EROFS EINVAL
#endif
#ifndef EMLINK
#define EMLINK EINVAL
#endif
#ifndef EPIPE
#define EPIPE EINVAL
#endif
#ifndef EDOM
#define EDOM EINVAL
#endif
#ifndef ERANGE
#define ERANGE EINVAL
#endif
#ifndef ENOMSG
#define ENOMSG EINVAL
#endif
#ifndef EIDRM
#define EIDRM EINVAL
#endif
#ifndef ECHRNG
#define ECHRNG EINVAL
#endif
#ifndef EL2NSYNC
#define EL2NSYNC EINVAL
#endif
#ifndef EL3HLT
#define EL3HLT EINVAL
#endif
#ifndef EL3RST
#define EL3RST EINVAL
#endif
#ifndef ELNRNG
#define ELNRNG EINVAL
#endif
#ifndef EUNATCH
#define EUNATCH EINVAL
#endif
#ifndef ENOCSI
#define ENOCSI EINVAL
#endif
#ifndef EL2HLT
#define EL2HLT EINVAL
#endif
#ifndef EDEADLK
#define EDEADLK EINVAL
#endif
#ifndef ENOLCK
#define ENOLCK EINVAL
#endif
#ifndef ENAMETOOLONG
#define ENAMETOOLONG EINVAL
#endif
#ifndef ELIBACC
#define ELIBACC EINVAL
#endif
#ifndef ELIBBAD
#define ELIBBAD EINVAL
#endif
#ifndef ELIBSCN
#define ELIBSCN EINVAL
#endif
#ifndef ELIBMAX
#define ELIBMAX EINVAL
#endif
#ifndef ELIBEXEC
#define ELIBEXEC EINVAL
#endif
#ifndef ENOSYS
#define ENOSYS EINVAL
#endif
#ifndef ELOOP
#define ELOOP EINVAL
#endif
#ifndef ERESTART
#define ERESTART EINVAL
#endif
#ifndef ENOTEMPTY
#define ENOTEMPTY EINVAL
#endif
#ifndef EOPNOTSUPP
#define EOPNOTSUPP EINVAL
#endif
#ifndef ESTALE
#define ESTALE EINVAL
#endif
#ifndef ENOTSOCK
#define ENOTSOCK EINVAL
#endif
#ifndef EDESTADDRREQ
#define EDESTADDRREQ EINVAL
#endif
#ifndef EMSGSIZE
#define EMSGSIZE EINVAL
#endif
#ifndef EPROTOTYPE
#define EPROTOTYPE EINVAL
#endif
#ifndef ENOPROTOOPT
#define ENOPROTOOPT EINVAL
#endif
#ifndef EPROTONOSUPPORT
#define EPROTONOSUPPORT EINVAL
#endif
#ifndef ESOCKTNOSUPPORT
#define ESOCKTNOSUPPORT EINVAL
#endif
#ifndef EPFNOSUPPORT
#define EPFNOSUPPORT EINVAL
#endif
#ifndef EAFNOSUPPORT
#define EAFNOSUPPORT EINVAL
#endif
#ifndef EADDRINUSE
#define EADDRINUSE EINVAL
#endif
#ifndef EADDRNOTAVAIL
#define EADDRNOTAVAIL EINVAL
#endif
#ifndef ENETDOWN
#define ENETDOWN EINVAL
#endif
#ifndef ENETUNREACH
#define ENETUNREACH EINVAL
#endif
#ifndef ENETRESET
#define ENETRESET EINVAL
#endif
#ifndef ECONNABORTED
#define ECONNABORTED EINVAL
#endif
#ifndef ECONNRESET
#define ECONNRESET EINVAL
#endif
#ifndef ENOBUFS
#define ENOBUFS EINVAL
#endif
#ifndef EISCONN
#define EISCONN EINVAL
#endif
#ifndef ENOTCONN
#define ENOTCONN EINVAL
#endif
#ifndef ESHUTDOWN
#define ESHUTDOWN EINVAL
#endif
#ifndef ETOOMANYREFS
#define ETOOMANYREFS EINVAL
#endif
#ifndef ETIMEDOUT
#define ETIMEDOUT EINVAL
#endif
#ifndef ECONNREFUSED
#define ECONNREFUSED EINVAL
#endif
#ifndef EHOSTDOWN
#define EHOSTDOWN EINVAL
#endif
#ifndef EHOSTUNREACH
#define EHOSTUNREACH EINVAL
#endif
#ifndef EREMOTE
#define EREMOTE EINVAL
#endif
#ifndef EBADRPC
#define EBADRPC EINVAL
#endif
#ifndef ERPCMISMATCH
#define ERPCMISMATCH EINVAL
#endif
#ifndef EPROGUNAVAIL
#define EPROGUNAVAIL EINVAL
#endif
#ifndef EPROGMISMATCH
#define EPROGMISMATCH EINVAL
#endif
#ifndef EPROCUNAVAIL
#define EPROCUNAVAIL EINVAL
#endif
#ifndef ENOREMOTE
#define ENOREMOTE EINVAL
#endif
#ifndef ENONDP
#define ENONDP EINVAL
#endif
#ifndef EBADFSYS
#define EBADFSYS EINVAL
#endif
#ifndef ENO32BIT
#define ENO32BIT EINVAL
#endif
#ifndef ENOVPE
#define ENOVPE EINVAL
#endif
#ifndef ENONETQ
#define ENONETQ EINVAL
#endif
#ifndef ENONETMAN
#define ENONETMAN EINVAL
#endif
#ifndef EVIDBUF2SML
#define EVIDBUF2SML EINVAL
#endif
#ifndef EVIDBUF2BIG
#define EVIDBUF2BIG EINVAL
#endif
#ifndef ECTRLTERM
#define ECTRLTERM EINVAL
#endif
#ifndef ENOLIC
#define ENOLIC EINVAL
#endif
#ifndef EDSTFAULT
#define EDSTFAULT EINVAL
#endif

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/ph/public/fixerrno.h $ $Rev: 224590 $" )
#endif
