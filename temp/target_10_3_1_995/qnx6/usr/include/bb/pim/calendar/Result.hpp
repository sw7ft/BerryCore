
/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_CALENDAR_RESULT_HPP
#define BB_PIM_CALENDAR_RESULT_HPP

#include <bb/pim/Global>

namespace bb {
namespace pim {
namespace calendar {

/*!
 * @brief The @c Result class includes possible result codes for calendar operations.
 *
 * @details When you call certain functions in the @c CalendarService class, some of
 * these functions include a result code. This code indicates whether the function
 * completed successfully or whether an error was generated.
 * 
 * @see CalendarService
 * 
 * @xmlonly
 * <apigrouping group="App Integration/Calendar"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT Result {
public:
    /*!
     * @brief An enumeration of possible result codes for calendar operations.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief Indicates that the function completed successfully.
         *
         * @since BlackBerry 10.0.0
         */
        Success = 0,
        /*!
         * @brief Indicates that a database error occurred and the function did not
         * complete successfully.
         *
         * @since BlackBerry 10.0.0
         */
        BackEndError = 1,
        /*!
         * @brief Return code for problems with PPS decoders.
         *
         * @since BlackBerry 10.3.0
         */
        PPSDecoderFailure = 2,
        /*!
         * @brief Return code for invalid arguments.
         *
         * @since BlackBerry 10.3.0
         */
        InvalidArguments = 3,
    };

private:
    Result();
    ~Result();
};

} // namespace calendar
} // namespace pim
} // namespace bb

#endif // BB_PIM_CALENDAR_RESULT_HPP
