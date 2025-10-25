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
#ifndef _IO_STREAM_H_INCLUDED
#define _IO_STREAM_H_INCLUDED

#ifndef _IO_H_INCLUDED
#include <io/io.h>
#endif

#ifndef _STDARG_H_INCLUDED
#include <stdarg.h>
#endif

__BEGIN_DECLS

typedef void(io_close_f)(io_bstream_t *bstream);

struct _io_bstream {
	io_stream_t	stream;
	unsigned	flags;
	_uint8		*buf;
	unsigned 	bufsiz, buf_pos, buf_nleft;
	unsigned	pos, nleft;
	io_close_f	*close_f;
};

__END_DECLS

#endif


#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/img/lib/public/io/io_stream.h $ $Rev: 224588 $" )
#endif
