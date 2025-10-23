/**
 * @copyright
 * Copyright BlackBerry Limited, 2012-2014
 * BlackBerry Limited. All rights reserved.
 */
#ifndef BB_CASCADES_MAPS_MAPIMAGEGENERATOR_HPP
#define BB_CASCADES_MAPS_MAPIMAGEGENERATOR_HPP

#include <bb/ImageData>
#include <bb/cascades/maps/Global>
#include <bb/cascades/maps/ViewProperties>
#include <bb/cascades/maps/MapImageGeneratorError>
#include <bb/platform/geo/GeoList>

#include <QObject>

namespace bb
{
namespace cascades
{
namespace maps
{
class MapImageGeneratorPrivate;

/**
 * @headerfile MapImageGenerator.hpp <bb/cascades/maps/MapImageGenerator>
 *
 * @brief A generator which makes an asynchronous request for a map image.
 *
 * To generate a map image, construct an instance of this class with a
 * @c ViewProperties object with the map center coordinates and altitude,
 * set the window size to a @c QRect with the width and height for the image,
 * connect your slot to the @c finished() signal,
 * and then call @c start().
 *
 * The following example generates a 600px X 600px image of Waterloo, Ontario without
 * a pin in the center:
 *
 * @snippet libbbcascadesmaps/examples/MapImageGenerator/src/MapImageGeneratorExamples.cpp mapimagegeneratornopinrequest
 *
 * This example generates a 600px X 600px image of Waterloo, Ontario with
 * a pin in the center:
 *
 * @snippet libbbcascadesmaps/examples/MapImageGenerator/src/MapImageGeneratorExamples.cpp mapimagegeneratorwithpinrequest
 *
 * The @c finished() signal will be emitted when the image is available and
 * the @c ImageData can be obtained from it like so:
 *
 * @snippet libbbcascadesmaps/examples/MapImageGenerator/src/MapImageGeneratorExamples.cpp mapimagegeneratorslot
 *
 * @note Multiple static map images cannot be loaded simultaneously. If you
 * generate a map image of a location using @c MapImageGenerator, you must wait
 * until the image is loaded successfully before generating another image. If a
 * second request is made before the first request completes, the first request
 * is canceled. You can listen for the @c finished() signal to determine whether
 * the image is available.
 *
 * @xmlonly
 * <apigrouping group="Location/Maps and map visualization"/>
 * <library name="bbcascadesmaps"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_CASCADES_MAPS_EXPORT MapImageGenerator : public QObject
{
    Q_OBJECT

Q_SIGNALS:

    /**
     * @brief Emitted when the image is ready.
     *
     * @details The status of the operation can be determined by calling @c error() on this parameter.
     *
     * @param generator The map image generator used to make the request for a static map image.
     *
     * @since BlackBerry 10.0.0
     */
    void finished( bb::cascades::maps::MapImageGenerator* generator );

public:
    /**
     * @brief Constructor based on view.
     *
     * This constructor generates a map image based on a view.
     *
     * @param viewProperties The view to base the image upon.
     * @param parent The parent object of this object.
     *
     * @since BlackBerry 10.0.0
     */
    explicit MapImageGenerator(
        const bb::cascades::maps::ViewProperties& viewProperties,
        QObject* parent = 0 );

    /**
     * @brief Constructor based on view and mappable data.
     *
     * This constructor generates a map image based on a view and
     * mappable data.
     *
     * Currently the data in @c GeoList will not be included in the image.
     * If the @c GeoList contains at least one item, the image will contain
     * a pin in the center (if possible in the requested image dimensions).
     *
     * @param viewProperties The view to base the image upon.
     * @param data The data to include in the image.
     * @param parent The parent object of this object.
     *
     * @since BlackBerry 10.0.0
     */
    MapImageGenerator( const bb::cascades::maps::ViewProperties& viewProperties,
                       const bb::platform::geo::GeoList& data, QObject* parent = 0 );

    virtual ~MapImageGenerator();

    /**
     * @brief Starts the image generation process.
     *
     * @since BlackBerry 10.0.0
     */
    void start();

    /**
     * @brief Gets the image data. If @c bb::ImageData::isValid() returns
     * @c false, there was an error generating the image.
     *
     * @return The resulting image.
     *
     * @since BlackBerry 10.0.0
     */
    bb::ImageData imageData() const;


    /**
     * @brief Retrieves any error that might have occurred while trying to get a static map
     * by calling <code>start()</code>.
     *
     * @details See @c bb::cascades::maps::MapImageGeneratorError for a list of error codes.
     *
     * @return The error code.
     *
     * @since BlackBerry 10.2.0
     */
    bb::cascades::maps::MapImageGeneratorError::Type error() const;

    /**
     * @brief Sets the source of the underlying generator used to produce map images.
     *
     * @details The generator source name must be set before the @c start() method
     * is called. Changing the generator source name of a request that is in
     * progress will have no effect.
     *
     * The possible values for the source generator name are:
     * - @c "default", an empty string or @c QString::null.
     *   If one of these values is supplied, then the default search rules are used.
     * - @c "built-in".
     *   If this value is supplied, the built-in generator is used.
     * - @c The name of the shared library containing the generator plug-in to be used.
     *   If necessary, the appropriate extension for shared libraries will be added.
     *   If the library cannot be found then @c start() will not generate
     *   a map image.
     *
     * @note Setting the source does not affect the existing cached images on device.
     *
     * @param src The name of the source generator.
     *
     * @since BlackBerry 10.2.0
     */
    void setGeneratorSourceName( const QString& src );

    /**
     * @brief Retrieves the name of the image generator source.
     *
     * Prior to calling <code>start()</code>, this method returns the source name,
     * as set by <code>setGeneratorSourceName(const QString& src)</code>.
     * After <code>start()</code>, this method returns the source name actually used.
     * If a file name was specified but not found, this method returns @c QString::null.
     *
     * @return The generator source name.
     *
     * @since BlackBerry 10.2.0
     */
    QString generatorSourceName() const;

private:
    Q_DISABLE_COPY( MapImageGenerator )
    MapImageGeneratorPrivate* d_ptr;

};

} /* namespace maps */
} /* namespace cascades */
} /* namespace bb */

#endif /* BB_CASCADES_MAPS_MAPIMAGEGENERATOR_HPP */
