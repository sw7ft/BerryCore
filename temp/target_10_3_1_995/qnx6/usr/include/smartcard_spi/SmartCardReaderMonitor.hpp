/*
 * SmartCardReaderMonitor.hpp
 *
 * Copyright Research In Motion Limited, 2012-2013
 */

#ifndef SMARTCARD_SPI_SMARTCARDREADERMONITOR_HPP_
#define SMARTCARD_SPI_SMARTCARDREADERMONITOR_HPP_


#include <smartcard/sc_data_types.h>
#include <smartcard/sc_reader_state.h>


namespace smartcard_spi
{

/**
 * Smart Card Reader Monitor can be used by reader drivers to notify of
 * reader state changes. E.g. a reader driver may notify the smart card framework
 * when a smart card has been removed from the reader.
 */
class SmartCardReaderMonitor
{

public:

    /**
     * Notifies smart card framework about reader state changes.
     * E.g. when the reader detects smart card removal, the reader driver may
     * used this function to notify the smart card framework about this
     * reader status change event.
     *
     * @param [out] readerState
     *      New reader state.
     * @return
     *      In case of success, @c SC_IFD_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    virtual sc_response_code_t updateReaderState( sc_reader_state_t& readerState ) = 0;


protected:

    /**
     * Default implementation constructor.
     */
    SmartCardReaderMonitor() {};

    /**
     * Destructor.
     */
    virtual ~SmartCardReaderMonitor() {};

};

} /* namespace smartcard_spi */

#endif /* SMARTCARD_SPI_SMARTCARDREADERMONITOR_HPP_ */
