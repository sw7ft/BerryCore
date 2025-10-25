/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 * 
 */

#ifndef BB_CASCADES_BASEOBJECT_H
#define BB_CASCADES_BASEOBJECT_H

#include <bb/cascades/bbcascades_global.h>

#include <QtCore/QObject>
#include <QtDeclarative/QtDeclarative>
#include <QtDeclarative/QDeclarativeParserStatus>
#include <QString>
#include <QScopedPointer>
#include <QDebug>

namespace bb {
namespace cascades {

class BaseObjectPrivate;

/*! 
 * @brief The base object for the classes in the framework.
 *
 * @details This class can be used as a base for class exposed to QML or just any
 * user class to be used with the framework.
 *
 * The class exposes a @c parent property (which returns the current parent of the
 * object as returned by @c QObject::parent()) and it provides a @c creationCompleted()
 * signal that is emitted when the object's construction and configuration has been completed.
 *
 * The signal is emitted when a class deriving from this class has been instantiated
 * from QML or constructed using its @c builder class.
 *
 * @xmlonly
 *     <apigrouping group="User interface/Core"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */    
class BBCASCADES_EXPORT BaseObject : public QObject, public QDeclarativeParserStatus {
    Q_OBJECT
    Q_INTERFACES(QDeclarativeParserStatus)
    
    /*! 
     * @brief This property is overridden from QObject.
     *
     * @details As the @c objectName property is overridden from the @c QObject class,
     * this signal will not be emitted if @c setObjectName() function is called directly
     * on @c QObject.
     *
     * The default value of this property is @c QString::null.
     * 
     * @see QObject::objectName().
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString objectName READ objectName WRITE setObjectName NOTIFY objectNameChanged FINAL)

    /*!
     * @brief A read-only property that represents this object's parent 
     *
     * @details The parent of an object is specified using @c QObject::setParent(QObject*). 
     * The purpose of the property is to expose the object's parent to QML.
     *
     * This property is read-only to prevent modifications from QML, where typically the parent is declaratively set. 
     * In C++ code, the parent can be explicitly set using @c QObject::setParent(QObject*), or implicitly set by adding
     * it to a visual container.
     *
     * The default value of this property is @c 0.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QObject * parent READ parent FINAL)
    
public:
    
    virtual ~BaseObject();

    /*!
     * @brief Sets the @c %objectName property.
     *
     * @param name The new name for the object.
     *
     * @since BlackBerry 10.0.0
     */
    void setObjectName(const QString &name);

    /*!
     * @brief Returns a debug string representing this object.
     *
     * @return A debug string for the object.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE virtual QString toDebugString() const;

    /*! @cond PRIVATE */

    /*!
     * Implementation method, not to be invoked directly.
     *
     * Overriding classes are expected to call super implementation.
     *
     * @copydoc QDeclarativeParserStatus::classBegin()
     */
    virtual void classBegin();

    /*!
     * Implementation method, not to be invoked directly.
     *
     * Overriding classes are expected to call super implementation.
     *
     * @copydoc QDeclarativeParserStatus::componentComplete()
     */
    virtual void componentComplete();

    /*! @endcond */
    
Q_SIGNALS:
    
    /*! 
     * @brief Emitted when this object is instantiated as a result
     * of loading a QML document and creating the root node (only after the root
     * component that caused this instantiation has completed construction), or when the object
     * is being constructed from its @c builder class.
     *
     * This signal indicates that the construction and initialization of the
     * object has been completed, the properties are initialized, and any QML
     * binding values have been assigned to the object.
     *
     * This signal is not emitted when the object is constructed from C++ using the constructor. 
     * If the object is constructed using its @c builder class, the signal is emitted when the 
     * the @c builder class returns the fully constructed object.
     *
     * This signal can be used when there is an activity that needs to be
     * performed, such as a property state integrity verification after the object
     * is instantiated from a QML document or a builder, but before control
     * is returned to the application.
     *
     * @see QmlDocument
     *
     * @since BlackBerry 10.0.0
     */
    void creationCompleted();

    /*! 
     * @brief This signal is emitted when the @c objectName property is changed.
     *
     * @see QObject, BaseObject::objectName.
     *
     * @since BlackBerry 10.0.0
     */
    void objectNameChanged(const QString &objectName);

public:
    /*!
     * @brief The builder base class.
     * 
     * @tparam BuilderType The type of the concrete @c builder of the most derived type.
     * @tparam BuiltType   The type of object built by this @c builder.
     *
     * @since BlackBerry 10.0.0
     */
    template <typename BuilderType, typename BuiltType>
    class TBuilder {

        /*!
         * @brief The object built by this @c builder.
         *
         * @since BlackBerry 10.0.0
         */
        BuiltType& m_instance;
    public:

        /*!
         * @brief Typecasts from a pointer to a @c builder, to a pointer to the @c build object.
         *
         * @details Each of the chained setters in the derived @c builders will return the @c builder to allow 
         * further chaining of setters. At the end of the chain, the @c builder will be converted 
         * with an implicit call to this operator.
         * 
         * This operator also invokes a constructed instance's @c BaseObject::componentComplete() 
         * method to indicate that the object's construction has been completed.
         * The instance is considered to have been fully constructed after this method returns.
         *
         * @since BlackBerry 10.0.0
         */
        operator BuiltType*() {
            m_instance.componentComplete();
            return &m_instance;
        }

        /*!
         * @brief Sets the parent @c QObject for the created UI object for the purposes of ownership.         *
         * This is equivalent to calling QObject::setParent(QObject *).
         *
         * @details Setting a parent does not place the created object into the visual hierarchy 
         * of the parent object, it is only used to express ownership. In order for an object to
         * be added to the visual hierarchy, the object needs to be added to a visual container (such as 
         * @c Container).
         *
         * Ownership of the created UI object is transferred to the specified parent object 
         * if it is not @c 0, otherwise the created UI object will not have a parent.
         *
         * @param newParent The parent object for the constructed object.
         * 
         * @see QObject::setParent(QObject *);
         *
         * @since BlackBerry 10.0.0
         */
        BuilderType& parent(QObject *newParent) {
            this->instance().setParent(newParent);
            return this->builder();
        }

        /*!
         * @brief Sets the @c objectName property of this object (the property is inherited from QObject).
         *
         * This is equivalent to calling @c QObject::setObjectName(const QString&).
         *
         * The @c objectName property can be used to look up the object by its name in a hierarchy
         * using @c QObject::findChild().
         *
         * @param name The object name.
         * 
         * @see QObject::setObjectName(const QString&);
         *
         * @since BlackBerry 10.0.0
         */
        BuilderType& objectName(const QString &name) {
            this->instance().setObjectName(name);
            return this->builder();
        }

        /*!
         * A convenience method for connecting passed receiver object's slot to
         * the constructed object's signal with the default connection type
         * Qt::AutoConnection.
         *
         * It is equivalent to calling @c QObject::connect(instance, signal, receiver, method) where
         * @c instance is an instance of constructed object returned by this builder.
         *
         * Example: connecting listener's slot @c onClicked() to button's @c clicked() signal.
         * @code
         * Button *button = Button::create()
         *     .connect(SIGNAL(clicked()), listener, SLOT(onClicked()));
         * @endcode
         * 
         * @param signal a non-@c null string containing constructed object's signal name
         * @param receiver A receiver object. This object cannot be @c null.
         * @param method a non-@c null name of the receiver's slot to connect the signal to
         *
         * @see QObject::connect(const QObject * sender,
         *                       const char * signal,
         *                       const QObject * receiver,
         *                       const char * method,
         *                       Qt::ConnectionType type)
         *
         * @since BlackBerry 10.0.0
         */
        BuilderType& connect(const char *signal, const QObject* receiver, const char *method) {
            bool res = QObject::connect(&this->instance(), signal, receiver, method);
            Q_ASSERT(res);
            Q_UNUSED(res);
            return this->builder();
        }

    protected:
        /*!
         * @brief Typecasts from a pointer to the object to build, to the builder.
         *
         * @details This method invokes @c BaseObject::classBegin() method to
         * indicate that the object has been created and its configuration through
         * the builder methods has begun.
         *
         * @since BlackBerry 10.0.0
         */
        TBuilder(BuiltType* _instance) : m_instance(*_instance) {
            m_instance.setCreationEnvironmentFromCode();
            m_instance.classBegin();
        }

        /*!
         * @brief Returns a reference to the instance being built.
         *
         * @return a reference to the instance being built.
         *
         * @since BlackBerry 10.0.0
         */
        BuiltType& instance() {
            return m_instance;
        }

        /*!
         * @brief Returns a reference to the builder of the most derived type.
         *
         * @return A reference to the builder of the most derived type.
         *
         * @since BlackBerry 10.0.0
         */
        BuilderType& builder() {
            return  *static_cast<BuilderType*>(this);
        }
    };


protected:

    /*!
     * @brief Constructs an instance of @c %BaseObject's subclass.
     * 
     * @param parent An optional parent, defaults to @c 0.
     *
     * @since BlackBerry 10.0.0
     */
    BaseObject(QObject *parent = 0);

    /*! @cond PRIVATE */
    BaseObject(BaseObjectPrivate &_d_ptr, QObject *parent = 0);

    /*!
     * @brief The private representation of the @c UIObject.
     */
    QScopedPointer<BaseObjectPrivate> d_ptr;
    /*! @endcond */
    
private:
    /*! @cond PRIVATE */
    void setCreationEnvironmentFromCode();
    Q_DECLARE_PRIVATE(BaseObject)
    Q_DISABLE_COPY(BaseObject)
    
    /*! @endcond */
 
};

    BBCASCADES_EXPORT QDebug operator<<(QDebug dbg, const BaseObject &base);

}
}

QML_DECLARE_TYPE(bb::cascades::BaseObject)

#endif	/* BB_CASCADES_BASEOBJECT_H */
