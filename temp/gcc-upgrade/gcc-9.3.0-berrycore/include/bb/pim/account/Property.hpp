/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_ACCOUNT_PROPERTY_HPP
#define BB_PIM_ACCOUNT_PROPERTY_HPP

#include <bb/pim/Global>

namespace bb {
namespace pim {
namespace account {

/*!
 * @brief The @c Property class provides the possible values that can be used to
 * describe individual data elements found within @c Account and @c Provider
 * objects.
 *
 * @xmlonly
 * <apigrouping group="App Integration/Account"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT Property
{
public:
    /*!
     * @brief Enumerates all possible properties for fields in the
     * @c settings and @c capabilities maps of @c Provider and @c Account
     * objects.
     *
     * @since BlackBerry 10.0.0
     */
    enum Field {
        Choices = 1,
        Immutable = 2,
        Private = 3,
        Required = 4,
        Type = 5,
        Value = 6,
        Credential = 7
    };

    /*!
     * @brief Enumerates all possible enterprise types. See the
     * @c Provider::isEnterprise() and Account::isEnterprise() functions for
     * more details.
     *
     * @since BlackBerry 10.0.0
     */
    enum EnterpriseType {
        EnterpriseUnknown = -1,
        NonEnterprise = 0,
        Enterprise = 1
    };

private:
    Property();
    ~Property();
};

} // namespace account
} // namespace pim
} // namespace bb

#endif // BB_PIM_ACCOUNT_PROPERTY_HPP
