/*!
 *
 * @copyright
 * Copyright Research In Motion Limited, 2012-2012
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_BBM_PROFILEBOXITEM_HPP
#define BB_PLATFORM_BBM_PROFILEBOXITEM_HPP


#include <bb/platform/bbm/Global>
#include <QString>
#include <QSharedDataPointer>


namespace bb
{
namespace platform
{
namespace bbm
{

class ProfileBoxItemPrivate;


/*!
 * @headerfile ProfileBoxItem.hpp <bb/platform/bbm/ProfileBoxItem>
 *
 * @brief Represents an item in your app's profile box inside the user's BBM profile.
 *
 * @details The ProfileBoxItem class provides accessor methods to the main attributes of a profile box item,
 * including cookie, itemId, iconId, and text.
 * <p>The user profile box is an
 * area for your app that appears in the current user's BlackBerry Messenger
 * profile. Each box contains a list of items, each composed of text and an
 * optional icon. A profile box can contain a maximum of 3 items. As new items
 * are added, older items are removed automatically.
 *</p>
 * <p>This box can be viewed by the current user and their contacts. It can be
 * modified by the current user and the app that owns it. The current user can
 * remove items only.
 * </p>
 * <p>The user can control whether an app's profile box appears in their profile
 * by using the global settings application. The application is only allowed to
 * make changes if the user enables this option. This can be checked using
 * @c permissionValue(Permission::ProfileUpdatesAllowed).
 * </p>
 * <p>The user can invoke the app from its profile box in their BBM
 * profile or a contact's BBM profile. The app will be brought to the foreground
 * or launched if it's not already running. Contacts who do not have the
 * app installed will be brought to the app's page in BlackBerry World if that app
 * version is available on BlackBerry World.
 * </p>
 * @since BlackBerry 10.0.0
 *
 * @xmlonly
 * <apigrouping group="App Integration/BBM"/>
 * <library name="bbplatformbbm"/>
 * @endxmlonly
 */
class BB_PLATFORM_BBM_EXPORT ProfileBoxItem
{

public:

    /*!
     * @brief Creates a new profile box item object.
     * @since BlackBerry 10.0.0
     */
    ProfileBoxItem();

    /*!
     * Copy constructor
     *
     * @param profileBoxItem The existing @c ProfileBoxItem object to copy.
     * @since BlackBerry 10.0.0
     */
    ProfileBoxItem(const ProfileBoxItem &profileBoxItem);

    /**
     * Assignment operator
     *
     * @param profileBoxItem The existing @c ProfileBoxItem object to copy.
     *
     * @return The @c ProfileBoxItem instance.
     * @since BlackBerry 10.0.0
     */
    ProfileBoxItem& operator=(const ProfileBoxItem &profileBoxItem);

    /*!
     * @brief Destroys this profile box item object.
     * @since BlackBerry 10.0.0
     */
    ~ProfileBoxItem();


    /*!
     * @brief Retrieves the id of this profile box item. Each @c ProfileBoxItem is identified by a unique,
     * non-negative numeric ID.
     * @return The ID of this profile box item.
     * @since BlackBerry 10.0.0
     */
    QString id() const;

    /*!
     * @brief Retrieves the iconId of the icon associated with the profile box item.  An image in a profile box
     * is identified by a unique, non-negative numeric ID. This icon must have been registered using
     * @c bool requestRegisterIcon(int iconId, bb::platform::bbm::ImageType::Type iconType, const QByteArray &iconData)
     * in @c ProfileBox.
     *
     * @return The ID of the icon associated with this profile box item or -1 if no icon is associated with
     * this @c ProfileBoxItem
     * @since BlackBerry 10.0.0
     */
    int iconId() const;

    /*!
     * @brief Retrieves the cookie associated with this profile box item.
     * A cookie is a string that you can customize for your app. The maximum length is 128 characters.
     * The cookie is a non-displayable element.
     * @return The cookie associated with this profile box item.
     * @since BlackBerry 10.0.0
     */
  QString cookie() const;

    /*!
     * @brief Retrieves the text of this profile box item.
     * @return The text of this profile box item.
     * @since BlackBerry 10.0.0
     */
  QString text() const;



private:
    QSharedDataPointer<ProfileBoxItemPrivate> d_ptr;
    friend class ProfileBoxItemPrivate;
};

} /* namespace bbm */
} /* namespace platform */
} /* namespace bb */
#endif /* BB_PLATFORM_BBM_PROFILEBOXITEM_HPP */
