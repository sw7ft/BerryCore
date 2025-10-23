/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2014
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_INVOKERECURRENCERULEFREQUENCY_HPP
#define BB_SYSTEM_INVOKERECURRENCERULEFREQUENCY_HPP

#include <bb/system/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace system
{

/*!
 * @headerfile InvokeRecurrenceRuleFrequency.hpp <bb/system/InvokeRecurrenceRuleFrequency>
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
class BB_SYSTEM_EXPORT InvokeRecurrenceRuleFrequency
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief The kinds of frequency used in a InvokeRecurrenceRule.
     *
     * @since BlackBerry 10.3.0
     */
    enum Type {
        /*!
         * @brief None.
         *
         * @details If value is set to "None" it means that @c #InvokeRecurrentRule will never happen.
         *
         * @since BlackBerry 10.3.0
         */
        None            = 0,

        /*!
         * @brief Yearly.
         *
         * @details Specifies the frequency of repeating events based on an interval of a year or more
         * (depending on the value of "interval" parameter of @c #InvokeRecurrentRule)
         *
         * @since BlackBerry 10.3.0
         */
        Yearly          = 1,

        /*!
         * @brief Monthly.
         *
         * @details Specifies the frequency of repeating events based on an interval of a month or more
         * (depending on the value of "interval" parameter of @c #InvokeRecurrentRule)
         *
         * @since BlackBerry 10.3.0
         */
        Monthly         = 2,

        /*!
         * @brief Weekly.
         *
         * @details Specifies the frequency of repeating events based on an interval of a week or more
         * (depending on the value of "interval" parameter of @c #InvokeRecurrentRule)
         *
         * @since BlackBerry 10.3.0
         */
        Weekly          = 3,

        /*!
         * @brief Daily.
         *
         * @details Specifies the frequency of repeating events based on an interval of a day or more
         * (depending on the value of "interval" parameter of @c #InvokeRecurrentRule)
         *
         * @since BlackBerry 10.3.0
         */
        Daily           = 4,

        /*!
         * @brief Hourly.
         *
         * @details Specifies the frequency of repeating events based on an interval of an hour or more
         * (depending on the value of "interval" parameter of @c #InvokeRecurrentRule)
         *
         * @since BlackBerry 10.3.0
         */
        Hourly          = 5,

        /*!
         * @brief Minutely.
         *
         * @details Specifies the frequency of repeating events based on an interval of a minute or more
         * (depending on the value of "interval" parameter of @c #InvokeRecurrentRule)
         *
         * @since BlackBerry 10.3.0
         */
        Minutely        = 6

    };

private:
//!@cond PRIVATE
    InvokeRecurrenceRuleFrequency();
    ~InvokeRecurrenceRuleFrequency();
//!@endcond
};

} // namespace system
} // namespace bb

QML_DECLARE_TYPE(bb::system::InvokeRecurrenceRuleFrequency)
#endif // BB_SYSTEM_INVOKERECURRENCERULEFREQUENCY_HPP
