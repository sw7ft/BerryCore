/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_DEVICE_CELLULARRADIOINFO_HPP
#define BB_DEVICE_CELLULARRADIOINFO_HPP

#include <bb/device/Global>
#include <bb/device/CellularBand>
#include <bb/device/CellularService>
#include <bb/device/CellularTechnology>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace device
{

class CellularRadioInfoPrivate;

/*!
 * @headerfile CellularRadioInfo.hpp <bb/device/CellularRadioInfo>
 *
 * @brief Encapsulates the capabilities and state of the cellular radio.
 *
 * @details The @c CellularRadioInfo class provides information about which types of 
 * wireless communication standards, voice/data services, and frequencies the radio 
 * supports (see @c technologies(), @c services(), and @c bands() respectively). Of the
 * supported wireless communication standards, the user may choose to enable all or a 
 * subset using the settings application (see @c enabledTechnologies()). The user may 
 * also use the settings application to turn the radio on and off (see @c poweredOn()).
 *
 * The @c networkCount() and @c activeTechnologies() methods provide information about
 * how many cellular networks the radio is connected to, and what wireless communication
 * standards they utilize. Additional details about a connected network can be obtained 
 * using the @c CellularNetworkInfo class.
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Radio and SIM"/>
 * <library name="bbdevice"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_DEVICE_EXPORT CellularRadioInfo : public QObject
{
    Q_OBJECT

    /*!
     * @brief Flag indicating whether the radio is turned on or off.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bool poweredOn READ isPoweredOn NOTIFY poweredOnChanged FINAL)
        
    /*!
     * @brief Bitfield of wireless communication standards the radio supports.
     *
     * @see @c bb::device::CellularTechnology::Type for a list of bitfield values.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::device::CellularTechnology::Types technologies READ technologies CONSTANT FINAL)

    /*!
     * @brief Bitfield of voice/data services the radio supports.
     *
     * @see @c bb::device::CellularService::Type for a list of bitfield values.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::device::CellularService::Types services READ services CONSTANT FINAL)

    /*!
     * @brief Bitfield of frequency bands the radio supports.
     *
     * @see @c bb::device::CellularBand::Type for a list of bitfield values.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::device::CellularBand::Types bands READ bands CONSTANT FINAL)

    /*!
     * @brief Bitfield of wireless communication standards that are currently allowed.
     *
     * @see @c bb::device::CellularTechnology::Type for a list of bitfield values.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::device::CellularTechnology::Types enabledTechnologies READ enabledTechnologies NOTIFY enabledTechnologiesChanged FINAL)
    
    /*!
     * @brief Bitfield of wireless communication standards that are currently in use.
     *
     * @see @c bb::device::CellularTechnology::Type for a list of bitfield values.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::device::CellularTechnology::Types activeTechnologies READ activeTechnologies NOTIFY activeTechnologiesChanged FINAL)
    
    /*!
     * @brief Number of connected cellular networks.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(int networkCount READ networkCount NOTIFY networkCountChanged FINAL)
    
    /*!
     * @brief Flag indicating if data services are enabled or disabled.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool dataEnabled READ isDataEnabled NOTIFY dataEnabledChanged FINAL REVISION 1)
    
    /*!
     * @brief Flag indicating if the device is beyond coverage of its home network for data services.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool dataRoaming READ isDataRoaming NOTIFY dataRoamingChanged FINAL REVISION 1)

public:
    /*!
     * @brief Creates a new @c CellularRadioInfo object.
     *
     * @param parent If not 0, the supplied parent will be responsible for deleting this instance.
     *
     * @since BlackBerry 10.0.0
     */
    explicit CellularRadioInfo(QObject *parent = 0);
    
    /*!
     * @brief Destroys this @c CellularRadioInfo object.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~CellularRadioInfo();

    /*!
     * @brief Indicates whether the radio is turned on or off.
     *
     * @return Returns @c true if the radio is turned on, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isPoweredOn() const;
    
    /*!
     * @brief Retrieves a bitfield of wireless communication standards the radio supports.
     *
     * @return Returns a bitfield of wireless communication standards the radio supports
     *
     * @see @c bb::device::CellularTechnology::Type for a list of bitfield values.
     *
     * @since BlackBerry 10.0.0
     */
    bb::device::CellularTechnology::Types technologies() const;
    
    /*!
     * @brief Retrieves a bitfield of voice/data services the radio supports.
     *
     * @return Returns a bitfield of voice/data services the radio supports.
     *
     * @see @c bb::device::CellularService::Type for a list of bitfield values.
     *
     * @since BlackBerry 10.0.0
     */
    bb::device::CellularService::Types services() const;
    
    /*!
     * @brief Retrieves a bitfield of frequency bands the radio supports.
     *
     * @return Returns a bitfield of frequency bands the radio supports.
     *
     * @see @c bb::device::CellularBand::Type for a list of bitfield values.
     *
     * @since BlackBerry 10.0.0
     */
    bb::device::CellularBand::Types bands() const;
    
    /*!
     * @brief Retrieves a bitfield of wireless communication standards that are currently 
     * allowed.
     *
     * @return Returns a bitfield of wireless communication standards that are currently allowed.
     *
     * @see @c bb::device::CellularTechnology::Type for a list of bitfield values.
     *
     * @since BlackBerry 10.0.0
     */
    bb::device::CellularTechnology::Types enabledTechnologies() const;
    
    /*!
     * @brief Retrieves a bitfield of wireless communication standards that are currently 
     * in use.
     *
     * @return Returns a bitfield of wireless communication standards that are currently in use.
     *
     * @see @c bb::device::CellularTechnology::Type for a list of bitfield values.
     *
     * @since BlackBerry 10.0.0
     */
    bb::device::CellularTechnology::Types activeTechnologies() const;
    
    /*!
     * @brief Retrieves the number of connected cellular networks.
     *
     * @return Returns the number of connected cellular networks.
     *
     * @since BlackBerry 10.0.0
     */
    int networkCount() const;
    
    /*!
     * @brief Indicates whether data services are enabled or disabled.
     *
     * @return Flag indicating if data services are enabled or disabled.
     *
     * @since BlackBerry 10.2.0
     */
    bool isDataEnabled() const;
    
    /*!
     * @brief Indicates whether the device is beyond coverage of its home network for data services.
     *
     * @return Flag indicating if the device is beyond coverage of its home network for data services.
     *
     * @since BlackBerry 10.2.0
     */
    bool isDataRoaming() const;

Q_SIGNALS:
    /*!
     * @brief Emitted when the radio turns on or off.
     *
     * @param poweredOn The new power state of the radio.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void poweredOnChanged(bool poweredOn);
    
    /*!
     * @brief Emitted when the allowed wireless communication standards change.
     *
     * @param technologies A bitfield of the new wireless communication standards that are 
     *                     currently allowed.
     *
     * @see @c bb::device::CellularTechnology::Type for a list of bitfield values.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void enabledTechnologiesChanged(bb::device::CellularTechnology::Types technologies);
    
    /*!
     * @brief Emitted when the active wireless communication standards change.
     *
     * @param technologies A bitfield of wireless communication standards that are currently in 
     *                     use.
     *
     * @see @c bb::device::CellularTechnology::Type for a list of bitfield values.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void activeTechnologiesChanged(bb::device::CellularTechnology::Types technologies);
    
    /*!
     * @brief Emitted when the number of connected cellular networks changes.
     *
     * @param networkCount The new number of connected cellular networks.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void networkCountChanged(int networkCount);
    
    /*!
     * @brief Emitted when data services become enabled or disabled.
     *
     * @param dataEnabled Flag indicating if data services are enabled or disabled.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.2.0
     */
    Q_REVISION(1) void dataEnabledChanged(bool dataEnabled);
    
    /*!
     * @brief Emitted when the roaming indicator for data services changes.
     *
     * @param dataRoaming Flag indicating if the device is beyond coverage of its home network for data services.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.2.0
     */
    Q_REVISION(1) void dataRoamingChanged(bool dataRoaming);

protected:
//!@cond PRIVATE
    Q_SIGNAL void enabledTechnologiesChanged(int technologies);

    Q_SIGNAL void activeTechnologiesChanged(int technologies);
//!@endcond

private:
//!@cond PRIVATE
    QScopedPointer<CellularRadioInfoPrivate> d_ptr;
    Q_DECLARE_PRIVATE(CellularRadioInfo)
    Q_DISABLE_COPY(CellularRadioInfo)
//!@endcond
};

} // namespace device
} // namespace bb

QML_DECLARE_TYPE(bb::device::CellularRadioInfo)

#endif // BB_DEVICE_CELLULARRADIOINFO_HPP
