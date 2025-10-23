/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_DEVICE_CELLULARDATAINTERFACE_HPP
#define BB_DEVICE_CELLULARDATAINTERFACE_HPP

#include <bb/device/Global>
#include <bb/device/CellularConnectionRequestResult>
#include <bb/device/CellularConnectionState>

#include <QObject>
#include <QString>
#include <QStringList>
#include <QScopedPointer>

namespace bb
{
namespace device
{

class CellularDataInterfacePrivate;

/*!
 * @headerfile CellularDataInterface.hpp <bb/device/CellularDataInterface>
 *
 * @brief Represents a logical network connection for a cellular data service. 
 *
 * @details A carrier may route traffic for different cellular data services over 
 * different network interfaces. Furthermore, different carriers may route traffic 
 * for the same service over different network interfaces. @c CellularDataInterface
 * maps the logical name of a cellular data service to its carrier-dependent network 
 * interface, provides information about the service's network connection, and 
 * allows the activation/de-activation of on-demand connections.
 *
 * Use @c allNames() to discover the set of cellular data services configured 
 * for this device. Possible logical names include:
 *
 * - @c a_gps - Connection for Assisted Global Positioning (A-GPS)
 * - @c bip - Connection for Bearer Independent Protocol (BIP) - see 3gpp TS 31.111 and 3gpp TS 27.007
 * - @c bip_2 - Alternate connection for BIP
 * - @c bip_3 - Alternate connection for BIP
 * - @c bip_4 - Alternate connection for BIP
 * - @c bip_5 - Alternate connection for BIP
 * - @c blackberry - Connection for BlackBerry services
 * - @c carrier_800 - Connection for carrier applications
 * - @c carrier_admin - Connection for carrier administrative applications
 * - @c carrier_apps - Connection for carrier applications
 * - @c ims - Connection for IP Multimedia Subsystem (IMS)
 * - @c internet - Connection for cellular Internet access
 * - @c mms - Connection for Multimedia Messaging Service (MMS)
 * - @c plan_admin - Connection for adminstration of user's cellular service plan
 * - @c rim_admin - Connection for administrative BlackBerry services
 * - @c software_update - Connection for downloading software updates
 * - @c streaming - Connection for alternate streaming channels
 * - @c tethering - Connection for tethering applications
 * - @c tethering_2 - Alternate connection for tethering applications
 * - @c tethering_entitlement - Connection for tethering entitlement check
 * - @c tethering_user - Connection for tethering applications with user supplied configuration
 * - @c vvm - Connection for Visual Voicemail (VVM)
 * - @c wap - Connection for Wireless Application Protocol (WAP)
 *
 * The following cellular data services support activation/de-activation of on-demand 
 * connections via @c requestConnect() and @c requestDisconnect():
 *
 * - @c carrier_800 - Requires @c cds_carrier_800 permission
 * - @c carrier_admin - Requires @c cds_carrier_admin permission
 * - @c carrier_apps - Requires @c cds_carrier_apps permission
 * - @c plan_admin - Requires @c cds_plan_admin permission
 *
 * Most applications that need to send/receive data over a network connection should
 * not bind to a specific network interface. Instead, these applications should 
 * accept the default route for their traffic. Even binding to the network interface
 * for @c internet is not recommended as this is a cellular-only connection and does 
 * not account for the availability of a WiFi connection.
 *
 * Applications that have a specific need to send/receive data using a particular 
 * cellular data service can do so using the following steps:
 *
 * -# Create an instance of @c CellularDataInterface using the logical name of your service.
 * -# Call @c isValid() to verify the logical name is correct and supported.
 * -# Call @c requestConnect() and check the return value for an error.
 * -# Wait for the @c connectionState property to become @c CellularConnectionState::Connected.
 * -# Query the @c networkInterfaceName property to get the service's network interface.
 * -# Set the @c SOCK_SO_BINDTODEVICE environment variable to the service's network interface; all subsequently created sockets will be bound to this network interface.
 * -# Send/receive data.
 * -# Call @c requestDisconnect().
 *
 * It is important to always call @c requestConnect() and @c requestDisconnect() 
 * regardless of the current connection state. The OS determines when to 
 * activate/de-activate an on-demand connection for a cellular data service based on 
 * the calls to @c requestConnect() and @c requestDisconnect(). When multiple
 * applications use the same service, the OS keeps the connection active until the
 * last application calls @c requestDisconnect(). Using a service without first 
 * calling @c requestConnect() means there is no guarantee the connection will
 * remain active while you're using it.
 *
 * Furthermore, you must keep the @c CellularDataInterface object alive until you're 
 * done sending/receiving data. The destructor for @c CellularDataInterface 
 * implicitly calls @c requestDisconnect().
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Radio and SIM"/>
 * <library name="bbdevice"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.2.0
 */
class BB_DEVICE_EXPORT CellularDataInterface : public QObject
{
    Q_OBJECT
    
    /*!
     * @brief Logical name of the cellular data service this object represents.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    
    /*!
     * @brief Flag indicating whether this object represents a valid interface.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool valid READ isValid NOTIFY validChanged FINAL)
    
    /*!
     * @brief Flag indicating if this interface is automatically connected when data 
     * services are enabled.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool alwaysOn READ isAlwaysOn NOTIFY alwaysOnChanged FINAL)
    
    /*!
     * @brief Flag indicating if only authorized processes can control and/or send 
     * traffic over this interface.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool accessControlled READ isAccessControlled NOTIFY accessControlledChanged FINAL)
    
    /*!
     * @brief Name of the network interface that handles traffic for this cellular 
     * data service.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(QString networkInterfaceName READ networkInterfaceName NOTIFY networkInterfaceNameChanged FINAL)
    
    /*!
     * @brief Name of the access point (APN) used by this cellular data service.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(QString accessPointName READ accessPointName NOTIFY accessPointNameChanged FINAL)
    
    /*!
     * @brief State of this cellular data services's network connection. See 
     * @c CellularConnectionState for details.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bb::device::CellularConnectionState::Type connectionState READ connectionState NOTIFY connectionStateChanged FINAL)
    
public:

    /*!
     * @brief Creates a @c CellularDataInterface object which defaults to an invalid 
     * state - no name.
     *
     * @param parent If not 0, the supplied parent will be responsible for deleting 
     * this instance.
     *
     * @since BlackBerry 10.2.0
     */
    explicit CellularDataInterface(QObject *parent = 0);
    
    /*!
     * @brief Creates a @c CellularDataInterface object for the specified interface.
     *
     * @param name Logical name of the cellular data service this object represents.
     * @param parent If not 0, the supplied parent will be responsible for deleting 
     * this instance.
     *
     * @since BlackBerry 10.2.0
     */
    explicit CellularDataInterface(const QString &name, QObject *parent = 0);
    
    /*!
     * @brief Destroys this @c CellularDataInterface object.
     *
     * @details If @c requestConnect() was previously called, implicitly calls 
     * @c requestDisconnect().
     *
     * @since BlackBerry 10.2.0
     */
    virtual ~CellularDataInterface();
    
    /*!
     * @brief Retrieves the logical name of the cellular data service this object 
     * represents.
     *
     * @return The logical name of the cellular data service this object represents.
     *
     * @since BlackBerry 10.2.0
     */
    QString name() const;
    
    /*!
     * @brief Changes the cellular data service this object represents.
     *
     * @details If @c requestConnect() was previously called, implicitly calls 
     * @c requestDisconnect() prior to switching to the new cellular data service.
     *
     * @param name Logical name of the new cellular data service this object 
     * represents.
     *
     * @since BlackBerry 10.2.0
     */
    void setName(const QString &name);
    
    /*!
     * @brief Indicates whether this object represents a valid interface.
     *
     * @return Flag indicating whether this object represents a valid interface.
     *
     * @since BlackBerry 10.2.0
     */
    bool isValid() const;
    
    /*!
     * @brief Indicates whether this interface is automatically connected when data 
     * services are enabled.
     *
     * @return Flag indicating if this interface is automatically connected when 
     * data services are enabled.
     *
     * @since BlackBerry 10.2.0
     */
    bool isAlwaysOn() const;
    
    /*!
     * @brief Indicates whether only authorized processes can control and/or send 
     * traffic over this interface.
     *
     * @return Flag indicating if only authorized processes can control and/or send 
     * traffic over this interface.
     *
     * @since BlackBerry 10.2.0
     */
    bool isAccessControlled() const;
    
    /*!
     * @brief Retrieves the name of the network interface that handles traffic for 
     * this cellular data service.
     *
     * @return Name of the network interface that handles traffic for this cellular
     * data service.
     *
     * @since BlackBerry 10.2.0
     */
    QString networkInterfaceName() const;
    
    /*!
     * @brief Retrieves the name of the access point (APN) used by this cellular 
     * data service.
     *
     * @return Name of the access point (APN) used by this cellular data service.
     *
     * @since BlackBerry 10.2.0
     */
    QString accessPointName() const;
    
    /*!
     * @brief Retrieves the state of this celluar data service's network connection.
     *
     * @return State of this cellular data service's network connection. See 
     * @c CellularConnectionState for details.
     *
     * @since BlackBerry 10.2.0
     */
    bb::device::CellularConnectionState::Type connectionState() const;
    
    /*!
     * @brief Attempt to activate the network connection for this cellular data 
     * service.
     *
     * @details This is an asynchronous operation. If 
     * @c CellularConnectionRequestResult::Requested 
     * is returned, monitor @c connectionState to determine when a connection has 
     * finally been established. Note that @c CellularConnectionRequestResult::Requested 
     * does not guarantee that a connection will ultimately be established, only that 
     * no immediate failure was detected.
     *
     * All clients that need to send traffic over the interface should call 
     * @c requestConnect() and @c requestDisconnect() when they start and stop using 
     * the interface regardless of the current value of @c connectionState. This 
     * ensures that on-demand interfaces remain active until the last client 
     * disconnects.
     *
     * @return Result of this request. See @c CellularConnectionRequestResult for 
     * details.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT int requestConnect();
    
    /*!
     * @brief Attempt to de-activate the network connection for this cellular data 
     * service.
     *
     * @details This is an asynchronous operation. If 
     * @c CellularConnectionRequestResult::Requested is returned, monitor 
     * @c connectionState to determine when a connection has finally been shut down. 
     * Note that @c CellularConnectionRequestResult::Requested does not guarantee that 
     * a connection will ultimately be shut down. The connection may be always-on or 
     * another application may still be using the on-demand connection.
     *
     * All clients that need to send traffic over the interface should call 
     * @c requestConnect() and @c requestDisconnect() when they start and stop using 
     * the interface regardless of the current value of @c connectionState. This 
     * ensures that on-demand interfaces remain active until the last client 
     * disconnects.
     *
     * @return Result of this request. See @c CellularConnectionRequestResult for 
     * details.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT int requestDisconnect();

    /*!
     * @brief Retrieves the logical names of each cellular data services configured 
     * for this device.
     *
     * @return List of logical names of each cellular data services configured for 
     * this device.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE static QStringList allNames();

Q_SIGNALS:

    /*!
     * @brief Emitted when the name of the logical interface this object represents 
     * changes.
     *
     * @param name The logical name of the cellular data service this object represents.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.2.0
     */
    void nameChanged(const QString &name);
    
    /*!
     * @brief Emitted when this object changes from representing an invalid interface 
     * to a valid interface or vice versa.
     *
     * @param valid Flag indicating whether this object represents a valid interface.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.2.0
     */
    void validChanged(bool valid);
    
    /*!
     * @brief Emitted when this interface changes from an on-demand connection to an 
     * always-on connection or vice versa.
     *
     * @param alwaysOn Flag indicating if this interface is automatically connected when data 
     * services are enabled.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.2.0
     */
    void alwaysOnChanged(bool alwaysOn);
    
    /*!
     * @brief Emitted when this interface changes whether only authorized processes 
     * can control and/or send traffic over this interface.
     *
     * @param accessControlled Flag indicating if only authorized processes can control and/or send 
     * traffic over this interface.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.2.0
     */
    void accessControlledChanged(bool accessControlled);
    
    /*!
     * @brief Emitted when the name of the network interface that maps to this 
     * logical interface changes.
     *
     * @param networkInterfaceName Name of the network interface that handles traffic for this cellular 
     * data service.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.2.0
     */
    void networkInterfaceNameChanged(const QString &networkInterfaceName);
    
    /*!
     * @brief Emitted when the name of the access point (APN) used by this interface 
     * changes.
     *
     * @param accessPointName Name of the access point (APN) used by this cellular data service.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.2.0
     */
    void accessPointNameChanged(const QString &accessPointName);
    
    /*!
     * @brief Emitted when the state of this interface's network connection changes.
     *
     * @param connectionState State of this celluar data services's network connection. See 
     * @c CellularConnectionState for details.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.2.0
     */
    void connectionStateChanged(bb::device::CellularConnectionState::Type connectionState);

//!@cond PRIVATE
    /*!
     * @since BlackBerry 10.2.0
     */
    void connectionStateChanged(int connectionState);
//!@endcond

private:
//!@cond PRIVATE
    QScopedPointer<CellularDataInterfacePrivate> d_ptr;
    Q_DECLARE_PRIVATE(CellularDataInterface)
    Q_DISABLE_COPY(CellularDataInterface)
//!@endcond
};

} // namespace device
} // namespace bb

#endif // BB_DEVICE_CELLULARDATAINTERFACE_HPP
