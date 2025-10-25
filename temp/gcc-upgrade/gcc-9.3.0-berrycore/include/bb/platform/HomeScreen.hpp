/*!
 * @copyright
 * Copyright Research In Motion Limited, 2011-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_HOMESCREEN_HPP
#define BB_PLATFORM_HOMESCREEN_HPP

#include <bb/platform/Global>

#include <bb/platform/DeviceLockState>
#include <bb/platform/WallpaperLockState>
#include <bb/platform/WallpaperResult>

#include <QtCore/QObject>
#include <QtCore/QScopedPointer>
#include <QtCore/QSize>
#include <QtCore/QString>
#include <QtCore/QUrl>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace platform
{

class HomeScreenPrivate;

/*!
 * @headerfile HomeScreen.hpp <bb/platform/HomeScreen>
 *
 * @brief The @c HomeScreen class encapsulates interactions between an application and the home screen on the device.
 *
 * @details The @c HomeScreen class provides an API for interactions between an application and the home screen.
 * The current set of possible interactions are:
 * - Changing the wallpaper on the background of the home screen to a new image.
 * - Notifications when the device becomes screen or password locked.
 * - Adding shortcuts for URLs.
 * - Notification when the device enters and exits bedside mode.
 *
 * Note that, once created, objects of this class cannot have their thread affinity changed,
 * either explicitly via @c QObject::moveToThread() or implicitly by changing the thread
 * affinity of the parent of the object.  Doing so results in undefined behavior.
 *
 * Example usage:
 * @include libbbplatform/Homescreen_constructor.cpp
 *
 * @xmlonly
 * <apigrouping group="Platform/Home screen"/>
 * <library name="bbplatform"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_PLATFORM_EXPORT HomeScreen : public QObject
{
    Q_OBJECT

    /*!
     * @brief The lock state of the device.
     *
     * @see @c bb::platform::DeviceLockState::Type for the list of lock states.
     *
     * Accessing the lock state property in QML
     * @snippet libbbplatform/HomeScreen_lockState.qml All
     *
     * @since BlackBerry 10.0.0
     */
     Q_PROPERTY(bb::platform::DeviceLockState::Type lockState READ lockState NOTIFY lockStateChanged FINAL)

     /*!
      * @brief Indicates whether the device is in bedside mode.
      *
      * @since BlackBerry 10.0.0
      */
     Q_PROPERTY(bool bedsideModeActive READ isBedsideModeActive NOTIFY bedsideModeActiveChanged FINAL)

     /*!
      * @brief Indicates the current wallpaper lock state.
      * 
      * @see @c bb::platform::WallpaperLockState::Type for the list of wallpaper lock states.
      * 
      * @since BlackBerry 10.2.0
      */
      Q_PROPERTY(bb::platform::WallpaperLockState::Type wallpaperLockState READ wallpaperLockState NOTIFY wallpaperLockStateChanged FINAL REVISION 1)
public:

    /*!
     * @brief Creates a new @c HomeScreen object.
     *
     * Constructing a @c HomeScreen object in C++
     * @snippet libbbplatform/HomeScreen_constructor.cpp All
     *
     * Constructing a @c HomeScreen object in QML
     * @snippet libbbplatform/HomeScreen_constructor.qml All
     *
     * @param parent If not 0, the supplied parent will be responsible for deleting this instance.
     *
     * @since BlackBerry 10.0.0
     */
    explicit HomeScreen(QObject *parent = 0);

    /*!
     * @brief Destroys this @c HomeScreen object.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~HomeScreen();

    /*!
     * @brief Returns the current state of the wallpaper lock.
     * 
     * @return The state of the wallpaper lock.  See @c bb::platform::WallpaperLockState for the
     * list of possible states.
     * 
     * @since BlackBerry 10.2.0
     */
    bb::platform::WallpaperLockState::Type wallpaperLockState() const;

    /*!
     * @brief Sets the home screen wallpaper for the current view to the supplied image.
     *
     * @details The path is provided as a URL, but it must be a path on the file system.
     * Legal path specifications are described below.
     *
     * The image will be scaled to fit the screen.
     *
     * If the wallpaper image is deleted while it is set as the current wallpaper (say, because
     * the image is an asset in an application that is then deleted), the image will remain the
     * wallpaper until the device is rebooted.  At that point, the default wallpaper will be reapplied.
     *
     * The new wallpaper is only applied to the currently active view (personal, work, etc.).
     *
     * Note that this method now operates synchronously.  The return value now indicates the results from
     * the home screen, not that the request was successfully issued.  A return value of @c true means the
     * request was successfully processed, @c false indicates an error (which we interpret as the wallpaper
     * being locked).  There is no longer any need to use the @c wallpaperFinished() signal to get the
     * results.  However, for backwards compatibility, the signal is still emitted.
     *
     * The supplied URL can be one of the following:
     * - An asset associated with the application.  The assets directory can be specified using the @c "asset:///" scheme
     *   in the URL.  The path of the URL is interpreted as a relative path using the assets directory as the base.
     *   For example, <code>QUrl("asset:///images/background.png")</code> uses an image from the assets directory.
     * - An absolute path to the file.  This can be specified using a @c "file:///" URL or simply supplying an absolute path
     *   with no scheme in the URL.  For example, <code>QUrl("file:///accounts/1000/shared/camera/background.png")</code> or
     *   <code>QUrl("/accounts/1000/shared/camera/background.png")</code> uses the image file from the shared photos directory (assuming
     *   the application has permission to access shared files).
     * - A relative path, relative to the root of the application's working directory.  To provide a relative path, do not
     *   supply a scheme in the URL.  Simply supply a relative path to the desired file. For example,
     *   <code>QUrl("app/native/assets/images/background.png")</code> uses an image from the assets directory.
     *
     * Unrecognized URL schemes will result in a failure.
     *
     * The supplied URL must refer to a file that contains a recognized image type. Recognized image files are those
     * that end in one of the following extensions: .jpg, jpeg, .jfif, .jif, .jpe, or .png.
     *
     * @warning Note that this method does not validate the contents of the supplied image, just that the extension
     * matches a recognized image file.  As a result, the return value of this method only indicates if
     * it successfully requested that the wallpaper be set to the supplied path, and not whether the wallpaper
     * was successfully changed.  If the path leads to an invalid image, this method may return true even
     * though the wallpaper is not changed.  Also note that supplying an invalid file will cause the wallpaper
     * to be reset to the system default.
     *
     * Setting the wallpaper in C++
     * @snippet libbbplatform/HomeScreen_setWallpaper.cpp All
     *
     * Setting the wallpaper in QML
     * @snippet libbbplatform/HomeScreen_setWallpaper.qml All
     *
     * @param wallpaperFile The URL to the file containing the new wallpaper image.
     *
     * @return @c true if the wallpaper request was successfully processed by the home screen, @c false otherwise.
     * This method may fail if there is a PPS failure, if the scheme in the URL is not recognized, if the supplied
     * wallpaper file is invalid (does not exist, cannot be read, is a directory, or is not a recognized image file),
     * or if the wallpaper is locked.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE bool setWallpaper( const QUrl & wallpaperFile );

    /*!
     * @brief Add a URL-launching-shortcut to the home screen.
     *
     * @details When the user clicks the shortcut, the URL is launched as if it were invoked via the
     * @c InvokeManager.
     *
     * The supplied icon path URL can be one of the following:
     * - An asset associated with the application.  The assets directory can be specified using the @c "asset:///" scheme
     *   in the URL.  The path of the URL is interpreted as a relative path using the assets directory as the base.
     *   For example, <code>QUrl("asset:///images/icon.png")</code> uses an image from the assets directory.
     * - An absolute path to the file.  This can be specified using a @c "file:///" URL or simply supplying an absolute path
     *   with no scheme in the URL.  For example, @c <code>QUrl("file:///accounts/1000/shared/camera/icon.png")</code> or
     *   <code>QUrl("/accounts/1000/shared/camera/icon.png")</code> uses the image file from the shared photos directory (assuming
     *   the application has permission to access shared files).
     * - A relative path, relative to the root of the application's working directory.  To provide a relative path, do not
     *   supply a scheme in the URL.  Simply supply a relative path to the desired file. For example,
     *   <code>QUrl("app/native/assets/images/icon.png")</code> uses an image from the assets directory.
     *
     * Unrecognized URL schemes will result in a failure.
     *
     * The supplied icon path URL must refer to a file that contains a recognized image type. Recognized image files
     * are those that end in one of the following extensions: .jpg, jpeg, .jfif, .jif, .jpe, or .png.
     *
     * Note that if the size of the supplied icon is larger than the expected icon size, it will be scaled
     * down to fit.  However, the supplied icon will not be scaled up if it is smaller than the expected
     * icon size.  Consult the UI guidelines for the correct icon size for the device.
     *
     * The supplied label is simplified before it is used.  This process strips any leading and trailing
     * whitespace, and any sequence of internal whitespace is replaced with a single space.  Whitespace
     * includes the characters @c '\\t', @c '\\n', @c '\\v', @c '\\f', @c '\\r', and @c ' '.
     *
     * Note that the supplied URL must be syntactically valid, but no effort is made to verify that
     * any application is registered for the URL scheme or that the URL refers to a legitimate resource.
     * If no URL handler exists for the provided scheme, then launching the shortcut will have no effect.
     * A complete list of recognized URL schemes can be found in the documentation for the
     * @c navigator_invoke() function.
     *
     * Adding a shortcut in C++
     * @snippet libbbplatform/HomeScreen_addShortcut.cpp All
     *
     * Adding a shortcut in QML
     * @snippet libbbplatform/HomeScreen_addShortcut.qml All
     *
     * @param iconPath The path to the icon for the shortcut, to be shown on the device's home screen.
     * @param iconLabel The label to appear under the icon on the device's home screen.
     * @param url The URL to invoke when the shortcut is launched by the user.
     *
     * @returns @c true if the shortcut was successfully added to the home screen, @c false otherwise.
     * Note that the shortcut is not added to the home screen if the icon path does not refer to a valid
     * image file, the icon label is empty, or the URL is empty.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE bool addShortcut( const QUrl &iconPath, const QString &iconLabel, const QUrl &url );

    /*!
     * @brief Returns the current lock state of the device.
     *
     * @see @c bb::platform::DeviceLockState for the list of device lock states.
     *
     * Checking the lock state in C++
     * @snippet libbbplatform/HomeScreen_lockState.cpp All
     *
     * Checking the lock state in QML
     * @snippet libbbplatform/HomeScreen_lockState.qml All
     *
     * @return The current lock state of the device.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE bb::platform::DeviceLockState::Type lockState() const;

    /*!
     * @brief Indicates whether the device is in bedside mode.
     *
     * @return @c true if the device is in bedside mode, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isBedsideModeActive() const;

Q_SIGNALS:
    /*!
     * @brief Emitted when the lock state on the device changes.
     *
     * @note Due to a work around for a Qt Core issue with accessing enums from QML
     * the argument of this signal doesn't follow naming convention for signals in
     * which the signal arguments are typically named to match the associated property's name.
     * Use the object's property to access current property value instead of the signal argument
     * to avoid runtime errors (i.e., use @c lockState instead of @c newState).
     *
     * Receiving the lock state changed signal in C++
     * @snippet libbbplatform/HomeScreen_lockStateChanged.cpp All
     *
     * Receiving the lock state changed signal in QML
     * @snippet libbbplatform/HomeScreen_lockStateChanged.qml All
     *
     * @param newState The new lock state of the device.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void lockStateChanged(bb::platform::DeviceLockState::Type newState);

    /*!
     * @brief Emitted when the wallpaper lock state on the device changes.
     * 
     * @param wallpaperLockState The new wallpaper lock state of the device.
     * 
     * @ingroup Signals
     * 
     * @since BlackBerry 10.2.0
     */
    Q_REVISION(1) void wallpaperLockStateChanged(bb::platform::WallpaperLockState::Type wallpaperLockState);

    /*!
     * @brief Emitted when a request to set the wallpaper is made, to provide the result of
     * the request.
     *
     * @details This result arrives in an event after the request is made.
     *
     * Note that multiple requests to update the wallpaper using the same path cannot
     * be differentiated.  If you make several calls to set the wallpaper using the same
     * path in rapid succession, you may find it difficult to associate a specific invocation
     * of this signal with a specific request.
     *
     * Receiving the wallpaper finished signal in C++
     * @snippet libbbplatform/HomeScreen_wallpaperFinished.cpp All
     *
     * Receiving the wallpaper finished signal in QML
     * @snippet libbbplatform/HomeScreen_wallpaperFinished.qml All
     *
     * @param path The path that was supplied to the @c setWallpaper() method.
     * @param result The result of the request to set the wallpaper. 
     *               See @c bb::platform::WallpaperResult for the list of possible results.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void wallpaperFinished(const QUrl &path, bb::platform::WallpaperResult::Type result);

    /*!
     * @brief Emitted when the device enters or leaves bedside mode.
     *
     * @param newState @c true if the device is now in bedside mode, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    void bedsideModeActiveChanged(bool newState);

protected:
//!@cond PRIVATE
    Q_SIGNAL void lockStateChanged(int newState);

    Q_SIGNAL void wallpaperFinished(const QUrl &path, int result);

    Q_REVISION(1) Q_SIGNAL void wallpaperLockStateChanged(int wallpaperLockState);
//!@endcond

private:
//!@cond PRIVATE
    QScopedPointer<HomeScreenPrivate> d_ptr;
    Q_DECLARE_PRIVATE(HomeScreen);
    Q_DISABLE_COPY(HomeScreen)
//!@endcond
};

} // namespace platform
} // namespace bb

QML_DECLARE_TYPE(bb::platform::HomeScreen)
#endif // BB_PLATFORM_HOMESCREEN_HPP
