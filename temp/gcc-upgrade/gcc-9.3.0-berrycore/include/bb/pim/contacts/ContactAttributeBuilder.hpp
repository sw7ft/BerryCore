/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */
#ifndef BB_PIM_CONTACTS_CONTACTATTRIBUTEBUILDER_HPP
#define BB_PIM_CONTACTS_CONTACTATTRIBUTEBUILDER_HPP

#include <bb/pim/contacts/ContactConsts>
#include <bb/pim/Global>
#include <QSharedDataPointer>
#include <QSharedData>
#include <QUrl>
#include <QDateTime>

namespace bb {
namespace pim {
namespace contacts {

class ContactAttribute;
class ContactAttributePrivate;

/*!
 * @brief The @c ContactAttributeBuilder class lets you create, and specify properties for, a new @c ContactAttribute
 * or edit an existing @c %ContactAttribute.
 * 
 * @details You can use this class to set properties, such as kind, sub-kind, and value, for a @c %ContactAttribute.
 * This class uses the builder pattern to create a @c %ContactAttribute and set its properties. Each of the @c set*()
 * functions returns a self reference to the builder, allowing you to chain function calls together. For example,
 * here's how to create a @c %ContactAttribute with a kind, sub-kind, and value using the builder pattern:
 *
 * @code
 * ContactAttribute attr = ContactAttributeBuilder()
                            .setKind(AttributeKind::Name)
                            .setSubKind(AttributeSubKind::NameGiven)
                            .setValue("Joe");
 * @endcode
 *
 * @see ContactAttribute
 *
 * @xmlonly
 * <apigrouping group="App Integration/Contacts"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT ContactAttributeBuilder
{
public:
    /*!
     * @brief Constructs a new @c ContactAttributeBuilder.
     *
     * @since BlackBerry 10.0.0
     */
    ContactAttributeBuilder();

    /*!
     * @brief Destroys this @c ContactAttributeBuilder.
     *
     * @since BlackBerry 10.0.0
     */
    ~ContactAttributeBuilder();

    /*!
     * @brief Copy constructor.
     * 
     * @details This function constructs a @c ContactAttributeBuilder containing exactly the same values as the
     * provided @c %ContactAttributeBuilder.
     * 
     * @param copy The @c %ContactAttributeBuilder to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    ContactAttributeBuilder(const ContactAttributeBuilder &copy);

    /*!
     * @brief Assignment operator.
     * 
     * @details This operator copies all values from the provided @c ContactAttributeBuilder into this
     * @c %ContactAttributeBuilder.
     * 
     * @param operand The @c %ContactAttributeBuilder from which to copy all values.
     *
     * @since BlackBerry 10.0.0
     */
    ContactAttributeBuilder& operator=(const ContactAttributeBuilder &operand);

    /*!
     * @brief Edits the provided @c ContactAttribute.
     * 
     * @details You can use this function to edit the properties of an existing @c %ContactAttribute, as an
     * alternative to calling @c ContactAttribute::edit().
     * 
     * @param editAttribute The @c %ContactAttribute to edit.
     * 
     * @see ContactAttribute::edit()
     *
     * @since BlackBerry 10.0.0
     */
    ContactAttributeBuilder(ContactAttribute &editAttribute);
    
    /*!
     * @brief Sets the kind value of the attribute.
     * 
     * @details The kind specifies metadata about the type of an attribute. The kind is represented by the
     * @c AttributeKind::Type enumeration and can be values such as Name, Email, Phone, and so on.
     * 
     * @param kind The kind to set.
     * 
     * @return A @c ContactAttributeBuilder with the provided kind value.
     *
     * @since BlackBerry 10.0.0
     */
    ContactAttributeBuilder& setKind(AttributeKind::Type kind);

    /*!
     * @brief Sets the sub-kind value of the attribute.
     * 
     * @details Similar to the kind of an attribute, the sub-kind refers to a sub-type of an attribute. For example,
     * if the kind of attribute is a phone number, then possible sub-kinds might be Work, Home, and so on. By using
     * combinations of kinds and sub-kinds, you can specify a wide range of attributes for contacts.
     * 
     * @param subkind The sub-kind to set.
     * 
     * @return A @c ContactAttributeBuilder with the provided sub-kind value.
     *
     * @since BlackBerry 10.0.0
     */
    ContactAttributeBuilder& setSubKind(AttributeSubKind::Type subkind);

    /*!
     * @brief Sets the value of the attribute.
     * 
     * @param value The value to set.
     *
     * @return A @c ContactAttributeBuilder with the provided value.
     *
     * @since BlackBerry 10.0.0
     */
    ContactAttributeBuilder& setValue(const QString &value);

    /*!
     * @brief Sets the value of the attribute using the provided @c QDateTime object.
     * 
     * @details The provided @c %QDateTime object is converted internally into a string value, so the @c QString value
     * is the definitive value for an attribute.
     * 
     * @param value The value to set, as a @c %QDateTime object.
     * 
     * @return A @c ContactAttributeBuilder with the provided @c %QDateTime value.
     *
     * @since BlackBerry 10.0.0
     */
    ContactAttributeBuilder& setValue(const QDateTime &value);

    /*!
     * @brief Sets the label of the attribute.
     * 
     * @details This label can be any @c QString, and you can use it as a custom label for the attribute, if needed.
     * For example, here's how to set a label for an attribute:
     * 
     * @code
     * attributeBuilder.setLabel("My father's cousin's roommate's cell phone number");
     * @endcode
     * 
     * @param label The label to set.
     * 
     * @return A @c ContactAttributeBuilder with the provided label.
     *
     * @since BlackBerry 10.0.0
     */
    ContactAttributeBuilder& setLabel(const QString &label);

    /*!
     * @brief Sets the group key of the attribute.
     * 
     * @details The group key is designed to group different types of attributes together. For example, consider a
     * set of attributes that describe an employee. This set might contain different attributes for the company name,
     * the employee's start date, and the employee's salary. If these attributes all share the same group key, then
     * they can be seen as belonging together to make up a meaningful set of data.
     * 
     * @param groupkey The group key to set.
     * 
     * @return A @c ContactAttributeBuilder with the provided group key.
     *
     * @since BlackBerry 10.0.0
     */
    ContactAttributeBuilder& setGroupKey(const QString &groupkey);

    /*!
     * @brief Sets the URL that's associated with the attribute.
     *
     * @details You can think of this property as a hyperlink that points to related information about the attribute.
     * 
     * @param launchUrl The URL to set.
     * 
     * @return A @c ContactAttributeBuilder with the provided URL.
     *
     * @since BlackBerry 10.0.0
     */
    ContactAttributeBuilder& setLaunchUrl(const QUrl &launchUrl);
    
    /*!
     * @brief Cast operator.
     * 
     * @details This operator casts an object to the @c ContactAttribute type.
     *
     * @since BlackBerry 10.0.0
     */
    operator ContactAttribute();

    /*!
     * @brief Finds or creates an @c AttributeKind using the provided string value.
     *
     * @details This function lets you create custom attribute kinds to store application-specific data in a
     * contact. Use this function along with @c determineAttributeSubKind() to add custom attributes.
     * 
     * @param kindValue A non-empty string value to find or create an @c AttributeKind::Type for.
     * 
     * @return An attribute kind based on the provided string value, or an invalid kind if the @c kindValue
     * parameter is empty.
     * 
     * @see determineAttributeSubKind()
     *
     * @since BlackBerry 10.0.0
     */
   static AttributeKind::Type determineAttributeKind(const QString &kindValue);


    /*!
     * @brief Finds or creates an @c AttributeSubKind using the provided string value.
     * 
     * @details This function lets you create custom attribute sub-kinds to store application-specific data in
     * a contact. Use this function along with @c determineAttributeKind() to add custom attributes.
     *
     * For example, you might add a custom attribute kind called "Hidden" (using @c %determineAttributeKind())
     * and then create a custom attribute sub-kind called "Secret" (using this function), which is not part of
     * the @c AttributeSubKind::Type enumeration.
     *
     * @param subKindValue A non-empty string value to find or create an @c AttributeSubKind::Type for.
     *
     * @return An attribute sub-kind based on the provided string value, or an invalid sub-kind if the
     * @c subKindValue parameter is empty.
     *
     * @see determineAttributeKind()
     *
     * @since BlackBerry 10.0.0
     */
    static AttributeSubKind::Type determineAttributeSubKind(const QString &subKindValue);

private:
    QExplicitlySharedDataPointer<ContactAttributePrivate> d_ptr;
    friend class ContactAttributePrivate;
};

} // namespace contacts 
} // namespace pim 
} // namespace bb 

#endif // BB_PIM_CONTACTS_CONTACTATTRIBUTEBUILDER_HPP
