/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_IDENTITY_IDENTITYSERVICEPROPERTYRESULT_HPP
#define BB_PLATFORM_IDENTITY_IDENTITYSERVICEPROPERTYRESULT_HPP

#include <bb/platform/Global>
#include <QtDeclarative/QtDeclarative>

namespace bb {
namespace platform {
namespace identity {

/*!
 * @headerfile IdentityServicePropertyResult.hpp <bb/platform/identity/IdentityServicePropertyResult>
 * @brief Contains enumerated return codes for asynchronous responses to API calls related to properties.
 * @xmlonly
 * <library name="bbplatform" />
 * <apigrouping group="Platform/Identity" />
 * @endxmlonly
 */
class BB_PLATFORM_EXPORT IdentityServicePropertyResult {
    Q_GADGET
    Q_ENUMS( Type )
public:
    enum Type {
        Success = 0, /*!< The call completed successfully.  In asynchronous calls, the request
         has been sent and either the success or failure callback is called
         when the resposne arrives. */

        InternalError = 49999, /*!< Error code 49999 is the default error code, and indicates that
         an internal error occurred while processing the request. */

        // BlackBerry ID library basic error codes (reserved range : 50000 - 50099)
        NameTooLong = 50002, /*!< The name provided is too long.  The maximum number of allowed
         characters is determined by the identity provider.  */

        AccountLocallyLockedOut = 50003, /*!< User authentication could not complete because the
         user account is locked. */

        UserCouldNotBeAuthenticated = 50004, /*!< The identity provider could not authenticate the
         user.  There are a variety of possible causes
         for this error, including technical reasons, the
         user canceled the authentication request, and
         failure to meet other conditions that the identity
         provider requires. */

        TooManyNamesPassed = 50005, /*!< The number of entries provided exceeds what the identity provider
         can handle. */

        InvalidRequest = 50006, /*!< The request is is malformed or not supported. */

        DoesNotExist = 50007, /*!< The requested item does not exist. */

        NotEnoughResources = 50010, /*!< This is a general error that could refer to a variety of causes.
         For example, the queue might be full and unable to process the
         request, there's insufficient memory to process the request,
         or other conditions established by the identity provider are
         preventing the request from completing successfully. */

        NullOrUnknownParameters = 50015, /*!< This is a general error that indicates that the parameters
         provided are not valid. */

        NotAllowed = 50017, /*!< This error is specific to the identity provider, and is returned
         if their security model does not allow the request by the application. */

        ValueTooLarge = 50107, /*!< This error is specific to the identity provider, and is returned if
         the value exceeds the size that the identity provider allows. */

        AlreadyExists = 50159, /*!< The requested item cannot be created because it already exists. */

        NotReady = 50207 /*!< The request could not be completed because the provider is not ready. */

    };

private:
    //!@cond PRIVATE
    IdentityServicePropertyResult();
    ~IdentityServicePropertyResult();
    //!@endcond PRIVATE
};

} // namespace identity
} // namespace platform
} // namespace bb

QML_DECLARE_TYPE( bb::platform::identity::IdentityServicePropertyResult )

#endif /* BB_PLATFORM_IDENTITY_IDENTITYSERVICEPROPERTYRESULT_HPP */
