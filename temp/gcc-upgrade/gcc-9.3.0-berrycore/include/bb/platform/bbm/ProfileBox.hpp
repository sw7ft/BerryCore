/*!
 *
 * @copyright
 * Copyright Research In Motion Limited, 2012-2012
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_BBM_PROFILEBOX_HPP
#define BB_PLATFORM_BBM_PROFILEBOX_HPP

#include <bb/platform/bbm/Global>
#include <bb/platform/bbm/ImageType>

#include <QObject>
#include <QList>
#include <QScopedPointer>

namespace bb
{
  namespace platform
  {
    namespace bbm
    {
      class Context;
      class ProfileBoxItem;
      class ProfileBoxPrivate;

      /*!
       * @headerfile ProfileBox.hpp <bb/platform/bbm/ProfileBox>
       *
       * @brief Represents a class that provides access to your app's profile box
       * in the user's BBM profile.
       *
       * @details The user profile box is an area for your app that appears in the 
       * current user's BlackBerry Messenger profile. Each box contains a list of 
       * items, each composed of text and an optional icon. A profile box can contain
       * a maximum of 3 items. As new items are added, older items are removed automatically.
       *
       * <p>The user can control whether your app's profile box appears in their profile
       * through the global settings for the app. The app is only allowed to
       * make changes if the user enables this option. You can check this setting by
       * calling @c permissionValue(Permission::ProfileUpdatesAllowed).
       * </p>
       *
       * <p>This box can be viewed by the current user and their contacts. It can be
       * modified by the current user and the app that owns it, but the current user can
       * remove items only.
       * </p>
       *
       * <p>The user can invoke the app from its profile box in their BBM
       * profile or a contact's BBM profile. The app will be brought to the foreground,
       * or launched if it's not already running. Contacts who do not have the
       * app installed will be brought to the app's page in BlackBerry World if that version
       * of the app is available on BlackBerry World.
       * </p>
       *
       * The functionality of this class is only available if the app has access to the
       * BBM Social Platform and has received permission, @c Permission::ProfileUpdatesAllowed.
       *
       * @since BlackBerry 10.0.0
       *
       * @xmlonly
       * <apigrouping group="App Integration/BBM"/>
       * <library name="bbplatformbbm"/>
       * @endxmlonly
       */
      class  BB_PLATFORM_BBM_EXPORT ProfileBox: public QObject
      {
        Q_OBJECT
      public:
        /*!
         * @brief Creates a new ProfileBox object with @c context as the basis.
         *
         * @param context The context that provides the basis for the
         * ProfileBox.
         * @param parent The QObject parent of this ProfileBox object.
         * @since BlackBerry 10.0.0
         */
        explicit ProfileBox(Context *context, QObject *parent = 0);

        /*!
         * @brief Destroys this ProfileBox object.
         * @since BlackBerry 10.0.0
         */
        virtual ~ProfileBox();

        /*!
         * @brief Request to add a ProfileBoxItem with text, icon, and
         * optional cookie.
         * The signal @c itemAdded() is emitted as an asynchronous response.
         *
         * @param text The text to be associated with the profile box item. Must
         * not be empty and can have a maximum of 100 characters, with no more
         * than 2 new line characters.
         * @param iconId The ID of the icon associated with this
         * profile box item or < 0 if no icon is associated.
         * @param cookie The cookie associated with this profile box item.
         * @c cookie can have a maximum of 128 characters.
         *
         * @return true if sending the request succeeds, false
         * otherwise. If the app does not have @c
         * Permission::ProfileUpdatesAllowed, returns false.
         * @since BlackBerry 10.0.0
         */
        bool requestAddItem(const QString &text,
                            int iconId,
                            const QString &cookie = QString());

        /*!
         * @brief Requests permission to add a ProfileBoxItem with text and optional
         * cookie.
         * The signal @c itemAdded() is emitted as an asynchronous response.
         *
         * @param text The text associated with the profile box item. @c text must
         * not be empty and can have a maximum of 100 characters, with no more
         * than 2 new line characters.
         * @param cookie The cookie associated with this profile box item.
         * @c cookie can have a maximum of 128 characters.
         *
         * @return true if sending the request succeeds, false
         * otherwise. If the application does not have @c
         * Permission::ProfileUpdatesAllowed, returns false.
         * @since BlackBerry 10.0.0
         */
        bool requestAddItem(const QString &text,
                            const QString &cookie = QString());

        /*!
         * @brief Retrieves the ProfileBoxItem with the specified @c itemId.
         *
         * @param itemId The ID of the ProfileBoxItem to retrieve.
         *
         * @return The ProfileBoxItem associated with the specified @c itemId; an empty
         * ProfileBoxItem otherwise. If the application does not have
         * @c Permission::ProfileUpdatesAllowed, returns an empty ProfileBoxItem.
         * @since BlackBerry 10.0.0
         */
        ProfileBoxItem item(const QString &itemId) const;

        /*!
         * @brief Returns all profile box items.
         *
         * @return A @c QList<ProfileBoxItem> with all the profile box
         * items. If the application does not have @c
         * Permission::ProfileUpdatesAllowed, returns an empty
         * @c QList<ProfileBoxItem>.
         * @since BlackBerry 10.0.0
         */
        QList<ProfileBoxItem> items() const;

        /*!
         * @brief Requests removal of the ProfileBoxItem with the specified itemId.
         *
         * @param itemId The itemId of the ProfileBoxItem to remove.
         * The signal @c itemRemoved() is emitted as an asynchronous response.
         *
         * @return true if sending the request succeeds, false
         * otherwise. If the application does not have
         * @c Permission::ProfileUpdatesAllowed, returns false.
         * @since BlackBerry 10.0.0
         */
        bool requestRemoveItem(const QString &itemId);

        /*!
         * @brief Requests removal of all items in the ProfileBox.
         * The signal @c itemRemoved() is emitted as an asynchronous response for each
         * item removed.
         *
         * @return true if sending the request succeeds, false
         * otherwise. If the application does not have @c
         * Permission::ProfileUpdatesAllowed, returns false.
         * @since BlackBerry 10.0.0
         */
        bool requestRemoveAllItems();


        /*!
         * @brief Returns the total number of items in the profile box.
         *
         * @return The count of items in the profile box. If the
         * application does not have @c Permission::ProfileUpdatesAllowed,
         * returns 0.
         * @since BlackBerry 10.0.0
         */
        int itemCount() const;

        /*!
         * @brief Requests registration of an icon with the specified iconId, iconType
         * and iconData.
         * The signal @c iconRegistered() is emitted as an asynchronous response.
         *
         * @param iconId The unique, non-negative ID of the icon to register.
         * @param iconType The MIME type of the icon. If an invalid MIME
         * type is specified, the behavior of this method is undefined.
         * @param iconData The icon data. @c iconData must not be empty.
         *
         * @return true if sending the request succeeds, false
         * otherwise. If the application does not have @c
         * Permission::ProfileUpdatesAllowed, returns false.
         * @since BlackBerry 10.0.0
         */
        bool requestRegisterIcon(int iconId, bb::platform::bbm::ImageType::Type iconType, const QByteArray &iconData);

        /*!
         * @brief Requests retrieval of the icon with the given iconId.
         * The signal @c iconRetrieved() is emitted as an asynchronous response.
         *
         * @param iconId The ID of the requested icon.
         *
         * @return true if sending the request succeeds, false
         * otherwise. If the application does not have @c
         * Permission::ProfileUpdatesAllowed, returns false.
         * @since BlackBerry 10.0.0
         */
        bool requestRetrieveIcon(int iconId) const;

        Q_SIGNALS:

        /*!
         * Emitted when the ProfileBoxItem is added to the ProfileBox.
         *
         * @param itemId The ID of the item added to the ProfileBox.
         * @since BlackBerry 10.0.0
         */
        void itemAdded(const QString &itemId);

        /*!
         * Emitted when a ProfileBoxItem is removed from the ProfileBox.
         *
         * @param itemId The ID of the ProfileBoxItem removed from the
         * ProfileBox.
         * @since BlackBerry 10.0.0
         */
        void itemRemoved(const QString &itemId);

        /*!
         * Emitted when the icon specified by the iconId is registered.
         *
         * @param iconId The ID of the registered icon.
         * @since BlackBerry 10.0.0
         */
        void iconRegistered(int iconId);


        /*!
         * Emitted in response to an icon retrieval request.
         *
         * @param iconId The ID of the icon that was retrieved.
         * @param iconType The MIME type of the icon that was retrieved. If an
         * invalid type was specified during icon registration, the behavior of
         * this method is undefined.
         * @param iconData The icon data.
         * @since BlackBerry 10.0.0
         */
        void iconRetrieved(int iconId, bb::platform::bbm::ImageType::Type iconType, const QByteArray &iconData);

      private:
        Q_DECLARE_PRIVATE(ProfileBox)
        Q_DISABLE_COPY(ProfileBox)
        QScopedPointer<ProfileBoxPrivate> d_ptr;
      };

    } /* namespace bbm */
  } /* namespace platform */
} /* namespace bb */
#endif /* BB_PLATFORM_BBM_PROFILEBOX_HPP */
