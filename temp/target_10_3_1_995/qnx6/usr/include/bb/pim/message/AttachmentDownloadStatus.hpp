/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_MESSAGE_ATTACHMENTDOWNLOADSTATUS_HPP
#define BB_PIM_MESSAGE_ATTACHMENTDOWNLOADSTATUS_HPP

#include <bb/pim/Global>

#include <QMetaType>

namespace bb {
namespace pim {
namespace message {

/*!
 * @headerfile AttachmentDownloadStatus.hpp <bb/pim/message/AttachmentDownloadStatus>
 *
 * @brief The @c AttachmentDownloadStatus class includes possible transmission statuses for
 * attachments in messages.
 *
 * @details An @c Attachment can have several different statuses that indicate whether transmission of the
 * attachment was successful. For example, you can use the enumeration values in this class to determine
 * if the attachment was sent successfully, is pending, or was unsuccessful because an error occurred.
 * 
 * @see Attachment
 *
 * @xmlonly
 * <apigrouping group="App Integration/Message"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT AttachmentDownloadStatus
{
public:
    /*!
     * @brief An enumeration of supported transmission statuses for attachments.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief Indicates that the attachment was downloaded successfully.
         *
         * @since BlackBerry 10.0.0
         */
        Success = 0,
        /*!
         * @brief Indicates that the attachment is too large by policy.
         *
         * @since BlackBerry 10.0.0
         */
        PolicyAttachmentTooLarge = 1,
        /*!
         * @brief Indicates that the attachment is not supported by policy.
         *
         * @since BlackBerry 10.0.0
         */
        PolicyAttachmentNotSupported = 2,
        /*!
         * @brief Indicates a reprovisioning account.
         *
         * @since BlackBerry 10.0.0
         */
        Reprovisioning = 3,
        /*!
         * @brief Indicates that the service is not available.
         *
         * @since BlackBerry 10.0.0
         */
        ServiceNotAvailable = 4,
        /*!
         * @brief Indicates an unknown error.
         *
         * @since BlackBerry 10.0.0
         */
        UnknownError = 5
    };

private:
    /*! @cond PRIVATE */
    AttachmentDownloadStatus();
    ~AttachmentDownloadStatus();
    /*! @endcond */
};

} /* namespace message */
} /* namespace pim */
} /* namespace bb */

Q_DECLARE_METATYPE(bb::pim::message::AttachmentDownloadStatus::Type)

#endif // BB_PIM_MESSAGE_ATTACHMENTDOWNLOADSTATUS_HPP
