/**
 * @copyright
 * Copyright BlackBerry Limited, 2012-2014
 * BlackBerry Limited. All rights reserved.
 */
#ifndef BB_CASCADES_MAPS_BLANKRENDERENGINE_HPP
#define BB_CASCADES_MAPS_BLANKRENDERENGINE_HPP

#include <bb/cascades/maps/Global>
#include <bb/cascades/maps/RenderEngine>
#include <bb/ImageData>

namespace bb
{
namespace cascades
{
namespace maps
{
class BlankRenderEnginePrivate;

/**
 * @headerfile BlankRenderEngine.hpp <bb/cascades/maps/BlankRenderEngine>
 *
 * @brief An empty render engine, which will be used when no other
 * engine can be found.
 *
 * @xmlonly
 * <apigrouping group="Location/Maps and map visualization"/>
 * <library name="bbcascadesmaps"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_CASCADES_MAPS_EXPORT BlankRenderEngine : public RenderEngine
{
    Q_OBJECT

public:

    /**
     * @brief Basic constructor.
     * @param parent The parent object to this object.
     *
     * @since BlackBerry 10.0.0
     */
    explicit BlankRenderEngine( QObject* parent = 0 );

    virtual ~BlankRenderEngine();

    virtual bb::cascades::maps::RenderEngine* newInstance() const;

    virtual QString elementIdAt( const QPoint& windowCoord ) const;

    virtual void initialize( bb::cascades::maps::RenderEngineConfiguration config );

    virtual bool isBaseMapVisible() const;

    virtual void render();

    virtual bb::platform::geo::Point windowToWorld(
        const QPoint& windowCoord ) const;

    virtual QPoint worldToWindow( const bb::platform::geo::Point&
                                  worldCoord ) const;

    virtual bb::platform::geo::BoundingBox calculateBoundingBox(
        const ViewProperties& view ) const;

    virtual void setViewport( const bb::cascades::maps::ViewProperties& view );

    virtual void setMapData( MapData* data );

    virtual void setBaseMapVisible( bool visible );

    virtual void teardown();

    virtual bb::cascades::maps::RenderEngineInfo characteristics() const;

    virtual bb::ImageData generateMapImage() const;

    virtual bool coverageSupported( const bb::cascades::maps::ViewProperties& region ) const;

    virtual int coveragePriority() const;

private:
    QScopedPointer<BlankRenderEnginePrivate> d_ptr;
    Q_DISABLE_COPY( BlankRenderEngine );
    Q_DECLARE_PRIVATE( BlankRenderEngine );
};

} /* namespace maps */
} /* namespace cascades */
} /* namespace bb */
#endif /* BB_CASCADES_MAPS_BLANKRENDERENGINE_HPP */
