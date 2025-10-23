/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */
#ifndef BB_SYSTEM_SYSTEMUIRETURNKEYACTION_HPP
#define BB_SYSTEM_SYSTEMUIRETURNKEYACTION_HPP

#include <bb/system/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace system
{

/*!
 * @headerfile SystemUiReturnKeyAction.hpp <bb/system/SystemUiReturnKeyAction>
 *
 * @brief The possible types of actions to associate with the Return key.
 *
 * @xmlonly
 * <apigrouping group="User Interface/System UI"/>
 * <library name="bbsystem"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT SystemUiReturnKeyAction
{
    Q_GADGET
    Q_ENUMS (Type)

public:
    /*!
     * @brief The possible types of actions to associate with the Return key.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {

        /*!
         * @brief The default return key.
         *
         * @since BlackBerry 10.0.0
         */
        Default = 0,

        /*!
         * @brief Return key type is Go.
         *
         * @since BlackBerry 10.0.0
         */
        Go      = 1,

        /*!
         * @brief Return key type is Join.
         *
         * @since BlackBerry 10.0.0
         */
        Join    = 2,

        /*!
         * @brief Return key type is Next.
         *
         * @since BlackBerry 10.0.0
         */
        Next    = 3,

        /*!
         * @brief Return key type is Search.
         *
         * @since BlackBerry 10.0.0
         */
        Search  = 4,

        /*!
         * @brief Return key type is Send.
         *
         * @since BlackBerry 10.0.0
         */
        Send    = 5,

        /*!
         * @brief Return key type is Submit.
         *
         * @since BlackBerry 10.0.0
         */
        Submit  = 6,

        /*!
         * @brief Return key type is Done.
         *
         * @since BlackBerry 10.0.0
         */
        Done    = 7,

        /*!
         * @brief Return key type is Connect.
         *
         * @since BlackBerry 10.0.0
         */
        Connect = 8

    };

private:
//!@cond PRIVATE
    SystemUiReturnKeyAction();
    ~SystemUiReturnKeyAction();
//!@endcond
};

} // namespace system
} // namespace bb

QML_DECLARE_TYPE(bb::system::SystemUiReturnKeyAction)
#endif // BB_SYSTEM_SYSTEMUIRETURNKEYACTION_HPP
