/*
 * Copyright © 1996-2012 Certicom Corp. All rights reserved.
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
#ifndef HUGSE56VER_H
#define HUGSE56VER_H

/** @file */

/* This file is auto-generated from tools/build/mkver, do not modify or commit. */

#include "sbdef.h"

#define HU_GSE56_MAJOR 5
#define HU_GSE56_MINOR 6
#define HU_GSE56_PATCH 2
#define HU_GSE56_BUILD 44214
#define HU_GSE56_VERSION "hugse56 5.6.2.44214   (http://svn/subrep/crypto-c/tags/5.6.2 )"

#ifdef __cplusplus
extern "C" {
#endif

/**
This function returns the version string for the product.

@retval HU_GSE56_VERSION The product version string.
*/
extern
SB_EXPORT
const char*
SB_CALLCONV
hu_Gse56Version (void);

#ifdef __cplusplus
}
#endif

#endif
