/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */


#ifndef BB_CASCADES_PICKERS_CONTACTSELECTIONMODE_HPP
#define BB_CASCADES_PICKERS_CONTACTSELECTIONMODE_HPP

#include <bb/cascades/pickers/Global>
#include <QObject>

namespace bb
{
namespace cascades
{
namespace pickers
{

/*!
 * @headerfile bb/cascades/pickers/ContactPicker
 * @brief Defines the selection mode that a @c ContactPicker should be launched in.
 * The @c %ContactPicker can be used to select a single contact, multiple contacts, or an attribute of a contact.
 * By default, the @c %ContactPicker allows the user to select a single contact.
 *
 * @xmlonly
 * <apigrouping group="App Integration/Contacts"/>
 * <library name="bbcascadespickers"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_CASCADES_PICKERS_EXPORT ContactSelectionMode
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    enum Type {

        /*! @brief This mode allows the user to select a single contact.
         *  The selection will complete as soon as a contact is selected.
         *
         * @since BlackBerry 10.0.0
         */
        Single = 0,
        /*! @brief This mode allows the user to select multiple contacts.
         * The user can select multiple contacts and the selection completes when the user
         * confirms the selection using the confirmation button.
         *
         * @since BlackBerry 10.0.0
         */
        Multiple = 1,
        /*! @brief This mode allows the selection of an attribute of a contact.
         * For example, a user can select a single phone number or an email address.
         *
         * @since BlackBerry 10.0.0
         */
        Attribute = 2,
        /*! @brief This mode allows the selection of multiple attributes of contacts.
         * For example, a user can select a phone number and an email address from different
         * contacts and have them returned as a list.
         *
         * @since BlackBerry 10.3.1
         */
        MultipleAttributes = 3
    };

private:
//! @cond PRIVATE
    ContactSelectionMode();
    virtual ~ContactSelectionMode();
//! @endcond PRIVATE
};

} /* namespace pickers */
} /* namespace cascades */
} /* namespace bb */
#endif /* BB_CASCADES_PICKERS_CONTACTSELECTIONMODE_HPP */
