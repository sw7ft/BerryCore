/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2014
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_PHONE_CALL_TYPE_HPP
#define BB_PIM_PHONE_CALL_TYPE_HPP

#include <bb/pim/Global>
#include <QString>
#include <QList>

namespace bb {
namespace pim {
namespace phone {

/**
 * @brief Call Type constants.
 *
 * @xmlonly
 * <apigrouping group="App Integration/Phone"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.3.0
 */
class BB_PIM_EXPORT CallType
{
public:
    enum Type
    {
        /*!
         * @brief The call's type cannot be determined.
         *
         * @since BlackBerry 10.3.0
         */
        Unknown = 0,

        /*!
         * @brief Incoming call.
         *
         * @since BlackBerry 10.3.0
         */
        Incoming = 1,

        /*!
         * @brief Missed call (e.g. a incoming call that was not answered).
         *
         * @since BlackBerry 10.3.0
         */
        Missed = 2,

        /*!
         * @brief Outgoing call.
         *
         * @since BlackBerry 10.3.0
         */
        Outgoing = 3,

        /* Possibly more to add in the future */
    };
};

typedef QList<CallType::Type> CallTypeList;

} // namespace phone
} // namespace pim
} // namespace bb

#endif /* BB_PIM_PHONE_CALL_TYPE_HPP */