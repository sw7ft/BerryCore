/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 * 
*/

#ifndef cascades_touchenterevent_h
#define cascades_touchenterevent_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/core/event.h>
#include <bb/cascades/core/touchtype.h>

namespace bb {
    namespace cascades {

    class TouchEnterEventPrivate;
    class VisualNode;

    /*!
     * @brief The touch enter event is sent as parameter to the touchEnter signal from VisualNode.
     *
     * @see VisualNode::touchEnter()
     *
     * @xmlonly
     * <qml>
     *     <class abstract="yes"/>
     * </qml>
     *     <apigrouping group="User interface/Events"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */    
    class BBCASCADES_EXPORT TouchEnterEvent: public Event
    {
    private:        
        Q_OBJECT
        
    public:
        /*!
         * Constructs a touch enter event.
         *
         * @since BlackBerry 10.0.0
         */
        TouchEnterEvent();

        /*!
         * Destructs the touch enter event.
         *
         * @since BlackBerry 10.0.0
         */
        virtual ~TouchEnterEvent();

        /*!
         * @brief Retrieves the event type.
         *
         * @return The event type.
         *
         * @since BlackBerry 10.0.0
         */        
        static QEvent::Type type();
  
        /*!
         * Retrieves a string representation of the touch enter event.
         *
         * @return A string representing the touch enter event.
         *
         * @since BlackBerry 10.0.0
         */     
        Q_INVOKABLE virtual QString toDebugString() const;

    private:
        /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(TouchEnterEvent)
        Q_DISABLE_COPY(TouchEnterEvent)
        /*! @endcond */
    };
}
}

QML_DECLARE_TYPE(bb::cascades::TouchEnterEvent)

#endif /* cascades_touchenterevent_h */
