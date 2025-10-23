/**
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CASCADES_MULTIMEDIA_CAMERA_HPP
#define BB_CASCADES_MULTIMEDIA_CAMERA_HPP

#include <bb/cascades/CustomControl>
#include <bb/cascades/Container>
#include <bb/cascades/DisplayDirection>
#include <bb/cascades/multimedia/CameraUnit>
#include <bb/cascades/multimedia/Global>

#include <QtDeclarative>
#include <QObject>

namespace bb
{
namespace cascades
{
namespace multimedia
{

class CameraPrivate;
class CameraSettings;

typedef QSharedPointer<unsigned char> SharedUCharPointer;

/*!
 * @brief A camera viewfinder control providing access to camera device hardware.
 *
 * @details The camera preview is displayed and scaled to fit within this control's display area
 * while maintaining its aspect ratio. Setting this control's width and height to values coinciding
 * with the aspect ratio of the capture resolution will display this control with its display area completely filled.
 *
 * The following actions need to be added to your BAR descriptor in order to use features of this API:
 *
 * - @c use_camera - Grants the ability to use the camera.
 *
 * - @c access_shared - Applications that call into this class to save captures require the @c access_shared action.
 *
 * - @c record_audio - Applications that call into this class to record audio require the @c record_audio action.
 *
 * @xmlonly
 * <apigrouping group="Multimedia/Camera"/>
 * @endxmlonly
 *
 *
 * @since BlackBerry 10.0.0
 */
class BB_CASCADES_MULTIMEDIA_EXPORT Camera : public CustomControl
{
    Q_OBJECT
    /*!
     * @brief The active camera unit.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::cascades::multimedia::CameraUnit::Type cameraUnit READ cameraUnit NOTIFY cameraUnitChanged FINAL)
    /*!
     * @brief The list of cameras present on the device.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QVariantList supportedCameras READ supportedCamerasQML CONSTANT FINAL)
    /*!
     * @brief The maximum zoom level supported by the last open camera.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(unsigned int maxZoomLevel READ maxZoomLevel FINAL)
    /*!
     * @brief Indicates whether the calling application currently has full access to the supported cameras.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bool allCamerasAccessible READ allCamerasAccessible FINAL)
    /*!
     * @brief The size, in bytes, of a viewfinder frame buffer based on the current
     *        viewfinder resolution, or 0 if a camera is not open.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(quint64 previewBufferSize READ previewBufferSize FINAL)
    /*!
     * @brief The orientation of the preview frame that is returned by @c previewFrameAvailable().
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(quint64 devicePreviewFrameDirection READ devicePreviewFrameDirection CONSTANT FINAL)

public:

    /*!
     * @brief Constructs a new @c %Camera instance.
     *
     * @param parent If not 0, ownership of the constructed object will be
     * transferred to the parent.
     *
     * @since BlackBerry 10.0.0
     */
    explicit Camera(Container *parent = 0);

    /*!
     * @brief Destroys this @c %Camera.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~Camera();

    /*!
     * @brief Gets the active camera unit.
     *
     * @details The active camera unit might be one of several cameras on the device,
     * such as the front-facing camera or rear-facing camera.
     *
     * @return The active camera unit.
     *
     * @since BlackBerry 10.0.0
     */
    bb::cascades::multimedia::CameraUnit::Type cameraUnit() const;

    /*!
     * @brief Determines if the desired camera is accessible.
     *
     * @param unit The camera unit to be opened (for example, the front-facing camera or
     *        rear-facing camera). The default value for this parameter is @c CameraUnit::Rear.
     *
     * @return @c true if the specified camera is accessible, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE bool isCameraAccessible(bb::cascades::multimedia::CameraUnit::Type unit = bb::cascades::multimedia::CameraUnit::Rear) const;

    /*!
     * @brief Determines if the device cameras are fully accessible.
     *
     * @return @c true if one or more cameras are present and accessible to the calling application,
     *         @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool allCamerasAccessible() const;

    /*!
     * @brief Powers up the camera sensor.
     *
     * @details This function asynchronously opens the camera. The camera must be opened before calling
     *          any function that interacts with it. Only one camera unit can be open at a time. The
     *          @c cameraOpened() signal is emitted if the camera is successfully opened, and the
     *          @c cameraOpenFailed() signal is emitted otherwise.
     *
     * @param unit The camera unit (for example, the front-facing camera or rear-facing camera) to be opened.
     *        The default value for this parameter is @c CameraUnit::Rear.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void open(bb::cascades::multimedia::CameraUnit::Type unit = bb::cascades::multimedia::CameraUnit::Rear);

    /*!
     * @brief Powers down the camera sensor.
     *
     * @details This function asynchronously closes the camera session. The @c cameraClosed() signal is
     *          emitted if the camera is successfully closed, and the @c cameraCloseFailed() signal is
     *          emitted otherwise.
     *
     *          In response to the @c bb::Application::asleep() signal, this function should be called in
     *          order to release camera resources that may be needed by other applications. The @c open()
     *          function can be called upon receiving the @c bb::Application::awake() signal.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void close();

    /*!
     * @brief Starts the viewfinder.
     *
     * @details This function asynchronously starts the viewfinder and begins streaming preview frames to the screen.
     *          The @c viewfinderStarted() signal is emitted if the viewfinder is successfully started, and the @c
     *          viewfinderStartFailed() signal is emitted otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void startViewfinder();

    /*!
     * @brief Stops the viewfinder.
     *
     * @details This function asynchronously stops the viewfinder. The @c viewfinderStopped() signal is emitted if the
     *          viewfinder is successfully stopped, and the @c viewfinderStopFailed() signal is emitted otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void stopViewfinder();

    /*!
     * @brief Captures an image when in photo mode.
     *
     * @details This function asynchronously captures a photo when the camera is in photo mode. The @c photoCaptured()
     *          signal is emitted if the capture is successful, and the @c photoCaptureFailed() signal is emitted otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void capturePhoto();

    /*!
     * @brief Starts video capture when in video mode.
     *
     * @details This function asynchronously starts the video recording process. The @c videoCaptureStarted() signal is emitted
     *          when the video capture process has been successfully started, and the @c videoCaptureFailed() signal
     *          is emitted otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void startVideoCapture();

    /*!
     * @brief Stops video capture.
     *
     * @details This function asynchronously stops the video recording process. The @c videoCaptureStopped() signal is emitted
     *          if the video recording process is successfully stopped, and the @c videoCaptureFailed() signal is emitted otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void stopVideoCapture();

    /*!
     * @brief Gets the camera settings for the current mode.
     *
     * @details This function populates the specified @c CameraSettings parameter with the settings
     *          for the currently selected mode. If a mode has not been selected, @c CameraModePhoto
     *          is assumed.
     *
     * @param settings A reference to the @c %CameraSettings object to populate.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void getSettings(CameraSettings *settings) const;

    /*!
     * @brief Applies the supplied settings to the camera.
     *
     * @details This function applies settings values that are supported by the current camera and mode.
     *          Settings can be confirmed by comparing the passed values to those returned by a subsequent
     *          call to @c getSettings(). The viewfinder is restarted as required.
     *          If settings are applied when the viewfinder is not running then the settings are not
     *          validated as a result of calling this method. Instead validation will occur on a subsequent
     *          call to @c startViewfinder.
     *
     * @param settings A reference to the @c CameraSettings object that contains the settings to
     *        apply.
     *
     * @return @c true if all settings were successfully applied, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT bool applySettings(CameraSettings *settings);

    /*!
     * @brief Gets the maximum zoom level supported by the open camera.
     *
     * @details The maximum zoom level is returned only if the camera is open.
     *
     * @return The maximum zoom level if the camera is open, and 0 otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    unsigned int maxZoomLevel() const;

    /*!
     * @brief Gets the orientation of the preview frames returned by the @c previewFrameAvailable() signal.
     *
     * @details The preview frame orientation is a counter-clockwise offset from the upright position of
     *          the device. For example, a @c bb::cascades::DisplayDirection::West orientation means that
     *          the image would need to be rotated 270 degrees clockwise to reach the correct orientation.
     *          Note that, in order to orient the image correctly, the current device orientation will need
     *          to be taken into account.
     *
     * @return The preview frame orientation.
     *
     * @since BlackBerry 10.0.0
     */
    bb::cascades::DisplayDirection::Type devicePreviewFrameDirection() const;

    /*!
     * @brief Gets the supported capture resolutions for the current camera mode.
     *
     * @details Valid resolutions are returned only when the camera is open.
     *
     * @param mode The camera mode.
     *
     * @return An ordered list of supported capture resolutions.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE QVariantList supportedCaptureResolutions(bb::cascades::multimedia::CameraMode::Type mode) const;

    /*!
     * @brief Gets the supported cameras on the device (for example, the front-facing camera
     *        or rear-facing camera).
     *
     * @return A list of supported cameras.
     *
     * @since BlackBerry 10.0.0
     */
    QList<bb::cascades::multimedia::CameraUnit::Type> supportedCameras() const;

    /*!
     * @brief Gets the size, in bytes, of a viewfinder frame buffer based on the current viewfinder resolution.
     *
     * @return The preview buffer size required by the camera buffer pool, or 0 if the camera is closed.
     *
     * @since BlackBerry 10.0.0
     */
    quint64 previewBufferSize();

    /*!
     * @brief Adds a buffer, provided by the application, to the viewfinder frame buffer pool.
     *
     * @details This function copies a viewfinder frame, when available, into the buffer that's specified
     *          by the @c previewBuffer parameter, and delivers a pointer to the filled buffer using the
     *          @c previewFrameAvailable() signal. A maximum of 16 buffers can be added to the preview buffer
     *          pool.
     *
     * @param previewBuffer The buffer to add to the buffer pool.
     * @param previewBufferSize The size of the buffer.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void addPreviewBuffer(const QSharedPointer<unsigned char> &previewBuffer, quint64 previewBufferSize);

Q_SIGNALS:

	/*!
	 * @brief Emitted when the camera unit changes.
     *
     * @param unit The new camera unit.
	 *
	 * @since BlackBerry 10.0.0
	 */
	void cameraUnitChanged(bb::cascades::multimedia::CameraUnit::Type unit);

	/*!
	 * @brief Emitted when the camera has been opened.
	 *
	 * @since BlackBerry 10.0.0
	 */
	void cameraOpened();

	/*!
	 * @brief Emitted when the camera was not opened successfully.
	 *
	 * @param error The error code indicating why the operation failed.
	 *
	 * @since BlackBerry 10.0.0
	 */
	void cameraOpenFailed(bb::cascades::multimedia::CameraError::Type error);

	/*!
	 * @brief Emitted when the camera has been closed.
	 *
	 * @since BlackBerry 10.0.0
	 */
	void cameraClosed();

	/*!
	 * @brief Emitted when the camera was not closed successfully.
	 *
	 * @param error The error code indicating why the operation failed.
	 *
	 * @since BlackBerry 10.0.0
	 */
	void cameraCloseFailed(bb::cascades::multimedia::CameraError::Type error);

    /*!
     * @brief Emitted when the viewfinder is started.
     *
     * @since BlackBerry 10.0.0
     */
    void viewfinderStarted();

    /*!
     * @brief Emitted when the viewfinder was not started successfully.
     *
     * @param error The error code indicating why the operation failed.
     *
     * @since BlackBerry 10.0.0
     */
    void viewfinderStartFailed(bb::cascades::multimedia::CameraError::Type error);

    /*!
     * @brief Emitted when the viewfinder is stopped.
     *
     * @since BlackBerry 10.0.0
     */
    void viewfinderStopped();

    /*!
     * @brief Emitted when the viewfinder was not stopped successfully.
     *
     * @param error The error code indicating why the operation failed.
     *
     * @since BlackBerry 10.0.0
     */
    void viewfinderStopFailed(bb::cascades::multimedia::CameraError::Type error);

    /*!
     * @brief Emitted when the shutter has been fired (for example, when taking a photo).
     *
     * @since BlackBerry 10.0.0
     */
    void shutterFired();

    /*!
     * @brief Emitted when a photo has been successfully captured.
     *
     * @since BlackBerry 10.0.0
     */
    void photoCaptured();

    /*!
     * @brief Emitted when an attempt to capture a photo has failed.
     *
     * @param error The error code indicating why the operation failed.
     *
     * @since BlackBerry 10.0.0
     */
    void photoCaptureFailed(bb::cascades::multimedia::CameraError::Type error);

    /*!
     * @brief Emitted when a photo has been successfully saved.
     *
     * @param fileName The file name of the saved picture.
     * @param length The length of the picture data array.
     *
     * @since BlackBerry 10.0.0
     */
    void photoSaved(const QString &fileName, quint64 length);

    /*!
     * @brief Emitted when an attempt to save a photo has failed.
     *
     * @param error The error code indicating why the operation failed.
     *
     * @since BlackBerry 10.0.0
     */
    void photoSaveFailed(bb::cascades::multimedia::CameraError::Type error);

    /*!
     * @brief Emitted to indicate that a viewfinder preview frame, in NV12 format, is available and
     *        provides a pointer to that preview frame.
     *
     * @details This signal is emitted when the camera mode is set to @c CameraMode::Photo and at least one
     *          buffer has been added to the camera buffer pool before starting the viewfinder. The client app is
     *          responsible for ensuring that preview buffers are available in the camera buffer pool. Viewfinder
     *          frames are only made available to the client app through this signal when they are present in the
     *          camera buffer pool. The @c addPreviewBuffer() function adds preview buffers to the camera buffer pool.
     *          A call to @c stopViewfinder() empties the camera buffer pool, releasing all buffer references.
     *
     *          The orientation of the frame is device-dependent. Use @c devicePreviewFrameDirection() to determine the
     *          orientation of the frame.
     *
     * @param previewBuffer The buffer, provided by the application, into which the preview frame data
     *                      has been copied. Data is in NV12 format.
     * @param size The size of the buffer.
     * @param width The width of the preview image, in pixels.
     * @param height The height of the preview image, in pixels.
     * @param stride The preview image stride.
     *
     * @since BlackBerry 10.0.0
     */
    void previewFrameAvailable(bb::cascades::multimedia::SharedUCharPointer previewBuffer, quint64 size,
                                unsigned int width, unsigned int height, unsigned int stride);

    /*!
     * @brief Emitted to indicate that the review image is ready, and provides a pointer to the image data.
     *
     * @param imgSize The size of the image.
     * @param imgData The review image.
     *
     * @since BlackBerry 10.0.0
     */
    void reviewImageReady(const QSize &imgSize, const QByteArray &imgData);

    /*!
     * @brief Emitted when the video capture starts.
     *
     * @since BlackBerry 10.0.0
     */
    void videoCaptureStarted();

    /*!
     * @brief Emitted when video capture fails.
     *
     * @param error The error code indicating why the operation failed.
     *
     * @since BlackBerry 10.0.0
     */
    void videoCaptureFailed(bb::cascades::multimedia::CameraError::Type error);

    /*!
     * @brief Emitted when the video capture is stopped.
     *
     * @param fileName The file name of the saved video.
     *
     * @since BlackBerry 10.0.0
     */
    void videoCaptureStopped(const QString &fileName);

    /*!
     * @brief Emitted when all camera resources have been released.
     *
     * @details This signal is emitted when the viewfinder has been stopped or is unavailable.
     *          This can occur when resources are taken by another foreground application.
     *          The camera needs to be restarted when regaining foreground or when the
     *          @c cameraResourceAvailable() signal is emitted.
     *
     * @since BlackBerry 10.0.0
     */
    void cameraResourceReleased();

    /*!
     * @brief Emitted when the camera resource is available again.
     *
     * @details This signal indicates that the viewfinder is ready to be started. It will be emitted only if the
     *          @c cameraResourceReleased() signal was previously emitted, and the camera is once again available for use.
     *
     * @since BlackBerry 10.1.0
     */
    void cameraResourceAvailable();

    /*!
     * @brief Emitted when the state of focus operations has changed.
     *
     * @param state The new focus state.
     *
     * @since BlackBerry 10.0.0
     */
    void focusStateChanged(bb::cascades::multimedia::CameraFocusState::Type state);

private:

    QVariantList supportedCamerasQML() const;

    QScopedPointer<CameraPrivate> const d_ptr;
    Q_DECLARE_PRIVATE(Camera);
    Q_DISABLE_COPY(Camera);
};

} /*! namespace multimedia */
} /*! namespace cascades */
} /*! namespace bb */

QML_DECLARE_TYPE(bb::cascades::multimedia::Camera)
QML_DECLARE_TYPE(bb::cascades::multimedia::SharedUCharPointer)

#endif /* header guard */
