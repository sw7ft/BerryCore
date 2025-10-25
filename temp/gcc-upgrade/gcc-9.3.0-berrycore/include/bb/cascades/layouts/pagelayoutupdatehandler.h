/*
 * Copyright (C) 2014 BlackBerry Limited. All rights reserved.
 */

#ifndef cascades_pagelayoutupdatehandler_h
#define cascades_pagelayoutupdatehandler_h

#include <bb/cascades/bbcascades_global.h>

#include <QtCore/QObject>
#include <QtDeclarative/QtDeclarative>

#include <bb/cascades/BaseObject>

namespace bb {
namespace cascades {

    class Page;
    class PageLayoutUpdateHandlerPrivate;

    /*!
     * @brief Used for listening to layout and sizing changes on a page.
     *
     * Here's a useful example of how to use the page's @c #bottomOverlayHeight to pad
     * a @c ListView so that the last item isn't obscured by the action bar when the user
     * has scrolled to the bottom:
     * @snippet tad/examples/applicationstructure/page/assets/main.qml page_qml3
     *
     * @xmlonly
     * <apigrouping group="User interface/Layouts"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.3.0
     */
    class BBCASCADES_EXPORT PageLayoutUpdateHandler : public BaseObject {
    private:
        Q_OBJECT

        /*!
         * @brief The height of the obscured area at the bottom of the target page.
         *
         * The property changes whenever the target page's bottom overlay area is updated. It is
         * the area at the bottom obscurred by other visual elements, typically the action bar.
         * The virtual keyboard is not considered as an overlay.
         *
         * The property is changed asynchronously when the layout system updates the target page.
         * Updates are triggered only once a change in position or dimensions has been completed.
         * Updates will not be made for any intermediate values while a control is being implicitly
         * animated by the layout system.
         *
         * The target page can only be specified during construction-time using the
         * constructor, builder, or as a parent component in QML. The update handler cannot
         * be changed at run-time.
         *
         * The default value is @c 0.0 if the handler doesn't have a target or if the target
         * hasn't been laid out yet.
         *
         * Here's as example of how to track a page's bottom overlay height in C++:
         * @code
         * Page *page = Page::create();
         * PageLayoutUpdateHandler::create(page)
         *     .onBottomOverlayHeightChanged(this, SLOT(onBottomOverlayHeightChanged(float)));
         * @endcode
         *
         * Here's as example of how to track a page's bottom overlay height in QML:
         * @code
         * Page {
         *    attachedObjects: [
         *        PageLayoutUpdateHandler {
         *            id: pageLayoutUpdateHandler
         *            onBottomOverlayHeightChanged: {
         *                console.log("bottomOverlayHeight: " + bottomOverlayHeight);
         *            }
         *        }
         *    ]
         * }
         * @endcode
         *
         * @since BlackBerry 10.3.0
         */
        Q_PROPERTY(float bottomOverlayHeight READ bottomOverlayHeight NOTIFY bottomOverlayHeightChanged FINAL)

    public:
        /*!
         * @brief Constructs a @c %PageLayoutUpdateHandler without a specified target page.
         *
         * @note There is no way to specify the target page for a handler constructed with
         * this constructor.
         *
         * @since BlackBerry 10.3.0
         */
        explicit PageLayoutUpdateHandler();

        /*!
         * @brief Constructs a @c %PageLayoutUpdateHandler with a specified page as the
         * target node.
         *
         * The constructed handler will receive layout frame updates from the
         * control and emit the appropriate signal.
         *
         * The passed page will assume ownership of this instance of
         * @c %PageLayoutUpdateHandler.
         *
         * @param target A page which will be used as a target for this handler.
         *
         * @since BlackBerry 10.3.0
         */
        explicit PageLayoutUpdateHandler(Page *target);

        /*!
         * @brief Destroys the handler.
         *
         * @since BlackBerry 10.3.0
         */
        virtual ~PageLayoutUpdateHandler();

        /*!
         * @brief Returns the height of the obscured area at the bottom of the page.
         *
         * @return The height in pixels of the obscured area at the bottom of the page.
         *
         * @since BlackBerry 10.3.0
         */
        float bottomOverlayHeight() const;

    Q_SIGNALS:

        /*!
         * @brief Emitted when the obscured area at the bottom of the page changes.
         *
         * @param bottomOverlayHeight The height in pixels of the obscured area at the bottom of the page.
         *
         * @since BlackBerry 10.3.0
         */
        void bottomOverlayHeightChanged(float bottomOverlayHeight);

    private:
        /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(PageLayoutUpdateHandler)
        Q_DISABLE_COPY(PageLayoutUpdateHandler)
        /*! @endcond */

    public:

        /*!
         * @brief Builder for constructing PageLayoutUpdateHandler objects
         *
         * @since BlackBerry 10.3.0
         */
        class BBCASCADES_EXPORT Builder {
        private:
            /*! \cond PRIVATE */
            PageLayoutUpdateHandler &m_instance;
            /*! \endcond */

        public:
            /*! \cond PRIVATE */
            Builder(Page *target);
            ~Builder();
            operator PageLayoutUpdateHandler*();
            /*! \endcond */

            /*!
             * @brief A convenience method for connecting the receiver object's slot to
             * the handler's @c bottomOverlayHeightChanged() signal.
             *
             * The default connection type @c Qt::AutoConnection.
             *
             * If @c QObject::connect() fails or any of the arguments is @c null an assert
             * statement is raised.
             *
             * Here's an example of how to connect the @c onBottomOverlayHeightChanged()
             * slot in @c pMyObject to the handler's @c bottomOverlayHeightChanged() signal:
             * @code
             * PageLayoutUpdateHandler::create(pPage)
             *     .onBottomOverlayHeightChanged(pMyObject, SLOT(onBottomOverlayHeightChanged(float)));
             * @endcode
             *
             * @param receiver A non-@c null receiver object.
             * @param method The non-@c null name of the receiver object slot to connect to.
             *
             * @see PageLayoutUpdateHandler::bottomOverlayHeightChanged()
             * @see QObject::connect(const QObject * sender,
             *                       const char * signal, const char * method,
             *                       Qt::ConnectionType type)
             *
             * @since BlackBerry 10.3.0
             */
            Builder& onBottomOverlayHeightChanged(QObject *receiver, const char* method);
        };

        /*!
         * @brief Constructs a Builder for a @c %PageLayoutUpdateHandler with a specified page as the
         * target node.
         *
         * The constructed handler will receive layout updates from the
         * page and emit the appropriate signal.
         *
         * The passed page will assume ownership of this instance of
         * @c %PageLayoutUpdateHandler.
         *
         * @code
         * PageLayoutUpdateHandler::create(pPage)
         *     .onBottomOverlayHeightChanged(pMyObject, SLOT(onBottomOverlayHeightChanged(float)));
         * @endcode
         *
         * @param target A non-@c null page that will be used as a target for this handler.
         *
         * @since BlackBerry 10.3.0
         */
        static Builder create(Page *target) {
            return Builder(target);
        }

    };

}
}

QML_DECLARE_TYPE(bb::cascades::PageLayoutUpdateHandler)

#endif	/* cascades_pagelayoutupdatehandler_h */
