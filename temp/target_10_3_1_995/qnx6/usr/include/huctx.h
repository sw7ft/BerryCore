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
/* $Id: huctx.h 36652 2008-03-14 19:59:06Z jgallant $
 * $Source$
 * $Name$
 */
#ifndef HUCTX_H
#define HUCTX_H

/** @file */

#ifdef __cplusplus
extern "C" {
#endif

#include "sbdef.h"

/** @addtogroup hu_ctx_api Global context APIs
 *
 * @{
 */

/** Prototype of user-provided callback function for memory allocation.

If <tt>size</tt> bytes of memory is not available, this function
should return <tt>NULL</tt>.

The <tt>cbData</tt> argument is initialized during global context
creation and will be passed to this function.

@param[in]  size    The number of bytes to allocate.
@param[in]  cbData  The user-provided callback data.

@retval -   A pointer to allocated memory, or <tt>NULL</tt> if insufficient
            memory is available.
*/

typedef void *
SB_CALLCONV
hu_MallocFunc(
    size_t size,
    void *cbData
);


/** Prototype of user-provided callback function for freeing memory.

The <tt>cbData</tt> argument is initialized during global context
creation and will be passed to this function.

@param[in]  ptr     A pointer to allocated memory.
@param[in]  cbData  The user-provided callback data.
*/

typedef void
SB_CALLCONV
hu_FreeFunc(
    void *ptr,
    void *cbData
);


/** Prototype of user-provided callback function for copying the specified
number of bytes from one memory location to another.

The memory areas will not overlap.

The <tt>cbData</tt> argument is initialized during global context
creation and will be passed to this function.

@param[out] dst     A pointer to destination memory location.
@param[in]  src     A pointer to source memory location.
@param[in]  len     The number of bytes to copy.
@param[in]  cbData  The user-provided callback data.
*/

typedef void
SB_CALLCONV
hu_MemCpyFunc(
    void *dst,
    const void *src,
    size_t len,
    void *cbData
);


/** Prototype of user-provided callback function for comparing the specified
number of bytes of two memory locations.

The <tt>cbData</tt> argument is initialized during global context
creation and will be passed to this function.

@param[in]  block1  A pointer to first memory location.
@param[in]  block2  A pointer to second memory pointer.
@param[in]  len     The number of bytes to compare.
@param[in]  cbData  The user-provided callback data.

@retval -   An integer less than, equal to, or greater than zero if the first
            <tt>len</tt> bytes of <tt>block1</tt> is less than, equal to, or 
	    greater than the first <tt>len</tt> bytes of <tt>block2</tt>, 
	    respectively.
*/

typedef int
SB_CALLCONV
hu_MemCmpFunc(
    const void *block1,
    const void *block2,
    size_t len,
    void *cbData
);


/** Prototype of user-provided callback function for filling a memory
location with the specified number of bytes of a constant value.

The <tt>cbData</tt> argument is initialized during global context
creation and will be passed to this function.

@param[out] buf     A pointer to memory location.
@param[in]  value   The character to fill with.
@param[in]  len     The number of bytes to fill.
@param[in]  cbData  The user-provided callback data.
*/

typedef void
SB_CALLCONV
hu_MemSetFunc(
    void *buf,
    int value,
    size_t len,
    void *cbData
);


/** Prototype of user-provided callback function for returning the time in
seconds since the Epoch (00:00:00 UTC, January 1, 1970).

The <tt>cbData</tt> argument is initialized during global context
creation and will be passed to this function.

@param[in]  cbData  The user-provided callback data.

@retval -   An unsigned 32-bit integer.

*/

typedef sb_Uint32
SB_CALLCONV
hu_TimeFunc(
    void* cbData
);


/** Creates a global context initialized with user-provided callback
functions.

All callback functions are mandatory.

The optional <tt>cbData</tt> argument will be passed to all callback
functions.

@param[in]  sbMalloc  Memory allocation callback function.
@param[in]  sbFree    Memory free callback function.
@param[in]  sbMemcpy  Memory copy callback function.
@param[in]  sbMemcmp  Memory compare callback function.
@param[in]  sbMemset  Memory set callback function.
@param[in]  sbTime    Time callback function.
@param[in]  cbData    Callback data.
@param[out] sbCtx     The global context pointer.

@retval SB_ERR_NULL_INPUT          One or more callback functions is 
                                   <tt>NULL</tt>.
@retval SB_ERR_NULL_GLOBAL_CTX_PTR The global context pointer is <tt>NULL</tt>.
@retval SB_FAIL_ALLOC              Memory allocation failure.
@retval SB_SUCCESS                 Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_GlobalCtxCreate(
    hu_MallocFunc* sbMalloc,
    hu_FreeFunc* sbFree,
    hu_MemCpyFunc* sbMemcpy,
    hu_MemCmpFunc* sbMemcmp,
    hu_MemSetFunc* sbMemset,
    hu_TimeFunc* sbTime,
    void *cbData,
    sb_GlobalCtx *sbCtx
);


/** Creates a global context initialized with default implementations
for callback functions.

@param[out]  sbCtx  The global context pointer.

@retval SB_ERR_NULL_GLOBAL_CTX_PTR The global context pointer is <tt>NULL</tt>.
@retval SB_FAIL_ALLOC              Memory allocation failure.
@retval SB_SUCCESS                 Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_GlobalCtxCreateDefault(
    sb_GlobalCtx *sbCtx
);


/** Retrieves the callback functions and callback data from a global context.

The pointers to callback functions or callback data should be set
to <tt>NULL</tt> if they are not required.

@param[in]  sbCtx     A global context.
@param[out] sbMalloc  Pointer to memory allocation function. (Optional)
@param[out] sbFree    Pointer to memory free function. (Optional)
@param[out] sbMemcpy  Pointer to memory copy function. (Optional)
@param[out] sbMemcmp  Pointer to memory compare function. (Optional)
@param[out] sbMemset  Pointer to memory set function. (Optional)
@param[out] sbTime    Pointer to time function. (Optional)
@param[out] cbData    Callback data. (Optional)

@retval SB_ERR_NULL_GLOBAL_CTX The global context is <tt>NULL</tt>.
@retval SB_SUCCESS             Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_GlobalCtxGet(
    sb_GlobalCtx sbCtx,
    hu_MallocFunc** sbMalloc,
    hu_FreeFunc** sbFree,
    hu_MemCpyFunc** sbMemcpy,
    hu_MemCmpFunc** sbMemcmp,
    hu_MemSetFunc** sbMemset,
    hu_TimeFunc** sbTime,
    void** cbData
);


/** Create a new SB global context from an existing one.

The new context has the same callbacks as the original, but
has no crypto support.

@param[in]  sbCtx     The original SB global context.
@param[out] newSbCtx  The new SB global context.

@retval SB_ERR_NULL_GLOBAL_CTX     The <tt>sbCtx</tt> argument is <tt>NULL</tt>.
@retval SB_ERR_NULL_GLOBAL_CTX_PTR The <tt>newSbCtx</tt> argument is 
                                   <tt>NULL</tt>.
*/
extern
SB_EXPORT
int 
SB_CALLCONV
hu_GlobalCtxCreateFromOriginal(
    sb_GlobalCtx sbCtx,
    sb_GlobalCtx *newSbCtx
);

/** Copy all the crypto from one SB global context into another one. 
The destination context must be initialized prior to this call.

@param[in]     srcSbCtx   The source SB global context.
@param[in,out] destSbCtx  The destination SB global context.

@retval SB_ERR_NULL_GLOBAL_CTX  The <tt>srcSbCtx</tt> and/or 
                                <tt>destSbCtx</tt> arguments are <tt>NULL</tt>.
*/
extern
SB_EXPORT
int 
SB_CALLCONV
hu_GlobalCtxCopyCrypto(
    sb_GlobalCtx srcSbCtx,
    sb_GlobalCtx destSbCtx
);

/** Destroys a global context.

@param[in,out] sbCtx  The global context pointer.

@retval SB_ERR_NULL_GLOBAL_CTX_PTR The global context pointer is <tt>NULL</tt>.
@retval SB_ERR_NULL_GLOBAL_CTX     The global context is <tt>NULL</tt>.
@retval SB_SUCCESS                 Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_GlobalCtxDestroy(
    sb_GlobalCtx *sbCtx
);

/** @} */

#ifdef __cplusplus
}
#endif

#endif
