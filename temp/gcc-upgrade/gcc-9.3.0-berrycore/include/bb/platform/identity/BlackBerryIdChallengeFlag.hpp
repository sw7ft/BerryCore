/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_IDENTITY_BLACKBERRYIDCHALLENGEFLAG_HPP
#define BB_PLATFORM_IDENTITY_BLACKBERRYIDCHALLENGEFLAG_HPP

#include <bb/platform/Global>
#include <QtDeclarative/QtDeclarative>

namespace bb {
namespace platform {
namespace identity {

/*!
 * @headerfile BlackBerryIdChallengeFlag.hpp <bb/platform/identity/BlackBerryIdChallengeFlag>
 * @brief The flags used for a challenge request.
 * @details Multiple flags can be combined using bitwise 'OR' unless stated
 * otherwise.
 * @sa challenge()
 * @xmlonly
 * <library name="bbplatform" />
 * <apigrouping group="Platform/Identity" />
 * @endxmlonly
 */
class BB_PLATFORM_EXPORT BlackBerryIdChallengeFlag {
    Q_GADGET
    Q_ENUMS( Type )
    Q_FLAGS( Types )
public:
    enum Type {
        /*!<
         * @brief Default challenge flag.
         * @details No options specified, and the challenge will follow the default
         * behavior.
         */
        Default = 0
    };
    Q_DECLARE_FLAGS( Types, Type )

private    :
    //!@cond PRIVATE
    BlackBerryIdChallengeFlag();
    ~BlackBerryIdChallengeFlag();
    //!@endcond PRIVATE
};
Q_DECLARE_OPERATORS_FOR_FLAGS( BlackBerryIdChallengeFlag::Types )

} // namespace identity
} // namespace platform
} // namespace bb

QML_DECLARE_TYPE( bb::platform::identity::BlackBerryIdChallengeFlag )

#endif /* BB_PLATFORM_IDENTITY_BLACKBERRYIDCHALLENGEFLAG_HPP */
