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
#if defined(__QNXNTO__)
	#define QNX_ERRNO( val, name )	name
#else
	#define QNX_ERRNO( val, name )	val
#endif

#define QNX_EOK              QNX_ERRNO(  0, EOK )               /* No error                                 */
#define QNX_EPERM            QNX_ERRNO(  1, EPERM )             /* Not owner                                */
#define QNX_ENOENT           QNX_ERRNO(  2, ENOENT )            /* No such file or directory                */
#define QNX_ESRCH            QNX_ERRNO(  3, ESRCH )             /* No such process                          */
#define QNX_EINTR            QNX_ERRNO(  4, EINTR )             /* Interrupted system call                  */
#define QNX_EIO              QNX_ERRNO(  5, EIO )               /* I/O error                                */
#define QNX_ENXIO            QNX_ERRNO(  6, ENXIO )             /* No such device or address                */
#define QNX_E2BIG            QNX_ERRNO(  7, E2BIG )             /* Arg list too big                         */
#define QNX_ENOEXEC          QNX_ERRNO(  8, ENOEXEC )           /* Exec format error                        */
#define QNX_EBADF            QNX_ERRNO(  9, EBADF )             /* Bad file number                          */
#define QNX_ECHILD           QNX_ERRNO( 10, ECHILD )            /* No child processes                       */
#define QNX_EAGAIN           QNX_ERRNO( 11, EAGAIN )            /* Resource unavailable, try again          */
#define QNX_ENOMEM           QNX_ERRNO( 12, ENOMEM )            /* Not enough space                         */
#define QNX_EACCES           QNX_ERRNO( 13, EACCES )            /* Permission denied                        */
#define QNX_EFAULT           QNX_ERRNO( 14, EFAULT )            /* Bad address                              */
#define QNX_ENOTBLK          QNX_ERRNO( 15, ENOTBLK )           /* Block device required                    */
#define QNX_EBUSY            QNX_ERRNO( 16, EBUSY )             /* Device or resource busy                  */
#define QNX_EEXIST           QNX_ERRNO( 17, EEXIST )            /* File exists                              */
#define QNX_EXDEV            QNX_ERRNO( 18, EXDEV )             /* Cross-device link                        */
#define QNX_ENODEV           QNX_ERRNO( 19, ENODEV )            /* No such device                           */
#define QNX_ENOTDIR          QNX_ERRNO( 20, ENOTDIR )           /* Not a directory                          */
#define QNX_EISDIR           QNX_ERRNO( 21, EISDIR )            /* Is a directory                           */
#define QNX_EINVAL           QNX_ERRNO( 22, EINVAL )            /* Invalid argument                         */
#define QNX_ENFILE           QNX_ERRNO( 23, ENFILE )            /* File table overflow                      */
#define QNX_EMFILE           QNX_ERRNO( 24, EMFILE )            /* Too many open files                      */
#define QNX_ENOTTY           QNX_ERRNO( 25, ENOTTY )            /* Not a character device                   */
#define QNX_ETXTBSY          QNX_ERRNO( 26, ETXTBSY )           /* Text file busy                           */
#define QNX_EFBIG            QNX_ERRNO( 27, EFBIG )             /* File too large                           */
#define QNX_ENOSPC           QNX_ERRNO( 28, ENOSPC )            /* No space left on device                  */
#define QNX_ESPIPE           QNX_ERRNO( 29, ESPIPE )            /* Illegal seek                             */
#define QNX_EROFS            QNX_ERRNO( 30, EROFS )             /* Read-only file system                    */
#define QNX_EMLINK           QNX_ERRNO( 31, EMLINK )            /* Too many links                           */
#define QNX_EPIPE            QNX_ERRNO( 32, EPIPE )             /* Broken pipe                              */
#define QNX_EDOM             QNX_ERRNO( 33, EDOM )              /* Math argument out of domain of function  */
#define QNX_ERANGE           QNX_ERRNO( 34, ERANGE )            /* Result too large                         */
#define QNX_ENOMSG           QNX_ERRNO( 35, ENOMSG )            /* No message of desired type               */
#define QNX_EIDRM            QNX_ERRNO( 36, EIDRM )             /* Identifier removed                       */
#define QNX_ECHRNG           QNX_ERRNO( 37, ECHRNG )            /* Channel number out of range              */
#define QNX_EL2NSYNC         QNX_ERRNO( 38, EL2NSYNC )          /* Level 2 not synchronized                 */
#define QNX_EL3HLT           QNX_ERRNO( 39, EL3HLT )            /* Level 3 halted                           */
#define QNX_EL3RST           QNX_ERRNO( 40, EL3RST )            /* Level 3 reset                            */
#define QNX_ELNRNG           QNX_ERRNO( 41, ELNRNG )            /* Link number out of range                 */
#define QNX_EUNATCH          QNX_ERRNO( 42, EUNATCH )           /* Protocol driver not attached             */
#define QNX_ENOCSI           QNX_ERRNO( 43, ENOCSI )            /* No CSI structure available               */
#define QNX_EL2HLT           QNX_ERRNO( 44, EL2HLT )            /* Level 2 halted                           */
#define QNX_EDEADLK          QNX_ERRNO( 45, EDEADLK )           /* Deadlock avoided                         */
#define QNX_ENOLCK           QNX_ERRNO( 46, ENOLCK )            /* No locks available in system             */

#define QNX_ENOTSUP          QNX_ERRNO( 77, ENOTSUP )           /* Not supported (1003.4)                   */
#define QNX_ENAMETOOLONG     QNX_ERRNO( 78, ENAMETOOLONG )      /* Name too long                            */

/* --- Shared library errors --- */

#define QNX_ELIBACC          QNX_ERRNO( 83, ELIBACC )           /* Can't access shared library              */
#define QNX_ELIBBAD          QNX_ERRNO( 84, ELIBBAD )           /* Accessing a corrupted shared library     */
#define QNX_ELIBSCN          QNX_ERRNO( 85, ELIBSCN )           /* .lib section in a.out corrupted          */
#define QNX_ELIBMAX          QNX_ERRNO( 86, ELIBMAX )           /* Attempting to link in too many libraries */
#define QNX_ELIBEXEC         QNX_ERRNO( 87, ELIBEXEC )          /* Attempting to exec a shared library      */

/* ----------------------------- */

#define QNX_ENOSYS           QNX_ERRNO( 89, ENOSYS )            /* Unknown system call                      */
#define QNX_ELOOP            QNX_ERRNO( 90, ELOOP )             /* Too many symbolic link or prefix loops   */
#define QNX_ERESTART         QNX_ERRNO( 91, ERESTART )          /* Restartable system call                  */
#define QNX_ENOTEMPTY        QNX_ERRNO( 93, ENOTEMPTY )         /* Directory not empty                      */

#define QNX_EOPNOTSUPP       QNX_ERRNO( 103, EOPNOTSUPP )       /* Operation not supported                  */

#define QNX_ESTALE           QNX_ERRNO( 122, ESTALE )           /* Potentially recoverable i/o error        */

/* --- Sockets --- */

/* non-blocking and interrupt i/o */
/*        QNX_EAGAIN           35        */    /* Resource temporarily unavailable */
/*        QNX_EWOULDBLOCK      35        */    /* Operation would block */
#define QNX_EWOULDBLOCK    QNX_EAGAIN              /* Operation would block */
#define QNX_EINPROGRESS      QNX_ERRNO( 236, EINPROGRESS )      /* Operation now in progress */
/*        QNX_EALREADY         37        */    /* Operation already in progress */
#define QNX_EALREADY        QNX_EBUSY              /* Operation already in progress */

/* ipc/network software -- argument errors */
#define QNX_ENOTSOCK         QNX_ERRNO( 238, ENOTSOCK )         /* Socket operation on non-socket */
#define QNX_EDESTADDRREQ     QNX_ERRNO( 239, EDESTADDRREQ )     /* Destination address required */
#define QNX_EMSGSIZE         QNX_ERRNO( 240, EMSGSIZE )         /* Message too long */
#define QNX_EPROTOTYPE       QNX_ERRNO( 241, EPROTOTYPE )       /* Protocol wrong type for socket */
#define QNX_ENOPROTOOPT      QNX_ERRNO( 242, ENOPROTOOPT )      /* Protocol not available */
#define QNX_EPROTONOSUPPORT  QNX_ERRNO( 243, EPROTONOSUPPORT )  /* Protocol not supported */
#define QNX_ESOCKTNOSUPPORT  QNX_ERRNO( 244, ESOCKTNOSUPPORT )  /* Socket type not supported */
#define QNX_EPFNOSUPPORT     QNX_ERRNO( 246, EPFNOSUPPORT )     /* Protocol family not supported */
#define QNX_EAFNOSUPPORT     QNX_ERRNO( 247, EAFNOSUPPORT )     /* Address family not supported by protocol family */
#define QNX_EADDRINUSE       QNX_ERRNO( 248, EADDRINUSE )       /* Address already in use */
#define QNX_EADDRNOTAVAIL    QNX_ERRNO( 249, EADDRNOTAVAIL )    /* Can't assign requested address */

/* ipc/network software -- operational errors */
#define QNX_ENETDOWN         QNX_ERRNO( 250, ENETDOWN )         /* Network is down */
#define QNX_ENETUNREACH      QNX_ERRNO( 251, ENETUNREACH )      /* Network is unreachable */
#define QNX_ENETRESET        QNX_ERRNO( 252, ENETRESET )        /* Network dropped connection on reset */
#define QNX_ECONNABORTED     QNX_ERRNO( 253, ECONNABORTED )     /* Software caused connection abort */
#define QNX_ECONNRESET       QNX_ERRNO( 254, ECONNRESET )       /* Connection reset by peer */
#define QNX_ENOBUFS          QNX_ERRNO( 255, ENOBUFS )          /* No buffer space available */
#define QNX_EISCONN          QNX_ERRNO( 256, EISCONN )          /* Socket is already connected */
#define QNX_ENOTCONN         QNX_ERRNO( 257, ENOTCONN )         /* Socket is not connected */
#define QNX_ESHUTDOWN        QNX_ERRNO( 258, ESHUTDOWN )        /* Can't send after socket shutdown */
#define QNX_ETOOMANYREFS     QNX_ERRNO( 259, ETOOMANYREFS )     /* Too many references: can't splice */
#define QNX_ETIMEDOUT        QNX_ERRNO( 260, ETIMEDOUT )        /* Connection timed out */
#define QNX_ECONNREFUSED     QNX_ERRNO( 261, ECONNREFUSED )     /* Connection refused */

/*      QNX_ELOOP          62        */        /* Too many levels of symbolic links */
/*      QNX_ENAMETOOLONG   63        */        /* File name too long */

#define QNX_EHOSTDOWN        QNX_ERRNO( 264, EHOSTDOWN )        /* Host is down */
#define QNX_EHOSTUNREACH     QNX_ERRNO( 265, EHOSTUNREACH )     /* No route to host */

/* Network File System */
/*      QNX_ESTALE           70     */          /* Stale NFS file handle */
#define QNX_EREMOTE          QNX_ERRNO( 271, EREMOTE )          /* Too many levels of remote in path */
#define QNX_EBADRPC          QNX_ERRNO( 272, EBADRPC )          /* RPC struct is bad */
#define QNX_ERPCMISMATCH     QNX_ERRNO( 273, ERPCMISMATCH )     /* RPC version wrong */
#define QNX_EPROGUNAVAIL     QNX_ERRNO( 274, EPROGUNAVAIL )     /* RPC prog. not avail */
#define QNX_EPROGMISMATCH    QNX_ERRNO( 275, EPROGMISMATCH )    /* Program version wrong */
#define QNX_EPROCUNAVAIL     QNX_ERRNO( 276, EPROCUNAVAIL )     /* Bad procedure for program */


/* --- QNX 4.0 specific --- */

#define QNX_ENOREMOTE        QNX_ERRNO( 1000, ENOREMOTE )       /* Must be done on local machine           */
#define QNX_ENONDP           QNX_ERRNO( 1001, ENONDP )          /* Need an NDP (8087...) to run            */
#define QNX_EBADFSYS         QNX_ERRNO( 1002, EBADFSYS )        /* Corrupted file system detected          */
#define QNX_ENO32BIT         QNX_ERRNO( 1003, ENO32BIT )        /* 32-bit integer fields were used         */
#define QNX_ENOVPE           QNX_ERRNO( 1004, ENOVPE )          /* No proc entry avail for virtual process */
#define QNX_ENONETQ          QNX_ERRNO( 1005, ENONETQ )         /* Process manager-to-net enqueuing failed */
#define QNX_ENONETMAN        QNX_ERRNO( 1006, ENONETMAN )       /* Could not find net manager for node no. */
#define QNX_EVIDBUF2SML      QNX_ERRNO( 1007, EVIDBUF2SML )     /* Told to allocate a vid buf too small    */
#define QNX_EVIDBUF2BIG      QNX_ERRNO( 1008, EVIDBUF2BIG )     /* Told to allocate a vid buf too big      */
#define QNX_EMORE            QNX_ERRNO( 1009, EMORE )           /* More to do, send message again          */
#define QNX_ECTRLTERM        QNX_ERRNO( 1010, ECTRLTERM )       /* Remap to the controlling terminal       */
#define QNX_ENOLIC           QNX_ERRNO( 1011, ENOLIC )          /* No license                              */
#define QNX_EDSTFAULT        QNX_ERRNO( 1012, EDSTFAULT )       /* Destination fault on msg pass           */


#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/ph/public/qnx_errno.h $ $Rev: 224590 $" )
#endif
