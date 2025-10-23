/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 * 
*/

#ifndef cascades_tapevent_h
#define cascades_tapevent_h

#include <bb/cascades/core/abstractgestureevent.h>

namespace bb {
    namespace cascades {

    class TapEventPrivate;

    /*!
     * @brief Tap events are emitted when the user performs a tap gesture.
     *
     * The tap event class holds information about a tap gesture, such as the
     * x and @c x coordinates.
     *
     * If input source is trackpad then the @c x and @c y coordinates are the center
     * point of the control.
     *
     * To listen to tap events received on a control, add a TapHandler gesture 
     * handler to the control.
     *
     * @see TapHandler
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
    class BBCASCADES_EXPORT TapEvent: public AbstractGestureEvent
    {
    private:
        Q_OBJECT

    public:
        /*!
         * @brief Constructs a tap event.
         *
         * The value of the @c inputSource property is set to its default value
         * @c InputSource::Touch.
         *
         * @param x - @c x coordinate of the tap, in local coordinate system.
         * @param y - @c x coordinate of the tap, in local coordinate system.
         * @return A tap event.
         *
         * @since BlackBerry 10.0.0
         */
        TapEvent(float x, float y);

        /*!
         * @brief Constructs a tap event.
         *
         * @param inputSource - The @c input source of the tap.
         * @param x - @c x coordinate of the tap, in local coordinate system.
         * @param y - @c x coordinate of the tap, in local coordinate system.
         * @return A tap event.
         *
         * @since BlackBerry 10.3.1
         */
        Q_REVISION(4)
        TapEvent(bb::cascades::InputSource::Type inputSource, float x, float y);

        /*!
         * @brief Destructs the tap event.
         *
         * @since BlackBerry 10.0.0
         */
        virtual ~TapEvent();

        /*!
         * @brief Retrieves the tap event type.
         *
         * @return The tap event type.
         *
         * @since BlackBerry 10.0.0
         */
        static QEvent::Type type();

    private:
        /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(TapEvent)
        Q_DISABLE_COPY(TapEvent)
        /*! @endcond */
    };
}
}

QML_DECLARE_TYPE(bb::cascades::TapEvent)

#endif /* cascades_tapevent_h */
