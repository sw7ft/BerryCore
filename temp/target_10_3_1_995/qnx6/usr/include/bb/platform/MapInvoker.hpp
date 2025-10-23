/*!
 *  @copyright
 *  Copyright (C) Research In Motion Limited, 2012-2013
 *  Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_MAPINVOKER_HPP
#define BB_PLATFORM_MAPINVOKER_HPP

#include <bb/platform/Global>
#include <bb/platform/MapSearchMode>
#include <QObject>

namespace bb
{
namespace platform
{

class MapInvokerPrivate;

/*!
 * @headerfile MapInvoker.hpp <bb/platform/MapInvoker>
 *
 * @brief Stores common properties that can be set in order to trigger map-related content requests.
 *
 * @details To gain access to more specific map requests, users should use sub-classes of this class
 * (for example, @c bb::platform::LocationMapInvoker and @c bb::platform::RouteMapInvoker).
 * This class also performs the actual map request through the Invocation Framework API.
 *
 * @xmlonly
 * <apigrouping group="Location/Maps invocation"/>
 * <library name="bbplatform"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_PLATFORM_EXPORT MapInvoker : public QObject
{
    Q_OBJECT

    /*!
     * @brief Indicates whether Maps application should start GPS/GeoLocation upon start up.
     *
     * @details This will cause the application to perform a transition to device's current location.
     * This is disabled, by default.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bool currentLocationEnabled READ isCurrentLocationEnabled WRITE setCurrentLocationEnabled RESET resetCurrentLocationEnabled NOTIFY currentLocationEnabledChanged FINAL)

    /*!
     * @brief Property containing the search center's latitude.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(double searchLatitude READ searchLatitude WRITE setSearchLatitude RESET resetSearchLatitude NOTIFY searchLatitudeChanged FINAL)

    /*!
     * @brief Property containing the search center's longitude.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(double searchLongitude READ searchLongitude WRITE setSearchLongitude RESET resetSearchLongitude NOTIFY searchLongitudeChanged FINAL)

    /*!
     * @brief Property containing the actual user's search text.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString searchText READ searchText WRITE setSearchText RESET resetSearchText NOTIFY searchTextChanged FINAL)

    /*!
     * @brief Property which specifies a predefined search mode (for example, linear or radial).
     *
     * @see @c bb::platform::MapSearchMode for the list of search modes.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::platform::MapSearchMode::Type searchMode READ searchMode WRITE setSearchMode RESET resetSearchMode NOTIFY searchModeChanged FINAL)

    /*!
     * @brief Property specifying the map viewing altitude level.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(int altitude READ altitude WRITE setAltitude RESET resetAltitude NOTIFY altitudeChanged FINAL)

    /*!
     * @brief Property specifying the orientation for displaying map's contents.
     *
     * Values are in degrees. Valid values are from 0 to 360.
     * 0 represents a North heading, and 180 represents South heading.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(int heading READ heading  WRITE setHeading RESET resetHeading NOTIFY headingChanged FINAL)

    /*!
     * @brief Property containing the map center's latitude
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(double centerLatitude READ centerLatitude WRITE setCenterLatitude RESET resetCenterLatitude NOTIFY centerLatitudeChanged FINAL)

    /*!
     * @brief Property containing the map center's longitude
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(double centerLongitude READ centerLongitude WRITE setCenterLongitude RESET resetCenterLongitude NOTIFY centerLongitudeChanged FINAL)

public:

    /*!
     * @brief Destroys a @c MapInvoker instance.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~MapInvoker();

    /*!
     * @brief Returns @c true if map contents should show the current location of the device.
     * @return @c true if contents should display the current location of the device.
     *
     * @since BlackBerry 10.0.0
     */
    bool isCurrentLocationEnabled() const;

    /*!
     * @brief Gets the search center's latitude.
     * @return The search center's latitude.
     *
     * @since BlackBerry 10.0.0
     */
    double searchLatitude() const;

    /*!
     * @brief Gets the search center's longitude.
     * @return The search center's longitude.
     *
     * @since BlackBerry 10.0.0
     */
    double searchLongitude() const;

    /*!
     * @brief Gets the search term. 
     *
     * The text value is free-form.
     *
     * @return The search text to be used.
     *
     * @since BlackBerry 10.0.0
     */
    QString searchText() const;

    /*!
     * @brief Returns the search mode that will be used when performing searches
     * (for example, search along a path or a radial search starting from a given location).
     *
     * @see @c bb::platform::MapSearchMode for the list of available search modes.
     *
     * @return The search mode.
     *
     * @since BlackBerry 10.0.0
     */
    bb::platform::MapSearchMode::Type searchMode() const;

    /*!
     * @brief Returns the map viewing altitude level.
     * @return The altitude level value.
     *
     * @since BlackBerry 10.0.0
     */
    int altitude() const;

    /*!
     * @brief Returns the heading for the map's contents.
     * @return The heading value.
     *
     * @since BlackBerry 10.0.0
     */
    int heading() const;

    /*!
     * @brief Returns the map center's latitude.
     * @return The map center's latitude.
     *
     * @since BlackBerry 10.0.0
     */
    double centerLatitude() const;

    /*!
     * @brief Returns the map center's longitude.
     * @return The map center's longitude.
     *
     * @since BlackBerry 10.0.0
     */
    double centerLongitude() const;

public Q_SLOTS:

    /*!
     * @brief Enables (or disables) the display of the current location of the device.
     * @param enable @c true if current location of the device should be be displayed, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    void setCurrentLocationEnabled(bool enable);

    /*!
     * @brief Disables the display of the current location of the device.
     *
     * @since BlackBerry 10.0.0
     */
    void resetCurrentLocationEnabled();

    /*!
     * @brief Sets the search center's latitude.
     * @param value The new search latitude.
     *
     * @since BlackBerry 10.0.0
     */
    void setSearchLatitude(double value);

    /*!
     * @brief Resets the search latitude to an undefined value.
     *
     * @since BlackBerry 10.0.0
     */
    void resetSearchLatitude();

    /*!
     * @brief Sets the search center's longitude.
     * @param value The new search longitude.
     *
     * @since BlackBerry 10.0.0
     */
    void setSearchLongitude(double value);

    /*!
     * @brief Resets the search longitude to an undefined value.
     *
     * @since BlackBerry 10.0.0
     */
    void resetSearchLongitude();

    /*!
     * @brief Sets the search term.
     * @param text The search text.
     *
     * @since BlackBerry 10.0.0
     */
    void setSearchText(const QString &text);

    /*!
     * @brief Clears the search text.
     *
     * @since BlackBerry 10.0.0
     */
    void resetSearchText();

    /*!
     * @brief Sets the search mode.
     * @param mode The search mode.
     *
     * @see @c bb::platform::MapSearchMode for the list of available modes.
     *
     * @since BlackBerry 10.0.0
     */
    void setSearchMode(bb::platform::MapSearchMode::Type mode);

    /*!
     * @brief Resets the search mode to radial search (@c bb::platform::MapSearchMode::Radial).
     *
     * @since BlackBerry 10.0.0
     */
    void resetSearchMode();

    /*!
     * @brief Sets the map viewing altitude level.
     * @param value The new map viewing altitude.
     *
     * @since BlackBerry 10.0.0
     */
    void setAltitude(int value);

    /*!
     * @brief Resets the map viewing altitude to an undefined value.
     *
     * @since BlackBerry 10.0.0
     */
    void resetAltitude();

    /*!
     * @brief Sets the heading for the map's contents.

     * @details Valid values are in degrees, between 0 and 360.
     * @param value The new heading.
     *
     * @since BlackBerry 10.0.0
     */
    void setHeading(int value);

    /*!
     * @brief Resets the map's heading to an undefined value.
     *
     * @since BlackBerry 10.0.0
     */
    void resetHeading();

    /*!
     * @brief Sets the map center's latitude.
     * @param value The new latitude of the map's center.
     *
     * @since BlackBerry 10.0.0
     */
    void setCenterLatitude(double value);

    /*!
     * @brief Resets the map center's latitude to undefined value.
     *
     * @since BlackBerry 10.0.0
     */
    void resetCenterLatitude();

    /*!
     * @brief Sets the map center's longitude.
     * @param value The new longitude of the map's center.
     *
     * @since BlackBerry 10.0.0
     */
    void setCenterLongitude(double value);

    /*!
     * @brief Resets the map center's longitude to an undefined value.
     *
     * @since BlackBerry 10.0.0
     */
    void resetCenterLongitude();

    /*!
     * @brief Triggers the actual request. 
     *
     * Depending on the actual invoker instance used, this will send the appropriate request
     * to the Maps application, through the Invocation Framework.
     *
     * @since BlackBerry 10.0.0
     */
    void go();

Q_SIGNALS:

    /*!
     * @brief Emitted when the flag controlling the display of the current device location changes.
     *
     * Listeners should update the view to display the current location.
     *
     * @param enable The new value of the flag.
     *
     * @since BlackBerry 10.0.0
     */
   void currentLocationEnabledChanged(bool enable);

    /*!
     * @brief Emitted when the latitude coordinate of search location changes.
     *
     * Listeners should update the view to reflect the new search position.
     *
     * @param newSearchLatitude The new value of the latitude coordinate.
     *
     * @since BlackBerry 10.0.0
     */
   void searchLatitudeChanged(double newSearchLatitude);

   /*!
    * @brief Emitted when the longitude coordinate of search location changes.
    *
    * Listeners should update the view to reflect the new search position.
    *
    * @param newSearchLongitude The new value of the longitude coordinate.
    *
    * @since BlackBerry 10.0.0
    */
   void searchLongitudeChanged(double newSearchLongitude);

   /*!
    * @brief Emitted when the search text changes.
    *
    * Listeners should update to reflect the new search text.
    *
    * @param newSearchText The new value of the search text.
    *
    * @since BlackBerry 10.0.0
    */
   void searchTextChanged(const QString &newSearchText);

   /*!
    * @brief Emitted when the search mode changes.
    *
    * Listeners should update to reflect the new search mode.
    *
    * @param newSearchPattern The new search mode.
    * 
    * @see @c bb::platform::MapSearchMode for the list of available search modes.
    *
    * @since BlackBerry 10.0.0
    */
   void searchModeChanged(bb::platform::MapSearchMode::Type newSearchPattern);

   /*!
    * @brief Emitted when the viewing altitude changes.
    *
    * Listeners should update the view to reflect the new altitude.
    *
    * @param newAltitude The new value of the viewing altitude.
    *
    * @since BlackBerry 10.0.0
    */
   void altitudeChanged(int newAltitude);

   /*!
    * @brief Emitted when the map's heading changes.
    *
    * Listeners should update the view to reflect the new heading.
    *
    * @param newHeading The new value of the map's heading.
    *
    * @since BlackBerry 10.0.0
    */
   void headingChanged(int newHeading);

   /*!
    * @brief Emitted when the latitude coordinate of the map's center changes.
    *
    * Listeners should update the view to reflect the new map center.
    *
    * @param newCenterLatitude The new latitude of the map's center.
    *
    * @since BlackBerry 10.0.0
    */
   void centerLatitudeChanged(double newCenterLatitude);

   /*!
    * @brief Emitted when the longitude coordinate of the map's center changes
    *
    * Listeners should update the view to reflect the new map center.
    *
    * @param newCenterLongitude The new longitude of the map's center.
    *
    * @since BlackBerry 10.0.0
    */
   void centerLongitudeChanged(double newCenterLongitude);

protected:

   /*! @cond PRIVATE */
   MapInvoker(QObject* parent, MapInvokerPrivate* d);

   MapInvokerPrivate* d_ptr;
   /*! @endcond */

private:
//!@cond PRIVATE
    Q_DECLARE_PRIVATE(MapInvoker);
    Q_DISABLE_COPY(MapInvoker);
//!@endcond
};

} /* namespace platform */
} /* namespace bb */

#endif /* BB_PLATFORM_MAPINVOKER_HPP */
