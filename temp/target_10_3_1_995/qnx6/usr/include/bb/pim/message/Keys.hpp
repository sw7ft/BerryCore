/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_MESSAGE_KEYS_HPP
#define BB_PIM_MESSAGE_KEYS_HPP

#include <QString>

namespace bb {
namespace pim {
namespace message {

/*!
 * @brief Represents a conversation ID.
 * 
 * @details This key uniquely identifies a @c Conversation.
 *
 * @since BlackBerry 10.0.0
 */
typedef QString ConversationKey;

/*!
 * @brief Represents a message ID.
 * 
 * @details This key uniquely identifies a @c Message.
 *
 * @since BlackBerry 10.0.0
 */
typedef qint64 MessageKey;

/*!
 * @brief Represents a message contact ID.
 * 
 * @details This key uniquely identifies a @c MessageContact.
 *
 * @since BlackBerry 10.0.0
 */
typedef qint64 MessageContactKey;

/*!
 * @brief Represents an attachment ID.
 * 
 * @details This key uniquely identifies an @c Attachment.
 *
 * @since BlackBerry 10.0.0
 */
typedef qint64 AttachmentKey;

/*!
 * @brief Represents a folder ID.
 * 
 * @details This key uniquely identifies a @c MessageFolder.
 *
 * @since BlackBerry 10.0.0
 */
typedef qint64 FolderKey;

/*!
 * @brief Represents an undefined key.
 *
 * @since BlackBerry 10.0.0
 */
typedef qint64 TransactionKey;

/*!
 * @brief ...
 *
 * @since BlackBerry 10.0.0
 */
const qint64 UndefinedKey = 0;


} /* namespace message */
} /* namespace pim */
} /* namespace bb */

#endif // BB_PIM_MESSAGE_KEYS_HPP
