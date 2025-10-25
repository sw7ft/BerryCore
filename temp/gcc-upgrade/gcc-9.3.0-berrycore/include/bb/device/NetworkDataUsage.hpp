/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2013
 * Research In Motion Limited. All rights reserved.
 */
#ifndef BB_DEVICE_NETWORKDATAUSAGE_HPP
#define BB_DEVICE_NETWORKDATAUSAGE_HPP

#include <bb/device/Global>
#include <QObject>
#include <QString>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace device
{

class NetworkDataUsagePrivate;

/*!
 * @headerfile NetworkDataUsage.hpp <bb/device/NetworkDataUsage>
 *
 * @brief Allows monitoring of network traffic statistics.
 *
 * @details The @c NetworkDataUsage classes measures the amount of data (in 
 * packets or bytes) sent or received by a particular network interface since
 * the device was last reset. To determine the name of a valid network interface 
 * for use with this class, use the @c QNetworkInterface::allInterfaces() and 
 * @c QNetworkInterface::humanReadableName() methods.
 
 * The traffics statistics reported by @c NetworkDataUsage are not live. You 
 * must call @c update() to obtain the latest packet/byte counts. To montior 
 * network usage over time, you can attach the @c update() slot to the @c timeout 
 * signal of a @c QTimer. However, be aware that polling can prevent the device 
 * from entering a low power state, which adversely affects battery life. If you 
 * must poll, please use the lowest frequency possible and suspend polling 
 * whenever possible.
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Info"/>
 * <library name="bbdevice"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.2.0
 */
class BB_DEVICE_EXPORT NetworkDataUsage : public QObject
{
    Q_OBJECT

    /*!
     * @brief Name of the network interface represented by this object.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(QString networkInterfaceName READ networkInterfaceName WRITE setNetworkInterfaceName NOTIFY networkInterfaceNameChanged FINAL)

    /*!
     * @brief The number of packets received through the network interface since 
     * the device was last reset.
     *
     * @details This value will only change as the result of call to @c update().
     *
     * @note Javascript does not support 64-bit numbers so this property is 
     * represented as a floating point value in QML. As a result, rounding errors 
     * may occur at higher values of this property. For optimal precision, access
     * this property from C++ instead.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(quint64 packetsReceived READ packetsReceived NOTIFY packetsReceivedChanged FINAL)
    
    /*!
     * @brief The number of bytes received through the network interface since 
     * the device was last reset.
     *
     * @details This value will only change as the result of call to @c update().
     *
     * @note Javascript does not support 64-bit numbers so this property is 
     * represented as a floating point value in QML. As a result, rounding errors 
     * may occur at higher values of this property. For optimal precision, access
     * this property from C++ instead.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(quint64 bytesReceived READ bytesReceived NOTIFY bytesReceivedChanged FINAL)
    
    /*!
     * @brief The number of packets sent through the network interface since 
     * the device was last reset.
     *
     * @details This value will only change as the result of call to @c update().
     *
     * @note Javascript does not support 64-bit numbers so this property is 
     * represented as a floating point value in QML. As a result, rounding errors 
     * may occur at higher values of this property. For optimal precision, access
     * this property from C++ instead.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(quint64 packetsSent READ packetsSent NOTIFY packetsSentChanged FINAL)
    
    /*!
     * @brief The number of bytes sent through the network interface since the 
     * device was last reset.
     *
     * @details This value will only change as the result of call to @c update().
     *
     * @note Javascript does not support 64-bit numbers so this property is 
     * represented as a floating point value in QML. As a result, rounding errors 
     * may occur at higher values of this property. For optimal precision, access
     * this property from C++ instead.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(quint64 bytesSent READ bytesSent NOTIFY bytesSentChanged FINAL)

public:
   /*!
    * @brief Creates a @c NetworkDataUsage object which defaults to an invalid 
    * state - no network interface.
    *
    * @param parent If not 0, the supplied parent will be responsible for deleting 
    * this instance.
    *
    * @since BlackBerry 10.2.0
    */
   explicit NetworkDataUsage(QObject *parent = 0);
   
   /*!
     * @brief Creates a @c NetworkDataUsage object for the specified network 
     * interface.
     *
     * @param networkInterfaceName Name of the network interface this object 
     * represents.
     * @param parent If not 0, the supplied parent will be responsible for deleting 
     * this instance.
     *
     * @since BlackBerry 10.2.0
     */
    explicit NetworkDataUsage(const QString &networkInterfaceName, QObject *parent = 0);

   /*!
    * @brief Destroys this @c NetworkDataUsage object.
    *
    * @since BlackBerry 10.2.0
    */
   virtual ~NetworkDataUsage();

    /*!
     * @brief Retrieves the name of the network interface represented by this 
     * object.
     *
     * @return The name of the network interface represented by this object.
     *
     * @since BlackBerry 10.2.0
     */
    QString networkInterfaceName() const;
    
    /*!
     * @brief Changes the network interface this object represents and resets all
     * packet/byte counts to zero.
     *
     * @param name The name of the network interface represented by this object.
     *
     * @since BlackBerry 10.2.0
     */
    void setNetworkInterfaceName(const QString &name);
    
    /*!
     * @brief Retrieves the number of packets received through the network 
     * interface since the device was last reset.
     *
     * @details This value will only change as the result of call to @c update().
     *
     * @return The number of packets received through the network interface since 
     * the device was last reset.
     *
     * @since BlackBerry 10.2.0
     */
    quint64 packetsReceived() const;
    
    /*!
     * @brief Retrieves the number of bytes received through the network 
     * interface since the device was last reset.
     *
     * @details This value will only change as the result of call to @c update().
     *
     * @return The number of bytes received through the network interface since 
     * the device was last reset.
     *
     * @since BlackBerry 10.2.0
     */
    quint64 bytesReceived() const;
    
    /*!
     * @brief Retrieves the number of packets sent through the network interface 
     * since the device was last reset.
     *
     * @details This value will only change as the result of call to @c update().
     *
     * @return The number of packets sent through the network interface since the 
     * device was last reset.
     *
     * @since BlackBerry 10.2.0
     */
    quint64 packetsSent() const;
    
    /*!
     * @brief Retrieves the number of bytes sent through the network interface 
     * since the device was last reset.
     *
     * @details This value will only change as the result of call to @c update().
     *
     * @return The number of bytes sent through the network interface since the 
     * device was last reset.
     *
     * @since BlackBerry 10.2.0
     */
    quint64 bytesSent() const;
    
    /*!
     * @brief Updates all packet/byte counts cached by this object.
     *
     * @return True if the operation succeeded; false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT bool update();

Q_SIGNALS:
    /*!
     * @brief Emitted when the name of the network interface this object represents 
     * changes.
     *
     * @param networkInterfaceName The name of the network interface represented 
     * by this object
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.2.0
     */
    void networkInterfaceNameChanged(const QString &networkInterfaceName);
    
    /*!
     * @brief Emitted when the number of packets received through the network 
     * interface changes.
     *
     * @details This property will only change as the result of a call to 
     * @c update().
     *
     * @param packetsReceived The number of packets received through the network 
     * interface since the device was last reset.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.2.0
     */
    void packetsReceivedChanged(quint64 packetsReceived);
    
    /*!
     * @brief Emitted when the number of bytes received through the network 
     * interface changes.
     *
     * @details This property will only change as the result of a call to 
     * @c update().
     *
     * @param bytesReceived The number of bytes received through the network 
     * interface since the device was last reset.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.2.0
     */
    void bytesReceivedChanged(quint64 bytesReceived);
    
    /*!
     * @brief Emitted when the number of packets sent through the network 
     * interface changes.
     *
     * @details This property will only change as the result of a call to 
     * @c update().
     *
     * @param packetsSent The number of packets sent through the network interface 
     * since the device was last reset.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.2.0
     */
    void packetsSentChanged(quint64 packetsSent);
    
    /*!
     * @brief Emitted when the number of bytes sent through the network interface 
     * changes.
     *
     * @details This property will only change as the result of a call to 
     * @c update().
     *
     * @param bytesSent The number of bytes sent through the network interface 
     * since the device was last reset.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.2.0
     */
    void bytesSentChanged(quint64 bytesSent);

private:
//!@cond PRIVATE
    Q_DECLARE_PRIVATE(NetworkDataUsage);
    Q_DISABLE_COPY(NetworkDataUsage);
    QScopedPointer<NetworkDataUsagePrivate> d_ptr;
//!@endcond
};

} // namespace device
} // namespace bb

QML_DECLARE_TYPE(bb::device::NetworkDataUsage)
#endif // BB_DEVICE_NETWORKDATAUSAGE_HPP
