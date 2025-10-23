/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_ACCOUNT_ACCOUNT_HPP
#define BB_PIM_ACCOUNT_ACCOUNT_HPP

#include <bb/pim/Global>
#include <bb/pim/account/Property>
#include <bb/pim/account/Service>
#include <QDebug>
#include <QSharedDataPointer>
#include <QString>
#include <QVariantMap>

namespace bb {
namespace pim {
namespace account {

class AccountPrivate;
class Provider;
class Result;

typedef qint64 AccountKey;
typedef qint64 ObjectKey;

/*!
 * @brief An @c Account.
 *
 * @details This class represents an @c Account record.
 *
 * @xmlonly
 * <apigrouping group="App Integration/Account"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT Account
{
public:
    /*!
     * @brief Predefined @c AccountKey value.
     *
     * @since BlackBerry 10.0.0
     */
    enum KeyValue {
        /*!
         * @brief Specifies an invalid @c AccountKey.
         *
         * @since BlackBerry 10.0.0
         */
        InvalidKey = -1
    };

    /*!
     * @brief Default constructor meant to be used as a utility constructor
     * for assignment operations.
     *
     * @details Using this constructor to build an @c Account object will result
     * in an @c Account object that is invalid. In other words, calling
     * @c isValid() on the created object will return @c false. This constructor
     * is used to create an empty @c Account object for the purposes of
     * assigning another valid @c Account object to it.
     *
     * @since BlackBerry 10.0.0
     */
    Account();

    /*!
     * @brief Creates a new @c Account object.
     *
     * @details Using this constructor to build an @c Account object will result
     * in an @c Account object with all properties set to the defaults, as
     * defined by the provider. This @c Account object can be used directly in
     * a call to the @c AccountService::createAccount() function.
     *
     * @note A call to the @c isValid() function for the @c Account object
     * will still return @c false as this account is not created until a call to
     * the @c AccountService::createAccount() function is made.
     *
     * @param provider The provider whose default properties are used to create
     * the @Account object.
     *
     * @since BlackBerry 10.0.0
     */
    explicit Account(const Provider &provider);

    /*!
     * @brief Creates a new @c Account object, assigning an owner of the account.
     *
     * @details Using this constructor to build an @c Account object will result
     * in an @c Account object with all properties set to the defaults, as
     * defined by the provider, and assign an owning application. This @c Account
     * object can be used directly in a call to the @c AccountService::createAccount()
     * function.
     *
     * @note A call to the @c isValid() function for the @c Account object
     * will still return @c false as this account is not created until a call to
     * the @c AccountService::createAccount() function is made.
     *
     * @param provider The provider whose default properties are used to create
     * the @Account object.
     *
     * @param owner  The owner of the account, which is the bar package name of the
     * application or service who owns the account. The owner MUST be the same as
     * the bar package name as seen in the /apps directory on the device.
     *
     * @since BlackBerry 10.3.0
     */
    Account(const Provider &provider, const QString &owner);

    /*!
     * @brief Destructor.
     *
     * @since BlackBerry 10.0.0
     */
    ~Account();

    /*!
     * @brief Creates a copy of an existing @c Account object.
     *
     * @param other The @c Account object to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    Account(const Account &other);

    /*!
     *
     * @brief Copies the data of an existing @c Account object to this object.
     *
     * @param other The @c Account object to be copied.
     *
     * @return The @c Account instance.
     *
     * @since BlackBerry 10.0.0
     */
    Account& operator=(const Account &other);

    /*!
     * @brief Represents the @c Account object's @c Provider object.
     *
     * @details Provides access to the @c Account object's @c Provider object.
     *
     * @return Returns the @c Provider object associated with
     * the @c Account object.
     *
     * @since BlackBerry 10.0.0
     */
    Provider provider() const;

    /*!
     * @brief Represents the @c Account object's @c displayName property.
     *
     * @details Provides access to the @c Account object's
     * @c displayName property.
     *
     * @return Returns a @c QString containing the @c Account object's
     * @c displayName property.
     *
     * @since BlackBerry 10.0.0
     */
    QString displayName() const;

    /*!
     * @brief Represents the @c Account object's @c owner property.
     *
     * @details Provides access to the @c Account object's
     * @c owner property.
     *
     * @return Returns a @c QString containing the @c Account object's
     * @c owner property.
     *
     * @since BlackBerry 10.3.0
     */
    QString owner() const;

    /*!
     * @brief Represents the @c Account object's @c id property.
     *
     * @details Provides access to the @c Account object's @c id property.
     *
     * @return Returns the value of the @c Account object's @c id property.
     *
     * @since BlackBerry 10.0.0
     */
    AccountKey id() const;

    /*!
     * @brief Represents the @c Account object's raw data.
     *
     * @details Provides access to the @c Account object's raw data.
     *
     * @return Returns a @c QVariantMap containing the @c Account object's raw data.
     *
     * @since BlackBerry 10.0.0
     */
    QVariantMap rawData() const;

    /*!
     * @brief Accessor for read-only capability of service.
     *
     * @details Returns whether the @c service is read-only for the account.
     * If it's not, it implies the @c service is read-write.
     *
     * @note The result of this function is not valid if the @c service is
     * not supported. You can determine whether the service is supported or not
     * by calling the @c Account::isServiceSupported() function with @c service as argument.
     *
     * @param service The service for which we seek the read-only capability
     * from for this @c Account object. Possible values are listed in
     * the @c Service::Type enumeration.
     *
     * @return Returns @c true if service is read-only for
     * the @c Account object, and @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isServiceAccessReadOnly(Service::Type service) const;

    /*!
     * @brief Accessor for support capability of service.
     *
     * @details Returns whether the @c service is supported for the account.
     * A supported service implies the account will continuously synchronize
     * all data for that service.
     *
     * @param service The service for which we seek the supported capability
     * from for this @c Account object. Possible values are listed in
     * the @c Service::Type enumeration.
     *
     * @return @c True if the service is supported
     * for the @c Account object, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isServiceSupported(Service::Type service) const;

    /*!
     * @brief Determines the @c Account object's enterprise account type.
     *
     * @details Returns whether this is an enterprise account.
     *
     * @note The value of @c Property::EnterpriseUnknown for
     * @c Property::EnterpriseType is not currently used and, as such,
     * applications should not need to add any code to check for this case.
     *
     * @return Returns the @c Property::EnterpriseType of the @c Account object.
     *
     * @since BlackBerry 10.0.0
     */
    Property::EnterpriseType isEnterprise() const;

    /*!
     * @brief Determines if the @c Account object is a social account.
     *
     * @return @c True if the @c Account object is a social account,
     * @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isSocial() const;

    /*!
     * @brief Determines if the @c Account object stores its data externally.
     *
     * @return @c True if the @c Account object stores its data externally,
     * @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool isExternalData() const;

    /*!
     * @brief For external @c Provider accounts, returns the invocation target for
     * the setup card of the @c Account.
     *
     * @return Returns a @c QString containing the invocation target for the setup
     * card of the @c Account for external @c Provider accounts. For normal accounts,
     * returns an empty @c QString.
     *
     * @since BlackBerry 10.2.0
     */
    QString externalSetupInvokeTarget() const;

    /*!
     * @brief For external @c Provider accounts, returns the invocation target for the @c external provider.
     *
     * @return Returns a @c QString containing the invocation target for the @c Account's
     * external provider bar package for external @c %Provider accounts. For normal accounts,
     * this method returns an empty @c %QString. This value can be used to issue
     * invokes to the external provider.
     *
     * @since BlackBerry 10.3.0
     */
    QString externalProviderInvokeTarget() const;

    /*!
     * @brief Accessor for the @c Account object's @c settings map.
     *
     * @details Provides access to the @c settings map field contained in the
     * entry @c key. If the field is not found, it checks in the provider's map.
     * If the field is not found in the provider's map, it will return
     * @c QVariant::Invalid.
     *
     * @param key The key used to search the @c settings map in order to obtain
     * the @c settings map entry. The keys that are considered
     * valid depend on the associated provider. Use the
     * @c Provider::settingsKeys() function to obtain a list of keys.
     *
     * @param property The key used to search the @c settings map entry
     * in order to obtain the field to be returned.
     *
     * @return Returns the @c Account object's @c settings field requested.
     * If the @c settings field is not found, it will return @c QVariant::Invalid.
     *
     * @since BlackBerry 10.0.0
     */
    QVariant settingsProperty(const QString &key, Property::Field property = Property::Value) const;

    /*!
     * @brief Accessor for the @c Account object's @c capabilities map.
     *
     * @details Provides access to the @c capabilities map field contained in
     * the entry @c key. If the field is not found, it checks in the provider's map.
     * If the field is not found in the provider's map, it will return
     * @c QVariant::Invalid.
     *
     * @param key The key used to search the @c capabilities map in order to obtain
     * the @c capabilities map entry. The keys that are considered
     * valid depend on the associated provider. Use the
     * @c Provider::capabilitiesKeys() function to obtain a list of keys.
     *
     * @param property The key used to search the @c capabilities map entry
     * in order to obtain the field to be returned.
     *
     * @return Returns the @c Account object's @c capabilities field requested.
     * If the @c capabilities field is not found, it will return @c QVariant::Invalid.
     *
     * @since BlackBerry 10.0.0
     */
    QVariant capabilitiesProperty(const QString &key, Property::Field property = Property::Value) const;

    /*!
     * @brief Set function for the @c Account object's @c displayName property.
     *
     * @details Assigns the value @c displayName to the @c Account object's
     * @c displayName property.
     *
     * @param displayName The value to assign to @c Account object's
     * @c displayName property.
     *
     * @since BlackBerry 10.0.0
     */
    void setDisplayName(const QString &displayName);

    /*!
     * @brief Set function for the @c Account object's @c externalData property.
     *
     * @details Assigns the value @c externalData to the @c Account object's
     * @c externalData property.  This is set to @c true if PIM data (beyond account
     * metadata) should not be stored within the PIM database store for the account.
     * This can occur if the account has no data or it's stored and managed
     * externally.  Calling this method is only allowed when the @c Provider is
     * "external"; for other Providers, @c isValidSet() returns @c false with an
     * appropriate @c validSetError() message.
     *
     * @param externalData The value to assign to the @c Account object's
     * @c externalData property.  The default value is @c False for this property.
     *
     * @since BlackBerry 10.2.0
     */
    void setExternalData(bool externalData);

    /*!
     * @brief Set function for the @c Account object's @c externalSetupInvokeTarget property.
     *
     * @details Assigns the value @c target to the @c Account object's
     * @c externalSetupInvokeTarget property. An @c Account would set this if
     * the account is external and has an Account Setup Card that is
     * invoked upon account creation or editing. Calling this method is only
     * allowed when the @c Provider is "external"; for other Providers, @c isValidSet()
     * returns @c false with an appropriate @c validSetError() message.
     *
     * @param target The value to assign to the @c Account object's
     * @c externalSetupInvokeTarget property. The default value is empty for this property.
     *
     * @since BlackBerry 10.2.0
     */
    void setExternalSetupInvokeTarget(QString const&target);

    /*!
     * @brief Set function for an @c Account object's external @c Provider invoke target property.
     *
     * @details Assigns the value @c target to the @c Account object's
     * @c external invoke target property. An @c Account would set this if
     * the account is external, and it has an external provider in the bar package
     * that is invoked when handling crucial account events (creation, deletion, etc).
     *
     * Calling this method is only allowed when @c %Provider is "external". For
     * other @c %Provider objects, the @c isValidSet() method returns @c false
     * with an appropriate @c validSetError() message.
     *
     * @param target The value to assign to the @c Account object's external
     * @c Provider invoke target property. The default value is empty for this property.
     *
     * @since BlackBerry 10.3.0
     */
    void setExternalProviderInvokeTarget(QString const&target);

    /*!
     * @brief Set function for the @c Account object's @c externalEnterprise value.
     *
     * @details Assigns the value @c enterprise to the @c Account object's
     * @c externalEnterprise value. A caller would set this if
     * the account is external and it's an enterprise-only account. Calling this
     * method is only allowed when the @c Provider is "external"; for other
     * Providers, @c isValidSet() returns @c false with an appropriate @c validSetError()
     * message. Also, an @c AccountPermissionError exception is raised when this
     * method is called by a caller who does not have enterprise permissions.
     *
     * @param enterprise The value to assign to the @c Account object's
     * @c externalEnterprise value. The default value is @c NonEnterprise
     * for external accounts.
     *
     * @since BlackBerry 10.2.0
     */
    void setExternalEnterprise(Property::EnterpriseType enterprise);

    /*!
     * @brief Set function for support capability of service.
     *
     * @details Assigns the value of @c serviceSupported to the account's
     * support capability for @c service. If @c serviceSupported is @c true,
     * it implies @c service is supported.
     * A supported service implies the account will continuously synchronize
     * all data for that service. To turn on synchronization for a specific
     * service, you need to set the support capability of the service to @c true
     * by calling this function and then by calling
     * the @c AccountService::updateAccount() function
     * (or the @c AccountService::createAccount() function for initial creation).
     *
     * @note Attempting to set the support capability of a service for an
     * account whose provider does not support the service will result in a
     * failed set operation. In this case, a call to the @c isValidSet() function
     * will return @c false and a call to @c validSetError() will indicate this
     * particular error.
     *
     * @param service The service for which we are setting the support capability.
     *
     * @param serviceSupported The value to set.
     *
     * @since BlackBerry 10.0.0
     */
    void setServiceSupported(Service::Type service, bool serviceSupported);

    /*!
     * @brief Set function for the @c Account object's @c settings map.
     *
     * @details Assigns the value of the @c fvalue parameter to the @c Account
     * object's @c settings map using a key value pair, if and only if
     * the following conditions are met:
     * (1) The key must exist in the associated provider.
     * (2) The data type of @c fvalue must match the data type of
     * the account field where it is being assigned.
     *
     * If one of the above conditions is not met, the value of
     * the @c settings map will not be changed.
     * In this case, a call to the @c isValidSet() function will return @c false
     * and a call to the @c validSetError() function will indicate this
     * particular error.
     *
     * @param key The key used to search the @c settings map in order to obtain
     * the @c settings map entry to be changed. The keys that are considered
     * valid depend on the associated provider. Use the
     * @c Provider::settingsKeys() function to obtain a list of keys.
     *
     * @param fvalue The value to set into the @c settings map entry.
     *
     * @since BlackBerry 10.0.0
     */
    void setSettingsValue(const QString &key, const QVariant &fvalue);

    /*!
     * @brief Set function for the @c Account object's @c capabilities map.
     *
     * @details Assigns the value of the @c fvalue parameter to the @c Account
     * object's @c capabilities map using a key value pair, if and only if
     * the following conditions are met:
     * (1) The key must exist in the associated provider.
     * (2) The data type of @c fvalue must match the data type of
     * the account field where it is being assigned.
     *
     * If one of the above conditions is not met, the value of
     * the @c capabilities map will not be changed.
     * In this case, a call to the @c isValidSet() function will return @c false
     * and a call to the @c validSetError() function will indicate this
     * particular error.
     *
     * @param key The key used to search the @c capabilities map in order to
     * obtain the @c capabilities map entry to be changed. The key types that
     * are considered valid depend on the associated provider. Use the
     * @c Provider::capabilitiesKeys() function to obtain a list of keys.
     *
     * @param fvalue The value to set into the @c capabilities map entry.
     *
     * @since BlackBerry 10.0.0
     */
    void setCapabilitiesValue(const QString &key, const QVariant &fvalue);

    /*!
     * @brief Object correctness.
     *
     * @details Determines whether or not the @c Account object returned from
     * @c AccountService function calls has acceptable attribute values.
     *
     * @return @c True if the @c Account object is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

    /*!
     * @brief Object correctness with regards to account creation.
     *
     * @details Determines whether or not creating an account with the
     * current Account object is possible. In other words, if all required
     * fields are present and valid.
     *
     * @note This function is called by the function @c AccountService::createAccount.
     *
     * @return A @c Result object with its @c success property set to
     * @c true, when enough information is available in the @c Account object to
     * successfully create an account. When enough information to successfully
     * create an account is not available in the @c Account object or the
     * information available is not properly set, this function returns a
     * @c Result object with its @c success property set to @c false, and its
     * @c message property set to the issues that need to be resolved in the
     * @c Account object so that account creation is possible with this
     * @c Account object.
     *
     * @since BlackBerry 10.0.0
     */
    Result isReadyForCreation() const;

    /*!
     * @brief Setter correctness.
     *
     * @details Determines whether or not the previous @c Account object set
     * operation succeeded or failed.
     *
     * @note If the previous set operation failed, the @c Account object will
     * not incorporate the result for that previous set operation, leaving the
     * @c Account object in the same state as before the previous set operation
     * was called.
     *
     * @return @c True if the previous set operation succeeded, @c false
     * otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValidSet() const;

    /*!
     * @brief Accessor for the setter correctness error.
     *
     * @details Provides access to the error message corresponding to the
     * previous setter operation. Error messages are only generated from failed
     * set operations. Calling this function when the set operation succeeds
     * will result in an empty string being returned.
     *
     * @return Returns the error message corresponding to the previous setter
     * operation if that operation failed, and an empty string otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    QString validSetError() const;

protected:
    /*!
     * @brief Set function for @c Account object's associated @c Provider object.
     *
     * @details Assigns the value of @c provider to the @c Account object's
     * associated @c Provider object. By doing this, the @c Account object
     * inherits all its properties from the associated @c Provider object.
     *
     * @param provider The value to set.
     *
     * @since BlackBerry 10.0.0
     */
    void setProvider(const Provider &provider);

    /*!
     * @brief Set function for @c Account object's @c id property.
     *
     * @details Assigns the value @c id to the @c Account object's @c id property.
     *
     * @param id The value to assign to @c Account object's @c id property.
     *
     * @since BlackBerry 10.0.0
     */
    void setId(AccountKey id);

    /*!
     * @brief Set function for read-only capability of service.
     *
     * @details Assigns the value of @c serviceAccessReadOnly to the account's
     * read-only capability for @c service. If @c serviceAccessReadOnly is @c true, it
     * implies @c service is read-only.
     *
     * @param service The service for which we are setting the read-only capability.
     * Possible values are listed in the @c Service::Type enumeration.
     *
     * @param serviceAccessReadOnly The value to set.
     *
     * @since BlackBerry 10.0.0
     */
    void setServiceAccessReadOnly(Service::Type service, bool serviceAccessReadOnly);

    /*!
     * @brief Set function for @c Account object's @c enterprise property.
     *
     * @details Assigns the value of @c enterprise to the @c Account object's
     * @c enterprise property.
     *
     * @param enterprise The value to set.
     *
     * @since BlackBerry 10.0.0
     */
    void setEnterprise(Property::EnterpriseType enterprise);

    /*!
     * @brief Set function for @c Account object's @c social property.
     *
     * @details Assigns the value of @c social to the @c Account object's
     * @c social property.
     *
     * @param social The value to set.
     *
     * @since BlackBerry 10.0.0
     */
    void setSocial(bool social);

    /*!
     * @brief Set function for @c Account object's raw data.
     *
     * @details Assigns the value of @c rawData to the @c Account
     * object's raw data.
     *
     * @param rawData The value to set.
     *
     * @since BlackBerry 10.0.0
     */
    void setRawData(const QVariantMap &rawData);

    /*!
     * @brief Set function for @c Account object's state of correctness.
     *
     * @details Assigns the value of @c valid to the object's state of correctness.
     *
     * @param valid The value to set.
     *
     * @since BlackBerry 10.0.0
     */
    void setValid(bool valid);

private:
    QSharedDataPointer<AccountPrivate> d_ptr;
    friend class AccountPrivate;
};

BB_PIM_EXPORT QDebug operator<<(QDebug dbg, const Account &account);

} // namespace account
} // namespace pim
} // namespace bb
Q_DECLARE_METATYPE(bb::pim::account::AccountKey)
Q_DECLARE_METATYPE( QList<bb::pim::account::AccountKey> )
#endif // BB_PIM_ACCOUNT_ACCOUNT_HPP
