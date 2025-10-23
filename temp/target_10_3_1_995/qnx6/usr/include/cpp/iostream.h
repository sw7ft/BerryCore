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






// iostream.h standard header
#ifndef _IOSTREAM_H_
#define _IOSTREAM_H_
#include <istream>
_STD_BEGIN

		// OBJECTS
static ios_base::Init _Ios_init0;
extern istream cin;
extern ostream cout;
extern ostream cerr, clog;
_STD_END

 #if _HAS_NAMESPACE
using namespace std;
 #endif /* _HAS_NAMESPACE */
#ifdef __QNXNTO__
#include<sys/srcversion.h>
__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/cpp/public/cpp/iostream.h $ $Rev: 244324 $" )
#endif
#endif /* _IOSTREAM_H_ */

/*
 * Copyright (c) 1992-2003 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1296 */

