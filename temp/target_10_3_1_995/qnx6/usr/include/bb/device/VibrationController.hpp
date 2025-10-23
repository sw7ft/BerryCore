/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_DEVICE_VIBRATIONCONTROLLER_HPP
#define BB_DEVICE_VIBRATIONCONTROLLER_HPP

#include <bb/device/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace device
{

class VibrationControllerPrivate;

/*!
 * @headerfile VibrationController.hpp <bb/device/VibrationController>
 *
 * @brief Allows control of vibration.
 *
 * @details The @c VibrationController class allows control of device vibration.
 *
 * Only one vibration request is supported at one time, device-wide. Further
 * vibration requests supercede the previous vibration request. For example,
 * if process A requests a vibration, then 1 second later process B requests
 * a 5 second vibration, process A's vibration request is terminated after
 * only 1 second, and process B's request plays for 5 seconds.
 *
 * Note that the maximum time allowed for a vibration is 5000ms (5 seconds).
 * Durations requested for longer will be truncated to 5000ms.
 *
 * Vibration is not supported in all cases on all devices. Use @c isSupported()
 * to determine whether you can use this class to control vibration.
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Control"/>
 * <library name="bbdevice"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_DEVICE_EXPORT VibrationController : public QObject
{
    Q_OBJECT

    /*!
     * @brief Whether you can make the device vibrate.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY( bool supported READ isSupported CONSTANT FINAL )

public:

    /*!
     * @brief Construct a @c VibrationController instance.
     *
     * @param parent If not 0, the supplied parent will be responsible for deleting 
     *               this instance.
     *
     * @since BlackBerry 10.0.0
     */
    explicit VibrationController( QObject *parent = 0 );

    /*!
     * @brief Destroy this @c VibrationController instance.
     *
     * @details This has no affect on in-progress vibrations.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~VibrationController();

    /*!
     * @brief Check whether you can make the device vibrate.
     *
     * @return Returns @c true if you can make the device vibrate, @c false 
     *         otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE bool isSupported() const;

public Q_SLOTS:
    /*!
     * @brief Make the device vibrate.
     *
     * @param intensity Intensity of the vibration, from 1 to 100.
     *
     * @warning Intensity value is currently ignored. All values treated as 100.
     *
     * @ingroup Slots
     *
     * @since BlackBerry 10.0.0
     */
    void start( unsigned int intensity = 100 );

    /*!
     * @brief Make the device vibrate.
     *
     * @param intensity Intensity of the vibration, from 1 to 100.
     * @param milliseconds Duration of the vibration, in milliseconds.
     *
     * @warning Intensity value is currently ignored. All values treated as 100. Milliseconds greater than 5000 will be truncated to 5000.
     *
     * @ingroup Slots
     *
     * @since BlackBerry 10.0.0
     */
    void start( unsigned int intensity, unsigned int milliseconds );

    /*!
     * @brief Stop any in-progress vibration.
     *
     * @details This function lets you cancel any in-progress vibration.
     *
     * @ingroup Slots
     *
     * @since BlackBerry 10.0.0
     */
    void stop();

private:
//!@cond PRIVATE
    Q_DECLARE_PRIVATE(VibrationController)
    Q_DISABLE_COPY(VibrationController)
    QScopedPointer<VibrationControllerPrivate> d_ptr;
//!@endcond
};

} // namespace device
} // namespace bb

QML_DECLARE_TYPE(bb::device::VibrationController)

#endif // BB_DEVICE_INFO_HPP
