/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CASCADES_MULTIMEDIA_BARCODEFORMAT_HPP
#define BB_CASCADES_MULTIMEDIA_BARCODEFORMAT_HPP

#include <bb/cascades/multimedia/Global>

#include <QObject>

namespace bb
{
namespace cascades
{
namespace multimedia
{

/*!
 * @headerfile BarcodeFormat.hpp <bb/cascades/multimedia/BarcodeFormat>
 *
 * @brief Represents formats that are supported by @c BarcodeDetector.
 *
 * Formats can be combined to allow @c %BarcodeDetector to search for multiple formats at the same time.
 * @c %BarcodeDetector can be configured to search for barcodes of any formats it supports using @c Any.
 *
 * @xmlonly
 * <apigrouping group="Multimedia/Barcodes"/>
 * <library name="bbcascadesmultimedia"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_CASCADES_MULTIMEDIA_EXPORT BarcodeFormat
{
    Q_GADGET
    Q_ENUMS( Type )
    Q_FLAGS( Types )

public:
    /*!
     * @brief Formats that are supported by @c BarcodeDetector.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
        /*! @brief Represents a QR code.
         *
         * @since BlackBerry 10.0.0
         */
        QrCode     = 0x1,

        /*! @brief Represents a data matrix.
         *
         * @since BlackBerry 10.0.0
         */
        DataMatrix = 0x2,

        /*! @brief Represents a UPC-E code.
         *
         * @since BlackBerry 10.0.0
         */
        UpcE       = 0x4,

        /*! @brief Represents a UPC-A code.
         *
         * @since BlackBerry 10.0.0
         */
        UpcA       = 0x8,

        /*! @brief Represents an EAN-8 code.
         *
         * @since BlackBerry 10.0.0
         */
        Ean8       = 0x10,

        /*! @brief Represents an EAN-13 code.
         *
         * @since BlackBerry 10.0.0
         */
        Ean13      = 0x20,

        /*! @brief Represents a Code 128 code.
         *
         * @since BlackBerry 10.0.0
         */
        Code128    = 0x40,

        /*! @brief Represents a Code 93 code.
         *
         * @since BlackBerry 10.0.0
         */
        Code39     = 0x80,

        /*! @brief Represents an ITF code.
         *
         * @since BlackBerry 10.0.0
         */
        Itf        = 0x100,

        /*! @brief Represents an Aztec format code.
         *
         * @since BlackBerry 10.0.0
         */
        Aztec      = 0x200,

        /*! @brief Allows @c BarcodeDetector to detect barcodes of any format that's known to it.
         *
         * @since BlackBerry 10.0.0
         */
        Any        = 0xffff
    };
    Q_DECLARE_FLAGS(Types, Type)

private:
//! @cond PRIVATE
    BarcodeFormat();
    ~BarcodeFormat();
//! @endcond
};

Q_DECLARE_OPERATORS_FOR_FLAGS(BarcodeFormat::Types)

} // namespace multimedia
} // namespace cascades
} // namespace bb

#endif // BB_CASCADES_MULTIMEDIA_BARCODEFORMAT_HPP
