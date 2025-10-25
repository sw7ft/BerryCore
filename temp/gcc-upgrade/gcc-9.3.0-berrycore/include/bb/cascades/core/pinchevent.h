/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 * 
*/

#ifndef cascades_pinchevent_h
#define cascades_pinchevent_h

#include <bb/cascades/bbcascades_global.h>

#include <QDebug>

#include <bb/cascades/core/abstractgestureevent.h>

namespace bb {
    namespace cascades {

    class PinchEventPrivate;

    /*!
     * @brief Pinch events are emitted when the user performs a pinch gesture.
     *
     * The pinch event class holds information about a pinch gesture, such as the
     * mid point of the gesture, the pinch ratio and the rotation.
     *
     * For events of this class, @c %AbstractGestureEvent::x/y represents the coordinates 
     * of the finger that first touched the screen, equivalent to @c touchPointX(0).
     *
     * To listen to pinch events received on a control, add a @c PinchHandler gesture 
     * handler to the control.
     *
     * @see PinchHandler
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
    class BBCASCADES_EXPORT PinchEvent: public AbstractGestureEvent
    {
    private:        
        Q_OBJECT
        
        /*!
         * @brief The @c x coordinate of midpoint in local coordinate system.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float midPointX READ midPointX FINAL CONSTANT)
        /*!
         * @brief The @c y coordinate of midpoint in local coordinate system.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float midPointY READ midPointY FINAL CONSTANT)
        /*!
         * @brief The ratio between the initial pinch distance and the current pinch distance.
         * The pinch ratio is filtered to achieve a smoother gesture.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float pinchRatio READ pinchRatio FINAL CONSTANT)
        /*!
         * @brief The rotation (in degrees, clockwise) relative to the start positions of the fingers.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float rotation READ rotation FINAL CONSTANT)
        /*!
         * @brief The distance (in pixels) between the touch points.
         * The distance is filtered to achieve a smoother gesture.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float distance READ distance FINAL CONSTANT)
        
    public:
        /*!
         * @brief Constructs a pinch event.
         *
         * @param midPointX  The @c x coordinate of midpoint in local coordinate system.
         * @param midPointY  The @c x coordinate of midpoint in local coordinate system.
         * @param pinchRatio The ratio between the initial pinch distance and the current pinch distance.
         * @param rotation   The rotation (in degrees, clockwise) relative to the start positions of the fingers.
         * @param distance   The distance (in pixels) between the touch points.
         * @return A pinch event.
         *
         * @since BlackBerry 10.0.0
         */
        PinchEvent(float midPointX, float midPointY, float pinchRatio, float rotation, float distance);

        /*!
         * @brief Destructs the pinch event.
         *
         * @since BlackBerry 10.0.0
         */
        virtual ~PinchEvent();

        /*!
         * @brief Retrieves the pinch event type.
         *
         * @return The pinch event type.
         *
         * @since BlackBerry 10.0.0
         */        
        static QEvent::Type type();

        /*!
         * @brief Retrieves the @c x coordinate of the midpoint in local coordinate system.
         *
         * @return The @c X coordinate of midpoint.
         *
         * @since BlackBerry 10.0.0
         */
        float midPointX() const;

        /*!
         * @brief Retrieves the @c x coordinate of the midpoint in local coordinate system.
         *
         * @return The @c y coordinate of midpoint.
         *
         * @since BlackBerry 10.0.0
         */
        float midPointY() const;

        /*!
         * @brief Retrieves the pinch ratio.
         *
         * The pinch ratio is filtered to achieve a smoother gesture.
         *
         * @return The pinch ratio.
         *
         * @since BlackBerry 10.0.0
         */
        float pinchRatio() const;

        /*!
         * @brief Retrieves the current pinch rotation.
         *
         * The rotation is expressed in degrees, clockwise, relative to the start positions of the fingers.
         *
         * @return The pinch rotation.
         *
         * @since BlackBerry 10.0.0
         */
        float rotation() const;

        /*!
         * @brief Retrieves the current distance (in pixels) between the touch points.
         *
         * The distance is filtered to achieve a smoother gesture.
         *
         * @return The distance between the touch points.
         *
         * @since BlackBerry 10.0.0
         */
        float distance() const;

        /*!
         * @brief Retrieves the @c x coordinate (in local coordinate system) for the touch point indicated by @c pointIndex.
         *
         * A pinch event will always contain two touch points, and they are indexed in the order they hit the screen.
         * If @c touchPoint is out-of-range, @c 0.0 is returned.
         *
         * @param pointIndex The index of the touch point to retrieve the @c x coordinate from.
         *
         * @return The local @c x coordinate of touch point indicated by @c pointIndex, or @c 0.0 if @c pointIndex is out-of-range.
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE float touchPointX(int pointIndex) const;

        /*!
         * @brief Retrieves the @c x coordinate (in local coordinate system) for the touch point indicated by @c pointIndex.
         *
         * A pinch event will always contain two touch points, and they are indexed in the order they hit the screen.
         * If @c touchPoint is out-of-range, @c 0.0 is returned.
         *
         * @param pointIndex The index of the touch point to retrieve the @c x coordinate from.
         * 
         * @return The local @c x coordinate of touch point indicated by @c pointIndex, or @c 0.0 if @c pointIndex is out-of-range.
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE float touchPointY(int pointIndex) const;
  
        /*!
         * @brief Retrieves a string representation of the pinch event.
         *
         * @return A string representing the pinch event.
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE virtual QString toDebugString() const;

    private:
        /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(PinchEvent)
        Q_DISABLE_COPY(PinchEvent)
        /*! @endcond */
    };

    /*!
     * @brief Streams debug output about a @c PinchEvent to the @c QDebug stream object.
     *
     * @param dbg          The @c QDebug stream.
     * @param pinchEvent   The @c PinchEvent to output debug information about.
     * 
     * @return             The @c QDebug stream.
     */
    BBCASCADES_EXPORT QDebug operator<<(QDebug dbg, const PinchEvent &pinchEvent);


}
}

QML_DECLARE_TYPE(bb::cascades::PinchEvent)

#endif /* cascades_pinchevent_h */
