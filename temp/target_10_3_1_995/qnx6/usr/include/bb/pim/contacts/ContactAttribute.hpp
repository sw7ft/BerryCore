 /*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */
#ifndef BB_PIM_CONTACTS_CONTACTATTRIBUTE_HPP
#define BB_PIM_CONTACTS_CONTACTATTRIBUTE_HPP

#include <bb/pim/contacts/ContactConsts>
#include <bb/pim/Global>
#include <QString>
#include <QExplicitlySharedDataPointer>
#include <QDateTime>
#include <QUrl>


namespace bb {
namespace pim {
namespace contacts {

class ContactAttributePrivate;
class ContactAttributeBuilder;

/*!
 * @brief The @c ContactAttribute class represents a property of a @c Contact.
 * 
 * @details A @c %ContactAttribute is a single piece of information about a @c %Contact, such as a phone number or email address.
 * A @c %ContactAttribute has a kind, which specifies high-level metadata about the attribute. Kinds of attributes are
 * represented by the @c AttributeKind::Type enumeration and include email, phone number, name, and so on. A @c %ContactAttribute
 * also has a sub-kind, which specifies additional, more granular metadata about the attribute. Sub-kinds are represented by
 * the @c AttributeSubKind::Type enumeration and include values such as Work (for emails), Home (for phone numbers), and so on.
 * 
 * There is no limit to the number of attributes a @c %Contact can have. You specify the values for a @c %ContactAttribute by
 * using a @c ContactAttributeBuilder.
 * 
 * @see Contact, ContactAttributeBuilder
 *
 * @xmlonly
 * <apigrouping group="App Integration/Contacts"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT ContactAttribute
{
public:
    /*!
     * @brief Constructs an empty @c ContactAttribute.
     * 
     * @details Creating a @c %ContactAttribute using this function will result in an attribute that has no data in it. You should
     * populate the data for the attribute by using a @c ContactAttributeBuilder.
     *
     * @since BlackBerry 10.0.0
     */
    ContactAttribute();

    /*!
     * @brief Copy constructor.
     * 
     * @details This function constructs a @c ContactAttribute containing exactly the same values as the provided
     * @c %ContactAttribute.
     * 
     * @param copy The @c %ContactAttribute to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    ContactAttribute(const ContactAttribute &copy);

    /*!
     * @brief Destroys this @c ContactAttribute.
     *
     * @since BlackBerry 10.0.0
     */
    ~ContactAttribute();

    /*!
     * @brief Assignment operator.
     * 
     * @details This operator copies all values from the provided @c ContactAttribute into this @c %ContactAttribute.
     * 
     * @param operand The @c %ContactAttribute from which to copy all values.
     *
     * @return A @c %ContactAttribute with all copied data
     *
     * @since BlackBerry 10.0.0
     */
    ContactAttribute& operator=(const ContactAttribute &operand);

    /*!
     * @brief Equality operator.
     * 
     * @details This operator determines if this @c ContactAttribute has the same values as another @c %ContactAttribute.
     * 
     * @param operand The @c %ContactAttribute from which to compare.
     * 
     * @return @c true if the values are considered equal, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool operator==(const ContactAttribute& operand) const;

    /*!
     * @brief Inequality operator.
     * 
     * @details This operator determines if this @c ContactAttribute has any different values from another
     * @c %ContactAttribute.
     * 
     * @param operand The @c %ContactAttribute from which to compare.
     * 
     * @return @c true if any of the values are not considered equal, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool operator!=(const ContactAttribute& operand) const;

    /*!
     * @brief Retrieves the ID of this @c ContactAttribute.
     * 
     * @details The ID uniquely identifies a @c %ContactAttribute in a particular source account. The ID is assigned
     * automatically by the database when a @c %ContactAttribute is persisted using the @c ContactService.  You can't
     * set the ID of a @c %ContactAttribute manually.
     * 
     * @return The ID of this @c %ContactAttribute.
     *
     * @since BlackBerry 10.0.0
     */
    int id() const;

    /*!
     * @brief Retrieves the kind of this @c ContactAttribute.
     * 
     * @details The kind specifies metadata about the type of an attribute. The kind is represented by the
     * @c AttributeKind::Type enumeration and can be values such as Name, Email, Phone, and so on.
     * 
     * @return The kind of this @c %ContactAttribute.
     * 
     * @see subKind()
     *
     * @since BlackBerry 10.0.0
     */
    AttributeKind::Type kind() const;

    /*!
     * @brief Retrieves the sub-kind of this @c ContactAttribute.
     * 
     * @details Similar to the kind of an attribute, the sub-kind refers to a sub-type of an attribute. The sub-kind
     * is represented by the @c AttributeSubKind::Type enumeration. For example, if the kind of attribute is a phone
     * number, then possible sub-kinds might be Work, Home, and so on. By using combinations of kinds and sub-kinds,
     * you can specify a wide range of attributes for contacts.
     * 
     * @return The sub-kind of this @c %ContactAttribute.
     * 
     * @see kind()
     *
     * @since BlackBerry 10.0.0
     */
    AttributeSubKind::Type subKind() const;

    /*!
     * @brief Retrieves the string value of this @c ContactAttribute.
     * 
     * @return The string value of this @c %ContactAttribute.
     *
     * @since BlackBerry 10.0.0
     */
    QString value() const;

    /*!
     * @brief Retrieves the value of this @c ContactAttribute as a date/time value.
     * 
     * @details If this @c %ContactAttribute can't be represented as a date/time value, then an invalid @c QDateTime
     * is returned.
     * 
     * @return The value of this @c %ContactAttribute as a date/time value, or an invalid @c %QDateTime if this
     * @c %ContactAttribute can't be represented as a date/time value.
     *
     * @since BlackBerry 10.0.0
     */
    QDateTime valueAsDateTime() const;

    /*!
     * @brief Retrieves the label of this @c ContactAttribute.
     * 
     * @details You can use this value as a custom label for the @c %ContactAttribute, if needed.
     * 
     * @return The label of this @c %ContactAttribute.
     *
     * @since BlackBerry 10.0.0
     */
    QString label() const;

    /*!
     * @brief Indicates whether this @c ContactAttribute is a primary attribute.
     * 
     * @details An attribute can be a primary attribute only if its kind is either Name or OrganizationAffiliation.
     * When a contact has more than one source provider, the contact might have multiple first names, last names, and
     * company names. The system selects one first name as the primary attribute to make UI display choices easier.
     * 
     * @return @c true if this @c %ContactAttribute is a primary attribute, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isPrimaryAttribute() const;

    /*!
     * @brief Retrieves the group key of this @c ContactAttribute.
     * 
     * @details The group key is designed to group different types of attributes together. For example, consider a
     * set of attributes that describe an employee. This set might contain different attributes for the company name,
     * the employee's start date, and the employee's salary. If these attributes all share the same group key, then
     * they can be seen as belonging together to make up a meaningful set of data.
     * 
     * @return The group key of this @c %ContactAttribute.
     *
     * @since BlackBerry 10.0.0
     */
    QString groupKey() const;

    /*!
     * @brief Retrieves the URL that's associated with this @c ContactAttribute.
     * 
     * @details You can think of this property as a hyperlink that points to related information about the attribute.
     * 
     * @return The URL that's associated with this @c %ContactAttribute.
     *
     * @since BlackBerry 10.0.0
     */
    QUrl launchUrl() const;

    /*!
     * @brief Retrieves a list of account IDs for this @c ContactAttribute.
     * 
     * @details This function retrieves a list of all accounts that use this @c %ContactAttribute.
     * 
     * @return A list of account IDs for this @c %ContactAttribute.
     *
     * @since BlackBerry 10.0.0
     */
    QList<AccountId> sources() const;

    /*!
     * @brief Attribute is a contact enhancement.
     *
     * @details This attribute is an enhancement discovered through cloud services.
     *
     * @return @c true if this @c %ContactAttribute is an enhancement, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isEnhancement() const;

    /*!
     * @brief Retrieves the localized display label of this @c ContactAttribute.
     * 
     * @details This value might not exist for all combinations of kinds and sub-kinds. However, many well-known
     * combinations should be available. For example, common combinations for phone numbers include the following:
     * - @c AttributeKind::Phone / @c AttributeSubKind::Work
     * - @c AttributeKind::Phone / @c AttributeSubKind::PhoneMobile
     * - @c AttributeKind::Phone / @c AttributeSubKind::Home
     * - @c AttributeKind::Phone / @c AttributeSubKind::Other
     * 
     * If you've set a custom label for the attribute using @c ContactAttributeBuilder::setLabel(), then this
     * function returns that label. If there isn't a label for the kind/sub-kind combination, then this function
     * returns an empty @c QString.
     * 
     * @return The localized display label of this @c %ContactAttribute, or an empty @c %QString if there isn't
     * a label for the kind/sub-kind combination.
     * 
     * @see determineAttributeDisplayLabel()
     *
     * @since BlackBerry 10.0.0
     */
    QString attributeDisplayLabel() const;

    /*!
     * @brief Edits the contents of this @c ContactAttribute.
     *
     * @details This function returns a @c ContactAttributeBuilder that you can use to change the values of this
     * @c %ContactAttribute.
     * 
     * @return A @c %ContactAttributeBuilder that you can use to change the values of this @c %ContactAttribute.
     *
     * @since BlackBerry 10.0.0
     */
    ContactAttributeBuilder edit();

    /*!
     * @brief Indicates whether this @c ContactAttribute is valid.
     * 
     * @details For a @c %ContactAttribute to be considered valid, it must contain at least a valid kind, valid sub-kind,
     * and non-empty value.
     * 
     * @return @c true if this @c %ContactAttribute is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

    /*!
     * @brief Retrieves the localized display label of this @c ContactAttribute, based on the provided kind, sub-kind, and
     * label, to use to display the @c %ContactAttribute.
     * 
     * @details This function is similar to @c attributeDisplayLabel(), but tries to find a displayable label based on the
     * provided kind, sub-kind, and label, instead of those of this @c %ContactAttribute. This function tries to find a
     * displayable label for the @c %ContactAttribute for UI display purposes. If none is returned, then it's up to the
     * caller to find a proper display label to use.
     *
     * @param kind The attribute kind.
     * @param subkind The attribute sub-kind.
     * @param label The default label value. This value is returned if the @c label parameter is not empty.
     * 
     * @return A localized display label if one is found, or an empty @c QString if one is not found.
     *
     * @since BlackBerry 10.0.0
     */
    static QString determineAttributeDisplayLabel(AttributeKind::Type kind, AttributeSubKind::Type subkind, QString label);

private:
    QExplicitlySharedDataPointer<ContactAttributePrivate> d_ptr;
    friend class ContactAttributePrivate;
};
typedef QList<ContactAttribute> ContactAttributeList;



} // namespace contacts
} // namespace pim
} // namespace bb


#endif // BB_PIM_CONTACTS_CONTACTATTRIBUTE_HPP
