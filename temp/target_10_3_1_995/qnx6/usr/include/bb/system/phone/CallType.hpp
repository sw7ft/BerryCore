/*!
 * @copyright
 * Copyright (C) 2012 - 2013 BlackBerry Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_PHONE_CALLTYPE_HPP
#define BB_SYSTEM_PHONE_CALLTYPE_HPP

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
 * @headerfile CallType.hpp <bb/system/phone/CallType>
 *
 * @brief Values describing the type of the call.
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
class BB_SYSTEM_EXPORT CallType
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief The type of the call.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
        /*!
         * @brief The call type is invalid.
         *
         * @since BlackBerry 10.0.0
         */
        Invalid = -1,

        /*!
         * @brief The call is incoming.
         *
         * @since BlackBerry 10.0.0
         */
        Incoming = 0,

        /*!
         * @brief The call is outgoing.
         *
         * @since BlackBerry 10.0.0
         */
        Outgoing = 1,

        /*!
         * @brief The call is a multi-party call.
         *
         * @since BlackBerry 10.0.0
         */
        MultiParty = 2,

        /*!
         * @brief The call is missed.
         *
         * @since BlackBerry 10.0.0
         */
        Missed = 3,

        /*!
         * @brief The call is a command call.
         *
         * @since BlackBerry 10.0.0
         */
        Command = 4,

        /*!
         * @brief The call is an emergency call.
         *
         * @since BlackBerry 10.0.0
         */
        Emergency = 5
    };

private:
    //!@cond PRIVATE
    CallType();
    ~CallType();
   //!@endcond
};

} // phone
} // system
} // bb

QML_DECLARE_TYPE(bb::system::phone::CallType)
#endif /* BB_SYSTEM_PHONE_CALLTYPE_HPP */
