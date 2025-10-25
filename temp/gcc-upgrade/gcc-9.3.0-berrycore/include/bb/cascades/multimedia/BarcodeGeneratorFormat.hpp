/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CASCADES_MULTIMEDIA_BARCODEGENERATORFORMAT_HPP
#define BB_CASCADES_MULTIMEDIA_BARCODEGENERATORFORMAT_HPP

#include <bb/cascades/multimedia/Global>
#include <bb/cascades/multimedia/BarcodeFormat>

#include <QObject>

namespace bb
{
namespace cascades
{
namespace multimedia
{

/*!
 * @headerfile BarcodeGeneratorFormat.hpp <bb/cascades/multimedia/BarcodeGeneratorFormat>
 *
 * @brief The supported encoding formats for the @c BarcodeGenerator.
 *
 * @xmlonly
 * <apigrouping group="Multimedia/Barcodes"/>
 * <library name="bbcascadesmultimedia"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_CASCADES_MULTIMEDIA_EXPORT BarcodeGeneratorFormat
{
    Q_GADGET
    Q_ENUMS( Type )

public:
    /*!
     * @brief The supported encoding formats for the @c BarcodeGenerator.
     *
     * @since BlackBerry 10.2.0
     */
    enum Type
    {
        /*!
         * @brief QrCode format, with level M error correction.
         *
         * @details <a href="http://en.wikipedia.org/wiki/QR_code">QrCode definition at Wikipedia</a>
         *
         * @since BlackBerry 10.2.0
         */
        QrCode = 1,

        /*!
         * @brief PDF417 format, with 8 codewords for error correction.
         *
         * @details <a href="http://en.wikipedia.org/wiki/PDF417">PDF417 definition at Wikipedia</a>
         *
         * @since BlackBerry 10.2.0
         */
        Pdf417 = 2,

        /*!
         * @brief Aztec format.
         *
         * @details <a href="http://en.wikipedia.org/wiki/Aztec_Code">Aztec definition at Wikipedia</a>
         *
         * @since BlackBerry 10.2.0
         */
        Aztec = 3,

        /*!
         * @brief European Article Number format.
         *
         * @details <a href="http://en.wikipedia.org/wiki/European_Article_Number">EAN definition at Wikipedia</a>
         *
         * @since BlackBerry 10.2.0
         */
        Ean = 4,

        /*!
         * @brief UPC Version A format.
         *
         * @details <a href="http://en.wikipedia.org/wiki/Universal_Product_Code">UPC definition at Wikipedia</a>
         *
         * @since BlackBerry 10.2.0
         */
        UpcA = 5,

        /*!
         * @brief UPC Version E format.
         *
         * @details <a href="http://en.wikipedia.org/wiki/Universal_Product_Code">UPC definition at Wikipedia</a>
         *
         * @since BlackBerry 10.2.0
         */
        UpcE = 6,

        /*!
         * @brief ISBN 10 digit format.
         *
         * @details <a href="http://en.wikipedia.org/wiki/ISBN">ISBN definition at Wikipedia</a>
         *
         * @since BlackBerry 10.2.0
         */
        IsbnX = 7,

        /*!
         * @brief Codabar format.
         *
         * @details <a href="http://en.wikipedia.org/wiki/Codabar">Codabar definition at Wikipedia</a>
         *
         * @since BlackBerry 10.2.0
         */
        Codabar = 8,

        /*!
         * @brief Code128 format.
         *
         * @details <a href="http://en.wikipedia.org/wiki/Code128">Code128 definition at Wikipedia</a>
         *
         * @since BlackBerry 10.2.0
         */
        Code128 = 9,

        /*!
         * @brief DataMatrix format.
         *
         * @details <a href="http://en.wikipedia.org/wiki/DataMatrix">DataMatrix definition at Wikipedia</a>
         *
         * @since BlackBerry 10.2.0
         */
        DataMatrix = 10,

        /*!
         * @brief ITF-14 format.
         *
         * @details <a href="http://en.wikipedia.org/wiki/ITF-14">ITF-14 definition at Wikipedia</a>
         *
         * @since BlackBerry 10.2.0
         */
        Itf14 = 11,

        /*!
         * @brief Maxicode format.
         *
         * @details <a href="http://en.wikipedia.org/wiki/Maxicode">Maxicode definition at Wikipedia</a>
         *
         * @since BlackBerry 10.2.0
         */
        Maxicode = 12,

        /*!
         * @brief Code39 format.
         *
         * @details <a href="http://en.wikipedia.org/wiki/Code39">Code39 definition at Wikipedia</a>
         *
         * @since BlackBerry 10.2.0
         */
        Code39 = 13
    };

#ifndef Q_MOC_RUN
    /*!
     * @brief Finds the @c bb::cascades::multimedia::BarcodeGeneratorFormat that corresponds to the supplied
     * @c bb::cascades::multimedia::BarcodeFormat.
     *
     * @details @c bb::cascades::multimedia::BarcodeFormat::Any is non-specific, and a default of
     * @c bb::cascades::multimedia::BarcodeGeneratorFormat::QrCode is assumed.
     *
     * @param barcodeFormat The @c bb::cascades::multimedia::BarcodeFormat which will be matched.
     *
     * @return One of @c bb::cascades::multimedia::BarcodeGeneratorFormat::Type.
     *
     * @since BlackBerry 10.2.0
     */
    static Q_INVOKABLE bb::cascades::multimedia::BarcodeGeneratorFormat::Type fromBarcodeFormat( bb::cascades::multimedia::BarcodeFormat::Type barcodeFormat );
#else
    /*!
     * @cond PRIVATE
     * This conditional directive is set up to make it appear that the fromBarcodeFormat() method returning the enumerator is available from QML
     * which it normally is not.  Since an int and the enum are compatible with loose typing you can call this method from QML
     * and compare it to the enum and it works.
     * @endcond
     */
    static Q_INVOKABLE int fromBarcodeFormat( int barcodeFormat );
#endif

private:
//! @cond PRIVATE
    BarcodeGeneratorFormat();
    ~BarcodeGeneratorFormat();
//! @endcond
};

} // namespace multimedia
} // namespace cascades
} // namespace bb

#endif // BB_CASCADES_MULTIMEDIA_BARCODEGENERATORFORMAT_HPP
