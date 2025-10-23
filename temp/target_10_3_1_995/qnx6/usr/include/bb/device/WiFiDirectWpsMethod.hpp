/*!
 * @copyright
 * Copyright BlackBerry Limited, 2013-2013
 * BlackBerry Limited. All rights reserved.
 */

#ifndef BB_DEVICE_WIFIDIRECTWPSMETHOD_HPP
#define BB_DEVICE_WIFIDIRECTWPSMETHOD_HPP

#include <bb/device/Global>
#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace device
{

/*!
 * @headerfile WiFiDirectWpsMethod.hpp <bb/device/WiFiDirectWpsMethod>
 *
 * @brief The WPS connection method to use.
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Control"/>
 * <library name="bbdevice"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_DEVICE_EXPORT WiFiDirectWpsMethod
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief The WPS connection method to use.
     *
     * @since BlackBerry 10.2.0
     */
    enum Type {
    	/*!
    	 * @brief The connection is completed through a physical button press on the devices.
    	 *
    	 * @since BlackBerry 10.2.0
    	 */
        PushButtonConfiguration = 0,

        /*!
         * @brief A random PIN is assigned for the connection attempt.
         *
         * @since BlackBerry 10.2.0
         */
        RandomPin = 1,

        /*!
         * @brief A custom PIN is provided for the connection attempt.
         *
         * @since BlackBerry 10.2.0
         */
        PresetPin = 2
    };

private:
//!@cond PRIVATE
    WiFiDirectWpsMethod();
    ~WiFiDirectWpsMethod();
//!@endcond
};

} // namespace device
} // namespace bb

QML_DECLARE_TYPE(bb::device::WiFiDirectWpsMethod)
#endif // BB_DEVICE_WIFIDIRECTWPSMETHOD_HPP
