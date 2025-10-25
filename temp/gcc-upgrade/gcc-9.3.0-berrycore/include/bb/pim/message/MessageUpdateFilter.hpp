/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef MessageUpdateFilter_HPP_
#define MessageUpdateFilter_HPP_

//#include <bb/pim/Global>
//#include <bb/pim/account/Account>
#include <bb/pim/message/MessageFolder>
#include <QSharedDataPointer>
#include <QDateTime>

namespace bb {
namespace pim {
namespace message {

class MessageUpdateFilterPrivate;

/*!
 * @headerfile MessageUpdateFilter.hpp <bb/pim/message/MessageUpdateFilter>
 *
 * @brief The @c MessageUpdateFilter class lets you specify options and parameters for bulk options.
 *
 * @details This class lets you specify options and parameters for bulk message update options,
 * such as mark or delete, and hide. To use this class, you need to instantiate a
 * @c MessageUpdateFilter object and set the @c priorDateTime and @c folderId.
 * You can optionally set @c MessageUpdateFilter::OperateOnFiledMessages or
 * @c MessageUpdateFilter::OperateOnSentMessages (these options are not
 * required when specifying a folder ID for a folder operation). Once the object is
 * created, you can pass it to the @c MessageService::markHidden() method.
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

class BB_PIM_EXPORT MessageUpdateFilter
{

public:

    /*!
    * @brief An enumeration of supported update filtering options.
    *
    * @since BlackBerry 10.3.0
    */
    enum UpdateOptions {
       /*!
        * @brief Indicates filtering on filed messages.
        *
        * @since BlackBerry 10.3.0
        */
       OperateOnFiledMessages= 1 << 0,
       /*!
        * @brief Indicates filtering on sent messages.
        *
        * @since BlackBerry 10.3.0
        */
       OperateOnSentMessages = 1 << 1
    };

    /*!
     * @brief An enumeration of supported operations for bulk message processing.
     *
     * @since BlackBerry 10.0.0
     */
    enum UpdateOperation {
       /*!
        * @brief Indicates an unknown operation.
        *
        * @since BlackBerry 10.0.0
        */
        Unknown    = 0,
       /*!
        * @brief Indicates a mark all as read operation.
        *
        * @since BlackBerry 10.0.0
        */
        MarkRead   = 1,
       /*!
        * @brief Indicates a mark all as unread operation.
        *
        * @since BlackBerry 10.0.0
        */
        MarkUnread = 2,
       /*!
        * @brief Indicates a delete operation.
        *
        * @since BlackBerry 10.0.0
        */
        Delete     = 3,
       /*!
        * @brief Indicates a hide operation.
        *
        * @since BlackBerry 10.0.0
        */
        Hide       = 4,
       /*!
        * @brief Indicates an unhide operation.
        *
        * @details This operation is currently not supported.
        *
        * @since BlackBerry 10.0.0
        */
        UnHide     = 5
    };

    /*!
     * @brief Constructs a new @c MessageUpdateFilter.
     *
     * @since BlackBerry 10.0.0
     */
    MessageUpdateFilter();

    /*!
     * @brief Copy constructor.
     *
     * @details This method constructs a @c MessageUpdateFilter containing exactly the same values as
     * the provided @c %MessageUpdateFilter.
     *
     * @param other The @c %MessageUpdateFilter to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    MessageUpdateFilter(const MessageUpdateFilter &other);

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c MessageUpdateFilter into this
     * @c %MessageUpdateFilter.
     *
     * @param other The @c %MessageUpdateFilter from which to copy all values.
     *
     * @return A @c %MessageUpdateFilter with all copied data.
     *
     * @since BlackBerry 10.0.0
     */
    MessageUpdateFilter& operator=(const MessageUpdateFilter &other);

    /*!
     * @brief Destroys this @c MessageUpdateFilter.
     *
     * @details This method cleans up and frees data and resources for the @c MessageUpdateFilter.
     *
     * @since BlackBerry 10.0.0
     */
    ~MessageUpdateFilter();


    /*!
     * @brief Sets the folder ID of the message folder that @c MessageUpdateFilter
     * applies to.
     *
     * @param folderId The folder where the MarkPrior Or DeletePrior operation is performed.
     *
     * @since BlackBerry 10.0.0
     */
    void setFolderId(MessageFolderKey folderId);

    /*!
     * @brief Sets the prior date and time values.
     *
     * @details This method sets the prior date and time values used by operations
     * using @c %MessageUpdateFilter.
     *
     * @param dateTime The date and time representing the upperbound time limit on the bulk delete action.
     * This is expressed in yyyy-MM-dd hh:mm:ss.zzzzzz format, for example, 2013-07-25 23:59:59.999999).
     *
     * @since BlackBerry 10.0.0
     */
    void setPriorDateTime(QDateTime& dateTime);

    /*!
     * @brief Adds option flags to this @c MessageUpdateFilter.
     *
     * @details This method sets option flags for this @c MessageUpdateFilter.
     * For example, if you want to exclude filed messages, call this method as follows:
     *
     * @code
     * setOptions(getOptions() | MessageUpdateFilter::OperateOnFiledMessages)
     * @endcode
     *
     * @param value The @c MessageUpdateFilter::Options to set.
     *
     * @since BlackBerry 10.0.0
     */
    void setOptions(int value);

    /*!
     * @brief Gets the folder ID of the message folder that @c MessageUpdateFilter
     * applies to.
     *
     * @return The folder ID of the message folder that @c MessageUpdateFilter applies to.
     *
     * @since BlackBerry 10.0.0
     */
    MessageFolderKey getFolderId() const;

    /*!
     * @brief Gets the prior date and time values.
     *
     * @details This method gets the prior date and time values used by operations
     * using @c %MessageUpdateFilter.
     *
     * @return A @c QString object expressed in yyyy-MM-dd hh:mm:ss.zzzzzz format
     * (for example, 2012-07-25 23:59:59.999999).
     *
     * @since BlackBerry 10.0.0
     */
    QString getPriorDateTime() const;

    /*!
     * @brief Gets all the options set for this @c MessageUpdateFilter.
     *
     * @details This method returns the options set for this @c MessageUpdateFilter,
     * as defined by @c MessageUpdateFilter::Options. For example, to check
     * if @c OperateOnFiledMessages is set, call this method as follows:
     *
     * @code
     * if (getOptions() & MessageUpdateFilter::OperateOnFiledMessages) != 0
     * @endcode
     *
     * @return The options that are set, as defined by @c MessageUpdateFilter::Options.
     *
     * @since BlackBerry 10.0.0
     */
    int getOptions() const;

    /*!
     * @brief Sets the priority inbox flag for @c MessageSearchFilter.
     *
     * @param isPriorityInboxSearch @c True if only priority inbox messages are to be operated on, @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
     void setPriorityInboxSearch(bool);

     /*!
      * @brief Gets the priority inbox flag for @c MessageSearchFilter.
      *
      * @return @c True if only priority inbox messages are operated on, @c false otherwise.
      *
      * @since BlackBerry 10.2.0
      */
     bool isPriorityInboxSearch() const;

private:
    QSharedDataPointer<MessageUpdateFilterPrivate> d_ptr;
};


} /* namespace message */
} /* namespace pim */
} /* namespace bb */

#endif /* MessageUpdateFilter_HPP_ */
