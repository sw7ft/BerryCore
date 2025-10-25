/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */


#ifndef BB_CASCADES_PICKERS_FILEPICKERSORTFLAG_HPP
#define BB_CASCADES_PICKERS_FILEPICKERSORTFLAG_HPP

#include <bb/cascades/pickers/Global>
#include <QObject>

namespace bb {
namespace cascades {
namespace pickers {

/*!
 * @headerfile FilePickerSortFlag.hpp <bb/cascades/pickers/FilePickerSortFlag>
 * @brief Defines the attributes that the files can be sorted on in FilePicker. 
 *
 * By default, the files will be sorted based on type of files being displayed. 
 * For example, picture files will be sorted by date and documents will be sorted by name.
 *
 * @xmlonly
 * <apigrouping group="Data management/File picker"/> 
 * <library name="bbcascadespickers"/>
 * <qml>
 *     <class register="enum-only"/>
 * </qml>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_CASCADES_PICKERS_EXPORT FilePickerSortFlag
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * Various Sortflags associated with FilePicker
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*! FilePicker will choose the appropriate sort type based on the type of files being displayed.
         *
         * @since BlackBerry 10.0.0
         */
        Default,

        /*!  Sort by Name
         *
         * @since BlackBerry 10.0.0
         */
        Name ,

        /*!  Sort by modification date
         *
         * @since BlackBerry 10.0.0
         */
        Date ,

        /*!  Sort by file suffix
         *
         * @since BlackBerry 10.0.0
         */
        Suffix ,

        /*!  Sort by file size
         *
         * @since BlackBerry 10.0.0
         */
        Size
    };

private:
    FilePickerSortFlag();
    ~FilePickerSortFlag();
};

}  /* namespace pickers */
} /* namespace cascades*/
} /* namespace bb */

#endif /* BB_CASCADES_PICKERS_FILEPICKERSORTFLAG_HPP */
