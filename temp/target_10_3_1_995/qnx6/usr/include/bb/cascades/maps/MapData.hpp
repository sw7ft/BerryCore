/**
 * @copyright
 * Copyright BlackBerry Limited, 2012-2014
 * BlackBerry Limited. All rights reserved.
 */
#ifndef BB_CASCADES_MAPS_MAPDATA_HPP
#define BB_CASCADES_MAPS_MAPDATA_HPP

#include <bb/cascades/maps/Global>
#include <bb/platform/geo/GeoList>
#include <bb/platform/geo/BoundingBox>
#include <bb/platform/geo/Style>
#include <bb/platform/geo/StyleSheet>

#include <QString>
#include <QObject>

namespace bb
{
namespace platform
{
namespace geo
{
class Geographic;
}
}
}
namespace bb
{
namespace cascades
{
namespace maps
{
class DataProvider;
class MapDataPrivate;

/**
 * @headerfile MapData.hpp <bb/cascades/maps/MapData>
 *
 * @brief A collection of data providers to be represented on a map.
 *
 * Object Ownership
 * ----------------
 * This class is under the ownership of the client application. The
 * client is responsible for creating and destroying this object.
 * However, if the client wants to link the lifetime of this object
 * with a @c MapView instance, then the client needs to explicitly set
 * this object as the child of the @c MapView.
 *
 * When a @c DataProvider instance is given to this object, it becomes
 * a child of this object. When this object is destroyed, so
 * are all of the @c DataProviders inside of it. Additionally, a single
 * @c DataProvider instance cannot be shared across multiple @c MapData
 * instances.
 *
 * @c Geographic elements that are added to this class have their parent set
 * to that of the default provider (see below). Since this class is the parent
 * of that @c DataProvider, this class becomes the indirect parent of the
 * added @c Geographic.
 *
 *
 * Reference Type
 * --------------
 * @c MapData is expected to be used as a <a
 * href="http://en.wikipedia.org/wiki/Reference_type">reference type</a>.
 * As such, care needs to be made when referencing this object in
 * multi-threaded environments. For example, deletion in one thread can
 * cause a dangling pointer in another thread.
 *
 * Also note that the contents of this container
 * (@c bb::platform::geo::DataProvider) are also reference types.
 *
 * Default Provider
 * ----------------
 * Every @c MapData instance has a default @c DataProvider. This object is
 * available to the client to store client created data (such as
 * GeoLocations), without requiring them to create a provider, or
 * write their own provider.
 *
 * The default provider cannot be removed.
 *
 * @xmlonly
 * <apigrouping group="Location/Maps and map visualization"/>
 * <library name="bbcascadesmaps"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_CASCADES_MAPS_EXPORT MapData : public QObject
{
    Q_OBJECT

    /**
     * @brief The styles associated with the data provider.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( bb::platform::geo::StyleSheet styles READ styles WRITE setStyles RESET resetStyles
                NOTIFY stylesChanged FINAL )

    /**
     * @brief The list of @c DataProvider objects associated with the data provider.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( QDeclarativeListProperty< bb::cascades::maps::DataProvider > dataProviders READ
                dataProviders FINAL )

Q_SIGNALS:

    /**
     * @brief Emitted when the focus has changed from one
     * element to another.
     *
     * @param focusedId The ID of the current element in focus.
     *
     * @since BlackBerry 10.0.0
     */
    void focusedIdChanged( const QString& focusedId );

    /**
     * @brief Emitted when a @c Geographic element has been added to
     * a @c DataProvider.
     *
     * @param providerId The ID of the provider that the @c Geographic
     * was added to.
     * @param elementId The ID of the element that was added.
     *
     * @since BlackBerry 10.0.0
     */
    void geoAdded( const QString& providerId, const QString& elementId );

    /**
     * @brief Emitted when multiple @c Geographic elements have been added
     * to a @c DataProvider.
     *
     * @param providerId The ID of the provider that the @c Geographic
     * was added to.
     * @param elementIds The IDs of the elements that were added.
     *
     * @since BlackBerry 10.0.0
     */
    void geoAddedBulk( const QString& providerId, const QStringList& elementIds );

    /**
     * @brief Emitted when a @c Geographic element has been removed
     * from a @c DataProvider.
     *
     * @param providerId The ID of the provider that the @c Geographic
     * was removed from.
     * @param elementId The ID of the element that was removed.
     *
     * @since BlackBerry 10.0.0
     */
    void geoRemoved( const QString& providerId, const QString& elementId );

    /**
     * @brief Emitted when multiple @c Geographic elements have been
     * removed from this @c DataProvider.
     *
     * @param providerId The ID of the provider that the @c Geographic
     * was removed from.
     * @param elementIds The IDs of the elements that were removed.
     *
     * @since BlackBerry 10.0.0
     */
    void geoRemovedBulk( const QString& providerId, const QStringList& elementIds );

    /**
     * @brief Emitted when the visibility of a @c DataProvider has
     * changed.
     *
     * @param providerId The ID of the provider whose visibility
     * has changed.
     * @param visible The new visible state.
     *
     * @since BlackBerry 10.0.0
     */
    void visibilityChanged( const QString& providerId, bool visible );

    /**
     * @brief Emitted when a @c DataProvider has been added to this
     * container.
     *
     * @param providerId The ID of the provider that has been added.
     *
     * @since BlackBerry 10.1.0
     */
    void providerAdded( const QString& providerId );

    /**
     * @brief Emitted when a @c DataProvider has been removed from
     * this container.
     *
     * @param providerId The ID of the provider that has been added.
     *
     * @since BlackBerry 10.1.0
     */
    void providerRemoved( const QString& providerId );

    /**
     * @brief Emitted when a @c Geographic's topography has been changed.
     *
     * @param providerId The ID of the provider that contains the
     * @c Geographic that was changed.
     * @param elementId The ID of the element that was changed.
     *
     * @since BlackBerry 10.1.0
     */
    void topographyChanged( const QString& providerId, const QString& elementId );

    /**
     * @brief Emitted when the @c styles property for this
     * @c MapData has changed.
     *
     * @param newStyles The new @c StyleSheet for this container.
     * @since BlackBerry 10.2.0
     */
    void stylesChanged( const bb::platform::geo::StyleSheet& newStyles );

public:
    /**
     * Constructor
     *
     * @param parent The parent object to this object.
     * @since BlackBerry 10.0.0
     */
    explicit MapData( QObject* parent = 0 );

    /**
     * Destructor
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~MapData();

    /**
     * @brief Adds a new @c DataProvider to the collection.
     *
     * This object takes ownership of the added provider.
     * (See class level documentation.)
     *
     * @param provider The new provider to add.
     * @return @c true if the provider was added successfully,
     * @c false if the provider couldn't be added (due to
     * provider ID collision).
     *
     * @since BlackBerry 10.0.0
     */
    bool addProvider( bb::cascades::maps::DataProvider* provider );

    /**
     * @brief Removes a @c DataProvider from the collection.
     *
     * Note: The default data provider cannot be removed.
     *
     * The memory for the provider is also freed, since it
     * is owned by this object. (See class level documentation.)
     *
     * @param providerId The ID of the provider to remove.
     * @return @c true if the removal was successful, @c false
     * if the provider could not be deleted or does not exist.
     *
     * @since BlackBerry 10.0.0
     */
    bool removeProvider( const QString& providerId );

    /**
     * @brief Gets the number of @c DataProviders in this collection.
     *
     * @return The number of providers in this collection.
     *
     * @since BlackBerry 10.0.0
     */
    int providerCount() const;

    /**
     * @brief Retrieves a list of all the provider IDs within this
     * container.
     *
     * @return A list of provider IDs.
     *
     * @since BlackBerry 10.0.0
     */
    QList<QString> providerIds() const;

    /**
     * @brief Gets the default provider.
     *
     * @return The default provider.
     *
     * @since BlackBerry 10.0.0
     */
    bb::cascades::maps::DataProvider* defaultProvider() const;

    /**
     * @brief Gets the provider with the given ID.
     *
     * @param providerId The ID of the desired @c DataProvider
     * instance.
     * @return The desired provider, or @c NULL if it
     * doesn't exist in this collection.
     *
     * @since BlackBerry 10.0.0
     */
    bb::cascades::maps::DataProvider* provider( const QString& providerId ) const;

    /**
     * @brief Gets the provider that houses the given @c Geographic
     * element.
     *
     * The ownership of the returned object is not transferred to the
     * caller. This @c MapData instance is still the parent / owner of the
     * returned @c DataProvider instance.
     *
     * @param element The @c Geographic element to base the search upon.
     * @return The desired @c DataProvider, or @c NULL if it doesn't exist.
     * @since BlackBerry 10.2.0
     */
    bb::cascades::maps::DataProvider* providerFor(
        const bb::platform::geo::Geographic* element ) const;

    /**
     * @brief Gets the provider that houses the given @c Geographic
     * element, based on its ID.
     *
     * The ownership of the returned object is not transferred to the
     * caller. This @c MapData instance is still the parent / owner of the
     * returned @c DataProvider instance.
     *
     * @param geoId The ID of the @c Geographic element to base the search upon.
     * @return The desired @c DataProvider, or @c NULL if it doesn't exist.
     * @since BlackBerry 10.2.0
     */
    bb::cascades::maps::DataProvider* providerFor(
        const QString& geoId ) const;

    /**
     * @brief Retrieves all the visible data that's in the given
     * latitude/longitude box. This operation is executed on all
     * @c visible providers (non-visible providers are not
     * included).
     *
     * @param box The bounding box to search within.
     * @return A list of visible entities.
     *
     * @since BlackBerry 10.0.0
     */
    bb::platform::geo::GeoList find(
        const bb::platform::geo::BoundingBox& box ) const;

    /**
     * @brief Retrieves the ID of the element that currently has focus.
     * If no element has focus, then the return value is an empty
     * string (@c QString::isEmpty()).
     *
     * If the @c DataProvider containing the element that currently has
     * focus is set invisible the focused ID will be reset.
     *
     * @return ID of the focused element.
     *
     * @since BlackBerry 10.0.0
     */
    QString focusedId() const;

    /**
     * @brief Sets the ID of the element to have focus.
     *
     * If there is no such element with ID @c newId or the @c DataProvider
     * containing the element with ID @c newId is not visible the focused
     * ID will not change.
     *
     * If the @c DataProvider containing the element that currently has
     * focus is set invisible the focused ID will be reset.
     *
     * @param newId the ID of the element that has focus.
     * @return @c true if the focused ID changed, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool setFocusedId( const QString& newId );

    /**
     * @brief Removes the focus from the element that has focus.
     *
     * @since BlackBerry 10.0.0
     */
    void resetFocusedId();

    /**
     * @brief Retrieves the element that currently has focus. If no
     * element has focus, @c NULL is returned.
     *
     * @return The element which has focus.
     *
     * @since BlackBerry 10.0.0
     */
    bb::platform::geo::Geographic* focusedGeographic();

    /**
     * @brief Convenience operation that adds the parameter to
     * the default container.
     *
     * This is equivalent to:
     * @code
     * defaultProvider()->add( geo )
     * @endcode
     *
     * @param geo The @c Geographic to be added.
     * @return @c true if added, @c false otherwise. The @c Geographic
     * is not added if an element with that ID already exists.
     *
     * @since BlackBerry 10.0.0
     */
    bool add( bb::platform::geo::Geographic* geo );

    /**
     * @brief Convenience operation that adds all the @c Geographic elements
     * in the parameter to the default provider.
     *
     * This is equivalent to:
     * @code
     * defaultProvider()->add( elements );
     * @endcode
     *
     * @param elements The @c Geographic elements to be added.
     * @return The number of successfully added elements.
     *
     * @since BlackBerry 10.0.0
     */
    int add( const bb::platform::geo::GeoList& elements );

    /**
     * @brief Convenience operation that removes the @c Geographic
     * with the given ID from the default container.
     *
     * This is equivalent to:
     * @code
     * defaultProvider()->remove( id )
     * @endcode
     *
     * @param id The ID of the @c Geographic to be removed.
     * @return @c true if the element was removed.
     *
     * @since BlackBerry 10.0.0
     */
    bool remove( const QString& id );

    /**
     * @brief Convenience operation that removes all the
     * @c Geographic elements named in the parameter from
     * the default container.
     *
     * This is equivalent to:
     * @code
     * defaultProvider()->remove( elements )
     * @endcode
     *
     * @param elements The @c Geographic elements to be removed.
     * @return The number of successfully removed elements.
     *
     * @since BlackBerry 10.0.0
     */
    int remove( const QStringList& elements );

    /**
     * @brief Convenience operation that retrieves the
     * Geographic with the given ID.
     *
     * This operation searches all @c DataProviders within this
     * object.
     *
     * @param id The ID of the desired @c Geographic.
     * @return The desired Geographic, @c NULL otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bb::platform::geo::Geographic* geographic( const QString& id );

    /**
     * @brief Removes all data in all providers.
     *
     * @since BlackBerry 10.0.0
     */
    void clear();

    /**
     * @brief Returns the number of @c Geographic elements in all the
     * visible providers.
     *
     * @param visibleOnly If @c true, then only the elements from
     * visible providers will be included in the count. If @c false,
     * all visible and invisible elements are counted.
     *
     * @since BlackBerry 10.1.0
     */
    int count( bool visibleOnly = true ) const;

    /**
     * @brief Returns the bounding box of the elements within this
     * model. If the number of elements is zero, then an invalid box
     * is returned.
     *
     * @param visibleOnly If @c true, then the bounding box will
     * contain the elements from visible providers. If @c false, all
     * visible and invisible elements are included.
     * @return The @c BoundingBox of all elements within this provider,
     * or an invalid box if there are no elements.
     *
     * @since BlackBerry 10.1.0
     */
    bb::platform::geo::BoundingBox boundingBox(
        bool visibleOnly = true ) const;

    /**
     * @brief Retrieves the collection of styles to be used when drawing
     * the @c Geographic elements within this container.
     *
     * @return The styles for this provider.
     *
     * @since BlackBerry 10.2.0
     */
    bb::platform::geo::StyleSheet styles() const;

    /**
     * @brief Sets the collection of styles to be used when drawing the @c
     * Geographic elements within this container.
     *
     * @param styles The new styles for this provider.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setStyles( const bb::platform::geo::StyleSheet& styles );

    /**
     * @brief Resets the collection of styles to an empty collection.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetStyles();

    /**
     * @brief Generates a @c Style applicable for the given element where
     * all unresolved style attributes (inherited attributes) have been
     * resolved.
     *
     * The @c Style resolution rules for a @c MapData container are
     * different than the resolution rules for a @c StyleSheet. A @c StyleSheet
     * only knows about itself while a @c MapData instance can contain
     * multiple @c StyleSheet: one for each @c DataProvider plus one for the
     * @c MapData element holding all the @c DataProviders. Thus, style
     * resolution for a @c MapData instance uses the style definition for
     * the @c MapData instance, plus the @c DataProvider that houses the @c
     * Geographic element in question.
     *
     * In brief, the @c MapData's styles override the @c DataProvider's. In
     * more explicit terms, the rules use the following sequence:
     * - from the @c MapData's @c StyleSheet, any styles registered to the @c
     *   element's ID
     * - from the @c DataProvider's @c StyleSheet from which the @c element
     *   resides, any styles registered to the @c element's ID
     * - from the @c MapData's @c StyleSheet, any styles registered to the @c
     *   element's style family
     * - from the @c DataProvider's @c StyleSheet from which the @c element
     *   resides, any styles registered to the @c element's style family
     * - from the @c MapData's @c StyleSheet, any styles registered to the @c
     *   element's class name
     * - from the @c DataProvider's @c StyleSheet from which the @c element
     *   resides, any styles registered to the @c element's class name
     * - from the @c MapData's @c StyleSheet, the default style
     * - from the @c DataProvider's @c StyleSheet from which the @c element
     *   resides, the default style
     * - the system-wide default style
     *
     * @param element The @c Geographic element to find a complete style
     * for.
     * @return A fully populated @c Style instance for the given element.
     *
     * @since BlackBerry 10.2.0
     */
    bb::platform::geo::Style resolveStyle( const bb::platform::geo::Geographic* element ) const;

private:
    /** @cond PRIVATE */
    MapDataPrivate* d_ptr;
    QDeclarativeListProperty< bb::cascades::maps::DataProvider > dataProviders();
    Q_DECLARE_PRIVATE( MapData );
    Q_DISABLE_COPY( MapData );
    /** @endcond */
};

} /* namespace maps */
} /* namespace cascades */
} /* namespace bb */

#endif /* BB_CASCADES_MAPS_MAPDATA_HPP */
