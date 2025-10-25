
/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_CALENDAR_BBMCONFERENCEUSERDATA_HPP
#define BB_PIM_CALENDAR_BBMCONFERENCEUSERDATA_HPP

#include <bb/pim/Global>
#include <bb/pim/calendar/DataTypes>
#include <QSharedDataPointer>
#include <QString>

namespace bb {
namespace pim {
namespace calendar {

class BbmConferenceUserDataPrivate;

/*!
 * @brief The @c BbmConferenceUserData class includes user data for a BBM conference call.
 *
 * @details This class contains user-defined information for a BBM conference call. This information
 * includes access code, moderator flag, and phone number.
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
class BB_PIM_EXPORT BbmConferenceUserData {
public:

    /*!
     * @brief Constructs a new @c BbmConferenceUserData.
     *
     * @since BlackBerry 10.0.0
     */
    BbmConferenceUserData();

    /*!
     * @brief Destroys this @c BbmConferenceUserData
     *
     * @since BlackBerry 10.0.0
     */
    ~BbmConferenceUserData();

    /*!
     * @brief Copy constructor.
     *
     * @details This function constructs a @c BbmConferenceUserData containing exactly the
     * same values as the provided @c %BbmConferenceUserData.
     *
     * @param other The @c %BbmConferenceUserData to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    BbmConferenceUserData(const BbmConferenceUserData& other);

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c BbmConferenceUserData
     * into this @c %BbmConferenceUserData.
     *
     * @param other The @c %BbmConferenceUserData from which to copy all values.
     *
     * @return A reference to this @c %BbmConferenceUserData.
     *
     * @since BlackBerry 10.0.0
     */
    BbmConferenceUserData& operator=(const BbmConferenceUserData& other);

    /*!
     * @brief Retrieves the access code of this conference.
     *
     * @details This function returns the access code that was selected by the user for this
     * conference.
     *
     * @return The user-selected access code.
     *
     * @since BlackBerry 10.0.0
     */
    QString accessCode() const;

    /*!
     * @brief Retrieves the moderator code of this conference.
     *
     * @details This function returns the moderator code that was selected by the user for
     * this conference.
     *
     * @return The user-selected moderator code.
     *
     * @since BlackBerry 10.3.0
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
     * @brief Retrieves the phone number of this conference.
     *
     * @details This function returns the phone number that was selected by the user for
     * this conference.
     *
     * @return The user-selected phone number.
     *
     * @since BlackBerry 10.0.0
     */
    QString phoneNumber() const;

    /*!
     * @brief Sets the access code of this conference.
     *
     * @param accessCode The new access code.
     *
     * @since BlackBerry 10.0.0
     */
    void setAccessCode(const QString& accessCode);

    /*!
     * @brief Sets the moderator code of this conference.
     *
     * @param moderatorCode The new moderator code.
     *
     * @since BlackBerry 10.3.0
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
     * @brief Sets the phone number for this conference.
     *
     * @param phoneNumber The new phone number.
     *
     * @since BlackBerry 10.0.0
     */
    void setPhoneNumber(const QString& phoneNumber);

    /*!
     * @brief Indicates whether this @c BbmConferenceUserData is valid.
     *
     * @details This function determines whether the attributes of this @c %BbmConferenceUserData
     * object have acceptable values.
     *
     * @return @c true if this @c %BbmConferenceUserData is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

private:
    QSharedDataPointer<BbmConferenceUserDataPrivate> d_ptr;

};

} // namespace calendar
} // namespace pim
} // namespace bb

#endif // BB_PIM_CALENDAR_BBMCONFERENCEUSERDATA_HPP

