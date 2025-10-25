/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2014
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_COMMON_CONTACT_ENTRY_HPP
#define BB_PIM_COMMON_CONTACT_ENTRY_HPP

#include <QSharedDataPointer>

#include <bb/pim/account/Account>
#include <bb/pim/contacts/ContactConsts>
#include <bb/pim/Global>

namespace bb {
namespace pim {
namespace common {

class ContactEntryPrivate;

/*!
 * @brief This class is used by @c CallHistoryService to return contact information
 * about a @c CallHistory.
 *
 * @xmlonly
 * <apigrouping group="App Integration/Phone"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.3.0
 */
class BB_PIM_EXPORT ContactEntry
{
public:

    /*!
     * @brief Constructs an invalid ContactEntry.
     *
     * @details The default constructor is meant to be used in conjunction with
     * the assignment operator. This constructor is useful in cases where
     * initialization needs to be deferred (such as a temporary variable).
     *
     * @see ContactEntry::isValid
     *
     * @since BlackBerry 10.3.0
     */
    ContactEntry();

    /*!
     * @brief Destroys this @c ContactEntry.
     *
     * @since BlackBerry 10.3.0
     */
    ~ContactEntry();

    /*!
     * @brief Copy constructor.
     *
     * @details This constructor initializes this @c ContactEntry with the values
     * from the provided @c ContactEntry.
     *
     * @param other The @c ContactEntry to be copied.
     *
     * @since BlackBerry 10.3.0
     */
    ContactEntry(const ContactEntry& other);

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c ContactEntry into this
     * @c ContactEntry.
     *
     * @since BlackBerry 10.3.0
     */
    ContactEntry& operator=(const ContactEntry& other);

    /*!
     * @brief Indicates the validity of this @c ContactEntry.
     *
     * @details This @c ContactEntry is valid if accountId and id are non-negative.
     *
     * @return true if this @c ContactEntry is valid, @c false otherwise.
     *
     * @since BlackBerry 10.3.0
     */
    bool isValid() const;

    /*!
     * @brief Unique identifier of the contact.
     *
     * @details  Use this ID in conjunction with ContactService
     * to get more details about the contact.
     *
     * @return contact's ID.
     *
     * @see @c bb::pim::contacts::ContactService
     *
     * @since BlackBerry 10.3.0
     */
    bb::pim::contacts::ContactId id() const;

    /*!
     * @brief The account ID for this contact.
     *
     * @details This ID corresponds to the provider account of this contact.
     *
     * @return contact's account ID.
     *
     * @see bb::pim::contacts::Contact::accountId
     *
     * @since BlackBerry 10.3.0
     */
    bb::pim::contacts::AccountId accountId() const;
private:
    QSharedDataPointer<ContactEntryPrivate> d_ptr;
    friend class ContactEntryPrivate;
};

} // namespace common
} // namespace pim
} // namespace bb

#endif /* BB_PIM_COMMON_CONTACT_ENTRY_HPP */