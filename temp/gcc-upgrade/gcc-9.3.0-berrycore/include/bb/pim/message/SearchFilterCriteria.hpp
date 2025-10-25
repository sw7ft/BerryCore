/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_MESSAGE_SEARCHFILTERCRITERIA_HPP
#define BB_PIM_MESSAGE_SEARCHFILTERCRITERIA_HPP

#include <bb/pim/Global>

namespace bb {
namespace pim {
namespace message {

/*!
 * @headerfile SearchFilterCriteria.hpp <bb/pim/message/SearchFilterCriteria>
 *
 * @brief The @c SearchFilterCriteria class includes possible search criteria that you can 
 * use to search for messages.
 *
 * @details You can use this class in conjunction with the @c MessageSearchFilter class
 * to specify criteria for searches. You can add a @c %SearchFilterCriteria (along with
 * an associated value to search for) to a @c %MessageSearchFilter by calling
 * @c MessageSearchFilter::addSearchCriteria(). Then, you can search for the messages
 * that fit this criteria (that is, the messages that have the specified value in the
 * specified field) by calling @c MessageService::searchLocal() or
 * @c MessageService::searchRemote().
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
class BB_PIM_EXPORT SearchFilterCriteria
{
public:
    /*!
     * @brief An enumeration of supported fields that you can use to search for messages.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief Indicates that any message fields can be used to search for messages.
         *
         * @since BlackBerry 10.0.0
         */
        Any=0,
        /*!
         * @brief Indicates that the search should apply to the From field of a message.
         *
         * @since BlackBerry 10.0.0
         */
        FromAddress = 1,
        /*!
         * @brief Indicates that the search should apply to the Recipient field of a
         * message.
         *
         * @since BlackBerry 10.0.0
         */
        Recipient = 2,
        /*!
         * @brief Indicates that the search should apply to the Subject field of a
         * message.
         *
         * @since BlackBerry 10.0.0
         */
        Subject = 3,
        /*!
         * @brief Indicates that the search should apply to the Body field of a message.
         *
         * @since BlackBerry 10.0.0
         */
        Body = 4
    };

private:
    /*! @cond PRIVATE */
    SearchFilterCriteria();
    ~SearchFilterCriteria();
    /*! @endcond */
};

} /* namespace message */
} /* namespace pim */
} /* namespace bb */

#endif // BB_PIM_MESSAGE_SEARCHFILTERCRITERIA_HPP
