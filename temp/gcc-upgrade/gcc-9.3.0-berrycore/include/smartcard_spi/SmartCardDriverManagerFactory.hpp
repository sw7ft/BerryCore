/*
 * SmartCardDriverManagerFactory.hpp
 *
 * Copyright Research In Motion Limited, 2012-2013
 */

#ifndef SMARTCARD_SPI_SMARTCARDDRIVERMANAGERFACTORY_HPP
#define SMARTCARD_SPI_SMARTCARDDRIVERMANAGERFACTORY_HPP


#include <smartcard_spi/SmartCardDriverManager.hpp>


namespace smartcard_spi
{
    /**
     * Smart card driver manager factory functions should be used to obtain
     * and destroy the single smart card driver manager instance.
     */

    /**
     * Retrieves @c SmartCardDriverManager single instance.
     *
     * @param [in] manager
     *      Smart card driver manager instance.
     * @return
     *      In case of success, SCARD_S_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    sc_response_code_t getSmartCardDriverManager( SmartCardDriverManager*& manager );


    /**
     * Destroys @c SmartCardDriverManager instance.
     *
     * Once @c SmartCardDriverManager instance is called, calls to
     * @c getSmartCardDriverManager will result in failure.
     *
     * @return
     *      In case of success, SCARD_S_SUCCESS is returned.
     *      Otherwise, an error code is returned.
     */
    sc_response_code_t destroySmartCardDriverManager();
}


#endif /* SMARTCARD_SPI_SMARTCARDDRIVERMANAGERFACTORY_HPP */
