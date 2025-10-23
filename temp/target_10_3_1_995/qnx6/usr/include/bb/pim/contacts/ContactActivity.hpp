/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */
#ifndef BB_PIM_CONTACTS_CONTACTACTIVITY_HPP
#define BB_PIM_CONTACTS_CONTACTACTIVITY_HPP

#include <bb/pim/Global>
#include <QSharedDataPointer>
#include <QDateTime>
#include <QString>


namespace bb {
namespace pim {
namespace contacts {
class ContactService;
class ContactActivityPrivate;

/*!
 * @brief The @c ContactActivity class represents an interaction with a @c Contact object.
 * 
 * @details A @c %ContactActivity is linked to a particular @c %Contact, and represents an interaction with that
 * @c %Contact using an email, phone call, or calendar event. For example, a @c %ContactActivity might represent receiving
 * a phone call from a particular contact in a user's Contacts application.
 * 
 * You can retrieve a list of @c %ContactActivity objects for a @c %Contact by using the @c ContactService.
 * 
 * @see Contact, ContactService
 *
 * @xmlonly
 * <apigrouping group="App Integration/Contacts"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT ContactActivity
{
public:
    /*!
     * @brief Constructs a new @c ContactActivity.
     *
     * @since BlackBerry 10.0.0
     */
    ContactActivity();

    /*!
     * @brief Destroys this @c ContactActivity.
     *
     * @since BlackBerry 10.0.0
     */
    ~ContactActivity();

    /*!
     * @brief Copy constructor.
     * 
     * @details This function constructs a @c ContactActivity containing exactly the same values as the provided
     * @c %ContactActivity.
     * 
     * @param copy The @c %ContactActivity to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    ContactActivity(const ContactActivity& copy);

    /*!
     * @brief Assignment operator.
     * 
     * @details This operator copies all values from the provided @c ContactActivity into this @c %ContactActivity.
     * 
     * @param operand The @c %ContactActivity from which to copy all values.
     *
     * @return A @c %ContactActivity with all copied data
     *
     * @since BlackBerry 10.0.0
     */
    ContactActivity& operator=(const ContactActivity& operand);
    
    /*!
     * @brief Retrieves the MIME type of this @c ContactActivity.
     * 
     * @details An example of a MIME type of an activity is "email". Using the MIME type, you can determine the
     * appropriate service to retrieve the object that's associated with the contact.
     * 
     * @return The MIME type of this @c %ContactActivity.
     *
     * @since BlackBerry 10.0.0
     */
    QString mimeType() const;

    /*!
     * @brief Indicates the direction of this @c ContactActivity.
     *
     * @return @c true if the direction of the activity is incoming, @c false if the direction is outgoing.
     *
     * @since BlackBerry 10.0.0
     */
    bool direction() const;

    /*!
     * @brief Retrieves the activity ID of this @c ContactActivity.
     * 
     * @details You can use the activity ID, along with the account ID and MIME type, to retrieve the object that
     * caused this activity.
     * 
     * @return The activity ID of this @c %ContactActivity.
     *
     * @since BlackBerry 10.0.0
     */
    int id() const;

    /*!
     * @brief Retrieves the account ID of this @c ContactActivity.
     * 
     * @details The account ID determines which account this @c %ContactActivity belongs to. You can use the account ID
     * to retrieve the details for the activity.
     * 
     * @return The account ID of this @c %ContactActivity.
     *
     * @since BlackBerry 10.0.0
     */
    int accountId() const;

    /*!
     * @brief Retrieves the description of this @c ContactActivity.
     * 
     * @details The description provides additional information depending on the source of the activity:
     * - For messages, the description is the subject of the message.
     * - For phone calls, the description is the phone number.
     * - For calendar events, the description is the subject of the event.
     * 
     * @return The description of this @c %ContactActivity.
     *
     * @since BlackBerry 10.0.0
     */
    QString description() const;

    /*!
     * @brief Retrieves the time stamp that's associated with this @c ContactActivity.
     * 
     * @return The date and time of this @c %ContactActivity.
     *
     * @since BlackBerry 10.0.0
     */
    QDateTime statusTimeStamp() const;
    
private:
    QSharedDataPointer<ContactActivityPrivate> d_ptr;
    friend class ContactActivityPrivate;
};

/**
 * QList<ContactActivity>
 */
typedef QList<ContactActivity> ContactActivityList;

} // namespace contacts
} // namespace pim
} // namespace bb

#endif // BB_PIM_CONTACTS_CONTACTACTIVITY_HPP
