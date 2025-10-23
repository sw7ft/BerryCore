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
/* $Id: sbreturn.h 44832 2014-03-13 19:13:15Z hwang $
 * $Source$
 * $Name$
 */
#ifndef SBRETURN_H
#define SBRETURN_H

#ifdef __cplusplus
extern "C" {
#endif

/*
Certicom Error Code Categories

All Certicom products use a common error code scheme.
APIs in each product return an integer error code. The actual size of the return code
will vary in size depending on the target O/S or compiler settings.
However, all Certicom products will only use the lower 2 bytes of the integer.
All Certicom products will return one of the following three types of error codes:

    (1) A general error code. These are a set of error codes that are common to most
        products. Most common error codes are in the range (0x0000-0x0FFF).
        However, there is one general error code that is identical to a Security Builder
        error code: CIC_ERR_MEMORY is identical to SB_FAIL_ALLOC.

    (2) A Security Builder error code. These are errors that are returned from Security
        Builder. All error codes are in the range (0xE000 - 0xFFFF).

    (3) A product specific error code. These are errors that are specific to the product.
        All product specific error codes are 2 bytes which are interpretted as follows:
        The top nibble of the hi-byte is used to indicate the product and the actual error
        is the rest of the nibbles.
            - 0x1   = specific error codes for SSL Plus.
            - 0x2   = specific error codes for WTLS Plus.
            - 0x3   = specific error codes for SBI.
            - 0x4   = specific error codes for SBI.
            - 0x5   = specific error codes for TPC.
            - 0x6   = error codes allocated in ranges smaller than 12 bits
              - 0x6F80 - 0x6FFF = error codes for Stores
            - 0x0,0xE,0xF are reserved for common error codes and Security Builder errors.
*/

#define SB_ERR_CIC_BASE    0x0000  /**< Error base for general Certicom common errors */
#define SB_ERR_SSL_BASE    0x1000  /**< Error base for SSL Plus specific errors */
#define SB_ERR_WTLS_BASE   0x2000  /**< Error base for WTLS Plus specific errors */
#define SB_ERR_SBI_BASE1   0x3000  /**< Error base for SBI specific errors */
#define SB_ERR_SBI_BASE2   0x4000  /**< Error base for SBI user specific errors */
#define SB_ERR_TPC_BASE    0x5000  /**< Error base for Trustpoint Client specific errors */
#define SB_ERR_SMALL_BASE  0x6000  /**< Error base for allocating small ranges of errors */
#define SB_ERR_CODE_SIGN   0x6E80  /**< Error base for Code Sign - 7 bits reserved */
#define SB_ERR_ETS_TB_BASE 0x6F00  /**< Error base for ETS Trusted Boot - 7 bits reserved */
#define SB_ERR_STORE_BASE  0x6F80  /**< Error base for Store errors - 7 bits reserved */
#define SB_ERR_SB_BASE1    0xE000  /**< Error base for Security Builder specific errors */
#define SB_ERR_SB_BASE2    0xF000  /**< Error base for Security Builder specific errors */


/*============= Common errors ==============*/

/** @addtogroup hula_rc_general General Return Codes
 *
 * @{
 *
 */

/** Success */
#define SB_SUCCESS                      0x0000

#define SB_NOT_IMPLEMENTED              0xFFFE
#define SB_FAILURE                      0xFFFF

/** @} */

/** @addtogroup hula_rc_common Common Return Codes
 *
 * @{
 *
 */


/** One of the parameters passed a NULL value */
#define SB_ERR_NULL_PARAMS              0xE101

/** One of the parameters, which is a pointer, was NULL */
#define SB_ERR_NULL_PARAMS_PTR          0xE102

#define SB_ERR_BAD_PARAMS               0xE103
#define SB_ERR_NULL_CONTEXT             0xE104
#define SB_ERR_NULL_CONTEXT_PTR         0xE105
#define SB_ERR_BAD_CONTEXT              0xE106
#define SB_ERR_NULL_RNG                 0xE107
#define SB_ERR_NO_RNG                   0xE108
#define SB_ERR_BAD_RNG_TYPE             0xE109
#define SB_ERR_BAD_RNG_CONTEXT          0xE10A
#define SB_ERR_BAD_YIELD_CONTEXT        0xE10B
#define SB_ERR_NULL_KEY                 0xE10C
#define SB_ERR_NULL_KEY_PTR             0xE10D
#define SB_ERR_BAD_KEY                  0xE10E
#define SB_ERR_NULL_KEY_LEN             0xE10F
#define SB_ERR_BAD_KEY_LEN              0xE110
#define SB_ERR_NULL_PRIVATE_KEY         0xE111
#define SB_ERR_BAD_PRIVATE_KEY          0xE112
#define SB_ERR_NULL_PRI_KEY_BUF         0xE113
#define SB_ERR_BAD_PRI_KEY_BUF_LEN      0xE114
#define SB_ERR_NULL_PUBLIC_KEY          0xE115
#define SB_ERR_BAD_PUBLIC_KEY           0xE116
#define SB_ERR_NULL_PUB_KEY_BUF         0xE117
#define SB_ERR_BAD_PUB_KEY_BUF_LEN      0xE118
#define SB_ERR_NULL_INPUT               0xE119
#define SB_ERR_NULL_INPUT_LEN           0xE11A
#define SB_ERR_BAD_INPUT_LEN            0xE11B
#define SB_ERR_NULL_INPUT_BUF           0xE11C
#define SB_ERR_BAD_INPUT_BUF_LEN        0xE11D
#define SB_ERR_BAD_INPUT                0xE11E
#define SB_ERR_NULL_OUTPUT              0xE11F
#define SB_ERR_NULL_OUTPUT_BUF          0xE120
#define SB_ERR_NULL_OUTPUT_BUF_LEN_PTR  0xE121
#define SB_ERR_NULL_OUTPUT_BUF_LEN      0xE122
#define SB_ERR_BAD_OUTPUT_BUF_LEN       0xE123
#define SB_ERR_NULL_ADDINFO             0xE124
#define SB_ERR_BAD_ALG                  0xE125
#define SB_ERR_BAD_FLAG                 0xE126
#define SB_ERR_NULL_BUFFER              0xE127
#define SB_ERR_NULL_LENGTH              0xE128
#define SB_ERR_BAD_LENGTH               0xE129
#define SB_ERR_OVERFLOW                 0xE12A
#define SB_ERR_NULL_HASH_INFO           0xE12B

/** The private key object cannot be exported. */
#define SB_ERR_PRI_KEY_NOT_EXPORTABLE   0xE12C
/** The public key object cannot be exported. */
#define SB_ERR_PUB_KEY_NOT_EXPORTABLE   0xE12D
/** The symmetric key object cannot be exported */
#define SB_ERR_SYM_KEY_NOT_EXPORTABLE   0xE12E


/** @} */

/*==== For key agreement schemes errors ====*/

/** @addtogroup hula_rc_keyagree Key Agreement Scheme Return Codes
 *
 * @{
 *
 */

#define SB_ERR_NULL_EPHEM_PRI_KEY       0xE201
#define SB_ERR_BAD_EPHEM_PRI_KEY        0xE202
#define SB_ERR_NULL_EPHEM_PUB_KEY       0xE203
#define SB_ERR_BAD_EPHEM_PUB_KEY        0xE204
#define SB_ERR_NULL_REM_EPHEM_PUB_KEY   0xE205
#define SB_ERR_BAD_REM_EPHEM_PUB_KEY    0xE206
#define SB_ERR_NULL_REM_PUB_KEY         0xE207
#define SB_ERR_BAD_REM_PUB_KEY          0xE208

/** @} */

/** @addtogroup hula_rc_signature Signature Scheme Return Codes
 *
 * @{
 *
 */

/*====== For signature schemes errors ======*/

#define SB_ERR_NULL_SIGNATURE           0xE301
#define SB_ERR_NULL_SIGNATURE_LEN       0xE302
#define SB_ERR_BAD_SIGNATURE_LEN        0xE303
#define SB_ERR_NULL_S_VALUE             0xE305
#define SB_ERR_NULL_S_VALUE_LEN         0xE306
#define SB_ERR_BAD_S_VALUE_LEN          0xE307
#define SB_ERR_NULL_R_VALUE             0xE308
#define SB_ERR_NULL_R_VALUE_LEN         0xE309
#define SB_ERR_BAD_R_VALUE_LEN          0xE30A
#define SB_ERR_BAD_HASH_TYPE            0xE30B

/** @} */

/* For public key encryption schemes errors (0xE4xx) */


/*====== For EC Calculator errors ======*/

/** @addtogroup hula_rc_eccalc EC Calculator Return Codes
 *
 * @{
 *
 */

#define SB_ERR_NULL_ORDER_INT           0xE501
#define SB_ERR_NULL_ORDER_INT_PTR       0xE502
#define SB_ERR_BAD_ORDER_INT            0xE503
#define SB_ERR_NULL_ECPOINT             0xE504
#define SB_ERR_NULL_ECPOINT_PTR         0xE505
#define SB_ERR_BAD_ECPOINT              0xE506

/** @} */


/*============ For IDLC errors =============*/

/** @addtogroup hula_rc_idlc IDLC Return Codes
 *
 * @{
 *
 */

#define SB_ERR_NULL_IDLC_P              0xE601
#define SB_ERR_BAD_IDLC_P_LEN           0xE602
#define SB_ERR_BAD_IDLC_P               0xE603
#define SB_ERR_NULL_IDLC_Q              0xE604
#define SB_ERR_BAD_IDLC_Q_LEN           0xE605
#define SB_ERR_BAD_IDLC_Q               0xE606
#define SB_ERR_NULL_IDLC_G              0xE607
#define SB_ERR_BAD_IDLC_G_LEN           0xE608
#define SB_ERR_BAD_IDLC_G               0xE609

/** @} */

/*============= For RSA errors =============*/

/** @addtogroup hula_rc_rsa RSA Return Codes
 *
 * @{
 *
 */

#define SB_ERR_BAD_PUB_EXP_LEN          0xE701
#define SB_ERR_NULL_RSA_N               0xE702
#define SB_ERR_BAD_RSA_N_LEN            0xE703
#define SB_ERR_BAD_RSA_N                0xE704
#define SB_ERR_NULL_RSA_E               0xE705
#define SB_ERR_BAD_RSA_E_LEN            0xE706
#define SB_ERR_BAD_RSA_E                0xE707
#define SB_ERR_NULL_RSA_D               0xE708
#define SB_ERR_BAD_RSA_D_LEN            0xE709
#define SB_ERR_BAD_RSA_D                0xE70A
#define SB_ERR_NULL_RSA_P               0xE70B
#define SB_ERR_BAD_RSA_P_LEN            0xE70C
#define SB_ERR_BAD_RSA_P                0xE70D
#define SB_ERR_NULL_RSA_Q               0xE70E
#define SB_ERR_BAD_RSA_Q_LEN            0xE70F
#define SB_ERR_BAD_RSA_Q                0xE711
#define SB_ERR_NULL_RSA_QINV            0xE712
#define SB_ERR_BAD_RSA_QINV_LEN         0xE713
#define SB_ERR_BAD_RSA_QINV             0xE714
#define SB_ERR_NULL_RSA_DP              0xE715
#define SB_ERR_BAD_RSA_DP_LEN           0xE716
#define SB_ERR_BAD_RSA_DP               0xE717
#define SB_ERR_NULL_RSA_DQ              0xE718
#define SB_ERR_BAD_RSA_DQ_LEN           0xE719
#define SB_ERR_BAD_RSA_DQ               0xE71A
#define SB_ERR_RSA_CRT_NOT_AVAILABLE    0xE71B

/** @} */

/*======== For block ciphers errors ========*/

/** @addtogroup hula_rc_block Block Cipher Return Codes
 *
 * @{
 *
 */

#define SB_ERR_BAD_MODE                 0xE801
#define SB_ERR_BAD_ALGORITHM            0xE802
#define SB_ERR_BAD_KEY_PARITY           0xE803
#define SB_ERR_BAD_KEY_OPTION           0xE804
#define SB_ERR_BAD_NUM_KEYS             0xE805
#define SB_ERR_BAD_ROUNDS               0xE806
#define SB_ERR_NULL_IV                  0xE807
#define SB_ERR_BAD_IV_LEN               0xE808
#define SB_ERR_WEAK_KEY                 0xE809
#define SB_ERR_BAD_BLOCK_LEN            0xE80A
#define SB_ERR_BAD_KEY_UNWRAP           0xE80B
#define SB_ERR_NO_MODE                  0xE80C
#define SB_ERR_INVALID_MAC              0xE80D
#define SB_ERR_MAC_INVALID              0xE80E
#define SB_ERR_BAD_IV                   0xE80F

/** @} */

/*== For hash algorithms, HMAC, KDF errors ==*/

/** @addtogroup hula_rc_hash Hash Algorithm Return Codes
 *
 * @{
 *
 */

#define SB_ERR_BAD_DIGEST_LEN           0xE901
#define SB_ERR_BAD_MESSAGE_LEN          0xE902

/** @} */


/*== For DRBG errors ==*/

/** @addtogroup hula_rc_drbg DRBG Return Codes
 *
 * @{
 *
 */

#define SB_ERR_RNG_BAD_DRBG_CONTEXT                    0xEA01
#define SB_ERR_RNG_INVALID_HANDLE                      0xEA02
#define SB_ERR_RNG_BAD_HANDLE                          0xEA03
#define SB_ERR_RNG_NO_MORE_HANDLE                      0xEA04
#define SB_ERR_RNG_SECURITY_STRENGTH_TOO_SMALL         0xEA05
#define SB_ERR_RNG_SECURITY_STRENGTH_NOT_SUPPORTED     0xEA06
#define SB_ERR_RNG_PREDICTIVE_RESISTANCE_NOT_SUPPORTED 0xEA07
#define SB_ERR_RNG_PERSONALIZATION_STRING_TOO_BIG      0xEA08
#define SB_ERR_RNG_ADDITIONAL_INPUT_TOO_BIG            0xEA09
#define SB_ERR_RNG_REQUESTED_BYTES_TOO_BIG             0xEA0A
#define SB_ERR_RNG_REQUESTED_SECURITY_TOO_BIG          0xEA0B
#define SB_ERR_RNG_REQUESTED_HASH_DERIVE_TOO_BIG       0xEA0C
#define SB_ERR_RNG_RESEED_IS_REQUIRED                  0xEA0D
#define SB_ERR_RNG_NULL_TIME_CALLBACK                  0xEA0E

/** @} */

/* For Common MATH errors */


/*============ SB Context errors ============*/

/** @addtogroup hula_rc_ctx Global Context Error Return Codes
 *
 * @{
 *
 */

#define SB_ERR_NULL_GLOBAL_CTX          0xEF01
#define SB_ERR_NULL_GLOBAL_CTX_PTR      0xEF02
#define SB_ERR_BAD_GLOBAL_CTX           0xEF03

/** @} */


/*============= Common failure ==============*/

/** @addtogroup hula_rc_common_fail Common Failure Return Codes
 *
 * @{
 *
 */

#define SB_FAIL_ALLOC                    0xF001
#define SB_FAIL_KEYGEN                   0xF002
#define SB_FAIL_LOCK                     0xF003
#define SB_FAIL_UNLOCK                   0xF004
#define SB_FAIL_NULL_PTR                 0xF005
#define SB_FAIL_INVALID_PRIVATE_KEY      0xF006

#define SB_FAIL_CANNOT_LOAD_LIBRARY      0xF007
#define SB_FAIL_LIBRARY_DISABLED         0xF008
#define SB_FAIL_INTEGRITY                0xF009
#define SB_FAIL_KAT                      0xF00A
#define SB_FAIL_OPEN_FILE                0xF00B
#define SB_FAIL_READ_FILE                0xF00C
#define SB_FAIL_LIBRARY_ALREADY_INIT     0xF00D
#define SB_FAIL_LIBRARY_NOT_INIT         0xF00E

/** @} */

/*========== ECC failures (0xF5xx) ==========*/

/** @addtogroup hula_rc_ecc ECC Failure Return Codes
 *
 * @{
 *
 */

#define SB_FAIL_ECIES_HMAC               0xF501
#define SB_FAIL_INVALID_SHARED_SECRET    0xF502
#define SB_FAIL_INVALID_SIGNATURE        0xF503

/** @} */

/* IDLC failures (0xF6xx) */


/*=========== RSA failures (0xF7xx) =========*/

/** @addtogroup hula_rc_rsa RSA Return Codes
 *
 * @{
 *
 */

#define SB_FAIL_BAD_PADDING              0xF701
#define SB_FAIL_PKCS1_DECRYPT            0xF702

/** @} */

/*========= RNG failures (0xFAxx) ===========*/

/** @addtogroup hula_rc_rng RNG Failure Return Codes
 *
 * @{
 *
 */

#define SB_FAIL_RANDOM_GEN               0xFA01

/** @} */

/*====== Common Math failures (0xFBxx) ======*/

/** @addtogroup hula_rc_math Math Return Codes
 *
 * @{
 *
 */

#define SB_FAIL_DIVIDE_BY_ZERO           0xFB01

/* Can occur when a parameter that
   was expected to be odd (e.g. a prime) was in fact even */
#define SB_FAIL_NO_INVERSE               0xFB02


/*========== FF failures (0xFCxx) ===========*/

#define SB_FAIL_NO_SOLUTION              0xFC01
#define SB_ERR_MODULUS_TOO_BIG           0xFC02
#define SB_ERR_MODULUS_TOO_SMALL         0xFC03


/* Big integer failures (0xFDxx) */

/*=== Prime Generation failures (0xFExx) ===*/

#define SB_FAIL_PRIME_GEN               0xFE01


/* ECA failures (0xFFxx) */

#define SB_ERR_POINT_AT_INFINITY         0xFF00

/** @} */


/** @addtogroup hula_rc_internal Internal Return Codes
 * 
 * @{
 *
 */

/** The provider argument is NULL. */
#define SB_ERR_NULL_PROVIDER                     0x3001

/** The pointer to provider object is NULL. */
#define SB_ERR_NULL_PROVIDER_PTR                 0x3002

/* UNUSED                                        0x3003 */

/** The "init" function for the provider was not called; i.e. 
 * cryptographic support has not been registered in the global context. */
#define SB_ERR_NULL_SESSION                      0x3004

/** @} */

/** @addtogroup hula_rc_really_internal Internal Return Codes
 * @{
 *
 */
/** The session pointer arg is NULL. */
#define SB_ERR_NULL_SESSION_PTR                  0x3005

/** The global context's session is not of the type required by this adapter.
 * This can happen if two adapters that both require initialization are
 * registered, or if one adapter's crypto support was registered, and another
 * adapter was initialized.
 */
#define SB_ERR_BAD_SESSION                       0x3006

/** operation is not supported. */
#define SB_ERR_NOT_SUPPORTED                     0x3007

/** cipher type is invalid. */
#define SB_ERR_BAD_CIPHER_TYPE                   0x3008

/** mode is invalid. */
#define SB_ERR_BAD_MODE_TYPE                     0x3009

/** MAC algorithm ID is invalid */
#define SB_ERR_BAD_MAC_TYPE                      0x300A

/** ECDH type (cofactor or not) ID is invalid */
#define SB_ERR_BAD_ECDH_TYPE                     0x300B

/* UNUSED                                        0x300C */

/* UNUSED                                        0x300D */

/* UNUSED                                        0x300E */

/** bad parameter. */
#define SB_ERR_BAD_PARAMETER                     0x300F

/** oid arg is NULL. */
#define SB_ERR_NULL_OID                          0x3010

/** the format of input data is incorrect. */
#define SB_ERR_BAD_INPUT_FORMAT                  0x3011

/** the handle is NULL. */
#define SB_ERR_NULL_HANDLE                       0x3012

/** the handle is invalid, probably wrong type. */
#define SB_ERR_BAD_HANDLE                        0x3013

/** the specified allocation policy is invalid or unsupported. */
#define SB_ERR_BAD_ALLOC_POLICY                  0x3014

/** @} */

/** @addtogroup hula_rc_notreg Unregistered Component
 *
 * @{
 *
 */

/** The provider does not have the crypto algorithm ECC registered */
#define SB_ERR_ECC_NOT_SUPPORTED                 0x3015


/** The provider does not have ECC curve sect163k1 registered */
#define SB_ERR_ECC_CURVE_SECT163K1_NOT_SUPPORTED 0x3016

/** The provider does not have ECC curve sect163r2 registered */
#define SB_ERR_ECC_CURVE_SECT163R2_NOT_SUPPORTED 0x3017

/** The provider does not have ECC curve sect233k1 registered */
#define SB_ERR_ECC_CURVE_SECT233K1_NOT_SUPPORTED 0x3018

/** The provider does not have ECC curve sect233r1 registered */
#define SB_ERR_ECC_CURVE_SECT233R1_NOT_SUPPORTED 0x3019

/** The provider does not have ECC curve sect239k1 registered */
#define SB_ERR_ECC_CURVE_SECT239K1_NOT_SUPPORTED 0x301A

/** The provider does not have ECC curve sect283k1 registered */
#define SB_ERR_ECC_CURVE_SECT283K1_NOT_SUPPORTED 0x301B

/** The provider does not have ECC curve sect283r1 registered */
#define SB_ERR_ECC_CURVE_SECT283R1_NOT_SUPPORTED 0x301C

/** The provider does not have ECC curve sect409k1 registered */
#define SB_ERR_ECC_CURVE_SECT409K1_NOT_SUPPORTED 0x301D

/** The provider does not have ECC curve sect409r1 registered */
#define SB_ERR_ECC_CURVE_SECT409R1_NOT_SUPPORTED 0x301E

/** The provider does not have ECC curve sect571k1 registered */
#define SB_ERR_ECC_CURVE_SECT571K1_NOT_SUPPORTED 0x301F

/** The provider does not have ECC curve sect571r1 registered */
#define SB_ERR_ECC_CURVE_SECT571R1_NOT_SUPPORTED 0x3020

/** The provider does not have ECC curve secp160r1 registered */
#define SB_ERR_ECC_CURVE_SECP160R1_NOT_SUPPORTED 0x3021

/** The provider does not have ECC curve secp192r1 registered */
#define SB_ERR_ECC_CURVE_SECP192R1_NOT_SUPPORTED 0x3022

/** The provider does not have ECC curve secp224r1 registered */
#define SB_ERR_ECC_CURVE_SECP224R1_NOT_SUPPORTED 0x3023

/** The provider does not have ECC curve secp256r1 registered */
#define SB_ERR_ECC_CURVE_SECP256R1_NOT_SUPPORTED 0x3024

/** The provider does not have ECC curve secp384r1 registered */
#define SB_ERR_ECC_CURVE_SECP384R1_NOT_SUPPORTED 0x3025

/** The provider does not have ECC curve secp521r1 registered */
#define SB_ERR_ECC_CURVE_SECP521R1_NOT_SUPPORTED 0x3026

/** The provider does not have ECC curve wtls5 registered */
#define SB_ERR_ECC_CURVE_WTLS5_NOT_SUPPORTED     0x3027

/** The provider does not have ECC curve wapi1 registered */
#define SB_ERR_ECC_CURVE_WAPI1_NOT_SUPPORTED     0x3028

/** The provider does not have ECC curve wapi1 registered */
#define SB_ERR_ECC_CURVE_GBP320T1_NOT_SUPPORTED  0x3029

/** The provider does not have ECC curve wapi1 registered */
#define SB_ERR_ECC_CURVE_GBP320R1_NOT_SUPPORTED  0x302A

/** The ECC curve ID is not valid */
#define SB_ERR_ECC_BAD_CURVE                     0x302F


/** The provider does not have the crypto algorithm RSA registered */
#define SB_ERR_RSA_NOT_SUPPORTED                 0x3030

/** The provider does not have the crypto algorithm IDLC registered */
#define SB_ERR_IDLC_NOT_SUPPORTED                0x3031

/** The provider does not have the crypto algorithm AES registered */
#define SB_ERR_AES_NOT_SUPPORTED                 0x3032

/** The provider does not have the crypto algorithm DES registered */
#define SB_ERR_DES_NOT_SUPPORTED                 0x3033

/** The provider does not have the crypto algorithm ARC2 registered */
#define SB_ERR_ARC2_NOT_SUPPORTED                0x3034

/** The provider does not have the crypto algorithm ARC4 registered */
#define SB_ERR_ARC4_NOT_SUPPORTED                0x3035

/** The provider does not have the crypto algorithm RC5 registered */
#define SB_ERR_RC5_NOT_SUPPORTED                 0x3036

/** The provider does not have the crypto algorithm Authenticated Encryption  registered */
#define SB_ERR_AUTHENC_NOT_SUPPORTED             0x3037

/** The provider does not have the crypto algorithm BF registered */
#define SB_ERR_BF_NOT_SUPPORTED                  0x3038

/** The provider does not have the crypto algorithm IDEA registered */
#define SB_ERR_IDEA_NOT_SUPPORTED                0x3039

/** The provider does not have the crypto algorithm CAST registered */
#define SB_ERR_CAST_NOT_SUPPORTED                0x303A

/** The provider does not have the crypto algorithm TWOFISH registered */
#define SB_ERR_TWOFISH_NOT_SUPPORTED             0x303B

/** The provider does not have the crypto algorithm MD2 registered */
#define SB_ERR_MD2_NOT_SUPPORTED                 0x3040

/** The provider does not have the crypto algorithm MD4 registered */
#define SB_ERR_MD4_NOT_SUPPORTED                 0x3041

/** The provider does not have the crypto algorithm MD5 registered */
#define SB_ERR_MD5_NOT_SUPPORTED                 0x3042

/** The provider does not have the crypto algorithm SHA1 registered */
#define SB_ERR_SHA1_NOT_SUPPORTED                0x3043

/** The provider does not have the crypto algorithm SHA224 registered */
#define SB_ERR_SHA224_NOT_SUPPORTED              0x3044

/** The provider does not have the crypto algorithm SHA256 registered */
#define SB_ERR_SHA256_NOT_SUPPORTED              0x3045

/** The provider does not have the crypto algorithm SHA384 registered */
#define SB_ERR_SHA384_NOT_SUPPORTED              0x3046

/** The provider does not have the crypto algorithm SHA512 registered */
#define SB_ERR_SHA512_NOT_SUPPORTED              0x3047

/** The provider does not have the crypto algorithm AES MMO registered */
#define SB_ERR_AES_MMO_NOT_SUPPORTED             0x3048


/** The provider does not have the crypto algorithm HMAC MD2 registered */
#define SB_ERR_HMAC_MD2_NOT_SUPPORTED            0x3050

/** The provider does not have the crypto algorithm HMAC MD4 registered */
#define SB_ERR_HMAC_MD4_NOT_SUPPORTED            0x3051

/** The provider does not have the crypto algorithm HMAC MD5 registered */
#define SB_ERR_HMAC_MD5_NOT_SUPPORTED            0x3052

/** The provider does not have the crypto algorithm HMAC SHA1 registered */
#define SB_ERR_HMAC_SHA1_NOT_SUPPORTED           0x3053

/** The provider does not have the crypto algorithm HMAC SHA224 registered */
#define SB_ERR_HMAC_SHA224_NOT_SUPPORTED         0x3054

/** The provider does not have the crypto algorithm HMAC SHA256 registered */
#define SB_ERR_HMAC_SHA256_NOT_SUPPORTED         0x3055

/** The provider does not have the crypto algorithm HMAC SHA384 registered */
#define SB_ERR_HMAC_SHA384_NOT_SUPPORTED         0x3056

/** The provider does not have the crypto algorithm HMAC SHA512 registered */
#define SB_ERR_HMAC_SHA512_NOT_SUPPORTED         0x3057

/** The provider does not have the crypto algorithm MAC XCBC AES registered */
#define SB_ERR_MAC_XCBC_AES_NOT_SUPPORTED        0x3058

/** The provider does not have the crypto algorithm CMAC AES registered */
#define SB_ERR_MAC_CMAC_AES_NOT_SUPPORTED        0x3059

/** The provider does not have a random number generator registered */
#define SB_ERR_RNG_NOT_SUPPORTED                 0x3060

/** The provider does not have ANSI KDF using SHA-1 registered */
#define SB_ERR_KDF_ANSI_SHA1_NOT_SUPPORTED       0x3061

/** The provider does not have IEEE KDF1 using SHA-1 registered */
#define SB_ERR_KDF_IEEE_KDF1_SHA1_NOT_SUPPORTED  0x3062

/** The provider does not have ANSI KDF using SHA-224 registered */
#define SB_ERR_KDF_ANSI_SHA224_NOT_SUPPORTED     0x3063

/** The provider does not have ANSI KDF using SHA-256 registered */
#define SB_ERR_KDF_ANSI_SHA256_NOT_SUPPORTED     0x3064

/** The provider does not have ANSI KDF using SHA-384 registered */
#define SB_ERR_KDF_ANSI_SHA384_NOT_SUPPORTED     0x3065

/** The provider does not have ANSI KDF using SHA-512 registered */
#define SB_ERR_KDF_ANSI_SHA512_NOT_SUPPORTED     0x3066

/** The provider does not have PKCS#5v1 KDF using MD2 registered */
#define SB_ERR_KDF_PKCS5_V1_MD2_NOT_SUPPORTED    0x3067

/** The provider does not have PKCS#5v1 KDF using MD5 registered */
#define SB_ERR_KDF_PKCS5_V1_MD5_NOT_SUPPORTED    0x3068

/** The provider does not have PKCS#5v1 KDF using SHA-1 registered */
#define SB_ERR_KDF_PKCS5_V1_SHA1_NOT_SUPPORTED   0x3069

/** The provider does not have PKCS#5v2 KDF using SHA-1 registered */
#define SB_ERR_KDF_PKCS5_V2_SHA1_NOT_SUPPORTED   0x306A

/** The provider does not have PKCS#5v2 KDF using SHA-256 registered */
#define SB_ERR_KDF_PKCS5_V2_SHA256_NOT_SUPPORTED 0x306B

/** The provider does not have PKCS#12v2 KDF using SHA-1 registered */
#define SB_ERR_KDF_PKCS12_V1_SHA1_NOT_SUPPORTED  0x306C

/** The provider does not have PKCS#12v2 KDF using SHA-256 registered */
#define SB_ERR_KDF_PKCS12_V1_SHA256_NOT_SUPPORTED 0x306D

/** The provider does not have a seeding source registered */
#define SB_ERR_SEED_NOT_SUPPORTED                0x306E

/** The KDF algorithm id is invalid */
#define SB_ERR_KDF_BAD_ALGORITHM                 0x306F

/** Unwrapping operation failed due to bad key or bad input data */
#define SB_ERR_UNWRAP_FAILED                     0x3070

/** More calls to multi-digest context than supported were attempted */
#define SB_ERR_MULTI_DIGEST_EXCEEDED             0x3071


/** The provider does not have IPSec Group 1 registered */
#define SB_ERR_IDLC_GROUP_IPSEC_1_NOT_SUPPORTED  0x3080

/** The provider does not have IPSec Group 2 registered */
#define SB_ERR_IDLC_GROUP_IPSEC_2_NOT_SUPPORTED  0x3081

/** The provider does not have IPSec Group 5 registered */
#define SB_ERR_IDLC_GROUP_IPSEC_5_NOT_SUPPORTED  0x3082

/** The provider does not have WTLS Group 1 registered */
#define SB_ERR_IDLC_GROUP_WTLS_1_NOT_SUPPORTED   0x3083

/** The provider does not have WTLS Group 2 registered */
#define SB_ERR_IDLC_GROUP_WTLS_2_NOT_SUPPORTED   0x3084

/** The provider does not have IPSec Group 14 registered */
#define SB_ERR_IDLC_GROUP_IPSEC_14_NOT_SUPPORTED  0x3085

/** The provider does not have IPSec Group 15 registered */
#define SB_ERR_IDLC_GROUP_IPSEC_15_NOT_SUPPORTED  0x3086

/** The provider does not have IPSec Group 16 registered */
#define SB_ERR_IDLC_GROUP_IPSEC_16_NOT_SUPPORTED  0x3087

/** The provider does not have IPSec Group 17 registered */
#define SB_ERR_IDLC_GROUP_IPSEC_17_NOT_SUPPORTED  0x3088

/** The provider does not have IPSec Group 18 registered */
#define SB_ERR_IDLC_GROUP_IPSEC_18_NOT_SUPPORTED  0x3089

/** The provider does not recognize the requested group */
#define SB_ERR_IDLC_BAD_GROUP                    0x308F

/** The provider does not have NIST Alternative 1 KDF registered */
#define SB_ERR_KDF_NIST_ALT1_NOT_SUPPORTED       0x3090

/** The provider does not have PKCS#5v2 KDF using SHA-224 registered */
#define SB_ERR_KDF_PKCS5_V2_SHA224_NOT_SUPPORTED 0x3091

/** The provider does not have PKCS#5v2 KDF using SHA-384 registered */
#define SB_ERR_KDF_PKCS5_V2_SHA384_NOT_SUPPORTED 0x3092

/** The provider does not have PKCS#5v2 KDF using SHA-512 registered */
#define SB_ERR_KDF_PKCS5_V2_SHA512_NOT_SUPPORTED 0x3093

/** The provider does not have PKCS#12v2 KDF using SHA-224 registered */
#define SB_ERR_KDF_PKCS12_V1_SHA224_NOT_SUPPORTED 0x3094

/** The provider does not have PKCS#12v2 KDF using SHA-384 registered */
#define SB_ERR_KDF_PKCS12_V1_SHA384_NOT_SUPPORTED 0x3095

/** The provider does not have PKCS#12v2 KDF using SHA-512 registered */
#define SB_ERR_KDF_PKCS12_V1_SHA512_NOT_SUPPORTED 0x3096

/** The provider does not have Key Split registered */
#define SB_ERR_KS_NOT_SUPPORTED 0x3097

/** The provider does not have ZMod Calculator registered */
#define SB_ERR_ZMOD_CALC_NOT_SUPPORTED 0x3098


/** @} */

/** @addtogroup hula_rc_base Provider-Specific Bases
 *
 * @{
 *
 */

/* Bases for provider specific errors.
 *
 * If the error generated by the provider cannot be mapped to a Security
 * Builder error then the error will have the bottom nibble of the hi-byte set
 * to determine which provider generated the error.
 */

/** Gets the base of an SBI error.
 *
 * SBI uses the bottom nibble of the hi-byte to indicate which provider
 * generated the error.
 */
#define SB_GET_ERR_BASE(e) ((e) & ~0xff)

/** base of Cryptoswift specific errors */
#define SB_ERR_CS_BASE             0x3100

/** base of BSAFE specific errors */
#define SB_ERR_BS_BASE             0x3200

/** base of PKCS #11 vendor-defined errors */
#define SB_ERR_PKCS11_VENDOR_BASE         0x3300

/** base of CAC specific errors */
#define SB_ERR_CAC_BASE            0x3400

/** base of O/S specific errors */
#define SB_ERR_OS_BASE             0x3600

/** base of CGX specific errors */
#define SB_ERR_CGX_BASE            0x3700

/** base of PKCS #11 specific errors. This error space slice is actually 0x3800-0x39FF. */
#define SB_ERR_PKCS11_BASE         0x3800

/* base of Freescale i.300 specific errors */
#define SB_ERR_I300_BASE           0x3A00

/** base of WTP specific errors */
#define SB_ERR_WTP_BASE            0x3B00

/** base of PowerQuicc specific errors */
#define SB_ERR_PQ_BASE             0x3C00 

/** base of Elliptic Semiconductor specific errors */
#define SB_ERR_ES_BASE             0x3D00 

/** @} */

#ifdef __cplusplus
}
#endif

#endif
