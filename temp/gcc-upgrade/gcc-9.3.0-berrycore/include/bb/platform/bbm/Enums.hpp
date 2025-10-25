/*!
 *
 * @copyright
 * Copyright Research In Motion Limited, 2012-2012
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_BBM_ENUMS_HPP
#define BB_PLATFORM_BBM_ENUMS_HPP

#include <bb/platform/bbm/Global>

#include <QObject>


namespace bb
{
namespace platform
{
namespace bbm
{

/*!
 * @headerfile Enums.hpp <bb/platform/bbm/UserStatus>
 *
 * @brief Represents the status of a BBM user or contact
 *
 * @details A user's status can be in one of two states on the BBM Social Platform: available or busy.
 *
 * @since BlackBerry 10.0.0
 *
 * @xmlonly
 * <apigrouping group="App Integration/BBM"/>
 * <library name="bbplatformbbm"/>
 * @endxmlonly
 */
class BB_PLATFORM_BBM_EXPORT UserStatus
{
    Q_GADGET
    Q_ENUMS(Type)
public:
    /*!
     * @brief The list of possible values for user status.
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
      /*! 
       * Indicates that the user is available. 
       * @since BlackBerry 10.0.0
       */
        Available = 1,
      /*! 
       * Indicates that the user is busy. 
       * @since BlackBerry 10.0.0
       */
        Busy      = 2
    };
};

/*!
 * @headerfile Enums.hpp <bb/platform/bbm/RegistrationState>
 *
 * @brief Represents the @c RegistrationState of an application on the BBM Social Platform.
 *
 * @details RegistrationState is updated by the BBM Social Platform.
 *
 * @since BlackBerry 10.0.0
 *
 * @xmlonly
 * <apigrouping group="App Integration/BBM"/>
 * <library name="bbplatformbbm"/>
 * @endxmlonly
 */
class BB_PLATFORM_BBM_EXPORT RegistrationState
{
    Q_GADGET
    Q_ENUMS(Type)
public:
    /*!
     * @brief The list of possible registration states.
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
      /*! 
       * Your app has successfully registered and has full access to the BBM Social Platform. 
       * @since BlackBerry 10.0.0
       */
      Allowed                   = 0,

      /*! 
       * The BBM Social Platform has not yet retrieved the access code for your app. 
       * @since BlackBerry 10.0.0
       */
      Unknown                   = 1,

      /*! 
       * Your app is not registered with the BBM Social Platform. Call @c requestRegisterApplication()
       * to start the registration process.
       * @since BlackBerry 10.0.0
       */
      Unregistered              = 2,

      /*! 
       * Your app initiated the registration process and it is currently in progress. 
       * @since BlackBerry 10.0.0
       */
      Pending                   = 3,

      /*! 
       * Your app was blocked by the user and does not have access to the BBM Social Platform APIs.
       * The user can unblock the app by using the global settings application.
       * @since BlackBerry 10.0.0
       */
      BlockedByUser             = 4,

      /*!
       * Your app was blocked by RIM and does not have access to the BBM Social Platform APIs.
       * The app has most likely violated the terms of use.
       * @since BlackBerry 10.0.0
       */
      BlockedByRIM              = 5,

      /*! 
       * A data connection could not be established to complete registration.
       * The user needs to enable data services and/or access sufficient data coverage.
       * @since BlackBerry 10.0.0
       */
      NoDataConnection          = 6,

      /*! 
       * Your app could not register due to an unexpected error. 
       * @since BlackBerry 10.0.0
       */
      UnexpectedError           = 7,

      /*! 
       * Your app could not register because an invalid UUID was used in the registration process.
       * @since BlackBerry 10.0.0
       */
      InvalidUuid               = 8,

      /*! 
       * Your app could not register because of a temporary error.
       * @since BlackBerry 10.0.0
       */
      TemporaryError            = 9,

      /*! 
       * Your app has reached the maximum number of users allowed.
       * @since BlackBerry 10.0.0
       */
      MaxDownloadsReached       = 10,

      /*! 
       * Your app's access to the BBM Social Platform has expired and no longer has access to the BBM Social
       * Platform APIs. This limit is not applied to apps that are downloaded from BlackBerry World. You can
       * submit your app to BlackBerry World to ensure that it does not reach this limit.
       * @since BlackBerry 10.0.0
       */
      Expired                   = 11,

      /*! 
       * The registration process was canceled by the user.
       * @since BlackBerry 10.0.0
       */ 
      CancelledByUser           = 12,

      /*! 
       * Your app cannot register on this device because the maximum number of allowed apps has been reached.
       * @since BlackBerry 10.0.0
       */
      MaxAppsReached            = 13,

     /*! 
      * Your app cannot access the BBM Social Platform because BBM is disabled. The user needs to follow
      * the instructions specified in the BBM app to re-enable BBM. Once BBM is re-enabled, your app will receive
      * a new access status.
      * @since BlackBerry 10.0.0
      */
     BbmDisabled              = 14,

     /*!
      * Your app does not have access to the BBM Social Platform because
      * it is installed in the Work perimeter. To connect to BBM you must install your
      * app in the Personal perimeter. 
      * @since BlackBerry 10.2
      */
     BlockedEnterprisePerimeter  = 15
    };
};


/*!
 * @headerfile Enums.hpp <bb/platform/bbm/ImageType>
 *
 * @brief Represents the type of the image
 *
 * @details ImageType indicates the graphic file format.
 *
 * @since BlackBerry 10.0.0
 *
 * @xmlonly
 * <apigrouping group="App Integration/BBM"/>
 * <library name="bbplatformbbm"/>
 * @endxmlonly
 */
class BB_PLATFORM_BBM_EXPORT ImageType
{
    Q_GADGET
    Q_ENUMS(Type)
public:
    /*!
     * @brief The list of image types supported.
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
      /*!  
       * @since BlackBerry 10.0.0
       */
      Unsupported   = 0,
      /*!
       * @since BlackBerry 10.0.0
       */
        Jpg       = 1,
      /*!
       * @since BlackBerry 10.0.0
       */
        Png       = 2,
      /*!
       * @since BlackBerry 10.0.0
       */
        Gif         = 3,
      /*!
       * @since BlackBerry 10.0.0
       */ 
        Bmp         = 4
    };
};


/*!
 * @headerfile Enums.hpp <bb/platform/bbm/Permission>
 *
 * @brief The type of application permission.
 *
 * @details The user can set permissions for your app by using the global settings application.
 *
 * @since BlackBerry 10.0.0
 *
 * @xmlonly
 * <apigrouping group="App Integration/BBM"/>
 * <library name="bbplatformbbm"/>
 * @endxmlonly
 */
class BB_PLATFORM_BBM_EXPORT Permission
{
    Q_GADGET
    Q_ENUMS(Type)
public:
    /*!
     * @brief The list of permission types.
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
      /*!  
       * Indicates that profile updates, including activities and achievements, can be added to the user's BBM profile.
       * @since BlackBerry 10.0.0
       */
        ProfileUpdatesAllowed         = 1,
      /*!  
       * Indicates whether this user has allowed other users of this app to send this user invitations to become
       * a BBM contact.
       * @since BlackBerry 10.0.0
       */
        ContactInvitationsAllowed       = 2
    };
};

/*!
 * @headerfile Enums.hpp <bb/platform/bbm/PermissionValue>
 *
 * @brief The possible values of application permissions.
 *
 * @since BlackBerry 10.0.0
 *
 * @xmlonly
 * <apigrouping group="App Integration/BBM"/>
 * <library name="bbplatformbbm"/>
 * @endxmlonly
 */
class BB_PLATFORM_BBM_EXPORT PermissionValue
{
    Q_GADGET
    Q_ENUMS(Type)
public:
    /*!
     * @brief The list of permission values.
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
      /*!
       * @since BlackBerry 10.0.0
       */
        Allowed               = 1,
      /*!  
       * @since BlackBerry 10.0.0
       */
        Denied                = 2
        //Do we need a PermissionValue - Prompt
    };
};

} /* namespace bbm */
} /* namespace platform */
} /* namespace bb */
#endif /* BB_PLATFORM_BBM_ENUMS_HPP */
