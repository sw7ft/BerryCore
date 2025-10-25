/*!
 * @copyright
 * Copyright BlackBerry Limited, 2012-2014
 * BlackBerry Limited. All rights reserved.
 */

/**
 * @file nfc_se_transaction.h
 *
 * @brief Functions to parse and process transaction notifications from the
 *        secure elements (SEs) on the device.
 *
 *        Single applications will receive a transaction notification, even if
 *        there are multiple applications registered to listen for a given
 *        application identifier (AID).
 */

#ifndef NFC_SE_TRANSACTION_H_
#define NFC_SE_TRANSACTION_H_

#include "nfc/nfc_api.h"
#include "nfc/nfc_types.h"
#include <stdint.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @typedef struct nfc_se_transaction_t
 * A data type for the @c nfc_se_transaction_t structure.
 */
typedef struct nfc_se_transaction_t nfc_se_transaction_t;

/**
 * @brief Validate the groupId(GID) of the source of the transaction for authenticity
 * @details A transaction notification received by an application contains the GID
 *          of the source process. The application should call this function to verify
 *          that the source of the received notification is the NFC service, not
 *          another application. The GID of an authentic transaction notification
 *          is added by the operating system and cannot be spoofed.
 *
 * @param [in] sourceGid The provided GID to verify against the NFC services
 *
 * @return @c #NFC_RESULT_SUCCESS if the GID belongs to the NFC service; one
 *         of the following error codes otherwise:
 *         - @c #NFC_RESULT_SE_REQUEST_REJECTED The GID provided belongs to another
 *         application.  This transaction should be ignored.
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR The NFC service is
 *           unreachable and we cannot verify the GID.
 *         - @c #NFC_RESULT_ERROR Some other error has occurred.
 */
NFC_API nfc_result_t nfc_se_transaction_check_source_gid(int64_t sourceGid);

/**
 * @brief This function has been deprecated
 * @deprecated Deprecated in BlackBerry 10.2.2. Use @c nfc_se_parse_transactionV2() instead.
 * @details This function parses the passed-in transaction data and returns a
 *          handle to the @c transaction argument.
 *
 *          Passing a value of @c NULL as an argument is not supported.
 *
 * @param [out] transaction
 *              A pointer that is updated to a @c #nfc_se_transaction_t value.
 *              This pointer is set to @c NULL if an error occurs while
 *              parsing the transaction. The memory associated with the
 *              transaction must be freed by calling @c nfc_se_free_transaction().
 * @param [in] transactionData
 *             The transaction data to be parsed.
 *
 * @return @c #NFC_RESULT_SUCCESS if the transaction is parsed successfully;
 *         otherwise, one of the following values is returned:
 *         - @c #NFC_RESULT_INVALID_PARAMETER: The @c transaction or
 *           @c transactionData argument is @c NULL.
 *         - @c #NFC_RESULT_OUT_OF_MEMORY: There is insufficient memory to
 *           parse the transaction data.
 *         - @c #NFC_RESULT_ERROR: An error occurred when parsing the
 *           transaction data.
 */
NFC_API nfc_result_t nfc_se_parse_transaction(nfc_se_transaction_t **transaction,
                                              const char* transactionData);

/**
 * @brief Parse a transaction into a @c nfc_se_transaction_t*
 * @details This function parses the passed-in transaction data and returns a
 *          handle to the @c transaction argument.
 *
 *          Passing a value of @c NULL as an argument is not supported.
 *
 * @param [out] transaction
 *              A pointer that is updated to a @c #nfc_se_transaction_t value.
 *              This pointer is set to @c NULL if an error occurs while
 *              parsing the transaction. The memory associated with the
 *              transaction must be freed by calling @c nfc_se_free_transaction().
 * @param [in] transactionData
 *             The transaction data to be parsed.
 * @param [in] sourceGid
 *             The GID of the source process that sent the transaction notification.
 *             This function verifies the source; if it is not NFC service, an error
 *             is returned.
 *
 * @return @c #NFC_RESULT_SUCCESS if the transaction is parsed successfully;
 *         otherwise, one of the following values is returned:
 *         - @c #NFC_RESULT_INVALID_PARAMETER: The @c transaction or
 *           @c transactionData argument is @c NULL.
 *         - @c #NFC_RESULT_SE_REQUEST_REJECTED The GID provided belongs to another
 *           application.  This transaction should be ignored.
 *         - @c #NFC_RESULT_OUT_OF_MEMORY: There is insufficient memory to
 *           parse the transaction data.
 *         - @c #NFC_RESULT_ERROR: An error occurred when parsing the
 *           transaction data.
 */
NFC_API nfc_result_t nfc_se_parse_transactionV2(nfc_se_transaction_t **transaction,
                                              const char* transactionData,
                                              int64_t sourceGid);

/**
 * @brief Free a transaction allocated with the @c nfc_se_parse_transaction()
 *        function
 * @details Passing a value of @c NULL as an argument is not supported.
 *
 * @param [in] transaction
 *             The @c #nfc_se_transaction_t value that is to be released.
 *
 * @return None.
 */
NFC_API void nfc_se_free_transaction(nfc_se_transaction_t * transaction);

/**
 * @brief Retrieve the type of secure element the specified transaction occurs
 *        on.
 * @details  Passing a value of @c NULL as an argument is not supported.
 *
 * @param [in] transaction
 *             The transaction whose secure element type is being queried.
 * @return The type of secure element the specified transaction occurs on.
 */
NFC_API secure_element_id_type_t nfc_se_transaction_get_se_type(nfc_se_transaction_t* transaction);

/**
 * @brief Retrieve the protocol used to perform the transaction
 * @details This function returns a bit-mask of @c #technology_types_t values
 *          representing the type of protocols available to perform the
 *          transaction.
 *
 *          Passing a value of @c NULL as an argument is not supported.
 *
 * @b Note: The protocol used is not available to all types of transactions.
 *
 * @param [in] transaction
 *             The transaction whose protocol type is being queried.
 * @return The @c #technology_types_t type of protocol used to perform the
 *         specified transaction, or @c #TECHNOLOGY_TYPE_NONE if protocol
 *         information is unavailable.
 */
NFC_API unsigned int nfc_se_transaction_get_protocol(nfc_se_transaction_t* transaction);

/**
 * @brief Retrieve the number of application identifiers (AIDs) involved in the
 *        transaction
 * @details  Passing a value of @c NULL as an argument is not supported.
 *
 * @param [in] transaction
 *             The transaction whose number of AIDs is being queried.
 * @return The number of AIDs involved in the specified transaction.
 */
NFC_API unsigned int nfc_se_transaction_get_number_of_aids(nfc_se_transaction_t* transaction);

/**
 * @brief Retrieve an AID used in a transaction
 * @details  Passing a value of @c NULL as an argument is not supported.
 *
 * @param [in] transaction
 *             The transaction to retrieve AID from.
 * @param [in] index
 *             The index of the AID to retrieve. This is a zero-based index,
 *             therefore it must be lower than the result returned from @c
 *             nfc_se_transaction_get_number_of_aids().
 * @param [out] aid
 *              A pointer to be filled in with the AID data.
 * @param [out] aidLength
 *              A pointer to a @c size_t value, which is filled in with the
 *              number of octets in the AID.
 *
 * @return @c #NFC_RESULT_SUCCESS if the AID is successfully retrieved; otherwise
 *         @c #NFC_RESULT_INVALID_PARAMETER if @c transaction is @c NULL, or if
 *         index is out of bounds.
 */
NFC_API nfc_result_t nfc_se_transaction_get_aid(nfc_se_transaction_t* transaction,
                                                unsigned int index,
                                                const uint8_t **aid,
                                                size_t *aidLength);
/**
 * @brief Retrieve the length of the event data from the transaction
 * @details Passing a value of @c NULL as an argument is not supported. You can
 *          use the @c nfc_se_transaction_get_event_data() function to retrieve
 *          the event data.
 *
 * @param [in] transaction
 *             The transaction to retrieve the event data length from.
 * @return The length of the event data. A value of @c 0 is returned if no event
 *         data is available. Since event data is optional, the length may not
 *         be available for all transactions.
 */
NFC_API size_t nfc_se_transaction_get_event_data_length(nfc_se_transaction_t* transaction);

/**
 * @brief Retrieve a pointer to the event data from the transaction
 * @details Passing a value of @c NULL as an argument is not supported. You can
 *          determine the length of the data returned by calling
 *          @c nfc_se_transaction_get_event_data_length().
 *
 * @param [in] transaction The transaction to retrieve event data from.
 * @return A pointer to the event data; @c NULL if no event data is available.
 *         Event data is optional, so data may not be available for all
 *         transactions.
 */
NFC_API const uint8_t *nfc_se_transaction_get_event_data(nfc_se_transaction_t* transaction);

/**
 * @brief Bring the current application to the foreground
 * @details This is done by invoking the application in the foreground. The
 *          invocation is sent to the specified targetId (usually the same
 *          target used to receive transaction notifications) with the supplied
 *          data as the payload (usually the transaction).
 *
 * @return @c #NFC_RESULT_SUCCESS if the application is brought to the
 *         foreground, or if the application is already in the foreground; one
 *         of the following error codes otherwise:
 *         - @c #NFC_RESULT_SE_REQUEST_REJECTED The calling application has not
 *           received a transaction notification in the last 30 seconds.
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR The NFC service is
 *           unreachable.
 *         - @c #NFC_RESULT_ERROR Some other error has occurred.
 */
NFC_API nfc_result_t nfc_se_transaction_foreground_application();

#ifdef __cplusplus
}
#endif


#endif /* NFC_SE_TRANSACTION_H_ */
