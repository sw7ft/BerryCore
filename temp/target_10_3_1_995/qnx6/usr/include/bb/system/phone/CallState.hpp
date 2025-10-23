/*!
 * @copyright
 * Copyright (C) 2012 - 2013 BlackBerry Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_PHONE_CALLSTATE_HPP
#define BB_SYSTEM_PHONE_CALLSTATE_HPP

#include <bb/system/Global>
#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace system
{
namespace phone
{

/*!
 * @headerfile CallState.hpp <bb/system/phone/CallState>
 *
 * @brief Values describing the states of a call.
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Phone"/>
 * <library name="bbsystem"/>
 * @endxmlonly
 *
 * @permissions You must also specify the @c access_phone permission in your bar-descriptor.xml file.
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT CallState
{
    Q_GADGET
    Q_ENUMS(Type)

public:

    /*!
     * @brief Values describing the states of a call.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
        /*!
         * @brief The state is invalid.
         *
         * @since BlackBerry 10.0.0
         */
        Invalid = -1,

        /*!
    	 * @brief The state is unknown.
         *
         * @since BlackBerry 10.0.0
    	 */
        Unknown = 0,

        /*!
         * @brief The call is incoming.
         *
         * @since BlackBerry 10.0.0
         */
        Incoming = 1,

        /*!
         * @brief The call is connecting.
         *
         * @since BlackBerry 10.0.0
         */
        Connecting = 2,

        /*!
         * @brief The call is ringing at the remote side.
         *
         * @since BlackBerry 10.0.0
         */
        RemoteRinging = 3,

        /*!
         * @brief The call is connected.
         *
         * @since BlackBerry 10.0.0
         */
        Connected = 4,

        /*!
         * @brief The call is disconnected.
         *
         * @since BlackBerry 10.0.0
         */
        Disconnected = 5,

        /*!
         * @brief The call failed.
         *
         * @since BlackBerry 10.0.0
         */
        Failed = 6,

        /*!
         * @brief The call is on hold.
         *
         * @since BlackBerry 10.0.0
         */
        Held = 7,

        /*!
         * @brief The call is a multi-party call with members.
         *
         * @since BlackBerry 10.0.0
         */
        MultiPartyMember = 8
    };

private:
    //!@cond PRIVATE
    CallState();
    ~CallState();
    //!@endcond
};

} // phone
} // system
} // bb

QML_DECLARE_TYPE(bb::system::phone::CallState)
#endif /* BB_SYSTEM_PHONE_CALLSTATE_HPP */
