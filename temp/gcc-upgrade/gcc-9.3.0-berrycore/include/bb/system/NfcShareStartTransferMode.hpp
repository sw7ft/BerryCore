/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_NFCSHARESTARTTRANSFERMODE_HPP
#define BB_SYSTEM_NFCSHARESTARTTRANSFERMODE_HPP

#include <bb/system/Global>

#include <QObject>

namespace bb
{
namespace system
{

/*!
 * @headerfile NfcShareStartTransferMode.hpp <bb/system/NfcShareStartTransferMode>
 *
 * @brief The list of supported modes for starting an NFC Transfer.
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/NFC"/>
 * <library name="bbsystem"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.2.0
 */
class BB_SYSTEM_EXPORT NfcShareStartTransferMode
{
    Q_GADGET
    Q_ENUMS(Type)

public:

    /*!
     * @brief The list of supported modes for starting an NFC Transfer.
     */
    enum Type {
        /*!
         * @brief When the user taps another NFC enabled device or NFC tag, 
         * the transfer of the specified NFC Share Content is automatically 
         * performed.
         */
        OnTap       = 0,

        /*!
         * @brief The transfer of the specified NFC Share Content is performed when
         * @c NfcShareManager::startTransfer() is called.
         *
         * @note This mode allows the content that will be shared to be set after the user taps another NFC enabled device.
         *       This mode might be useful when developer doesn't want to allocate any
         *       resources required for sharing in advance, or when it's not clear if the user will ever use the NFC Share functionality.
         */
        OnDemand    = 1
    };

private:
//!@cond PRIVATE
    NfcShareStartTransferMode();
    ~NfcShareStartTransferMode();
//!@endcond
};
} // namespace system
} // namespace bb

#endif /* BB_SYSTEM_NFCSHARESTARTTRANSFERMODE_HPP */
