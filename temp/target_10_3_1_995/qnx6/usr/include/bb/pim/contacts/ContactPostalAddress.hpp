/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */
#ifndef BB_PIM_CONTACTS_CONTACTPOSTALADDRESS_HPP
#define BB_PIM_CONTACTS_CONTACTPOSTALADDRESS_HPP

#include <bb/pim/Global>
#include <bb/pim/contacts/ContactConsts>
#include <QString>
#include <QExplicitlySharedDataPointer>

namespace bb {
namespace pim {
namespace contacts {

class ContactPostalAddressPrivate;
class ContactPostalAddressBuilder;

/*!
 * @brief The @c ContactPostalAddress class represents a postal address for a contact.
 * 
 * @details This class contains information about a postal address that's associated with a @c Contact, such as city, country,
 * postal code, latitude, and longitude.
 * 
 * You can retrieve a list of postal addresses for a contact by using @c Contact::postalAddresses(). You can add or delete a
 * postal address for a contact by using @c ContactBuilder::addPostalAddress() and @c ContactBuilder::deletePostalAddress(),
 * respectively. You can create a new @c %ContactPostalAddress and specify values for an existing @c %ContactPostalAddress by
 * using a @c ContactPostalAddressBuilder. 
 * 
 * @see Contact, ContactPostalAddressBuilder
 *
 * @xmlonly
 * <apigrouping group="App Integration/Contacts"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT ContactPostalAddress
{
public:
    /*!
     * @brief Constructs a new @c ContactPostalAddress.
     *
     * @since BlackBerry 10.0.0
     */
    ContactPostalAddress();

    /*!
     * @brief Destroys this @c ContactPostalAddress.
     *
     * @since BlackBerry 10.0.0
     */
    ~ContactPostalAddress();

    /*!
     * @brief Copy constructor.
     * 
     * @details This function constructs a @c ContactPostalAddress containing exactly the same values as the provided
     * @c %ContactPostalAddress.
     * 
     * @param copy The @c %ContactPostalAddress to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    ContactPostalAddress(const ContactPostalAddress &copy);

    /*!
     * @brief Assignment operator.
     * 
     * @details This operator copies all values from the provided @c ContactPostalAddress into this @c %ContactPostalAddress.
     * 
     * @param copy The @c %ContactPostalAddress from which to copy all values.
     *
     * @return A @c %ContactPostalAddress with all copied data
     *
     * @since BlackBerry 10.0.0
     */
    ContactPostalAddress& operator=(const ContactPostalAddress &copy);

    /*!
     * @brief Equality operator.
     * 
     * @details This operator determines if this @c ContactPostalAddress has the same values as another
     * @c %ContactPostalAddress.
     * 
     * @param operand The @c %ContactPostalAddress from which to compare.
     * 
     * @return @c true if the values are considered equal, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool operator==(const ContactPostalAddress& operand) const;

    /*!
     * @brief Inequality operator.
     * 
     * @details This operator determines if this @c ContactPostalAddress has any different values from another
     * @c %ContactPostalAddress.
     * 
     * @param operand The @c %ContactPostalAddress from which to compare.
     * 
     * @return @c true if any of the values are not considered equal, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool operator!=(const ContactPostalAddress& operand) const;

    /*!
     * @brief Retrieves the internal ID of this @c ContactPostalAddress.
     * 
     * @details The internal ID is set only if the data is retrieved by the @c ContactService.
     * 
     * @return The internal ID of this @c %ContactPostalAddress.
     *
     * @since BlackBerry 10.0.0
     */
    int id() const;

    /*!
     * @brief Retrieves the label of this @c ContactPostalAddress.
     * 
     * @details You can use this value as a custom label for the @c %ContactPostalAddress, if needed.
     * 
     * @return The label of this @c %ContactPostalAddress.
     *
     * @since BlackBerry 10.0.0
     */
    QString label() const;

    /*!
     * @brief Retrieves the first address line field of this @c ContactPostalAddress.
     * 
     * @return The first address line field of this @c %ContactPostalAddress.
     *
     * @since BlackBerry 10.0.0
     */
    QString line1() const;

    /*!
     * @brief Retrieves the second address line field of this @c ContactPostalAddress.
     * 
     * @return The second address line field of this @c %ContactPostalAddress.
     *
     * @since BlackBerry 10.0.0
     */
    QString line2() const;

    /*!
     * @brief Retrieves the city field of this @c ContactPostalAddress.
     * 
     * @return The city field of this @c %ContactPostalAddress.
     *
     * @since BlackBerry 10.0.0
     */
    QString city() const;

    /*!
     * @brief Retrieves the region field of this @c ContactPostalAddress.
     * 
     * @details The region field might contain different values for different countries. For example, for a US postal
     * address, this field would contain the state. For a Canadian postal address, this field would contain the
     * province.
     * 
     * @return The region field of this @c %ContactPostalAddress.
     *
     * @since BlackBerry 10.0.0
     */
    QString region() const;

    /*!
     * @brief Retrieves the country field of this @c ContactPostalAddress.
     * 
     * @return The country field of this @c %ContactPostalAddress.
     *
     * @since BlackBerry 10.0.0
     */
    QString country() const;

    /*!
     * @brief Retrieves the postal code field of this @c ContactPostalAddress.
     * 
     * @return The postal code field of this @c %ContactPostalAddress.
     *
     * @since BlackBerry 10.0.0
     */
    QString postalCode() const;

    /*!
     * @brief Retrieves the latitude field of this @c ContactPostalAddress.
     * 
     * @details The value of this field should be in the range of +- 90.0 degrees. A positive number indicates a location
     * that's north of the equator, and a negative number indicates a location that's south of the equator.
     * 
     * @return The latitude field of this @c %ContactPostalAddress.
     *
     * @since BlackBerry 10.0.0
     */
    double latitude() const;

    /*!
     * @brief Retrieves the longitude field of this @c ContactPostalAddress.
     * 
     * @details The value of this field should be in the range of +- 180.0 degrees. A positive number indicates a location
     * that's east of the prime meridian, and a negative number indicates a location that's west of the prime
     * meridian.
     * 
     * @return The longitude field of this @c %ContactPostalAddress.
     *
     * @since BlackBerry 10.0.0
     */
    double longitude() const;

    /*!
     * @brief Indicates whether the latitude and longitude values of this @c ContactPostalAddress are valid.
     * 
     * @details If either the latitude or longitude are outside of their allowed ranges, then this function returns
     * @c false.
     * 
     * @return @c true if the latitude and longitude values of this @c %ContactPostalAddress are valid, @c false
     * otherwise.
     * 
     * @see latitude(), longitude()
     *
     * @since BlackBerry 10.0.0
     */
    bool isValidLatitudeLongitude() const;

    /*!
     * @brief Retrieves the sub-kind of this @c ContactPostalAddress.
     * 
     * @details The valid sub-kinds of a @c %ContactPostalAddress are @c AttributeSubKind::Home,
     * @c AttributeSubKind::Work, or @c AttributeSubKind::Other.
     * 
     * @return The sub-kind of this @c %ContactPostalAddress.
     *
     * @since BlackBerry 10.0.0
     */
    AttributeSubKind::Type subKind() const;

    /*!
     * @brief Indicates whether this @c ContactPostalAddress is valid.
     * 
     * @details A @c %ContactPostalAddress is considered invalid if all fields are empty and the latitude and longitude
     * values are invalid. You should use this function to determine if a @c %ContactPostalAddress is valid before you
     * use it.
     * 
     * @return @c true if this @c %ContactPostalAddress is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

    /*!
     * @brief Edits the contents of this @c ContactPostalAddress.
     *
     * @details This function returns a @c ContactPostalAddressBuilder that you can use to change the values of this
     * @c %ContactPostalAddress.
     * 
     * @return A @c %ContactPostalAddressBuilder that you can use to change the values of this @c %ContactPostalAddress.
     *
     * @since BlackBerry 10.0.0
     */
    ContactPostalAddressBuilder edit();

    /*!
     * @brief Represents a default invalid latitude value.
     * 
     * @details When a default instance of @c ContactPostalAddress is created, the latitude is set to @c InvalidLatitude.
     *
     * @since BlackBerry 10.0.0
     */
    static double InvalidLatitude;

    /*!
     * @brief Represents a default invalid longitude value.
     * 
     * @details When a default instance of @c ContactPostalAddress is created, the latitude is set to @c InvalidLongitude.
     *
     * @since BlackBerry 10.0.0
     */
    static double InvalidLongitude;

private:
    QExplicitlySharedDataPointer<ContactPostalAddressPrivate> d_ptr;
    friend class ContactPostalAddressPrivate;
};

typedef QList<ContactPostalAddress> ContactPostalAddressList;

} // namespace contacts
} // namespace pim
} // namespace bb
#endif // BB_PIM_CONTACTS_CONTACTPOSTALADDRESS_HPP
