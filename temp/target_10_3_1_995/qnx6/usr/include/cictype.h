/*
 * Copyright © 1996-2014 Certicom Corp. All rights reserved.
 * 
 * This software contains trade secrets, confidential information, and other
 * intellectual property of Certicom Corp. and its licensors. This software
 * cannot be used, reproduced, or distributed in whole or in part by any means
 * without the explicit prior consent of Certicom Corp. Such consent must arise
 * from a separate license agreement from Certicom or its licensees, as 
 * appropriate.
 * 
 * Certicom, Certicom AMS, ACC, Asset Control Core, Certicom Bar Code
 * Authentication Agent, Certicom ECC Core, Certicom Security Architecture,
 * Certicom Trusted Infrastructure, Certicom CodeSign, Certicom KeyInject,
 * ChipActivate, DieMax, Security Builder, Security Builder API, 
 * Security Builder API for .NET, Security Builder BSP, Security Builder Crypto,
 * Security Builder ETS, Security Builder GSE, Security Builder IPSec, Security
 * Builder MCE, Security Builder NSE, Security Builder PKI, Security Builder SSL
 * and SysActivate are trademarks or registered trademarks of Certicom Corp.
 * All other companies and products listed herein are trademarks or registered
 * trademarks of their respective holders.
 *
 * BlackBerry®, RIM®, Research In Motion® and related trademarks are owned by
 * Research In Motion Limited. Used under license.
 * 
 */
/* $Id: cictype.h 26782 2005-08-30 14:05:02Z sroberts $
 * $Source$
 * $Name$
 */
#ifndef CICTYPE_H
#define CICTYPE_H

#include "cicdef.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CIC_VERSION "$Name$"

#ifndef CIC_CALLCONV
#define CIC_CALLCONV SB_CALLCONV
#endif

#ifndef CIC_EXPORT
#define CIC_EXPORT SB_EXPORT
#endif

typedef int cic_Err;

/*
 Fixed length integer definitions. For some systems, just get the definitions
 from stdint.h.
*/

#ifdef CIC_HAVE_STDINT
#include <stdint.h>

typedef uint8_t  cic_Uint8;
typedef uint16_t cic_Uint16;
typedef uint32_t cic_Uint32;

typedef int8_t  cic_Int8;
typedef int16_t cic_Int16;
typedef int32_t cic_Int32;

#else

/*
 For systems that don't have stdint.h, try to fish it out of limits.h
*/

#ifndef _NO_LIMITS_H
#  include <limits.h>

#    if (ULONG_MAX == 4294967295U)
       typedef unsigned long cic_Uint32;
       typedef signed long cic_Int32;
#    elif (UINT_MAX == 4294967295U)
       typedef unsigned int cic_Uint32;
       typedef signed int cic_Int32;
#    else
#      error cic_Uint32 undefined
#    endif

#    if (UINT_MAX == 65535U)
       typedef unsigned int cic_Uint16;
       typedef signed int cic_Int16;
#    elif (USHRT_MAX == 65535U)
       typedef unsigned short cic_Uint16;
       typedef signed short cic_Int16;
#    else
#      error cic_Uint16 undefined
#    endif

#    if (UCHAR_MAX == 255)
       typedef unsigned char cic_Uint8;
       typedef signed char cic_Int8;
#    else
#      error cic_Uint8 undefined
#    endif

#  else

/*
 On a platform that doesn't have stdint.h or limits.h, guess
 that short is 16-bit and int is 32-bit.
*/
      typedef unsigned char  cic_Uint8;
      typedef signed   char  cic_Int8;

      typedef unsigned short cic_Uint16;
      typedef signed   short cic_Int16;

      typedef unsigned long  cic_Uint32;
      typedef signed   long  cic_Int32;
#  endif
#endif

#if !defined(size_t) || !defined(NULL)
# include <stddef.h>
# if !defined(size_t) || !defined(NULL)
#   include <stdlib.h>
# endif
#endif

/* We do NOT want whatever system definition may come in
 * (sometimes (void*)0, sometimes (0), sometimes 0, depending
 * on which header you include first, even on the same o/s).
 */
#ifdef NULL
# undef NULL
#endif

#define NULL 0

typedef cic_Uint8 cic_Bool;
#define CIC_TRUE    1
#define CIC_FALSE   0

/** A simple structure for passing a pointer and its length */
typedef struct cic_Buffer
{
    cic_Uint32  length;
    cic_Uint8   *data;
} cic_Buffer;


#ifdef __cplusplus
}
#endif


#endif

