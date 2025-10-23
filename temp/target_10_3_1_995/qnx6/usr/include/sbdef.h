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
/* $Id: sbdef.h 41815 2010-12-06 16:15:04Z mimueller $
 * $Source$
 * $Name$
 */
#ifndef SBDEF_H
#define SBDEF_H


#ifdef __cplusplus
extern "C" {
#endif


/*==================== FUNCTION DECLARATION DEFINITIONS ======================*/

#ifndef SB_CALLCONV
# define SB_CALLCONV                  
#endif
#ifndef SB_CALLBACK_CALLCONV
# define SB_CALLBACK_CALLCONV         
#endif
#ifndef SB_EXPORT
# define SB_EXPORT                    
#endif



/*==================== DATA TYPE DEFINITIONS =================================*/

typedef struct _sb_GlobalCtx      *sb_GlobalCtx;
typedef struct _sb_Provider       *sb_Provider;
typedef struct _sb_Session        *sb_Session;
typedef struct _sb_Params         *sb_Params;
typedef struct _sb_Key            *sb_Key;
typedef struct _sb_PublicKey      *sb_PublicKey;
typedef struct _sb_PrivateKey     *sb_PrivateKey;
typedef struct _sb_Context        *sb_Context;
typedef struct _sb_YieldCtx       *sb_YieldCtx;
typedef struct _sb_RNGCtx         *sb_RNGCtx;
typedef struct _sb_RNGCtx         *sb_RngCtx;
typedef struct _sb_ECCalcOrderInt *sb_ECCalcOrderInt;
typedef struct _sb_ECCalcECPoint  *sb_ECCalcECPoint;


/*==================== BASIC TYPE DEFINITIONS ================================*/

/*
 * The following inclusion is used for the compilers that do not contain the
 * definition of size_t or NULL by default.
 */
#if !defined(size_t) || !defined(NULL)
#include <stddef.h>

    /*
     * If these symbols are not defined in stddef.h (e.g. Windows CE),
     * try stdlib.h
     */
#    if !defined(size_t) || !defined(NULL)
#    include <stdlib.h>
#    endif
#endif

typedef unsigned long  sb_Uint32;
typedef unsigned short  sb_Uint16;
typedef long  sb_Int32;
typedef short  sb_Int16;

/*
 * The following definition is necessary for the compilers that do not
 * allow space in the commandline specification of the macros.
 */
#ifndef SBUSHORT
#  define SBUSHORT unsigned short
#endif /* SBUSHORT */
#ifndef SBULONG
#  define SBULONG unsigned long
#endif /* SBULONG */

#ifdef __cplusplus
}
#endif

#endif


