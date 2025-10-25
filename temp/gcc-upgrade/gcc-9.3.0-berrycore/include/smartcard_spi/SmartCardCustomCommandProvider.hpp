

/*
 * SmartCardCustomCommandProvider.hpp
 *
 * Copyright Research In Motion Limited, 2012-2013
 */

#ifndef SMARTCARD_SPI_SMARTCARDCUSTOMCOMMANDPROVIDER_HPP
#define SMARTCARD_SPI_SMARTCARDCUSTOMCOMMANDPROVIDER_HPP


#include <smartcard_spi/SmartCardInterface.hpp>


namespace smartcard_spi
{

/**
 * @c SmartCardCustomCommandProvider defines functionality that allows
 * sending custom APDU commands.
 */
class SmartCardCustomCommandProvider : public SmartCardInterface
{

public:

    /**
     * Destructor.
     */
    virtual ~SmartCardCustomCommandProvider();


    /**
     * Sends a custom APDU command.
     *
     * @param [in] apduCommand
     *      APDU command to send.
     * @param [in] apduCommandLength
     *      The length of the APDU command to send.
     * @param [out] apduResponse
     *      Response APDU.
     * @param [in, out] apduResponseLength
     *      Response APDU length.
     * @return
     *      In case of success, SCARD_S_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t sendApdu( const unsigned char* apduCommand,
                                         unsigned int apduCommandLength,
                                         unsigned char* apduResponse,
                                         unsigned int& apduResponseLength );

protected:

    /**
     * Default implementation constructor.
     */
    SmartCardCustomCommandProvider();

};

} // namespace smartcard_spi

#endif /* SMARTCARD_SPI_SMARTCARDCUSTOMCOMMANDPROVIDER_HPP */
