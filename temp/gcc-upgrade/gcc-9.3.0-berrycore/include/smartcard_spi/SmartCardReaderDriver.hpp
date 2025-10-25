/*
 * SmartCardReaderDriver.hpp
 *
 * Copyright Research In Motion Limited, 2012-2013
 */

#ifndef SMARTCARD_SPI_SMARTCARDREADERDRIVER_HPP
#define SMARTCARD_SPI_SMARTCARDREADERDRIVER_HPP

#include <smartcard_spi/SmartCardDataTypes.hpp>


#define SC_SMART_CARD_READER_DRIVER_API_VERSION_1 1


namespace smartcard_spi
{

class SmartCardReader;
class SlotLogicalSmartCardReader;


enum SmartCardReaderDriverApiVersion
{
    SMART_CARD_READER_DRIVER_API_VERSION_1 = 1
};


/**
 * The @c SmartCardReaderDriver interface defines all the methods used to acquire
 * specific types of resources provided by an individual smart card reader
 * driver. Resources are acquired and released by calling one of the various
 * create methods and the destroy method.
 * A custom implementation of this class is provided by each smart card reader
 * driver that registers with the smart card service.
 */
class SmartCardReaderDriver
{

public:

    /**
     * Destructor.
     */
    virtual ~SmartCardReaderDriver();


    /**
     * Retrieves the API version.
     *
     * This function will be implemented by the framework.
     * The driver should not be overriding the version.
     */
    virtual int getApiVersion() const { return SMART_CARD_READER_DRIVER_API_VERSION_1; };


    /**
     * Creates an instance of the @c SmartCardReader implementation
     * provided by the smart card reader driver.
     *
     * @param [out] reader
     *      The pointer used to hold a reference to the requested instance.
     * @return
     *      In case of success, @c SCARD_S_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t createReader( SmartCardReader*& reader );


    /**
     * Creates an instance of the @c SlotLogicalSmartCardReader
     * implementation provided by the smart card reader driver.
     *
     * @param [out] reader
     *      The pointer used to hold a reference to the requested instance.
     * @return
     *      In case of success, @c SCARD_S_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t createSlotLogicalReader( SlotLogicalSmartCardReader*& reader );


    /**
     * Destroys the provided @c SmartCardReader instance.
     * Note that this method can be used for objects created by any of the
     * @c create methods defined in this class.
     *
     * @param [in] reader
     *      The instance to be destroyed. Must not be NULL.
     * @return
     *      In case of success, @c SCARD_S_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t destroyReader( SmartCardReader* reader );


protected:

    /**
     * Default implementation constructor.
     */
    SmartCardReaderDriver();

};

} /* namespace smartcard_spi */

#endif /* SMARTCARD_SPI_SMARTCARDREADERDRIVER_HPP */
