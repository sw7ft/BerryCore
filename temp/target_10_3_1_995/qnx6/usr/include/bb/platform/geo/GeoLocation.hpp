/**
 * @copyright
 * Copyright BlackBerry Limited, 2012-2014
 * BlackBerry Limited. All rights reserved.
 */
#ifndef BB_PLATFORM_GEO_GEOLOCATION_HPP
#define BB_PLATFORM_GEO_GEOLOCATION_HPP

#include <bb/Global>
#include <bb/platform/geo/Global>
#include <bb/platform/geo/Geographic>
#include <bb/platform/geo/Point>
#include <bb/platform/geo/Marker>

#include <QScopedPointer>
#include <QDebug>

namespace bb
{
namespace platform
{
namespace geo
{

class GeoLocationPrivate;

/**
 * @headerfile GeoLocation.hpp <bb/platform/geo/GeoLocation>
 *
 * @brief A location in geographic space that represents a latitude and
 * longitude coordinate, and is visually represented on the map using its
 * @c Marker attribute.
 *
 * @note See @c Geographic for information on object ownership and
 * reference types.
 *
 * @xmlonly
 * <apigrouping group="Location/Geographic elements"/>
 * <library name="bbcascadesmaps"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PLATFORM_GEO_EXPORT GeoLocation : public bb::platform::geo::Geographic
{
    Q_OBJECT

    /**
     * @brief The coordinates of this location.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY( bb::platform::geo::Point point READ point WRITE setPoint NOTIFY pointChanged FINAL )

    /**
     * @cond PRIVATE
     * @deprecated use the marker property instead
     */
    Q_PROPERTY( QString iconUri READ iconUri WRITE setIconUri NOTIFY iconUriChanged FINAL )
    /** @endcond */

    /**
     * @brief The marker used to indicate this location.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY( bb::platform::geo::Marker marker READ marker WRITE setMarker RESET resetMarker NOTIFY
                markerChanged FINAL )

    /**
     * @brief The radius of interest of the circle that represents this location.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( double radius READ radius WRITE setRadius NOTIFY radiusChanged REVISION 1 FINAL )

public:

    /**
     * @brief Creates an instance of @c GeoLocation.
     *
     * The resulting location defaults to that of a default
     * @c Point.
     *
     * @param id The identifier for this @c Geographic. It is up
     * to the caller to ensure the uniqueness of Geographic IDs.
     * @param parent The @c QObject parent of this object.
     *
     * @since BlackBerry 10.0.0
     */
    explicit GeoLocation( const QString& id, QObject* parent = 0 );

    /**
     * @brief Creates an instance of @c GeoLocation with the given
     * latitude and longitude.
     *
     * @param lat The latitude value (0 default).
     * @param lon The longitude value (0 default).
     * @param parent The @c QObject parent of this object.
     *
     * @since BlackBerry 10.0.0
     */
    explicit GeoLocation( double lat = 0, double lon = 0,
                          QObject* parent = 0 );

    /**
     * @brief Creates an instance of @c GeoLocation with the
     * information provided.
     *
     * @param id The identifier for this @c Geographic. It is up
     * to the caller to ensure the uniqueness of Geographic IDs.
     * @param name The name of this location.
     * @param location The location of this @c Point.
     * @param parent The @c QObject parent of this object.
     *
     * @since BlackBerry 10.0.0
     */
    GeoLocation( const QString& id, const QString& name,
                 const bb::platform::geo::Point& location,
                 QObject* parent = 0 );

    virtual ~GeoLocation();

    /**
     * @brief Retrieves all point-based attributes of this location.
     *
     * @return A @c Point version of this location.
     *
     * @since BlackBerry 10.0.0
     */
    bb::platform::geo::Point point() const;

    /**
     * @brief Sets all point-based attributes of this location.
     *
     * @return @c true if operation resulted in a change.
     *
     * @since BlackBerry 10.0.0
     */
    Q_REVISION( 2 )
    Q_SLOT bool setPoint( const bb::platform::geo::Point& point );

    /**
     * @brief Gets the altitude of this @c Point in meters.
     *
     * @since BlackBerry 10.0.0
     */
    double altitude() const;

    /**
     * @brief Sets the altitude of this @c Point in meters.
     *
     * @return @c true if the operation resulted in a change.
     *
     * @since BlackBerry 10.0.0
     */
    Q_REVISION( 2 )
    Q_SLOT bool setAltitude( double alt );

    /**
     * @brief Captures how the @c altitude attribute should be
     * interpreted.
     * The default value is @c AltitudeMode::RelativeToGround.
     *
     * @return How the altitude property should be
     * interpreted.
     *
     * @since BlackBerry 10.0.0
     */
    bb::platform::geo::AltitudeMode::Type altitudeMode() const;

    /**
     * @brief Sets the altitude mode.
     *
     * @copydoc bb::platform::geo::AltitudeMode::Type
     * @return @c true if the attribute changed.
     *
     * @since BlackBerry 10.0.0
     */
    Q_REVISION( 2 )
    Q_SLOT bool setAltitudeMode( bb::platform::geo::AltitudeMode::Type mode );

    /**
     * @brief Gets the point's latitude in degrees.
     *
     * @since BlackBerry 10.0.0
     */
    double latitude() const;

    /**
     * @brief Sets the point's latitude in degrees.
     *
     * @return @c true if operation resulted in a change.
     *
     * @since BlackBerry 10.0.0
     */
    Q_REVISION( 2 )
    Q_SLOT bool setLatitude( double lat );

    /**
     * @brief Gets the point's longitude in degrees.
     *
     * @since BlackBerry 10.0.0
     */
    double longitude() const;

    /**
     * @brief Sets the point's longitude in degrees.
     *
     * @return @c true if operation resulted in a change.
     *
     * @since BlackBerry 10.0.0
     */
    Q_REVISION( 2 )
    Q_SLOT bool setLongitude( double lon );

    /**
     * @cond PRIVATE
     * @deprecated use marker() instead
     */
    QString iconUri() const BB_DEPRECATED;
    /** @endcond */

    /**
     * @cond PRIVATE
     * @deprecated use marker() instead
     */
    Q_SLOT void setIconUri( const QString& iconUri ) BB_DEPRECATED;
    /** @endcond */

    /**
     * @brief Retrieves the marker, or icon, used to indicate this location.
     *
     * @return The location's marker.
     * @since BlackBerry 10.0.0
     */
    bb::platform::geo::Marker marker() const;

    /**
     * @brief Sets the marker, or icon, used to indicate this location.
     *
     * @param marker The new marker.
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setMarker( const bb::platform::geo::Marker& marker );

    /**
     * @brief Resets the marker to the default icon, the blue pin.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void resetMarker();

    /**
     * @brief The radius of interest of this location.
     *
     * @return The radius of interest of this location.
     * @since BlackBerry 10.2.0
     */
    Q_REVISION( 1 )
    double radius() const;

    /**
     * @brief Sets the radius of interest of this location.
     *
     * @param newRadius The new radius value for this location.
     * @return @c true if this location's radius has changed.
     * @since BlackBerry 10.2.0
     */
    Q_REVISION( 1 )
    bool setRadius( double newRadius );

    /**
     * @brief Resets the radius of interest of this location to 0 meters.
     *
     * @since BlackBerry 10.2.0
     */
    Q_REVISION( 1 )
    Q_SLOT void resetRadius();

    virtual bb::platform::geo::BoundingBox boundingBox() const;

Q_SIGNALS:

    /**
     * @brief Emitted when the point of this location changes.
     *
     * @since BlackBerry 10.0.0
     */
    void pointChanged( const bb::platform::geo::Point& point );

    /** @cond PRIVATE */
    /**
     * @brief Emitted when the URI location of the resource icon
     * changes.
     */
    void iconUriChanged( const QString& iconUri );
    /** @endcond */

    /**
     * @brief Emitted when the marker changes.
     *
     * @since BlackBerry 10.0.0
     */
    void markerChanged( const bb::platform::geo::Marker& newMarker );

    /**
     * @brief Emitted when the radius of interest has changed
     *
     * @param newRadius The new radius of this location.
     * @since BlackBerry 10.2.0
     */
    Q_REVISION( 1 )
    void radiusChanged( double newRadius );

private:
    /** @cond PRIVATE */
    QScopedPointer<GeoLocationPrivate> d_ptr;
    Q_DISABLE_COPY( GeoLocation )
    Q_DECLARE_PRIVATE( GeoLocation )
    /** @endcond */

};

BB_PLATFORM_GEO_EXPORT QDebug operator<<( QDebug dbg, const GeoLocation* pt );

} // namespace geo
} // namespace platform
} // namespace bb
#endif // BB_PLATFORM_GEO_GEOLOCATION_HPP
