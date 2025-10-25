/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_NFCSHARESUCCESS_HPP
#define BB_SYSTEM_NFCSHARESUCCESS_HPP

#include <bb/system/Global>

#include <QObject>

namespace bb
{
namespace system
{

/*!
 * @headerfile NfcShareSuccess.hpp <bb/system/NfcShareSuccess>
 *
 * @brief The list of notifications provided to the @c NfcShareManager::finished()
 * signal after successfully sharing content using NFC.
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/NFC"/>
 * <library name="bbsystem"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT NfcShareSuccess
{
    Q_GADGET
    Q_ENUMS(Type)

public:

    /*!
     * @brief The list of notifications provided to the @c NfcShareManager::finished()
     * signal after successfully sharing content using NFC.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief A connection handover was successfully established and the process of transferring files
         * over Bluetooth or WiFi Direct transport has started.
         *
         * @since BlackBerry 10.0.0
         */
        File                        = 0,

        /*!
         * @brief Data content was successfully sent to the receiving NFC-enabled device.
         *
         * @details This notification is not sent until the recipient confirms the data was received.
         * The data is transferred using the Simple NDEF Exchange Protocol (SNEP).
         *
         * @since BlackBerry 10.0.0
         */
        Snep                        = 1,

        /*!
         * @brief Data content was successfully written to an NFC tag.
         *
         * @since BlackBerry 10.0.0
         */
        TagWrite                    = 2
    };
private:
//!@cond PRIVATE
    NfcShareSuccess();
    ~NfcShareSuccess();
//!@endcond
};
} // namespace system
} // namespace bb

#endif /* BB_SYSTEM_NFCSHARESUCCESS_HPP */
