/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_MESSAGE_ATTACHMENTENCODING_HPP
#define BB_PIM_MESSAGE_ATTACHMENTENCODING_HPP

#include <bb/pim/Global>

namespace bb {
namespace pim {
namespace message {

/*!
 * @headerfile AttachmentEncoding.hpp <bb/pim/message/AttachmentEncoding>
 *
 * @brief The @c AttachmentEncoding class represents the encoding type of a message attachment.
 * 
 * @details An @c Attachment object can have different encoding types. The attachment might be
 * encoded using UTF-8 or ASCII. You can use this class to determine the encoding type.
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
class BB_PIM_EXPORT AttachmentEncoding
{
public:
    /*!
     * @brief An enumeration of supported encoding types for attachments.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        None   = 0,
        /*!
        * @brief Indicates the UTF-8 encoding type.
         *
         * @since BlackBerry 10.0.0
        */
        Utf8   = 1,
        /*!
        * @brief Indicates the ASCII encoding type.
         *
         * @since BlackBerry 10.0.0
        */
        Ascii  = 2,
        /*!
        * @brief Indicates the Latin1 encoding type.
         *
         * @since BlackBerry 10.0.0
        */
        Latin1 = 3
    };

private:
    /*! @cond PRIVATE */
    AttachmentEncoding();
    ~AttachmentEncoding();
    /*! @endcond */
};

} /* namespace message */
} /* namespace pim */
} /* namespace bb */

#endif /* BB_PIM_MESSAGE_ATTACHMENTENCODING_HPP */
