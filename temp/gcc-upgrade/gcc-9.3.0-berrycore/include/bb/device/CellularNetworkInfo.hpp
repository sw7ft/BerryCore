/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_DEVICE_CELLULARNETWORKINFO_HPP
#define BB_DEVICE_CELLULARNETWORKINFO_HPP

#include <bb/device/Global>
#include <bb/device/CellularService>
#include <bb/device/CellularTechnology>

#include <QObject>
#include <QString>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace device
{

class CellularNetworkInfoPrivate;

/*!
 * @headerfile CellularNetworkInfo.hpp <bb/device/CellularNetworkInfo>
 *
 * @brief Encapsulates the capabilities and state of a connected cellular network.
 *
 * @details The @c CellularNetworkInfo class represents a single network that the cellular 
 * radio is connected to. The radio may be connected to multiple networks simultaneously. 
 * This can occur when using @c CellularTechnology::Cdma1X. The first connected network 
 * (@c CellularTechnology::Evdo or @c CellularTechnology::Lte) will provide data service 
 * and the second network (@c CellularTechnology::Cdma1X) will provide voice service. In 
 * most other cases, only a single network will be connected. Use 
 * @c CellularRadioInfo::networkCount() to determine the total number of connected 
 * networks and @c setIndex() to associate a @c CellularNetworkInfo object with one of 
 * those networks. If no network exists for the current index, all properties report 
 * empty/zero values.
 *
 * The @c CellularNetworkInfo class provides information about which wireless 
 * communication standard and voice/data services the network supports (see @c technology() 
 * and @c services() respectively). It also provides details about the network's identity
 * (see @c name(), @c mobileCountryCode(), and @c mobileNetworkCode()) and radio signal
 * strength (see @c signalStrength()). Use @c isRoaming() to distinguish between a visited
 * network and the user's home network.
 *
 * Location information may be derived using the identity of the base station providing 
 * service for the network. For GSM/UMTS networks, see @c cellId() and 
 * @c locationAreaCode(). For LTE networks, see @c cellId() and @c trackingAreaCode(). For 
 * CDMA networks, see @c baseStationId(), @c networkId(), and @c systemId().
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Radio and SIM"/>
 * <library name="bbdevice"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_DEVICE_EXPORT CellularNetworkInfo : public QObject
{
    Q_OBJECT
    
    /*!
     * @brief Index of the connected network represented by this object (see 
     * @c CellularRadioInfo::networkCount()).
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(int index READ index WRITE setIndex NOTIFY indexChanged FINAL)

    /*!
     * @brief Wireless communication standard used by the network.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::device::CellularTechnology::Type technology READ technology NOTIFY technologyChanged FINAL)

    /*!
     * @brief Bitfield of voice/data services the network supports.
     *
     * @see @c bb::device::CellularService::Type for a list of flag values.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::device::CellularService::Types services READ services NOTIFY servicesChanged FINAL)

    /*!
     * @brief Human readable name of the network.
     *
     * @see @c displayName property for the name displayed by Settings
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString name READ name NOTIFY nameChanged FINAL)

    /*!
     * @brief Unique identifier for the country where the network is located.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString mobileCountryCode READ mobileCountryCode NOTIFY mobileCountryCodeChanged FINAL)

    /*!
     * @brief Unique identifier for the network within its country.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString mobileNetworkCode READ mobileNetworkCode NOTIFY mobileNetworkCodeChanged FINAL)

    /*!
     * @brief Power measurement of the network's radio signal.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(int signalStrength READ signalStrength NOTIFY signalStrengthChanged FINAL)

    /*!
     * @brief Flag indicating whether the device is beyond coverage of its home network.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bool roaming READ isRoaming NOTIFY roamingChanged FINAL)

    /*!
     * @brief Unique identifier for the base station serving the GSM/UMTS/LTE network.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(int cellId READ cellId NOTIFY cellIdChanged FINAL)

    /*!
     * @brief Identifier for the geographic region which contains the base station 
     * serving the GSM/UMTS network.
     *
     * @permissions The application must have the @c access_location_services permission to access this information.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(int locationAreaCode READ locationAreaCode NOTIFY locationAreaCodeChanged FINAL)

    /*!
     * @brief Unique identifier for the geographic region which contains the base station 
     * serving the LTE network.
     *
     * @permissions The application must have the @c access_location_services permission to access this information.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(int trackingAreaCode READ trackingAreaCode NOTIFY trackingAreaCodeChanged FINAL)

    /*!
     * @brief Unique identifier for the base station serving the CDMA network.
     *
     * @permissions The application must have the @c access_location_services permission to access this information.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(int baseStationId READ baseStationId NOTIFY baseStationIdChanged FINAL)

    /*!
     * @brief Identifier for a geographic region which contains the base 
     * station serving the CDMA network.
     *
     * @permissions The application must have the @c access_location_services permission to access this information.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(int networkId READ networkId NOTIFY networkIdChanged FINAL)

    /*!
     * @brief Unique identifier for a geographic region which contains the base station serving 
     * the CDMA network.
     *
     * @permissions The application must have the @c access_location_services permission to access this information.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(int systemId READ systemId NOTIFY systemIdChanged FINAL)
    
    /*!
     * @brief Returns network name as reported by Settings and QuickSettings. On second-tier
     * carriers, the network name returned may be the name of the first-tier carrier, and not
     * the name reported by Settings.
     *
     * @see @c name property for the official name returned by the network
     *
     * @since BlackBerry 10.3.0
     */
    Q_PROPERTY(QString displayName READ displayName NOTIFY displayNameChanged FINAL) 

public:
    /*!
     * @brief Creates a new @c CellularNetworkInfo object which represents the first connected 
     * network (@c index() == 0).
     *
     * @param parent If not 0, the supplied parent will be responsible for deleting this instance.
     *
     * @since BlackBerry 10.0.0
     */
    explicit CellularNetworkInfo(QObject *parent = 0);

    /*!
     * @brief Creates a new @c CellularNetworkInfo object which represents the specified connected 
     * network.
     *
     * @param index Index of the connected network this object will represent (see 
     *              @c CellularRadioInfo::networkCount()).
     * @param parent If not 0, the supplied parent will be responsible for deleting this instance.
     *
     * @since BlackBerry 10.0.0
     */
    explicit CellularNetworkInfo(int index, QObject *parent = 0);

    /*!
     * @brief Destroys this @c CellularNetworkInfo object.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~CellularNetworkInfo();
    
    /*!
     * @brief Retrieves the index of the connected network represented by this object.
     *
     * @return Returns the index of the connected network represented by this object (see 
     * @c CellularRadioInfo::networkCount()).
     *
     * @since BlackBerry 10.0.0
     */
    int index() const;

    /*!
     * @brief Retrieves the wireless communication standard used by the network.
     *
     * @return Returns the wireless communication standard used by the network or 
     * @c CellularTechnology::None if no network is currently connected.
     *
     * @since BlackBerry 10.0.0
     */
    bb::device::CellularTechnology::Type technology() const;
    
    /*!
     * @brief Retrieves a bitfield of voice/data services the network supports.
     *
     * @return Returns a bitfield of voice/data services the network supports or 
     * @c CellularService::None if no network is currently connected.
     *
     * @see @c bb::device::CellularService::Type for a list of flag values.
     *
     * @since BlackBerry 10.0.0
     */
    bb::device::CellularService::Types services() const;
    
    /*!
     * @brief Retrieves the human readable name of the network.
     *
     * @return Returns the human readable name of the network or an empty string if no network is 
     * currently connected or the network does not provide a name. There are certain cases (such as
     * second tier providers) where this may return a valid value that is not expected by the user.
     *
     * @see @c displayName() function for the name used by Settings (probably what the user expects)
     *
     * @since BlackBerry 10.0.0
     */
    QString name() const;
    
    /*!
     * @brief Retrieves the unique identifier for the country where the network is located.
     *
     * @details The mobile country code (MCC) is composed of 3 or 4 decimal digits. For further 
     * details about the structure of the MCC, see ITU-T recommendation E.212.
     *
     * @return Returns the country code of the network encoded as a string or an empty string if no 
     * network is currently connected.
     *
     * @since BlackBerry 10.0.0
     */
    QString mobileCountryCode() const;
    
    /*!
     * @brief Retrieves the unique identifier for the network within its country.
     *
     * @details The mobile network code (MNC) is composed of 2 or 3 decimal digits. For further 
     * details about the structure of the MNC, see ITU-T recommendation E.212.
     *
     * Only GSM, UMTS, and LTE networks support MNC.
     *
     * @return Returns the network code of the network encoded as a string or an empty string if the 
     * network does not support MNC or is not currently connected.
     *
     * @since BlackBerry 10.0.0
     */
    QString mobileNetworkCode() const;
    
    /*!
     * @brief Retrieves a power measurement of the network's radio signal.
     *
     * @details Received signal strength indication (RSSI) is a measurement of radio signal's 
     * power in dBm.
     *
     * @return Returns the RSSI of the network or 0 if no network is currently connected.
     *
     * @since BlackBerry 10.0.0
     */
    int signalStrength() const;
    
    /*!
     * @brief Indicates whether the device is beyond coverage of its home network.
     *
     * @return Returns @c true if the device is connected to a visited network, @c false if the device
     * is connected to its home network or no network.
     *
     * @since BlackBerry 10.0.0
     */
    bool isRoaming() const;

    /*!
     * @brief Retrieves the unique identifier for the base station serving the GSM/UMTS/LTE 
     * network.
     *
     * @details The cell ID is unique only within a location/tracking area (see 
     * @c locationAreaCode() and @c trackingAreaCode()).
     *
     * Only GSM, UMTS, and LTE networks support cell ID.
     *
     * @permissions The application must have the @c access_location_services permission to access this information.
     *
     * @return Returns the cell ID for the base station serving the GSM/UMTS/LTE network or 0 if the 
     * caller does not have sufficient permission, the network technology is not GSM/UMTS/LTE, 
     * or no network is currently connected.
     *
     * @since BlackBerry 10.0.0
     */
    int cellId() const;

    /*!
     * @brief Retrieves the unique identifier for the geographic region which contains the base 
     * station serving the GSM/UMTS network.
     *
     * @details The location area code (LAC) is unique within the network.
     *
     * Only GSM and UMTS networks support LAC.
     *
     * @permissions The application must have the @c access_location_services permission to access this information.
     *
     * @return Returns the LAC for the base station serving the GSM/UMTS network or 0 if the caller does 
     * not have sufficient permission, the network technology is not GSM/UMTS, or no network is 
     * currently connected.
     *
     * @since BlackBerry 10.0.0
     */
    int locationAreaCode() const;

    /*!
     * @brief Retrieves the unique identifier for the geographic region which contains the base 
     * station serving the LTE network.
     *
     * @details The tracking area code (TAC) is unique within the network.
     *
     * Only LTE networks support TAC.
     *
     * @permissions The application must have the @c access_location_services permission to access this information.
     *
     * @return Returns the TAC for the base station serving the LTE network or 0 if the caller does not 
     * have sufficient permission, the network technology is not LTE, or no network is currently 
     * connected.
     *
     * @since BlackBerry 10.0.0
     */
    int trackingAreaCode() const;

    /*!
     * @brief Retrieves the unique identifier for the base station serving the CDMA network.
     *
     * @details The base station ID (BID) is unique within a system (see @c systemId()).
     *
     * Only CDMA networks support BID.
     *
     * @permissions The application must have the @c access_location_services permission to access this information.
     *
     * @return Returns the BID for the base station serving the CDMA network or 0 if the caller does not 
     * have sufficient permission, the network technology is not CDMA, or no network is currently 
     * connected.
     *
     * @since BlackBerry 10.0.0
     */
    int baseStationId() const;

    /*!
     * @brief Retrieves the unique identifier for a geographic region within a system which 
     * contains the base station serving the CDMA network.
     *
     * @details The network ID (NID) is unique within a system (see @c systemId()).
     *
     * Only CDMA networks support NID.
     *
     * @permissions The application must have the @c access_location_services permission to access this information.
     *
     * @return Returns the NID for the base station serving the CDMA network or 0 if the caller does not 
     * have sufficient permission, the network technology is not CDMA, or no network is currently 
     * connected.
     *
     * @since BlackBerry 10.0.0
     */
    int networkId() const;

    /*!
     * @brief Retrieves the unique identifier for a geographic region which contains the 
     * base station serving the CDMA network.
     *
     * @details The system ID (SID) is globally unique.
     *
     * Only CDMA networks support SID.
     *
     * @permissions The application must have the @c access_location_services permission to access this information.
     *
     * @return Returns the SID for the base station serving the CDMA network or 0 if the caller does not 
     * have sufficient permission, the network technology is not CDMA, or no network is currently 
     * connected.
     *
     * @since BlackBerry 10.0.0
     */
    int systemId() const;

    /*!
     * @brief Retrieves the network name, cross referenced with other information,
     * as reported by Settings and QuickSettings.
     *
     * @return Returns the network name, cross referenced with other information,
     * as reported by Settings and QuickSettings, that provides a user friendly name, or an 
     * empty string if no network is currently connected or the network does not provide a name.
     *
     * @see @c name() function for the official name returned by the network
     *
     * @since BlackBerry 10.3.0
     */
    QString displayName() const;

public Q_SLOTS:
    /*!
     * @brief Changes the connected network represented by this object.
     *
     * @param index The index of the connected network represented by this object (see 
     * @c CellularRadioInfo::networkCount()).
     *
     * @ingroup Slots
     *
     * @since BlackBerry 10.0.0
     */
    void setIndex(int index);

Q_SIGNALS:
    /*!
     * @brief Emitted when the connected network represented by this object changes.
     *
     * @param index The index of the new connected network represented by this object (see 
     * @c CellularRadioInfo::networkCount()).
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void indexChanged(int index);

    /*!
     * @brief Emitted when the wireless communication standard of the network changes.
     *
     * @param tech The new wireless communication standard of the network.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void technologyChanged(bb::device::CellularTechnology::Type tech);

    /*!
     * @brief Emitted when the supported voice/data services of the network change.
     *
     * @param services A bitfield of the new voice/data services the network supports.
     *
     * @see @c bb::device::CellularService::Type for a list of flag values.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void servicesChanged(bb::device::CellularService::Types services);

    /*!
     * @brief Emitted when the human readable name of the network changes.
     *
     * @param name The new human readable name of the network.
     *
     * @see @c displayNameChanged signal for the name used by Settings
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void nameChanged(const QString &name);

    /*!
     * @brief Emitted when the mobile country code (MCC) of the network changes. 
     *
     * @param mcc The new MCC of the network.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void mobileCountryCodeChanged(const QString &mcc);

    /*!
     * @brief Emitted when the mobile network code (MNC) of the network changes.
     *
     * @param mnc The new MNC of the network.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void mobileNetworkCodeChanged(const QString &mnc);

    /*!
     * @brief Emitted when the power measurement of the network's radio signal changes.
     *
     * @param rssi The new received signal strength indication (RSSI) of the network in dBm.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void signalStrengthChanged(int rssi);

    /*!
     * @brief Emitted when the roaming indicator changes.
     *
     * @param roaming @c true if the device is currently connected to a visited network, @c false if 
     * the device is currently connected to its home network or no network.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void roamingChanged(bool roaming);
    
    /*!
     * @brief Emitted when the cell ID for the base station serving the GSM/UMTS/LTE network 
     * changes.
     *
     * @param cellId The new cell ID for the base station serving the GSM/UMTS/LTE network.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void cellIdChanged(int cellId);

    /*!
     * @brief Emitted when the location area code (LAC) for the base station serving the 
     * GSM/UMTS network changes.
     *
     * @param lac The new LAC for the base station serving the GSM/UMTS network.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void locationAreaCodeChanged(int lac);

    /*!
     * @brief Emitted when the tracking area code (TAC) for the base station serving the LTE 
     * network changes.
     *
     * @param tac The new TAC for the base station serving the LTE network.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void trackingAreaCodeChanged(int tac);

    /*!
     * @brief Emitted when the base station ID (BID) for the base station serving the CDMA 
     * network changes.
     *
     * @param bid The new BID for the base station serving the CDMA network.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void baseStationIdChanged(int bid);

    /*!
     * @brief Emitted when the network ID (NID) for the base station serving the CDMA network 
     * changes.
     *
     * @param nid The new NID for the base station serving the CDMA network.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void networkIdChanged(int nid);

    /*!
     * @brief Emitted when the system ID (SID) for the base station serving the CDMA network 
     * changes.
     *
     * @param sid The new SID for the base station serving the CDMA network.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void systemIdChanged(int sid);

    /*!
     * @brief Emitted when the display name of the network changes.
     *
     * @param name The new display name of the network.
     *
     * @see @c nameChanged signal for the official name returned by the network
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.3.0
     */
    void displayNameChanged(const QString &name);

protected:
//!@cond PRIVATE
    Q_SIGNAL void technologyChanged(int tech);

    Q_SIGNAL void servicesChanged(int services);
//!@endcond

private:
//!@cond PRIVATE
    QScopedPointer<CellularNetworkInfoPrivate> d_ptr;
    Q_DECLARE_PRIVATE(CellularNetworkInfo)
    Q_DISABLE_COPY(CellularNetworkInfo)
//!@endcond
};

} // namespace device
} // namespace bb

QML_DECLARE_TYPE(bb::device::CellularNetworkInfo)

#endif // BB_DEVICE_CELLULARNETWORKINFO_HPP
