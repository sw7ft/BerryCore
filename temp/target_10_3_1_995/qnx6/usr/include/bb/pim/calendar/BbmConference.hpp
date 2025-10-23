
/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_CALENDAR_BBMCONFERENCE_HPP
#define BB_PIM_CALENDAR_BBMCONFERENCE_HPP

#include <bb/pim/Global>
#include <bb/pim/calendar/DataTypes>
#include <QSharedDataPointer>
#include <QList>
#include <QStringList>

namespace bb {
namespace pim {
namespace calendar {

class BbmConferenceBridgeData;
class BbmConferenceEventData;
class BbmConferencePreferredData;
class BbmConferenceUserData;
class BbmConferencePrivate;

/*!
 * @brief The @c BbmConference class provides data for BBM conference calls.
 *
 * @details This class contains information for a BBM conference call that's associated with
 * an event. This information includes phone labels (such as "US toll-free" and "Canada toll-
 * free"), phone numbers, and participant data.
 *
 * @see BbmConferencePreferredData, BbmConferenceUserData
 * 
 * @xmlonly
 * <apigrouping group="App Integration/Calendar"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT BbmConference {
public:

    /*!
     * @brief Constructs a new @c BbmConference.
     *
     * @since BlackBerry 10.0.0
     */
    BbmConference();

    /*!
     * @brief Destroys this @c BbmConference.
     *
     * @since BlackBerry 10.0.0
     */
    ~BbmConference();

    /*!
     * @brief Copy constructor.
     *
     * @details This function constructs a @c BbmConference containing exactly the
     * same values as the provided @c %BbmConference.
     *
     * @param other The @c %BbmConference to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    BbmConference(const BbmConference& other);

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c BbmConference
     * into this @c %BbmConference.
     *
     * @param other The @c %BbmConference from which to copy all values.
     *
     * @return A reference to this @c %BbmConference.
     *
     * @since BlackBerry 10.0.0
     */
    BbmConference& operator=(const BbmConference& other);

    /*!
     * @brief Retrieves the list of phone labels for this @c BbmConference.
     *
     * @details A phone label is used to indicate the type of a phone number. You can use
     * the following phone labels:
     * - 0: US toll-free
     * - 1: Canada toll-free
     * - 2: other toll-free
     * - 3: internal number
     * - 4: local number
     * - 5: direct number
     * - 6: other
     * - 7: UK toll-free
     * 
     * The values for phone labels are aligned with the elements that are returned from the
     * @c phoneNumbers() function. The first value from @c phoneLabels() is the type for
     * the first phone number from @c %phoneNumbers(), the second value is the second phone
     * number's type, and so on.
     *
     * @return The list of phone labels for this @c %BbmConference.
     *
     * @since BlackBerry 10.0.0
     */
    QStringList phoneLabels() const;

    /*!
     * @brief Retrieves the list of phone numbers for this @c BbmConference.
     *
     * @details This function returns the list of available phone numbers for this
     * @c %BbmConference object.
     *
     * @return The list of phone numbers for this @c %BbmConference.
     *
     * @since BlackBerry 10.0.0
     */
    QStringList phoneNumbers() const;

    /*!
     * @brief Retrieves the preferred conference data for this @c BbmConference.
     *
     * @details This function returns the call parameters that were parsed from the details
     * field in the event. These parameters include information such as access code and
     * participant code.
     *
     * @return The preferred conference data for this @c %BbmConference.
     *
     * @since BlackBerry 10.0.0
     */
    BbmConferencePreferredData preferredData() const;

    /*!
     * @brief Retrieves the conference user data for this @c BbmConference.
     *
     * @details This function returns the call parameters that were selected by the user.
     * These parameters include information such as access code and moderator flag.
     *
     * @return The conference user data for this @c %BbmConference.
     *
     * @since BlackBerry 10.0.0
     */
    BbmConferenceUserData userData() const;

    /*!
     * @brief Retrieves the event conference data for this @c BbmConference.
     *
     * @details This function returns the call parameters that were parsed from the details
     * field in the event. These parameters include information such as moderator code and
     * participant code.
     *
     * @return The event conference data for this @c %BbmConference.
     *
     * @since BlackBerry 10.2.0
     */
    BbmConferenceEventData eventData() const;

    /*!
     * @brief Retrieves the conference bridge for this @c BbmConference.
     *
     * @details A conference bridge contains information about available phone numbers,
     * mapped per country, moderator access code, and participants access code.
     * The information contained in the @c BbmConferenceBridgeData class
     * is already available in the following accessors of the @c BbmConference class:
     * @c eventData(), @c preferredData(), and @c userData(), as well as the methods
     * @c phoneNumbers() and @c setPhoneNumbers().
     * Please use these instead as the @c BbmConferenceBridgeData class will be deprecated.
     *
     * @return The conference bridge for this @c %BbmConference.
     *
     * @since BlackBerry 10.2.0
     */
    BbmConferenceBridgeData bridgeData() const;

    /*!
     * @brief Adds a new phone label to this @c BbmConference.
     *
     * @details This function appends a phone label to the list of existing phone labels
     * for this @c %BbmConference.
     *
     * @param phoneLabel The phone label to add.
     *
     * @since BlackBerry 10.0.0
     */
    void addPhoneLabel(const QString& phoneLabel);

    /*!
     * @brief Clears the phone labels for this @c BbmConference.
     *
     * @details This function removes all phone labels from this @c %BbmConference
     * object.
     *
     * @since BlackBerry 10.0.0
     */
    void resetPhoneLabels();

    /*!
     * @brief Sets the list of phone labels for this @c BbmConference.
     *
     * @details This function clears the list of phone labels for this @c %BbmConference
     * object and then populates it with phone labels from the provided list.
     *
     * @param phoneLabels The new list of phone labels.
     *
     * @since BlackBerry 10.0.0
     */
    void setPhoneLabels(const QStringList& phoneLabels);

    /*!
     * @brief Adds a phone number to this @c BbmConference.
     *
     * @details This function appends a new phone number to the list of phone number for this
     * @c %BbmConference object.
     *
     * @param phoneNumber The phone number to add.
     *
     * @since BlackBerry 10.0.0
     */
    void addPhoneNumber(const QString& phoneNumber);

    /*!
     * @brief Clears the phone numbers for this @c BbmConference.
     *
     * @details This function removes all phone numbers from this @c %BbmConference
     * object.
     *
     * @since BlackBerry 10.0.0
     */
    void resetPhoneNumbers();

    /*!
     * @brief Sets the list of phone numbers for this @c BbmConference.
     *
     * @details This function clears the list of phone numbers for this @c %BbmConference
     * object and then populates it with phone numbers from the provided list.
     *
     * @param phoneNumbers The new list of phone numbers.
     *
     * @since BlackBerry 10.0.0
     */
    void setPhoneNumbers(const QStringList& phoneNumbers);

    /*!
     * @brief Sets the preferred conference data for this @c BbmConference.
     *
     * @param preferredData The new preferred conference data.
     *
     * @since BlackBerry 10.0.0
     */
    void setPreferredData(const BbmConferencePreferredData& preferredData);

    /*!
     * @brief Sets the event conference data for this @c BbmConference.
     *
     * @param preferredData The new event conference data.
     *
     * @since BlackBerry 10.2.0
     */
    void setEventData(const BbmConferenceEventData& eventData);

    /*!
     * @brief Sets the conference user data for this @c BbmConference.
     *
     * @param userData The new user conference data.
     *
     * @since BlackBerry 10.0.0
     */
    void setUserData(const BbmConferenceUserData& userData);

    /*!
     * @brief Sets the conference bridge for this @c BbmConference.
     *
     * @details The information contained in the @c BbmConferenceBridgeData class
     * is already available in the following accessors of the @c BbmConference class:
     * @c eventData(), @c preferredData(), and @c userData(), as well as the methods
     * @c phoneNumbers() and @c setPhoneNumbers().
     * Please use these instead as the @c BbmConferenceBridgeData class will be deprecated.

     * @param bridgeData The new user conference bridge.
     *
     * @since BlackBerry 10.2.0
     */
    void setBridgeData(const BbmConferenceBridgeData& bridgeData);

    /*!
     * @brief Indicates whether this @c BbmConference is valid.
     *
     * @details This function determines whether the attributes of this @c %BbmConference
     * object have acceptable values.
     *
     * @return @c true if this @c %BbmConference is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

private:
    QSharedDataPointer<BbmConferencePrivate> d_ptr;

};

} // namespace calendar
} // namespace pim
} // namespace bb

#endif // BB_PIM_CALENDAR_BBMCONFERENCE_HPP

