/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_DEVICE_BATTERYINFO_HPP
#define BB_DEVICE_BATTERYINFO_HPP

#include <bb/device/BatteryChargingState>
#include <bb/device/BatteryCondition>
#include <bb/device/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace device
{

class BatteryInfoPrivate;

/*!
 * @headerfile BatteryInfo.hpp <bb/device/BatteryInfo>
 *
 * @brief A class that provides the battery information of the device.
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Info"/>
 * <library name="bbdevice"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_DEVICE_EXPORT BatteryInfo : public QObject
{
    Q_OBJECT

    /*!
     * @brief The level of charge left in the battery (as a percentage, 0 to 100).
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(int level READ level NOTIFY levelChanged FINAL)

    /*!
     * @brief The current charging state of the battery.  
     *
     * Used to determine if the battery is plugged in to a charging source, and whether it is charging.
     *
     * @see @c bb::device::BatteryChargingState.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::device::BatteryChargingState::Type chargingState READ chargingState NOTIFY levelChanged FINAL)

    /*!
     * @brief Indicates if a battery is present or not.
     *
     *
     * @since BlackBerry 10.0.0
     */
     Q_PROPERTY( bool present READ isPresent NOTIFY presentChanged FINAL )

     /*!
      * @brief Indicates the current condition of the battery.
      *
      * @see @c bb::device::BatteryCondition.
      *
      * @since BlackBerry 10.0.0
      */
     Q_PROPERTY( bb::device::BatteryCondition::Type condition READ condition NOTIFY conditionChanged FINAL)

    /*!
     * @brief fullChargeCapacity is the compensated capacity of the battery when fully charged. 
     *
     * fullChargeCapacity is measured in mAh.
     *
     * @since BlackBerry 10.0.0
     */
     Q_PROPERTY( int fullChargeCapacity READ fullChargeCapacity NOTIFY fullChargeCapacityChanged FINAL )

    /*!
     * @brief cycleCount is the number of cycles the battery has experienced with a range of 0 to 65,535.
     *
     * @since BlackBerry 10.0.0
     */
     Q_PROPERTY( int cycleCount READ cycleCount NOTIFY cycleCountChanged FINAL )

    /*!
     * @brief The average temperature of the battery. 
     *
     * If the battery has N thermistors, @c temperature is the average value of all the temperature readings in degrees Celsius.
     *
     * @since BlackBerry 10.0.0
     */
     Q_PROPERTY( float temperature READ temperature NOTIFY temperatureChanged FINAL )

    /*!
     * @brief The RxID of the wireless charging receiver chip. 
     *
     * The RxID is the string representation of an 11-byte value.
     * If the device has not been on a charging pad since boot up, the RxID will be an empty string.
     * The RxID is a wireless charging receiver identifier and can be used to identify the device to wireless charging systems.
     *
     * @since BlackBerry 10.3.0
     */
     Q_PROPERTY( QString rxid READ rxid NOTIFY rxidChanged FINAL )

public:
 
    /*!
     * @brief Constructs a @c BatteryInfo object.
     *
     * Constructs a @c BatteryInfo object from which may be retrieved information about the battery of the device.
     *
     * @param parent If not 0, the supplied parent will be responsible for deleting this instance.
     *
     * @note A @c BatteryInfo constructed in this way will return information on the active battery (if more than one
     * battery is present in the device).
     *
     * @since BlackBerry 10.0.0
     */
    explicit BatteryInfo(QObject * parent = 0);

    /*!
     * @brief Destroys this @c BatteryInfo object.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~BatteryInfo();

    /*!
     * @brief The percentage of battery charge.
     *
     * @return Battery level from 0 to 100, or -1 if the value was not available.
     *
     * @since BlackBerry 10.0.0
     */
    int level() const;
 
    /*!
     * @brief Retrieves the current charging state of the battery.
     * @see @c bb::device::BatteryChargingState.
     * @return The current charging state.
     *
     * @since BlackBerry 10.0.0
     */
    BatteryChargingState::Type chargingState() const;

    /*!
     * @brief Whether a battery is present or not.
     *
     * @return @c True if a battery is detected, @c False otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isPresent() const;

    /*!
     * @brief The condition of the battery.
     * 
     * @return One of @c bb::device::BatteryCondition.
     *
     * @since BlackBerry 10.0.0
     */
    BatteryCondition::Type condition() const;

    /*!
     * @brief fullChargeCapacity is the compensated capacity of the battery when fully charged. 
     *
     * fullChargeCapacity is measured in mAh.
     *
     * @return The number of mAh available when the battery is at full charge, or -1 if the value
     * was not available.
     *
     * @since BlackBerry 10.0.0
     */
    int fullChargeCapacity() const;

    /*!
     * @brief cycleCount is the number of cycles the battery has experienced with a range of 0 to 65,535.
     *
     * @return The cycle count as an integer, or -1 if the value was not available.
     *
     * @since BlackBerry 10.0.0
     */
    int cycleCount() const;

    /*!
     * @brief The average temperature of the battery. 
     *
     * If the battery has N thermistors, @c temperature() is the average value of all the temperature readings in degrees Celsius.
     *
     * @return The battery temperature measured in degrees Celsius, or @c std::numeric_limits<float>::min() if the value was not available.
     *
     * @since BlackBerry 10.0.0
     */
    float temperature() const;

    /*!
     * @brief The RxID of the wireless charging receiver chip. 
     *
     * The RxID is the string representation of an 11-byte value.
     * If the device has not been on a charging pad since boot up, the RxID will be an empty string. 
     *
     * @return The 11-byte value as a string or an empty string if the device has not been on the charging pad since boot up.
     *
     * @since BlackBerry 10.3.0
     */
    QString rxid() const;

Q_SIGNALS:

    /*!
     * @brief Emitted when either the charging level or the charging state changes (or both).
     *
     * @param level The battery level as a value from 0 to 100
     * @param newChargingState The current charging state.  @see @c bb::device::BatteryChargingState.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void levelChanged(int level, bb::device::BatteryChargingState::Type newChargingState);

    /*!
     * @brief Emitted if the presence of a battery changes.
     *
     * @param present The new indication of whether a battery is present or not.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void presentChanged( bool present );

    /*!
     * @brief Emitted if the condition of the battery changes.
     *
     * @param condition The new condition of the battery.  @see @c bb::device::BatteryCondition.
     *
     * @since BlackBerry 10.0.0
     */
    void conditionChanged( bb::device::BatteryCondition::Type condition );

    /*!
     * @brief Emitted if the full charge capacity changes.
     *
     * The capacity is measured in mAh.
     *
     * @param fullChargeCapacity The new full charge capacity.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void fullChargeCapacityChanged( int fullChargeCapacity );

    /*!
     * @brief Emitted when the cycle count changes.
     *
     * @param cycleCount The new cycle count.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void cycleCountChanged( int cycleCount );

    /*!
     * @brief Emitted when the battery temperature changes.
     *
     * The temperature is measured in degrees Celsius.
     *
     * @param temperature The new temperature in degrees Celsius.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void temperatureChanged( float temperature );

    /*!
     * @brief Emitted when the RxID changes.
     *
     * The RxID is the string representation of an 11-byte value.
     *
     * @param rxid The new RxID value.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.3.0
     */
    void rxidChanged( QString rxid  );

protected:
//!@cond PRIVATE
    Q_SIGNAL void levelChanged( int level, int newChargingState );

    Q_SIGNAL void conditionChanged( int condition );
//!@endcond

private:
    //!@cond PRIVATE
    Q_DISABLE_COPY(BatteryInfo)
    Q_DECLARE_PRIVATE(BatteryInfo)
    BatteryInfoPrivate * const d_ptr; // not a scoped ptr. see constructor.
    //!@endcond
};

} // namespace device
} // namespace bb

QML_DECLARE_TYPE(bb::device::BatteryInfo)

#endif // BB_DEVICE_BATTERYINFO_HPP
