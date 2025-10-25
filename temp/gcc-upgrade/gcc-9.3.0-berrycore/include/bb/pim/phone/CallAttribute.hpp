/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2014
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_PHONE_CALL_ATTRIBUTE_HPP
#define BB_PIM_PHONE_CALL_ATTRIBUTE_HPP

#include <bb/pim/Global>

namespace bb {
namespace pim {
namespace phone {

/*!
 * @brief An enumeration of @c CallEntry attributes for filtering purposes.
 *
 * @see CallHistoryFilter
 *
 * @xmlonly
 * <apigrouping group="App Integration/Phone"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.3.0
 */
class BB_PIM_EXPORT CallAttribute
{
public:
    enum Type {

        /*!
         * @brief Sort by CallEntry ID. This is the default value.
         *
         * @since BlackBerry 10.3.0
         */
        Id = 0,

        /*!
         * @brief Sort by Start Date
         *
         * @since BlackBerry 10.3.0
         */
        StartDate = 1,

        /*!
         * @brief Sort by caller name (name from the network).
         *
         * @since BlackBerry 10.3.0
         */
        Name = 2,

        /*!
         * @brief Sort by caller number.
         *
         * @since BlackBerry 10.3.0
         */
        Number = 3,

        /*!
         * @brief Sort by call type.
         *
         * @see CallType
         *
         * @since BlackBerry 10.3.0
         */
        CallType = 4,

        /*!
         * @brief Sort by Line.
         *
         * @since BlackBerry 10.3.0
         */
        Line = 5,
    };
};

} // namespace phone
} // namespace pim
} // namespace bb

#endif /* BB_PIM_PHONE_CALL_ATTRIBUTE_HPP */