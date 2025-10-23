/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_NFCSHAREDATACONTENT_HPP
#define BB_SYSTEM_NFCSHAREDATACONTENT_HPP

#include <bb/system/Global>

#include <QString>
#include <QUrl>
#include <QByteArray>
#include <QSharedDataPointer>

namespace bb
{
namespace system
{

class NfcShareDataRequestPrivate;

/*!
 * @headerfile NfcShareDataContent.hpp <bb/system/NfcShareDataContent>
 *
 * @brief Defines a request to share data over NFC.
 *
 * @details Clients specify the data they want to share by creating an instance of @c NfcShareDataContent,
 *          populating it with data, and passing the object to
 *          @c NfcShareManager::setShareContent(const NfcShareDataContent &).
 *
 *          A request must contain a valid combination of MIME type, data and URI fields. Rules that must
 *          be followed are:
 *          - If the data field is not empty, the MIME type of the data must be specified. The URI field will be ignored.
 *          - If the data field is empty, a valid URI must be provided.
 *          - The MIME type may be empty only if the data field is empty and a valid URI is provided. This can be used to share
 *            a link to a URL or remote file.
 *
 *          The following illustrates some of the most common data content specifications:
 *           1. URL:
 *                -      data: URL as plain text
 *                - MIME type: "text/URI-list"
 *                -       URI: empty
 *                .
 *                      -or-
 *                -      data: empty
 *                - MIME type: empty
 *                -       URI: URL using the correct URI scheme
 *           2. Phone number - A phone number is represented as a URI with a scheme of "tel:", and so appears as follows:
 *                -      data: telephone number URI as a string, with a scheme of "tel:" followed by the number
 *                - MIME type: "text/URI-list"
 *                -       URI: empty
 *                .
 *                      -or-
 *                -      data: empty
 *                - MIME type: empty
 *                -       URI: URL with a URI scheme of "tel:"
 *           3. Text:
 *                -      data: text in UTF-8 format
 *                - MIME type: "text/plain"
 *                -       URI: empty
 *           4. User-defined payload:
 *                -      data: user-specific data encoded as an array of bytes
 *                - MIME type: user-specific MIME type that can be recognized by the receiving application on the target device
 *                -       URI: empty
 *           5. AppWorld - AppWorld content is referenced as a URI with a scheme of "appworld://".  Use the URL and phone number
 *                         specifications above as a guide.
 *
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/NFC"/>
 * <library name="bbsystem"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */

class BB_SYSTEM_EXPORT NfcShareDataContent
{
public:
    /*!
     * @brief Creates a new @c NfcShareDataContent object.
     *
     * @since BlackBerry 10.0.0
     */
    NfcShareDataContent();

    /*!
     * @brief Creates a copy of an existing @c NfcShareDataContent object.
     *
     * @param other The source @c NfcShareDataContent object to copy.
     *
     * @since BlackBerry 10.0.0
     */
    NfcShareDataContent(const NfcShareDataContent &other);

    /*!
     * @brief Destroys this @c NfcShareDataContent object.
     *
     * @since BlackBerry 10.0.0
     */
    ~NfcShareDataContent();

    /*!
     * @brief Copies the data of an existing @c NfcShareDataContent object to this object.
     *
     * @param other The source @c NfcShareDataContent object to copy.
     *
     * @return The @c NfcShareDataContent instance.
     *
     * @since BlackBerry 10.0.0
     */
    NfcShareDataContent& operator=(const NfcShareDataContent &other);

    /*!
     * @brief Returns the MIME type of the data to be shared.
     *
     * @details The MIME type must be a valid Internet media type,
     * such as "image/png".
     *
     * Required: YES.
     *
     * @return Returns the MIME type of the data.
     *
     * @since BlackBerry 10.0.0
     */
    QString mimeType() const;

    /*!
     * @brief Sets the MIME type of the data sent to be shared.
     *
     * @details The MIME type must be a valid Internet media type,
     * such as "image/png".
     *
     * Required: YES.
     *
     * @param mimeType The MIME type of the data.
     *
     * @since BlackBerry 10.0.0
     */
    void setMimeType(const QString &mimeType);

    /*!
     * @brief Returns the binary data to be shared.
     *
     * @details Valid values depend on the MIME type specified by @c setMimeType(). If
     * omitted, the MIME type and URI must be sufficient for the sharing operation to proceed.
     *
     * Required: NO.
     *
     * @return Returns the binary data to be shared or an empty array if no data is to be shared.
     *
     * @since BlackBerry 10.0.0
     */
    QByteArray data() const;

    /*!
     * @brief Sets the binary data sent to be shared.
     *
     * @details Valid values depend on the MIME type specified by @c setMimeType(). If
     * omitted, the MIME type and URI must be sufficient for the sharing operation to proceed.
     *
     * Required: NO.
     *
     * @param data The binary data to be shared or an empty array if no data is to be shared.
     *
     * @since BlackBerry 10.0.0
     */
    void setData(const QByteArray &data);

    /*!
     * @brief Returns the uniform resource identifier (URI) of the data to be shared.
     *
     * @details If omitted, the MIME type and data must be sufficient for the sharing operation to proceed.
     *
     * Required: NO.
     *
     * @return Returns the uniform resource identifier (URI) to be shared or an empty URI if the
     *         no URI is required.
     *
     * @since BlackBerry 10.0.0
     */
    QUrl uri() const;

    /*!
     * @brief Sets the uniform resource identifier (URI) of the data to be shared.
     *
     * @details If omitted, the MIME type and data must be sufficient for the sharing operation to proceed.
     *
     * @details Required: NO.
     *
     * @param uri The uniform resource identifier (URI) to be shared or an empty URI if
     *            no URI is required.
     *
     * @since BlackBerry 10.0.0
     */
    void setUri(const QUrl &uri);

private:
//!@cond PRIVATE
    QSharedDataPointer<NfcShareDataRequestPrivate> d;
//!@endcond
};

} // namespace system
} // namespace bb

#endif /* BB_SYSTEM_NFCSHAREDATACONTENT_HPP */
