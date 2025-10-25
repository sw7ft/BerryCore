/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_DEVICE_CELLULARSERVICE_HPP
#define BB_DEVICE_CELLULARSERVICE_HPP

#include <bb/device/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace device
{

/*!
 * @headerfile CellularService.hpp <bb/device/CellularService>
 *
 * @brief Services supported by a cellular radio or network.
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Radio and SIM"/>
 * <library name="bbdevice"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_DEVICE_EXPORT CellularService
{
    Q_GADGET
    Q_ENUMS(Type)
    Q_FLAGS(Types)

public:
    /*!
     * @brief Services supported by a cellular radio or network.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief No services supported.
         *
         * @since BlackBerry 10.0.0
         */
        None                    = 0x0,

        /*!
         * @brief Emergency calls supported.
         *
         * @since BlackBerry 10.0.0
         */
        Emergency               = 0x1,

        /*!
         * @brief Voice service supported.
         *
         * @since BlackBerry 10.0.0
         */
        Voice                   = 0x2,

        /*!
         * @brief After an emergency call, an operator can call the device back or determine
         * its approximate location.
         *
         * @since BlackBerry 10.0.0
         */
        E911Callback            = 0x4,

        /*!
         * @brief Data service supported.
         *
         * @since BlackBerry 10.0.0
         */
        Data                    = 0x100,

        /*!
         * @brief Connections can be handed off between a cellular network and an IP network.
         *
         * @since BlackBerry 10.0.0
         */
        GenericAccessNetwork    = 0x200,

        /*!
         * @brief Voice and data service can be used simultaneously.
         *
         * @since BlackBerry 10.0.0
         */
        ConcurrentVoiceData     = 0x400,

        /*!
         * @brief GPRS supported for data service.
         *
         * @since BlackBerry 10.0.0
         */
        DataGprs                = 0x1000,

        /*!
         * @brief EDGE supported for data service.
         *
         * @since BlackBerry 10.0.0
         */
        DataEdge                = 0x2000,

        /*!
         * @brief UMTS supported for data service.
         *
         * @since BlackBerry 10.0.0
         */
        DataUmts                = 0x4000,

        /*!
         * @brief HSPA supported for data service.
         *
         * @since BlackBerry 10.0.0
         */
        DataHspa                = 0x8000,

        /*!
         * @brief HSPA+ supported for data service.
         *
         * @since BlackBerry 10.0.0
         */
        DataHspaP               = 0x10000,

        /*!
         * @brief CDMA 1X supported for data service.
         *
         * @since BlackBerry 10.0.0
         */
        DataCdma                = 0x20000,

        /*!
         * @brief EV-DO Release 0 supported for data service.
         *
         * @since BlackBerry 10.0.0
         */
        DataEvdo0               = 0x40000,

        /*!
         * @brief EV-DO Revision A supported for data service.
         *
         * @since BlackBerry 10.0.0
         */
        DataEvdoA               = 0x80000,

        /*!
         * @brief eHRPD supported for data service.
         *
         * @since BlackBerry 10.0.0
         */
        DataEhrpd               = 0x100000,

        /*!
         * @brief LTE supported for data service.
         *
         * @since BlackBerry 10.0.0
         */
        DataLte                 = 0x200000
    };
    Q_DECLARE_FLAGS(Types, Type)

private:
//!@cond PRIVATE
    CellularService();
    ~CellularService();
//!@endcond
};

Q_DECLARE_OPERATORS_FOR_FLAGS(CellularService::Types)

} // namespace device
} // namespace bb

QML_DECLARE_TYPE(bb::device::CellularService)
#endif // BB_DEVICE_CELLULARSERVICE_HPP
