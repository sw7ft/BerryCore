/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_IDENTITY_IDENTITYSERVICELOGVERBOSITY_HPP
#define BB_PLATFORM_IDENTITY_IDENTITYSERVICELOGVERBOSITY_HPP

#include <bb/platform/Global>
#include <QtDeclarative/QtDeclarative>

namespace bb {
namespace platform {
namespace identity {

/*!
 * @headerfile IdentityServiceLogVerbosity.hpp <bb/platform/identity/IdentityServiceLogVerbosity>
 * @brief Logging verbosity
 * @details These options can be set using the @c IdentityService::setLogVebosity().
 * @xmlonly
 * <library name="bbplatform" />
 * <apigrouping group="Platform/Identity" />
 * @endxmlonly
 */
class BB_PLATFORM_EXPORT IdentityServiceLogVerbosity {
    Q_GADGET
    Q_ENUMS( Type )
public:
    enum Type {
        None = 0, /*!< With the logging verbosity set to "silent", logs will not be generated. */
        Normal = 1, /*!< "Normal" is the default verbosity, which generates errors and warnings. */
        Verbose = 2 /*!< The "verbose" logging level includes the "normal" level plus info
         logging to help debug application integration. */
    };

private:
    //!@cond PRIVATE
    IdentityServiceLogVerbosity();
    ~IdentityServiceLogVerbosity();
    //!@endcond PRIVATE
};

} // namespace identity
} // namespace platform
} // namespace bb

QML_DECLARE_TYPE( bb::platform::identity::IdentityServiceLogVerbosity )

#endif /* BB_PLATFORM_IDENTITY_IDENTITYSERVICELOGVERBOSITY_HPP */
