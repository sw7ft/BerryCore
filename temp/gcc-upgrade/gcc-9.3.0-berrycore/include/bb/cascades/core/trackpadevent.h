/*!
 * @copyright
 * Copyright Research In Motion Limited, 2014
 * Research In Motion Limited. All rights reserved.
 * 
*/

#ifndef cascades_trackpadevent_h
#define cascades_trackpadevent_h

#include <bb/cascades/bbcascades_global.h>

#include <QDebug>

#include <bb/cascades/core/event.h>
#include <bb/cascades/core/trackpadeventtype.h>

namespace bb {
    namespace cascades {

    class TrackpadEventPrivate;
    class VisualNode;

    /*!
     * @brief Trackpad events are emitted when the user swipes, presses, or releases the trackpad.
     *
     * In order to listen to events from the trackpad, you need to add a
     * @c %TrackpadHandler to the @c %VisualNode::eventHandlers.
     *
     * @see TrackpadHandler, VisualNode::eventHandlers()
     *
     * @xmlonly
     * <qml>
     * <class register="yes"/>
     * </qml>
     * @endxmlonly
     *
     * @xmlonly
     *     <apigrouping group="User interface/Events"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.3.1
     */
    class BBCASCADES_EXPORT TrackpadEvent: public Event
    {
    private:
        Q_OBJECT

        /*!
         * @brief The horizontal displacement since the last TrackpadEvent.
         *
         * @since BlackBerry 10.3.1
         */
        Q_PROPERTY(float deltaX READ deltaX FINAL)

        /*!
        * @brief The vertical displacement since the last TrackpadEvent.
         *
         * @since BlackBerry 10.3.1
         */
        Q_PROPERTY(float deltaY READ deltaY FINAL)

        /*!
         * @brief The trackpad type of the event.
         *
         * @since BlackBerry 10.3.1
         */
        Q_PROPERTY(bb::cascades::TrackpadEventType::Type trackpadEventType READ trackpadEventType FINAL)

        /*!
         * @brief A Boolean expression indicating whether the Alt modifier key was pressed when the trackpad event occurred.
         *
         * @since BlackBerry 10.3.1
         */
        Q_PROPERTY(bool altPressed READ isAltPressed FINAL CONSTANT)

        /*!
         * @brief A Boolean expression indicating whether the Shift modifier key was pressed when the trackpad event occurred.
         *
         * @since BlackBerry 10.3.1
         */

        Q_PROPERTY(bool shiftPressed READ isShiftPressed FINAL CONSTANT)

        /*!
         * @brief A Boolean expression indicating whether the Control modifier key was pressed when the trackpad event occurred.
         *
         * @since BlackBerry 10.3.1
         */
        Q_PROPERTY(bool ctrlPressed READ isCtrlPressed FINAL CONSTANT)

    public:
        /*!
         * @brief Creates a @c %TrackpadEvent
         *
         * @param trackpadEventType The type of trackpad event.
         * @param deltaX            The horizontal displacement since the last trackpad event.
         * @param deltaY            The vertical displacement since the last trackpad event.
         * @param isAltPressed      The pressed state of alt key.
         * @param isShiftPressed    The pressed state of shift key.
         * @param isCtrlPressed     The pressed state of ctrl key.
         *
         * @since BlackBerry 10.3.1
         */
        TrackpadEvent(TrackpadEventType::Type trackpadEventType, float deltaX, float deltaY,
                      bool isAltPressed, bool isShiftPressed, bool isCtrlPressed);

        /*!
         * @brief Destructs the event.
         *
         * @since BlackBerry 10.3.1
         */
        virtual ~TrackpadEvent();

        /*!
         * @brief Retrieves the horizontal displacement since the last TrackpadEvent.
         *
         * @return The horizontal displacement since the last TrackpadEvent.
         *
         * @since BlackBerry 10.3.1
         */
        float deltaX() const;

        /*!
         * @brief Retrieves the horizontal displacement since the last TrackpadEvent.
         *
         * @return The vertical displacement since the last TrackpadEvent.
         *
         * @since BlackBerry 10.3.1
         */
        float deltaY() const;

        /*!
         * @brief The trackpad event type.
         *
         * @return The trackpad event type.
         *
         * @since BlackBerry 10.3.1
         */
        bb::cascades::TrackpadEventType::Type trackpadEventType() const;

        /*!
         * @brief Convenience function for checking if the trackpad event type returned from trackpadEventType() is TrackpadEventType::Begin.
         *
         * @return @c true if the trackpad event type is TrackpadEventType::Begin.
         *
         * @since BlackBerry 10.3.1
         */
        Q_INVOKABLE bool isBegin() const;

        /*!
         * @brief Convenience function for checking if the trackpad event type returned from trackpadEventType() is TrackpadEventType::End.
         *
         * @return @c true if the trackpad event type is TrackpadEventType::End.
         *
         * @since BlackBerry 10.3.1
         */
        Q_INVOKABLE bool isEnd() const;

        /*!
         * @brief Convenience function for checking if the trackpad event type returned from trackpadEventType() is TrackpadEventType::Move.
         *
         * @return @c true if the trackpad event type is TrackpadEventType::Move.
         *
         * @since BlackBerry 10.3.1
         */
        Q_INVOKABLE bool isMove() const;

        /*!
         * @brief Convenience function for checking if the trackpad is pressed.
         *
         * @return @c true if the trackpad is pressed.
         *
         * @since BlackBerry 10.3.1
         */
        Q_INVOKABLE bool isPressed() const;

        /*!
         * @brief Retrieves the alt modifier key state during the event.
         *
         * @return @c true if the alt modifier key was pressed during the event, and @c false otherwise.
         *
         * @since BlackBerry 10.3.1
         */
        bool isAltPressed() const;

        /*!
         * @brief Retrieves the shift modifier key state during the event.
         *
         * @return @c true if the shift modifier key was pressed during the event, and @c false otherwise.
         *
         * @since BlackBerry 10.3.1
         */
        bool isShiftPressed() const;

        /*!
         * @brief Retrieves the ctrl modifier key state during the event.
         *
         * @return @c true if the ctrl modifier key was pressed during the event, and @c false otherwise.
         *
         * @since BlackBerry 10.3.1
         */
        bool isCtrlPressed() const;

        /*!
         * @brief Retrieves the event type.
         *
         * @return The event type.
         *
         * @since BlackBerry 10.3.1
         */
        static QEvent::Type type();

        /*!
         * @brief Retrieves a string representation of the trackpad event.
         *
         * @return A string representing the trackpad event.
         *
         * @since BlackBerry 10.3.1
         */
        Q_INVOKABLE virtual QString toDebugString() const;

    private:
        /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(TrackpadEvent)
        Q_DISABLE_COPY(TrackpadEvent)
        /*! @endcond */
    };

    /*!
     * @brief Streams debug output about a TrackpadEvent to the QDebug stream object.
     *
     * @param dbg            The QDebug stream.
     * @param trackpadEvent  The TrackpadEvent to output debug information about.
     * @return               The QDebug stream.
     */
    BBCASCADES_EXPORT QDebug operator<<(QDebug dbg, const TrackpadEvent &trackpadEvent);

}
}

QML_DECLARE_TYPE(bb::cascades::TrackpadEvent)

#endif /* cascades_trackpadevent_h */
