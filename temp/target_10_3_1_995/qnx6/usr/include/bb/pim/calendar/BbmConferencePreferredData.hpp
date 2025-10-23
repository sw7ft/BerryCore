
/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_CALENDAR_BBMCONFERENCEPREFERREDDATA_HPP
#define BB_PIM_CALENDAR_BBMCONFERENCEPREFERREDDATA_HPP

#include <bb/pim/Global>
#include <bb/pim/calendar/DataTypes>
#include <QSharedDataPointer>
#include <QString>

namespace bb {
namespace pim {
namespace calendar {

class BbmConferencePreferredDataPrivate;

/*!
 * @brief The @c BbmConferencePreferredData class includes data for a BBM conference call.
 *
 * @details This class contains conference call information that's discovered by the BBM conference
 * module. This information includes access code, moderator code, and so on.
 * 
 * @see BbmConference
 * 
 * @xmlonly
 * <apigrouping group="App Integration/Calendar"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT BbmConferencePreferredData {
public:

    /*!
     * @brief Constructs a new @c BbmConferencePreferredData.
     *
     * @since BlackBerry 10.0.0
     */
    BbmConferencePreferredData();

    /*!
     * @brief Destroys this @c BbmConferencePreferredData.
     *
     * @since BlackBerry 10.0.0
     */
    ~BbmConferencePreferredData();

    /*!
     * @brief Copy constructor.
     *
     * @details This function constructs a @c BbmConferencePreferredData containing exactly the
     * same values as the provided @c %BbmConferencePreferredData.
     *
     * @param other The @c %BbmConferencePreferredData to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    BbmConferencePreferredData(const BbmConferencePreferredData& other);

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c BbmConferencePreferredData
     * into this @c %BbmConferencePreferredData.
     *
     * @param other The @c %BbmConferencePreferredData from which to copy all values.
     *
     * @return A reference to this @c %BbmConferencePreferredData.
     *
     * @since BlackBerry 10.0.0
     */
    BbmConferencePreferredData& operator=(const BbmConferencePreferredData& other);

    /*!
     * @brief Retrieves the access code of this conference.
     *
     * @return The access code.
     *
     * @since BlackBerry 10.0.0
     */
    QString accessCode() const;

    /*!
     * @brief Retrieves the access code for the moderator of this conference.
     *
     * @return The moderator access code.
     *
     * @since BlackBerry 10.0.0
     */
    QString moderatorCode() const;

    /*!
     * @brief Indicates whether the current user is the moderator of this conference.
     *
     * @return @c true if the current user is the moderator, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isModerator() const;

    /*!
     * @brief Retrieves the access code for participants of this conference.
     *
     * @return The participant access code.
     *
     * @since BlackBerry 10.0.0
     */
    QString participantCode() const;

    /*!
     * @brief Retrieves the phone number for this conference.
     *
     * @return The phone number.
     *
     * @since BlackBerry 10.0.0
     */
    QString phoneNumber() const;


    /*!
     * @brief Sets the access code for this conference.
     *
     * @param accessCode The new access code.
     *
     * @since BlackBerry 10.0.0
     */
    void setAccessCode(const QString& accessCode);

    /*!
     * @brief Sets the moderator access code for this conference.
     *
     * @param moderatorCode The new moderator access code.
     *
     * @since BlackBerry 10.0.0
     */
    void setModeratorCode(const QString& moderatorCode);

    /*!
     * @brief Sets whether the current user is the moderator of this conference.
     *
     * @param moderator If @c true the current user is the moderator, if @c false the current
     * user is not the moderator.
     *
     * @since BlackBerry 10.0.0
     */
    void setModerator(bool moderator);

    /*!
     * @brief Sets the participant access code for this conference.
     *
     * @param participantCode The new participant access code.
     *
     * @since BlackBerry 10.0.0
     */
    void setParticipantCode(const QString& participantCode);

    /*!
     * @brief Sets the phone number for this conference.
     *
     * @param phoneNumber The new phone number.
     *
     * @since BlackBerry 10.0.0
     */
    void setPhoneNumber(const QString& phoneNumber);

    /*!
     * @brief Indicates whether this @c BbmConferencePreferredData is valid.
     *
     * @details This function determines whether the attributes of this @c %BbmConferencePreferredData
     * object have acceptable values.
     *
     * @return @c true if this @c %BbmConferencePreferredData is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

private:
    QSharedDataPointer<BbmConferencePreferredDataPrivate> d_ptr;

};

} // namespace calendar
} // namespace pim
} // namespace bb

#endif // BB_PIM_CALENDAR_BBMCONFERENCEPREFERREDDATA_HPP

