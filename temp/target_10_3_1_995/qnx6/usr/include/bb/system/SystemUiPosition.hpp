/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */
#ifndef BB_SYSTEM_SYSTEMUIPOSITION_HPP
#define BB_SYSTEM_SYSTEMUIPOSITION_HPP

#include <bb/system/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace system
{

/*!
 * @headerfile SystemUiPosition.hpp <bb/system/SystemUiPosition>
 *
 * @brief The possible positions of system UI components on the device screen.
 *
 * @xmlonly
 * <apigrouping group="User Interface/System UI"/>
 * <library name="bbsystem"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT SystemUiPosition
{
    Q_GADGET
    Q_ENUMS (Type)

public:
    /*!
     * @brief The possible positions of system UI components on the device screen.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief Middle center position.
         *
         * @since BlackBerry 10.0.0
         */
        MiddleCenter = 0,
        /*!
         * @brief Top center position.
         *
         * @since BlackBerry 10.0.0
         */
        TopCenter    = 1,
        /*!
         * @brief Bottom center position.
         *
         * @since BlackBerry 10.0.0
         */
        BottomCenter = 2
    };

private:
//!@cond PRIVATE
    SystemUiPosition();
    ~SystemUiPosition();
//!@endcond
};

} // namespace system
} // namespace bb

QML_DECLARE_TYPE(bb::system::SystemUiPosition)
#endif // BB_SYSTEM_SYSTEMUIPOSITION_HPP
