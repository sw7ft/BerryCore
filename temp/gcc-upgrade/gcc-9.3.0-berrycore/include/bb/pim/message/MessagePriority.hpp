/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_MESSAGE_PRIORITY_HPP
#define BB_PIM_MESSAGE_PRIORITY_HPP

#include <bb/pim/Global>

#include <QMetaType>

namespace bb {
namespace pim {
namespace message {

/*!
 * @headerfile MessagePriority.hpp <bb/pim/message/MessagePriority>
 *
 * @brief The @c MessagePriority class includes priority levels for messages.
 *
 * @details You can use this class to determine the priority of a @c Message. For example,
 * messages can be marked as low, normal, or high priority. You can set the priority of
 * a message by calling @c MessageService::setPriority().
 * 
 * @see Message, MessageService
 *
 * @xmlonly
 * <apigrouping group="App Integration/Message"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT MessagePriority
{
public:
    /*!
     * @brief An enumeration of possible priority levels for messages.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief Indicates a low priority on a message.
         *
         * @since BlackBerry 10.0.0
         */
        Low    = 0,
        /*!
         * @brief Indicates a normal priority on a message.
         *
         * @since BlackBerry 10.0.0
         */
        Normal = 1,
        /*!
         * @brief Indicates a high priority on a message.
         *
         * @since BlackBerry 10.0.0
         */
        High   = 2
    };

private:
    /*! @cond PRIVATE */
    MessagePriority();
    ~MessagePriority();
    /*! @endcond */
};

} /* namespace message */
} /* namespace pim */
} /* namespace bb */

Q_DECLARE_METATYPE(bb::pim::message::MessagePriority::Type)

#endif // BB_PIM_MESSAGE_PRIORITY_HPP
