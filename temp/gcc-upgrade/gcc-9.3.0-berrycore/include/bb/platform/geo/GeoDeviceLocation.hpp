/**
 * @copyright
 * Copyright BlackBerry Limited, 2013-2014
 * BlackBerry Limited. All rights reserved.
 */
#ifndef BB_PLATFORM_GEO_GEODEVICELOCATION_HPP
#define BB_PLATFORM_GEO_GEODEVICELOCATION_HPP

#include <bb/platform/geo/Global>
#include <bb/platform/geo/Geographic>
#include <bb/platform/geo/Point>
#include <bb/platform/geo/Marker>

#include <QDebug>

namespace bb
{
namespace platform
{
namespace geo
{
class GeoDeviceLocationPrivate;

/**
 * @headerfile GeoDeviceLocation.hpp <bb/platform/geo/GeoDeviceLocation>
 *
 * @brief A point in geographic space that represents the device's
 * current latitude and longitude coordinates.
 *
 * @details
 *
 * @section sec_markers_overview Markers
 *
 * The @c GeoDeviceLocation class uses @c Markers to indicate the device's
 * current location on the map. It has two @c Marker properties, one used
 * when the device has a valid heading, the other used when the device
 * doesn't have a valid heading. Only one marker property is displayed at a
 * time, depending on the @c #headingValid property.
 *
 * If no markers are provided, default ones will be used. (The defaults can
 * be restored using the @c reset* operations.)
 *
 * @subsection sec_directional_doc Directional Device Marker
 *
 * The @c #deviceDirectionalMarker property is the @c Marker that is used
 * to visually represent the device's location on a map when the direction
 * of the device is known.
 *
 * The icon for the marker is expected to point North initially, and is
 * rotated in accordance with the device's heading.  For example, if the @c
 * #heading is 90 degrees, then the icon is rotated a quarter turn to the
 * right. The icon is rotated around the marker's "location coordinate"
 * attribute (@c Marker::locationCoordinate()).
 *
 * @subsection sec_directionless_doc Directionless Device Marker
 *
 * The @c #deviceDirectionlessMarker property is the @c Marker that is used
 * to visually represent the device's location on a map when the direction
 * of the device is not known.
 *
 * This marker is not rotated since it does not represent directionality.
 *
 * @xmlonly
 * <apigrouping group="Location/Geographic elements"/>
 * <library name="bbcascadesmaps"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_PLATFORM_GEO_EXPORT GeoDeviceLocation : public
    bb::platform::geo::Geographic
{
    Q_OBJECT

    /**
     * @brief The location of the device.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(
        bb::platform::geo::Point point
        READ point
        NOTIFY pointChanged
        FINAL )

    /**
     * @brief The direction the device is heading, in degrees from
     * true North.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(
        double heading
        READ heading
        NOTIFY headingChanged
        FINAL )

    /**
     * @brief The validity of the @c #heading property.
     *
     * The @c heading property can be invalid while the @c GeoDeviceLocation is valid
     * in the case where the device is not moving.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(
        bool headingValid
        READ isHeadingValid
        NOTIFY headingValidityChanged
        FINAL )

    /**
     * @brief The speed the device is traveling at, in meters/second.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(
        float speed
        READ speed
        NOTIFY speedChanged
        FINAL )

    /**
     * @brief The accuracy of the device's location, in meters, or a value less than
     * @c 0 if the location is not valid.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(
        float pointAccuracy
        READ pointAccuracy
        NOTIFY pointAccuracyChanged
        FINAL )

    /**
     * @brief The marker used to represent this device's location when
     * the heading of the device is invalid.
     *
     * @details See @ref sec_directionless_doc for more information.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(
        bb::platform::geo::Marker deviceDirectionlessMarker
        READ deviceDirectionlessMarker
        WRITE setDeviceDirectionlessMarker
        RESET resetDeviceDirectionlessMarker
        NOTIFY deviceDirectionlessMarkerChanged
        FINAL )

    /**
     * @brief The marker used to represent this location when it
     * has a valid heading.
     *
     * @details See @ref sec_directional_doc for more information.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(
        bb::platform::geo::Marker deviceDirectionalMarker
        READ deviceDirectionalMarker
        WRITE setDeviceDirectionalMarker
        RESET resetDeviceDirectionalMarker
        NOTIFY deviceDirectionalMarkerChanged
        FINAL )

    /**
     * @brief The validity of the device's location. The device has a valid
     * location when it has received a location update from a location source.
     *
     * @since BlackBerry 10.3.0
     */
    Q_PROPERTY(
        bool valid
        READ isValid
        NOTIFY validChanged
        REVISION 2
        FINAL )

public:

    /**
     * @brief Creates an instance of GeoDeviceLocation.
     *
     * @param parent The @c QObject parent of this object.
     * @since BlackBerry 10.2.0
     */
    explicit GeoDeviceLocation( QObject* parent = 0 );

    /**
     * @brief Creates an instance of @c GeoDeviceLocation.
     *
     * @param id The identifier for this @c Geographic. It is up
     * to the caller to ensure the uniqueness of @c Geographic IDs.
     * @param parent The @c QObject parent of this object.
     * @since BlackBerry 10.2.0
     */
    explicit GeoDeviceLocation( const QString& id, QObject* parent = 0 );

    /**
     * @brief Destructor
     *
     * @since BlackBerry 10.2.0
     */
    virtual ~GeoDeviceLocation();

    /**
     * @brief Retrieves the point.
     *
     * @since BlackBerry 10.2.0
     */
    bb::platform::geo::Point point() const;

    /**
     * @brief Retrieves the bearing to true north from the direction of
     * travel, in degrees.
     *
     * This property is undefined if @c #headingValid is @c false.
     *
     * @return The device's bearing.
     *
     * @since BlackBerry 10.2.0
     */
    double heading() const;

    /**
     * @brief Determines if the @c #heading property contains valid
     * information.
     *
     * @return @c true if the @c #heading property contains valid
     * information, @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool isHeadingValid() const;

    /**
     * @brief Retrieves the ground speed, in meters/sec.
     *
     * @return The ground speed.
     *
     * @since BlackBerry 10.2.0
     */
    float speed() const;

    /**
     * @brief Retrieves the accuracy of the provided latitude-longitude
     * values, in meters.
     *
     * @return The accuracy.
     *
     * @since BlackBerry 10.2.0
     */
    float pointAccuracy() const;

    /**
     * @brief Retrieves the marker used to indicate this location when
     * the device's heading is invalid.
     *
     * @details See @ref sec_directionless_doc for more information.
     *
     * @return The device's marker when the heading is invalid.
     * @since BlackBerry 10.2.0
     */
    bb::platform::geo::Marker deviceDirectionlessMarker() const;

    /**
     * @brief Sets the marker used to indicate this location when
     * the device's heading is invalid.
     *
     * @details See @ref sec_directionless_doc for more information.
     *
     * @param marker The new marker.
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setDeviceDirectionlessMarker(
        const bb::platform::geo::Marker& marker );

    /**
     * @brief Resets the directionless marker to the default icon.
     *
     * @details See @ref sec_directionless_doc for more information.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetDeviceDirectionlessMarker();

    /**
     * @brief Retrieves the marker used to indicate this location when
     * the device's heading is valid.
     *
     * @details See @ref sec_directional_doc for more information.
     *
     * @return The device's marker when the heading is valid.
     * @since BlackBerry 10.2.0
     */
    bb::platform::geo::Marker deviceDirectionalMarker() const;

    /**
     * @brief Sets the marker used to indicate this location when the
     * device's heading is valid.
     *
     * @details See @ref sec_directional_doc for more information.
     *
     * @param marker The new marker.
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setDeviceDirectionalMarker(
        const bb::platform::geo::Marker& marker );

    /**
     * @brief Resets the directional marker to the default icon.
     *
     * @details See @ref sec_directional_doc for more information.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetDeviceDirectionalMarker();

    /**
     * @brief Retrieves the validity of the device's location.
     *
     * @return @c true if the device's location is valid, @c false otherwise.
     *
     * @since BlackBerry 10.3.0
     */
    bool isValid() const;

Q_SIGNALS:
    /**
     * @brief Emitted when the device's location has changed.
     * @param point The new location for the device.
     *
     * @since BlackBerry 10.2.0
     */
    void pointChanged( const bb::platform::geo::Point& point );

    /**
     * @brief Emitted when the device changes direction.
     * @param heading The new direction for the device.
     *
     * @since BlackBerry 10.2.0
     */
    void headingChanged( double heading );

    /**
     * @brief Emitted when the heading's validity property changes.
     *
     * @param headingValidity The new state of the heading's validity.
     *
     * @since BlackBerry 10.2.0
     */
    void headingValidityChanged( bool headingValidity );

    /**
     * @brief Emitted when the device's speed changes.
     * @param speed The device's new speed.
     *
     * @since BlackBerry 10.2.0
     */
    void speedChanged( float speed );

    /**
     * @brief Emitted when the accuracy of the device's location
     * changes.
     * @param accuracy The location's new accuracy.
     *
     * @since BlackBerry 10.2.0
     */
    void pointAccuracyChanged( float accuracy );

    /**
     * @brief Emitted when the directionless marker changes.
     *
     * @details See @ref sec_directionless_doc for more information.
     *
     * @param newMarker The new marker.
     * @since BlackBerry 10.2.0
     */
    void deviceDirectionlessMarkerChanged(
        const bb::platform::geo::Marker& newMarker );

    /**
     * @brief Emitted when the directional marker changes.
     *
     * @details See @ref sec_directional_doc for more information.
     *
     * @param newMarker The new marker.
     * @since BlackBerry 10.2.0
     */
    void deviceDirectionalMarkerChanged(
        const bb::platform::geo::Marker& newMarker );

    /**
     * @brief Emitted when the validity of the device's location changes.
     * @param valid @c true if the device's location has become valid, @c false
     * if the device's location has become invalid.
     *
     * @since BlackBerry 10.3.0
     */
    void validChanged( bool valid );

private:
    /** @cond PRIVATE */
    GeoDeviceLocationPrivate* d_ptr;
    Q_DISABLE_COPY( GeoDeviceLocation )
    Q_DECLARE_PRIVATE( GeoDeviceLocation )
    /** @endcond */
};

BB_PLATFORM_GEO_EXPORT QDebug operator<<( QDebug dbg,
        const GeoDeviceLocation* pt );

} // namespace geo
} // namespace platform
} // namespace bb
#endif // BB_PLATFORM_GEO_GEODEVICELOCATION_HPP
