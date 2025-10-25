/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CASCADES_PICKERS_FILEPICKERSOURCERESTRICTION_HPP_
#define BB_CASCADES_PICKERS_FILEPICKERSOURCERESTRICTION_HPP_

#include <bb/cascades/pickers/Global>
#include <QObject>

namespace bb {
namespace cascades {
namespace pickers {

/*!
 * @headerfile FilePickerSourceRestriction.hpp <bb/cascades/pickers/FilePickerSourceRestriction>
 * @brief Defines source restriction modes in FilePicker.
 *
 * If the restriction mode is not specified, FilePicker will default to restriction mode @c None.
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
 * @since BlackBerry 10.2.0
 */
class BB_CASCADES_PICKERS_EXPORT FilePickerSourceRestriction
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * SourceRestrictionModes associated with FilePicker
     *
     * @since BlackBerry 10.2.0
     */
    enum Type {
        /*! FilePicker will allow all sources to be displayed.
         *
         * @since BlackBerry 10.2.0
         */
        None ,

        /*! Displays specific source defined by path set in setDirectories().
         *  If path is not set nothing is displayed.
         *
         * @since BlackBerry 10.2.0
         */
        PathOnly ,

        /*! Displays local sources only.
         *
         * @since BlackBerry 10.2.0
         */
        LocalOnly,

        /*! Displays cloud sources only.
		 *
		 * @since BlackBerry 10.2.0
		 */
        CloudOnly
    };

private:

    FilePickerSourceRestriction();
    ~FilePickerSourceRestriction();
};

}  /* namespace pickers */
} /* namespace cascades*/
} /* namespace bb */



#endif /* BB_CASCADES_PICKERS_FILEPICKERSOURCERESTRICTION_HPP_ */
