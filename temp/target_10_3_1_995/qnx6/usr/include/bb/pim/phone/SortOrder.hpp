/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2014
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_PHONE_SORT_ORDER_HPP
#define BB_PIM_PHONE_SORT_ORDER_HPP

#include <bb/pim/Global>

namespace bb {
namespace pim {
namespace phone {

/*!
 * @brief Sort order values.
 *
 * @xmlonly
 * <apigrouping group="App Integration/Phone"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.3.0
 */
class BB_PIM_EXPORT SortOrder
{
public:
    enum Type {
        /*!
         * @brief Indicates that results should be sorted in ascending order.
         *
         * @since BlackBerry 10.3.0
         */
        Ascending = 0,

        /*!
         * @brief Indicates that results should be sorted in descending order.
         *
         * @since BlackBerry 10.3.0
         */
        Descending = 1
    };
};

} // namespace phone
} // namespace pim
} // namespace bb

#endif /* BB_PIM_PHONE_SORT_ORDER_HPP */