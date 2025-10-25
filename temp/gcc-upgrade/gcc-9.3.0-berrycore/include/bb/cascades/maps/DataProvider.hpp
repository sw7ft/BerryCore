/**
 * @copyright
 * Copyright BlackBerry Limited, 2012-2014
 * BlackBerry Limited. All rights reserved.
 */
#ifndef BB_CASCADES_MAPS_DATAPROVIDER_HPP
#define BB_CASCADES_MAPS_DATAPROVIDER_HPP

#include <bb/cascades/maps/Global>
#include <bb/platform/geo/GeoList>
#include <bb/platform/geo/Point>
#include <bb/platform/geo/BoundingBox>
#include <bb/platform/geo/StyleSheet>

#include <QObject>

class QString;

namespace bb
{
namespace cascades
{
namespace maps
{
class DataProviderPrivate;

/**
 * @headerfile DataProvider.hpp <bb/cascades/maps/DataProvider>
 *
 * @brief A source of mappable data.
 *
 * Dynamic %DataProvider Example
 * ----------------------------
 * It is possible to have a @c DataProvider whose contents change as the map's
 * viewport changes. To accomplish this, create a subclass of @c DataProvider.
 * Add slots to the class to be connected to the signals from @c MapView.
 * For example:
 *
 * @snippet libbbcascadesmaps/examples/DataProvider/src/DataProviderExamples.cpp dynamicdataprovider
 *
 * Finally, emit notifications, such as @c geoAdded(), when elements have been
 * added or removed from the container.
 *
 * Object Ownership
 * ----------------
 * Elements added to this @c DataProvider (that is, instances of @c Geographic
 * objects) are owned by this @c DataProvider. When this @c DataProvider is
 * deleted, all of its @c Geographic objects are also deleted.
 *
 * When this @c DataProvider is added to a @c MapData object, the @c MapData
 * instance owns this object (through parent child relationships).
 *
 * Reference Type
 * --------------
 * @c DataProvider is expected to be used as a <a
 * href="http://en.wikipedia.org/wiki/Reference_type">reference type</a>.
 * As such, care needs to be made when referencing this object in
 * multi-threaded environments. For example, deletion in one thread can
 * cause a dangling pointer in another thread.
 *
 * Also note that the contents of this container
 * (@c bb::platform::geo::Geographic) are also reference types.
 *
 * @xmlonly
 * <apigrouping group="Location/Maps and map visualization"/>
 * <library name="bbcascadesmaps"/>
 * @endxmlonly
 * @since BlackBerry 10.0.0
 */
class BB_CASCADES_MAPS_EXPORT DataProvider : public QObject
{
    Q_OBJECT

    /**
     * @brief The styles associated with the data provider.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(
        bb::platform::geo::StyleSheet styles
        READ styles
        WRITE setStyles
        RESET resetStyles
        NOTIFY stylesChanged
        FINAL )

    /**
     * @brief The visibility of the data provider.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( bool visible READ isVisible WRITE setVisible NOTIFY visibilityChanged FINAL )

    /**
     * @brief The ID of the data provider.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( QString providerId READ providerId WRITE setProviderId NOTIFY providerIdChanged FINAL )

Q_SIGNALS:

    /**
     * @brief Emitted when a @c Geographic element has been added to
     * this data provider.
     *
     * @param providerId The ID of the data provider that the @c
     * Geographic was added to.
     * @param elementId The ID of the element that was added.
     * @since BlackBerry 10.0.0
     */
    void geoAdded( const QString& providerId, const QString& elementId );

    /**
     * @brief Emitted when multiple @c Geographic elements have been
     * added to this data provider.
     *
     * @param providerId The ID of the data provider that the @c
     * Geographic was added to.
     * @param elementIds The IDs of the elements that were added.
     * @since BlackBerry 10.0.0
     */
    void geoAddedBulk( const QString& providerId,
                       const QStringList& elementIds );

    /**
     * @brief Emitted when a @c Geographic element has been removed
     * from this data provider.
     *
     * @param providerId The ID of the data provider that the @c
     * Geographic was removed from.
     * @param elementId The ID of the element that was removed.
     * @since BlackBerry 10.0.0
     */
    void geoRemoved( const QString& providerId, const QString& elementId );

    /**
     * @brief Emitted when multiple @c Geographic elements have been
     * removed from this data provider.
     *
     * @param providerId The ID of the data provider that the @c
     * Geographic was removed from.
     * @param elementIds The IDs of the elements that were removed.
     * @since BlackBerry 10.0.0
     */
    void geoRemovedBulk( const QString& providerId,
                         const QStringList& elementIds );

    /**
     * @brief Emitted when the visibility of this data provider has
     * changed.
     *
     * @param providerId The ID of the data provider whose visibility
     * has changed.
     * @param visible The new visible state.
     * @since BlackBerry 10.0.0
     */
    void visibilityChanged( const QString& providerId, bool visible );

    /**
     * @brief Emitted when the topography of a @c Geographic within this
     * data provider has changed.
     *
     * @param providerId The ID of the data provider that contains the
     * @c Geographic that was changed.
     * @param elementId The ID of the element that was changed.
     * @since BlackBerry 10.1.0
     */
    void topographyChanged( const QString& providerId,
                            const QString& elementId );

    /**
     * @brief Emitted when the @c styles property for this
     * @c DataProvider has changed.
     *
     * @param newStyles The new @c StyleSheet for this provider.
     * @since BlackBerry 10.2.0
     */
    void stylesChanged( const bb::platform::geo::StyleSheet& newStyles );

    /**
     * @brief Emitted when provider ID has changed.
     *
     * @param providerId The new provider ID.
     * @since BlackBerry 10.2.0
     */
    void providerIdChanged( const QString& providerId );

public:

    /**
     * @brief Simple constructor.
     *
     * @details A unique identifier will be generated for the @c
     * providerId property.
     *
     * @param parent The @c QObject parent. If this object is handed to
     * a @c MapData instance, that instance will become this object's
     * parent.
     * @since BlackBerry 10.2.0
     */
    explicit DataProvider( QObject* parent = 0 );

    /**
     * @brief Multi-parameter constructor
     *
     * @param id The unique identifier for this data provider. If this
     * parameter is @c QString::null or empty, a unique ID will be generated.
     * @param parent The @c QObject parent. If this object is handed to
     * a @c MapData instance, that instance will become this object's
     * parent.
     * @since BlackBerry 10.0.0
     */
    explicit DataProvider( const QString& id,
                           QObject* parent = 0 );

    /**
     * @brief Destructor.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~DataProvider();

    /**
     * @brief Gets the unique identifier for this data provider.
     *
     * @since BlackBerry 10.0.0
     */
    QString providerId() const;

    /**
     * @brief Sets the unique identifier for this data provider.
     *
     * @param id The unique identifier for this data provider. If this
     * parameter is @c QString::null or empty, a unique ID will be generated.
     * @since BlackBerry 10.0.0
     */
    void setProviderId( const QString& id );

    /**
     * @brief Determines if this data provider is currently visible or
     * not.
     *
     * @return @c true if is visible, @c false otherwise.
     * @since BlackBerry 10.0.0
     */
    bool isVisible() const;

    /**
     * @brief Makes this data provider visible.
     *
     * @param visible If @c true, the contents of this data provider
     * will become visible to the map (the view will not change to make
     * them "on screen"). If @c false, this data provider's contents
     * will become invisible to the map.
     * @since BlackBerry 10.0.0
     */
    void setVisible( bool visible );

    /**
     * @brief Gets the data for this data provider.
     *
     * @since BlackBerry 10.0.0
     */
    bb::platform::geo::GeoList toGeoList() const;

    /**
     * @brief Adds the element to this data provider's collection.
     *
     * Elements that are added to this data provider become children
     * of this instance. When something has been added, a
     * notification is emitted.
     *
     * @param element The element to be added.
     * @return @c true if the addition was successful, @c false
     * otherwise.
     * @since BlackBerry 10.0.0
     */
    bool add( bb::platform::geo::Geographic* element );

    /**
     * @brief Adds all the @c Geographic elements to this data
     * provider.
     *
     * Elements that are added to this data provider become children
     * of this instance. When all these elements are added,
     * a single notification is emitted.
     *
     * @param elements The elements to be added.
     * @return The number of elements added.
     * @since BlackBerry 10.0.0
     */
    int add( const bb::platform::geo::GeoList& elements );

    /**
     * @brief Removes the element with the ID from this data provider's
     * collection.
     *
     * If the element has been successfully removed, then a
     * notification is performed.
     *
     * @param elementId The ID of the element to remove.
     * @return true if the element was removed successfully, @c false
     * otherwise.
     * @since BlackBerry 10.0.0
     */
    bool remove( const QString& elementId );

    /**
     * @brief Removes all the elements with the given IDs from
     * this data provider's collection.
     *
     * A notification is triggered with the elements that have
     * been removed. A removed element is freed from memory.
     *
     * @param elements The list of IDs to be removed.
     * @return The number of elements removed.
     * @since BlackBerry 10.0.0
     */
    int remove( const QStringList& elements );

    /**
     * @brief Removes all data in this data provider.
     *
     * @since BlackBerry 10.0.0
     */
    void clear();

    /**
     * @brief Gets the @c Geographic element with the given ID from
     * this collection.
     *
     * @return @c NULL if the element was not found.
     * @since BlackBerry 10.2.0
     */
    bb::platform::geo::Geographic* geographic( const QString& id ) const;

    /**
     * @brief Retrieves all the visible data that's in the given
     * lat/lon box.
     *
     * @param box The bounding box to search within.
     * @return A list of visible entities.
     * @since BlackBerry 10.0.0
     */
    bb::platform::geo::GeoList find(
        const bb::platform::geo::BoundingBox& box ) const;

    /**
     * @brief Returns the number of @c Geographic elements in this data
     * provider.
     *
     * @since BlackBerry 10.1.0
     */
    int count() const;

    /**
     * @brief Returns the bounding box of the elements within this data
     * provider. If the number of elements is zero, then an invalid box
     * is returned.
     *
     * @return The @c BoundingBox of all elements within this data
     * provider, or an invalid box if there are no elements.
     * @since BlackBerry 10.1.0
     */
    bb::platform::geo::BoundingBox boundingBox() const;

    /**
     * @brief Retrieves the collection of styles to be used when drawing
     * the @c Geographic elements within this data provider.
     *
     * @return The styles for this provider.
     * @since BlackBerry 10.2.0
     */
    bb::platform::geo::StyleSheet styles() const;

    /**
     * @brief Sets the collection of styles to be used when drawing the
     * @c Geographic elements within this data provider.
     *
     * @param styles The new styles for this provider.
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setStyles( const bb::platform::geo::StyleSheet& styles );

    /**
     * @brief Resets the collection of styles to an empty collection.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetStyles();

private:
    /** @cond PRIVATE */
    Q_DISABLE_COPY( DataProvider )
    Q_DECLARE_PRIVATE( DataProvider )
    DataProviderPrivate* d_ptr;
    /** @endcond */
};

} /* namespace maps */
} /* namespace cascades */
} /* namespace bb */
#endif /* BB_CASCADES_MAPS_DATAPROVIDER_HPP */
