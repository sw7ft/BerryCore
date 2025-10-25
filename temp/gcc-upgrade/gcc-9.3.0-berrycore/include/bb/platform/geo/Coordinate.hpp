/**
 * @copyright
 * Copyright BlackBerry Limited, 2013-2014
 * BlackBerry Limited. All rights reserved.
 */
#ifndef BB_PLATFORM_GEO_COORDINATE_HPP
#define BB_PLATFORM_GEO_COORDINATE_HPP

#include <bb/platform/geo/Global>
#include <bb/platform/geo/BoundingBox>

#include <QSharedDataPointer>
#include <QDebug>

namespace bb
{
namespace platform
{
namespace geo
{
class CoordinatePrivate;

/**
 * @headerfile Coordinate.hpp <bb/platform/geo/Coordinate>
 *
 * @brief A @c Coordinate in geographic space that is represented by latitude,
 * longitude and altitude components.
 *
 * Validity
 * --------
 * A @c Coordinate is considered valid when all of its attributes are set.
 * If a @c Coordinate is invalid, its attributes are undefined.
 *
 * World Coordinate Reference
 * --------------------------
 * Coordinates are stated using the
 * [WGS84](http://en.wikipedia.org/wiki/WGS_84) reference coordinate system. A
 * @c Coordinate's altitude is interpreted based on context in which it is being
 * used, via @c AltitudeMode, as in various classes such as @c Point,
 * @c GeoLocation, @c GeoShape, etc.
 *
 * @xmlonly
 * <apigrouping group="Location/Geographic elements"/>
 * <library name="bbcascadesmaps"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_PLATFORM_GEO_EXPORT Coordinate
{
public:

    /**
     * @brief Creates an invalid @c Coordinate.
     *
     * @since BlackBerry 10.2.0
     */
    Coordinate();

    /**
     * @brief Creates a valid @c Coordinate instance.
     *
     * @param lat The latitude value.
     * @param lon The longitude value.
     * @param altitude The altitude value (0 default).
     *
     * @since BlackBerry 10.2.0
     */
    Coordinate( double lat, double lon, double altitude = 0 );

    /**
     * @brief Copy constructor.
     *
     * @param src The object from which to copy information.
     *
     * @since BlackBerry 10.2.0
     */
    Coordinate( const Coordinate& src );

    /**
     * @brief Destructor.
     *
     * @since BlackBerry 10.2.0
     */
    ~Coordinate();

    /**
     * @brief Assignment operator.
     *
     * @param src The object from which to copy information.
     *
     * @since BlackBerry 10.2.0
     */
    Coordinate& operator=( const Coordinate& src );

    /**
     * @brief Equality operator.
     *
     * @return @c true if all properties are equal.
     *
     * @since BlackBerry 10.2.0
     */
    bool operator==( const Coordinate& rhs ) const;

    /**
     * @brief Inequality operator.
     *
     * @return @c true if any property is not equal.
     *
     * @since BlackBerry 10.2.0
     */
    bool operator!=( const Coordinate& rhs ) const;

    /**
     * @brief Gets the altitude of this coordinate in meters.
     *
     * @since BlackBerry 10.2.0
     */
    double altitude() const;

    /**
     * @brief Sets the altitude of this coordinate in meters.
     *
     * @return @c true if the operation resulted in a change.
     *
     * @since BlackBerry 10.2.0
     */
    bool setAltitude( double alt );

    /**
     * @brief Retrieves the coordinate's latitude.
     *
     * @since BlackBerry 10.2.0
     */
    double latitude() const;

    /**
     * @brief Sets the coordinate's latitude.
     *
     * @return @c true if the operation resulted in a change.
     *
     * @since BlackBerry 10.2.0
     */
    bool setLatitude( double lat );

    /**
     * @brief Gets the coordinate's longitude.
     *
     * @since BlackBerry 10.2.0
     */
    double longitude() const;

    /**
     * @brief Sets the coordinate's longitude.
     *
     * @return @c true if the operation resulted in a change.
     *
     * @since BlackBerry 10.2.0
     */
    bool setLongitude( double lon );

    /**
     * @brief Convenience method to set latitude, longitude.
     * This operation does not change the altitude.
     *
     * @param lat The new latitude.
     * @param lon The new longitude.
     * @return @c true if the operation resulted in a change.
     *
     * @since BlackBerry 10.2.0
     */
    bool set( double lat, double lon );

    /**
     * @brief Convenience method to set latitude, longitude and
     * altitude.
     *
     * @param lat The new latitude.
     * @param lon The new longitude.
     * @param alt The new altitude.
     * @return @c true if the operation resulted in a change.
     *
     * @since BlackBerry 10.2.0
     */
    bool set( double lat, double lon, double alt );

    /**
     * @brief The bounding box of this coordinate.
     *
     * @return The bounding box of this Coordinate.
     *
     * @since BlackBerry 10.2.0
     */
    BoundingBox boundingBox() const;

    /**
     * @brief Indicates whether this @c Coordinate contains valid
     * information.
     *
     * @return @c true if this instance is in a valid state, @c false
     * otherwise.
     * @since BlackBerry 10.2.0
     */
    bool isValid() const;

    /**
     * @brief Invalidates this @c Coordinate.
     *
     * @since BlackBerry 10.2.0
     */
    void invalidate();

private:
    /** @cond PRIVATE */
    QSharedDataPointer<CoordinatePrivate> p;
    /** @endcond */

};

BB_PLATFORM_GEO_EXPORT QDebug operator<<( QDebug dbg, const Coordinate& pt );

} // namespace geo
} // namespace platform
} // namespace bb

Q_DECLARE_METATYPE( bb::platform::geo::Coordinate );

#endif // BB_PLATFORM_GEO_COORDINATE_HPP
