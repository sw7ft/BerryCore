/**
 * @copyright
 * Copyright BlackBerry Limited, 2012-2014
 * BlackBerry Limited. All rights reserved.
 */
#ifndef BB_CASCADES_MAPS_RENDERENGINE_HPP
#define BB_CASCADES_MAPS_RENDERENGINE_HPP

#include <bb/cascades/maps/Global>
#include <bb/platform/geo/Point>
#include <bb/cascades/maps/RenderEngineInfo>

#include <bb/ImageData>
#include <QPoint>
#include <QObject>

namespace bb
{
namespace cascades
{
namespace maps
{
class ViewProperties;
class RenderEngineConfiguration;
class MapData;

/**
 * @headerfile RenderEngine.hpp <bb/cascades/maps/RenderEngine>
 *
 * @brief The common interface for all rendering engine implementations.
 *
 * Communication Between MapView and RenderEngine
 * ----------------------------------------------
 * The only object that directly talks to a render engine instance is the
 * @c MapView class. A majority of the operations triggered by @c MapView are
 * synchronous in nature, and thus are blocking. Some of these calls could
 * be executed on the main GUI event thread (for example,
 * @c RenderEngine::windowToWorld). The exception to this is slot operations.
 * These are executed asynchronously using Qt's queued messaging system.
 *
 * Synchronous methods need to return **very** promptly. If they require
 * longer, a separate thread should be spawned to turn it into an
 * asynchronous operation.
 *
 * Render Engine Timeline
 * ----------------------
 * Creation and Metadata: The render engine instance will be created using
 * the default, empty constructor. At that point, the framework can query
 * the properties of the engine. At this point, the engine should not be
 * consuming any significant portion of memory.
 *
 * Configuration: Once it has been determined that the engine is going
 * to be used, its initialize() operation is called to set up the engine.
 * At this point, the engine can set itself up, ready to perform renders.
 *
 * Render Cycle: While an engine is in use, its render() operation
 * will be executed in a separate thread. It is at this point that the
 * engine needs to convert geographic data into OpenGL calls. Once a single
 * render cycle has completed, the renderCompleted() signal has to be
 * emitted so that the framework is notified.
 *
 * The render cycle needs to complete in a timely fashion. If a long-term
 * process needs to be performed (such as downloading data), then the action
 * should be initiated off-thread and the @c render() operation completed.
 * Once the long-term process has completed, the render can resume, and
 * then the @c renderCompleted() signal can be emitted.
 *
 * Closure: Once the framework has finished with the engine (but before
 * destruction), the @c teardown() operation will be executed. At this point,
 * the engine instance should clean up as much as possible. However, it may
 * be reconfigured / re-initiated again using the @c initialize() operation.
 * (The @c teardown() operation will be executed on the thread with @c MapView
 * affinity: the GUI thread.)
 *
 * Destruction: The engine's destructor is only called once the
 * framework is, itself, destructed.
 *
 * Note: Due to the fact that the engine may be in memory, but not in
 * use, it is important that the engine be as memory efficient as possible.
 * Thus, only between the @c initialize() and @c teardown() states should the
 * engine consider itself "actively rendering".
 *
 * Memory Management
 * -----------------
 * When an instance of this class is handed to a @c MapView instance, the
 * @c MapView claims ownership of the render engine. Thus, @c MapView is
 * responsible for the destruction of the @c RenderEngine when it has been
 * given to the @c MapView.
 *
 * Reference Data and Thread Safety
 * --------------------------------
 * @c RenderEngine implementations need to be aware that the @c MapData
 * object is not thread safe. As such, care needs to be taken with
 * dangling pointers to @c Geographic and @c DataProvider objects.
 *
 * How to Make a RenderEngine a Plug-in
 * ------------------------------------
 * @c RenderEngine instances can be automatically discovered and used by
 * @c MapView if they follow a plug-in format. To do this:
 *
 * - Have the engine subclass @c RenderEngine
 *
 * - Declare it as an implementation of the @c RenderEngine interface by using
 * the @c Q_INTERFACES macro, which gets placed under the @c Q_OBJECT macro
 * in the engine's header file:
 * @code
 * Q_INTERFACES( bb::cascades::maps::RenderEngine )
 * @endcode
 *
 * - Export the engine as a plug-in using the @c Q_EXPORT_PLUGIN2 macro,
 * where @c project_target is the name of the project's @c TARGET value
 * in the @c .pro file, and @c plugin_classname is the name of the class
 * extending RenderEngine:
 * @code
 * Q_EXPORT_PLUGIN2( project_target, plugin_classname )
 * @endcode
 * The macro gets placed at the bottom of the engine's CPP implementation
 * file.
 *
 * - Build the engine as a plugin, and bundle it as a shared library by
 * adding the following to the project's @c .pro file:
 * @code
 * CONFIG += shared plugin
 * @endcode
 *
 * - Deploy the plugin library to one of the following locations:
 *   - <tt>/usr/lib/qt4/plugins/mapview-renderengine</tt> - for system-wide
 *     plugins
 *   - <tt>[application root]/app/native/lib/mapview-renderengine</tt> -
 *     for application specific plugins.
 *
 * Target Audience
 * ---------------
 * This class is designed for clients wishing to extend MapView only.
 *
 * @xmlonly
 * <apigrouping group="Location/Maps and map visualization"/>
 * <library name="bbcascadesmaps"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_CASCADES_MAPS_EXPORT RenderEngine : public QObject
{
    Q_OBJECT

public Q_SLOTS:
    /**
     * @brief Initiates a render cycle using the location information
     * previously provided.
     *
     * Note: This operation will not be called again until it has returned.
     * Thus, there might be a backlog of render requests. It is important
     * that this operation return in a timely fashion so that other
     * messages in the messaging queue can be delivered.
     *
     * @since BlackBerry 10.0.0
     */
    virtual void render() = 0;


Q_SIGNALS:
    /**
     * @brief Indicates to observers that a render cycle has been
     * completed.
     *
     * @since BlackBerry 10.0.0
     */
    void renderCompleted();

    /**
     * @brief Emitted when the @c RenderEngine cannot fully render the
     * current map viewing area.
     *
     * @since BlackBerry 10.0.0
     */
    void coverageUnavailable();

    /**
     * @brief Emitted when the "enable inline traffic" state has
     * changed.
     *
     * @param enabled The new state for inline traffic being
     * enabled / disabled.
     * @since BlackBerry 10.2.0
     */
    void inlineTrafficEnabledChanged( bool enabled );

    /**
     * @brief Emitted when the "inline traffic available" state has
     * changed.
     *
     * @param available The availability state for the inline traffic
     * flag.
     * @since BlackBerry 10.2.0
     */
    void inlineTrafficAvailableChanged( bool available );

public:

    /**
     * @brief Base Constructor.
     *
     * @param parent The parent object to this object.
     *
     * @since BlackBerry 10.0.0
     */
    explicit RenderEngine( QObject* parent = 0 );

    /**
     * @brief Destructor.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~RenderEngine();

    /**
     * @brief Creates a new instance of this render engine.
     * This factory method is only used through the plug-in
     * system.
     *
     * @return The new instance of the @c RenderEngine, never null.
     *
     * @since BlackBerry 10.0.0
     */
    virtual bb::cascades::maps::RenderEngine* newInstance() const = 0;

    /**
     * @brief Gets the element ID of the interactable element at the
     * given window coordinates.
     * @param windowCoord the location of the point of interest.
     * @return The ID of the element available, or an empty string if
     * no element exists.
     *
     * @since BlackBerry 10.0.0
     */
    virtual QString elementIdAt( const QPoint& windowCoord ) const = 0;

    /**
     * @brief Initializes the engine.
     *
     * @since BlackBerry 10.0.0
     */
    virtual void initialize( bb::cascades::maps::RenderEngineConfiguration config ) = 0;

    /**
     * @brief Indicates whether base map data is included in the rendered
     * output.
     *
     * Base map data includes items such as ground information,
     * roads, and so on.
     *
     * @return @c true if the base map is included.
     *
     * @since BlackBerry 10.0.0
     */
    virtual bool isBaseMapVisible() const = 0;

    /**
     * @brief Converts the screen coordinates to world coordinates.
     *
     * This is a blocking call (synchronous). See the class level comment
     * titled "Communication Between MapView and RenderEngine".
     *
     * @param windowCoord The coordinates within the viewport's window to
     * convert.
     * @return The coordinates representing the window's coordinates.
     *
     * @since BlackBerry 10.0.0
     */
    virtual bb::platform::geo::Point windowToWorld(
        const QPoint& windowCoord ) const = 0;

    /**
     * @brief Converts a world coordinate into a screen/window
     * coordinate.
     *
     * This is a blocking call.
     *
     * @param worldCoord The world (lat/lon) coordinates to convert.
     * @return The window coordinates representing the world
     * coordinates. The returned coordinates may not be within the
     * current window's view.
     *
     * @since BlackBerry 10.0.0
     */
    virtual QPoint worldToWindow( const bb::platform::geo::Point&
                                  worldCoord ) const = 0;

    /**
     * @brief Calculates a new bounding box based on the view
     * properties provided.
     *
     * @param view The properties of the view to base the
     * calculation on.
     * @return A bounding box that matches the limits of the view.
     *
     * @since BlackBerry 10.0.0
     */
    virtual bb::platform::geo::BoundingBox calculateBoundingBox(
        const bb::cascades::maps::ViewProperties& view ) const = 0;

    /**
     * @brief Changes the properties of the view.
     *
     * This call is not an explicit request to initiate a new render.
     * To initiate a new render use @c RenderEngine::render.
     *
     * This is a blocking call (synchronous). See the class level
     * comment titled "Communication Between MapView and RenderEngine".
     *
     * @param view The new view properties.
     *
     * @since BlackBerry 10.0.0
     */
    virtual void setViewport( const bb::cascades::maps::ViewProperties& view ) = 0;

    /**
     * @brief Gives the render engine the mapping data container
     * holding non-atlas data.
     *
     * @param data The container for mapping data. This parameter is
     * owned by the parent @c MapView instance.
     *
     * @since BlackBerry 10.0.0
     */
    virtual void setMapData( bb::cascades::maps::MapData* data ) = 0;

    /**
     * @brief Sets whether or not the base map should be included in
     * the rendered output.
     *
     * @param visible @c true if the base map should be
     * included.
     *
     * @since BlackBerry 10.0.0
     */
    virtual void setBaseMapVisible( bool visible ) = 0;

    /**
     * @brief Provides an opportunity for the engine to perform any
     * shutdown work.
     *
     * @since BlackBerry 10.0.0
     */
    virtual void teardown() = 0;

    /**
     * @brief Gets the characteristics of this engine.
     *
     * @return The information concerning the characteristics of
     * this engine.
     *
     * @since BlackBerry 10.0.0
     */
    virtual bb::cascades::maps::RenderEngineInfo characteristics() const = 0;

    /**
     * @brief Converts the current map into an image.
     *
     * @return The viewport's content as an image.
     *
     * @since BlackBerry 10.0.0
     */
    virtual bb::ImageData generateMapImage() const = 0;

    /**
     * @brief Indicates whether this render engine has coverage for
     * the given region.
     * Note: Important factors to be considered are center, altitude
     * and bounding box.
     *
     * @param region The region in question.
     * @return @c true if this engine has map coverage for the @b
     * entire region, @c false if partial coverage or no coverage.
     *
     * @since BlackBerry 10.0.0
     */
    virtual bool coverageSupported( const bb::cascades::maps::ViewProperties& region )
        const = 0;

    /**
     * @brief Indicates the priority for which this engine should be used
     * when two engines have coverage over the same area. Thus, if render
     * engine A and B both have coverage over the current viewport,
     * the render engine with the higher priority will be used.
     *
     * Current priorities include:
     * - 5: Reserved for Application-provided plug-in
     * - 4: 3D System Render Engine
     * - 3: 2D System Render Engine
     * - 0: Blank Render Engine (no memory consumption)
     *
     * @return The priority for this render engine. A higher number
     * equals a higher priority. Numbers range from 0 to 5. 5 indicates
     * an RE should absolutely be used, while 3 indicates a "normal"
     * priority.
     *
     * @since BlackBerry 10.0.0
     */
    virtual int coveragePriority() const = 0;

    /**
     * @brief Enables the inclusion of inline traffic within the map.
     *
     * Note: If the render engine doesn't support inline traffic,
     * setting this value will have no effect.
     *
     * @param enabled @c true to enable, @c false to disable inline
     * traffic.
     * @since BlackBerry 10.2.0
     */
    void setInlineTrafficEnabled( bool enabled );

    /**
     * @brief Indicates whether inline traffic has been enabled within
     * this @c RenderEngine.
     *
     * @return @c true to enable, @c false to disable inline
     * traffic.
     * @since BlackBerry 10.2.0
     */
    bool isInlineTrafficEnabled();

    /**
     * @brief Sets the flag indicating if inline traffic is available
     * within the current map view.
     *
     * @details It is the @c RenderEngine's responsibility to call
     * this operation whenever the availability state changes.
     *
     * @param available @c true if traffic data is available for the
     * current view, @c false if no traffic data is available.
     * @since BlackBerry 10.2.0
     */
    void setInlineTrafficAvailable( bool available );

    /**
     * @brief Indicates whether there is inline traffic available for
     * the current map view.
     *
     * @return @c true if traffic data is available for the
     * current view, @c false if no traffic data is available.
     * @since BlackBerry 10.2.0
     */
    bool isInlineTrafficAvailable();

private:
    Q_DISABLE_COPY( RenderEngine );
};

} /* namespace maps */
} /* namespace cascades */
} /* namespace bb */

Q_DECLARE_INTERFACE( bb::cascades::maps::RenderEngine, "com.rim.mapview.renderengine/1.0" );

#endif /* BB_CASCADES_MAPS_RENDERENGINE_HPP */
