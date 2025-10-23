/*
 * Research In Motion Limited. Copyright (C) 2013.
 * Research In Motion Limited. All rights reserved.
 */

/**
 * @file sc_data_types.h
 *
 * The files defines common smart card data types.
 * Most of the types are defined by PC/SC specification.
 *
 * PC/SC specification can be found at
 * http://www.pcscworkgroup.com/specifications/overview.php
 *
 * PC/SC spec parts 5 and 6 may of particular interest to developers.
 *
 * Acronyms that are being using in this API
 * (refer to PC/SC part 1 for more information):
 *
 *  - PC/SC - Smart card specification that is being followed in this API.
 *  - ATR -   Smart card answer to reset. A binary card type identifier.
 *  - DER -   Distinguished encoding rules. Often used for encoding cryptographic
 *            documents (e.g. certificates).
 *  - X509 -  Standard format for public key certificates.
 *  - ICC -   Integrated circuit card. A general name for smart cards.
 *  - IHV -   ICC holder verification.
 *  - CHV -   Card holder verification. Refers to a mechanism of
 *            authenticating card user to a card.
 *  - IFD -   Interface Device. A terminal, communication device, or machine
 *            to which the integrated circuit(s) card is electrically connected
 *            during operation. Essentially, IFD refers to smart card reader.
 *  - ICCSP - An ICCSP is a Service Provider that interfaces ICC functionality.
 */


#ifndef SC_DATA_TYPES_H
#define SC_DATA_TYPES_H


#include <limits.h>


__BEGIN_DECLS


/**
 * Maximum ATR length.
 */
#define SC_MAX_ATR_LENGTH 33

/**
 * Maximum card or reader name length.
 * This length includes NULL-terminating character.
 */
#define SC_MAX_NAME_LENGTH 37

/**
 * Maximum length of user-friendly card label.
 * This length includes NULL-terminating character.
 */
#define SC_MAX_CARD_LABEL_LENGTH 256


/**
 * Infinite timeout.
 */
#define SC_INFINITE UINT_MAX


/**
 * A string representing smart card ATR.
 */
typedef unsigned char   sc_atr_string_t[ SC_MAX_ATR_LENGTH ];

/**
 * A string representing card name.
 */
typedef char            sc_card_name_t[ SC_MAX_NAME_LENGTH ];

/**
 * A string representing card reader name.
 */
typedef char            sc_reader_name_t[ SC_MAX_NAME_LENGTH ];

/**
 * A string representing card label.
 */
typedef char            sc_card_label_t[ SC_MAX_CARD_LABEL_LENGTH ];


/**
 * Smart card interface handle types as defined by PC/SC specification.
 */
typedef enum
{
    /**
     * Handle for performing smart card manager operations.
     * Currently not supported.
     */
    SC_HANDLE_MANAGER                  = 0,

    /**
     * Handle for performing direct reader operations.
     * Currently not supported.
     */
    SC_HANDLE_READER                   = 1,

    /**
     * Handle for performing slot logical operations.
     */
    SC_HANDLE_READER_SLOT_LOGICAL      = 2,

    /**
     * Handle for performing direct card operations.
     * Currently not supported.
     */
    SC_HANDLE_CARD                     = 3,

    /**
     * Handle for performing card holder verification (CHV).
     * In particular, the interface allows PIN verification, getting the
     * number of remaining attempts, etc.
     */
    SC_HANDLE_CARD_HOLDER_VERIFIER     = 4,

    /**
     * Handle for performing cryptographic operations.
     * In particular, the interface allows encrypt, decrypt, sign.
     */
    SC_HANDLE_CARD_CRYPTO_PROVIDER_X   = 5,

    /**
     * Handle for sending custom APDU commands to the card.
     */
    SC_HANDLE_CUSTOM_COMMAND_PROVIDER  = 6

} sc_handle_type_t;


/**
 * Reader states that may be be assigned to
 * "current state" and "event state" fields of sc_reader_state_t instance.
 */
typedef enum
{
    /**
     * When appears in current state:
     * The application is unaware of the current state, and would like to know.
     * The use of this value results in an immediate return from state
     * transition-monitoring services. This is represented by all bits set to zero.
     */
    SC_SCARD_STATE_UNAWARE        = 0x00000001,

    /**
     * When appears in current state:
     * The application is not interested in this reader, and it should not be
     * considered during monitoring operations. If this bit value is set, all
     * other bits are ignored.
     *
     * When appears in event state:
     * The application requested that this reader be ignored. No other bits
     * will be set.
     */
    SC_SCARD_STATE_IGNORE         = 0x00000002,

    /**
     * When appears in current state:
     * The application believes that this reader is not available for use. If
     * this bit is set, then all the following bits are ignored.
     *
     * When appears in event state:
     * This implies that the actual state of this reader is not available. If
     * this bit is set, then all the following bits are clear.
     */
    SC_SCARD_STATE_UNAVAILABLE    = 0x00000004,

    /**
     * When appears in current state:
     * The application believes that there is not a card in the reader. If this
     * bit is set, all the following bits are ignored.
     *
     * When appears in event state:
     * This implies that there is no card in the reader. If this bit is set,
     * all the following bits will be clear.
     */
    SC_SCARD_STATE_EMPTY          = 0x00000008,

    /**
     * When appears in current state:
     * The application believes that there is a card in the reader.
     *
     * When appears in event state:
     * This implies that there is a card in the reader.
     */
    SC_SCARD_STATE_PRESENT        = 0x00000010,

    /**
     * When appears in current state:
     * The application believes that there is a card in the reader with an ATR
     * matching one of the target cards. If this bit is set,
     * @c SC_SCARD_STATE_PRESENT is assumed.
     *
     * When appears in event state:
     * This implies that there is a card in the reader with an ATR matching one
     * of the target cards. If this bit is set, @c SC_SCARD_STATE_PRESENT will
     * also be set. This bit is returned only by the @c sc_locate_cards() function.
     */
    SC_SCARD_STATE_ATRMATCH       = 0x00000020,

    /**
     * When appears in current state:
     * The application believes that the card in the reader is allocated for
     * exclusive use by another application. If this bit is set,
     * @c SC_SCARD_STATE_PRESENT is assumed.
     *
     * When appears in event state:
     * This implies that the card in the reader is allocated for exclusive
     * use by another application. If this bit is set,
     * @c SC_SCARD_STATE_PRESENT will also be set.
     */
    SC_SCARD_STATE_EXCLUSIVE      = 0x00000040,

    /**
     * When appears in current state:
     * The application believes that the card in the reader is in use by one or
     * more other applications, but may be connected to in shared mode.
     * If this bit is set, @c SC_SCARD_STATE_PRESENT is assumed.
     *
     * When appears in event state:
     * This implies that the card in the reader is in use by one or more other
     * applications, but may be connected to in shared mode. If this bit is
     * set, SCARD_STATE_PRESENT will also be set.
     */
    SC_SCARD_STATE_INUSE          = 0x00000080,

    /**
     * When appears in event state:
     * This implies that there is a difference between the state input by the
     * calling application, and the current state. When this bit is set, the
     * application may assume a significant state change has occurred on this
     * reader.
     */
    SC_SCARD_STATE_CHANGED        = 0x00000100,

    /**
     * When appears in event state:
     * This implies that the given reader name is not recognized by the
     * Resource Manager. If this bit is set, then @c SC_SCARD_STATE_CHANGED
     * will also be set.
     */
    SC_SCARD_STATE_UNKNOWN        = 0x00000200,

    /**
     * When appears in current or event state:
     * This value means that the reader is not connected to a device.
     */
    SC_SCARD_STATE_NOT_CONNECTED  = 0x00000400  // not an official PC/SC state

} sc_reader_state_value_t;


/**
 * Card disposition actions are used to indicate the desired disposition of the
 * card following a Transaction or when a connection is terminated.
 */
typedef enum
{
    /**
     * Do not alter card state.
     */
    SC_SCARD_LEAVE_CARD         = 0,

    /**
     * Reset the card.
     */
    SC_SCARD_RESET_CARD         = 1,

    /**
     * Un-power and terminate access to the card.
     */
    SC_SCARD_UNPOWER_CARD       = 2,

    /**
     * Eject the card from the reader.
     */
    SC_SCARD_EJECT_CARD         = 3,

    /**
     * Used to indicate that a sophisticated commercial reader should move the
     * card to the confiscation bin and not return it to the user.
     */
    SC_SCARD_CONFISCATE_CARD    = 4,

    /**
     * Keeps the card powered until client detaches requesting card reset or power-down.
     * This card disposition action is not part of PC/SC specification.
     */
    SC_SCARD_KEEP_CARD_POWERED  = 5

} sc_card_disposition_t;


/**
 * Card access modes are used to indicate mode of access to a card.
 */
typedef enum
{
    /**
     * Application is willing to share access to card with other applications.
     */
    SC_SCARD_SHARE_SHARED       = 0x00000001,

    /**
     * Application requires exclusive access to the card.
     */
    SC_SCARD_SHARE_EXCLUSIVE    = 0x00000002,

    /**
     * Application requires connection to reader whether or not card is present.
     * Implies exclusive access.
     */
    SC_SCARD_DIRECT             = 0x00000004,

    /**
     * Application is not willing to show any UI such as PIN prompt or Insert Card dialogs.
     * This is not a PC/SC flag.
     */
    SC_SCARD_NO_UI              = 0x00000008,

    /**
     * Application is willing to show PIN prompt over the lock screen.
     * This is not a PC/SC flag.
     */
    SC_SCARD_PIN_OVER_LOCK_SCREEN = 0x00000010

} sc_card_access_mode_t;


/**
 * ICC holder verification modes modes.
 */
typedef enum
{
    /**
     * Global ICC holder verification.
     */
    SC_FL_IHV_GLOBAL       = 0x00000001,

    /**
     * Local ICC holder verification.
     */
    SC_FL_IHV_LOCAL        = 0x00000002,

    /**
     * Enable ICC holder verification.
     */
    SC_FL_IHV_ENABLE       = 0x00000004,

    /**
     * Disable ICC holder verification.
     */
    SC_FL_IHV_DISABLE      = 0x00000008,

    /**
     * Change ICC holder code (PIN).
     */
    SC_FL_IHV_CHANGE       = 0x00000010,

    /**
     * Indicates to the ICCSP that it should not pop up a dialog requesting
     * input of CHV information; rather, only the CHV state should be returned.
     */
    SC_FL_IHV_CHECKONLY    = 0x00000020,

    /**
     * Forces ICC holder verification even if the previous CHV was successful
     * or code (PIN) is cached.
     * Not an official PC/SC CHV flag.
     */
    SC_FL_IHV_FORCEVERIFY  = 0x00000040

} sc_ihv_mode_t;


/**
 * Card PIN types.
 */
typedef enum
{
    /**
     * Alphanumeric PIN type.
     */
    SC_CODE_TYPE_ALPHANUMERIC  = 0,

    /**
     * Numeric PIN type.
     */
    SC_CODE_TYPE_NUMERIC       = 1,

    /**
     * Alpha-only PIN type.
     */
    SC_CODE_TYPE_ALPHA         = 2

} sc_code_type_t;


/**
 * Cryptographic algorithm types.
 */
typedef enum
{
    /**
     * Cryptographic algorithm is not specified or not known.
     */
    SC_CRYPTO_ALGORITHM_NONE          = 0,

    /**
     * Raw RSA cryptographic algorithm.
     * The algorithm only performs key exponentiation; no padding is added or removed.
     * Padded input is expected. Padding should be added by the caller.
     */
    SC_CRYPTO_ALGORITHM_RSA           = 1,

    /**
     * Unpadded RSA cryptographic algorithm.
     * The algorithm adds padding and performs key exponentiation.
     * Unpadded input is expected.
     * Padding will be added by the smart card driver, or the smart card.
     */
    SC_CRYPTO_ALGORITHM_RSA_UNPADDED  = 2,

    /**
     * DSA cryptographic algorithm.
     */
    SC_CRYPTO_ALGORITHM_DSA           = 3,

    /**
     * ECDSA cryptographic algorithm.
     */
    SC_CRYPTO_ALGORITHM_ECDSA         = 4,

    /**
     * ECGDSA cryptographic algorithm.
     */
    SC_CRYPTO_ALGORITHM_ECGDSA        = 5

} sc_crypto_algorithm_t;


/**
 * Protocol identifiers that define the protocols used in communication with the card.
 * These must be defined such that a protocol maps to a specific bit position
 * so that multiple protocols may be specified by combining them with a bitwise
 * OR operation.
 */
typedef enum
{
    /**
     * Protocol undefined.
     */
    SC_SCARD_PROTOCOL_UNDEFINED  = 0x00000001,

    /**
     * Provides hint to reader that it should use default communication
     * parameters to establish communication with the card.
     */
    SC_SCARD_PROTOCOL_DEFAULT    = 0x00000002,

    /**
     * Provides hint to reader that it should attempt to negotiate optimal
     * communications settings with the card.
     */
    SC_SCARD_PROTOCOL_OPTIMAL    = 0x00000004,

    /**
     * ISO/IEC 7186 T=0 protocol.
     */
    SC_SCARD_PROTOCOL_T0         = 0x00000008,

    /**
     * ISO/IEC 7186 T=1 protocol.
     */
    SC_SCARD_PROTOCOL_T1         = 0x00000010,

    /**
     * Raw protocol.
     */
    SC_SCARD_PROTOCOL_RAW        = 0x00000020,

    /**
     * App Data protocol.
     */
    SC_SCARD_PROTOCOL_APPDATA    = 0x00000040

} sc_protocol_t;


/**
 * Response codes as defined by PC/SC specification.
 */
typedef enum
{
    /**
     * @name Success codes
     * @{
     */

    /**
     * No error was encountered.
     */
    SC_SCARD_S_SUCCESS                       = 0,

    /**
     * Device success code.
     */
    SC_DEVICE_SUCCESS                        = 0,

    /**
     * Reader success code.
     */
    SC_IFD_SUCCESS                           = 0,

    /**
     * @}
     *
     * @name Error codes
     * @{
     */

    /**
     * One or more of the supplied parameters' values is not valid.
     */
    SC_SCARD_E_INVALID_VALUE                 = -1,

    /**
     * The specified IFD name is not recognized.
     */
    SC_SCARD_E_UNKNOWN_READER                = -2,

    /**
     * The specified ICC name is not recognized.
     */
    SC_SCARD_E_UNKNOWN_CARD                  = -3,

    /**
     * Function not implemented or not available at the moment.
     */
    SC_E_NOTIMPL                             = -4,

    /**
     * The supplied handle was invalid.
     */
    SC_SCARD_E_INVALID_HANDLE                = -5,

    /**
     * An attempt was made to end a non-existent transaction.
     */
    SC_SCARD_E_NOT_TRANSACTED                = -6,

    /**
     * Reader error when reading a tag.
     */
    SC_IFD_ERROR_TAG                         = -7,

    /**
     * IO failure.
     */
    SC_SCARD_E_IO                            = -8,

    /**
     * Invalid data or buffer length.
     */
    SC_SCARD_E_INVALID_LENGTH                = -9,

    /**
     * Connected card is invalid.
     */
    SC_SCARD_E_INVALID_CARD                  = -10,

    /**
     * Verify operation failed.
     * Not an official PC/SC code.
     */
    SC_SCARD_E_VERIFY_FAILED                 = -11,

    /**
     * Not enough memory available to complete this command.
     */
    SC_SCARD_E_NO_MEMORY                     = -12,

    /**
     * Invalid certificate.
     */
    SC_SCARD_E_INVALID_CERT                  = -14,

    /**
     * The operation requires an ICC, but no ICC is currently in the device.
     */
    SC_SCARD_E_NO_SMARTCARD                  = -15,

    /**
     * Reader is not connected.
     * Not an official PC/SC code.
     */
    SC_SCARD_E_NOT_CONNECTED                 = -16,

    /**
     * An internal consistency check failed.
     */
    SC_SCARD_F_INTERNAL_ERROR                = -17,

    /**
     * A system or service is in invalid state.
     * Not an official PC/SC code.
     */
    SC_SCARD_E_INVALID_STATE                 = -18,

    /**
     * The specified IFD is not currently available for use.
     */
    SC_SCARD_E_READER_UNAVAILABLE            = -20,

    /**
     * Reader is currently in use, and cannot be shared.
     * Not an official PC/SC code.
     */
    SC_SCARD_E_READER_IN_USE                 = -21,

    /**
     * The data buffer to receive returned data is too small for the returned data.
     */
    SC_SCARD_E_INSUFFICIENT_BUFFER           = -22,

    /**
     * Action is not supported.
     * Not an official PC/SC code.
     */
    SC_SCARD_E_NOT_SUPPORTED                 = -23,

    /**
     * Service or component is not found.
     * Not an official PC/SC code.
     */
    SC_SCARD_E_NOT_FOUND                     = -24,

    /**
     * The requested protocols are incompatible with the protocol currently in
     * use with the ICC.
     */
    SC_SCARD_E_PROTO_MISMATCH                = -25,

    /**
     * Reader PTS failure.
     */
    SC_IFD_ERROR_PTS_FAILURE                 = -26,

    /**
     * Reader not supported error.
     */
    SC_IFD_ERROR_NOT_SUPPORTED               = -27,

    /**
     * Reader protocol is not supported.
     */
    SC_IFD_PROTOCOL_NOT_SUPPORTED            = -28,

    /**
     * The IFD or ICC is not ready to accept commands.
     */
    SC_SCARD_E_NOT_READY                     = -29,

    /**
     * Error occurred on power action.
     */
    SC_IFD_ERROR_POWER_ACTION                = -30,

    /**
     * The specified timeout value has expired.
     */
    SC_SCARD_E_TIMEOUT                       = -31,

    /**
     * The action was cancelled.
     */
    SC_SCARD_E_CANCELLED                     = -32,

    /**
     * Communication error with the reader.
     */
    SC_IFD_COMMUNICATION_ERROR               = -33,

    /**
     * Reader response timeout.
     */
    SC_IFD_RESPONSE_TIMEOUT                  = -34,

    /**
     * Service is not available.
     */
    SC_SCARD_E_SERVICE_UNAVAILABLE           = -35,

    /**
     * ICC is not available.
     * Not an official PC/SC code.
     */
    SC_SCARD_E_ICC_UNAVAILABLE               = -36,

    /**
     * There are no operations to cancel.
     */
    SC_SCARD_E_NO_OPERATIONS_TO_CANCEL       = -37,

    /**
     * Operation has been canceled.
     */
    SC_SCARD_E_CANCELED_OPERATION            = -38,

    /**
     * @}
     *
     * @name Warning codes and miscellaneous status codes
     * @{
     */

    /**
     * ICC is present in the reader.
     */
    SC_IFD_ICC_PRESENT           = 1,

    /**
     * ICC is not present in the reader.
     */
    SC_IFD_ICC_NOT_PRESENT       = 2,

    /**
     * Operation has been canceled by user.
     */
    SC_SCARD_W_CANCELLED_BY_USER = 3,

    /**
     * The card has been reset, so any shared state information is invalid.
     * This error may be cleared by the SCardReconnect service.
     */
    SC_SCARD_W_RESET_CARD        = 4,

    /**
     * The reader cannot communicate with the card, due to ATR configuration
     * conflicts. This error may be cleared by the SCardReconnect service.
     */
    SC_SCARD_W_UNSUPPORTED_CARD  = 5,

    /**
     * A Verify failed because the wrong PIN was presented.
     */
    SC_SCARD_W_WRONG_CHV         = 6,

    /**
     * A Verify is blocked because the maximum number of PIN submission
     * attempts has been reached.
     */
    SC_SCARD_W_CHV_BLOCKED       = 7,

    /**
     * CHV verification is not initialized.
     * Not an official PC/SC code.
     */
    SC_SCARD_W_CHV_UNINITIALIZED = 8

    /**
     * @}
     */

} sc_response_code_t;


__END_DECLS

#endif /* SC_DATA_TYPES_H */
