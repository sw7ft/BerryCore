/**
 * @copyright
 * Copyright BlackBerry Limited, 2013-2014
 * BlackBerry Limited. All rights reserved.
 */
#ifndef BB_PLATFORM_GEO_GEOPOLYGON_HPP
#define BB_PLATFORM_GEO_GEOPOLYGON_HPP

#include <bb/platform/geo/Global>
#include <bb/platform/geo/GeoShape>
#include <bb/platform/geo/Polyline>

#include <QScopedPointer>

namespace bb
{
namespace platform
{
namespace geo
{
class GeoPolygonPrivate;

/**
 * @headerfile GeoPolygon.hpp <bb/platform/geo/GeoPolygon>
 *
 * @brief A polygon is an arbitrary object in geographic space that is
 * defined by a sequence of coordinates.
 *
 * At a basic level, a simple polygon is defined as just an outer boundary.
 * A more complex polygon can be created using an outer boundary with inner
 * boundaries. All boundaries are closed-looped polylines.
 *
 * Note: The associated @c Style edge properties only apply to the outer
 * boundary, not the inner boundaries, of a @c GeoPolygon.
 *
 * Note: Inner boundaries do not have any style associated with them. They
 * represent areas where the fill of the @c GeoPolygon does not draw.
 *
 * @xmlonly
 * <apigrouping group="Location/Geographic elements"/>
 * <library name="bbcascadesmaps"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_PLATFORM_GEO_EXPORT GeoPolygon : public bb::platform::geo::GeoShape
{
    Q_OBJECT

    /**
     * @brief The outer edge of the polygon.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( bb::platform::geo::Polyline outerBoundary READ outerBoundary WRITE setOuterBoundary
                NOTIFY outerBoundaryChanged FINAL )

    /**
     * @brief The inner edges of the polygon.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( QList<bb::platform::geo::Polyline> innerBoundaries READ innerBoundaries WRITE
                setInnerBoundaries NOTIFY innerBoundariesChanged FINAL )

public:

    /**
     * @brief Creates an instance of @c GeoPolygon.
     *
     * @param parent The @c QObject parent of this object.
     * @since BlackBerry 10.2.0
     */
    explicit GeoPolygon( QObject* parent = 0 );

    /**
     * @brief Creates an instance of @c GeoPolygon.
     *
     * @param id The identifier for this @c Geographic. It is up
     * to the caller to ensure the uniqueness of Geographic IDs.
     * @param parent The @c QObject parent of this object.
     *
     * @since BlackBerry 10.2.0
     */
    explicit GeoPolygon( const QString& id, QObject* parent = 0 );

    /**
     * @brief Destructor.
     *
     * @since BlackBerry 10.2.0
     */
    virtual ~GeoPolygon();

    /**
     * @brief Retrieves the vertices of the outer boundary.
     *
     * @return The vertices of the outer boundary of the polygon.
     *
     * @since BlackBerry 10.2.0
     */
    Polyline outerBoundary() const;

    /**
     * @brief Set polygon outer boundary.
     *
     * @param line The new outer boundary for this polygon.
     * @return @c true if the operation resulted in a change.
     * @since BlackBerry 10.2.0
     */
    bool setOuterBoundary( const bb::platform::geo::Polyline& line );

    /**
     * @brief Retrieves a collection of all the inner boundaries
     * within the polygon.
     *
     * @return A collection of boundaries (instances of @c Polyline)
     * that make up the inner boundaries of this polygon.
     * @since BlackBerry 10.2.0
     */
    QList<Polyline> innerBoundaries() const;

    /**
     * @brief Sets the inner boundaries for this polygon.
     *
     * @param newInnerBoundaries A collection of boundaries (instances of
     * @c Polyline) that make up the inner boundaries of this polygon.
     * @since BlackBerry 10.2.0
     */
    void setInnerBoundaries( const QList<bb::platform::geo::Polyline>&
                             newInnerBoundaries );

Q_SIGNALS:
    /**
     * @brief Emitted when the polygon's outer boundary has changed.
     *
     * @since BlackBerry 10.2.0
     */
    void outerBoundaryChanged( const bb::platform::geo::Polyline&
                               outerBoundary );

    /**
     * @brief Emitted when the polygon's collection of inner boundaries have changed.
     *
     * @param newInnerBoundaries The collection of new inner boundaries.
     * @since BlackBerry 10.2.0
     */
    void innerBoundariesChanged( const QList<bb::platform::geo::Polyline>&
                                 newInnerBoundaries );

private:
    /** @cond PRIVATE */
    QScopedPointer<GeoPolygonPrivate> d_ptr;
    Q_DISABLE_COPY( GeoPolygon )
    Q_DECLARE_PRIVATE( GeoPolygon )
    /** @endcond */
};


} // namespace geo
} // namespace platform
} // namespace bb

#endif /* BB_PLATFORM_GEO_GEOPOLYGON_HPP */
