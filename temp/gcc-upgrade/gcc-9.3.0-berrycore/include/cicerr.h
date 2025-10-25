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
/* $Id: cicerr.h 26782 2005-08-30 14:05:02Z sroberts $
 * $Source$
 * $Name$
 */
#ifndef CICERR_H
#define CICERR_H

#include "sbreturn.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
    General error codes.

    These are general error codes that exist in most products.
    All general errors are in the range (0x0000 - 0x0FFFF)
*/
#define CIC_ERR_NONE                        0x0000  /**< No error */
#define CIC_ERR_NO_PTR                      0x0001  /**< Null pointer */
#define CIC_ERR_ILLEGAL_PARAM               0x0002  /**< Illegal param */
#define CIC_ERR_SMALL_BUFFER                0x0003  /**< Buffer too small */
#define CIC_ERR_WOULD_BLOCK                 0x0004  /**< IO Blocking */
#define CIC_ERR_TIMEOUT                     0x0005  /**< Timeout */
#define CIC_ERR_BAD_LENGTH                  0x0006  /**< Bad length */
#define CIC_ERR_NOT_FOUND                   0x0007  /**< Not found */
#define CIC_ERR_BAD_CTX                     0x0008  /**< Bad context */
#define CIC_ERR_BAD_INDEX                   0x0009  /**< Bad index */
#define CIC_ERR_RANDOM                      0x000A  /**< Entropy generation */
#define CIC_ERR_MEM_UNDERRUN                0x000B  /**< Memory underrun detected by memory test harness. */
#define CIC_ERR_MEM_OVERRUN                 0x000C  /**< Memory overrun detected by memory test harness. */
#define CIC_ERR_MEM_WAS_FREED               0x000D  /**< Duplicate free detected by the memory test harness. */
#define CIC_ERR_MEM_NOT_OURS                0x000E  /**< Attempt to free unallocated memory detected by test harness. */
#define CIC_ERR_MEM_ZERO_ALLOCED            0x000F  /**< Attempt to allocate zero bytes of memory. */
#define CIC_ERR_NOT_IMPLEMENTED             0x0FFE  /**< Functionality not implemented */
#define CIC_ERR_INTERNAL                    0x0FFF  /**< Some unknown internal error */

#define CIC_ERR_CODING_BAD_ENCODING  0x0221
#define CIC_ERR_BASE64_BAD_ENCODING  CIC_ERR_CODING_BAD_ENCODING
#define CIC_ERR_CODING_BAD_PEM       0x0222
#define CIC_ERR_BASE64_BAD_PEM       CIC_ERR_CODING_BAD_PEM

/*
    General error codes that are identical to Security Builder errors.

    These are general error codes that exist in most products and the value of the
    error code is identical to an error code from Security Builder.
*/
#define CIC_ERR_MEMORY                      SB_FAIL_ALLOC  /**< SB_FAIL_ALLOC Allocation error */

#ifdef __cplusplus
}
#endif

#endif

