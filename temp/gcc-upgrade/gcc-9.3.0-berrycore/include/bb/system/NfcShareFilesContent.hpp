/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_NFCSHAREFILESCONTENT_HPP
#define BB_SYSTEM_NFCSHAREFILESCONTENT_HPP

#include <bb/system/Global>

#include <QUrl>
#include <QSharedDataPointer>

namespace bb
{
namespace system
{

class NfcShareFileRequestPrivate;

/*!
 * @headerfile NfcShareFilesContent.hpp <bb/system/NfcShareFilesContent>
 *
 * @brief Defines a request to share local files over NFC.
 *
 * @details Clients specify the files they wish to share by creating an instance of @c NfcShareFilesContent,
 *          populating it with local file paths in URI form, and passing the object to
 *          @c NfcShareManager::setShareContent(const NfcShareFilesContent &).
 *
 *          Note that a request must contain at least one file to be valid.
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/NFC"/>
 * <library name="bbsystem"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */

class BB_SYSTEM_EXPORT NfcShareFilesContent
{
public:
    /*!
     * @brief Creates a new @c NfcShareFilesContent object.
     *
     * @since BlackBerry 10.0.0
     */
    NfcShareFilesContent();

    /*!
     * @brief Creates a copy of an existing @c NfcShareFilesContent object.
     *
     * @param other The source @c NfcShareFilesContent object to copy.
     *
     * @since BlackBerry 10.0.0
     */
    NfcShareFilesContent(const NfcShareFilesContent &other);

    /*!
     * @brief Destroys this @c NfcShareFilesContent object.
     *
     * @since BlackBerry 10.0.0
     */
    ~NfcShareFilesContent();

    /*!
     * @brief Copies the data of an existing @c NfcShareFilesContent object to this object.
     *
     * @param other The source @c NfcShareFilesContent object to copy.
     *
     * @return Returns the @c NfcShareFilesContent instance.
     *
     * @since BlackBerry 10.0.0
     */
    NfcShareFilesContent& operator=(const NfcShareFilesContent &other);

    /*!
     * 
     * @brief Returns the list of local file paths to be shared using NFC.
     *
     * @details The paths are specified as URIs with a scheme of "file://" and a path to
     * a file on the local file system.
     *
     * Required: YES.
     *
     * @return Returns the list of files to be shared using NFC as a list of @c QUrl objects.
     *
     * @since BlackBerry 10.0.0
     */
    QList<QUrl> fileUrls() const;

    /*!
     * @brief Sets the list of local file paths to be shared using NFC.
     *
     * @details Local files are specified as URIs with a scheme of "file://" and a
     * path to a file on the local file system.
     *
     * To be valid, there must be at least one file in the list.
     *
     * Required: YES.
     *
     * @param urls A list of @c QUrl objects that reference local files.
     *
     * @since BlackBerry 10.0.0
     */
    void setFileUrls(const QList<QUrl> &urls);

private:
//!@cond PRIVATE
    QSharedDataPointer<NfcShareFileRequestPrivate> d;
//!@endcond
};
} // namespace system
} // namespace bb

#endif /* BB_SYSTEM_NFCSHAREFILESCONTENT_HPP */
