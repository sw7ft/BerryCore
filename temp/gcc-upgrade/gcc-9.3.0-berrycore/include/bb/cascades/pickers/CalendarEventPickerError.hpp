/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CASCADES_PICKERS_CALENDAREVENTPICKERERROR_HPP
#define BB_CASCADES_PICKERS_CALENDAREVENTPICKERERROR_HPP

#include <bb/cascades/pickers/Global>

#include <QObject>

namespace bb
{
namespace cascades
{
namespace pickers
{

/*!
 * @headerfile CalendarEventPickerError.hpp <bb/cascades/pickers/CalendarEventPickerError>
 *
 * @brief An error class for indicating failures when launching the calendar picker.
 *
 * @details
 *
 * The @c %CalendarEventPickerError class is used to determine why launching the @c %CalendarEventPicker
 * has failed during launch.
 *
 * @xmlonly
 * <apigrouping group="App Integration/Calendar"/>
 * <library name="bbcascadespickers"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_CASCADES_PICKERS_EXPORT CalendarEventPickerError
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    enum Type {
        /*!
         * @brief Success.
         *
         * @since BlackBerry 10.0.0
         */
        None                    = 0,

        /*!
         * @brief The picker  failed as a result of an internal error.
         *
         * @details Examples of internal errors include running out of memory or
         * entering an unexpected state.
         *
         * @since BlackBerry 10.0.0
         */
        Internal                = 1,

        /*!
         * @brief A request failed because the requesting entity lacks sufficient permissions.
         *
         * @since BlackBerry 10.0.0
         */
        InsufficientPermissions  = 2,

    };

private:
//!@cond PRIVATE
    CalendarEventPickerError();
    ~CalendarEventPickerError();
//!@endcond PRIVATE
};

} // namespace bb
} // namespace cascades
} // namespace pickers
#endif // BB_CASCADES_PICKERS_CALENDAREVENTPICKERERROR_HPP
