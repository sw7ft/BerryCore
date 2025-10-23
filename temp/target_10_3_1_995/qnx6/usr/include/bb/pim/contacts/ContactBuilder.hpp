/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */
#ifndef BB_PIM_CONTACTS_CONTACTBUILDER_HPP
#define BB_PIM_CONTACTS_CONTACTBUILDER_HPP

#include <bb/pim/contacts/ContactConsts>
#include <bb/pim/contacts/Contact>
#include <bb/pim/Global>
#include <QSharedDataPointer>
#include <QPair>

namespace bb {
namespace pim {
namespace contacts {

class ContactPrivate;

/*!
 * @brief The @c ContactBuilder class lets you create, and specify properties for, a new @c Contact or edit an existing
 * @c %Contact.
 *
 * @details You can use this class to set properties, such as attributes, a postal address, or a photo, for a
 * @c %Contact. This class uses the builder pattern to create a @c %Contact and set its properties. Each of
 * the functions returns a self reference to the builder, allowing you to chain function calls together. For example,
 * here's how to create a @c %Contact with two attributes using the builder pattern:
 *
 * @code
 * Contact createARandomContact()
 * {
 *     ContactService *service = new ContactService();
 *     ContactBuilder builder;
 *     builder.addAttribute(ContactAttributeBuilder()
 *                               .setKind(AttributeKind::Name)
 *                               .setSubKind(AttributeSubKind::NameGiven)
 *                               .setValue(QString("Random" + QString::number(
 *                                                     std::rand()))));
 *     builder.addAttribute(ContactAttributeBuilder()
 *                               .setKind(AttributeKind::Name)
 *                               .setSubKind(AttributeSubKind::NameNickname)
 *                               .setValue("Bobo The Clown"));
 *     return service->createContact(builder, false);
 * }
 * @endcode
 *
 * Any changes that you make to a @c %Contact using this builder are temporary until the changes are persisted by using
 * the @c ContactService.
 *
 * @see Contact, ContactService
 *
 * @xmlonly
 * <apigrouping group="App Integration/Contacts"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT ContactBuilder
{
public:
    /*!
     * @brief Constructs a new @c ContactBuilder.
     *
     * @since BlackBerry 10.0.0
     */
    ContactBuilder();

    /*!
     * @brief Edits the provided @c Contact.
     *
     * @details You can use this function to edit the properties of an existing @c %Contact, as an alternative to calling
     * @c Contact::edit().
     *
     * @param contact The @c %Contact to edit.
     *
     * @see Contact::edit()
     *
     * @since BlackBerry 10.0.0
     */
    ContactBuilder(Contact &contact);

    /*!
     * @brief Copy constructor.
     *
     * @details This function constructs a @c ContactBuilder containing exactly the same values as the provided
     * @c %ContactBuilder.
     *
     * @param copy The @c %ContactBuilder to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    ContactBuilder(const ContactBuilder &copy);

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c ContactBuilder into this @c %ContactBuilder.
     *
     * @param cb The @c %ContactBuilder from which to copy all values.
     *
     * @return A @c %ContactBuilder with all copied data
     *
     * @since BlackBerry 10.0.0
     */
    ContactBuilder& operator=(const ContactBuilder &cb);

    /*!
     * @brief Destroys this @c ContactBuilder.
     *
     * @since BlackBerry 10.0.0
     */
    ~ContactBuilder();

    /*!
     * @brief Sets whether the contact is a favorite contact.
     *
     * @details Favorite contacts are displayed in the favorites grid in the Contacts application.
     *
     * @param isFavorite If @c true the contact is a favorite contact, if @c false the contact is not a favorite
     * contact.
     *
     * @return A @c ContactBuilder with the provided indication of whether the contact is a favorite contact.
     *
     * @since BlackBerry 10.0.0
     */
    ContactBuilder& setFavorite(bool isFavorite);

    /*!
     * @brief Adds an attribute to the contact.
     *
     * @details Attributes are represented by the @c ContactAttribute class. You can use a @c ContactAttributeBuilder
     * to easily create a @c %ContactAttribute to add to a contact.
     *
     * @param attrib The @c %ContactAttribute to add.
     *
     * @return A @c ContactBuilder with the provided @c %ContactAttribute.
     *
     * @see ContactAttribute, ContactAttributeBuilder
     *
     * @since BlackBerry 10.0.0
     */
    ContactBuilder& addAttribute(const ContactAttribute &attrib);

    /*!
     * @brief Adds a postal address to the contact.
     *
     * @details Postal addresses are represented by the @c ContactPostalAddress class. You can use a
     * @c ContactPostalAddressBuilder to easily create a @c %ContactPostalAddress to add to a contact.
     *
     * @param addr The @c %ContactPostalAddress to add.
     *
     * @return A @c ContactBuilder with the provided @c %ContactPostalAddress.
     *
     * @see ContactPostalAddress, ContactPostalAddressBuilder
     *
     * @since BlackBerry 10.0.0
     */
    ContactBuilder& addPostalAddress(const ContactPostalAddress &addr);

    /*!
     * @brief Adds a photo to the contact.
     *
     * @details Photos are represented by the @c ContactPhoto class. You can use a @c ContactPhotoBuilder to easily
     * create a @c %ContactPhoto to add to a contact.
     *
     * @param photo The @c %ContactPhoto to add.
     * @param isPrimary If @c true this photo is the primary photo for the contact, if @c false this photo is not
     * the primary photo for the contact.
     *
     * @return A @c ContactBuilder with the provided @c %ContactPhoto.
     *
     * @see ContactPhoto, ContactPhotoBuilder
     *
     * @since BlackBerry 10.0.0
     */
    ContactBuilder& addPhoto(const ContactPhoto &photo, bool isPrimary = true);

    /*!
     * @brief Deletes the provided attribute from the contact.
     *
     * @details The provided @c ContactAttribute must be one of the attributes of the contact. Otherwise, this function
     * does nothing.
     *
     * @param attr The @c %ContactAttribute to delete.
     *
     * @return A @c ContactBuilder with the provided @c %ContactAttribute deleted.
     *
     * @since BlackBerry 10.0.0
     */
    ContactBuilder& deleteAttribute(const ContactAttribute &attr);

    /*!
     * @brief Deletes the provided postal address from the contact.
     *
     * @details The provided @c ContactPostalAddress must be part of the contact. Otherwise, this function does nothing.
     *
     * @param addr The @c %ContactPostalAddress to delete.
     *
     * @return A @c ContactBuilder with the provided @c %ContactPostalAddress deleted.
     *
     * @since BlackBerry 10.0.0
     */
    ContactBuilder& deletePostalAddress(const ContactPostalAddress &addr);

    /*!
     * @brief Deletes the photo with the provided file path from the contact.
     *
     * @details This function deletes a @c ContactPhoto from the contact, where the original file path of the
     * @c %ContactPhoto matches the provided parameter. The @c %ContactPhoto with the provided file path must
     * be part of the contact. Otherwise, this function does nothing.
     *
     * @param origPhotoFilepath The file path of the @c %ContactPhoto to delete.
     *
     * @return A @c ContactBuilder with the provided @c %ContactPhoto deleted.
     *
     * @since BlackBerry 10.0.0
     */
    ContactBuilder& deletePhoto(QString origPhotoFilepath);

    /*!
     * @brief Deletes the provided photo from the contact.
     *
     * @details The provided @c ContactPhoto must be part of the contact. Otherwise, this function does nothing.
     *
     * @param photo The @c %ContactPhoto to delete.
     *
     * @return A @c ContactBuilder with the provided @c %ContactPhoto deleted.
     *
     * @since BlackBerry 10.0.0
     */
    ContactBuilder& deletePhoto(const ContactPhoto &photo);

    /*!
     * @brief Sets notes for the contact.
     *
     * @details There should be only one note attribute per contact.
     *
     * @param notes The notes to set.
     *
     * @return A @c ContactBuilder with the provided notes.
     *
     * @since BlackBerry 10.0.0
     */
    ContactBuilder& setNotes(const QString &notes);

    /*!
     * @brief Cast operator.
     *
     * @details This operator casts an object to the @c Contact type.
     *
     * @since BlackBerry 10.0.0
     */
    operator Contact();

    /*!
     * @brief Copies information from the provided contact into this contact.
     *
     * @details This function copies externally visible data from the @c Contact that is passed in. None of the IDs
     * are copied.
     *
     * @param c The @c %Contact to copy information from.
     *
     * @return A @c ContactBuilder with the information from the provided @c %Contact.
     *
     * @since BlackBerry 10.0.0
     */
    ContactBuilder& addFromContact(const Contact &c);

    /*!
     * @brief Updates any new attributes that exist in one contact but not in another contact.
     *
     * @details This function adds any attributes that exist in one of the @c Contact parameters
     * (@c newContact) but don't exist in the other @c %Contact parameter (@c existingContact). You
     * can use this function to provide new updates for a contact.
     *
     * @param existingContact The existing contact.
     * @param newContact The contact with possibly new attributes.
     *
     * @return @c true if any attributes were added, @c false otherwise.
     *
     * @since BlackBerry 10.1.0
     */
    bool updateContact(const Contact& existingContact, const Contact& newContact);

    /*!
     * @brief Sets an existing contact photo as the primary photo for the contact.
     *
     * @details There should be only one primary photo per contact.
     *
     * @param photo The photo to set.
     *
     * @return A @c ContactBuilder with the provided primary photo.
     *
     * @since BlackBerry 10.3.0
     */
    ContactBuilder& setPrimaryPhoto(const ContactPhoto& photo);
private:
    QExplicitlySharedDataPointer<ContactPrivate> d_ptr;
    friend class ContactPrivate;
};

} // namespace contacts
} // namespace pim
} // namespace bb


#endif // BB_PIM_CONTACTS_CONTACTBUILDER_HPP
