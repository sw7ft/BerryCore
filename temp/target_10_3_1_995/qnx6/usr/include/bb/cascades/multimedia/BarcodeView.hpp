/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CASCADES_MULTIMEDIA_BARCODEVIEW_HPP
#define BB_CASCADES_MULTIMEDIA_BARCODEVIEW_HPP

#include <bb/cascades/multimedia/Global>
#include <bb/cascades/CustomControl>
#include <bb/cascades/Container>
#include <bb/cascades/multimedia/BarcodeGeneratorError>
#include <bb/cascades/multimedia/BarcodeGeneratorFormat>

#include <QObject>
#include <QtDeclarative>
#include <QUrl>
#include <QScopedPointer>

namespace bb
{

namespace cascades
{
namespace multimedia
{

class BarcodeViewPrivate;

/*!
 * @headerfile BarcodeView.hpp <bb/cascades/multimedia/BarcodeView>
 *
 * @brief A visual control used to display barcodes.
 *
 * @details The barcode displayed in a @c BarcodeView is controlled by the specified barcode encoding format and the supplied data.
 *
 * @xmlonly
 * <apigrouping group="Multimedia/Barcodes"/>
 * <library name="bbcascadesmultimedia"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_CASCADES_MULTIMEDIA_EXPORT BarcodeView : public CustomControl
{
    Q_OBJECT

    /*!
     * @brief The barcode encoding format used to encode the supplied data.
     *
     * @details The default format is @c bb::cascades::multimedia::BarcodeGeneratorFormat::QrCode.
     * See @c bb::cascades::multimedia::BarcodeGeneratorFormat for more details.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( bb::cascades::multimedia::BarcodeGeneratorFormat::Type format READ format WRITE setFormat NOTIFY formatChanged FINAL )

    /*!
     * @brief The data encoded into the barcode.
     *
     * @details Not all data can be encoded in all barcode formats.  It is up to you to ensure the correct amount and type
     * of data is supplied for the encoding to succeed.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( QString data READ data WRITE setData NOTIFY dataChanged FINAL )

public:
    /*!
     * @brief Creates an instance of the @c %BarcodeView class.
     *
     * @param parent If not 0, ownership of the constructed object is transferred to the parent.
     *
     * @since BlackBerry 10.2.0
     */
    explicit BarcodeView(Container *parent = 0);

    /*!
     * @brief Destroys this @c %BarcodeView.
     *
     * @since BlackBerry 10.2.0
     */
    virtual ~BarcodeView();

    /*!
     * @brief The result of the last barcode generation attempt.
     *
     * @details The result of this call may change after updating the properties or changing the layout of the @c BarcodeView control.
     *
     * @returns One of @c bb::cascades::multimedia::BarcodeGeneratorError.
     *
     * @since BlackBerry 10.2.0
     */
#ifndef Q_MOC_RUN
    Q_INVOKABLE bb::cascades::multimedia::BarcodeGeneratorError::Type error() const;
#else
    /*!
     * @cond PRIVATE
     * This conditional directive is set up to make it appear that the error() method returning the enumerator is availble from QML
     * which it normally is not.  Since an int and the enum are compatible with loose typing you can call this method from QML
     * and compare it to the enum and it works.
     * @endcond
     */
    Q_INVOKABLE int error() const;
#endif

    /*!
     * @brief The barcode encoding format.
     *
     * @returns The barcode encoding format used to encode the data. See @c bb::cascades::multimedia::BarcodeGeneratorFormat for more details.
     *
     * @since BlackBerry 10.2.0
     */
    bb::cascades::multimedia::BarcodeGeneratorFormat::Type format() const;

    /*!
     * @brief Sets the barcode encoding format.
     *
     * @param format See @c bb::cascades::multimedia::BarcodeGeneratorFormat for more details.
     *
     * @since BlackBerry 10.2.0
     */
    void setFormat( bb::cascades::multimedia::BarcodeGeneratorFormat::Type format );

    /*!
     * @brief The barcode data.
     *
     * @returns The data encoded in the barcode.
     *
     * @since BlackBerry 10.2.0
     */
    QString data() const;

    /*!
     * @brief Sets the data to be encoded into the barcode.
     *
     * @details Not all data can be encoded in all barcode formats.  It is up to you to ensure the correct amount and type
     * of data is supplied for the encoding to succeed.
     *
     * @param data The data to encode.
     *
     * @since BlackBerry 10.2.0
     */
    void setData( const QString &data );

Q_SIGNALS:
    /*!
     * @brief Emitted when the encoding format for the barcode is changed.
     *
     * @param format See @c bb::cascades::multimedia::BarcodeGeneratorFormat for more details.
     *
     * @since BlackBerry 10.2.0
     */
    void formatChanged( bb::cascades::multimedia::BarcodeGeneratorFormat::Type format );

    /*!
     * @brief Emitted when the data being encoded in the barcode has changed.
     *
     * @param data The data that has been encoded in the barcode.
     *
     * @since BlackBerry 10.2.0
     */
    void dataChanged( const QString &data );

    /*!
     * @brief Emitted when the generation of the barcode is complete.
     *
     * @details See @c bb::cascades::BarcodeGeneratorError for more details.
     *
     * @param error The result of the last operation.
     *
     * @since BlackBerry 10.2.0
     */
    void finished( bb::cascades::multimedia::BarcodeGeneratorError::Type error );

protected:
//! @cond PRIVATE
    Q_SIGNAL void formatChanged( int format );

    Q_SIGNAL void finished( int error );
//! @endcond

private:
//! @cond PRIVATE
    Q_DISABLE_COPY(BarcodeView);
    Q_DECLARE_PRIVATE(BarcodeView);
    QScopedPointer<BarcodeViewPrivate> d_ptr;
//! @endcond
};

} // namespace multimedia
} // namespace cascades
} // namespace bb

QML_DECLARE_TYPE(bb::cascades::multimedia::BarcodeView);
#endif // BB_CASCADES_MULTIMEDIA_BARCODEVIEW_HPP
