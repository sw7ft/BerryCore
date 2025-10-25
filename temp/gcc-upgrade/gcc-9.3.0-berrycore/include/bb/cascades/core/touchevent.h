/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 * 
*/

#ifndef cascades_touchevent_h
#define cascades_touchevent_h

#include <bb/cascades/bbcascades_global.h>

#include <QDebug>

#include <bb/cascades/core/event.h>
#include <bb/cascades/core/touchtype.h>

namespace bb {
    namespace cascades {

    class TouchEventPrivate;
    class VisualNode;

    /*!
     * @brief Touch events are emitted when the user touches the screen.
     *
     * The touch event class holds information about a touch, such as the
     * touch coordinates and the type of touch.
     *
     * To listen to touch events received on a control, connect a slot to 
     * one of the touch signals exposed in the visual node base class.
     *
     * @see VisualNode::touch(), VisualNode::touchCapture()
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
     * @since BlackBerry 10.0.0
     */    
    class BBCASCADES_EXPORT TouchEvent: public Event
    {
    private:        
        Q_OBJECT
        
        /*!
         * @brief  @c x coordinate of the touch relative to the window.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float windowX READ windowX FINAL)
        /*!
         * @brief  @c y coordinate of the touch relative to the window.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float windowY READ windowY FINAL)
        /*!
         * @brief  @c x coordinate of the touch relative to the visual node where the touch signal is emitted.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float localX READ localX FINAL)
        /*!
         * @brief  @c y coordinate of the touch relative to the visual node where the touch signal is emitted.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float localY READ localY FINAL)
        /*!
         * @brief The touch target of this event.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::VisualNode* target READ target FINAL)
        /*!
         * @brief The touch type of the event.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::TouchType::Type touchType READ touchType FINAL)
        /*!
         * @brief A Boolean expression indicating whether the Alt modifier key was pressed when the touch occurred.
         *
         * @since BlackBerry 10.3.0
         */
        Q_PROPERTY(bool altPressed READ isAltPressed REVISION 3 FINAL CONSTANT)
        /*!
         * @brief A Boolean expression indicating whether the Shift modifier key was pressed when the touch occurred.
         *
         * @since BlackBerry 10.3.0
         */
        Q_PROPERTY(bool shiftPressed READ isShiftPressed REVISION 3 FINAL CONSTANT)
        /*!
         * @brief A Boolean expression indicating whether the Control modifier key was pressed when the touch occurred.
         *
         * @since BlackBerry 10.3.0
         */
        Q_PROPERTY(bool ctrlPressed READ isCtrlPressed REVISION 3 FINAL CONSTANT)

    public:
        /*!
         * @brief Constructs a touch event.
         *
         * @param touchType - The type of touch.
         * @param screenX - Touch @c x coordinate relative to the screen.
         * @param screenY - Touch @c x coordinate relative to the screen.
         * @param windowX - Touch @c x coordinate relative to the window.
         * @param windowY - Touch @c x coordinate relative to the window.
         * @param localX - Touch @c x coordinate relative to the node that emitts the touch signal.
         * @param localY - Touch @c x coordinate relative to the node that emitts the touch signal.
         * @param target - The touch target of this event.
         * @return A touch event.
         *
         * @since BlackBerry 10.0.0
         */
        TouchEvent(TouchType::Type touchType, float screenX, float screenY, float windowX, float windowY, float localX, float localY, VisualNode* target);

        /*!
         * @brief Destructs the touch event.
         *
         * @since BlackBerry 10.0.0
         */
        virtual ~TouchEvent();

        /*!
         * @brief Retrieves the touch event type.
         *
         * @return The touch event type.
         *
         * @since BlackBerry 10.0.0
         */        
        static QEvent::Type type();

        /*!
         * @brief Retrieves the @c x coordinate of the touch relative to the screen.
         *
         * @return The @c x coordinate of the touch.
         *
         * @since BlackBerry 10.0.0
         */
        float screenX() const;

        /*!
         * @brief Retrieves the @c y coordinate of the touch relative to the screen.
         *
         * @return The @c y coordinate of the touch.
         *
         * @since BlackBerry 10.0.0
         */
        float screenY() const;

        /*!
         * @brief Retrieves the @c x coordinate of the touch relative to the window.
         *
         * @return The @c x coordinate of the touch.
         *
         * @since BlackBerry 10.0.0
         */
        float windowX() const;

        /*!
         * @brief Retrieves the @c y coordinate of the touch relative to the window.
         *
         * @return The @c y coordinate of the touch.
         *
         * @since BlackBerry 10.0.0
         */
        float windowY() const;

        /*!
         * @brief Retrieves the @c x coordinate of the touch relative to the node that emitts the touch signal.
         *
         * @return The @c x coordinate of the touch.
         *
         * @since BlackBerry 10.0.0
         */
        float localX() const;

        /*!
         * @brief Retrieves the @c y coordinate of the touch relative to the node that emitts the touch signal.
         *
         * @return The @c y coordinate of the touch.
         *
         * @since BlackBerry 10.0.0
         */
        float localY() const;        

        /*!
         * @brief Retrieves the touch target of this event.
         *
         * @return The touch target.
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::VisualNode* target() const;
        
        /*!
         * @brief Retrieves the touch type of the event.
         *
         * @return The touch type.
         *
         * @since BlackBerry 10.0.0
         */ 
        bb::cascades::TouchType::Type touchType() const;

        /*!
         * @brief Convenience function for checking if the touch type returned from touchType() is TouchType::Move.
         *
         * @return @c true if the touch type is TouchType::Move.
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE bool isMove() const;

        /*!
         * @brief Convenience function for checking if the touch type returned from touchType() is TouchType::Up.
         *
         * @return @c true if the touch type is TouchType::Up.
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE bool isUp() const;

        /*!
         * @brief Convenience function for checking if the touch type returned from touchType() is TouchType::Down.
         *
         * @return @c true if the touch type is TouchType::Down.
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE bool isDown() const;

        /*!
         * @brief Convenience function for checking if the touch type returned from touchType() is TouchType::Cancel.
         *
         * @return @c true if the touch type is TouchType::Cancel.
         *
         * @since BlackBerry 10.0.0
         */        
        Q_INVOKABLE bool isCancel() const;

        /*!
         * @brief Retrieves the alt modifier key state during the event.
         *
         * @return @c true if the alt modifier key was pressed during the event, and @c false otherwise.
         *
         * @since BlackBerry 10.3.0
         */
        Q_REVISION(3)
        bool isAltPressed() const;

        /*!
         * @brief Retrieves the shift modifier key state during the event.
         *
         * @return @c true if the shift modifier key was pressed during the event, and @c false otherwise.
         *
         * @since BlackBerry 10.3.0
         */
        Q_REVISION(3)
        bool isShiftPressed() const;

        /*!
         * @brief Retrieves the ctrl modifier key state during the event.
         *
         * @return @c true if the ctrl modifier key was pressed during the event, and @c false otherwise.
         *
         * @since BlackBerry 10.3.0
         */
        Q_REVISION(3)
        bool isCtrlPressed() const;

        /*!
         * @brief Retrieves a string representation of the touch event.
         *
         * @return A string representing the touch event.
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE virtual QString toDebugString() const;

    private:
        /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(TouchEvent)
        Q_DISABLE_COPY(TouchEvent)
        /*! @endcond */
    };

    /*!
     * @brief Streams debug output about a TouchEvent to the QDebug stream object.
     *
     * @param dbg          The QDebug stream.
     * @param touchEvent   The TouchEvent to output debug information about.
     * @return             The QDebug stream.
     */
    BBCASCADES_EXPORT QDebug operator<<(QDebug dbg, const TouchEvent &touchEvent);

}
}

QML_DECLARE_TYPE(bb::cascades::TouchEvent)

#endif /* cascades_touchevent_h */
