/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */
#ifndef BB_PIM_CONTACTS_CONTACTGROUP_HPP
#define BB_PIM_CONTACTS_CONTACTGROUP_HPP

#include <bb/pim/contacts/ContactConsts>
#include <bb/pim/Global>
#include <QString>
#include <QExplicitlySharedDataPointer>
#include <QMetaType>

namespace bb {
namespace pim {
namespace contacts {

class ContactGroupPrivate;

/*!
 * @brief The @c ContactGroup class represents a group contact which can contain a number of individual contacts as members.
 *
 * @details A contact group is a way of associating a number of contacts together to facilitate browsing and group communication.
 * A @c Contact can be added as a member of the group using @c ContactService::addContactToGroup. All available contact groups can be
 *  retrieved using @c ContactService::groups. The @ContactAttribute addresses to use when communicating with a contact through a group
 *  can be specified using @c ContactService::updateGroupMembership.
 *
 * @xmlonly
 * <apigrouping group="App Integration/Contacts"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.3.0
 */
class BB_PIM_EXPORT ContactGroup
{
public:
    /*!
     * @brief Constructs an empty @c ContactGroup.
     *
     * @details Creating a @c %ContactGroup using this function will result in a contact group that has no data in it. You should
     * populate the data for the contact group by using a @c ContactBuilderBuilder.
     *
     * @since BlackBerry 10.3.0
     */
    ContactGroup();

    /*!
     * @brief Copy constructor.
     *
     * @details This function constructs a @c ContactGroup containing exactly the same values as the provided @c %ContactGroup.
     *
     * @param contactGroup The @c %ContactGroup to be copied.
     *
     * @since BlackBerry 10.3.0
     */
    ContactGroup(const ContactGroup &contactGroup);

    /*!
     * @brief Destroys this @c ContactGroup.
     *
     * @since BlackBerry 10.3.0
     */
    ~ContactGroup();

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c ContactGroup into this @c %ContactGroup.
     *
     * @param contact The @c %ContactGroup from which to copy all values.
     *
     * @return A @c %ContactGroup with all copied data
     *
     * @since BlackBerry 10.3.0
     */
    ContactGroup& operator=(const ContactGroup &contactGroup);

    /*!
     * @brief Retrieves the name of this @c ContactGroup.
     *
     * @return name The name of this @c %ContactGroup.
     *
     * @see ContactService
     *
     * @since BlackBerry 10.3.0
     */
    QString name() const;

    /*!
     * @brief Indicates whether this @c ContactGroup is a favorite.
     *
     * @details If this @c %ContactGroup is a favorite, this function returns @c true. Favorite contacts are displayed in the
     * favorites grid in the Contacts application.
     *
     * @return @c true if this @c %ContactGroup is a favorite, @c false otherwise.
     *
     * @since BlackBerry 10.3.0
     */
    bool isFavourite() const;

    /*!
     * @brief Retrieves the ID of this @c ContactGroup.
     *
     * @details You can use this value to interact with this @c %ContactGroup and perform different operations using the
     * @c ContactService, such as retrieving the contact group details. The ID is assigned automatically when the contact group
     * is added to the database using the @c ContactService, and you can't change the ID after it's been assigned.
     *
     * @return The ID of this @c %ContactGroup.
     *
     * @since BlackBerry 10.3.0
     */
    GroupId id() const;
private:
    QExplicitlySharedDataPointer<ContactGroupPrivate> d_ptr;
    friend class ContactGroupPrivate;
};

} // namespace contacts
} // namespace pim
} // namespace bb
Q_DECLARE_METATYPE(bb::pim::contacts::ContactGroup)

#endif // BB_PIM_CONTACTS_CONTACTGROUP_HPP

