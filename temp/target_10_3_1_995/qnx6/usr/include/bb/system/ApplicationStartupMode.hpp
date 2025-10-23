/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_APPLICATIONSTARTUPMODE_HPP
#define BB_SYSTEM_APPLICATIONSTARTUPMODE_HPP

#include <bb/system/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace system
{

/*!
 * @headerfile ApplicationStartupMode.hpp <bb/system/ApplicationStartupMode>
 *
 * @brief The list of possible reasons an application was launched.
 *
 * @xmlonly
 * <apigrouping group="App Integration/Invocation framework"/>
 * <library name="bbsystem"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT ApplicationStartupMode
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief The list of possible reasons an application was launched.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        
        /*!
         * @brief The application was launched normally (i.e., not due to an invoke message).
         *
         * @since BlackBerry 10.0.0
         */
        LaunchApplication = 0,
        
        /*!
         * @brief The application was launched due to an invoke message and should run as a normal 
         * application.
         *
         * @since BlackBerry 10.0.0
         */
        InvokeApplication = 1,
        
        //!@cond PRIVATE
        /*!
         * @brief The application was launched due to an invoke message and should run as a viewer.
         *
         * @note Deprecated. To maintain binary compatibility, do not remove or renumber.
         */
        InvokeViewer = 2,
        //!@endcond

        /*!
         * @brief The application was launched due to an invoke message and should run as a card.
         *
         * @since BlackBerry 10.0.0
         */
        InvokeCard = 3,

        /*!
         * @brief The application was launched due to an invoke message and should run as a headless
         * application.
         *
         * @since BlackBerry 10.3.0
         */
        InvokeHeadless = 4,

        /*!
         * @brief The application was launched normally (i.e., not due to an invoke message)
         * and should run as a headless application.
         *
         * @since BlackBerry 10.3.0
         */
        LaunchHeadless = 5
};

private:
//!@cond PRIVATE
    ApplicationStartupMode();
    ~ApplicationStartupMode();
//!@endcond
};

} // namespace system
} // namespace bb

QML_DECLARE_TYPE(bb::system::ApplicationStartupMode)
#endif // BB_SYSTEM_APPLICATIONSTARTUPMODE_HPP
