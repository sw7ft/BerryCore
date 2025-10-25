/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_IDENTITY_BLACKBERRYIDASSURANCELEVEL_HPP
#define BB_PLATFORM_IDENTITY_BLACKBERRYIDASSURANCELEVEL_HPP

#include <bb/platform/Global>
#include <QtDeclarative/QtDeclarative>

namespace bb {
namespace platform {
namespace identity {

/*!
 * @headerfile BlackBerryIdAssuranceLevel.hpp <bb/platform/identity/BlackBerryIdAssuranceLevel>
 * @brief These are the levels of assurance returned by the challenge API
 * using BlackBerry ID as an identity provider.
 * @sa IdentityServiceProvider, IdentityServiceProvider::challenge(),
 * IdentityServiceProvider::challengeComplete()
 * @xmlonly
 * <library name="bbplatform" />
 * <apigrouping group="Platform/Identity" />
 * @endxmlonly
 */
class BB_PLATFORM_EXPORT BlackBerryIdAssuranceLevel {
    Q_GADGET
    Q_ENUMS( Type )
public:
    enum Type {
        AuthenticatedOffline = 0, /*!< BlackBerry ID level of assurance when authentication
         * was performed offline.
         * */

        AuthenticatedOnline = 1 /*!< BlackBerry ID level of assurance when authentication
         * was performed online.
         */
    };

private:
    //!@cond PRIVATE
    BlackBerryIdAssuranceLevel();
    ~BlackBerryIdAssuranceLevel();
    //!@endcond PRIVATE
};

} // namespace identity
} // namespace platform
} // namespace bb

QML_DECLARE_TYPE( bb::platform::identity::BlackBerryIdAssuranceLevel )

#endif /* BB_PLATFORM_IDENTITY_BLACKBERRYIDASSURANCELEVEL_HPP */
