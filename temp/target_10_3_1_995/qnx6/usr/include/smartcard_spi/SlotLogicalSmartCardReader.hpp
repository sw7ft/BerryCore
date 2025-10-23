/*
 * SlotLogicalSmartCardReader.hpp
 *
 * Copyright Research In Motion Limited, 2012-2013
 */

#ifndef SMARTCARD_SPI_SLOTLOGICALSMARTCARDREADER_HPP
#define SMARTCARD_SPI_SLOTLOGICALSMARTCARDREADER_HPP


#include <smartcard_spi/SmartCardDataTypes.hpp>
#include <smartcard_spi/SmartCardReader.hpp>
#include <smartcard_spi/SmartCardIoHeader.hpp>


namespace smartcard_spi
{

/**
 * The slot logical device interface provides communication services in order to support
 * the data exchange between the ICC and the ICC Service Provider.
 */
class SlotLogicalSmartCardReader : public SmartCardReader
{

public:

    /**
     * Destructor.
     */
    virtual ~SlotLogicalSmartCardReader();


    /**
     * Retrieves the value corresponding to a given capabilities tag.
     *
     * @param [in] tag
     *      The tag of interest.
     * @param [out] value
     *      The value of the tag in TLV format. Must not be NULL.
     * @param [in,out] valueLength
     *      The length of @c value.
     * @return
     *      In case of success, @c SC_IFD_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t getCapabilities( unsigned int tag,
                                                unsigned char* value,
                                                unsigned int& valueLength );


    /**
     * Sets the value for a given capabilities tag.
     *
     * @param [in] tag
     *      The tag of interest.
     * @param [in] value
     *      The value of the tag to be set in TLV format. May be NULL.
     * @param [in] valueLength
     *      The length of @c value.
     * @return
     *      In case of success, @c SC_IFD_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t setCapabilities( unsigned int tag,
                                                const unsigned char* value,
                                                unsigned int valueLength );


    /**
     * Set the protocols and protocol parameters that the reader should use.
     *
     * @param [in] protocolType
     *      A list of protocol types encoded in the same way as for the
     *      TAG_ASYNCHRONOUS_PROTOCOL_TYPES (0x0120) and
     *      TAG_SYNCHRONOUS_PROTOCOL_TYPES (0x0126) tags or
     *      the special value IFD_DEFAULT_PROTOCOL.
     *
     * @param [in] selectionFlags
     *      Indicates which of the optional parameters (@c pps1, @c pps2, and @c pps3),
     *      if any, have to be negotiated and included in the request.
     *      It is obtained by performing a bitwise OR operation on the following flags:
     *
     *      - @c IFD_NEGOTIATE_PPS1
     *      - @c IFD_NEGOTIATE_PPS2
     *      - @c IFD_NEGOTIATE_PPS3
     *
     * @param [in] pps1
     *      An optional protocol parameter.
     * @param [in] pps2
     *      An optional protocol parameter.
     * @param [in] pps3
     *      An optional protocol parameter.
     *
     * @return
     *      In case of success, @c SC_IFD_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t setProtocolParameters( unsigned int protocolType,
                                                      IfdPpsParameterSelectionFlag selectionFlags,
                                                      unsigned char pps1,
                                                      unsigned char pps2,
                                                      unsigned char pps3 );


    /**
     * Requests the inserted card to be powered up, powered down, reset, or other
     * actions allowed by @c IfdPowerAction enumeration.
     *
     * If the method reports success and the action requested was either a reset
     * or a power up, then the ATR returned by the card, and the protocol
     * parameters can be accessed through the @c getCapabilities() function.
     *
     * @param [in] actionRequested
     *      The power-related action to be performed against the inserted card.
     * @return
     *      In case of success, @c SC_IFD_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t powerIcc( IfdPowerAction powerAction );


    /**
     * Requests the reader to mechanically swallow the smart card
     * if the reader supports such a feature.
     *
     * @return
     *      In case of success, @c SC_IFD_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t swallowIcc();


    /**
     * Request the reader to mechanically eject the smart card
     * if the reader supports such a feature.
     *
     * @return
     *      In case of success, @c SC_IFD_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t ejectIcc();


    /**
     * Requests the reader to confiscate the smart card
     * if the reader supports such a feature.
     *
     * @return
     *      In case of success, @c SC_IFD_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t confiscateIcc();


    /**
     * Transmits the provided command to the smart card.
     *
     * @param [in] commandIoHeader
     *      The protocol control information structure corresponding to the
     *      protocol to use for sending.
     * @param [in] command
     *      The command to be sent to the smart card. Must not be NULL.
     * @param [in] commandLength
     *      The length of @c command.
     * @param [out] responseIoHeader
     *      The protocol control information structure corresponding to the
     *      protocol used to receive data from ICC.
     * @param [in,out] response
     *      The response to the command received from the smart card. Must not be NULL.
     * @param [in,out] responseLength
     *      The length of @c response.
     * @return
     *      In case of success, @c SC_IFD_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t transmitToIcc( const SmartCardIoHeader& commandIoHeader,
                                              const unsigned char* command,
                                              unsigned int commandLength,
                                              SmartCardIoHeader& responseIoHeader,
                                              unsigned char* response,
                                              unsigned int& responseLength );


    /**
     * Returns card presence status.
     * This function does not block.
     *
     * @return
     *      @c SC_IFD_ICC_PRESENT when ICC is present.
     *      @c SC_IFD_ICC_NOT_PRESENT when ICC is not present.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t isIccPresent();


protected:

    /**
     * Default implementation constructor.
     */
    SlotLogicalSmartCardReader();

};

}

#endif /* SMARTCARD_SPI_SLOTLOGICALSMARTCARDREADER_HPP */
