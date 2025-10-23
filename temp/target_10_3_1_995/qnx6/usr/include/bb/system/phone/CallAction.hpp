/*!
 * @copyright
 * Copyright (C) 2014 BlackBerry Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_PHONE_CALLACTION_HPP
#define BB_SYSTEM_PHONE_CALLACTION_HPP

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
 * @headerfile CallAction.hpp <bb/system/phone/CallAction>
 *
 * @brief Values describing the actions that can be performed on a phone call.
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Phone"/>
 * <library name="bbsystem"/>
 * @endxmlonly
 *
 * @permissions You must also specify the @c access_phone permission in your bar-descriptor.xml file.
 *
 * @since BlackBerry 10.3.0
 */
class BB_SYSTEM_EXPORT CallAction
{
    Q_GADGET
    Q_ENUMS(Type)

public:

    /*!
     * @brief Values describing the actions that can be performed on a phone call.
     *
     * @since BlackBerry 10.3.0
     */
    enum Type
    {
        /*!
         * @brief The hold call action.
         *
         * @since BlackBerry 10.3.0
         */
        HoldCall = 1,

        /*!
         * @brief The resume call action.
         *
         * @since BlackBerry 10.3.0
         */
        ResumeCall = 2,

        /*!
         * @brief The split call action.
         *
         * @since BlackBerry 10.3.0
         */
        SplitCall = 3
    };

private:
    //!@cond PRIVATE
    CallAction();
    ~CallAction();
    //!@endcond
};

} // phone
} // system
} // bb

QML_DECLARE_TYPE(bb::system::phone::CallAction)
#endif /* BB_SYSTEM_PHONE_CALLACTION_HPP */
