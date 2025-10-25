/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */


#ifndef BB_CASCADES_PICKERS_FILEPICKERMODE_HPP
#define BB_CASCADES_PICKERS_FILEPICKERMODE_HPP

#include <bb/cascades/pickers/Global>
#include <QObject>

namespace bb {
namespace cascades {
namespace pickers {

/*!
 * @headerfile FilePickerMode.hpp <bb/cascades/pickers/FilePickerMode>
 *
 * @brief Defines whether the FilePicker is used for picking single or multiple files or
 * selecting a destination for saving one or more files.
 *
 * By default, FilePicker will open in picker mode.
 *
 * @xmlonly
 * <apigrouping group="Data management/File picker"/>
 * <library name="bbcascadespickers"/>
 * <qml>
 *     <class register="enum-only"/>
 * </qml>
 * @endxmlonly
 *
 *
 * @since BlackBerry 10.0.0
 */
class BB_CASCADES_PICKERS_EXPORT FilePickerMode
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * The modes associated with FilePicker
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {

        /*!
         * @brief This mode allows the application to select a file for a specific task,
         * for example, attaching a file to an email or selecting a profile picture.
         *
         * @since BlackBerry 10.0.0
         */
        Picker = 0,
        /*!
         * @brief This mode allows the application to select a location for saving a file,
         * for example, saving an email attachment or saving a modified document.
         *
         * @since BlackBerry 10.0.0
         */
        Saver =1,

        /*!
         * @brief This mode allows the application to select multiple files for a specific task,
         * for example, attaching files to an email.
         *
         * @since BlackBerry 10.0.0
         */
        PickerMultiple = 2,

        /*!
         * @brief This mode allows the application to select a location to save multiple files.
         *
         *
         * @since BlackBerry 10.0.0
         */
        SaverMultiple = 3

    };

private:
//! @cond PRIVATE
    FilePickerMode();
    ~FilePickerMode();
//! @endcond PRIVATE
};

}  /* namespace pickers */
} /* namespace cascades*/
} /* namespace bb */


#endif /* BB_CASCADES_PICKERS_FILEPICKERMODE_HPP */
