/*
 * SmartCardInterface.hpp
 *
 * Copyright Research In Motion Limited, 2012-2013
 */

#ifndef SMARTCARD_SPI_SMARTCARDINTERFACE_HPP
#define SMARTCARD_SPI_SMARTCARDINTERFACE_HPP


#include <smartcard/sc_data_types.h>
#include <smartcard/sc_smart_card_id.h>


#define SC_SMART_CARD_INTERFACE_API_VERSION_1 1


namespace smartcard_spi
{


class SmartCardSession;


enum SmartCardInterfaceApiVersion
{
    SMART_CARD_INTERFACE_API_VERSION_1 = 1,
    SMART_CARD_INTERFACE_API_VERSION_2 = 2
};


/**
 * @c SmartCardInterface interface describes all the methods that any smart card
 * interface must provide.
 */
class SmartCardInterface
{

public:


    /**
     * Destructor.
     */
    virtual ~SmartCardInterface();


    /**
     * Retrieves the API version.
     *
     * This function will be implemented by the framework.
     * The driver should not be overriding the version.
     */
    virtual int getApiVersion() const { return SMART_CARD_INTERFACE_API_VERSION_2; };


    /**
     * Opens a session to the smart card located in a given reader.
     * If the reader is unknown to the smart card subsystem, an error is returned.
     *
     * @param [in] readerName
     *      Reader name where the smart card to connect to is located.
     * @param [in] cardAccessMode
     *      Card access mode.
     * @param [in] session
     *      Smart card session.
     * @return
     *      In case of success, @c SC_SCARD_S_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t attachByReader( const sc_reader_name_t& readerName,
                                               sc_card_access_mode_t cardAccessMode,
                                               SmartCardSession& session );


    /**
     * Closes smart card session.
     * If no connection is currently opened, an error is returned.
     *
     * Upon termination, the action indicated by @c dispositionAction is
     * performed if possible.
     *
     * Any application may reset the card even in shared access mode.
     * Power-down and eject actions will succeed only if the application has
     * exclusive access to the card.
     *
     * @param [in] dispositionAction
     *      The action to be performed upon termination.
     * @return
     *      In case of success, @c SC_SCARD_S_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t detach( sc_card_disposition_t dispositionAction );


    /**
     * Re-establish an existing connection to a smart card.
     *
     * Example uses of this method include:
     *
     * - Changing the mode of an existing connection (via @c cardAccessMode parameter).
     *
     * Note that a connection must have previously been established, otherwise
     * an error is returned.
     *
     * @param [in] cardAccessMode
     *      Card access mode.
     * @return
     *      In case of success, @c SC_SCARD_S_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t reconnect( sc_card_access_mode_t cardAccessMode );


    /**
     * Retrieves an identifier uniquely identifying the currently connected
     * smart card.
     *
     * @param [out] cardId
     *      Card ID.
     * @return
     *      In case of success, @c SC_SCARD_S_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t getSmartCardId( sc_smart_card_id_t& cardId );


    /**
     * Retrieves the card driver name.
     *
     * @param [out] cardName
     *      Card name.
     * @return
     *      In case of success, @c SC_SCARD_S_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t getCardName( sc_card_name_t& cardName );


    /**
     * Cancel all in-progress operations.
     *
     * @param [in] forceCancel
     *      If set to true, all in-progress operations must be terminated
     *      immediately. Otherwise, attempts to gracefully cancel all
     *      in-prorgress operations should be made where possible.
     * @return
     *      In case of success, @c SC_SCARD_S_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t cancel( bool forceCancel );


protected:

    /**
     * Default implementation constructor.
     */
    SmartCardInterface();

};

}

#endif /* SMARTCARD_SPI_SMARTCARDINTERFACE_HPP */

