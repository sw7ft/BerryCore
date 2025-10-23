/**
 * @copyright
 * Copyright BlackBerry Limited, 2012-2014
 * BlackBerry Limited. All rights reserved.
 */
#ifndef BB_PLATFORM_GEO_BOUNDINGBOX_HPP
#define BB_PLATFORM_GEO_BOUNDINGBOX_HPP

#include <bb/platform/geo/Global>

#include <QSharedDataPointer>
#include <QMetaType>

namespace bb
{
namespace platform
{
namespace geo
{
class Point;
class BoundingBoxPrivate;

/**
 * @headerfile BoundingBox.hpp <bb/platform/geo/BoundingBox>
 *
 * @brief A 2-dimensional, axis-aligned bounding box (rectangle) used to
 * define the limits of a Geographic element, or any other bounding box.
 *
 * Validity
 * --------
 * A bounding box is considered valid when all of its attributes (edges)
 * are set. If a bounding box is invalid, its attributes are undefined.
 *
 * @xmlonly
 * <apigrouping group="Location/Geographic elements"/>
 * <library name="bbcascadesmaps"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PLATFORM_GEO_EXPORT BoundingBox
{
public:

    /**
     * @brief Default Constructor.
     * Creates a default (invalid) bounding box.
     *
     * @since BlackBerry 10.0.0
     */
    BoundingBox();

    /**
     * @brief Full constructor.
     * Creates a bounding box with the given edges (top, bottom, left,
     * right).
     *
     * @since BlackBerry 10.0.0
     */
    BoundingBox( double top, double bottom,
                 double left, double right );

    /** @brief Default Copy Constructor.
     *
     * @since BlackBerry 10.0.0
     */
    BoundingBox( const BoundingBox& src );

    /** @brief Default Destructor.
     *
     * @since BlackBerry 10.0.0
     */
    ~BoundingBox();

    /** @brief Assignment operator.
     *
     * @since BlackBerry 10.0.0
     */
    BoundingBox& operator=( const BoundingBox& src );

    /** @brief Equality operator.
     *
     * @since BlackBerry 10.0.0
     */
    bool operator==( const BoundingBox& rhs ) const;

    /** @brief Inequality operator.
     *
     * @since BlackBerry 10.0.0
     */
    bool operator!=( const BoundingBox& rhs ) const;

    /**
     * @brief Gets the latitude of the top edge of the bounding box.
     *
     * @since BlackBerry 10.0.0
     */
    double top() const;

    /**
     * @brief Sets the latitude of the top edge of the bounding box.
     * @return @c true if this modification was performed; otherwise, false
     * if this modification is invalid.
     *
     * @since BlackBerry 10.0.0
     */
    bool setTop( double top );

    /**
     * @brief Gets the latitude of the bottom edge of the bounding box.
     *
     * @since BlackBerry 10.0.0
     */
    double bottom() const;

    /**
     * @brief Sets the latitude of the bottom edge of the bounding box.
     * @return @c true if this modification was performed; otherwise, false
     * if this modification is invalid.
     *
     * @since BlackBerry 10.0.0
     */
    bool setBottom( double bottom );

    /**
     * @brief Gets the longitude of the left edge of the bounding box.
     *
     * @since BlackBerry 10.0.0
     */
    double left() const;

    /**
     * @brief Sets the longitude of the left edge of the bounding box.
     * @return @c true if this modification was performed; otherwise, false
     * if this modification is invalid.
     *
     * @since BlackBerry 10.0.0
     */
    bool setLeft( double left );

    /**
     * @brief Gets the longitude of the right edge of the bounding box.
     *
     * @since BlackBerry 10.0.0
     */
    double right() const;

    /**
     * @brief Sets the longitude of the right edge of the bounding box.
     * @return @c true if this modification was performed; otherwise, false
     * if this modification is invalid.
     *
     * @since BlackBerry 10.0.0
     */
    bool setRight( double right );

    /**
     * @brief Sets the values of all edges of the bounding box (top edge,
     * bottom edge, left edge, right edge).
     *
     * @return @c true if this modification was performed; otherwise, false
     * if this modification is invalid.
     *
     * @since BlackBerry 10.0.0
     */
    bool set( double top = 0, double bottom = 0,
              double left = 0, double right = 0 );

    /**
     * @brief Expands this bounding box's boundaries to include the bounding
     * box given as the parameter.
     *
     * If the parameter is invalid, nothing is done. If this bounding box is
     * invalid but the parameter is valid, this bounding box is set to the
     * values of the parameter. If both bounding boxes are invalid, nothing
     * is done.
     *
     * @param other The bounding box to expand this bounding box to
     * include. If @c other is invalid, no modifications are performed.
     * @return @c true if this operation modified this object; otherwise,
     * false if no modifications were made.
     *
     * @since BlackBerry 10.0.0
     */
    bool expandToInclude( const BoundingBox& other );

    /**
     * @brief Expands this bounding box's boundaries to include the
     * the bounding box indicated by the edges given as parameters.
     * @return @c true if this operation modified this object; otherwise,
     * false if no modifications were made.
     *
     * @since BlackBerry 10.0.0
     */
    bool expandToInclude( double top, double bottom,
                          double left, double right );

    /**
     * @brief Determines if @c this bounding box shares any space with
     * the @c other bounding box given as the parameter.
     *
     * @param other The bounding box to compare this bounding box with.
     * @return @c true if the two boxes share any space
     * in common. If either of the bounding boxes (this or other) are
     * invalid, then @c false is returned.
     *
     * @since BlackBerry 10.0.0
     */
    bool intersects( const BoundingBox& other ) const;

    /**
     * @brief Determines if this bounding box shares any space with
     * the bounding box indicated by the edges given as parameters.
     *
     * @return @c true if the two boxes share any space
     * in common. If this bounding box is invalid, then @c false
     * is returned.
     *
     * @since BlackBerry 10.0.0
     */
    bool intersects( double top, double bottom,
                     double left, double right ) const;

    /**
     * @brief Determines if @c this bounding box wholly contains the
     * contents of the @c other bounding box given as the parameter.
     *
     * @param other The bounding box to compare this bounding box with.
     * @return @c true if the bounding box given as the parameter is
     * completely inside this bounding box. If either of the bounding boxes
     * (this or other) are invalid, then @c false is returned.
     *
     * @since BlackBerry 10.0.0
     */
    bool whollyContains( const BoundingBox& other ) const;

    /**
     * @brief Determines if @c this bounding box wholly contains the
     * contents of the bounding box indicated by the edges given as
     * parameters.
     *
     * @return @c true if the bounding box indicated by the parameters is
     * completely inside this bounding box. If this bounding box is invalid,
     * then @c false is returned.
     *
     * @since BlackBerry 10.0.0
     */
    bool whollyContains( double top, double bottom,
                         double left, double right ) const;

    /**
     * @brief Gets the coordinates of the center of this bounding box.
     *
     * If this bounding box is invalid, then the returned @c Point is also
     * invalid.
     *
     * @since BlackBerry 10.0.0
     */
    Point center() const;

    /**
     * @brief Indicates whether this bounding box contains valid
     * information.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

    /**
     * @brief Invalidates this bounding box.
     *
     * @since BlackBerry 10.0.0
     */
    void invalidate();

    /**
     * @brief Calculates the width of the bounding box in degrees.
     *
     * @since BlackBerry 10.1.0
     */
    double width() const;

    /**
     * @brief Calculates the height of the bounding box in degrees.
     *
     * @since BlackBerry 10.1.0
     */
    double height() const;

private:
    QSharedDataPointer<BoundingBoxPrivate> p;
};

BB_PLATFORM_GEO_EXPORT QDebug operator<<( QDebug dbg, const BoundingBox& pt );

} // namespace geo
} // namespace platform
} // namespace bb

Q_DECLARE_METATYPE( bb::platform::geo::BoundingBox );

#endif /* BB_PLATFORM_GEO_BOUNDINGBOX_HPP */
