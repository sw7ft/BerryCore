/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef FILEPICKERERROR_HPP_
#define FILEPICKERERROR_HPP_
#include <bb/cascades/pickers/Global>

#include <QObject>

namespace bb
{
namespace cascades
{
namespace pickers
{

/*!
 * @headerfile FilePickerError.hpp <bb/cascades/pickers/FilePickerError>
 *
 * @brief An error class for indicating failures from the file picker.
 *
 * @details
 *
 * The @c %FilePickerError class is used to determine why the @c %FilePicker
 * has failed.
 *
 * @xmlonly
 * <apigrouping group="Data Management/File picker"/>
 * <library name="bbcascadespickers"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_CASCADES_PICKERS_EXPORT FilePickerError
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    enum Type {
        /*!
         * @brief Success.
         *
         * @since BlackBerry 10.2.0
         */
        None                    = 0,

        /*!
         * @brief The picker  failed as a result of an internal error.
         *
         * @details Examples of internal errors include running out of memory or
         * entering an unexpected state.
         *
         * @since BlackBerry 10.2.0
         */
        Internal                = 1,

        /*!
         * @brief A request to open FilePicker failed because the path is empty for PathOnly source restriction.
         *
         * @since BlackBerry 10.2.0
         */
        PathOnlyRestrictionRequiresPath  = 2,

        /*!
         * @brief A request to open FilePicker failed because there is no available source.
         *
         * @since BlackBerry 10.2.0
         */
        SourceUnavailable  = 3,

    };

private:
//!@cond PRIVATE
    FilePickerError();
    ~FilePickerError();
//!@endcond PRIVATE
};

} // namespace bb
} // namespace cascades
} // namespace pickers



#endif /* FILEPICKERERROR_HPP_ */
