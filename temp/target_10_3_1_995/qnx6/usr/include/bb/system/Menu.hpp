/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_MENU_HPP
#define BB_SYSTEM_MENU_HPP

#include <bb/system/Global>

#include <QScopedPointer>
#include <QList>
#include <QString>
#include <QUrl>

namespace bb
{
namespace system
{

class MenuItem;
class MenuPrivate;

/*!
 * @headerfile Menu.hpp <bb/system/Menu>
 *
 * @brief A menu of invokable items.
 *
 * @xmlonly
 * <apigrouping group="User Interface/System UI"/>
 * <library name="bbsystem"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */

class BB_SYSTEM_EXPORT Menu
{
public:
    /*!
     * @brief Creates a new @c Menu object.
     *
     * @since BlackBerry 10.0.0
     */
    Menu();

    /*!
     * @brief Creates a copy of an existing @c Menu object.
     *
     * @param other The source @c Menu object to copy.
     *
     * @since BlackBerry 10.0.0
     */
    Menu(const Menu &other);

    /*!
     * @brief Destroys this @c Menu object.
     *
     * @since BlackBerry 10.0.0
     */
    ~Menu();

    /*!
     * @brief Copies the data from an existing @c Menu object to this object.
     *
     * @param other The source @c Menu object to copy.
     *
     * @return The @c Menu instance.
     *
     * @since BlackBerry 10.0.0
     */
    Menu& operator=(const Menu &other);

    /*!
     * @brief Returns the localized title of the menu.
     *
     * @details This can be used at the top of
     * the menu to describe the items in the menu.
     *
     * @return The localized title of the menu, or an empty string if the menu
     *         instance is not valid (see @c isValid()).
     *
     * @since BlackBerry 10.0.0
     */
    QString title() const;

    /*!
     * @brief Returns the localized subtitle of the menu.
     *
     * @details This is a secondary title
     * that can be presented as subscript to the main title.
     *
     * @return The localized subtitle of the menu, or an empty string if the menu
     *         instance is not valid (see @c isValid()).
     *
     * @since BlackBerry 10.0.0
     */
    QString subtitle() const;

    /*!
     * @brief Returns a path to a localized icon file that can be displayed with the menu title.
     *
     * @return A path to a localized icon file that can be displayed with the menu title,
     *         or a default (invalid) @c QUrl if the menu instance is not valid (see @c isValid()).
     *
     * @since BlackBerry 10.0.0
     */
    QUrl titleIcon() const;

    /*!
     * @brief Returns a path to a localized icon file that can be displayed with the menu subtitle.
     *
     * @return A path to a localized icon file that can be displayed with the menu subtitle,
     *         or a default (invalid) @c QUrl if the menu instance is not valid (see @c isValid()).
     *
     * @since BlackBerry 10.0.0
     */
    QUrl subtitleIcon() const;

    /*!
     * @brief Returns the list of menu items.
     *
     * @return The list of menu items. If the menu instance is not valid (see @c isValid()),
     *         an empty list is returned.
     *
     * @since BlackBerry 10.0.0
     */
    QList<MenuItem> items() const;

    /*!
     * @brief Indicates if this menu is valid.
     *
     * @details This menu is valid if all of the following conditions are met:
     * - A request to populate a menu was made using the @c bb::system::MenuManager::populateMenu() method.
     * - The request completed, indicated by the arrival of the @c bb::system::MenuManager::finished() signal.
     * - The request was successful, indicated by @c bb::system::MenuManager::error() returning a value of
     *   @c bb::system::MenuManagerError::None.
     *
     * @return @c true if this menu is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

private:
//!@cond PRIVATE
    QScopedPointer<MenuPrivate> const d_ptr;
    Q_DECLARE_PRIVATE(Menu)
//!@endcond
};

} // namespace system
} // namespace bb

#endif // BB_SYSTEM_MENU_HPP
