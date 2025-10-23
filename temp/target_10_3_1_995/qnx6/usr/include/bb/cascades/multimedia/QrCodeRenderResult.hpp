/**
 * @copyright
 * Copyright Research In Motion Limited, 2013-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CASCADES_MULTIMEDIA_QRCODERENDERRESULT_HPP
#define BB_CASCADES_MULTIMEDIA_QRCODERENDERRESULT_HPP

#include <bb/cascades/multimedia/Global>

#include <QObject>

namespace bb
{
namespace cascades
{
namespace multimedia
{

/*!
 * @headerfile QrCodeRenderResult.hpp <bb/cascades/multimedia/QrCodeRenderResult>
 *
 * @brief Provides result codes for QrCodeView rendering.
 *
 * @xmlonly
 * <apigrouping group="Multimedia/Barcodes"/>
 * <library name="bbcascadesmultimedia"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_CASCADES_MULTIMEDIA_EXPORT QrCodeRenderResult
{
    Q_GADGET
    Q_ENUMS( Type )

public:
    /*!
     * @brief An enumeration of possible QR Code render results.
     *
     * @since BlackBerry 10.2.0
     */
    enum Type
    {
        /*!
         * @brief Indicates that the operation was successful.
         *
         * @since BlackBerry 10.2.0
         */
        Success = 0,

        /*!
         * @brief Indicates that an internal, unspecified error occurred.
         *
         * @since BlackBerry 10.2.0
         */
        InternalError = 1,

        /*!
         * @brief Indicates that the QrCodeView::data() was empty.
         *
         * @since BlackBerry 10.2.0
         */
        DataEmpty = 2,

        /*!
         * @brief Indicates that the QrCodeView::data() was too large to generate a QR code.
         *
         * @since BlackBerry 10.2.0
         */
        DataTooLarge = 3,

        /*!
         * @brief Indicates that the width or height was too small.
         *
         * @details The width or height of the control was 0 or negative, or too small to hold the QR code.
         *
         * @since BlackBerry 10.2.0
         */
        OutputAreaTooSmall = 4,

        /*!
         * @brief Indicates that there was not enough memory to complete the operation.
         *
         * @since BlackBerry 10.2.0
         */
        InsufficientMemory = 5,
    };

private:
//! @cond PRIVATE
    QrCodeRenderResult();
    ~QrCodeRenderResult();
//! @endcond
};

} // namespace multimedia
} // namespace cascades
} // namespace bb

#endif // _HPP
