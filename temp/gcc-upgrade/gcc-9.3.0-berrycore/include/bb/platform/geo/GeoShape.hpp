/**
 * @copyright
 * Copyright BlackBerry Limited, 2013-2014
 * BlackBerry Limited. All rights reserved.
 */
#ifndef BB_PLATFORM_GEO_GEOSHAPE_HPP
#define BB_PLATFORM_GEO_GEOSHAPE_HPP

#include <bb/platform/geo/Global>
#include <bb/platform/geo/Geographic>
#include <bb/platform/geo/AltitudeMode>

#include <QObject>
#include <QScopedPointer>
#include <QString>

namespace bb
{
namespace platform
{
namespace geo
{
class GeoShapePrivate;

/**
 * @headerfile GeoShape.hpp <bb/platform/geo/GeoShape>
 *
 * @brief A base class for all geographic shapes.
 *
 * @xmlonly
 * <apigrouping group="Location/Geographic elements"/>
 * <library name="bbcascadesmaps"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_PLATFORM_GEO_EXPORT GeoShape : public Geographic
{
    Q_OBJECT

    /**
     * @brief How the altitude property of all Coordinates within this
     * shape should be interpreted.
     *
     * Default value is AltitudeMode::RelativeToGround.
     *
     * @copydoc bb::platform::geo::AltitudeMode::Type
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( bb::platform::geo::AltitudeMode::Type altitudeMode READ altitudeMode WRITE
                setAltitudeMode RESET resetAltitudeMode NOTIFY altitudeModeChanged FINAL )

public:

    /**
     * @brief Destructor.
     *
     * @since BlackBerry 10.2.0
     */
    virtual ~GeoShape();

    /**
     * @brief Retrieves the altitude mode.
     *
     * @since BlackBerry 10.2.0
     */
    AltitudeMode::Type altitudeMode() const;

    /**
     * @brief Sets the altitude mode for the map's view.
     *
     * @param mode The new altitude mode.
     * @copydoc bb::platform::geo::AltitudeMode::Type
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setAltitudeMode( bb::platform::geo::AltitudeMode::Type
                                 mode );

    /**
     * @brief Resets the altitude mode to the default value of
     * AltitudeMode::RelativeToGround.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetAltitudeMode();

Q_SIGNALS:
    /**
     * @brief Emitted when the view's altitude mode has changed.
     *
     * @param mode The new altitude mode for this shape.
     * @since BlackBerry 10.2.0
     */
    void altitudeModeChanged( bb::platform::geo::AltitudeMode::Type mode );

protected:

    /**
     * @brief Constructor.
     * @param parent The parent of this @c Geographic.
     *
     * @since BlackBerry 10.2.0
     */
    explicit GeoShape( QObject* parent = 0 );

    /**
     * @brief Constructor.
     *
     * @param id The identifier for this @c Geographic. It is up
     * to the caller to ensure the uniqueness of Geographic IDs.
     * @param parent The parent of this @c Geographic.
     * @since BlackBerry 10.2.0
     */
    explicit GeoShape( const QString& id, QObject* parent = 0 );

private:
    /** @cond PRIVATE */
    QScopedPointer<GeoShapePrivate> d_ptr;
    Q_DISABLE_COPY( GeoShape )
    Q_DECLARE_PRIVATE( GeoShape );
    /** @endcond */
};


} //namespace geo
} //namespace platform
} //namespace bb
#endif /* BB_PLATFORM_GEO_GEOSHAPE_HPP */
