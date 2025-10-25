/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_listrearrangehandler_h
#define cascades_listrearrangehandler_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/core/uiobject.h>

namespace bb {
    namespace cascades {

    class RearrangeHandlerPrivate;
    class RearrangeMoveStartEvent;
    class RearrangeMoveUpdateEvent;
    class RearrangeMoveEndEvent;
    class RearrangeMoveAbortEvent;
    class IRearrangeHost;

   /*!
    * @brief The object type of the rearrange handler used to manage rearrange sessions. 
    * An application should never construct a handler itself. Instead use the already attached handler 
    * of the @c ListView by accessing the @c ListView::rearrangeHandler property.
    *
    * For more information about rearranging lists, see 
    * the [Rearranging lists documentation](https://developer.blackberry.com/native/documentation/cascades/ui/lists/list_view_selection.html#rearranginglists103).
    *
    * @xmlonly
    * <apigrouping group="User interface/List"/>
    * @endxmlonly
    *
    * @since BlackBerry 10.3.0 
    */
    class BBCASCADES_EXPORT RearrangeHandler : public UIObject
    {
    private:
        Q_OBJECT

      /*! @brief Activates or deactivates rearrange mode on the hosting @c ListView.
      *
      * @since BlackBerry 10.3.0 
      */
      Q_PROPERTY( bool active READ active WRITE setActive NOTIFY activeChanged FINAL)

    public:
       /*! \cond PRIVATE */
       /*!@brief Constructs a @c %RearrangeHandler. An application should never construct a
        * handler itself. Instead use the already attached handler of the @c ListView by accessing
        * the @c ListView::rearrangeHandler property.
        * 
        * @since BlackBerry 10.3.0 
        */
        explicit RearrangeHandler( IRearrangeHost* pHost = 0 );

        /*! @brief Destroys the @c %RearrangeHandler. An application should never construct a
        * handler itself. Instead use the already attached handler of the @c ListView by accessing
        * the @c ListView::rearrangeHandler property.
        *
        * @since BlackBerry 10.3.0 
        */
        virtual ~RearrangeHandler();
        /*! \endcond */


      /*!
      * @brief Returns the current value of the property @c RearrangeHandler::active.
      *
      * @return The active state of the handler.
      *
      * @see setActive(), @c RearrangeHandler::active
      *
      * @since BlackBerry 10.3.0
      */
      Q_SLOT bool active();

      /*!
      * @brief Sets the value for the property @c RearrangeHandler::active.
      *
      * @param active The new value for the property.
      *
      * @see active(), @c RearrangeHandler::active
      *
      * @since BlackBerry 10.3.0
      */
      Q_SLOT void setActive( bool active );

Q_SIGNALS:

     /*! @brief Emitted when the active state of the handler changes.
      *
      * @param active The new active state of the handler.
      *
      * @since BlackBerry 10.3.0 
      */
      void activeChanged( bool active );

      /*!
      * @brief Emitted when a move session is started.
      *
      * @param event An event object containing details and support for handling the signal.
      *        The event object must not be stored for later use, because it is destroyed after emitting the signal.
      *
      * @see @c RearrangeMoveStartEvent, @c moveUpdated(), @c moveEnded(), @c moveAborted()
      *
      * @since BlackBerry 10.3.0 
      */
      void moveStarted( bb::cascades::RearrangeMoveStartEvent* event );

      /*! @brief Emitted when the item being rearranged is hovering over a possible target destination. 
      * 
      * The application can either choose to respond to this signal by performing the move within the data 
      * model. In such case, the empty space in the list layout will move to the new drop target. The user still 
      * retains control over the item visual. 
      * If an application chooses to ignore the request, the list layout will remain unchanged. The 
      * user still retains control over the drag visual.
      *
      * **IMPORTANT**: Signalling the move operation to the list must be done by emitting the 
      * DataModel::itemMoved() signal. Notifying the list through pairs of DataModel::itemRemoved() 
      * DataModel::itemAdded() will cause the move session to be aborted since the list will receive
      * a remove signal for the item being rearranged.
      *
      * @param event An event object containing details and support for handling the signal.
      *        The event object must not be stored for later use, because it is destroyed after emitting the signal.
      *
      * @see @c RearrangeMoveUpdateEvent, @c DataModel::itemMoved(), @c moveStarted(), @c moveEnded(), @c moveAborted()
      *
      * @since BlackBerry 10.3.0
      */
      void moveUpdated( bb::cascades::RearrangeMoveUpdateEvent* event );

      /*! @brief Emitted when the currently active rearrange session is ended
      * normally.
      *
      * @param event An event object containing details and support for handling the signal.
      *        The event object must not be stored for later use, because it is destroyed after emitting the signal.
      *
      * @see @c RearrangeMoveEndEvent, @c moveStarted(), @c moveUpdated(), @c moveAborted()
      *
      * @since BlackBerry 10.3.0
      */
      void moveEnded( bb::cascades::RearrangeMoveEndEvent* event );

      /*! @brief Emitted when the currently active move session is aborted. This occurs when the framework 
      * forcefully terminates the session, thereby interrupting any current user interaction.
      * Note that the item will remain where it was last moved to, that is, the position it had after the most recent
      * moveUpdated() signal that wasn't denied.
      *
      * @param event An event object containing details and support for handling the signal.
      *        The event object must not be stored for later use, because it is destroyed after emitting the signal.
      *
      * @see @c RearrangeMoveEndEvent, @c moveStarted(), @c moveUpdated(), @c moveEnded()
      *
      * @since BlackBerry 10.3.0
      */
      void moveAborted( bb::cascades::RearrangeMoveEndEvent* event );

    private:
        /*! \cond PRIVATE */
        Q_DECLARE_PRIVATE(RearrangeHandler)
        Q_DISABLE_COPY(RearrangeHandler)
        /*! \endcond */

    }; 

    /*!
    * @brief The object type used for events passed with the signal RearrangeHandler::moveStarted().
    *
    * @see RearrangeMoveUpdateEvent, RearrangeMoveEndEvent
    *
    * @xmlonly
    * <apigrouping group="User interface/List"/>
    * @endxmlonly
    *
    * @since BlackBerry 10.3.0 
    */
    class BBCASCADES_EXPORT RearrangeMoveStartEvent : public QObject
    {
      Q_OBJECT

    public:
      /*! \cond PRIVATE */

      /*!@brief Constructs a @c %RearrangeMoveStartEvent.
      *
      * @since BlackBerry 10.3.0 
      */
      explicit RearrangeMoveStartEvent( QVariantList startIndexPath );

      /*! @brief Destroys the @c %RearrangeMoveStartEvent.
      *
      * @since BlackBerry 10.3.0 
      */
      virtual ~RearrangeMoveStartEvent();

     /*! \endcond */

    public:
      /*!
      * @brief The index path of the item lifted by the user.
      *
      * @since BlackBerry 10.3.0 
      */
      Q_PROPERTY(QVariantList startIndexPath READ startIndexPath FINAL)

    public:

      /*!
      * @brief Returns the current value of the RearrangeMoveStartEvent::startIndexPath property.
      *
      * @return The current property value.
      *
      * @since BlackBerry 10.3.0 
      */
      Q_SLOT QVariantList startIndexPath();

    private:

      /*! \cond PRIVATE */
      QVariantList m_startIndexPath;
      /*! \endcond */

    };

    /*!
    * @brief The object type used for events passed with the signal RearrangeHandler::moveUpdated().
    *
    * @see RearrangeMoveStartEvent, RearrangeMoveEndEvent
    *
    * @xmlonly
    * <apigrouping group="User interface/List"/>
    * @endxmlonly
    *
    * @since BlackBerry 10.3.0 
    */
    class BBCASCADES_EXPORT RearrangeMoveUpdateEvent : public QObject
    {
      Q_OBJECT

    public:
      /*! \cond PRIVATE */

      /*!@brief Constructs a @c RearrangeMoveUpdateEvent.
      * @since BlackBerry 10.3.0 
      */
      explicit RearrangeMoveUpdateEvent( QVariantList fromIndexPath, QVariantList toIndexPath );
       
      /*! @brief Destroys the @c RearrangeMoveUpdateEvent.
      * @since BlackBerry 10.3.0 
      */
      virtual ~RearrangeMoveUpdateEvent();

     /*! \endcond */
    public:
      /*!
      * @brief The index path of the item that is currently being rearranged. Note that this
      * index path doesn't necessarily correspond to the start index path of the move session.
      *
      * @see RearrangeMoveStartEvent
      *
      * @since BlackBerry 10.3.0 
      */
      Q_PROPERTY(QVariantList fromIndexPath READ fromIndexPath FINAL)

      /*!
      * @brief The suggested target position of the item being rearranged.
      *
      * @since BlackBerry 10.3.0 
      */
      Q_PROPERTY(QVariantList toIndexPath READ toIndexPath FINAL)

    public:

      /*!
      * @brief Returns the current value of the RearrangeMoveUpdateEvent::fromIndexPath property.
      *
      * @return The current property value.
      *
      * @since BlackBerry 10.3.0 
      */
      Q_SLOT QVariantList fromIndexPath();

      /*!
      * @brief Returns the current value of the RearrangeMoveUpdateEvent::toIndexPath property.
      *
      * @return The current property value.
      *
      * @since BlackBerry 10.3.0 
      */
      Q_SLOT QVariantList toIndexPath();

      /*!
      * @brief Should be invoked by the application when the proposed move operation isn't carried out.
      *
      * @since BlackBerry 10.3.0 
      */
      Q_SLOT void denyMove();

    public:

    /*! \cond PRIVATE */
    Q_SIGNAL void moveDenied( QVariantList fromIndexPath, QVariantList toIndexPath );
    /*! \endcond */

    private:

      /*! \cond PRIVATE */
      QVariantList m_fromIndexPath;
      QVariantList m_toIndexPath;
      /*! \endcond */
    };

    /*!
    * @brief The object type used for events passed with the signals RearrangeHandler::moveEnded and RearrangeHandler::moveAborted).
    *
    * @see RearrangeMoveStartEvent, RearrangeMoveUpdateEvent
    *
    * @xmlonly
    * <apigrouping group="User interface/List"/>
    * @endxmlonly
    *
    * @since BlackBerry 10.3.0 
    */
    class BBCASCADES_EXPORT RearrangeMoveEndEvent : public QObject
    {
      Q_OBJECT

    public:
      /*! \cond PRIVATE */

      /*!@brief Constructs a @c %RearrangeMoveEndEvent.
      * @since BlackBerry 10.3.0 
      */
      explicit RearrangeMoveEndEvent( QVariantList endIndexPath );
       
      /*! @brief Destroys the @c %RearrangeMoveEndEvent.
      * @since BlackBerry 10.3.0 
      */
      virtual ~RearrangeMoveEndEvent ();

      /*! \endcond */
    public:
     /*!
      * @brief The resulting position of the rearranged item.
      *
      * @since BlackBerry 10.3.0 
      */
      Q_PROPERTY(QVariantList endIndexPath READ endIndexPath FINAL)
    
    public:

      /*!
      * @brief Returns the current value of the RearrangeMoveEndEvent::endIndexPath property.
      *
      * @return The current property value.
      *
      * @since BlackBerry 10.3.0 
      */
      Q_SLOT QVariantList endIndexPath();

    private:

      /*! \cond PRIVATE */
      QVariantList m_endIndexPath;
      /*! \endcond */
    };
  }
}


QML_DECLARE_TYPE(bb::cascades::RearrangeHandler)
QML_DECLARE_TYPE(bb::cascades::RearrangeMoveStartEvent)
QML_DECLARE_TYPE(bb::cascades::RearrangeMoveEndEvent)
QML_DECLARE_TYPE(bb::cascades::RearrangeMoveAbortEvent)
QML_DECLARE_TYPE(bb::cascades::RearrangeMoveUpdateEvent)


#endif // cascades_listrearrangehandler_h
