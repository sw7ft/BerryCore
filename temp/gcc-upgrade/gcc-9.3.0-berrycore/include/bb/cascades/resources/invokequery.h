/* Copyright (C) 2012-2013 Research In Motion Limited.  */

#ifndef cascades_invokequery_h
#define cascades_invokequery_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/system/FileTransferMode>
#include <bb/system/SecurityPerimeter>
#include <QtCore/QByteArray>
#include <QtCore/QString>
#include <QtCore/QUrl>
#include <QtCore/QVariant>
#include <QtDeclarative/QtDeclarative>

#include <bb/cascades/BaseObject>

namespace bb {
    namespace cascades {

    class InvokeQueryPrivate;

    /*!
     * @brief Contains the query data to use in invoke items.
     *
     * An @c %InvokeQuery is used by other classes in %Cascades that need
     * to send a query to the MenuService to ask for handlers that are
     * registered for handling certain types of data.
     *
     * For more information about invocations and the %Invoke framework, @c
     * bb::system::InvokeManager, @c bb::system::InvokeAction and @c
     * bb::system::InvokeTarget, @c bb::system::MenuManager might be
     * good places to start.
     *
     * At least one of @c #mimeType and @c #uri must be set.
     * The @c #data, @c #invokeActionId, and @c #invokeTargetId properties are
     * optional (they don't need to be set). If left undefined, they will not be
     * used to filter what handlers the %Invoke framework will return.
     *
     * Here's how you create an @c %InvokeQuery using the builder pattern:
     *
     * @code
     * InvokeQuery* pInvokeQuery(InvokeQuery::create()
     *   .mimeType("text/txt")
     *   .uri("file:///path/to/my/textfile")
     *   .invokeActionId("bb.action.OPEN"));
     * @endcode
     *
     * And here's how you create an @c %InvokeQuery using QML:
     *
     * @code
     * InvokeQuery {
     *   mimeType: "text/txt"
     *   uri: "file:///path/to/my/textfile"
     *   invokeActionId: "bb.action.OPEN"
     * }
     * @endcode
     *
     * @xmlonly
     * <qml>
     * <class abstract="no"/>
     * </qml>
     * <apigrouping group="User interface/Application structure"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT InvokeQuery : public BaseObject
    {
        Q_OBJECT

        /*!
         * @brief Identifies the MIME type of the data to operate on.
         *
         * If this property is changed, a call to updateQuery() is needed to trigger
         * a re-query to MenuService with the changed parameter content.
         *
         * This property is @e mandatory if uri is not set. If uri is set this property is optional.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QString mimeType READ mimeType WRITE setMimeType NOTIFY mimeTypeChanged FINAL)

        /*!
         * @brief Identifies the data to operate on.
         *
         * If this property is changed, a call to updateQuery() is needed to trigger
         * a re-query to MenuService with the changed parameter content.
         *
         * This property is  @e mandatory if mimeType is not set. If mimeType is set this property is optional.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QUrl uri READ uri WRITE setUri NOTIFY uriChanged FINAL)

        /*!
         * @brief The mode to be used for transferring the file pointed to by the
         * @c #uri.
         *
         * If this property is changed, a call to updateQuery() is needed to trigger
         * a re-query to MenuService with the changed parameter content.
         *
         * The default value of this property is @c
         * bb::system::FileTransferMode::Unspecified.
         *
         * This property is optional.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::system::FileTransferMode::Type fileTransferMode READ fileTransferMode WRITE setFileTransferMode NOTIFY fileTransferModeChanged FINAL)

/*! @cond PRIVATE */
        /*!
         * @brief The security perimeter in which the selected action is to be invoked.
         *
         * If this property is changed, a call to updateQuery() is needed to trigger
         * a re-query to MenuService with the changed parameter content.
         *
         * The default value of this property is @c
         * bb::system::SecurityPerimeter::Default.
         *
         * This property is optional.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::system::SecurityPerimeter::Type perimeter READ perimeter WRITE setPerimeter NOTIFY perimeterChanged FINAL)
/*! @endcond */

        /*!
         * @brief Arbitrary data to be used by the query.
         *
         * This property holds a blob of data to send as part of the query.
         * For example, the blob could be a line of text or other data that
         * can be parsed and interpreted in the query.
         *
         * If this property is changed, a call to updateQuery() is needed to trigger
         * a re-query to MenuService with the changed parameter content.
         *
         * This property is optional.
         *
         * Its default value is an empty @c QVariant.
         *
         * @xmlonly
         * <qml>
         * <variant type="QByteArray"/>
         * </qml>
         * @endxmlonly
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QVariant data READ dataQml WRITE setDataQml NOTIFY dataChangedQml FINAL)

        /*!
         * @brief The metadata used when querying for an action/target.
         *
         * If this property is changed, a call to updateQuery() is needed to trigger
         * a re-query to MenuService with the changed parameter content.
         *
         * This property is optional.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QVariantMap metadata READ metadata WRITE setMetadata NOTIFY metadataChanged FINAL)

        /*!
         * @brief The ID of the invoke action to query for.
         *
         * If this property is changed, a call to updateQuery() is needed to trigger
         * a re-query to MenuService with the changed parameter content.
         *
         * This property is optional.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QString invokeActionId READ invokeActionId WRITE setInvokeActionId NOTIFY invokeActionIdChanged FINAL)

        /*!
         * @brief The ID of the invoke target to query for.
         *
         * If this property is changed, a call to updateQuery() is needed to trigger
         * a re-query to MenuService with the changed parameter content.
         *
         * This property is optional.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QString invokeTargetId READ invokeTargetId WRITE setInvokeTargetId NOTIFY invokeTargetIdChanged FINAL)

        /*!
         * @brief Indicates whether to include the invoking application itself as a potential target.
         *
         * The default value is @c false, meaning the invoking application itself will not be
         * considered as a potential target for this query.

         * If this property is changed, a call to updateQuery() is needed to trigger
         * a re-query to MenuService with the changed parameter content.
         *
         * This property is optional.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bool invokerIncluded READ invokerIncluded WRITE setInvokerIncluded NOTIFY invokerIncludedChanged FINAL)

    public:
        /*! @cond PRIVATE */
        /*!
         * @brief Creates a new @c %InvokeQuery.
         *
         * @param pParent The parent of this object.
         */
        InvokeQuery(QObject* pParent=0);
        /*! @endcond */
        ~InvokeQuery();

        /*!
         * @brief The data MIME type of this query.
         *
         * @return The data MIME type of this query.
         *
         * @since BlackBerry 10.0.0
         */
        QString mimeType() const;

        /*!
         * @brief The data URI of this query.
         *
         * @return The data URI of this query.
         *
         * @since BlackBerry 10.0.0
         */
        QUrl uri() const;

        /*!
         * @brief The file transfer mode used during invocation.
         *
         * @return The file transfer mode of this query.
         *
         * @since BlackBerry 10.0.0
         */
        bb::system::FileTransferMode::Type fileTransferMode() const;
/*! @cond PRIVATE */
        /*!
         * @brief The security perimeter in which the selected action is to be invoked.
         *
         * @return The security perimeter of this query.
         *
         * @since BlackBerry 10.0.0
         */
        bb::system::SecurityPerimeter::Type perimeter() const;
/*! @endcond */

        /*!
         * @brief Gets the data to be used in a query by this @c %InvokeQuery.
         *
         * @return The data to be used in a query by this @c %InvokeQuery.
         *
         * @since BlackBerry 10.0.0
         */
        QByteArray data() const;

        /*!
         * @brief Gets the metadata to be used in a query by this @c %InvokeQuery.
         *
         * @return The metadata used in a query by this @c %InvokeQuery.
         *
         * @since BlackBerry 10.0.0
         */
        QVariantMap metadata() const;

        /*!
         * @brief The action ID of this query.
         *
         * @return The action ID of this query.
         *
         * @since BlackBerry 10.0.0
         */
        QString invokeActionId() const;

        /*!
         * @brief The target ID of this query.
         *
         * @return The target ID of this query.
         *
         * @since BlackBerry 10.0.0
         */
        QString invokeTargetId() const;


        /*!
         * @brief Flag indicating if invoking application shall be included in query result or not.
         *
         * @return True if invoking application is to be included in query result, false otherwise.
         *
         * @since BlackBerry 10.0.0
         */
        bool invokerIncluded() const;

        /*!
         * @brief Sets the data MIME type of this query.
         *
         * @param mimeType The new data MIME type of this query.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setMimeType(const QString& mimeType);

        /*!
         * @brief Sets the data URI of this query.
         *
         * @param uri The new data URI of this query.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setUri(const QUrl& uri);

        /*!
         * @brief Sets the file transfer mode to be used during invocation.
         *
         * @param mode The file transfer mode to be used during invocation.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setFileTransferMode(bb::system::FileTransferMode::Type mode);
/*! @cond PRIVATE */
        /*!
         * @brief Sets the security perimeter to be used during invocation.
         *
         * @param perimeter The security perimeter to be used during invocation.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setPerimeter(bb::system::SecurityPerimeter::Type perimeter);
/*! @endcond */
        /*!
         * @brief Sets the data to be used in a query by this @c %InvokeQuery.
         *
         * @param data The data to be used in a query by this @c %InvokeQuery.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setData(const QByteArray& data);

        /*!
         * @brief Sets the metadata to be used in a query by this @c %InvokeQuery.
         *
         * @param metadata The metadata to be used in a query by this @c %InvokeQuery.
         *
         * @since BlackBerry 10.0.0
         */
        void setMetadata(const QVariantMap& metadata);

        /*!
         * @brief Gets the data to be used in a query by this @c %InvokeQuery.
         *
         * @param invokeActionId The new action ID of this query.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setInvokeActionId(const QString& invokeActionId);

        /*!
         * @brief Sets the target ID of this query.
         *
         * @param invokeTargetId The new target ID of this query.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setInvokeTargetId(const QString& invokeTargetId);

        /*!
         * @brief Sets flag indicating if invoking application shall be included in query result or not.
         *
         * @param invokerIncluded Set to true for invoking application to be included in query result.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setInvokerIncluded(bool invokerIncluded);

        /*!
         * @brief Tell holding class InvokeQuery is updated.
         *
         * Use @c %updateQuery to tell the holding class that the %InvokeQuery has been
         * updated. The holding class will use the new properties in a re-query to
         * MenuService and replace the previous result with the new result.
         *
         * The preferred way of usage is to make all the needed property changes before
         * calling @c %updateQuery.
         *
         * Below is a small example on how to trigger a new query on changed properties.
         *
         * @code
         * InvokeActionItem {
         *   id: iai
         *   query {
         *     mimeType: "image/png"
         *     onQueryChanged: iai.query.updateQuery()
         *   }
         * }
         * @endcode
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void updateQuery();

    Q_SIGNALS:
        /*!
         * @brief Emitted when MIME type has been changed.
         *
         * @param mimeType The new mimeType set to be used by @c updateQuery.
         *
         * @since BlackBerry 10.0.0
         */
        void mimeTypeChanged(const QString& mimeType);

        /*!
         * @brief Emitted when uri has been changed.
         *
         * @param uri The new uri set to be used by @c updateQuery.
         *
         * @since BlackBerry 10.0.0
         */
        void uriChanged(const QUrl& uri);

        /*!
         * @brief Emitted when file transfer mode has been changed.
         *
         * @note Due to a work around for a Qt Core issue with accessing enums from QML
         * the argument of this signal doesn't follow naming convention for signals in
         * which the signal arguments are typically named to match the associated property's name.
         * Use the object's property to access current property value instead of the signal argument
         * to avoid runtime errors (i.e. use @c fileTransferMode instead of @c newFileTransferMode).
         *
         * @param newFileTransferMode The new file transfer mode set to be used by @c updateQuery.
         *
         * @since BlackBerry 10.0.0
         */
        void fileTransferModeChanged(bb::system::FileTransferMode::Type newFileTransferMode);
/*! @cond PRIVATE */
        /*!
         * @brief Emitted when perimeter has been changed.
         *
         * @note Due to a work around for a Qt Core issue with accessing enums from QML
         * the argument of this signal doesn't follow naming convention for signals in
         * which the signal arguments are typically named to match the associated property's name.
         * Use the object's property to access current property value instead of the signal argument
         * to avoid runtime errors (i.e. use @c perimeter instead of @c newPerimeter).
         *
         * @param newPerimeter The new perimeter set to be used by @c updateQuery.
         *
         * @since BlackBerry 10.0.0
         */
        void perimeterChanged(bb::system::SecurityPerimeter::Type newPerimeter);
/*! @endcond */
        /*!
         * @brief Emitted when data property has been changed.
         *
         * @param data The new data property set to be used by @c updateQuery.
         *
         * @since BlackBerry 10.0.0
         */
        void dataChanged(const QByteArray& data);

        /*!
         * @brief Emitted when metadata has been changed.
         *
         * @param metadata The new metadata set to be used by @c updateQuery.
         *
         * @since BlackBerry 10.0.0
         */
        void metadataChanged(const QVariantMap& metadata);

        /*! @cond PRIVATE */
        void dataChangedQml(const QVariant& data);
        /*! @endcond */

        /*!
         * @brief Emitted when invoke action id has been changed.
         *
         * @param invokeActionId The new invoke action id set to be used by @c updateQuery.
         *
         * @since BlackBerry 10.0.0
         */
        void invokeActionIdChanged(const QString& invokeActionId);

        /*!
         * @brief Emitted when invoke target id has been changed.
         *
         * @param invokeTargetId The new invoke target id set to be used by @c updateQuery.
         *
         * @since BlackBerry 10.0.0
         */
        void invokeTargetIdChanged(const QString& invokeTargetId);

        /*!
         * @brief Emitted when invokerIncluded has been changed.
         *
         * @param invokerIncluded The new value of invokerIncluded property.
         *
         * @since BlackBerry 10.0.0
         */
        void invokerIncludedChanged(bool invokerIncluded);

        /*!
         * @brief Convenience signal emitted when any one of the properties has been changed.
         *
         * @since BlackBerry 10.0.0
         */
        void queryChanged();

    private:
        /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(InvokeQuery)
        Q_DISABLE_COPY(InvokeQuery)

        /*!
         * @brief Gets the data to be used in a query by this @c %InvokeQuery.
         *
         * @return The data to be used in a query by this @c %InvokeQuery.
         */
        QVariant dataQml() const;

        /*!
         * @brief Sets the data to be used in a query by this @c %InvokeQuery.
         *
         * @param data The data to be used in a query by this @c %InvokeQuery.
         */
        void setDataQml(const QVariant& data);

        typedef InvokeQuery ThisClass;
        typedef BaseObject BaseClass;
        /*! @endcond */

    protected:
        /*!
         * @brief A builder template for constructing an @c InvokeQuery.
         *
         * To retrieve the builder, call @c InvokeQuery::create().
         *
         * @tparam BuilderType The type of the concrete builder of the most derived type.
         * @tparam BuiltType The type of object built by this builder.
         *
         * @since BlackBerry 10.0.0
         */
        template <typename BuilderType, typename BuiltType>
            class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType>
        {
        protected:
            /*!
             * @brief Creates a new builder constructing an @c InvokeQuery.
             *
             * @param node The instance of @c %InvokeQuery to build.
             *
             * @since BlackBerry 10.0.0
             */
            TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node)
            {
            }

        public:

            /*!
             * @brief Sets the data MIME type to use in this query.
             *
             * @param mimeType The data MIME type to use in this query.
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& mimeType(const QString& mimeType) {
                this->instance().setMimeType(mimeType);
                return this->builder();
            }

            /*!
             * @brief Sets the data URI to use in this query.
             *
             * @param uri The data URI to use in this query.
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& uri(const QUrl& uri) {
                this->instance().setUri(uri);
                return this->builder();
            }

            /*!
             * @brief Sets the data URI to use in this query.
             *
             * @param uri The data URI to use in this query.
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& uri(const QString& uri) {
                this->instance().setUri(uri);
                return this->builder();
            }

            /*!
             * @brief Sets the file transfer mode to be used during invocation.
             *
             * @param mode The file transfer mode to be used during invocation.
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& fileTransferMode(bb::system::FileTransferMode::Type mode) {
                this->instance().setFileTransferMode(mode);
                return this->builder();
            }
/*! @cond PRIVATE */
            /*!
             * @brief Sets the security perimeter to be used during invocation.
             *
             * @param perimeter The security perimeter to be used during invocation.
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& perimeter(bb::system::SecurityPerimeter::Type perimeter) {
                this->instance().setPerimeter(perimeter);
                return this->builder();
            }
/*! @endcond */

            /*!
             * @brief Sets the data to use in this query.
             *
             * @param data The data to use in this query.
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& data(const QByteArray& data) {
                this->instance().setData(data);
                return this->builder();
            }

            /*!
             * @brief Sets the metadata to use in this query.
             *
             * @param metadata The metadata to use in this query.
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& metadata(const QVariantMap& metadata) {
                this->instance().setMetadata(metadata);
                return this->builder();
            }

            /*!
             * @brief Sets the action ID to use in this query.
             *
             * @param invokeActionId The action ID to use in this query.
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& invokeActionId(const QString& invokeActionId) {
                this->instance().setInvokeActionId(invokeActionId);
                return this->builder();
            }

            /*!
             * @brief Sets the target ID to use in this query.
             *
             * @param invokeTargetId The target ID to use in this query.
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& invokeTargetId(const QString& invokeTargetId) {
                this->instance().setInvokeTargetId(invokeTargetId);
                return this->builder();
            }

            /*!
             * @brief Sets flag indicating if invoking application shall be included in query result or not.
             *
             * @param invokerIncluded Set to true for invoking application to be included in query result.
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& invokerIncluded(bool invokerIncluded) {
                this->instance().setInvokerIncluded(invokerIncluded);
                return this->builder();
            }

            /*!
             * A convenience method for connecting the passed receiver's slot to
             * the mimeTypeChanged(const QString&) signal with the default connection type set to
             * Qt::AutoConnection. Here's some related sample code:
             *
             * @code
             * InvokeQuery *pInvokeQuery(InvokeQuery::create()
             *     .onMimeTypeChanged(this, SLOT(myOnMimeTypeChanged(const QString&))));
             * @endcode
             *
             * @param receiver a non-@c null receiver object
             * @param method a non-@c null name of the slot in the receiver object to connect to
             *
             * @see BaseObject::TBuilder::connect()
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& onMimeTypeChanged(const QObject* receiver, const char *method) {
                this->connect(SIGNAL(mimeTypeChanged(const QString&)), receiver, method);
                return this->builder();
            }

            /*!
             * A convenience method for connecting the passed receiver's slot to
             * the uriChanged(const QUrl&) signal with the default connection type set to
             * Qt::AutoConnection. Here's some related sample code:
             *
             * @code
             * InvokeQuery *pInvokeQuery(InvokeQuery::create()
             *     .onUriChanged(this, SLOT(myOnUriChanged(const QUrl&))));
             * @endcode
             *
             * @param receiver a non-@c null receiver object
             * @param method a non-@c null name of the slot in the receiver object to connect to
             *
             * @see BaseObject::TBuilder::connect()
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& onUriChanged(const QObject* receiver, const char *method) {
                this->connect(SIGNAL(uriChanged(const QUrl&)), receiver, method);
                return this->builder();
            }

            /*!
             * A convenience method for connecting the passed receiver's slot to
             * the fileTransferModeChanged(bb::system::FileTransferMode::Type) signal
             * with the default connection type set to
             * Qt::AutoConnection. Here's some related sample code:
             *
             * @code
             * InvokeQuery *pInvokeQuery(InvokeQuery::create()
             *     .onFileTransferModeChanged(this, SLOT(myOnFileTransferModeChanged(bb::system::FileTransferMode::Type))));
             * @endcode
             *
             * @param receiver a non-@c null receiver object
             * @param method a non-@c null name of the slot in the receiver object to connect to
             *
             * @see BaseObject::TBuilder::connect()
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& onFileTransferModeChanged(const QObject* receiver, const char *method) {
                this->connect(SIGNAL(fileTransferModeChanged(bb::system::FileTransferMode::Type)), receiver, method);
                return this->builder();
            }
/*! @cond PRIVATE */
            /*!
             * A convenience method for connecting the passed receiver's slot to
             * the perimeterChanged(bb::system::SecurityPerimeter::Type) signal
             * with the default connection type set to
             * Qt::AutoConnection. Here's some related sample code:
             *
             * @code
             * InvokeQuery *pInvokeQuery(InvokeQuery::create()
             *     .onPerimeterChanged(this, SLOT(myOnPerimeterChanged(bb::system::SecurityPerimeter::Type))));
             * @endcode
             *
             * @param receiver a non-@c null receiver object
             * @param method a non-@c null name of the slot in the receiver object to connect to
             *
             * @see BaseObject::TBuilder::connect()
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& onPerimeterChanged(const QObject* receiver, const char *method) {
                this->connect(SIGNAL(perimeterChanged(bb::system::SecurityPerimeter::Type)), receiver, method);
                return this->builder();
            }
/*! @endcond */
            /*!
             * A convenience method for connecting the passed receiver's slot to
             * the dataChanged(const QByteArray&) signal with the default connection type set to
             * Qt::AutoConnection. Here's some related sample code:
             *
             * @code
             * InvokeQuery *pInvokeQuery(InvokeQuery::create()
             *     .onDataChanged(this, SLOT(myOnDataChanged(const QByteArray&))));
             * @endcode
             *
             * @param receiver a non-@c null receiver object
             * @param method a non-@c null name of the slot in the receiver object to connect to
             *
             * @see BaseObject::TBuilder::connect()
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& onDataChanged(const QObject* receiver, const char *method) {
                this->connect(SIGNAL(dataChanged(const QByteArray&)), receiver, method);
                return this->builder();
            }

            /*!
             * A convenience method for connecting the passed receiver's slot to
             * the metadataChanged(const QVariantMap&) signal with the default connection type set to
             * Qt::AutoConnection. Here's some related sample code:
             *
             * @code
             * InvokeQuery *pInvokeQuery(InvokeQuery::create()
             *     .onMetadataChanged(this, SLOT(myOnMetadataChanged(const QVariantMap&))));
             * @endcode
             *
             * @param receiver a non-@c null receiver object
             * @param method a non-@c null name of the slot in the receiver object to connect to
             *
             * @see BaseObject::TBuilder::connect()
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& onMetadataChanged(const QObject* receiver, const char *method) {
                this->connect(SIGNAL(metadataChanged(const QVariantMap&)), receiver, method);
                return this->builder();
            }

            /*!
             * A convenience method for connecting the passed receiver's slot to
             * the invokeActionChanged(const QString&) signal with the default connection type set to
             * Qt::AutoConnection. Here's some related sample code:
             *
             * @code
             * InvokeQuery *pInvokeQuery(InvokeQuery::create()
             *     .onInvokeActionChanged(this, SLOT(myOnInvokeActionChanged(const QString&))));
             * @endcode
             *
             * @param receiver a non-@c null receiver object
             * @param method a non-@c null name of the slot in the receiver object to connect to
             *
             * @see BaseObject::TBuilder::connect()
             *
             * @deprecated Use @c onInvokeActionIdChanged(const QObject* receiver, const char *method) instead
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& onInvokeActionChanged(const QObject* receiver, const char *method) {
                this->connect(SIGNAL(invokeActionChanged(const QString&)), receiver, method);
                return this->builder();
            }

            /*!
             * A convenience method for connecting the passed receiver's slot to
             * the invokeActionIdChanged(const QString&) signal with the default connection type set to
             * Qt::AutoConnection. Here's some related sample code:
             *
             * @code
             * InvokeQuery *pInvokeQuery(InvokeQuery::create()
             *     .onInvokeActionIdChanged(this, SLOT(myOnInvokeActionIdChanged(const QString&))));
             * @endcode
             *
             * @param receiver a non-@c null receiver object
             * @param method a non-@c null name of the slot in the receiver object to connect to
             *
             * @see BaseObject::TBuilder::connect()
             *
             * @since BlackBerry 10.2.0
             */
            BuilderType& onInvokeActionIdChanged(const QObject* receiver, const char *method) {
                this->connect(SIGNAL(invokeActionIdChanged(const QString&)), receiver, method);
                return this->builder();
            }

            /*!
             * A convenience method for connecting the passed receiver's slot to
             * the invokeTargetChanged(const QString&) signal with the default connection type set to
             * Qt::AutoConnection. Here's some related sample code:
             *
             * @code
             * InvokeQuery *pInvokeQuery(InvokeQuery::create()
             *     .onInvokeTargetChanged(this, SLOT(myOnInvokeTargetChanged(const QString&))));
             * @endcode
             *
             * @param receiver a non-@c null receiver object
             * @param method a non-@c null name of the slot in the receiver object to connect to
             *
             * @see BaseObject::TBuilder::connect()
             *
             * @deprecated Use @c onInvokeTargetIdChanged(const QObject* receiver, const char *method) instead
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& onInvokeTargetChanged(const QObject* receiver, const char *method) {
                this->connect(SIGNAL(invokeTargetChanged(const QString&)), receiver, method);
                return this->builder();
            }

            /*!
             * A convenience method for connecting the passed receiver's slot to
             * the invokeTargetIdChanged(const QString&) signal with the default connection type set to
             * Qt::AutoConnection. Here's some related sample code:
             *
             * @code
             * InvokeQuery *pInvokeQuery(InvokeQuery::create()
             *     .onInvokeTargetIdChanged(this, SLOT(myOnInvokeTargetIdChanged(const QString&))));
             * @endcode
             *
             * @param receiver a non-@c null receiver object
             * @param method a non-@c null name of the slot in the receiver object to connect to
             *
             * @see BaseObject::TBuilder::connect()
             *
             * @since BlackBerry 10.2.0
             */
            BuilderType& onInvokeTargetIdChanged(const QObject* receiver, const char *method) {
                this->connect(SIGNAL(invokeTargetIdChanged(const QString&)), receiver, method);
                return this->builder();
            }

            /*!
             * A convenience method for connecting the passed receiver's slot to
             * the queryChanged() signal with the default connection type set to
             * Qt::AutoConnection. Here's some related sample code:
             *
             * @code
             * InvokeQuery *pInvokeQuery(InvokeQuery::create()
             *     .onQueryChanged(this, SLOT(myOnQueryChanged())));
             * @endcode
             *
             * @param receiver a non-@c null receiver object
             * @param method a non-@c null name of the slot in the receiver object to connect to
             *
             * @see BaseObject::TBuilder::connect()
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& onQueryChanged(const QObject* receiver, const char *method) {
                this->connect(SIGNAL(queryChanged()), receiver, method);
                return this->builder();
            }

            /*!
             * A convenience method for connecting the passed receiver's slot to
             * the invokerIncludedChanged() signal with the default connection type set to
             * Qt::AutoConnection. Here's some related sample code:
             *
             * @code
             * InvokeQuery *pInvokeQuery(InvokeQuery::create()
             *     .onInvokerIncludedChanged(this, SLOT(myOnInvokerIncludedChanged(bool))));
             * @endcode
             *
             * @param receiver a non-@c null receiver object
             * @param method a non-@c null name of the slot in the receiver object to connect to
             *
             * @see BaseObject::TBuilder::connect()
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& onInvokerIncludedChanged(const QObject* receiver, const char *method) {
                this->connect(SIGNAL(invokerIncludedChanged(bool)), receiver, method);
                return this->builder();
            }

            /*!
             * A convenience method to internally connect the slot updateQuery()
             * to the queryChanged() signal to have automatic update of the query
             * result on any changed property.
             * The default connection type is used which is set to
             * Qt::AutoConnection. Here's some related sample code:
             *
             * @code
             * InvokeQuery *pInvokeQuery(InvokeQuery::create()
             *     .updateOnQueryChanged());
             * @endcode
             *
             * @see BaseObject::TBuilder::connect()
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& updateOnQueryChanged() {
                this->connect(SIGNAL(queryChanged()), &this->instance(), SLOT(updateQuery()));
                return this->builder();
            }
        };

    private:
        /*!
         * @brief A builder for constructing an @c InvokeQuery.
         *
         * To retrieve the builder, call @c InvokeQuery::create().
         */
        class Builder : public TBuilder<Builder, ThisClass>
        {
        public:
            /*!
             * @brief Creates a new builder constructing an @c InvokeQuery.
             */
            explicit Builder()
                : TBuilder<Builder, ThisClass>(new ThisClass()) {
            }
        };

    public:
        /*!
         * @brief Creates and returns a builder for constructing an @c %InvokeQuery.
         *
         * Usage:
         * @code
         * InvokeQuery* pInvokeQuery(InvokeQuery::create()
         *   .uri("file:///mytextfile")
         *   .invokeActionId("bb.action.OPEN"));
         * @endcode
         *
         * @return A builder used for constructing an @c %InvokeQuery.
         *
         * @since BlackBerry 10.0.0
         */
        static Builder create() {
            return Builder();
        }
    };
}
}

QML_DECLARE_TYPE(bb::cascades::InvokeQuery)

#endif  // cascades_invokequery_h
