/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */


#ifndef BB_CASCADES_PICKERS_FILEPICKERSORTORDER_HPP
#define BB_CASCADES_PICKERS_FILEPICKERSORTORDER_HPP

#include <bb/cascades/pickers/Global>
#include <QObject>

namespace bb {
namespace cascades {
namespace pickers {
/*!
 * @headerfile  FilePickerSortOrder.hpp <bb/cascades/pickers/FilePickerSortOrder>
 * @brief Defines the possible sort order. 
 * 
 * By default, FilePicker will choose the sort order based on the type of files being
 * displayed. For example, picture files are sorted in ascending order.
 *
 * @xmlonly
 * <apigrouping group="Data management/File picker"/>
 * <library name="bbcascadespickers"/>
 * <qml>
 *    <class register="enum-only"/>
 * </qml>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_CASCADES_PICKERS_EXPORT FilePickerSortOrder
{
    Q_GADGET
    Q_ENUMS(Type)
public:
    /*!
     * Sort order for the FilePicker
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*! FilePicker will choose the sort order based on the type of files being displayed
         *
         * @since BlackBerry 10.0.0
         */
        Default ,
        /*! Content will be sorted in ascending order
         *
         * @since BlackBerry 10.0.0
         */
        Ascending ,
        /*! Content will be sorted in descending order
         *
         * @since BlackBerry 10.0.0
         */
        Descending
    };
private:
    FilePickerSortOrder();
    ~FilePickerSortOrder();
};

}  /* namepsace pickers */
} /* namespace cascades*/
} /* namespace bb */

#endif /* BB_CASCADES_PICKERS_FILEPICKERSORTORDER_HPP */
