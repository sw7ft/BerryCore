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
#ifndef HUAPIVER_H
#define HUAPIVER_H

/** @file */

/* This file is auto-generated from tools/build/mkver, do not modify or commit. */

#include "sbdef.h"

#define HU_API_MAJOR 5
#define HU_API_MINOR 6
#define HU_API_PATCH 4
#define HU_API_BUILD 44867
#define HU_API_VERSION "sbapi 5.6.4.44867   (subrep/crypto-c/branches/release/5.6.4 )"

#ifdef __cplusplus
extern "C" {
#endif

/**
This function returns the version string for the product.

@retval HU_API_VERSION The product version string.
*/
extern
SB_EXPORT
const char*
SB_CALLCONV
hu_ApiVersion (void);

#ifdef __cplusplus
}
#endif

#endif
