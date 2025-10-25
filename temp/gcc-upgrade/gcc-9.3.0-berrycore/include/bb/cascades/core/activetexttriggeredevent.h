/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 * 
 */

#ifndef cascades_activetextactivationevent_h
#define cascades_activetextactivationevent_h

#include <bb/cascades/bbcascades_global.h>

#include <QDebug>

#include <bb/cascades/core/event.h>

namespace bb {
    namespace cascades {

    class ActiveTextTriggeredEventPrivate;

    /*!
     * @brief An event indicating that an active text has been activated.
     *
     * @details The event provides the HREF of the active text as well as the actual text. 
     * The HREF is @c null if the active text is not created from a markup link.
     *
     * @xmlonly
     *     <apigrouping group="User interface/Events"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT ActiveTextTriggeredEvent: public Event
    {
    private:        
        Q_OBJECT

        /*!
         * @brief The text of the active text.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QString text READ text FINAL CONSTANT)

        /*!
         * @brief The HREF of the active text.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QUrl href READ href FINAL CONSTANT)

    public:
        /*!
         * @brief Constructs a activation event.
         *
         * @param text The text of the event which has been activated.
         * @param href The HREF of the event which has been activated.
         *
         * @since BlackBerry 10.0.0
         */
        ActiveTextTriggeredEvent(QString text, QUrl href);

        /*!
         * @brief Destructs the event.
         *
         * @since BlackBerry 10.0.0
         */
        virtual ~ActiveTextTriggeredEvent();

        /*!
         * @brief Retrieves the event type.
         *
         * @return The event type.
         *
         * @since BlackBerry 10.0.0
         */        
        static QEvent::Type type();

        /*!
         * @brief Retrieves the text of the event.
         *
         * @return The text of the event.
         *
         * @since BlackBerry 10.0.0
         */
        QString text() const;

        /*!
         * @brief Retrieves the HREF of the event.
         *
         * @return The HREF of the event.
         *
         * @since BlackBerry 10.0.0
         */
        QUrl href() const;

        /*!
         * @brief Aborts the activation of the default active text action.
         *
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE void abort();

        /*!
         * @brief Retrieves a string representation of the event.
         *
         * @return A string representing the event.
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE virtual QString toDebugString() const;

    private:
        /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(ActiveTextTriggeredEvent)
        Q_DISABLE_COPY(ActiveTextTriggeredEvent)
        /*! @endcond */
    };

    /*!
     * @brief Streams debug output about an @c ActiveTextTriggeredEvent to the @c QDebug stream object.
     *
     * @param dbg                       The @c QDebug stream.
     * @param ActiveTextTriggeredEvent  The @c ActiveTextTriggeredEvent whose debug information will be output.
     * @return                          The @c QDebug stream.
     */
    BBCASCADES_EXPORT QDebug operator<<(QDebug dbg, const ActiveTextTriggeredEvent &ActiveTextTriggeredEvent);

}
}

QML_DECLARE_TYPE(bb::cascades::ActiveTextTriggeredEvent)

#endif /* cascades_activetexttriggeredevent_h */
