/**
 * @copyright
 * Copyright BlackBerry Limited, 2013-2014
 * BlackBerry Limited. All rights reserved.
 */
#ifndef BB_CASCADES_MAPS_GEOGRAPHICSPROVISIONINGBRIDGE_HPP
#define BB_CASCADES_MAPS_GEOGRAPHICSPROVISIONINGBRIDGE_HPP

#include <bb/cascades/maps/Global>
#include <bb/cascades/maps/GeographicsProvisioningBridgeDataSource>
#include <bb/cascades/maps/GeographicsProvisioningBridgeResult>

#include <QObject>
#include <QUrl>

namespace bb
{
namespace cascades
{
namespace maps
{
class GeographicsProvisioningBridgePrivate;
class DataProvider;

/**
 * @headerfile GeographicsProvisioningBridge.hpp <bb/cascades/maps/GeographicsProvisioningBridge>
 *
 * @brief A bridge to translate an external geographic data source into @c Geographic data and add
 * it to a @c DataProvider.
 *
 * The @c GeographicsProvisioningBridge class lets you convert external geographic data, such as a
 * KML file, into @c Geographic data and add it to a @c DataProvider. Data sources can be local or
 * remotely accessed by HTTP. This class is specifically intended to make it easier to populate a
 * @c DataProvider with data in QML.
 *
 * The @c #type property has a default value of @c GeographicsProvisioningBridgeDataSource::AutoDetect,
 * which indicates that the content type should be detected automatically. If this property is set to any other
 * value, automatic detection of content type will not occur and the data will be treated as the provided type.
 *
 * To populate a @c DataProvider with the geographic data from an external source:
 * - Set the @c #source property to the URL of the data source.
 * - Set the @c #destinationProvider property to the destination @c DataProvider.
 * - Call @c GeographicsProvisioningBridge::load() from @c Page::onCreationCompleted().
 *
 * If the @c #destinationProvider property is not set when @c GeographicsProvisioningBridge::load() is
 * called the operation will fail and an error will be emitted.
 *
 * Here is an example in QML:
 *
 * @snippet libbbcascadesmaps/examples/GeographicsProvisioningBridge/assets/main.qml geographicsprovisioningbridge_qml
 *
 * @xmlonly
 * <apigrouping group="Location/Geographic elements"/>
 * <library name="bbcascadesmaps"/>
 * @endxmlonly
 * @since BlackBerry 10.2.0
 */
class BB_CASCADES_MAPS_EXPORT GeographicsProvisioningBridge: public QObject
{
    Q_OBJECT

    /**
     * @brief The source of the data.
     *
     * In QML, relative paths are relative to the QML document in which this object is declared.
     * In C++, relative paths are relative to the application's working directory.
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( QUrl source READ source WRITE setSource NOTIFY sourceChanged FINAL )

    /**
     * @brief The destination @c DataProvider of the data.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( bb::cascades::maps::DataProvider* destinationProvider READ destinationProvider WRITE
                setDestinationProvider NOTIFY destinationProviderChanged FINAL )

    /**
     * @brief The type of data source.
     *
     * This property has a default value of @c GeographicsProvisioningBridgeDataSource::AutoDetect,
     * which indicates that the content type should be detected automatically. If this property
     * is set to any other value, automatic detection of content type will not occur and the data
     * will be treated as the provided type.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( bb::cascades::maps::GeographicsProvisioningBridgeDataSource::Type type READ type WRITE
                setType NOTIFY typeChanged FINAL )

    /**
     * @brief Whether the data source is remote or local.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( bool sourceRemote READ isSourceRemote NOTIFY sourceRemoteChanged FINAL )

Q_SIGNALS:

    /**
     * @brief Emitted when the @c #source property has changed.
     *
     * @param source The new value for the @c source property.
     * @since BlackBerry 10.2.0
     */
    void sourceChanged( QUrl source );

    /**
     * @brief Emitted when the @c #destinationProvider property has changed.
     *
     * @param destinationProvider The new value for the @c dataProvider property.
     * @since BlackBerry 10.2.0
     */
    void destinationProviderChanged( bb::cascades::maps::DataProvider* destinationProvider );

    /**
     * @brief Emitted when the @c #type property has changed.
     *
     * @param type The new value for the @c type property.
     * @since BlackBerry 10.2.0
     */
    void typeChanged( bb::cascades::maps::GeographicsProvisioningBridgeDataSource::Type type );

    /**
     * @brief Emitted when the @c #sourceRemote property has changed.
     *
     * @param sourceRemote The new value for the @c sourceRemote property.
     * @since BlackBerry 10.2.0
     */
    void sourceRemoteChanged( bool sourceRemote );

    /**
     * @brief Emitted when loading operation has finished and the data has been added to
     * the @c DataProvider.
     *
     * @param resultType The result of the loading operation.
     * @param errorMessage An error message if @c resultType is not @c GeographicsProvisioningBridgeResult::Success.
     * @since BlackBerry 10.2.0
     */
    void finished( bb::cascades::maps::GeographicsProvisioningBridgeResult::Type resultType,
                   const QString& errorMessage );

protected:
    /** @cond PRIVATE */
    /**
     * @brief Emitted with the type has changed.
     */
    Q_SIGNAL void typeChanged( int type );

    /**
     * @brief Emitted when finished.
     */
    Q_SIGNAL void finished( int resultType, const QString& errorMessage );
    /** @endcond */

public:

    /**
     * @brief Constructor.
     *
     * @param parent The parent object to this object.
     * @since BlackBerry 10.2.0
     */
    explicit GeographicsProvisioningBridge( QObject* parent = 0 );

    /**
     * @brief Destructor.
     *
     * @since BlackBerry 10.2.0
     */
    virtual ~GeographicsProvisioningBridge();

    /**
     * @brief Gets the current value of the @c #source property.
     *
     * @return The current URL to the data source.
     * @since BlackBerry 10.2.0
     */
    QUrl source() const;

    /**
     * @brief Sets a new URL of the data source.
     *
     * @param source The new URL of the data source.
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setSource( const QUrl& source );

    /**
     * @brief Gets the current destination @c DataProvider.
     *
     * @return The current destination @c DataProvider, or @c NULL if the
     * destination @c DataProvider is not set.
     * @since BlackBerry 10.2.0
     */
    DataProvider* destinationProvider() const;

    /**
     * @brief Sets a new destination @c DataProvider.
     *
     * @param provider The new destination @c DataProvider.
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setDestinationProvider( bb::cascades::maps::DataProvider* provider );

    /**
     * @brief Gets the current value of the @c #type property.
     *
     * @return The current data source type.
     * @since BlackBerry 10.2.0
     */
    GeographicsProvisioningBridgeDataSource::Type type();

    /**
     * @brief Sets the value of the @c #type property.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setType( GeographicsProvisioningBridgeDataSource::Type type );

    /**
     * @brief Gets the current value of the @c #sourceRemote property.
     *
     * @return @c true if the data source is remote, @c false if the data source is local.
     * @since BlackBerry 10.2.0
     */
    bool isSourceRemote();

    /**
     * @brief Loads the data from the data source into the destination provider.
     *
     * The @c finished() signal is emitted when loading is complete.
     *
     * If a network download is already in progress it will be stopped.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void load();

    /**
     * @brief Stops the current load operation if a network download is in progress.
     *
     * If a load operation is stopped no error signal will be emitted.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void abort();

private:
    /** @cond PRIVATE */
    Q_DECLARE_PRIVATE( GeographicsProvisioningBridge )
    Q_DISABLE_COPY( GeographicsProvisioningBridge )
    GeographicsProvisioningBridgePrivate* d_ptr;
    /** @endcond */
};

} /* namespace maps */
} /* namespace cascades */
} /* namespace bb */
#endif /* BB_CASCADES_MAPS_GEOGRAPHICSPROVISIONINGBRIDGE_HPP */
