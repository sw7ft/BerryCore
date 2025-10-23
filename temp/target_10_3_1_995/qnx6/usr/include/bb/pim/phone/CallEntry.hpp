/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2014
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_PHONE_CALL_ENTRY_HPP
#define BB_PIM_PHONE_CALL_ENTRY_HPP

#include <bb/pim/account/Account>
#include <bb/pim/contacts/ContactConsts>
#include <bb/pim/phone/CallType>

#include <QList>
#include <QSharedDataPointer>

namespace bb {
namespace pim {
namespace phone {

/*!
 * @brief typedef for Call Entry ID
 *
 * @since BlackBerry 10.3.0
 */
typedef qint64 CallEntryId;

class CallEntryPrivate;

/*!
 * @brief A @c CallEntry represents the history of a single call.
 *
 * @details To fetch a history of calls made, use @c CallHistoryService.
 *
 * @see CallHistoryService::callHistory()
 *
 * @xmlonly
 * <apigrouping group="App Integration/Phone"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.3.0
 */
class BB_PIM_EXPORT CallEntry
{
public:
    /*!
     * @brief Constructs an invalid CallEntry.
     *
     * @details The default constructor is meant to be used in conjunction with
     * the assignment operator. This constructor is useful in cases where
     * initialization needs to be deferred (such as a temporary variable).
     *
     * @see CallEntry::isValid
     *
     * @since BlackBerry 10.3.0
     */
    CallEntry();

    /*!
     * @brief Copy constructor.
     *
     * @details This constructor initializes this @c CallEntry with the values
     * from the provided @c CallEntry.
     *
     * @param other The @c CallEntry to be copied.
     *
     * @since BlackBerry 10.3.0
     */
    CallEntry(const CallEntry& other);

    /*!
     * @brief Destroys this @c CallEntry.
     *
     * @since BlackBerry 10.3.0
     */
    ~CallEntry();

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c CallEntry into this
     * @c CallEntry.
     *
     * @param other The @c CallEntry to be copied.
     *
     * @since BlackBerry 10.3.0
     */
    CallEntry& operator=(const CallEntry& other);

    /* Basic information */

    /*!
     * @brief Indicates the validity of this @c CallEntry
     *
     * @details This @c CallEntry is valid if accountId and id are non-negative.
     *
     * @return true if the @c CallEntry is valid, otherwise false
     */
    bool isValid() const;

    /*!
     * @brief The unique identifier of this call.
     *
     * @return This CallEntry's ID.
     *
     * @since BlackBerry 10.3.0
     */
    CallEntryId id() const;

    /*!
     * @brief Retrieves the account ID of this call.
     *
     * @return This CallEntry's account ID.
     *
     * @since BlackBerry 10.3.0
     */
    bb::pim::account::AccountKey accountId() const;

    /*!
     * @brief The phone number of the call.
     *
     * @return This CallEntry's phone number.
     *
     * @note This field may be empty if the network does not provide this information.
     *
     * @since BlackBerry 10.3.0
     */
    QString phoneNumber() const;

    /*!
     * @brief Retrieves caller name as provided by the network.
     *
     * @return This CallEntry's name as provided by the network (e.g. Caller ID).
     *
     * @note If the network does not provide a name, this field will be empty.
     *
     * @since BlackBerry 10.3.0
     */
    QString callerName() const;

    /*!
     * @brief Retrieves the duration of call, in seconds.
     *
     * @return Duration of call, in seconds.
     *
     * @since BlackBerry 10.3.0
     */
    int duration() const;

    /*!
     * @brief Retrieves the error code from the network. A value of 0 usually implies no error.
     *
     * @return Error code from the network.
     *
     * @since BlackBerry 10.3.0
     */
    int networkCode() const;

    /*!
     * @brief Retrieves when the call began.
     *
     * @return when the call began.
     *
     * @since BlackBerry 10.3.0
     */
    QDateTime startDate() const;

    /*!
     * @brief Retrieves the type of the call.
     *
     * @details This field publishes the type of the call.
     *
     * @return the type of the call.
     *
     * @see CallType::Type
     *
     * @since BlackBerry 10.3.0
     */
    CallType::Type callType() const;

    /*!
     * @brief Retrieves the name of the line on which the call was made.
     *
     * @details The phone may support multiple lines on which a call can be made.
     * The most common line is cellular; a cellular call will have "cellular" in this field.
     *
     * @return the CallEntry's Line ID.
     *
     * @since BlackBerry 10.3.0
     */
    QString lineId() const;
private:
    QSharedDataPointer<CallEntryPrivate> d_ptr;
    friend class CallEntryPrivate;
};

/*!
 * @brief List of Call Entry IDs.
 *
 * @since BlackBerry 10.3.0
 */
typedef QList<CallEntryId> CallEntryIdList;

} // namespace phone
} // namespace pim
} // namespace bb

#endif /* BB_PIM_PHONE_CALL_ENTRY_HPP */