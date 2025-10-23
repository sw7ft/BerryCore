
/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_CALENDAR_ATTENDEE_HPP
#define BB_PIM_CALENDAR_ATTENDEE_HPP

#include <bb/pim/Global>
#include <bb/pim/calendar/DataTypes>
#include <bb/pim/calendar/AttendeeRole>
#include <bb/pim/calendar/AttendeeStatus>
#include <QSharedDataPointer>
#include <QString>

namespace bb {
namespace pim {
namespace calendar {

class AttendeePrivate;

/*!
 * @brief The @c Attendee class represents a participant of a meeting.
 *
 * @details This class includes information about a meeting participant, such as the attendee type,
 * name, email address, and so on. This class also includes information such as whether the attendee
 * is the owner of the meeting, whether the attendee has accepted or declined the meeting invitation,
 * and other meeting-related information.
 * 
 * You can retrieve a list of an event's participants by calling @c CalendarEvent::attendees(). This
 * function returns a list of @c %Attendee objects, each of which corresponds to a participant of the
 * event.
 * 
 * @see CalendarEvent
 * 
 * @xmlonly
 * <apigrouping group="App Integration/Calendar"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT Attendee {
public:

    /*!
     * @brief An enumeration of supported attendee types.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief Indicates an invalid attendee type.
         *
         * @since BlackBerry 10.0.0
         */
        Invalid = 0,
        /*!
         * @brief Indicates that the attendee is hosting the meeting.
         *
         * @since BlackBerry 10.0.0
         */
        Host = 1,
        /*!
         * @brief Indicates that the attendee is a participant in the meeting.
         *
         * @since BlackBerry 10.0.0
         */
        Participant = 2,
    };

    /*!
     * @brief Constructs a new @c Attendee.
     *
     * @since BlackBerry 10.0.0
     */
    Attendee();

    /*!
     * @brief Destroys this @c Attendee.
     *
     * @since BlackBerry 10.0.0
     */
    ~Attendee();

    /*!
     * @brief Copy constructor.
     *
     * @details This function constructs an @c Attendee containing exactly the same values as the
     * provided @c %Attendee.
     *
     * @param other The @c %Attendee to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    Attendee(const Attendee& other);

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c Attendee into this
     * @c %Attendee.
     *
     * @param other The @c %Attendee from which to copy all values.
     *
     * @return A reference to this @c %Attendee.
     *
     * @since BlackBerry 10.0.0
     */
    Attendee& operator=(const Attendee& other);

    /*!
     * @brief Retrieves the email address of this @c Attendee.
     *
     * @return The email address of this @c %Attendee.
     *
     * @since BlackBerry 10.0.0
     */
    QString email() const;

    /*!
     * @brief Retrieves the name of this @c Attendee.
     *
     * @return The name of this @c %Attendee.
     *
     * @since BlackBerry 10.0.0
     */
    QString name() const;

    /*!
     * @brief Retrieves the type of this @c Attendee.
     *
     * @details An attendee can either be the host of a meeting (indicated by @c Attendee::Host) or
     * a participant of a meeting (indicated by @c Attendee::Participant).
     *
     * @return The type of this @c %Attendee.
     *
     * @since BlackBerry 10.0.0
     */
    Attendee::Type type() const;

    /*!
     * @brief Retrieves the role of this @c Attendee.
     *
     * @details This function returns the participation role of this attendee. An attendee can be:
     * - the chair of the meeting (@c AttendeeRole::Chair)
     * - required in the meeting (@c AttendeeRole::ReqParticipant)
     * - optional (@c AttendeeRole::OptParticipant)
     * - listed for information purposes only (@c AttendeeRole::NonParticipant)
     *
     * @return The role of this @c %Attendee.
     * 
     * @see AttendeeRole
     *
     * @since BlackBerry 10.0.0
     */
    AttendeeRole::Type role() const;

    /*!
     * @brief Retrieves the ID of this @c Attendee.
     *
     * @details The ID uniquely identifies an @c %Attendee.
     *
     * @return The ID of this @c %Attendee.
     *
     * @since BlackBerry 10.0.0
     */
    AttendeeId id() const;

    /*!
     * @brief Retrieves the event ID of this @c Attendee.
     *
     * @details The event ID identifies the event in which this attendee participates.
     *
     * @return The event ID of this @c %Attendee.
     *
     * @since BlackBerry 10.0.0
     */
    EventId eventId() const;

    /*!
     * @brief Retrieves the contact ID of this @c Attendee.
     *
     * @details The contact ID identifies the contact that this @c %Attendee object represents.
     * An @c %Attendee object can exist without a corresponding contact.
     *
     * @return The contact ID of this @c %Attendee.
     *
     * @since BlackBerry 10.0.0
     */
    ContactId contactId() const;

    /*!
     * @brief Retrieves the acceptance status of this @c Attendee.
     *
     * @details This function indicates the attendance status of the attendee, such as whether the
     * attendee:
     * - has confirmed their presence (@c AttendeeStatus::Accepted)
     * - has refused the meeting request (@c AttendeeStatus::Declined)
     * - will attempt to attend (@c AttendeeStatus::Tentative)
     * - has not yet responded (@c AttendeeStatus::NotResponded)
     *
     * @return The acceptance status of this @c %Attendee.
     *
     * @since BlackBerry 10.0.0
     */
    AttendeeStatus::Type status() const;

    /*!
     * @brief Indicates whether this @c Attendee represents the current user.
     *
     * @return @c true if this @c %Attendee represents the current user, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isOwner() const;

    /*!
     * @brief RSVP flag for attendees in an iCalendar attachment.
     *
     * @return @c true if the meeting organizer requires a response from this @c %Attendee.
     *
     * @since BlackBerry 10.2.0
     */
    bool rsvp() const;


    /*!
     * @brief Sets the email address of this @c Attendee.
     *
     * @param email The new email address.
     *
     * @since BlackBerry 10.0.0
     */
    void setEmail(const QString& email);

    /*!
     * @brief Sets the name of this @c Attendee.
     *
     * @param name The new name.
     *
     * @since BlackBerry 10.0.0
     */
    void setName(const QString& name);

    /*!
     * @brief Sets the type of this @c Attendee.
     *
     * @param type The new type.
     *
     * @since BlackBerry 10.0.0
     */
    void setType(Attendee::Type type);

    /*!
     * @brief Sets the role of this @c Attendee.
     *
     * @param role The new role.
     *
     * @since BlackBerry 10.0.0
     */
    void setRole(AttendeeRole::Type role);

    /*!
     * @brief Sets the ID of this @c Attendee.
     *
     * @param id The new ID.
     *
     * @since BlackBerry 10.0.0
     */
    void setId(AttendeeId id);

    /*!
     * @brief Sets the event ID of this @c Attendee.
     *
     * @param eventId The new event ID.
     *
     * @since BlackBerry 10.0.0
     */
    void setEventId(EventId eventId);

    /*!
     * @brief Sets the contact ID of this @c Attendee.
     *
     * @param contactId The new contact ID.
     *
     * @since BlackBerry 10.0.0
     */
    void setContactId(ContactId contactId);

    /*!
     * @brief Sets the acceptance status of this @c Attendee.
     *
     * @param status The new acceptance status.
     *
     * @since BlackBerry 10.0.0
     */
    void setStatus(AttendeeStatus::Type status);

    /*!
     * @brief Sets whether this @c Attendee represents the current user.
     *
     * @param owner If @c true this @c %Attendee represents the current user, if @c false
     * this @c %Attendee does not represent the current user.
     *
     * @since BlackBerry 10.0.0
     */
    void setOwner(bool owner);

    /*!
     * @brief Sets the RSVP flag on this @c Attendee.
     *
     * @param rsvp The new flag value.
     *
     * @since BlackBerry 10.2.0
     */
    void setRsvp(bool rsvp);

    /*!
     * @brief Indicates whether this @c Attendee is valid.
     *
     * @details This function determines whether the attributes of this @c %Attendee object have
     * acceptable values.
     *
     * @return @c true if this @c %Attendee is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

private:
    QSharedDataPointer<AttendeePrivate> d_ptr;

};

} // namespace calendar
} // namespace pim
} // namespace bb

#endif // BB_PIM_CALENDAR_ATTENDEE_HPP

