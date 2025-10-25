/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_NOTIFICATIONGLOBALSETTINGS_HPP
#define BB_PLATFORM_NOTIFICATIONGLOBALSETTINGS_HPP

#include <bb/platform/Global>
#include <bb/platform/NotificationPolicy>
#include <bb/platform/NotificationMode>
#include <bb/platform/NotificationSettingsError>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{

namespace platform
{

class NotificationGlobalSettingsPrivate;

/*!
 * @headerfile NotificationGlobalSettings.hpp <bb/platform/NotificationGlobalSettings>
 *
 * @brief Provides access to persistent global notification settings.
 *
 * @details The @c NotificationGlobalSettings class provides methods to access and
 *          modify persistent global notification settings. Mutator methods in this
 *          class are protected by access permissions because they allow modification
 *          of global settings. Be sure to check the descriptions of individual methods,
 *          and ensure that the required permissions have been granted before using them.
 *
 *          The global notification settings are represented by a set of policies. These
 *          policies determine which effects may be triggered by the Notification system.
 *          Ultimately the Notification system will decide which effects actually get
 *          presented to the user based on a combination of an application's notification
 *          settings and the global notification settings (see @c bb::platform::NotificationApplicationSettings
 *          for more details).
 *
 * @permissions This class requires that the application be granted the
 *              @c access_notify_settings_control capability if it wants to modify global settings.
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
class BB_PLATFORM_EXPORT NotificationGlobalSettings: public QObject
{
    Q_OBJECT

    /*!
     * @brief Defines the global policy for sound effects.
     *
     * @details The sound setting determines if the Notification system may play a sound when notifying the user.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( bb::platform::NotificationPolicy::Type sound READ sound WRITE setSound NOTIFY soundChanged FINAL )

    /*!
     * @brief Defines the global policy for vibration effects.
     *
     * @details The vibrate setting determines if the Notification system may vibrate the device when notifying the user.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( bb::platform::NotificationPolicy::Type vibrate READ vibrate WRITE setVibrate NOTIFY vibrateChanged FINAL )

    /*!
     * @brief Defines the global policy for LED effects.
     *
     * @details The LED setting determines if the Notification system may flash the LED when notifying the user.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( bb::platform::NotificationPolicy::Type led READ led WRITE setLed NOTIFY ledChanged FINAL )

    /*!
     * @brief Defines the global policy for Instant Preview effects.
     *
     * @details The preview setting determines if the Notification system may display an Instant Preview when notifying the user.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( bb::platform::NotificationPolicy::Type preview READ preview WRITE setPreview NOTIFY previewChanged FINAL )

    /*!
     * @brief Defines the volume for sound effects.
     *
     * @details The volume is represented by an integer in the range [0,100].
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( int volume READ volume WRITE setVolume NOTIFY volumeChanged FINAL )

    /*!
     * @brief Defines the notification mode.
     *
     * @see @c bb::platform::NotificationMode for a list of possible modes.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( bb::platform::NotificationMode::Type mode READ mode WRITE setMode NOTIFY modeChanged FINAL )

public:
    /*!
     * @brief Constructs a new @c NotificationGlobalSettings instance.
     *
     * @param parent If not 0, the supplied parent will be responsible for deleting this instance.
     *
     * @since BlackBerry 10.2.0
     */
    explicit NotificationGlobalSettings(QObject* parent = 0);

    /*!
     * @brief Destroys the @c NotificationGlobalSettings instance.
     *
     * @since BlackBerry 10.2.0
     */
    virtual ~NotificationGlobalSettings();

    /*!
     * @brief Returns the global policy for sound effects.
     *
     * @return The policy for sound effects. The possible policies are:
     *         @li @c bb::platform::NotificationPolicy::Allow - the Notification system may play a sound
     *             when notifying the user.
     *         @li @c bb::platform::NotificationPolicy::Deny - the Notification system will not play a sound
     *             when notifying the user.
     *         @li @c bb::platform::NotificationPolicy::Unknown - the policy could not be determined at this time.
     *
     * @since BlackBerry 10.2.0
     */
    bb::platform::NotificationPolicy::Type sound() const;

    /*!
     * @brief Returns the global policy for vibration effects.
     *
     * @return The policy for vibration effects. The possible policies are:
     *         @li @c bb::platform::NotificationPolicy::Allow - the Notification system may vibrate the device
     *             when notifying the user.
     *         @li @c bb::platform::NotificationPolicy::Deny - the Notification system will not vibrate the device
     *             when notifying the user.
     *         @li @c bb::platform::NotificationPolicy::Unknown - the policy could not be determined at this time.
     *
     * @since BlackBerry 10.2.0
     */
    bb::platform::NotificationPolicy::Type vibrate() const;

    /*!
     * @brief Returns the global policy for LED effects.
     *
     * @return The policy for LED effects. The possible policies are:
     *         @li @c bb::platform::NotificationPolicy::Allow - the Notification system may flash the LED
     *             when notifying the user.
     *         @li @c bb::platform::NotificationPolicy::Deny - the Notification system will not flash the LED
     *             when notifying the user.
     *         @li @c bb::platform::NotificationPolicy::Unknown - the policy could not be determined at this time.
     *
     * @since BlackBerry 10.2.0
     */
    bb::platform::NotificationPolicy::Type led() const;

    /*!
     * @brief Returns the global policy for Instant Preview effects.
     *
     * @return The policy Instant Preview effects. The possible policies are:
     *         @li @c bb::platform::NotificationPolicy::Allow - the Notification system may display an Instant Preview
     *             when notifying the user.
     *         @li @c bb::platform::NotificationPolicy::Deny - the Notification system will not display an Instant Preview
     *             when notifying the user.
     *         @li @c bb::platform::NotificationPolicy::Unknown - the policy could not be determined at this time.
     *
     * @since BlackBerry 10.2.0
     */
    bb::platform::NotificationPolicy::Type preview() const;

    /*!
     * @brief Returns the volume for sound effects.
     *
     * @details The volume is an integer in the range [0,100].
     *
     * @return An integer in the range [0,100] or -1 if the volume could not be determined.
     *
     * @since BlackBerry 10.2.0
     */
    int volume() const;

    /*!
     * @brief Returns the notification mode.
     *
     * @see @c bb::platform::NotificationMode for a list of possible modes
     *
     * @return Returns the notification mode.
     *
     * @since BlackBerry 10.2.0
     */
    bb::platform::NotificationMode::Type mode() const;

    /*!
     * @brief Sets the global policy for sound effects.
     *
     * @details This method will only update the policy if the current
     *          notification mode allows it.
     *
     * @param policy The new policy for sound effects. Valid policies are:
     *              @li @c bb::platform::NotificationPolicy::Allow, which will allow the Notification system
     *                  to play a sound when notifying the user.
     *              @li @c bb::platform::NotificationPolicy::Deny, which will deny the Notification system
     *                  from playing a sound when notifying the user.
     *
     * @return @c bb::platform::NotitficationSettingsError::None, if the request was successful, or an error code
     *         otherwise. See @c bb::platform::NotificationSettingsError for the list of values.
     *
     * @permissions This function requires that the application be granted
     *              the @c access_notify_settings_control capability.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE bb::platform::NotificationSettingsError::Type setSound(bb::platform::NotificationPolicy::Type policy);

    /*!
     * @brief Sets the global policy for vibration effects.
     *
     * @details This method will only update the policy if the current
     *          notification mode allows it.
     *
     * @param policy The new policy for vibration effects. Valid policies are:
     *               @li @c bb::platform::NotificationPolicy::Allow, which will allow the Notification system
     *                   to vibrate the device when notifying the user.
     *               @li @c bb::platform::NotificationPolicy::Deny, which will deny the Notification system
     *                   from vibrating the device when notifying the user.
     *
     * @return @c bb::platform::NotitficationSettingsError::None, if the request was successful, or an error code
     *         otherwise. See @c bb::platform::NotificationSettingsError for the list of values.
     *
     * @permissions This function requires that the application be granted
     *              the @c access_notify_settings_control capability.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE bb::platform::NotificationSettingsError::Type setVibrate(bb::platform::NotificationPolicy::Type policy);

    /*!
     * @brief Sets the global policy for LED effects.
     *
     * @details This method will only update the policy if the current
     *          notification mode allows it.
     *
     * @param policy The new policy for LED effects. Valid policies are:
     *               @li @c bb::platform::NotificationPolicy::Allow, which will allow the Notification system
     *                   to flash the LED when notifying the user.
     *               @li @c bb::platform::NotificationPolicy::Deny, which will deny the Notification system
     *                   from flashing the LED when notifying the user.
     *
     * @return @c bb::platform::NotitficationSettingsError::None, if the request was successful, or an error code
     *         otherwise. See @c bb::platform::NotificationSettingsError for the list of values.
     *
     * @permissions This function requires that the application be granted
     *              the @c access_notify_settings_control capability.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE bb::platform::NotificationSettingsError::Type setLed(bb::platform::NotificationPolicy::Type policy);

    /*!
     * @brief Sets the global policy for Instant Preview effects.
     *
     * @details This method will only update the policy if the
     *          current notification mode allows it.
     *
     * @param policy The new global policy for Instant Preview effects. Valid policies are:
     *               @li @c bb::platform::NotificationPolicy::Allow, which will allow the Notification system to
     *                   display an Instant Preview when notifying the user.
     *               @li @c bb::platform::NotificationPolicy::Deny, which will deny the Notification system
     *                   from displaying an Instant Preview when notifying the user.
     *
     * @return @c bb::platform::NotitficationSettingsError::None, if the request was successful, or an error code
     *         otherwise. See @c bb::platform::NotificationSettingsError for the list of values.
     *
     * @permissions This function requires that the application be granted
     *              the @c access_notify_settings_control capability.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE bb::platform::NotificationSettingsError::Type setPreview(bb::platform::NotificationPolicy::Type policy);

    /*!
     * @brief Sets the volume for sound effects.
     *
     * @details The volume is an integer in the range [0,100].
     *
     * @param volume An integer in the range [0,100]. If the value is outside the valid range, it will be clamped to [0,100].
     *
     * @return @c bb::platform::NotitficationSettingsError::None, if the request was successful, or an error code
     *         otherwise. See @c bb::platform::NotificationSettingsError for the list of values.
     *
     * @permissions This function requires that the application be granted
     *              the @c access_notify_settings_control capability.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE bb::platform::NotificationSettingsError::Type setVolume(int volume);

    /*!
     * @brief Sets the notification mode.
     *
     * @see @c bb::platform::NotificationMode for a list of possible modes
     *
     * @return @c bb::platform::NotitficationSettingsError::None, if the request was successful, or an error code
     *         otherwise. See @c bb::platform::NotificationSettingsError for the list of values.
     *
     * @permissions This function requires that the application be granted
     *              the @c access_notify_settings_control capability.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE bb::platform::NotificationSettingsError::Type setMode(bb::platform::NotificationMode::Type mode);

Q_SIGNALS:
    /*!
     * @brief Emitted when the policy for the @c NotificationGlobalSettings::sound property changes.
     *
     * @param policy The new policy for the @c NotificationGlobalSettings::sound property.
     *
     * @since BlackBerry 10.2.0
     */
    void soundChanged(bb::platform::NotificationPolicy::Type policy);

    /*!
     * @brief Emitted when the policy for the @c NotificationGlobalSettings::vibrate property changes.
     *
     * @param policy The new policy for the @c NotificationGlobalSettings::vibrate property.
     *
     * @since BlackBerry 10.2.0
     */
    void vibrateChanged(bb::platform::NotificationPolicy::Type policy);

    /*!
     * @brief Emitted when the policy for the @c NotificationGlobalSettings::led property changes.
     *
     * @param policy The new policy for the @c NotificationGlobalSettings::led property.
     *
     * @since BlackBerry 10.2.0
     */
    void ledChanged(bb::platform::NotificationPolicy::Type policy);

    /*!
     * @brief Emitted when the policy for the @c NotificationGlobalSettings::preview property changes.
     *
     * @param policy The new policy for the @c NotificationGlobalSettings::preview property.
     *
     * @since BlackBerry 10.2.0
     */
    void previewChanged(bb::platform::NotificationPolicy::Type policy);

    /*!
     * @brief Emitted when the value of @c NotificationGlobalSettings::volume changes.
     *
     * @param volume The new volume for the @c NotificationGlobalSettings::volume property.
     *
     * @since BlackBerry 10.2.0
     */
    void volumeChanged(int volume);

    /*!
     * @brief Emitted when the @c NotificationGlobalSettings::mode changes.
     *
     * @param mode The new mode for the @c NotificationGlobalSettings::mode property.
     *
     * @since BlackBerry 10.2.0
     */
    void modeChanged(bb::platform::NotificationMode::Type mode);

protected:
//!@cond PRIVATE
    /*!
     * @brief Sets the policy for sound effects on a global level. This is used for QML.
     */
    Q_INVOKABLE int setSound(int policy);

    /*!
     * @brief Sets the policy for vibration effects on a global level. This is used for QML.
     */
    Q_INVOKABLE int setVibrate(int policy);

    /*!
     * @brief Sets the policy for led effects on a global level. This is used for QML.
     */
     Q_INVOKABLE int setLed(int policy);

    /*!
     * @brief Sets the policy for Instant Preview effects on a global level. This is used for QML.
     */
     Q_INVOKABLE int setPreview(int policy);

    /*!
     * @brief Sets the notification mode. This is used for QML.
     */
     Q_INVOKABLE int setMode(int mode);

    /*!
     * @brief Emitted when the policy for the @c NotificationGlobalSettings::sound property changes.
     *        This is used for QML.
     */
    Q_SIGNAL void soundChanged(int policy);

    /*!
     * @brief Emitted when the policy for the @c NotificationGlobalSettings::vibrate property changes.
     *        This is used for QML.
     */
    Q_SIGNAL void vibrateChanged(int policy);

    /*!
     * @brief Emitted when the policy @c NotificationGlobalSettings::led property changes.
     *        This is used for QML.
     */
    Q_SIGNAL void ledChanged(int policy);

    /*!
     * @brief Emitted when the policy for the @c NotificationGlobalSettings::preview property changes.
     *        This is used for QML.
     */
    Q_SIGNAL void previewChanged(int policy);

    /*!
     * @brief Emitted when the mode for the @c NotificationGlobalSettings::mode property changes.
     *        This is used for QML.
     */
    Q_SIGNAL void modeChanged(int mode);
//!@endcond
private:
//!@cond PRIVATE
    Q_DECLARE_PRIVATE(NotificationGlobalSettings)
    Q_DISABLE_COPY(NotificationGlobalSettings)
    NotificationGlobalSettingsPrivate * const d_ptr;
//!@endcond
};

} // namespace platform
} // namespace bb

QML_DECLARE_TYPE(bb::platform::NotificationGlobalSettings)
#endif // BB_PLATFORM_NOTIFICATIONGLOBALSETTINGS_HPP
