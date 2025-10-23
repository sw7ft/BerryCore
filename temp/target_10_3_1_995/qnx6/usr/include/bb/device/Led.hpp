/*!
 * @copyright
 * Copyright Research In Motion Limited, 2011-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_DEVICE_LED_HPP
#define BB_DEVICE_LED_HPP

#include <bb/device/Global>
#include <bb/device/LedColor>

#include <QObject>
#include <QScopedPointer>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace device
{

class LedPrivate;

/*!
 * @headerfile Led.hpp <bb/device/Led>
 *
 * @brief The @c Led class represents requests for flashing the LED present on the 
 *        device.
 *
 * @permissions This class requires that the application be granted the 
 *              @c access_led_control capability.
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Control"/>
 * <library name="bbdevice"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_DEVICE_EXPORT Led : public QObject
{
    Q_OBJECT

    /*!
     * @brief Retrieve the color of the @c Led instance.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::device::LedColor::Type color READ color WRITE setColor RESET resetColor NOTIFY colorChanged FINAL)

    /*!
     * @brief Retrieve the number of flashes remaining for the @c Led instance.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(int remainingFlashCount READ remainingFlashCount NOTIFY remainingFlashCountChanged FINAL)

    /*!
     * @brief Retrieve the state of the @c Led instance.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bool active READ isActive NOTIFY activeChanged FINAL)

public:
    /*!
     * @brief Construct an @c Led instance with default options, i.e., with color as 
     *        @c bb::device::LedColor::Red.
     *
     * @details The @c Led instance is not activated automatically. Invoke @c flash()
     *          to activate the @c Led instance.
     *
     * @param parent If not 0, the supplied parent is responsible for deleting 
     *               this instance.
     *
     * @permissions This application must have the @c access_led_control permission 
     *              to use this class.
     *
     * @since BlackBerry 10.0.0
     */
    explicit Led(QObject* parent=0);

    /*!
     * @brief Construct an @c Led instance with a custom color.
     *
     * @details The @c Led instance is not activated automatically. Invoke @c flash()
     *          to activate the @c Led instance.
     *
     * @param ledColor The color of the LED request.
     * @param parent The parent of this instance.
     *
     * @permissions This application must have the @c access_led_control permission 
     *              to use this class.
     *
     * @since BlackBerry 10.0.0
     */
    explicit Led(bb::device::LedColor::Type ledColor, QObject* parent=0);

    /*!
     * @brief Destroy the @c Led instance.
     *
     * @details This will cancel any pending requests.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~Led();

    /*!
     * @brief Retrieve the color of the @c Led instance.
     * 
     * @details If @c Led::active property is @c true, this represents the color that
     *          is flashing.
     *
     * @return Returns the color of this instance.
     *
     * @since BlackBerry 10.0.0
     */
    bb::device::LedColor::Type color() const;

    /*!
     * @brief Retrieve the number of flashes remaining for the @c Led instance.
     *
     * @details If the @c Led::active property is @c false, 0 is returned.
     *          If the @c Led::active property is @c true, this represents the 
     *          remaining number of times that the active color is flashed.
     *          If the @c Led instance is set to flash indefinitely, a value of -1 
     *          is returned.
     * 
     * @return Returns the number of flashes remaining for this @c Led instance.
     *
     * @since BlackBerry 10.0.0
    */
    int remainingFlashCount() const;

    /*!
     * @brief Retrieve the state of the @c Led instance.
     * 
     * @details Represents the state of the requests initiated using this instance.
     *
     * @return Returns @c true if a flash request is pending.
     *
     * @since BlackBerry 10.0.0
     */
    bool isActive() const;

    /*!
     *
     * @brief Set the color of the @c Led instance.
     * 
     * @details If the @c Led::active property is @c true and @c ledColor is not
     *          @c LedColor::None, then the last request will continue with the new 
     *          color without resetting the @c Led::remainingFlashCount property.
     *          If @c ledColor is @c LedColor::None, then the request is 
     *          canceled, emitting the @c activeChanged() signal instead of the 
     *          @c colorChanged() signal.
     *
     * @param ledColor The new color for this instance.
     *
     * @since BlackBerry 10.0.0
     */
    void setColor(bb::device::LedColor::Type ledColor);

    /*!
     * @brief Reset the color of this instance.
     *
     * @details The default value is @c bb::device::LedColor::Red.
     *
     * @since BlackBerry 10.0.0
     */
    void resetColor();

public Q_SLOTS:
    /*!
     * @brief Requests that the LED is flashed indefinitely with the color returned 
     *        by @c color().
     *
     * @details The @c Led::active property is set to @c true.
     *
     * @note Any existing requests are canceled.
     * @note If the @c Led::color property is @c LedColor::None, then no action is 
     *       taken.
     *
     * @ingroup Slots
     *
     * @since BlackBerry 10.0.0
     */
    void flash();

    /*!
     * @brief Requests that the LED is flashed the specified number of times with the
     *        color returned by @c color().
     *
     * @details The @c Led::active property is set to @c true.
     *
     * @note Any existing requests are canceled.
     * @note If the @c Led::color property is @c LedColor::None, then no action is
     *       taken.
     *
     * @param count The number of times that the LED should be flashed. A negative  
     *              number is treated as a request to flash indefinitely.
     *
     * @ingroup Slots
     *
     * @since BlackBerry 10.0.0
     */
    void flash(int count);

    /*!
     * @brief Cancel any active requests that were made using @c flash().
     *
     * @details The @c Led::active property is set to false and any requests to flash
     *          the LED that were made outside of this instance are not canceled.
     *
     * @ingroup Slots
     *
     * @since BlackBerry 10.0.0
     */
    void cancel();

Q_SIGNALS:
    /*!
     * @brief Emitted when the @c Led::color property changes.
     *
     * @param value The new value for the @c Led::color property.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void colorChanged(bb::device::LedColor::Type value);

    /*!
     * @brief Emitted when the @c Led::remainingFlashCount property changes.
     *
     * @details When the count reaches 0, the request is completed, and therefore the
     *          @c activeChanged() signal is emitted instead of this signal.
     *
     * @note This signal is not emitted for indefinite flash requests.
     *
     * @param value The new value for the @c Led::remainingFlashCount property.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void remainingFlashCountChanged(int value);

    /*!
     * @brief Emitted when the @c Led::active property changes.
     *
     * @param value The new value for the @c Led::active property.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void activeChanged(bool value);

protected:
//!@cond PRIVATE
    Q_SIGNAL void colorChanged(int value);
//!@endcond

private:
//!@cond PRIVATE
    Q_DECLARE_PRIVATE(Led)
    Q_DISABLE_COPY(Led)
    QScopedPointer<LedPrivate> d_ptr;
//!@endcond
};

} // device
} // bb

QML_DECLARE_TYPE(bb::device::Led)

#endif // BB_DEVICE_LED_HPP
