/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 * 
*/

#ifndef cascades_keylistener_h
#define cascades_keylistener_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/UIObject>

namespace bb {
    namespace cascades {

      class KeyEvent;
      class KeyListenerPrivate;

       /*!  
        * @brief Enables controls to be notified on key events that are introduced by user interaction
        * with the keyboard.        
        *
        * A key listener can be attached to objects that inherit from @c Control and @c AbstractPane classes.
        * Please note that the key events propagate from the control in focus up to the root of the scene.
        * In case no control is currently in focus, all key events are redirected to the root.                
        *
        * A key listener has 3 signals @c keyEvent, @c keyPressed and @c keyReleased. The @c %keyEvent signal is emitted every
        * time a key event arrives at the control. The @c %keyPressed is only emitted in case of a key 
        * press event. Similarly, the @c %keyReleased signal is only emitted as a key relese event arrives at a control
        *
        * Here's how to create an @c %KeyListener and add it to a @c %Control. 
        
        * @code
        * KeyListener* myKeyListener = KeyListener::create()
        *     .onKeyEvent(this, SLOT
        *               (onKeyEventHandler(bb::cascades::KeyEvent *)))
        *     .onKeyPressed(this, SLOT
        *               (onKeyPressedHandler(bb::cascades::KeyEvent *)))
        *     .onKeyReleased(this, SLOT
        *               (onKeyReleasedHandler(bb::cascades::KeyEvent *)));
        *
        * Page* myPage = Page::create();
        * myPage->addKeyListener(myKeyListener);
        * @endcode
        *
        * Here's another example of how to create a @c %KeyListener, this time by calling the constructor
        * and connecting it to each signal individually.
        * @code
        * KeyListener* myKeyListener = new KeyListener();
        * QObject::connect(myKeyListener, SIGNAL(keyEvent(bb::cascades::KeyEvent*)),
        *                    this, SLOT(onKeyEventHandler(KeyEvent *)));
        * QObject::connect(myKeyListener, SIGNAL(keyPressed(bb::cascades::KeyEvent*)),
        *                    this, SLOT(onKeyPressedHandler(KeyEvent *)));
        * QObject::connect(myKeyListener, SIGNAL(keyReleased(bb::cascades::KeyEvent*)),
        *                    this, SLOT(onKeyReleasedHandler(KeyEvent *)));
        *
        * Control* myControl = Control::create();
        * myControl->addKeyListener(myKeyListener);
        * @endcode
        *
        * And here's how to create a key listener for a @c %Control using QML:
        * @code
        * Control {
        *     keyListeners: [
        *         KeyListener {
        *             onKeyEvent: {                      
        *             }
        *             
        *             onKeyPressed: {                      
        *             }
        *
        *             onKeyReleased: {                      
        *             }        
        *         }
        *     ]
        * }
        * @endcode
        *
        * @xmlonly
        *     <apigrouping group="User interface/Events"/>
        * @endxmlonly
        *
        *
        * @since BlackBerry 10.1.0
        */

      class BBCASCADES_EXPORT KeyListener : public UIObject {
            Q_OBJECT

        public:
            explicit KeyListener(UIObject *parent=0);
            virtual ~KeyListener();

Q_SIGNALS:
           /*!
            * @brief Emitted when a key event is received by the control that is attached to this key listener. 
            *
            * @since BlackBerry 10.1.0
            */
            void keyEvent(bb::cascades::KeyEvent *event);

           /*!
            * @brief Emitted when a key press event is received by the control that is attached to this key listener. 
            *
            * @since BlackBerry 10.1.0
            */
            void keyPressed(bb::cascades::KeyEvent *event);

           /*!
            * @brief Emitted when a key release event is received by the control that is attached to this key listener. 
            *
            * @since BlackBerry 10.1.0
            */
            void keyReleased(bb::cascades::KeyEvent *event);

            /*!
             * @brief Emitted when a key long press event is received by the control that is attached to this key listener.
             *
             * @since BlackBerry 10.2.0
             */
            Q_REVISION(2)
            void keyLongPressed(bb::cascades::KeyEvent *event);

            /*!
             * @brief Emitted when a key released after long press event is received by the control that is attached to this key listener.
             *
             * @since BlackBerry 10.2.0
             */
            Q_REVISION(2)
            void keyLongReleased(bb::cascades::KeyEvent *event);

      public:

          /*!
           * @brief A Builder template for constructing a @c %KeyListener. To retrieve the builder, call
           * @c KeyListener::create().
           *
           * @since BlackBerry 10.1.0
           */
          template <typename BuilderType, typename BuiltType>
          class TBuilder : public BaseObject::TBuilder<BuilderType, BuiltType>
          {
          protected:
              TBuilder(BuiltType* node) : BaseObject::TBuilder<BuilderType, BuiltType>(node)
              {
              }
          public:
              /*!
               * @brief A convenience method for connecting the slot of the receiver, passed in as a parameter, to
               * the @c keyEvent() signal with the default connection type @c Qt::AutoConnection.
               *
               * Example:
               * @code
               * KeyListener *keyListener = KeyListener::create()
               *     .onKeyEvent(this, SLOT(onKeyEventHandler(bb::cascades::KeyEvent*)));
               * @endcode
               *
               * @param receiver A receiver object. This object cannot be @c null.
               * @param method The name of the slot to connect to the receiver object.
               *               The receiver object cannot be @c null.
               *
               * @see BaseObject::TBuilder::connect()
               *
               * @since BlackBerry 10.1.0
               */
              BuilderType& onKeyEvent(const QObject* receiver, const char *method) {
                  this->connect(SIGNAL(keyEvent(bb::cascades::KeyEvent*)), receiver, method);
                  return this->builder();
              }
              /*!
               * @brief A convenience method for connecting the slot of the receiver, passed in as a parameter, to
               * the @c keyPressed() signal with the default connection type @c Qt::AutoConnection.
               *
               * Example:
               * @code
               * KeyListener *keyListener = KeyListener::create()
               *     .onKeyPressed(this, SLOT(onKeyPressedHandler(bb::cascades::KeyEvent*)));
               * @endcode
               *
               * @param receiver A receiver object. This object cannot be @c null.
               * @param method The name of the slot to connect to the receiver object.
               *               The receiver object cannot be @c null.
               *
               * @see BaseObject::TBuilder::connect()
               *
               * @since BlackBerry 10.1.0
               */
              BuilderType& onKeyPressed(const QObject* receiver, const char *method) {
                  this->connect(SIGNAL(keyPressed(bb::cascades::KeyEvent*)), receiver, method);
                  return this->builder();
              }
              /*!
               * @brief A convenience method for connecting a passed receiver's slot to
               * the @c keyReleased() signal with the default connection type of 
               * Qt::AutoConnection.
               *
               * Example:
               * @code
               * KeyListener *keyListener = KeyListener::create()
               *     .onKeyReleased(this, SLOT(onKeyReleasedHandler(bb::cascades::KeyEvent*)));
               * @endcode
               *
               * @param receiver A receiver object. This object cannot be @c null.
               * @param method The name of the slot to connect to the receiver object.
               *               The receiver object cannot be @c null.
               *               
               * @see BaseObject::TBuilder::connect()
               *
               * @since BlackBerry 10.1.0
               */
              BuilderType& onKeyReleased(const QObject* receiver, const char *method) {
                  this->connect(SIGNAL(keyReleased(bb::cascades::KeyEvent*)), receiver, method);
                  return this->builder();
              }
              /*!
               * @brief A convenience method for connecting the slot of the receiver, passed in as a parameter, to
               * the @c keyLongPressed() signal with the default connection type @c Qt::AutoConnection.
               *
               * Example:
               * @code
               * KeyListener *keyListener = KeyListener::create()
               *     .onKeyLongPressed(this, SLOT(onKeyLongPressedHandler(bb::cascades::KeyEvent*)));
               * @endcode
               *
               * @param receiver A receiver object. This object cannot be @c null.
               * @param method The name of the slot to connect to the receiver object.
               *               The receiver object cannot be @c null.
               *
               * @see BaseObject::TBuilder::connect()
               *
               * @since BlackBerry 10.2.0
               */
              BuilderType& onKeyLongPressed(const QObject* receiver, const char *method) {
                  this->connect(SIGNAL(keyLongPressed(bb::cascades::KeyEvent*)), receiver, method);
                  return this->builder();
              }
              /*!
               * @brief A convenience method for connecting a passed receiver's slot to
               * the @c keyLongReleased() signal with the default connection type of
               * Qt::AutoConnection.
               *
               * Example:
               * @code
               * KeyListener *keyListener = KeyListener::create()
               *     .onKeyLongReleased(this, SLOT(onKeyLongReleasedHandler(bb::cascades::KeyEvent*)));
               * @endcode
               *
               * @param receiver A receiver object. This object cannot be @c null.
               * @param method The name of the slot to connect to the receiver object.
               *               The receiver object cannot be @c null.
               *
               * @see BaseObject::TBuilder::connect()
               *
               * @since BlackBerry 10.2.0
               */
              BuilderType& onKeyLongReleased(const QObject* receiver, const char *method) {
                  this->connect(SIGNAL(keyLongReleased(bb::cascades::KeyEvent*)), receiver, method);
                  return this->builder();
              }
          };
          
          /*!
           * @brief A Builder template for constructing a @c KeyListener.
           *
           * To retrieve the Builder, call @c KeyListener::create().
           *
           * @since BlackBerry 10.1.0
           */
          class Builder : public TBuilder<Builder, KeyListener>
          {
          public:
              explicit Builder() : TBuilder<Builder, KeyListener>(new KeyListener()) {}
          };
          
          /*!
           * @brief Creates and returns a Builder for constructing a @c %KeyListener.
           *
           * The following sample uses the Builder to create a @c %KeyListener:
           * @code
           * KeyListener* shortcut = KeyListener::create();
           * @endcode
           *
           * @return A builder used for constructing a @c %KeyListener.
           *
           * @since BlackBerry 10.1.0
           */
          static Builder create() {
              return Builder();
          }
          
        private:
            Q_DECLARE_PRIVATE(KeyListener)
        };
    }
}


QML_DECLARE_TYPE(bb::cascades::KeyListener)


#endif // cascades_keylistener_h
