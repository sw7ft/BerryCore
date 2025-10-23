/* Copyright (C) 2012-2013 Research In Motion Limited.  */

#ifndef cascades_webpageeventhandler_h
#define cascades_webpageeventhandler_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/core/touchtype.h>

#include <QtCore/QObject>

namespace bb {
  namespace cascades {

    class Event;
    class WebPageEventHandlerPrivate;

    /*!
     * @brief A class that injects events into a @c WebPage.
     *
     * When rendering a @c WebPage using a @c WebPageCompositor in a custom OpenGL scene, you can
     * map screen events from the screen window coordinate system to the webpage content coordinate system depending
     * on how the page is projected onto the screen, and inject them using this API.
     *
     * This API can also be used to inject mouse and keyboard events.
     *
     * You can create events using @c createTouchEvent().
     *
     * This object can be created on any thread. However, the object has an affinity for the thread it was created on,
     * and may not be used on any other thread.
     *
     * @note Events are handled asynchronously, please refer to @c handleEvent(Event*) and @c eventHandled(Event*) for
     *       more detailed information.
     *
     * An example of multi-threaded use is as follows:
     *
     * @snippet tad/examples/controls/webpageeventhandler/src/screenthread.h webpageeventhandler1
     *
     * @snippet tad/examples/controls/webpageeventhandler/src/screenthread.cpp webpageeventhandler2
     *
     * @snippet tad/examples/controls/webpageeventhandler/src/mythread.h webpageeventhandler3
     *
     * @snippet tad/examples/controls/webpageeventhandler/src/mythread.cpp webpageeventhandler4
     *
     * @snippet tad/examples/controls/webpageeventhandler/src/main.cpp webpageeventhandler5
     *
     * @c WebPageCompositor is normally used from C++, but here is an example of using @c WebPageCompositor in QML:
     *
     * @snippet tad/examples/controls/webpageeventhandlerqml/assets/main.qml webpageeventhandlerqml_qml1
     *
     * Add the following lines to the C++ main program to register @c WebPageCompositor:
     *
     * @snippet tad/examples/controls/webpageeventhandlerqml/src/webpageeventhandlerqml.cpp webpageeventhandlerqml1
     *
     * @xmlonly
     * <apigrouping group="User interface/Web"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
	 */
    class BBCASCADES_EXPORT WebPageEventHandler : public QObject {
        Q_OBJECT

    public:
        /*!
         * @brief Constructs a @c WebPageEventHandler.
         *
         * The @c WebPageEventHandler must be connected to a @c WebPage before any methods can be
         * called on it.
         *
         * @see @c connectToWebPage(const QString&).
         *
         * @param parent Optional parent for this object.
         *
         * @since BlackBerry 10.0.0
         */
        explicit WebPageEventHandler(QObject* parent = 0);
        virtual ~WebPageEventHandler();

        /**
         * @brief Creates a touch event.
         *
         * The event returned can be injected using @c handleEvent(Event*) when the app receives a @c screen_event_t
         * of type @c SCREEN_EVENT_MTOUCH_TOUCH, MOVE or RELEASE.
         *
         * You can add touch points to the event using c addTouchPoint().
         *
         * @c TouchType::Down, @c Move, and @c Up events correspond to @c SCREEN_EVENT_MTOUCH_TOUCH, @c MOVE or @c RELEASE,
         * respectively.
         *
         * @c TouchType::Cancel events are used in situations where an @c Up event will never come, for example
         * when the app decides to stop sending events for an ongoing touch interaction and instead handle the rest of
         * the sequence without any involvement of the webpage.
         *
         * An example can clarify this. Consider a scenario where touch events are used to interact with the
         * webpage, but also used to scroll the webpage.
         * A touch move should first be sent to @c handleEvent(Event*), and the caller should wait for
         * @c eventHandled() signal to be emitted. If the finger moves a certain distance from the touch down point,
         * the app may want to start scrolling instead. The webpage will expect the sequence to complete, and a
         * @c Cancel event should be injected to accomplish that.
         *
         * @see @c addTouchPoint().
         *
         * @param touchType A member of the @c TouchType::Type enum, or @c SCREEN_EVENT_MTOUCH_TOUCH, @c MOVE or @c RELEASE.
         *
         * @returns An @c Event representing a touch event. Ownership of the event is transferred to the caller.
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE bb::cascades::Event* createTouchEvent(int touchType) const;

        /*!
         * @brief Adds a touch point to a touch event.
         *
         * @c TouchType::Down and @c Up typically only have one touch point associated.
         *
         * For @c TouchType::Move one or more fingers that moved may be grouped together into one event by
         * adding multiple touch points, to reduce the number of events the webpage has to process.
         *
         * @c TouchType::Cancel events can't have any touch points.
         *
         * The parameters match those provided by the screen for @c screen_event_t instances of type @c SCREEN_EVENT_MTOUCH_TOUCH, @c MOVE or @c RELEASE.
         * The definitions of these values are found in screen/screen.h.
         *
         * The position of the screen event needs to be converted to the webpage viewable area before passing it as
         * the @c localX and @c localY parameters of this method.
         * Initially, the viewable area of the webpage is positioned at (0, 0) and the webpage uses an 1:1 scale, so
         * conversion to the webpage viewable area coordinate system is straight forward.
         * However, if a @c WebPageCompositor has been connected to the @c WebPage, the viewable
         * area of the webpage may have been changed using the compositor APIs and the application is responsible for
         * mapping the screen coordinates to the currently viewable area. This mapping also depends on where the web
         * page is rendered relative to the screen window that received the original screen event.
         *
         * @param localX Corresponds to @c SCREEN_PROPERTY_SOURCE_POSITION, mapped to the webpage viewable area coordinate system.
         * @param localY Corresponds to @c SCREEN_PROPERTY_SOURCE_POSITION, mapped to the webpage viewable area coordinate system.
         * @param screenX Corresponds to @c SCREEN_PROPERTY_POSITION.
         * @param screenY Corresponds to @c SCREEN_PROPERTY_POSITION.
         * @param id Corresponds to @c SCREEN_PROPERTY_TOUCH_ID.
         * @param pressure Corresponds to @c SCREEN_PROPERTY_TOUCH_PRESSURE.
         * @param orientation Corresponds to @c SCREEN_PROPERTY_TOUCH_ORIENTATION.
         * @param sequenceId Corresponds to @c SCREEN_PROPERTY_SEQUENCE_ID.
         * @param timestamp Corresponds to @c SCREEN_PROPERTY_TIMESTAMP.
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE void addTouchPoint(bb::cascades::Event*, int localX, int localY, int screenX, int screenY, int id, int pressure, int orientation, int sequenceId, long long timestamp) const;

        /*!
         * @brief Creates a key event.
         *
         * The event returned can be injected using @c handleEvent(Event*) when the app receives a @c screen_event_t of type @c SCREEN_EVENT_KEYBOARD.
         * The definitions of these values are found in @c screen/screen.h.
         *
         * @param scan Corresponds to @c SCREEN_PROPERTY_KEY_SCAN.
         * @param sym Corresponds to @c SCREEN_PROPERTY_KEY_SYM.
         * @param cap Corresponds to @c SCREEN_PROPERTY_KEY_CAP.
         * @param flags Corresponds to @c SCREEN_PROPERTY_KEY_FLAGS.
         * @param modifiers Corresponds to @c SCREEN_PROPERTY_KEY_MODIFIERS.
         * @param sequenceId Corresponds to @c SCREEN_PROPERTY_SEQUENCE_ID.
         * @param timestamp Corresponds to @c SCREEN_PROPERTY_TIMESTAMP.
         *
         * @returns An @c Event representing a key event. Ownership of the event is transferred to the caller.
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE bb::cascades::Event* createKeyEvent(int scan, int sym, int cap, int flags, int modifiers, int sequenceId, long long timestamp) const;

        /*!
         * @brief Creates a mouse event.
         *
         * The event returned can be injected using @c handleEvent(Event*) when the app receives a @c screen_event_t of type @c SCREEN_EVENT_POINTER.
         * The definitions of these values are found in @c screen/screen.h.
         *
         * The position of the screen event needs to be converted to the webpage viewable area before passing it as
         * the @c localX and @c localY parameters of this method.
         * Initially, the viewable area of the webpage is positioned at (0, 0) and the webpage uses an 1:1 scale, so
         * conversion to the webpage viewable area coordinate system is straight forward.
         * However, if a @c WebPageCompositor has been connected to the @c WebPage, the viewable
         * area of the webpage may have been changed using the compositor APIs and the application is responsible for
         * mapping the screen coordinates to the currently viewable area. This mapping also depends on where the web
         * page is rendered relative to the screen window that received the original screen event.
         *
         * @param buttonState Corresponds to @c SCREEN_PROPERTY_BUTTONS.
         * @param localX Corresponds to @c SCREEN_PROPERTY_SOURCE_POSITION, mapped to the webpage viewable area coordinate system.
         * @param localY Corresponds to @c SCREEN_PROPERTY_SOURCE_POSITION, mapped to the webpage viewable area coordinate system.
         * @param screenX Corresponds to @c SCREEN_PROPERTY_POSITION.
         * @param screenY Corresponds to @c SCREEN_PROPERTY_POSITION.
         * @param wheelDelta @c wheelTicks converted to a number of pixels the webpage should scroll when it receives a wheel event.
         * @param wheelTicks Corresponds to @c SCREEN_PROPERTY_MOUSE_WHEEL.
         *
         * @returns An @c Event representing a mouse event. Ownership of the event is transferred to the caller.
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE bb::cascades::Event* createMouseEvent(int buttonState, int localX, int localY, int screenX, int screenY, int wheelDelta, int wheelTicks) const;

    public Q_SLOTS:
        /*!
         * @brief Connects to a @c WebPage created on the main thread.
         *
         * @since BlackBerry 10.0.0
         */
        void connectToWebPage(const QString& uniqueId);

        /*!
         * @brief Assigns keyboard focus to the connected @c WebPage.
         *
         * @since BlackBerry 10.0.0
         */
        void setKeyboardFocus(bool focus);

        /*!
         * @brief Injects a touch, mouse or key event into the connected WebPage.
         *
         * The event to handle can be a specialized event created using @c createTouchEvent(), @c createMouseEvent()
         * or @c createKeyEvent(). It can also be a @c TouchEvent.
         *
         * The event is handled asynchronously. The @c WebPageEventHandler does not assume ownership of
         * the event, but the event must not be deleted until the @c eventHandled() signal is emitted for the event.
         *
         * If the event is accepted, the @c QEvent::isAccepted() flag will be set on the event and you can
         * check the status of that flag in a slot connected to @c eventHandled() signal.
         *
         * An example can clarify this. Consider a scenario where touch events are used to interact with the
         * webpage, but also used to scroll the webpage.
         * A touch move should first be sent to @c handleEvent(Event*), and the caller should wait for
         * the @c eventHandled() signal to be emitted. Then the @c QEvent::isAccepted() flag should be checked.
         * If it's found that the event is accepted, any default action associated with the event,
         * in this case scrolling, should not be performed. Otherwise, go ahead and call
         * @c WebPageCompositor::scrollToPoint() to scroll the webpage.
         *
         * @param event An @c Event created using @c createTouchEvent(), @c createMouseEvent(), @c createKeyEvent()
         *              or a @c TouchEvent.
         *
         * @since BlackBerry 10.0.0
         */
        void handleEvent(bb::cascades::Event* event);

    Q_SIGNALS:
        /*!
         * @brief Emitted when successfully connected to a webpage.
         *
         * @since BlackBerry 10.0.0
         */
        void connectionSucceeded();

        /*!
         * @brief Emitted when connection failed.
         *
         * @since BlackBerry 10.0.0
         */
        void connectionFailed();

        /*!
         * @brief Emitted when interaction with the webpage causes it to request the virtual keyboard to be shown.
         *
         * @param layout One of the @c virtualkeyboard_layout_t values from @c bps/virtualkeyboard.h.
         * @param enterKey One of the @c virtualkeyboard_enter_t value from @c bps/virtualkeyboard.h.
         *
         * @since BlackBerry 10.0.0
         */
        void keyboardShowRequested(int layout, int enterKey);

        /*!
         * @brief Emitted when interaction with the webpage causes it to request the virtual keyboard to be hidden.
         *
         * @since BlackBerry 10.0.0
         */
        void keyboardHideRequested();

        /*!
         * Emitted asynchronously when the connected @c WebPage finishes processing an event previously
         * injected by calling @c handleEvent(Event*). At a minimum, a slot connected to this signal should delete
         * the event.
         *
         * Example slot implementation:
         *
         * @snippet tad/examples/controls/webpageeventhandler/src/myclass.cpp webpageeventhandler6
         *
         * @since BlackBerry 10.0.0
         */
        void eventHandled(bb::cascades::Event* event);

    private:
        Q_DECLARE_PRIVATE(WebPageEventHandler)
        Q_DISABLE_COPY(WebPageEventHandler)

        WebPageEventHandlerPrivate* const d_ptr;
    };

  } // namespace cascades
} // namespace bb

#endif // cascades_webpageeventhandler_h

