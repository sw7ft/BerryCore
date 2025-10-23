/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */
#ifndef BB_SYSTEM_INVOKELISTCURSORDIRECTION_HPP
#define BB_SYSTEM_INVOKELISTCURSORDIRECTION_HPP

#include <bb/system/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace system
{

/*!
 * @headerfile InvokeListCursorDirection.hpp <bb/system/InvokeListCursorDirection>
 *
 * @brief Specifies the direction of the invoke list cursor.
 *
 * @xmlonly
 * <apigrouping group="App Integration/Invocation framework"/>
 * <library name="bbsystem"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_SYSTEM_EXPORT InvokeListCursorDirection
{
    Q_GADGET
    Q_ENUMS (Type)

public:
    /*!
     * @brief Describes the direction of movement for an invoke list cursor.
     *
     * @since BlackBerry 10.2.0
     */
    enum Type {

        /**
         * Indicates that the cursor's direction is towards the next list item.
         *
         * @since BlackBerry 10.2.0
         */
        Next        = 0,

        /**
         * Indicates that the cursor's direction is towards the previous list item.
         *
         * @since BlackBerry 10.2.0
         */
        Previous    = 1
    };

private:
//!@cond PRIVATE
    InvokeListCursorDirection();
    ~InvokeListCursorDirection();
//!@endcond
};

} // namespace system
} // namespace bb

QML_DECLARE_TYPE(bb::system::InvokeListCursorDirection)
#endif // BB_SYSTEM_INVOKELISTCURSORDIRECTION_HPP
