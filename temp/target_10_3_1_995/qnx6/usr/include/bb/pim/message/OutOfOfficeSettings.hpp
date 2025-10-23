/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2014
 * Research In Motion Limited. All rights reserved.
 */
#ifndef BB_PIM_MESSAGE_OUT_OF_OFFICE_SETTINGS_HPP
#define BB_PIM_MESSAGE_OUT_OF_OFFICE_SETTINGS_HPP

#include <bb/Global>
#include <bb/pim/Global>

#include <QDateTime>
#include <QSharedDataPointer>

namespace bb {
namespace pim {
namespace message {

class OutOfOfficeSettingsPrivate;

/*!
 * @brief The @c OutOfOfficeSettings class includes information about out-of-office replies
 * for messages.
 * 
 * @details You can use this class to set the Out of Office option, and you can specify
 * the text to use as the out-of-office reply message.
 *
 * @xmlonly
 * <apigrouping group="App Integration/Message"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */

class BB_PIM_EXPORT OutOfOfficeSettings
{
public:
    /*!
     * @brief Constructs a new @c OutOfOfficeSettings.
     *
     * @details By default, the constructor creates an object that has the out-of-office disabled,
     * with no text (either general or external) and no schedule.
     *
     * @since BlackBerry 10.0.0
     */
    OutOfOfficeSettings();

    /*!
     * @brief Destroys this @c OutOfOfficeSettings.
     *
     * @since BlackBerry 10.0.0
     */
    ~OutOfOfficeSettings();

    /*!
     * @brief Constructs a new @c OutOfOfficeSettings with the provided state and text.
     * 
     * @details The state is an integer that should be either 0 (to disable the
     * out-of-office option) or 1 (to enable the out-of-office option). The provided
     * text is used as the out-of-office reply.
     * 
     * @param state The state of the out-of-office option (either 0 or 1).
     * @param text The out-of-office reply text.
     *
     * @since BlackBerry 10.0.0
     */
    OutOfOfficeSettings(int state, const QString& text);

    //!@cond PRIVATE
    explicit OutOfOfficeSettings(OutOfOfficeSettingsPrivate* outOfOfficeSettingsPrivate);
    //@endcond

    /*!
     * @brief Copy constructor.
     * 
     * @details This function constructs an @c OutOfOfficeSettings containing exactly the same values as
     * the provided @c %OutOfOfficeSettings.
     * 
     * @param other The @c %OutOfOfficeSettings to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    OutOfOfficeSettings(const OutOfOfficeSettings &other);


    /*!
     * @brief Assignment operator.
     * 
     * @details This operator copies all values from the provided @c OutOfOfficeSettings into this
     * @c %OutOfOfficeSettings.
     * 
     * @param other The @c %OutOfOfficeSettings from which to copy all values.
     *
     * @return An @c %OutOfOfficeSettings with all copied data.
     *
     * @since BlackBerry 10.0.0
     */
    OutOfOfficeSettings& operator=(const OutOfOfficeSettings &other);

    /*!
     * @brief Retrieves whether out-of-office notifications are enabled for this @c OutOfOfficeSettings.
     *
     * @details This function returns 1 (equivalent to @c true) if automatic replies are enabled or 0 otherwise (no automatic
     * replies are sent).
     *
     * @return The state of out-of-office automatic replies (either 0 or 1).
     *
     * @since BlackBerry 10.0.0
     */
    int isEnabled() const;

    /*!
     * @brief Sets the enabled state of this @c OutOfOfficeSettings.
     *
     * @details The provided state should either be @c true (if automatic replies are enabled) or @c false
     * (no automatic replies are sent).
     *
     * @param newState The desired state for the out-of-office notifications.
     *
     * @since BlackBerry 10.3.1
     */
    void setEnabled(bool newState);

    //!@cond PRIVATE
    /*!
     * @brief This function has been deprecated.
     *
     * @details The provided state should be either 0 (to disable the out-of-office option)
     * or 1 (to enable the out-of-office option).
     *
     * @deprecated BlackBerry 10.3.1. Use @c OutOfOfficeSettings::setEnabled().
     *
     * @param state The new state of the out-of-office option (either 0 or 1).
     *
     * @since BlackBerry 10.0.0
     */
    void setState(int state) BB_DEPRECATED;
    //@endcond

    /*!
     * @brief Retrieves the out-of-office reply text of this @c OutOfOfficeSettings.
     *
     * @return The text of the automatic reply notifications.
     *
     * @since BlackBerry 10.3.1
     */

    QString text() const;

    //!@cond PRIVATE
    /*!
     * @brief This function has been deprecated.
     *
     * @deprecated BlackBerry 10.3.1. Use @c OutOfOfficeSettings::text().
     *
     * @since BlackBerry 10.0.0
     */

    QString Text() const BB_DEPRECATED;
    //@endcond

    /*!
     * @brief Sets the out-of-office reply text of this @c OutOfOfficeSettings.
     *
     * @param text The new out-of-office reply text.
     *
     * @since BlackBerry 10.0.0
     */
    void setText(const QString& text);

    /*!
     * @brief Retrieves the state of the external notifications of this @c OutOfOfficeSettings.
     *
     * @details For servers that support external recipient notifications, these can be turned
     * on or off independently from the general state of out-of-office notifications. If the
     * general state of out-of-office notifications is off, no notifications will be sent to any
     * recipients, regardless of the external state.
     *
     * @return @c true if the external out-of-office option is enabled, @c false otherwise.
     *
     * @since BlackBerry 10.3.1
     */
    bool isExternalEnabled() const;

    /*!
     * @brief Sets the state for the external notifications of this @c OutOfOfficeSettings.
     *
     * @details For servers that support it, external notifications can be assigned a separate text
     * and state. This state works in conjunction with the external notification text set with the
     * @c OutOfOfficeSettings::setExternalText() function. If the external text is empty, the state
     * will not be effective and no notifications will be sent to external recipients.
     *
     * @param externalState If @c true external out-of-office notifications are enabled, if @c false
     * external out-of-office notifications are disabled.
     *
     * @since BlackBerry 10.3.1
     */

    void setExternalEnabled(bool externalState);

    /*!
     * @brief Retrieves the out-of-office reply text for external recipients of this @c OutOfOfficeSettings.
     *
     * @details If the server has the capability to send different out-of-office messages to internal and external
     * recipients, this function will return the message for external recipients. If the server does not have the
     * capability to send a different external message, the message in @c OutOfOfficeSettings::text() is
     * sent to external recipients and the value of @c OutOfOfficeSettings::externalText() should be disregarded.
     *
     * @return The text of the automatic reply notifications that will be sent to external recipients.
     *
     * @since BlackBerry 10.3.1
     */

    QString externalText() const;

    /*!
     * @brief Sets the out-of-office reply text specifically for external recipients for this @c OutOfOfficeSettings.
     *
     * @details If the server has the capability to send different out-of-office messages to internal and external
     * recipients, this function should be used to set a different message for external recipients.
     * If the value for the external text is left empty, the external recipients will not receive any notifications.
     * If the server does not support different out-of-office messages for internal and external recipients, the
     * notification sent to external recipients will be the same as that for internal recipients, regardless of the
     * value set here.
     *
     * @param text The new external out-of-office reply text.
     *
     * @since BlackBerry 10.3.1
     */

    void setExternalText(const QString& text);

    /*!
     * @brief Retrieves the start of the scheduled time during which the out-of-office reply will be sent to recipients
     * for this @c OutOfOfficeSettings.
     *
     * @details If the server has the capability to enable a schedule during which out-of-office messages
     * are sent, and the schedule has been set, this function will return the start time.
     *
     * @return The start date and time of the interval during which out-of-office messages will be sent.
     * If the schedule is not enabled, the @c QDateTime value returned will not be valid.
     *
     * @since BlackBerry 10.3.1
     */

    QDateTime scheduleStart() const;

    /*!
     * @brief Retrieves the end of the scheduled time during which the out-of-office reply will be sent to recipients
     * for this @c OutOfOfficeSettings.
     *
     * @details If the server has the capability to enable a schedule during which out-of-office messages
     * are sent, and the schedule has been set, this function will return the end time.
     *
     * @return The end date and time of the interval during which out-of-office messages will be sent.
     * If the schedule is not enabled, the @c QDateTime value returned will not be valid.
     *
     * @since BlackBerry 10.3.1
     */

    QDateTime scheduleEnd() const;

    /*!
     * @brief Sets the scheduled time during which the out-of-office reply will be sent to recipients
     * for this @c OutOfOfficeSettings.
     *
     * @details If the server has the capability to enable a schedule during which out-of-office messages
     * are sent, this function should be used to set the schedule start and end time. Out-of-office notifications
     * must be enabled by calling the @c OutOfOfficeSettings::setState() function or the schedule will have no effect.
     * If either the @c startTime or @c endTime is invalid, the @c endTime is before the @c startTime, or the
     * @c endTime is in the past, the schedule will not be enabled.
     *
     * @param startTime The start date and time of the interval during which out-of-office messages will be sent.
     * @param endTime The end date and time of the interval during which out-of-office messages will be sent.
     *
     * @since BlackBerry 10.3.1
     */

    void setSchedule(const QDateTime& startTime, const QDateTime& endTime);

    /*!
     * @brief Disables the scheduling of out-of-office notifications for this @c OutOfOfficeSettings.
     *
     * @details This function will remove any out-of-office schedule and leave the notifications in either
     * the enabled or disabled state. It will clear the start and end time values.
     *
     * @since BlackBerry 10.3.1
     */

    void clearSchedule();

    /*!
     * @brief Indicates whether this @c OutOfOfficeSettings is valid.
     * 
     * @details The validity of the @c OutOfOfficeSettings only applies to an @c OutOfOfficeSettings
     * object returned by the @c MessageService::outOfOffice() function. In that case, the validity will
     * be set based on whether the message provider was able to obtain valid out-of-office settings
     * from the server.
     *
     * @return @c true if this @c %OutOfOfficeSettings is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

private:
    QSharedDataPointer<OutOfOfficeSettingsPrivate> d_ptr;

};


} /* namespace message */
} /* namespace pim */
} /* namespace bb */


#endif // BB_PIM_MESSAGE_OUT_OF_OFFICE_SETTINGS_HPP
