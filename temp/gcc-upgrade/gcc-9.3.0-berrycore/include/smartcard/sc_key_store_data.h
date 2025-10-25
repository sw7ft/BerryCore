/*
 * Research In Motion Limited. Copyright (C) 2013.
 * Research In Motion Limited. All rights reserved.
 */

/**
 * @file sc_key_store_data.h
 *
 * Key store data instances are used to store information about individual keys
 * located on a smart card.
 *
 * Information stored in a @c sc_key_store_data_t instance includes:
 *
 * - certificate information
 * - cryptographic system information
 * - cryptographic token information
 */


#ifndef SC_KEY_STORE_DATA_H
#define SC_KEY_STORE_DATA_H

#include <smartcard/sc_crypto_system.h>
#include <smartcard/sc_crypto_token.h>
#include <smartcard/sc_certificate.h>
#include <smartcard/sc_data_types.h>

#include <sys/platform.h>


__BEGIN_DECLS


/**
 * Key store data represents a key element on the card.
 * E.g. it can represent a certificate with the corresponding private key on
 * the card. Alternatively, it can represent a symmetric key on the card.
 */
typedef struct _sc_key_store_data_t sc_key_store_data_t;


/**
 * Creates @c sc_key_store_data_t instance.
 * To destroy the instance, use @c sc_key_store_data_destroy() function.
 *
 * @param [out] key_store_data
 *      Key store data instance to be created. Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_key_store_data_create( sc_key_store_data_t** key_store_data );


/**
 * Destroys @c sc_key_store_data_t instance.
 *
 * @param [in] key_store_data
 *      Created key store data instance. Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_key_store_data_destroy( sc_key_store_data_t* key_store_data );


/**
 * Retrieves the certificate associated with this key store data instance.
 *
 * @param [in] key_store_data
 *      Key store data instance. Must not be NULL.
 * @param [out] certificate
 *      The certificate associated with this key store data instance.
 *      Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_key_store_data_get_certificate( const sc_key_store_data_t* key_store_data,
                                                      const sc_certificate_t** certificate );


/**
 * Retrieves the cryptographic system associated with this key store data instance.
 *
 * @param [in] key_store_data
 *      Key store data instance. Must not be NULL.
 * @param [out] crypto_system
 *      The cryptographic system associated with this key store data instance.
 *      Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_key_store_data_get_crypto_system( const sc_key_store_data_t* key_store_data,
                                                        const sc_crypto_system_t** crypto_system );


/**
 * Retrieves the crypto token associated with this key store data instance.
 *
 * @param [in] key_store_data
 *      Key store data instance.  Must not be NULL.
 * @param [out] crypto_token
 *      The crypto token associated with this key store data instance.
 *      Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_key_store_data_get_crypto_token( const sc_key_store_data_t* key_store_data,
                                                       const sc_crypto_token_t** crypto_token );


/**
 * Serializes key store data instance.
 *
 * @param [in] key_store_data
 *      Key store data instance. Must not be NULL.
 * @param [out] buffer
 *      The buffer where the serialized form of the instance will be written to.
 *      If this parameter is NULL, then this function only computes the size of
 *      the buffer required to hold the serialized form of the instance.
 * @param [in,out] buffer_length
 *      If @c buffer is not NULL, then this parameter indicates the length of @c buffer.
 *      Otherwise, the size of the buffer required to hold the serialized data is
 *      written to this parameter upon return. Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_key_store_data_serialize( const sc_key_store_data_t* key_store_data,
                                                unsigned char* buffer,
                                                size_t* buffer_length );


/**
 * Deserializes the provided data and populates the provided key store data
 * instance with the data from the provided serialized buffer.
 *
 * @param [in] key_store_data
 *      Key store data instance. Must not be NULL.
 * @param [in] buffer
 *      Buffer containing the serialized data to populate the instance with.
 *      Must not be NULL.
 * @param [in] buffer_length
 *      The length of @c buffer.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_key_store_data_deserialize( sc_key_store_data_t* key_store_data,
                                                  const unsigned char* buffer,
                                                  size_t buffer_length );


__END_DECLS

#endif /* SC_KEY_STORE_DATA_H */
