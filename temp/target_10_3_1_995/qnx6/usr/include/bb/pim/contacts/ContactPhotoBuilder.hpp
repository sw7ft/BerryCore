/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */
#ifndef BB_PIM_CONTACTS_CONTACTPHOTOBUILDER_HPP
#define BB_PIM_CONTACTS_CONTACTPHOTOBUILDER_HPP

#include <bb/pim/Global>
#include <QSharedDataPointer>
#include <QString>

namespace bb {
namespace pim {
namespace contacts {

class ContactPhotoPrivate;

/*!
 * @brief The @c ContactPhotoBuilder class lets you create, and specify properties for, a new @c ContactPhoto or edit
 * an existing @c %ContactPhoto.
 * 
 * @details You can use this class to set properties, such as file path, for a @c %ContactPhoto. This class uses the
 * builder pattern to create a @c %ContactPhoto and set its properties. Each of the @c set*() functions returns a self
 * reference to the builder, allowing you to chain function calls together. For example, here's how to create a
 * @c %ContactPhoto with a file path using the builder pattern:
 *
 * @code
 * ContactPhoto photo = ContactPhotoBuilder()
                        .setOriginalPhoto("/images/photos/myPhoto1.png");
 * @endcode
 *
 * @see ContactPhoto
 *
 * @xmlonly
 * <apigrouping group="App Integration/Contacts"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT ContactPhotoBuilder
{
public:
    /*!
     * @brief Constructs a new @c ContactPhotoBuilder.
     *
     * @since BlackBerry 10.0.0
     */
    ContactPhotoBuilder();

    /*!
     * @brief Edits the provided @c ContactPhoto.
     * 
     * @details You can use this function to edit the properties of an existing @c %ContactPhoto, as an alternative to
     * calling @c ContactPhoto::edit().
     * 
     * @param photo The @c %ContactPhoto to edit.
     * 
     * @see ContactPhoto::edit()
     *
     * @since BlackBerry 10.0.0
     */
    ContactPhotoBuilder(ContactPhoto &photo);

    /*!
     * @brief Destroys this @c ContactPhoto.
     *
     * @since BlackBerry 10.0.0
     */
    ~ContactPhotoBuilder();

    /*!
     * @brief Copy constructor.
     * 
     * @details This function constructs a @c ContactPhotoBuilder containing exactly the same values as the provided
     * @c %ContactPhotoBuilder.
     * 
     * @param copy The @c %ContactPhotoBuilder to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    ContactPhotoBuilder(const ContactPhotoBuilder &copy);

    /*!
     * @brief Assignment operator.
     * 
     * @details This operator copies all values from the provided @c ContactPhotoBuilder into this @c %ContactPhotoBuilder.
     * 
     * @param operand The @c %ContactPhotoBuilder from which to copy all values.
     *
     * @return A @c %ContactPhotoBuilder with all copied data
     *
     * @since BlackBerry 10.0.0
     */
    ContactPhotoBuilder& operator=(const ContactPhotoBuilder &operand);
    
    /*!
     * @brief Sets the file path of the original photo.
     * 
     * @details You should not prefix the file path with "file://". This string is added when you retrieve the photo using
     * @c ContactPhoto::smallPhoto(), @c ContactPhoto::largePhoto(), or @c ContactPhoto::originalPhoto().
     * 
     * @param filepath The file path to set.
     * 
     * @return A @c ContactPhotoBuilder with the provided file path.
     *
     * @since BlackBerry 10.0.0
     */
    ContactPhotoBuilder& setOriginalPhoto(const QString &filepath);

    /*!
     * @brief Sets whether this photo is the primary photo for a contact.
     * 
     * @details The default value is @c false (the @c ContactPhoto that's created is not the primary photo).
     * 
     * @param isPrimary If @c true the photo is the primary photo for a contact, if @c false the photo is not a primary
     * photo for a contact.
     * 
     * @return A @c ContactPhotoBuilder with the provided indication of whether the photo is a primary photo for a contact.
     *
     * @since BlackBerry 10.0.0
     */
    ContactPhotoBuilder& setPrimaryPhoto(bool isPrimary);
    
    /*!
     * @brief Cast operator.
     * 
     * @details This operator casts an object to the @c ContactPhoto type.
     *
     * @since BlackBerry 10.0.0
     */
    operator ContactPhoto();

private:
    QExplicitlySharedDataPointer<ContactPhotoPrivate>       d_ptr;
    friend class ContactPhotoPrivate;
};

} // namespace contacts
} // namespace pim
} // namespace bb

#endif // BB_PIM_CONTACTS_CONTACTPHOTOBUILDER_HPP
