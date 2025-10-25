/**
 * @copyright
 * Copyright BlackBerry Limited, 2012-2014
 * BlackBerry Limited. All rights reserved.
 */
#ifndef BB_CASCADES_MAPS_RENDERENGINECONFIGURATION_HPP
#define BB_CASCADES_MAPS_RENDERENGINECONFIGURATION_HPP

#include <bb/cascades/maps/Global>

#include <QString>
#include <QSharedDataPointer>

namespace bb
{
namespace cascades
{
namespace maps
{
class RenderEngineConfigurationPrivate;

/**
 * @headerfile RenderEngineConfiguration.hpp <bb/cascades/maps/RenderEngineConfiguration>
 *
 * Configuration information that's passed to a RenderEngine upon
 * initialization.
 *
 * @xmlonly
 * <apigrouping group="Location/Maps and map visualization"/>
 * <library name="bbcascadesmaps"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_CASCADES_MAPS_EXPORT RenderEngineConfiguration
{
public:
    /**
     * @brief Basic constructor.
     *
     * @since BlackBerry 10.0.0
     */
    RenderEngineConfiguration();

    /**
     * @brief Destructor.
     *
     * @since BlackBerry 10.0.0
     */
    ~RenderEngineConfiguration();

    /**
     * @brief Copy Constructor.
     *
     * @param src The object to copy information from.
     *
     * @since BlackBerry 10.0.0
     */
    RenderEngineConfiguration( const RenderEngineConfiguration& src );

    /**
     * @brief Assignment.
     *
     * @param src The object to copy information from.
     *
     * @since BlackBerry 10.0.0
     */
    RenderEngineConfiguration& operator=( const RenderEngineConfiguration& src );

    /**
     * @brief Retrieves the window group name for the
     * @c ForeignWindowControl element.
     *
     * @since BlackBerry 10.0.0
     */
    QString foreignWindowWindowGroup() const;

    /**
     * @brief Retrieves the window ID for the
     * @c ForeignWindowControl element.
     *
     * @since BlackBerry 10.0.0
     */
    QString foreignWindowWindowId() const;

private:
    friend class RenderEngineConfigurationPrivate;
    QSharedDataPointer<RenderEngineConfigurationPrivate> p;
};

} /* namespace maps */
} /* namespace cascades */
} /* namespace bb */
#endif /* BB_CASCADES_MAPS_RENDERENGINECONFIGURATION_HPP */
