/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CASCADES_MULTIMEDIA_BARCODEDETECTORVISUALS_HPP
#define BB_CASCADES_MULTIMEDIA_BARCODEDETECTORVISUALS_HPP

#include <bb/cascades/multimedia/Global>
#include <bb/cascades/CustomControl>
#include <bb/cascades/Container>
#include <bb/cascades/multimedia/BarcodeDetector>
#include <bb/cascades/multimedia/BarcodeFormat>

#include <QtDeclarative>
#include <QObject>

namespace bb
{
namespace cascades
{
namespace multimedia
{

class BarcodeDetectorVisualsPrivate;

/*!
 * @headerfile BarcodeDetectorVisuals.hpp <bb/cascades/multimedia/BarcodeDetectorVisuals>
 *
 * @brief Provides visual feedback during barcode detection.
 *
 * @details This control provides visual indicators showing where the barcode detector is finding possible
 * barcode registration marks in the field of view.  To use this control, simply position it directly on top of the
 * @c bb::cascades::multimedia::Camera control being used as the viewfinder and assign the @c barcodeDetector
 * property to a @c bb::cascades::multimedia::BarcodeDetector instance.
 *
 * Example usage:
 * @snippet libbbcascadesmultimedia/BarcodeDetectorVisuals_example.qml Declaring BarcodeDetectorVisuals
 * @link libbbcascadesmultimedia/BarcodeDetectorVisuals_example.qml
 * See full example
 * @endlink
 *
 * @note When using the @c %BarcodeDetectorVisuals class, the @c detected() signal in this class should be monitored
 * instead of the @c detected() signal in the @c BarcodeDetector class.  This will give the @c %BarcodeDetectorVisuals the
 * time necessary to complete all visual animations prior to emitting the @c detected() signal.
 *
 * @note Using this object requires your application to have the following named assets:
 * - images/bb_cascades_multimedia_barcodedetectorvisuals_target_box.png
 * - images/bb_cascades_multimedia_barcodedetectorvisuals_target_box.amd
 * - images/bb_cascades_multimedia_barcodedetectorvisuals_detected_box.png
 * - images/bb_cascades_multimedia_barcodedetectorvisuals_detected_box.amd
 *
 * These assets will be used by the visuals for the indicators.  If these are not supplied, you will have no visual
 * feedback during the detection process.
 *
 * @see bb::cascades::Image
 *
 * @xmlonly
 * <apigrouping group="Multimedia/Barcodes"/>
 * <library name="bbcascadesmultimedia"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_CASCADES_MULTIMEDIA_EXPORT BarcodeDetectorVisuals : public CustomControl
{
    Q_OBJECT

    /*!
     * @brief The barcode detector to monitor.
     *
     * @details The @c %BarcodeDetectorVisuals class requires an instance of a @c bb::cascades::multimedia::BarcodeDetector
     * to provide the visual feedback from.  An instance must be assigned to this property.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::cascades::multimedia::BarcodeDetector *barcodeDetector READ barcodeDetector WRITE setBarcodeDetector FINAL);

public:

    /*!
     * @brief Creates an instance of the @c %BarcodeDetectorVisuals class.
     *
     * @param parent If not 0, ownership of the constructed object will be
     * transferred to the parent.
     *
     * @since BlackBerry 10.0.0
     */
    explicit BarcodeDetectorVisuals(Container *parent = 0);

    /*!
     * @brief Destroys this @c %BarcodeDetectorVisuals.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~BarcodeDetectorVisuals();

    /*!
     * @brief Returns the attached barcode detector.
     *
     * @note The @c BarcodeDetector pointer that's returned maintains its original ownership.  The @c %BarcodeDetectorVisuals
     * does not take ownership or modify ownership of this object in any way.  It is the implementor's responsibility
     * to ensure the @c barcodeDetector instance is valid for the lifetime of the @c %BarcodeDetectorVisuals.
     *
     * @return The @c bb::cascades::multimedia::BarcodeDetector instance that this object is attached to.
     *
     * @since BlackBerry 10.0.0
     */
    bb::cascades::multimedia::BarcodeDetector *barcodeDetector() const;

    /*!
     * @brief Sets the barcode detector to use.
     *
     * @note The @c BarcodeDetector pointer that's supplied maintains its original ownership.  The @c %BarcodeDetectorVisuals
     * does not take ownership or modify ownership of this object in any way.  It is the implementor's responsibility
     * to ensure the @c barcodeDetector instance is valid for the lifetime of the @c %BarcodeDetectorVisuals.
     *
     * @param barcodeDetector The instance of the @c bb::cascades::multimedia::BarcodeDetector that this object
     * will monitor to provide visual feedback.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setBarcodeDetector( bb::cascades::multimedia::BarcodeDetector *barcodeDetector );

Q_SIGNALS:
    /*!
     * @brief Emitted when a barcode is detected.
     *
     * @note When using the @c %BarcodeDetectorVisuals, this signal should be monitored instead of the
     * @c detected() signal in @c BarcodeDetector.  The signal is identical and will be emitted after all
     * visual animations have completed.
     *
     * @param data The barcode data.
     * @param format The format of the barcode that was detected.
     *
     * @since BlackBerry 10.0.0
     */
    void detected(const QString &data, bb::cascades::multimedia::BarcodeFormat::Type format);

protected:
//! @cond PRIVATE
    Q_SIGNAL void detected(const QString &data, int format);
//! @endcond

private:
//! @cond PRIVATE
    QScopedPointer<BarcodeDetectorVisualsPrivate> const d_ptr;
    Q_DECLARE_PRIVATE(BarcodeDetectorVisuals);
    Q_DISABLE_COPY(BarcodeDetectorVisuals);
//! @endcond
};
/*!
 * @example libbbcascadesmultimedia/BarcodeDetectorVisuals_example.qml
 * Example use in QML
 */

} // namespace multimedia
} // namespace cascades
} // namespace bb

QML_DECLARE_TYPE(bb::cascades::multimedia::BarcodeDetectorVisuals)

#endif // BB_CASCADES_MULTIMEDIA_BARCODEDETECTORVISUALS_HPP
