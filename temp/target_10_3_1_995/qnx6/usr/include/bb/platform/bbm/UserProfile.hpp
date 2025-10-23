/*!
 *
 * @copyright
 * Copyright Research In Motion Limited, 2012-2012
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_BBM_USERPROFILE_HPP
#define BB_PLATFORM_BBM_USERPROFILE_HPP

#include <bb/platform/bbm/Global>
#include <bb/platform/bbm/UserStatus>

#include <QObject>

namespace bb
{
  namespace platform
  {
    namespace bbm
    {
      class Context;
      class UserProfilePrivate;

      /*!
       * @headerfile UserProfile.hpp <bb/platform/bbm/UserProfile>
       *
       * @brief Represents the user's BBM profile.
       *
       * @c UserProfile is a class that represents the user's BBM profile on the
       * BBM Social Platform. You can retrieve the user's display name, and
       * change the user's display picture, status, and personal message.
       * To access this information the application has to have access allowed.
       *
       * @since BlackBerry 10.0.0
       *
       * @xmlonly
       * <apigrouping group="App Integration/BBM"/>
       * <library name="bbplatformbbm"/>
       * @endxmlonly
       */
      class BB_PLATFORM_BBM_EXPORT UserProfile: public QObject
      {
        Q_OBJECT

      public:

        /*!
         * @brief Creates a new @c UserProfile object.
         *
         * @param context The @c context that provides the basis for the
         * UserProfile.
         * @param parent The @c QObject parent of this @c UserProfile object.
         * @since BlackBerry 10.0.0
         */
        explicit UserProfile(Context *context, QObject *parent = 0);

        /*!
         * @brief Destroys this @c UserProfile instance.
         * @since BlackBerry 10.0.0
         */
        virtual ~UserProfile();

        /*!
         * @brief Retrieves the version of the BBM connected app that is running
         * on the user's device.
         * @return The version of the BBM connected app that is running on the
         * user's device.
         * @since BlackBerry 10.0.0
         */
        QString applicationVersion() const;

        /*!@cond PRIVATE
         * @brief Deprecated
         * @deprecated This method returns the BBM Social Platform Version. Use
         * Context::platformVersion() instead.
         * @see Context::platformVersion()
         * @since BlackBerry 10.0.0
         */
        BB_PLATFORM_BBM_DEPRECATED int sdkVersion() const;
        //!@endcond PRIVATE

        /*!
         * @brief Retrieve the version of BBM that is running on the user's
         * device.
         * 
         * @details Possible BBM versions are:
         * <ul>
         *    <li>0x0100 for BBM version 1.0 on devices running BlackBerry Device Software 5.0 or earlier</li>
         *    <li>0x0200 for BBM version 2.0 on devices running BlackBerry Device Software 5.0 or earlier</li>
         *    <li>0x0201 for BBM version 2.1 on devices running BlackBerry Device Software 5.0 or earlier</li>
         *    <li>0x0202 for BBM version 2.2 on devices running BlackBerry Device Software 5.0 or earlier</li>
         *    <li>0x0205 for BBM version 2.5 on devices running BlackBerry Device Software 5.0 or earlier</li>
         *    <li>0x0206 for BBM version 2.6 on devices running BlackBerry Device Software 5.0 or earlier</li>
         *    <li>0x0600 for BBM version 6.0 on devices running BlackBerry Device Software 5, BlackBerry 6, or BlackBerry 7</li>
         *    <li>0x0601 for BBM version 6.1 on devices running BlackBerry Device Software 5, BlackBerry 6, or BlackBerry 7</li>
         *    <li>0x0700 for BBM version 7.0 on devices running BlackBerry Device Software 5, BlackBerry 6, or BlackBerry 7</li>
         *    <li>0x0a00 for BBM version 10.0 on devices running BlackBerry 10</li>
         *    <li>0x00 for unknown version</li>
         * </ul>
         *    
         * @return int The version of BBM that is running on the user's device. If the version
         * is unknown, returns 0.
         * @since BlackBerry 10.2.0
         */
        int bbmVersion() const;

        /*!
         * @brief Retrieves the user's BBM display name.
         * @return The user's BBM display name.
         */
        QString displayName() const;

        /*!
         * @brief Retrieves the user's BBM personal message.
         * @return The user's BBM personal message.
         * @since BlackBerry 10.0.0
         */
        QString personalMessage() const;


        /*!
         * @brief Retrieves the user's BBM status.
         * @return The user's BBM status.
         * @since BlackBerry 10.0.0
         */
        bb::platform::bbm::UserStatus::Type status() const;

        /*!
         * @brief Retrieves the user's BBM status message.
         * @return The user's BBM status message.
         * @since BlackBerry 10.0.0
         */
        QString statusMessage() const;

        /*!
         * @brief Retrieves the user's @c ppid.
         *
         * A user's @c ppid is the same across multiple instances of BBM (for
         * example, on a BlackBerry smartphone and a BlackBerry tablet), when
         * the user signs in with the same BlackBerry ID.
         *
         * @return The user's @c ppid.
         * @since BlackBerry 10.0.0
         */
        QString ppId() const;

        /*!
         * @brief Retrieves the user's @c handle.
         *
         * The @c handle is an identifier for a user on the BBM Social Platform
         * whose device is running BlackBerry 7 or earlier. It is provided for
         * backwards compatibility and should NOT be used as a persistent
         * identifier for a user. Use the @c ppid instead.
         *
         * The User's @c handle is the same for each instance of BBM (for
         * example, on a BlackBerry smartphone and a BlackBerry tablet).
         *
         * @return The user's @c handle.
         * @since BlackBerry 10.0.0
         */
        QString handle() const;

        /*!
         * @brief Retrieves the MIME type of the user's display picture.
         * If an invalid MIME type is provided, the behavior of
         * this method is undefined.
         *
         * @return The MIME type of the user's display picture.
         * @since BlackBerry 10.0.0
         */
        bb::platform::bbm::ImageType::Type displayPictureMimeType() const;

        /*!
         * @brief Retrieves the user's BBM display picture.
         * @return The user's BBM display picture.
         * @since BlackBerry 10.0.0
         */
        QByteArray displayPicture() const;

        /*!
         * @brief Updates the user's BBM personal message.
         * The signal @c personalMessageUpdated() is emitted as an asynchronous
         * response.
         * @param value The new personal message.
         *
         * @return true if sending the request succeeds; false otherwise.
         * @since BlackBerry 10.0.0
         */
        bool requestUpdatePersonalMessage(const QString &value);

        /*!
         * @brief Requests permission to update the user's BBM status and status
         * message.
         * The signal @c statusUpdated() is emitted as an asynchronous response.
         * @param status The new user status.
         * @param statusMessage The new status message.
         *
         * @return true if sending the request succeeds; false otherwise.
         * @since BlackBerry 10.0.0
         */
        bool requestUpdateStatus(bb::platform::bbm::UserStatus::Type status,
                                 const QString &statusMessage);

        /*!
         * @brief Requests permission to update the user's BBM display picture.
         * The signal @c displayPictureUpdated is emitted as an asynchronous
         *  response. The display picture is limited to 32kB of data; an attempt
         * to update with a display picture that exceeds this limit will fail.
         * @param imageType The MIME type of the new display picture. If an
         * invalid MIME type is provided, the behavior of this method is
         * undefined.
         * @param displayPicture The new display picture data.
         *
         * @return true if sending the request succeeds; false otherwise.
         * @since BlackBerry 10.0.0
         */
        bool requestUpdateDisplayPicture(
          bb::platform::bbm::ImageType::Type imageType,
          const QByteArray &displayPicture);

        Q_SIGNALS:

        /*!
         * @brief Emitted when the user's BBM @c displayName property changes.
         * @param value The new value of the @c displayName property.
         * @since BlackBerry 10.0.0
         */
        void displayNameUpdated(const QString &value);

        /*!
         * @brief Emitted when the user's BBM @c personalMessage property
         * changes.
         * @param value The new value of the @c personalMessage property.
         * @since BlackBerry 10.0.0
         */
        void personalMessageUpdated(const QString &value);

        /*!
         * @brief Emitted when the user's BBM @c status and/or @c statusMessage
         * changes.
         * @param status The new value of the @c status property.
         * @param statusMessage The new value of the @c statusMessage property.
         * @since BlackBerry 10.0.0
         */
        void statusUpdated(bb::platform::bbm::UserStatus::Type status,
                           const QString &statusMessage);

        /*!
         * @brief Emitted when the user's BBM display picture changes.
         * @param displayPictureMimeType The new value of the
         * @c displayPictureMimeType. If an invalid MIME type is provided,
         * the behavior of this method is undefined.
         * @param displayPicture The new value of the display picture data.
         * @since BlackBerry 10.0.0
         */
        void displayPictureUpdated(
          bb::platform::bbm::ImageType::Type displayPictureMimeType,
          const QByteArray &displayPicture);



      private:
        Q_DECLARE_PRIVATE(UserProfile)
        Q_DISABLE_COPY(UserProfile)
        QScopedPointer<UserProfilePrivate> d_ptr;
      };

    } /* namespace bbm */
  } /* namespace platform */
} /* namespace bb */
#endif /* BB_PLATFORM_BBM_USERPROFILE_HPP */
