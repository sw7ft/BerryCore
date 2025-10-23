/**
 * @copyright
 * Copyright BlackBerry Limited, 2013-2014
 * BlackBerry Limited. All rights reserved.
 */
#ifndef BB_PLATFORM_GEO_GEOPOLYLINE_HPP
#define BB_PLATFORM_GEO_GEOPOLYLINE_HPP

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
class GeoPolylinePrivate;

/**
 * @headerfile GeoPolyline.hpp <bb/platform/geo/GeoPolyline>
 *
 * @brief A polyline in geographic space that is represented by a set of
 * ordered Points.
 *
 * @xmlonly
 * <apigrouping group="Location/Geographic elements"/>
 * <library name="bbcascadesmaps"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_PLATFORM_GEO_EXPORT GeoPolyline : public bb::platform::geo::GeoShape
{
    Q_OBJECT

    /**
     * @brief The collection of vertices making up this line.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( bb::platform::geo::Polyline line READ line WRITE setLine NOTIFY lineChanged FINAL )

public:

    /**
     * @brief Creates an instance of @c GeoPolyline.
     *
     * @param parent The @c QObject parent of this object.
     * @since BlackBerry 10.2.0
     */
    explicit GeoPolyline( QObject* parent = 0 );

    /**
     * @brief Creates an instance of @c GeoPolyline.
     *
     * @param id The identifier for this @c Geographic. It is up
     * to the caller to ensure the uniqueness of Geographic IDs.
     * @param parent The @c QObject parent of this object.
     *
     * @since BlackBerry 10.2.0
     */
    explicit GeoPolyline( const QString& id, QObject* parent = 0 );

    /**
     * @brief Creates an instance of @c GeoPolyline with the
     * information provided.
     *
     * @param id The identifier for this @c Geographic. It is up
     * to the caller to ensure the uniqueness of Geographic IDs.
     * @param name The name of this location.
     * @param line Vertices of the polyline.
     * @param parent The @c QObject parent of this object.
     *
     * @since BlackBerry 10.2.0
     */
    GeoPolyline( const QString& id, const QString& name,
                 const Polyline& line, QObject* parent = 0 );

    virtual ~GeoPolyline();

    /**
     * @brief Retrieves the @c Polyline containing the vertices.
     *
     * @return @c Polyline containing the vertices.
     *
     * @since BlackBerry 10.2.0
     */
    Polyline line() const;

    /**
     * @brief set polyline.
     *
     * @return @c true if the operation resulted in a change.
     *
     * @since BlackBerry 10.2.0
     */
    bool setLine( const Polyline& line );

Q_SIGNALS:
    /**
     * @brief Emitted when the line has changed.
     *
     * @since BlackBerry 10.2.0
     */
    void lineChanged( const bb::platform::geo::Polyline& line );

private:
    /** @cond PRIVATE */
    QScopedPointer<GeoPolylinePrivate> d_ptr;
    Q_DISABLE_COPY( GeoPolyline )
    Q_DECLARE_PRIVATE( GeoPolyline )
    /** @endcond */
};


} // namespace geo
} // namespace platform
} // namespace bb

#endif /* BB_PLATFORM_GEO_GEOPOLYLINE_HPP */
