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
/* $Id: cicdef.h 41815 2010-12-06 16:15:04Z mimueller $
 * $Source$
 * $Name$
 */
#ifndef CICDEF_H
#define CICDEF_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sbdef.h"

typedef enum cic_AllocPolicy
{
    CIC_ALLOC_COPY = 0,   /**< Make a copy of the memory block */

    CIC_ALLOC_USE  = 1,   /**< Store a pointer to a memory block and use it.
                               The caller own the block and will not deallocate
                               it early.
                          */

    CIC_ALLOC_KEEP = 2,   /**< The called function will own the memory block.
                               The caller will not care about it any more.
                          */

  /* This is for backwards compatibility */
  CIC_ALLOCATION_POINTER_COPY     = CIC_ALLOC_USE,
  CIC_ALLOCATION_DATA_COPY        = CIC_ALLOC_COPY

} cic_AllocPolicy;

typedef enum cic_AllocPolicy cic_AllocationType;

typedef unsigned long cic_Flags;

#ifndef CIC_SEG
#ifdef PALM_SHARED
#define CIC_SEG(segment_name) __attribute__ ((section (#segment_name)))
#else
#define CIC_SEG(segment_name)
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif

