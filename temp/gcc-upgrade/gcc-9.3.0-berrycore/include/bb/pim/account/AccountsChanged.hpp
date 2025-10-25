
/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_ACCOUNT_ACCOUNTSCHANGED_HPP
#define BB_PIM_ACCOUNT_ACCOUNTSCHANGED_HPP

#include <bb/pim/Global>
#include <bb/pim/account/Account>
#include <QSharedDataPointer>
#include <QList>

namespace bb {
namespace pim {
namespace account {

class AccountsChangedPrivate;
class AccountChangeListener;

/*!
 * @brief The @c AccountsChanged class provides the necessary information to the
 * client regarding changes that have taken place on @c Account objects stored on
 * the device.
 *
 * @details When an account is added, updated or deleted by the device core
 * application or some third-party application running on the device, it may be
 * necessary for other applications to be made aware of these changes. The signal
 * @c AccountService::accountsChanged is provided for clients that want to
 * respond to such account changes. This particular signal will include an
 * @c AccountsChanged object that will contain the account ids of any added,
 * updated, and deleted accounts.
 *
 * @xmlonly
 * <apigrouping group="App Integration/Account"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT AccountsChanged {
public:

    /*!
     * @brief Creates a new @c AccountsChanged object.
     *
     * @since BlackBerry 10.0.0
     */
    AccountsChanged();

    /*!
     * @brief Destructor.
     *
     * @since BlackBerry 10.0.0
     */
    ~AccountsChanged();

    /*!
     * @brief Creates a copy of an existing @c AccountsChanged object.
     *
     * @param other The @c AccountsChanged object to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    AccountsChanged(const AccountsChanged& other);

    /*!
     * @brief Copies the data of an existing @c AccountsChanged object to this object.
     *
     * @param other The @c AccountsChanged object to be copied.
     *
     * @return Returns the @c AccountsChanged instance.
     *
     * @since BlackBerry 10.0.0
     */
    AccountsChanged& operator=(const AccountsChanged& other);

    /*!
     * @brief Represents the newly-created accounts sent with the signal @c AccountService::accountsChanged.
     *
     * @return Returns a @c QList containing the @c id of all newly-created @c Account objects.
     *
     * @since BlackBerry 10.0.0
     */
    QList<AccountKey> createdAccountIds() const;

    /*!
     * @brief Represents the newly-updated accounts sent with the signal @c AccountService::accountsChanged.
     *
     * @return Returns a @c QList containing the @c id of all newly-updated @c Account objects.
     *
     * @since BlackBerry 10.0.0
     */
    QList<AccountKey> updatedAccountIds() const;

    /*!
     * @brief Represents the newly-deleted accounts sent with the signal @c AccountService::accountsChanged.
     *
     * @return Returns a @c QList containing the @c id of all newly-deleted @c Account objects.
     *
     * @since BlackBerry 10.0.0
     */
    QList<AccountKey> deletedAccountIds() const;

    /*!
     * @brief Represents the newly-authenticated accounts sent with the signal @c AccountService::accountsChanged().
     *
     * @return Returns a @c QList containing the @c id of all newly-authenticated @c Account objects.
     *
     * @since BlackBerry 10.1.0
     */
    QList<AccountKey> connectedAccountIds() const;

    /*!
     * @brief Represents the newly-invalidated accounts sent with the signal @c AccountService::accountsChanged().
     *
     * @return Returns a @c QList containing the @c id of all newly-invalidated @c Account objects.
     *
     * @since BlackBerry 10.1.0
     */
    QList<AccountKey> invalidatedAccountIds() const;

    /*!
     * @brief Represents the accounts that have just started syncing sent with the signal @c AccountService::accountsChanged().
     *
     * @return Returns a @c QList containing the @c id of all @c Account objects that have just started syncing.
     *
     * @since BlackBerry 10.1.0
     */
    QList<AccountKey> syncStartedAccountIds() const;

    /*!
     * @brief Represents the newly-synced accounts sent with the signal @c AccountService::accountsChanged().
     *
     * @return Returns a @c QList containing the @c id of all newly-synced @c Account objects.
     *
     * @since BlackBerry 10.1.0
     */
    QList<AccountKey> syncedAccountIds() const;

protected:
    /*!
     * @brief Set function for the newly-created accounts to be sent with the signal
     * @c AccountService::accountsChanged.
     *
     * @param createdAccountIds The @c QList containing the @c id of all newly-created
     * @c Account objects to be sent.
     *
     * @since BlackBerry 10.0.0
     */
    void setCreatedAccountIds(const QList<AccountKey> &createdAccountIds);

    /*!
     * @brief Set function for the newly-updated accounts to be sent with the signal
     * @c AccountService::accountsChanged.
     *
     * @param updatedAccountIds The @c QList containing the @c id of all newly-updated
     * @c Account objects to be sent.
     *
     * @since BlackBerry 10.0.0
     */
    void setUpdatedAccountIds(const QList<AccountKey> &updatedAccountIds);

    /*!
     * @brief Set function for the newly-deleted accounts to be sent with the signal
     * @c AccountService::accountsChanged.
     *
     * @param deletedAccountIds The @c QList containing the @c id of all newly-deleted
     * @c Account objects to be sent.
     *
     * @since BlackBerry 10.0.0
     */
    void setDeletedAccountIds(const QList<AccountKey> &deletedAccountIds);

    /*!
     * @brief Set function for newly-authenticated accounts to be sent with the signal
     * @c AccountService::accountsChanged(). Prior to receiving this signal, these
     * accounts aren't necessarily in an invalid or disconnected state.
     *
     * @param connectedAccountIds A @c QList containing the @c id of all
     * newly-authenticated @c Account objects to be sent.
     *
     * @since BlackBerry 10.1.0
     */
    void setConnectedAccountIds(const QList<AccountKey> &connectedAccountIds);

    /*!
     * @brief Set function for newly-invalidated accounts to be sent with the signal
     * @c AccountService::accountsChanged().
     *
     * @param invalidatedAccountIds A @c QList containing the @c id of all
     * newly-invalidated @c Account objects to be sent.
     *
     * @since BlackBerry 10.1.0
     */
    void setInvalidatedAccountIds(const QList<AccountKey> &invalidatedAccountIds);

    /*!
     * @brief Set function for the accounts that have just started syncing
     * to be sent with the signal @c AccountService::accountsChanged().
     *
     * @param syncStartedAccountIds A @c QList containing the @c id of all
     * @c Account objects that have just started syncing to be sent.
     *
     * @since BlackBerry 10.1.0
     */
    void setSyncStartedAccountIds(const QList<AccountKey> &syncStartedAccountIds);

    /*!
     * @brief Set function for newly-synced accounts to be sent with the signal
     * @c AccountService::accountsChanged().
     *
     * @param syncedAccountIds A @c QList containing the @c id of all
     * newly-synced @c Account objects to be sent.
     *
     * @since BlackBerry 10.1.0
     */
    void setSyncedAccountIds(const QList<AccountKey> &syncedAccountIds);

private:
    QSharedDataPointer<AccountsChangedPrivate> d_ptr;
    friend class AccountChangeListener;

};

} // namespace account
} // namespace pim
} // namespace bb

#endif // BB_PIM_ACCOUNT_ACCOUNTSCHANGED_HPP

