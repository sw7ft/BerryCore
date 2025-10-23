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
/* $Id: hurtti.h 44832 2014-03-13 19:13:15Z hwang $
 * $Source: /cvs/ca/eng/consec/sbi/src/husw/src/huapi/include/hurtti.h,v $
 * $Name:  $
 */
#ifndef HURTTI_H
#define HURTTI_H

/** @file */

#include "sbdef.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 
 *
 * Structure of tags is:
 *
 * | 8 | 8 | 4 | 4 | 4 | 4 |
 * +-+-+-+-+-+-+-+-+-+-+-+-+
 *   |   |   |   |   |   |   |
 *   |   |   |   |   |   +-- structure tags
 *   |   |   |   |   |
 *   |   |   |   |   +-- implementation (L, lower range, 0..14 only: SB, Cryptoki,... )
 *   |   |   |   |
 *   |   |   |   +-- algorithm type
 *   |   |   |
 *   |   |   +-- algorithm class (RSA, ECC, HASH, Ciphers, ...)
 *   |   |
 *   |   +-- extra space for implementation (H, higher range, 16..255 only)
 *   |
 *   +-- reserved
 */

/** @addtogroup rtti_tag_macros Tag Macros
 *
 * @{
 */

typedef sb_Int32 sb_Tag;                           /**< Tags are 32-bit values. */

#define HU_TAG_CLASS(x)   (x & 0x0000ff00)         /**< Gets the algorithm class of a tag. */
#define HU_TAG_ALGO(x)    (x & 0x0000f000)         /**< Gets the algorithm type of a tag. */
#define HU_TAG_TYPE(x)    (x & 0x00000f00)         /**< Gets the TYPE of a tag. */
#define HU_TAG_STRUCT(x)  (x & 0x0000000f)         /**< Gets the structure tags of a tag.*/

/** @} */

/* Implementation tag gets defined in one of the two partitions, 4-bit L and 8-bit H.
 *                 /- L, if 0 <= L < 15
 * impl_tag(x) is +
 *                 \- H, if L == 15; H >= 16.
 *
 * Note 1: To prevent partitions' collisions, the range 0..15 is prohibited in H.
 *
 * Note 2: L=15 is a special case which does not specify any tag on its own.
 *         it is only a flag to use the H value instead of L.
 *
 * Note 3: L=15 H=255 is reserved to specify the bad tag.
 */

#define HU_TAG_LIB_LO_MASK     0x000000f0
#define HU_TAG_LIB_HI_MASK     0x00ff0000

/** @addtogroup rtti_tag_macros Tag Macros
 *
 * @{
 */

#define HU_TAG_LIB(tag)       ( (tag) & (HU_TAG_LIB_LO_MASK | HU_TAG_LIB_HI_MASK) ) /**< Gets the implementation of a tag.*/

/** @} */

/** @addtogroup rtti_do_not_include_in_docs
 *
 * @{
 *
 */

#define HU_TAG_LIB_LO(tag)    (((tag) & HU_TAG_LIB_LO_MASK) >> 4)

#define HU_TAG_LIB_HI(tag)    (((tag) & HU_TAG_LIB_HI_MASK) >> 16)

#define HU_TAG_LIB_VALID(tag) ((HU_TAG_LIB_LO(tag) < 15 && HU_TAG_LIB_HI(tag) == 0) || \
                               (HU_TAG_LIB_LO(tag) == 15 && HU_TAG_LIB_HI(tag) > 15 && HU_TAG_LIB_HI(tag) < 255) )

#define HU_TAG_LIB_MATCH(tag,lib_tag) (HU_TAG_LIB(tag) == (lib_tag))

#define HU_TAG_LIB_BAD         0x00ff00f0

#define HU_TAG_LIB_SET(tag,lib_tag)  ( (tag) &= ~(HU_TAG_LIB_LO_MASK | HU_TAG_LIB_HI_MASK), (tag) |=  (HU_TAG_LIB_VALID(lib_tag) ? (lib_tag) : HU_TAG_LIB_BAD) )


/** @} */

/** @addtogroup rtti_tag_algo Algorithm Classes
 *
 * @{
 */

#define HU_TAG_ALGO_RSA     0x00000000   /**< RSA algorithm class. */
#define HU_TAG_ALGO_IDLC    0x00001000   /**< IDLC algorithm class. */
#define HU_TAG_ALGO_ECC     0x00002000   /**< ECC algorithm class. */
#define HU_TAG_ALGO_BLOCK   0x00003000   /**< Block & stream cipher algorithm class. */
#define HU_TAG_ALGO_HASH    0x00004000   /**< Hash & HMAC algorithm class. */
#define HU_TAG_ALGO_RNG     0x00005000   /**< RNG algorithm class. */
#define HU_TAG_ALGO_AUTHENC 0x00006000   /**< Authenticated Encryption algorithm class. */
/** @} */

/** @addtogroup rtti_tag_type Algorithm Sub-Class
 *
 * @{
 */

#define HU_TAG_TYPE_DES         0x00000000   /**< DES algorithm class. */
#define HU_TAG_TYPE_RC5         0x00000100   /**< RC5 algorithm class. */
#define HU_TAG_TYPE_AES         0x00000200   /**< AES algorithm class. */
#define HU_TAG_TYPE_RC2         0x00000300   /**< RC2 algorithm class. */
#define HU_TAG_TYPE_RESERVE     0x00000500   /**< Reserved. */
#define HU_TAG_TYPE_RC4         0x00000A00   /**< RC4 algorithm class. */
#define HU_TAG_TYPE_BF          0x00000B00   /**< BF  algorithm class. */
#define HU_TAG_TYPE_IDEA        0x00000C00   /**< IDEA algorithm class. */
#define HU_TAG_TYPE_CAST        0x00000D00   /**< CAST algorithm class. */
#define HU_TAG_TYPE_TWOFISH     0x00000E00   /**< TWOFISH algorithm class. */
#define HU_TAG_TYPE_PAD         0x00000F00   /**< Padding algorithm class. */

#define HU_TAG_TYPE_SHA1        0x00000000   /**< SHA1 algorithm class. */
#define HU_TAG_TYPE_MD5         0x00000100   /**< MD5 algorithm class. */
#define HU_TAG_TYPE_MD2         0x00000200   /**< MD2 algorithm class. */
#define HU_TAG_TYPE_SHA256      0x00000300   /**< SHA256 algorithm class. */
#define HU_TAG_TYPE_SHA384      0x00000400   /**< SHA384 algorithm class. */
#define HU_TAG_TYPE_SHA512      0x00000500   /**< SHA512 algorithm class. */
#define HU_TAG_TYPE_MD4         0x00000600   /**< MD4 algorithm class. */
#define HU_TAG_TYPE_SHA224      0x00000700   /**< SHA224 algorithm class. */
#define HU_TAG_TYPE_AES_MMO     0x00000800   /**< AES MMO algorithm class. */

#define HU_TAG_TYPE_HMAC        0x00000A00   /**< HMAC algorithm class. */
#define HU_TAG_TYPE_HMAC_V2     0x00000B00   /**< HMAC v2 (with key objects) algorithm class. */
#define HU_TAG_TYPE_CIPHERMAC   0x00000C00   /**< MAC algorithm class */

#define HU_TAG_STRUCT_HMAC_CONTEXT_SHA1     0x00000001   /**< HMAC SHA1 context structure tag. */
#define HU_TAG_STRUCT_HMAC_CONTEXT_MD5      0x00000002   /**< HMAC MD5 context structure tag. */
#define HU_TAG_STRUCT_HMAC_CONTEXT_SHA256   0x00000003   /**< HMAC SHA256 context structure tag. */
#define HU_TAG_STRUCT_HMAC_CONTEXT_SHA384   0x00000004   /**< HMAC SHA384 context structure tag. */
#define HU_TAG_STRUCT_HMAC_CONTEXT_SHA512   0x00000005   /**< HMAC SHA512 context structure tag. */
#define HU_TAG_STRUCT_HMAC_CONTEXT_SHA224   0x00000006   /**< HMAC SHA224 context structure tag. */

#define HU_TAG_STRUCT_HMAC_KEY_MD5          0x00000007   /**< HMAC MD5 key structure tag. */
#define HU_TAG_STRUCT_HMAC_KEY_SHA1         0x00000008   /**< HMAC SHA1 key structure tag. */
#define HU_TAG_STRUCT_HMAC_KEY_SHA224       0x00000009   /**< HMAC SHA224 key structure tag. */
#define HU_TAG_STRUCT_HMAC_KEY_SHA256       0x0000000A   /**< HMAC SHA256 key structure tag. */
#define HU_TAG_STRUCT_HMAC_KEY_SHA384       0x0000000B   /**< HMAC SHA384 key structure tag. */
#define HU_TAG_STRUCT_HMAC_KEY_SHA512       0x0000000C   /**< HMAC SHA512 key structure tag. */

#define HU_TAG_STRUCT_CIPHERMAC_KEY_XCBC_AES          0x00000000 /**< MAC XCBC AES key structure tag. */
#define HU_TAG_STRUCT_CIPHERMAC_CONTEXT_XCBC_AES      0x00000001 /**< MAC XCBC AES context structure tag. */

#define HU_TAG_STRUCT_CIPHERMAC_KEY_AES_CMAC      0x00000002 /**< AES CMAC key structure tag. */
#define HU_TAG_STRUCT_CIPHERMAC_CONTEXT_AES_CMAC  0x00000003 /**< AES CMAC context structure tag. */


#define HU_TAG_STRUCT_AUTHENC_KEY_CCM              0x00000000 /**< Authenticated Encryption CCM key tag. */ 
#define HU_TAG_STRUCT_AUTHENC_KEY_CCMSTAR          0x00000001 /**< Authenticated Encryption CCMSTAR key tag. */ 
#define HU_TAG_STRUCT_AUTHENC_KEY_GCM              0x00000002 /**< Authenticated Encryption GCM key tag. */ 
#define HU_TAG_STRUCT_AUTHENC_CONTEXT_CCM          0x00000003 /**< Authenticated Encryption CCM context structure tag. */ 
#define HU_TAG_STRUCT_AUTHENC_CONTEXT_CCMSTAR      0x00000004 /**< Authenticated Encryption CCMSTAR context structure tag. */ 
#define HU_TAG_STRUCT_AUTHENC_CONTEXT_GCM          0x00000005 /**< Authenticated Encryption GCM context structure tag. */ 



#define HU_TAG_STRUCT_HASH_CONTEXT_AES_MMO  0x00000001   /**< AES MMO hash context structure tag. */

/* For backward compatibility */
#define HU_TAG_TYPE_HMAC_SHA1     HU_TAG_STRUCT_HMAC_CONTEXT_SHA1  /**< HMAC SHA1 context structure tag. */
#define HU_TAG_TYPE_HMAC_MD5      HU_TAG_STRUCT_HMAC_CONTEXT_MD5   /**< HMAC MD5 context structure tag. */
#define HU_TAG_TYPE_HMAC_SHA256   HU_TAG_STRUCT_HMAC_CONTEXT_SHA256  /**< HMAC SHA256 context structure tag. */
#define HU_TAG_TYPE_HMAC_SHA384   HU_TAG_STRUCT_HMAC_CONTEXT_SHA384  /**< HMAC SHA384 context structure tag. */
#define HU_TAG_TYPE_HMAC_SHA512   HU_TAG_STRUCT_HMAC_CONTEXT_SHA512  /**< HMAC SHA512 context structure tag. */
#define HU_TAG_TYPE_HMAC_SHA224   HU_TAG_STRUCT_HMAC_CONTEXT_SHA224  /**< HMAC SHA224 context structure tag. */


#define HU_TAG_PROVIDER        0x0000B001  /**< Provider Structure tag. */

/** @} */

#define HU_TAG_SYMPAD_CONTEXT   0x00003F00  /**< Symmetric padding cipher context tag. */

/** @addtogroup rtti_tag_session Session Tags
 *
 * @{
 */



#define HU_TAG_SESSION          0x0000B100  /**< Session tag. */

/*UNUSED HU_TAG_SESSION_GENERIC 0x0000B101 */
#define HU_TAG_SESSION_CK       0x0000B102  /**< Cryptoki session tag. */
#define HU_TAG_SESSION_CGX      0x0000B103  /**< CGX session tag. */
#define HU_TAG_SESSION_SAHARA   0x0000B104  /**< SAHARA session tag. */
#define HU_TAG_SESSION_CAC      0x0000B105  /**< CAC session tag. */
/*UNUSED HU_TAG_SESSION_WTP    0x0000B106 */
/*UNUSED HU_TAG_SESSION_GSE2   0x0000B107 */
/*UNUSED HU_TAG_SESSION_OSSL   0x0000B108 */
#define HU_TAG_SESSION_PQ       0x0000B109  /**< PowerQuicc session tag. */
#define HU_TAG_SESSION_I300     0x0000B10A
#define HU_TAG_SESSION_GSE22    0x0000B10B  /**< GSE2.2 session tag */
#define HU_TAG_SESSION_OMAP1710 0x0000B10C  /**< OMAP1710 session tag */
/*RESERVED HU_TAG_SESSION_RESERVE  0x0000B10D */

/** @} */

#define HU_TAG_SB                0x00000000  /**< Security Builder implementation tag. */
#define HU_TAG_CS                0x00000010  /**< Cswift implementation tag. */
#define HU_TAG_BS                0x00000020  /**< BSAFE implementation tag. */
#define HU_TAG_CK                0x00000030  /**< Cryptoki implementation tag. */
#define HU_TAG_CAC               0x00000040  /**< CAC implementation tag. */

/* Legacy tag names.
 */
#define HU_TAG_PKCS11   HU_TAG_CK
#define HU_TAG_BSAFE    HU_TAG_BS


/** @addtogroup sbi_tag_cgx CGX tags

@{ 
*/
#define SBI_TAG_CGX                              0x00000050  /**< CGX implementation tag. */
#define SBI_TAG_CGX_DES_PARAMS                   0x00003050  /**< CGX DES params Tag */
#define SBI_TAG_CGX_DES_DES_KEY                  0x00003051  /**< CGX DES key Tag */
#define SBI_TAG_CGX_DES_TDES_KEY                 0x00003052  /**< CGX TDES key Tag */
#define SBI_TAG_CGX_DES_DESX_KEY                 0x00003053  /**< CGX DESX key Tag */
#define SBI_TAG_CGX_DES_CONTEXT                  0x00003054  /**< CGX DES context Tag */
#define SBI_TAG_CGX_SHA1_CONTEXT                 0x00004051  /**< CGX SHA1 hash context tag. */
#define SBI_TAG_CGX_MD5_CONTEXT                  0x00004151  /**< CGX MD5 hash context tag. */

/** @} sbi_tag_CGX */


/** @addtogroup sbi_tag_sah SAHARA tags

@{ 
*/
#define SBI_TAG_SAH                              0x00000060  /**< SAHARA implementation tag. */
#define SBI_TAG_SAH_DES_PARAMS                   0x00003060  /**< SAHARA DES params Tag */
#define SBI_TAG_SAH_DES_DES_KEY                  0x00003061  /**< SAHARA DES key Tag */
#define SBI_TAG_SAH_DES_TDES_KEY                 0x00003062  /**< SAHARA TDES key Tag */
#define SBI_TAG_SAH_DES_CONTEXT                  0x00003064  /**< SAHARA DES context Tag */
#define SBI_TAG_SAH_AES_PARAMS                   0x00003260  /**< SAHARA AES params Tag */
#define SBI_TAG_SAH_AES_KEY                      0x00003263  /**< SAHARA AES key Tag */
#define SBI_TAG_SAH_AES_CONTEXT                  0x00003264  /**< SAHARA AES context Tag */
#define SBI_TAG_SAH_SHA1_CONTEXT                 0x00004061  /**< SAHARA SHA1 hash context tag. */
#define SBI_TAG_SAH_MD5_CONTEXT                  0x00004161  /**< SAHARA MD5 hash context tag. */
#define SBI_TAG_SAH_ECC                          0x00002060  /**< SAHARA ECC Tag */
#define SBI_TAG_SAH_ECC_PARAMS                   0x00002061  /**< SAHARA ECC params Tag */
#define SBI_TAG_SAH_ECC_PRIVATE_KEY              0x00002062  /**< SAHARA ECC private key Tag */
#define SBI_TAG_SAH_ECC_PUBLIC_KEY               0x00002063  /**< SAHARA ECC public key Tag */
#define SBI_TAG_SAH_RSA_CONTEXT                  0x00000162  /**< SAHARA RSA context tag. */
#define SBI_TAG_SAH_RSA_PARAMS                   0x00000163  /**< SAHARA RSA params tag. */
#define SBI_TAG_SAH_RSA_PUBLIC_KEY               0x00000164  /**< SAHARA RSA public key tag. */
#define SBI_TAG_SAH_RSA_PRIVATE_KEY              0x00000165  /**< SAHARA RSA private key tag. */
#define SBI_TAG_SAH_RSA_PKCS1_V15_ENC_CTX        0x00000266  /**< SAHARA RSA PKCS1v15 encoding context tag. */
#define SBI_TAG_SAH_RSA_PKCS1_V15_DEC_CTX        0x00000267  /**< SAHARA RSA PKCS1v15 decoding context tag. */
#define SBI_TAG_SAH_PKCS1_V15_SIG_PAD_EXP_CTX    0x00000268  /**< SAHARA RSA PKCS1v15 sig pad expo context tag. */
#define SBI_TAG_SAH_PKCS1_V15_VER_PAD_EXP_CTX    0x00000269  /**< SAHARA RSA PKCS1v15 verify pad expo context tag. */
#define SBI_TAG_SAH_RSA_PKCS1_V15_SIGN_CTX       0x0000026a  /**< SAHARA RSA PKCS1v15 sign context tag. */
#define SBI_TAG_SAH_RSA_PKCS1_V15_VERIFY_CTX     0x0000026b  /**< SAHARA RSA PKCS1v15 verify context tag. */
#define SBI_TAG_SAH_IDLC_CONTEXT                 0x00001061  /**< SAHARA IDLC context tag. */
#define SBI_TAG_SAH_IDLC_PARAMS                  0x00001062  /**< SAHARA IDLC params tag. */
#define SBI_TAG_SAH_IDLC_PRIVATE_KEY             0x00001063  /**< SAHARA IDLC private key tag. */
#define SBI_TAG_SAH_IDLC_PUBLIC_KEY              0x00001064  /**< SAHARA IDLC public key tag. */

/** @} sbi_tag_sah */

/** @addtogroup sbi_tag_i300 Freescale i.300 tags
 * @{
 */

#define HU_TAG_I300                              0x00000060

/** @} */


/** @addtogroup sbi_tag_ss Store Server tags

@{ 
*/

#define SBI_TAG_SS                               0x00000070  /**< Store Server implementation tag. */

/** @} sbi_tag_ss */

/** @addtogroup rtti_tag_wtp WTP tags

@{ 
*/
#define HU_TAG_WTP                              0x00000080  /**< WTP implementation tag. */
#define HU_TAG_WTP_DES_PARAMS                   0x00003080  /**< WTP DES params Tag */
#define HU_TAG_WTP_DES_DES_KEY                  0x00003081  /**< WTP DES key Tag */
#define HU_TAG_WTP_DES_TDES_KEY                 0x00003082  /**< WTP TDES key Tag */
#define HU_TAG_WTP_DES_CONTEXT                  0x00003084  /**< WTP DES context Tag */
#define HU_TAG_WTP_AES_PARAMS                   0x00003280  /**< WTP AES params Tag */
#define HU_TAG_WTP_AES_KEY                      0x00003283  /**< WTP AES key Tag */
#define HU_TAG_WTP_AES_CONTEXT                  0x00003284  /**< WTP AES context Tag */
#define HU_TAG_WTP_SHA1_CONTEXT                 0x00004081  /**< WTP SHA1 hash context tag. */
#define HU_TAG_WTP_MD5_CONTEXT                  0x00004181  /**< WTP MD5 hash context tag. */
#define HU_TAG_WTP_IDLC_PARAMS                  0x00001082  /**< WTP IDLC params tag. */
#define HU_TAG_WTP_IDLC_PRIVATE_KEY             0x00001083  /**< WTP IDLC private key tag. */
#define HU_TAG_WTP_IDLC_PUBLIC_KEY              0x00001084  /**< WTP IDLC public key tag. */
#define HU_TAG_WTP_RSA_PARAMS                   0x00000183  /**< RSA params tag. */
#define HU_TAG_WTP_RSA_PUBLIC_KEY               0x00000184  /**< RSA public key tag. */
#define HU_TAG_WTP_RSA_PRIVATE_KEY              0x00000185  /**< RSA private key tag. */
#define HU_TAG_WTP_HMAC_SHA1_KEY                0x00004A88  /**< WTP HMAC SHA1 key Tag */
#define HU_TAG_WTP_HMAC_SHA1_CONTEXT            0x00004A81  /**< WTP HMAC SHA1 context Tag */
#define HU_TAG_WTP_HMAC_SHA1_V2_KEY             0x00004B88  /**< WTP HMAC SHA1  key Tag */
#define HU_TAG_WTP_HMAC_SHA1_V2_CONTEXT         0x00004B81  /**< WTP HMAC SHA1 context Tag */
#define HU_TAG_WTP_FIPS186_RNG_CONTEXT          0x00005001  /**< WTP RNG FIPS186 context Tag */
/** @} rtti_tag_wtp */

#define HU_TAG_SBGSE1           0x00000090  /**< SBGSE1 implementation tag. */
#define HU_TAG_SBGSE2           0x000000A0  /**< SBGSE2 implementation tag. */
#define HU_TAG_PQ               0x000000B0  /**< PowerQuicc implementation tag. */
#define HU_TAG_NSE              0x000000C0  /**< NSE implementation tag */
#define HU_TAG_OSSL             0x000000D0  /**< OPENSSL implementation tag */
#define HU_TAG_ES               0x000000E0  /**< Elliptic Semiconductor implementation tag */
#define HU_TAG_MX31             0x00000060  /**< Freescale MX31 adapter tag (re-use of SAHARA tag) */

#define HU_TAG_LKNL             0x001000F0  /**< Linux Kernel adapter tag */
#define HU_TAG_OMAPK            0x002000F0  /**< TI OMAP 1710 Kernel adapter tag */
#define HU_TAG_OMAPU            0x003000F0  /**< TI OMAP 1710 User Space adapter tag */

#define HU_TAG_CAPI             0x003000F0  /**< Capi adapter Tag. (Wrapper for wincrypt CSP RSA provider) */
#define HU_TAG_CAPI_RSA_PRIVATE_KEY             0x003001F5 /** CAPI RSA PRIVATE KEY TAG **/
#define HU_TAG_CAPI_RSA_PARAMS  0x003001F3

#define HU_TAG_RIM              0x004000F0  /**< RIM AES adapter tag */

/** @addtogroup rtti_tag_funcs Tag Query APIs

@{ 
*/

/** Retrieves the tag value from a parameter object.

@param[in]  params  Parameter object.

@return The tag value.
*/
extern
SB_EXPORT
sb_Tag
SB_CALLCONV
hu_ParamsTag( 
    sb_Params params 
);


/** Retrieves the tag value from a private key object.

@param[in]  privKey  Private key object.

@return The tag value.
*/

extern
SB_EXPORT
sb_Tag
SB_CALLCONV
hu_PrivateKeyTag(
    sb_PrivateKey privKey
);

/** Retrieves the tag value from a public key object.

@param[in]  pubKey  Public key object.

@return The tag value.
*/

extern
SB_EXPORT
sb_Tag
SB_CALLCONV
hu_PublicKeyTag(
    sb_PublicKey pubKey
);

/** Retrieves the tag value from a key object.

@param[in]  key  Key object.

@return The tag value.
*/

extern
SB_EXPORT
sb_Tag
SB_CALLCONV
hu_KeyTag(
    sb_Key key
);

/** Retrieves the tag value from a context object.

@param[in]  context  Context object.

@return The tag value.  
*/

extern
SB_EXPORT
sb_Tag
SB_CALLCONV
hu_ContextTag(
    sb_Context context
);


/** Retrieves the tag value from a Global Context for the specified algorithm.

@param[in]  ctx  Global Context
@param[in]  tag  A tag which specifies which algorithm the tag is being 
                 requested for. Currently, only <tt>HU_TAG_TYPE_AES</tt> is 
		 supported.

@return   The tag value. This will be <tt>0</tt> if the tag for the requested 
          algorithm could not be determined. This occurs when <tt>ctx</tt> is 
	  <tt>NULL</tt>, <tt>ctx</tt> has not had a provider registered, or the 
	  adapter being queried does not support RTTI. This function is only 
	  supported in SB Crypto-C 5.5 and onwards. <tt>HU_TAG_LIB(tag)</tt> 
	  can be used on the returned tag to extract the provider that is 
	  registered.
*/

extern
SB_EXPORT
sb_Tag
SB_CALLCONV
hu_GlobalContextTag(
    sb_GlobalCtx ctx,
    sb_Tag tag
);

/** @} sbi_tag_funcs */

#ifdef __cplusplus
}
#endif

#endif
