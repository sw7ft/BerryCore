/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_MESSAGE_SEARCHSTATUSCRITERIA_HPP
#define BB_PIM_MESSAGE_SEARCHSTATUSCRITERIA_HPP

#include <bb/pim/Global>

namespace bb {
namespace pim {
namespace message {

/*!
 *
 * @brief The @c SearchStatusCriteria class includes possible statuses that you can 
 * use to search for messages.
 *
 * @details You can use this class in conjunction with the @c MessageSearchFilter class
 * to specify status criteria for searches. You can add a @c %SearchStatusCriteria to a
 * @c %MessageSearchFilter by calling @c MessageSearchFilter::addStatusCriteria().
 * Then, you can search for messages that include the specified status by calling
 * by calling @c MessageService::searchLocal() or @c MessageService::searchRemote().
 * 
 * @see MessageSearchFilter, MessageService
 *
 * @xmlonly
 * <apigrouping group="App Integration/Message"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT SearchStatusCriteria
{
public:
    /*!
     * @brief An enumeration of supported statuses for messages.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
        * @brief Indicates that the search should apply to unread messages.
         *
         * @since BlackBerry 10.0.0
        */
        Unread=0,
        /*!
        * @brief Indicates that the search should apply to flagged messages.
         *
         * @since BlackBerry 10.0.0
        */
        Flagged = 1,
        /*!
        * @brief Indicates that the search should apply to messages with attachments.
         *
         * @since BlackBerry 10.0.0
        */
        Attachments = 2,
        /*!
        * @brief Indicates that the search should apply to messages that were
        * received today.
         *
         * @since BlackBerry 10.0.0
        */
        Today = 3,
        /*!
        * @brief Indicates that the search should apply to messages that were
        * received yesterday.
         *
         * @since BlackBerry 10.0.0
        */
        Yesterday = 4,
        /*!
        * @brief Indicates that the search should apply to inbound (received)
        * messages.
         *
         * @since BlackBerry 10.0.0
        */
        Received = 5,
        /*!
        * @brief Indicates that the search should apply to messages that were
        * received last week.
         *
         * @since BlackBerry 10.0.0
        */
        LastWeek = 6,
    };

private:
    /*! @cond PRIVATE */
    SearchStatusCriteria();
    ~SearchStatusCriteria();
    /*! @endcond */
};

} /* namespace message */
} /* namespace pim */
} /* namespace bb */

#endif // BB_PIM_MESSAGE_SEARCHSTATUSCRITERIA_HPP
