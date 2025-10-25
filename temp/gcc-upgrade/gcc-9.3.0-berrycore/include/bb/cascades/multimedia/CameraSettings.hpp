/**
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CASCADES_MULTIMEDIA_CAMERASETTINGS_HPP
#define BB_CASCADES_MULTIMEDIA_CAMERASETTINGS_HPP

#include <bb/cascades/multimedia/CameraMode>

#include <bb/cascades/multimedia/Global>

#include <QObject>
#include <QPoint>
#include <QRect>
#include <QSize>
#include <QtDeclarative>

namespace bb
{
namespace cascades
{
namespace multimedia
{

class CameraSettingsPrivate;

/*!
 * @brief Used to query and apply camera behavioral settings.
 *
 * @details This class is a container class that holds the properties used to control the behavior
 * of the camera. Camera settings must be passed as parameters to the @c Camera::applySettings()
 * function. The changed signals implemented by this class are emitted when their corresponding property
 * values have changed. These signals only report that a change has taken place, and do not
 * indicate that camera settings were applied successfully.
 *
 * @xmlonly
 * <apigrouping group="Multimedia/Camera"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_CASCADES_MULTIMEDIA_EXPORT CameraSettings : public QObject
{
    Q_OBJECT
    /*!
     * @brief A camera mode selector value.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::cascades::multimedia::CameraMode::Type cameraMode READ cameraMode WRITE setCameraMode NOTIFY cameraModeChanged FINAL)
    /*!
     * @brief A shooting mode selector value.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::cascades::multimedia::CameraShootingMode::Type shootingMode READ shootingMode WRITE setShootingMode NOTIFY shootingModeChanged FINAL)
    /*!
     * @brief A scene mode selector value.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::cascades::multimedia::CameraSceneMode::Type sceneMode READ sceneMode WRITE setSceneMode NOTIFY sceneModeChanged FINAL)
    /*!
     * @brief A flash mode selector value.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::cascades::multimedia::CameraFlashMode::Type flashMode READ flashMode WRITE setFlashMode NOTIFY flashModeChanged FINAL)
    /*!
     * @brief A focus mode selector value.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::cascades::multimedia::CameraFocusMode::Type focusMode READ focusMode WRITE setFocusMode NOTIFY focusModeChanged FINAL)
    /*!
     * @brief A focus region setting.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QRect focusRegion READ focusRegion WRITE setFocusRegion NOTIFY focusRegionChanged FINAL)
    /*!
     * @brief A capture resolution setting.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QSize captureResolution READ captureResolution WRITE setCaptureResolution NOTIFY captureResolutionChanged FINAL)
    /*!
     * @brief A zoom level setting.
     *
     * @since BlackBerry 10.0.0
     *
     */
    Q_PROPERTY(unsigned int zoomLevel READ zoomLevel WRITE setZoomLevel NOTIFY zoomLevelChanged FINAL)
    /*!
     * @brief The cameraRollPath property can be used to set the directory on the device where files are saved.
     * Typical publicly accessible locations designated for use by the camera are:
     *        .../accounts/1000/shared/camera
     *        .../accounts/1000/removable/sdcard/camera
     *        .../accounts/1000-enterprise/shared/camera
     *        .../accounts/1000-corp/shared/camera
     *
     *        NOTE: In releases prior to 10.2.1, setting the roll path to a private folder such as your application sandbox would fail.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString cameraRollPath READ cameraRollPath WRITE setCameraRollPath NOTIFY cameraRollPathChanged FINAL)

    /*!
     * @brief A visibility setting.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged FINAL)

public:

    /*!
     * @brief Creates a new @c %CameraSettings instance.
     *
     * @param parent If not 0, the supplied parent will be responsible for deleting this instance.
     *
     * @since BlackBerry 10.0.0
     */
    explicit CameraSettings(QObject *parent=0);

    /*!
     * @brief Destroys this @c %CameraSettings.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~CameraSettings();

    /*!
     * @brief Gets the current camera mode.
     *
     * @return The camera mode.
     *
     * @since BlackBerry 10.0.0
     */
    bb::cascades::multimedia::CameraMode::Type cameraMode() const;

    /*!
     * @brief Sets the camera mode and updates the settings to the default values for
     *        that mode.
     *
     * @param mode The camera mode to set.
     *
     * @since BlackBerry 10.0.0
     */
     void setCameraMode(bb::cascades::multimedia::CameraMode::Type mode);

    /*!
     * @brief Gets the current shooting mode.
     *
     * @return The shooting mode.
     *
     * @since BlackBerry 10.0.0
     */
     bb::cascades::multimedia::CameraShootingMode::Type shootingMode() const;

    /*!
     * @brief Sets the shooting mode.
     *
     * @param mode The shooting mode to set.
     *
     * @since BlackBerry 10.0.0
     */
    void setShootingMode(bb::cascades::multimedia::CameraShootingMode::Type mode);

    /*!
     * @brief Gets the current scene mode.
     *
     * @return The scene mode.
     *
     * @since BlackBerry 10.0.0
     */
    bb::cascades::multimedia::CameraSceneMode::Type sceneMode() const;

    /*!
     * @brief Sets the scene mode.
     *
     * @param mode The scene mode to set.
     *
     * @since BlackBerry 10.0.0
     */
    void setSceneMode(bb::cascades::multimedia::CameraSceneMode::Type mode);

    /*!
     * @brief Gets the current flash mode.
     *
     * @return The flash mode.
     *
     * @since BlackBerry 10.0.0
     */
    bb::cascades::multimedia::CameraFlashMode::Type flashMode() const;

    /*!
     * @brief Sets the flash mode.
     *
     * @param mode The flash mode to set.
     *
     * @since BlackBerry 10.0.0
     */
    void setFlashMode(bb::cascades::multimedia::CameraFlashMode::Type mode);

    /*!
     * @brief Gets the current focus mode.
     *
     * @return The focus mode.
     *
     * @since BlackBerry 10.0.0
     */
    bb::cascades::multimedia::CameraFocusMode::Type focusMode() const;

    /*!
     * @brief Sets the focus mode.
     *
     * @param mode The focus mode to set.
     *
     * @since BlackBerry 10.0.0
     */
    void setFocusMode(bb::cascades::multimedia::CameraFocusMode::Type mode);

    /*!
     * @brief Gets the current capture resolution.
     *
     * @return A @c QSize object that contains the capture resolution.
     *
     * @since BlackBerry 10.0.0
     */
    QSize captureResolution() const;

    /*!
     * @brief Sets the capture resolution.
     *
     * @details For more information about supported resolutions, see
     *          @c Camera::supportedCaptureResolutions().
     *
     * @param resolution The capture resolution to set.
     *
     * @since BlackBerry 10.0.0
     */
    void setCaptureResolution(const QSize &resolution);

    /*!
     * @brief Gets current zoom level.
     *
     * @return The zoom level.
     *
     * @since BlackBerry 10.0.0
     */
    unsigned int zoomLevel() const;

    /*!
     * @brief Sets the zoom level.
     *
     * @details Smooth zoom is employed if it is supported.
     *
     * @param level The zoom level to set.
     *
     * @since BlackBerry 10.0.0
     */
    void setZoomLevel(unsigned int level);

    /*!
     * @brief Specifies coordinates to use for a focus target.
     *
     * @param focusRegion The position for focus. The x-coordinate is the
     * offset from screen left to the leftmost edge of the focus region and the y-coordinate is
     * the offset from screen top to the topmost edge of the focus region. The width and height
     * represent the size of the focus region.
     *
     * @details
     * The focusMode property must be set to a value other than Off for this region to take effect
     * when applied to the camera. Once applied, the autofocus algorithm will give priority to focusing
     * on objects within the region.
     *
     * @since BlackBerry 10.0.0
     */
    void setFocusRegion(const QRect &focusRegion);

    /*!
     * @brief Gets the focus coordinates that are set.
     *
     * @return The coordinates of the focus region.
     *
     * @since BlackBerry 10.0.0
     */
    QRect focusRegion() const;

    /*!
     * @brief Sets the location where the media will be saved.
     *
     * @param path The location where the media will be saved.
     *
     * @since BlackBerry 10.0.0
     */
    void setCameraRollPath(const QString &path);

    /*!
     * @brief Gets the location where media is saved.
     *
     * @return The location where media is saved.
     *
     * @since BlackBerry 10.0.0
     */
    QString cameraRollPath() const;

    /*!
     * @brief Indicates whether the camera control is visible.
     *
     * @return @c true if the camera control is visible, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool visible() const;

    /*!
     * @brief Sets whether the camera control is visible.
     *
     * @param visible @c True to make the camera control visible, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    void setVisible(bool visible);

Q_SIGNALS:
	/*!
     * @brief Emitted when the camera mode setting has been changed.
     *
     * @param mode The new camera mode.
	 *
	 * @since BlackBerry 10.0.0
     */
    void cameraModeChanged(bb::cascades::multimedia::CameraMode::Type mode);

    /*!
     * @brief Emitted when the shooting mode setting has been changed.
     *
     * @param mode The new shooting mode.
     *
     * @since BlackBerry 10.0.0
     */
    void shootingModeChanged(bb::cascades::multimedia::CameraShootingMode::Type mode);

    /*!
     * @brief Emitted when the scene mode setting has been changed.
     *
     * @param mode The new scene mode.
     *
     * @since BlackBerry 10.0.0
     */
    void sceneModeChanged(bb::cascades::multimedia::CameraSceneMode::Type mode);

    /*!
     * @brief Emitted when the flash mode setting has been changed.
     *
     * @param mode The new flash mode.
     *
     * @since BlackBerry 10.0.0
     */
    void flashModeChanged(bb::cascades::multimedia::CameraFlashMode::Type mode);

    /*!
     * @brief Emitted when the focus mode setting has been changed.
     *
     * @param mode The new focus mode.
     *
     * @since BlackBerry 10.0.0
     */
    void focusModeChanged(bb::cascades::multimedia::CameraFocusMode::Type mode);

    /*!
     * @brief Emitted when the focus region has been changed.
     *
     * @param focusRegion The new focus region.
     *
     * @since BlackBerry 10.0.0
     */
    void focusRegionChanged(const QRect &focusRegion);

    /*!
     * @brief Emitted when the capture resolution has been changed.
     *
     * @param resolution The new capture resolution.
     *
     * @since BlackBerry 10.0.0
     */
    void captureResolutionChanged(const QSize &resolution);

    /*!
     * @brief Emitted when the zoom level has been changed.
     *
     * @param level The new zoom level.
     *
     * @since BlackBerry 10.0.0
     */
    void zoomLevelChanged(unsigned int level);

    /*!
     * @brief Emitted when the camera roll path has been changed.
     *
     * @param path The new camera roll path.
     *
     * @since BlackBerry 10.0.0
     */
    void cameraRollPathChanged(const QString &path);

    /*!
     * @brief Emitted when the visibility changes.
     *
     * @param visible The new visible value.
     *
     * @since BlackBerry 10.0.0
     */
    void visibleChanged(bool visible);

private:
    friend class Camera;
    friend class CameraPrivate;

    QScopedPointer<CameraSettingsPrivate> const d_ptr;
    Q_DECLARE_PRIVATE(CameraSettings);
    Q_DISABLE_COPY(CameraSettings);
};

} /*! namespace multimedia */
} /*! namespace cascades */
} /*! namespace bb */

QML_DECLARE_TYPE(bb::cascades::multimedia::CameraSettings)

#endif /* header guard */
