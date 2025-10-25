/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_DEVICE_CELLULARBAND_HPP
#define BB_DEVICE_CELLULARBAND_HPP

#include <bb/device/Global>
#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace device
{

/*!
 * @headerfile CellularBand.hpp <bb/device/CellularBand>
 *
 * @brief Frequency bands supported by a cellular radio or network.
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Radio and SIM"/>
 * <library name="bbdevice"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_DEVICE_EXPORT CellularBand
{
    Q_GADGET
    Q_ENUMS(Type)
    Q_FLAGS(Types)

public:
    /*!
     * @brief Frequency bands supported by a cellular radio or network.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief No bands supported.
         *
         * @since BlackBerry 10.0.0
         */
        None        = 0x0,

        /*!
         * @brief CDMA Band 0 (800 MHz).
         *
         * @since BlackBerry 10.0.0
         */
        Cdma0       = 0x1,

        /*!
         * @brief CDMA Band 1 (1900 MHz).
         *
         * @since BlackBerry 10.0.0
         */
        CdmaI       = 0x2,

        /*!
         * @brief CDMA Band 15 (1700/2100 MHz).
         *
         * @since BlackBerry 10.0.0
         */
        CdmaXV      = 0x4,

        /*!
         * @brief GSM-850 Band (850 MHz).
         *
         * @since BlackBerry 10.0.0
         */
        Gsm850      = 0x8,

        /*!
         * @brief GSM-900 Band (900 MHz).
         *
         * @since BlackBerry 10.0.0
         */
        Gsm900      = 0x10,

        /*!
         * @brief GSM-1800 Band (1800 MHz).
         *
         * @since BlackBerry 10.0.0
         */
        Gsm1800     = 0x20,

        /*!
         * @brief GSM-1900 Band (1900 MHz).
         *
         * @since BlackBerry 10.0.0
         */
        Gsm1900     = 0x40,

        /*!
         * @brief UMTS Band 1 (2100 MHz).
         *
         * @since BlackBerry 10.0.0
         */
        UmtsI       = 0x80,

        /*!
         * @brief UMTS Band 2 (1900 MHz).
         *
         * @since BlackBerry 10.0.0
         */
        UmtsII      = 0x100,

        /*!
         * @brief UMTS Band 3 (1800 MHz).
         *
         * @since BlackBerry 10.0.0
         */
        UmtsIII     = 0x200,

        /*!
         * @brief UMTS Band 4 (1700 MHz).
         *
         * @since BlackBerry 10.0.0
         */
        UmtsIV      = 0x400,

        /*!
         * @brief UMTS Band 5 (850 MHz).
         *
         * @since BlackBerry 10.0.0
         */
        UmtsV       = 0x800,

        /*!
         * @brief UMTS Band 6 (800 MHz).
         *
         * @since BlackBerry 10.0.0
         */
        UmtsVI      = 0x1000,

        /*!
         * @brief UMTS Band 7 (2600 MHz).
         *
         * @since BlackBerry 10.0.0
         */
        UmtsVII     = 0x2000,

        /*!
         * @brief UMTS Band 8 (900 MHz).
         *
         * @since BlackBerry 10.0.0
         */
        UmtsVIII    = 0x4000,

        /*!
         * @brief UMTS Band 9 (1700 MHz).
         *
         * @since BlackBerry 10.0.0
         */
        UmtsIX      = 0x8000,

        /*!
         * @brief UMTS Band 10 (1700 MHz).
         *
         * @since BlackBerry 10.0.0
         */
        UmtsX       = 0x10000,

        /*!
         * @brief LTE Band 2 (1900 MHz).
         *
         * @since BlackBerry 10.0.0
         */
        LteII       = 0x20000,

        /*!
         * @brief LTE Band 3 (1800 MHz).
         *
         * @since BlackBerry 10.0.0
         */
        LteIII      = 0x40000,

        /*!
         * @brief LTE Band 4 (1700/2100 MHz).
         *
         * @since BlackBerry 10.0.0
         */
        LteIV       = 0x80000,

        /*!
         * @brief LTE Band 5 (850 MHz).
         *
         * @since BlackBerry 10.0.0
         */
        LteV        = 0x100000,

        /*!
         * @brief LTE Band 7 (2600 MHz).
         *
         * @since BlackBerry 10.0.0
         */
        LteVII      = 0x200000,

        /*!
         * @brief LTE Band 8 (900 MHz).
         *
         * @since BlackBerry 10.0.0
         */
        LteVIII     = 0x400000,

        /*!
         * @brief LTE Band 13 (700 MHz).
         *
         * @since BlackBerry 10.0.0
         */
        LteXIII     = 0x800000,

        /*!
         * @brief LTE Band 17 (700 MHz).
         *
         * @since BlackBerry 10.0.0
         */
        LteXVII     = 0x1000000,

        /*!
         * @brief LTE Band 20 (800 MHz).
         *
         * @since BlackBerry 10.0.0
         */
        LteXX       = 0x2000000
    };
    Q_DECLARE_FLAGS(Types, Type)

private:
//!@cond PRIVATE
    CellularBand();
    ~CellularBand();
//!@endcond
};

Q_DECLARE_OPERATORS_FOR_FLAGS(CellularBand::Types)

} // namespace device
} // namespace bb

QML_DECLARE_TYPE(bb::device::CellularBand)
#endif // BB_DEVICE_CELLULARBAND_HPP
