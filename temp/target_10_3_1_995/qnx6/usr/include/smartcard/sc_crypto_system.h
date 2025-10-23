/*
 * Research In Motion Limited. Copyright (C) 2013.
 * Research In Motion Limited. All rights reserved.
 */

/**
 * @file sc_crypto_system.h
 *
 * Crypto system instances are used to store information about various cryptographic systems.
 *
 * Information stored in a @c sc_crypto_sytem_t includes:
 * - the supported algorithm
 * - the supported key size (in bits)
 */


#ifndef SC_CRYPTO_SYSTEM_H
#define SC_CRYPTO_SYSTEM_H

#include <smartcard/sc_data_types.h>

#include <sys/platform.h>
#include <stddef.h>


__BEGIN_DECLS


/**
 * Cryptographic system describes a set of cryptographic primitives for
 * cryptographic operations. E.g. RSA 2048.
 */
typedef struct _sc_crypto_system_t sc_crypto_system_t;


/**
 * Creates @c sc_crypto_system_t instance.
 * To destroy the instance, use @c sc_crypto_system_destroy() function.
 *
 * @param [out] crypto_system
 *      Created crypto system instance. Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_crypto_system_create( sc_crypto_system_t** crypto_system );


/**
 * Destroys @c sc_crypto_system_t instance.
 *
 * @param [in] crypto_system
 *      Crypto system instance to be destroyed. Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_crypto_system_destroy( sc_crypto_system_t* crypto_system );


/**
 * Retrieves the crypto system algorithm.
 *
 * @param [in] crypto_system
 *      Crypto system instance. Must not be NULL.
 * @param [out] crypto_algorithm
 *      Crypto algorithm. Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_crypto_system_get_algorithm( const sc_crypto_system_t* crypto_system,
                                                   sc_crypto_algorithm_t* crypto_algorithm );


/**
 * Sets the crypto system algorithm.
 *
 * @param [in] crypto_system
 *      Crypto system instance. Must not be NULL.
 * @param [in] crypto_algorithm
 *      Crypto algorithm.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_crypto_system_set_algorithm( sc_crypto_system_t* crypto_system,
                                                   sc_crypto_algorithm_t crypto_algorithm );


/**
 * Retrieves the supported key size in bits.
 *
 * @param [in] crypto_system
 *      Crypto system instance. Must not be NULL.
 * @param [out] key_bit_length
 *      Key length in bits. Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_crypto_system_get_key_bit_length( const sc_crypto_system_t* crypto_system,
                                                        size_t* key_bit_length );


/**
 * Sets the supported key size in bits.
 *
 * @param [in] crypto_system
 *      Crypto system instance. Must not be NULL.
 * @param [in] key_bit_length
 *      Key length in bits.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_crypto_system_set_key_bit_length( sc_crypto_system_t* crypto_system,
                                                        size_t key_bit_length );


/**
 * Retrieves the string representation of the curve object identifier (OID).
 * The OID should be a NULL-terminated string using dot notation, for example, "1.3.132.0.35".
 *
 * @param [in] crypto_system
 *      The crypto system instance. Must not be NULL.
 * @param [out] curve_oid
 *      The output buffer where the curve OID is written.
 *      If NULL, only the length of the curve OID is returned.
 * @param [in,out] curve_oid_length
 *      On input, the length of the @c curve_oid buffer array.
 *      On output, the length of the curve OID.
 *      Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_crypto_system_get_curve_oid( const sc_crypto_system_t* crypto_system,
                                                   char* curve_oid, size_t* curve_oid_length );


/**
 * Sets the string representation of the curve object identifier (OID).
 * The OID should be a NULL-terminated string using dot notation, for example, "1.3.132.0.35".
 *
 * @param [in] crypto_system
 *      The crypto system instance. Must not be NULL.
 * @param [in] curve_oid
 *      The curve OID. Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_crypto_system_set_curve_oid( sc_crypto_system_t* crypto_system,
                                                   const char* curve_oid );


/**
 * Serializes crypto system instance.
 *
 * @param [in] crypto_system
 *      Crypto system instance. Must not be NULL.
 * @param [out] buffer
 *      The buffer where the serialized form of the instance will be written to.
 *      If this parameter is NULL, then this function only computes the size of
 *      the buffer required to hold the serialized form of the instance.
 * @param [in,out] length
 *      On input, the length of the @c buffer.
 *      On output, the length of the serialized data.
 *      Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_crypto_system_serialize( const sc_crypto_system_t* crypto_system,
                                               unsigned char* buffer,
                                               size_t* buffer_length );


/**
 * Deserializes the provided data and populates the provided crypto system
 * instance with the data from the provided serialized buffer.
 *
 * @param [in] crypto_system
 *      Crypto system instance. Must not be NULL.
 * @param [in] buffer
 *      Buffer containing the serialized data to populate the instance with.
 *      Must not be NULL.
 * @param [in] buffer_length
 *      The length of @c buffer.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_crypto_system_deserialize( sc_crypto_system_t* crypto_system,
                                                 const unsigned char* buffer,
                                                 size_t buffer_length );


__END_DECLS

#endif /* SC_CRYPTO_SYSTEM_H */
