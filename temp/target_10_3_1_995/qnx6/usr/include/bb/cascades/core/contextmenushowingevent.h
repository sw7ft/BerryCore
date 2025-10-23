/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 * 
 */

#ifndef cascades_contextmenushowingevent_h
#define cascades_contextmenushowingevent_h

#include <bb/cascades/bbcascades_global.h>

#include <QDebug>

#include <bb/cascades/core/event.h>

namespace bb {
    namespace cascades {

    class ContextMenuShowingEventPrivate;

    /*! 
     * @brief An event indicating that the Context menu is about to be displayed.
     *
     * @details This event provides the coordinates of where the user pressed to
     * invoke the menu (@c %touchX, @c %touchY properties), as well as a
     * way to abort the showing of the menu using @c abort() method.
     *
     * @see ContextMenuHandler
     *
     * @xmlonly
     *     <apigrouping group="User interface/Events"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT ContextMenuShowingEvent: public Event
    {
    private:        
        Q_OBJECT

        /*!
         * @brief The @c  x coordinate of the event, in the local coordinate system.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float touchX READ touchX FINAL CONSTANT)
        /*!
         * @brief The @c  x coordinate of the event, in the local coordinate system.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float touchY READ touchY FINAL CONSTANT)

    public:
        /*!
         * @brief Constructs a showing event.
         *
         * @param x The @c  x coordinate of the event that caused the menu to be shown,
         * in the local coordinate system.
         * @param y The @c  x coordinate of the event that caused the menu to be shown,
         * in the local coordinate system.
         *
         * @since BlackBerry 10.0.0
         */
        ContextMenuShowingEvent(float x, float y);

        /*!
         * @brief Destructs the event.
         *
         * @since BlackBerry 10.0.0
         */
        virtual ~ContextMenuShowingEvent();

        /*!
         * @brief Retrieves the event type.
         *
         * @return The event type.
         *
         * @since BlackBerry 10.0.0
         */        
        static QEvent::Type type();

        /*!
         * @brief Retrieves the @c  x coordinate of the event, in the local coordinate system.
         *
         * @return The x coordinate of the event.
         *
         * @since BlackBerry 10.0.0
         */
        float touchX() const;

        /*!
         * @brief Retrieves the @c  x coordinate of the event, in the local coordinate system.
         *
         * @return The y coordinate of the event.
         *
         * @since BlackBerry 10.0.0
         */
        float touchY() const;

        /*!
         * @brief Aborts the showing of the Context menu.
         *
         * @see ContextMenuHandler::showing()
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE void abort();

        /*!
         * @brief Retrieves a string representation of the event.
         *
         * @return A string representing the gesture event.
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE virtual QString toDebugString() const;

    private:
        /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(ContextMenuShowingEvent)
        Q_DISABLE_COPY(ContextMenuShowingEvent)
        /*! @endcond */
    };

    /*!
     * @brief Streams debug output about a @c ContextMenuShowingEvent to the @c QDebug stream object.
     *
     * @param dbg                       The @c QDebug stream.
     * @param contextMenuShowingEvent   The @c ContextMenuShowingEvent to output debug information about.
     * @return                          The @c QDebug stream.
     */
    BBCASCADES_EXPORT QDebug operator<<(QDebug dbg, const ContextMenuShowingEvent &contextMenuShowingEvent);

}
}

QML_DECLARE_TYPE(bb::cascades::ContextMenuShowingEvent)

#endif /* cascades_contextmenushowingevent_h */
