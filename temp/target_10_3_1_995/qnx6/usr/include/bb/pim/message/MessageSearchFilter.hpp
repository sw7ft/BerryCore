/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_MESSAGE_MESSAGESEARCHFILTER_HPP
#define BB_PIM_MESSAGE_MESSAGESEARCHFILTER_HPP

#include <bb/pim/Global>
#include <bb/pim/account/Account>
#include <bb/pim/message/SearchFilterCriteria>
#include <bb/pim/message/SearchStatusCriteria>
#include <bb/pim/message/MessageFolder>

#include <QSharedDataPointer>
#include <QHash>

namespace bb {
namespace pim {
namespace message {

class MessageSearchFilterPrivate;

/*!
 * @brief The @c MessageSearchFilter class lets you specify search criteria for messages.
 * 
 * @details This class lets you search for and retrieve @c Message objects that fit certain
 * criteria. For example, you can search for messages that include the text "Cascades" in
 * the subject. Or, you can search for messages that have a certain status, such as read
 * or unread messages.
 * 
 * You can create a @c %MessageSearchFilter object and then pass it as a parameter to
 * search functions in @c MessageService (@c MessageService::searchLocal() and
 * @c MessageService::searchRemote()). A @c %MessageSearchFilter uses the
 * @c SearchFilterCriteria and @c SearchStatusCriteria to hold the criteria to search for.
 * 
 * @see Message, MessageService, SearchFilterCriteria, SearchStatusCriteria
 *
 * @xmlonly
 * <apigrouping group="App Integration/Message"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */

class BB_PIM_EXPORT MessageSearchFilter
{

public:

    /*!
     * @brief Constructs a new @c MessageSearchFilter.
     *
     * @since BlackBerry 10.0.0
     */
    MessageSearchFilter();

    /*!
     * @brief Copy constructor.
     * 
     * @details This function constructs a @c MessageSearchFilter containing exactly the same values as
     * the provided @c %MessageSearchFilter.
     * 
     * @param other The @c %MessageSearchFilter to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    MessageSearchFilter(const MessageSearchFilter &other);

    /*!
     * @brief Assignment operator.
     * 
     * @details This operator copies all values from the provided @c MessageSearchFilter into this
     * @c %MessageSearchFilter.
     * 
     * @param other The @c %MessageSearchFilter from which to copy all values.
     *
     * @return A @c %MessageSearchFilter with all copied data.
     *
     * @since BlackBerry 10.0.0
     */
    MessageSearchFilter& operator=(const MessageSearchFilter &other);

    /*!
     * @brief Destroys this @c MessageSearchFilter.
     *
     * @since BlackBerry 10.0.0
     */
    ~MessageSearchFilter();


    /*!
     * @brief Sets the folder ID of the message folder that this @c MessageSearchFilter
     * applies to.
     *
     * @param folderId The folder to search.
     *
     * @since BlackBerry 10.0.0
     */
    void setFolderId(MessageFolderKey folderId);

    /*!
     * @brief Sets the account ID that this @c MessageSearchFilter applies to.
     * 
     * @details Note that this function may be deprecated in the future. The account ID
     * must be passed as a parameter to @c MessageService::searchLocal() and
     * @c MessageService::searchRemote(), and so the account ID that's specified here
     * is not used.
     * 
     * @param accountId The account to search.
     *
     * @since BlackBerry 10.0.0
     */
    void setAccountId(bb::pim::account::AccountKey accountId);

    /*!
     * @brief Sets the offset of this @c MessageSearchFilter.
     * 
     * @details This function sets the number of messages after the first message that
     * this @c %MessageSearchFilter starts searching.
     * 
     * @param offset The offset (in number of messages).
     *
     * @since BlackBerry 10.0.0
     */
    void setOffset(int offset);

    /*!
     * @brief Sets the maximum number of search results for this @c MessageSearchFilter.
     * 
     * @param limit The maximum number of search results.
     *
     * @since BlackBerry 10.0.0
     */
    void setLimit(int limit);

    /*!
     * @brief Retrieves the key-value pairs of search parameters for this @c MessageSearchFilter.
     * 
     * @details For example, if you want to search for all messages that have a subject of "hello",
     * this function returns a key-value pair of <"subject", "hello">
     *
     * @return The key-value pairs of search parameters.
     *
     * @since BlackBerry 10.0.0
     */
    QHash<QString, QString> searchParams() const;

    /*!
     * @brief Adds a search criteria to this @c MessageSearchFilter.
     * 
     * @details For example, if you want search for all messages that have a subject of "hello",
     * you should call this function with parameters of @c SearchFilterCriteria::Subject and "hello".
     * 
     * @param searchCriteria The type of search criteria to add (for example, subject, body, and so
     * on).
     * @param value The value to search for.
     *
     * @since BlackBerry 10.0.0
     */
    void addSearchCriteria(SearchFilterCriteria::Type searchCriteria, const QString& value);

    /*!
     * @brief Adds a status criteria to this @c MessageSearchFilter.
     * 
     * @details For example, if you want search for unread messages only, you should call this
     * function with a parameter of @c SearchStatusCriteria::Unread.
     * 
     * @param statusCriteria The status criteria to add.
     *
     * @since BlackBerry 10.0.0
     */
    void addStatusCriteria(SearchStatusCriteria::Type statusCriteria);

    /*!
     * @brief Removes the provided status criteria that was previously set for this
     * @c MessageSearchFilter.
     * 
     * @param statusCriteria The status criteria to remove.
     *
     * @since BlackBerry 10.0.0
     */
    void removeStatusCriteria(SearchStatusCriteria::Type statusCriteria);

    /*!
     * @brief Sets the priority inbox flag for search
     * @c MessageSearchFilter.
     *
     * @param isPriorityInboxSearch Set to true if only priority inbox emails
     * need to be shown in search results.
     *
     * @since BlackBerry 10.2.0
     */
     void setPriorityInboxSearch(bool);

     /*!
      * @brief Gets the priority inbox flag status for search
      * @c MessageSearchFilter.
      *
      * @return @c true if Priority Inbox Search flag was set to true earlier,
      * false otherwise.
      *
      * @since BlackBerry 10.2.0
      */
     bool isPriorityInboxSearch() const;

private:
    QSharedDataPointer<MessageSearchFilterPrivate> d_ptr;


};


} /* namespace message */
} /* namespace pim */
} /* namespace bb */

#endif // BB_PIM_MESSAGE_MESSAGESEARCHFILTER_HPP
