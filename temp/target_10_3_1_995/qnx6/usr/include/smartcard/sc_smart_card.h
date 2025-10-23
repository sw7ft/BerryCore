/*
 * Research In Motion Limited. Copyright (C) 2013.
 * Research In Motion Limited. All rights reserved.
 */

/*
 * @file sc_smart_card.h
 * Smart card header contains the main smart card functionality.
 *
 *
 * @mainpage Smart Card API Overview
 * Smart card API provides access to smart card functionality including:
 *   - Cryptographic API (e.g. encrypt, decrypt, sign).
 *   - Smart card PIN API (e.g. verify PIN, get num of remaining attempts, etc).
 *   - Smart card session management (e.g. attach/detach)
 *   - Reader functionality (e.g. listing available readers, monitoring reader state)
 *   - Ability to send custom APDUs.
 *
 *
 * Here is a sample flow for accessing smart card functionality:
 *   - Create context using sc_create_context()
 *   - Allocate a handle for accessing reader functionality using
 *         sc_allocate_handle( context, SC_HANDLE_READER_SLOT_LOGICAL, reader_name )
 *   - Obtain supported card drivers that can work with the card in the reader using
 *         sc_get_card_types_for_reader()
 *   - Chose the card driver to use and allocate card holder verifier handle using
 *         sc_allocate_handle( context, SCS_HANDLE_CARD_HOLDER_VERIFIER, chosen_card_name )
 *   - Attach to the card via reader using
 *         sc_attach_by_reader( context, reader_name, SCARD_SHARE_EXCLUSIVE )
 *   - Execute required actions on the card.
 *   - Detach using sc_detach().
 *   - Destroy context using sc_destroy_context().
 */


#ifndef SC_SMART_CARD_H
#define SC_SMART_CARD_H

#include <smartcard/sc_data_types.h>
#include <smartcard/sc_crypto_system.h>
#include <smartcard/sc_key_store_data.h>
#include <smartcard/sc_reader_state.h>
#include <smartcard/sc_smart_card_id.h>

#include <sys/types.h>
#include <sys/platform.h>


__BEGIN_DECLS


/**
 * Smart card operations require a valid smart card context to be initialized.
 * When smart card context is no longer required it should be destroyed.
 */
typedef struct _sc_context_t sc_context_t;


/**
 * Creates a new context used to describe the environment within which individual
 * smart card operations are performed.
 *
 * When context is no longer needed, use @c sc_context_destroy() function to
 * destroy the instance.
 *
 * @param [out] context
 *      Created smart card context. Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_context_create( sc_context_t** context );


/**
 * Similarly to @c sc_create_context, this function creates a new context.
 * However, the extended functionality context also provides functionality
 * for using extended smart card services. This functionality is protected
 * by _sys_access_extended_smartcard_functionality system capability.
 *
 * When no longer needed, the context instance should be destroyed using
 * @c sc_context_destroy() function.
 *
 * @param [out] context
 *      Created smart card context. Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_context_create_extended( sc_context_t** context );


/**
 * Destroys the specified context.
 *
 * @param [in] context
 *      Smart card context instance to be destroyed. Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_context_destroy( sc_context_t* context );


/**
 * Allocates a handle for the specified resource. Resources are identified by
 * type and name. While all resources have a specific type, not all resources
 * have an associated name. Generally, all reader and card resources require a
 * name to be specified.
 *
 * Note that only a single instance of each type of handle can be stored within
 * a context. Attempting to associate multiple instances of a single type of
 * handle will result in an error to be returned.
 *
 * When a handle is no longer required, the handle should be deallocated using
 * @c sc_free_handle function.
 *
 * @param [in] context
 *      Active smart card context. Must not be NULL.
 * @param [in] handle_type
 *      The type of the resource for which a handle is being requested.
 * @param [in] handle_name
 *      The name of the resource for which a handle is being requested.
 *      This can be NULL if the resource does not have an associated name.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_allocate_handle( sc_context_t* context,
                                       sc_handle_type_t handle_type,
                                       const char* handle_name );


/**
 * De-allocates the specified handle.
 *
 * @param [in] context
 *      Active smart card context. Must not be NULL.
 * @param [in] handle_type
 *      The type of the resource for which a handle is being freed.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_free_handle( sc_context_t* context,
                                   sc_handle_type_t handle_type );


/**
 * Opens a session to the smart card located in a given reader. If the reader
 * is unknown to the smart card subsystem, then an error is returned. Other
 * connection options will be set by the driver to optimize communication
 * with the card.
 *
 * Before opening a session to a smart card, a card handle must first have been
 * allocated. Otherwise, an error is returned.
 *
 * @param [in] context
 *      Active smart card context. Must not be NULL.
 * @param [in] reader_name
 *      The name of the reader where the smart card to connect to is located.
 *      Must not be NULL.
 * @param [in] card_access_mode
 *      This parameter indicates whether the connection is open for shared
 *      or exclusive access. If the requested mode is unavailable, an error
 *      is returned.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_attach_by_reader( sc_context_t* context,
                                        const char* reader_name,
                                        sc_card_access_mode_t card_access_mode );


/**
 * Opens a session to the smart card corresponding to a card ID. If the desired
 * card is not found, the user will be prompted to insert the card specified by
 * the provided card ID.
 *
 * If this function succeeds, then a smart card handle will be added to the
 * provided context. As such, it is necessary to explicitly release the handle
 * using the @c sc_free_handle() function before another smart card handle can
 * be allocated.
 *
 * @param [in] context
 *      Active smart card context. Must not be NULL.
 * @param [in] smart_card_id
 *      Smart card ID to attach to. Must not be NULL.
 * @param [in] handle_type
 *      The type of smart card resource the session will be used with. For
 *      example, if the smart card will be used to perform cryptographic
 *      operations, then a value of SC_HANDLE_CARD_CRYPTO_PROVIDER_X should be
 *      specified.
 * @param [in] card_access_mode
 *      This parameter indicates whether the connection is opened for shared
 *      or exclusive access. If the requested mode is unavailable, an error
 *      is returned.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      If the requested card is not available, SCARD_E_ICC_UNAVAILABLE is returned.
 *      If the reader required to read the card is not available,
 *      SCARD_E_READER_IN_USE is returned.
 *      If the function fails for any other reason, an error code is returned.
 */
sc_response_code_t sc_attach_by_smart_card_id( sc_context_t* context,
                                               sc_smart_card_id_t* smart_card_id,
                                               sc_handle_type_t handle_type,
                                               sc_card_access_mode_t card_access_mode );


/**
 * Closes any open smart card session.
 * If no connection is currently opened, then an error is returned.
 *
 * Upon termination, the action indicated by @c disposition action is
 * performed, if possible. Allowed actions include:
 *
 * - leave the card
 * - reset the card
 * - power down and close the card
 * - eject the card
 *
 * Any application may reset the card, even in shared access mode. Power-down
 * and eject actions will succeed only if the application has exclusive
 * access to the card.
 *
 * @param [in] context
 *      Active smart card context. Must not be NULL.
 * @param [in] card_disposition
 *      Disposition action to be performed upon termination.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_detach( sc_context_t* context,
                              sc_card_disposition_t card_disposition );


/**
 * Re-establishes an existing connection to a smart card.
 * Example uses of this function include:
 *
 * - Changing the mode of an existing connection (via the @c flags
 *   parameter).
 *
 * Note that a connection must have previously been established, otherwise
 * an error is returned.
 *
 * @param [in] context
 *      Active smart card context. Must not be NULL.
 * @param [in] card_access_mode
 *      This parameter indicates whether the connection is opened for shared
 *      or exclusive access. If the requested mode is unavailable, an error
 *      is returned.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_reconnect( sc_context_t* context,
                                 sc_card_access_mode_t card_access_mode );



/**
 * Cancels all outstanding smart card operations
 * excluding calls to @c sc_get_status_change().
 *
 * @param [in] context
 *      Active smart card context. Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_cancel( sc_context_t* context );


/**
 * Retrieves the list of all available smart card readers.
 *
 * @param [in] context
 *      Active smart card context. Must not be NULL.
 * @param [in,out] readers
 *      The reader array that will be used to write all the available readers to.
 *      If NULL, only the number of available smart card readers is retrieved.
 * @param [in,out] num_readers
 *      On input, this value indicates the number of elements in the @c readers
 *      array.
 *      On output, the value contains the number of reader names that were
 *      written to @c readers array. Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_list_readers( sc_context_t* context,
                                    sc_reader_name_t* readers,
                                    size_t* num_readers );


/**
 * Retrieves the list of all available card types matching the supplied ATR.
 * If ATR parameter is NULL, all cards match the supplied criteria.
 *
 * Matching for the ATR is determined by examining each registered card type
 * and performing byte-wise comparison of the card driver registered ATR
 * against the supplied ATR.
 *
 * @param [in] context
 *      Active smart card context. Must not be NULL.
 * @param [in] atr
 *      The ATR to compare against registered card types. May be NULL.
 * @param [in,out] cards
 *      The card array that will be used to write all the available cards to.
 *      If NULL, only the number of available card types is retrieved.
 * @param [in,out] num_cards
 *      On input, this value indicates the length of the @c cards
 *      array.
 *      On output, this contains the number of card names that were
 *      written to @c cards array. Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_list_card_types( sc_context_t* context,
                                       const sc_atr_string_t* atr,
                                       sc_card_name_t* cards,
                                       size_t* num_cards );


/**
 * Retrieves card states for the cards of interest.
 * The value of the @c event_state field of each @c sc_reader_state_t instance
 * indicates whether a card matching one of the specified card types is present.
 * Unknown card types are ignored.
 * If an unknown reader is specified then an error is returned.
 *
 * To block pending insertion of the desired card types use the
 * @c sc_get_status_change() function.
 *
 * @param [in] context
 *      Active smart card context. Must not be NULL.
 * @param [in] cards
 *      Array of card types of interest.
 * @param [in] num_cards
 *      Number of elements in @c cards array.
 * @param [in,out] reader_states
 *      On input, the array describes the set of readers of interest.
 *      On output, the array contains information indicating whether a card
 *      matching one of the specified card types is present.
 * @param [in] num_reader_states
 *      Number of elements in @c reader_states array.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_locate_cards( sc_context_t* context,
                                    const sc_card_name_t* cards,
                                    size_t num_cards,
                                    sc_reader_state_t** reader_states,
                                    size_t num_reader_states );


/**
 * Retrieves list of card types matching the ATR of the card in the reader
 * associated with the provided context. This function is useful in
 * determining which card types can be used to manipulate the card in the
 * reader.
 *
 * A handle of type @c SC_HANDLE_READER_SLOT_LOGICAL must be
 * allocated before calling this function, otherwise an error is returned.
 *
 * @param [in] context
 *      Active smart card context. Must not be NULL.
 * @param [in,out] cards
 *      Array of card types that can drive the card in the reader.
 *      If NULL, only the number of available card types is retrieved.
 * @param [in,out] num_cards
 *      On input, this value indicates the number of elements in @c cards array.
 *      On output, the value indicates the number of card names that were
 *      written to @c cards array. Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_get_card_types_for_reader( sc_context_t* context,
                                                 sc_card_name_t* cards,
                                                 size_t* num_cards );


/**
 * Waits until there is a status change in the provided list of readers or the
 * specified timeout period expires. A timeout value of @c SC_INFINITE is used
 * to indicate that the calling application is willing to wait forever.
 * A timeout value of zero is used to indicate that the function should return
 * immediately.
 *
 * If an unknown reader is specified, then an error is returned.
 *
 * Note that this function will provide information on when cards are removed
 * or inserted into one of the specified readers. It does not indicate
 * anything about the card types that may be in a specified reader. This
 * ensures that the calling application is made aware of all changes across
 * the readers of interest making it possible to present appropriate UI.
 *
 * @param [in] context
 *      Active smart card context. Must not be NULL.
 * @param [in,out] reader_states
 *      On input, the array describes the set of the readers of interest and the
 *      current states that the caller believes each reader is in.
 *      On output, the array contains updated information about each readers state.
 *      The list must contain at least one item.
 * @param [in] num_reader_states
 *      Number of elements in @c reader_states array.
 * @param [in] timeout
 *      The amount of time in milliseconds to wait before unblocking.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_get_status_change( sc_context_t* context,
                                         sc_reader_state_t** reader_states,
                                         size_t num_reader_states,
                                         unsigned int timeout );


/**
 * Terminates all outstanding smart card actions. Only requests that require
 * waiting for external action by a smart card or user can be canceled.
 * Any such outstanding requests will terminate with a result code
 * indicating that the action was canceled. It is particularly useful to
 * cancel outstanding calls to @c sc_get_status_change().
 *
 * @param [in] context
 *      Active smart card context. Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_cancel_get_status_change( sc_context_t* context );


/**
 * Retrieves an identifier uniquely identifying the currently connected smart
 * card. If no connection is currently opened, an error is returned.
 *
 * @param [in] context
 *      Active smart card context. Must not be NULL.
 * @param [out] smart_card_id
 *      Smart card ID instance used to store the requested identifier.
 *      Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_get_smart_card_id( sc_context_t* context,
                                         sc_smart_card_id_t* smart_card_id );


/**
 * Retrieves key store data associated with the keys stored on the card.
 * The returned collection of key store data describes all private and symmetric
 * keys stored on the card including any certificates associated with those
 * keys.
 *
 * A handle of type @c SC_HANDLE_CARD_CRYPTO_PROVIDER_X must be
 * allocated before calling this function, otherwise an error is returned.
 *
 * @param [in] context
 *      Active smart card context. Must not be NULL.
 * @param [in,out] key_store_data
 *      Array of key store data instances to be populated by data.
 *      If NULL, only the size of the key store data collection is retrieved.
 * @param [in,out] num_key_store_data_elements
 *      On input, this value indicates the number of elements in
 *      @c key_store_data array.
 *      On output, the value specifies the number of key store data instances
 *      that were populated with data.
 *      Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_get_key_store_data( sc_context_t* context,
                                          sc_key_store_data_t** key_store_data,
                                          size_t* num_key_store_data_elements );


/**
 * Initializes the smart card in preparation to perform encryption operations
 * with the specified cryptographic system and key.
 *
 * A handle of type @c SC_HANDLE_CARD_CRYPTO_PROVIDER_X must be
 * allocated before calling this function, otherwise an error is returned.
 *
 * @param [in] context
 *      Active smart card context. Must not be NULL.
 * @param [in] crypto_system
 *      Cryptographic system to use for encryption operation.
 * @param [in] key
 *      A cryptographic token describing the key to use for encryption
 *      operation.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_encrypt_init( sc_context_t* context,
                                    const sc_crypto_system_t* crypto_system,
                                    const sc_crypto_token_t* key );


/**
 * Encrypts plaintext data in a single part.
 *
 * Depending on card driver implementation, this function may or may not be
 * called multiple times without re-initializing.
 *
 * A handle of type @c SC_HANDLE_CARD_CRYPTO_PROVIDER_X must be
 * allocated before calling this function, otherwise an error is returned.
 *
 * @param [in] context
 *      Active smart card context. Must not be NULL.
 * @param [in] plaintext
 *      The input buffer containing the plaintext to be encrypted.
 *      Must not be NULL.
 * @param [in] plaintext_length
 *      Plaintext buffer length.
 * @param [out] ciphertext
 *      The output buffer where the ciphertext data will be written.
 *      If NULL, only ciphertext length will be returned.
 * @param [in,out] ciphertext_length
 *      On input, ciphertext buffer length.
 *      On output, ciphertext length. Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_encrypt( sc_context_t* context,
                               const unsigned char* plaintext,
                               size_t plaintext_length,
                               unsigned char* ciphertext,
                               size_t* ciphertext_length );


/**
 * Initializes the smart card in preparation to perform decryption operations
 * with the specified cryptographic system and key.
 *
 * A handle of type @c SC_HANDLE_CARD_CRYPTO_PROVIDER_X must be
 * allocated before calling this function, otherwise an error is returned.
 *
 * @param [in] context
 *      Active smart card context. Must not be NULL.
 * @param [in] crypto_system
 *      Cryptographic system to use for decryption operation.
 * @param [in] key
 *      A cryptographic token describing the key to use for decryption
 *      operation.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_decrypt_init( sc_context_t* context,
                                    const sc_crypto_system_t* crypto_system,
                                    const sc_crypto_token_t* key );


/**
 * Decrypts encrypted data in a single part.
 *
 * Depending on card driver implementation, this function may or may not be
 * called multiple times without re-initalizing.
 *
 * A handle of type @c SC_HANDLE_CARD_CRYPTO_PROVIDER_X must be
 * allocated before calling this function, otherwise an error is returned.
 *
 * @param [in] context
 *      Active smart card context. Must not be NULL.
 * @param [in] ciphertext
 *      The input buffer containing the ciphertext to be decrypted.
 *      Must not be NULL.
 * @param [in] ciphertext_length
 *      Ciphertext buffer length.
 * @param [out] plaintext
 *      The output buffer where the plaintext data will be written.
 *      If NULL, only plaintext length will be returned.
 * @param [in,out] plaintext_length
 *      On input, plaintext buffer length.
 *      On output, plaintext length. Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_decrypt( sc_context_t* context,
                               const unsigned char* ciphertext,
                               size_t ciphertext_length,
                               unsigned char* plaintext,
                               size_t* plaintext_length );


/**
 * Initializes the smart card in preparation to perform signing operations with
 * the specified cryptographic system and key.
 *
 * A handle of type @c SC_HANDLE_CARD_CRYPTO_PROVIDER_X must be
 * allocated before calling this function, otherwise an error is returned.
 *
 * @param [in] context
 *      Active smart card context. Must not be NULL.
 * @param [in] crypto_system
 *      Cryptographic system to use for signing operation.
 * @param [in] key
 *      A cryptographic token describing the key to use for signing
 *      operation.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_sign_init( sc_context_t* context,
                                 const sc_crypto_system_t* crypto_system,
                                 const sc_crypto_token_t* key );


/**
 * Performs a signing operation.
 *
 * Depending on card driver implementation, this function may or may not be
 * called multiple times without re-initalizing.
 *
 * A handle of type @c SC_HANDLE_CARD_CRYPTO_PROVIDER_X must be
 * allocated before calling this function, otherwise an error is returned.
 *
 * @param [in] context
 *      Active smart card context. Must not be NULL.
 * @param [in] plaintext
 *      The input buffer containing the plaintext to be encrypted.
 *      Must not be NULL.
 * @param [in] plaintext_length
 *      Plaintext buffer length.
 * @param [out] signature
 *      The output buffer where the signature data will be written.
 *      If NULL, only signature length will be returned.
 * @param [in,out] signature_length
 *      On input, signature buffer length.
 *      On output, signature length. Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_sign( sc_context_t* context,
                            const unsigned char* plaintext,
                            size_t plaintext_length,
                            unsigned char* signature,
                            size_t* signature_length );


/**
 * Returns a buffer with random bytes generated by the card.
 * The data produced by this method should be cryptographically random.
 *
 * A handle of type @c SC_HANDLE_CARD_CRYPTO_PROVIDER_X must be
 * allocated before calling this function, otherwise an error is returned.
 *
 * @param [in] context
 *      Active smart card context. Must not be NULL.
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
sc_response_code_t sc_generate_random_data( sc_context_t* context,
                                            unsigned char* randomData,
                                            size_t* randomDataLength );


/**
 * Retrieves the number of PIN attempts remaining for the card.
 *
 * @param [in] context
 *      Active smart card context. Must not be NULL.
 * @param [out] num_attempts
 *      Number of remaining PIN attempts on the card. Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_get_number_of_remaining_pin_attempts( sc_context_t* context,
                                                            unsigned char* num_attempts );


/**
 * Retrieves the PIN type for the current card.
 *
 * @param [in] context
 *      Active smart card context. Must not be NULL.
 * @param [out] code_type
 *      Code type. Must not be NULL.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_get_pin_type( sc_context_t* context,
                                    sc_code_type_t* code_type );


/**
 * Performs card holder verification.
 *
 * If code is supplied, it is sent to the card for verification.
 * If no code is supplied, then the user will be prompted for smart card PIN.
 * If the CHV requirements for the currently selected path are already satisfied,
 * e.g. by a prior CHV, then the service provider may simply return success.
 *
 * A handle of type @c SC_HANDLE_CARD_HOLDER_VERIFIER must be
 * allocated before calling this function, otherwise an error is returned.
 *
 * @param [in] context
 *      Active smart card context. Must not be NULL.
 * @param [in] code
 *      Smart card code (e.g. PIN) used to authenticate user to the card.
 *      If NULL, user will be prompted for smart card PIN.
 * @param [in] code_length
 *      Code length
 * @param [in] ihv_mode
 *      Indicates whether the CHV (Card Holder Verification) is to be made
 *      against a local (SC_FL_IHV_LOCAL) or global (SC_FL_IHV_GLOBAL) code.
 *      If the SC_FL_IHV_CHECKONLY flag is specified, then no UI should be
 *      presented to obtain CHV from device user.
 * @param [in,out] ref
 *      A vendor-specific reference value.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_verify( sc_context_t* context,
                              const unsigned char* code,
                              size_t code_length,
                              sc_ihv_mode_t ihv_mode,
                              unsigned int* ref );


/**
 * Changes smart card PIN on the card.
 *
 * @param [in] context
 *      Active smart card context. Must not be NULL.
 * @param[in] old_code
 *      Old smart card code. May be NULL.
 *      E.g. NULL May be provided to initialize a card with PIN.
 * @param[in] old_code_length
 *      Old smart card code.
 * @param[in] old_code_length
 *      New smart card code.
 * @param[in] new_code_length
 *      New smart card code length.
 * @param [in] ihv_mode
 *      Indicates whether the CHV (Card Holder Verification) is to be made
 *      against a local (SC_FL_IHV_LOCAL) or global (SC_FL_IHV_GLOBAL) code.
 *      If the SC_FL_IHV_CHECKONLY flag is specified, then no UI should be
 *      presented to obtain CHV from device user.
 * @param [in] ref
 *      A vendor-specific reference value.
 * @return
 *      If the function succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      Otherwise, an error code is returned.
 */
sc_response_code_t sc_change_code( sc_context_t* context,
                                   const unsigned char* old_code,
                                   size_t old_code_length,
                                   const unsigned char* new_code,
                                   size_t new_code_length,
                                   sc_ihv_mode_t ihv_mode,
                                   unsigned int ref );


/**
 * Sends a custom APDU command to a card.
 *
 * Context must be created via @c sc_context_create_extended
 * for this function to succeed.
 *
 * @param [in] context
 *      Active smart card context. Must not be NULL.
 * @param [in] request_apdu
 *      Raw request APDU. Must not be NULL.
 * @param [in] request_apdu_length
 *      Request APDU byte array.
 * @param [out] response_apdu
 *      Raw response APDU.
 *      If NULL, only response APDU length is returned.
 * @param [in,out] response_apdu_length
 *      Response APDU length.
 *      Must not be NULL.
 * @return
 *      If the method succeeds, @c SC_SCARD_S_SUCCESS is returned. If the method
 *      fails, an error code is returned.
 */
sc_response_code_t sc_send_apdu( sc_context_t* context,
                                 const unsigned char* request_apdu,
                                 size_t request_apdu_length,
                                 unsigned char* response_apdu,
                                 size_t* response_apdu_length );


/**
 * Generates a cryptographic key on the card.
 *
 * @param [in] context
 *      The active smart card context. Must not be NULL.
 * @param [in] crypto_system
 *      The cryptographic system instance specifying key parameters. Must not be NULL.
 * @param [in,out] key_store_data
 *      The instance of the key store data that identifies the key on the card.
 *      On input, if an existing key store data element is provided, the existing
 *      key referenced by this instance is replaced with a newly generated key.
 *      If a newly created (empty) key store data instance is provided,
 *      a new key is generated.
 *      On output, the instance of the key store data that identifies the newly generated key.
 *      Must not be NULL.
 * @return
 *      If the method succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      If the method fails, an error code is returned.
 */
sc_response_code_t sc_generate_key( sc_context_t* context,
                                    const sc_crypto_system_t* crypto_system,
                                    sc_key_store_data_t* key_store_data );


/**
 * Retrieves the public key associated with the specified key store data.
 *
 * @param [in] context
 *      The active smart card context. Must not be NULL.
 * @param [in] key_store_data
 *      The instance of the key store data that identifies the key on the card.
 *      Must not be NULL.
 * @param [out] public_key
 *      The output buffer where the public key data is written.
 *      The DER-encoded public key is returned in X.509 format.
 *      If NULL, only the public key length is returned.
 * @param [in,out] public_key_length
 *      On input, the length of the public key buffer.
 *      On output, the length of the public key.
 *      Must not be NULL.
 * @return
 *      If the method succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      If the method fails, an error code is returned.
 */
sc_response_code_t sc_get_public_key( sc_context_t* context,
                                      const sc_key_store_data_t* key_store_data,
                                      unsigned char* public_key,
                                      size_t* public_key_length );


/**
 * Imports the X.509 certificate to the smart card for the specified key.
 *
 * @param [in] context
 *      The active smart card context. Must not be NULL.
 * @param [in] certificate
 *      The certificate to import.
 *      The certificate should be DER-encoded in X.509 format.
 *      Must not be NULL.
 * @param [in] certificate_length
 *      The certificate length.
 * @param [in,out] key_store_data
 *      The instance of the key store data that identifies the key slot where
 *      the certificate should be imported. The key store data instance
 *      may be modified so it contains the correct key reference.
 *      In particular, the certificate data in the instance may be updated.
 *      Must not be NULL.
 * @return
 *      If the method succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      If the method fails, an error code is returned.
 */
sc_response_code_t sc_import_certificate( sc_context_t* context,
                                          const unsigned char* certificate,
                                          size_t certificate_length,
                                          sc_key_store_data_t* key_store_data );


/**
 * Imports a new key to the smart card.
 *
 * @param [in] context
 *      The active smart card context. Must not be NULL.
 * @param [in] certificate
 *      The certificate to import.
 *      The certificate should be DER-encoded in X.509 format.
 *      Must not be NULL.
 * @param [in] certificate_length
 *      The certificate length.
 * @param [in] private_key
 *      The private key to import.
 *      The private key should be DER-encoded in PKCS8 format and provided
 *      in plain text (PKCS8 should not be encrypted).
 *      Must not be NULL.
 * @param [in] private_key_length
 *      The length of the private key.
 * @param [in,out] key_store_data
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
sc_response_code_t sc_import_key( sc_context_t* context,
                                  const unsigned char* certificate,
                                  size_t certificate_length,
                                  const unsigned char* private_key,
                                  size_t private_key_length,
                                  sc_key_store_data_t* key_store_data );


/**
 * Removes the specified key from the card.
 *
 * @param [in] context
 *      The active smart card context. Must not be NULL.
 * @param [in] key_store_data
 *      The instance of the key store data that identifies the key on the card
 *      to be removed.
 *      Must not be NULL.
 * @return
 *      If the method succeeds, @c SC_SCARD_S_SUCCESS is returned.
 *      If the method fails, an error code is returned.
 */
sc_response_code_t sc_remove_key( sc_context_t* context,
                                  const sc_key_store_data_t* key_store_data );


__END_DECLS

#endif /* SC_SMART_CARD_H */
