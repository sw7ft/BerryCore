/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */
#ifndef BB_PIM_CONTACTS_CONTACTONLINE_STATUS_HPP
#define BB_PIM_CONTACTS_CONTACTONLINE_STATUS_HPP

#include <bb/pim/Global>
#include <bb/pim/contacts/ContactConsts>
#include <QSharedDataPointer>
#include <QSharedData>
#include <QDateTime>
#include <QVariantMap>

namespace bb {
namespace pim {
namespace contacts {

class ContactOnlineStatusPrivate;

/*!
 * @brief The @c ContactOnlineStatus class represents the online status of a contact.
 * 
 * @details You can use this class to determine the online status of a @c Contact, as well as other information about the contact's
 * status. For example, you can retrieve the status message and status time stamp for a contact's status.
 * 
 * @see Contact
 *
 * @xmlonly
 * <apigrouping group="App Integration/Contacts"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT ContactOnlineStatus
{
public:
    /*!
     * @brief Constructs a new @c ContactOnlineStatus.
     *
     * @since BlackBerry 10.0.0
     */
    ContactOnlineStatus();

    /*!
     * @brief Destroys this @c ContactOnlineStatus.
     *
     * @since BlackBerry 10.0.0
     */
    ~ContactOnlineStatus();

    /*!
     * @brief Copy constructor.
     * 
     * @details This function constructs a @c ContactOnlineStatus containing exactly the same values as the provided
     * @c %ContactOnlineStatus.
     * 
     * @param copy The @c %ContactOnlineStatus to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    ContactOnlineStatus(const ContactOnlineStatus &copy);

    /*!
     * @brief Assignment operator.
     * 
     * @details This operator copies all values from the provided @c ContactOnlineStatus into this @c %ContactOnlineStatus.
     * 
     * @param operand The @c %ContactOnlineStatus from which to copy all values.
     *
     * @return A @c %ContactOnlineStatus with all copied data
     *
     * @since BlackBerry 10.0.0
     */
    ContactOnlineStatus& operator=(const ContactOnlineStatus &operand);
    
    /*!
     * @brief Retrieves the original account ID of the contact that's associated with this @c ContactOnlineStatus.
     * 
     * @details Contacts can be merged from multiple accounts to form a single contact. For example, contacts might be
     * merged from a LinkedIn account, Facebook account, and Twitter account. If the same contact exists in all accounts,
     * the contact information is merged into a single contact that includes all of the information from each account.
     * This function returns the account ID of the specific account that this online status applies to.
     * 
     * You can use this value, along with the @c AccountService class, to determine specific information about the
     * account.
     * 
     * @return The original account ID of the contact that's associated with this @c %ContactOnlineStatus.
     *
     * @see AccountService
     *
     * @since BlackBerry 10.0.0
     */
    AccountId originAccountId() const;

    /*!
     * @brief Retrieves the original sourced contact ID of the contact that's associated with this @c ContactOnlineStatus.
     * 
     * @details Contacts can be merged from multiple accounts to form a single contact. For example, contacts might be
     * merged from a LinkedIn account, Facebook account, and Twitter account. If the same contact exists in all accounts,
     * the contact information is merged into a single contact that includes all of the information from each account.
     * This function returns the contact ID of the specific contact (not the merged contact) that this online status
     * applies to.
     * 
     * You can use this value, along with the @c originAccountId() function, to retrieve a specific contact using
     * @c ContactService::contactDetails().
     * 
     * @return The original sourced contact ID of the contact that's associated with this @c %ContactOnlineStatus.
     *
     * @see @c ContactService
     *
     * @since BlackBerry 10.0.0
     */
    ContactId originContactId() const;

    /*!
     * @brief Retrieves the original sourced status ID of this @c ContactOnlineStatus.
     * 
     * @return The original sourced status ID of this @c %ContactOnlineStatus.
     *
     * @since BlackBerry 10.0.0
     */
    StatusId  originStatusId() const;

    /*!
     * @brief Retrieves the internal ID of this @c ContactOnlineStatus.
     * 
     * @return The internal ID of this @c %ContactOnlineStatus.
     *
     * @since BlackBerry 10.0.0
     */
    int id() const;
    
    /*!
     * @brief Indicates whether the source account that's associated with this @c ContactOnlineStatus is currently
     * synchronizing.
     * 
     * @return @c true if the source account is currently synchronizing, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isSyncing() const;

    /*!
     * @brief Indicates whether a Wi-Fi connection is currently active.
     * 
     * @return @c true if a Wi-Fi connection is currently active, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isWifiOn() const;

    /*!
     * @brief Retrieves the online status code of this @c ContactOnlineStatus.
     * 
     * @details The possible values of this status code and their associated states are as follows:
     * - 0: offline
     * - 1: online
     * - 2: away
     * - 3: busy
     * 
     * @return The online status code of this @c %ContactOnlineStatus.
     *
     * @since BlackBerry 10.0.0
     */
    int onlineStatusCode() const;

    /*!
     * @brief Retrieves the status message of this @c ContactOnlineStatus.
     * 
     * @details This message can be any text that the contact has set on their account.
     * 
     * @return The status message of this @c %ContactOnlineStatus.
     *
     * @since BlackBerry 10.0.0
     */
    QString statusMessage() const;

    /*!
     * @brief Retrieves the rich status of this @c ContactOnlineStatus.
     *
     * @details This status can include, text, images, links and videos.
     *
     * @return The complete status of this @c %ContactOnlineStatus.
     *
     * @since BlackBerry 10.0.0
     */
    QVariantMap status() const;

    /*!
     * @brief Retrieves the time stamp of this @c ContactOnlineStatus.
     * 
     * @details This time stamp represents the last time that the contact's status was updated.
     * 
     * @return The time stamp of this @c %ContactOnlineStatus.
     *
     * @since BlackBerry 10.0.0
     */
    QDateTime statusTimeStamp() const;
    
    /*!
     * @brief Indicates whether the user likes this @c ContactOnlineStatus.
     * 
     * @return @c true if the user likes this @c %ContactOnlineStatus, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool userLikes() const;

    /*!
     * @brief Indicates whether the user is allowed to like this @c ContactOnlineStatus.
     * 
     * @return @c true if the user likes this @c %ContactOnlineStatus, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool canLike() const;

    /*!
     * @brief Retrieves the number of likes for this @c ContactOnlineStatus.
     * 
     * @return The number of likes for this @c %ContactOnlineStatus.
     *
     * @since BlackBerry 10.0.0
     */
    int likeCount() const;

    /*!
     * @brief Indicates whether the user has favorited this @c ContactOnlineStatus.
     * 
     * @return @c true if the user has favorited this @c %ContactOnlineStatus, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isFavorited() const;

    /*!
     * @brief Indicates whether the user has retweeted this @c ContactOnlineStatus.
     * 
     * @return @c true if the user has retweeted this @c %ContactOnlineStatus, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isRetweeted() const;

    /*!
     * @brief Indicates whether the user is allowed to comment on this @c ContactOnlineStatus.
     * 
     * @return @c true if the user can comment on this @c %ContactOnlineStatus, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool canComment() const;

    /*!
     * @brief Indicates whether the user is allowed to delete this @c ContactOnlineStatus.
     * 
     * @return @c true if the user is allowed to delete this @c %ContactOnlineStatus, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool canDelete() const;

    /*!
     * @brief Retrieves the number of comments for this @c ContactOnlineStatus.
     * 
     * @return The number of comments for this @c %ContactOnlineStatus.
     *
     * @since BlackBerry 10.0.0
     */
    int commentCount() const;

 private:
    QSharedDataPointer<ContactOnlineStatusPrivate> d_ptr;
    friend class ContactOnlineStatusPrivate;
};

} // namespace contacts
} // namespace pim
} // namespace bb

#endif // BB_PIM_CONTACTS_CONTACTONLINE_STATUS_HPP
