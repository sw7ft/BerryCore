/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */
#ifndef BB_PIM_CONTACTS_CONTACTGROUPBUILDER_HPP
#define BB_PIM_CONTACTS_CONTACTGROUPBUILDER_HPP

#include <bb/pim/contacts/ContactConsts>
#include <bb/pim/contacts/ContactGroup>
#include <bb/pim/Global>
#include <QSharedDataPointer>
#include <QPair>

namespace bb {
namespace pim {
namespace contacts {

class ContactGroupPrivate;

/*!
 * @brief The @c ContactGroupBuilder class lets you create and specify properties for a new @c ContactGroup or edit an existing
 * @c %ContactGroup.
 *
 * @details You can use this class to set properties, such as attributes, a postal address, or a photo, for a
 * @c %ContactGroup. This class uses the builder pattern to create a @c %ContactGroup and set its properties. Each of
 * the functions returns a self reference to the builder, allowing you to chain function calls together. For example,
 * here's how to create a @c %ContactGroup with two attributes using the builder pattern:
 *
 * @code
 * ContactGroup createARandomContactGroup()
 * {
 *     ContactService service;
 *     ContactGroupBuilder builder;
 *     return service.createContactGroup(builder);
 * }
 * @endcode
 *
 * Any changes that you make to a @c %ContactGroup using this builder are temporary until the changes are persisted by using
 * the @c ContactService.
 *
 * @see ContactGroup, ContactService
 *
 * @xmlonly
 * <apigrouping group="App Integration/Contacts"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.3.0
 */
class BB_PIM_EXPORT ContactGroupBuilder
{
public:
    /*!
     * @brief Constructs a new @c ContactGroupBuilder.
     *
     * @since BlackBerry 10.3.0
     */
    ContactGroupBuilder();

    /*!
     * @brief Edits the provided @c ContactGroup.
     *
     * @details You can use this function to edit the properties of an existing @c %ContactGroup, as an alternative to calling
     * @c ContactGroup::edit().
     *
     * @param contact The @c %ContactGroup to edit.
     *
     * @see ContactGroup::edit()
     *
     * @since BlackBerry 10.3.0
     */
    ContactGroupBuilder(ContactGroup &contact);

    /*!
     * @brief Copy constructor.
     *
     * @details This function constructs a @c ContactGroupBuilder containing exactly the same values as the provided
     * @c %ContactGroupBuilder.
     *
     * @param copy The @c %ContactGroupBuilder to be copied.
     *
     * @since BlackBerry 10.3.0
     */
    ContactGroupBuilder(const ContactGroupBuilder &copy);

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c ContactGroupBuilder into this @c %ContactGroupBuilder.
     *
     * @param cgb The @c %ContactGroupBuilder from which to copy all values.
     *
     * @return A @c %ContactGroupBuilder with all copied data.
     *
     * @since BlackBerry 10.3.0
     */
    ContactGroupBuilder& operator=(const ContactGroupBuilder &cgb);

    /*!
     * @brief Destroys this @c ContactGroupBuilder.
     *
     * @since BlackBerry 10.3.0
     */
    ~ContactGroupBuilder();

    /*!
     * @brief Sets the name for the group.
     *
     * @param name The group name to set.
     *
     * @return A @c ContactGroupBuilder with the modified group name.
     *
     * @since BlackBerry 10.3.0
     */
    ContactGroupBuilder& setName(const QString &name);

    /*!
     * @brief Sets whether the contact group is a favorite contact.
     *
     * @details Favorite contacts are displayed in the favorites grid in the Contacts application.
     *
     * @param isFavorite If @c true the contact group is a favorite contact, if @c false the contact group is not a favorite
     * contact.
     *
     * @return A @c ContactGroupBuilder with the provided indication of whether the contact group is a favorite contact.
     *
     * @since BlackBerry 10.3.0
     */
    ContactGroupBuilder& setFavourite(bool isFavourite);

    /*!
     * @brief Cast operator.
     *
     * @details This operator casts an object to the @c ContactGroup type.
     *
     * @since BlackBerry 10.3.0
     */
    operator ContactGroup();

private:
    QExplicitlySharedDataPointer<ContactGroupPrivate> d_ptr;
    friend class ContactGroupPrivate;
};

} // namespace contacts
} // namespace pim
} // namespace bb


#endif // BB_PIM_CONTACTS_CONTACTGROUPBUILDER_HPP
