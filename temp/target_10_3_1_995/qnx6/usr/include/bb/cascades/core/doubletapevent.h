/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 * 
*/

#ifndef cascades_doubletapevent_h
#define cascades_doubletapevent_h

#include <bb/cascades/core/abstractgestureevent.h>

namespace bb {
    namespace cascades {

    class DoubleTapEventPrivate;

    /*!
     * @brief Double tap events are emitted when the user performs a double tap gesture.
     *
     * The double tap event class holds information about a double tap gesture, such as the
     * x and @c x coordinates.
     *
     * For events of this class, %AbstractGestureEvent::x/y represents the release
     * coordinates of the second tap.
     *
     * To listen to double tap events received on a control, add a DoubleTapHandler gesture 
     * handler to the control.
     *
     * @see DoubleTapHandler
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
    class BBCASCADES_EXPORT DoubleTapEvent: public AbstractGestureEvent
    {
    private:        
        Q_OBJECT
                
    public:
        /*!
         * @brief Constructs a double tap event.
         *
         * @param x - @c x coordinate of the double tap, in local coordinate system.
         * @param y - @c x coordinate of the double tap, in local coordinate system.
         * @return A double tap event.
         *
         * @since BlackBerry 10.0.0
         */
        explicit DoubleTapEvent(float x, float y);

        /*!
         * @brief Destructs the double tap event.
         *
         * @since BlackBerry 10.0.0
         */
        virtual ~DoubleTapEvent();

        /*!
         * @brief Retrieves the double tap event type.
         *
         * @return The double tap event type.
         *
         * @since BlackBerry 10.0.0
         */        
        static QEvent::Type type();

    private:
        /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(DoubleTapEvent)
        Q_DISABLE_COPY(DoubleTapEvent)
        /*! @endcond */
    };
}
}

QML_DECLARE_TYPE(bb::cascades::DoubleTapEvent)

#endif /* cascades_doubletapevent_h */
