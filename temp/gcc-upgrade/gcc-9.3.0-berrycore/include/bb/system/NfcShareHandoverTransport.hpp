/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_NFCSHAREHANDOVERTRANSPORT_HPP
#define BB_SYSTEM_NFCSHAREHANDOVERTRANSPORT_HPP

#include <bb/system/Global>

#include <QObject>

namespace bb
{
namespace system
{

/*!
 * @headerfile NfcShareHandoverTransport.hpp <bb/system/NfcShareHandoverTransport>
 *
 * @brief The list of transports supported by NFC handover.
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/NFC"/>
 * <library name="bbsystem"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.2.0
 */
class BB_SYSTEM_EXPORT NfcShareHandoverTransport
{
    Q_GADGET
    Q_ENUMS(Type)

public:

    /*!
     * @brief The list of transports supported by NFC handover.
     *
     * @details The transports that can be used when file sharing is initiated by an NFC tap.
     *
     * @since BlackBerry 10.2.0
     */
    enum Type {
        /*!
         * @brief Bluetooth transport.
         *
         * @since BlackBerry 10.2.0
         */
        Bluetooth  = 0,

        /*!
         * @brief WiFi Direct transport.
         *
         * @since BlackBerry 10.2.0
         */
        WiFiDirect = 1
    };

private:
//!@cond PRIVATE
    NfcShareHandoverTransport();
    ~NfcShareHandoverTransport();
//!@endcond
};
} // namespace system
} // namespace bb

#endif /* BB_SYSTEM_NFCSHAREHANDOVERTRANSPORT_HPP */
