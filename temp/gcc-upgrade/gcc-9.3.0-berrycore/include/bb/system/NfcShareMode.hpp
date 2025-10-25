/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_NFCSHAREMODE_HPP
#define BB_SYSTEM_NFCSHAREMODE_HPP

#include <bb/system/Global>

#include <QObject>

namespace bb
{
namespace system
{

/*!
 * @headerfile NfcShareMode.hpp <bb/system/NfcShareMode>
 *
 * @brief The list of supported NFC share modes.
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/NFC"/>
 * <library name="bbsystem"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT NfcShareMode
{
    Q_GADGET
    Q_ENUMS(Type)

public:

    /*!
     * @brief The list of supported NFC share modes.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief NFC sharing is disabled on the device.
         *
         * @since BlackBerry 10.0.0
         */
        Disabled      = 0,

        /*!
         * @brief The device can share data with another NFC-enabled device or
         * write to an NFC tag.
         *
         * @details Method of sharing is selected automatically based on the NFC target detected.
         *
         * @since BlackBerry 10.0.0
         */
        Data          = 1,

        /*!
         * @brief The device can share files with another NFC-enabled device
         * using Bluetooth or WiFi Direct transports.
         *
         * @since BlackBerry 10.0.0
         */
        File          = 2,

        /*!
         * @brief The device can write to an NFC tag.
         *
         * @since BlackBerry 10.2.0
         */
        DataTagWrite  = 3,

        /*!
         * @brief The device can share data with another NFC-enabled device via Simple NDEF Exchange Protocol (SNEP).
         *
         * @details SNEP is a standard NFC peer-to-peer protocol that allows data to be pushed from one NFC-enabled device to another
         * NFC-enabled device. The sending and receiving device must both support SNEP.
         *
         * @since BlackBerry 10.2.0
         */
        DataSnep      = 4

    };


private:
//!@cond PRIVATE
    NfcShareMode();
    ~NfcShareMode();
//!@endcond
};
} // namespace system
} // namespace bb

#endif /* BB_SYSTEM_NFCSHAREMODE_HPP */
