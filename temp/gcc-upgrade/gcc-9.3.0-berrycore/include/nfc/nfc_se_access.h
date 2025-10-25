/*!
 * @copyright
 * Copyright BlackBerry Limited, 2012-2014
 * BlackBerry Limited. All rights reserved.
 */

/**
 * @file nfc_se_access.h
 *
 * @brief Functions to provide access to the secure elements of the device.
 *
 */


#include <stdint.h>
#include <stdbool.h>
#include "nfc/nfc_api.h"
#include "nfc/nfc_types.h"

#ifndef NFC_SE_ACCESS_H_
#define NFC_SE_ACCESS_H_

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Provide the number of readers available to the calling application
 *
 * @param [out] pNumberOfReaders
 *              The number of readers available to the calling application.
 *
 * @return @c #NFC_RESULT_SUCCESS if the readers are retrieved successfully,
 *         or @c #NFC_RESULT_INVALID_PARAMETER if a parameter is invalid.
 */
NFC_API nfc_result_t nfc_se_service_get_num_readers(uint32_t* pNumberOfReaders);

/**
 * @brief Provide a list of readers accessible to this application
 *
 * @param [out] phReaders
 *              The array of resulting reader handles.
 *
 * @param [in, out] pNumberOfReaders
 *                  Caller sends the number of elements in the phReader array.
 *                  The result is the number or reader handles within the
 *                  phReaders array.
 *
 * @return @c #NFC_RESULT_SUCCESS if the readers are retrieved successfully;
 *         or one of the following:
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: An attempt to connect to
 *           the NFC system has failed.
 *         - @c #NFC_RESULT_SE_INPUT_TOO_SHORT: There are not enough elements
 *           in the phReaders array.
 */
NFC_API nfc_result_t nfc_se_service_get_readers(uint32_t* phReaders,
                                                uint32_t* pNumberOfReaders);

/**
 * @brief Return the user-friendly name of this reader
 *
 * @param [in] hSEReader
 *             The handle to the reader whose name is to be provided.
 * @param [out] pName
 *              The character array to place the name.
 * @param [in, out] pLen
 *                  The length of the pName character array sent in, and the
 *                  actual length returned or the length returned in case of an
 *                  error.
 *
 * @return @c #NFC_RESULT_SUCCESS if the reader name is successfully retrieved;
 *         or one of the following:
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: An attempt to connect to
 *           the NFC system has failed.
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_SE_INVALID_HANDLE: The @c hSEReader is invalid.
 *         - @c #NFC_RESULT_SE_INPUT_TOO_SHORT: The pName argument is too
 *           short. The expected length is specified in the @c pLen argument.
 */
NFC_API nfc_result_t nfc_se_reader_get_name(uint32_t hSEReader,
                                            char* pName,
                                            uint32_t *pLen );


/**
 * @brief Connect to a secure element in a reader
 *
 * @param [in] hSEReader
 *             The handle to the reader.
 * @param [out] pSESession
 *              The resulting session to the specified reader.
 *
 * @return @c #NFC_RESULT_SUCCESS if the session is created successfully;
 *         or one of the following:
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: An attempt to connect to
 *           the NFC system has failed.
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_SE_INVALID_HANDLE: The @c hSEReader is invalid.
 */
NFC_API nfc_result_t nfc_se_reader_open_session(uint32_t hSEReader,
                                                uint32_t* pSESession);

/**
 * @brief Set the technology types (protocols) that are to be emulated
 * @details Use this function to enable or disable UICC secure element card
 *          emulation (UICC SE CE).
 *
 * @param [in] hSESession
 *             The handle to the open session.
 * @param [in] technologyTypes
 *             The technology types to emulate. This bit field must be
 *             constructed from the @c #technology_types_t constants. To enable
 *             card emulation, set this parameter to an appropriate technology
 *             type; to disable card emulation, set it to
 *             @c #TECHNOLOGY_TYPE_NONE.
 *
 * @return @c #NFC_RESULT_SUCCESS if the technology types are set successfully;
 *         or one of the following:
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: An attempt to connect to
 *           the NFC system failed.
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_SE_INVALID_HANDLE: The @c hSESession is invalid.
 *         - @c #NFC_RESULT_OPERATION_REJECTED: The UICC secure element is not
 *           the currently active secure element.  Call the
 *           @c nfc_se_set_uicc_active() function in order to set the UICC to
 *           be the active secure element.
 *         - @c #NFC_RESULT_RESOURCE_BUSY: The protocol cannot be set due to
 *           an ongoing RF session.
 */
NFC_API nfc_result_t nfc_se_reader_set_technology_types(uint32_t hSESession,
                                                        uint32_t technologyTypes);


/**
 * @brief Retrieve the technology types that are emulated for the NFC reader
 * @details Use this function to determine what protocols are emulated by
 *          the device.
 *
 * @param [in] hSESession
 *             The handle to the open session.
 * @param [in] batteryMode
 *             The battery mode to get the technology types for. Refer to
 *             @c #battery_mode_t for valid battery modes.
 * @param [out] pTechnologyTypes
 *              The technology types being emulated. This bit field is
 *              constructed from the @c #technology_types_t constants.
 *
 * @return @c #NFC_RESULT_SUCCESS if the technology types are set successfully;
 *         or one of the following:
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: An attempt to connect to
 *           the NFC system has failed.
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_SE_INVALID_HANDLE: The @c hSESession is invalid.
 */
NFC_API nfc_result_t nfc_se_reader_get_technology_types(uint32_t hSESession,
                                                        uint32_t batteryMode,
                                                        uint32_t* pTechnologyTypes);


/**
 * @brief Register an NFC application ID (AID) to be handled by the secure element
 *        associated with the session provided.
 * @details Use this function to register an AID to be handled by a particular
 *          secure element available on the device.
 *          In feature set 1, this function is not supported and returns
 *          @c #NFC_RESULT_UNSUPPORTED_API.
 *
 * @param [in] hSESession
 *             The handle to the open session.
 * @param [in] aid
 *             Pointer to the buffer containing the AID.
 * @param [in] aid_len
 *             Length of the AID.
 * @param [in] category
 *             The purpose of the application. This is used to help the user
 *             choose an application when an AID conflict occurs between two
 *             or more applications.
 * @param [in] invoke_target
 *             The target ID in a null-terminated string. When an NFC reader
 *             selects the registered AID, the NFC system includes this target
 *             ID in the invocation message it sends.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: The application is not
 *           connected to the NFC system.
 *         - @c #NFC_RESULT_OUT_OF_MEMORY: The system memory available for
 *           the NFC system to complete this operation is insufficient.
 *         - @c #NFC_RESULT_OPERATION_REJECTED: One of the following errors has occurred:
 *           .The application already started an UICC secure element.
 *           .The application already registered the same AID.
 *           .The AID is not valid for the specified category.
 *         - @c #NFC_RESULT_SE_INVALID_HANDLE: The @c hSESession is invalid.
 *         - @c #NFC_RESULT_UNSUPPORTED_API: This API is not supported in this
 *           feature set.
 */
NFC_API nfc_result_t nfc_se_register_aid(uint32_t hSESession,
                                         const uint8_t* aid,
                                         size_t aid_len,
                                         app_category_type_t category,
                                         const char* invoke_target);


/**
 * @brief Deregister an application ID (AID) from the secure element associated
 *        with the session provided.
 * @details Use this function to deregister an application ID (AID) from the
 *          secure element associated with the session. Note that calling this
 *          function does not remove the secure element's ability to handle the
 *          AID. It simply removes the specified AID from AID management (such
 *          as resolving AID conflicts and setting correct defaults) by the NFC
 *          service.
 *          In feature set 1, this function is not supported and returns
 *          @c #NFC_RESULT_UNSUPPORTED_API.
 *
 * @param [in] hSESession
 *             The handle to the open session.
 * @param [in] aid
 *             Pointer to the buffer containing the AID.
 * @param [in] aid_len
 *             Length of the AID.
 *
 * @return @c #NFC_RESULT_SUCCESS if the AID is deregistered successfully, or
 *         one of the following:
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: An attempt to connect to
 *           the NFC system has failed.
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_SE_INVALID_HANDLE: The @c hSESession is invalid.
 *         - @c #NFC_RESULT_OPERATION_REJECTED: This AID has not been registered
 *           by this application for SE.
 *         - @c #NFC_RESULT_UNSUPPORTED_API: This API is not supported in this
 *           feature set.
 */
NFC_API nfc_result_t nfc_se_unregister_aid(uint32_t hSESession,
                                           const uint8_t* aid,
                                           size_t aid_len);


/**
 * @brief Check if the application ID (AID) is registered with the secure
 *        element associated with the session provided.
 * @details An application uses this function to check if it has already registered
 *          the specified AID.
 *          In feature set 1, this function is not supported and returns
 *          @c #NFC_RESULT_UNSUPPORTED_API.
 *
 * @param [in] hSESession
 *             The handle to the open session.
 * @param [in] aid
 *             Pointer to the buffer containing the AID.
 * @param [in] aid_len
 *             Length of the AID.
 * @param [out] is_registered
 *             A pointer to a boolean value that is set when the function
 *             returns @c #NFC_RESULT_SUCCESS. This value is set to @c true if
 *             the calling application has already registered the AID, @c false
 *             otherwise.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: An attempt to connect to
 *           the NFC system has failed.
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_SE_INVALID_HANDLE: The @c hSESession is invalid.
 *         - @c #NFC_RESULT_UNSUPPORTED_API: This API is not supported in this
 *           feature set.
 */
NFC_API nfc_result_t nfc_se_is_aid_registered(uint32_t hSESession,
                                              const uint8_t* aid,
                                              size_t aid_len,
                                              bool* is_registered);


/**
 * @brief Close all the sessions opened on this reader
 *
 * @param [in] hSEReader
 *             The handle to the reader.
 *
 * @return @c #NFC_RESULT_SUCCESS if the sessions are successfully closed;
 *         or one of the following:
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: An attempt to connect to
 *           the NFC system has failed.
 *         - @c #NFC_RESULT_SE_INVALID_HANDLE: The @c hSEReader is invalid.
 */
NFC_API nfc_result_t nfc_se_reader_close_sessions(uint32_t hSEReader);


/**
 * @brief Report if the secure element is present for a specific reader
 *
 * @param [in] hSEReader
 *             The handle to the reader.
 * @param [out] pIsPresent
 *              @c true if the reader with handle @c hSEReader has a valid
 *              secure element, @c false otherwise. This value is valid only
 *              when this function returns @c #NFC_RESULT_SUCCESS.
 *
 * @return @c #NFC_RESULT_SUCCESS if the presence of a secure element for the
 *         selected reader is determined; or one of the following values
 *         is returned:
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: An attempt to connect to
 *           the NFC system has failed.
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_SE_INVALID_HANDLE: The @c hSEReader is invalid.
 */
NFC_API nfc_result_t nfc_se_reader_is_secure_element_present(uint32_t hSEReader,
                                                             bool* pIsPresent);

/**
 * The maximum buffer size of the Answer To Reset (ATR) as specified in
 * Section 8.2.1 of ISO/IEC 7816-3.
 */
#define ATR_BUFFER_SIZE 33

/**
 * The container for querying for the Answer To Reset (ATR).
 */
typedef uint8_t atrResponseBuffer[ATR_BUFFER_SIZE];

/**
 * @brief Retrieve the reader that provides this session
 *
 * @param [in] hSESession
 *             The handle to the reader.
 * @param [out] phSEReader
 *              The session this reader is bound to.
 *
 * @return @c #NFC_RESULT_SUCCESS if the session is retrieved successfully;
 *         or one of the following:
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: An attempt to connect to
 *           the NFC system has failed.
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_SE_INVALID_HANDLE: The @c hSESession is invalid.
 */
NFC_API nfc_result_t nfc_se_session_get_reader(uint32_t hSESession,
                                               uint32_t* phSEReader);

/**
 * @brief Retrieve an access to the basic channel
 *
 * @details Basic channels are defined in the ISO 7816-4 specification (the one
 *          that has number 0). Access to the basic channel is only available
 *          for certain secure elements.
 *
 * @param [in] hSESession
 *             The handle to the session.
 * @param [in] fcpResponseType
 *             The format of the File Control Parameter(FCP) information
 *             requested from the secure element. The value of this argument
 *             must be one of the constants defined by @c #fcp_type_t. Use @c
 *             OPEN_NO_FCP_INFO if you are not interested in the results.
 * @param [out] phSEChannel
 *              The channel created to the secure element.
 * @param [out] pnLengthOfResponseInBytes
 *              The length of the response data returned as a result of the
 *              open call. This argument is set to @c 0 if there is no data,
 *              @c -1 if the @c fctResponseType argument is unsupported by the
 *              reader on which the session has been opened, and @c NULL if @c
 *              OPEN_NO_FCP_INFO is provided to the @c fcpResponseType
 *              argument. Use the @c nfc_se_channel_get_transmit_data()
 *              function to read the data received prior to any APDU exchanges.
 *
 * @return @c #NFC_RESULT_SUCCESS if the session is retrieved successfully;
 *         or one of the following:
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: An attempt to connect to
 *           the NFC system has failed.
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_SE_INVALID_HANDLE: The @c hSESession is invalid.
 */
NFC_API nfc_result_t nfc_se_session_open_basic_channel(uint32_t hSESession,
                                                       fcp_type_t fcpResponseType,
                                                       uint32_t* phSEChannel,
                                                       int32_t* pnLengthOfResponseInBytes);


/**
 * @brief Create and obtain access to the logical channel
 * @details After access is obtained, a logical connection is created to
 *           an applet on the secure element. Logical channels are defined
 *           in the ISO 7816-4 specification.
 *
 * @param [in] hSESession
 *             The handle to the session.
 * @param [in] pAID
 *             The Application ID that the caller wants to open a channel with.
 * @param [in] nLengthOfAIDInBytes
 *              The length of the pAID argument.
 * @param [in] fcpResponseType
 *             The format of the FCP information requested from the Secure
 *             Element. The value of this argument must be one of the constants
 *             defined by @c #fcp_type_t. Use @c OPEN_NO_FCP_INFO if you are
 *             not interested in the results.
 * @param [out] phSEChannel
 *              The channel created to the secure element.
 * @param [out] pLengthOfResponseInBytes
 *              The length of the response data returned as a result of the
 *              open call. This argument is set to @c 0 if there is no data and
 *              @c -1 if the provided @c fctResponseType argument is
 *              unsupported by the reader which the session has been opened on.
 *              It may be @c NULL if @c OPEN_NO_FCP_INFO is supplied to the @c
 *              fcpResponseType argument. Use the @c
 *              nfc_se_channel_get_transmit_data() function to read the data
 *              received prior to any APDU exchanges.
 *
 * @return @c #NFC_RESULT_SUCCESS if the session is retrieved successfully;
 *         or one of the following:
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: An attempt to connect to
 *           the NFC system has failed.
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_SE_INVALID_HANDLE: The @c hSESession is invalid.
 *         - @c #NFC_RESULT_SE_OUT_OF_LOGICAL_CHANNELS: No logical channels are
 *           available, because all channels are in use.
 *         - @c #NFC_RESULT_SE_AID_NOT_FOUND: The applet with the specified
 *           Application ID (AID) cannot be found.
 *         - @c #NFC_RESULT_SE_REQUEST_REJECTED: The request is rejected by the
 *           Access Control files (ACF) or some other security mechanism.
 */
NFC_API nfc_result_t nfc_se_session_open_logical_channel(uint32_t hSESession,
                                                         const uint8_t* pAID,
                                                         size_t nLengthOfAIDInBytes,
                                                         fcp_type_t fcpResponseType,
                                                         uint32_t* phSEChannel,
                                                         int32_t* pLengthOfResponseInBytes);

/**
 * @brief Close the connection with the secure element
 *
 * @param [in] hSESession
 *             The handle to the session you like to close.
 *
 * @return @c #NFC_RESULT_SUCCESS if the session is retrieved successfully;
 *         or one of the following:
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: An attempt to connect to
 *           the NFC system has failed.
 *         - @c #NFC_RESULT_SE_INVALID_HANDLE: The @c hSESession is invalid.
 */
NFC_API nfc_result_t nfc_se_session_close_session(uint32_t hSESession);

/**
 * @brief Check if a session is closed.
 *
 * @param [in] hSESession
 *             The handle to the session of interest.
 * @param [out] pIsClosed
 *              @c true if the session is not open with the specified handle,
 *              @c false otherwise. This value is valid only when this function
 *              returns @c #NFC_RESULT_SUCCESS.
 *
 * @return @c #NFC_RESULT_SUCCESS if the platform is able to determine if
 *         the session is closed; or one of the following values is
 *         returned:
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: An attempt to connect to
 *           the NFC system has failed.
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 */
NFC_API nfc_result_t nfc_se_session_is_session_closed(uint32_t hSESession,
                                                      bool* pIsClosed);


/**
 * @brief Retrieve the Answer to Reset of this secure element
 *
 * @param [in] hSESession
 *             The handle to the session you of interest.
 * @param [out] pAtr
 *              ATR of the secure element the session is open for.
 * @param [in] nLengthOfAtrInBytes
 *             The length of the ATR buffer sent in.
 * @param [out] pLengthOfReturnedAtrInBytes
 *              The length of the ATR returned.
 *
 * @return @c #NFC_RESULT_SUCCESS if the session is retrieved successfully;
 *         or one of the following:
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: An attempt to connect to
 *           the NFC system has failed.
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_SE_INVALID_HANDLE: The @c hSESession is invalid.
 *         - @c #NFC_RESULT_SE_INPUT_TOO_SHORT: The @c nLengthOfAtrInBytes is
 *           shorter than the ATR length.  The required buffer length is returned
 *           in @c pLengthOfReturnedAtrInBytes if this error is returned.
 */
NFC_API nfc_result_t nfc_se_session_get_atr(uint32_t hSESession,
                                            uint8_t* pAtr,
                                            size_t nLengthOfAtrInBytes,
                                            size_t* pLengthOfReturnedAtrInBytes );

/**
 * @brief Close any channel opened on this session
 *
 * @param [in] hSESession
 *             The handle to the session the channels should be closed on.
 *
 * @return @c #NFC_RESULT_SUCCESS if the sessions are closed successfully,
 *         or one of the following:
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: An attempt to connect to
 *           the NFC system has failed.
 *         - @c #NFC_RESULT_SE_INVALID_HANDLE: The @c hSESession is invalid.
 */
NFC_API nfc_result_t nfc_se_session_close_channels(uint32_t hSESession);

/**
 * @brief Close this channel to the secure element
 *
 * @param [in] hSEchannel
 *             The handle to the channel to close.
 *
 * @return @c #NFC_RESULT_SUCCESS if the channel has been closed successfully,
 *         or one of the following:
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: An attempt to connect to
 *           the NFC system has failed.
 *         - @c #NFC_RESULT_SE_INVALID_HANDLE: The @c hSEchannel is invalid.
 */
NFC_API nfc_result_t nfc_se_channel_close_channel(uint32_t hSEchannel);

/**
 * @brief Indicate if the specified channel is the basic channel
 *
 * @param [in] hSEchannel
 *             The handle to the channel of interest.
 * @param [out] pIsBasicChannel
 *              @c true if the handle refers to a basic channel, @c false
 *              otherwise. This value is valid only when this function returns
 *              @c #NFC_RESULT_SUCCESS.
 * @return @c #NFC_RESULT_SUCCESS if the platform is able to determine if
 *         the specified channel is a basic channel; or one of the
 *         following:
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: An attempt to connect to
 *           the NFC system has failed.
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_SE_INVALID_HANDLE: The @c hSEchannel is invalid.
 */
NFC_API nfc_result_t nfc_se_channel_is_basic_channel(uint32_t hSEchannel,
                                                     bool* pIsBasicChannel);

/**
 * @brief Transmit an Application Data Unit (APDU) command (as per ISO 7816-4)
 *        to the secure element
 * @details The response length is returned. In order to retrieve the data the
 *          @c nfc_se_channel_get_transmit_data() function must be called. If a
 *          subsequent call on the same channel is made before a call to the @c
 *          nfc_se_channel_get_transmit_data() function, then the data of the
*           original exchange is lost.
 *
 * @param [in] hSEChannel
 *             The handle to the channel the APDU should be transmitted over.
 * @param [in] pSendAPDUBuffer
 *             The APDU to send.
 * @param [in] nLengthOfSendAPDUBufferInBytes
 *             The length of the pSendAPDUBuffer.
 * @param [out] pnLengthOfResponseInBytes
 *              The length of any response received from the command sent in.
 *              Data is retrieved using the
 *              @c nfc_se_channel_get_transmit_data() function.
 *
 * @return @c #NFC_RESULT_SUCCESS if the the APDU is transmitted successfully,
 *         or one of the following:
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: An attempt to connect to
 *           the NFC system has failed.
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_SE_INVALID_HANDLE: The @c hSEchannel is invalid.
 *         - @c #NFC_RESULT_SE_INVALID_APDU: The APDU provided is malformed or
 *           invalid.
 *         - @c #NFC_RESULT_SE_REQUEST_REJECTED: The request is rejected by the
 *           Access Control files (ACF) or some other security mechanism.
 */
NFC_API nfc_result_t nfc_se_channel_transmit_apdu(uint32_t hSEChannel,
                                                  const uint8_t* pSendAPDUBuffer,
                                                  size_t nLengthOfSendAPDUBufferInBytes,
                                                  size_t* pnLengthOfResponseInBytes);

/**
 * @brief Retrieve the result of the APDU exchange on a specific channel
 *
 * @details A call to this method must be made for every call to the @c
 *          nfc_se_channel_transmit_apdu() function. The amount of data
 *          returned is the lesser of the buffer size passed in and the data
 *          available on this channel. Any leftover data becomes inaccessible.
 *
 * @param [in] hSEChannel
 *             The handle to the channel the APDU exchange was completed on.
 * @param [out] pReceiveAPDUBuffer
 *              The resulting APDU from the previous APDU exchange.
 * @param [in, out] pnLengthOfReceiveAPDUBufferInBytes
 *                  The length of the expected data. If the data requested is
 *                  greater than the data buffered then this value is modified
 *                  to reflect the amount of data buffered. More data than
 *                  available is never returned.
 *
 * @return @c #NFC_RESULT_SUCCESS if the the APDU result has been retrieved;
 *         or one of the following:
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: An attempt to connect to
 *           the NFC system has failed.
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_SE_INVALID_HANDLE: The @c hSEchannel is invalid.
 */
NFC_API nfc_result_t nfc_se_channel_get_transmit_data(uint32_t hSEChannel,
                                                      uint8_t* pReceiveAPDUBuffer,
                                                      size_t* pnLengthOfReceiveAPDUBufferInBytes);

/**
 * @brief Retrieve the session that has opened this channel
 *
 * @param [in] hSEChannel
 *             The handle to the channel of interest.
 * @param [out] phSESession
 *              The handle to the Session that was used to open the channel.
 *
 * @return @c #NFC_RESULT_SUCCESS if the session is retrieved successfully;
 *         or one of the following:
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: An attempt to connect to
 *           the NFC system has failed.
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_SE_INVALID_HANDLE: The @c hSEchannel is invalid.
 */
NFC_API nfc_result_t nfc_se_channel_get_session(uint32_t hSEChannel,
                                                uint32_t* phSESession);


/**
 * @brief Determine if the specified channel is closed
 *
 * @param [in] hSEChannel
 *             The handle to the channel of interest.
 * @param [out] pIsClosed
 *              @c false if the handle refers to an open channel @c true
 *              otherwise. This value is valid only when this function returns
 *              @c #NFC_RESULT_SUCCESS.
 *
 * @return @c #NFC_RESULT_SUCCESS if the platform is able to determine if
 *         the specified channel is closed; or one of the following
 *         values is returned:
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: An attempt to connect to
 *           the NFC system has failed.
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_SE_INVALID_HANDLE: The @c hSEchannel is invalid.
 */
NFC_API nfc_result_t nfc_se_channel_is_closed(uint32_t hSEChannel,
                                              bool* pIsClosed);

/**
 * @brief Create and obtain access to the logical channel for a specific Secure
 *        Element
 * @details After access is obtained, a logical connection is created to an
 *          applet on the secure element. Logical channels are defined in the
 *          ISO 7816-4 specification.
 *
 * @param [in] secureElementType
 *             The type of secure element that the channel should be created
 *             for; either @c #UICC_SE_ID or @c #EMBEDDED_SE_ID.
 * @param [in] pAID
 *             The Application ID that the caller wants to open a channel with.
 * @param [in] nLengthOfAIDInBytes
 *             The length of the pAID argument.
 * @param [in] fcpResponseType
 *             The format of the FCP information requested from the Secure
 *             Element. The value of this argument must be one of the
 *             constants defined by @c #fcp_type_t. Use @c #OPEN_NO_FCP_INFO if
 *             you are not interested in the results.
 * @param [out] phSESession
 *              The session created to the secure element. The caller of this
 *              method is responsible for closing the session via the
 *              @c nfc_se_session_close_session() method.
 * @param [out] phSEChannel
 *              The channel created to the secure element.  The caller of this
 *              method is responsible for closing the channel via the
 *              @c nfc_se_channel_close_channel() method.
 * @param [out] pResponseLen
 *              The length of the response data returned as a result of the
 *              open call. This argument is set to @c 0 if there is no data and
 *              @c -1 if the provided @c fctResponseType argument is
 *              unsupported by the reader which the session is opened on. It
 *              may be @c NULL if @c #OPEN_NO_FCP_INFO is supplied to the @c
 *              fcpResponseType argument. Use the @c
 *              nfc_se_channel_get_transmit_data() function to read the data
 *              received prior to any APDU exchanges.
 *
 * @return @c #NFC_RESULT_SUCCESS if the session is retrieved successfully;
 *         or one of the following:
 *         - @c #NFC_RESULT_SE_NOT_PRESENT: The secure element specified is
 *           not available.
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: An attempt to connect to
 *           the NFC system has failed.
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_SE_OUT_OF_LOGICAL_CHANNELS: No logical channels are
 *           available, because all channels are in use.
 *         - @c #NFC_RESULT_SE_AID_NOT_FOUND: The applet with the specified
 *           application ID (AID) cannot be found.
 *         - @c #NFC_RESULT_SE_REQUEST_REJECTED: The request is rejected by the
 *           access control file (ACF) or some other security mechanism.
 */
NFC_API nfc_result_t nfc_se_open_logical_channel_direct(secure_element_id_type_t secureElementType,
                                                        const uint8_t* pAID,
                                                        size_t nLengthOfAIDInBytes,
                                                        fcp_type_t fcpResponseType,
                                                        uint32_t* phSESession,
                                                        uint32_t* phSEChannel,
                                                        int32_t* pResponseLen);

/**
 * @brief Obtain the type of the active secure element
 * @details The active secure element refers to the secure element that is
 *          currently emulating a technology type.
 *
 * @param [out] activeSEType
 *              The type of secure element that is currently active;
 *              either @c #UICC_SE_ID or @c #EMBEDDED_SE_ID.
 *
 * @return @c #NFC_RESULT_SUCCESS if the active secure element Type has been
 *         retrieved successfully; or one of the following values is
 *         returned:
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: An attempt to connect to
 *           the NFC system has failed.
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 */
NFC_API nfc_result_t nfc_se_get_active_se_type(secure_element_id_type_t *activeSEType);


/**
 * @brief Set the UICC as the active secure element
 * @details This function starts the process of setting the UICC as the active
 *          secure element. Calling this function may result in a dialog asking
 *          the end user to agree to this change.  The calling application will
 *          receive the result of the action through the
 *          @c #NFC_CE_SET_UICC_ACTIVE_SE_TYPE_EVENT bps event.
 *
 * @return @c #NFC_RESULT_SUCCESS if the process of setting the UICC as the
 *            active secure element has been initiated; otherwise the following
 *            value is returned:
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: An attempt to connect to
 *           the NFC system has failed.
 */
NFC_API nfc_result_t nfc_se_set_uicc_active();

/**
 * @brief Initiates the activation of the Single Wire Protocol(SWP) line for
 *        the UICC secure element
 * @details This function initiates the activation process of the SWP line for
 *          the UICC.  If your application uses the Contactless Registry
 *          Service(CRS) applet in order to hide and display a specific applet,
 *          then it should call this function to activate the SWP line before
 *          sending any APDUs to the CRS applet.
 *
 * @return @c #NFC_RESULT_SUCCESS if the SWP line activation has been
 *             triggered; otherwise the following value is returned:
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: An attempt to connect to
 *           the NFC system has failed.
 *         - @c #NFC_RESULT_OPERATION_REJECTED: SWP was disabled on this device
 *           by the carrier.
 */
NFC_API nfc_result_t nfc_se_enable_swp();

/**
 * @brief Determine whether the UICC secure element card emulation (UICC SE CE)
 *        is enabled
 * @details Use this function to determine if the UICC SE CE service
 *          is enabled.
 *
 * Card emulation is enabled by the system when the following conditions are true:
 *  - Card emulation is allowed by the carrier settings.
 *  - Card emulation is allowed by the IT policies.
 *  - NFC Connectivity is set to On on Settings > Network Connections > NFC.
 *  - The option "When locked or backlight is off" is selected on
 *    Settings > Network Connections > NFC. If the option isn't selected,
 *    then all of the following conditions must be true:
 *     - The device backlight is on.
 *     - The device screen is unlocked.
 *     - The device isn't in bedside mode.
 *
 * Card emulation in the "enabled" state doesn't mean that card emulation is currently
 * active. For card emulation to be active, you must ensure that an NFC-enabled UICC
 * is inserted in the device and configured correctly.
 *
 * @param [out] enabled
 *              @c true if the card emulation service is enabled, @c false otherwise.
 *
 * @return @c #NFC_RESULT_SUCCESS if the current state of the card emulation
 *         has been retrieved successfully; or one of the following values is
 *         returned:
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: An attempt to connect to
 *           the NFC system has failed.
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 */
NFC_API nfc_result_t nfc_se_is_uicc_ce_enabled(bool* enabled);

#ifdef __cplusplus
}
#endif


#endif /* NFC_SE_ACCESS_H_ */
