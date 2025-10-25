/*
 * PushCommand.hpp
 *
 * (C) 2012 Research In Motion Ltd. All Rights Reserved.
 * RIM, Research In Motion -- Reg. U.S. Patent and Trademark Office
 * The RIM Logo and Inter@ctive are trademarks of Research In Motion, Limited
 * All materials confidential information of Research In Motion, Limited
 *
 * This enumeration defines the commands that are supported by Push Service.
 *
 *  @since 10.0.0
 */

#ifndef BB_COMMUNICATIONS_PUSH_PUSHCOMMAND_HPP_
#define BB_COMMUNICATIONS_PUSH_PUSHCOMMAND_HPP_
namespace bb {
namespace communications {
namespace push {

enum PushCommand {
	 CreateSession = 0,
	 CreateChannel = 1,
	 DestroyChannel = 2,
	 RegisterToLaunch = 3,
	 UnregisterFromLaunch = 4,
	 AcceptPush = 5,
	 RejectPush = 6

};
} // namespace push
} // namespace communications
} // namespace bb

#endif /* BB_COMMUNICATIONS_PUSH_PUSHCOMMAND_HPP_ */
