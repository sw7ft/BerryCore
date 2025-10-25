/*!
 *  @copyright
 *  Copyright (C) Research In Motion Limited, 2012-2013
 *  Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_LOCATIONMAPINVOKER_HPP
#define BB_PLATFORM_LOCATIONMAPINVOKER_HPP

#include <bb/platform/Global>
#include <bb/platform/MapInvoker>
#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace platform
{

class LocationMapInvokerPrivate;

/*!
 * @headerfile LocationMapInvoker.hpp <bb/platform/LocationMapInvoker>
 *
 * @brief An invoker for viewing a certain location (or a set of locations) on a map.
 *
 * @details This invoker can be used inside any widget type
 * (in order to give it a certain visual representation) and thus, when that UI component is activated by the user,
 * this invoker will trigger the actual request to map the contents to be displayed.
 * 
 * Example use of this invoker in QML code (in conjunction with a button):
 * @code
 * import bb.cascades 1.0
 * import bb.platform 1.0
 *
 * Page {
 *   content: Container {
 *      layout: DockLayout {}
 *
 *      attachedObjects:[  
 *         LocationMapInvoker {
 *            id: locationInvokerID
 *              
 *            // This example shows how to bind properties to pre-defined values.
 *            // One can bind properties to values coming from other widgets 
 *            // within this QML page (e.g. text field's input)
 *
 *            centerLatitude :  45.416667    // Ottawa's latitude
 *            centerLongitude : -75.7        // Ottawa's longitude
 *            altitude : 200
 *
 *            // Request for a given POI (point of interest) to be shown 
 *            // on the map also.
 *
 *            locationLatitude : 45.4555
 *            locationLongitude : -75.68
 *            locationName : "My Favorite location"
 *            // 'geocodeLocationEnabled' boolean property is not explicitly set, 
 *            // so it will be false.
 *
 *            // Also request for a search around the center of map 
 *            // (as part of setting properties available on superclass MapInvoker)
 *            searchText : "Music"
 *            searchLatitude : 45.416667
 *            searchLongitude : -75.7
 *            // 'searchMode' property is not explicitly set, 
 *            // so this will be a Radial search
 *         }
 *      ]
 *
 *      // Make a Cascades button (or any Cascades widget) 
 *      // that can be used to trigger location invoker.
 *      Button {            
 *         verticalAlignment: VerticalAlignment.Center
 *         horizontalAlignment: HorizontalAlignment.Center
 *
 *         text: "Map it"
 *
 *          // When button is clicked, call the invoker by its ID            
 *          onClicked: {
 *             locationInvokerID.go();
 *          }
 *      }
 *   }
 * }
 * @endcode
 *
 * @xmlonly
 * <apigrouping group="Location/Maps invocation"/>
 * <library name="bbplatform"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_PLATFORM_EXPORT LocationMapInvoker : public MapInvoker
{
    Q_OBJECT

    /*!
     * @brief Specifies a single point of interest's latitude.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(double  locationLatitude  READ locationLatitude  WRITE setLocationLatitude RESET resetLocationLatitude NOTIFY locationLatitudeChanged FINAL)

    /*!
     * @brief Specifies a single point of interest's longitude.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(double  locationLongitude  READ locationLongitude  WRITE setLocationLongitude RESET resetLocationLongitude NOTIFY locationLongitudeChanged FINAL)

    /*!
     * @brief Specifies a single point of interest's name.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString locationName  READ locationName  WRITE setLocationName RESET resetLocationName NOTIFY locationNameChanged FINAL)

    /*!
     * @brief Specifies a single point of interest's description.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString locationDescription READ locationDescription WRITE setLocationDescription RESET resetLocationDescription NOTIFY locationDescriptionChanged FINAL)

    /*!
     * @brief Specifies whether the point of interest location needs to be geocoded (or reverse geocoded).
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bool geocodeLocationEnabled  READ isGeocodeLocationEnabled  WRITE setGeocodeLocationEnabled RESET resetGeocodeLocationEnabled NOTIFY geocodeLocationEnabledChanged FINAL)

    /*!
     * @brief Specifies all the necessary information about a set of POIs (points of interest).
     *
     * This information must be presented in the form of a KML document.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString kmlContent READ kmlContent WRITE setKmlContent RESET resetKmlContent NOTIFY kmlContentChanged FINAL)

public:

    /*!
     * @brief Constructs a @c LocationMapInvoker instance.
     *
     * This is the invoker through which users can set map view specific properties.
     *
     * @param parent If not 0, the supplied parent will be responsible for deleting this instance.
     *
     * @since BlackBerry 10.0.0
     */
    explicit LocationMapInvoker(QObject* parent = 0);

    /*!
     * @brief Destroys a @c LocationMapInvoker instance.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~LocationMapInvoker();

    /*!
     * @brief Gets the point of interest's latitude.
     *
     * @return The latitude value.
     *
     * @since BlackBerry 10.0.0
     */
    double locationLatitude() const;

    /*!
     * @brief Gets the point of interest's longitude.
     *
     * @return The longitude value.
     *
     * @since BlackBerry 10.0.0
     */
    double locationLongitude() const;

    /*!
     * @brief Gets the point of interest's name.
     *
     * @return The name value.
     *
     * @since BlackBerry 10.0.0
     */
    QString locationName() const;

    /*!
     * @brief Gets the point of interest's description.
     * @return The description value.
     *
     * @since BlackBerry 10.0.0
     */
    QString locationDescription() const;

    /*!
     * @brief Specifies the need for geocoding the POI's (Point Of Interest) location.
     *
     * @return @c true if POI's location needs to be geocoded, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isGeocodeLocationEnabled() const;

    /*!
     * @brief Gets the KML content which specifies a set of POIs (Points Of Interest) along with their
     * attributes (for example, latitude, longitude, name, description).
     *
     * @return The KML-formatted content.
     *
     * @since BlackBerry 10.0.0
     */
    QString kmlContent() const;

public Q_SLOTS:

   /*!
    * @brief Sets the point of interest's latitude.
    *
    * @param value The latitude value.
    *
    * @since BlackBerry 10.0.0
    */
   void setLocationLatitude(double value);

   /*!
    * @brief Resets the point of interest's latitude to an undefined value.
    *
    * @since BlackBerry 10.0.0
    */
   void resetLocationLatitude();

   /*!
    * @brief Sets the point of interest's longitude.
    *
    * @param value The longitude value.
    *
    * @since BlackBerry 10.0.0
    */
   void setLocationLongitude(double value);

   /*!
    * @brief Resets the point of interest's longitude to an undefined value.
    *
    * @since BlackBerry 10.0.0
    */
   void resetLocationLongitude();

   /*!
    * @brief Sets the point of interest's name.
    *
    * @param name The name value.
    *
    * @since BlackBerry 10.0.0
    */
   void setLocationName(const QString &name);

   /*!
    * @brief Resets the point of interest's name to an undefined value.
    *
    * @since BlackBerry 10.0.0
    */
   void resetLocationName();

   /*!
    * @brief Sets the point of interest's description.
    *
    * @param description The description value.
    *
    * @since BlackBerry 10.0.0
    */
   void setLocationDescription(const QString &description);

   /*!
    * @brief Resets the point of interest's description to an undefined value.
    *
    * @since BlackBerry 10.0.0
    */
   void resetLocationDescription();

   /*!
    * @brief Enables or disables geocoding of a POI's location.
    *
    * @param enable @c true if geocoding needs to be performed, @c false otherwise.
    *
    * @since BlackBerry 10.0.0
    */
   void setGeocodeLocationEnabled(bool enable);

   /*!
    * @brief Disables the geocoding of POI's location.
    *
    * @since BlackBerry 10.0.0
    */
   void resetGeocodeLocationEnabled();

   /*!
    * @brief Sets the KML content specifying a set of POIs (Points Of Interest).
    *
    * @param content The KML-formatted content.
    *
    * @since BlackBerry 10.0.0
    */
   void setKmlContent(const QString &content);

   /*!
    * @brief Resets the KML content to an undefined value.
    *
    * @since BlackBerry 10.0.0
    */
   void resetKmlContent();

Q_SIGNALS:

    /*!
     * @brief Emitted when the latitude coordinate of a location of interest changes.
     *
     * Listeners should update the view to display the location at the new position.
     *
     * @param newLocationLatitude The new latitude value.
     *
     * @since BlackBerry 10.0.0
     */
    void locationLatitudeChanged(double newLocationLatitude);

    /*!
     * @brief Emitted when the longitude coordinate of a location of interest changes.
     *
     * Listeners should update the view to display the location at the new position.
     *
     * @param newLocationLongitude The new longitude value.
     *
     * @since BlackBerry 10.0.0
     */
    void locationLongitudeChanged(double newLocationLongitude);

    /*!
     * @brief Emitted when the name of a location of interest changes.
     *
     * Listeners should update the view to display the location's new name.
     *
     * @param newLocationName The new location name.
     *
     * @since BlackBerry 10.0.0
     */
    void locationNameChanged(const QString &newLocationName);

    /*!
     * @brief Emitted when the description of a location of interest changes.
     *
     * Listeners should update the view to display the location's new description.
     *
     * @param newLocationDescription The new location description.
     *
     * @since BlackBerry 10.0.0
     */
    void locationDescriptionChanged(const QString &newLocationDescription);

    /*!
     * @brief Emitted when the flag for geocoding (or reverse geocoding) for a location of interest changes.
     *
     * Listeners should update the view to display a geocoded/reverse geocoded location.
     * For example, when flag is @c true and location name is provided, then listener should geocode the location.
     * Also, if flag is @c true and the location latitude and longitude are available but the location name is not provided,
     * then listener should reverse geocode the location.
     *
     * @param enable The new value of the flag.
     *
     * @since BlackBerry 10.0.0
     */
    void geocodeLocationEnabledChanged(bool enable);

   /*!
     * @brief Emitted when there was a value change in the KML content of a location of interest.
     *
     * Listeners should update the view to display the new content, according to new KML document instructions.
     *
     * @param newKmlContent The new value of KML content.
    *
    * @since BlackBerry 10.0.0
     */
    void kmlContentChanged(const QString &newKmlContent);

private:
//!@cond PRIVATE
    Q_DECLARE_PRIVATE(LocationMapInvoker);

    Q_DISABLE_COPY(LocationMapInvoker);
//!@endcond
};

} /* namespace platform */
} /* namespace bb */

QML_DECLARE_TYPE(bb::platform::LocationMapInvoker)

#endif /* BB_PLATFORM_LOCATIONMAPINVOKER_HPP */
