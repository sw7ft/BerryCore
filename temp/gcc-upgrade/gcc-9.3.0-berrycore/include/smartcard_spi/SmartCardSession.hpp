/*
 * SmartCardSession.hpp
 *
 * Copyright Research In Motion Limited, 2012-2013
 */

#ifndef SMARTCARD_SPI_SMARTCARDSESSION_HPP
#define SMARTCARD_SPI_SMARTCARDSESSION_HPP


#include <smartcard_spi/SmartCardDataTypes.hpp>
#include <smartcard_spi/SmartCardIoHeader.hpp>
#include <smartcard_spi/SmartCardHolderVerifier.hpp>


namespace smartcard_spi
{


/**
 * The SmartCardSession interface provides an API for managing and manipulating
 * connections to smart cards and smart card readers facilitating communication
 * between them and smart card drivers.
 */
class SmartCardSession
{

public:

    /**
     * Opens connection to the card located in a given reader.
     *
     * @param [in] deviceName
     *      The reader device name holding the card to connect to.
     *      The specified device must be a slot logical device.
     * @param [in] flags
     *      This parameter describes the desired access mode and is used to
     *      indicate three things:
     *       - First, it indicates whether the connection is opened for shared
     *         or exclusive access. If the requested mode is unavailable an error
     *         is returned.
     *       - Second, it indicates whether the caller desires a "direct"
     *         connection to the reader. Direct mode implies that a connection
     *         will be established even if a card is not present.
     *       - Finally, it is a hint to the reader indicating whether it
     *         should use default reader-card communication settings to attempt to
     *         optimize those settings if the card is still in negotiable mode as
     *         defined by ISO/IEC 7816.
     * @param [in] preferredProtocols
     *      The set of protocols that can be used when initializing the
     *      connection to the card. Note that only one of the protocols
     *      identified in this parameter will be used. If none of the listed
     *      protocols is available then an error is returned.
     * @param [out] activeProtocol
     *      The actual protocol used in the connection to the smart card.
     * @return
     *      In case of success, @c SCARD_S_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t connect( const sc_reader_name_t& deviceName,
                                        unsigned int flags,
                                        unsigned int preferredProtocols,
                                        sc_protocol_t& activeProtocol ) = 0;


    /**
     * Re-establishes an existing connection to a smart card.
     * Example uses of this method include:
     *
     * - Changing the mode of an existing connection (via the @c flags parameter).
     * - Acknowledging and clearing error conditions preventing access to the card.
     *
     * Note that a connection must have previously been established, otherwise
     * an error is returned.
     *
     * @param [in] flags
     *      This parameter describes the desired access mode and is used to
     *      indicate three things:
     *       - First, it indicates whether the connection is opened for shared
     *         or exclusive access. If the requested mode is unavailable an error
     *         is returned.
     *       - Second, it indicates whether the caller desires a "direct"
     *         connection to the reader. Direct mode implies that a connection
     *         will be established even if a card is not present.
     *       - Finally, it is a hint to the reader indicating whether it
     *         should use default reader-card communication settings to attempt to
     *         optimize those settings if the card is still in negotiable mode as
     *         defined by ISO/IEC 7816.
     * @param [in] preferredProtocols
     *      The set of protocols that can be used when initializing the
     *      connection to the card. Note that only one of the protocols
     *      identified in this parameter will be used. If none of the listed
     *      protocols is available then an error is returned.
     * @param [in] dispositionAction
     *      The desired action to be performed as part of reestablishing the
     *      connection to the card.
     * @param [out] activeProtocol
     *      The actual protocol used in the connection to the smart card.
     * @return
     *      In case of success, @c SCARD_S_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t reconnect( unsigned int flags,
                                          unsigned int preferredProtocols,
                                          sc_card_disposition_t dispositionAction,
                                          sc_protocol_t& activeProtocol ) = 0;


    /**
     * Terminates the current smart card connection.
     * If no connection is currently active, then an error is returned.
     *
     * Upon termination, the action indicated by @c dispositionAction is
     * performed if possible.
     *
     * Any application may reset the card, even in shared access mode.
     * Power-down and eject actions will succeed only if the application has exclusive
     * access to the card.
     *
     * @param [in] dispositionAction
     *      The action to be performed upon termination.
     * @return
     *      In case of success, @c SCARD_S_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t disconnect( sc_card_disposition_t dispositionAction ) = 0;


    /**
     * Retrieves the current status of a smart card in a reader.
     * If no connection is currently active, then an error is returned.
     *
     * @param [out] readerNames
     *      A list of the display names by which the smart card reader is known.
     *      The array contains @c sc_reader_name_t pointers.
     *      The array should be allocated by the caller.
     *      The caller should also allocate @c sc_reader_name_t instances that are provided as
     *      array elements.
     *      The operation will fill data into provided sc_reader_name_t instances.
     *      If NULL, only the number of elements will be returned.
     * @param [in/out] numReaderNames
     *      Number of reader names in @c readerNames array.
     *      The array should be allocated by the caller, and will be populated by the function.
     *      On input, the length of @c readerNames array.
     *      The number of allocated @c sc_reader_name_t instances should be no less than @c numReaderNames.
     *      On output, the number of reader names populated in the array.
     * @param [out] state
     *      The current smart card state.
     * @param [out] activeProtocol
     *      The current protocol.
     *      The returned value is meaningful if and only if a connection
     *      to the smart card is active.
     * @param [out] atrString
     *      The ATR string from the currently inserted card if available.
     * @return
     *      In case of success, @c SCARD_S_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t status( sc_reader_name_t** readerNames,
                                       unsigned int& numReaderNames,
                                       IfdState& state,
                                       sc_protocol_t& activeProtocol,
                                       AtrString& atrString ) = 0;


    /**
     * Sends a request to the smart card.
     *
     * @param [in] requestIoHeader
     *      The protocol control information structure corresponding to the
     *      protocol to use for sending.
     * @param [in] requestData
     *      The buffer containing the data to be sent to the smart card.
     * @param [in] requestDataLength
     *      The length of @c requestData.
     * @param [out] responseIoHeader
     *      The protocol control information structure corresponding to the
     *      protocol used to receive data from the smart card.
     * @param [in,out] responseData
     *      The data buffer used to store the response. It must be large
     *      enough to hold the maximum amount of data that may be returned.
     * @param [in,out] responseDataLength
     *      On input this specifies the length of @c responseData.
     *      Upon return, this specifies the number of bytes returned by the card.
     * @return
     *      In case of success, @c SCARD_S_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t transmit( const SmartCardIoHeader& requestIoHeader,
                                         const unsigned char* requestData,
                                         unsigned int requestDataLength,
                                         SmartCardIoHeader& responseIoHeader,
                                         unsigned char* responseData,
                                         unsigned int& responseDataLength ) = 0;


    /**
     * Retrieves the reader attribute value associated with a given tag.
     * If the tag is unknown, an error is returned.
     *
     * @param [in] tag
     *      The tag of the attribute value to retrieve.
     * @param [out] attribute
     *      The value of the attribute in TLV format.
     * @param [in,out] attributeLength
     *      The length of @c attribute.
     * @return
     *      In case of success, @c SCARD_S_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t getReaderCapabilities( unsigned int tag,
                                                      unsigned char* attribute,
                                                      unsigned int& attributeLength ) = 0;


    /**
     * Sets the reader attribute associated with a given tag.
     * If the tag is unknown, cannot be set, or the provided value is illegal,
     * an error is returned.
     *
     * @param [in] tag
     *      The tag of the attribute to be set.
     * @param [in] attribute
     *      The new attribute value in TLV format.
     * @param [in] attributeLength
     *      The length of @c attributeLength.
     * @return
     *      In case of success, @c SCARD_S_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t setReaderCapabilities( unsigned int tag,
                                                      const unsigned char* attribute,
                                                      unsigned int attributeLength ) = 0;

    /**
     * Creates @c SmartCardIoHeader instance.
     *
     * @param [out] ioHeader
     *      An instance of IO header allocated on the heap.
     *      The caller is responsible for calling @c destroyIoHeader to
     *      de-allocate the instance.
     * @return
     *      In case of success, @c SCARD_S_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t createIoHeader( SmartCardIoHeader*& ioHeader ) = 0;


    /**
     * Destroys @c SmartCardIoHeader instance.
     *
     * @param [out] ioHeader
     *      An instance of IO header to destroy.
     * @return
     *      In case of success, @c SCARD_S_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t destroyIoHeader( SmartCardIoHeader* ioHeader ) = 0;


    /**
     * Requests smart card service to obtain CHV code and call back to
     * @c verify on @c SmartCardHolderVerifier interface.
     *
     * If code is not cached or code caching is not allowed, smart card service
     * will display a dialog to obtain the code from the user. The dialog
     * will comply with general code request dialog UX flow.
     *
     * Smart card service may invoke the following operations on
     * @c SmartCardHolderVerifier interface:
     *  - @c getSmartCardId
     *  - @c getMaximumNumberOfPinAttempts
     *  - @c getNumberOfPinAttemptsRemaining
     *  - @c verify
     *
     * If the driver associated with this session does not support
     * @c SmartCardHolderVerifier interface, an error will be returned.
     *
     * @param [in] codeType
     *      Code type.
     * @param [in] minCodeLength
     *      Minimum code length. Negative value if unknown.
     * @param [in] maxCodeLength
     *      Maximum code length. Negative value if unknown.
     * @param [in] allowCodeCaching
     *      True if code caching is allowed by the driver. False, otherwise.
     *      Code caching is subject to settigns and IT policy restrictions.
     * @param [in] flags
     *      Indicates whether the CHV is to be made against a local (@c SC_FL_IHV_LOCAL)
     *      or global (@c SC_FL_IHV_GLOBAL) code.
     * @param [in] ref
     *      A vendor-specific reference value.
     * @param [in] smartCardHolderVerifier
     *      An instance that can provide @c SmartCardHolderVerifier functionality.
     *      The provided instance should be prepared to handle call-backs from the smart card service.
     *      Attach/detach operations will not be called on this instance.
     *      The instance should be created and destroyed by the caller.
     *      I.e. the provided instance is not a managed smart card resource.
     * @return
     *      In case of success, @c SCARD_S_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t requestCodeVerification( sc_code_type_t codeType,
                                                        int minCodeLength,
                                                        int maxCodeLength,
                                                        bool allowCodeCaching,
                                                        unsigned int flags,
                                                        unsigned int ref,
                                                        SmartCardHolderVerifier& smartCardHolderVerifier ) = 0;


protected:

    /**
     * Default implementation constructor.
     */
    SmartCardSession() {}


    /**
     * Destructor.
     */
    virtual ~SmartCardSession() {}

};

} // namespace smartcard_spi

#endif /* SMARTCARD_SPI_SMARTCARDSESSION_HPP */

