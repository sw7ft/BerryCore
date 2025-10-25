/*
 * $QNXLicenseC: $
 */


/*
 * Copyright (C) 2008 The Android Open Source Project
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
#ifndef _SYS_INOTIFY_H_
#define _SYS_INOTIFY_H_

#include <sys/cdefs.h>
#include <sys/types.h>
#include <stdint.h>

__BEGIN_DECLS


extern int inotify_init(void);
extern int inotify_add_watch(int fd, const char * path, uint32_t mask);
extern int inotify_rm_watch(int fd, int32_t wd);


struct inotify_event {
	_Int32t   wd;
	_Uint32t  mask;
	_Uint32t  cookie;
	_Uint32t  len;
	char name[0];
};


#define IN_ACCESS           0x00000001
#define IN_MODIFY           0x00000002
#define IN_ATTRIB           0x00000004
#define IN_CLOSE_WRITE      0x00000008
#define IN_CLOSE_NOWRITE    0x00000010
#define IN_OPEN             0x00000020
#define IN_MOVED_FROM       0x00000040
#define IN_MOVED_TO         0x00000080
#define IN_CREATE           0x00000100
#define IN_DELETE           0x00000200
#define IN_DELETE_SELF      0x00000400
#define IN_MOVE_SELF        0x00000800

#define IN_UNMOUNT          0x00002000
#define IN_Q_OVERFLOW       0x00004000
#define IN_IGNORED          0x00008000

#define IN_CLOSE            (IN_CLOSE_WRITE | IN_CLOSE_NOWRITE)  
#define IN_MOVE             (IN_MOVED_FROM | IN_MOVED_TO)  

#define IN_ONLYDIR          0x01000000
#define IN_DONT_FOLLOW      0x02000000
#define IN_EXCL_UNLINK      0x04000000
#define IN_MASK_ADD         0x20000000
#define IN_ISDIR            0x40000000
#define IN_ONESHOT          0x80000000  

#define IN_ALL_EVENTS (IN_ACCESS | IN_MODIFY | IN_ATTRIB | IN_CLOSE_WRITE | IN_CLOSE_NOWRITE | IN_OPEN | IN_MOVED_FROM | IN_MOVED_TO | IN_DELETE | IN_CREATE | IN_DELETE_SELF | IN_MOVE_SELF)


__END_DECLS

#endif /* #ifndef _SYS_INOTIFY_H_ */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL$ $REV$")
#endif
