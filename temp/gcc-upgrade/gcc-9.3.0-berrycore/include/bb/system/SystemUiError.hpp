/*!
 * @copyright
 * Copyright Research In Motion Limited, 2011-2013
 * Research In Motion Limited. All rights reserved.
 */
#ifndef BB_SYSTEM_SYSTEMUIERROR_HPP
#define BB_SYSTEM_SYSTEMUIERROR_HPP

#include <bb/system/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace system
{

/*!
 * @headerfile SystemUiError.hpp <bb/system/SystemUiError>
 *
 * @brief The errors that can be returned by the system dialog service.
 *
 * @xmlonly
 * <apigrouping group="User Interface/System UI"/>
 * <library name="bbsystem"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT SystemUiError
{
    Q_GADGET
    Q_ENUMS (Type)

public:
    /*!
     * @brief The errors that can be returned by the system dialog service.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {

        /*!
         * @brief No errors have occurred.
         *
         * @since BlackBerry 10.0.0
         */
        None                    = 0,

        /*!
         * @brief An unknown error has occurred.
         *
         * @since BlackBerry 10.0.0
         */
        Unknown                 = 1,

        /*!
         * @brief Requests may be invalid if buttons are required to be used but no buttons are included.
         *
         * @since BlackBerry 10.0.0
         */
        NoButtons               = 2,

        /*!
         * @brief Instance is in an invalid state.
         *
         * @details Invalid state errors occur when an instance is in an invalid state, for example, if one of the objects it owns was destroyed.
         *
         * @since BlackBerry 10.0.0
         */
        InvalidState            = 3,

        /*!
         * @brief Service unavailable errors occur when the system dialog service is unavailable.
         *
         * @since BlackBerry 10.0.0
         */
        ServiceUnavailable      = 4
    };

private:
//!@cond PRIVATE
    SystemUiError();
    ~SystemUiError();
//!@endcond
};

} // namespace system
} // namespace bb

QML_DECLARE_TYPE(bb::system::SystemUiError)
#endif // BB_SYSTEM_SYSTEMUIERROR_HPP
