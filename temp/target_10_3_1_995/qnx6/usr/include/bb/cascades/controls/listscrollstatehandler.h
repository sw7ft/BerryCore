/* Copyright (C) 2012-2013 Research In Motion Limited.  */

#ifndef cascades_listscrollstatehandler_h
#define cascades_listscrollstatehandler_h

#include <bb/cascades/bbcascades_global.h>

#include <QtCore/QObject>
#include <QtDeclarative/QtDeclarative>
#include <QRectF>
#include <bb/cascades/ListView>
#include <bb/cascades/BaseObject>

  
namespace bb {
namespace cascades {

    class Control;
    class ListScrollStateHandlerPrivate;

    /*!
     * @brief Listens for scroll state changes on a @c ListView.
     *
     * The properties in this class provide read-only access to the scroll state of the
     * target @c %ListView.
     *
     * The properties are changed asynchronously when the scroll state of the target @c %ListView
     * changes. Because of this, the state reported by a @c ListScrollStateHandler may be out of sync
     * for a few frames after creation, or when the state changes.
     *
     * The target @c %ListView can only be specified during construction using the
     * constructor, builder, or as a parent component in QML. The state handler cannot
     * be changed at run time.
     *
     * Here's an example of how to track the @c %ListView scroll state in C++.
     * 
     * @code
     * ListView *pListView = ListView::create();
     *
     * ListScrollStateHandler::create(pListView)
     *     .onScrollingChanged(this, SLOT(handleScrollingChanged(bool)));
     *
     * // pListView owns the created handler so there is no need to keep a reference
     * // to it, and it will be deleted when the ListView is deleted.
     * @endcode
     *
     * In QML, the handler must be attached to a @c %ListView. 
     * The following sample demonstrates how to show a @c Label when a @c %ListView is scrolling.
     * @code
     * Container {
     *     Label {
     *         id: scrollLabel
     *         text: "Scrolling"
     *         opacity: 0
     *     }
     *
     *     // The ListView we want to track.
     *     // Note that this ListView lacks a DataModel. See the ListView
     *     // documentation for a complete ListView example.
     *     ListView {
     *         attachedObjects: [
     *             // This handler is tracking the scroll state of the ListView.
     *             ListScrollStateHandler {
     *             id: scrollStateHandler
     *
     *                 onScrollingChanged: {
     *                     if (scrolling) {
     *                         scrollLabel.setOpacity(1);
     *                     }
     *                     else {
     *                         scrollLabel.setOpacity(0);
     *                     }
     *                 }
     *             }
     *         ]
     *     }
     * }
     * @endcode
     *
     * @xmlonly
     * <apigrouping group="User interface/List"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT ListScrollStateHandler : public BaseObject {
        Q_OBJECT

        /*!
         * @brief A read-only property representing the scroll state of the target @c ListView.
         *
         * This property changes when the scroll state of the target @c %ListView changes.
         * A @c scrollingChanged(bool) signal is emitted whenever the property changes.
         *
         * The default value of this property is @c false.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bool scrolling READ isScrolling NOTIFY scrollingChanged FINAL)

        /*!
         * @brief A read-only property that indicates whether the list is positioned at the start of its items.
         *
         * This property changes when the scroll position of the target @c ListView changes.
         *
         * The default value of this property is @c false.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bool atBeginning READ isAtBeginning NOTIFY atBeginningChanged FINAL)

        /*!
         * @brief A read-only property that indicates if the list is positioned at the end of its items.
         *
         * This property changes when the scroll position of the target @c ListView changes.
         *
         * The default value of this property is @c false.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bool atEnd READ isAtEnd NOTIFY atEndChanged FINAL)

        /*!
         * @brief A read-only property that holds the index path to the first visible item.
         *
         * This property changes when the first visible item of the target @c ListView changes.
         * When there are no items in the list, this property holds an empty @c QVariantList.
         *
         * The default value of this property is an empty @c QVariantList.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QVariantList firstVisibleItem READ firstVisibleItem NOTIFY firstVisibleItemChanged FINAL)

    public:
        /*!
         * @brief Constructs a @c ListScrollStateHandler with a specified @c ListView as the 
         * target node.
         *
         * The constructed handler will receive scroll state changes from the
         * @c %ListView and emit a @c scrollingChanged() signal.
         *
         * The passed @c %ListView will assume ownership of this instance of
         * @c %ListScrollStateHandler.
         *
         * @param target The target @c %ListView for this handler.
         *
         * @since BlackBerry 10.0.0
         */
        explicit ListScrollStateHandler(ListView *target = NULL);

        /*!
         * @brief Destroys the handler.
         *
         * @since BlackBerry 10.0.0
         */
        virtual ~ListScrollStateHandler();

        /*!
         * @brief Returns the current scroll state of the target @c ListView.
         *
         * @return @c true if the target @c %ListView is currently scrolling, @c false otherwise.
         *
         * @since BlackBerry 10.0.0
         */
        bool isScrolling() const;

        /*!
         * @brief Checks if the target @c ListView is at its start position.
         *
         * @return @c true if the target @c %ListView is positioned at the start of its list items,
         * @c false otherwise.
         *
         * @since BlackBerry 10.0.0
         */
        bool isAtBeginning() const;

        /*!
         * @brief Checks if the target @c ListView is at its end position.
         *
         * @return @c true if the target @c %ListView is positioned at the end of its list items,
         * @c false otherwise.
         *
         * @since BlackBerry 10.0.0
         */
        bool isAtEnd() const;

        /*!
         * @brief Returns the first visible item in the target @c ListView.
         *
         * @return The first visible item in the target @c %ListView, or an empty
         *         @c QVariantList if the @c %ListView is empty.
         *
         * @since BlackBerry 10.0.0
         */
        QVariantList firstVisibleItem() const;

      Q_SIGNALS:
        /*!
         * @brief Emitted when the target @c ListView starts or stops scrolling.
         *
         * @param scrolling @c true when the target @c %ListView starts scrolling,
         *                  @c false when the target @c %ListView stops scrolling.
         *
         * @since BlackBerry 10.0.0
         */
        void scrollingChanged(bool scrolling);

        /*!
         * @brief Emitted when the target @c ListView scrolls to, or away from, its beginning
         *        position.
         *
         * @param atBeginning @c true if the target @c %ListView is at the beginning position,
         *                    @c false otherwise.
         *
         * @since BlackBerry 10.0.0
         */
        void atBeginningChanged(bool atBeginning);

        /*!
         * @brief Emitted when the target @c ListView scrolls to, or away from, its end
         *        position.
         *
         * @param atEnd @c true if the target @c %ListView is at the end position,
         *              @c false otherwise.
         *
         * @since BlackBerry 10.0.0
         */
        void atEndChanged(bool atEnd);

        /*!
         * @brief Emitted when the first visible item of the target
         *        @c ListView changes.
         *
         * @param firstVisibleItem The index path to the first visible item
         *              of the target @c %ListView, or an empty 
         *              @c QVariantList if there are no items in the
         *              @c %ListView.
         *
         * @since BlackBerry 10.0.0
         */
        void firstVisibleItemChanged(QVariantList firstVisibleItem);

    private:
        /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(ListScrollStateHandler)
        Q_DISABLE_COPY(ListScrollStateHandler)
        /*! @endcond */

    public:

        /*!
         * @brief A builder template for constructing a @c ListScrollStateHandler.
         *
         * @since BlackBerry 10.0.0
         */
        class BBCASCADES_EXPORT Builder {
        private:
            /*! \cond PRIVATE */
            ListScrollStateHandler &m_instance;
            /*! \endcond */

        public:
            /*! \cond PRIVATE */
            Builder(ListView *target);
            ~Builder();
            operator ListScrollStateHandler*();
            /*! \endcond */

            /*!
             * @brief A convenience method for connecting the receiver object's slot to
             * the handler's @c scrollingChanged() signal.
             *
             * The default connection type is @c Qt::AutoConnection.
             *
             * If @c QObject::connect() fails or any of the arguments is @c null an assert
             * statement is raised.
             *
             * Here's an example of how to connect the @c %onScrollingChanged()
             * slot in @c pMyObject to the handler's @c %scrollingChanged() signal:
             * @code
             * ListScrollStateHandler::create(pListView)
             *     .onScrollingChanged(pMyObject, SLOT(onScrollingChanged(bool)));
             * @endcode
             *
             * @param receiver A non-@c null receiver object.
             * @param method The non-@c null name of the receiver object slot to connect to.
             *
             * @see ListScrollStateHandler::scrollingChanged()
             * @see QObject::connect(const QObject * sender,
             *                       const char * signal, const char * method,
             *                       Qt::ConnectionType type)
             *
             * @since BlackBerry 10.0.0
             */
            Builder& onScrollingChanged(QObject *receiver, const char* method);

            /*!
             * @brief A convenience method for connecting the receiver object's slot to
             * the handler's @c atBeginningChanged() signal.
             *
             * The default connection type is @c Qt::AutoConnection.
             *
             * If @c QObject::connect() fails or any of the arguments is @c null an assert
             * statement is raised.
             *
             * Here's an example of how to connect the @c %atBeginningChanged()
             * slot in @c pMyObject to the handler's @c %atBeginningChanged() signal:
             * @code
             * ListScrollStateHandler::create(pListView)
             *     .atBeginningChanged(pMyObject, SLOT(atBeginningChanged(bool)));
             * @endcode
             *
             * @param receiver A non-@c null receiver object.
             * @param method The non-@c null name of the receiver object slot to connect to.
             *
             * @see ListScrollStateHandler::atBeginningChanged()
             * @see QObject::connect(const QObject * sender,
             *                       const char * signal, const char * method,
             *                       Qt::ConnectionType type)
             *
             * @since BlackBerry 10.0.0
             */
            Builder& onAtBeginningChanged(QObject *receiver, const char* method);

            /*!
             * @brief A convenience method for connecting the receiver object's slot to
             * the handler's @c atEndChanged() signal.
             *
             * The default connection type is @c Qt::AutoConnection.
             *
             * If @c QObject::connect() fails or any of the arguments is @c null an assert
             * statement is raised.
             *
             * Here's an example of how to connect the @c %atEndChanged()
             * slot in @c pMyObject to the handler's @c %atEndChanged() signal:
             * @code
             * ListScrollStateHandler::create(pListView)
             *     .atEndChanged(pMyObject, SLOT(atEndChanged(bool)));
             * @endcode
             *
             * @param receiver A non-@c null receiver object.
             * @param method The non-@c null name of the receiver object slot to connect to.
             *
             * @see ListScrollStateHandler::atEndChanged()
             * @see QObject::connect(const QObject * sender,
             *                       const char * signal, const char * method,
             *                       Qt::ConnectionType type)
             *
             * @since BlackBerry 10.0.0
             */
            Builder& onAtEndChanged(QObject *receiver, const char* method);

            /*!
             * @brief A convenience method for connecting the receiver object's slot to
             * the handler's @c firstVisibleItemChanged() signal.
             * 
             * The default connection type is @c Qt::AutoConnection.
             *
             * If @c QObject::connect() fails or any of the arguments is @c null an assert
             * statement is raised.
             *
             * The following example shows you how to connect the @c %firstVisibleItemChanged()
             * slot in @c pMyObject to the handler's @c %firstVisibleItemChanged() signal:
             * @code
             * ListScrollStateHandler::create(pListView)
             *     .onFirstVisibleItemChanged(pMyObject, SLOT(onFirstVisibleItemChanged(QVariantList)));
             * @endcode
             *
             * @param receiver A non-@c null receiver object.
             * @param method The non-@c null name of the receiver object slot to connect to.
             *
             * @see ListScrollStateHandler::onFirstVisibleItemChanged()
             * @see QObject::connect(const QObject * sender,
             *                       const char * signal, const char * method,
             *                       Qt::ConnectionType type)
             *
             * @since BlackBerry 10.0.0
             */
            Builder& onFirstVisibleItemChanged(QObject *receiver, const char* method);
        };

        /*!
         * @brief Constructs a builder for a @c %ListScrollStateHandler with a  
         * specified @c ListView as the target node.
         *
         * The constructed handler will receive calls when the scroll state of
         * the @c %ListView changes and emit the @c scrollingChanged() signal.
         *
         * The passed @c %ListView will assume ownership of this instance of
         * @c %ListScrollStateHandler.
         *
         * @code
         * ListScrollStateHandler::create(pListView)
         *     .onScrollingChanged(pMyObject, SLOT(onScrollingChanged(bool)));
         * @endcode
         *
         * @param target A non-@c null @c ListView that will be used as a target 
         *               for this handler.
         *
         * @since BlackBerry 10.0.0
         */
        static Builder create(ListView *target) {
            return Builder(target);
        }

    };

}
}

QML_DECLARE_TYPE(bb::cascades::ListScrollStateHandler)

#endif	/* cascades_listscrollstatehandler_h */
