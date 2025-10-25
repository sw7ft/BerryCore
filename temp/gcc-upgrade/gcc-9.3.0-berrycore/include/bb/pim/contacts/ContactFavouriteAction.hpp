/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */
#ifndef BB_PIM_CONTACTS_CONTACTFAVOURITEACTION_HPP
#define BB_PIM_CONTACTS_CONTACTFAVOURITEACTION_HPP

#include <bb/pim/Global>
#include <QSharedDataPointer>
#include <QSharedData>
#include <QString>

namespace bb {
namespace pim {
namespace contacts {

class ContactFavouriteActionPrivate;
/* @cond PRIVATE */

/*!
 * @brief The @c ContactFavouriteAction class represents a favorite action for a @c ContactAttribute.
 * 
 * @details You can use a @c %ContactFavouriteAction to specify the most common action for a particular attribute of a
 * contact. For example, you could make sure that an attribute is always associated with the "email" action. You can
 * specify more than one favorite action for a contact attribute.
 * 
 * You can set and retrieve favorite actions for a contact attribute by using functions in the @c ContactService class
 * (@c ContactService::favouriteActions() and @c ContactService::setFavouriteAction()). You can create a new
 * @c %ContactFavouriteAction and specify values for an existing @c %ContactFavouriteAction by using a
 * @c ContactFavouriteActionBuilder.
 * 
 * Here's how to set a favorite action for a contact:
 * 
 * @code
 * qDebug() << "Creating a new contact";
 * Contact returnData = service.createContact(builder, false);
 * qDebug() << "Create done";
 * EXPECT_TRUE(returnData.id() != 0);
 * int contact_id = returnData.id();
 * 
 * // Get the contact
 * qDebug() << "getting contact details for contact " << contact_id;
 * Contact contact = service.contactDetails(contact_id);
 * printContact(contact);
 * EXPECT_TRUE(contact.attributes().size() == 1);
 * 
 * // set favourite action
 * QVariantMap action;
 * ContactFavouriteActionBuilder ab;
 * ab.setActionName("call");
 * ab.setAttributeAssociation(contact.attributes().first().id());
 * service.setFavouriteAction(contact_id, ab);
 * 
 * // get favourite actions
 * QList<ContactFavouriteAction> actions = service.favouriteActions(contact_id);
 * EXPECT_TRUE(actions.count() > 0);
 * EXPECT_TRUE(actions[0].attributeId() == contact.attributes().first().id());
 * EXPECT_TRUE(actions[0].actionName() == QString("call"));
 * @endcode
 * 
 * @see ContactService, ContactFavouriteActionBuilder
 *
 * @xmlonly
 * <apigrouping group="App Integration/Contacts"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT ContactFavouriteAction
{
public:
    /*!
     * @brief Constructs a new @c ContactFavouriteAction.
     *
     * @since BlackBerry 10.0.0
     */
    ContactFavouriteAction();
    
    /*!
     * @brief Copy constructor.
     * 
     * @details This function constructs a @c ContactFavouriteAction containing exactly the same values as the provided
     * @c %ContactFavouriteAction.
     * 
     * @param copy The @c %ContactFavouriteAction to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    ContactFavouriteAction(const ContactFavouriteAction &copy);
    
    /*!
     * @brief Destroys this @c ContactFavouriteAction.
     *
     * @since BlackBerry 10.0.0
     */
    ~ContactFavouriteAction();
    
    /*!
     * @brief Assignment operator.
     * 
     * @details This operator copies all values from the provided @c ContactFavouriteAction into this
     * @c %ContactFavouriteAction.
     * 
     * @param operand The @c %ContactFavouriteAction from which to copy all values.
     *
     * @return A @c %ContactFavouriteAction with all copied data
     *
     * @since BlackBerry 10.0.0
     */
    ContactFavouriteAction& operator=(const ContactFavouriteAction &operand);

    /*!
     * @brief Retrieves the ID of this @c ContactFavouriteAction.
     * 
     * @details The ID uniquely identifies this @c %ContactFavouriteAction, and is assigned when the action is created.
     * 
     * @return The ID of this @c %ContactFavouriteAction.
     *
     * @since BlackBerry 10.0.0
     */
    int id() const;
    
    /*!
     * @brief Retrieves the attribute ID that's associated with this @c ContactFavouriteAction.
     * 
     * @details The attribute ID specifies which attribute this action is associated with.
     * 
     * @return The attribute ID of this @c %ContactFavouriteAction.
     *
     * @since BlackBerry 10.0.0
     */
    int attributeId() const;
    
    /*!
     * @brief Retrieves the name of the action of this @c ContactFavouriteAction.
     * 
     * @details This value is the name of the action that's associated with the attribute, and can be a @c QString such as
     * "phone", "email", "text", and so on.
     * 
     * @return The name of the action of this @c %ContactFavouriteAction.
     *
     * @since BlackBerry 10.0.0
     */
    QString actionName() const;

private:
    QSharedDataPointer<ContactFavouriteActionPrivate> d_ptr;
    friend class ContactFavouriteActionPrivate;
};
/* @endcond */

} // namespace contacts
} // namespace pim
} // namespace bb

#endif // BB_PIM_CONTACTS_CONTACTFAVOURITEACTION_HPP
