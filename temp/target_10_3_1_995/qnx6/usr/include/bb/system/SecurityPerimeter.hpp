/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_SECURITYPERIMETER_HPP
#define BB_SYSTEM_SECURITYPERIMETER_HPP

#include <bb/system/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace system
{

/*!
 * @headerfile SecurityPerimeter.hpp <bb/system/SecurityPerimeter>
 *
 * @brief The perimeter associated with the application.
 *
 * @xmlonly
 * <apigrouping group="Platform/Security"/>
 * <library name="bbsystem"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT SecurityPerimeter
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief The perimeter associated with the application.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief The context-specific default perimeter.
         *
         * @since BlackBerry 10.0.0
         */
        Default = 0,

        /*!
         * @brief The enterprise perimeter.
         *
         * @since BlackBerry 10.0.0
         */
        Enterprise = 1,

        /*!
         * @brief The personal perimeter.
         *
         * @since BlackBerry 10.0.0
         */
        Personal = 2
    };

private:
//!@cond PRIVATE
    SecurityPerimeter();
    ~SecurityPerimeter();
//!@endcond
};

} // namespace system
} // namespace bb

QML_DECLARE_TYPE(bb::system::SecurityPerimeter)
#endif // BB_SYSTEM_SECURITYPERIMETER_HPP
