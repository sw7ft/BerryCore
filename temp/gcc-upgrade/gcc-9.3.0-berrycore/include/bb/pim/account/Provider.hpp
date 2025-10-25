/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_ACCOUNT_PROVIDER_HPP
#define BB_PIM_ACCOUNT_PROVIDER_HPP

#include <bb/pim/Global>
#include <bb/pim/account/Property>
#include <bb/pim/account/Service>
#include <QDebug>
#include <QList>
#include <QSharedDataPointer>
#include <QString>
#include <QVariant>

namespace bb {
namespace pim {
namespace account {

class ProviderPrivate;

/*!
 * @brief A @c Provider.
 *
 * @details This class represents a @c Provider record.
 * The functions in the @c AccountService class allow you to populate a
 * @c Provider record and retrieve information from it.
 *
 * @xmlonly
 * <apigrouping group="App Integration/Account"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT Provider
{
public:

    /*!
     * @brief Creates a copy of an existing @c Provider object.
     *
     * @param other The @c Provider object to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    Provider(const Provider &other);

    /*!
     * @brief Destructor
     *
     * @since BlackBerry 10.0.0
     */
    ~Provider();

    /*!
     * @brief Copies the data of an existing @c Provider object to this object.
     *
     * @param other The @c Provider object to be copied.
     *
     * @return The @c Provider instance.
     *
     * @since BlackBerry 10.0.0
     */
    Provider& operator=(const Provider &other);

    /*!
     * @brief Represents the @c Provider object's @c name property.
     *
     * @details Provides access to the @c Provider object's @c name property.
     *
     * @return Returns a @c QString containing the @c Provider object's @c name property.
     *
     * @since BlackBerry 10.0.0
     */
    QString name() const;

    /*!
     * @brief Represents the @c Provider object's @c id property.
     *
     * @details Provides access to the @c Provider object's @c id property.
     * Use the @c AccountService::providers() function to obtain the complete
     * list of current providers.
     *
     * @return Returns a @c QString containing the @c Provider object's @c id property.
     *
     * @since BlackBerry 10.0.0
     */
    QString id() const;

    /*!
     * @brief Accessor for read-only capability of service
     *
     * @details Returns whether the @c service is read-only for the provider.
     * If it's not, it implies the @c service is read-write.
     * Note: An @c Account object created using this @c Provider object will
     * inherit the read-only capability for all services from this @c Provider object.
     * Switching the read-only capability of a service for an account is not possible.
     *
     * @param service The service for which we seek the read-only capability
     * from for this @c Provider object. Possible values are listed in
     * the @c Service::Type enumeration.
     *
     * @return Returns true if the @c Provider object's capability to support
     * the @c service is read-only, and false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isServiceAccessReadOnly(Service::Type service) const;

    /*!
     * @brief Accessor for support capability of service
     *
     * @details Returns whether the @c service is supported for the provider.
     * Note: An @c Account object created using this @c Provider object will
     * inherit the support capability for all services from this @c Provider object.
     * Switching the support capability of a service for an account from true to false is possible.
     * See the @c Account::setServiceSupported() function for more details.
     *
     * @param service The service for which we seek the supported capability
     * from for this @c Provider object. Possible values are listed in
     * the @c Service::Type enumeration.
     *
     * @return Returns true if the @c Provider object is capable of supporting
     * the @c service, and false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isServiceSupported(Service::Type service) const;

    /*!
     * @brief Represents the @c Provider object's @c enterprise property.
     *
     * @details Provides access to the @c Provider object's @c enterprise property.
     * Note: An @c Account object created using this @c Provider object will
     * inherit the enterprise property from this @c Provider object, except for
     * a provider with @c enterprise set to @c Property::EnterpriseUnknown.
     * Such a provider may create several types of accounts, some with @c
     * enterprise set to Property::Enterprise and others with @c enterprise
     * set to Property::NonEnterprise.
     *
     * @return Returns the @c Property::EnterpriseType of the @c Provider object.
     *
     * @since BlackBerry 10.0.0
     */
    Property::EnterpriseType isEnterprise() const;

    /*!
     * @brief Represents the @c Provider object's @c social property.
     *
     * @details Provides access to the @c Provider object's @c social property.
     * Note: An @c Account object created using this @c Provider object will
     * inherit the social property from this @c Provider object.
     *
     * @return Returns true if the @c Provider object is a provider that creates
     * social accounts, and false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isSocial() const;

    /*!
     * @brief Accessor for the @c Provider object's settings map keys.
     *
     * @details Provides access to the @c Provider object's @c settings map keys.
     *
     * @return Returns a @c QList containing valid keys that can be used to search the
     * @c Provider object's @c settings map as well as any @c settings map
     * from an @c Account object created using this @c Provider object.
     *
     * @since BlackBerry 10.0.0
     */
    QList<QString> settingsKeys() const;

    /*!
     * @brief Accessor for the @c Provider object's @c settings map.
     *
     * @details Provides access to the @c settings map field contained in the
     * entry @c key. If the field is not found, it will return
     * @c QVariant::Invalid.
     *
     * @param key The key used to search the @c settings map in order to obtain
     * the @c settings map entry. Use the @c settingsKeys() function to obtain
     * a list of valid keys.
     *
     * @param property The key used to search the @c settings map entry
     * in order to obtain the field to be returned.
     *
     * @return Returns the @c Provider object's @c settings field requested.
     * If the @c settings field is not found, it will return @c QVariant::Invalid.
     *
     * @since BlackBerry 10.0.0
     */
    QVariant settingsProperty(const QString &key, Property::Field property = Property::Value) const;

    /*!
     * @brief Accessor for the @c Provider object's @c capabilities map keys.
     *
     * @details Provides access to the @c Provider object's @c capabilities map keys.
     *
     * @return Returns a @c QList containing valid keys that can be used to search the
     * @c Provider object's @c capabilities map as well as any @c capabilities
     * map from an @c Account object created using this @c Provider object.
     *
     * @since BlackBerry 10.0.0
     */
    QList<QString> capabilitiesKeys() const;

    /*!
     * @brief Accessor for the @c Provider object's @c capabilities map.
     *
     * @details Provides access to the @c capabilities map field contained in the
     * entry @c key. If the field is not found, it will return
     * @c QVariant::Invalid.
     *
     * @param key The key used to search the @c capabilities map in order to obtain
     * the @c capabilities map entry. Use the @c capabilitiesKeys() function to
     * obtain a list of valid keys.
     *
     * @param property The key used to search the @c capabilities map entry
     * in order to obtain the field to be returned.
     *
     * @return Returns the @c Provider object's @c capabilities field requested.
     * If the @c capabilities field is not found, it will return @c QVariant::Invalid.
     *
     * @since BlackBerry 10.0.0
     */
    QVariant capabilitiesProperty(const QString &key, Property::Field property = Property::Value) const;

    /*!
     * @brief Represents the @c Provider object's raw data.
     *
     * @details Provides access to the @c Provider object's raw data.
     *
     * @return Returns a @c QVariantMap containing the @c Provider object's raw data.
     *
     * @since BlackBerry 10.0.0
     */
    QVariantMap rawData() const;

    /*!
     * @brief Object correctness
     *
     * @details Determines whether or not the @c Provider object returned from
     * @c AccountService function calls has acceptable attribute values.
     *
     * @return Returns true if the @c Provider object is valid, and false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

protected:
    /*!
     * @brief Creates a new @c Provider object.
     *
     * @since BlackBerry 10.0.0
     */
    Provider();

    /*!
     * @brief Set function for @c Provider object's @c name property.
     *
     * @details Assigns the value @c name to the @c Provider object's
     * @c name property.
     *
     * @param name The value to assign to @c Provider object's @c name property.
     *
     * @since BlackBerry 10.0.0
     */
    void setName(const QString &name);

    /*!
     * @brief Set function for @c Provider object's @c id property.
     *
     * @details Assigns the value @c id to the @c Provider object's @c id property.
     *
     * @param id The value to assign to @c Provider object's @c id property.
     *
     * @since BlackBerry 10.0.0
     */
    void setId(const QString &id);

    /*!
     * @brief Set function for support capability of service.
     *
     * @details Assigns the value of @c serviceSupported to the provider's support
     * capability for @c service. If @c serviceSupported is true, it implies @c service
     * is supported.
     *
     * @param service The service for which we are setting the support capability.
     * Possible values are listed in the @c Service::Type enumeration.
     *
     * @param serviceSupported The value to set.
     *
     * @since BlackBerry 10.0.0
     */
    void setServiceSupported(Service::Type service, bool serviceSupported);

    /*!
     * @brief Set function for read-only capability of service.
     *
     * @details Assigns the value of @c serviceAccessReadOnly to the provider's
     * read-only capability for @c service. If @c serviceAccessReadOnly is true, it
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
     * @brief Set function for @c Provider object's @c enterprise property.
     *
     * @details Assigns the value of @c enterprise to the @c Provider object's
     * @c enterprise property.
     *
     * @param enterprise The value to set.
     *
     * @since BlackBerry 10.0.0
     */
    void setEnterprise(Property::EnterpriseType enterprise);

    /*!
     * @brief Set function for @c Provider object's @c social property.
     *
     * @details Assigns the value of @c social to the @c Provider object's
     * @c social property.
     *
     * @param social The value to set.
     *
     * @since BlackBerry 10.0.0
     */
    void setSocial(bool social);

    /*!
     * @brief Set function for @c Provider object's raw data.
     *
     * @details Assigns the value of @c rawData to the @c Provider object's
     * raw data.
     *
     * @param rawData The value to set.
     *
     * @since BlackBerry 10.0.0
     */
    void setRawData(const QVariantMap &rawData);

    /*!
     * @brief Set function for @c Provider object's state of correctness.
     *
     * @details Assigns the value of @c valid to the object's state of correctness.
     *
     * @param valid The value to set.
     *
     * @since BlackBerry 10.0.0
     */
    void setValid(bool valid);

private:
    QSharedDataPointer<ProviderPrivate> d_ptr;
    friend class AccountPrivate;
    friend class ProviderPrivate;
    friend class AccountServicePrivate;
};

BB_PIM_EXPORT QDebug operator<<(QDebug dbg, const Provider &provider);

} // namespace account
} // namespace pim
} // namespace bb

#endif // BB_PIM_ACCOUNT_PROVIDER_HPP
