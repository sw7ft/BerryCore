/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_CONTACTS_CONTACTFOLDER_HPP
#define BB_PIM_CONTACTS_CONTACTFOLDER_HPP

#include <bb/pim/Global>
#include <QString>
#include <QSharedDataPointer>
#include <QString>
#include <QMetaType>

namespace bb {
namespace pim {
namespace contacts {

class ContactFolderPrivate;

/*!
 * @brief Represents a key to identify a contact folder within an account.
 *
 * @details You can use this key as a unique identifier for a contact folder.
 *
 * @since BlackBerry 10.3.1
 */
typedef quint64 ContactFolderKey;

/*!
 * @brief The @c ContactFolder class represents a folder to store contacts.
 *
 * @details You can use contact folders to organize contacts into logical
 * groupings. To retrieve the list of contact folders in an account, you can
 * call @c ContactService::folders().
 *
 * @xmlonly
 * <apigrouping group="App Integration/Contacts"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.3.1
 */

class BB_PIM_EXPORT ContactFolder
{

public:
    /*!
     * @brief Constructs a new @c ContactFolder.
     *
     * @since BlackBerry 10.3.1
     */
    ContactFolder();

    /*!
     * @brief Destroys this @c ContactFolder.
     *
     * @since BlackBerry 10.3.1
     */
    ~ContactFolder();

    /*!
     * @brief Copy constructor.
     *
     * @details This function constructs a @c ContactFolder containing exactly the same values as
     * the provided @c %ContactFolder.
     *
     * @param other The @c %ContactFolder to be copied.
     *
     * @since BlackBerry 10.3.1
     */
    ContactFolder(const ContactFolder &other);

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c ContactFolder into this
     * @c %ContactFolder.
     *
     * @param other The @c %ContactFolder from which to copy all values.
     *
     * @return A @c %ContactFolder with all copied data.
     *
     * @since BlackBerry 10.3.1
     */
    ContactFolder& operator=(const ContactFolder &other);


    /*!
     * @brief Retrieves the name of this @c ContactFolder.
     *
     * @return The contact folder's name.
     *
     * @since BlackBerry 10.3.1
     */
    QString name() const;

    /*!
     * @brief Retrieves the ID of this @c ContactFolder.
     *
     * @details You can use this ID to access contacts within this contact folder.
     *
     * @return The contact folder's ID.
     *
     * @since BlackBerry 10.3.1
     */
    ContactFolderKey id() const;

    /*!
     * @brief Retrieves the ID of the parent folder of this @c ContactFolder.
     *
     * @details You can use the parent folder ID to set up a tree view of contacts folders.
     *
     * @return The contact folder's parent folder ID.
     *
     * @since BlackBerry 10.3.1
     */
    ContactFolderKey parentId() const;

    /*!
     * @brief Indicates the current sync configuration of this @c ContactFolder.
     *
     * @return @c true if sync is enabled, @c false if sync is disabled.
     *
     * @since BlackBerry 10.3.1
     */
    bool syncConfig() const;

private:
    QSharedDataPointer<ContactFolderPrivate> d_ptr;
    friend class ContactFolderPrivate;
};

} // namespace contacts
} // namespace pim
} // namespace bb

Q_DECLARE_METATYPE(bb::pim::contacts::ContactFolder)


#endif // BB_PIM_CONTACTS_CONTACTFOLDER_HPP

