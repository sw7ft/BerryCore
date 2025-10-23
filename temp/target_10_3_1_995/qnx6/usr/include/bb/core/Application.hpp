/*!
 * @copyright
 * Copyright Research In Motion Limited, 2011-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CORE_APPLICATION_HPP
#define BB_CORE_APPLICATION_HPP

#include <bb/IconBadge>
#include <bb/ProcessState>
#include <bb/Global>
#include <QCoreApplication>
#include <QObject>
#include <QScopedPointer>
#include <QString>
#include <QUrl>
#include <QtDeclarative/QtDeclarative>

namespace bb {

class ApplicationPrivate;
class Event;

/*!
 * @headerfile Application.hpp <bb/Application>
 *
 * @brief The @c %Application class is used as the basis for your own custom application. This
 * class provides a simple set of wrappers for the lifecycle events
 * that you will need during the execution of your application.
 *
 * @details This class is used by non-Cascades applications, or applications providing their own UI framework functionality. If you are creating a GUI
 * application, you should use the @c bb::cascades::Application class.
 *
 * Only one instance of the @c %Application class should be used in your application.
 *
 * Example usage in C++
 * @include libbb/Application_constructor.cpp
 *
 * @xmlonly
 * <apigrouping group="Platform/Home screen"/>
 * <library name="bb"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_CORE_EXPORT Application : public QCoreApplication
{
    Q_OBJECT

    /*!
     * @brief The auto exit flag, for controlling the behavior of an exiting application.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bool autoExit READ autoExit WRITE setAutoExit NOTIFY autoExitChanged FINAL)
public:

    /*!
     * @brief Initializes a new instance of the @c %Application class.
     *
     * @details Normal usage of the constructor expects the @c argc and @c argv from @c main() to be passed in. These
     * values will be made available through the @c QCoreApplication::arguments() method.
     *
     * Constructing an @c %Application object in C++
     * @snippet libbb/Application_constructor.cpp All
     *
     * It is not possible to create an instance of this class in QML. Instead, an instance of
     * this class must be created in C++ and exported to QML with the @c QmlDocument::setContextProperty()
     * method. For Cascades applications, the @c bb::cascades::Application object returned by the method
     * @c bb::cascades::Application::instance() is automatically exported to QML as a context property
     * using the property name @c Application. Since @c %bb::cascades::Application is a subclass of this
     * class, all methods, signals, and slots can be used via this property. All QML examples in this
     * documentation will assume the presence of a property named @c Application that provides access to
     * an instance of @c %bb::cascades::Application that represents this application.
     *
     * @warning The data referred to by @c argc and @c argv must stay valid for the entire lifetime of the @c Application object. 
     * In addition, @c argc must be greater than zero and @c argv must contain at least one valid character string.
     *
     * @param argc The number of entries in the argument array @c argv passed to the @c %Application instance
     *
     * @param argv The array of parameters to the @c %Application.
     *
     * @since BlackBerry 10.0.0
     */
    Application(int &argc, char **argv);
    /*!
     * @example libbb/Application_constructor.cpp
     * Example use in C++
     */

    /*!
     * @brief Destroys the @c Application instance.
     *
     * @details When the @c %Application is destroyed, all signals and slots are disconnected.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~Application();

    /*!
     * @brief Returns a pointer to the application's @c bb::Application instance.
     *
     * If no instance has been allocated, or if the application instance is not
     * a @c bb::Application, @c null is returned.
     *
     * @return A pointer to the @c bb::Application instance or @c 0 if Application
     * has not been instantiated (or is not a bb::Application).
     *
     * @since BlackBerry 10.0.0
     */
    static bb::Application * instance();

    /*!
     * @brief Sets the main window group ID for this application.
     * 
     * @details This method can be used to register a specific window group as the application's
     * main window group.  The signals @c thumbnail(), @c fullscreen(), @c invisible(), @c asleep(),
     * and @c awake() will be emitted when the corresponding event occurs on either no window
     * group (window group ID of @c "none") or on the application's main window group.
     *
     * If this method is not called, then the application's main window group will be the first
     * valid window group that appears in a lifecycle event.  A valid window group ID is a non-empty
     * string that is not the value @c "none".  For applications that do not use
     * window groups or use a single window group (the default in a Cascades application), this
     * default behavior should produce correct results for the five lifecycle signals (@c thumbnail(),
     * @c fullscreen(), @c invisible(), @c asleep(), and @c awake()).
     *
     * If an application creates multiple window groups (which must be done explicitly), then this
     * method can be called to ensure the application's main group is set correctly.  In this case,
     * you should consider using the five lifecycle events augmented with the window group ID to
     * receive more precise lifecycle information.  These augmented signals are
     * @c windowGroupThumbnailed(const QString &), @c windowGroupFullscreen(const QString &),
     * @c windowGroupInvisible(const QString &), @c windowGroupAsleep(const QString &), and
     * @c windowGroupAwake(const QString &).
     * 
     * @param mainWindowGroupID The ID of the application's main window group.  If this ID is
     * empty or holds the value @c "none" then the main window group ID is not updated.
     *
     * @since BlackBerry 10.0.0
     */
    void setMainWindowGroup(const QString &mainWindowGroupID);

    /*!
     * @brief Deregisters the provided window group.
     *
     * @details After deregistering, all state information about the window group is discarded.
     * 
     * Note that you do not have to explicitly register a window group for state to be
     * maintained. This class automatically maintains the window state about any window group for
     * which state events are received. When deleting a window group, it can be beneficial
     * to deregister it so that state information is no longer maintained in memory.
     *
     * @param windowGroupID The ID of the window group to deregister. If the window group
     * is not recognized, this method does nothing.
     *
     * @since BlackBerry 10.0.0
     */
    void deregisterWindowGroup(const QString &windowGroupID);

    /*!
     * @brief Sets a prompt to appear when the user attempts to close the application.
     *
     * @details This function allows an application to prevent the user from closing the
     * application without warning. If the user tries to close the application, a dialog box
     * is displayed with the title and message specified. The dialog box will have 2 buttons:
     * "Cancel" and "Close". If the user selects "Close", the application will be closed.
     * If the user selects "Cancel", the dialog box will close and the application will continue running.
     *
     * Note that the save prompt for an application is stored persistently on the device. The last
     * call to this method on any @c ApplicationSupport or @c Application object determines the
     * close prompt that will be shown. The close prompt persists until @c clearClosePrompt() is
     * called on any @c %ApplicationSupport or @c %Application object. Destroying the object that set
     * the close prompt does not reset the value.
     *
     * Note that all commas and double quotes are stripped from the title and message parameters
     * before they are displayed. These characters cannot be displayed correctly. If the
     * text also includes backslash characters ('\'), this process can introduce unexpected
     * white space characters like tabs ('\\t') and newlines ('\\n'). Since these whitespace
     * characters are allowed in the dialog box, they cannot be stripped.
     *
     * Escape characters can be used, but they may be awkward to specify. The string provided
     * to this method is in turn forwarded to the device's home screen process, which interprets
     * the string a second time, including any escape characters. This can require multiple
     * levels of escaping to produce the desired effect. For instance, to add a backslash ('\')
     * character to the close prompt, the string "\\\\" must be used. This provides the string
     * "\\" to this object. When this string is forwarded to the home screen, "\\" is interpreted
     * again to become '\'.
     *
     * Setting a close prompt in C++
     * @snippet libbb/Application_setClosePrompt.cpp All
     *
     * Setting a close prompt in QML
     * @snippet libbb/Application_setClosePrompt.qml All
     *
     * @param title The title of the close prompt dialog box. This title replaces the current
     * close prompt title if it is already set.
     * @param message The message of the close prompt dialog box. This message replaces the
     * current close prompt message if it is already set.
     *
     * @return @c true if the close prompt was set, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE bool setClosePrompt(const QString &title, const QString &message);
    /*!
     * @example libbb/Application_setClosePrompt.cpp
     * Example use in C++
     *
     * @example libbb/Application_setClosePrompt.qml
     * Example use in QML
     */
 
    /*!
     * @brief Clears the current close prompt.
     *
     * @details This function removes any close prompt that was set, regardless of which @c ApplicationSupport
     * or @c Application object set the prompt. When the close prompt is cleared, no close prompt
     * dialog box will appear when the user tries to close the application, and the application exits normally.
     * 
     * If there is no current close prompt, this method has no effect.
     *
     * Example usage in C++
     * @snippet libbb/Application_clearClosePrompt.cpp All
     * 
     * Example usage in QML
     * @snippet libbb/Application_clearClosePrompt.qml All
     *
     * @return @c true if the close prompt was cleared, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE bool clearClosePrompt();
    /*!
     * @example libbb/Application_clearClosePrompt.cpp
     * Example use in C++
     *
     * @example libbb/Application_clearClosePrompt.qml
     * Example use in QML
     */

    /*!
     * @brief Indicates if the main window group for the application is currently active.
     * 
     * @details If this method is called before Navigator events are processed, this method will
     * return @c false since the application has not updated its state.
     * 
     * @return @c true if the main window group for the application is currently active, @c false otherwise.
     * 
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE bool isAwake() const;

    /*!
     * @brief Indicates if the main window group for the application is currently inactive.
     * 
     * @details If this method is called before Navigator events are processed, this method will
     * return @c false since the application has not updated its state.
     * 
     * @return @c true if the main window group for the application is currently inactive, @c false otherwise.
     * 
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE bool isAsleep() const;

    /*!
     * @brief Indicates if the main window group for the application application is currently thumbnailed.
     * 
     * @details A window group is thumbnailed if is is currently not fullscreen but is
     * still visible on the display.
     * 
     * If this method is called before Navigator events are processed, this method will
     * return @c false since the application has not updated its state.
     * 
     * @return @c true if the main window group for the application is currently thumbnailed, @c false otherwise.
     * 
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE bool isThumbnailed() const;

    /*!
     * @brief Indicates if the main window group for the application is currently invisible.
     * 
     * @details A window group is invisible if it cannot be seen on the display.
     * 
     * If this method is called before Navigator events are processed, this method will
     * return @c false since the application has not updated its state.
     * 
     * @return @c true if the main window group for the application is currently invisible, @c false otherwise.
     * 
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE bool isInvisible() const;

    /*!
     * @brief Indicates if the main window group for the application is currently fullscreen.
     * 
     * @details If this method is called before Navigator events are processed, this method will
     * return @c false since the application has not updated its state.
     * 
     * @return @c true if the main window group for the application is currently fullscreen, @c false otherwise.
     * 
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE bool isFullscreen() const;

    /*!
     * @brief Indicates if the given window group is currently active.
     * 
     * @details If this method is called before Navigator events are processed, this method will
     * return @c false since the application has not updated its state. Specifically, the process
     * must receive an execution state update from Navigator with the given @c windowGroupID before this
     * method can return a correct result.
     * 
     * @param windowGroupID The ID of the window group that is being queried.
     * 
     * @return @c true if the supplied window group is currently active, @c false otherwise.
     * If the window group ID is not recognized, this method returns @c false.
     * 
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE bool isWindowGroupAwake(const QString &windowGroupID) const;

    /*!
     * @brief Indicates if the given window group is currently inactive.
     * 
     * @details If this method is called before Navigator events are processed, this method will
     * return @c false since the application has not updated its state. Specifically, the process
     * must receive an execution state update from Navigator with the given @c windowGroupID before this
     * method can return a correct result.
     * 
     * @param windowGroupID The ID of the window group that is being queried.
     * 
     * @return @c true if the supplied window group is currently inactive, @c false otherwise.
     * If the window group is not recognized, this method returns @c false.
     * 
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE bool isWindowGroupAsleep(const QString &windowGroupID) const;

    /*!
     * @brief Indicates if the given window group is currently thumbnailed.
     * 
     * @details A window group is thumbnailed if is is currently not fullscreen but is
     * still visible on the display.
     * 
     * If this method is called before Navigator events are processed, this method will
     * return @c false since the application has not updated its state. Specifically, the process
     * must receive a UI state update from Navigator with the given @c windowGroupID before this
     * method can return a correct result.
     * 
     * @param windowGroupID The ID of the window group that is being queried.
     * 
     * @return @c true if the supplied window group is currently thumbnailed, @c false otherwise.
     * If the window group is not recognized, this method returns @c false.
     * 
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE bool isWindowGroupThumbnailed(const QString &windowGroupID) const;

    /*!
     * @brief Indicates if the given window group is currently invisible.
     * 
     * @details A window group is invisible if it cannot be seen on the display.
     * 
     * If this method is called before Navigator events are processed, this method will
     * return @c false since the application has not updated its state. Specifically, the process
     * must receive a UI state update from Navigator with the given @c windowGroupID before this
     * method can return a correct result.
     * 
     * @param windowGroupID The ID of the window group that is being queried.
     * 
     * @return @c true if the supplied window group is currently invisible, @c false otherwise.
     * If the window group is not recognized, this method returns @c false.
     * 
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE bool isWindowGroupInvisible(const QString &windowGroupID) const;

    /*!
     * @brief Indicates if the given window group is currently fullscreen.
     * 
     * @details If this method is called before Navigator events are processed, this method will
     * return @c false since the application has not updated its state.  Specifically, the process
     * must receive a UI state update from Navigator with the given @c windowGroupID before this
     * method can return a correct result.
     * 
     * @param windowGroupID The ID of the window group that is being queried.
     * 
     * @return @c true if the supplied window group is currently fullscreen, @c false otherwise.
     * If the window group is not recognized, this method return @c false.
     * 
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE bool isWindowGroupFullscreen(const QString &windowGroupID) const;

public Q_SLOTS:

    /*!
     * @brief Sets the behavior for an exiting application.
     *
     * @details The value of the auto exit flag dictates the behavior of an exiting application.
     *
     * If the auto exit flag is @c true, then this application will automatically call
     * @c quit() on this object to exit the application's event loop when the application is closed by the user.
     * This will result in the @c QCoreApplication::aboutToQuit() signal being emitted, which can
     * be used for any necessary clean up. Note that this cleanup code must complete within three
     * seconds or the application will be automatically killed. Also note that the @c manualExit()
     * signal will not be emitted.
     *
     * If the auto exit flag is false, then the application assumes responsibility for the process of
     * exiting the application. The @c manualExit() signal is emitted, so the application can perform
     * any necessary actions. The application has three seconds to complete the exit process or be killed,
     * if in release mode. If more time is needed, the application can request additional time by calling the
     * @c extendTerminationTimeout() method. When all actions are complete, the application must call
     * @c quit() on this object.
     * 
     * Note that if @c quit() isn't called within the three second timeframe, and the app is being run
     * in debug mode, the app will NOT be slain by the operating system to allow for more indepth debugging.
     * If the app is running in release mode, it will be slain.
     *
     * To avoid potential races with respect to exiting an application, make sure that a slot is
     * connected to the @c manualExit() signal before the auto exit flag is set to false.
     *
     * Note that this method has no effect after the @c manualExit() or
     * @c QCoreApplication::aboutToQuit() signal has been emitted.
     *
     * By default, the auto exit flag is set to true, so the application will exit automatically.
     *
     * Setting the auto exit flag in C++
     * @snippet libbb/Application_setAutoExit.cpp All
     *
     * Setting the auto exit flag in QML
     * @snippet libbb/Application_setAutoExit.qml All
     *
     * @param autoExit The new value of the auto exit flag.
     *
     * @ingroup Slots
     *
     * @since BlackBerry 10.0.0
     */
    void setAutoExit(bool autoExit);
    /*!
     * @example libbb/Application_setAutoExit.cpp
     * Example use in C++
     *
     * @example libbb/Application_setAutoExit.qml
     * Example use in QML
     */

    /*!
     * @brief Returns the value of the auto exit flag.
     *
     * @details The flag is set using the @c setAutoExit(bool) method.
     *
     * Obtaining the value of the auto exit flag in C++
     * @snippet libbb/Application_autoExit.cpp All
     *
     * Obtaining the value of the auto exit flag in QML
     * @snippet libbb/Application_autoExit.qml All
     *
     * @return The value of the auto exit flag.
     *
     * @ingroup Slots
     *
     * @since BlackBerry 10.0.0
     */
    bool autoExit() const;
    /*!
     * @example libbb/Application_autoExit.cpp
     * Example use in C++
     *
     * @example libbb/Application_autoExit.qml
     * Example use in QML
     */

    /*!
     * @brief Gives the application two more seconds to exit before being automatically killed.
     *
     * @details An exiting application has three seconds to complete any shutdown and exit. After
     * three seconds, the application will be automatically killed. If the application needs more
     * than three seconds, this method can extend the termination timeout.
     *
     * After calling this method, the application has two seconds to terminate before it is
     * automatically killed. Note that this does not add two seconds to the existing timeout, but
     * rather resets the timeout to two seconds from the time this method is called. So if an
     * application calls this method immediately after being told to exit, the application has only
     * two seconds (down from the original timeout of three seconds) to exit.
     *
     * This method can be called multiple times to extend the termination timeout for longer
     * periods of time.
     *
     * Extending the termination timeout in C++
     * @snippet libbb/Application_extendTerminationTimeout.cpp All
     *
     * Extending the termination timeout in QML
     * @snippet libbb/Application_extendTerminationTimeout.qml All
     *
     * @return @c true if the request to extend the timeout was successful, @c false otherwise.
     *
     * @ingroup Slots
     *
     * @since BlackBerry 10.0.0
     */
    bool extendTerminationTimeout();
    /*!
     * @example libbb/Application_extendTerminationTimeout.cpp
     * Example use in C++
     *
     * @example libbb/Application_extendTerminationTimeout.qml
     * Example use in QML
     */

    /*!
     * @brief Applies a badge to the application's icon on the home screen and the window frame when
     * the application is thumbnailed.
     *
     * @details Once applied, the badge will still be applied to the application's icon after the
     * application exits. However, a badge will not persist across device resets.
     *
     * Setting the icon badge of an application in C++
     * @snippet libbb/Application_setIconBadge.cpp All
     *
     * Setting the icon badge of an application in QML
     * @snippet libbb/Application_setIconBadge.qml All
     *
     * @param badge The new badge to be applied.
     *
     * @returns @c true if the badge was successfully applied, @c false otherwise.
     *
     * @ingroup Slots
     *
     * @since BlackBerry 10.0.0
     */
    bool setIconBadge(bb::IconBadge::Type badge);
    /*!
     * @example libbb/Application_setIconBadge.cpp
     * Example use in C++
     *
     * @example libbb/Application_setIconBadge.qml
     * Example use in QML
     */

    /*!
     * @brief Minimizes the application window to a thumbnail and sends the user to the
     * application switcher on the home screen.
     *
     * @details This method causes the application to minimize itself into a thumbnail.
     * This operation is identical to the user swiping up from the bottom touch-sensitive
     * bezel into the screen. The user is taken to the application switcher on the
     * device's home screen.
     *
     * Example usage in C++
     * @snippet libbb/Application_minimize.cpp All
     *
     * Example usage in QML
     * @snippet libbb/Application_minimize.qml All
     *
     * @return @c true if the minimize request was successfully sent, @c false otherwise.
     *
     * @ingroup Slots
     *
     * @since BlackBerry 10.0.0
     */
    bool minimize();
    /*!
     * @example libbb/Application_minimize.cpp
     * Example use in C++
     *
     * @example libbb/Application_minimize.qml
     * Example use in QML
     */

    /*!
     * @brief Requests that Navigator close the application.
     *
     * @details An application should call this method if it decides that it needs to
     * exit. This method informs Navigator that the application wishes to exit. In
     * response, Navigator posts an exit event to the application. The application
     * should wait for this event then shut down normally.
     *
     * @note In general, applications should not programmatically exit. They should
     * terminate only when explicitly closed by the end user.
     *
     * Example usage in C++
     * @snippet libbb/Application_requestExit.cpp All
     *
     * Example usage in QML
     * @snippet libbb/Application_requestExit.qml All
     *
     * @return @c true if the close request was successfully sent, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool requestExit();
    /*!
     * @example libbb/Application_requestExit.cpp
     * Example use in C++
     *
     * @example libbb/Application_requestExit.qml
     * Example use in QML
     */

    /*!
     * @brief Call this method when the application has finished setting its restoration state
     * and wishes to be pooled.
     * 
     * @details This method should be called after setting the application's restoration state
     * in a slot attached to the @c pooling() signal. The request identifier parameter in
     * this method is the identifier from the signal argument.
     * 
     * If this method is not called within one second of receiving the @c pooling() signal,
     * the application will be terminated rather than pooled.
     *
     * @param poolRequestID The identifier for the pooling request, supplied by
     * the @c pooling(const QString &) signal.
     *
     *
     * @since BlackBerry 10.0.0
     */
    void poolingComplete( const QString &poolRequestID ) const;

Q_SIGNALS:

    /*!
     * @brief Emitted when the application has been thumbnailed.
     *
     * @details Any slot attached to this signal is notified when your application
     * is no longer fullscreen. This includes the application being thumbnailed on a 
     * swipe-up or a side-swipe to the task switcher.
     *
     * The state of the application's main window group is considered to be the state of
     * the @c Application as a whole.
     *
     * @note If you connect to both this signal and @c windowGroupThumbnailed(const QString &) then
     * you will receive duplicate notifications for the application's main window group.
     *
     * Example usage in C++
     * @snippet libbb/Application_thumbnail.cpp Connecting to the thumbnail signal
     * @link libbb/Application_thumbnail.cpp
     * See full example
     * @endlink
     *
     * Example use in QML
     * @snippet libbb/Application_thumbnail.qml All
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void thumbnail();
    /*!
     * @example libbb/Application_thumbnail.cpp 
     * This example illustrates how to connect to the @c Application @c thumbnail signal in C++.
     *
     * @example libbb/Application_thumbnail.qml
     * This example illustrates how to connect to the @c Application @c thumbnail signal in QML.
     */

    /*!
     * @brief Emitted when a window group has been thumbnailed.
     *
     * @details Any slot attached to this signal is notified when a window group in the
     * application is no longer fullscreen.  This includes the application being thumbnailed on a 
     * swipe-up or a side-swipe to the task switcher.
     *
     * @note If you connect to both this signal and @c thumbnail() then you will receive duplicate
     * notifications for the application's main window group.
     *
     * A window group ID of @c "none" should normally be treated as an event for the application's
     * main window group.
     *
     * @param windowGroupID The ID of the window group that has just been thumbnailed.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void windowGroupThumbnailed(const QString &windowGroupID);

    /*!
     * @brief Emitted when the application is restored to fullscreen status.
     *
     * @details This signal is emitted when the application is restored to fullscreen, such
     * as after being thumbnailed, or if it becomes the active application from the task
     * switcher interface.
     *
     * The state of the application's main window group is considered to be the state of
     * the @c Application as a whole.
     *
     * @note If you connect to both this signal and @c windowGroupFullscreen(const QString &) then
     * you will receive duplicate notifications for the application's main window group.
     *
     * Example usage in C++
     * @snippet libbb/Application_fullscreen.cpp Connecting to the fullscreen signal
     * @link libbb/Application_fullscreen.cpp
     * See full example
     * @endlink
     *
     * Example use in QML
     * @snippet libbb/Application_fullscreen.qml All
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void fullscreen();
    /*!
     * @example libbb/Application_fullscreen.cpp 
     * This example illustrates how to connect to the @c %Application @c fullscreen signal in C++.
     *
     * @example libbb/Application_fullscreen.qml
     * This example illustrates how to connect to the @c %Application @c fullscreen signal in QML.
     */

    /*!
     * @brief Emitted when a window group is restored to fullscreen status.
     *
     * @details This signal is emitted when a window group in an application is restored to fullscreen,
     * such as after being thumbnailed, or if it becomes the active application from the task
     * switcher interface.
     *
     * @note If you connect to both this signal and @c fullscreen() then you will receive duplicate
     * notifications for the application's main window group.
     *
     * A window group ID of @c "none" should normally be treated as an event for the application's
     * main window group. This can happen because this event can occur before a window message has been
     * processed by the application, which means the window group ID is not yet available in the framework.
     *
     * @param windowGroupID The ID of the window group that is now fullscreen.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void windowGroupFullscreen(const QString &windowGroupID);

    /*!
     * @brief Emitted when the application is no longer visible.
     *
     * @details Any slot attached to this signal is notified when your application is no longer visible.
     * Your application is considered to be no longer visible when your application window is outside
     * the viewable area of the Navigator. This includes when your window is off-screen during a task switch,
     * or when the tray is raised and obscures all application windows, etc.
     *
     * The state of the application's main window group is considered to be the state of
     * the @c Application as a whole.
     *
     * @note If you connect to both this signal and @c windowGroupInvisible(const QString &) then
     * you will receive duplicate notifications for the application's main window group.
     *
     * Example usage in C++
     * @snippet libbb/Application_invisible.cpp Connecting to the invisible signal
     * @link libbb/Application_invisible.cpp
     * See full example
     * @endlink
     *
     * Example usage in QML
     * @snippet libbb/Application_invisible.qml All
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void invisible();
    /*!
     * @example libbb/Application_invisible.cpp 
     * This example illustrates how to connect to the @c Application @c invisible signal in C++.
     *
     * @example libbb/Application_invisible.qml 
     * This example illustrates how to connect to the @c Application @c invisible signal in QML.
     */

    /*!
     * @brief Emitted when a window group is no longer visible.
     *
     * @details Any slot attached to this signal is notified when a window group in the application
     * is no longer visible.
     *
     * @note If you connect to both this signal and @c invisible() then you will receive duplicate
     * notifications for the application's main window group.
     *
     * A window group ID of @c "none" should normally be treated as an event for the application's
     * main window group.
     *
     * @param windowGroupID The ID of the window group that is now invisible.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void windowGroupInvisible(const QString &windowGroupID);

    /*!
     * @brief Emitted when the Navigator detects a swipe down gesture.
     *
     * @details Any slot attached to this signal is notified when the Navigator detects a swipe down gesture.
     * Typically the application should display a menu in response to this gesture.
     *
     * Example usage in C++
     * @snippet libbb/Application_swipeDown.cpp Connecting to the swipeDown signal
     * @link libbb/Application_swipeDown.cpp
     * See full example
     * @endlink
     *
     * Example usage in QML
     * @snippet libbb/Application_swipeDown.qml All
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void swipeDown();
    /*!
     * @example libbb/Application_swipeDown.cpp 
     * This example illustrates how to connect to the @c Application @c swipeDown signal in C++.
     *
     * @example libbb/Application_swipeDown.qml
     * This example illustrates how to connect to the @c Application @c swipeDown signal in QML.
     */

    /*!
     * @brief Emitted when the application becomes inactive.
     *
     * @details Any slot attached to this signal is notified when the application becomes inactive. 
     * This occurs when the application is no longer in the foreground and the device decides that 
     * your application should no longer execute.
     *
     * When this signal is received the @c %Application should attempt to reduce CPU usage as much as 
     * possible, such as by presenting a "pause" or other suitable mechanism.
     *
     * The state of the application's main window group is considered to be the state of
     * the @c Application as a whole.
     *
     * @note If you connect to both this signal and @c windowGroupAsleep(const QString &) then
     * you will receive duplicate notifications for the application's main window group.
     *
     * Example usage in C++
     * @snippet libbb/Application_asleep.cpp Connecting to the asleep signal
     * @link libbb/Application_asleep.cpp
     * See full example
     * @endlink
     *
     * Example usage in QML
     * @snippet libbb/Application_asleep.qml All
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void asleep();
    /*!
     * @example libbb/Application_asleep.cpp
     * This example illustrates how to connect to the @c Application @c asleep signal in C++.
     *
     * @example libbb/Application_asleep.qml
     * This example illustrates how to connect to the @c Application @c asleep signal in QML.
     */

    /*!
     * @brief Emitted when a window group becomes inactive.
     *
     * @details Any slot attached to this signal is notified when a window group in an
     * application becomes inactive.  When this signal is received by an application, it should
     * reduce CPU usage as much as possible with respect to the given window group.
     *
     * @note If you connect to both this signal and @c asleep() then you will receive duplicate
     * notifications for the application's main window group.
     *
     * A window group ID of @c "none" should normally be treated as an event for the application's
     * main window group.
     *
     * @param windowGroupID The ID of the window group that is now inactive.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void windowGroupAsleep(const QString &windowGroupID);

    /*!
     * @brief Emitted when the application becomes active.
     *
     * @details Any slot attached to this signal is notified when your application becomes 
     * active. This occurs when the application transitions to the foreground.
     *
     * When this signal is received the @c %Application should resume all normal activity.
     *
     * The state of the application's main window group is considered to be the state of
     * the @c Application as a whole.
     *
     * @note If you connect to both this signal and @c windowGroupAwake(const QString &) then
     * you will receive duplicate notifications for the application's main window group.
     *
     * Example usage in C++
     * @snippet libbb/Application_awake.cpp Connecting to the awake signal
     * @link libbb/Application_awake.cpp
     * See full example
     * @endlink
     *
     * Example usage in QML
     * @snippet libbb/Application_awake.qml All
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void awake();
    /*!
     * @example libbb/Application_awake.cpp
     * This example illustrates how to connect to the @c Application @c awake signal in C++.
     *
     * @example libbb/Application_awake.qml
     * This example illustrates how to connect to the @c Application @c awake signal in QML.
     */

    /*!
     * @brief Emitted when a window group becomes active.
     *
     * @details Any slot attached to this signal is notified when a window group in an application
     * becomes active.  When this signal is received, the application should resume all normal
     * activity with respect to the given window group.
     *
     * @note If you connect to both this signal and @c awake() then you will receive duplicate
     * notifications for the application's main window group.
     *
     * A window group ID of @c "none" should normally be treated as an event for the application's
     * main window group.
     *
     * @param windowGroupID The ID of the window group that is now active.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void windowGroupAwake(const QString &windowGroupID);

    /*!
     * @brief Emitted when the application is closed by the user or by the system with the auto
     * exit flag set to @c false.
     *
     * @details If the application is handling the exit process, then this signal is emitted
     * when the application is closed. Any code that needs to be run to shut down the application
     * should be placed in a slot connected to this signal. The slot is also responsible for
     * calling the @c quit() method on this object to slow down the application's event loop, and
     * ensure that it has sufficient time to complete any actions.
     *
     * This signal is not emitted if the application is killed because the application is considered
     * to be unresponsive.
     *
     * This signal is not emitted if the auto exit flag is set to @c true.
     * 
     * @see @c setAutoExit(bool) for more details on handling application exit.
     *
     * Example usage in C++
     * @snippet libbb/Application_manualExit.cpp Connecting to the manualExit signal
     * @link libbb/Application_manualExit.cpp
     * See full example
     * @endlink
     *
     * Example usage in QML
     * @snippet libbb/Application_manualExit.qml All
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void manualExit();
    /*!
     * @example libbb/Application_manualExit.cpp
     * This example illustrates how to connect to the @c Application @c manualExit signal in C++.
     *
     * @example libbb/Application_manualExit.qml
     * This example illustrates how to connect to the @c Application @c manualExit signal in QML.
     */

    /*!
     * @brief Emitted when the auto exit flag changes.
     *
     * Example usage in C++
     * @snippet libbb/Application_autoExitChanged.cpp Connecting to the autoExitChanged signal
     * @link libbb/Application_autoExitChanged.cpp
     * See full example
     * @endlink
     *
     * Example usage in QML
     * @snippet libbb/Application_autoExitChanged.qml All
     * 
     * @param newAutoExit The new value of the auto exit flag.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void autoExitChanged(bool newAutoExit);
    /*!
     * @example libbb/Application_autoExitChanged.cpp
     * This example illustrates how to connect to the @c Application @c manualExit signal in C++.
     *
     * @example libbb/Application_autoExitChanged.qml
     * This example illustrates how to connect to the @c Application @c manualExit signal in QML.
     */

    /*!
     * @brief Emitted when the application is moved to a different process state.
     *
     * @details Notifies the application when the process execution state has changed. The
     * state will be one of the values enumerated by @c bb::ProcessState.
     *
     * @param processState The new process state of the application.
     *
     * Example usage in C++
     * @snippet libbb/Application_processStateChanged.cpp Connecting to the processStateChanged signal
     * @link libbb/Application_processStateChanged.cpp
     * See full example
     * @endlink
     *
     * Example usage in QML
     * @snippet libbb/Application_processStateChanged.qml All
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void processStateChanged( bb::ProcessState::Type processState );
    /*!
     * @example libbb/Application_processStateChanged.cpp
     * This example illustrates how to connect to the @c Application @c processStateChanged(bb::ProcessState::Type) signal in C++.
     *
     * @example libbb/Application_processStateChanged.qml
     * This example illustrates how to connect to the @c Application @c processStateChanged(bb::ProcessState::Type) signal in QML.
     */

    /*!
     * @brief Emitted when the application is being asked to be put in to the application pool.
     *
     * @details This signal is received when the user closes the application. The application can choose
     * to be pooled in memory rather than terminated. A pooled process is still running but has no visible
     * windows. Restoring a pooled application is faster than launching a new instance.
     * 
     * This signal allows an application to set its restoration state, which is the state from which the application will
     * resume when it is restored from the pool. Typically, the application will reset its UI state so restoring the
     * pooled application will appear identical to a fresh launch.  However, the application can choose other restoration
     * states if it wishes to resume from some other state. The restoration state should be determined when the application
     * is pooled rather than when it is next restored, as changing the UI on restoration can result in flickers as the UI
     * updates or can result in stale data appearing in the UI.
     * 
     * The application must call the @c poolingComplete() method with the pool request identifier within one second
     * of receiving this signal to indicate that the application has set its restoration state and wishes to be pooled.
     * Otherwise, the application will be terminated rather than pooled.
     * 
     * After being pooled, the application should enter the @c bb::ProcessState::Stopped state, and become invisible and inactive.
     * Restoring the application from the pool is similar to restoring the application from a thumbnail.  It should enter the
     * @c bb::ProcessState::Foreground state, and become fullscreen and active.
     * 
     * @param poolRequestID A unique identifier for this pooling request, this value must be passed to a call to @c poolComplete()
     * when the application is finished any work necessary to be pooled.
     *
     * Example usage in C++
     * @snippet libbb/Application_pooling.cpp Connecting to the pooling signal
     * @link libbb/Application_pooling.cpp
     * See full example
     * @endlink
     *
     * Example usage in QML
     * @snippet libbb/Application_pooling.qml All
     *
     *
     * @ingroup Signals
     * 
     * @note This signal should not be used as the trigger for releasing resources and other
     * heavy assets prior to the user leaving the application. Instead, the application
     * should perform those actions when the @c processStateChanged(bb::ProcessType) signal arrives with
     * a @c bb::ProcessState::Stopping value. These resources should be restored when the application
     * becomes active.
     *
     * @note If this pooling request does not have a corresponding call made to @c poolingComplete() (with
     * the supplied poolRequestID) the application will be terminated instead.
     * 
     * @note A pooled process may still be terminated if necessary. For instance, if the device runs low on memory,
     * pooled applications may be terminated to make memory available for other applications.
     * 
     * @since BlackBerry 10.0.0
     */
    void pooling( const QString &poolRequestID );
    /*!
     * @example libbb/Application_pooling.cpp
     * This example illustrates how to connect to the @c Application @c pooling(const QString &) signal in C++.
     *
     * @example libbb/Application_pooling.qml
     * This example illustrates how to connect to the @c Application @c pooling(const QString &) signal in QML.
     */

protected:
//!@cond PRIVATE
    /*!
     * @brief Workaround for passing enum values to methods in QML.
     *
     * @note This is only meant as a workaround. This slot should not be used by C++ code.
     * Instead, see @c setIconBadge(bb::IconBadge::Type).
     */
    Q_SLOT bool setIconBadge(int badge);

    Q_SIGNAL void processStateChanged( int processState );
//!@endcond
private:
//!@cond PRIVATE
    ApplicationPrivate * const d_ptr;  // Reference to the private implementation of the Application class
    Q_DISABLE_COPY(Application) // Hides the copy constructor
    Q_DECLARE_PRIVATE(Application) // Hides the application constructor
//!@endcond
};

} // namespace bb

QML_DECLARE_TYPE(bb::Application)
#endif // BB_CORE_APPLICATION_HPP
