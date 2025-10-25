
/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_CALENDAR_ONLINECONFERENCEDATA_HPP
#define BB_PIM_CALENDAR_ONLINECONFERENCEDATA_HPP

#include <bb/pim/Global>
#include <QSharedDataPointer>
#include <QString>

namespace bb {
namespace pim {
namespace calendar {

class OnlineConferenceDataPrivate;

/*!
 * @brief The @c OnlineConferenceData class includes data for an online conference call.
 *
 * @details This class contains conference call information received from an external
 * application that provides online conference calls.
 *
 * @xmlonly
 * <apigrouping group="App Integration/Calendar"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.3.0
 */
class BB_PIM_EXPORT OnlineConferenceData {
public:

    /*!
     * @brief Constructs a new @c OnlineConferenceData.
     *
     * @since BlackBerry 10.3.0
     */
    OnlineConferenceData();

    /*!
     * @brief Destroys this @c OnlineConferenceData.
     *
     * @since BlackBerry 10.3.0
     */
    ~OnlineConferenceData();

    /*!
     * @brief Copy constructor.
     *
     * @details This function constructs a @c OnlineConferenceData containing exactly the
     * same values as the provided @c %OnlineConferenceData.
     *
     * @param other The @c %OnlineConferenceData to be copied.
     *
     * @since BlackBerry 10.3.0
     */
    OnlineConferenceData(const OnlineConferenceData& other);

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c OnlineConferenceData
     * into this @c %OnlineConferenceData.
     *
     * @param other The @c %OnlineConferenceData from which to copy all values.
     *
     * @return A reference to this @c %OnlineConferenceData.
     *
     * @since BlackBerry 10.3.0
     */
    OnlineConferenceData& operator=(const OnlineConferenceData& other);

    /*!
     * @brief Retrieves the site name for this conference.
     *
     * @return The site name.
     *
     * @since BlackBerry 10.3.0
     */
    QString siteName() const;

    /*!
     * @brief Retrieves the meeting key for this conference.
     *
     * @return The meeting key.
     *
     * @since BlackBerry 10.3.0
     */
    QString meetingKey() const;

    /*!
     * @brief Retrieves the conference identifier for this conference.
     *
     * @return The conference identifier.
     *
     * @since BlackBerry 10.3.0
     */
    QString conferenceId() const;

    /*!
     * @brief Retrieves the user name for this conference.
     *
     * @return The user name.
     *
     * @since BlackBerry 10.3.0
     */
    QString userName() const;

    /*!
     * @brief Sets the site name for this conference.
     *
     * @param siteName The new site name.
     *
     * @since BlackBerry 10.3.0
     */
    void setSiteName(const QString& siteName);

    /*!
     * @brief Sets the meeting key for this conference.
     *
     * @param meetingKey The new meeting key.
     *
     * @since BlackBerry 10.3.0
     */
    void setMeetingKey(const QString& meetingKey);

    /*!
     * @brief Sets the conference identifier for this conference.
     *
     * @param conferenceId The new conference identifier.
     *
     * @since BlackBerry 10.3.0
     */
    void setConferenceId(const QString& conferenceId);

    /*!
     * @brief Sets the user name for this conference.
     *
     * @param userName The user name.
     *
     * @since BlackBerry 10.3.0
     */
    void setUserName(const QString& userName);

    /*!
     * @brief Indicates whether this @c OnlineConferenceData is valid.
     *
     * @details This function determines whether the attributes of
     * this @c %OnlineConferenceData object have acceptable values.
     *
     * @return @c True if this @c %OnlineConferenceData is valid, @c false otherwise.
     *
     * @since BlackBerry 10.3.0
     */
    bool isValid() const;

private:
    QSharedDataPointer<OnlineConferenceDataPrivate> d_ptr;
};

} /* namespace calendar */
} /* namespace pim */
} /* namespace bb */

#endif /* BB_PIM_CALENDAR_ONLINECONFERENCEDATA_HPP */
