/**
 * @copyright
 * Copyright BlackBerry Limited, 2013-2014
 * BlackBerry Limited. All rights reserved.
 */
#ifndef BB_CASCADES_MAPS_MAPIMAGECACHEMANAGER_HPP
#define BB_CASCADES_MAPS_MAPIMAGECACHEMANAGER_HPP

#include <bb/cascades/maps/Global>

#include <QSharedDataPointer>

namespace bb
{
namespace cascades
{
namespace maps
{
class MapImageCacheManagerPrivate;

/**
 * @headerfile MapImageCacheManager.hpp <bb/cascades/maps/MapImageCacheManager>
 *
 * @brief Provides management actions on a cache of static map images.
 *
 * @details Caching of map images occurs when using @c MapImageGenerator.
 * The management functions within this manager
 * (for example <code>setCacheEnable(bool enable)</code>, <code>setTotalDataLimit(int newLimit)</code>)
 * work globally on a single shared cache.
 * Thus, even if multiple instances of this manager are created, they all manage a
 * single shared cache instance.
 * Also, there is no reference counting on enabling/disabling of cache.
 *
 * By default, the cache is enabled.
 * By default, the amount of space that map image content can take up is 2 megabytes.
 *
 * The total limit size can be modified but it cannot go beyond the
 * maximum value of 10 megabytes.
 *
 * @xmlonly
 * <apigrouping group="Location/Maps and map visualization"/>
 * <library name="bbcascadesmaps"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_CASCADES_MAPS_EXPORT MapImageCacheManager
{

public:
    /** Default Constructor
     *
     * @since BlackBerry 10.2.0
     */
    MapImageCacheManager();

    /** Default Destructor
     *
     * @since BlackBerry 10.2.0
     */
    ~MapImageCacheManager();

    /**
     * @brief Enables (or disables) the cache.
     *
     * @param enable @c true if cache should be enabled, @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    void setCacheEnabled( bool enable );

    /**
     * @brief Resets the enabling capability on this cache, to the default value.
     * The default value is to enable this cache.
     *
     * @since BlackBerry 10.2.0
     */
    void resetCacheEnabled();

    /**
     * @brief Specifies whether this cache is currently enabled or not.
     *
     * @return @c true if cache is enabled.
     *
     * @since BlackBerry 10.2.0
     */
    bool isCacheEnabled() const;

    /**
     * @brief Sets the new limit on how much space local files can occupy on disk.
     * Setting a new limit may affect contents of the cache.
     *
     * For example, when the new limit value is less than current cache cost, then
     * deletion of existing cache entries will happen automatically.
     *
     * Setting the limit to a value larger than the maximum possible value of
     * 10 megabytes will result in a data limit of 10 megabytes.
     *
     * @param newLimit The new limit (in bytes) for the total size of all data image files on disk.
     *
     * @since BlackBerry 10.2.0
     */
    void setTotalDataLimit( int newLimit );

    /**
     * @brief Resets the amount of space that map image data can take to the default value.
     *
     * @since BlackBerry 10.2.0
     */
    void resetTotalDataLimit();

    /**
     * @brief Returns the amount of space (in bytes) that map image data can take on disk.
     *
     * @return The current limit size (in bytes).
     *
     * @since BlackBerry 10.2.0
     */
    int totalDataLimit() const;

    /**
     * @brief Clears the cache contents.
     *
     * @return @c true if clearing operation completed with no errors, @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool clearCache();

private:
    Q_DISABLE_COPY( MapImageCacheManager );
    QSharedDataPointer<MapImageCacheManagerPrivate> p;
};

}
/* namespace maps */
} /* namespace cascades */
} /* namespace bb */

#endif /* BB_CASCADES_MAPS_MAPIMAGECACHEMANAGER_HPP */
