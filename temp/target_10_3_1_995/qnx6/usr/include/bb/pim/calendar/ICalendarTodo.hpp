
/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_CALENDAR_ICALENDARTODO_HPP
#define BB_PIM_CALENDAR_ICALENDARTODO_HPP

#include <bb/pim/Global>
#include <bb/pim/calendar/DataTypes>
#include <bb/pim/calendar/ICalendarTodoStatus>
#include <bb/pim/calendar/ICalendarTodoPriority>
#include <QSharedDataPointer>
#include <QDateTime>
#include <QString>

namespace bb {
namespace pim {
namespace calendar {

class Recurrence;
class ICalendarTodoPrivate;

/*!
 * @brief A to-do object contained in an iCalendar file.
 *
 * @details
 * This represents a task built from a VTODO object in an iCalendar file.
 *
 * @xmlonly
 * <apigrouping group="App Integration/Calendar"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT ICalendarTodo {
public:

    /*!
     * @brief Constructor
     *
     * @details
     * Creates an object
     *
     * @since BlackBerry 10.0.0
     */
    ICalendarTodo();

    /*!
     * @brief Destructor
     *
     * @details
     * Class destructor
     *
     * @since BlackBerry 10.0.0
     */
    ~ICalendarTodo();

    /*!
     * @brief Copy constructor
     *
     * @details
     * Creates an object with values copied from the one passed as parameter.
     *
     * @since BlackBerry 10.0.0
     */
    ICalendarTodo(const ICalendarTodo& other);

    /*!
     * @brief Assignment operator
     *
     * @details
     * Updates the object's fields with values from the one passed as parameter.
     *
     * @return Reference to the object that received the assignment.
     *
     * @since BlackBerry 10.0.0
     */
    ICalendarTodo& operator=(const ICalendarTodo& other);

    /*!
     * @brief To-do's subject
     *
     * @details
     * Returns the subject of the to-do.
     *
     * @return The attribute's value.
     *
     * @since BlackBerry 10.0.0
     */
    QString subject() const;

    /*!
     * @brief Due date
     *
     * @details
     * Date and time when the task is due.
     *
     * @return The attribute's value.
     *
     * @since BlackBerry 10.0.0
     */
    QDateTime due() const;

    /*!
     * @brief To-do's status
     *
     * @details
     * Status of completion.
     *
     * @return The attribute's value.
     *
     * @since BlackBerry 10.0.0
     */
    ICalendarTodoStatus::Type status() const;

    /*!
     * @brief Date of completion
     *
     * @details
     * Date and time of completion.
     *
     * @return The attribute's value.
     *
     * @since BlackBerry 10.0.0
     */
    QDateTime completed() const;

    /*!
     * @brief To-do's description
     *
     * @details
     * Returns the description of the task.
     *
     * @return The attribute's value.
     *
     * @since BlackBerry 10.0.0
     */
    QString description() const;

    /*!
     * @brief Universal identifier
     *
     * @details
     * Returns the task's universal identifier.
     *
     * @return The attribute's value.
     *
     * @since BlackBerry 10.0.0
     */
    QString uid() const;

    /*!
     * @brief Recurrence
     *
     * @details
     * Returns the to-do's recurrence rule.
     *
     * @return The attribute's value.
     *
     * @since BlackBerry 10.0.0
     */
    Recurrence recurrence() const;

    /*!
     * @brief Priority
     *
     * @details
     * Priority for the task.
     *
     * @return The attribute's value.
     *
     * @since BlackBerry 10.0.0
     */
    ICalendarTodoPriority::Type priority() const;


    /*!
     * @brief Subject setter
     *
     * @details
     * Changes the to-do's subject.
     *
     * @param subject new value for the attribute
     *
     * @since BlackBerry 10.0.0
     */
    void setSubject(const QString& subject);

    /*!
     * @brief Setter for the due dater
     *
     * @details
     * Assigns a value to the due date attribute.
     *
     * @param due new value for the attribute
     *
     * @since BlackBerry 10.0.0
     */
    void setDue(const QDateTime& due);

    /*!
     * @brief Setter for the status attribute
     *
     * @details
     * Changes the object's status.
     *
     * @param status new value for the attribute
     *
     * @since BlackBerry 10.0.0
     */
    void setStatus(ICalendarTodoStatus::Type status);

    /*!
     * @brief Date of completion setter
     *
     * @details
     * Modifies the date of completion.
     *
     * @param completed new value for the attribute
     *
     * @since BlackBerry 10.0.0
     */
    void setCompleted(const QDateTime& completed);

    /*!
     * @brief Description setter
     *
     * @details
     * Changes the description attribute in the to-do.
     *
     * @param description new value for the attribute
     *
     * @since BlackBerry 10.0.0
     */
    void setDescription(const QString& description);

    /*!
     * @brief UId setter
     *
     * @details
     * Sets the UId for the to-do.
     *
     * @param uid new value for the attribute
     *
     * @since BlackBerry 10.0.0
     */
    void setUid(const QString& uid);

    /*!
     * @brief Recurrence setter
     *
     * @details
     * Sets the to-do's recurrence rule.
     *
     * @param recurrence new value for the attribute
     *
     * @since BlackBerry 10.0.0
     */
    void setRecurrence(const Recurrence& recurrence);

    /*!
     * @brief Priority setter
     *
     * @details
     * Changes the object's priority.
     *
     * @param priority new value for the attribute
     *
     * @since BlackBerry 10.0.0
     */
    void setPriority(ICalendarTodoPriority::Type priority);

    /*!
     * @brief Object correctness
     *
     * @details
     * Checks if the object's attributes have acceptable values.
     *
     * @return True if the object is valid, false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

private:
    QSharedDataPointer<ICalendarTodoPrivate> d_ptr;

};

} // namespace calendar
} // namespace pim
} // namespace bb

#endif // BB_PIM_CALENDAR_ICALENDARTODO_HPP

