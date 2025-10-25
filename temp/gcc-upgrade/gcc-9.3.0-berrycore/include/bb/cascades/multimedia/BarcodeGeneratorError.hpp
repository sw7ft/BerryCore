/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CASCADES_MULTIMEDIA_BARCODEGENERATORERROR_HPP
#define BB_CASCADES_MULTIMEDIA_BARCODEGENERATORERROR_HPP

#include <bb/cascades/multimedia/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace cascades
{
namespace multimedia
{

/*!
 * @headerfile BarcodeGeneratorError.hpp <bb/cascades/multimedia/BarcodeGeneratorError>
 *
 * @brief Lists the return codes for the @c BarcodeGenerator operations.
 *
 * @xmlonly
 * <apigrouping group="Multimedia/Barcodes"/>
 * <library name="bbcascadesmultimedia"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_CASCADES_MULTIMEDIA_EXPORT BarcodeGeneratorError
{
    Q_GADGET
    Q_ENUMS( Type )

public:
    /*!
     * @brief Lists the return codes for the @c BarcodeGenerator operations.
     *
     * @since BlackBerry 10.2.0
     */
    enum Type
    {
        /*! @brief No error occurred.
         *
         * @since BlackBerry 10.2.0
         */
        None     = 0,

        /*! @brief An unrecoverable internal error occurred.
         *
         * @since BlackBerry 10.2.0
         */
        Internal = 1,

        /*! @brief The supplied data is too long to encode.
         *
         * @since BlackBerry 10.2.0
         */
        DataTooLong = 2,

        /*! @brief The supplied data is invalid and can't be encoded.
         *
         * @details The supplied data contains characters that can't be encoded in the selected format.
         *
         * @since BlackBerry 10.2.0
         */
        InvalidData = 3,

        /*! @brief Could not write to the specified location.
         *
         * @details Commonly caused by file permission restrictions or setting
         * a path that does not exist.
         *
         * @since BlackBerry 10.2.0
         */
        FileAccess = 4,

        /*! @brief Incorrect check digit supplied for encoding.
         *
         * @since BlackBerry 10.2.0
         */
        InvalidCheckDigit = 5
    };

private:
//! @cond PRIVATE
    BarcodeGeneratorError();
    ~BarcodeGeneratorError();
//! @endcond
};

} // namespace multimedia
} // namespace cascades
} // namespace bb

QML_DECLARE_TYPE(bb::cascades::multimedia::BarcodeGeneratorError)

#endif // BB_CASCADES_MULTIMEDIA_BARCODEGENERATORERROR_HPP
