/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2014
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_PHONE_CALL_HISTORY_ERROR_HPP
#define BB_PIM_PHONE_CALL_HISTORY_ERROR_HPP

#include <bb/pim/Global>

namespace bb {
namespace pim {
namespace phone {

/*!
 * @brief Operation result values.
 *
 * @xmlonly
 * <apigrouping group="App Integration/Phone"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.3.0
 */
class BB_PIM_EXPORT CallHistoryError
{
public:
    enum Type {

        /*!
         * @brief No Error.
         *
         * @since BlackBerry 10.3.0
         */
        None = 0,

        /*!
         * @brief Operation failed.
         *
         * @since BlackBerry 10.3.0
         */
        Unknown = 1,

        /*!
         * @brief Requested data does not exist.
         *
         * @since BlackBerry 10.3.0
         */
        DoesNotExist = 2,

        // add more here...
    };
};

} // namespace phone
} // namespace pim
} // namespace bb

#endif /* BB_PIM_PHONE_CALL_HISTORY_ERROR_HPP */