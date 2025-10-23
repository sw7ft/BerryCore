/*
 * SmartCardDriverManager.hpp
 *
 * Copyright Research In Motion Limited, 2012-2013
 */

#ifndef SMARTCARD_SPI_SMARTCARDDRIVERMANAGER_HPP
#define SMARTCARD_SPI_SMARTCARDDRIVERMANAGER_HPP


#include <smartcard/sc_data_types.h>
#include <smartcard_spi/SmartCardDataTypes.hpp>


namespace smartcard_spi
{

class SmartCardDriver;
class SmartCardReaderDriver;
class SmartCardReaderMonitor;


/**
 * Smart card driver manager allows registering card and reader drivers.
 *
 * Once manager instance is obtained, the following sequence of steps should typically take place:
 *
 *  1. Initialize the manager instance using @c initialize function.
 *  2. Register card and reader drivers using register functions.
 *  3. Allocate threads for operating the driver and call @c runDriver.
 *  4. Handle process termination when @c runDriver calls return
 *     (e.g. by joining main thread with the allocated threads).
 *
 *  The main thread could be given to smart card framework via @c runDriver, or it could be used for
 *  driver purposes (e.g. for UI event thread).
 */
class SmartCardDriverManager
{

public:

    /**
     * Initializes smart card framework.
     *
     * This function should be called before any other functions on this interface.
     *
     * @param [in] driverLaunchInvocationTarget
     *      Driver invocation target (as defined in the driver application bar descriptor)
     *      that will be used by smart card service for launching the driver.
     *      Must not be NULL.
     * @return
     *      In case of success, SCARD_S_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t initialize( const char* driverLaunchInvocationTarget ) = 0;


    /**
     * Registers card driver.
     *
     * Smart card framework will maintain a pointer to the provided factory.
     * It is expected that the factory object will not be deleted until
     * @c SmartCardDriverManager instance is destroyed (this will typically
     * occur when the driver process terminates).
     *
     * @param [in] cardName
     *      Card name.
     * @param [in] atr
     *      Answer to Reset (ATR) of the card supported by this driver.
     * @param [out] atrMask
     *      ATR mask that will be used to match the provided ATR against the card ATR.
     * @param [in] SmartCardDriver
     *      Smart card factory implementation provided by driver developer.
     *      Must not be NULL.
     * @return
     *      In case of success, SCARD_S_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t registerCardDriver( const sc_card_name_t& cardName,
                                                   const AtrString& atr,
                                                   const AtrString& atrMask,
                                                   SmartCardDriver* smartCardDriver ) = 0;


    /**
     * Registers reader driver.
     *
     * Smart card framework will maintain a pointer to the provided factory.
     * It is expected that the factory object will not be deleted until
     * @c SmartCardDriverManager instance is destroyed (this will typically
     * occur when the driver process terminates).
     *
     * @param [in] readerName
     *      Reader name.
     * @param [in] smartCardReaderDriver
     *      Smart card reader factory implementation provided by driver developer.
     *      Must not be NULL.
     * @return
     *      In case of success, SCARD_S_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t registerReaderDriver( const sc_reader_name_t& readerName,
                                                     SmartCardReaderDriver* smartCardReaderDriver ) = 0;


    /**
     * By calling this function, the driver provides threads to smart card framework to
     * operate the driver.
     *
     * This function will not return unless the driver no longer needs to run or a
     * catastrophic failure occurs.
     *
     * If the driver no longer needs to run, all calls to @runDriver will return with
     * @c SCARD_S_SUCCESS return code. It is expected that the driver main function
     * will then exit, and the driver process will terminate. The driver process will
     * be restarted when needed.
     *
     * At least 2 threads should be passed in.
     * Having 4 threads is recommended.
     *
     * @return
     *      In case of success, SCARD_S_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t runDriver() = 0;


    /**
     * Retrieves @c SmartCardReaderMonitor instance.
     * The instance is managed by the smart card driver manager.
     * I.e. the caller does not need to de-allocate this instance.
     *
     * @param [out] readerMonitor
     *      An instance of @c SmartCardReaderMonitor.
     * @return
     *      In case of success, SCARD_S_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t getSmartCardReaderMonitor( SmartCardReaderMonitor*& readerMonitor ) = 0;


protected:

    /**
     * Default implementation constructor.
     */
    SmartCardDriverManager() {}


    /**
     * Destructor
     */
    virtual ~SmartCardDriverManager() {}

};

}


#endif /* SMARTCARD_SPI_SMARTCARDDRIVERMANAGER_HPP */
