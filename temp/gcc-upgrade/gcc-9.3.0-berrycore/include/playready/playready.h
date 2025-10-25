/*
 * $QNXLicenseC:
 * Copyright 2007, QNX Software Systems. All Rights Reserved.
 *
 * This source code may contain confidential information of QNX Software
 * Systems (QSS) and its licensors.  Any use, reproduction, modification,
 * disclosure, distribution or transfer of this software, or any software
 * that includes or is based upon any of this code, is prohibited unless
 * expressly authorized by QSS by written agreement.  For more information
 * (including whether this source code file has been published) please
 * email licensing@qnx.com. $
*/

#ifndef __PLAYREADY_DRM_H__
#define __PLAYREADY_DRM_H__

#include <stdio.h>
#include <stdint.h>
#include <playready/playready_types.h>
#include <mmedia/media_output_type.h>

__BEGIN_DECLS

#define DrmResultWrapper( x ) DrmResult( x, __func__ )
API_PUBLIC DRM_RESULT_t DrmResult(DRM_LONG_t err, const char *func );

typedef enum pr_soap_action { SOAP_ACTION_GET_LICENSE = 0, SOAP_ACTION_ACK_LICENSE,} pr_soap_action_t;
typedef enum pr_license_protocol { LICENCE_UNKNOWNPROTOCOL=0, LICENSE_V2PROTOCOL, LICENSE_V3PROTOCOL } pr_license_protocol_t;
typedef enum pr_cipher { DRM_CIPHER_INVALID = 0, DRM_RC4_CIPHER = 1, DRM_AES_COUNTER_CIPHER = 2, DRM_DES_CIPHER = 3} pr_cipher_t;

/**
* Initialize the PlayReady DRM environment using an identifer
*
* @param hdl:   the returned DRM handle  on success
* @return DRM_SUCCESS if the call succeeds or an error code
*/
API_PUBLIC DRM_RESULT_t PlayReadyInitWithId( PlayReady_t **hdl, const DRM_BYTE_t *data, DRM_DWORD_t dsize );

/**
* Read irmss.dat file from ReadOnly FS.
*
* @param [pData] : [out] pointer to a buffer for irmss.dat file content
* @param [pDataLength]     : [in,out]  pointer to above buffer size (in bytes); return actual length of delivered
*
* @return DRM_SUCCESS if the call succeeds or an error
*/
API_PUBLIC DRM_RESULT_t PlayReadyReadIrmss( DRM_BYTE_t *pData, DRM_DWORD_t *pDataLength );

/**
 * Check right on the DRM session
 *
 * @param hdl:  a DRM handle return by the PlayReadyInit() function
 * @param data Pointer to the property-specific data
 * @param dsize Count of bytes in the property-specific data
 * @param udata User data that will be passed through to the callback function
 *
 * @return DRM_SUCCESS if the call succeeds or an error code
 */
API_PUBLIC DRM_RESULT_t PlayReadyCheckPlaybackRight( PlayReady_t *hdl, const DRM_BYTE_t *data, DRM_DWORD_t dsize, void *udata );

/**
 * Consume DRM right.
 *
 * @param hdl DRM handle that was returned from a successfull call to PlayReadyInit
 * @param udata User data that will be passed through to the callback function
 * @return DRM_SUCCESS if the call succeedsi or an error
 */
API_PUBLIC DRM_RESULT_t PlayReadyConsumeRights( PlayReady_t *hdl, const void *udata );

/**
 *  Retrieve the stream Encryption cipher type.
 *
 * @param hdl DRM handle that was returned from a successfull call to PlayReadyInit
 * @param buf: a pointer to the RM header object
 * @param bsize size of  buf
 * @param cipher_type the retrieved cipher type on success
 * @return DRM_SUCCESS if the call succeedsi or an error
 */
API_PUBLIC DRM_RESULT_t PlayReadyGetDrmCipherType( PlayReady_t *hdl, const DRM_BYTE_t *buf, DRM_DWORD_t bsize, DRM_DWORD_t *cipher_type );

/**
 * Decrypt "coctail" protected content .
 *
 * @param hdl DRM handle that was returned from a successfull call to PlayReadyInit
 * @param data Pointer to an array of encrypted bytes. This data is decrypted and returned in the same buffer.
 * @param dsize Count of bytes in data
 *
 * @return DRM_SUCCESS if the call succeeds or an error
 */
API_PUBLIC DRM_RESULT_t PlayReadyCocktailDecrypt( PlayReady_t *hdl, DRM_BYTE_t *data, DRM_DWORD_t dsize );

/**
 * Decrypt AES counter-mode protected content.
 *
 * @param hdl  DRM handle that was returned from a successfull call to PlayReadyInit
 * @param data Pointer to an array of encrypted bytes. This data is decrypted and returned in the same buffer.
 * @param dsize Count of bytes in data
 * @param sampleID sample ID for the current sample
 *
 * @return DRM_SUCCESS if the call succeeds or an error
 */
API_PUBLIC DRM_RESULT_t PlayReadyAesDecrypt( PlayReady_t *hdl, DRM_BYTE_t *data, DRM_DWORD_t dsize, DRM_UINT64_t sampleID );

/**
 * Decrypt AES counter-mode protected content, using explicit offsets.
 *
 * @param hdl  DRM handle that was returned from a successfull call to PlayReadyInit
 * @param data Pointer to an array of encrypted bytes. This data is decrypted and returned in the same buffer.
 * @param dsize Count of bytes in data
 * @param sampleID sample ID for the current sample
 * @param qwBlockOffset Block offset within the payload
 * @param bByteOffset Byte offset within the current block
 *
 * @return DRM_SUCCESS if the call succeeds or an error
 */
API_PUBLIC DRM_RESULT_t PlayReadyAesDecryptOffset( PlayReady_t *hdl, DRM_BYTE_t *data, DRM_DWORD_t dsize, DRM_UINT64_t sampleID, DRM_UINT64_t qwBlockOffset, DRM_BYTE_t bByteOffset );

/**
 * Get a response from a license server after submiting a license challenge
 *
 * @param hdl DRM handle that was returned from a successfull call to PlayReadyInit
 * @param surl :  license server url
 * @param action:  soap action to be taken. one of the following SOAP_ACTION_GET_LICENSE or SOAP_ACTION_ACK_LICENSE
 * @param challenge:  array of bytes used for the license challenge
 * @param chalenge_len: the chalenge length in bytes
 * @param response:  array of bytes constituing the challenge response, caller must free the memory after usage
 * @param response_len: the response length in bytes
 * @return DRM_SUCCESS if the call succeeds or an error
 */
API_PUBLIC DRM_RESULT_t PlayReadyLicenseGetChallengeResponse( PlayReady_t *hdl, DRM_BYTE_t *surl, pr_soap_action_t action, DRM_BYTE_t *challenge, DRM_DWORD_t chalenge_len, DRM_BYTE_t **response, DRM_DWORD_t *response_len );

/**
 * Process a license response, which results from posting a license challenge.
 *
 * @param hdl: DRM handle that was returned from a successfull call to PlayReadyInit
 * @param data: Pointer to an array of bytes containing the response from a license server
 * @param dsize: Count of bytes in the license response
 * @param lic_protocol: NULL or  a pointer to a DRM_DWORD type where the function can store the license protocol on success:
 *                      LICENCE_UNKNOWNPROTOCOL, LICENSE_V2PROTOCOL, or  LICENSE_V3PROTOCOL
 * @return DRM_SUCCESS if the call succeeds or an error
 */
API_PUBLIC DRM_RESULT_t PlayReadyLicenseProcessResponse( PlayReady_t *hdl, DRM_BYTE_t *data, DRM_DWORD_t dsize, DRM_DWORD_t *lic_protocol );


/**
 * Generate a license Acknowlegment response to be sent back to the licence server. (V3 licence protocol)
 *
 * @param hdl DRM handle that was returned from a successfull call to PlayReadyInit
 * @param ack  Pointer to pointer to an array of bytes containing the returned generated ackknowlegment response to be sent to the server
 * caller must free the memory when no longer needed
 * @param ask_len size of the returned ack bytes array.
 *
 * @return DRM_SUCCESS if the call succeeds or an error
 */
API_PUBLIC DRM_RESULT_t PlayReadyLicenseGenerateAck( PlayReady_t *hdl, DRM_BYTE_t **ack, DRM_DWORD_t *ack_len);

/**
 * Process a license Acknowlegment response sent by the license server to to be push to the local license store. (V3 licence protocol)
 *
 * @param hdl DRM handle that was returned from a successfull call to PlayReadyInit
 * @param response pointer to an array of bytes containing the server returned acknowledged response to be push to the license store.
 * @param rsize size of the response bytes array.
 *
 * @return DRM_SUCCESS if the call succeeds or an error
 */
API_PUBLIC DRM_RESULT_t PlayReadyLicenseProcessAckResponse( PlayReady_t *hdl, DRM_BYTE_t *response, DRM_DWORD_t rsize, DRM_RESULT_t *dr1);

/**
 * Generate a license challenge based on the previously set content ID.
 *
 * @param drmHandle DRM handle that was returned from a successfull call to PlayReadyDrmInit
 * @param rights An array of strings describing the requested rights for
 *               the content
 * @param rightsCount An integer giving the number of elements in each of
 *                    the previous array
 * @param pDomainId Pointer to a domain ID that is used by V3 license protocol. Some of its fields can be empty. It is ignored for V2 license protocol.
 * @param customData Pointer to a buffer that contains custom data to be sent to the server. It can be NULL
 * @param customDataLength Contains the size (number of characters) of the custom data.
 * @param silentURL Pointer to a buffer that contains the silent license acquisition URL that is parsed out from the content header.
                               If it is NULL the function returns an error and the size of the required buffer is stored in silentURLLength
 * @param silentURLLength Pointer to a variable that contains the size in characters of the silent license acquisition URL buffer during input and
                              receives the actual size in characters of the silent license acquisition URL during output.
 * @param nonSilentURL Pointer to a buffer that contains the nonsilent license acquisition URL that is parsed out from the content header.
                               If it is NULL, the function returns an error and the size of the required buffer is stored in nonSilentURLLength
 * @param nonSilentURLLength Pointer to a variable that contains the size in characters of the nonsilent license acquisition URL buffer during input and
                               receives the actual size in characters of the nonsilent license acquisition URL during output
 * @param challenge Pointer to a buffer to receive a generated challenge byte stream. If it is NULL, the function returns an error and
                               the size of the required buffer is stored in challengeLength
 * @param challengeLength Pointer to a variable that contains the size (in bytes) of the challenge buffer on input,
                               and receives the size (in bytes) of the challenge buffer on output.
 *
 * @return DRM_SUCCESS if the call succeeds
 * @return DRM_ERROR_MEMORY if the buffers passed for challenge is too small or
 *                                               not enough memory to perform the requested operation
 * @return DRM_ERROR_PARAM if the parameters are invalid
 */
API_PUBLIC DRM_RESULT_t PlayReadyLicenseGenerateChallenge( PlayReady_t *hdl,
                                              const DRM_CONST_STRING_t **rights,
                                              DRM_DWORD_t              rightsCount,
                                              const DRM_DOMAIN_ID_t    *pDomainId,
                                              DRM_BYTE_t               *customData,
                                              DRM_DWORD_t              customDataLength,
                                              DRM_BYTE_t               *silentURL,
                                              DRM_DWORD_t              *silentURLLength,
                                              DRM_BYTE_t               *nonSilentURL,
                                              DRM_DWORD_t              *nonSilentURLLength,
                                              DRM_BYTE_t               *challenge,
                                              DRM_DWORD_t              *challengeLength );

/**
 * Check the Output Protection level against current outpout ports in use
 *
 * @param hdl:  a DRM handle return by the PlayReadyInit() function
 * @param opl:  Pointer to a data structure describing the type of audio and video output in use,
 *              and the currently engaged content protection . (see mmedia/media_output_type.h)
 * @return DRM_SUCCESS if the call succeeds or an error code
 */
API_PUBLIC DRM_RESULT_t PlayReadyCheckCurrentOPL( PlayReady_t *hdl, MmOutputProtectionEventInfo_t *opl );

/**
 * Check the if the license associated with the current handle has an authorized Miracast export
 *
 * @param hdl:  a DRM handle return by the PlayReadyInit() function
 * @return DRM_SUCCESS if the call succeeds or an error code
 */
API_PUBLIC DRM_RESULT_t PlayReadyIsMiracastExportAuthorized( PlayReady_t *hdl );

/**
* Remove license.hds file from device
*
* @return DRM_SUCCESS if the call succeeds or an error code
*/
API_PUBLIC DRM_RESULT_t PlayReadyWipeLS(void);


/**
 * Data Structure to facilitate the export of functions and variables when the playready library
 * is loaded as a dll .
 * A single dlsym()  looking for this interface is sufficient to access the exposed API
 */
typedef struct
{
  const DRM_CONST_STRING_t *playback_rights;
  DRM_RESULT_t (*Init)(PlayReady_t **hdl);
  DRM_VOID_t   (*Uninit)(PlayReady_t *hdl);
  DRM_VOID_t   (*VerboseMode)( PlayReady_t *hdl, DRM_DWORD_t mode);
  DRM_RESULT_t (*CheckPlaybackRight)(PlayReady_t *hdl, const DRM_BYTE_t *data, DRM_DWORD_t dsize, void *udata);
  DRM_RESULT_t (*CheckCurrentOPL)( PlayReady_t *hdl, MmOutputProtectionEventInfo_t *opl );
  DRM_RESULT_t (*ConsumeRights)(PlayReady_t *hdl,const void *udata);
  DRM_RESULT_t (*GetDrmCipherType)(PlayReady_t *hdl, const DRM_BYTE_t *buf, DRM_DWORD_t bsize, DRM_DWORD_t *cipher_type);
  DRM_RESULT_t (*CocktailDecrypt)(PlayReady_t *hdl, DRM_BYTE_t *data, DRM_DWORD_t dsize);
  DRM_RESULT_t (*AesDecrypt)(PlayReady_t *hdl, DRM_BYTE_t *data, DRM_DWORD_t dsize, DRM_UINT64_t sampleID);
  DRM_RESULT_t (*ContentSetProperty)(PlayReady_t *hdl,const DRM_BYTE_t *data,DRM_DWORD_t dsize);
  DRM_RESULT_t (*DeviceAcquireLicence)(PlayReady_t *hdl,const DRM_CONST_STRING_t **rights,DRM_DWORD_t rightsCount,
                                       const DRM_DOMAIN_ID_t *pDomainId, DRM_BYTE_t *customData, DRM_DWORD_t customDataLength);
  DRM_RESULT_t (*AesDecryptOffset)(PlayReady_t *hdl, DRM_BYTE_t *data, DRM_DWORD_t dsize, DRM_UINT64_t sampleID,
                                    DRM_UINT64_t qwBlockOffset, DRM_BYTE_t bByteOffset);
  DRM_RESULT_t (*IsMiracastExportAuthorized)(PlayReady_t *hdl);
} MediaPlayReadyDrmInterface;

__END_DECLS
#endif



