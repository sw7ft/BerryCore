/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_IDENTITY_IDENTITYSERVICETOKENRESULT_HPP
#define BB_PLATFORM_IDENTITY_IDENTITYSERVICETOKENRESULT_HPP

#include <bb/platform/Global>
#include <QtDeclarative/QtDeclarative>

namespace bb {
namespace platform {
namespace identity {

/*!
 * @headerfile IdentityServiceTokenResult.hpp <bb/platform/identity/IdentityServiceTokenResult>
 * @brief Contains enumerated return codes for asynchronous responses to API calls related to tokens.
 * @xmlonly
 * <library name="bbplatform" />
 * <apigrouping group="Platform/Identity" />
 * @endxmlonly
 */
class BB_PLATFORM_EXPORT IdentityServiceTokenResult {
    Q_GADGET
    Q_ENUMS( Type )
public:
    enum Type {
        Success = 0, /*!< The call completed successfully.  In asynchronous calls, the request
         has been sent and either the success or failure callback is called
         when the response arrives. */

        InternalError = 49999, /*!< Error code 49999 is the default error code, and indicates that
         an internal error occurred while processing the request. */

        // BlackBerry ID library basic error codes (reserved range : 50000 - 50099)
        AccountLocallyLockedOut = 50003, /*!< User authentication could not complete because the
         user account is locked. */

        UserCouldNotBeAuthenticated = 50004, /*!< The identity provider could not authenticate the
         user.  There are a variety of possible causes
         for this error, including technical reasons, the
         user canceled the authentication request, and
         failure to meet other conditions that the identity
         provider requires. */

        InvalidRequest = 50006, /*!< The request is malformed or not supported. */

        UnknownTokenType = 50008, /*!< This error may be returned with the requestToken() function,
         and indicates that the identity provider is unable to determine,
         or does not support, the type of token that was requested.  This
         error is specific to the identity provider. */

        UnknownAppliesTo = 50009, /*!< This error may be returned with the requestToken() function,
         and indicates that the identity provider is unable to determine
         the application or service that the token applies to.  This
         error is specific to the identity provider. */

        NotEnoughResources = 50010, /*!< This is a general error that could refer to a variety of causes.
         For example, the queue might be full and unable to process the
         request, there's insufficient memory to process the request,
         or other conditions established by the identity provider are
         preventing the request from completing successfully. */

        CannotGetTokenWhileOffline = 50011, /*!<  This error is returned with the requestToken() function,
         and indicates that a token could not be obtained because
         the identity provider's user authentication service is
         offline. */

        ErrorWhileContactingService = 50012, /*!< An error occurred while contacting the identity service,
         which could include network issues. */

        NullOrUnknownParameters = 50015 /*!< This is a general error that indicates that the parameters
         provided are not valid. */

    };

private:
    //!@cond PRIVATE
    IdentityServiceTokenResult();
    ~IdentityServiceTokenResult();
    //!@endcond PRIVATE
};

} // namespace identity
} // namespace platform
} // namespace bb

QML_DECLARE_TYPE( bb::platform::identity::IdentityServiceTokenResult )

#endif /* BB_PLATFORM_IDENTITY_IDENTITYSERVICETOKENRESULT_HPP */
