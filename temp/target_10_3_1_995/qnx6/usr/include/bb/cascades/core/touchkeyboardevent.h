/* Copyright (c) 2013 BlackBerry. All rights reserved. */

#ifndef cascades_touchkeyboardevent_h
#define cascades_touchkeyboardevent_h

#include <bb/cascades/bbcascades_global.h>

#include <QDebug>
#include <QtCore/QString>

#include <bb/cascades/core/event.h>
#include <bb/cascades/core/touchtype.h>

namespace bb {
    namespace cascades {

    class TouchKeyboardEventPrivate;
    class VisualNode;

    /*!
     * @brief Touch keyboard events are emitted when the user touches the touch keyboard.
     *
     * In order to listen to events from the touch keyboard, you need to add a
     * @c %TouchKeyboardHandler to the @c %VisualNode::eventHandlers.
     *
     * @see TouchKeyboardHandler, VisualNode::eventHandlers()
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
     * @since BlackBerry 10.3.0
     */
    class BBCASCADES_EXPORT TouchKeyboardEvent: public Event
    {
    private:
        Q_OBJECT

        /*!
         * @brief The @c x coordinate of the touch event relative to the screen.
         *
         * @warning The screen coordinates depend on the physical placement of the
         *          "touch keyboard" relative to the main "touch screen". It is
         *          therefore not recommended to use these as absolute coordinates,
         *          as the offset of the "touch keyboard" from the "touch screen" is
         *          both device-dependent and orientation-dependent.
         *
         * @since BlackBerry 10.3.0
         */
        Q_PROPERTY(float screenX READ screenX FINAL)

        /*!
         * @brief The @c y coordinate of the touch event relative to the screen.
         *
         * @warning The screen coordinates depend on the physical placement of the
         *          "touch keyboard" relative to the main "touch screen". It is
         *          therefore not recommended to use these as absolute coordinates,
         *          as the offset of the "touch keyboard" from the "touch screen" is
         *          both device-dependent and orientation-dependent.
         *
         * @since BlackBerry 10.3.0
         */
        Q_PROPERTY(float screenY READ screenY FINAL)

        /*!
         * @brief The touch type of the event.
         *
         * @since BlackBerry 10.3.0
         */
        Q_PROPERTY(bb::cascades::TouchType::Type touchType READ touchType FINAL)

        /*!
         * @brief The finger id of the event.
         *
         * Each finger is assigned a unique finger id during its touch interaction.
         *
         * @since BlackBerry 10.3.0
         */
        Q_PROPERTY(int fingerId READ fingerId FINAL)

    public:
        /*!
         * @brief Creates a @c %TouchKeyboardEvent
         *
         * @param touchType The type of touch.
         * @param screenX   Touch @c x coordinate, relative to screen.
         * @param screenY   Touch @c y coordinate, relative to screen.
         * @param fingerId  Touch @c finger id.
         *
         * @since BlackBerry 10.3.0
         */
        TouchKeyboardEvent(TouchType::Type touchType, float screenX, float screenY, int fingerId);

        /*!
         * @brief Destructs the event.
         *
         * @since BlackBerry 10.3.0
         */
        virtual ~TouchKeyboardEvent();

        /*!
         * @brief Retrieves the @c x coordinate of the touch event relative to the screen.
         *
         * @warning The screen coordinates depend on the physical placement of the
         *          "touch keyboard" relative to the main "touch screen". It is
         *          therefore not recommended to use these as absolute coordinates,
         *          as the offset of the "touch keyboard" from the "touch screen" is
         *          both device-dependent and orientation-dependent.
         *
         * @return The @c x coordinate of the touch event.
         *
         * @since BlackBerry 10.3.0
         */
        float screenX() const;

        /*!
         * @brief Retrieves the @c y coordinate of the touch event relative to the screen.
         *
         * @warning The screen coordinates depend on the physical placement of the
         *          "touch keyboard" relative to the main "touch screen". It is
         *          therefore not recommended to use these as absolute coordinates,
         *          as the offset of the "touch keyboard" from the "touch screen" is
         *          both device-dependent and orientation-dependent.
         *
         * @return The @c y coordinate of the touch event.
         *
         * @since BlackBerry 10.3.0
         */
        float screenY() const;

        /*!
         * @brief The touch type of the event.
         *
         * @return The touch type.
         *
         * @since BlackBerry 10.3.0
         */
        bb::cascades::TouchType::Type touchType() const;

        /*!
         * @brief The finger id of the event.
         *
         * Each finger is assigned a unique finger id during its touch interaction.
         *
         * @return The finger id.
         *
         * @since BlackBerry 10.3.0
         */
        int fingerId() const;

        /*!
         * @brief Retrieves the event type.
         *
         * @return The event type.
         *
         * @since BlackBerry 10.3.0
         */
        static QEvent::Type type();

        /*!
         * @brief Retrieves a string representation of the touch event.
         *
         * @return A string representing the touch event.
         *
         * @since BlackBerry 10.3.0
         */
        Q_INVOKABLE virtual QString toDebugString() const;

    private:
        /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(TouchKeyboardEvent)
        Q_DISABLE_COPY(TouchKeyboardEvent)
        /*! @endcond */
    };

    /*!
     * @brief Streams debug output about a TouchKeyboardEvent to the QDebug stream object.
     *
     * @param dbg   The QDebug stream.
     * @param event The TouchKeyboardEvent to output debug information about.
     * @return      The QDebug stream.
     */
    BBCASCADES_EXPORT QDebug operator<<(QDebug dbg, const TouchKeyboardEvent &event);

}
}

QML_DECLARE_TYPE(bb::cascades::TouchKeyboardEvent)

#endif /* cascades_touchkeyboardevent_h */
