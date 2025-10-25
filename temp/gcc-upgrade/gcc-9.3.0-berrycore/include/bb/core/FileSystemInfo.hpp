/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CORE_FILESYSTEMINFO_HPP
#define BB_CORE_FILESYSTEMINFO_HPP

#include <QObject>
#include <QString>

#include <bb/Global>
#include <QtDeclarative/QtDeclarative>

namespace bb
{

class FileSystemInfoPrivate;

/*!
 * @headerfile FileSystemInfo.hpp <bb/FileSystemInfo>
 *
 * @brief The @c %FileSystemInfo class provides information about the file system
 * on a device.
 *
 * @details Instances of this class provide the capacity and amount of free space
 * on the file system on a device.
 *
 * @xmlonly
 * <apigrouping group="Platform/Info"/>
 * <library name="bb"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_CORE_EXPORT FileSystemInfo : public QObject
{
    Q_OBJECT

public:
    /*!
     * @brief Creates a new @c FileSystemInfo object.
     *
     * Example usage in C++
     * @snippet libbb/FileSystemInfo_constructor.cpp All
     *
     * Example usage in QML
     * @snippet libbb/FileSystemInfo_constructor.qml All
     *
     * @param parent If not 0, the supplied parent will be responsible for deleting this instance.
     *
     * @since BlackBerry 10.0.0
     */
    explicit FileSystemInfo(QObject *parent = 0);
    /*!
     * @example libbb/FileSystemInfo_constructor.cpp
     * Example use in C++
     *
     * @example libbb/FileSystemInfo_constructor.qml
     * Example use in QML
     */

    /*!
     * @brief Destroys this @c FileSystemInfo object.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~FileSystemInfo();

    /*!
     * @brief Returns the POSIX error code for the last API call on this
     * object.
     *
     * Example usage in C++
     * @snippet libbb/FileSystemInfo_error.cpp All
     *
     * Example usage in QML
     * @snippet libbb/FileSystemInfo_error.qml All
     *
     * @return @c EOK if the last API call succeeded, the POSIX error code
     * for the failure ( from @c errno.h ) otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE int error() const;
    /*!
     * @example libbb/FileSystemInfo_error.cpp
     * Example use in C++
     *
     * @example libbb/FileSystemInfo_error.qml
     * Example use in QML
     */

    /*!
     * @brief Returns a human-readable description of the POSIX error code
     * returned by @c error().
     *
     * @details This is the value produced by @c strerror(), from @c string.h.
     *
     * Example usage in C++
     * @snippet libbb/FileSystemInfo_errorString.cpp All
     *
     * Example usage in QML
     * @snippet libbb/FileSystemInfo_errorString.qml All
     *
     * @return A string describing the POSIX error code from @c error().
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE QString errorString() const;
    /*!
     * @example libbb/FileSystemInfo_errorString.cpp
     * Example use in C++
     *
     * @example libbb/FileSystemInfo_errorString.qml
     * Example use in QML
     */

    /*!
     * @brief Returns the capacity of the file system for the provided
     * path in bytes.
     *
     * @details This method returns the user-accessible capacity of the
     * file system. The device may reserve a portion of the file system
     * for its own use. Where possible, this method corrects for this
     * reserved space and returns the amount of storage that is accessible
     * to an application.
     *
     * Example usage in C++
     * @snippet libbb/FileSystemInfo_fileSystemCapacity.cpp All
     *
     * Example usage in QML
     * @snippet libbb/FileSystemInfo_fileSystemCapacity.qml All
     *
     * @param path A path to any existing file or directory within the file
     * system being queried.
     *
     * @return The user-accessible capacity of the file system in bytes, or
     * -1 in the event of an error. On error, call @c error() to identify
     * the cause.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE qint64 fileSystemCapacity(const QString &path);
    /*!
     * @example libbb/FileSystemInfo_fileSystemCapacity.cpp
     * Example use in C++
     *
     * @example libbb/FileSystemInfo_fileSystemCapacity.qml
     * Example use in QML
     */

    /*!
     * @brief Returns the amount of free space available on the file system
     * for the provided path in bytes.
     *
     * @details This method returns the user-accessible free space of the file
     * system. The device may reserve a portion of the file system for its own
     * use. Where possible, this method corrects for this reserved space and
     * returns the amount of storage that is accessible to an application.
     *
     * Example usage in C++
     * @snippet libbb/FileSystemInfo_availableFileSystemSpace.cpp All
     *
     * Example usage in QML
     * @snippet libbb/FileSystemInfo_availableFileSystemSpace.qml All
     *
     * @param path A path to any existing file or directory within the file
     * system being queried.
     *
     * @return The user-accessible free space of the file system in bytes, or
     * -1 in the event of an error. On error, call @c error() to identify
     * the cause.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE qint64 availableFileSystemSpace(const QString &path);
    /*!
     * @example libbb/FileSystemInfo_availableFileSystemSpace.cpp
     * Example use in C++
     *
     * @example libbb/FileSystemInfo_availableFileSystemSpace.qml
     * Example use in QML
     */

    /*!
     * @brief Returns the maximum capacity of the main storage on the device, in bytes.
     *
     * @details This method returns the maximum capacity of the main storage on the
     * device in bytes.This value can be displayed to the user as the storage capacity
     * of the device (for example, 4. 8, or 16GB of storage) as a multiple of one Gig 1000*1000*1000.
     *
     * It does not correct for any reserved space for its own use
     * and returns the amount of main storage of which, not all
     * will be accessible to an application. The returned value should be used
     * for display purposes only. It does not reflect the actual space that can
     * be used on a device.
     *
     * Example usage in C++
     * @snippet libbb/FileSystemInfo_physicalCapacity.cpp All
     *
     * Example usage in QML
     * @snippet libbb/FileSystemInfo_physicalCapacity.qml All
     *
     *
     * @return The maximum capacity of the main storage on device in bytes, or
     * -1 in the event of an error. On error, call @c error() to identify
     * the cause.
     *
     * @since BlackBerry 10.3.0
     */
    Q_REVISION(1)
    Q_INVOKABLE qint64 physicalCapacity();
    /*!
     * @example libbb/FileSystemInfo_physicalCapacity.cpp
     * Example use in C++
     *
     * @example libbb/FileSystemInfo_physicalCapacity.qml
     * Example use in QML
     */

private:
//!@cond PRIVATE
    QScopedPointer<FileSystemInfoPrivate> d_ptr;
    Q_DECLARE_PRIVATE(FileSystemInfo);
    Q_DISABLE_COPY(FileSystemInfo)
//!@endcond

};

} // namespace bb

QML_DECLARE_TYPE(bb::FileSystemInfo)
#endif // BB_CORE_FILESYSTEMINFO_HPP
