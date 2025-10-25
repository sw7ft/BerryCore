/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_NETWORK_PUSHCOMMAND_HPP
#define BB_NETWORK_PUSHCOMMAND_HPP

#include <bb/network/Global>

#include <QMetaObject>

namespace bb
{
namespace network
{

/*!
 * @headerfile PushCommand.hpp <bb/network/PushCommand>
 *
 * @brief Encapsulates the commands that are supported by the Push Service.
 *
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Push"/>
 * <library name="bbnetwork"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */

class BB_NETWORK_EXPORT PushCommand
{
	Q_GADGET
	Q_ENUMS(Type)
	Q_FLAGS(Types)

public:

    /*!
     * @brief The commands that are supported by the Push Service.
     *
     * @since BlackBerry 10.0.0
     */
     enum Type {
        /*!
         * @brief Create a session.
         *
         * @since BlackBerry 10.0.0
         */
         CreateSession = 0,
        /*!
         * @brief Create a channel.
         *
         * @since BlackBerry 10.0.0
         */
         CreateChannel = 1,
        /*!
         * @brief Destroy a channel.
         *
         * @since BlackBerry 10.0.0
         */         
         DestroyChannel = 2,
        /*!
         * @brief Register to launch in the background when a push is received.
         *
         * @since BlackBerry 10.0.0
         */
         RegisterToLaunch = 3,
        /*!
         * @brief Cancel a previous request to launch in the background.
         *
         * @since BlackBerry 10.0.0
         */
         UnregisterFromLaunch = 4,
        /*!
         * @brief Accept pushed content.
         *
         * @since BlackBerry 10.0.0
         */
         AcceptPush = 5,
        /*!
         * @brief Reject pushed content.
         *
         * @since BlackBerry 10.0.0
         */
         RejectPush = 6
	};
	Q_DECLARE_FLAGS(Types, Type)

private:
//!@cond PRIVAT
	PushCommand();
	~PushCommand();
//!@endcond PRIVATE
};

Q_DECLARE_OPERATORS_FOR_FLAGS(PushCommand::Types)

} // namespace network
} // namespace bb

#endif /* BB_NETWORK_PUSHCOMMAND_HPP */
