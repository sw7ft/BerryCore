/**
 * @copyright
 * Copyright BlackBerry Limited, 2012-2014
 * BlackBerry Limited. All rights reserved.
 */
#ifndef BB_PLATFORM_GEO_GEO_MARKER_HPP
#define BB_PLATFORM_GEO_GEO_MARKER_HPP

#include <bb/platform/geo/Global>

#include <QSharedDataPointer>
#include <QPoint>
#include <QSize>
#include <QDebug>

namespace bb
{
namespace platform
{
namespace geo
{
class MarkerPrivate;

/**
 * @headerfile Marker.hpp <bb/platform/geo/Marker>
 *
 * @brief A visual representation of a location on a map.
 *
 * Markers are designed to indicate a location's position. Examples of
 * markers include push pins, arrows, or bullseyes.  A marker is a fixed
 * image: when the map is zoomed in or out, the marker stays the same screen
 * size.
 *
 * Markers are defined by the following properties:
 *   - icon URI: the location of the icon image
 *   - icon size: the pixel dimensions of the icon image at the icon URI. Note that
 *   this is not used to scale the image.
 *   - location coordinates: the coordinates within the icon image that is positioned
 *   at the actual location on the map
 *   - caption coordinates: the coordinates within the icon image that the caption
 *   bubble tail points to
 *
 * @xmlonly
 * <apigrouping group="Location/Geographic elements"/>
 * <library name="bbcascadesmaps"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PLATFORM_GEO_EXPORT Marker
{
public:

    /**
     * @brief Creates a @c Marker instance.
     *
     * @since BlackBerry 10.0.0
     */
    Marker();

    /**
     * @brief Creates a @c Marker instance.
     *
     * @param iconUri The URI of the marker's icon. See #setIconUri.
     * @param iconSize The size of the marker's icon. See #setIconSize.
     * @param locCoord The coordinates within the icon to position over the
     * actual location. See #setLocationCoordinate.
     * @param captionCoord The coordinates within the icon that the tail of
     * the focus caption bubble points to. See #setCaptionTailCoordinate.
     *
     * @since BlackBerry 10.0.0
     */
    Marker( const QString& iconUri,
            const QSize& iconSize,
            const QPoint& locCoord,
            const QPoint& captionCoord );

    /**
     * @brief Copy constructor.
     *
     * @param src The object from which to copy information.
     *
     * @since BlackBerry 10.0.0
     */
    Marker( const Marker& src );

    /**
     * @brief Destructor.
     *
     * @since BlackBerry 10.0.0
     */
    ~Marker();

    /**
     * @brief Assignment operator.
     *
     * @param src The object from which to copy information.
     *
     * @since BlackBerry 10.0.0
     */
    Marker& operator=( const Marker& src );

    /**
     * @brief Equality operator.
     *
     * @return @c true if all properties are equal.
     *
     * @since BlackBerry 10.0.0
     */
    bool operator==( const Marker& rhs ) const;

    /**
     * @brief Inequality operator.
     *
     * @return @c true if any property is different.
     *
     * @since BlackBerry 10.0.0
     */
    bool operator!=( const Marker& rhs ) const;

    /**
     * @brief Returns the URI to the icon.
     *
     * @return The URI to the icon, as set in @c setIconUri().
     * @since BlackBerry 10.0.0
     */
    QString iconUri() const;

    /**
     * @brief Returns the absolute path to the icon stated in @c
     * #setIconUri.
     *
     * This operation returns an absolute path to the icon's location
     * using a POSIX format. Thus, any "file://" or "asset:///"
     * protocols have been resolved to local paths, and relative paths
     * have been resolved.
     *
     * This is a read-only property set through @c #setIconUri().
     *
     * @return The absolute path to the icon.
     * @since BlackBerry 10.2.0
     */
    QString absoluteIconPath() const;

    /**
     * @brief Sets the URI location of its graphical icon resource.
     *
     * If the image that the icon points to doesn't exist, or if
     * it is an invalid image, then no marker is displayed on
     * the map.
     *
     * @param uri The path to the local icon. Paths can be
     * absolute paths (eg: @c /usr/hmi/...), relative paths (relative
     * to the application's root directory, eg:
     * @c ./app/native/assets/...), file protocols
     * (eg: @c %file:///...) or asset protocols  (eg: @c asset:///...).
     *
     * @since BlackBerry 10.0.0
     */
    void setIconUri( const QString& uri );

    /**
     * @brief The size of the marker's icon.
     *
     * @return The marker's icon size.
     *
     * @since BlackBerry 10.0.0
     */
    QSize iconSize() const;

    /**
     * @brief Sets the size of the marker's icon.
     *
     * This must be set to the actual dimensions of the icon image as it is
     * used to position the icon on the map. Values that do not match the icon's
     * dimensions will not cause the icon to be scaled, and may result in incorrect
     * rendering of the icon on the map.
     *
     * @param iconSize The new size of the icon.
     *
     * @since BlackBerry 10.0.0
     */
    void setIconSize( const QSize& iconSize );

    /**
     * @brief The coordinates within the marker that overlay the actual
     * location.
     * Examples include the point of a push-pin, the center of a
     * bullseye, or the head of an arrow.
     *
     * @return The coordinates within the marker that represent the
     * location.
     *
     * @since BlackBerry 10.0.0
     */
    QPoint locationCoordinate() const;

    /**
     * @brief Sets the coordinates within the marker that represents
     * the location.
     *
     * @param locCoord The new coordinates within the marker.
     * @see locationCoordinate()
     *
     * @since BlackBerry 10.0.0
     */
    void setLocationCoordinate( const QPoint& locCoord );

    /**
     * @brief The coordinates within the marker where the caption
     * bubble's tail should point to.
     *
     * @return The point within the icon where the caption bubble can
     * safely point to.
     *
     * @since BlackBerry 10.0.0
     */
    QPoint captionTailCoordinate() const;

    /**
     * @brief Sets the coordinates within the marker where the caption
     * bubble's tail should point to.
     *
     * @param captionCoord The point within the icon where the caption
     * bubble can safely point to.
     *
     *
     * @since BlackBerry 10.0.0
     */
    void setCaptionTailCoordinate( const QPoint& captionCoord );

private:
    /** @cond PRIVATE */
    QSharedDataPointer<MarkerPrivate> p;
    /** @endcond */

};

BB_PLATFORM_GEO_EXPORT QDebug operator<<( QDebug dbg, const Marker& pt );

} // namespace geo
} // namespace platform
} // namespace bb

Q_DECLARE_METATYPE( bb::platform::geo::Marker );

#endif // BB_PLATFORM_GEO_GEO_MARKER_HPP
