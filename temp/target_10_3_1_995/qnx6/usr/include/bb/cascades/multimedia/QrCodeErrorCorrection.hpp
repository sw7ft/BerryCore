/**
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CASCADES_MULTIMEDIA_QRCODEERRORCORRECTION_HPP
#define BB_CASCADES_MULTIMEDIA_QRCODEERRORCORRECTION_HPP

#include <bb/cascades/multimedia/Global>

#include <QObject>

namespace bb
{
namespace cascades
{
namespace multimedia
{

/*!
 * @headerfile QrCodeErrorCorrection.hpp <bb/cascades/multimedia/QrCodeErrorCorrection>
 *
 * @brief Provides error correction levels for QR codes, such as low, medium, and high.
 *
 * @details The values in this class indicate what level of error correction should be
 *          encoded into the QR code. A higher error correction means that the resultant
 *          QR code is more likely to be scannable even when damaged. These levels
 *          correspond to the L/M/Q/H levels defined in the QR code specification.
 *
 *          For more information, see http://en.wikipedia.org/wiki/QR_code.
 *
 * @xmlonly
 * <apigrouping group="Multimedia/Barcodes"/>
 * <library name="bbcascadesmultimedia"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_CASCADES_MULTIMEDIA_EXPORT QrCodeErrorCorrection
{
    Q_GADGET
    Q_ENUMS( Type )

public:
    /*!
     * @brief An enumeration of possible error correction levels.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
        /*!
         * @brief Indicates low error correction, in which approximately 7% of codewords
         *        can be restored.
         *
         * @since BlackBerry 10.0.0
         */
        Low = 1,

        /*!
         * @brief Indicates medium error correction, in which approximately 15% of codewords
         *        can be restored.
         *
         * @since BlackBerry 10.0.0
         */
        Medium = 2,

        /*!
         * @brief Indicates quality error correction, in which approximately 25% of codewords
         *        can be restored.
         *
         * @since BlackBerry 10.0.0
         */
        Quality = 3,

        /*!
         * @brief Indicates high error correction, in which approximately 30% of codewords
         *        can be restored.
         *
         * @since BlackBerry 10.0.0
         */
        High = 4
    };

private:
//! @cond PRIVATE
    QrCodeErrorCorrection();
    ~QrCodeErrorCorrection();
//! @endcond
};

} // namespace multimedia
} // namespace cascades
} // namespace bb

#endif // _HPP
