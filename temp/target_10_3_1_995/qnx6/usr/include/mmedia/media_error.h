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

#ifndef __MEDIAERROR_DEFS_H__
#define __MEDIAERROR_DEFS_H__

#include <errno.h>

typedef enum
{
  /* audio card specific error mapping                                                                         */
  MM_EAINCV  = -500000, /* audio error: driver version incompatible with the library that the application uses */
  MM_EAINVAL = -EINVAL, /* audio error: driver invalid mode                                                    */
  MM_EAACCES = -EACCES, /* audio error: driver search permission is denied on a component of the path prefix   */
  MM_EAINTR  = -EINTR,  /* audio error: open operation was interrupted by a signal                             */
  MM_EAMFILE = -EMFILE, /* audio error: too many file descriptors are currently in use by this process         */
  MM_EANFILE = -ENFILE, /* audio error: too many files are currently open in the system                        */
  MM_EANOENT = -ENOENT, /* audio error: the named device doesn't exist                                         */
  MM_EANOMEM = -ENOMEM, /* audio error: no memory available for data structures                                */
  /* system error mapping                                                               */
  MM_EOK     = EOK,         /* No error                                                 */
  MM_EPERM   = EPERM,       /* Not owner                                                */
  MM_ENOENT  = ENOENT,      /* No such file or directory                                */
  MM_ESRCH   = ESRCH,       /* No such process                                          */
  MM_EINTR   = EINTR,       /* Interrupted system call                                  */
  MM_EIO     = EIO,         /* I/O error                                                */
  MM_ENOSYS  = ENOSYS,      /* The read() function isn't implemented for the filesystem */
  MM_EOVERFLOW = EOVERFLOW, /* attempt to read at or beyond EOF                         */
  MM_ENXIO   = ENXIO,       /* No such device or address                                */
  MM_EAGAIN  = EAGAIN,      /* Resource unavailable, try again                          */
  MM_ENOMEM  = ENOMEM,      /* Not enough space                                         */
  MM_ECHRNG  = ECHRNG,      /* Channel number out of range                              */
  MM_ELNRNG  = ELNRNG,      /* Link number out of range                                 */
  MM_ENOTSUP = ENOTSUP,     /* stream format not supported                              */
  MM_EBADF   = EBADF,       /* Bad file number                                          */
  MM_EFAULT  = EFAULT,      /* Bad address                                              */
  MM_ENOTBLK = ENOTBLK,     /* Block device required                                    */
  MM_EBUSY   = EBUSY,       /* Device or resource busy                                  */
  MM_EEXIST  = EEXIST,      /* File exists                                              */
  MM_ENODEV  = ENODEV,      /* No such device                                           */
  MM_ENOTDIR = ENOTDIR,     /* Not a directory                                          */
  MM_EISDIR  = EISDIR,      /* Is a directory                                           */
  MM_EINVAL  = EINVAL,      /* Invalid argument                                         */
  MM_EMFILE  = EMFILE,      /* Too many open files                                      */
  MM_ENOTTY  = ENOTTY,      /* Inappropriate I/O control operation                      */
  MM_EFBIG   = EFBIG,       /* File too large                                           */
  MM_ENOSPC  = ENOSPC,      /* No space left on device                                  */
  MM_ESPIPE  = ESPIPE,      /* Illegal seek                                             */

  /* Multimedia framework specific  error                                 */
  MM_EIND    = 4000,  /* error interface not defined                      */
  MM_ENSTA,           /* error no streamer available                      */
  MM_ENSST,           /* error no seekable stream                         */
  MM_ESNST,           /* error couldn't sniff stream                      */
  MM_EFNO,            /* error couldn't negotiate format                  */
  MM_EMBS,            /* error memory buffer size negotiation             */
  MM_EMFL,            /* error memory mapping flag negotiation            */
  MM_EMAL,            /* error multiple sub-graph memory allocator        */

  MM_EICAA,           /* error input channel already acquired             */
  MM_EICNA,           /* error input channel not acquired                 */
  MM_EICAR,           /* error input channel already released             */
  MM_EICAS,           /* error input channel already set                  */
  MM_EICNS,           /* error input channel not set                      */

  MM_EOCAA,           /* error output channel already acquired            */
  MM_EOCNA,           /* error output channel not acquired                */
  MM_EOCAR,           /* error output channel already released            */
  MM_EOCAS,           /* error output channel already set                 */
  MM_EOCNS,           /* error output channel not set                     */

  MM_ECDNV,           /* error channel direction not valid                */
  MM_EETNV,           /* error element type not valid                     */
  MM_EMIINA,          /* error MediaInput  interface not available        */
  MM_EMOINA,          /* error MediaOutput interface not available        */
  MM_EMWINA,          /* error MediaWriter interface not available        */
  MM_EMRINA,          /* error MediaReader interface not available        */
  MM_EMTPINA,         /* error MediaTrickPlay interface not available     */
  MM_EMTPIIS,         /* error MediaTrickPlay invalid initial state       */
  MM_EMLRINA,         /* error MediaListReader interface not available    */
  MM_EMLMINA,         /* error MediaListMaker interface not available     */
  MM_EMTCINA,         /* error MediaTimeConverter interface not available */
  MM_ENCPTT,          /* error couldn't convert position to time          */
  MM_ENCTTP,          /* error couldn't convert time  to position         */
  MM_ERAINA,          /* error AOResourceAccess interface not available   */
  MM_ERUNKN,          /* error unknown resource                           */
  MM_ERNSET,          /* error couldn't set resource                      */
  MM_EMSCNA,          /* error no MM_MEMORY_SOURCE channel available      */
  MM_EINTF,           /* error invalid time format                        */
  MM_ESRLAS,          /* error streamer readlist already set              */
  MM_ENDEC,           /* error unable to instatiate the decoder object    */
  MM_EEVRNG,          /* error event number out of range                  */
  MM_EEVTNP,          /* error event type not produced                    */
  MM_EFNS,            /* error filter not stopped                         */
  MM_EFIE,            /* error filter or filters in error state.          */
  MM_ETMMS,           /* error too many filters claim to be able to seek the stream */
  MM_ETMMT,           /* error too many filters claim to be able to trickplay the stream */
  MM_EIIS,            /* error invalid initial state                      */

  MM_ECIF,            /* error Create interface failed                    */
  MM_ENSF,            /* error no such filter                             */
  MM_ENFSF,           /* error no filter supports format                  */
  MM_EDRMP,           /* error DRM protected                              */
  MM_ETMFID,          /* error to many filter with the interface defined  */
  MM_EDRMNORIGHTS,    /* error DRM no rights to play the file             */
  MM_EDRMCDT,         /* error DRM corrupted data store                   */
  MM_EDRMOPL,              /* error DRM Output Level Protection mismatch , output port not specified    */
  MM_EDRMOPL_HDMI,         /* error DRM Output Level Protection mismatch on the HDMI output port        */
  MM_EDRMOPL_DISPLAYPORT,  /* error DRM Output Level Protection mismatch on the DISPLAYPORT output port */
  MM_EDRMOPL_DVI,          /* error DRM Output Level Protection mismatch on the DVI         output port */
  MM_EDRMOPL_ANALOG_VIDEO, /* error DRM Output Level Protection mismatch on any video ANALOG output port (ex: S-VIDEO,COMPOSITE,RGB,RGBHW,YPbPr..) */
  MM_EDRMOPL_ANALOG_AUDIO, /* error DRM Output Level Protection mismatch on any audio ANALOG output port (ex: HEADPHONE, SPEAKER OUT..) */
  MM_EDRMOPL_TOSLINK,      /* error DRM Output Level Protection mismatch on the TOSLINK output port     */
  MM_EDRMOPL_SPDIF,        /* error DRM Output Level Protection mismatch on the S-PDIF output port      */
  MM_EDRMOPL_BLUETOOTH,    /* error DRM Output Level Protection mismatch on the BLUETOOTH output port   */
  MM_EDRMOPL_WIRELESSHD,   /* error DRM Output Level Protection mismatch on the WIRELESSHD output port  */
  MM_EDRMOPL_WIFI_DIRECT,  /* error DRM Output Level Protection mismatch on the WI-FI Direct output port (Wireless display products such as Miracast,WiDi,..etc) */
  MM_EDRMOPL_LAST = MM_EDRMOPL_WIRELESSHD +4,
  MM_EDRMEL,               /* error DRM license was found but has expired, either by depleting the play count or via an end time. */
  MM_EIGNORED,             /* Seek unsupported, but it's safe to restart after stop                     */
  MM_EREVOCABLE,           /* Some filters didn't set MM_MEMORY_REVOCABLE but the allocator did         */
  MM_EREVOKED,             /* Buffer memory revoked                                                     */
} MmErr_t;

#endif

/* __SRCVERSION("media_error.h $Rev: 728206 $"); */

#include <sys/srcversion.h>
__SRCVERSION( "$URL$ $Rev: 728206 $" )
