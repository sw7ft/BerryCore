/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_CLIPBOARD_HPP
#define BB_SYSTEM_CLIPBOARD_HPP

#include <bb/system/Global>

#include <QObject>
#include <QScopedPointer>

namespace bb
{
namespace system
{
class ClipboardPrivate;

/*!
 * @headerfile Clipboard.hpp <bb/system/Clipboard>
 *
 * @brief Copy and paste data within an application or between applications.
 *
 * @details The @c Clipboard class lets you add or remove data from the clipboard that
 * is shared between applications on the device. This clipboard allows for copying and
 * pasting data in different locations within the same application, or between different
 * applications on the device.
 *
 * Data in the clipboard is referenced by type. Multiple types of data can exist in the
 * clipboard at the same time. Each type typically refers to a different encoding of the
 * same data. For example, an application copying data from an HTML source might insert both 
 * HTML markup and plain text into the clipboard. This increases the likelihood that
 * an application performing a paste operation will find data in the clipboard with a suitable 
 * encoding. For example, a rich document editor performing a paste operation might 
 * first look for HTML markup in the clipboard and fall back to plain text if no HTML 
 * markup is found, whereas a simple document editor might look for plain text data only.
 *
 * A type can be any non-empty string. For compatibility with other applications, using Internet 
 * media types (i.e., MIME types) is recommended. For example, "text/plain", "text/html", 
 * and "text/rtf" are three commonly-used encodings for textual data.
 *
 * The following example shows how to "paste" plain text data from the clipboard:
 *
 * @code
 * bb::system::Clipboard clipboard;
 * QByteArray data = clipboard.value("text/plain");
 * if (!data.isEmpty()) {
 *     // process data from clipboard
 * }
 * @endcode
 *
 * The following example shows how to "copy" html and plain text data to the clipboard:
 *
 * @code
 * bb::system::Clipboard clipboard;
 * clipboard.clear();
 * clipboard.insert("text/html", "<b>Hello world</b>");
 * clipboard.insert("text/plain", "Hello world");
 * @endcode
 *
 * @xmlonly
 * <apigrouping group="Platform/Utility"/>
 * <library name="bbsystem"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT Clipboard : public QObject
{
    Q_OBJECT
public:

    /*!
     * @brief Creates a new @c Clipboard object that manages data stored in the default, 
     * system-wide clipboard.
     *
     * @details All applications run within a particular security perimeter and the data they 
     * copy to the system clipboard is associated with that perimeter. Applications 
     * in the same perimeter can share data via the clipboard but may be blocked (due to 
     * a security policy) from accessing data in a different perimeter.
     *
     * @param parent If not 0, the supplied parent will be responsible for deleting this instance.
     *
     * @since BlackBerry 10.0.0
     */
    explicit Clipboard(QObject *parent = 0);
    
    /*!
     * @brief Creates a new @c Clipboard object that manages data stored in the specified 
     * directory.
     *
     * @details You can use a custom path to create a clipboard local to this application or a 
     * subset of applications. All users of the custom clipboard must have appropriate 
     * filesystem permissions to access the directory.
     *
     * @note All files in the specified directory are assumed to be owned by the 
     * clipboard. Calling @c clear() will delete every file in the directory.
     *
     * @param path A directory that stores data for a custom clipboard, or an empty path 
     *             to indicate the default, system-wide clipboard - see 
     *             @c Clipboard(QObject*) for more details.
     * @param parent If not 0, the supplied parent will be responsible for deleting this instance.
     *
     * @since BlackBerry 10.0.0
     */
    explicit Clipboard(const QString &path, QObject *parent = 0);

    /*!
     * @brief Destroys this @c Clipboard object.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~Clipboard();
    
    /*!
     * @brief Indicates whether the clipboard contains data for the specified type.
     *
     * @details Data may exist for the specified type in a different security perimeter. 
     * Furthermore, a security policy may block the caller from accessing this perimeter. 
     * If this occurs, @c false will be returned and @c restricted will be set to @c true.
     *
     * @param type The type of data requested from the clipboard.
     * @param restricted If not 0, @c restricted is an out parameter that is set to @c true if data exists 
     *                   but is not accessible to the caller, @c false otherwise.
     *
     * @return @c true if the data exists in the clipboard for the specified type and 
     *         is accessible to the caller, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool contains(const QString &type, bool *restricted = 0) const;

    /*!
     * @brief Retrieves data from the clipboard for the specified type.
     *
     * @details Data may exist for the specified type in a different security perimeter. 
     * Furthermore, a security policy may block the caller from accessing this perimeter. 
     * If this occurs, an empty byte array will be returned and @c restricted will be set 
     * to @c true.
     *
     * @param type The type of data requested from the clipboard.
     * @param restricted If not 0, @c restricted is an out parameter that is set to @c true if data exists 
     *                   but is not accessible to the caller, @c false otherwise.
     *
     * @return The raw clipboard data or an empty byte array if the type could not be 
     *         found, if the data is not accessible to the caller, or if an error occurred.
     *
     * @since BlackBerry 10.0.0
     */
    QByteArray value(const QString &type, bool *restricted = 0) const;

    /*!
     * @brief Adds new data to the clipboard for the specified type.
     
     * @details If data already exists for the type, the data is replaced. Data for other types 
     * is unaffected by this operation.
     *
     * @param type The type of data being added the clipboard.
     * @param data The raw data to put in the clipboard.
     *
     * @return @c true if the data was added to the clipboard successfully, @c false 
     *         otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool insert(const QString &type, const QByteArray &data);

    /*!
     * @brief Deletes data from the clipboard for the specified type.
     *
     * @param type The type of data to remove from the clipboard.
     *
     * @return @c true if the data was deleted from the clipboard successfully, @c false 
     *         otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool remove(const QString &type);
    
    /*!
     * @brief Deletes all data from the clipboard.
     *
     * @return @c true if all data was deleted from the clipboard successfully, @c false 
     *         otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool clear();

private:
//!@cond PRIVATE
    QScopedPointer<ClipboardPrivate> d_ptr;
    Q_DECLARE_PRIVATE(Clipboard)
    Q_DISABLE_COPY(Clipboard)
//!@endcond
};

} // namespace system
} // namespace bb

#endif // BB_SYSTEM_CLIPBOARD_HPP
