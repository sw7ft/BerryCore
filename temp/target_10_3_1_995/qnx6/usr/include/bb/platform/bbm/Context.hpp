/*!
 *
 * @copyright
 * Copyright Research In Motion Limited, 2012-2012
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_BBM_CONTEXT_HPP
#define BB_PLATFORM_BBM_CONTEXT_HPP

#include <bb/platform/bbm/Global>
#include <bb/platform/bbm/RegistrationState>

#include <QObject>
#include <QScopedPointer>
#include <QUuid>

namespace bb
{
  namespace platform
  {
    namespace bbm
    {
      class ContextPrivate;

      /*!
       * @headerfile Context.hpp <bb/platform/bbm/Context>
       *
       * @brief Represents a class that has the necessary context for access to the BBM Social Platform.
       *
       * @details Creating a @c Context object initializes the BBM Social Platform for access.
       * Calling @c requestRegisterApplication() registers your app with the BBM Social Platform.
       * You can verify if your app has access to the BBM Social Platform by calling @c registrationAccessState().
       * @c RegistrationState::Allowed is returned if registration is successful. Once successfully
       * registered, your app can use the BBM Social Platform APIs.
       *
       * @since BlackBerry 10.0.0
       *
       * @xmlonly
       * <apigrouping group="App Integration/BBM"/>
       * <library name="bbplatformbbm"/>
       * @endxmlonly
       */
      class BB_PLATFORM_BBM_EXPORT Context: public QObject
      {
        Q_OBJECT
      public:
        /*!
         * @brief Creates a new @c Context object for your app.
         * The context object provides access to the BBM Social Platform APIs.
         *
         * @param applicationUuid The UUID is a unique, 128-bit, 36-character identifier that you generate
         * for your app using a UUID generator. The UUID string must conform to the Microsoft 8-4-4-4-12
         * format (xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx).
         * Valid characters consist of hexadecimal values in the ranges 0 to 9 and a to f.

         * A registration dialog may appear in your app after you invoke this function. The dialog
         * indicates to the user that your app is connecting to BBM. The user must dismiss
         * the dialog once registration is complete.
         *
         * @param parent The @c QObject parent of this @c Context object.
         * @see @c QUuid
         * @since BlackBerry 10.0.0
         */

        explicit Context(const QUuid &applicationUuid = QUuid(), QObject *parent = 0);

        /*!
         * @brief Destroys this @c Context object.
         * @since BlackBerry 10.0.0
         */
        virtual ~Context();

        /*!
         * @brief Requests registration of your app with the BBM Social Platform.
         *
         * @details <p>A progress registration dialog may appear in your
         * application after you invoke this function. The user can
         * cancel registration by dismissing the dialog. Once
         * registration is complete, a system toast may appear indicating to
         * the user that your application is now connected to BBM. If
         * registration does not complete successfully, a system dialog may
         * appear informing the user about the reason for failure.</p>
         * <p>If BBM is not set up when registration starts, the user may decide
         * to set up BBM. This action triggers registration to resume.
         * </p> The signal @c registrationStateUpdated is emitted as an
         * asynchronous response.
         *
         * @return true if sending the request succeeds, false otherwise.
         * @since BlackBerry 10.0.0
         */
        Q_SLOT bool requestRegisterApplication();

        /*!
         * @brief Requests registration of your app with the BBM Social Platform.
         *
         * @details A UUID is a unique, 128-bit, 36-character identifier that you
         * generate for your app using a UUID (or GUID) generator. The UUID string must conform to
         * the Microsoft 8-4-4-4-12 format (xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx).
         * Valid characters consist of hexadecimal values in the ranges 0 to 9 and a to f.
         * <p>Registration takes place in "silent" mode so that the registration progress
         * dialog does not appear to the user after you invoke this function.
         * Once registration is complete, a system toast appears to indicate to
         * the user that your application is now connected to BBM. If registration
         * does not complete successfully, no system dialog is displayed to inform
         * the user about the reason for failure.</p>
         * <p>If permission to connect to BBM is not set up when registration starts,
         * the user may decide to set up BBM. This action will cause registration to resume.</p>
         *
         * </p> The signal @c registrationStateUpdated is emitted as an
         * asynchronous response.
         *
         * @return true if sending the request succeeds, false otherwise.
         * @since BlackBerry 10.2.0
         */
        Q_SLOT bool requestRegisterApplicationSilent();

        /*!
         * @brief Retrieves the registration state of your app.
         * @return The registration state, @c RegistrationState::Type.
         * @since BlackBerry 10.0.0
         */
        bb::platform::bbm::RegistrationState::Type registrationState() const;

        /*!
         * @brief Verifies whether the registration state of your app is @c RegistrationState::Allowed
         * @return true if the registration state is @c RegistrationState::Allowed, false otherwise.
         * @since BlackBerry 10.0.0
         */
        bool isAccessAllowed() const;

        /*!
         * @brief Retrieves the version of the BBM Social Platform.
         * @details The possible versions are:
         *      200 - the second release of the BBM Social Platform for
         *      BlackBerry 10. Release date: June, 2013.
         *      100 - the first release of the BBM Social Platform for
         *      BlackBerry 10. Release date: January, 2013. Also, the first
         *      release of the BBM Social Platform for BlackBerry Device Software version
         *      5, BlackBerry 6, and BlackBerry 7. Release date: October, 2011.
         *
         *      120 - release for BlackBerry Device Software version 5,
         *      BlackBerry 6, and BlackBerry 7. Release date: November, 2011.
         *
         *      130 - release for BlackBerry Device Software version 5,
         *      BlackBerry 6, and BlackBerry 7. Release date: February, 2012.
         * You can use the version number to check whether your application is
         * compatible with this version of the BBM Social Platform.
         *
         * @return The curent platform version number.
         * @since BlackBerry 10.0.0
         */
        int platformVersion() const;

       /*!
	    * @brief Determine if BBM is set up on the user's device.
	    * @details Verifies whether the user has completed the set up of
	    * BBM on their device by signing in with their BlackBerry ID
		* (Setup > BlackBerry Messenger).
        *
        * @return true if the BBM is setup, false otherwise.
        * @since BlackBerry 10.2.0
        */
        bool isBbmSetup() const;

        Q_SIGNALS:


        /*! @brief Emitted when your app's access to the BBM Social Platform is updated.
         * @details Access to the BBM Social Platform APIs, afforded by the @c Context object, becomes available
         * only after the registration access state changes to @c RegistrationState::AccessAllowed.
         *
         * @param state @c bb::platform::bbm::RegistrationState.
         * @since BlackBerry 10.0.0
         */
        void registrationStateUpdated(bb::platform::bbm::RegistrationState::Type state);


      private:
        QScopedPointer<ContextPrivate> d_ptr;
        Q_DECLARE_PRIVATE(Context)
        Q_DISABLE_COPY(Context)
      };

    }
  }
}
#endif /* BB_PLATFORM_BBM_CONTEXT_HPP */
