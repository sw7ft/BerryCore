/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

//!@cond PRIVATE

#ifndef BB_CORE_UITOOLKITSUPPORT_HPP
#define BB_CORE_UITOOLKITSUPPORT_HPP

#include <bb/Global>
#include <bb/Orientation>
#include <bb/ProcessExecutionState>
#include <bb/ProcessState>
#include <bb/ProcessUIState>
#include <bb/SwipeDownMode>

#include <QObject>
#include <QString>
#include <QUrl>

namespace bb
{

class UIToolkitSupportPrivate;

/*!
 * @headerfile UIToolkitSupport.hpp <bb/UIToolkitSupport>
 *
 * @brief The UIToolkitSupport class provides functionality that is generally useful only
 * to UI toolkits.
 *
 * @details User applications can receive this information through other sources, making it
 * unlikely that applications should need to use this class.  Either the UI toolkit that the
 * application is using will provide this information, or the UI toolkit will handle the events
 * that are generated in pre-determined ways.
 *
 * Instances of this  class provides signals on various lifecycle events over the lifetime of a
 * running process.  This includes the execution state (whether the process is currently active
 * or inactive).
 *
 * Instances of this class also provides support for orientation, allowing the toolkit to decide
 * how to handle changes in device orientation.
 *
 * Instances of this class provide methods and events related to "swipe down" events, where the
 * user swipes from the touch-sensitive bevel from the top of the screen onto the application window.
 *
 * This class is not thread-safe.  Accessing it from multiple threads will produce undefined behavior.
 * 
 * Note that, once created, objects of this class cannot have their thread affinity changed,
 * either explicitly via QObject::moveToThread() or implicitly by changing the thread
 * affinity of the parent of the object.  Doing so results in undefined behavior.
 *
 * @xmlonly
 * <apigrouping group="Platform/Utility"/>
 * <library name="bb"/>
 * @endxmlonly 
 */
class BB_CORE_EXPORT UIToolkitSupport : public QObject
{
    Q_OBJECT

    /*!
     * @brief The execution state of the process.
     *
     * See bb::ProcessExecutionState.
     */
    Q_PROPERTY(bb::ProcessExecutionState::Type executionState READ executionState NOTIFY executionStateChanged FINAL)

    /*!
     * @brief The UI state of the process.
     *
     * See bb::ProcessUIState.
     */
    Q_PROPERTY(bb::ProcessUIState::Type uiState READ uiState NOTIFY uiStateChanged FINAL)

    /*!
     * @brief The current state of the process within the system.
     *
     * @see bb::ProcessState for information on each state.
     *
     */
     Q_PROPERTY( bb::ProcessState::Type processState READ processState NOTIFY processStateChanged FINAL )

public:

    /*!
     * @brief Creates a UIToolkitSupport object.
     *
     * @param parent If not 0, the supplied parent will be responsible for deleting this instance.
     */
    explicit UIToolkitSupport(QObject *parent = 0);

    /*!
     * @brief Destroys this UIToolkitSupport object.
     */
    virtual ~UIToolkitSupport();

    /*!
     * @brief Return the main window group ID for this application.
     *
     * @details If you are using the Screen library directly, this will be of use.
     *
     * The main window group will default to the first valid window group in a screen
     * event, where a valid window group ID is a non-empty string that is not @c "none".
     * The @c setWindowGroupID(const QString &) method can be used to override this
     * default.
     *
     * If the application does not yet know its window group ID, an empty string will
     * be returned.
     *
     * @return The window group ID for this application's window.
     */
    QString windowGroupID() const;

    /*!
     * @brief Sets the main window group ID for this application.
     * 
     * @details This method can be used to register a specific window group as the application's
     * main window group, overriding the default main window group.
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
     */
    void setMainWindowGroup(const QString &mainWindowGroupID);

    /*!
     * @brief Deregisters the provided window group.
     *
     * @details After deregistering, all state information about the window group is discarded.
     * The methods @c executionStateForWindowGroup(const QString &) and
     * @c uiStateForWindowGroup(const QString &) will behave as though the window group is not
     * recognized unless additional events for the group are processed.
     * 
     * Note that you do not have to explicitly register a window group for state to be
     * maintained. This class automatically maintains window state about any window group for
     * which state events are received.  When deleting a window group, it can be beneficial
     * to deregister it so that state information is no longer maintained in memory.
     *
     * Note that this must be done on each instance of @c bb::UIToolkitSupport and on the
     * instance of @c bb::Application, as each maintain their own individual state.
     *
     * @param windowGroupID The ID of the window group to deregister. If the window group
     * is not recognized, this method does nothing.
     */
    void deregisterWindowGroup(const QString &windowGroupID);

    /*!
     * @brief Returns the current execution state of this process.
     *
     * @details This is the execution state of the main window group, as defined by
     * @c windowGroupID().
     *
     * @return The current execution state of this process.
     */
    bb::ProcessExecutionState::Type executionState() const;

    /*!
     * @brief Returns the current execution state for a window group.
     *
     * @details If the supplied window group is not recognized, @c bb::ProcessExecutionState::Unknown
     * will be returned.
     *
     * @param windowGroupID The ID of the window group for which the process execution state
     * is being requested.
     * 
     * @return Returns the current execution state for the supplied window group.
     */
    bb::ProcessExecutionState::Type executionStateForWindowGroup(const QString &windowGroupID) const;

    /*!
     * @brief Returns the current UI state of this process.
     *
     * @details This is the UI state of the main window group, as defined by
     * @c windowGroupID().
     * 
     * @return The current UI state of this process.
     */
    bb::ProcessUIState::Type uiState() const;

    /*!
     * @brief Returns the current UI state for a window group.
     * 
     * @details If the supplied window group is unrecognized, @c bb::ProcessUIState::Unknown will
     * be returned.
     *
     * @param windowGroupID The ID of the window group for which the UI state is being requested.
     * 
     * @return Returns the current UI state for the supplied window state.
     */
    bb::ProcessUIState::Type uiStateForWindowGroup(const QString &windowGroupID) const;

    /*!
     * @brief Set the behavior for swipe down events.
     *
     * @details Only one mode may be active at any given time.  The default behavior
     * is @c SwipeDownModeCompletionOnly.
     *
     * Note that if you change the behavior for swipe down events, it is still possible to
     * receive an event based on the previous mode.  This can happen if a swipe down event is
     * in transit when you change the swipe down mode.
     *
     * @param swipeDownMode The new SwipeDownMode to use.
     *
     * @return @c true if the mode was set successfully, @c false otherwise.
     */
    bool setSwipeDownMode(bb::SwipeDownMode::Type swipeDownMode);

    /*!
     * @brief Set the timeout for the application to creates its application window.
     *
     * @details Normally, an application has 30 seconds to create its application window.
     * If an application is unable to create its window in this time frame (say, because
     * of initialization or loading issues), it must set this timeout to be sufficiently
     * long.  Otherwise, the application will be terminated.
     *
     * Note that the supplied value is the total time, in milliseconds, that the application
     * expects to need before it can create its application window.  It is not the amount of
     * extra time needed by the application.  If an application expects to need 45 seconds
     * before it can create its window, then the value of the @c milliseconds parameter
     * should be 45000 for 45 total seconds, not 15000 to extend the default timeout by 15
     * seconds.
     *
     * Further, the timeout is reset and starts again when this method is called, with the
     * supplied value.  For example, if an application waits 20 seconds and then calls this
     * method with a value of 45000 (for 45 seconds), the application has 45 additional seconds
     * to create its application window for a total of 65 seconds.
     *
     * Note that the timeout can be set to a value shorter than the 30 second default, in which
     * case the application has less time to create its window before being killed.
     * 
     * @param milliseconds The total time, in milliseconds, that the application expects to
     * need before it can create its application window.
     *
     * @return @c true if the timeout was set to the supplied value, @c false otherwise.
     */
    bool setWindowCreationTimeout(int milliseconds);

    /*!
     * @brief Indicate whether the application will accept this rotation request.
     *
     * @details This method is called in response to a @c orientationCheck() signal, using
     * the orientation request identifier received in the signal handler, to indicate if
     * the application will rotate for this orientation request.
     *
     * If @c willRotate is @c false, the application has declined to rotate.  Nothing further
     * will happen.
     *
     * If @c willRotate is @c true, the application has committed to rotating.  The application
     * should not start the process of resizing its screens for the new orientation at this
     * time.  The application should receive the @c orientation() signal and should
     * resize in response to that signal.
     *
     * Note that only one call to this method should be made for any given rotation request.
     * If there are multiple @c UIToolkitSupport objects in an application or multiple slots
     * connected to its signals, they must coordinate to ensure that only one responds.
     *
     * @param orientationRequestID The identifier of a rotation request, received with the
     * @c deviceHasRotated signal.
     * @param willRotate A flag indicating whether the application is committing to rotate
     * or not.
     *
     * @return @c true if the response was successfully communicated to the device,
     * @c false otherwise.
     */
    bool orientationCheckResponse(const QString &orientationRequestID, bool willRotate);

    /*!
     * @brief Indicates that the application has completed a rotation request.
     *
     * @details This method is generally called in response to the @c orientation()
     * signal to indicate that the application has finished resizing its screens for a rotation
     * request.
     *
     * @param orientationRequestID The identifier of a rotation request, received with
     * the @c orientation() signal.
     *
     * @return @c true if the completion indication was successfully communicated to the
     * device, @c false otherwise.
     */
    bool doneOrientation(const QString &orientationRequestID);

    /*!
     * @brief Sets the orientation of the application.
     *
     * @details The application should not start the process of rotating after calling this method.
     * After making this call, the rotation process will start with the application receiving the
     * @c orientation() signal and proceed normally from that point.  The @c orientationCheck()
     * signal and response are bypassed.  This means that the application is committed to rotating
     * to the supplied orientation.
     *
     * @param orientation The desired orientation of the application.
     *
     * @return @c true if the rotation process to set the orientation to the provided value
     * was successfully started, @c false otherwise.
     */
    bool requestOrientation(bb::Orientation::Type orientation);

    /*!
     * @brief Locks the application orientation to its current orientation.
     *
     * @details The orientation of the application cannot be changed until it is unlocked
     * by a call to @c unlockOrientation().
     *
     * Take care not to lock the orientation while a rotation is currently in progress.
     * The timing of the request to lock the orientation and the in-progress rotation may
     * yield unexpected results.
     *
     * @return @c true if the orientation was successfully locked, @c false otherwise.
     */
    bool lockOrientation();

    /*!
     * @brief Unlocks the application orientation so that it can change with the
     * device orientation.
     *
     * @details The orientation of the application can now change with the orientation of the
     * device. The @c lockOrientation() method can be used to lock the orientation to its
     * current orientation.
     *
     * @return @c true if the orientation was successfully unlocked, @c false otherwise.
     */
    bool unlockOrientation();

    /*!
     * @brief Resolves local URLs to file system paths.
     *
     * @details resolves local URLs to file system path strings where the following schemas are accepted:
     *   "asset:"  for files in the app's asset folder.  QUrl("asset:///foo/bar.txt") -> "/accounts/1000/appdata/com.example.MyExampleApp/app/native/assets/foo/bar.txt"
     *   "file:"   for absolute paths on the device.     QUrl("file:///foo/bar.txt")  -> "/foo/bar.txt"
     *   no schema - path relative to current directory. QUrl("foo/bar.txt")          -> "/a/b/c/currentdir/foo/bar.txt"  (ie if path was relative, it becomes absolute)
     *   no schema - path absolute (starts with "/").    QUrl("/foo/bar.txt")         -> "/foo/bar.txt"  (unchanged)
     *
     *   In the case of "asset:" schema, the resolved path will also include any folders used by the static asset selector.
     *   For example if the application contains resolution or theme specific assets which are properly included in the assets folder,
     *   QUrl("asset":///images/wallpaper.png") may resolve to "/accounts/1000/appdata/com.example.MyExampleApp/app/native/assets/720x720/VisualStyle.bright/images/wallpaper.png"
     *   depending on the assets folder structure, display resolution and application theme.
     *
     * @param localUrl Local URL to be converted to a file system path.
     *
     * @return Absolute file system path, or empty if the URL was malformed.  Note the path need not exist in the file system.
     */
    static QString absolutePathFromUrl(const QUrl & localUrl);

    /*!
     * @brief Returns the current state of the process within the system.
     *
     * @details While related to @c bb::ProcessExecutionState, this state allows for further
     * information about how the process should behave on an ongoing basis.
     * See @c bb::ProcessState for information about how the process should behave
     * in each state.
     *
     * @return The current process state as one of @c bb::ProcessState::Type.
     */
    bb::ProcessState::Type processState() const;

    /*!
     * @brief Call this method when a notified process has finished all work prior to
     * being moved to the process pool.
     *
     * @param poolRequestID The identifier for the pooling request, supplied by
     * the @c poolRequest() signal.
     *
     */
    bool poolingComplete( const QString &poolRequestID ) const;

Q_SIGNALS:

    /*!
     * @brief Emitted when the execution state of this process changes.
     *
     * @param newState The new execution state of this process.
     * @param windowGroupID Identifies the window for which this signal was emitted.
     * If you are using the Screen library directly this will be useful, otherwise you can ignore
     * this parameter.
     *
     * @ingroup Signals
     */
    void executionStateChanged(bb::ProcessExecutionState::Type newState, const QString &windowGroupID);

    /*!
     * @brief Emitted when the UI state of this process changes.
     *
     * @param newState The new execution state of this process.
     * @param windowGroupID Identifies the window for which this signal was emitted.
     * If you are using the Screen library directly this will be useful, otherwise you can ignore
     * this parameter.
     *
     * @ingroup Signals
     */
    void uiStateChanged(bb::ProcessUIState::Type newState, const QString &windowGroupID);

    /*!
     * @brief Emitted when a swipe down gesture is detected.
     *
     * @details The precise meaning of this signal is determined by the swipe down mode that was set when the
     * gesture was detected.
     *
     * @sa @c setSwipeDownMode
     *
     * @param swipeDownMode The swipe down mode that was set when the swipe down gesture was detected.
     * This value can be used to correctly interpret the signal and respond appropriately.
     * 
     * @ingroup Signals
     */
    void swipedDown(bb::SwipeDownMode::Type swipeDownMode);

    /*!
     * @brief Emitted when the application has been closed by the user.
     *
     * @details Any slot attached to this signal is notified when the user exits your
     * application. 
     *
     * @ingroup Signals
     */
    void exit();

    /*!
     * @brief Emitted when the device has rotated.
     *
     * @details Applications should call @c orientationCheckResponse() to indicate if they are
     * willing to rotate.  If the application supplies a value of @c true to
     * @c orientationCheckResponse(), this will commit the application to rotating, but the
     * application should not act on that decision until the @c orientation() signal is received.
     * If the application declines to rotate, then the process is over and no further signals will
     * be received.
     *
     * @param orientationRequestID The request identifier, which is needed in the call
     * to @c orientationCheckResponse().
     * @param angle The angle to which the device has rotated.
     *
     * @ingroup Signals
     */
    void orientationCheck(const QString &orientationRequestID, bb::Orientation::Type angle);

    /*!
     * @brief Emitted during the orientation sequence to inform the application about the size 
     * of the display in the new orientation.
     *
     * @details When assuming a new orientation, the dimensions of the display may not be
     * simply the swap of the width and height.  This can be due to titlebars, or other UI
     * elements not under control of the application.  The width and height supplied here
     * should be used to determine the new size of the display the application will
     * be assuming.
     *
     * @param orientationRequestID The request identifier, which is needed in the call to
     * @c doneOrientation().
     * @param width The horizontal dimension of the display.
     * @param height The vertical dimension of the display.
     *
     * @ingroup Signals
     */
    void orientationSize( const QString &orientationRequestID, int width, int height );

    /*!
     * @brief Emitted when the application should rotate.
     *
     * @details When finished, the application should call @c doneOrientation()
     * to indicate that it has completed the rotation process.
     *
     * Regardless, the @c orientationCompleted() signal will always be emitted at
     * some time after this signal.
     * 
     * @param orientationRequestID The request identifier, which is needed in the call to
     * @c doneOrientation().
     * @param angle The angle to which the application has rotated.
     *
     * @ingroup Signals
     */
    void orientation(const QString &orientationRequestID, bb::Orientation::Type angle);

    /*!
     * @brief Emitted when the rotation process has completed.
     *
     * @details No response is necessary.  This is for information only.
     *
     * @param angle The angle to which the application has rotated.
     *
     * @ingroup Signals
     */
    void orientationCompleted(bb::Orientation::Type angle);

    /*!
     * @brief Emitted when the current state of this process in the system.
     *
     * @details This indicates a change of the process partition, from
     * unbounded, to bounded, to stopped.  It differs from the @c ProcessExecutionState
     * in that the @c ProcessExecutionState notifies when the process is likely
     * to be directly accessed by the user, whereas this indicates when the process
     * is being suspended or reanimated due to system state.
     *
     * @param processState The new state of the process.
     *
     * @ingroup Signals
     *
     * @note It is expected that an application will release as many resources
     * as possible when entering the @c bb::ProcessState::Stopping state.  It
     * should be assumed the application will be suspended for a large amount of
     * time when entering this state.
     */
    void processStateChanged( bb::ProcessState::Type processState );


    /*!
     * @brief Indicates the process is being asked to be stored in the process
     * pool and should prepare itself for execution at a future date.
     *
     * @details When a process receives this signal, and desires to appear
     * as if it has launched fresh, it should reset the UI to a fresh state
     * at this point.  At any point after this signal the application can be
     * brought to the foreground via the user launching the application from
     * the home screen.
     *
     * If the application does not wish to be pooled, simply ignore this signal.
     *
     * @param poolId This value is passed to the @ poolComplete to signal the
     * application is ready to be moved in to the process pool.
     *
     * @ingroup Signals
     *
     * @note This signal should not be used as the point at which resources are
     * released.  Applications should handle the @c processStateChanged signal
     * when the @c bb::ProcessState::Stopping value is passed in.
     */
    void poolRequest( const QString &poolRequestId );

private:
//!@cond PRIVATE
    QScopedPointer<UIToolkitSupportPrivate> d_ptr;
    Q_DECLARE_PRIVATE(UIToolkitSupport);
    Q_DISABLE_COPY(UIToolkitSupport);
//!@endcond
};

} // namespace bb

#endif // BB_CORE_UITOOLKITSUPPORT_HPP

//!@endcond
