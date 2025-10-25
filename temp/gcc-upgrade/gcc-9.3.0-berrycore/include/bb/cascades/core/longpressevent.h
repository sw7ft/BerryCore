/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 * 
*/

#ifndef cascades_longpressevent_h
#define cascades_longpressevent_h

#include <bb/cascades/core/abstractgestureevent.h>

namespace bb {
    namespace cascades {

    class LongPressEventPrivate;

    /*! 
     * @brief Long press events are emitted when the user performs a long press gesture.
     *
     * @details The long press event class holds information about a long press gesture, such as the
     * @c x and @c y coordinates.
     *
     * If input source is trackpad then the @c x and @c y coordinates are the center point of
     * the control.
     *
     * To listen to long press events received from a control, add a @c LongPressHandler gesture 
     * handler to the control.
     *
     * @see LongPressHandler
     *
     * @xmlonly
     * <qml>
     *     <class register="yes"/>
     * </qml>
     * @endxmlonly
     *
     * @xmlonly
     *     <apigrouping group="User interface/Events"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT LongPressEvent: public AbstractGestureEvent
    {
    private:
        Q_OBJECT

    public:
        /*!
         * @brief Constructs a long press event.
         *
         * The value of the @c inputSource property is set to its default value
         * @c InputSource::Touch.
         *
         * @param x The @c x coordinate of the long press, in the local coordinate system.
         * @param y The @c y coordinate of the long press, in the local coordinate system.
         *
         * @return A long press event.
         *
         * @since BlackBerry 10.0.0
         */
        LongPressEvent(float x, float y);

        /*!
         * @brief Constructs a long press event.
         *
         * @param inputSource - The @c input source of the long press.
         * @param x The @c x coordinate of the long press, in the local coordinate system.
         * @param y The @c y coordinate of the long press, in the local coordinate system.
         *
         * @return A long press event.
         *
         * @since BlackBerry 10.3.1
         */
        Q_REVISION(4)
        LongPressEvent(bb::cascades::InputSource::Type inputSource, float x, float y);

        /*!
         * @brief Destructs the long press event.
         *
         * @since BlackBerry 10.0.0
         */
        virtual ~LongPressEvent();

        /*!
         * @brief Retrieves the tap event type.
         *
         * @return The long press event type.
         *
         * @since BlackBerry 10.0.0
         */
        static QEvent::Type type();

    private:
        /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(LongPressEvent)
        Q_DISABLE_COPY(LongPressEvent)
        /*! @endcond */
    };
}
}

QML_DECLARE_TYPE(bb::cascades::LongPressEvent)

#endif /* cascades_longpressevent_h */
