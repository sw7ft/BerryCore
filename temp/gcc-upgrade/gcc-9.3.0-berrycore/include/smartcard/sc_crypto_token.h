/*
 * Research In Motion Limited. Copyright (C) 2013.
 * Research In Motion Limited. All rights reserved.
 */

/**
 * @file sc_crypto_token.h
 *
 * The set of functions in sc_crypto_token.h facilitate the management and
 * manipulation of @c sc_crypto_token_t instances, which are
 * general containers used to store meta-data that may be used within various
 * cryptographic operations.
 *
 * All information stored within and retrieved from a @c sc_crypto_token_t
 * instance is indexed by a string-based key. Instances will generally be
 * retrieved from a specific smart card driver, which will populate them with
 * some set of data that can be used in future cryptographic operations. Since
 * each smart card driver may require different information that may be be
 * mutually exclusive, there is no standard set of information that is
 * guaranteed to be available in all instances. Moreover, outside of smart card
 * drivers, it is not expected for any other components to require intimate
 * knowledge of the information stored within a single instance. Therefore,
 * knowledge of information stored within an instance is expected to be explicit.
 */


#ifndef SC_CRYPTO_TOKEN_H
#define SC_CRYPTO_TOKEN_H

#include <smartcard/sc_data_types.h>

#include <sys/platform.h>
#include <sys/types.h>


__BEGIN_DECLS


/**
 * Cryptographic token represents a cryptographic key on the card.
 * E.g. it could be a symmetric key or a private key.
 */
typedef struct _sc_crypto_token_t sc_crypto_token_t;


/**
 * Creates @c sc_crypto_token_t instance.
 * To destroy the instance, use @c sc_crypto_token_destroy() function.
 *
 * @param [out] crypto_token
 *      Created crypto token instance. Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_crypto_token_create( sc_crypto_token_t** crypto_token );


/**
 * Destroys @c sc_crypto_token_t instance.
 *
 * @param [in] crypto_token
 *      Crypto token instance to be destroyed. Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_crypto_token_destroy( sc_crypto_token_t* crypto_token );


/**
 * Stores integer value in crypto token instance.
 *
 * @param [in] crypto_token
 *      Crypto token instance. Must not be NULL.
 * @param [in] key
 *      Attribute key. NULL-terminate string. Must not be NULL.
 * @param [in] value
 *      Integer value to be stored.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_crypto_token_put_property_int( sc_crypto_token_t* crypto_token,
                                                     const char* key,
                                                     int value );


/**
 * Retrieves integer value from crypto token instance.
 *
 * @param [in] crypto_token
 *      Crypto token instance. Must not be NULL.
 * @param [in] key
 *      Attribute key. NULL-terminate string. Must not be NULL.
 * @param [out] value
 *      Integer value mapped to the specified key. Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_crypto_token_get_property_int( const sc_crypto_token_t* crypto_token,
                                                     const char* key,
                                                     int* value );



/**
 * Stores binary data in crypto token instance.
 *
 * @param [in] crypto_token
 *      Crypto token instance. Must not be NULL.
 * @param [in] key
 *      Attribute key. NULL-terminate string. Must not be NULL.
 * @param [in] value
 *      Binary data to be stored.
 * @param [in] value_length
 *      The length of @c value.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_crypto_token_put_property_byte_array( sc_crypto_token_t* crypto_token,
                                                            const char* key,
                                                            const unsigned char* value,
                                                            size_t value_length );


/**
 * Retrieves binary data from crypto token instance.
 *
 * @param [in] crypto_token
 *      Crypto token instance. Must not be NULL.
 * @param [in] key
 *      Attribute key. NULL-terminate string. Must not be NULL.
 * @param [in,out] value
 *      The buffer used to store the requested binary data.
 *      If NULL, then the length of the requested value is written to @c value_length.
 * @param [in,out] value_length
 *      If @c value is NULL, then this parameter is used to store the
 *      length of the binary data currently mapped to the specified key on
 *      return. If @c value is not NULL, then this parameter indicates
 *      the length of @c value on input. Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_crypto_token_get_property_byte_array( const sc_crypto_token_t* crypto_token,
                                                            const char* key,
                                                            unsigned char* value,
                                                            size_t* value_length );


/**
 * Removes a property value a from crypto token instance.
 *
 * @param [in] crypto_token
 *      Crypto token instance. Must not be NULL.
 * @param [in] key
 *      Attribute key. NULL-terminate string. Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_crypto_token_remove_property( sc_crypto_token_t* crypto_token,
                                                    const char* key );


/**
 * Serializes crypto token instance.
 *
 * @param [in] crypto_token
 *      Crypto token instance. Must not be NULL.
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
sc_response_code_t sc_crypto_token_serialize( const sc_crypto_token_t* crypto_token,
                                              unsigned char* buffer,
                                              size_t* buffer_length );


/**
 * Deserializes the provided data and populates the provided crypto token
 * instance with the data from the provided serialized buffer.
 *
 * @param [in] crypto_token
 *      Crypto token instance. Must not be NULL.
 * @param [in] buffer
 *      Buffer containing the serialized data to populate the instance with.
 *      Must not be NULL.
 * @param [in] buffer_length
 *      The length of @c buffer.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_crypto_token_deserialize( sc_crypto_token_t* crypto_token,
                                                const unsigned char* buffer,
                                                size_t buffer_length );


__END_DECLS

#endif /* SC_CRYPTO_TOKEN_DATA_H */
