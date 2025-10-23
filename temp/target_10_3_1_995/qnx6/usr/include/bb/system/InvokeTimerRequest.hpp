/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2014
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_INVOKETIMERREQUEST_HPP
#define BB_SYSTEM_INVOKETIMERREQUEST_HPP

#include <bb/system/Global>
#include <bb/system/InvokeReply>
#include <bb/system/InvokeAction>
#include <bb/system/InvokeDateTime>
#include <bb/system/InvokeRecurrenceRule>

#include <QSharedDataPointer>

namespace bb
{
namespace system
{

class InvokeTimerRequestPrivate;

/*!
 * @headerfile InvokeTimerRequest.hpp <bb/system/InvokeTimerRequest>
 *
 * @brief Encapsulates a request to register a timer with the invocation service.
 *
 * @details The register timer trigger request message is sent to the invocation
 * service to register a new invocation timer trigger.
 *
 * @xmlonly
 * <apigrouping group="App Integration/Invocation framework"/>
 * <library name="bbsystem"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.3.0
 */
class BB_SYSTEM_EXPORT InvokeTimerRequest
{
    Q_ENUMS(Type)

public:

    /*!
     * @brief The kinds of timer requests.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief Unknown type
         *
         * @since BlackBerry 10.0.0
         */
        Unknown = 0,

        /*!
         * @brief Type of type timer request that allows you to specify an @c InvokeDateTime
         *
         * @since BlackBerry 10.0.0
         */
        SpecificTime = 1,

        /*!
         * @brief Type of type timer request that allows you to specify an @c InvokeRecurrenceRule
         *
         * @since BlackBerry 10.0.0
         */
        RecurrentRule = 2
    };


public:

    /*!
     * @brief Creates a new @c #InvokeTimerRequest object.
     *
     * @brief The timer request params need to be set by calling the method
     * @c #set
     *
     * @since BlackBerry 10.3.0
     */
    InvokeTimerRequest();


    /*!
     * @brief Creates a new @c #InvokeTimerRequest object.
     *
     * @param timerId The ID for this request.
     *   A timer is required to have a timer ID attribute. The timer ID is used to uniquely identify and deregister
     *   the timer within an application package.
     * @param specificTime The @c #InvokeDateTime representing the specific time
     *   for the timer. If the @c #specificTime is of type
     *   @c #InvokeDateTime::Anchored, the assigned time zone
     *   may or may not be recognized. If the assigned time zone is not
     *   recognized the timer registration request will fail.
     * @param target The target to invoke
     *
     * @since BlackBerry 10.3.0
     */
    InvokeTimerRequest(const QString &timerId, const InvokeDateTime &specificTime, const QString &target);


    /*!
     * @brief Creates a new @c #InvokeTimerRequest object.
     *
     * @param timerId The ID for this request.
     *   A timer is required to have a timer ID attribute. The timer ID is used to uniquely identify and deregister
     *   the timer within an application package. Recurrence Rules have to be explicitly deregistered unlike single shot Specific Timers which
     *   expire on completion. It means that @c #timerId must be saved by developer to be used later for deregistering Recurrence Rule.
     *   Otherwise, the timer would stay registered and active forever.
     * @param recurrenceRule A recurrence rule that specifies the interval at which to trigger a headless application
     * @param target The target to invoke
     *
     * @since BlackBerry 10.3.0
     */
    InvokeTimerRequest(const QString &timerId, const InvokeRecurrenceRule &recurrenceRule, const QString &target);

    /*!
     * @brief Creates a copy of an existing @c #InvokeTimerRequest object.
     *
     * @param other The source @c #InvokeTimerRequest object to copy.
     *
     * @since BlackBerry 10.3.0
     */
    InvokeTimerRequest(const InvokeTimerRequest &other);

    /*!
     * @brief Destroys this @c #InvokeTimerRequest object.
     *
     * @since BlackBerry 10.3.0
     */
    virtual ~InvokeTimerRequest();

    /*!
     * @brief Copies the data of an existing @c #InvokeTimerRequest object to
     * this object.
     *
     * @param other The source @c #InvokeTimerRequest object to copy.
     *
     * @return The @c #InvokeTimerRequest instance.
     *
     * @since BlackBerry 10.3.0
     */
    InvokeTimerRequest& operator=(const InvokeTimerRequest &other);

    /*!
     * @brief Sets the params for the timer request of @c #InvokeTimerRequest::SpecificTime type
     *
     * @param timerId The ID for this request.
     *   A timer is required to have a timer ID attribute. The timer ID is used to uniquely identify and deregister
     *   the timer within an application package.
     * @param specificTime The @c #InvokeDateTime representing the specific time
     *   for the timer. If the @c #specificTime is of type
     *   @c #InvokeDateTime::Anchored, the assigned time zone
     *   may or may not be recognized. If the assigned time zone is not
     *   recognized the timer registration request will fail.
     * @param target The target to invoke
     *
     * @since BlackBerry 10.3.0
     */
    void set(const QString &timerId,  const InvokeDateTime &specificTime, const QString &target);


    /*!
     * @brief Sets the params for the timer request of @c #InvokeTimerRequest::RecurrentRule type
     *
     * @param timerId The ID for this request.
     *   A timer is required to have a timer ID attribute. The timer ID is used to uniquely identify and deregister
     *   the timer within an application package. Recurrence Rules have to be explicitly deregistered unlike single shot Specific Timers which
     *   expire on completion. It means that @c #timerId must be saved by developer to be used later for deregistering Recurrence Rule.
     *   Otherwise, the timer would stay registered and active forever.
     * @param recurrenceRule  A recurrence rule that specifies the interval at which to trigger a headless application
     * @param target The target to invoke
     *
     * @since BlackBerry 10.3.0
     */
    void set(const QString &timerId, const InvokeRecurrenceRule &recurrenceRule, const QString &target);

    /*!
     * @brief Return the assigned target.
     *
     * @return target that was previously set or an empty string
     *
     * @since BlackBerry 10.3.0
     */
    QString target() const;

    /*!
     * @brief Return the assigned timerId.
     *
     * @details Recurrence Rules have to be explicitly deregistered unlike single shot Specific Timers which
     *   expire on completion. It means that @c #timerId must be saved by developer to be used later for deregistering Recurrence Rule.
     *   Otherwise, the timer would stay registered and active forever.
     *
     * @return timerId that was previously set or an empty string
     *
     * @since BlackBerry 10.3.0
     *
     */
    QString timerId() const;


    /*!
     * @brief Return the timer type.
     *
     * @return timerType One of the timer types defined in @c #InvokeTimerRequest::Type (Unknown, SpecificTime, RecurrentRule)
     *
     * @since BlackBerry 10.3.0
     *
     */
    InvokeTimerRequest::Type type() const;

    /*!
     * @brief Return the assigned specific time.
     *
     * @return specific time that was previously set
     *
     * @since BlackBerry 10.3.0
     *
     */
    bb::system::InvokeDateTime specificTime() const;

    /*!
     * @brief Return the assigned recurrence rule.
     *
     * @return recurrence rule that was previously set
     *
     * @since BlackBerry 10.3.0
     *
     */
    bb::system::InvokeRecurrenceRule recurrenceRule() const;

    /*!
     * @brief Returns true if this @c #InvokeTimerRequest object is valid.
     *
     * @details The method returns true if both the @c #target and the
     * @c #timerId representing this @c #InvokeTimerRequest object are not
     * empty and the @c #specificTime is valid or @c #recurrenceRule is valid
     * depending on the @c #type of the request
     *
     * @return true if valid, false otherwise
     *
     * @since BlackBerry 10.3.0
     */
    bool isValid() const;


private:
//!@cond PRIVATE
    QSharedDataPointer<InvokeTimerRequestPrivate> d;


//!@endcond
};

} // namespace system
} // namespace bb

#endif // BB_SYSTEM_INVOKETIMERREQUEST_HPP
