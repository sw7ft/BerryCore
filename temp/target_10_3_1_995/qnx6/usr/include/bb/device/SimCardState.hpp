/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_DEVICE_SIMCARDSTATE_HPP
#define BB_DEVICE_SIMCARDSTATE_HPP

#include <bb/device/Global>
#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace device
{

/*!
 * @headerfile SimCardState.hpp <bb/device/SimCardState>
 *
 * @brief The state of the SIM card.
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Radio and SIM"/>
 * <library name="bbdevice"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_DEVICE_EXPORT SimCardState
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief The state of the SIM card.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief SIM card is not present.
         *
         * @details The SIM card slot is empty, a foreign object was inserted, or 
         *          the SIM card has been inserted incorrectly.
         *
         * @since BlackBerry 10.0.0
         */
        NotDetected = 0,

        /*!
         * @brief SIM card is not valid.
         *
         * @details The SIM card is for a different carrier or the SIM card is not
         *          compatible with the device's technology.
         *
         * @since BlackBerry 10.0.0
         */
        Incompatible = 1,

        /*!
         * @brief SIM card is not activated.
         *
         * @since BlackBerry 10.0.0
         */
        NotProvisioned = 2,

        /*!
         * @brief SIM card is not accessible.
         *
         * @details An invalid response was received from the SIM card, the SIM card 
         *          is not readable, the SIM card is corrupt, or the SIM card could 
         *          not be initialized.
         *
         * @since BlackBerry 10.0.0
         */
        ReadError = 3,

        /*!
         * @brief SIM card requires CHV validation.
         *
         * @details The SIM card is present but a PIN is required to access it.
         *
         * @since BlackBerry 10.0.0
         */
        PinRequired = 4,

        /*!
         * @brief SIM card is ready for normal operation.
         *
         * @since BlackBerry 10.0.0
         */
        Ready = 5
    };

private:
//!@cond PRIVATE
    SimCardState();
    ~SimCardState();
//!@endcond
};

} // namespace device
} // namespace bb

QML_DECLARE_TYPE(bb::device::SimCardState)
#endif // BB_DEVICE_SIMCARDSTATE_HPP
