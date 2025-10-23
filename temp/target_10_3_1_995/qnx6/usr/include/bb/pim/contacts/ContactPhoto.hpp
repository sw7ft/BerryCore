/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */
#ifndef BB_PIM_CONTACTS_CONTACTPHOTO_HPP
#define BB_PIM_CONTACTS_CONTACTPHOTO_HPP

#include <bb/pim/Global>
#include <QExplicitlySharedDataPointer>
#include <QString>

namespace bb {
namespace pim {
namespace contacts {

class ContactPhotoPrivate;
class ContactPhotoBuilder;

/*!
 * @brief The @c ContactPhoto class represents a photo that's associated with a @c Contact.
 *
 * @details This class contains references to photos on the file system that's associated with the contact. Each contact
 * can have multiple photos associated with it, and one photo can be designated the primary photo of the contact.
 *
 * You can retrieve a list of photos for a contact by using @c Contact::photos(). You can retrieve the primary photo for
 * a contact by using @c Contact::primaryPhoto(), and set the primary photo by using @c ContactService::setPrimaryPhoto().
 * You can create a new @c %ContactPhoto and specify values for an existing @c %ContactPhoto by using a
 * @c ContactPhotoBuilder.
 *
 * @see Contact, ContactService, ContactPhotoBuilder
 *
 * @xmlonly
 * <apigrouping group="App Integration/Contacts"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT ContactPhoto
{
public:
    /*!
     * @brief Constructs a new @c ContactPhoto.
     *
     * @since BlackBerry 10.0.0
     */
    ContactPhoto();

    /*!
     * @brief Destroys this @c ContactPhoto.
     *
     * @since BlackBerry 10.0.0
     */
    ~ContactPhoto();

    /*!
     * @brief Copy constructor.
     *
     * @details This function constructs a @c ContactPhoto containing exactly the same values as the provided
     * @c %ContactPhoto.
     *
     * @param copy The @c %ContactPhoto to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    ContactPhoto(const ContactPhoto &copy);

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c ContactPhoto into this @c %ContactPhoto.
     *
     * @param copy The @c %ContactPhoto from which to copy all values.
     *
     * @return A @c %ContactPhoto with all copied data
     *
     * @since BlackBerry 10.0.0
     */
    ContactPhoto& operator=(const ContactPhoto &copy);

    /*!
     * @brief Retrieves the file path of the small photo that's associated with this @c ContactPhoto.
     *
     * @details There is a "file://" prefix added to the response to help make Cascades integration easier.
     *
     * @return The file path of the small photo that's associated with this @c %ContactPhoto.
     *
     * @since BlackBerry 10.0.0
     */
    QString smallPhoto() const;

    /*!
     * @brief Retrieves the file path of the large photo that's associated with this @c ContactPhoto.
     *
     * @details There is a "file://" prefix added to the response to help make Cascades integration easier.
     *
     * @return The file path of the large photo that's associated with this @c %ContactPhoto.
     *
     * @since BlackBerry 10.0.0
     */
    QString largePhoto() const;

    /*!
     * @brief Retrieves the file path of the original photo that's associated with this @c ContactPhoto.
     *
     * @details Both the small photo and large photo are created based on this original photo. There is a
     * "file://" prefix added to the response to help make Cascades integration easier.
     *
     * @return The file path of the original photo that's associated with this @c %ContactPhoto.
     *
     * @since BlackBerry 10.0.0
     */
    QString originalPhoto() const;

    /*!
     * @brief Retrieves the source account ID of this @c ContactPhoto.
     *
     * @details You can use the source account ID to help locate the origin of the photo.
     *
     * @return The source account ID of this @c %ContactPhoto.
     *
     * @since BlackBerry 10.0.0
     */
    int sourceAccountId() const;

    /*!
     * @brief Edits the contents of this @c ContactPhoto.
     *
     * @details This function returns a @c ContactPhotoBuilder that you can use to change the values of this
     * @c %ContactPhoto.
     *
     * @return A @c %ContactPhotoBuilder that you can use to change the values of this @c %ContactPhoto.
     *
     * @since BlackBerry 10.0.0
     */
    ContactPhotoBuilder edit();

    /*!
     * @brief Retrieves the internal ID of this @c ContactPhoto.
     *
     * @return The internal ID of this @c %ContactPhoto.
     *
     * @since BlackBerry 10.0.0
     */
    int id() const;

    /*!
     * @brief Indicates whether this @c ContactPhoto is valid.
     *
     * @details You should use this function to determine if a @c %ContactPhoto is valid before you use it.
     *
     * @return @c true if this @c %ContactPhoto is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

    /*!
     * @brief Retrieves the photo hash that's associated with this @c ContactPhoto.
     *
     * @details You should use this function to retrieve the hash of a @c %ContactPhoto for comparison.
     *
     * @return The hash of the photo that's associated with this @c %ContactPhoto.
     *
     * @since BlackBerry 10.3.0
     */
    QString photoHash() const;
private:
    QExplicitlySharedDataPointer<ContactPhotoPrivate> d_ptr;
    friend class ContactPhotoPrivate;
};
typedef QList<ContactPhoto> ContactPhotoList;

} // namespace contacts
} // namespace pim
} // namespace bb


#endif // BB_PIM_CONTACTS_CONTACTPHOTO_HPP
