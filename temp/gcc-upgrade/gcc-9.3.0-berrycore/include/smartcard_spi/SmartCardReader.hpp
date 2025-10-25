/*
 * SmartCardReader.hpp
 *
 * Copyright Research In Motion Limited, 2012-2013
 */

#ifndef SMARTCARD_SPI_SMARTCARDREADER_HPP
#define SMARTCARD_SPI_SMARTCARDREADER_HPP


#include <smartcard/sc_data_types.h>


namespace smartcard_spi
{


enum SmartCardReaderApiVersion
{
    SMART_CARD_READER_API_VERSION_1 = 1
};



/**
 * @c SmartCardReader interface describes the basic methods that all reader driver
 * interfaces must provide. The methods included in this class correspond to
 * functionality required by most, if not all, specialized smart card reader
 * interfaces.
 */
class SmartCardReader
{

public:

    /**
     * Destructor.
     */
    virtual ~SmartCardReader();


    /**
     * Retrieves the API version.
     *
     * This function will be implemented by the framework.
     * The driver should not be overriding the version.
     */
    virtual int getApiVersion() const { return SMART_CARD_READER_API_VERSION_1; };


    /**
     * Retrieves the reader name used when registering this driver with the core subsystem.
     *
     * @param [out] readerName
     *      Reader driver name.
     * @return
     *      In case of success, @c SC_DEVICE_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t getReaderName( sc_reader_name_t& readerName );


    /**
     * Retrieves the user-friendly reader name associated with this driver.
     *
     * @param [out] readerLabel
     *      Reader label.
     * @return
     *      In case of success, @c SC_DEVICE_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t getReaderLabel( sc_card_label_t& readerLabel );


protected:

    /**
     * Default implementation constructor.
     */
    SmartCardReader();

};

} /* namespace smartcard_spi */

#endif /* SMARTCARD_SPI_SMARTCARDREADER_HPP */
