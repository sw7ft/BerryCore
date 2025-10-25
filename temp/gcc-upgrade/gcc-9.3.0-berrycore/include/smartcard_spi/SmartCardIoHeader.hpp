/*
 * SmartCardIoHeader.hpp
 *
 * Copyright Research In Motion Limited, 2012-2013
 */

#ifndef SMARTCARD_SPI_SMARTCARDIOHEADER_HPP
#define SMARTCARD_SPI_SMARTCARDIOHEADER_HPP


#include <smartcard/sc_data_types.h>


namespace smartcard_spi
{

/**
 * IO header for smart card APDU transmission.
 *
 * This interface may be created by @c SmartCardSession and is used for
 * transmitting APDU IO header to smart card reader.
 */
class SmartCardIoHeader
{

public:

    /**
     * Retrieves protocol version.
     *
     * @param [out] protocol
     *      Protocol version.
     * @return
     *      In case of success, @c SC_IFD_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t getProtocol( unsigned int& protocol ) const = 0;


    /**
     * Sets protocol version.
     *
     * @param [in] protocol
     *      Protocol version.
     * @return
     *      In case of success, @c SC_IFD_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t setProtocol( unsigned int protocol ) = 0;


protected:

    /**
     * Default implementation constructor.
     */
    SmartCardIoHeader() {}


    /**
     * Destructor.
     */
    virtual ~SmartCardIoHeader() {}

};

}

#endif /* SMARTCARD_SPI_SMARTCARDIOHEADER_HPP */
