/*!
 * @copyright
 * Copyright Research In Motion Limited, 2011-2013
 * Research In Motion Limited. All rights reserved.
 * 
 */

#ifndef cascades_abstractgestureevent_h
#define cascades_abstractgestureevent_h

#include <bb/cascades/bbcascades_global.h>
#include <QDebug>
#include <bb/cascades/core/event.h>
#include <bb/cascades/core/inputsource.h>

namespace bb {
    namespace cascades {

    class AbstractGestureEventPrivate;

    /*! 
     * @brief This is the base class for all gesture events.
     *
     * See specialized classes for details.
     *
     * @see PinchEvent, TapEvent, DoubleTapEvent, LongPressEvent
     *
     * @xmlonly
     *        <apigrouping group="User interface/Events"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT AbstractGestureEvent: public Event
    {
    private:
        Q_OBJECT

        /*!
         * @brief The  @c x coordinate of the event, in local coordinate system.
         *
         * The meaning of this can vary between specialized classes. For more information,
         * see gestures that make use of more than one touch point.
         *
         * If the input source is trackpad then the @c x coordinate will be the center point
         * of the control.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float x READ x FINAL CONSTANT)
        /*!
         * @brief The  @c y coordinate of the event, in local coordinate system.
         *
         * The meaning of this can vary between specialized classes. For more information,
         * see gestures that make use of more than one touch point.
         *
         * If the input source is trackpad then the @c y coordinate will be the center point
         * of the control.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float y READ y FINAL CONSTANT)
        /*!
         * @brief The input source of the event.
         *
         * @since BlackBerry 10.3.1
         */
        Q_PROPERTY(bb::cascades::InputSource::Type inputSource READ inputSource CONSTANT REVISION 4 FINAL)

    public:
        /*!
         * @brief Destructs the gesture event.
         *
         * @since BlackBerry 10.0.0
         */
        virtual ~AbstractGestureEvent();

        /*!
         * @brief Retrieves the gesture event type.
         *
         * @return The gesture event type.
         *
         * @since BlackBerry 10.0.0
         */
        static QEvent::Type type();

        /*!
         * @brief Retrieves the @c x coordinate of the event, in local coordinate system.
         *
         * @return X coordinate of the event.
         *
         * @since BlackBerry 10.0.0
         */
        float x() const;

        /*!
         * @brief Retrieves the @c x coordinate of the event, in local coordinate system.
         *
         * @return Y coordinate of the event.
         *
         * @since BlackBerry 10.0.0
         */
        float y() const;

        /*!
         * @brief Retrieves the input source of the event.
         *
         * @return The input source.
         *
         * @since BlackBerry 10.3.1
         */
        Q_REVISION(4)
        bb::cascades::InputSource::Type inputSource() const;

        /*!
         * @brief Retrieves a string representation of the gesture event.
         *
         * @return A string representing the gesture event.
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE virtual QString toDebugString() const;

    protected:
    /*! @cond PRIVATE */
        AbstractGestureEvent(AbstractGestureEventPrivate &d_ptr, QEvent::Type type);
    /*! @endcond */

    private:
    /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(AbstractGestureEvent)
        Q_DISABLE_COPY(AbstractGestureEvent)
    /*! @endcond */
    };

    /*!
     * @brief Streams debug output about a AbstractGestureEvent to the QDebug stream object.
     *
     * @param dbg                    The QDebug stream.
     * @param abstractGestureEvent   The AbstractGestureEvent to output debug information about.
     * @return                       Returns the QDebug stream.
     */
    BBCASCADES_EXPORT QDebug operator<<(QDebug dbg, const AbstractGestureEvent &abstractGestureEvent);


}
}

QML_DECLARE_TYPE(bb::cascades::AbstractGestureEvent)

#endif /* cascades_abstractgestureevent_h */
