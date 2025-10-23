/**
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CASCADES_MULTIMEDIA_CAMERATYPES_HPP
#define BB_CASCADES_MULTIMEDIA_CAMERATYPES_HPP

#include <bb/cascades/multimedia/Global>

#include <QtDeclarative>

namespace bb
{
namespace cascades
{
namespace multimedia
{

/*!
 * @brief Provides values that identify a particular camera on the device, such as the
 *        front-facing camera or rear-facing camera.
 *
 * @xmlonly
 * <apigrouping group="Multimedia/Camera"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_CASCADES_MULTIMEDIA_EXPORT CameraUnit
{
    Q_GADGET
    Q_ENUMS(Type)

public:

    /*!
     * @brief An enumeration of possible camera identifiers.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
        /*!
         * @brief Indicates that no camera is selected.
         *
         * @since BlackBerry 10.0.0
         */
        None  = 0,

        /*!
         * @brief Indicates the front-facing camera.
         *
         * @since BlackBerry 10.0.0
         */
        Front = 1,

        /*!
         * @brief Indicates the rear-facing camera.
         *
         * @since BlackBerry 10.0.0
         */
        Rear  = 2,
    };
private:
    CameraUnit();
    ~CameraUnit();
};

/*!
 * @brief Provides values for camera modes, such as photo mode or video mode.
 *
 * @xmlonly
 * <apigrouping group="Multimedia/Camera"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_CASCADES_MULTIMEDIA_EXPORT CameraMode
{
    Q_GADGET
    Q_ENUMS(Type)

public:

    /*!
     * @brief An enumeration of possible camera mode selection values.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
        /*!
         * @brief Indicates the still camera mode.
         *
         * @since BlackBerry 10.0.0
         */
        Photo         = 0,

        /*!
         * @brief Indicates the video camera mode.
         *
         * @since BlackBerry 10.0.0
         */
        Video         = 1,
    };
private:
    CameraMode();
    ~CameraMode();
};

/*!
 * @brief Provides values for camera focus modes, such as manual, automatic, and macro.
 *
 * @xmlonly
 * <apigrouping group="Multimedia/Camera"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_CASCADES_MULTIMEDIA_EXPORT CameraFocusMode
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief An enumeration of possible focus mode selector values.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
        /*!
         * @brief Indicates that focus is disabled.
         *
         * @since BlackBerry 10.0.0
         */
        Off             = 0,

        /*!
         * @brief Indicates manual focus mode.
         *
         * @since BlackBerry 10.0.0
         */
        Manual          = 1,

        /*!
         * @brief Indicates automatic single-cycle focus mode.
         *
	 * @details Single-cycle focus occurs once and then stops.
	 *
         * @since BlackBerry 10.0.0
         */
        Auto            = 2,

        /*!
         * @brief Indicates single-cycle macro focus mode.
         *
	 * @details Single-cycle focus occurs once and then stops.
         *
         * @since BlackBerry 10.0.0
         */
        Macro           = 3,

        /*!
         * @brief Indicates continuous automatic focus mode.
         *
	 * @details With this mode the focus algorithm restarts if the scene goes out of focus.
	 *
         * @since BlackBerry 10.0.0
         */
        ContinuousAuto  = 4,

        /*!
         * @brief Indicates continuous macro focus mode.
         *
	 * @details With this mode the focus algorithm restarts if the scene goes out of focus.
	 *
         * @since BlackBerry 10.0.0
         */
        ContinuousMacro = 5
    };
private:
    CameraFocusMode();
    ~CameraFocusMode();
};

/*!
 * @brief Provides values for camera flash modes, such as always-on and automatic.
 *
 * @xmlonly
 * <apigrouping group="Multimedia/Camera"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_CASCADES_MULTIMEDIA_EXPORT CameraFlashMode
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief An enumeration of possible flash mode selector values.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
        /*!
         * @brief Indicates that the flash is disabled.
         *
         * @since BlackBerry 10.0.0
         */
        Off   = 0,

        /*!
         * @brief Indicates that the flash is always used.
         *
         * @since BlackBerry 10.0.0
         */
        On    = 1,

        /*!
         * @brief Indicates that the flash is used in low-light conditions.
         *
         * @since BlackBerry 10.0.0
         */
        Auto  = 2,

        /*!
         * @brief Indicates that the flash light is on for the duration that the viewfinder
         *        is active.
         *
         * @since BlackBerry 10.0.0
         */
        Light = 3
    };
private:
    CameraFlashMode();
    ~CameraFlashMode();
};

/*!
 * @brief Provides values for camera scene modes, such as action and night.
 *
 * @xmlonly
 * <apigrouping group="Multimedia/Camera"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_CASCADES_MULTIMEDIA_EXPORT CameraSceneMode
{
    Q_GADGET
    Q_ENUMS(Type)

public:

    /*!
     * @brief An enumeration of scene mode selector values.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
        /*!
         * @brief Indicates automatic scene mode.
         *
         * @since BlackBerry 10.0.0
         */
        Auto         = 0,

        /*!
         * @brief Indicates action scene mode.
         *
         * @since BlackBerry 10.0.0
         */
        Action       = 1,

        /*!
         * @brief Indicates whiteboard scene mode.
         *
         * @since BlackBerry 10.0.0
         */
        Whiteboard   = 2,

        /*!
         * @brief Indicates night scene mode.
         *
         * @since BlackBerry 10.0.0
         */
        Night        = 3,

        /*!
         * @brief Indicates beach-and-snow scene mode.
         *
         * @since BlackBerry 10.0.0
         */
        BeachAndSnow = 4
    };
private:
    CameraSceneMode();
    ~CameraSceneMode();
};

/*!
 * @brief Provides values for camera capture modes, such as normal and image stabilization.
 *
 * @xmlonly
 * <apigrouping group="Multimedia/Camera"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_CASCADES_MULTIMEDIA_EXPORT CameraShootingMode
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief An enumeration of possible capture mode selector values.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
        /*!
         * @brief Indicates normal capture mode.
         *
         * @since BlackBerry 10.0.0
         */
        Normal          = 0,

        /*!
         * @brief Indicates that image stabilization is enabled.
         *
         * @since BlackBerry 10.0.0
         */
        Stabilization   = 1,
    };
private:
    CameraShootingMode();
    ~CameraShootingMode();
};

/*!
  * @brief Provides values for camera focus states, such as waiting, searching, and
  *        locked.
  *
  * @xmlonly
  * <apigrouping group="Multimedia/Camera"/>
  * @endxmlonly
  *
  * @since BlackBerry 10.0.0
  */
class BB_CASCADES_MULTIMEDIA_EXPORT CameraFocusState
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief An enumeration of focus state identifier values.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
        /*!
         * @brief Indicates that no focus state exists.
         *
         * @since BlackBerry 10.0.0
         */
        None      = 0,

        /*!
         * @brief Indicates that the camera is waiting for focus.
         *
         * @since BlackBerry 10.0.0
         */
        Waiting   = 1,

        /*!
         * @brief Indicates that the camera is searching for focus.
         *
         * @since BlackBerry 10.0.0
         */
        Searching = 2,

        /*!
         * @brief Indicates that focus has failed.
         *
         * @since BlackBerry 10.0.0
         */
        Failed    = 3,

        /*!
         * @brief Indicates that focus has been locked.
         *
         * @since BlackBerry 10.0.0
         */
        Locked    = 4
    };
private:
    CameraFocusState();
    ~CameraFocusState();
};

/*!
 * @brief Provides reason codes for camera errors, such as a bad pointer, API failure,
 *        or to indicate that the camera is in use.
 *
 * @xmlonly
 * <apigrouping group="Multimedia/Camera"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_CASCADES_MULTIMEDIA_EXPORT CameraError
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief An enumeration of possible error reason codes.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
        /*!
         * @brief Indicates an unspecified error.
         *
         * @since BlackBerry 10.0.0
         */
        General            = 0,

        /*!
         * @brief Indicates an illegal pointer argument.
         *
         * @since BlackBerry 10.0.0
         */
        BadPointer         = 1,

        /*!
         * @brief Indicates that the operation could not be completed.
         *
         * @since BlackBerry 10.0.0
         */
        APIFailure         = 2,

        /*!
         * @brief Indicates that the argument is an unsupported value.
         *
         * @since BlackBerry 10.0.0
         */
        InvalidArgument    = 3,

        /*!
         * @brief Indicates that the operation cannot be performed within the current
         *        camera state.
         *
         * @since BlackBerry 10.0.0
         */
        InvalidState       = 4,

        /*!
         * @brief Indicates that there is insufficient space remaining on the recording
         *        file system.
         *
         * @since BlackBerry 10.0.0
         */
        RecordingSpaceFull = 5,

        /*!
         * @brief Indicates that the camera is currently in use, possibly by another process.
         *
         * @since BlackBerry 10.0.0
         */
        CameraInUse        = 6,

        /*!
         * @brief Indicates that the microphone is currently in use, possibly by another process.
         *
         * @since BlackBerry 10.0.0
         */
        MicInUse           = 7
    };
private:
    CameraError();
    ~CameraError();
};

} // namespace multimedia
} // namespace cascades
} // namespace bb

#endif /* header guard */
