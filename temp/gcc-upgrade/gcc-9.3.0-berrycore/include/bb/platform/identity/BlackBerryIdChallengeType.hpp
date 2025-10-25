/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_IDENTITY_BLACKBERRYIDCHALLENGETYPE_HPP
#define BB_PLATFORM_IDENTITY_BLACKBERRYIDCHALLENGETYPE_HPP

#include <bb/platform/Global>
#include <QtDeclarative/QtDeclarative>

namespace bb {
namespace platform {
namespace identity {

/*!
 * @headerfile BlackBerryIdChallengeType.hpp <bb/platform/identity/BlackBerryIdChallengeType>
 * @brief The type used for a challenge request.
 * @details These are the types of challenges that are available to applications
 * using BlackBerry ID as an identity provider.
 * @sa challenge()
 * @xmlonly
 * <library name="bbplatform" />
 * <apigrouping group="Platform/Identity" />
 * @endxmlonly
 */
class BB_PLATFORM_EXPORT BlackBerryIdChallengeType {
    Q_GADGET
    Q_ENUMS( Type )
public:
    enum Type {
        /*!<
         * @brief Authentication challenge type.
         * @details Prompts the user to authenticate with their current password.
         * @note This ignores GUI Allowed and will present the user with a pop
         * up to confirm the password.
         */
        Authenticate = 0,

        /*!<
         * @brief Email confirmation challenge type.
         * @details Prompts the user to confirm their email.
         * This will present the user with a pop up to allow the
         * email confirmation to be sent.
         * @note This ignores GUI Allowed and will present the user with a pop
         * up to allow the email confirmation to be sent.
         */
        EmailConfirmation = 1

    };

private:
    //!@cond PRIVATE
    BlackBerryIdChallengeType();
    ~BlackBerryIdChallengeType();
    //!@endcond PRIVATE
};

} // namespace identity
} // namespace platform
} // namespace bb

QML_DECLARE_TYPE( bb::platform::identity::BlackBerryIdChallengeType )

#endif /* BB_PLATFORM_IDENTITY_BLACKBERRYIDCHALLENGETYPE_HPP */
