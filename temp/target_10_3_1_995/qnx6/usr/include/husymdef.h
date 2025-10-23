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
/* $Id: husymdef.h 44832 2014-03-13 19:13:15Z hwang $
 * $Source$
 * $Name$
 */
#ifndef HU_SYMDEF_H
#define HU_SYMDEF_H

#ifdef __cplusplus
extern "C" {
#endif

#define HU_SYMCIPHER_CIPHER_DES           1   /**< Algorithm ID for DES block cipher */
#define HU_SYMCIPHER_CIPHER_TDES          2   /**< Algorithm ID for 3DES block cipher */
#define HU_SYMCIPHER_CIPHER_DESX          3   /**< Algorithm ID for DESX block cipher */
#define HU_SYMCIPHER_CIPHER_AES_128       4   /**< Algorithm ID for AES 128-bit key strength block cipher */
#define HU_SYMCIPHER_CIPHER_ARC4          5   /**< Algorithm ID for ARC4 stream cipher */
#define HU_SYMCIPHER_CIPHER_ARC2_40       6   /**< Algorithm ID for ARC2 40-bit block cipher */
#define HU_SYMCIPHER_CIPHER_ARC2_64       7   /**< Algorithm ID for ARC2 64-bit block cipher */
#define HU_SYMCIPHER_CIPHER_ARC2_128      8   /**< Algorithm ID for ARC2 128-bit block cipher */
#define HU_SYMCIPHER_CIPHER_AES_192       9   /**< Algorithm ID for AES 192-bit key strength block cipher */
#define HU_SYMCIPHER_CIPHER_AES_256      10   /**< Algorithm ID for AES 256-bit key strength block cipher */
#define HU_SYMCIPHER_CIPHER_BF_64        11   /**< Algorithm ID for BF 64-bit block cipher */
#define HU_SYMCIPHER_CIPHER_IDEA_64      12   /**< Algorithm ID for IDEA 64-bit block cipher */
#define HU_SYMCIPHER_CIPHER_CAST_64      13   /**< Algorithm ID for CAST 64-bit block cipher */
#define HU_SYMCIPHER_CIPHER_TWOFISH_128  14   /**< Algorithm ID for TWOFISH 128-bit block cipher */

#define HU_SYMCIPHER_MODE_ECB          1   /**< Algorithm ID for ECB mode */
#define HU_SYMCIPHER_MODE_CBC          2   /**< Algorithm ID for CBC mode */
#define HU_SYMCIPHER_MODE_CFB64        3   /**< Algorithm ID for CFB 64 mode */
#define HU_SYMCIPHER_MODE_OFB64        4   /**< Algorithm ID for OFB 64 mode */
#define HU_SYMCIPHER_MODE_OFB128       5   /**< Algorithm ID for OFB 128 mode */
#define HU_SYMCIPHER_MODE_CFB128       6   /**< Algorithm ID for CFB 128 mode */

#define HU_SYMCIPHER_MODE_CTR_BASE        7 /**< Base of Algorithm IDs for CTR mode */
#define HU_SYMCIPHER_MODE_CTR(ctrBits)    (HU_SYMCIPHER_MODE_CTR_BASE | (ctrBits << 8))  /** Macro for constructing CTR mode IDs */
#define HU_SYMCIPHER_MODE_CTR8            HU_SYMCIPHER_MODE_CTR(8)   /**< Algorithm ID for CTR mode with 8 bit counter */
#define HU_SYMCIPHER_MODE_CTR16           HU_SYMCIPHER_MODE_CTR(16)  /**< Algorithm ID for CTR mode with 16 bit counter */
#define HU_SYMCIPHER_MODE_CTR32           HU_SYMCIPHER_MODE_CTR(32)  /**< Algorithm ID for CTR mode with 32 bit counter */
#define HU_SYMCIPHER_MODE_CTR64           HU_SYMCIPHER_MODE_CTR(64)  /**< Algorithm ID for CTR mode with 64 bit counter */
#define HU_SYMCIPHER_MODE_CTR128          HU_SYMCIPHER_MODE_CTR(128) /**< Algorithm ID for CTR mode with 128 bit counter */


#ifdef __cplusplus
}
#endif

#endif
