/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CASCADES_PICKERS_FILEPICKERVIEWMODE_HPP
#define BB_CASCADES_PICKERS_FILEPICKERVIEWMODE_HPP

#include <bb/cascades/pickers/Global>
#include <QObject>

namespace bb {
namespace cascades {
namespace pickers {

/*!
 * @headerfile FilePickerViewMode.hpp <bb/cascades/pickers/FilePickerViewMode>
 * @brief Defines view modes in FilePicker. 
 *
 * If the view mode is not specified, FilePicker will choose the view mode based on
 * the FileType, for example, GridView for pictures and Videos and ListView for documents and music.
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
class BB_CASCADES_PICKERS_EXPORT FilePickerViewMode
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * ViewModes associated with FilePicker
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*! FilePicker will choose the view mode based on the type of files being displayed.
         *
         * @since BlackBerry 10.0.0
         */
        Default ,

        /*! Displays files and folders in a list.
         *
         * @since BlackBerry 10.0.0
         */
        ListView ,

        /*! Displays files and folders in a grid.
         *
         * @since BlackBerry 10.0.0
         */
        GridView
    };

private:

    FilePickerViewMode();
    ~FilePickerViewMode();
};

}  /* namespace pickers */
} /* namespace cascades*/
} /* namespace bb */

#endif /* BB_CASCADES_PICKERS_FILEPICKERVIEWMODE_HPP */
