/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CASCADES_PICKERS_FILETYPE_HPP
#define BB_CASCADES_PICKERS_FILETYPE_HPP

#include <bb/cascades/pickers/Global>
#include <QObject>
#include <QFlags>
#include <QtDeclarative>

namespace bb {
namespace cascades {
namespace pickers {

/*!
 *  @headerfile FileType.hpp <bb/cascades/pickers/FileType>
 *  @brief Defines the type of files that the user can select in FilePicker. 
 *
 * Multiple types can be combined by using the OR operator. If no FileType is
 * specified, FileType::Other will be used as the default.
 *
 *  FilePicker will filter the content based on the MIME type associated with these types.
 *
 * @xmlonly
 * <apigrouping group="Data management/File picker"/>
 * <library name="bbcascadespickers"/>
 *
 * <qml>
 *     <class register="enum-only"/>
 * </qml>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_CASCADES_PICKERS_EXPORT FileType
{
    Q_GADGET
    Q_FLAGS(Types)

public:
    /*!
     * @brief Types associated with FilePicker
     * @xmlonly
     *
     * <qml>
     *   <enum flagsType="bb::cascades::pickers::FileType::Types"/>
     * </qml>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {

        /*! @brief Pictures. Refers to files with MIME type images.
         *
         * @since BlackBerry 10.0.0
         */
        Picture = 0x1,

        /*! @brief Documents. Refers to a subset of files with MIME type application that are supported on the device.
         *
         * @since BlackBerry 10.0.0
         */
        Document = 0x2,

        /*! @brief Music. Refers to files with MIME type audio.
         *
         * @since BlackBerry 10.0.0
         */
        Music = 0x4,

        /*! @brief Videos. Refers to files with MIME type Video.
         *
         * @since BlackBerry 10.0.0
         */
        Video = 0x8,

        /*! @brief Refers to types other than the types listed above.
         *
         * @since BlackBerry 10.0.0
         */
        Other = 0x10

    };
    /*! @brief Using Qt's macro for type safe way to provide OR combination of enum values
     *
     * @since BlackBerry 10.0.0
     */
    Q_DECLARE_FLAGS(Types, Type);

private:
        FileType();
        ~FileType();
};

Q_DECLARE_OPERATORS_FOR_FLAGS(bb::cascades::pickers::FileType::Types);

}  /* namespace pickers */
} /* namespace cascades*/
} /* namespace bb */

#endif /* BB_CASCADES_PICKERS_FILETYPE_HPP_ */
