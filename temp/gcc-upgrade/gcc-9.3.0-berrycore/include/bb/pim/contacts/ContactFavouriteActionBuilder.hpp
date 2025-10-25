/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_CONTACTS_CONTACTFAVOURITEACTIONBUILER_HPP
#define BB_PIM_CONTACTS_CONTACTFAVOURITEACTIONBUILER_HPP

#include <bb/pim/Global>
#include <QString>
#include <QSharedDataPointer>

namespace bb {
namespace pim {
namespace contacts {

class ContactFavouriteActionPrivate;
/* @cond PRIVATE */
/*!
 * @brief The @c ContactFavouriteActionBuilder class lets you create, and specify properties for, a new
 * @c ContactFavouriteAction or edit an existing @c %ContactFavouriteAction.
 * 
 * @details You can use this class to set properties, such as action name and attribute association, for a 
 * @c %ContactFavouriteAction. This class uses the builder pattern to create a @c %ContactFavouriteAction and set its
 * properties. Each of the @c set*() functions returns a self reference to the builder, allowing you to chain function
 * calls together. For example, here's how to create a @c %ContactFavouriteAction with a name and attribute association
 * using the builder pattern:
 *
 * @code
 * ContactFavouriteAction action = ContactFavouriteActionBuilder()
                                   .setActionName("email")
                                   .setAttributeAssociation(123456);
 * @endcode
 *
 * @see ContactFavouriteAction
 *
 * @xmlonly
 * <apigrouping group="App Integration/Contacts"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT ContactFavouriteActionBuilder
{
public:
    /*!
     * @brief Constructs a new @c ContactFavouriteActionBuilder.
     *
     * @since BlackBerry 10.0.0
     */
    ContactFavouriteActionBuilder();

    /*!
     * @brief Copy constructor.
     * 
     * @details This function constructs a @c ContactFavouriteActionBuilder containing exactly the same values as the
     * provided @c %ContactFavouriteActionBuilder.
     * 
     * @param copy The @c %ContactFavouriteAction to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    ContactFavouriteActionBuilder(const ContactFavouriteActionBuilder& copy);

    /*!
     * @brief Destroys this @c ContactFavouriteActionBuilder.
     *
     * @since BlackBerry 10.0.0
     */
    ~ContactFavouriteActionBuilder();

    /*!
     * @brief Assignment operator.
     * 
     * @details This operator copies all values from the provided @c ContactFavouriteActionBuilder into this
     * @c %ContactFavouriteActionBuilder.
     *
     * @param operand The @c %ContactFavouriteActionBuilder from which to copy all values.
     *
     * @return A @c %ContactFavouriteActionBuilder with all copied data
     *
     * @since BlackBerry 10.0.0
     */
    ContactFavouriteActionBuilder& operator=(const ContactFavouriteActionBuilder& operand);

    /*!
     * @brief Sets the name of the action.
     * 
     * @details This value is the name of the action that's associated with the attribute, and can be a @c QString such as
     * "phone", "email", "text", and so on.
     * 
     * @param actionName The action name to set.
     * 
     * @return A @c ContactFavouriteActionBuilder with the provided action name.
     *
     * @since BlackBerry 10.0.0
     */
    ContactFavouriteActionBuilder& setActionName(QString actionName);

    /*!
     * @brief Sets the attribute ID of the action.
     * 
     * @details The attribute ID specifies which attribute this action is associated with.
     * 
     * @param attributeId The attribute ID to set.
     *
     * @return A @c ContactFavouriteActionBuilder with the provided attribute ID.
     *
     * @since BlackBerry 10.0.0
     */
    ContactFavouriteActionBuilder& setAttributeAssociation(int attributeId);

    /*!
     * @brief Cast operator.
     * 
     * @details This operator casts an object to the @c ContactFavouriteAction type.
     *
     * @since BlackBerry 10.0.0
     */
    operator ContactFavouriteAction();

private:
    QExplicitlySharedDataPointer<ContactFavouriteActionPrivate> d_ptr;
    friend class ContactFavouriteActionPrivate;
};

/* @endcond */

} // namespace contacts
} // namespace pim
} // namespace bb

#endif // BB_PIM_CONTACTS_CONTACTFAVOURITEACTIONBUILER_HPP
