/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_ACCOUNT_ACCOUNTSERVICE_HPP
#define BB_PIM_ACCOUNT_ACCOUNTSERVICE_HPP

#include <bb/pim/Global>
#include <bb/pim/account/Account>
#include <bb/pim/account/Service>
#include <QList>
#include <QMap>
#include <QObject>
#include <QScopedPointer>
#include <QString>
#include <QVariantList>
#include <QVariantMap>

namespace bb {
namespace pim {
namespace account {

class AccountServicePrivate;
class AccountsChanged;
class Provider;
class Result;

/*!
 * @brief The @c AccountService class is the entry point for Account Management.
 *
 * @details It provides operations to manipulate @c Account objects and to view
 * @c Provider objects, which are used to build @c Account objects.
 *
 * Read access to the Account's domain is automatically granted when
 * requesting permission to another domain (access_pimdomain_messages or
 * access_pimdomain_contacts or access_pimdomain_calendars or
 * access_pimdomain_notebooks). Any Account calls requiring write access (to edit,
 * add or delete an account) are not granted to third party applications and will
 * result in failure.
 *
 * A signal is emitted when accounts are added, deleted, or modified.
 * Clients can respond to these signals.
 *
 * @xmlonly
 * <apigrouping group="App Integration/Account"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT AccountService : public QObject
{
    Q_OBJECT

public:

    /*!
     * @brief Creates a new @c AccountService object.
     *
     * @since BlackBerry 10.0.0
     */
    AccountService();

    /*!
     * @brief Destructor.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~AccountService();

    /*!
     * @brief Retrieves the list of @c Account objects currently stored on the
     * device.
     *
     * @return Returns a @c QList containing @c Account objects.
     *
     * @since BlackBerry 10.0.0
     */
    QList<Account> accounts();

    /*!
     * @brief Retrieves the list of @c Account objects currently stored on the
     * device including any accounts which are disabled.
     *
     * @return Returns a @c QList containing all @c Account objects.
     *
     * @since BlackBerry 10.3.0
     */
    QList<Account> allAccounts();

    /*!
     * @brief Retrieves the list of @c Account objects currently stored on the
     * device and currently synchronizing data for the @c service.
     *
     * @param service The value for which we seek the
     * @c Account::isServiceSupported(service) function to be set to true.
     *
     * @return Returns a @c QList containing @c Account objects, or an empty @c QList
     * if no matches were found.
     *
     * @since BlackBerry 10.0.0
     */
    QList<Account> accounts(Service::Type service);

    /*!
     * @brief Retrieves the list of @c Account objects currently stored on the
     * device, currently synchronizing data for the @c service and created from
     * a specific provider.
     *
     * @param service The value for which we seek the
     * @c Account::isServiceSupported(service) function to be set to true.
     *
     * @param providerId The value of the @c Provider object's @c id property
     * used to identify the provider to match with the @c Account::provider()
     * function.
     *
     * @return Returns a @c QList containing @c Account objects, or an empty @c QList
     * if no matches were found.
     *
     * @since BlackBerry 10.0.0
     */
    QList<Account> accounts(Service::Type service, const QString &providerId);

    /*!
     * @brief Retrieves a specific @c Account object.
     *
     * @param accountId The value of the @c Account object's @c id property
     * used to identify a specific account.
     *
     * @return Returns the @c Account object whose @c id property is set to
     * @c accountId, or an invalid @c Account object if no matches were found.
     *
     * @since BlackBerry 10.0.0
     */
    Account account(AccountKey accountId);

    /*!
     * @brief Creates an @c Account object.
     *
     * @param providerId The value of a @c Provider object's @c id property
     * used to identify the specific provider to use in creating a new @c Account object.
     *
     * @param accountData The data used to create the @c Account object. Initially,
     * the @c accountData should be created using the @c Account constructor that
     * takes a provider object as an argument. This generates the account
     * with the provider's default values. You can change
     * the default values using the setters available before calling
     * this function to create the account. The @c id property should not be
     * included in @c accountData as a new identifier will be generated. The
     * newly-created account will be returned in @c accountData if the function
     * is successful.
     *
     * @return Returns a @c Result object with @c success set to true if the
     * account creation is successful. If the account creation fails, returns
     * a @c Result object with @c success set to false and @c message containing
     * the detailed error message that caused the failure.
     *
     * @since BlackBerry 10.0.0
     */
    Result createAccount(const QString &providerId, Account &accountData);

    /*!
     * @brief Creates an @c Account object specifying an access secret
     *
     * @param providerId The value of a @c Provider object's @c id property
     * used to identify the specific provider to use in creating a new @c Account object.
     *
     * @param accountData The data used to create the @c Account object. Initially,
     * the @c accountData should be created using the @c Account constructor that
     * takes a provider object as an argument. This generates the account
     * with the provider's default values. You can change
     * the default values using the setters available before calling
     * this function to create the account. The @c id property should not be
     * included in @c accountData as a new identifier will be generated. The
     * newly-created account will be returned in @c accountData if the function
     * is successful.
     *
     * @param accessSecret The secret needed to be passed by clients to access this
     * account. The secret can only be passed at creation time and never modified.
     * Clients pass this secret into SessionManagementService::setSessionSecret()
     * before making any calls to the PIM library. This allows access to this
     * account, otherwise the account is hidden from the client.
     *
     * @return Returns a @c Result object with @c success set to true if the
     * account creation is successful. If the account creation fails, returns
     * a @c Result object with @c success set to false and @c message containing
     * the detailed error message that caused the failure.
     *
     * @since BlackBerry 10.2.0
     */
    Result createAccount(const QString &providerId, Account &accountData, const QString &accessSecret);

    /*!
     * @brief Updates an @c Account object.
     *
     * @param accountId The value of this @c Account object's @c id property.
     * This value must match the @c id property found in @c accountData.
     *
     * @param accountData The data used to update the @c Account object. Initially,
     * the @c accountData should be created using the already existing account
     * with @id property specified by accountId. The user may then choose to
     * change some of the values using the setters available before calling
     * this function to update the account. The @c id property of @c accountData
     * must match the value in @c accountId.
     *
     * @return Returns a @c Result object with @c success set to true if the
     * account update is successful. If the account update fails, returns
     * a @c Result object with @c success set to false and @c message containing
     * the detailed error message that caused the failure.
     *
     * @since BlackBerry 10.0.0
     */
    Result updateAccount(AccountKey accountId, const Account &accountData);

    /*!
     * @brief Deletes an @c Account object.
     *
     * @param accountId The value of a @c Account object's @c id property
     * used to identify the account to delete.
     *
     * @return Returns a @c Result object with @c success set to true if the
     * account deletion is successful. If the account deletion fails, returns
     * a @c Result object with @c success set to false and @c message containing
     * the detailed error message that caused the failure.
     *
     * @since BlackBerry 10.0.0
     */
    Result deleteAccount(AccountKey accountId);

    /*!
     * @brief Validates an @c Account object based on provider-specific checks.
     *
     * @param accountId The value of a @c Account object's @c id property
     * used to identify the account to test.
     *
     * @return Returns a @c Result object with @c success set to true if the
     * account validation is successful. If the account validation fails, returns
     * a @c Result object with @c success set to false and @c message containing
     * the detailed error message that caused the failure.
     *
     * @since BlackBerry 10.0.0
     */
    Result testAccount(AccountKey accountId);

    /*!
     * @brief Synchronizes the data for @c service of all @c Account objects that
     * currently support it.
     *
     * @param service The value of @c service for which we seek to synchronize
     * the data.
     *
     * @return Returns a @c Result object with @c success set to true if the
     * synchronization is successful. If the synchronization fails, returns
     * a @c Result object with @c success set to false and @c message containing
     * the detailed error message that caused the failure.
     *
     * @since BlackBerry 10.0.0
     */
    Result syncAccounts(Service::Type service);

    /*!
     * @brief Retrieves the default account set for a specific service.
     *
     * @details The default account is used by applications to specify the
     * output outlet. For example, the default account for @c Service::Messages
     * specifies the account from which an email application to send email from.
     *
     * @param service The value of @c service for which we seek the default
     * account.
     *
     * @return Returns the default account for the specific service,
     * or an invalid account if no default exists for that service.
     *
     * @since BlackBerry 10.0.0
     */
    Account defaultAccount(Service::Type service);

    /*!
     * @brief Retrieves the object ID set as the default for a specific service.
     *
     * @details This is useful for @c Service::Calendars which requires
     * an account as well as a calendar folder as the default.
     * This functionality is also available by using the
     * @c CalendarService::defaultCalendarFolder() function. It is recommended
     * that the latter be used.
     *
     * @param service The value of @c service for which we seek the default
     * account and object.
     *
     * @return Returns the object ID set as the default for @c service, and
     * Account::InvalidKey if no default exists for that service.
     *
     * @since BlackBerry 10.0.0
     */
    ObjectKey getDefault(Service::Type service);

    /*!
     * @brief Retrieves the default accounts set for all services.
     *
     * @return Returns a @c QMap containing the default accounts that are set for all services.
     *
     * @since BlackBerry 10.0.0
     */
    QMap<Service::Type,Account> defaultAccounts();

    /*!
     * @brief Associates a specific account as the default for a specific service.
     * Note: Changing the default for a specific service affects all
     * applications that are using the default account functionality.
     *
     * @details For @c Service::Calendars, this call will be ignored and
     * the current default account will be returned. To set the default calendar,
     * use @c CalendarService::setDefaultCalendarFolder instead.
     *
     * @param service The value of @c service for which we seek to change the
     * default account.
     *
     * @param accountId The value of an @c Account object's @c id property
     * used to identify the account to set as the default. The account in
     * question must exist and it must currently support @c service to be
     * considered as the default account.
     *
     * @return Returns the default account for @c service.
     * For @c Service::Calendars, this call will be ignored and the current
     * default account will be returned.
     *
     * @since BlackBerry 10.0.0
     */
    Account setDefaultAccount(Service::Type service, AccountKey accountId);

    /*!
     * @brief Associates a specific account and object as the default for a
     * specific service.
     * Note: Changing the default for a specific service affects all
     * applications that are using the default account functionality.
     *
     * @details This is useful for @c Service::Calendars which requires
     * an account as well as a calendar folder as the default.
     * This functionality is also available by using the
     * @c CalendarService::setDefaultCalendarFolder() function. It is
     * recommended that the latter be used.
     *
     * @param service The value of @c service for which we seek to change the
     * default account and object.
     *
     * @param accountId The value of an @c Account object's @c id property
     * used to identify the account to set as the default. The account in
     * question must exist and it must currently support @c service to be
     * considered as the default account.
     *
     * @param objectId The value of an object located within the @c Account
     * object specified by @c accountId.
     *
     * @return Returns a @c Result object with @c success set to true if
     * setting the new default is successful. If setting the new default fails, returns
     * a @c Result object with @c success set to false and @c message containing
     * the detailed error message that caused the failure.
     *
     * @since BlackBerry 10.0.0
     */
    Result setDefault(Service::Type service, AccountKey accountId, ObjectKey objectId);

    /*!
     * @brief Retrieves the list of all @c Provider objects.
     *
     * @return Returns a @c QList of @c Provider objects.
     *
     * @since BlackBerry 10.0.0
     */
    QList<Provider> providers();

    /*!
     * @brief Retrieves a specific @c Provider object.
     *
     * @param providerId The value of the @c Provider object's @c id property
     * used to identify a specific provider.
     *
     * @return Returns the @c Provider object whose @c id property is set to
     * @c providerId, or an invalid @c Provider object if no matches were found.
     *
     * @since BlackBerry 10.0.0
     */
    Provider provider(const QString &providerId);

Q_SIGNALS:
    /*!
     * @brief Represents the signal emitted when one or more @c Account objects
     * have been changed (added, updated, or deleted).
     *
     * @param notification The lists of account ids for added, updated, or deleted accounts.
     * See the @c AccountsChanged class for more details.
     *
     * @since BlackBerry 10.0.0
     */
    void accountsChanged(const bb::pim::account::AccountsChanged &notification);

private:
    Q_DISABLE_COPY(AccountService)
    Q_DECLARE_PRIVATE(AccountService)
    QScopedPointer<AccountServicePrivate> d_ptr;
};

} // namespace account
} // namespace pim
} // namespace bb

#endif // BB_PIM_ACCOUNT_ACCOUNTSERVICE_HPP
