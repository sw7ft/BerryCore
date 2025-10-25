/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef MarkOrDeletePrior_HPP_
#define MarkOrDeletePrior_HPP_

#include <bb/pim/Global>
#include <bb/pim/account/Account>
#include <bb/pim/message/MarkOrDeletePriorOp>

#include <QSharedDataPointer>
#include <QHash>

namespace bb {
namespace pim {
namespace message {

class MarkOrDeletePriorFilterPrivate;

/*!
 * @headerfile MarkOrDeletePriorFilter.hpp <bb/pim/message/MarkOrDeletePriorFilter>
 *
 * @brief The @c MarkOrDeletePriorFilter class lets you specify options and parameters for prior options.
 *
 * @details This class lets you specify options and parameters for prior options,
 * such as mark or delete. To use this class, you need to instantiate a
 * @c MarkOrDeletePriorFilter object and set the priorDateTime and folderId.
 * You can optionally set @c MarkOrDeletePriorFilter::OperateOnFiledMessages or
 * @c MarkOrDeletePriorFilter::OperateOnSentMessages (these options are not
 * required when specifying a folder ID for a folder operation). Once the object is
 * created, you can pass it to the @c MessageService::markOrDeletePrior() method.
 *
 * @see Message, MessageService, MarkOrDeletePriorOp
 *
 * @xmlonly
 * <apigrouping group="App Integration/Message"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */

class BB_PIM_EXPORT MarkOrDeletePriorFilter
{

public:

    /* @brief An enumeration of supported prior to date operations for messages.
    *
    * @since BlackBerry 10.0.0
    */
    enum Options {
       /*!
       * @brief Indicates that the prior to date operations should apply to unread messages.
       * This option is not meant to be used for prior operations on search results.
       *
       * @since BlackBerry 10.0.0
       */
       OperateOnFiledMessages= 1 << 0,
       /*!
       * @brief Indicates that the prior to date operations should apply to flagged messages.
       * This option is not meant to be used for prior operations on search results.
       * @since BlackBerry 10.0.0
       */
       OperateOnSentMessages = 1 << 1
    };


    /*!
     * @brief Constructs a new @c MarkOrDeletePriorFilter.
     *
     * @since BlackBerry 10.0.0
     */
    MarkOrDeletePriorFilter();

    /*!
     * @brief Copy constructor.
     *
     * @details This method constructs a @c MarkOrDeletePriorFilter containing exactly the same values as
     * the provided @c %MarkOrDeletePriorFilter.
     *
     * @param other The @c %MarkOrDeletePriorFilter to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    MarkOrDeletePriorFilter(const MarkOrDeletePriorFilter &other);

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c MarkOrDeletePriorFilter into this
     * @c %MarkOrDeletePriorFilter.
     *
     * @param other The @c %MarkOrDeletePriorFilter from which to copy all values.
     *
     * @return A @c %MarkOrDeletePriorFilter with all copied data.
     *
     * @since BlackBerry 10.0.0
     */
    MarkOrDeletePriorFilter& operator=(const MarkOrDeletePriorFilter &other);

    /*!
     * @brief Destroys this @c MarkOrDeletePriorFilter.
     *
     * @details This method cleans up and frees data and resources for the @c MarkOrDeletePriorFilter.
     *
     * @since BlackBerry 10.0.0
     */
    ~MarkOrDeletePriorFilter();


    /*!
     * @brief Sets the folder ID of the message folder that @c MarkOrDeletePriorFilter
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
     * using @c %MarkOrDeletePriorFilter.
     *
     * @param dateTime The date and time representing the upperbound time limit on the bulk delete action.
     * This is expressed in yyyy-MM-dd hh:mm:ss.zzzzzz format, for example, 2013-07-25 23:59:59.999999).
     *
     * @since BlackBerry 10.0.0
     */
    void setPriorDateTime(QDateTime& dateTime);

    /*!
     * @brief Adds option flags to this @c MarkOrDeletePriorFilter.
     *
     * @details This method sets option flags for this @c MarkOrDeletePriorFilter.
     * For example, if you want to exclude filed messages, call this method as follows:
     *
     * @code
     * setOptions(getOptions() | MarkOrDeletePriorFilter::OperateOnFiledMessages)
     * @endcode
     *
     * @param value The @c MarkOrDeletePriorFilter::Options to set.
     *
     * @since BlackBerry 10.0.0
     */
    void setOptions(int value);

    /*!
     * @brief Gets the folder ID of the message folder that @c MarkOrDeletePriorFilter
     * applies to.
     *
     * @return The folder ID of the message folder that @c MarkOrDeletePriorFilter applies to.
     *
     * @since BlackBerry 10.0.0
     */
    MessageFolderKey getFolderId() const;

    /*!
     * @brief Gets the prior date and time values.
     *
     * @details This method gets the prior date and time values used by operations
     * using @c %MarkOrDeletePriorFilter.
     *
     * @return A @c QString object expressed in yyyy-MM-dd hh:mm:ss.zzzzzz format
     * (for example, 2012-07-25 23:59:59.999999).
     *
     * @since BlackBerry 10.0.0
     */
    QString getPriorDateTime() const;

    /*!
     * @brief Gets all the options set for this @c MarkOrDeletePriorFilter.
     *
     * @details This method returns the options set for this @c MarkOrDeletePriorFilter,
     * as defined by @c MarkOrDeletePriorFilter::Options. For example, to check
     * if @c OperateOnFiledMessages is set, call this method as follows:
     *
     * @code
     * if (getOptions() & MarkOrDeletePriorFilter::OperateOnFiledMessages) != 0
     * @endcode
     *
     * @return The options that are set, as defined by @c MarkOrDeletePriorFilter::Options.
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
    QSharedDataPointer<MarkOrDeletePriorFilterPrivate> d_ptr;
};


} /* namespace message */
} /* namespace pim */
} /* namespace bb */

#endif /* MarkOrDeletePriorFilter_HPP_ */
