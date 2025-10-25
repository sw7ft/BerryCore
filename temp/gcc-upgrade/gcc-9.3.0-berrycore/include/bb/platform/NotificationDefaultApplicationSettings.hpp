/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_NOTIFICATIONDEFAULTAPPLICATIONSETTINGS_HPP
#define BB_PLATFORM_NOTIFICATIONDEFAULTAPPLICATIONSETTINGS_HPP

#include <bb/platform/Global>
#include <bb/platform/NotificationPolicy>
#include <bb/platform/NotificationSettingsError>
#include <bb/platform/NotificationPriorityPolicy>


namespace bb
{

namespace platform
{

class NotificationDefaultApplicationSettingsPrivate;

/*!
 * @headerfile NotificationDefaultApplicationSettings.hpp <bb/platform/NotificationDefaultApplicationSettings>
 *
 * @brief An application's default notification settings.
 *
 * @details This class should ONLY be used to change an application's default notification settings. The new
 *          settings can be specified by using the setter methods provided. The new settings will not be applied
 *          until @c apply() is called.
 *
 * @note If an application does not use this class to change its default notification settings,
 *       the default settings will be used and cannot be changed.
 *
 * @xmlonly
 * <apigrouping group="Platform/Notifications"/>
 * <library name="bbplatform"/>
 * @endxmlonly
 *
 * @see bb::platform::NotificationApplicationSettings
 *
 * @since BlackBerry 10.2.0
 */
class BB_PLATFORM_EXPORT NotificationDefaultApplicationSettings
{

public:
    /*!
     * @brief Constructs a new @c NotificationDefaultApplicationSettings instance.
     *
     * @since BlackBerry 10.2.0
     */
    NotificationDefaultApplicationSettings();

    /*!
     * @brief Destroys the @c NotificationDefaultApplicationSettings instance.
     *
     * @since BlackBerry 10.2.0
     */
    ~NotificationDefaultApplicationSettings();

    /*!
     * @brief Constructs a @c NotificationDefaultApplicationSettings as a copy of @c other.
     *
     * @param other The @c NotificationDefaultApplicationSettings to copy from.
     *
     * @since BlackBerry 10.2.0
     */
    NotificationDefaultApplicationSettings(const NotificationDefaultApplicationSettings &other);

    /*!
     * @brief Assigns the value of @c other to this @c NotificationDefaultApplicationSettings instance.
     *
     * @return The @c NotificationDefaultApplicationSettings instance.
     *
     * @since BlackBerry 10.2.0
     */
    NotificationDefaultApplicationSettings & operator=(const NotificationDefaultApplicationSettings &other);

    /*!
     * @brief Returns the sound effects policy for the @c NotificationDefaultApplicationSettings instance.
     *
     * @return @c bb::platform::NotificationPolicy::Type containing the policy for sound effects.
     *
     * @since BlackBerry 10.2.0
     */
    bb::platform::NotificationPolicy::Type sound() const;

    /*!
     * @brief Returns the vibration effects policy for the @c NotificationDefaultApplicationSettings instance.
     *
     * @return @c bb::platform::NotificationPolicy::Type containing the policy for vibration effects.
     *
     * @since BlackBerry 10.2.0
     */
    bb::platform::NotificationPolicy::Type vibrate() const;

    /*!
     * @brief Returns the LED effects policy for the @c NotificationDefaultApplicationSettings instance.
     *
     * @return @c bb::platform::NotificationPolicy::Type containing the policy for LED effects.
     *
     * @since BlackBerry 10.2.0
     */
    bb::platform::NotificationPolicy::Type led() const;

    /*!
     * @brief Returns the Instant Preview effects policy for the @c NotificationDefaultApplicationSettings instance.
     *
     * @return @c bb::platform::NotificationPriorityPolicy::Type containing the Instant Preview effects policy.
     *
     * @since BlackBerry 10.2.0
     */
    bb::platform::NotificationPriorityPolicy::Type preview() const;

    /*!
     * @brief Returns the vibration count for the @c NotificationDefaultApplicationSettings instance.
     *
     * @details The vibrate count is an integer in the range [1,5].
     *
     * @return An integer in the range [1,5] or -1 if the vibrate count has not been set.
     *
     * @since BlackBerry 10.2.0
     */
    int vibrateCount() const;

    /*!
     * @brief Returns the tone path for the @c NotificationDefaultApplicationSettings instance.
     *
     * @return A QUrl containing the tone path.
     *
     * @since BlackBerry 10.2.0
     */
    QUrl tonePath() const;

    /*!
     * @brief Sets the sound effects policy for the @c NotificationDefaultApplicationSettings instance.
     *
     * @details The new policy will not be applied until @c apply() is called.
     *
     * @param policy The new policy for sound effects. Valid policies are:
     *               @li @c bb::platform::NotificationPolicy::Allow, which will allow the Notification system
     *                   to play a sound when notifying the user.
     *               @li @c bb::platform::NotificationPolicy::Deny, which will deny the Notification system
     *                   from playing a sound when notifying the user.
     *
     * @since BlackBerry 10.2.0
     */
    void setSound(bb::platform::NotificationPolicy::Type policy);

    /*!
     * @brief Sets the vibration effects policy for the @c NotificationDefaultApplicationSettings instance.
     *
     * @details The new policy will not be applied until @c apply() is called.
     *
     * @param policy The new policy for vibration effects. Valid policies are:
     *               @li @c bb::platform::NotificationPolicy::Allow, which will allow the Notification system
     *                   to vibrate the device when notifying the user.
     *               @li @c bb::platform::NotificationPolicy::Deny, which will deny the Notification system
     *                   from vibrating the device when notifying the user.
     *
     * @since BlackBerry 10.2.0
     */
    void setVibrate(bb::platform::NotificationPolicy::Type policy);

    /*!
     * @brief Sets the LED effects policy for the @c NotificationDefaultApplicationSettings instance.
     *
     * @details The new policy will not be applied until @c apply() is called.
     *
     * @param policy The new policy for LED effects. Valid policies are:
     *               @li @c bb::platform::NotificationPolicy::Allow, which will allow the Notification system
     *                   to flash the LED when notifying the user.
     *               @li @c bb::platform::NotificationPolicy::Deny, which will deny the Notification system
     *                   from flashing the LED when notifying the user.
     *
     * @since BlackBerry 10.2.0
     */
    void setLed(bb::platform::NotificationPolicy::Type policy);

    /*!
     * @brief Sets the Instant Preview effects policy for the @c NotificationDefaultApplicationSettings instance.
     *
     * @details The new policy will not be applied until @c apply() is called.
     *
     * @param policy The new policy for Instant Preview effects. Valid policies are:
     *               @li @c bb::platform::NotificationPriorityPolicy::Allow - the Notification system may display
     *                   an Instant Preview for the notifications sent by an application.
     *               @li @c bb::platform::NotificationPriorityPolicy::Deny - the Notification system will not display
     *                   an Instant Preview for any notifications sent by an application.
     *               @li @c bb::platform::NotificationPriorityPolicy::NotApplicable - Instant Preview effects are not
     *                   applicable to an application, and the user setting will be hidden from the Application Settings UI.
     *                   This is the default for all applications that do not have a BlackBerry Hub account.
     *               @li @c bb::platform::NotificationPriorityPolicy::PriorityOnly - the Notification system may only display
     *                   an Instant Preview for notifications which come from a priority source.
     *
     * @since BlackBerry 10.2.0
     */
    void setPreview(bb::platform::NotificationPriorityPolicy::Type policy);

    /*!
     * @brief Sets the vibrate count of the @c NotificationDefaultApplicationSettings instance.
     *
     * @details The new vibration count will not be applied until @c apply() is called.
     *          The vibrate count is an integer in the range [1,5].
     *
     * @param count An integer in the range [1,5]. If the value is outside the valid range it will be clamped to [1,5].
     *
     * @since BlackBerry 10.2.0
     */
    void setVibrateCount(int count);

    /*!
     * @brief Sets the tone path of the @c NotificationDefaultApplicationSettings instance.
     *
     * @details This setting will not be applied until @c apply() is called. The @c tonePath must be specified
     *          as a file URI to a public asset or a shared asset on the device. A local asset can be changed to
     *          a public asset in the Assets tab of a project's bar-descriptor.xml.
     *
     * @param tonePath The new tone path.
     *
     * @since BlackBerry 10.2.0
     */
    void setTonePath(const QUrl &tonePath);

    /*!
     * @brief Updates the application's default notification settings.
     *
     * @details This method updates the application's default notification settings
     *          to those specified by this instance. The new settings will only be applied
     *          if the default settings haven't been modified already.
     *
     * @return @c bb::platform::NotificationSettingsError::None, if the request was successful, or an error code
     *         otherwise. See @c bb::platform::NotificationSettingsError for the list of values.
     *
     * @since BlackBerry 10.2.0
     */
     bb::platform::NotificationSettingsError::Type apply();
private:
//!@cond PRIVATE
    class NotificationDefaultApplicationSettingsPrivate;
    QSharedDataPointer<NotificationDefaultApplicationSettingsPrivate> d_ptr;
//!@endcond
};

} // namespace platform
} // namespace bb

#endif // BB_PLATFORM_NOTIFICATIONDEFAULTAPPLICATIONSETTINGS_HPP
