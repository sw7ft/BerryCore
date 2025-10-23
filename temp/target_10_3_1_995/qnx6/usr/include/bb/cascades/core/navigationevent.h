/* Copyright (C) 2014 BlackBerry Limited. All rights reserved. */

#ifndef cascades_navigationevent_h
#define cascades_navigationevent_h

#include <bb/cascades/bbcascades_global.h>

#include <QDebug>

#include <bb/cascades/core/event.h>
#include <bb/cascades/core/navigationeventtype.h>

namespace bb {
    namespace cascades {

    class NavigationEventPrivate;
    class VisualNode;

    /*!
     * @brief Navigation events are emitted when the user navigates by swiping, tap or long press on a trackpad or similar.
     *
     * In order to listen to navigation events, you need to add a
     * @c %NavigationHandler to the @c %VisualNode::eventHandlers.
     *
     * @see NavigationHandler, VisualNode::eventHandlers()
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
     * @since BlackBerry 10.3.1
     */
    class BBCASCADES_EXPORT NavigationEvent: public Event
    {
    private:
        Q_OBJECT

        /*!
         * @brief The navigation type of the event.
         *
         * @since BlackBerry 10.3.1
         */
        Q_PROPERTY(bb::cascades::NavigationEventType::Type navigationEventType READ navigationEventType FINAL)

        /*!
         * @brief The multiplier of the event.
         *
         * The multiplier is an integer describing how many navigation steps this event corresponds
         * to. The navigation should be done in the direction described by @c navigationEventType.
         *
         * @since BlackBerry 10.3.1
         */
        Q_PROPERTY(int multiplier READ multiplier FINAL CONSTANT)

    public:
        /*!
         * @brief Creates a @c %NavigationEvent
         *
         * @param navigationEventType The navigation type.
         *
         * @since BlackBerry 10.3.1
         */
        NavigationEvent(NavigationEventType::Type navigationEventType);

        /*!
         * @brief Creates a @c %NavigationEvent
         *
         * @param navigationEventType The navigation type.
         * @param multiplier The multiplier for the navigation event.
         *
         * @since BlackBerry 10.3.1
         */
        NavigationEvent(NavigationEventType::Type navigationEventType, int multiplier);

        /*!
         * @brief Destructs the event.
         *
         * @since BlackBerry 10.3.1
         */
        virtual ~NavigationEvent();

        /*!
         * @brief The navigation type of the event.
         *
         * @return The navigation type.
         *
         * @since BlackBerry 10.3.1
         */
        bb::cascades::NavigationEventType::Type navigationEventType() const;

        /*!
         * @brief Retrieves the event type.
         *
         * @return The event type.
         *
         * @since BlackBerry 10.3.1
         */
        static QEvent::Type type();

        /*!
         * @brief Retrieves the number of navigation steps this event corresponds to.
         *
         * @return The event multiplier.
         *
         * @since BlackBerry 10.3.1
         */
        int multiplier() const;

        /*!
         * @brief Retrieves a string representation of the navigation event.
         *
         * @return A string representing the navigation event.
         *
         * @since BlackBerry 10.3.1
         */
        Q_INVOKABLE virtual QString toDebugString() const;

    private:
        /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(NavigationEvent)
        Q_DISABLE_COPY(NavigationEvent)
        /*! @endcond */
    };

    /*!
     * @brief Streams debug output about a NavigationEvent to the QDebug stream object.
     *
     * @param dbg              The QDebug stream.
     * @param navigationEvent  The NavigationEvent to output debug information about.
     * @return                 The QDebug stream.
     */
    BBCASCADES_EXPORT QDebug operator<<(QDebug dbg, const NavigationEvent &navigationEvent);

}
}

QML_DECLARE_TYPE(bb::cascades::NavigationEvent)

#endif /* cascades_navigationevent_h */
