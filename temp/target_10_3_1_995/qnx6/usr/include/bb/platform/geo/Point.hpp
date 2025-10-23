/**
 * @copyright
 * Copyright BlackBerry Limited, 2012-2014
 * BlackBerry Limited. All rights reserved.
 */
#ifndef BB_PLATFORM_GEO_POINT_HPP
#define BB_PLATFORM_GEO_POINT_HPP

#include <bb/platform/geo/Global>
#include <bb/platform/geo/AltitudeMode>
#include <bb/platform/geo/BoundingBox>

#include <QSharedDataPointer>
#include <QDebug>

namespace bb
{
namespace platform
{
namespace geo
{
class PointPrivate;

/**
 * @headerfile Point.hpp <bb/platform/geo/Point>
 *
 * @brief A point in geographic space that is represented by latitude and
 * longitude coordinates in degrees and an altitude coordinate in meters.
 *
 * Validity
 * --------
 * A @c Point is considered valid when its three main attributes (altitude,
 * latitude and longitude) are set.  If a @c Point is invalid, its attributes
 * are undefined.
 *
 * @xmlonly
 * <apigrouping group="Location/Geographic elements"/>
 * <library name="bbcascadesmaps"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PLATFORM_GEO_EXPORT Point
{
public:

    /**
     * @brief Creates a valid point instance.
     *
     * Unless otherwise provided, a point defaults to 0 degrees
     * latitude, 0 degrees longitude, and 0 meters above ground.
     *
     * For historical reasons, the empty constructor creates a valid
     * instance of @c Point.
     *
     * @param lat The latitude value (0 default).
     * @param lon The longitude value (0 default).
     *
     * @since BlackBerry 10.0.0
     */
    explicit Point( double lat = 0, double lon = 0 );

    /**
     * @brief Copy constructor.
     *
     * @param src The object from which to copy information.
     *
     * @since BlackBerry 10.0.0
     */
    Point( Point const& src );

    /**
     * @brief Destructor.
     *
     * @since BlackBerry 10.0.0
     */
    ~Point();

    /**
     * @brief Assignment operator.
     *
     * @param src The source object from which to copy information and
     * assign to this object.
     *
     * @since BlackBerry 10.0.0
     */
    Point& operator=( const Point& src );

    /**
     * @brief Equality operator.
     *
     * @return @c true if all properties are equal.
     *
     * @since BlackBerry 10.0.0
     */
    bool operator==( const Point& rhs ) const;

    /**
     * @brief Inequality operator.
     *
     * @return @c true if any property is different.
     *
     * @since BlackBerry 10.0.0
     */
    bool operator!=( const Point& rhs ) const;

    /**
     * @brief Gets the altitude of this point in meters.
     *
     * @since BlackBerry 10.0.0
     */
    double altitude() const;

    /**
     * @brief Sets the altitude of this point in meters.
     *
     * @return @c true if the operation resulted in a change.
     *
     * @since BlackBerry 10.0.0
     */
    bool setAltitude( double alt );

    /**
     * @brief Captures how the @c altitude attribute should be
     * interpreted.
     * Default value is @c AltitudeMode::RelativeToGround.
     *
     * @return How the altitude property should be
     * interpreted.
     *
     * @since BlackBerry 10.0.0
     */
    AltitudeMode::Type altitudeMode() const;

    /**
     * @brief Sets the altitude mode.
     *
     * @copydoc bb::platform::geo::AltitudeMode::Type
     * @return @c true if the attribute changed.
     *
     * @since BlackBerry 10.0.0
     */
    bool setAltitudeMode( AltitudeMode::Type mode );

    /**
     * @brief Retrieves the point's latitude in degrees.
     *
     * @since BlackBerry 10.0.0
     */
    double latitude() const;

    /**
     * @brief Sets the point's latitude in degrees.
     *
     * @return @c true if the operation resulted in a change.
     *
     * @since BlackBerry 10.0.0
     */
    bool setLatitude( double lat );

    /**
     * @brief Gets the point's longitude in degrees.
     *
     * @since BlackBerry 10.0.0
     */
    double longitude() const;

    /**
     * @brief Sets the point's longitude in degrees.
     *
     * @return @c true if the operation resulted in a change.
     *
     * @since BlackBerry 10.0.0
     */
    bool setLongitude( double lon );

    /**
     * @brief Sets the point's latitude and longitude in degrees.
     *
     * This will result in a valid @c Point.
     *
     * @return @c true if the operation resulted in a change.
     *
     * @since BlackBerry 10.0.0
     */
    bool set( double lat, double lon );

    /**
     * @brief Moves this point by the values given in the parameter.
     * This takes into consideration latitude, longitude and altitude.
     *
     * @param rhs The point values that are added to this point. No
     * changes occur if @c rhs is invalid. If this @c Point is
     * invalid while @c rhs is valid, then @c this becomes equal to
     * @c rhs.
     *
     * @return A reference to this point.
     *
     * @since BlackBerry 10.0.0
     */
    Point& operator+=( const Point& rhs );

    /**
     * @brief Moves this point by the values given in the parameter, in
     * a negative direction. This takes into consideration latitude,
     * longitude and altitude.
     *
     * @param rhs The point values that are subtracted from this point.
     * No changes occur if @c rhs is invalid. If this @c Point is
     * invalid while @c rhs is valid, then @c this because a negative
     * copy of @c rhs.
     *
     * @return A reference to this point.
     *
     * @since BlackBerry 10.0.0
     */
    Point& operator-=( const Point& rhs );

    /**
     * @brief The bounding box of this point.
     * @return The bounding box of this point.
     *
     * @since BlackBerry 10.0.0
     */
    bb::platform::geo::BoundingBox boundingBox() const;

    /**
     * @brief Indicates whether this point contains valid
     * information.
     *
     * @since BlackBerry 10.2.0
     */
    bool isValid() const;

    /**
     * @brief Invalidates this point.
     *
     * @since BlackBerry 10.2.0
     */
    void invalidate();

private:
    QSharedDataPointer<PointPrivate> p;

};

BB_PLATFORM_GEO_EXPORT QDebug operator<<( QDebug dbg, const Point& pt );

/**
 * @brief Adds two points together.
 * This creates a new point whose values are based on the addition of the
 * two parameters.
 *
 * @param one The first point to be combined.
 * @param two The second point to be combined.
 * @return A new @c Point object whose values are the addition of the two
 * parameters.
 */
BB_PLATFORM_GEO_EXPORT const Point operator+( const Point& one, const Point& two );

/**
 * @brief Subtracts two points.
 * This creates a new point whose values are based on the subtraction of
 * the two parameters.
 *
 * @param one The first point to be combined.
 * @param two The second point to be combined.
 * @return A new @c Point object whose values are the subtraction of the two
 * parameters.
 */
BB_PLATFORM_GEO_EXPORT const Point operator-( const Point& one, const Point& two );

} // namespace geo
} // namespace platform
} // namespace bb

Q_DECLARE_METATYPE( bb::platform::geo::Point );

#endif // BB_PLATFORM_GEO_POINT_HPP
