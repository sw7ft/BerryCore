/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_NOTIFICATIONAPPLICATIONSETTINGS_HPP
#define BB_PLATFORM_NOTIFICATIONAPPLICATIONSETTINGS_HPP

#include <bb/platform/Global>
#include <bb/platform/NotificationPolicy>
#include <bb/platform/NotificationPriorityPolicy>

#include <QObject>
#include <QUrl>
#include <QtDeclarative/QtDeclarative>

namespace bb
{

namespace platform
{

class NotificationApplicationSettingsPrivate;

/*!
 * @headerfile NotificationApplicationSettings.hpp <bb/platform/NotificationApplicationSettings>
 *
 * @brief Provides methods to read an application's persistent notification settings.
 *
 * @details The @c NotificationApplicationSettings class provides methods to read an application's
 *          notification settings. The settings themselves are set by the end user.
 *
 *          An application's notification settings are represented by a set of policies. These policies
 *          determine which effects (such as playing a sound, vibrating the device, flashing the LED, and so on) may be
 *          triggered when the Notification system wants to notify the user. Ultimately the Notification system will
 *          decide which effects actually get presented to the user based on a combination of an application's notification
 *          settings and the global notification settings.
 *
 *          The role of the notification settings are as such:
 *
 *          @li SOUND   If the global setting for sound effects is set to "allow", then an application setting may
 *                      override the global setting to "deny". If the global setting is set to "deny" then the
 *                      application setting will have no effect.
 *
 *          @li VIBRATE If the global setting for vibration effects is set to "allow", then an application setting may
 *                      override the global setting to "deny". If the global setting is set to "deny" then the application
 *                      setting will have no effect.
 *
 *          @li LED     If the global setting for LED effects is set to "allow", then an application setting may override the
 *                      global setting to "deny". If the global setting is set to "deny" then the application setting will have
 *                      no effect.
 *
 *          @li PREVIEW If the global setting for Instant Preview effects is set to "allow", then an application setting may
 *                      override the global setting to "deny". The application setting may also be set to "priority only",
 *                      in which case the Notification system will only display Instant Previews for notifications coming
 *                      from priority sources. If the application setting is set to "not applicable", then Instant Preview
 *                      effects are not applicable to the application and the user setting will be hidden in the Application
 *                      Settings UI. If the global setting is set to "deny" then the application setting will have no effect.
 *
 *          @li ALERTS  If alerts are "enabled", then the settings will behave as described above. If alerts are "disabled",
 *                      then no effects will be triggered, regardless of other notification settings.
 *
 *          An application may use @c NotificationDefaultApplicationSettings to perform a one time change
 *          of its initial settings from the defaults set by the Notification system. If you do not change the
 *          initial settings, the defaults set by the Notification system will be used and cannot be changed.
 *
 * @xmlonly
 * <apigrouping group="Platform/Notifications"/>
 * <library name="bbplatform"/>
 * @endxmlonly
 *
 * @see @c bb::platform::NotificationDefaultApplicationSettings, @c bb::platform::NotificationGlobalSettings
 *
 * @since BlackBerry 10.2.0
 */
class BB_PLATFORM_EXPORT NotificationApplicationSettings: public QObject
{
    Q_OBJECT

    /*!
     * @brief Defines whether notifications sent by an application will trigger any effects.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( bool  alertsEnabled READ alertsEnabled NOTIFY alertsEnabledChanged FINAL )

    /*!
     * @brief Defines an application's policy for sound effects.
     *
     * @details The sound setting determines if the Notification system may play a sound when notifying the user.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( bb::platform::NotificationPolicy::Type sound READ sound NOTIFY soundChanged FINAL )

    /*!
     * @brief Defines an application's policy for vibration effects.
     *
     * @details The vibrate setting determines if the Notification system may vibrate the device
     *          when notifying the user.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( bb::platform::NotificationPolicy::Type vibrate READ vibrate NOTIFY vibrateChanged FINAL )

    /*!
     * @brief Defines an application's policy for LED effects.
     *
     * @details The LED setting determines if the Notification system may flash the LED when notifying
     *          the user.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( bb::platform::NotificationPolicy::Type led READ led NOTIFY ledChanged FINAL )

    /*!
     * @brief Defines an application's policy for Instant Preview effects.
     *
     * @details The preview setting determines if the Notification system may display an Instant Preview
     *          when notifying the user.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( bb::platform::NotificationPriorityPolicy::Type preview READ preview NOTIFY previewChanged FINAL )

    /*!
     * @brief Defines the number of times vibration effects will be played.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( int vibrateCount READ vibrateCount NOTIFY vibrateCountChanged FINAL )

    /*!
     * @brief Defines the path to the tone that should be played for sound effects.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( QUrl tonePath READ tonePath NOTIFY tonePathChanged FINAL )

public:
    /*!
     * @brief Constructs a new @c NotificationApplicationSettings instance.
     *
     * @param parent If not 0, the supplied parent will be responsible for deleting this instance.
     *
     * @since BlackBerry 10.2.0
     */
    explicit NotificationApplicationSettings(QObject* parent = 0);

    /*!
     * @brief Destroys the @c NotificationApplicationSettings instance.
     *
     * @since BlackBerry 10.2.0
     */
    virtual ~NotificationApplicationSettings();

    /*!
     * @brief Returns whether notifications sent by an application may trigger any effects.
     *
     * @return @c true if effects may be triggered by notifications sent from an application
     *         @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool alertsEnabled() const;

    /*!
     * @brief Returns an application's policy for sound effects.
     *
     * @return The policy for sound effects. Possible policies are:
     *         @li @c bb::platform::NotificationPolicy::Allow - the Notification system may play a sound
     *             for the notifications sent by an application.
     *         @li @c bb::platform::NotificationPolicy::Deny - the Notification system will not play a sound
     *             for any notifications sent by an application.
     *         @li @c bb::platform::NotificationPolicy::Unknown - the policy could not be determined at this time.
     *
     * @since BlackBerry 10.2.0
     */
    bb::platform::NotificationPolicy::Type sound() const;

    /*!
     * @brief Returns an application's policy for vibration effects.
     *
     * @return The policy for vibration effects. Possible policies are:
     *         @li @c bb::platform::NotificationPolicy::Allow - the Notification system may vibrate the device
     *             for the notifications sent by an application.
     *         @li @c bb::platform::NotificationPolicy::Deny - the Notification system will not vibrate the device
     *             for any notifications sent by an application.
     *         @li @c bb::platform::NotificationPolicy::Unknown - the policy could not be determined at this time.
     *
     * @since BlackBerry 10.2.0
     */
    bb::platform::NotificationPolicy::Type vibrate() const;

    /*!
     * @brief Returns an application's policy for LED effects.
     *
     * @return The policy for LED effects. Possible policies are:
     *         @li @c bb::platform::NotificationPolicy::Allow - the Notification system may flash the
     *             LED for the notifications sent by an application.
     *         @li @c bb::platform::NotificationPolicy::Deny - the Notification system will not flash the
     *             LED for any notifications sent by an application.
     *         @li @c bb::platform::NotificationPolicy::Unknown - the policy could not be determined at this time.
     *
     * @since BlackBerry 10.2.0
     */
    bb::platform::NotificationPolicy::Type led() const;

    /*!
     * @brief Returns an application's policy for Instant Preview effects.
     *
     * @return The policy for Instant Preview effects. Possible policies are:
     *         @li @c bb::platform::NotificationPriorityPolicy::Allow - the Notification system may display an
     *             Instant Preview for the notifications sent by an application.
     *         @li @c bb::platform::NotificationPriorityPolicy::Deny - the Notification system will not display an
     *             Instant Preview for any notifications sent by an application.
     *         @li @c bb::platform::NotificationPriorityPolicy::NotApplicable - Instant Preview effects are not
     *             applicable to an application, and the user setting will be hidden from the Application Settings UI.
     *             This is the default for all applications that do not have a BlackBerry Hub account.
     *         @li @c bb::platform::NotificationPriorityPolicy::PriorityOnly - the Notification system may only display an
     *             Instant Preview for notifications which come from a priority source.
     *         @li @c bb::platform::NotificationPriorityPolicy::Unknown - the policy could not be determined at this time.
     *
     * @since BlackBerry 10.2.0
     */
    bb::platform::NotificationPriorityPolicy::Type preview() const;

    /*!
     * @brief Returns the number of times a vibration effect will be played.
     *
     * @details The vibrate count is an integer in the range [1,5].
     *
     * @return An integer in the range [1,5] or -1 if the vibrate count could not be determined.
     *
     * @since BlackBerry 10.2.0
     */
    int vibrateCount() const;

    /*!
     * @brief Returns the path to the tone that will be played for an application's sound notifications.
     *
     * @return A QUrl containing the tone path.
     *
     * @since BlackBerry 10.2.0
     */
    QUrl tonePath() const;

Q_SIGNALS:
    /*!
     * @brief Emitted when the state of @c NotificationApplicationSettings::alertsEnabled changes.
     *
     * @param state The new state for the @c NotificationApplicationSettings::alertsEnabled property.
     *
     * @since BlackBerry 10.2.0
     */
    void alertsEnabledChanged(bool enabled);

    /*!
     * @brief Emitted when the policy for the @c NotificationApplicationSettings::sound property changes.
     *
     * @param policy The new policy for the @c NotificationApplicationSettings::sound property.
     *
     * @since BlackBerry 10.2.0
     */
    void soundChanged(bb::platform::NotificationPolicy::Type  policy);

    /*!
     * @brief Emitted when the policy for the @c NotificationApplicationSettings::vibrate property changes.
     *
     * @param policy The new policy for the @c NotificationApplicationSettings::vibrate property.
     *
     * @since BlackBerry 10.2.0
     */
    void vibrateChanged(bb::platform::NotificationPolicy::Type policy);

    /*!
     * @brief Emitted when the policy for the @c NotificationApplicationSettings::led property changes.
     *
     * @param policy The new policy for the @c NotificationApplicationSettings::led property.
     *
     * @since BlackBerry 10.2.0
     */
    void ledChanged(bb::platform::NotificationPolicy::Type policy);

    /*!
     * @brief Emitted when the policy for the @c NotificationApplicationSettings::preview property changes.
     *
     * @param policy The new policy for the @c NotificationApplicationSettings::preview property.
     *
     * @since BlackBerry 10.2.0
     */
    void previewChanged(bb::platform::NotificationPriorityPolicy::Type policy);

    /*!
     * @brief Emitted when the value for the @c NotificationApplicationSettings::vibrateCount property changes.
     *
     * @param count The new value for the @c NotificationApplicationSettings::vibrateCount property.
     *
     * @since BlackBerry 10.2.0
     */
    void vibrateCountChanged(int count);

    /*!
     * @brief Emitted when the value for the @c NotificationApplicationSettings::tonePath property changes.
     *
     * @param tonePath The new path for the @c NotificationApplicationSettings::tonePath property.
     *
     * @since BlackBerry 10.2.0
     */
    void tonePathChanged(const QUrl &tonePath);

protected:
//!@cond PRIVATE
    /*!
     * @brief Emitted when the policy for the @c NotificationApplicationSettings::sound property changes.
     *        This is used for QML.
     */
    Q_SIGNAL void soundChanged(int policy);

    /*!
     * @brief Emitted when the policy for the @c NotificationApplicationSettings::vibrate property changes.
     *        This is used for QML.
     */
    Q_SIGNAL void vibrateChanged(int policy);

    /*!
     * @brief Emitted when the policy for the @c NotificationApplicationSettings::led changes.
     *       This is used for QML.
     */
    Q_SIGNAL void ledChanged(int policy);

    /*!
     * @brief Emitted when the policy for the @c NotificationApplicationSettings::preview changes.
     *        This is used for QML.
     */
    Q_SIGNAL void previewChanged(int policy);
//!@endcond
private:
//!@cond PRIVATE
    Q_DECLARE_PRIVATE(NotificationApplicationSettings)
    Q_DISABLE_COPY(NotificationApplicationSettings)
    NotificationApplicationSettingsPrivate * const d_ptr;
//!@endcond
};

} // namespace platform
} // namespace bb

QML_DECLARE_TYPE(bb::platform::NotificationApplicationSettings)
#endif // BB_PLATFORM_NOTIFICATIONAPPLICATIONSETTINGS_HPP
