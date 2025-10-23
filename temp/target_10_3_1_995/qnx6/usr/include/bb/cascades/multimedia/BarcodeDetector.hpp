/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CASCADES_MULTIMEDIA_BARCODEDETECTOR_HPP
#define BB_CASCADES_MULTIMEDIA_BARCODEDETECTOR_HPP

#include <bb/cascades/multimedia/BarcodeFormat>
#include <bb/cascades/multimedia/Camera>

#include <bb/Global>
#include <bb/cascades/multimedia/Global>

#include <QObject>
#include <QtDeclarative>
#include <QList>
#include <QPoint>

namespace bb
{

class ImageData; // forward declaration is all that is needed

namespace cascades
{
namespace multimedia
{

class BarcodeDetectorPrivate;

/*!
 * @headerfile BarcodeDetector.hpp <bb/cascades/multimedia/BarcodeDetector>
 *
 * @brief Allows detection of barcode codes.
 *
 * @details When attached to a @c Camera, this class will search for barcodes.
 * When a barcode is detected, the @c detected() signal is emitted.
 *
 * By default, @c %BarcodeDetector will search for QR codes.  It can be configured to search for
 * other barcode formats using the @c formats property.
 *
 * Barcodes can only be detected when the @c %Camera can provide preview frames.  This generally
 * means that the viewfinder must be active.
 *
 * In order to function correctly, there must be only one instance of @c %BarcodeDetector attached
 * to a @c %Camera instance, and that @c %Camera instance must not have any other consumers of its
 * preview frames.
 *
 * Example usage in QML
 * @include libbbcascadesmultimedia/BarcodeDetector_example.qml
 *
 * @xmlonly
 * <apigrouping group="Multimedia/Barcodes"/>
 * <library name="bbcascadesmultimedia"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_CASCADES_MULTIMEDIA_EXPORT BarcodeDetector : public QObject
{
    Q_OBJECT

    /*!
     * @brief The @c Camera to which this detector is attached.
     *
     * The detector can only be attached to one @c %Camera at once.  Attaching to a new @c %Camera
     * will detach the detector from the @c %Camera to which it was previously attached, if any.
     * Setting this property to NULL will cause the detector to be detached from the current @c %Camera,
     * if any.
     *
     * @c %BarcodeDetector will use @c CameraFocusMode::ContinuousAuto on the attached
     * @c %Camera.  This is done because the @c %BarcodeDetector is most effective on barcodes that
     * are in focus.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::cascades::multimedia::Camera *camera READ camera WRITE setCamera NOTIFY cameraChanged FINAL);

    /*!
     * @brief The barcode formats that this detector should look for.
     *
     * The detector can search for multiple formats at the same time.  When a barcode is detected, the @c BarcodeFormat
     * is included in the @c detected() signal.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::cascades::multimedia::BarcodeFormat::Types formats READ formats WRITE setFormats NOTIFY formatsChanged FINAL);

public:
    /*!
     * @brief Creates an instance of the @c %BarcodeDetector class.
     *
     * @param parent If not 0, the supplied parent will be responsible for deleting this instance.
     *
     * @since BlackBerry 10.0.0
     */
    explicit BarcodeDetector(QObject *parent = 0);

    /*!
     * @brief Destroys this @c %BarcodeDetector.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~BarcodeDetector();

    /*!
     * @brief Gets the @c Camera to which this detector is attached.
     *
     * @return The @c %Camera to which this detector is attached.
     *
     * @since BlackBerry 10.0.0
     */
    bb::cascades::multimedia::Camera *camera() const;

    /*!
     * @brief Attaches this detector to a @c Camera.
     *
     * The detector can only be attached to one @c %Camera at once, so calling this function will
     * detach the detector from the @c %Camera to which it was previously attached, if any.
     * Passing NULL will cause the detector to be detached from the current @c %Camera, if any.
     *
     * @c %BarcodeDetector will use @c CameraFocusMode::ContinuousAuto on the attached
     * @c %Camera.  This is done because the @c %BarcodeDetector is most effective on barcodes that
     * are in focus.
     *
     * @param camera The @c %Camera to attach this detector to.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setCamera(bb::cascades::multimedia::Camera *camera);

    /*!
     * @brief Gets the barcode formats that this detector is looking for.
     *
     * @return The barcode formats that this detector is looking for.
     *
     * @since BlackBerry 10.0.0
     */
    bb::cascades::multimedia::BarcodeFormat::Types formats() const;

    /*!
     * @brief Sets the barcode formats that this detector should look for.
     *
     * The detector can search for multiple formats at the same time.  When a barcode is detected, the @c BarcodeFormat
     * is included in the @c detected() signal.
     *
     * @param formats The barcodes formats that this detector should look for.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setFormats(bb::cascades::multimedia::BarcodeFormat::Types formats);

    /*!
     * @brief Looks for a barcode within a given @c Image.
     *
     * Independent of the camera-based detection, you can search for barcodes in any image.
     * This function searches for the same set of barcode formats as are set using @c setFormats().
     *
     * @param image The image containing a barcode.
     * @param foundFormat An optional output parameter. If not null, then on successful detection @c foundFormat
     * is set to the type of barcode found.  Otherwise, it is left unchanged.
     *
     * @return The barcode data, or an empty string if no barcode was detected.
     *
     * @since BlackBerry 10.0.0
     */
    QString scanImage(bb::ImageData const & image, bb::cascades::multimedia::BarcodeFormat::Type * foundFormat = 0) const;

Q_SIGNALS:
//! @cond PRIVATE
    /*!
     * @brief Emitted when a barcode is detected.
     *
     * Barcodes can only be detected when the @c Camera can provide preview frames.  This generally
     * means that the viewfinder must be active.
     *
     * @param data The barcode data.
     * @param format The format of the barcode that was detected.
     */
    void barcodeDetected(const QString &data, BarcodeFormat::Type format) BB_DEPRECATED;
//! @endcond

    /*!
     * @brief Emitted when a barcode is detected.
     *
     * Barcodes can only be detected when the @c Camera can provide preview frames.  This generally
     * means that the viewfinder must be active.
     *
     * @param data The barcode data.
     * @param format The format of the barcode that was detected.
     *
     * @since BlackBerry 10.0.0
     */
    void detected(const QString &data, bb::cascades::multimedia::BarcodeFormat::Type format);

    /*!
     * @brief Emitted when a new @c Camera is attached or when this detector is detached from the
     * current @c Camera.
     *
     * @param camera The new camera for this object.
     *
     * @since BlackBerry 10.0.0
     */
    void cameraChanged(bb::cascades::multimedia::Camera *camera);

    /*!
     * @brief Emitted when the @c formats property changes.
     *
     * @param newFormats The new value of the @c formats property.
     *
     * @since BlackBerry 10.0.0
     */
    void formatsChanged(bb::cascades::multimedia::BarcodeFormat::Types newFormats);

    /*!
     * @brief Emitted when a potential registration mark has been detected in the scanned image.
     *
     * @param position The point at which the mark is located, scaled to the dimensions of the
     * @c Camera viewfinder used by the attached @c %BarcodeDetector.
     *
     * @since BlackBerry 10.0.0
     */
    void potentialRegistrationMarkDetected( const QPoint &position );

    /*!
     * @brief Emitted when registration marks have been detected.
     *
     * @details The list of points are the detected registration marks of the detected barcode.
     *
     * @param positions The list of points defining the registration marks of the detected barcode.
     *
     * @since BlackBerry 10.0.0
     */
    void registrationMarksDetected( const QList<QPoint> &positions );

    /*!
     * @brief Emitted at the start of scanning an image, or a camera frame, when looking for a barcode.
     *
     * @details This signal will always be emitted before the @c detected() signal can be emitted.
     *
     * @note The order of events, per frame, is:
     * - @c scanStarted()
     * - @c potentialRegistrationMarkDetected() (N times)
     * - @c scanCompleted()
     * - @c registrationMarksDetected() (only once, and only if a barcode is detected)
     * - @c detected() (only once, and only if a barcode is detected)
     *
     * @since BlackBerry 10.0.0
     */
    void scanStarted();

    /*!
     * @brief Emitted when the scan of an image, or a camera frame, is completed when looking for a barcode.
     *
     * @details This signal will always be emitted before the @c detected() signal can be emitted.
     *
     * @note The order of events, per frame, is:
     * - @c scanStarted()
     * - @c potentialRegistrationMarkDetected() (N times)
     * - @c scanCompleted()
     * - @c registrationMarksDetected() (only once, and only if a barcode is detected)
     * - @c detected() (only once, and only if a barcode is detected)
     *
     * @since BlackBerry 10.0.0
     */
    void scanCompleted();

protected:
//! @cond PRIVATE
    Q_SIGNAL void potentialRegistrationMarkDetected( const QVariant &position );

    Q_SIGNAL void registrationMarksDetected( const QVariant &positions );

    Q_SIGNAL void detected(const QString &data, int format);

    Q_SIGNAL void formatsChanged( int newFormats);
//! @endcond

private:
//! @cond PRIVATE
    Q_SIGNAL void barcodeDetected(const QString &data, int format) BB_DEPRECATED;
    Q_DISABLE_COPY(BarcodeDetector);
    Q_DECLARE_PRIVATE(BarcodeDetector);
    BarcodeDetectorPrivate * const d_ptr;
//! @endcond
};

} // namespace multimedia
} // namespace cascades
} // namespace bb

QML_DECLARE_TYPE(bb::cascades::multimedia::BarcodeDetector);
#endif /* header guard */
