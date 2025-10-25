/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_MESSAGE_MIMETYPES_HPP
#define BB_PIM_MESSAGE_MIMETYPES_HPP

#include <bb/pim/Global>
#include <QString>

namespace bb {
namespace pim {
namespace message {

/*!
 * @brief The @c MimeTypes class includes constants that represent possible MIME types
 * for messages.
 *
 * @see Message
 *
 * @xmlonly
 * <apigrouping group="App Integration/Message"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT MimeTypes
{
public:
    /*!
     * @brief Represents an SMS message.
     *
     * @since BlackBerry 10.0.0
     */
    static const QString Sms;
    /*!
     * @brief Represents an MMS message.
     *
     * @since BlackBerry 10.0.0
     */
    static const QString Mms;
    /*!
     * @brief Represents a Cell Broadcast Service message.
     *
     * @since BlackBerry 10.0.0
     */
    static const QString Cbs;
    /*!
     * @brief Represents a Rich Communication Suite message.
     *
     * @since BlackBerry 10.3.1
     */
    static const QString Rcs;

private:
    MimeTypes();
    ~MimeTypes();
};

} /* namespace message */
} /* namespace pim */
} /* namespace bb */

#endif // BB_PIM_MESSAGE_MIMETYPES_HPP
