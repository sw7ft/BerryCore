/**
 * @copyright
 * Copyright BlackBerry Limited, 2012-2014
 * BlackBerry Limited. All rights reserved.
 */
#ifndef BB_CASCADES_MAPS_MAPVIEW_HPP
#define BB_CASCADES_MAPS_MAPVIEW_HPP

#include <bb/cascades/maps/Global>
#include <bb/platform/geo/Point>
#include <bb/platform/geo/AltitudeMode>
#include <bb/cascades/CustomControl>
#include <bb/ImageData>

namespace bb
{
namespace cascades
{
class TapEvent;
namespace maps
{
class MapData;
class ViewProperties;
class DataProvider;
class RenderEngine;
class MapViewPrivate;

/**
 * @headerfile MapView.hpp <bb/cascades/maps/MapView>
 *
 * @brief A graphics user interface (GUI) control that displays a map along
 * with user-defined geographic elements, which can be points of interest
 * or other location-aware elements.
 *
 * @details All data shown on the map is provided through the client
 * provided @c MapData object. A client provided @c MapData instance is
 * controlled by the client. Thus, when the @c MapView is destroyed, the
 * @c MapData instance still exists, and it is up to the client to free that
 * memory. If the client wants to link the @c MapView and @c MapData objects
 * together, then they can do so by making the @c MapData a child of the
 * @c MapView.
 *
 * If a @c MapData object is not provided by the
 * client, then one is automatically created. In this case, the @c MapData
 * instance is setup as a child of the @c MapView.
 *
 * @c MapView will automatically pick an appropriate @c RenderEngine instance
 * based on the available plug-ins. @c MapView will automatically switch to a
 * different @c RenderEngine if the current engine cannot fully render the
 * current view (usually due to lack of mapping data). If a @c RenderEngine is
 * explicitly set by the client application, then dynamic @c RenderEngine
 * switching is not performed.
 *
 * @section sec_classic_trackpad_overview Classic Trackpad Support
 *
 * Unlike other types of controls and content, a @c MapView has no left or right
 * boundaries, and depending on the altitude value, the top and bottom can be too
 * large a distance away to reach using the trackpad. Due to this difference,
 * @c MapView will request focus by default when added to an application, and
 * trackpad focus won't leave the @c MapView to go to other controls. This
 * must be taken into account when configuring the user interface, for instance
 * by providing menu options to activate controls that cannot be reached with
 * the trackpad.
 *
 * While the @c MapView will request focus on creation, other Cascades elements
 * such as @c ActionItem may have higher focus priority, so care must be taken to
 * ensure the @c MapView receives focus to allow trackpad interaction.
 *
 * Depending on the UI configuration, custom focus handling or modification of
 * the @c Navigation properties of other UI elements may be required.
 *
 * If focus is explicitly removed from the @c MapView, it must be returned
 * using @c Control::requestFocus() to allow trackpad control of the map
 * contents again.
 *
 * @section sec_animation_overview Map Animation
 *
 * @c MapView has the ability to animate the transition between two points.
 * This is offered through the @c animateToLocation operations.
 *
 * The @c setLocation, @c setLatitude, @c setLongitude and @c setAltitude
 * operations are performed immediately, while the @c animateToLocation
 * operations slide and zoom the map from the current coordinates to the
 * new coordinates. If the new coordinates are not within the mapview's contents,
 * the animation will simulate a flying experience, as it starts from current map altitude,
 * then it goes to a predefined altitude and arrives at the new location
 * at the altitude specified by user. If the new coordinates are within the
 * mapview's contents and destination altitude is same as current altitude,
 * then animation will simply pan to the new location.
 *
 * While the animation is being performed, changes to the @c #latitude and @c
 * #longitude properties are reflected through their
 * associated @c propertyChanged signals. In addition, depending on the animation requested, changes to the
 * @c #altitude property are also reflected through its
 * associated @c propertyChanged signal.
 *
 * @c MapView has the ability to animate the transition between two altitudes,
 * while the currently displayed map center is maintained on the map.
 * This is offered through the @c animateToAltitude operation.
 * While this animation is being performed, changes to the
 * @c #altitude property are reflected through its associated @c propertyChanged signal.
 *
 *  @c MapView has the ability to animate the transition between two headings,
 * while the currently displayed map center is maintained on the map.
 * When animating to new heading, the algorithm chooses the shortest rotation of map contents.
 * For example, if the current heading is 0 degrees (North) and the user requested to animate to 364 degrees,
 * then animation will rotate the map contents clock-wise from 0 degrees to 4 degrees.
 * This is offered through the @c animateToHeading operation.
 * While this animation is being performed, changes to the
 * @c #heading property are reflected through its associated @c propertyChanged signal.
 *
 * The amount of time it takes to perform an animation is controlled
 * through the @c #animationDuration property. If the map is performing an
 * animation, this state is reflected through the @c #animationActive
 * property.
 *
 * A user can interrupt the animation by interacting with the screen (tap,
 * touch, pinch, etc) or by using a trackpad or a touch-sensitive keyboard.
 * If an animation is interrupted, it stops at the point it was interrupted.
 *
 * @xmlonly
 * <apigrouping group="Location/Maps and map visualization"/>
 * <library name="bbcascadesmaps"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_CASCADES_MAPS_EXPORT MapView : public bb::cascades::CustomControl
{
    Q_OBJECT

    /**
     * @brief Gets the viewport's altitude in meters.
     *
     * Default value is 0 meters.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY( double altitude READ altitude WRITE setAltitude RESET resetAltitude NOTIFY
                altitudeChanged FINAL )

    /**
     * @brief Indicates how the viewport's altitude property should be
     * interpreted.
     *
     * Default value is @c AltitudeMode::RelativeToGround
     *
     * @see bb::platform::geo::AltitudeMode::Type
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY( bb::platform::geo::AltitudeMode::Type altitudeMode READ altitudeMode WRITE
                setAltitudeMode RESET resetAltitudeMode NOTIFY altitudeModeChanged FINAL )

    /**
     * @brief Gets the heading of the viewport in compass degrees.
     *
     * Values are based on a compass, with 0 equaling North, 90
     * equaling East, and so on. Default value is 0 (North).
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY( double heading READ heading WRITE setHeading RESET resetHeading NOTIFY headingChanged
                FINAL )

    /**
     * @brief The latitude of the viewport in coordinate degrees (-90 to
     * +90).
     *
     * Default value is 0.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY( double latitude READ latitude WRITE setLatitude RESET resetLatitude NOTIFY
                latitudeChanged FINAL )

    /**
     * @brief The longitude of the viewport in coordinate degrees (-180 to
     * +180).
     *
     * Default value is 0.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY( double longitude READ longitude WRITE setLongitude RESET resetLongitude NOTIFY
                longitudeChanged FINAL )

    /**
     * @brief The viewport's tilt in angle degrees, where 0 is straight
     * down.
     *
     * Values are based on a camera pointing straight down (equaling 0) to
     * pointing tangential to the earth's surface (equaling 90).
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY( int tilt READ tilt WRITE setTilt RESET resetTilt NOTIFY tiltChanged FINAL )

    /**
     * @brief The geographic element that is currently in focus.
     * This is a convenience property for @c MapData's focused element.
     *
     * Default value is an empty string.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY( QString focusedId READ focusedId WRITE setFocusedId RESET resetFocusedId NOTIFY
                focusedIdChanged FINAL )

    /**
     * @brief The geographic element that is currently being followed.
     *
     * Default value is an empty string.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY( QString followedId READ followedId WRITE setFollowedId RESET resetFollowedId NOTIFY
                followedIdChanged FINAL )

    /**
     * @brief The location caption's content.
     *
     * @see setCaptionContent( bb::cascades::Container* )
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( bb::cascades::Container* captionContent READ captionContent WRITE setCaptionContent
                RESET resetCaptionContent NOTIFY captionContentChanged REVISION 1 FINAL )

    /**
     * @brief The @c MapData for the @c MapView.
     *
     * @see setMapData( bb::cascades::MapData* )
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( bb::cascades::maps::MapData* mapData READ mapData WRITE setMapData RESET resetMapData
                NOTIFY mapDataChanged REVISION 1 FINAL )

    /**
     * @brief Enables or disables the inclusion of traffic
     * conditions within the map.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(
        bool inlineTrafficEnabled
        READ isInlineTrafficEnabled
        WRITE setInlineTrafficEnabled
        RESET resetInlineTrafficEnabled
        NOTIFY inlineTrafficEnabledChanged
        REVISION 1
        FINAL );

    /**
     * @brief Indicates whether inline traffic is available within the
     * current map view.
     *
     * Only applicable when inline traffic is enabled.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(
        bool inlineTrafficAvailable
        READ isInlineTrafficAvailable
        NOTIFY inlineTrafficAvailableChanged
        REVISION 1
        FINAL );

    /**
     * @brief Indicates whether inline traffic is supported with the
     * currently selected @c RenderEngine
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(
        bool inlineTrafficSupported
        READ isInlineTrafficSupported
        NOTIFY inlineTrafficSupportedChanged
        REVISION 1
        FINAL );

    /**
     * @brief The length of time (in milliseconds) that it takes to
     * perform an animation initiated by any animation function.
     *
     * If a value is not provided, the duration of the animation is computed
     * dynamically based on the initial and final values of the animation.
     *
     * See @ref sec_animation_overview for additional information.
     *
     * @since BlackBerry 10.3.0
     */
    Q_PROPERTY(
        int animationDuration
        READ animationDuration
        WRITE setAnimationDuration
        RESET resetAnimationDuration
        NOTIFY animationDurationChanged
        REVISION 2
        FINAL
    );

    /**
     * @brief Indicates if the map is currently performing an
     * animation as triggered by of any animation function.
     *
     * See @ref sec_animation_overview for additional information.
     *
     * @since BlackBerry 10.3.0
     */
    Q_PROPERTY(
        bool animationActive
        READ isAnimationActive
        NOTIFY animationActiveChanged
        REVISION 2
        FINAL
    );

public:
    /**
     * Default Constructor.
     *
     * @param parent The parent object to this object.
     * @since BlackBerry 10.0.0
     */
    explicit MapView( bb::cascades::Container* parent = 0 );

    /**
     * Destructor.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~MapView();

    /**
     * @brief Retrieves the altitude in meters.
     *
     * @since BlackBerry 10.0.0
     */
    double altitude() const;

    /**
     * @brief Sets the altitude for the map's view.
     *
     * @param newAlt The new altitude, in meters.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setAltitude( double newAlt );

    /**
     * @brief Resets the altitude to the default value of 4000 meters.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void resetAltitude();

    /**
     * @brief Retrieves the altitude mode.
     *
     * @since BlackBerry 10.0.0
     */
    bb::platform::geo::AltitudeMode::Type altitudeMode() const;

    /**
     * @brief Sets the altitude mode for the map's view.
     *
     * @param newAlt The new altitude mode.
     * @see bb::platform::geo::AltitudeMode::Type
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setAltitudeMode( bb::platform::geo::AltitudeMode::Type newAlt );

    /**
     * @brief Resets the altitude mode to the default value of
     * @c AltitudeMode::RelativeToGround.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void resetAltitudeMode();

    /**
     * @brief Retrieves the heading in degrees.
     *
     * @since BlackBerry 10.0.0
     */
    double heading() const;

    /**
     * @brief Sets the heading for the map's view.
     *
     * @param newHeading The new heading, in degrees where 0 is
     * North.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setHeading( double newHeading );

    /**
     * @brief Resets the heading to the default value of 0
     * degrees (North).
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void resetHeading();

    /**
     * @brief Retrieves the latitude in degrees.
     *
     * @since BlackBerry 10.0.0
     */
    double latitude() const;

    /**
     * @brief Sets the latitude for the map's view.
     *
     * @param newLat The new latitude, in degrees decimal.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setLatitude( double newLat );

    /**
     * @brief Resets the latitude to the default value of 0
     * degrees.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void resetLatitude();

    /**
     * @brief Retrieves the longitude in degrees.
     *
     * @since BlackBerry 10.0.0
     */
    double longitude() const;

    /**
     * @brief Sets the longitude for the map's view.
     *
     * @param newLon The new longitude, in degrees decimal.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setLongitude( double newLon );

    /**
     * @brief Resets the longitude to the default value of 0
     * degrees.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void resetLongitude();

    /**
     * @brief Retrieves the tilt angle in degrees.
     *
     * @since BlackBerry 10.0.0
     */
    int tilt() const;

    /**
     * @brief Sets the tilt for the map's view.
     *
     * @param newTilt The new tilt. Values are based on a camera
     * pointing straight down (equaling 0) to pointing tangential
     * to the earth's surface (equaling 90).
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setTilt( int newTilt );

    /**
     * @brief Resets the tilt to the default value of 0 degrees
     * (straight down).
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void resetTilt();

    /**
     * @brief Retrieves the ID of the element that currently
     * has focus (selected).
     *
     * If the @c DataProvider containing the element that currently has
     * focus is set invisible the focused ID will be reset.
     *
     * @return The ID of the element in focus. A null string
     * is returned if nothing is in focus.
     *
     * @since BlackBerry 10.0.0
     */
    QString focusedId() const;

    /**
     * @brief Sets the ID of the element to have focus.
     *
     * If there is no such element with ID @c newFocusedId or
     * the @c DataProvider containing the element with ID
     * @c newFocusedId is not visible the focused ID will not change.
     *
     * If the @c DataProvider containing the element that currently has
     * focus is set invisible the focused ID will be reset.
     *
     * @param newFocusedId The ID of the element to set focus on.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setFocusedId( const QString& newFocusedId );

    /**
     * @brief Resets the focused element ID to the default value
     * of nothing.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void resetFocusedId();

    /**
     * @brief Retrieves the ID of the element that is currently
     * being followed.
     *
     * If the @c DataProvider containing the element that is currently
     * being followed is set invisible the followed ID will be reset.
     *
     * @return The ID of the element being followed, or null string
     * is returned if nothing is being followed.
     *
     * @since BlackBerry 10.0.0
     */
    QString followedId() const;

    /**
     * @brief Sets the element to be followed. By default the
     * followed element will be shown at center of the map view.
     * If the current map location is modified by
     * the user then the followed ID will be reset.
     *
     * If there is no element with the given ID, or the @c DataProvider
     * containing the element with the given ID is invisible there will
     * be no change.
     *
     * If the @c DataProvider containing the element that is currently
     * being followed is set invisible the followed ID will be reset.
     *
     * @param newFollowedId The ID of the element to follow.
     * @param horizontalOffset Defines the horizontal position
     * of the followed element on this map view relative to center.
     * Valid values are from -1.0 to 1.0, the effective offset pixel
     * value equals <code>horizontalOffset/('map view width'/2)</code>.
     * Therefore, -1.0 defines left edge; 1.0 defines right edge.
     * @param verticalOffset Defines the vertical position
     * of the followed element on this map view relative to center.
     * Valid values are from -1.0 to 1.0, the effective offset pixel
     * value equals <code>verticalOffset/('map view height'/2)</code>.
     * Therefore, -1.0 defines top edge; 1.0 defines bottom edge.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setFollowedId( const QString& newFollowedId,
                               float horizontalOffset = 0.0, float verticalOffset = 0.0 );

    /**
     * @brief Resets the followed element ID to the default value
     * of nothing. This means turn off follow mode.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void resetFollowedId();

    /**
     * @brief Retrieves the caption's content.
     *
     * Note: Ownership of the container is not transferred as part of
     * this operation: @c MapView is still the parent of the @c
     * Container.
     *
     * @return The current content for the caption bubble, or @c NULL if
     * the caption bubble is disabled.
     *
     * @since BlackBerry 10.2.0
     * @see setCaptionContent( bb::cascades::Container* )
     */
    Q_REVISION( 1 )
    bb::cascades::Container* captionContent() const;

    /**
     * @brief Sets the caption's content.
     *
     * @c MapView uses a location caption (callout bubble) to
     * indicate the @c Geographic element that is in focus, as well as
     * provide visual information about that focused element. The
     * contents of this caption can be replaced with custom
     * content.
     *
     * The default contents of the caption consists of two text fields,
     * one displaying the focused element's name, the other displaying
     * the element's description. The default caption can optionally
     * also contain a "go" button. (This button can be disabled through
     * @c #setCaptionGoButtonVisible( bool ).) The @c captionLabelTapped
     * signal is emitted if the text fields are tapped. The
     * @c captionButtonClicked signal is emitted when the "go" button
     * is clicked. The caption's contents will be the default content
     * container if it has not otherwise been set by the client.
     *
     * The caption's contents can be replaced with an arbitrary
     * container. This container only holds the new content of the
     * caption, it does not contain the caption's chrome (the callout
     * frame). At this time, the caption content is height limited.
     * The content height is currently set at 137 pixels and is the same
     * for all device screen layouts. Therefore, if the new contents
     * exceed the caption's limits, the excess will be truncated.
     *
     * The caption's new contents can contain controls that emit
     * signals. It is up to the container's author to set up any
     * signal/slot connections.
     *
     * @c MapView takes ownership of the provided container. If a new
     * container is provided, the previous container is deleted.
     *
     * To remove the entire caption (contents and chrome), a @c
     * NULL value is passed to this operation. To reset the caption's
     * content to the default value, use #resetCaptionContent.
     *
     * @param captionContent The new caption's content. If @c
     * NULL, the caption is disabled.
     *
     * @since BlackBerry 10.2.0
     */
    Q_REVISION( 1 )
    Q_SLOT void setCaptionContent( bb::cascades::Container* captionContent );

    /**
     * @brief Resets the caption's content to the default value.
     *
     * @see setCaptionContent( bb::cascades::Container* )
     * @since BlackBerry 10.2.0
     */
    Q_REVISION( 1 )
    Q_SLOT void resetCaptionContent();

    /**
     * @brief Sets the map location to that of the focused element.
     *
     * @details If there is no focused element, nothing is done.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setLocationOnFocused();

    /**
     * @brief Changes the map's view so that all visible data within
     * the map's model (@c #mapData()) is within the map's view.
     * If there is no visible data, the view does not change.
     *
     * @since BlackBerry 10.1.0
     */
    Q_SLOT void setLocationOnVisible();

    /**
     * @brief Retrieves the data on the map.
     *
     * @since BlackBerry 10.0.0
     */
    bb::cascades::maps::MapData* mapData();

    /**
     * @brief Retrieves the data on the map.
     *
     * @since BlackBerry 10.0.0
     */
    const bb::cascades::maps::MapData* mapData() const;

    /**
     * @brief Adds a new @c MapData container to this view.
     *
     * @details The provided parameter will replace the existing @c MapData
     * container. Connections will automatically be made between the
     * @c MapView and @c MapData instances.
     *
     * See class-level documentation for more information.
     *
     * @param data The new container of data to show on the map.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setMapData( bb::cascades::maps::MapData* data );

    /**
     * @brief Sets the location of the screen using latitude and
     * longitude coordinates.
     *
     * @param loc The location to set the map to.
     * @return @c true if a change occurred.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT bool setLocation( const bb::platform::geo::Point& loc );

    /**
     * @brief Sets the map's location such that the entire bounding
     * box is visible within the map's view.
     *
     * Note: This can modify latitude, longitude, altitude, altitude
     * mode and heading.
     *
     * @param area The box to be shown in the view. If this is invalid,
     * no change is performed.
     *
     * @return @c true if a change occurred.
     *
     * @since BlackBerry 10.1.0
     */
    Q_SLOT bool setLocation( const bb::platform::geo::BoundingBox& area );

    /**
     * @brief Animates the map to the new location.
     * Similar to #setLocation, but instead of jumping directly to the
     * location, the map "flys" from its current location to the new
     * location.
     *
     * See @ref sec_animation_overview for additional information.
     *
     * @param latitude The destination latitude.
     * @param longitude The destination longitude.
     *
     * @since BlackBerry 10.3.0
     */
    Q_REVISION( 2 )
    Q_INVOKABLE void animateToLocation(
        double latitude, double longitude );

    /**
     * @brief Animates the map to the new location.
     * Similar to #setLocation, but instead of jumping directly to the
     * location, the map "flys" from its current location to the new
     * location.
     *
     * See @ref sec_animation_overview for additional information.
     *
     * @param latitude The destination latitude.
     * @param longitude The destination longitude.
     * @param altitude The destination altitude.
     *
     * @since BlackBerry 10.3.0
     */
    Q_REVISION( 2 )
    Q_INVOKABLE void animateToLocation(
        double latitude, double longitude, double altitude );

    /**
     * @brief Animates the map to the new location.
     * Similar to #setLocation, but instead of jumping directly to the
     * location, the map "flys" from its current location to the new
     * location.
     *
     * See @ref sec_animation_overview for additional information.
     *
     * @param location The coordinates of the destination.
     *
     * @since BlackBerry 10.3.0
     */
    Q_REVISION( 2 )
    Q_SLOT void animateToLocation(
        const bb::platform::geo::Point& location );

    /**
     * @brief Animates the map to the new altitude.
     * Similar to #setAltitude, but instead of jumping directly to the
     * altitude, the map gradually zooms in (or out) from its current altitude to the new
     * altitude. The current map center does not change.
     *
     * See @ref sec_animation_overview for additional information.
     *
     * @param newAlt The destination altitude.
     *
     * @since BlackBerry 10.3.1
     */
    Q_REVISION( 3 )
    Q_SLOT void animateToAltitude( double newAlt );

    /**
     * @brief Animates the map's view to rotate to the new heading.
     * Similar to #setHeading, but instead of rotating directly to the
     * new heading, the map's view gradually rotates from its current heading
     * to the new heading, using shortest rotation. The direction of rotation
     * (clockwise/counter-clockwise) will be determined by the relative postion
     * of the new heading against the current heading.
     * The current map center does not change.
     *
     * See @ref sec_animation_overview for additional information.
     *
     * @param newHeading The destination heading in degrees (0 is North, 90 is East).
     *
     * @since BlackBerry 10.3.1
     */
    Q_REVISION( 3 )
    Q_SLOT void animateToHeading( double newHeading );

    /**
     * @brief Sets the map's location to be that of the window's x and
     * y coordinates.
     * @details The window's origin is the upper, left corner.
     *
     * @param x The window's x coordinate to make the center of the
     * window.
     * @param y The window's y coordinate to make the center of the
     * window.
     * @return @c true if a change occurred.
     *
     * @since BlackBerry 10.0.0
     */
    bool setLocationWindowAbsolute( int x, int y );

    /**
     * @brief Sets the map's location to be that of the window's
     * coordinates in pixels.
     * @details The window's origin is the upper, left corner.
     *
     * @param pixelLocation The window's coordinates (in pixels)
     * that will become the new center of the map's window.
     * @return @c true if a change occurred.
     *
     * @since BlackBerry 10.0.0
     */
    bool setLocationWindowAbsolute( const QPoint& pixelLocation );

    /**
     * @brief Sets the location of the window relative to the current x
     * and y coordinates.
     * @details The units used are screen pixels.
     *
     * @param deltaX Move the current center of the map
     * <code>deltaX</code> pixels on the X axis.
     * @param deltaY Move the current center of the map
     * <code>deltaY</code> pixels on the Y axis.
     * @return @c true if a change occurred.
     *
     * @since BlackBerry 10.0.0
     */
    bool setLocationWindowDelta( int deltaX, int deltaY );

    /**
     * @brief Sets the location of the window relative to the current
     * location in pixels.
     * @details The units used are screen pixels.
     *
     * @param deltaPixelLocation The relative amount to move the
     * center of the map.
     * @return @c true if a change occurred.
     *
     * @since BlackBerry 10.0.0
     */
    bool setLocationWindowDelta( const QPoint& deltaPixelLocation );

    /**
     * @brief Gets all the properties of the current view.
     *
     * @return A handle to the viewport properties.
     *
     * @since BlackBerry 10.0.0
     */
    bb::cascades::maps::ViewProperties viewProperties() const;

    /**
     * @brief Allows for the explicit setting of the render engine that
     * this @c MapView instance should use.
     *
     * @details Note: This @c MapView instance will take explicit
     * ownership of the provided @c RenderEngine. Thus, @c MapView will
     * decide when the parameter's destructor will be called.
     *
     * When a @c RenderEngine instance is explicitly set through this
     * method, dynamic @c RenderEngine switching will be disabled (see
     * class level documentation concerning this). A @c NULL value will
     * re-enable dynamic @c RenderEngine switching.
     *
     * @param newEngine A pointer to the new render engine. A value of
     * @c NULL tells @c MapView to automatically pick the best suited
     * @c RenderEngine from the list of available plug-ins.
     *
     * @since BlackBerry 10.0.0
     */
    void setRenderEngine( bb::cascades::maps::RenderEngine* newEngine );

    /**
     * @brief Sets the render engine to the named plug-in.
     *
     * Given a plug-in name of @c FooBar, MapView will look for a
     * RenderEngine plug-in in the following locations
     * - <tt>[app_root]/app/native/lib/mapview-renderengine/FooBar.so</tt>
     * - <tt>[app_root]/app/native/lib/mapview-renderengine/libFooBar.so</tt>
     * - <tt>QTDIR/plugins/mapview-renderengine/FooBar.so</tt>
     * - <tt>QTDIR/plugins/mapview-renderengine/libFooBar.so</tt>
     * Where @c QTDIR is the installation location of Qt.
     *
     * The plug-in must properly implement the @c RenderEngine interface,
     * plus adhere to the plug-in structure as described in the
     * @c RenderEngine class documentation.
     *
     * See the class level documentation for information on dynamic
     * @c RenderEngine switching.
     *
     * @param pluginName The name of the plug-in to use as the render
     * engine.
     * @return @c true if the plug-in was successfully loaded, @c false
     * otherwise. See the application's log for information as to why
     * the plug-in didn't load.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT bool setRenderEngine( const QString& pluginName );

    /**
      * @brief Generates an image of the current map view.
      *
      * @return An image of the currently viewed map.
     *
     * @since BlackBerry 10.0.0
      */
    bb::ImageData generateStaticMapImage();

    /**
     * @brief The axis-aligned bounding box of this control's view.
     *
     * @return The bounding box containing the current view.
     *
     * @since BlackBerry 10.0.0
     */
    bb::platform::geo::BoundingBox boundingBox() const;

    /**
     * @brief Gets a URL representing the current map view.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE QString url() const;

    /**
     * @brief Gets a Geo URI representing the current focused location
     * (if available), otherwise representing the current map view.
     *
     * The Geo URI (Uniform Resource Identifier) is a URI scheme as
     * defined by the Internet Engineering Task Force's
     * <a href="http://en.wikipedia.org/wiki/RFC_5870">RFC 5870</a>
     *
     * @return A string representing the current view in GeoURI format.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE QString geoUri() const;

    /**
     * @brief Sets whether or not the "Go" button, used to navigate to the
     * focused element, should appear in the focus caption bubble.
     * This method only applies to the default caption content.
     * If client provides a custom content (using @c setCaptionContent(bb::cascades::Container*)) then
     * it is the responsibility of the client to provide such button as part of that content.
     *
     * In the case of default content, the "Go" button automatically appears on the focus
     * caption bubble.
     *
     * @param showButton @c true to show the "Go" button, @c false to hide
     * the "Go" button.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void setCaptionGoButtonVisible( bool showButton );

    /**
     * @brief Converts window coordinates (pixels) into world
     * coordinates (latitude/longitude).
     *
     * The origin of the window's coordinates are the upper left
     * corner of the @c MapView window (not screen), with positive
     * values going right (x axis) and down (y axis).
     *
     * @param windowCoordinates The window coordinates to be
     * converted.
     *
     * @return The world coordinates of the given @c QPoint.
     *
     * @since BlackBerry 10.0.0
     */
    bb::platform::geo::Point windowToWorld( const QPoint& windowCoordinates ) const;

    /**
     * @brief Converts world coordinates (latitude/longitude) into
     * window coordinates (pixels).
     *
     * The origin of the window's coordinates are the upper left
     * corner of the @c MapView window (not screen), with positive
     * values going right (x axis) and down (y axis).
     *
     * @param worldCoordinates The latitude/longitude coordinates
     * to be converted.
     *
     * @return The window coordinates of the given @c Point.
     *
     * @since BlackBerry 10.0.0
     */
    QPoint worldToWindow( const bb::platform::geo::Point& worldCoordinates ) const;

    /**
     * @brief Sets the boundaries of the current view.
     *
     * View boundaries prevent the user from viewing portions of the
     * map that exceed these boundaries.  There are two boundaries: an
     * inner boundary and an outer boundary.
     *
     * The outer boundary keeps the map's view within the boundary.
     * Thus, the user cannot pan or zoom beyond its borders. The inner
     * boundary works in the opposite direction: the inner boundary
     * is always visible within the map's view.
     *
     * Both boundaries do not need to be supplied. An inner boundary
     * can be supplied by itself, the outer boundary can be supplied,
     * or both boundaries can be supplied.
     *
     * Examples:
     * - If an inner boundary is supplied representing a box around the
     * Eiffel Tower, then the user will not be able to pan or zoom the
     * map so the Eiffel Tower is no longer on the map.
     * - If an outer boundary is supplied representing a box around
     * Paris, then the user will be able to zoom in on Paris, will be
     * able to pan around Paris, but will not be able to pan or zoom
     * outside of Paris.
     * - If an inner boundary for the Eiffel Tower and an outer
     * boundary for Paris are supplied, then the user will be able to
     * zoom and pan in and around Paris (but not outside of Paris) such
     * that the Eiffel Tower is always on the map.
     *
     * It is possible for the boundary's aspect ratio to differ from
     * that of the view. For example, if the @c MapView is square (1x1
     * aspect ratio) and the @c outerBoundary has a 2x1 ratio, then the
     * map's view will be expanded such that the entire @c
     * outerBoundary is visible.
     *
     * If both parameters are invalid, then the view boundaries are
     * removed. This is equivalent to calling @c resetViewBoundaries().
     *
     * It is a requirement that the @c innerBoundary is within the box
     * of the @c outerBoundary.
     *
     * If the currently-displayed section of the map does not satisfy
     * the inner and outer boundaries, the map will be adjusted accordingly.
     *
     * @param innerBoundary The user will not be able to set the map's
     * view such that its borders are within this boundary. In
     * essence, the user will not be able to zoom further zoom into
     * this zone. An invalid @c BoundingBox indicates no inner boundary.
     * @param outerBoundary The user will not be able to view the map
     * beyond of this boundary. An invalid @c BoundingBox indicates no
     * outer boundary.
     * @return @c true if the view boundaries were changed as
     * a result of this call, @c false otherwise. Boundaries are not
     * changed if the inner boundary is not fully contained within
     * the outer boundary, or if the supplied parameters match the
     * current boundaries for this object.
     * @since BlackBerry 10.2.0
     */
    bool setViewBoundaries( const bb::platform::geo::BoundingBox& innerBoundary,
                            const bb::platform::geo::BoundingBox& outerBoundary );

    /**
     * @brief Removes all view boundaries.
     *
     * @see setViewBoundaries
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetViewBoundaries();

    /**
     * @brief Retrieves the inner view boundary.
     *
     * @see setViewBoundaries
     *
     * @return The inner view boundary.
     * @since BlackBerry 10.2.0
     */
    bb::platform::geo::BoundingBox innerViewBoundary() const;

    /**
     * @brief Retrieves the outer view boundary.
     *
     * @see setViewBoundaries
     *
     * @return The outer view boundary.
     * @since BlackBerry 10.2.0
     */
    bb::platform::geo::BoundingBox outerViewBoundary() const;

    /**
     * @brief Resets the @c MapData to a new empty @c MapData instance.
     *
     * The existing @c MapData and all @c DataProvider instances owned by it will be
     * deleted.
     *
     * @since BlackBerry 10.2.0
     */
    void resetMapData();

    /**
     * @brief Determines if inline traffic mapping is enabled.
     *
     * @return @c true if enabled, @c false otherwise.
     * @since BlackBerry 10.2.0
     */
    Q_REVISION( 1 )
    bool isInlineTrafficEnabled() const;

    /**
     * @brief Enables (or disables) inline traffic mapping.
     *
     * Note: If inline traffic is not supported, setting this
     * attribute will have no effect.
     *
     * @param @c true to enable, @c false to disable inline traffic
     * mapping.
     * @see isInlineTrafficSupported
     * @since BlackBerry 10.2.0
     */
    Q_REVISION( 1 )
    void setInlineTrafficEnabled( bool enabled );

    /**
     * @brief Resets inline traffic mapping to its default state
     * of disabled.
     *
     * @since BlackBerry 10.2.0
     */
    Q_REVISION( 1 )
    void resetInlineTrafficEnabled();

    /**
     * @brief Determines if inline traffic data is available for
     * the current map view.
     *
     * @return @c true if inline traffic data is available within
     * the current map view, @c false otherwise.
     * @since BlackBerry 10.2.0
     */
    Q_REVISION( 1 )
    bool isInlineTrafficAvailable() const;

    /**
     * @brief Determines if the current @c RenderEngine implementation
     * supports the inclusion of inline traffic mapping.
     *
     * @return @c true if supported, @c false otherwise.
     * @since BlackBerry 10.2.0
     */
    Q_REVISION( 1 )
    bool isInlineTrafficSupported() const;

    /**
     * @brief The amount of time it takes to perform an animation.
     *
     * See @ref sec_animation_overview for additional information.
     *
     * @since BlackBerry 10.3.0
     */
    Q_REVISION( 2 )
    int animationDuration() const;

    /**
     * @brief Sets the amount of time it takes to perform an animation.
     *
     * See @ref sec_animation_overview for additional information.
     *
     * @param milliSeconds The new amount of time it should take for
     * an animation to run to completion.
     * @since BlackBerry 10.3.0
     */
    Q_REVISION( 2 )
    Q_SLOT void setAnimationDuration( int milliSeconds );

    /**
     * @brief Resets the amount of time it takes to perform a
     * animation to the default value.
     *
     * See @ref sec_animation_overview for additional information.
     *
     * @since BlackBerry 10.3.0
     */
    Q_REVISION( 2 )
    Q_SLOT void resetAnimationDuration();

    /**
     * @brief Indicates if the map's animation is currently running.
     *
     * See @ref sec_animation_overview for additional information.
     *
     * @return @c true if the map's animation is currently running,
     * @c false otherwise.
     * @since BlackBerry 10.3.0
     */
    Q_REVISION( 2 )
    bool isAnimationActive() const;

Q_SIGNALS:

    /**
     * @brief Emitted when the view's altitude has changed.
     *
     * @since BlackBerry 10.0.0
     */
    void altitudeChanged( double newAlt );

    /**
     * @brief Emitted when the view's altitude mode has changed.
     *
     * @since BlackBerry 10.0.0
     */
    void altitudeModeChanged( bb::platform::geo::AltitudeMode::Type mode );

    /**
     * @brief Emitted when the view's heading has changed.
     *
     * @since BlackBerry 10.0.0
     */
    void headingChanged( double newHeading );

    /**
     * @brief Emitted when the view's latitude has changed.
     *
     * @since BlackBerry 10.0.0
     */
    void latitudeChanged( double newLat );

    /**
     * @brief Emitted when the view's longitude has changed.
     *
     * @since BlackBerry 10.0.0
     */
    void longitudeChanged( double newLon );

    /**
     * @brief Emitted when the view's tilt angle has changed.
     *
     * @since BlackBerry 10.0.0
     */
    void tiltChanged( int newTilt );

    /**
     * @brief Emitted when the element with focus has changed.
     *
     * @since BlackBerry 10.0.0
     */
    void focusedIdChanged( const QString& idWithFocus );

    /**
     * @brief Emitted when followed ID has changed.
     *
     * @since BlackBerry 10.0.0
     */
    void followedIdChanged( const QString& idOfFollowed );

    /**
     * @brief Initiates a new render. (Asynchronous)
     *
     * @since BlackBerry 10.0.0
     */
    void requestRender();

    /**
     * @brief Emitted whenever a @c Geographic is tapped.
     * Listeners should show additional information associated with
     * this element.  For example, display details.
     *
     * @param id The ID of the location that was tapped.
     *
     * @since BlackBerry 10.0.0
     */
    void locationTapped( const QString& id ) const;

    /**
     * @brief Emitted when an element has had a long-press performed
     * on it.
     * Listeners should show actions available for this element.  For
     * example, show crosscut menu.
     *
     * @param id The ID of the @c GeoLocation that was interacted with.
     *
     * @since BlackBerry 10.0.0
     */
    void locationLongPressed( const QString& id ) const;

    /**
     * @brief Emitted when a long press has occurred on the map.
     *
     * This differs from @c locationLongPressed in that this signal
     * is generated when a long press occurs at a location not associated
     * with a @c GeoLocation. Whereas @c locationLongPressed is generated
     * when a long press occurs on a @c GeoLocation.
     *
     * @param coordinates The world coordinates where the long press
     * occurred.
     *
     * @since BlackBerry 10.0.0
     */
    void mapLongPressed( const bb::platform::geo::Point& coordinates ) const;

    /**
     * @brief Emitted when the button on the focused geographic caption
     * bubble is clicked.
     *
     * @since BlackBerry 10.0.0
     */
    void captionButtonClicked() const;

    /**
     * @brief Emitted when the text label on the focused geographic
     * caption bubble is tapped.
     *
     * @since BlackBerry 10.0.0
     */
    void captionLabelTapped( bb::cascades::TapEvent* tapEvent ) const;

    /**
     * @brief Emitted when the caption's content container changes.
     *
     * @see setCaptionContent( bb::cascades::Container* )
     *
     * @since BlackBerry 10.2.0
     */
    Q_REVISION( 1 )
    void captionContentChanged( bb::cascades::Container* newContent );

    /**
     * @brief Emitted when the @c MapData changes.
     *
     * @see setMapData( bb::cascades::maps::MapData* )
     *
     * @since BlackBerry 10.2.0
     */
    Q_REVISION( 1 )
    void mapDataChanged( bb::cascades::maps::MapData* mapData );

    /**
     * @brief Emitted when the enabled state for inline traffic
     * mapping changes.
     *
     * @param enabled @c true if inline traffic is enabled, @c false
     * otherwise.
     * @since BlackBerry 10.2.0
     */
    Q_REVISION( 1 )
    void inlineTrafficEnabledChanged( bool enabled );

    /**
     * @brief Emitted when the availability of inline traffic data
     * changes for the current map view.
     *
     * @param available @c true if inline traffic is available, @c false
     * otherwise.
     * @since BlackBerry 10.2.0
     */
    Q_REVISION( 1 )
    void inlineTrafficAvailableChanged( bool available );

    /**
     * @brief Emitted when the support for inline traffic mapping changes.
     *
     * @param supported @c true if inline traffic is supported, @c false otherwise.
     * @since BlackBerry 10.2.0
     */
    Q_REVISION( 1 )
    void inlineTrafficSupportedChanged( bool supported );

    /**
     * @brief Emitted when the duration of an animation changes.
     *
     * See @ref sec_animation_overview for additional information.
     *
     * @param milliseconds The new animation duration value.
     * @since BlackBerry 10.3.0
     */
    Q_REVISION( 2 )
    Q_SIGNAL void animationDurationChanged( int milliseconds );

    /**
     * @brief Emitted when the map's animation starts or stops.
     *
     * See @ref sec_animation_overview for additional information.
     *
     * @param animationActivity @c true if the animation is active,
     * @c false otherwise.
     * @since BlackBerry 10.3.0
     */
    Q_REVISION( 2 )
    Q_SIGNAL void animationActiveChanged( bool animationActivity );

private:
    /** @cond PRIVATE */
    Q_DECLARE_PRIVATE( MapView )
    MapViewPrivate* d_ptr;
    Q_DISABLE_COPY( MapView );
    /** @endcond */
};

} /* namespace maps */
} /* namespace cascades */
} /* namespace bb */

#endif /* BB_CASCADES_MAPS_MAPVIEW_HPP */
