/*
 * $QNXLicenseC:
 * Copyright 2013, QNX Software Systems. All Rights Reserved.
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

#ifndef OPENMAX_AL_FM_H_
#define OPENMAX_AL_FM_H_

#ifdef __cplusplus
extern "C" {
#endif

#define FM_RADIO_AVAILABLE               0
#define FM_RADIO_CARRIER_DISABLED        1
#define FM_RADIO_MCC_DISABLED            2
#define FM_RADIO_HARDWARE_NOT_SUPPORTED  3
#define FM_RADIO_IT_POLICY_DISABLED      4

extern int fmIsRadioAvailable(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
