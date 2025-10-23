/*!
 * @copyright
 * Copyright (C) 2012 - 2013 BlackBerry Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_PHONE_LINETYPE_HPP
#define BB_SYSTEM_PHONE_LINETYPE_HPP

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
 * @headerfile LineType.hpp <bb/system/phone/LineType>
 *
 * @brief The types of phone lines available for making calls.
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
class BB_SYSTEM_EXPORT LineType
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief Values describing the type of a phone line.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
        /*!
         * @brief The line is invalid.
         *
         * @since BlackBerry 10.0.0
         */
        Invalid = -1,

        /*!
         * @brief The line is cellular.
         *
         * @since BlackBerry 10.0.0
         */
        Cellular = 0,

        /*!
         * @brief The line is MVS (Mobile Voice System).
         *
         * @since BlackBerry 10.0.0
         */
        MVS = 1,

        /*!
         * @brief The line is video chat.
         *
         * @since BlackBerry 10.0.0
         */
        VideoChat = 2,

        /*!
          * @brief The line is SecuVOICE (Secure Voice).
          *
          * @since BlackBerry 10.2
          */
        SecuVOICE = 3
    };

private:
    //!@cond PRIVATE
    LineType();
    ~LineType();
    //!@endcond
};

} // phone
} // system
} // bb

QML_DECLARE_TYPE(bb::system::phone::LineType)
#endif /* BB_SYSTEM_PHONE_LINETYPE_HPP */
