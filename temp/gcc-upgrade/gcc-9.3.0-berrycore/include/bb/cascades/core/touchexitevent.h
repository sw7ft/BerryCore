/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 * 
*/

#ifndef cascades_touchexitevent_h
#define cascades_touchexitevent_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/core/event.h>
#include <bb/cascades/core/touchtype.h>

namespace bb {
    namespace cascades {

    class TouchExitEventPrivate;
    class VisualNode;

    /*!
     * @brief The touch exit event is sent as parameter to the touchExit signal from VisualNode.
     *
     * @see VisualNode::touchExit()
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
    class BBCASCADES_EXPORT TouchExitEvent: public Event
    {
    private:
        Q_OBJECT

    public:
        /*!
         * Constructs a touch exit event.
         *
         * @since BlackBerry 10.0.0
         */
        explicit TouchExitEvent();

        /*!
         * Destructs the touch exit event.
         *
         * @since BlackBerry 10.0.0
         */
        virtual ~TouchExitEvent();

        /*!
         * @brief Retrieves the event type.
         *
         * @return The event type.
         *
         * @since BlackBerry 10.0.0
         */
        static QEvent::Type type();

        /*!
         * Retrieves a string representation of the touch exit event.
         *
         * \return A string representing the touch exit event.
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE virtual QString toDebugString() const;

    private:
        /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(TouchExitEvent)
        Q_DISABLE_COPY(TouchExitEvent)
        /*! @endcond */
    };

}
}

QML_DECLARE_TYPE(bb::cascades::TouchExitEvent)

#endif /* cascades_touchexitevent_h */
