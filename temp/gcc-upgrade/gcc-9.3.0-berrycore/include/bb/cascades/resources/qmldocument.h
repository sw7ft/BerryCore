/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_qmldocument_h
#define cascades_qmldocument_h

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtDeclarative/QDeclarativeError>
#include <QtDeclarative/QDeclarativeContext>

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/BaseObject>

class QDeclarativeContext;
class QUrl;
class QDeclarativeEngine;
class QDeclarativeComponent;

namespace bb {
    namespace cascades {

        class QmlDocumentPrivate;
        class Control;
        class QmlDocument;

    /*!
     * 
     * @brief Represents a QML document that can be loaded into a C++ application.
     *
     * QML documents are loaded using a specified asset name. QML documents are considered
     * to be assets, meaning that they should be packaged with the application.
     *
     * All documents loaded with this class will share the same QDeclarativeEngine
     * which is associated with the application. However, each document will have
     * its own QDeclarativeContext derived from the root context of the shared application
     * engine. Properties of this context can be set using QmlDocument::setContextProperty() method.
     * The shared context is accessible via the QmlDocument::documentContext() method. New
     * contexts can be derived from this context and used for creating root nodes.
     *
     * Once the document is successuflly loaded using the builder's QmlDocument::Builder::load(const QString&) method
     * (one should use QmlDocument::hasErrors() method to check whether the document was loaded
     * successfully) a root node can be instantiated for the tree represented by
     * this document using the QmlDocument::createRootObject() template method. The root node must
     * be a derivative of the UIObject class. Multiple root nodes can be instantiated from
     * the same QmlDocument instance. It is possible to specify a context to create a root
     * node with, in case a derived context needs to be created.
     *
     * During the instantiation of the root node, the UIObject::creationCompleted() signal
     * will be emitted for all UIObjects in the tree.
     *
     * Note that the context properties should be set prior to instantiating the
     * root node of the document.
     *
     * <h2>Object ownership</h2>
     *
     * When you create a @c QmlDocument object, no parent object is set by default. To ensure that the object
     * gets cleaned up when the app exits, you must manually set the parent to an object that has a lifespan
     * sufficient enough to outlast all the components within the document, such as the scene or the @c Application instance.
     * The easiest way of setting ownership is by using the @c parent() builder function when you instantiate
     * the @c %QmlDocument:
     *
     * @code
     * QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);
     * @endcode
     *
     * If the QmlDocument instance is only used for creating a single instance of the root object
     * this root object can be set as a parent of the QmlDocument instance so the latter will
     * be deleted when the node instance is deleted.
     *
     * The QmlDocument object owns its encapsulated context and declarative component. The
     * user is responsible for all contexts derived from the shared document's context.
     * The declarative engine is owned by the application instance and must not
     * be deleted.
     *
     * The root nodes created using QmlDocument::createRootObject() are owned by
     * the user. The QmlDocument object which was used to create the root node
     * must have longer lifespan than the root nodes themselves.
     *
     * This example shows how to load and instantiate a QmlDocument document:
     * @code
     * QmlDocument *qml = QmlDocument::create("asset:///ApplicationScreen.qml").parent(this);
     * if (!qml->hasErrors()) {
     *     Page *page = qml->createRootObject<Page>();
     *     if (page) {
     *         setScene(page);
     *     }
     * }
     * @endcode
     *
     * Here's an example of loading and instantiating a @c %QmlDocument document and setting
     * shared context properties:
     *
     * @code
     * QmlDocument *qml = QmlDocument::create("asset:///ApplicationScreen.qml")
     *    // Sets shared context property myObject to 'this'
     *    .property("myObject", this)
     *    // Sets shared context property myData to 'dataObject'     
     *    .property("myData", dataObject);
     *
     * if (!qml->hasErrors()) {
     *     Page *page= qml->createRootObject<Page>();
     *     if (page) {
     *         setScene(page);
     *     }
     * }
     * @endcode
     *
     * Here's an example of creating a root node with a derived context:
     *
     * @code
     * QmlDocument *qml = QmlDocument::create("asset:///ApplicationScreen.qml").parent(this);
     * if (!qml->hasErrors()) {
     *     QDeclarativeContext *derivedContext1 = 
     *             new QDeclarativeContext(qml->documentContext());
     *     derivedContext1->setContextProperty("myObject", this);
     *     derivedContext1->setContextProperty("myData", dataObject1);
     *
     *     // Create a control with derived declarative context
     *     Control *control1 =
     *             qml->createRootObject<Control>(derivedContext1);
     *
     *     // Now create another root node with a different context
     *     QDeclarativeContext *derivedContext2 =
     *             new QDeclarativeContext(qml->documentContext());
     *     derivedContext2->setContextProperty("myObject", that);
     *     derivedContext2->setContextProperty("myData", dataObject2);
     *     Control *control2 =
     *             qml->createRootObject<Control>(derivedContext2);
     *
     *     // A way to ensure the context doesn't get leaked
     *     derivedContext->setParent(control2);
     *
     *     // ... use the created controls
     * }
     * @endcode
     *
     *
     * @see QDeclarativeEngine, QDeclarativeContext, QDeclarativeComponent, UIObject
     *
     * @xmlonly
     * <apigrouping group="User interface/Resources"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT QmlDocument : public QObject
    {
        Q_OBJECT
        
        /*!
         * @brief A @c QUrl from which this document has been loaded
         *
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QUrl source READ source FINAL CONSTANT)

    public:
        /*!
         * @brief A destructor for this object.
         *
         * @since BlackBerry 10.0.0
         */
        virtual ~QmlDocument();

        /*!
         * @brief A template method for instantiating a root node from the QML
         * document associated with this class.
         *
         * The node will be created using the context associated with this document
         * unless a specific context is specified with the optional @c context
         * parameter, in which case the component will be created using that passed
         * context.
         *
         * This method can be called multiple times to create multiple instances
         * of the root node.
         *
         * During the instantiation of the root node the UIObject::creationCompleted() signal
         * will be emitted for all UIObjects in the tree.
         *
         * The ownership of the returned node is transferred to the user.
         * The document must be successfully loaded prior to this call and the type
         * specified for the template must be a UIObject subclass, otherwise this
         * method will return @c 0.
         *
         * Example of creating a root node:
         *
         * @code
         * QmlDocument *qml = QmlDocument::create("asset:///ApplicationScreen.qml").parent(this);
         * if (!qml->hasErrors()) {
         *     // Creates a control which inherits context properties from
         *     // the shared context
         *     Control *control = qml->createRootObject<Control>();
         *     // ...
         * }
         * @endcode
         *
         * Example of creating a root node with a derived context:
         *
         *
         * @code
         * QmlDocument *qml = QmlDocument::create("asset:///ApplicationScreen.qml").parent(this);
         * if (!qml->hasErrors()) {
         *     QDeclarativeContext *derivedContext = 
         *             new QDeclarativeContext(qml->documentContext());
         *     derivedContext->setContextProperty("myObject", dataObject);
         *     // Creates a control with derived declarative context
         *     Control *control =
         *             qml->createRootObject<Control>(derivedContext);
         *     // ...
         * }
         * @endcode
         *
         * @return A newly created root object of the tree represented by the document, or @c 0
         * if the root node cannot be created.
         * @param context An optional context for creating the root node. If not set the shared
         * document's context will be used for creating the root node.
         *
         * @sa documentContext(), QDeclarativeComponent::create()
         *
         * @since BlackBerry 10.0.0
         */
        template <class T>
        T* createRootObject(QDeclarativeContext *context = 0) {
            BaseObject * rootUINode = createRootObject(context);
            T* rootNode = qobject_cast<T*>(rootUINode);
            if (rootUINode && !rootNode) {
                // object cannot be cast to *T, prevent a leak by destroying created root
                delete rootUINode;
                rootUINode = 0;
            }
            return rootNode;
        }
        
        
        /*!
         * @brief Explictly loads this document
         *
         * If the document is already loaded, this function has no effect
         *
         * @return returns @c true if loadded successfully, @c false otherwise. 
         *
         * @since BlackBerry 10.0.0
         */
        bool load();
        
        /*!
         * @brief Sets the context property for the shared context associated with this document.
         * 
         * Each document has its own context derived from the root context of the
         * shared declarative engine.
         *
         * For your own contexts derived from the shared context associated with
         * the documents you will need
         * to use QDeclarativeContext::setContextProperty directly.
         *
         * @param propertyName The name of the context property to set.
         * @param object The value of the property to set.
         *
         * @see documentContext()
         *
         * @since BlackBerry 10.0.0
         */
        void setContextProperty(const QString &propertyName, QObject *object);

        /*!
         * @brief Returns the shared context associated with this document.
         *
         * This context is derived from the root context of the shared QDeclarativeEngine.
         *
         * One would typically use this method in case there's a need to override
         * context properties for a new instance of the root node. In this case
         * one can create a child context, override context properties on this
         * new context and use it to create the root node.
         *
         * The QmlDocument owns the returned context. However, the user will
         * be responsible for derived contexts created from this context.
         *
         * @see createRootObject()
         *
         * @return A shared context associated with this document.
         *
         * @since BlackBerry 10.0.0
         */
        QDeclarativeContext * documentContext();
        
        /*!
         * @brief Returns false when this document was successfully loaded.
         *
         * This method returns @c false if the document associated with this object was loaded
         * successfully. It returns @c true if the document hasn't yet been loaded or it
         * failed to load. If it failed to load the QmlDocument::errors() method can used to
         * get the list of errors.
         *
         * @see errors(), Builder::load()
         *         
         * @return @c true if this document has errors, @c false otherwise.
         *
         * @since BlackBerry 10.0.0
         */
        bool hasErrors();

        /*!
         * @brief Returns the list of the errors produced when loading the document.
         *
         * The list will be empty if there were no errors or the document hasn't
         * yet been loaded.
         * 
         * @return A list of errors.
         *
         *
         * @since BlackBerry 10.0.0
         */
        QList<QDeclarativeError> errors();
        
        /*!
         * @brief Returns the source @c QUrl from which this document has been loaded
         * 
         * @return the source @c QUrl
         *
         * @since BlackBerry 10.0.0
         */
        QUrl source() const;
        
        
        /*!
         * @brief Returns the default declarative engine used to load and create this document
         *
         * The declarative engine is owned by the bb::cascades::Application instance and is not 
         * supposed to change ownership. 
         *
         * @see QDeclarativeEngine
         * 
         * @return the default declarative engine
         *
         * @since BlackBerry 10.0.0
         */
        static QDeclarativeEngine * defaultDeclarativeEngine();        
        
        /*!
         * @brief A builder used to construct the QmlDocument object instance,
         * set properties and load the document.
         *
         * See QmlDocument::create() methods for getting a concrete Builder for
         * constructing a QmlDocument.
         *
         * @since BlackBerry 10.0.0
         */
                
    public:
        class Builder {
        private:
            /*! \cond PRIVATE */
            QmlDocument& m_instance;
            const bool m_autoLoad;
            /*! \endcond */
        protected:
            /*! \cond PRIVATE */
            QmlDocument& instance() {
                return m_instance;
            }
             /*! \endcond */
        public:
            /*! \cond PRIVATE */
            Builder(const QUrl &source, bool autoLoad = true)
                    : m_instance(*new QmlDocument(source)), m_autoLoad(autoLoad) {}
            
            operator QmlDocument*() {
                if (m_autoLoad) {
                    m_instance.load();
                }
                return &m_instance;
            }
            /*! \endcond */

            /*!
             * @brief Sets the property for the shared context associated with document.
             *
             * @copydetails QmlDocument::setContextProperty()
             *
             * @since BlackBerry 10.0.0
             */
            Builder& property(const QString &propertyName, QObject *object) {
                m_instance.setContextProperty(propertyName, object);
                return *this;
            }
            

            /*!
             * @brief Sets the parent @c QObject for the created ui object for the purpose of ownership.
             *
             * This is equivalent to calling QObject::setParent(QObject *).
             *
             * Setting a parent does not place the created object into the visual hierarchy 
             * of the parent object, it is only used to express ownership. In order for object to
             * be added to visual hierarchy the object needs to be added to a visual container (such as 
             * Container).
             *
             * The ownership of the created ui object is transferred to the specified parent object 
             * if it is not @c 0, otherwise the created ui object will not have a parent.
             *
             * @param newParent the parent object for the constructed object
             * @sa QObject::setParent(QObject *);
             *
             * @since BlackBerry 10.0.0
             */
            Builder& parent(QObject *newParent) {
                m_instance.setParent(newParent);
                return *this;
            }
            
            /*!
             * @brief Sets the objectName property of this object (the property is inherited from QObject).
             *
             * This is equivalent to calling QObject::setObjectName(const QString&).
             *
             * Object name can be used to look up the object by its name in a hierarchy
             * using QObject::findChild().
             *
             * @param name the object name
             * @see QObject::setObjectName(const QString&);
             *
             * @since BlackBerry 10.0.0
             */
            Builder& objectName(const QString &name) {
                m_instance.setObjectName(name);
                return *this;
            }            
        };
        
        
        /*!
         * @brief Creates and returns a builder for constructing a QmlDocument instance with
         * a parent object and an asset name to load the document from.
         *
         * @param qmlAsset The QML asset name load the document from, specified relative to the assets root.
         * @param autoLoad if @c true the document is automatic loaded, otherwise it is required to call load fuction explicitly. The default is @c true .
         *
         * @since BlackBerry 10.0.0
         */
        static Builder create(const QString &qmlAsset, bool autoLoad = true) {
            return create(QUrl(qmlAsset),autoLoad);
        }
        
   
        
        /*!
         * @brief Creates and returns a builder for constructing a QmlDocument instance with
         * a parent object and a URL to load the document from.
         *
         * @param source The URL to load the document from. Currently only relative and "file://" URLs are supported
         * @param autoLoad if @c true the document is automatic loaded, otherwise it is required to call load fuction explicitly. The default is @c true .
         *
         * @since BlackBerry 10.0.0
         */
        static Builder create(const QUrl &source, bool autoLoad = true) {
            return Builder(source,autoLoad);
        }


    private:
        /*! \cond PRIVATE */
        BaseObject * createRootObject(QDeclarativeContext *context);

        Q_DECLARE_PRIVATE(QmlDocument)
        Q_DISABLE_COPY(QmlDocument)
        QmlDocument(const QUrl &source);
        QmlDocumentPrivate * const d_ptr;
        /*! \endcond */
    };
    

    }
}

#endif // cascades_qmldocument_h

