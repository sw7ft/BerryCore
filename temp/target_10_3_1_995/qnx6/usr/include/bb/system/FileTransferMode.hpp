/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_FILETRANSFERMODE_HPP
#define BB_SYSTEM_FILETRANSFERMODE_HPP

#include <bb/system/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace system
{

/*!
 * @headerfile FileTransferMode.hpp <bb/system/FileTransferMode>
 *
 * @brief The types of transfer that can be applied to a file during invocation.
 *
 * @details When an invocation is sent containing a URI with a scheme of @c "file://"
 * and with a path that references a file that is not in the shared area, a file
 * transfer mode may be applied to transfer the file to the target's private inbox.
 * This enumeration allows the sender to control how and if the private transfer is
 * performed. Using this enumeration the sender can skip the private transfer,
 * transfer by copy as a readable file, as a readable and writable file, or as a
 * hard link to the original file.
 *
 * @xmlonly
 * <apigrouping group="App Integration/Invocation framework"/>
 * <library name="bbsystem"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT FileTransferMode
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief The types of transfer that can be applied to a file during invocation.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {

        /*!
         * @brief Use the default behavior specified by the invoke service.
         *
         * @since BlackBerry 10.0.0
         */
        Unspecified     = 0,

        /*!
         * @brief Skip file transfer handling and deliver the file as-is.
         *
         * @since BlackBerry 10.0.0
         */
        Preserve        = 1,

        /*!
         * @brief Create a read only copy of the file in the target's private inbox.
         *
         * @since BlackBerry 10.0.0
         */
        CopyReadOnly    = 2,

        /*!
         * @brief Create a read/write copy of the file in the target's private inbox.
         *
         * @since BlackBerry 10.0.0
         */
        CopyReadWrite   = 3,

        /*!
         * @brief Create a hard link to the file in the target's private inbox.
         *
         * @details When a hard link is specified, the permissions on the file must allow other
         * users to read it (i.e., in UNIX-style file permissions, o+r). In addition, if
         * the file permissions allow other users to both read and write (i.e., in
         * UNIX-style file permissions, o+rw), then the sender must have write access to
         * the file.
         *
         * @since BlackBerry 10.0.0
         */
        Link            = 4
    };

private:
//!@cond PRIVATE
    FileTransferMode();
    ~FileTransferMode();
//!@endcond
};

} // namespace system
} // namespace bb

QML_DECLARE_TYPE(bb::system::FileTransferMode)
#endif /* BB_SYSTEM_FILETRANSFERMODE_HPP */
