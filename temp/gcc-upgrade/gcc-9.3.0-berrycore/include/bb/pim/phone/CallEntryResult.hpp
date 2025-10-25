/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2014
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_PHONE_CALL_ENTRY_RESULT_HPP
#define BB_PIM_PHONE_CALL_ENTRY_RESULT_HPP

#include <QSharedDataPointer>

#include <bb/pim/account/Account>
#include <bb/pim/contacts/ContactConsts>
#include <bb/pim/phone/CallEntry>
#include <bb/pim/common/ContactEntry>

namespace bb {
namespace pim {
namespace phone {

class CallEntryResultPrivate;

/**
 * @brief This class represents the results of fetching CallEntry from @c CallHistoryService.
 *
 * Extra information about CallEntry (such as @c ContactEntry) is also populated here, if requested.
 *
 * @xmlonly
 * <apigrouping group="App Integration/Phone"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.3.0
 */
class BB_PIM_EXPORT CallEntryResult
{
public:
    /*!
     * @brief Construct an invalid CallEntryResult.
     *
     * @details The default constructor is meant to be used in conjunction with
     * the assignment operator. This constructor is useful in cases where
     * initialization needs to be deferred (such as a temporary variable).
     *
     * @see CallEntryResult::isValid
     *
     * @since BlackBerry 10.3.0
     */
    CallEntryResult();

    /*!
     * @brief Copy constructor.
     *
     * @details This constructor initializes this @c CallEntryResult with the values
     * from the provided @c CallEntryResult.
     *
     * @param other The @c CallEntryResult to be copied.
     *
     * @since BlackBerry 10.3.0
     */
    CallEntryResult(const CallEntryResult& other);

    /*!
     * @brief Destroys this @c CallEntryResult.
     *
     * @since BlackBerry 10.3.0
     */
    ~CallEntryResult();

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c CallEntryResult into this
     * @c CallEntryResult.
     *
     * @param other The @c CallEntryResult to be copied.
     *
     * @since BlackBerry 10.3.0
     */
    CallEntryResult& operator=(const CallEntryResult& other);

    /*!
     * @brief Indicates the validity of this @c CallEntryResult.
     *
     * @details This @c CallEntryResult is valid if its @c CallEntry is valid.
     *
     * @return true if this @c CallEntryResult is valid, @c false otherwise.
     *
     * @see CallEntryResult::call, CallEntry::isValid
     *
     * @since BlackBerry 10.3.0
     */
    bool isValid() const;

    /*!
     * @brief Retrieve the @c CallEntry.
     *
     * @return The @c CallEntry.
     *
     * @since BlackBerry 10.3.0
     */
    CallEntry call() const;

    /*!
     * @brief Retrieve a list of contacts that match this @c CallEntry.
     *
     * @details This list is populated by contact search during a fetch.
     * Without contact search enabled, this list will be empty.
     *
     * @return a list of contacts that match this @c CallEntry
     *
     * @see CallHistoryFilter::contactSearchEnabled
     *
     * @since BlackBerry 10.3.0
     */
    QList<bb::pim::common::ContactEntry> contacts() const;

private:
    QSharedDataPointer<CallEntryResultPrivate> d_ptr;
    friend class CallEntryResultPrivate;
};

} // namespace phone
} // namespace pim
} // namespace bb

#endif /* BB_PIM_PHONE_CALL_ENTRY_RESULT_HPP */