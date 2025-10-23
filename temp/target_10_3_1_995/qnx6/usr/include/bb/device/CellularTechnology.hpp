/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_DEVICE_CELLULARTECHNOLOGY_HPP
#define BB_DEVICE_CELLULARTECHNOLOGY_HPP

#include <bb/device/Global>
#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace device
{

/*!
 * @headerfile CellularTechnology.hpp <bb/device/CellularTechnology>
 *
 * @brief Communication standards supported by a cellular radio or network.
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Radio and SIM"/>
 * <library name="bbdevice"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_DEVICE_EXPORT CellularTechnology
{
    Q_GADGET
    Q_ENUMS(Type)
    Q_FLAGS(Types)

public:
    /*!
     * @brief Communication standards supported by a cellular radio or network.
     * @xmlonly
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief No technologies supported.
         *
         * @since BlackBerry 10.0.0
         */
        None    = 0x0,

        /*!
         * @brief Global system for mobile communications (GSM).
         *
         * @since BlackBerry 10.0.0
         */
        Gsm     = 0x1,

        /*!
         * @brief Universal mobile telecommunications system (UMTS).
         *
         * @since BlackBerry 10.0.0
         */
        Umts    = 0x2,

        /*!
         * @brief CDMA2000 1xRTT.
         *
         * @since BlackBerry 10.0.0
         */
        Cdma1X  = 0x4,

        /*!
         * @brief CDMA2000 1xEV-DO.
         *
         * @since BlackBerry 10.0.0
         */
        Evdo    = 0x8,

        /*!
         * @brief Long term evolution (LTE).
         *
         * @since BlackBerry 10.0.0
         */
        Lte     = 0x10
    };
    Q_DECLARE_FLAGS(Types, Type)

private:
//!@cond PRIVATE
    CellularTechnology();
    ~CellularTechnology();
//!@endcond
};

Q_DECLARE_OPERATORS_FOR_FLAGS(CellularTechnology::Types)

} // namespace device
} // namespace bb

QML_DECLARE_TYPE(bb::device::CellularTechnology)
#endif // BB_DEVICE_CELLULARTECHNOLOGY_HPP
