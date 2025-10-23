/*!
 * @copyright
 * Copyright BlackBerry Limited, 2012-2014
 * BlackBerry Limited. All rights reserved.
 */

/**
 * @file nfc_ndef.h
 *
 * This file provides functions for Near Field Communication (NFC) Data Exchange
 * Format (NDEF).
 *
 * For complete specifications, go to the NFC Forum Specifications
 * page at http://www.nfc-forum.org/specs/.
 */

#include <sys/types.h>
#include <stdbool.h>
#include <stdint.h>
#include "nfc/nfc_api.h"
#include "nfc/nfc_types.h"

#ifndef NFC_NDEF_H_
#define NFC_NDEF_H_

__BEGIN_DECLS

/**
 * A structure that represents an NDEF (NFC Data Exchange Format)
 * data message that contains references to one or more NDEF records
 * (@c struct @c nfc_ndef_message_t).
 */
struct nfc_ndef_message_t;

/**
 * @typedef struct nfc_ndef_message_t
 * A type definition of the @c nfc_ndef_message_t structure.
 */
typedef struct nfc_ndef_message_t nfc_ndef_message_t;

/**
 * A structure that represents a logical NFC Data Exchange Format (NFC) record.
 * The NDEF record contains:
 * - 3-bit TNF (Type Name Format) field, which indicates how to interpret
 *   the type field.
 * - Variable length type, which describes the record format.
 * - Variable length ID, which is a unique identifier for the NDEF record.
 * - Variable length payload, which is the actual data payload.
 */
struct nfc_ndef_record_t;

/**
 * @typedef struct nfc_ndef_record_t
 * A type definition of the @c struct @c nfc_ndef_record_t structure.
 */
typedef struct nfc_ndef_record_t nfc_ndef_record_t;

/**
 * @brief This enumeration specifies the type of the unicode encoding used
 *        for strings
 */
typedef enum {
   /**
    * UTF-8 (UCS Transformation Format - 8-bit).
    */
    UTF_8 = 1,
   /**
    * UTF-16 (UCS Transformation Format - 16-bit).
    */
    UTF_16 = 2
} nfc_ndef_rtd_encoding_t;

/*****************************************************************************
 *                      NDEF record retrieval functions                      *
 *****************************************************************************/

/**
 * @brief Retrieve the number of NDEF records found in an NDEF message
 * @details This function gets the number of NDEF records in NDEF message.
 *
 * @param msg The NDEF message retrieved from the NDEF read.
 * @param count The number of NDEF records found.
 *
 * @return @c #NFC_RESULT_SUCCESS, or @c #NFC_RESULT_INVALID_PARAMETER
 *         to indicate an invalid argument.
 */
NFC_API nfc_result_t nfc_get_ndef_record_count(const nfc_ndef_message_t *msg,
                                               unsigned int* count);

/**
 * @brief Get an NDEF record from an NDEF message
 * @details This function gets an NDEF record found in an NDEF message.
 *          Ownership of the memory associated with the returned NDEF record
 *          remains with the NDEF message.
 *
 * @param msg The NDEF message retrieved from the NDEF read.
 * @param index The index of the record required from the NDEF message.
 * @param rec The returned NDEF record.
 *
 * @return @c #NFC_RESULT_SUCCESS, or @c #NFC_RESULT_INVALID_PARAMETER
 *         to indicate an invalid argument.
 */
NFC_API nfc_result_t nfc_get_ndef_record(const nfc_ndef_message_t *msg,
                                         unsigned int index,
                                         nfc_ndef_record_t **rec);

/**
 * @brief Add a NDEF record to an NDEF message
 * @details This function adds an NDEF record to an NDEF message. If this
 *          function does not return @c #NFC_RESULT_SUCCESS, the ownership for
 *          the memory associated with @c rec remains with the application, and
 *          should be cleaned up via @c nfc_delete_ndef_record(). Otherwise, the
 *          memory associated with @c rec is subsequently owned by @c msg. In
 *          this case, if @c msg is deleted via @c nfc_delete_ndef_message()
 *          with its parameter @c delete_records set to @c false, @c rec should
 *          not be cleaned up manually by the application.
 *
 * @param msg The NDEF message to add the NDEF record to.
 * @param rec The NDEF record to add.
 *
 * @return @c #NFC_RESULT_SUCCESS, or @c #NFC_RESULT_INVALID_PARAMETER
 *         to indicate an invalid argument.
 */
NFC_API nfc_result_t nfc_add_ndef_record(nfc_ndef_message_t* msg,
                                         const nfc_ndef_record_t* rec);

/*****************************************************************************
 *                        NDEF message creation                              *
 *****************************************************************************/

/**
 * @brief Create an empty NDEF message
 * @details This function creates an empty NDEF message.
 *
 * @param msg The created NDEF message.
 *
 * @return @c #NFC_RESULT_SUCCESS, or @c #NFC_RESULT_INVALID_PARAMETER
 *         to indicate an invalid argument.
 */
NFC_API nfc_result_t nfc_create_ndef_message(nfc_ndef_message_t** msg);

/**
 * @brief Create an NDEF message from a byte array.
 * @details This function creates an NDEF message from a byte array.
 *
 * @param bytes The NDEF message byte array.
 * @param byte_length The byte length of the byte array.
 * @param msg The returned NDEF message. This message must be disposed of by
 *            calling @c nfc_delete_ndef_message() when no no longer required.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_BAD_NDEF_FORMAT: The byte array does not contain a
 *           valid NDEF record.
 */
NFC_API nfc_result_t nfc_create_ndef_message_from_bytes(const uchar_t* bytes,
                                                        size_t byte_length,
                                                        nfc_ndef_message_t** msg);

/**
 * @brief Delete an NDEF message
 * @details This function deletes an NDEF message that is no longer required.
 *
 * @param msg The NDEF message to delete.
 * @param delete_records If @c true, the function will delete and free the
 *                       memory associated with the NDEF records stored
 *                       inside the NDEF message. If @c false, the application
 *                       must make a call to @c nfc_delete_ndef_record() for
 *                       each NDEF record in this NDEF message to avoid a
 *                       memory leak.
 *
 * @return @c #NFC_RESULT_SUCCESS, or @c #NFC_RESULT_INVALID_PARAMETER
 *         to indicate an invalid argument.
 */
NFC_API nfc_result_t nfc_delete_ndef_message(nfc_ndef_message_t* msg,
                                             bool delete_records);

/*****************************************************************************
 *                      NDEF message retrieval functions                     *
 *****************************************************************************/

/**
 * @brief Return the serialized length of a NDEF message
 * @details This function returns the length in bytes of all records contained
 *          inside an NDEF message.
 *
 * @param msg The NDEF message to retrieve the length of.
 * @param byte_length The returned byte length of the message.
 *
 * @return @c #NFC_RESULT_SUCCESS, or @c #NFC_RESULT_INVALID_PARAMETER
 *         to indicate an invalid argument.
 */
NFC_API nfc_result_t nfc_get_ndef_message_byte_length(const nfc_ndef_message_t *msg,
                                                      size_t* byte_length);

/**
 * @brief Return the serialized data of NDEF message
 * @details This function returns the data bytes of all records contained inside
 *          an NDEF message.
 *
 * @param msg The NDEF message to retrieve the data from.
 * @param data A pointer to a pre-allocated array to return the data bytes of
 *             the message. This array must be at least equal to the
 *             length returned by the @c nfc_get_ndef_message_byte_length()
 *             function; otherwise, a call to this function will generate
 *             undefined behavior.
 *
 * @return @c #NFC_RESULT_SUCCESS, or @c #NFC_RESULT_INVALID_PARAMETER
 *         to indicate an invalid argument.
 */
NFC_API nfc_result_t nfc_get_ndef_message_bytes(const nfc_ndef_message_t *msg,
                                                uchar_t* data);

/*****************************************************************************
 *                        NDEF record creation                               *
 *****************************************************************************/

/**
 * @brief Create an NDEF record
 * @details This function creates an NDEF record. The parameters passed into
 *          this function must be valid according to the NFC Forum "NFC Data
 *          Exchange Format (NDEF) Technical Specification".
 *
 * @param tnf NDEF Type Name Format.
 * @param recordtype The record or mime type associated with the TNF.
 * @param payload The NDEF record's payload.
 * @param payload_length The byte length of the payload.
 * @param id Must be @c NULL or an empty string for record with @c tnf
 *        @c #NDEF_TNF_UNCHANGED, otherwise optional.
 * @param rec The returned NDEF record. Application must delete this record
 *        using @c nfc_delete_ndef_record() when no longer in use.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_OUT_OF_MEMORY: The system memory available for
 *           the NFC system to complete this operation is insufficient.
 */
NFC_API nfc_result_t nfc_create_ndef_record(tnf_type_t tnf,
                                            const char* recordtype,
                                            const uchar_t* payload,
                                            size_t payload_length,
                                            const char* id,
                                            nfc_ndef_record_t** rec);

/**
 * @brief Delete an NDEF record
 * @details This function deletes a NDEF record that is no longer required.
 *          Do not delete an NDEF record owned by an NDEF message unless you
 *          delete all records of that message.
 *          Once you have deleted all NDEF records stored in an NDEF message
 *          destroy the message by setting the parameter @c delete_records to
 *          @c false.
 *
 * @param rec The NDEF record to delete.
 *
 * @return @c #NFC_RESULT_SUCCESS, or @c #NFC_RESULT_INVALID_PARAMETER
 *         to indicate an invalid argument.
 */
NFC_API nfc_result_t nfc_delete_ndef_record(nfc_ndef_record_t* rec);

/*****************************************************************************
 *                        NDEF record attributes                             *
 *****************************************************************************/

/**
 * @brief Retrieve the record type of a NDEF record
 * @details This function returns the record type associated with the NDEF
 *          record. The record type is returned as is and may not conform to
 *          the NDEF specification.
 *
 * @param rec The NDEF record.
 * @param record_type The returned record type.
 *
 * @return @c #NFC_RESULT_SUCCESS, or @c #NFC_RESULT_INVALID_PARAMETER
 *         to indicate an invalid argument.
 */
NFC_API nfc_result_t nfc_get_ndef_record_type(const nfc_ndef_record_t* rec,
                                              char** record_type);

/**
 * @brief Retrieve the record id of an NDEF record
 * @details This function returns the record ID associated with the NDEF record.
 *          The record ID is returned as is and may not be a valid URI that
 *          conforms to RFC 3986.
 *
 * @param rec The NDEF record.
 * @param id The returned record ID.
 *
 * @return @c #NFC_RESULT_SUCCESS, or @c #NFC_RESULT_INVALID_PARAMETER
 *         to indicate an invalid argument.
 */
NFC_API nfc_result_t nfc_get_ndef_record_id(const nfc_ndef_record_t* rec,
                                            char** id);

/**
 * @brief Get the TNF of an NDEF record
 * @details This function returns the type name format associated with the NDEF
 *          record.
 *
 * @param rec The NDEF record.
 * @param tnf The returned type name format.
 *
 * @return @c #NFC_RESULT_SUCCESS, or @c #NFC_RESULT_INVALID_PARAMETER
 *         to indicate an invalid argument.
 */
NFC_API nfc_result_t nfc_get_ndef_record_tnf(const nfc_ndef_record_t* rec,
                                             tnf_type_t* tnf);

/**
 * @brief Get the payload of a NDEF record
 * @details This function returns the payload associated with the NDEF record.
 *
 * @param rec The NDEF record.
 * @param payload The returned payload.
 * @param payload_length The returned payload length.
 *
 * @return @c #NFC_RESULT_SUCCESS, or @c #NFC_RESULT_INVALID_PARAMETER
 *         to indicate an invalid argument.
 */
NFC_API nfc_result_t nfc_get_ndef_record_payload(const nfc_ndef_record_t* rec,
                                                 uchar_t** payload,
                                                 size_t* payload_length);


/*****************************************************************************
 *                          URI Record functions                             *
 *****************************************************************************/
/**
 * @brief Create an NFC Forum Well-known URI NDEF record
 * @details This function creates an NFC Forum Well-known URI NDEF record.
 *
 * @param utf8_uri The uri in UTF-8.
 * @param rec The returned URI NDEF record.
 *
 * @return @c #NFC_RESULT_SUCCESS, or @c #NFC_RESULT_INVALID_PARAMETER to
 *         indicate an invalid argument.
 */
NFC_API nfc_result_t nfc_create_uri_record(const char* utf8_uri,
                                           nfc_ndef_record_t** rec);

/**
 * @brief Return the fully qualified URI string from an uri NDEF record
 * @details This function returns the fully qualified URI string from an uri
 *          NDEF record.
 *
 * @param rec The URI NDEF record. Chunked NDEF records are not supported.
 * @param utf8_uri The returned allocated null-terminated fully qualified uri in
 *                 UTF-8. This string must be de-allocated by calling the
 *                 @c free() function.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid, or the
 *           provided NDEF record is chunked.
 *         - @c #NFC_RESULT_OUT_OF_MEMORY: The system memory available for
 *           the NFC system to complete this operation is insufficient.
 */
NFC_API nfc_result_t nfc_get_rtd_uri(const nfc_ndef_record_t* rec,
                                     char** utf8_uri);

/*****************************************************************************
 *                          Text functions                                   *
 *****************************************************************************/

/**
 * @brief Create an NFC Forum Well-Known Text NDEF record
 * @details This function creates an NFC Forum Well-Known Text NDEF record.
 *
 * @param utf8_string The text in UTF-8.
 * @param language The ISO/IANA locale code.
 * @param rec The returned Text NDEF record
 *
 * @return @c #NFC_RESULT_SUCCESS, or @c #NFC_RESULT_INVALID_PARAMETER
 *         to indicate an invalid argument.
 */
NFC_API nfc_result_t nfc_create_text_record(const char* utf8_string,
                                            const char* language,
                                            nfc_ndef_record_t** rec);

/**
 * @brief Return the string encoded in a text NDEF record
 * @details This function returns the text string encoded in a text NDEF record.
 *
 * @param rec The text NDEF record. Chunked NDEF records are not supported.
 * @param text The returned allocated null-terminated text string in either
 *             UTF-8 or UTF-16, indicated by the text_encoding argument. This
 *             string must be de-allocated by calling the @c free() function.
 * @param language A pointer to an allocated NULL-terminated two or five byte
 *                 ISO/IANA locale code. This string must be deallocated by
 *                 calling the free() function.
 * @param text_encoding A pointer to the encoded text. The text is encoded in
 *                      UTF-8 or UTF-16.
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid, or the
 *           provided NDEF record is chunked.
 *         - @c #NFC_RESULT_OUT_OF_MEMORY: The system memory available for
 *           the NFC system to complete this operation is insufficient.
 */
NFC_API nfc_result_t nfc_get_rtd_text(const nfc_ndef_record_t* rec,
                                      char** text,
                                      char** language,
                                      nfc_ndef_rtd_encoding_t* text_encoding);

/*****************************************************************************
 *                          SmartPoster Record functions                     *
 *****************************************************************************/

/**
 * @brief Validate if a smart poster record is consistent with the specification.
 * @details This function reviews the data embedded inside a smart poster
 *          NDEF record and verifies that the record is compliant with the NFC
 *          Forum specification for smart poster records.
 *
 * @param sp_rec The smart poster NDEF record to check
 * @return @c #NFC_RESULT_SUCCESS, otherwise @c NFC_RESULT_INVALID_PARAMETER
 *         to indicate that the record is not a valid smart poster record.
 */
NFC_API nfc_result_t nfc_validate_sp(nfc_ndef_record_t* sp_rec);

/**
 * @brief Create an NFC Forum Well-Known SmartPoster NDEF record
 * @details This function creates an NFC Forum Well-Known SmartPoster NDEF
 *          record.
 *
 * @param utf8_uri The UTF-8 encoded text. The URI will be set for the
 *                 mandatory URI record of a SmartPoster NDEF record.
 * @param rec The returned SmartPoster NDEF record.
 *
 * @return @c #NFC_RESULT_SUCCESS, or @c #NFC_RESULT_INVALID_PARAMETER
 *         to indicate an invalid argument.
 */
NFC_API nfc_result_t nfc_create_sp_record(const char* utf8_uri,
                                          nfc_ndef_record_t** rec);

/**
 * @brief Return the text and language set inside a smart poster title record
 * @details This function returns, if available, the data associated with the
 *          requested title record embedded inside the smart poster NDEF record
 *          payload.
 *
 * @param sp_rec The smart poster record containing the embedded title record
 *               in its payload. Chunked NDEF records are not supported.
 * @param req_lang The full or partial language to search for. The match
 *                 compares all available title records languages with the
 *                 length of the language string specified. For example, a
 *                 search on "en" will match either "en" or "en-US". The current
 *                 locale is used when this argument is set to @c NULL.
 * @param utf_title The returned allocated null-terminated title string encoded
 *                  in either UTF-8 or UTF-16 format. This string must be
 *                  deallocated by calling the @c free() function.
 * @param found_lang The returned allocated null-terminated two or five byte
 *                   language locale code. This string must be deallocated by
 *                   calling the @c free() function.
 * @param title_encoding A pointer to the encoding used for the @c title
 *                       argument.
 * @param return_any A flag that specifies whether to return the first title
 *                   record when no matches are found. When set to @c true,
 *                   the first title record that is found is returned when no
 *                   matches are found. When set to @c false, no value is
 *                   returned.
 *
 * @return @c #NFC_RESULT_SUCCESS; otherwise @c #NFC_RESULT_INVALID_PARAMETER
 *         to indicate that a parameter is invalid, or that the provided NDEF
 *         record is chunked.
 */
NFC_API nfc_result_t nfc_get_sp_title(const nfc_ndef_record_t* sp_rec,
                                      const char* req_lang,
                                      char** utf_title,
                                      char** found_lang,
                                      nfc_ndef_rtd_encoding_t* title_encoding,
                                      bool return_any);

/**
 * @brief Return the URI set inside a smart poster URI record
 * @details This function returns, if available, the data associated with the
 *          requested URI record embedded inside the smart poster NDEF record
 *          payload.
 *
 * @param sp_rec The smart poster record containing the embedded URI record
 *               in its payload. Chunked NDEF records are not supported.
 * @param utf8_uri The returned allocated null-terminated fully qualified URI
 *                 in UTF-8. This string must be de-allocated by calling the
 *                 @c free() function.
 *
 * @return @c #NFC_RESULT_SUCCESS, otherwise @c #NFC_RESULT_INVALID_PARAMETER
 *         to indicate that a parameter is invalid, or that the provided NDEF
 *         record is chunked.
 */
NFC_API nfc_result_t nfc_get_sp_uri(const nfc_ndef_record_t* sp_rec,
                                    char** utf8_uri);

/**
 * @brief Retrieve the value set inside a smart poster action record
 * @details This function returns, if available, the data associated with the
 *          requested action record embedded inside the smart poster NDEF record
 *          payload.
 *
 * @param sp_rec The smart poster record containing the embedded action record
 *               in its payload. Chunked NDEF records are not supported.
 * @param value The returned value byte associated with the action record.
 *
 * @return @c #NFC_RESULT_SUCCESS, otherwise @c #NFC_RESULT_INVALID_PARAMETER
 *         to indicate that a parameter is invalid, or that the provided NDEF
 *         record is chunked.
 */
NFC_API nfc_result_t nfc_get_sp_action(const nfc_ndef_record_t* sp_rec,
                                       uchar_t* value);

/**
 * @brief Retrieve the data associated with a specific smart poster media or
 *        icon record
 * @details This function returns, if available, the data associated with the
 *          requested media record embedded inside the smart poster NDEF record
 *          payload.
 *
 * @param sp_rec The smart poster record containing the embedded media record in
 *               its payload. Chunked NDEF records are not supported.
 * @param index The index of the record found from 0 to the value from @c
 *              nfc_get_sp_media_count() minus 1. Values outside this range
 *              returns @c #NFC_RESULT_INVALID_PARAMETER.
 * @param mime_type The returned allocated null-terminated mime type. This
 * string must be de-allocated by calling @c free().
 * @param data The returned allocated media data. This string must be
 *             de-allocated by calling the @c free() function.
 * @param data_length The length of the data buffer.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid, or the
 *           provided NDEF record is chunked.
 *         - @c #NFC_RESULT_OUT_OF_MEMORY: The system memory available for
 *           the NFC system to complete this operation is insufficient.
 */
NFC_API nfc_result_t nfc_get_sp_media_data(const nfc_ndef_record_t* sp_rec,
                                           unsigned int index,
                                           char** mime_type,
                                           uchar_t** data,
                                           size_t* data_length);

/**
 * @brief Return the number of media records stored inside a smart poster record
 * @details This function returns, if available, the number of media records
 *          embedded inside the smart poster NDEF record payload.
 *
 * @param sp_rec The smart poster record containing the embedded media records
 *               in its payload. Chunked NDEF records are not supported.
 * @param count The number of media records.
 *
 * @return @c #NFC_RESULT_SUCCESS, otherwise @c #NFC_RESULT_INVALID_PARAMETER
 *         to indicate that a parameter is invalid, or that the provided NDEF
 *         record is chunked.
 */
NFC_API nfc_result_t nfc_get_sp_media_count(const nfc_ndef_record_t* sp_rec,
                                            unsigned int* count);

/**
 * @brief Retrieve the size data inside a smart poster title record
 * @details This function returns, if available, the size of the data embedded
 *          inside the smart poster NDEF record payload.
 *
 * @param sp_rec The smart poster record containing the embedded size record in
 *               its payload. Chunked NDEF records are not supported.
 * @param size A pointer to the size of the data inside a smart poster title
 *             record.
 *
 * @return @c #NFC_RESULT_SUCCESS, otherwise @c #NFC_RESULT_INVALID_PARAMETER
 *         to indicate that a parameter is invalid, or that the provided NDEF
 *         record is chunked.
 */
NFC_API nfc_result_t nfc_get_sp_size(const nfc_ndef_record_t* sp_rec,
                                     uint32_t* size);

/**
 * @brief Retrieve the type that is set inside a smart poster title record
 * @details This function returns, if available, the type of the data embedded
 *          inside the smart poster NDEF record payload.
 *
 * @param sp_rec The smart poster record containing the embedded type record in
 *               its payload. Chunked NDEF records are not supported.
 * @param type A pointer to the allocated type for the data. This string must be
 *             de-allocated by calling the @c free() function.
 *
 * @return @c #NFC_RESULT_SUCCESS, otherwise @c #NFC_RESULT_INVALID_PARAMETER
 *         to indicate that a parameter is invalid, or that the provided NDEF
 *         record is chunked.
 */
NFC_API nfc_result_t nfc_get_sp_type(const nfc_ndef_record_t* sp_rec,
                                     char** type);

/**
 * @brief Add a smart poster title record to a smart poster NDEF record
 * @details This function adds the data associated with a title record to a
 *          smart poster NDEF record payload.
 *
 * @param sp_rec The smart poster NDEF record to add the title record to its
 *               payload. Chunked NDEF records are not supported.
 * @param lang The ISO/IANA language code of the title string. If the selected
 *             language has already been added to the payload, then function
 *             returns @c #NFC_RESULT_INVALID_PARAMETER.
 * @param utf8_string The null-terminated title string in UTF-8.
 *
 * @return @c #NFC_RESULT_SUCCESS, otherwise @c #NFC_RESULT_INVALID_PARAMETER
 *         to indicate that a parameter is invalid, or that the provided NDEF
 *         record is chunked.
 */
NFC_API nfc_result_t nfc_add_sp_title(nfc_ndef_record_t* sp_rec,
                                      const char* lang,
                                      const char* utf8_string);

/**
 * @brief Set the mandatory smart poster URI record in a smart poster NDEF
 *        record
 * @details This function sets the data associated with a URI record inside the
 *          smart poster NDEF record payload. Without a URI record, a smart
 *          poster record is considered invalid. This function must not be
 *          called more than once on the same NDEF record.
 *
 * @param sp_rec The smart poster NDEF record to add the URI record to its
 *               payload. Chunked NDEF records are not supported.
 * @param utf8_uri The null-terminated fully qualified URI in UTF-8.
 *
 * @return @c #NFC_RESULT_SUCCESS, otherwise @c #NFC_RESULT_INVALID_PARAMETER
 *         to indicate that a parameter is invalid, or that the provided NDEF
 *         record is chunked.
 */
NFC_API nfc_result_t nfc_set_sp_uri(nfc_ndef_record_t* sp_rec,
                                    const char* utf8_uri);

/**
 * @brief Set the optional smart poster action record in a smart poster NDEF
 *        record
 * @details This function sets the optional action data embedded inside the
 *          smart poster NDEF record payload. This function must not be
 *          called more than once on the same NDEF record.
 *
 * @param sp_rec The smart poster NDEF record to add the action record to its
 *               payload. Chunked NDEF records are not supported.
 * @param value The value byte associated with the action record.
 *
 * @return @c #NFC_RESULT_SUCCESS, otherwise @c #NFC_RESULT_INVALID_PARAMETER
 *         to indicate that a parameter is invalid, or that the provided NDEF
 *         record is chunked.
 */
NFC_API nfc_result_t nfc_set_sp_action(nfc_ndef_record_t* sp_rec,
                                       uchar_t value);

/**
 * @brief Add a smart poster media/icon record to a smart poster NDEF record
 * @details This function adds the data associated with a media record to a
 *          smart poster NDEF record payload.
 *
 * @param sp_rec The smart poster NDEF record to add the media record to
 *               its payload. Chunked NDEF records are not supported.
 * @param mime_type The null-terminated mime type.
 * @param data The media data to add.
 * @param data_length The length of the data buffer.
 *
 * @return @c #NFC_RESULT_SUCCESS, otherwise @c #NFC_RESULT_INVALID_PARAMETER
 *         to indicate that a parameter is invalid, or that the provided NDEF
 *         record is chunked.
 */
NFC_API nfc_result_t nfc_add_sp_media_data(nfc_ndef_record_t* sp_rec,
                                           const char* mime_type,
                                           const uchar_t* data,
                                           size_t data_length);

/**
 * @brief Set the optional smart poster size record in a smart poster NDEF
 *        record
 * @details This function sets the optional size record inside the smart poster
 *          NDEF record payload. This function must not be
 *          called more than once on the same NDEF record.
 *
 * @param sp_rec The smart poster NDEF record to add the size record to its
 *               payload. Chunked NDEF records are not supported.
 * @param size The 32-bit value representing the size.
 *
 * @return @c #NFC_RESULT_SUCCESS, otherwise @c #NFC_RESULT_INVALID_PARAMETER
 *         to indicate that a parameter is invalid, or that the provided NDEF
 *         record is chunked.
 */
NFC_API nfc_result_t nfc_set_sp_size(nfc_ndef_record_t* sp_rec,
                                     uint32_t size);

/**
 * @brief Set the optional smart poster type record in a smart poster NDEF
 *        record
 * @details This function sets the optional type record inside the smart poster
 *          NDEF record payload. This function must not be called more than once
 *          on the same NDEF record.
 *
 * @param sp_rec The smart poster NDEF record to add the type record to its
 *               payload. Chunked NDEF records are not supported.
 * @param type The MIME-type value.
 *
 * @return @c #NFC_RESULT_SUCCESS, otherwise @c #NFC_RESULT_INVALID_PARAMETER
 *         to indicate that a parameter is invalid, or that the provided NDEF
 *         record is chunked.
 */
NFC_API nfc_result_t nfc_set_sp_type(nfc_ndef_record_t* sp_rec,
                                     const char* type);

/*****************************************************************************
 *                          Other RTD Records functions                      *
 *****************************************************************************/
/**
 * @brief Create a NFC Forum Media type NDEF record
 * @details This function creates an NFC Forum Media type NDEF record.
 *
 * @param mime_type The MIME-type of the payload.
 * @param payload Binary content of the data. The content is set as the NDEF
 *                record's payload.
 * @param payload_len The length (in bytes) of the payload.
 * @param rec The returned media type NDEF record.
 *
 * @return @c #NFC_RESULT_SUCCESS, or @c #NFC_RESULT_INVALID_PARAMETER
 *         to indicate that a parameter is invalid.
 */
NFC_API nfc_result_t nfc_create_media_type_record(const char* mime_type,
                                                  const uchar_t* payload,
                                                  size_t payload_len,
                                                  nfc_ndef_record_t** rec);

/**
 * @brief Create a NFC Forum External type NDEF record
 * @details This function creates an NFC Forum External type NDEF record.
 *
 * @param domain_name The domain name of the organization responsible for
 *                    managing the name space for the record type.
 * @param type_name An application-specific record type that is valid for the
 *                  namespace defined by the domain_name argument.
 * @param payload Binary content of the application specific type, which is to
 *                be set as the NDEF record's payload.
 * @param payload_len The byte length of the payload.
 * @param rec The returned external type NDEF record.
 *
 * @return @c #NFC_RESULT_SUCCESS, or @c #NFC_RESULT_INVALID_PARAMETER
 *         to indicate that a parameter is invalid.
 *
 */
NFC_API nfc_result_t nfc_create_external_type_record(const char* domain_name,
                                                     const char* type_name,
                                                     const uchar_t* payload,
                                                     size_t payload_len,
                                                     nfc_ndef_record_t** rec);

/*****************************************************************************
 *   Handover Bluetooth Carrier Record functions                             *
 *****************************************************************************/
/**
 * @brief Create an NFC Forum Bluetooth carrier NDEF record for connection
 *        handover
 * @details This function creates an NFC Forum Media NDEF record with record type
 *          "application/vnd.bluetooth.ep.oob".
 *
 * @param mac_addr The MAC address of Bluetooth device. A valid MAC address
 *                 must have the following format:
 *                 - <tt>00:00:00:00:00:00\0</tt>
 *                 - 18 bytes in size
 *                 - NULL terminated
 *                 - 2 HEX digits per byte
 *                 - HEX digits at the end of address string
 *
 * @param device_name The Bluetooth device name.
 * @param device_class The Bluetooth class of device.
 * @param rec The returned Bluetooth carrier NDEF record.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 *         - @c #NFC_RESULT_OUT_OF_MEMORY: The system memory available for
 *           the NFC system to complete this operation is insufficient.
 */
NFC_API nfc_result_t nfc_create_handover_bluetooth_carrier_record(const char* mac_addr,
                                                                  const char* device_name,
                                                                  unsigned int device_class,
                                                                  nfc_ndef_record_t** rec);

/**
 * @brief Return the handover transport type from a connection handover carrier
 *        NDEF record
 * @details This function returns the transport type from a connection handover
 *          carrier NDEF record.
 *
 * @param rec The connection handover carrier NDEF record.
 * @param transport The returned connection handover transport type in
 *                  @c #handover_transport_type_t.
 *
 * @return @c #NFC_RESULT_SUCCESS, otherwise @c #NFC_RESULT_INVALID_PARAMETER
 *         to indicate that a parameter is invalid, or that the provided NDEF
 *         record is chunked.
 */
NFC_API nfc_result_t nfc_get_handover_transport_type(const nfc_ndef_record_t* rec,
                                                     handover_transport_type_t* transport);

/**
 * @brief Return the Bluetooth MAC address from a Bluetooth carrier NDEF record
 * @details This function returns the Bluetooth MAC address from a Bluetooth
 *          carrier NDEF record.
 *
 * @param rec The Bluetooth carrier NDEF record. Chunked NDEF records are not
 *            supported.
 * @param mac_addr The returned Bluetooth MAC address. This string must be
 *                 de-allocated by calling the @c free() function.  A valid MAC
 *                 address must have the following format:
 *                 - <tt>00:00:00:00:00:00\0</tt>
 *                 - 18 bytes in size
 *                 - NULL terminated
 *                 - 2 HEX digits per byte
 *                 - HEX digits at the end of address string
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid, or the
 *           provided NDEF record is chunked.
 *         - @c #NFC_RESULT_OUT_OF_MEMORY: The system memory available for
 *           the NFC system to complete this operation is insufficient.
 */
NFC_API nfc_result_t nfc_get_handover_bluetooth_mac_address(const nfc_ndef_record_t* rec,
                                                            char** mac_addr);

/**
 * @brief Return the Bluetooth device name from a Bluetooth carrier NDEF record
 * @details This function returns the Bluetooth device name from a Bluetooth
 *          carrier NDEF record.
 *
 * @param rec The Bluetooth carrier NDEF record. Chunked NDEF records are not
 *            supported.
 * @param device_name The returned Bluetooth device name. The device_name
 *                    can be a string, an empty string (if the device_name
 *                    defined in the record has a length of 0) or a NULL pointer
 *                    (if no device_name was defined in the record). This string
 *                    must be de-allocated by calling the @c free() function.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid, or the
 *           provided NDEF record is chunked.
 *         - @c #NFC_RESULT_OUT_OF_MEMORY: The system memory available for
 *           the NFC system to complete this operation is insufficient.
 */
NFC_API nfc_result_t nfc_get_handover_bluetooth_device_name(const nfc_ndef_record_t* rec,
                                                            char** device_name);

/**
 * @brief Return the Bluetooth class of device information from a Bluetooth
 *        carrier NDEF record
 * @details This function returns the Bluetooth class of device information from
 *          a Bluetooth carrier NDEF record.
 *
 * @param rec The Bluetooth carrier NDEF record. Chunked NDEF records are not
 *            supported.
 * @param device_class The returned Bluetooth class of device value.
 *
 * @return @c #NFC_RESULT_SUCCESS, otherwise @c #NFC_RESULT_INVALID_PARAMETER
 *         to indicate that a parameter is invalid, or that the provided NDEF
 *         record is chunked.
 */
NFC_API nfc_result_t nfc_get_handover_bluetooth_device_class(const nfc_ndef_record_t* rec,
                                                             unsigned int* device_class);

/**
 * @brief Return the MAC address from a Wi-Fi Direct carrier NDEF record
 * @details This function returns the MAC address from a Wi-Fi Direct
 *          carrier NDEF record.
 *
 * @param rec The Wi-Fi Direct carrier NDEF record. Chunked NDEF records are not
 *            supported.
 * @param mac_addr The returned Wi-Fi Direct MAC address. This string must be
 *                 de-allocated by calling the @c free() function.  A valid MAC
 *                 address must have the following format:
 *                 - <tt>00:00:00:00:00:00\0</tt>
 *                 - 18 bytes in size
 *                 - NULL terminated
 *                 - 2 HEX digits per byte
 *                 - HEX digits at the end of address string
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid, or the
 *           provided NDEF record is chunked.
 *         - @c #NFC_RESULT_OUT_OF_MEMORY: The system memory available for
 *           the NFC system to complete this operation is insufficient.
 */
NFC_API nfc_result_t nfc_get_handover_wifi_direct_mac_address(const nfc_ndef_record_t* rec,
                                                              char** mac_addr);

/**
 * @brief Return the device name from a Wi-Fi Direct carrier NDEF record
 * @details This function returns the device name from a Wi-Fi Direct
 *          carrier NDEF record.
 *
 * @param rec The Wi-Fi Direct carrier NDEF record. Chunked NDEF records are not
 *            supported.
 * @param device_name The returned Wi-Fi Direct device name. The device name
 *                    can be a string, an empty string (if the device name
 *                    defined in the record has a length of 0) or a NULL pointer
 *                    (if no device name was defined in the record). This string
 *                    must be de-allocated by calling the @c free() function.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid, or the
 *           provided NDEF record is chunked.
 *         - @c #NFC_RESULT_OUT_OF_MEMORY: The system memory available for
 *           the NFC system to complete this operation is insufficient.
 */
NFC_API nfc_result_t nfc_get_handover_wifi_direct_device_name(const nfc_ndef_record_t* rec,
                                                              char** device_name);

/**
 * @brief Return the device type from a Wi-Fi Direct carrier NDEF record
 * @details This function returns the device type from a Wi-Fi Direct
 *          carrier NDEF record.
 *
 * @param rec The Wi-Fi Direct carrier NDEF record. Chunked NDEF records are not
 *            supported.
 * @param device_type The returned Wi-Fi Direct device type. The device type
 *                    can be a string, an empty string (if the device type
 *                    defined in the record has a length of 0) or a NULL pointer
 *                    (if no device type was defined in the record). This string
 *                    must be de-allocated by calling the @c free() function.
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid, or the
 *           provided NDEF record is chunked.
 *         - @c #NFC_RESULT_OUT_OF_MEMORY: The system memory available for
 *           the NFC system to complete this operation is insufficient.
 */
NFC_API nfc_result_t nfc_get_handover_wifi_direct_device_type(const nfc_ndef_record_t* rec,
                                                              char** device_type);
__END_DECLS

#endif /* NFC_NDEF_H_ */
