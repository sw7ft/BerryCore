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
/* $Id: sbmem.h 44191 2012-05-30 17:19:20Z thowie $
 * $Source$
 * $Name$
 */
#ifndef _SBMEM_H
#define _SBMEM_H

/** @file */

#ifdef __cplusplus
extern "C" {
#endif

#include "sbdef.h"

typedef unsigned long sb_memHandle;  /**< Deprecated. **/

#define SB_NULL_HANDLE 0            /**< NULL memory handle. **/


/** @addtogroup hu_callback_api Callback APIs
 *
 * @{
 */

/** Callback interface for allocating memory.

The <tt>cbData</tt> argument must be a global context so that this 
function can call the user-provided callback that was registered during
global context creation.
 
@param[in] size    Number of bytes to allocate.
@param[in] cbData  Global context.

@retval Pointer to allocated memory, or <tt>NULL</tt> if insufficient
        memory is available.
*/

extern
SB_EXPORT
void *
SB_CALLCONV
sb_malloc(
    size_t size,
    void *cbData
);


/** Callback interface for freeing memory.

The <tt>cbData</tt> argument must be a global context so that this 
function can call the user-provided callback that was registered during
global context creation.

@param[in] ptr     Pointer to allocated memory.
@param[in] cbData  Global context.
*/

extern
SB_EXPORT
void
SB_CALLCONV
sb_free(
    void *ptr,
    void *cbData
);


/** Callback interface for copying memory.

The <tt>dst</tt> and <tt>src</tt> buffers may overlap.

The <tt>cbData</tt> argument must be a global context so that this 
function can call the user-provided callback that was registered during
global context creation.
 
@param[out] dst     Pointer to destination memory location.
@param[in]  src     Pointer to source memory location.
@param[in]  len     Number of bytes to copy.
@param[in]  cbData  Global context.
*/

extern
SB_EXPORT
void
SB_CALLCONV
sb_memcpy(
    void *dst,
    const void *src,
    size_t len,
    void *cbData
);


/** Callback interface for comparing memory.

The <tt>cbData</tt> argument must be a global context so that this 
function can call the user-provided callback that was registered during
global context creation.
 
@param[in] block1  Pointer to first memory location.
@param[in] block2  Pointer to second memory pointer.
@param[in] len     Number of bytes to compare.
@param[in] cbData  Global context.

@retval - Integer less than, equal to, or greater than zero if the first
        <tt>len</tt> bytes of <tt>block1</tt> is less than, equal
        to, or greater than the first <tt>len</tt> bytes of
        <tt>block2</tt>, respectively.
*/

extern
SB_EXPORT
int
SB_CALLCONV
sb_memcmp(
    const void *block1,
    const void *block2,
    size_t len,
    void *cbData
);


/** Callback interface for filling memory with a value.

The <tt>cbData</tt> argument must be a global context so that this 
function can call the user-provided callback that was registered during
global context creation.

@param[out] buf     Pointer to memory location.
@param[in]  value   Character to fill with.
@param[in]  len     Number of bytes to fill.
@param[in]  cbData  Global context.
*/

extern
SB_EXPORT
void
SB_CALLCONV
sb_memset(
    void *buf,
    int value,
    size_t len,
    void *cbData
);


/** Callback interface for getting the time in seconds since the Epoch.

The <tt>cbData</tt> argument must be a global context so that this 
function can call the user-provided callback that was registered during
global context creation.
 
@param[in] cbData  Global context.

@retval An unsigned 32-bit integer.
*/

extern
SB_EXPORT
sb_Uint32
SB_CALLCONV
sb_time(
    void *cbData
);

/** @} */

/** @deprecated Deprecated. 
*/

extern
SB_EXPORT
void *
SB_CALLCONV
sb_memHandleLock (
    sb_memHandle memHandle,
    void * cbData
);


/** @deprecated Deprecated. 
*/

extern
SB_EXPORT
sb_memHandle
SB_CALLCONV
sb_memUnlock (
    void * memPtr,
    void * cbData
);


#ifdef __cplusplus
}
#endif

#endif
