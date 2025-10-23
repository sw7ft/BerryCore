/*!
 * @copyright
 * Copyright BlackBerry Limited, 2013-2014
 * BlackBerry Limited. All rights reserved.
 */

#ifndef BB_DEVICE_WIFIDIRECT_HPP
#define BB_DEVICE_WIFIDIRECT_HPP

#include <bb/device/Global>

#include <bb/device/WiFiDirectResult>
#include <bb/device/WiFiDirectDeviceType>
#include <bb/device/WiFiDirectSecondaryDeviceType>
#include <bb/device/WiFiDirectIntent>
#include <bb/device/WiFiDirectWpsMethod>
#include <bb/device/WiFiDirectConnectionState>
#include <bb/device/WiFiDirectRole>

#include <QObject>
#include <QtDeclarative/QtDeclarative>
#include <QDateTime>

namespace bb
{
namespace device
{

class WiFiDirectPrivate;

/*!
 * @headerfile WiFiDirect.hpp <bb/device/WiFiDirect>
 *
 * @brief The @c WiFiDirect class provides the entry point to accessing information
 *        about WiFiDirect devices, or establishing connections with those devices.
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Control"/>
 * <library name="bbdevice"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_DEVICE_EXPORT WiFiDirect : public QObject
{
    Q_OBJECT

    /*!
     * @brief Indicates if WiFi Direct is currently scanning for available devices or not.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( bool scanning READ isScanning NOTIFY scanningChanged FINAL )

    /*!
     * @brief Indicates if the WiFi Direct service is enabled or not.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( bool enabled READ isEnabled NOTIFY enabledChanged FINAL )

    /*!
     * @brief Indicates if the WiFi Direct service is supported on this device or not.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( bool supported READ isSupported CONSTANT FINAL )

    /*!
     * @brief The timestamp of the last time the current list of discovered devices has been updated.
     *
     * @details If no scan has been performed or if the list of discovered devices is
     * unavailable (or being updated), @c lastUpdate will be invalid (@c lastUpdate.isValid() is false).
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( QDateTime lastUpdate READ lastUpdate NOTIFY lastUpdateChanged FINAL )

    /*!
     * @brief The current state of the connection to the network group.
     *
     * @details See @c bb::device::WiFiDirectConnectionState for more details.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( bb::device::WiFiDirectConnectionState::Type connectionState READ connectionState NOTIFY connectionStateChanged FINAL )

    /*!
     * @brief The name of the network interface used to connect to the network group.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( QString networkInterfaceName READ networkInterfaceName NOTIFY networkInterfaceNameChanged FINAL )

    /*!
     * @brief Your role within the network group.
     *
     * @details See @c bb::device::WiFiDirectRole for more details.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( bb::device::WiFiDirectRole::Type networkRole READ networkRole NOTIFY networkRoleChanged FINAL )

    /*!
     * @brief The SSID for the network group.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( QString networkSsid READ networkSsid NOTIFY networkSsidChanged FINAL )

    /*!
     * @brief The MAC address of the network group owner.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( QString networkOwnerHardwareAddress READ networkOwnerHardwareAddress NOTIFY networkOwnerHardwareAddressChanged FINAL )

    /*!
     * @brief The IP address of the network group owner.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( QString networkOwnerIpAddress READ networkOwnerIpAddress NOTIFY networkOwnerIpAddressChanged FINAL )

    /*!
     * @brief The password for the network group.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( QString networkPassword READ networkPassword NOTIFY networkPasswordChanged FINAL )


public:
    /*!
     * @brief Construct a @c WiFiDirect instance.
     *
     * @param parent If not 0, the supplied parent is responsible for deleting
     *               this instance.
     *
     * @since BlackBerry 10.2.0
     */
    explicit WiFiDirect( QObject * parent = 0 );

    /*!
     * @brief Destroy the @c WiFiDirect instance.
     */
    virtual ~WiFiDirect();

    /*!
     * @brief Indicates if the WiFi Direct service is supported on this device or not.
     *
     * @returns @c True if the service is supported, @c False otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    static bool isSupported();

    /*!
     * @brief Enables scanning mode on the device, scanning for new visible devices every 5 seconds.
     * 
     * The scan lasts for 60 seconds. A device must call the @c requestScan() method in order to be visible for discovery.
     *
     * @return One of @c bb::device::WiFiDirectResult, indicating the result of the attempt to enable
     * scanning mode.
     *
     * @since BlackBerry 10.2.0
     */
#ifndef Q_MOC_RUN
    Q_INVOKABLE bb::device::WiFiDirectResult::Type requestScan();
#else
    /*!
     * @cond PRIVATE
     * This conditional directive is set up to make it appear that the requestScan() method returning the enumerator is available from QML
     * which it normally is not.  Since an int and the enum are compatible with loose typing you can call this method from QML
     * and compare it to the enum and it works.
     * @endcond
     */
    Q_INVOKABLE int requestScan();
#endif

    /*!
     * @brief Creates a session with the WiFiDirect service. The @c requestStartSession() should be called once the device is connected.
     *
     * @details Without a registered session, the underlying service will close any connections after
     * 20 seconds.
     *
     * @return One of @c bb::device::WiFiDirectResult::Type.  If @c WiFiDirectResult::Success is returned
     * the session key will be delivered by the @c sessionStarted signal.
     *
     * @since BlackBerry 10.2.0
     */
#ifndef Q_MOC_RUN
    Q_INVOKABLE bb::device::WiFiDirectResult::Type requestStartSession();
#else
    /*!
     * @cond PRIVATE
     * This conditional directive is set up to make it appear that the requestStartSession() method returning the enumerator is available from QML
     * which it normally is not.  Since an int and the enum are compatible with loose typing you can call this method from QML
     * and compare it to the enum and it works.
     * @endcond
     */
    Q_INVOKABLE int requestStartSession();
#endif

    /*!
     * @brief Destroys a session established with the WiFiDirect service.
     *
     * @param session The identifier for the established session to be torn down.
     *
     * @return One of @c bb::device::WiFiDirectResult::Type.  If @c WiFiDirectResult::Success is returned
     * the session will be gone when the @c sessionStopped signal is emitted.
     *
     * @since BlackBerry 10.2.0
     */
#ifndef Q_MOC_RUN
    Q_INVOKABLE bb::device::WiFiDirectResult::Type requestStopSession( const QString &session );
#else
    /*!
     * @cond PRIVATE
     * This conditional directive is set up to make it appear that the requestStopSession() method returning the enumerator is available from QML
     * which it normally is not.  Since an int and the enum are compatible with loose typing you can call this method from QML
     * and compare it to the enum and it works.
     * @endcond
     */
    Q_INVOKABLE int requestStopSession( const QString &session );
#endif

    /*!
     * @brief Attempts to connect to the specified device using the supplied method.
     *
     * @details The target device must not be part of a WiFiDirect group, otherwise the connection
     * will fail.
     *
     * @param hardwareAddress The unique identifier of the device to which the connection will be attempted.
     * @param intent See @c bb::device::WiFiDirectIntent for more details.
     * @param wpsMethod See @c bb::device::WiFiDirectWpsMethod for more details.
     * @param wpsPin The PIN to use for the connection attempt.  Leave blank for none.  The PIN will only be
     * used for connections with @c bb::device::WiFiDirectWpsMethod::PresetPin.
     *
     * @return Returns one of @c bb::device::WiFiDirectResult.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE bb::device::WiFiDirectResult::Type requestConnect( const QString &hardwareAddress, bb::device::WiFiDirectIntent::Type intent, bb::device::WiFiDirectWpsMethod::Type wpsMethod, const QString &wpsPin );

    /*!
     * @brief Attempts to abort a connection attempt that is in progress.
     *
     * @return One of @c bb::device::WiFiDirectResult, indicating the result of the attempt.
     *
     * @since BlackBerry 10.2.0
     */
#ifndef Q_MOC_RUN
    Q_INVOKABLE bb::device::WiFiDirectResult::Type cancelConnectRequest();
#else
    /*!
     * @cond PRIVATE
     * This conditional directive is set up to make it appear that the cancelConnectRequest() method returning the enumerator is available from QML
     * which it normally is not.  Since an int and the enum are compatible with loose typing you can call this method from QML
     * and compare it to the enum and it works.
     * @endcond
     */
    Q_INVOKABLE int cancelConnectRequest();
#endif

    /*!
     * @brief Obtains the IP address for the device specified by the supplied hardware address.
     *
     * @param hardwareAddress The unique identifier for the device.
     *
     * @return A @c QString containing the IP address of the device specified by @c hardwareAddress, if
     * it could be obtained, otherwise an empty string is returned.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE QString ipAddress( const QString &hardwareAddress ) const;

    /*!
     * @brief Obtains the name of the device specified by the supplied hardware address.
     *
     * @param hardwareAddress The unique identifier for the device.
     *
     * @return A @c QString containing the name of the device specified by @c hardwareAddress, if
     * it could be obtained, otherwise an empty string is returned.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE QString name( const QString &hardwareAddress ) const;

    /*!
     * @brief Obtains the type of the device specified by the supplied hardware address.
     *
     * @param hardwareAddress The unique identifier for the device.
     *
     * @return A @c bb::device::WiFiDirectDeviceType containing the type of the device specified by @c hardwareAddress, if
     * it could be obtained, otherwise @c bb::device::WiFiDirectDeviceType::Unknown is returned.
     *
     * @since BlackBerry 10.2.0
     */
#ifndef Q_MOC_RUN
    Q_INVOKABLE bb::device::WiFiDirectDeviceType::Type deviceType( const QString &hardwareAddress ) const;
#else
    /*!
     * @cond PRIVATE
     * This conditional directive is set up to make it appear that the deviceType() method returning the enumerator is available from QML
     * which it normally is not.  Since an int and the enum are compatible with loose typing you can call this method from QML
     * and compare it to the enum and it works.
     * @endcond
     */
    Q_INVOKABLE int deviceType( const QString &hardwareAddress ) const;
#endif

    /*!
     * @brief Returns the hardwareAddress for each connected device.
     *
     * @return A @c QStringList containing the hardware address for each device currently
     * connected to the network group.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE QStringList connectedDevices() const;

    /*!
     * @brief Returns the hardwareAddress for each device currently visible.
     *
     * @return A @c QStringList containing the hardware addresses for all devices
     * currently visible to the WiFi Direct service.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE QStringList visibleDevices() const;

    /*!
     * @brief Indicates if a WiFi Direct scan is currently being performed.
     *
     * @return @c True if the device is currently scanning, @c False otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool isScanning() const;

    /*!
     * @brief Indicates if the WiFi Direct service is enabled or not.
     *
     * @return @c True if the service is enabled, @c False otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool isEnabled() const;

    /*!
     * @brief The timestamp of the last time the current list of discovered devices has been updated.
     *
     * @details If no scan has been performed or if the list of discovered devices is
     * unavailable (or being updated), the @c QDateTime returned will have @c isValid()
     * set to false.
     *
     * @return A @c QDateTime indicating the last time a WiFi Direct scan has been performed or
     * an invalid @c QDateTime if not applicable.
     *
     * @since BlackBerry 10.2.0
     */
    QDateTime lastUpdate() const;

    /*!
     * @brief The current state of the connection to a network group.
     *
     * @details See @c bb::device::WiFiDirectConnectionState for more details.
     *
     * @returns One of @c bb::device::WiFiDirectConnectionState.
     *
     * @since BlackBerry 10.2.0
     */
    bb::device::WiFiDirectConnectionState::Type connectionState() const;

    /*!
     * @brief The name of the network interface for this group.
     *
     * @return A @c QString containing the network interface name for the established
     * network group.
     *
     * @since BlackBerry 10.2.0
     */
    QString networkInterfaceName() const;

    /*!
     * @brief Your role within the network group.
     *
     * @return The role indicated for the network group, otherwise @c bb::device::WiFiDirectRole::Unknown.
     * See @c bb::device::WiFiDirectRole for more details.
     *
     * @since BlackBerry 10.2.0
     */
    bb::device::WiFiDirectRole::Type networkRole() const;

    /*!
     * @brief The SSID of the network group.
     *
     * @return A @c QString containing the network group SSID.
     *
     * @since BlackBerry 10.2.0
     */
    QString networkSsid() const;

    /*!
     * @brief The MAC address of the group owner for the network group.
     *
     * @return A @c QString containing the MAC address of the network group owner.
     *
     * @since BlackBerry 10.2.0
     */
    QString networkOwnerHardwareAddress() const;

    /*!
     * @brief The IP address of the network group owner.
     *
     * @return A @c QString containing the IP address of the network group owner.
     *
     * @since BlackBerry 10.2.0
     */
    QString networkOwnerIpAddress() const;

    /*!
     * @brief The password for the network group.
     *
     * @return A @c QString containing the password for the network group.
     *
     * @since BlackBerry 10.2.0
     */
    QString networkPassword() const;


Q_SIGNALS:

    /*!
     * @brief Emitted when a session is established on a connection.
     *
     * @param session The identifier for the session that has been established.
     *
     * @since BlackBerry 10.2.0
     */
    void sessionStarted( const QString &session );

    /*!
     * @brief Emitted when the session identified in @c requestStopSession is torn down.
     *
     * @since BlackBerry 10.2.0
     */
    void sessionStopped();

    /*!
     * @brief Emitted when a WiFi Direct device is discovered during a scan.
     *
     * @param name The device-assigned human readable name for the device.
     * @param hardwareAddress The unique identifier for the device.
     * @param type One of @c bb::device::WiFiDirectDeviceType.
     * @param secondaryType Zero, one or more of @c bb::device::WiFiDirectSecondaryDeviceType.
     * @param role One of @c bb:device::WiFiDirectRole.
     *
     * @since BlackBerry 10.3.0
     */
    Q_REVISION(1) void deviceDiscovered( const QString &name,
                      const QString &hardwareAddress,
                      bb::device::WiFiDirectDeviceType::Type type,
                      bb::device::WiFiDirectSecondaryDeviceType::Types secondaryTypes,
                      bb::device::WiFiDirectRole::Type role );

    /*!
     * @brief Emitted when a WiFi Direct device is discovered during a scan.
     *
     * @details This signal has been deprecated. Please use the @c deviceDiscovered signal instead.
     *
     * @param name The device-assigned human readable name for the device.
     * @param hardwareAddress The unique identifier for the device.
     * @param type One of @c bb::device::WiFiDirectDeviceType.
     *
     * @since BlackBerry 10.2.0
     */
    void deviceFound( const QString &name,
                      const QString &hardwareAddress,
                      bb::device::WiFiDirectDeviceType::Type type );

    /*!
     * @brief Emitted when a device held in the visibleDevices list is determined to be no longer visible.
     *
     * @details Since the visibleDevices list is only updated after a scan, it is possible to have this signal
     * be raised for devices that were no longer available a considerable time ago.
     *
     * @param hardwareAddress The unique identifier for the device that is no longer visible.
     *
     * @since BlackBerry 10.2.0
     */
    void deviceLost( const QString &hardwareAddress );

    /*!
     * @brief Emitted when a device joins the network group.
     *
     * @param name The name of the device that has joined.
     * @param hardwareAddress The unique identifier for the new device.
     * @param type See @c bb::device::WiFiDirectDeviceType for details.
     * @param ipAddress The IP address of the new device.
     * @param intent See @c bb::device::WiFiDirectIntent for details.
     *
     * @since BlackBerry 10.2.0
     */
    void deviceConnected( const QString &name, const QString &hardwareAddress, bb::device::WiFiDirectDeviceType::Type type, const QString &ipAddress, bb::device::WiFiDirectIntent::Type intent );

    /*!
     * @brief Emitted when a previously connected device is removed from the list of connected devices.
     *
     * @param hardwareAddress The unique identifier for the device that disconnected.
     *
     * @since BlackBerry 10.2.0
     */
    void deviceDisconnected( const QString &hardwareAddress );

    /*!
     * @brief Emitted when the device changes its scanning mode.
     *
     * @param scanning @c True if the device is now scanning, @c False otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    void scanningChanged( bool scanning );

    /*!
     * @brief Emitted when the state of the WiFi Direct service changes.
     *
     * @param enabled @c True if the service is enabled, @c False otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    void enabledChanged( bool enabled );

    /*!
     * @brief Emitted whenever the list of visible devices is updated.
     *
     * @param lastUpdate The timestamp when the list of visible devices has been updated last.
     *
     * @since BlackBerry 10.2.0
     */
    void lastUpdateChanged( QDateTime lastUpdate );

    /*!
     * @brief Emitted when the network group connection state changes.
     *
     * @param connectionState Indicates the new state of the connection to the network group.
     *
     * @since Blackberry 10.2.0
     */
    void connectionStateChanged( bb::device::WiFiDirectConnectionState::Type connectionState );

    /*!
     * @brief Emitted when your role within the network group has changed.
     *
     * @param networkRole Your new role within the network group.
     *
     * @since BlackBerry 10.2.0
     */
    void networkRoleChanged( bb::device::WiFiDirectRole::Type networkRole);

    /*!
     * @brief Emitted when the interface associated with the network group changes.
     *
     * @param networkInterfaceName The name of the network interface.
     *
     * @since BlackBerry 10.2.0
     */
    void networkInterfaceNameChanged( QString networkInterfaceName );

    /*!
     * @brief Emitted when the SSID of the network group changes.
     *
     * @param networkSsid  The new SSID of the network group.
     *
     * @since BlackBerry 10.2.0
     */
    void networkSsidChanged( QString networkSsid );

    /*!
     * @brief Emitted when the Group Owner hardware address changes.
     *
     * @param networkHardwareAddress The unique identifier of the hardware of the group owner
     *
     * @since BlackBerry 10.2.0
     */
    void networkOwnerHardwareAddressChanged( QString networkHardwareAddress );

    /*!
     * @brief Emitted when the IP address of the network group owner changes.
     *
     * @param networkIpAddress The new IP address of the group owner.
     *
     * @since BlackBerry 10.2.0
     */
    void networkOwnerIpAddressChanged( QString networkIpAddress );

    /*!
     * @brief Emitted when the network group password changes.
     *
     * @param networkPassword The new network group password.
     *
     * @since BlackBerry 10.2.0
     */
    void networkPasswordChanged( QString networkPassword );

    /*!
     * @brief Emitted when the device is no longer scanning for visible devices.
     *
     * @since BlackBerry 10.2.0
     */
    void scanCompleted();

protected:
//!@cond PRIVATE
    Q_INVOKABLE int requestConnect( const QString &hardwareAddress, int intent, int wpsMethod, const QString &wpsPin );
    Q_SIGNAL void stateChanged( int state );

    Q_SIGNAL void deviceFound( const QString &name, const QString &hardwareAddress, int type);

    Q_REVISION(1) Q_SIGNAL void deviceDiscovered( const QString &name,
        const QString &hardwareAddress, int type, int secondaryTypes, int role);

    Q_SIGNAL void deviceConnected( const QString &name, const QString &hardwareAddress, int type, const QString &ipAddress, int intent );

    Q_SIGNAL void connectionStateChanged( int networkState );

    Q_SIGNAL void networkRoleChanged( int networkRole);

//!@endcond

private:
//!@cond PRIVATE
    Q_DECLARE_PRIVATE(WiFiDirect)
    Q_DISABLE_COPY(WiFiDirect)
    QScopedPointer<WiFiDirectPrivate> d_ptr;
//!@endcond
};

} // device
} // bb

QML_DECLARE_TYPE(bb::device::WiFiDirect)

#endif // BB_DEVICE_WIFIDIRECT_HPP
