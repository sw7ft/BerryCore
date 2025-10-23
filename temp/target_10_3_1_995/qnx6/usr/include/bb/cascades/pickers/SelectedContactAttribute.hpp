/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */


#ifndef BB_CASCADES_PICKERS_SELECTEDCONTACTATTRIBUTE_HPP_
#define BB_CASCADES_PICKERS_SELECTEDCONTACTATTRIBUTE_HPP_

#include <bb/cascades/pickers/Global>
#include <bb/pim/contacts/ContactConsts>

#include <QtDeclarative>
#include <QSharedData>

namespace bb
{
namespace cascades
{
namespace pickers
{

class SelectedContactAttributePrivate;

/*!
 * @brief Represents the selection of an attribute of a contact from the @c ContactPicker.
 * This class is used to return the details of the selected attribute when the picker is in attribute selection mode.
 *
 * @xmlonly
 * <apigrouping group="App Integration/Contacts"/>
 * <library name="bbcascadespickers"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_CASCADES_PICKERS_EXPORT SelectedContactAttribute{

public:
    /*!
     * @brief Constructs a new SelectedContactAttribute
     *
     * @since BlackBerry 10.0.0
     */
    SelectedContactAttribute();

    /*!
     * @brief Copy Constructor
     *
     * @since BlackBerry 10.0.0
     */
    SelectedContactAttribute(const SelectedContactAttribute &copy);

    /*!
     * @brief Equals operator
     *
     * @since BlackBerry 10.0.0
     */
    bool operator==(const SelectedContactAttribute &operand) const;

    /*!
     * @brief Assignment operator
     *
     * @since BlackBerry 10.0.0
     */
    SelectedContactAttribute& operator=(const SelectedContactAttribute &operand);

    /*!
     * @brief Not equals operator
     *
     * @since BlackBerry 10.0.0
     */
    bool operator!=(const SelectedContactAttribute &operand) const;

    /*!
     * @brief The destructor for the SelectedContactAttribute
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~SelectedContactAttribute();

    /*!
     * @brief Sets the value of the selected attribute's kind
     *
     * @param attributeKind - the kind of the selected attribute.
     *
     * @since BlackBerry 10.0.0
     */
    void setAttributeKind(bb::pim::contacts::AttributeKind::Type attributeKind);

    /*!
     * @brief The kind of selected attribute.
     *
     * @return bb::pim::contacts::AttributeSubKind::Type
     *
     * @since BlackBerry 10.0.0
     */
    bb::pim::contacts::AttributeKind::Type attributeKind() const;

    /*!
     * @brief Sets the value of the selected attribute's subKind
     *
     * @param attributeSubKind - the subKind of the selected attribute.
     *
     *
     * @since BlackBerry 10.0.0
     */
    void setAttributeSubKind(bb::pim::contacts::AttributeSubKind::Type attributeSubKind);

    /*!
     * @brief The subKind of selected attribute.
     *
     * @return bb::pim::contacts::AttributeSubKind::Type
     *
     * @since BlackBerry 10.0.0
     */
    bb::pim::contacts::AttributeSubKind::Type attributeSubKind() const;

    /*!
     * @brief Sets the id of the contact that the selected attribute belongs to.
     *
     * @param contactId - the contact id.
     *
     * @since BlackBerry 10.0.0
     */
    void setContactId(int contactId);

    /*!
     * @brief The id of the contact that the selected attribute belongs to.
     * @return int - the contact id.
     *
     * @since BlackBerry 10.0.0
     */
    int contactId() const;

    /*!
     * @brief Sets the value of the selected attribute.
     *
     * @param value - the value of the attribute.
     *
     * @since BlackBerry 10.0.0
     */
    void setValue(const QString &value);

    /*!
     * @brief The value of the selected attribute.
     * @return QString - the value.
     *
     * @since BlackBerry 10.0.0
     */
    QString value() const;

private:
    //! @cond PRIVATE
    QExplicitlySharedDataPointer<SelectedContactAttributePrivate> d_ptr;
    friend class ContactAttributePrivate;
    //! @endcond PRIVATE
};


} /* namespace pickers */
} /* namespace cascades */
} /* namespace bb */
#endif /* BB_CASCADES_PICKERS_SELECTEDCONTACTATTRIBUTE_HPP_ */
