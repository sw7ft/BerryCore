
/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_CALENDAR_NOTIFICATION_HPP
#define BB_PIM_CALENDAR_NOTIFICATION_HPP

#include <bb/pim/Global>
#include <bb/pim/calendar/DataTypes>
#include <QSharedDataPointer>
#include <QList>
#include <QString>
#include <QStringList>

namespace bb {
namespace pim {
namespace calendar {

class NotificationPrivate;

/*!
 * @brief The @c Notification class represents an email notification that's sent to the
 * participants of a meeting.
 *
 * @details This class contains data for a notification email that's sent to the
 * participants of a created, changed, or cancelled meeting. This class includes 
 * information such as added and deleted participants that will be notified, user
 * comments, and account ID.
 * 
 * @xmlonly
 * <apigrouping group="App Integration/Calendar"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT Notification {
public:

    /*!
     * @brief Constructs a new @c Notification.
     *
     * @since BlackBerry 10.0.0
     */
    Notification();

    /*!
     * @brief Destroys this @c Notification.
     *
     * @since BlackBerry 10.0.0
     */
    ~Notification();

    /*!
     * @brief Copy constructor.
     *
     * @details This function constructs a @c Notification containing exactly the
     * same values as the provided @c %Notification.
     *
     * @param other The @c %Notification to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    Notification(const Notification& other);

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c Notification
     * into this @c %Notification.
     *
     * @param other The @c %Notification from which to copy all values.
     *
     * @return A reference to this @c %Notification.
     *
     * @since BlackBerry 10.0.0
     */
    Notification& operator=(const Notification& other);

    /*!
     * @brief Retrieves the user comments for this @c Notification.
     *
     * @details This function returns the comments by the user on the meeting that was
     * created, changed, or cancelled.
     *
     * @return The user comments for this @c %Notification.
     *
     * @since BlackBerry 10.0.0
     */
    QString comments() const;

    /*!
     * @brief Retrieves the account ID for this @c Notification.
     *
     * @details This function returns the ID for the calendar account containing the
     * event referred to by the notification.
     *
     * @return The account ID for this @c %Notification.
     *
     * @since BlackBerry 10.0.0
     */
    AccountId accountId() const;

    /*!
     * @brief Indicates whether this @c Notification should be sent to all participants.
     *
     * @return @c true if the notification should be sent to all participants of the
     * meeting, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isNotifyAll() const;

    /*!
     * @brief Retrieves the messaging account ID for this @c Notification.
     *
     * @details This function returns the identifier of the messaging account to be used
     * to send the notification.
     *
     * @return The messaging account ID for this @c %Notification.
     *
     * @since BlackBerry 10.0.0
     */
    AccountId messageAccountId() const;

    /*!
     * @brief Retrieves the added participants that will be notified by this
     * @c Notification.
     *
     * @details This function returns the list of participants that were added to the
     * meeting, to whom the notification will be sent.
     *
     * @return The added participants.
     *
     * @since BlackBerry 10.0.0
     */
    QStringList newAttendeeEmails() const;

    /*!
     * @brief Retrieves the removed participants that will be notified by this
     * @c Notification.
     *
     * @details This function returns the list of participants that were removed from the
     * meeting, to whom the notification will be sent.
     *
     * @return The removed participants.
     *
     * @since BlackBerry 10.0.0
     */
    QStringList deletedAttendeeEmails() const;


    /*!
     * @brief Sets the user comments for this @c Notification.
     *
     * @param comments The new user comments.
     *
     * @since BlackBerry 10.0.0
     */
    void setComments(const QString& comments);

    /*!
     * @brief Sets the account ID for this @c Notification.
     *
     * @param accountId The new account ID.
     *
     * @since BlackBerry 10.0.0
     */
    void setAccountId(AccountId accountId);

    /*!
     * @brief Sets whether this @c Notification should be sent to all participants.
     *
     * @param notifyAll If @c true the notification is sent to all participants, if
     * @c false the notification is not sent to all participants.
     *
     * @since BlackBerry 10.0.0
     */
    void setNotifyAll(bool notifyAll);

    /*!
     * @brief Sets the messaging account ID for this @c Notification.
     *
     * @param messageAccountId The new messaging account ID.
     *
     * @since BlackBerry 10.0.0
     */
    void setMessageAccountId(AccountId messageAccountId);

    /*!
     * @brief Adds a new attendee to this @c Notification.
     *
     * @details This function appends a new attendee to the existing list of new
     * attendees.
     *
     * @param newAttendeeEmail The new attendee to add.
     *
     * @since BlackBerry 10.0.0
     */
    void addNewAttendeeEmail(const QString& newAttendeeEmail);

    /*!
     * @brief Removes all new attendees from this @c Notification.
     *
     * @since BlackBerry 10.0.0
     */
    void resetNewAttendeeEmails();

    /*!
     * @brief Sets the list of new attendees for this @c Notification.
     *
     * @details This function replaces the current list of new attendees with the
     * provided list.
     *
     * @param newAttendeeEmails The new list of new attendees.
     *
     * @since BlackBerry 10.0.0
     */
    void setNewAttendeeEmails(const QStringList& newAttendeeEmails);

    /*!
     * @brief Adds a deleted attendee to this @c Notification.
     *
     * @details This function appends a deleted attendee to the existing list of
     * deleted attendees.
     *
     * @param deletedAttendeeEmail The deleted attendee to add.
     *
     * @since BlackBerry 10.0.0
     */
    void addDeletedAttendeeEmail(const QString& deletedAttendeeEmail);

    /*!
     * @brief Removes all deleted attendees from this @c Notification.
     *
     * @since BlackBerry 10.0.0
     */
    void resetDeletedAttendeeEmails();

    /*!
     * @brief Sets the list of deleted attendees for this @c Notification.
     *
     * @details This function replaces the current list of deleted attendees with the
     * provided list.
     *
     * @param deletedAttendeeEmails The new list of deleted attendees.
     *
     * @since BlackBerry 10.0.0
     */
    void setDeletedAttendeeEmails(const QStringList& deletedAttendeeEmails);

    /*!
     * @brief Indicates whether this @c Notification is valid.
     *
     * @details This function determines whether the attributes of this @c %Notification
     * object have acceptable values.
     *
     * @return @c true if this @c %Notification is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

private:
    QSharedDataPointer<NotificationPrivate> d_ptr;

};

} // namespace calendar
} // namespace pim
} // namespace bb

#endif // BB_PIM_CALENDAR_NOTIFICATION_HPP

