/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
*/

#ifndef cascades_event_h
#define cascades_event_h

#include <bb/cascades/bbcascades_global.h>

#include <QtCore/QEvent>
#include <QMetaType>
#include <QtCore/QTime>
#include <QtCore/QObject>
#include <QtDeclarative/QtDeclarative>
#include <QDebug>

#include <bb/cascades/core/propagationphase.h>

namespace bb {
    namespace cascades {

    class UIObject;
    class EventPrivate;
    
    /*!
     * @brief Base class for events.
     *
     * @details The event base class holds general information about an event, such as
     * the @c %timestamp when emitted and the @c #propagationPhase it is delivered in.
     *
     * @xmlonly
     *     <qml>
     *         <class register="yes"/>
     *     </qml>
     * @endxmlonly
     *
     * @xmlonly
     *     <apigrouping group="User interface/Events"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT Event : public QObject, public QEvent
    {
    private:        
        Q_OBJECT
        
        /*!
         * @brief Timestamp taken when the event was emitted.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QTime timestamp READ timestamp FINAL)
        /*!
         * @brief The propagation phase the event was received in.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::PropagationPhase::Type propagationPhase READ propagationPhase FINAL)

    public:
        /*!
         * @brief Destructs the event.
         *
         * @since BlackBerry 10.0.0
         */
        virtual ~Event();
               
        /*!
         * @brief Retrieves a timestamp taken when the event was emitted.
         *
         * \return The time when the event was emitted.
         *
         * @since BlackBerry 10.0.0
         */
        QTime timestamp() const;
                
        /*!
         * @brief Retrieves the propagation phase that this event was sent in.
         *
         * \return The propagation phase.
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::PropagationPhase::Type propagationPhase() const;
        
        /*!
         * @brief Retrieves a string representation of the event.
         *
         * \return A string representing the event.
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE virtual QString toDebugString() const;

    protected:   
        /*! @cond PRIVATE */
        Event(QEvent::Type _type);
        Event(EventPrivate &_d_ptr, QEvent::Type _type);
        EventPrivate * const d_ptr;
        /*! @endcond */
        
    private:
        /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(Event)
        Q_DISABLE_COPY(Event)
        /*! @endcond */
    };

    /*!
     * @brief Streams debug output about an Event to the QDebug stream object.
     *
     * @param dbg     The QDebug stream.
     * @param event   The Event to output debug information about.
     * 
     * @return        The QDebug stream.
     */             
    BBCASCADES_EXPORT QDebug operator<<(QDebug dbg, const Event &event);
    
}
}

QML_DECLARE_TYPE(bb::cascades::Event)

#endif /* cascades_event_h */

