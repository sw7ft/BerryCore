/**
 * @copyright
 * Copyright BlackBerry Limited, 2012-2014
 * BlackBerry Limited. All rights reserved.
 */
#ifndef BB_PLATFORM_GEO_GEOGRAPHIC_HPP
#define BB_PLATFORM_GEO_GEOGRAPHIC_HPP

#include <bb/Global>
#include <bb/platform/geo/Global>
#include <bb/platform/geo/BoundingBox>

#include <QObject>
#include <QScopedPointer>
#include <QString>


namespace bb
{
namespace platform
{
namespace geo
{
class GeographicPrivate;

/**
 * @headerfile Geographic.hpp <bb/platform/geo/Geographic>
 *
 * @brief An entity that can be placed on a map.
 *
 * Identifier Uniqueness
 * ---------------------
 * All instances of @c Geographic must have a unique identifier, which is
 * tracked through the @c id property. If two elements exist within a
 * container (for example, @c GeoList, @c DataProvider, @c MapData or other
 * containers) and have the same ID, then one instance will overwrite the
 * other instance.
 *
 * It is the responsibility of the application to ensure that the IDs used
 * are unique. Note: A unique ID will be generated on object creation if no
 * ID is provided.
 *
 * Subclass Contract
 * -----------------
 * Subclasses must perform the following:
 * - Call @c setBoundingBox(BoundingBox) whenever this object's bounding
 * box changes.
 * - Emit a @c topographyChanged signal when the contents of the @c
 * Geographic have changed.
 *
 * Reference Type
 * --------------
 * @c Geographic and its subclasses are expected to be used as a <a
 * href="http://en.wikipedia.org/wiki/Reference_type">reference type</a>.
 * As such, care needs to be made when referencing this object in
 * multithreaded environments. For example, deletion in one thread can
 * cause a dangling pointer in another thread.
 *
 * @xmlonly
 * <apigrouping group="Location/Geographic elements"/>
 * <library name="bbcascadesmaps"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PLATFORM_GEO_EXPORT Geographic : public QObject
{
    Q_OBJECT

    /**
     * @deprecated Use the @c geoId property instead.
     */
    Q_PROPERTY( QString id READ id WRITE setId NOTIFY idChanged FINAL )

    /**
     * @brief The ID of this @c Geographic object.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( QString geoId READ geoId WRITE setGeoId NOTIFY geoIdChanged FINAL )

    /**
     * @brief The name of this object.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY( QString name READ name WRITE setName NOTIFY nameChanged FINAL )

    /**
     * @brief The description of this object.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY( QString description READ description WRITE setDescription NOTIFY descriptionChanged
                FINAL )

    /**
     * @brief The axis-aligned bounding box in which this object is
     * contained.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY( bb::platform::geo::BoundingBox boundingBox READ boundingBox NOTIFY boundaryChanged
                FINAL )

    /**
     * @brief The style family to be used in conjunction with this element.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( QString styleFamily READ styleFamily WRITE setStyleFamily NOTIFY styleFamilyChanged
                FINAL )

public:
    /**
     * @brief Constructor. If no ID is supplied when constructing a
     * @c Geographic entity, an ID that is guaranteed to be unique
     * will be auto-generated.
     *
     * @param parent The parent of this @c Geographic.
     *
     * @since BlackBerry 10.0.0
     */
    explicit Geographic( QObject* parent = 0 );

    /**
     * @brief Constructor.
     * @param id The identifier for this @c Geographic.
     * @param parent The parent of this @c Geographic.
     *
     * @since BlackBerry 10.0.0
     */
    explicit Geographic( const QString& id, QObject* parent = 0 );

    virtual ~Geographic();

    /**
     * @brief Retrieves the axis-aligned bounding box for this
     * Geographic.
     *
     * @since BlackBerry 10.0.0
     */
    virtual bb::platform::geo::BoundingBox boundingBox() const;

    /**
     * @brief Gets the description of this @c Geographic.
     *
     * @since BlackBerry 10.0.0
     */
    QString description() const;

    /**
     * @brief Sets the description of this @c Geographic.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setDescription( const QString& desc );

    /**
     * @deprecated Use @c geoId() instead.
     */
    QString id() const BB_DEPRECATED;

    /**
     * @brief Gets the unique identifier for this @c Geographic. If two
     * @c Geographics are attribute-wise equal, they still need to have
     * different IDs. The ID needs to be unique within a process.
     *
     * @since BlackBerry 10.2.0
     */
    QString geoId() const;

    /**
     * @deprecated Use @c setGeoId() instead.
     */
    Q_SLOT void setId( const QString& id ) BB_DEPRECATED;

    /**
     * @brief Sets the ID of this @c Geographic.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setGeoId( const QString& id );

    /**
     * @brief Gets the name of this @c Geographic.
     *
     * @since BlackBerry 10.0.0
     */
    QString name() const;

    /**
     * @brief Sets the name of this @c Geographic.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setName( const QString& name );

    /**
     * @brief Gets the style family for this @c Geographic.
     *
     * @since BlackBerry 10.2.0
     * @see StyleSheet
     */
    QString styleFamily() const;

    /**
     * @brief Sets the style family for this @c Geographic.
     *
     * @param styleFamily The new style family for this element.
     * @since BlackBerry 10.2.0
     * @see StyleSheet
     */
    Q_SLOT void setStyleFamily( const QString& styleFamily );

Q_SIGNALS:

    /**
     * @brief Emitted when the description of this @c Geographic changes.
     *
     * @since BlackBerry 10.0.0
     */
    void descriptionChanged( const QString& desc );

    /**
     * @deprecated Use @c geoIdChanged() instead.
     */
    void idChanged( const QString& id ) BB_DEPRECATED;

    /**
     * @brief Emitted when the ID of this @c Geographic changes.
     *
     * @since BlackBerry 10.2.0
     */
    void geoIdChanged( const QString& id );

    /**
     * @brief Emitted when the name of this @c Geographic changes.
     *
     * @since BlackBerry 10.0.0
     */
    void nameChanged( const QString& name );

    /**
     * @brief Emitted by derived classes when the bounding box has
     * changed. See the @c BoundingBox documentation.
     *
     * @since BlackBerry 10.0.0
     */
    void boundaryChanged( const bb::platform::geo::BoundingBox& box );

    /**
     * @brief Emitted when the topography of this @c Geographic
     * changes. A @c Geographic's topography captures the location (or
     * geographic) properties of the element.
     * @param id The ID of this @c Geographic.
     *
     * @since BlackBerry 10.1.0
     */
    void topographyChanged( const QString& id );

    /**
     * @brief Emitted when the style family attribute changes.
     *
     * @since BlackBerry 10.2.0
     */
    void styleFamilyChanged( const QString& newFamily );

    /** @cond PRIVATE */
    void boundingBoxChanged( const BoundingBox& box ) BB_DEPRECATED;
    /** @endcond */

protected:
    void setBoundingBox( const bb::platform::geo::BoundingBox& newBox );

private:
    /** @cond PRIVATE */
    QScopedPointer<GeographicPrivate> d_ptr;
    Q_DISABLE_COPY( Geographic )
    Q_DECLARE_PRIVATE( Geographic );
    /** @endcond */
};


} //namespace geo
} //namespace platform
} //namespace bb
#endif /* BB_PLATFORM_GEO_GEOGRAPHIC_HPP */
