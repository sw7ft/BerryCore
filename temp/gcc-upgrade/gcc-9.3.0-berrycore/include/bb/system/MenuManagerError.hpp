/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_MENUMANAGERERROR_HPP
#define BB_SYSTEM_MENUMANAGERERROR_HPP

#include <bb/system/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace system
{

/*!
 * @headerfile MenuManagerError.hpp <bb/system/MenuManagerError>
 *
 * @brief The list of errors that can occur when populating a menu of invokable items.
 *
 * @xmlonly
 * <apigrouping group="User Interface/System UI"/>
 * <library name="bbsystem"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT MenuManagerError
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief The list of errors that can occur when populating a menu of invokable items.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief No error; the request was successful.
         *
         * @since BlackBerry 10.0.0
         */
        None = 0,

        /*!
         * @brief System error (out of memory, etc.).
         *
         * @since BlackBerry 10.0.0
         */
        System = 1,
    };

private:
//!@cond PRIVATE
    MenuManagerError();
    ~MenuManagerError();
//!@endcond
};

} // namespace system
} // namespace bb

QML_DECLARE_TYPE(bb::system::MenuManagerError)
#endif // BB_SYSTEM_MENUMANAGERERROR_HPP
