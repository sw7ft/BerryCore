/*
 * SmartCardDriver.hpp
 *
 * Copyright Research In Motion Limited, 2012-2013
 */

#ifndef SMARRTCARD_SPI_SMARTCARDDRIVER_HPP
#define SMARRTCARD_SPI_SMARTCARDDRIVER_HPP

#include <smartcard_spi/SmartCardDataTypes.hpp>


namespace smartcard_spi
{

class SmartCardCryptoProvider;
class SmartCardHolderVerifier;
class SmartCardCustomCommandProvider;
class SmartCardInterface;


enum SmartCardDriverApiVersion
{
    SMART_CARD_DRIVER_API_VERSION_1 = 1
};


/**
 * The interface defines all the methods used to acquire resources provided by
 * smart card drivers. Resources are acquired and released by calling one of the
 * @c create functions and the destroySmartCard() function respectively.
 */
class SmartCardDriver
{

public:

    /**
     * Destructor.
     */
    virtual ~SmartCardDriver();


    /**
     * Retrieves the API version.
     *
     * This function will be implemented by the framework.
     * The driver should not be overriding the version.
     */
    virtual int getApiVersion() const { return SMART_CARD_DRIVER_API_VERSION_1; };


    /**
     * Creates @c SmartCardInterface instance.
     *
     * @param [in] cardName
     *      Card type name for which an instance is to be constructed.
     * @param [out] card
     *      Created instance.
     * @return
     *      In case of success, SCARD_S_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t createSmartCard( const sc_card_name_t& cardName,
                                                SmartCardInterface*& card );


    /**
     * Creates @c SmartCardCryptoProvider instance.
     *
     * @param [in] cardName
     *      Card type name for which an instance is to be constructed.
     * @param [out] card
     *      Created instance.
     * @return
     *      In case of success, SCARD_S_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t createSmartCardCryptoProvider(
            const sc_card_name_t& cardName, SmartCardCryptoProvider*& card );


    /**
     * Creates @c SmartCardHolderVerifier instance.
     *
     * @param [in] cardName
     *      Card type name for which an instance is to be constructed.
     * @param [out] card
     *      Created instance.
     * @return
     *      In case of success, SCARD_S_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t createSmartCardHolderVerifier(
            const sc_card_name_t& cardName, SmartCardHolderVerifier*& card );


    /**
     * Creates @c SmartCardCustomCommandProvider instance.
     *
     * @param [in] cardName
     *      Card type name for which an instance is to be constructed.
     * @param [out] card
     *      Created instance.
     * @return
     *      In case of success, SCARD_S_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t createSmartCardCustomCommandProvider(
            const sc_card_name_t& cardName, SmartCardCustomCommandProvider*& card );


    /**
     * Destroys the provided @c SmartCardInterface instance.
     * This function may be used for any object inherited from @c SmartCardInteface.
     *
     * @param [in] card
     *      Instance to destroy.
     * @return
     *      In case of success, SCARD_S_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t destroySmartCard( SmartCardInterface* card );


protected:

    /**
     * Default implementation constructor.
     */
    SmartCardDriver();

};

} /* namespace smartcard_spi */

#endif /* SMARRTCARD_SPI_SMARTCARDDRIVER_HPP */
