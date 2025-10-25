/**
 * @copyright
 * Copyright BlackBerry Limited, 2012-2014
 * BlackBerry Limited. All rights reserved.
 */
#ifndef BB_CASCADES_MAPS_VIEW_PROPERTIES_HPP
#define BB_CASCADES_MAPS_VIEW_PROPERTIES_HPP

#include <bb/cascades/maps/Global>
#include <bb/platform/geo/Point>
#include <bb/platform/geo/BoundingBox>

#include <QSharedDataPointer>
#include <QPoint>
#include <QSize>
#include <QDebug>

namespace bb
{
namespace cascades
{
namespace maps
{
class ViewPropertiesPrivate;

/**
 * @headerfile ViewProperties.hpp <bb/cascades/maps/ViewProperties>
 *
 * @brief The properties of the current view.
 *
 * @xmlonly
 * <apigrouping group="Location/Maps and map visualization"/>
 * <library name="bbcascadesmaps"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_CASCADES_MAPS_EXPORT ViewProperties
{

public:
    /**
     * @brief Basic constructor.
     *
     * @since BlackBerry 10.0.0
     */
    ViewProperties();

    /**
     * @brief Destructor.
     *
     * @since BlackBerry 10.0.0
     */
    ~ViewProperties();

    /**
     * @brief Copy constructor.
     *
     * @param src The object from which to copy information.
     *
     * @since BlackBerry 10.0.0
     */
    ViewProperties( const ViewProperties& src );

    /**
     * @brief Assignment operator.
     *
     * @param src The object from which to copy information.
     *
     * @since BlackBerry 10.0.0
     */
    ViewProperties& operator=( const ViewProperties& src );

    /**
     * @brief Indicates from what height, in meters, that the map is
     * viewed at.
     *
     * @see #altitudeMode
     * @return The view's altitude.
     *
     * @since BlackBerry 10.0.0
     */
    double altitude() const;

    /**
     * @brief Sets the height the map is viewed at, in meters.
     *
     * @param alt The new altitude.
     * @return @c true if a change occurred, @c false otherwise
     *
     * @since BlackBerry 10.0.0
     */
    bool setAltitude( double alt );

    /**
     * @brief Captures how the @c altitude attribute should be
     * interpreted.
     *
     * @return The altitude's mode.
     *
     * @since BlackBerry 10.0.0
     */
    bb::platform::geo::AltitudeMode::Type altitudeMode() const;

    /**
     * @brief Sets the altitude mode.
     *
     * @see AltitudeMode
     * @param mode The new altitude mode.
     * @return @c true if the attribute changed.
     *
     * @since BlackBerry 10.0.0
     */
    bool setAltitudeMode( bb::platform::geo::AltitudeMode::Type mode );

    /**
     * @brief Gets the direction of the view in degrees.
     *
     * @return The view's heading, or direction.
     *
     * @since BlackBerry 10.0.0
     */
    double heading() const;

    /**
     * @brief Sets the orientation of the view.
     * @details Heading is the angle of the
     * view based on a compass reading. Units are degrees. Thus, a
     * value of 90 indicates that the view is facing east.
     *
     * @param heading The new heading. Before this value is applied, it
     * is normalized to be within the range of 0 to 360.
     * @return @c true if a change occurred, @c false otherwise
     *
     * @since BlackBerry 10.0.0
     */
    bool setHeading( double heading );

    /**
     * @brief Gets the latitude of the view.
     *
     * @return The latitude of the center of the view.
     *
     * @since BlackBerry 10.0.0
     */
    double latitude() const;

    /**
     * @brief Sets the latitude of the view.
     *
     * @param newLat The new latitude coordinate. The value is
     * normalized (between -90 and +90) before being applied.
     * @return @c true if the attribute was changed.
     *
     * @since BlackBerry 10.0.0
     */
    bool setLatitude( double newLat );

    /**
     * @brief Gets the longitude of the view.
     *
     * @return The longitude of the center of the view.
     *
     * @since BlackBerry 10.0.0
     */
    double longitude() const;

    /**
     * @brief Sets the longitude of the view.
     *
     * @param newLon The new longitude coordinate. The value is
     * normalized (between -180 and +180) before being applied.
     * @return @c true if the attribute was changed.
     *
     * @since BlackBerry 10.0.0
     */
    bool setLongitude( double newLon );

    /**
     * @brief Gets the center of the viewport's coordinates in the form
     * of a Point.
     *
     * @return The center coordinate.
     *
     * @since BlackBerry 10.0.0
     */
    bb::platform::geo::Point center() const;

    /**
     * @brief Gets the current view's tilt in degrees, where a value of 0 is
     * pointing straight down.
     *
     * @return The view's tilt value.
     *
     * @since BlackBerry 10.0.0
     */
    int tilt() const;

    /**
     * @brief Sets the view's tilt in degrees.
     *
     * @param newTilt The view's new tilt value.
     * @return @c true if the attribute was changed.
     *
     * @since BlackBerry 10.0.0
     */
    bool setTilt( int newTilt );

    /**
     * @brief Gets the window's size.
     *
     * @return The window's size in pixels.
     *
     * @since BlackBerry 10.0.0
     */
    QSize windowSize() const;

    /**
     * @brief Sets the properties of the window.
     *
     * @param newDimensions The new dimensions of the window.
     *
     * @since BlackBerry 10.0.0
     */
    void setWindow( const QRect& newDimensions );

    /**
     * @brief Gets the coordinates of the middle of the window.
     *
     * @return The midpoint of the view in screen coordinates.
     *
     * @since BlackBerry 10.0.0
     */
    QPoint windowMidpoint() const;

    /**
     * @brief Retrieves the bounding box that this view encapsulates.
     *
     * @return The bounding box of the view.
     *
     * @since BlackBerry 10.0.0
     */
    bb::platform::geo::BoundingBox boundingBox() const;

    /**
     * @brief Sets the bounding box for this view.
     *
     * @param box The new bounding box for this view.
     *
     *
     * @since BlackBerry 10.0.0
     */
    void setBoundingBox( const bb::platform::geo::BoundingBox& box );

private:
    QSharedDataPointer<ViewPropertiesPrivate> p;
};

BB_CASCADES_MAPS_EXPORT QDebug operator<<( QDebug dbg, ViewProperties const& src );

} /* namespace maps */
} /* namespace cascades */
} /* namespace bb */
#endif // BB_CASCADES_MAPS_VIEW_PROPERTIES_HPP
