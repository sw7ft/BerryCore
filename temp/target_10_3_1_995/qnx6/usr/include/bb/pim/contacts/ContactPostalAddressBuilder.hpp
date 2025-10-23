/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */
#ifndef BB_PIM_CONTACTS_CONTACTPOSTALADDRESSBUILDER_HPP
#define BB_PIM_CONTACTS_CONTACTPOSTALADDRESSBUILDER_HPP

#include <bb/pim/contacts/ContactConsts>
#include <bb/pim/Global>
#include <QSharedDataPointer>
#include <QSharedData>
#include <QString>

namespace bb {
namespace pim {
namespace contacts {

class ContactPostalAddressPrivate;
class ContactPostalAddress;

/*!
 * @brief The @c ContactPostalAddressBuilder class lets you create, and specify properties for, a new @c ContactPostalAddress
 * or edit an existing @c %ContactPostalAddress.
 * 
 * @details You can use this class to set properties, such as city, country, postal code, and so on, for a
 * @c %ContactPostalAddress. This class uses the builder pattern to create a @c %ContactPostalAddress and set its properties.
 * Each of the @c set*() functions returns a self reference to the builder, allowing you to chain function calls together.
 * For example, here's how to create a @c %ContactPostalAddress with a first address line, city, region, and country using the
 * builder pattern:
 *
 * @code
 * ContactPostalAddress address = ContactPostalAddressBuilder()
                                  .setLine1("419 Phillip St.")
                                  .setCity("Waterloo")
                                  .setRegion("Ontario")
                                  .setCountry("Canada");
 * @endcode
 *
 * @see ContactPostalAddress
 *
 * @xmlonly
 * <apigrouping group="App Integration/Contacts"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT ContactPostalAddressBuilder
{
public:
    /*!
     * @brief Constructs a new @c ContactPostalAddressBuilder.
     *
     * @since BlackBerry 10.0.0
     */
    ContactPostalAddressBuilder();

    /*!
     * @brief Destroys this @c ContactPostalAddressBuilder.
     *
     * @since BlackBerry 10.0.0
     */
    ~ContactPostalAddressBuilder();

    /*!
     * @brief Copy constructor.
     * 
     * @details This function constructs a @c ContactPostalAddressBuilder containing exactly the same values as the provided
     * @c %ContactPostalAddressBuilder.
     * 
     * @param copy The @c %ContactPostalAddressBuilder to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    ContactPostalAddressBuilder(const ContactPostalAddressBuilder &copy);

    /*!
     * @brief Edits the provided @c ContactPostalAddress.
     * 
     * @details You can use this function to edit the properties of an existing @c %ContactPostalAddress, as an alternative to
     * calling @c ContactPostalAddress::edit().
     * 
     * @param address The @c %ContactPostalAddress to edit.
     * 
     * @see ContactPostalAddress::edit()
     *
     * @since BlackBerry 10.0.0
     */
    ContactPostalAddressBuilder(ContactPostalAddress &address);

    /*!
     * @brief Assignment operator.
     * 
     * @details This operator copies all values from the provided @c ContactPostalAddressBuilder into this
     * @c %ContactPostalAddressBuilder.
     * 
     * @param operand The @c %ContactPostalAddressBuilder from which to copy all values.
     *
     * @return A @c %ContactPostalAddressBuilder with all copied data
     *
     * @since BlackBerry 10.0.0
     */
    ContactPostalAddressBuilder& operator=(const ContactPostalAddressBuilder &operand);
    
    /*!
     * @brief Sets the label for the postal address.
     * 
     * @details You can use this value as a custom label for the @c %ContactPostalAddress, if needed.
     * 
     * @param label The label to set.
     * 
     * @return A @c ContactPostalAddressBuilder with the provided custom label.
     *
     * @since BlackBerry 10.0.0
     */
    ContactPostalAddressBuilder& setLabel(const QString &label);

    /*!
     * @brief Sets the first address line field of the postal address.
     * 
     * @param line1 The first address line value to set.
     * 
     * @return A @c ContactPostalAddressBuilder with the provided first address line value.
     *
     * @since BlackBerry 10.0.0
     */
    ContactPostalAddressBuilder& setLine1(const QString &line1);

    /*!
     * @brief Sets the second address line field of the postal address.
     * 
     * @param line2 The second address line value to set.
     * 
     * @return A @c ContactPostalAddressBuilder with the provided second address line value.
     *
     * @since BlackBerry 10.0.0
     */
    ContactPostalAddressBuilder& setLine2(const QString &line2);

    /*!
     * @brief Sets the city field of the postal address.
     * 
     * @param city The city value to set.
     * 
     * @return A @c ContactPostalAddressBuilder with the provided city value.
     *
     * @since BlackBerry 10.0.0
     */
    ContactPostalAddressBuilder& setCity(const QString &city);

    /*!
     * @brief Sets the region field of the postal address.
     * 
     * @details The region field might contain different values for different countries. For example, for a US postal
     * address, this field would contain the state. For a Canadian postal address, this field would contain the
     * province.
     * 
     * @param region The region value to set.
     * 
     * @return A @c ContactPostalAddressBuilder with the provided region value.
     *
     * @since BlackBerry 10.0.0
     */
    ContactPostalAddressBuilder& setRegion(const QString &region);

    /*!
     * @brief Sets the country field of the postal address.
     * 
     * @param country The country value to set.
     * 
     * @return A @c ContactPostalAddressBuilder with the provided country value.
     *
     * @since BlackBerry 10.0.0
     */
    ContactPostalAddressBuilder& setCountry(const QString &country);

    /*!
     * @brief Sets the postal code field of the postal address.
     * 
     * @param postalCode The postal code value to set.
     * 
     * @return A @c ContactPostalAddressBuilder with the provided postal code value.
     *
     * @since BlackBerry 10.0.0
     */
    ContactPostalAddressBuilder& setPostalCode(const QString &postalCode);

    /*!
     * @brief Sets the latitude field of the postal address.
     * 
     * @param latitude The latitude value to set.
     * 
     * @return A @c ContactPostalAddressBuilder with the provided latitude value.
     *
     * @since BlackBerry 10.0.0
     */
    ContactPostalAddressBuilder& setLatitude(double latitude);

    /*!
     * @brief Sets the longitude field of the postal address.
     * 
     * @param longitude The longitude value to set.
     * 
     * @return A @c ContactPostalAddressBuilder with the provided longitude value.
     *
     * @since BlackBerry 10.0.0
     */
    ContactPostalAddressBuilder& setLongitude(double longitude);

    /*!
     * @brief Sets the sub-kind field of the postal address.
     * 
     * @details The valid sub-kinds of a @c %ContactPostalAddress are @c AttributeSubKind::Home,
     * @c AttributeSubKind::Work, or @c AttributeSubKind::Other.
     * 
     * @param subkind The sub-kind value to set.
     * 
     * @return A @c ContactPostalAddressBuilder with the provided sub-kind value.
     *
     * @since BlackBerry 10.0.0
     */
    ContactPostalAddressBuilder& setSubKind(AttributeSubKind::Type subkind);

    /*!
     * @brief Cast operator.
     * 
     * @details This operator casts an object to the @c ContactPostalAddress type.
     *
     * @since BlackBerry 10.0.0
     */
    operator ContactPostalAddress();
private:
    QExplicitlySharedDataPointer<ContactPostalAddressPrivate>       d_ptr;
    friend class ContactPostalAddressPrivate;
};


} // namespace contacts
} // namespace pim
} // namespace bb



#endif // BB_PIM_CONTACTS_CONTACTPOSTALADDRESSBUILDER_HPP
