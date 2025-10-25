/*
 * Research In Motion Limited. Copyright (C) 2013.
 * Research In Motion Limited. All rights reserved.
 */

/**
 * @file sc_smart_card_id.h
 *
 * Smart card ID instances are used to store smart card identifying information.
 * Information stored in smart card ID instances includes:
 *
 * - card identifier that is unique within a specific type of card.
 * - card label that can be used to identify a specific smart card to the user.
 * - card name identifying the corresponding smart card driver that should be
 *   used to manipulate the card.
 * - reader name identifying the smart card reader driver corresponding to the
 *   smart card reader used to interact with the card.
 */


#ifndef SC_SMART_CARD_ID_H
#define SC_SMART_CARD_ID_H


#include <smartcard/sc_data_types.h>

#include <stddef.h>
#include <stdbool.h>
#include <sys/platform.h>


__BEGIN_DECLS


/**
 * Smart card identifier that uniquely identifies a smart card in a reader.
 */
typedef struct _sc_smart_card_id_t sc_smart_card_id_t;


/**
 * Creates @c sc_smart_card_id_t instance.
 * To destroy the instance, use @c sc_smart_card_id_destroy() function.
 *
 * @param [out] smart_card_id
 *      Created smart card ID instance. Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_smart_card_id_create( sc_smart_card_id_t** smart_card_id );


/**
 * Creates @c sc_smart_card_id_t instance copy.
 * To destroy the instance, use @c sc_smart_card_id_destroy() function.
 *
 * @param [in] smart_card_id
 *      The existing @c sc_smart_card_id_t instance to be copied. Must not be NULL.
 * @param [out] smart_card_id_copy
 *      Created smart card ID instance copy. Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_smart_card_id_copy( const sc_smart_card_id_t* smart_card_id,
                                          sc_smart_card_id_t** smart_card_id_copy );


/**
 * Destroys @c sc_smart_card_id_t instance.
 *
 * @param [in] smart_card_id
 *      Smart card ID instance to be destroyed. Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_smart_card_id_destroy( sc_smart_card_id_t* smart_card_id );


/**
 * Retrieves the card numeric identifier.
 *
 * @param [in] smart_card_id
 *      Smart card ID instance. Must not be NULL.
 * @param [out] card_id
 *      Card numeric identifier. Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_smart_card_id_get_card_id( const sc_smart_card_id_t* smart_card_id,
                                                 long long* card_id );


/**
 * Sets the card numeric identifier.
 *
 * @param [in] smart_card_id
 *      Smart card ID instance. Must not be NULL.
 * @param [in] card_id
 *      Card numeric identifier.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_smart_card_id_set_card_id( sc_smart_card_id_t* smart_card_id,
                                                 long long card_id );


/**
 * Retrieves the card label.
 *
 * @param [in] smart_card_id
 *      Smart card ID instance. Must not be NULL.
 * @param [out] card_label
 *      User-friendly card label. Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_smart_card_id_get_card_label( const sc_smart_card_id_t* smart_card_id,
                                                    const sc_card_label_t** card_label );


/**
 * Sets the card label.
 *
 * @param [in] smart_card_id
 *      Smart card ID instance. Must not be NULL.
 * @param [in] card_label
 *      User-friendly card label.
 *      If the provided card label is NULL, the instance field will be set to empty string.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_smart_card_id_set_card_label( sc_smart_card_id_t* smart_card_id,
                                                    const sc_card_label_t* card_label );


/**
 * Retrieves the card driver name.
 *
 * @param [in] smart_card_id
 *      Smart card ID instance. Must not be NULL.
 * @param [out] card_name.
 *      Card driver name. Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_smart_card_id_get_card_name( const sc_smart_card_id_t* smart_card_id,
                                                   const sc_card_name_t** card_name );


/**
 * Sets the card driver name.
 *
 * @param [in] smart_card_id
 *      Smart card ID instance. Must not be NULL.
 * @param [in] card_name.
 *      Card driver name.
 *      If the provided card name is NULL, the instance field will be set to empty string.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_smart_card_id_set_card_name( sc_smart_card_id_t* smart_card_id,
                                                   const sc_card_name_t* card_name );


/**
 * Retrieves the reader name the card is known to be inserted in.
 *
 * @param [in] smart_card_id
 *      Smart card ID instance. Must not be NULL.
 * @param [out] reader_name
 *      Reader driver name associated with the reader the card is inserted in.
 *      Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_smart_card_id_get_reader_name( const sc_smart_card_id_t* smart_card_id,
                                                     const sc_reader_name_t** reader_name );


/**
 * Sets the reader name.
 *
 * @param [in] smart_card_id
 *      Smart card ID instance. Must not be NULL.
 * @param [in] reader_name
 *      Reader driver name associated with the reader the card is inserted in.
 *      If the provided reader name is NULL, the instance field will be set to empty string.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_smart_card_id_set_reader_name( sc_smart_card_id_t* smart_card_id,
                                                     const sc_reader_name_t* reader_name );


/**
 * Compare two smart card ID instances to determine if they are equal.
 * If both instances are NULL, then they are considered equal.
 *
 * @param [in] smart_card_id1
 *      The first instance involved in comparison.
 * @param [in] smart_card_id2
 *      The second instance involved in comparison.
 * @param [out] result
 *      A non-zero value is written to this parameter if the instances are equal.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_smart_card_id_equal( const sc_smart_card_id_t* smart_card_id1,
                                           const sc_smart_card_id_t* smart_card_id2,
                                           bool* result );


/**
 * Serializes a smart card ID instance.
 *
 * @param [in] smart_card_id
 *      Smart card ID instance. Must not be NULL.
 * @param [out] buffer
 *      The buffer where the serialized form of the instance will be written to.
 *      If this parameter is NULL then this function only computes the size of
 *      the buffer required to hold the serialized form of the instance.
 * @param [in,out] buffer_length
 *      If @c buffer is not NULL, then this parameter indicates the length of @c buffer.
 *      Otherwise, the size of the buffer required to hold the serialized data is
 *      written to this parameter upon return.  Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_smart_card_id_serialize( const sc_smart_card_id_t* smart_card_id,
                                               unsigned char* buffer,
                                               size_t* buffer_length );


/**
 * Deserializes the provided data and populates the provided smart card ID
 * instance with the data from the provided serialized buffer.
 *
 * @param [in] smart_card_id
 *      Smart card ID instance. Must not be NULL.
 * @param [in] buffer
 *      The buffer containing the serialized data to populate the instance with.
 *      Must not be NULL.
 * @param [in] buffer_length
 *      The length of @c buffer.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_smart_card_id_deserialize( sc_smart_card_id_t* smart_card_id,
                                                 const unsigned char* buffer,
                                                 size_t buffer_length );


__END_DECLS

#endif /* SC_SMART_CARD_ID_H */
