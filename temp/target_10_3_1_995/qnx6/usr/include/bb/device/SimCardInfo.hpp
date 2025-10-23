/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_DEVICE_SIMCARDINFO_HPP
#define BB_DEVICE_SIMCARDINFO_HPP

#include <bb/device/Global>
#include <bb/device/SimCardState>

#include <QObject>
#include <QString>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace device
{

class SimCardInfoPrivate;

/*!
 * @headerfile SimCardInfo.hpp <bb/device/SimCardInfo>
 *
 * @brief Encapsulates the state and contents of a subscriber identification module 
 *        (SIM) card.
 *
 * @details The SIM card stores information used to authenticate and identify a 
 *          subscriber of a cellular network. The presence of a SIM card can be 
 *          detected using the @c state() method. Information stored on the SIM card 
 *          includes the subscriber's home network (see @c mobileCountryCode() and 
 *          @c mobileNetworkCode()) and the serial number of the SIM card 
 *          (see @c serialNumber()).
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Radio and SIM"/>
 * <library name="bbdevice"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_DEVICE_EXPORT SimCardInfo : public QObject
{
    Q_OBJECT

    /*!
     * @brief Indicates whether the data on the SIM card can be accessed or why not.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::device::SimCardState::Type state READ state NOTIFY stateChanged FINAL)

    /*!
     * @brief Unique identifier for the country where the SIM card's home network is
     *           located.
     *
     * @permissions The application must have the @c read_device_identifying_information permission to
     *              access this property.
     *
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString mobileCountryCode READ mobileCountryCode NOTIFY mobileCountryCodeChanged FINAL)

    /*!
     * @brief Unique identifier for the SIM card's home network within its country.
     *
     * @permissions The application must have the @c read_device_identifying_information permission to
     *              access this property.
     *
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString mobileNetworkCode READ mobileNetworkCode NOTIFY mobileNetworkCodeChanged FINAL)

    /*!
     * @brief Unique identifier for the SIM card.
     *
     * @permissions The application must have the @c read_device_identifying_information permission to
     *              access this property.
     *
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString serialNumber READ serialNumber NOTIFY serialNumberChanged FINAL)

//! @cond PRIVATE    
    /*!
     * @brief The subscriber identifier (IMSI) of the SIM card.
     *
     * @permissions The application must have the @c access_uicc_carrier_restricted 
     *              permission to access this property.
     *
     * @since BlackBerry 10.0.0
     */
     Q_PROPERTY(QString subscriberIdentifier READ subscriberIdentifier NOTIFY subscriberIdentifierChanged FINAL )
//! @endcond
     
public:
    /*!
     * @brief Creates a new @c SimCardInfo object.
     *
     * @param parent If not 0, the supplied parent will be responsible for deleting 
     *               this instance.
     *
     * @since BlackBerry 10.0.0
     */
    explicit SimCardInfo(QObject *parent = 0);
    
    /*!
     * @brief Destroys this @c SimCardInfo object.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~SimCardInfo();

    /*!
     * @brief Retrieves the state of the SIM card.
     *
     * @return Returns the state of the SIM card or @c SimCardState::NotDetected if 
     *         the caller does not have sufficient permission.
     *
     * @since BlackBerry 10.0.0
     */
    bb::device::SimCardState::Type state() const;
    
    /*!
     * @brief Retrieves the unique identifier for the country where the SIM card's 
     *        home network is located.
     *
     * @details The mobile country code (MCC) is composed of 3 or 4 decimal digits.
     *          For more information about the structure of the MCC, see ITU-T 
     *          recommendation E.212.
     *
     * @return Returns the country code of the SIM card's home network encoded as a 
     *         string, or an empty string if the caller does not have sufficient 
     *         permission or if the SIM card's state is not @c SimCardState::Ready.
     *
     * @permissions The application must have the @c read_device_identifying_information permission to
     *              access this method.
     *
     *
     * @since BlackBerry 10.0.0
     */
    QString mobileCountryCode() const;
    
    /*!
     * @brief Retrieves the unique identifier for the SIM card's home network within 
     *        its country.
     *
     * @details The mobile network code (MNC) is composed of 2 or 3 decimal digits. 
     *          For further details about the structure of the MNC, see ITU-T 
     *          recommendation E.212.
     *
     * @return Returns the network code of the SIM card's home network encoded as a 
     *         string, or an empty string if the caller does not have sufficient 
     *         permission or if the SIM card's state is not @c SimCardState::Ready.
     *
     * @permissions The application must have the @c read_device_identifying_information permission to
     *              access this method.
     *
     *
     * @since BlackBerry 10.0.0
     */
    QString mobileNetworkCode() const;
    
    /*!
     * @brief Retrieves the unique identifier for the SIM card.
     *
     * @details The integrated circuit card identifier (ICCID) uniquely identifies a 
     *          SIM card. The ICCID is composed of 19 or 20 decimal digits plus a 
     *          check digit. For more information about the structure of the ICCID, 
     *          see ITU-T recommendation E.118.
     *
     * @return Returns the ICCID of the SIM card encoded as a string, or an empty 
     *         string if the caller does not have sufficient permission or if the SIM 
     *         card's state is not @c SimCardState::Ready.
     *
     * @permissions The application must have the @c read_device_identifying_information permission to
     *              access this method.
     *
     *
     * @since BlackBerry 10.0.0
     */
    QString serialNumber() const;

//! @cond PRIVATE
    /*!
     * @brief Retrieves the unique subscriber identifier for the SIM card.
     *
     * @details The unique identification associated with all GSM, UMTS and LTE 
     *          network SIM cards, stored on the device, and sent by the phone to the 
     *          network.
     *
     * @return Returns the IMSI of the SIM card encoded as a string, or an empty 
     *         string if the caller does not have sufficient permission, or if the 
     *         SIM card does not offer a value for retrieval.
     *
     * @permissions The application must have the @c access_uicc_carrier_restricted 
     *              permission to access this method.
     *
     * @since BlackBerry 10.0.0
     */
    QString subscriberIdentifier() const;
//! @endcond
    
Q_SIGNALS:
    /*!
     * @brief Emitted when the state of the SIM card changes.
     *
     * @param state The new state of the SIM card.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void stateChanged(bb::device::SimCardState::Type state);
    
    /*!
     * @brief Emitted when the mobile country code (MCC) of the SIM card's home 
     *        network changes. 
     *
     * @param mcc The new MCC of the SIM card's home network.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void mobileCountryCodeChanged(const QString &mcc);
    
    /*!
     * @brief Emitted when the mobile network code (MNC) of the SIM card's home 
     *        network changes.
     *
     * @param mnc The new MNC of the SIM card's home network.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void mobileNetworkCodeChanged(const QString &mnc);
    
    /*!
     * @brief Emitted when the integrated circuit card identifier (ICCID) of the SIM
     *        card changes.
     *
     * @param serialNumber The new ICCID of the SIM card.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void serialNumberChanged(const QString &serialNumber);

//! @cond PRIVATE    
    /*!
     * @brief Emitted when the subscriber identifier of the SIM card changes.
     * 
     * @param subscriberIdentifier The new IMSI of the SIM card.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void subscriberIdentifierChanged( const QString &subscriberIdentifier );
//! @endcond
    
protected:
//!@cond PRIVATE
    Q_SIGNAL void stateChanged(int state);
//!@endcond

private:
//!@cond PRIVATE
    QScopedPointer<SimCardInfoPrivate> d_ptr;
    Q_DECLARE_PRIVATE(SimCardInfo)
    Q_DISABLE_COPY(SimCardInfo)
//!@endcond
};

} // namespace device
} // namespace bb

QML_DECLARE_TYPE(bb::device::SimCardInfo)

#endif // BB_DEVICE_SIMCARDINFO_HPP
