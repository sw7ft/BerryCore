/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_ACCOUNT_SERVICE_HPP
#define BB_PIM_ACCOUNT_SERVICE_HPP

#include <bb/pim/Global>

namespace bb {
namespace pim {
namespace account {

/*!
 * @brief The @c Service class provides the possible values that can be used as
 * a parameter to an assortment of functions in the @c AccountService, @c Account,
 * and @c Provider classes.
 *
 * @details An account may support one or more services. By default, an account's
 * services are inherited from the provider that was used to create the account.
 * A supported service implies the account will continuously synchronize all
 * data for that service. Setting a supported service to false implies the account
 * will stop synchronizing all data for that service.
 *
 * @xmlonly
 * <apigrouping group="App Integration/Account"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT Service
{
public:

    /*!
     * @brief Enumerates all possible services.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        Calendars = 1,
        Contacts = 2,
        Notebook = 3,
        Geolocations = 4,
        Linking = 5,
        Memos = 6,
        Messages = 7,
        Tags = 8,
        Tasks = 9,
        Phone = 10
    };

private:
    Service();
    ~Service();
};

} // namespace account
} // namespace pim
} // namespace bb

#endif // BB_PIM_ACCOUNT_SERVICE_HPP
