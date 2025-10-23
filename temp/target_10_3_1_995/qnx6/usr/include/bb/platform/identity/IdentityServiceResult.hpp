/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_IDENTITY_IDENTITYSERVICERESULT_HPP
#define BB_PLATFORM_IDENTITY_IDENTITYSERVICERESULT_HPP

#include <bb/platform/Global>
#include <QtDeclarative/QtDeclarative>

namespace bb {
namespace platform {
namespace identity {

/*!
 * @headerfile IdentityServiceResult.hpp <bb/platform/identity/IdentityServiceResult>
 * @brief Contains enumerated return codes for synchronous responses to API calls.
 * @xmlonly
 * <library name="bbplatform" />
 * <apigrouping group="Platform/Identity" />
 * @endxmlonly
 */
class BB_PLATFORM_EXPORT IdentityServiceResult {
    Q_GADGET
    Q_ENUMS( Type )
public:
    enum Type {
        Success = 0, /*!< The call completed successfully.  In asynchronous calls, the request
         has been sent and either the success or failure callback is called
         when the response arrives. */

        UnableToCommunicateWithProvider = 70, /*!< Unable to communicate with the identity provider. */

        InvalidParameter = 22, /*!< An invalid parameter was passed to the function. */

        InsufficientMemory = 12, /*!< The system has insufficient memory to complete the operation. */

        MessageTooBig = 7, /*!< Message is too big to send to the identity provider. */

        InternalError = 49999/*!< Error code 49999 is the default error code, and indicates that
         an internal error occurred while processing the request. */
    };

private:
    //!@cond PRIVATE
    IdentityServiceResult();
    ~IdentityServiceResult();
    //!@endcond PRIVATE
};

} // namespace identity
} // namespace platform
} // namespace bb

QML_DECLARE_TYPE( bb::platform::identity::IdentityServiceResult )
#endif /* BB_PLATFORM_IDENTITY_IDENTITYSERVICERESULT_HPP */
