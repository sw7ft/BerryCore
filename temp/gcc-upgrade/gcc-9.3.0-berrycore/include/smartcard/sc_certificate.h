/*
 * Research In Motion Limited. Copyright (C) 2013.
 * Research In Motion Limited. All rights reserved.
 */

/**
 * @file sc_certificate.h
 *
 * Certificate instance represents X509 (public key certificate standard)
 * certificate and allows certificate DER encoding retrieval.
 *
 * DER (Distinguished Encoding Rules) encoding is a common encoding
 * used for certificates.
 */


#ifndef SC_CERTIFICATE_H
#define SC_CERTIFICATE_H

#include <smartcard/sc_data_types.h>

#include <sys/platform.h>
#include <sys/types.h>


__BEGIN_DECLS


/**
 * A type describing X509 certificate.
 */
typedef struct _sc_certificate_t sc_certificate_t;


/**
 * Creates an @c sc_certificate_t instance.
 * To destroy the instance, use @c sc_certificate_destroy() function.
 *
 * @param [out] certificate
 *      Created certificate instance. Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_certificate_create( sc_certificate_t** certificate );


/**
 * Destroys a @c sc_certificate_t instance.
 *
 * @param [in] certificate
 *      Certificate instance to be destroyed. Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_certificate_destroy( sc_certificate_t* certificate );


/**
 * Retrieves DER-encoded certificate data.
 *
 * @param [in] certificate
 *      Certificate instance. Must not be NULL.
 * @param [out] data
 *      The buffer where the certificate data is to be written to.
 *      This parameter can be NULL, and if it is, this function will only
 *      return the length of certificate data.
 * @param [in,out] data_length
 *      If @c data is NULL, then the size of the raw certificate data,
 *      in bytes, is written to this parameter upon returning from the function.
 *      If @c data is not NULL, then this parameter indicates the
 *      length of @c data on input and is updated to indicate the
 *      number of bytes that were written to @c data on output.
 *      Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_certificate_get_data( const sc_certificate_t* certificate,
                                            unsigned char* data,
                                            size_t* data_length );


/**
 * Sets DER-encoded certificate data.
 *
 * @param [in] certificate
 *      Certificate instance. Must not be NULL.
 * @param [in] data
 *      The buffer containing the raw DER certificate data to be set.
 *      If @c data is NULL, then the currently stored certificate data is cleared.
 * @param [in] data_length
 *      The length of the @c data buffer. If the length is zero then
 *      the currently stored certificate data is cleared.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_certificate_set_data( sc_certificate_t* certificate,
                                            const unsigned char* data,
                                            size_t data_length );


/**
 * Serializes the provided certificate instance.
 *
 * @param [in] certificate
 *      Certificate instance. Must not be NULL.
 * @param [out] buffer
 *      The buffer where the serialized form of the instance will be written to.
 *      If this parameter is NULL then this function only computes the size of
 *      the buffer required to hold the serialized form of the instance.
 * @param [in,out] buffer_length
 *      If @c buffer is not NULL, then this parameter indicates the length of @c buffer.
 *      Otherwise, the size of the buffer required to hold the serialized data is
 *      written to this parameter upon return. Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_certificate_serialize( const sc_certificate_t* certificate,
                                             unsigned char* buffer,
                                             size_t* buffer_length );


/**
 * Deserializes the provided data and populates the provided certificate instance
 * with the data from the provided serialized buffer.
 *
 * @param [in] certificate
 *      Certificate instance. Must not be NULL.
 * @param [in] buffer
 *      Buffer containing the serialized data to populate the instance with.
 *      Must not be NULL.
 * @param [in] buffer_length
 *      The length of @c buffer.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_certificate_deserialize( sc_certificate_t* certificate,
                                               const unsigned char* buffer,
                                               size_t buffer_length );


__END_DECLS

#endif /* SC_CERTIFICATE_H */
