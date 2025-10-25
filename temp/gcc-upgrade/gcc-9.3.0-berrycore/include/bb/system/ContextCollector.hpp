/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */
//! @cond PRIVATE
#ifndef BB_SYSTEM_CONTEXTCOLLECTOR_HPP
#define BB_SYSTEM_CONTEXTCOLLECTOR_HPP

#include <bb/system/Global>
#include <bb/system/ContextActivityState>
#include <bb/system/ContextEvent>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace system
{

class ContextCollectorPrivate;

/*!
 * @headerfile ContextCollector.hpp <bb/system/ContextCollector>
 *
 * @brief A class for sending Context Collection events.
 *
 * @details The Context Collection Library (CCL) enables the collection of rich data about users in order to
 * provide a much more contextually aware, truly personalized user experience. The Context Collection Library (CCL)
 * enables you to collect and store this data so you can carry out deep, cross-application analysis, helping provide
 * insights that will allow RIM to create a highly relevant experience.
 *
 * @c %ContextCollector allocates memory when initialized, so you should try to reuse it when possible to reduce
 * the overhead. That being said, you can still create a new instance whenever you need to. Here's how to create
 * a new instance of @c %ContextCollector on the stack and set the app name and version.
 *
 * @snippet libbbsystem/CascadesContextTest/src/main.cpp context_event_cpp_1
 *
 * Once created, the @c %ContextCollector is enabled and ready to start sending events. You can check to
 * make sure that the object is initilaized correctly calling @c isValid(). Here's how to check the object's
 * validity, and create and trigger a custom @c ContextEvent.
 *
 * @snippet libbbsystem/CascadesContextTest/src/main.cpp context_event_cpp_2
 *
 * @c %ContextCollector can also be used within QML by adding it to a component's @c attachedObjects. Here's
 * how to create the @c ContextCollector and @c ContextEvent, and set the collector's app name and version.
 *
 * @snippet libbbsystem/CascadesContextTest/assets/main.qml context_event_qml_1
 *
 * The functions within @c ContextCollector and @c ContextEvent are all @c Q_INVOKABLE, so you can do everything
 * to create and trigger your events right within QML. Here's a @c Button that when clicked, creates and triggers
 * several different events and activities.
 *
 * @snippet libbbsystem/CascadesContextTest/assets/main.qml context_event_qml_2
 *
 * @permissions The application must have the @c access_cclagent_service permission to access this information.
 *
 * @xmlonly
 * <apigrouping group="Platform/Context collector"/>
 * <library name="bbsystem"/>
 * @endxmlonly 
 */
class BB_SYSTEM_EXPORT ContextCollector : public QObject
{
    Q_OBJECT

    /*!
     * @brief The name of the application sending events.
     */
    Q_PROPERTY(QString applicationName READ applicationName WRITE setApplicationName RESET resetApplicationName NOTIFY applicationNameChanged FINAL)

    /*!
     * @brief The version of the application sending events.
     */
    Q_PROPERTY(QString applicationVersion READ applicationVersion WRITE setApplicationVersion RESET resetApplicationVersion NOTIFY applicationVersionChanged FINAL)

public:
    /*!
     * @brief Constructs a @c ContextCollector object.
     *
     * @details The object will be invalid until the @c ContextCollector::applicationName and
     * @c ContextCollector::applicationVersion properties are set.
     *
     * @param parent If not @c 0, the supplied parent will be responsible for deleting this instance.
     */
    explicit ContextCollector(QObject *parent = 0);

    /*!
     * @brief Constructs a @c ContextCollector object with the provided application name and version.
     *
     * @details This constructor will become valid immediately if the supplied application name and version are valid.
     *
     * @param applicationName The name of the application sending events.
     * @param applicationVersion The version of the application sending events.
     * @param parent If not @c 0, the supplied parent will be responsible for deleting this instance.
     */
    explicit ContextCollector(const QString &applicationName, const QString &applicationVersion, QObject *parent = 0);

    /*!
     * @brief Destroys this @c ContextCollector object.
     */
    virtual ~ContextCollector();

    /*!
     * @brief Retrieves the application name.
     *
     * @return Returns the application name.
     */
    QString applicationName() const;

    /*!
     * @brief Retrieves the application version.
     *
     * @return Returns the application version.
     */
    QString applicationVersion() const;

    /*!
     * @brief Sends a custom event.
     *
     * @details This method collects data related to various custom application events. The calling application can use this
     * API to instrument various events in the application.
     *
     * @param eventName The name of the event to send.
     * @param event An optional event object containing additional key-value pairs.
     */
    Q_INVOKABLE void sendCustomEvent(const QString &eventName, bb::system::ContextEvent *event = 0);

    /*!
     * @brief Sends an event after an application error.
     *
     * @details This method collects data related to an application error. The calling application can use this
     * API to instrument various errors or exceptions in the application.
     *
     * @param errorMessage A description of the error.
     * @param event An optional event object containing additional key-value pairs.
     */
    Q_INVOKABLE void sendApplicationError(const QString &errorMessage, bb::system::ContextEvent *event = 0);

    /*!
     * @brief Sends an event after a search operation.
     *
     * @details This method collects data when a user searches within the application.  The calling application
     * can use this API to instrument search applications in the application.
     *
     * @param searchString The search text.
     * @param event An optional event object containing additional key-value pairs.
     */
    Q_INVOKABLE void sendSearchEvent(const QString &searchString, bb::system::ContextEvent *event = 0);

    /*!
     * @brief Sends an event marking activity states.
     *
     * @details This method collects data when an activity starts, pauses or ends.  The calling application can use
     * this API to instrument the state of various activities in the application.
     *
     * @param activityName The name of the activity.
     * @param state The state of the activity.  See @c bb::system::ContextActivityState for the list of valid states.
     * @param event An optional event object containing additional key-value pairs.
     */
    Q_INVOKABLE void sendActivity(const QString &activityName, bb::system::ContextActivityState::Type state, bb::system::ContextEvent *event = 0);

    /*!
     * @brief Sends an event after a button click.
     *
     * @details This method collects data when a user clicks an application button.  The calling application can use
     * this API to instrument button clicks in the application.
     *
     * @param event An optional event object containing additional key-value pairs.
     */
    Q_INVOKABLE void sendButtonClick(bb::system::ContextEvent *event = 0);

    /*!
     * @brief Sends an event when content is viewed.
     *
     * @details This method collects data when content (such as a screen, article, or image) is viewed.
     * The calling application can use this API to instrument data accesses in the application.
     *
     * @param event An optional event object containing additional key-value pairs.
     */
    Q_INVOKABLE void sendContentView(bb::system::ContextEvent *event = 0);

    /*!
     * @brief Sends an event when an advertisement is clicked.
     *
     * @details This method collects data when a user clicks an advertisement.  The calling application
     * can use this API to instrument accesses to advertisements in the application.
     *
     * @param adName The name of the advertisement.
     * @param event An optional event object containing additional key-value pairs.
     */
    Q_INVOKABLE void sendAdClick(const QString &adName, bb::system::ContextEvent *event = 0);

    /*!
     * @brief Sends an event after a conversion event.
     *
     * @details This method is used to collect data when a conversion event (such as a purchase) occurs.
     * The calling application can use this API to instrument conversion events in the application.
     *
     * @param conversionName The name of the conversion event.
     * @param event An optional event object containing additional key-value pairs.
     */
    Q_INVOKABLE void sendConversionEvent(const QString &conversionName, bb::system::ContextEvent *event = 0);

    /*!
     * @brief Sends a corporate-liable event.
     *
     * @details Corporate-liable events are special events that allow corporate-liable devices to track
     * conversations and transmissions for internal corporate legal purposes.
     * This event is just like a custom event except that it does not require consent and events are sent to the
     * corporate-liable store of the device.  These events are not sent to the Context Collection Server.
     *
     * @param eventName The name of the event to send.
     * @param event An optional event object containing additional key-value pairs.
     */
    Q_INVOKABLE void sendCorporateLiableEvent(const QString &eventName, bb::system::ContextEvent *event = 0);

public Q_SLOTS:

    /*!
     * @brief Sets the application name.
     *
     * @param applicationName The application name.
     */
    void setApplicationName(const QString& applicationName);

    /*!
     * @brief Sets the application version.
     *
     * @param applicationVersion The application version.
     */
    void setApplicationVersion(const QString& applicationVersion);

    /*!
     * @brief Resets the application name to @c QString::null
     */
    void resetApplicationName();

    /*!
     * @brief Resets the application version to @c QString::null
     */
    void resetApplicationVersion();

    /*!
     * @brief Checks if this object has been successfully initialized.
     *
     * @return @c true if this object is valid, @c false otherwise.
     */
    bool isValid() const;

    /*!
     * @brief Checks if this @c ContextCollector is enabled.
     *
     * @details Checks if the user has consented to send diagnostic and usage data to RIM.
     * This function should only be used for events that are expensive to create and send.
     *
     * @return @c true if enabled, @c false otherwise.
     */
    bool isEnabled() const;

Q_SIGNALS:
    /*!
     * @brief Emitted when the @c ContextCollector::applicationName property is changed programmatically.
     *
     * @param value The new value of the @c ContextCollector::applicationName property.
     */
    void applicationNameChanged(const QString &value);

    /*!
     * @brief Emitted when the @c ContextCollector::applicationVersion property is changed programmatically.
     *
     * @param value The new value of the @c ContextCollector::applicationVersion property.
     */
    void applicationVersionChanged(const QString &value);

protected:
    //! @cond PRIVATE
    Q_INVOKABLE void sendActivity(const QString &activityName, int state, bb::system::ContextEvent *event = 0);
    //! @endcond

private:
    //! @cond PRIVATE
    Q_DECLARE_PRIVATE(ContextCollector)
    Q_DISABLE_COPY(ContextCollector)
    QScopedPointer<ContextCollectorPrivate> const d_ptr;
    //! @endcond
};

} // namespace system
} // namespace bb

QML_DECLARE_TYPE(bb::system::ContextCollector)

#endif // BB_SYSTEM_CONTEXTCOLLECTOR_HPP
//! @endcond
