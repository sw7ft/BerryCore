/**
 * @copyright
 * Copyright BlackBerry Limited, 2013-2013
 * BlackBerry Limited. All rights reserved.
 */
#ifndef BB_PLATFORM_GEO_POLYLINE_HPP
#define BB_PLATFORM_GEO_POLYLINE_HPP

#include <bb/platform/geo/BoundingBox>
#include <bb/platform/geo/Coordinate>

#include <QList>
#include <QSharedDataPointer>
#include <QDebug>

namespace bb
{
namespace platform
{
namespace geo
{
class PolylinePrivate;

/**
 * @headerfile Polyline.hpp <bb/platform/geo/Polyline>
 *
 * @brief A @c Polyline in geographic space that is represented by an ordered
 * set of latitude and longitude coordinates (vertices).
 *
 * Note: Invalid coordinates are ignored when it comes to adding new
 * coordinates.
 *
 * @xmlonly
 * <apigrouping group="Location/Geographic elements"/>
 * <library name="bbcascadesmaps"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_PLATFORM_GEO_EXPORT Polyline
{

public:

    /**
     * @brief Creates a @c Polyline instance, default constructor.
     *
     * @since BlackBerry 10.2.0
     */
    Polyline();

    /**
     * @brief Copy constructor
     *
     * @param src The source of the copy information.
     *
     * @since BlackBerry 10.2.0
     */
    Polyline( const Polyline& src );

    /**
     * @brief Given a list of @c Coordinates, creates a @c Polyline
     * instance.
     *
     * @param points The list of @c Coordinates (vertices) used to
     * compose the @c Polyline. Invalid coordinates are ignored.
     *
     * @since BlackBerry 10.2.0
     */
    Polyline( const QList<Coordinate>& points );

    /**
     * @brief Destructor.
     *
     * @since BlackBerry 10.2.0
     */
    ~Polyline();

    /**
     * @brief Assignment operator.
     * @param src The source of the assignment.
     *
     * @since BlackBerry 10.2.0
     */
    Polyline& operator=( const Polyline& src );

    /**
     * @brief Equality operator.
     *
     * @param other The @c Polyline to compare.
     * @return @c true if all the coordinates of the two lines are
     * equal in value and order.
     *
     * @since BlackBerry 10.2.0
     */
    bool operator==( const Polyline& other ) const;

    /**
     * @brief Inequality operator.
     *
     * @param other The @c Polyline to compare.
     * @return @c true if there is any difference in value or order
     * between this object and the parameter.
     *
     * @since BlackBerry 10.2.0
     */
    bool operator!=( const Polyline& other ) const;

    /**
     * @brief Appends the vertex to this @c Polyline.
     *
     * @param vertex The coordinate to the appended. An invalid
     * coordinate is ignored.
     *
     * @since BlackBerry 10.2.0
     */
    void append( const Coordinate& vertex );

    /**
     * @brief Appends the list of given vertices to this object.
     *
     * @param vertices The list of coordinates to be appended. Invalid
     * coordinates are ignored.
     *
     * @since BlackBerry 10.2.0
     */
    void append( const QList<Coordinate>& vertices );

    /**
     * @brief Returns the @c Coordinate (vertex) at index position.
     * Index must be a valid index position (i.e., 0 <= index <
     * size()).
     *
     * @param index The position of the desired coordinate.
     * @return The desired coordinate. If the index is out of
     * bounds, then an invalid @c Coordinate is returned.
     *
     * @since BlackBerry 10.2.0
     */
    Coordinate at( int index ) const;

    /**
     * @brief Inserts point at index position.
     *
     * @param vertex The vertex to be inserted. An invalid coordinate
     * is ignored.
     * @param index The position for the vertex to be added. If index
     * is 0, the value is prepended to the @c Polyline.  If index is
     * size(), the value is appended to the @c Polyline. If the index
     * is outside the accepted range, then the operation is ignored.
     *
     * @since BlackBerry 10.2.0
     */
    void insertAt( const Coordinate& vertex, int index );

    /**
     * @brief Removes the vertex at the position @c index.
     *
     * @param index The position index. @c index must be a valid index
     * position (i.e., 0 <= index < size()). If the index is outside
     * the accepted range, then the operation is ignored.
     *
     * @since BlackBerry 10.2.0
     */
    void removeAt( int index );

    /**
     * @brief Replaces the vertex at the position @c index.
     *
     * @param index The position index. @c index must be a valid index
     * position (i.e., 0 <= index < size()). If the index is outside
     * the accepted range, then the operation is ignored.
     * @param point The new @c Coordinate to replace the point at @c
     * index. If @c point is an invalid coordinate, it is ignored.
     *
     * @since BlackBerry 10.2.0
     */
    void replace( int index, const Coordinate& point );

    /**
     * @brief Removes all @c Coordinates (vertices).
     *
     * @since BlackBerry 10.2.0
     */
    void clear();

    /**
     * @brief Returns the number of points (vertices) in the
     * @c Polyline.
     *
     * @since BlackBerry 10.2.0
     */
    int size() const;

    /**
     * @brief Equivalent to @c size().
     *
     * @since BlackBerry 10.2.0
     */
    int count() const;

    /**
     * @brief Determines if there are any vertices in this @c
     * Polyline.
     *
     * @return @c true if the size is zero.
     *
     * @since BlackBerry 10.2.0
     */
    bool isEmpty() const;

    /**
     * @brief Retrieves the bounding box for this shape.
     *
     * @since BlackBerry 10.2.0
     */
    BoundingBox boundingBox() const;

private:
    /** @cond PRIVATE */
    QSharedDataPointer<PolylinePrivate> p;
    /** @endcond */

};

} // namespace geo
} // namespace platform
} // namespace bb

Q_DECLARE_METATYPE( bb::platform::geo::Polyline );

#endif /* BB_PLATFORM_GEO_POLYLINE_HPP */
