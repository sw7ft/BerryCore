/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_NOTEBOOK_NOTEBOOKENTRYATTACHMENT_HPP
#define BB_PIM_NOTEBOOK_NOTEBOOKENTRYATTACHMENT_HPP

#include <bb/pim/Global>

#include <bb/pim/account/Account>

#include <QSharedDataPointer>
#include <QString>

namespace bb
{
namespace pim
{
namespace notebook
{

class NotebookEntryAttachmentPrivate;

/*!
 * @headerfile NotebookEntryAttachment.hpp <bb/pim/notebook/NotebookEntryAttachment>
 *
 * @brief The @c NotebookEntryAttachment class represents an attachment to a @c NotebookEntry.
 *
 * @details Notebook entry attachments augment the @c Notebook experience by allowing media such as voice
 * notes and images to be added to notebook entries.  Attachments are specified by a MIME type, an account
 * key, and a data ID.  The account key and data ID should contain enough information to uniquely identify
 * and retrieve the media item on the system.
 *
 * The Remember application natively supports a small set of MIME types for @c %NotebookEntryAttachment objects,
 * as documented below, and will ignore attachments whose MIME types it does not recognize.  However, you
 * can create arbitrary @c %NotebookEntryAttachment objects to be used in your own applications.  In the future,
 * this API may be extended to allow arbitrary MIME types to be registered for use within the Remember application.
 *
 * The following MIME types are currently supported:
 *
 * <b>Media files:</b>
 * - audio/aac
 * - audio/amr
 * - audio/mp4
 * - audio/qcp
 * - audio/basic
 * - audio/ogg
 * - audio/x-aiff
 * - audio/x-midi
 * - audio/x-mpeg
 * - audio/x-mpegurl
 * - audio/x-scpls
 * - audio/x-wav
 * - image/bmp
 * - image/cgm
 * - image/gif
 * - image/ief
 * - image/jpeg
 * - image/pict
 * - image/png
 * - image/svg+xml
 * - image/tiff
 * - image/vnd.djvu
 * - image/x-cmu-raster
 * - image/x-icon
 * - image/x-jg
 * - image/x-macpaint
 * - image/x-photoshop
 * - image/x-portable-anymap
 * - image/x-portable-bitmap
 * - image/x-portable-graymap
 * - image/x-portable-pixmap
 * - image/x-quicktime
 * - image/x-rgb
 * - image/x-xbitmap
 * - image/x-xpixmap
 * - image/x-xwindowdump
 * - video/3gpp
 * - video/3gpp2
 * - video/h264
 * - video/MP2T
 * - video/mp4
 * - video/mpeg
 * - video/mpeg2
 * - video/quicktime
 * - video/vnd.mpegurl
 * - video/x-dv
 * - video/x-m4v
 * - video/x-matroska
 * - video/x-matroska-3d
 * - video/x-ms-asf
 * - video/x-ms-wma
 * - video/x-ms-wmv
 * - video/x-msvideo
 * - video/x-rad-screenplay
 * - video/x-sgi-movie
 *
 * <b>Documents:</b>
 * - application/pdf
 * - application/msword
 * - application/vnd.ms-excel
 * - application/vnd.ms-excel.sheet.macroEnabled.12
 * - application/vnd.ms-excel.template.macroEnabled.12
 * - application/vnd.ms-powerpoint
 * - application/vnd.ms-powerpoint.presentation.macroEnabled.12
 * - application/vnd.ms-powerpoint.slideshow.macroEnabled.12
 * - application/vnd.ms-powerpoint.template.macroEnabled.12
 * - application/vnd.ms-word.document.macroEnabled.12
 * - application/vnd.ms-word.template.macroEnabled.12
 * - application/vnd.openxmlformats-officedocument.presentationml.presentation
 * - application/vnd.openxmlformats-officedocument.presentationml.slideshow
 * - application/vnd.openxmlformats-officedocument.presentationml.template
 * - application/vnd.openxmlformats-officedocument.spreadsheetml.sheet
 * - application/vnd.openxmlformats-officedocument.spreadsheetml.template
 * - application/vnd.openxmlformats-officedocument.wordprocessingml.document
 * - application/vnd.openxmlformats-officedocument.wordprocessingml.template
 *
 * <b>Zip files:</b>
 * - application/zip
 *
 * <b>Text:</b>
 * - text/plain
 *
 * <b>Contact cards:</b>
 * - text/vcard
 *
 * <b>Calendar events:</b>
 * - text/calendar
 *
 * <b>Security certificates:</b>
 * - application/x-x509-ca-cert
 *
 * For these MIME types, the @c dataId represents the URL to access the raw file from the file system.
 *
 * <b>PIM data:</b>
 * - message/rfc822
 *
 * For this MIME type, the @c dataId is a uib URL.
 *
 * Example usage:
 * @code
 *   // Here's how to create a NotebookEntryAttachment representing a JPEG image.
 *   NotebookEntryAttachment attachment;
 *   attachment.setMimeType( "image/jpeg" );
 *   attachment.setDataId( "file:///path/to/image" );
 * @endcode
 *
 * @see Notebook, NotebookEntry
 *
 * @xmlonly
 * <apigrouping group="App Integration/Notebook"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT NotebookEntryAttachment
{

public:
    /*!
     * @brief Constructs a new @c NotebookEntryAttachment with default values.
     *
     * @since BlackBerry 10.0.0
     */
    NotebookEntryAttachment();

    /*!
     * @brief Copy constructor.
     *
     * @details This function constructs a @c NotebookEntryAttachment containing exactly the same values as the
     * provided @c %NotebookEntryAttachment.
     *
     * @param other The @c %NotebookEntryAttachment to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    NotebookEntryAttachment(const NotebookEntryAttachment &other);

    /*!
     * @brief Destroys this @c NotebookEntryAttachment.
     *
     * @since BlackBerry 10.0.0
     */
    ~NotebookEntryAttachment();

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c NotebookEntryAttachment into this
     * @c %NotebookEntryAttachment.
     *
     * @param other The @c %NotebookEntryAttachment from which to copy all values.
     *
     * @return A reference to this @c %NotebookEntryAttachment.
     *
     * @since BlackBerry 10.0.0
     */
    NotebookEntryAttachment& operator=(const NotebookEntryAttachment &other);

    /*!
     * @brief Equality operator.
     *
     * @details This operator returns @c true if the MIME type, account key, and data ID of the provided
     * @c NotebookEntryAttachment are equal to those of this @c %NotebookEntryAttachment, and returns
     * @c false otherwise.  The @c QString objects that represent the MIME type and data ID are compared
     * using the @c QString::compare() function.
     *
     * @param other The @c %NotebookEntryAttachment to check for equality.
     *
     * @return @c true if the provided @c %NotebookEntryAttachment is equal to this one, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool operator==(const NotebookEntryAttachment &other) const;

    /*!
     * @brief Inequality operator.
     *
     * @details This operator returns @c true if the MIME type, account key, or data ID of the provided
     * @c NotebookEntryAttachment are different from those of this @c %NotebookEntryAttachment, and returns
     * @c false otherwise.  The @c QString objects that represent the MIME type and data ID are compared
     * using the @c QString::compare() function.
     *
     * @param other The @c %NotebookEntryAttachment to check for inequality.
     *
     * @return @c true if the provided @c %NotebookEntryAttachment is not equal to this one, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool operator!=(const NotebookEntryAttachment &other) const;

    /*!
     * @brief Sets the MIME type for this @c NotebookEntryAttachment.
     *
     * @param mimeType The MIME type for this @c %NotebookEntryAttachment.
     *
     * @since BlackBerry 10.0.0
     */
    void setMimeType(const QString &mimeType);

    /*!
     * @brief Retrieves the MIME type of this @c NotebookEntryAttachment.
     *
     * @return The MIME type of this @c %NotebookEntryAttachment.
     *
     * @since BlackBerry 10.0.0
     */
    QString mimeType() const;

    /*!
     * @brief Sets the data ID for this @c NotebookEntryAttachment.
     *
     * @param dataId The data ID for this @c %NotebookEntryAttachment.
     *
     * @since BlackBerry 10.0.0
     */
    void setDataId(const QUrl &dataId);

    /*!
     * @brief Retrieves the data ID of this @c NotebookEntryAttachment.
     *
     * @return The data ID of this @c %NotebookEntryAttachment.
     *
     * @since BlackBerry 10.0.0
     */
    QUrl dataId() const;

private:
    QSharedDataPointer<NotebookEntryAttachmentPrivate> d_ptr;
};

} // namespace notebook
} // namespace pim
} // namespace bb

Q_DECLARE_METATYPE(bb::pim::notebook::NotebookEntryAttachment)

#endif /* BB_PIM_NOTEBOOK_NOTEBOOKENTRYATTACHMENT_HPP */
