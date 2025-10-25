/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_NFCSHARESETCONTENTERROR_HPP
#define BB_SYSTEM_NFCSHARESETCONTENTERROR_HPP

#include <bb/system/Global>

#include <QObject>

namespace bb
{
namespace system
{

/*!
 * @headerfile NfcShareSetContentError.hpp <bb/system/NfcShareSetContentError>
 *
 * @brief The list of errors that can occur when setting the content to share by using
 * NFC.
 *
 * @details The values in this enumeration describe the return value of the methods.
 * @c bb::system::NfcShareManager::setShareContent(const bb::system::NfcShareFilesContent&) and
 * @c bb::system::NfcShareManager::setShareContent(const bb::system::NfcShareDataContent&).
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/NFC"/>
 * <library name="bbsystem"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT NfcShareSetContentError
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief The list of errors that can occur when setting the content to share using
     * NFC.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief No error.
         *
         * @details The content to be shared using NFC has been updated.
         *
         * @since BlackBerry 10.0.0
         */
        None                    = 0,

        /*!
         * @brief The content to be shared using NFC could not be updated because the device is
         * currently transferring content using NFC.
         *
         * @since BlackBerry 10.0.0
         */
        TransferInProgress      = 1,

        /*!
         * @brief The content to be shared using NFC could not be updated because its type does
         * not match the current share mode of the @c NfcShareManager object.
         *
         * @since BlackBerry 10.0.0
         */
        InvalidShareMode        = 2,

        /*!
         * @brief The content to be shared using NFC was not updated because the supplied request
         * object was invalid.
         *
         * @details The @c NfcShareFilesContent or @c NfcShareDataContent
         * object does not form a valid description of the content to be shared.
         *
         * @since BlackBerry 10.0.0
         */
        InvalidShareRequest     = 3,

        /*!
         * @brief The data to be shared using NFC was not updated because of an expected error.
         *
         * @since BlackBerry 10.0.0
         */
        Unknown                 = 4
    };

private:
//!@cond PRIVATE
    NfcShareSetContentError();
    ~NfcShareSetContentError();
//!@endcond
};
} // namespace system
} // namespace bb

#endif /* BB_SYSTEM_NFCSHARESETCONTENTERROR_HPP */
