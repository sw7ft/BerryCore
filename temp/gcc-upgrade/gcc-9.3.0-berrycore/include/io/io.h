/* Copyright 2013, QNX Software Systems. All Rights Reserved.
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
/*! \file io.h */

#ifndef _IO_H_INCLUDED
#define _IO_H_INCLUDED

#ifndef _STDARG_H_INCLUDED
#include <stdarg.h>
#endif

#ifdef _WIN32
#include <gfpr/gfpr.h>
#endif

__BEGIN_DECLS

typedef unsigned (io_read_f)(_Uintptrt data, void *buf, unsigned nbytes);
typedef int (io_unread_f)(_Uintptrt data, const void *buf, unsigned nbytes);
typedef int (io_skip_f)(_Uintptrt data, unsigned nbytes);
typedef int (io_unskip_f)(_Uintptrt data, unsigned nbytes);
typedef int (io_ctl_f)(_Uintptrt data, unsigned arg, _Uintptrt value);
typedef unsigned (io_write_f)(_Uintptrt data, const void *buf, unsigned nbytes);
typedef int (io_seek_f)(_Uintptrt data, int offset, int whence);

typedef enum {
	IO_READ = 0x01,
	IO_WRITE = 0x02,
} io_mode_t;

typedef struct _io_bstream io_bstream_t;
typedef union _io_stream io_stream_t;
typedef int (io_open_f)(io_bstream_t*, va_list);

typedef struct {
	_Uintptrt	fd;
	io_ctl_f	*ctl_f;
	io_read_f	*read_f;
	io_skip_f	*skip_f;
	io_unread_f	*unread_f;
	io_unskip_f	*unskip_f;
} io_istream_t;

typedef struct {
	_Uintptrt	fd;
	io_ctl_f	*ctl_f;
	io_write_f	*write_f;
	io_seek_f	*seek_f;
	io_read_f	*read_f;
} io_ostream_t;

typedef struct {
	_Uintptrt	fd;
	io_ctl_f	*ctl_f;
} io_cstream_t;

union _io_stream {
	io_istream_t	input;
	io_ostream_t	output;
	io_cstream_t	common;
};

typedef struct {
	void		*buf;
	unsigned	nbuf;
} io_buffer_t;

extern io_stream_t *io_open(io_open_f*, io_mode_t, ...);
extern void io_close(io_stream_t*);

extern io_open_f IO_FD;
extern io_open_f IO_MEM;

// for input streams
#define io_read(_s, _b, _n)	\
	(((io_istream_t*)(_s))->read_f(((io_istream_t*)(_s))->fd, (void*)(_b), (unsigned)(_n)))
#define io_unread(_s, _b, _n)	\
	(((io_istream_t*)(_s))->unread_f(((io_istream_t*)(_s))->fd, (const void*)(_b), (unsigned)(_n)))
#define io_skip(_s, _n)	\
	(((io_istream_t*)(_s))->skip_f(((io_istream_t*)(_s))->fd, (unsigned)(_n)))
#define io_ctl(_s, _a, _v)	\
	(((io_istream_t*)(_s))->ctl_f(((io_istream_t*)(_s))->fd, (unsigned)(_a), (_Uintptrt)(_v)))
#define io_unskip(_s, _n)	\
	(((io_istream_t*)(_s))->unskip_f(((io_istream_t*)(_s))->fd, (unsigned)(_n)))

// for output streams
#define io_octl(_s, _a, _v)	\
	(((io_ostream_t*)(_s))->ctl_f(((io_ostream_t*)(_s))->fd, (unsigned)(_a), (_Uintptrt)(_v)))
#define io_oread(_s, _b, _n)	\
	(((io_ostream_t*)(_s))->read_f(((io_ostream_t*)(_s))->fd, (void*)(_b), (unsigned)(_n)))
#define io_write(_s, _b, _n)	\
	(((io_ostream_t*)(_s))->write_f(((io_ostream_t*)(_s))->fd, (const void*)(_b), (unsigned)(_n)))
#define io_seek(_s, _b, _n)	\
	(((io_ostream_t*)(_s))->seek_f(((io_ostream_t*)(_s))->fd, (int)(_b), (int)(_n)))

__END_DECLS

/* set buffering (for buffered reading/writing); takes value of type "unsigned*"
   which points to a value that will dictate new buffer size (0 to disable
   buffering). The address will be filled with the previous buffer size */
#define	IO_CTL_SETBUF		1

/* limit number of bytes to read/write from the current location; takes value
   of type "unsigned". NOTE limit can only be set once and cannot be adjusted
   after io has begun */
#define IO_CTL_SETMAX		2

#define IO_CTL_GETBUF		3

#endif


#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/img/lib/public/io/io.h $ $Rev: 719830 $" )
#endif
