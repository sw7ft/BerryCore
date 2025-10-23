/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_MENUITEM_HPP
#define BB_SYSTEM_MENUITEM_HPP

#include <bb/system/Global>
#include <bb/system/MenuItemType>

#include <QScopedPointer>
#include <QString>
#include <QUrl>

namespace bb
{
namespace system
{

class Menu;
class MenuItemInvokeParams;
class MenuItemPrivate;

/*!
 * @headerfile MenuItem.hpp <bb/system/MenuItem>
 *
 * @brief A menu entry that can be invoked directly or may contain additional
 *        sub-menu entries.
 *
 * A menu item contains information (labels and an icon) that can be used to present the
 * menu to the user. It also provides the action to take when the item is selected. Selecting
 * a menu item can either initiate the invocation of a target using specific data, MIME type,
 * and/or URI, or it can result in the presentation of a submenu to give the user more options to
 * choose from.
 *
 * To determine which action to take, check the following:
 * - <code>invoke().isValid()</code> : If this returns @c true, the menu item contains a valid invocation
 *   request that should be run when the menu item is selected.
 * - <code>subMenu().isValid()</code> : If this returns @c true, then the menu item contains a submenu
 *   that should be displayed when the menu item is selected.
 *
 * @xmlonly
 * <apigrouping group="User Interface/System UI"/>
 * <library name="bbsystem"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */

class BB_SYSTEM_EXPORT MenuItem
{
public:
    /*!
     * @brief Creates a new @c MenuItem object.
     *
     * @since BlackBerry 10.0.0
     */
    MenuItem();

    /*!
     * @brief Creates a copy of an existing @c MenuItem object.
     *
     * @param other The source @c MenuItem object to copy.
     *
     * @since BlackBerry 10.0.0
     */
    MenuItem(const MenuItem &other);

    /*!
     * @brief Destroys this @c MenuItem object.
     *
     * @since BlackBerry 10.0.0
     */
    ~MenuItem();

    /*!
     * @brief Copies the data from an existing @c MenuItem object to this object.
     *
     * @param other The source @c MenuItem object to copy.
     *
     * @return The @c MenuItem instance.
     *
     * @since BlackBerry 10.0.0
     */
    MenuItem& operator=(const MenuItem &other);

    /*!
     * @brief Returns a path to a localized icon file that represents the menu item.
     *
     * @return A path to a localized icon file that represents the menu item.
     *
     * @since BlackBerry 10.0.0
     */
    QUrl icon() const;

    /*!
     * @brief Returns an optional path to a localized icon file that represents the menu item.
     *
     * @return A path to a localized icon file that represents the menu item, or an empty
     *         QUrl if not present.
     *
     * @since BlackBerry 10.2.0
     */
    QUrl secondaryIcon() const;

    /*!
     * @brief Returns the localized label describing the menu item.
     *
     * @return The localized label describing the menu item.
     *
     * @since BlackBerry 10.0.0
     */
    QString label() const;

    /*!
     * @brief Returns an optional secondary label describing the menu item.
     *
     * @return The localized secondary label describing the menu item, or an
     *         empty string if not present.
     *
     * @since BlackBerry 10.0.0
     */
    QString secondaryLabel() const;

    /*!
     * @brief Returns an optional tertiary label describing the menu item.
     *
     * @return The localized tertiary label describing the menu item, or an
     *         empty string if not present.
     *
     * @since BlackBerry 10.0.0
     */
    QString tertiaryLabel() const;

//!@cond PRIVATE
    /*!
     * @brief Returns an optional frecency score.
     *
     * @return The frecency score, or 0 if not present.
     *
     * @since BlackBerry 10.2.0
     */
    int frecency() const;

    /*!
     * @brief Returns the type of the menu item.
     *
     * @return The menu item type.
     *
     * @since BlackBerry 10.2.0
     */
    MenuItemType::Type itemType() const;
//!@endcond

    /*!
     * @brief Returns the invocation parameters that will be used to invoke the action
     * associated with this menu item when it is selected.
     *
     * @return The invocation parameters for this menu item.
     *
     * @since BlackBerry 10.0.0
     */
    MenuItemInvokeParams invoke() const;

    /*!
     * @brief Returns the sub-menu that should be presented when this
     * menu item is selected.
     *
     * @return The sub-menu to be presented.
     *
     * @since BlackBerry 10.0.0
     */
    Menu subMenu() const;

private:
//!@cond PRIVATE
    QScopedPointer<MenuItemPrivate> const d_ptr;
    Q_DECLARE_PRIVATE(MenuItem)
//!@endcond
};

} // namespace system
} // namespace bb

#endif // BB_SYSTEM_MENUITEM_HPP
