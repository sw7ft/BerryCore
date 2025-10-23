/*!
 * @copyright
 * Copyright Research In Motion Limited, 2011-2014
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_DEVICE_HARDWAREINFO_HPP
#define BB_DEVICE_HARDWAREINFO_HPP

#include <bb/device/Global>
#include <bb/device/HdmiConnector>

#include <QObject>
#include <QString>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace device
{
class HardwareInfoPrivate;

/*!
 * @headerfile HardwareInfo.hpp <bb/device/HardwareInfo>
 *
 * @brief Provides access to information about the device hardware.
 *
 * @details The @c HardwareInfo class provides access to information about the
 *          configuration, availability, or general values about the device hardware.
 *          Many of the methods are protected by permissions because they can be used
 *          to uniquely identify a device. Be sure to check the description of
 *          individual methods before using them, and ensure that the required
 *          permissions have been requested.
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Info"/>
 * <library name="bbdevice"/>
 * @endxmlonly
 *
 *
 * @since BlackBerry 10.0.0
 */
class BB_DEVICE_EXPORT HardwareInfo: public QObject
{
    Q_OBJECT

    /*!
     * @brief The unique identifier for the device.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString pin READ pin CONSTANT FINAL)

    /*!
     * @brief The serial number for the device.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString serialNumber READ serialNumber CONSTANT FINAL)

    /*!
     * @brief International mobile equipment identity (IMEI) of the device.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString imei READ imei CONSTANT FINAL)

    /*!
     * @brief Mobile equipment identifier (MEID) of the device.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString meid READ meid CONSTANT FINAL)

    /*!
     * @brief Hardware identifier of the device.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY( QString hardwareId READ hardwareId CONSTANT FINAL )

    /*!
     * @brief Name of the device.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY( QString deviceName READ deviceName CONSTANT FINAL )

    /*!
     * @brief The device model name.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY( QString modelName READ modelName CONSTANT FINAL )

    /*!
     * @brief The device model number.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY( QString modelNumber READ modelNumber CONSTANT FINAL )

    /*!
     * @brief Indicates if the device is a physical keyboard device or not.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY( bool isPhysicalKeyboardDevice READ isPhysicalKeyboardDevice CONSTANT FINAL )

    /*!
     * @brief Indicates what kind of HDMI connector the device has, if any.
     *
     * @since BlackBerry 10.1.0
     */
    Q_PROPERTY( bb::device::HdmiConnector::Type hdmiConnector READ hdmiConnector CONSTANT FINAL REVISION 1 )


    /*!
     * @brief Indicates if the device is a trackpad device or not.
     *
     * @since BlackBerry 10.3.1
     */
    Q_PROPERTY( bool isTrackpadDevice READ isTrackpadDevice CONSTANT FINAL REVISION 2 )

    /*!
     * @brief Indicates if the device has physical phone keys (Send and End) or not.
     *
     * @since BlackBerry 10.3.1
     */
    Q_PROPERTY( bool hasPhysicalPhoneKeys READ hasPhysicalPhoneKeys CONSTANT FINAL REVISION 2 )  

    /*!
     * @brief Indicates if the device has a physical back button or not.
     *
     * @since BlackBerry 10.3.1
     */
    Q_PROPERTY( bool hasPhysicalBackButton READ hasPhysicalBackButton CONSTANT FINAL REVISION 2 )

    /*!
     * @brief Indicates if the device has a physical menu button or not.
     *
     * @since BlackBerry 10.3.1
     */
    Q_PROPERTY( bool hasPhysicalMenuButton READ hasPhysicalMenuButton CONSTANT FINAL REVISION 2 )

public:
   /*!
    * @brief Constructs a @c HardwareInfo object.
    *
    * @details Constructs a @c HardwareInfo object that can be used to retrieve
    *          information about the device.
    *
    * @param parent If not 0, the supplied parent is responsible for deleting this
    *               instance.
    *
    * @since BlackBerry 10.0.0
    */
   explicit HardwareInfo(QObject * parent = 0);

   /*!
    * @brief Destroys this @c HardwareInfo object.
    *
    * @since BlackBerry 10.0.0
    */
   virtual ~HardwareInfo();

    /*!
     * @brief Retrieves the device PIN.
     *
     * @details This function lets you retrieve the PIN of the BlackBerry device,
     *          which is a unique identifier for the device.
     *
     * Some examples of PIN number values are:
     *  - @c "0x08A34C0A"
     *  - @c "0x31C45EF8"
     *  - @c "0x89912341"
     *
     * @permissions The application must have the
     *              @c read_device_identifying_information permission to access
     *              the device PIN.
     *
     * @return The PIN of the device, or an empty string if the calling function
     *         does not have sufficient permission to read the PIN value.
     *
     * @since BlackBerry 10.0.0
     */
    QString pin() const;

    /*!
     * @brief Retrieves the device serial number.
     *
     * @details This function retrieves the serial number of the device as a
     *          @c QString. When displayed as a string it typically takes the form of
     *          a 22 digit base 10 number.
     *
     * Some examples of serial number values are:
     * - @c "0000000000134300329165"
     * - @c "0000000000134300213459"
     * - @c "0000000000134300118234"
     *
     * @permissions The application must have the @c
     *              read_device_identifying_information permission to access the
     *              serial number.
     *
     * @return The serial number of the device, or an empty string if the
     *         calling function does not have sufficient permission.
     *
     * @since BlackBerry 10.0.0
     */
    QString serialNumber() const;

    /*!
     * @brief Retrieves the international mobile equipment identity (IMEI) of the
     *        device.
     *
     * @details The IMEI uniquely identifies a device that connects to a GSM cellular
     *          network. The IMEI is composed of 14 decimal digits, plus a check
     *          digit. For more information about the structure of the IMEI, see
     *          3GPP TS 23.003.
     *
     * @permissions The application must have the
     *              @c read_device_identifying_information permission to access the
     *              deivce's IMEI.
     *
     * @return The IMEI of the device encoded as a string, an empty string in the
     *         case where either the calling function does not have sufficient
     *         permission to read the IMEI, or if the device has no IMEI.
     *
     * @since BlackBerry 10.0.0
     */
    QString imei() const;

    /*!
     * @brief Retrieves the mobile equipment identifier (MEID) of the device.
     *
     * @details The MEID uniquely identifies a device that connects to a CDMA
     *          cellular network. The MEID is composed of 14 hexadecimal digits.
     *          For more information about the structure of the MEID, see
     *          3GPP2 report S.R0048.
     *
     * @permissions The application must have the
     *              @c read_device_identifying_information permission to access the
     *              device's MEID.
     *
     * @return The MEID of the device encoded as a string, or an empty string in the
     *         case where either the calling function does not have sufficient
     *         permission to read the MEID, or if the device has no MEID.
     *
     * @since BlackBerry 10.0.0
     */
    QString meid() const;

    /*!
     * @brief Retrieves the hardware identifier of the device.
     *
     * @details The hardware identifier provides a value that is identical across all
     *          devices of similar configuration.
     *
     * An example of a hardware identifier is:
     *  - @c "0x04002607".
     *
     * All devices with this identifier will have the same
     * characteristics, such as radio, screen size, processor, etc.
     *
     * @return The hardware identifier of the device encoded as a string.
     *
     * @since BlackBerry 10.0.0
     */
    QString hardwareId() const;

    /*!
     * @brief Retrieves the 'name' identifier attached to the device model.
     *
     * @details The device name provides a value that helps to identify the device.
     *
     * @return The name of the device encoded as a string.
     *
     * @since BlackBerry 10.0.0
     */
    QString deviceName() const;

    /*!
     * @brief Returns the number of processors on the device.
     *
     * @return The number of processors on the device, or 0 on error.
     *
     * @since BlackBerry 10.0.0
     */
    int processorCount() const;
//!@cond PRIVATE
    /*
     * Non-const version of the above, for backwards compatibility. Use of this
     * method is discouraged.
     */
    int processorCount() BB_DEVICE_DEPRECATED;
//!@endcond

    /*!
     * @brief Returns the CPU clock speed of the processor at the supplied index, in
     *        MHz.
     *
     * @param cpuNumber The index of the CPU for which the clock speed is requested.
     *                  Valid indices are greater than or equal to 0 and less than
     *                  the number of available processors
     *                  (as given by @c HardwareInfo::processorCount()).
     *
     * @return The clock speed of the processor at the provided index, or 0 on error.
     *
     * @since BlackBerry 10.0.0
     */
    int processorSpeed(int cpuNumber) const;
//!@cond PRIVATE
    /*
     * Non-const version of the above, for backwards compatibility. Use of this
     * method is discouraged.
     */
    int processorSpeed(int cpuNumber) BB_DEVICE_DEPRECATED;
//!@endcond

    /*!
     * @brief Returns the CPU model of the processor at the supplied index.
     *
     * @param cpuNumber The index of the CPU for the model requested. Valid indices
     * are greater than or equal to 0 and less than the number of available
     * processors (as given by @c HardwareInfo::processorCount()).
     *
     * @return The model of the processor at the index provided, and an empty
     *         string otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    QString processorModel(int cpuNumber) const;
//!@cond PRIVATE
    /*
     * Non-const version of the above, for backwards compatibility. Use of this
     * method is discouraged.
     */
    QString processorModel(int cpuNumber) BB_DEVICE_DEPRECATED;
//!@endcond

    /*!
     * @brief Returns the model name of the device.
     *
     * @permissions The application must have the
     *              @c access_device_model_name permission to access the model name
     *              of the device.
     *
     * @return The model name of the device, or an empty string otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    QString modelName() const;

    /*!
     * @brief Returns the model number of the device.
     *
     * @permissions The application must have the
     *              @c access_device_model_name permission to access the model number
     *              of the device.
     *
     * @return The model number of the device, or an empty string otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    QString modelNumber() const;

    /*!
     * @brief Returns whether or not a physical keyboard is present on the device.
     *
     * @return @c true if the device has a physical keyboard, and @c false
     *         otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isPhysicalKeyboardDevice() const;

    /*!
     * @brief Indicates whether the device possesses an HDMI connector, and if so what type.
     *
     * @return One of @c bb::device::HdmiConnector::Type.
     *
     * @since BlackBerry 10.1.0
     */
    bb::device::HdmiConnector::Type hdmiConnector() const;

    /*!
     * @brief Returns whether or not a trackpad is present on the device.
     *
     * @return @c true if the device has a trackpad, and @c false
     *         otherwise.
     *
     * @since BlackBerry 10.3.1
     */
    bool isTrackpadDevice() const;

    /*!
     * @brief Returns whether or not physical phone keys (Send and End)
     * are present on the device.
     *
     * @return @c true if the device has phone keys, and @c false
     *         otherwise.
     *
     * @since BlackBerry 10.3.1
     */
    bool hasPhysicalPhoneKeys() const;

    /*!
     * @brief Returns whether or not a physical back button is present
     * on the device.
     *
     * @return @c true if the device has a back button, and @c false
     *         otherwise.
     *
     * @since BlackBerry 10.3.1
     */
    bool hasPhysicalBackButton() const;

    /*!
     * @brief Returns whether or not a physical menu button is present
     * on the device.
     *
     * @return @c true if the device has a menu button, and @c false
     *         otherwise.
     *
     * @since BlackBerry 10.3.1
     */
    bool hasPhysicalMenuButton() const;

private:
//!@cond PRIVATE
    QScopedPointer<HardwareInfoPrivate> d_ptr;
    Q_DECLARE_PRIVATE(HardwareInfo)
    Q_DISABLE_COPY(HardwareInfo)
//!@endcond
};

} // namespace device
} // namespace bb

QML_DECLARE_TYPE(bb::device::HardwareInfo)

#endif // BB_DEVICE_HARDWAREINFO_HPP
