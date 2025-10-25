/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2014
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_INVOKERECURRENCERULELIMIT_HPP
#define BB_SYSTEM_INVOKERECURRENCERULELIMIT_HPP

#include <bb/system/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace system
{

/*!
 * @headerfile InvokeRecurrenceRuleLimit.hpp <bb/system/InvokeRecurrenceRuleLimit>
 *
 * @brief The list of possible results of a request to the invocation service.
 *
 * @xmlonly
 * <apigrouping group="App Integration/Invocation framework"/>
 * <library name="bbsystem"/>
 * <qml>
 *    <class register="enum-only" />
 * </qml>
 * @endxmlonly
 *
 * @since BlackBerry 10.3.0
 */
class BB_SYSTEM_EXPORT InvokeRecurrenceRuleLimit
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief The kinds of limits used in a @c #InvokeRecurrenceRule.
     *
     * @since BlackBerry 10.3.0
     */
    enum Type {
        /*!
         * @brief No limit.
         *
         * @details There is no "count" or "date" limit for a specific rule.
         *
         * @since BlackBerry 10.3.0
         */
        None       = 0,

        /*!
         * @brief Count limit.
         *
         * @details This limit guarantees that the recurrence rule will no longer be applied after it was triggered the specified number of times.
         *
         * @since BlackBerry 10.3.0
         */
        Count      = 1,

        /*!
         * @brief Date limit.
         *
         * @details This is the time at which the recurrence rule will no longer be applied.
         *
         * @since BlackBerry 10.3.0
         */
        Date       = 2

    };

private:
//!@cond PRIVATE
    InvokeRecurrenceRuleLimit();
    ~InvokeRecurrenceRuleLimit();
//!@endcond
};

} // namespace system
} // namespace bb

QML_DECLARE_TYPE(bb::system::InvokeRecurrenceRuleLimit)
#endif // BB_SYSTEM_INVOKERECURRENCERULELIMIT_HPP
