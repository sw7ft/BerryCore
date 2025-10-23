/*!
 *  @copyright
 *  Copyright (C) Research In Motion Limited, 2012-2013
 *  Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_ROUTEMAPINVOKER_HPP
#define BB_PLATFORM_ROUTEMAPINVOKER_HPP

#include <bb/platform/Global>
#include <bb/platform/MapInvoker>
#include <bb/platform/MapNavigationMode>
#include <bb/platform/MapTransportationMode>
#include <bb/platform/HandsFreeNavigation>
#include <QObject>
#include <QtDeclarative/QtDeclarative>


namespace bb
{
namespace platform
{

class RouteMapInvokerPrivate;

/*!
 * @headerfile RouteMapInvoker.hpp <bb/platform/RouteMapInvoker>
 *
 * @brief An invoker used to trigger navigation through a map route.
 *
 * @details This invoker can be used inside any widget type
 * (in order to give it a certain visual representation) and thus, when that UI component is activated by the user,
 * this invoker will trigger the actual request to display the route information.
 * 
 * Use example of this invoker in QML code (in conjunction with a button):
 * @code
 * import bb.cascades 1.0
 * import bb.platform 1.0
 *
 * Page {
 *   content: Container {
 *      layout: DockLayout {}
 *
 *      attachedObjects:[  
 *         RouteMapInvoker {
 *            id: routeInvokerID
 *              
 *            // This example shows binding properties to pre-defined values
 *            // For example, you can request a route from Ottawa to Toronto, 
 *            // avoiding the highways.
 *
 *            // You can bind properties to values coming from other widgets 
 *            // within this QML page (for example, text field's input)
 *            startLatitude    :  45.416667         // Ottawa's latitude
 *            startLongitude   : -75.7              // Ottawa's longitude
 *            startName        : "Ottawa, Ontario"
 *            startDescription : "Canada's capital"
 *
 *            endLatitude      : 43.652527          // Toronto's latitude
 *            endLongitude     : -79.381961         // Toronto's longitude
 *            endName          : "Toronto, Ontario"
 *            endDescription   : "My trip's destination"
 *
 *            // Specify any extra route options...
 *            avoidHighwaysEnabled : true
 *
 *            // Specify what should be the center of the map.
 *            centerLatitude : 44.4555
 *            centerLongitude : -77.7744
 *            // 'heading' property is not explicitly set, 
 *            // so it will be: 0 (i.e., facing North).
 *
 *         }
 *      ]
 *
 *      // Make a Cascades button (or any Cascades widget) 
 *      // that can be used to trigger route invoker.
 *      Button {            
 *         verticalAlignment: VerticalAlignment.Center
 *         horizontalAlignment: HorizontalAlignment.Center
 *
 *         text: "Get route"
 *
 *          // When button is clicked, call the invoker by its ID
 *          onClicked: {
 *             routeInvokerID.go();
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
class BB_PLATFORM_EXPORT  RouteMapInvoker : public MapInvoker
{
    Q_OBJECT

    /*!
     * @brief Specifies the start location's latitude.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(double startLatitude READ startLatitude WRITE setStartLatitude RESET resetStartLatitude NOTIFY startLatitudeChanged FINAL)

    /*!
     * @brief Specifies the start location's latitude.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(double startLongitude READ startLongitude WRITE setStartLongitude RESET resetStartLongitude NOTIFY startLongitudeChanged FINAL)

    /*!
     * @brief Specifies the start location's name.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString startName READ startName WRITE setStartName RESET resetStartName NOTIFY startNameChanged FINAL)

    /*!
     * @brief Specifies the start location's description.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString startDescription READ startDescription WRITE setStartDescription RESET resetStartDescription NOTIFY startDescriptionChanged FINAL)

    /*!
     * @brief Specifies the start location's free-form address.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString startAddress READ startAddress WRITE setStartAddress RESET resetStartAddress NOTIFY startAddressChanged FINAL)

    /*!
     * @brief Specifies the end location's latitude.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(double endLatitude READ endLatitude WRITE setEndLatitude RESET resetEndLatitude NOTIFY endLatitudeChanged FINAL)

    /*!
     * @brief Specifies the end location's longitude.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(double endLongitude READ endLongitude WRITE setEndLongitude RESET resetEndLongitude NOTIFY endLongitudeChanged FINAL)

    /*!
     * @brief Specifies the end location's name.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString endName READ endName WRITE setEndName RESET resetEndName NOTIFY endNameChanged FINAL)

    /*!
     * @brief Specifies the end location's description.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString endDescription READ endDescription WRITE setEndDescription RESET resetEndDescription NOTIFY endDescriptionChanged FINAL)

    /*!
     * @brief Specifies the end location's free-form address.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString endAddress READ endAddress WRITE setEndAddress RESET resetEndAddress NOTIFY endAddressChanged FINAL)

    /*!
     * @brief Specifies the hands-free mode, as a way to start the navigation user experience.
	 * 
	 * @see @c bb::platform::HandsFreeNavigation for the list of possible values.
     *
     * @since BlackBerry 10.3.0
     */
    Q_PROPERTY(bb::platform::HandsFreeNavigation::Type handsFreeNavigation READ handsFreeNavigation WRITE setHandsFreeNavigation RESET resetHandsFreeNavigation NOTIFY handsFreeNavigationChanged REVISION 1 FINAL)
	
    /*!
     * @brief Specifies the navigation mode (for example use shortest route, use fastest route).
     *
     * @see @c bb::platform::MapNavigationMode for the list of navigation modes.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::platform::MapNavigationMode::Type navigationMode READ navigationMode WRITE setNavigationMode RESET resetNavigationMode NOTIFY navigationModeChanged FINAL)

    /*!
     * @brief Specifies whether the route should avoid any tolls.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bool avoidTollsEnabled READ isAvoidTollsEnabled WRITE setAvoidTollsEnabled RESET resetAvoidTollsEnabled NOTIFY avoidTollsEnabledChanged FINAL)

    /*!
     * @brief Specifies whether the route should avoid any highways.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bool avoidHighwaysEnabled READ isAvoidHighwaysEnabled WRITE setAvoidHighwaysEnabled RESET resetAvoidHighwaysEnabled NOTIFY avoidHighwaysEnabledChanged FINAL)

    /*!
     * @brief Specifies the mode of transportation (for example, car transportation, pedestrian transportation).
     *
     * @see @c bb::platform::MapTransportationMode for the list of modes of transportation.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::platform::MapTransportationMode::Type transportationMode READ transportationMode WRITE setTransportationMode RESET resetTransportationMode NOTIFY transportationModeChanged FINAL)

public:
    /*!
     * @brief Constructs a @c RouteMapInvoker instance.
     *
     * This is the invoker through which users can set navigation-specific properties.
     *
     * @param parent If not 0, the supplied parent will be responsible for deleting this instance.
     *
     * @since BlackBerry 10.0.0
     */
    explicit RouteMapInvoker(QObject* parent = 0);

    /*!
     * @brief Destroys a @c RouteMapInvoker instance.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~RouteMapInvoker();

    /*!
     * @brief Gets the latitude value of the starting location (for a given navigation route).
     *
     * @return The starting point's latitude.
     *
     * @since BlackBerry 10.0.0
     */
    double startLatitude() const;

    /*!
     * @brief Gets the longitude value of the starting location (for a given navigation route).
     *
     * @return The starting point's longitude.
     *
     * @since BlackBerry 10.0.0
     */
    double startLongitude() const;

    /*!
     * @brief Gets the name of the starting location (for a given navigation route).
     *
     * @return The starting point's name.
     *
     * @since BlackBerry 10.0.0
     */
    QString startName() const;

    /*!
     * @brief Gets the description of the starting location (for a given navigation route).
     *
     * @return The starting point's description.
     *
     * @since BlackBerry 10.0.0
     */
    QString startDescription() const;

    /*!
     * @brief Gets the address of the starting location (for a given navigation route).
     *
     * @return The starting point's address.
     *
     * @since BlackBerry 10.0.0
     */
    QString startAddress() const;

    /*!
     * @brief Gets the latitude value of the end location (for a given navigation route).
     *
     * @return The end point's latitude.
     *
     * @since BlackBerry 10.0.0
     */
    double endLatitude() const;

    /*!
     * @brief Gets the longitude value of the end location (for a given navigation route).
     *
     * @return The end point's longitude.
     *
     * @since BlackBerry 10.0.0
     */
    double endLongitude() const;

    /*!
     * @brief Gets the name of the end location (for a given navigation route).
     *
     * @return The end point's name.
     *
     * @since BlackBerry 10.0.0
     */
    QString endName() const;

    /*!
     * @brief Gets the description of the end location (for a given navigation route).
     *
     * @return The end point's description.
     *
     * @since BlackBerry 10.0.0
     */
    QString endDescription() const;

    /*!
     * @brief Gets the address of the end location (for a given navigation route).
     *
     * @return The end point's address.
     *
     * @since BlackBerry 10.0.0
     */
    QString endAddress() const;

    /*!
     * @brief Indicates if the UI for the route navigation should be presented in a hands-free manner.
	 * If undefined, then receiver should use their default behaviour.
     *
     * @see @c bb::platform::HandsFreeNavigation for the list of possible values. 
     *
     * @return @c The hands free navigation value.
     *
     * @since BlackBerry 10.3.0
     */
    Q_REVISION(1) bb::platform::HandsFreeNavigation::Type handsFreeNavigation() const;	
	
    /*!
     * @brief Gets the navigation mode for a given route
     * (for example, try to find the shortest possible route or the fastest route).
     *
     * @see @c bb::platform::MapNavigationMode for the list of navigation modes.
     *
     * @return The navigation mode.
     *
     * @since BlackBerry 10.0.0
     */
    bb::platform::MapNavigationMode::Type navigationMode() const;

    /*!
     * @brief Indicates if the route should try to avoid any tolls (as an option) in determining a navigation route between two locations.
     *
     * @return @c true if the navigation route should try to avoid any tolls, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isAvoidTollsEnabled() const;

    /*!
     * @brief Indicates if the route should try to avoid any highways (as an option) in determining a navigation route between two locations.
     *
     * @return @c true if the navigation route should try to avoid any highways, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isAvoidHighwaysEnabled() const;

    /*!
     * @brief Gets the mode of transportation for a given route
     * (for example, use pedestrian as the mode of transportation, or use a car).
     *
     * @see @c bb::platform::MapTransportationMode for the list of modes of transportation.
     *
     * @return The transportation mode.
     *
     * @since BlackBerry 10.0.0
     */
    bb::platform::MapTransportationMode::Type transportationMode() const;

public Q_SLOTS:

    /*!
     * @brief Sets the latitude value of the starting location (for a given navigation route).
     *
     * If the start location is not set, it is assumed that the start location is the device's current location.
     *
     * @param value The latitude value.
     *
     * @since BlackBerry 10.0.0
     */
    void setStartLatitude(double value);

    /*!
     * @brief Resets the latitude value of the starting location to an undefined value.
     *
     * @since BlackBerry 10.0.0
     */
    void resetStartLatitude();

    /*!
     * @brief Sets the longitude value of the starting location (for a given navigation route).
     *
     * If the start location is not set, it is assumed that the start location is the device's current location.
     *
     * @param value The longitude value.
     *
     * @since BlackBerry 10.0.0
     */
    void setStartLongitude(double value);

    /*!
     * @brief Resets the longitude value of the starting location to an undefined value.
     *
     * @since BlackBerry 10.0.0
     */
    void resetStartLongitude();

    /*!
     * @brief Sets the name of the starting location (for a given navigation route).
     *
     * @param name The name value.
     *
     * @since BlackBerry 10.0.0
     */
    void setStartName(const QString &name);

    /*!
     * @brief Clears the name value of the starting location.
     *
     * @since BlackBerry 10.0.0
     */
    void resetStartName();

    /*!
     * @brief Sets the description of the starting location (for a given navigation route).
     *
     * @param description The description value.
     *
     * @since BlackBerry 10.0.0
     */
    void setStartDescription(const QString &description);

    /*!
     * @brief Clears the description value of the starting location.
     *
     * @since BlackBerry 10.0.0
     */
    void resetStartDescription();

    /*!
     * @brief Sets the address of the starting location (for a given navigation route).
     *
     * @param address The address value.
     *
     * @since BlackBerry 10.0.0
     */
    void setStartAddress(const QString &address);

    /*!
     * @brief Clears the address value of the starting location.
     *
     * @since BlackBerry 10.0.0
     */
    void resetStartAddress();

    /*!
     * @brief Sets the latitude value of the end location (for a given navigation route).
     *
     * If the end location is not set, it is assumed that the end location is the device's current location.
     *
     * @param value The latitude value.
     *
     * @since BlackBerry 10.0.0
     */
    void setEndLatitude(double value);

    /*!
     * @brief Resets the latitude value of the end location to an undefined value.
     *
     * @since BlackBerry 10.0.0
     */
    void resetEndLatitude();

    /*!
     * @brief Sets the longitude value of the end location (for a given navigation route).
     *
     * If the end location is not set, it is assumed that the end location is the device's current location.
     *
     * @param value The longitude value.
     *
     * @since BlackBerry 10.0.0
     */
    void setEndLongitude(double value);

    /*!
     * @brief Resets the longitude value of the end location to an undefined value.
     *
     * @since BlackBerry 10.0.0
     */
    void resetEndLongitude();

    /*!
     * @brief Sets the name of the end location (for a given navigation route).
     *
     * @param name The name value.
     *
     * @since BlackBerry 10.0.0
     */
    void setEndName(const QString &name);

    /*!
     * @brief Clears the name value of the end location.
     *
     * @since BlackBerry 10.0.0
     */
    void resetEndName();

    /*!
     * @brief Sets the description of the end location (for a given navigation route).
     *
     * @param description The description value.
     *
     * @since BlackBerry 10.0.0
     */
    void setEndDescription(const QString &description);

    /*!
     * @brief Clears the description value of the end location.
     *
     * @since BlackBerry 10.0.0
     */
    void resetEndDescription();

    /*!
     * @brief Sets the address of the starting location (for a given navigation route).
     *
     * @param address The address value.
     *
     * @since BlackBerry 10.0.0
     */
   void setEndAddress(const QString &address);

   /*!
    * @brief Clears the name value of the end location.
    *
    * @since BlackBerry 10.0.0
    */
   void resetEndAddress();
   
   /*!
    * @brief Sets the hands-free navigation.
    * Enabled if route navigation is to use hands free approach, Disabled if navigating the route needs user's input or 
    * Undefined if receiver should use their default behaviour.
    *
    * @param newValue The hands-free navigation value. See @c bb::platform::HandsFreeNavigation for the list of possible values. 
	* By default, this value is set to Undefined.
    *
    * @since BlackBerry 10.3.0
    */
   Q_REVISION(1) void setHandsFreeNavigation(bb::platform::HandsFreeNavigation::Type newValue);

   /*!
    * @brief Resets hands-free navigation to its default value.
    * @see setHandsFreeNavigation(bb::platform::HandsFreeNavigation::Type ) for default value.
	* 
    * @since BlackBerry 10.3.0
    */
   Q_REVISION(1) void resetHandsFreeNavigation();

   /*!
    * @brief Sets the navigation mode.
    *
    * @param mode The navigation mode value.  See @c bb::platform::MapNavigationMode for the list of navigation modes.
    *
    * @since BlackBerry 10.0.0
    */
   void setNavigationMode(bb::platform::MapNavigationMode::Type mode);

   /*!
    * @brief Resets the navigation mode to @c bb::platform::MapNavigationMode::Undefined.
    *
    * @since BlackBerry 10.0.0
    */
   void resetNavigationMode();

   /*!
    * @brief Enables (or disables) the 'avoid tolls' navigation option.
    *
    * @param enable @c true if navigation is to avoid any tolls, @c false if a route can include tolls.
    *
    * @since BlackBerry 10.0.0
    */
   void setAvoidTollsEnabled(bool enable);

   /*!
    * @brief Disables the 'avoid tolls' navigation option.
    *
    * @since BlackBerry 10.0.0
    */
   void resetAvoidTollsEnabled();

   /*!
    * @brief Enables (or disables) the 'avoid highways' navigation option.
    *
    * @param enable @c true if navigation is to avoid any highways, @c false if a route can include highways.
    *
    * @since BlackBerry 10.0.0
    */
   void setAvoidHighwaysEnabled(bool enable);

   /*!
    * @brief Disables the 'avoid highways' navigation option.
    *
    * @since BlackBerry 10.0.0
    */
   void resetAvoidHighwaysEnabled();

   /*!
    * @brief Sets the mode of transportation.
    *
    * @param mode The mode of transportation value.  See @c bb::platform::MapTransportationMode for
    * the list of modes of transportation.
    *
    * @since BlackBerry 10.0.0
    */
   void setTransportationMode(bb::platform::MapTransportationMode::Type mode);

   /*!
    * @brief Resets the mode of transportation to @c bb::platform::MapTransportationMode::Undefined.
    *
    * @since BlackBerry 10.0.0
    */
   void resetTransportationMode();

Q_SIGNALS:

    /*!
     * @brief Emitted when the latitude coordinate of the start location changes.
     *
     * Listeners should update the view to display the start location's new position.
     *
     * @param newStartLatitude The new latitude of the start location.
     *
     * @since BlackBerry 10.0.0
     */
    void startLatitudeChanged(double newStartLatitude);

    /*!
     * @brief Emitted when the longitude coordinate of the start location changes.
     *
     * Listeners should update the view to display the start location's new position.
     *
     * @param newStartLongitude The new longitude of the start location.
     *
     * @since BlackBerry 10.0.0
     */
    void startLongitudeChanged(double newStartLongitude);

    /*!
     * @brief Emitted when the name of the start location changes.
     *
     * Listeners should update the view to display the start location's new name.
     *
     * @param newStartName The new name of the start location.
     *
     * @since BlackBerry 10.0.0
     */
    void startNameChanged(const QString &newStartName);

    /*!
     * @brief Emitted when the description of the start location changes.
     *
     * Listeners should update the view to display the start location's new description.
     *
     * @param newStartDescription The new description of the start location.
     *
     * @since BlackBerry 10.0.0
     */
    void startDescriptionChanged(const QString &newStartDescription);

    /*!
     * @brief Emitted when the address of the start location changes.
     *
     * Listeners should update the view to display the start location's new address.
     *
     * @param newStartAddress The new address of the start location.
     *
     * @since BlackBerry 10.0.0
     */
    void startAddressChanged(const QString &newStartAddress);

    /*!
     * @brief Emitted when the latitude coordinate of the end location changes.
     *
     * Listeners should update the view to display the end location's new position.
     *
     * @param newEndLatitude The new latitude of the end location.
     *
     * @since BlackBerry 10.0.0
     */
    void endLatitudeChanged(double newEndLatitude);

    /*!
     * @brief Emitted when the longitude coordinate of the end location changes.
     *
     * Listeners should update the view to display the end location's new position.
     *
     * @param newEndLongitude The new longitude of the end location.
     *
     * @since BlackBerry 10.0.0
     */
    void endLongitudeChanged(double newEndLongitude);

    /*!
     * @brief Emitted when the name of the end location changes.
     *
     * Listeners should update the view to display the end location's new name.
     *
     * @param newEndName New name of the end location.
     *
     * @since BlackBerry 10.0.0
     */
    void endNameChanged(const QString &newEndName);

    /*!
     * @brief Emitted when the description of the end location changes.
     *
     * Listeners should update the view to display the end location's new description.
     *
     * @param newEndDescription The new description of the end location.
     *
     * @since BlackBerry 10.0.0
     */
    void endDescriptionChanged(const QString &newEndDescription);

    /*!
     * @brief Emitted when the address of the end location changes.
     *
     * Listeners should update the view to display the end location's new address.
     *
     * @param newEndAddress The new address of the end location.
     *
     * @since BlackBerry 10.0.0
     */
    void endAddressChanged(const QString &newEndAddress);

    /*!
     * @brief Emitted when hands-free navigation changes.
     *
     * Listeners should update the view to display the route using this new option value.
     *
     * @param newValue The new hands-free navigation value. See @c bb::platform::HandsFreeNavigation for the list of possible values.
     *
     * @since BlackBerry 10.3.0
     */
    Q_REVISION(1) void handsFreeNavigationChanged(bb::platform::HandsFreeNavigation::Type newValue);
	
    /*!
     * @brief Emitted when the navigation mode option of a route changes.
     *
     * Listeners should update the view to display the route using this new option value.
     *
     * @param newMode The new navigation mode.  See @c bb::platform::MapNavigationMode for the list of navigation modes.
     *
     * @since BlackBerry 10.0.0
     */
    void navigationModeChanged(bb::platform::MapNavigationMode::Type newMode);

    /*!
     * @brief Emitted when the flag for avoiding road tolls changes.
     *
     * Listeners should update the view to display the route using this new option value.
     *
     * @param enable Indicates if toll avoidance is now enabled or not.
     *
     * @since BlackBerry 10.0.0
     */
    void avoidTollsEnabledChanged(bool enable);

    /*!
     * @brief Emitted when the flag for avoiding highways changes.
     *
     * Listeners should update the view to display the route using this new option value.
     *
     * @param enable Indicates if highway avoidance is now enabled or not.
     *
     * @since BlackBerry 10.0.0
     */
    void avoidHighwaysEnabledChanged(bool enable);

    /*!
     * @brief Emitted when the mode of transportation of a route changes.
     *
     * Listeners should update the view to display the route using this new option value.
     *
     * @param newMode The new transportation mode.  See @c bb::platform::MapTransportationMode for the list of modes of transportation.
     *
     * @since BlackBerry 10.0.0
     */
    void transportationModeChanged(bb::platform::MapTransportationMode::Type newMode);

private:
//!@cond PRIVATE
    Q_DECLARE_PRIVATE(RouteMapInvoker);

    Q_DISABLE_COPY(RouteMapInvoker);
//!@endcond
};

} /* namespace platform */
} /* namespace bb */

QML_DECLARE_TYPE(bb::platform::RouteMapInvoker)

#endif /* BB_PLATFORM_ROUTEMAPINVOKER_HPP */
