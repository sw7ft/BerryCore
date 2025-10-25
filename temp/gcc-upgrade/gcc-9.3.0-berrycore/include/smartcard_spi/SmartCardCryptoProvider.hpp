/*
 * SmartCardCryptoProvider.hpp
 *
 * Copyright Research In Motion Limited, 2012-2013
 */

#ifndef SMARTCARD_SPI_SMARTCARDCRYPTOPROVIDER_HPP
#define SMARTCARD_SPI_SMARTCARDCRYPTOPROVIDER_HPP


#include <smartcard/sc_crypto_system.h>
#include <smartcard/sc_crypto_token.h>
#include <smartcard/sc_key_store_data.h>
#include <smartcard_spi/SmartCardInterface.hpp>


namespace smartcard_spi
{

/**
 * @c SmartCardCryptoProvider defines smart card cryptographic functionality.
 */
class SmartCardCryptoProvider : public SmartCardInterface
{

public:

    /**
     * Destructor.
     */
    virtual ~SmartCardCryptoProvider();


    /**
     * Retrieves key store data associated with the keys stored on the card.
     * The returned collection of key store data describes all private and symmetric
     * keys stored on the card including any certificates associated with those
     * keys.
     *
     * @param [in/out] keyStoreDataElements
     *      The array of key store data pointers.
     *      The array should be allocated by the caller, and it will be populated by this function.
     *      The @c sc_key_store_data_t instances should be pre-allocated by the caller.
     *      If NULL, only the number of elements will be returned.
     * @param [in/out] keyStoreDataElementsLength.
     *      On input, specifies the length of @c keyStoreDataElements array allocated by the caller.
     *      The number of pre-allocated key store data elements should be no less than
     *      @c keyStoreDataElementsLength.
     *      On output, specifies the number of key store data elements available.
     * @return
     *      In case of success, SC_SCARD_S_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t getKeyStoreData( sc_key_store_data_t** keyStoreDataElements,
                                                unsigned int& numKeyStoreDataElements );


    /**
     * Initializes the smart card in preparation to perform encryption operations
     * with the specified cryptographic system and key.
     *
     * @param [in] cryptoSystem
     *      Cryptographic system to use for encryption operation.
     *      NULL may be allowed, e.g. the driver only supports one cryptographic system.
     * @param [in] key
     *      A cryptographic token describing the key to use for encryption
     *      operation.
     *      NULL may be allowed, e.g. the driver only supports one cryptographic key.
     * @return
     *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t encryptInit( const sc_crypto_system_t* cryptoSystem,
                                            const sc_crypto_token_t* key );


    /**
     * Encrypts data in a single part.
     *
     * Algorithm specific notes:
     *
     * - RSA: No padding bytes are added or removed.
     *
     * Depending on card driver implementation, this function may or may not be
     * called multiple times without re-initializing.
     *
     * @param [in] plaintext
     *      The input buffer containing the plaintext to be encrypted.
     *      Must not be NULL.
     * @param [in] plaintextLength
     *      Plaintext buffer length.
     * @param [out] ciphertext
     *      The output buffer where the ciphertext data will be written.
     *      If NULL, only ciphertext length will be returned.
     * @param [in,out] ciphertextLength
     *      On input, ciphertext buffer length.
     *      On output, ciphertext length.
     * @return
     *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t encrypt( const unsigned char* plaintext,
                                        unsigned int plaintextLength,
                                        unsigned char* ciphertext,
                                        unsigned int& ciphertextLength );


    /**
     * Initializes the smart card in preparation to perform decryption operations
     * with the specified cryptographic system and key.
     *
     * @param [in] cryptoSystem
     *      Cryptographic system to use for decryption operation.
     *      NULL may be allowed, e.g. the driver only supports one cryptographic system.
     * @param [in] key
     *      A cryptographic token describing the key to use for decryption
     *      operation.
     *      NULL may be allowed, e.g. the driver only supports one cryptographic key.
     * @return
     *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t decryptInit( const sc_crypto_system_t* cryptoSystem,
                                            const sc_crypto_token_t* key );


    /**
     * Decrypt encrypted data in a single part.
     *
     * Algorithm specific notes:
     *
     * - RSA: No padding bytes are added or removed.
     *
     * Depending on card driver implementation, this function may or may not be
     * called multiple times without re-initalizing.
     *
     * @param [in] ciphertext
     *      The input buffer containing the ciphertext to be decrypted.
     *      Must not be NULL.
     * @param [in] ciphertextLength
     *      Ciphertext buffer length.
     * @param [out] plaintext
     *      The output buffer where the plaintext data will be written.
     *      If NULL, only plaintext length will be returned.
     * @param [in,out] plaintextLength
     *      On input, plaintext buffer length.
     *      On output, plaintext length.
     * @return
     *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t decrypt( const unsigned char* ciphertext,
                                        unsigned int ciphertextLength,
                                        unsigned char* plaintext,
                                        unsigned int& plaintextLength );


    /**
     * Initializes the smart card in preparation to perform signing operations with
     * the specified cryptographic system and key.
     *
     * @param [in] cryptoSystem
     *      Cryptographic system to use for signing operation.
     *      NULL may be allowed, e.g. the driver only supports one cryptographic system.
     * @param [in] key
     *      A cryptographic token describing the key to use for signing
     *      operation.
     *      NULL may be allowed, e.g. the driver only supports one cryptographic key.
     * @return
     *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t signInit( const sc_crypto_system_t* cryptoSystem,
                                         const sc_crypto_token_t* key );


    /**
     * Performs a signing operation.
     *
     * Algorithm specific notes:
     *
     * - RSA: No padding bytes are added or removed.
     *
     * Depending on card driver implementation, this function may or may not be
     * called multiple times without re-initalizing.
     *
     * @param [in] data
     *      The input buffer containing the data to be signed.
     *      Must not be NULL.
     * @param [in] dataLength
     *      Data buffer length.
     * @param [out] signature
     *      The output buffer where the signature data will be written.
     *      If NULL, only signature length will be returned.
     * @param [in,out] signatureLength
     *      On input, signature buffer length.
     *      On output, signature length.
     * @return
     *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t sign( const unsigned char* data,
                                     unsigned int dataLength,
                                     unsigned char* signature,
                                     unsigned int& signatureLength );


    /**
     * Returns a buffer with random bytes generated by the card.
     * The data produced by this method shall be cryptographically random.
     *
     * @param [out] randomData
     *      A buffer for storing generated random data.
     *      If NULL is specified, @c randomDataLength parameter may return the
     *      maximum number of bytes it can generate. If this feature is not
     *      supported, the function will return an error.
     * @param [in,out] randomDataLength
     *      On input, specifies the requested number of random bytes to generate.
     *      On output, returns the actual number of random bytes generated.
     * @return
     *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t generateRandomData( unsigned char* randomData,
                                                   unsigned int& randomDataLength );


    /**
     * Generates a cryptographic key on the card.
     *
     * @param [in] cryptoSystem
     *      The cryptographic system instance specifying key parameters. Must not be NULL.
     * @param [in,out] keyStoreData
     *      The instance of the key store data that identifies the key on the card.
     *      On input, if an existing key store data element is provided, the existing
     *      key referenced by this instance is replaced with a newly generated key.
     *      If a newly created (empty) key store data instance is provided,
     *      a new key is generated.
     *      On output, this parameter indicates the instance of the key store data that
     *      identifies the newly generated key. Must not be NULL.
     * @return
     *      If the method succeeds, @c SC_SCARD_S_SUCCESS is returned.
     *      If the method fails, an error code is returned.
     */
    virtual sc_response_code_t generateKey( const sc_crypto_system_t* cryptoSystem,
                                            sc_key_store_data_t* keyStoreData );


    /**
     * Retrieves the public key associated with the specified key store data.
     *
     * @param [in] keyStoreData
     *      The instance of the key store data that identifies the key on the card.
     *      Must not be NULL.
     * @param [out] publicKey
     *      The output buffer where the public key data is written.
     *      The DER-encoded public key is returned in X.509 format.
     *      If NULL, only the public key length is returned.
     * @param [in,out] publicKeyLength
     *      On input, the length of the public key buffer.
     *      On output, the length of the public key.
     *      Must not be NULL.
     * @return
     *      If the method succeeds, @c SC_SCARD_S_SUCCESS is returned.
     *      If the method fails, an error code is returned.
     */
    virtual sc_response_code_t getPublicKey( const sc_key_store_data_t* keyStoreData,
                                             unsigned char* publicKey,
                                             unsigned int& publicKeyLength );


    /**
     * Imports the X.509 certificate to the smart card for the specified key.
     *
     * @param [in] certificate
     *      The certificate to import.
     *      The certificate should be DER-encoded in X.509 format.
     *      Must not be NULL.
     * @param [in] certificateLength
     *      The certificate length.
     * @param [in,out] keyStoreData
     *      The instance of the key store data that identifies the key slot where
     *      the certificate should be imported. The key store data instance
     *      may be modified so it contains the correct key reference.
     *      In particular, the certificate data in the instance may be updated.
     *      Must not be NULL.
     * @return
     *      If the method succeeds, @c SC_SCARD_S_SUCCESS is returned.
     *      If the method fails, an error code is returned.
     */
    virtual sc_response_code_t importCertificate( const unsigned char* certificate,
                                                  unsigned int certificateLength,
                                                  sc_key_store_data_t* keyStoreData );


    /**
     * Imports a new key to the smart card.
     *
     * @param [in] certificate
     *      The certificate to import.
     *      The certificate should be DER-encoded in X.509 format.
     *      Must not be NULL.
     * @param [in] certificateLength
     *      The certificate length.
     * @param [in] privateKey
     *      The private key to import.
     *      The private key should be DER-encoded in PKCS8 format and provided
     *      in plain text (PKCS8 should not be encrypted).
     *      Must not be NULL.
     * @param [in] privateKeyLength
     *      The length of the private key.
     * @param [in,out] keyStoreData
     *      The instance of the key store data that identifies the key on the card.
     *      On input, if an existing key store data element is provided, the existing
     *      key referenced by this instance is replaced with a new key created from
     *      the provided data. If a newly created key store data instance is provided,
     *      a new key is created.
     *      On output, this parameter indicates the instance of the key store data that
     *      identifies the newly created key. Must not be NULL.
     * @return
     *      If the method succeeds, @c SC_SCARD_S_SUCCESS is returned.
     *      If the method fails, an error code is returned.
     */
    virtual sc_response_code_t importKey( const unsigned char* certificate,
                                          unsigned int certificateLength,
                                          const unsigned char* privateKey,
                                          unsigned int privateKeyLength,
                                          sc_key_store_data_t* keyStoreData );


    /**
     * Removes the specified key from the card.
     *
     * @param [in] keyStoreData
     *      The instance of the key store data that identifies the key on the card
     *      to be removed.
     *      Must not be NULL.
     * @return
     *      If the method succeeds, @c SC_SCARD_S_SUCCESS is returned.
     *      If the method fails, an error code is returned.
     */
    virtual sc_response_code_t removeKey( const sc_key_store_data_t* keyStoreData );

protected:

    /**
     * Default implementation constructor.
     */
    SmartCardCryptoProvider();

};

} // namespace smartcard_spi

#endif /* SMARTCARD_SPI_SMARTCARDCRYPTOPROVIDER_HPP */
