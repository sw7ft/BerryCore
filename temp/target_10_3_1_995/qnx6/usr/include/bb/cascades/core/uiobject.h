/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 * 
*/

#ifndef cascades_uiobject_h
#define cascades_uiobject_h

#include <bb/cascades/bbcascades_global.h>

#include <QtCore/QObject>
#include <QtDeclarative/QtDeclarative>
#include <QtDeclarative/QDeclarativeListProperty>
#include <QtCore/QDebug>

#include <bb/cascades/BaseObject>
#include <bb/cascades/UIConfig>

namespace bb {
    namespace cascades {

    class Event;
    class UIObjectPrivate;

    /*!
     * @brief The base for all Cascades UI classes.
     *
     * @c %UIObject extends @c BaseObject by adding functionality for subscribing to receive events
     * targeted to this object; and adding an @c attachedObjects property which
     * allows declaratively adding children to derived classes' instances in QML.
     *
     * @xmlonly
     *     <apigrouping group="User interface/Core"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT UIObject : public BaseObject {
        Q_OBJECT

        /*!
         * @brief A hierarchical list of the UIObject's attached objects.
         *
         * This QDeclarativeListProperty can contain any QObject. When a QObject is added
         * to property, the UIObject takes ownership of the attached object. 
         *
         * This feature is typically used from QML to specify business logic
         * object or any other shared objects for the subnodes of this UIObject. 
         * In C++ the same functionality can be achived by setting a parent
         * of a QObject to be attached to the QObject which is going to own it. 
         *
         * QML usage example (MyObject is a custom class registered 
         * for QML using the @c qmlRegisterType() function):
         *
         * @code
         * Container {
         *     Label { text: "Title: " + myObject.title } 
         *     Label { text: "Subject: " + myObject.subject }
         *     attachedObjects: [
         *         MyObject { id: myObject
         *             title: "Hello World"
         *             subject: "Nice Day"
         *         }
         *     ]
         * }
         * @endcode
         * 
         * @xmlonly
         * <qml>
         * <property name="attachedObjects" listType="QObject" defaultProperty="no"/>
         * </qml>
         * @endxmlonly
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QDeclarativeListProperty<QObject> attachedObjects READ attachedObjects FINAL)

        /*!
         * @brief An object that gives access to unit conversion routines.
         *
         * QML use:
         * @snippet tad/examples/foundation/assets/main.qml uiconfig_qml
         *
         * C++ use:
         * @snippet tad/examples/foundation/src/UIConfigExamples.cpp uiconfig1
         *
         *
         * @since Blackberry 10.3.0
         */
        Q_PROPERTY(bb::cascades::UIConfig* ui READ ui CONSTANT REVISION 3)

    public:
        /*!
         * @brief Destructs a UIObject.
         *
         * @since BlackBerry 10.0.0
         */
        virtual ~UIObject();

        /*!
         * @brief Overloaded to implement the event mechanism in Cascades.
         *
         * \warning If this function is overridden, it \e must be called by the derived class for 
         * events to work properly in Cascades.
         *
         * \param event The received event.
         * \return \c True if the received \c event was recognized and processed, \c false otherwise.
         *
         * @since BlackBerry 10.0.0
         */
        virtual bool event(QEvent *event);

        /*!
         * @brief Returns the @c UIConfig for this ui object.
         *
         * The @c UIConfig can be used to perform unit conversions from
         * design units (du) and snapped design units (sdu) to pixels.
         *
         * Ownership remains with Cascades.
         *
         * C++ use:
         * @snippet tad/examples/foundation/src/UIConfigExamples.cpp uiconfig1
         *
         * @return The @c UIConfig for this ui object.
         *
         * @since BlackBerry 10.3.0
         */
        Q_REVISION(3)
        Q_INVOKABLE bb::cascades::UIConfig *ui() const;

    protected:
        /*!
         * @brief Overloaded to implement the event mechanism in Cascades.
         *
         * If this function is overridden, it \e must be called by the derived class for 
         * events to work properly in Cascades.
         *
         * \param signal The connected signal.
         *
         * @since BlackBerry 10.0.0
         */
        virtual void connectNotify ( const char * signal );

        /*!
         * @brief Overloaded to implement the event mechanism in Cascades.
         *
         * If this function is overridden, it \e must be called by the derived class for 
         * events to work properly in Cascades.
         *
         * \param signal The disconnected signal.
         *
         * @since BlackBerry 10.0.0
         */
        virtual void disconnectNotify ( const char * signal );
        
    protected:
        /*! @cond PRIVATE */
        /*!
         * Constructs a UI object with a parent.
         * If not 0, the ownership of the constructed object will be transfered to the parent.
         *
         * \param _d_ptr The private representation of the UIObject.
         * \param parent The parent container or 0. Optional and will default to 0 if not specified.
         */
        UIObject(UIObjectPrivate &_d_ptr, UIObject* parent = 0);

        /*! @endcond */

    private:

        /*! @cond PRIVATE */
        QDeclarativeListProperty<QObject> attachedObjects();
        
        Q_DECLARE_PRIVATE(UIObject)
        Q_DISABLE_COPY(UIObject)
        /*! @endcond */
    };

}
}

QML_DECLARE_TYPE(bb::cascades::UIObject)

#endif	/* cascades_uiobject_h */

