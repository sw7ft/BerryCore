/**
 * @copyright
 * Copyright BlackBerry Limited, 2012-2014
 * BlackBerry Limited. All rights reserved.
 */
#ifndef BB_CASCADES_MAPS_MAPLONGPRESSTOPINDROP_HPP
#define BB_CASCADES_MAPS_MAPLONGPRESSTOPINDROP_HPP

#include <bb/cascades/maps/Global>

#include <QObject>

namespace bb
{
namespace cascades
{
namespace maps
{
class MapView;
class MapLongPressToPinDropPrivate;

/**
 * @headerfile MapLongPressToPinDrop.hpp <bb/cascades/maps/MapLongPressToPinDrop>
 *
 * @brief A utility action class for performing a pin drop, which is the
 * creation of a new point of interest (pin) triggered
 * by a user's action.
 *
 * This class connects to the @c MapView::mapLongPressed() signal.  When
 * a user performs a long-press on an empty map space, this class creates
 * the new pin.
 *
 * The steps taken by this class to create the pin are as follows:
 * - Create a new @c GeoLocation at the point the map was pressed.
 * - Asynchronously initiate a reverse geocode to get the street address.
 * - Set the map's focus to the new pin.
 * - Emit a @c pinCreated() signal.
 * - Update the name of the @c GeoLocation with the address information,
 *   when the reverse geocode has completed.
 *
 * This action is connected to a @c MapView instance. When the action and a
 * map are associated, the @c MapView object becomes the parent of the action
 * object. Thus, when an instance of this class has been created and
 * associated with a @c MapView instance, the instance should not be
 * explicitly destroyed by the client.
 *
 * To connect this action to a @c MapView instance:
 * @snippet libbbcascadesmaps/examples/MapLongPressToPinDrop/src/MapLongPressToPinDropExamples.cpp addmaplongpresstopindroptomapview
 *
 * When a new pin is created, the corresponding new @c GeoLocation object is
 * added to the associated @c MapView's @c MapData object. To retrieve the
 * new @c GeoLocation when the @c pinCreated() signal is emitted:
 * @snippet libbbcascadesmaps/examples/MapLongPressToPinDrop/src/MapLongPressToPinDropExamples.hpp maplongpresstopindroponpincreatedslot
 *
 * @xmlonly
 * <apigrouping group="Location/Maps and map visualization"/>
 * <library name="bbcascadesmaps"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_CASCADES_MAPS_EXPORT MapLongPressToPinDrop : public QObject
{
    Q_OBJECT

public:

    /**
     * @brief Constructor
     * @param map The @c MapView control that this action
     * is to be associated with. This parameter is required and
     * can't be @c NULL.
     *
     * @since BlackBerry 10.0.0
     */
    explicit MapLongPressToPinDrop( bb::cascades::maps::MapView* map );

    /** @brief Destructor.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~MapLongPressToPinDrop();

Q_SIGNALS:

    /**
     * @brief Emitted when a new pin is created.
     * Note: This signal can be emitted before the reverse
     * geocode has completed.
     * @param id The ID of the new @c Geographic entity.
     *
     * @since BlackBerry 10.0.0
     */
    void pinCreated( const QString& id );

    /**
     * @brief Emitted when the reverse geocode of the address of a new
     * pin has completed.
     * @param id The ID of the @c Geographic that was reverse geocoded.
     * @param success @c true if the reverse geocode succeeded,
     * @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    void reverseGeocodeFinished( const QString& id, bool success );

private:
    Q_DISABLE_COPY( MapLongPressToPinDrop )
    Q_DECLARE_PRIVATE( MapLongPressToPinDrop )
    QScopedPointer<MapLongPressToPinDropPrivate> d_ptr;

};

} /* namespace maps */
} /* namespace cascades */
} /* namespace bb */
#endif /* BB_CASCADES_MAPS_MAPLONGPRESSTOPINDROP_HPP */
