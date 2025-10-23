/* Copyright (C) 2012-2013 Research In Motion Limited.  */

#ifndef cascades_layoutupdatehandler_h
#define cascades_layoutupdatehandler_h

#include <bb/cascades/bbcascades_global.h>

#include <QtCore/QObject>
#include <QtDeclarative/QtDeclarative>
#include <QRectF>

#include <bb/cascades/BaseObject>

namespace bb {
namespace cascades {

    class Control;
    class LayoutUpdateHandlerPrivate;

    /*!
     * @brief Used for listening to layout and sizing changes on a control.
     *
     * The @c #layoutFrame property provides read only access to target control's layout
     * frame. The layout frame is defined by a @c QRectF object that specifies
     * a rectangle's X and Y coordinates and length and width.
     * 
     * The property is changed asynchronously when the layout system changes the target
     * control's layout position and dimensions.
     *
     * Updates are triggered only once a change in position or dimensions has been completed.
     * Updates will not be made for any intermediate values while a control is being implicitly
     * animated by the layout system.
     * 
     * The target control can only be specified during construction time using the
     * constructor, builder, or as a parent component in QML. The update handler cannot
     * be changed at run time.
     *
     * Here's an example for how to track a container's layout position and size changes in C++.
     * 
     * @code
     * Control *pButton = Button::create().text("Check out my layout!");
     *
     * LayoutUpdateHandler::create(pButton)
     *     .onLayoutFrameChanged(this, SLOT(handleLayoutFrameUpdated(QRectF)));
     *
     * // pButton owns the created handler so there is no need to keep a reference to it,
     * // and it will be deleted when the button is deleted.
     * @endcode
     *
     * In QML, the handler must be attached to a Control derivative, otherwise
     * the handler will have no effect. Here's an example of how the
     * handler can be used in QML. The position and size of
     * the blue container is bound to the layout position and size of the button.
     *
     * @code
     * Container {
     *     layout: AbsoluteLayout {}
     *
     *     // The position and size of this container is bound to
     *     // the position and size of the button.
     *     Container {
     *         preferredWidth: handler.layoutFrame.width + 20
     *         preferredHeight: handler.layoutFrame.height + 20
     *         layoutProperties: AbsoluteLayoutProperties {
     *             positionX: handler.layoutFrame.x - 10
     *             positionY: handler.layoutFrame.y - 10
     *         }
     *         background: Color.Blue
     *     }
     *     Button {
     *         text: "I'm being followed!"
     *         layoutProperties: AbsoluteLayoutProperties {
     *             id: props
     *         }
     *         onClicked: {
     *             props.positionX += 10;
     *             props.positionY += 10;
     *         }
     *         attachedObjects: [
     *             // This handler is tracking the layout frame of the button.
     *             LayoutUpdateHandler {
     *                 id: handler
     *                 onLayoutFrameChanged: {
     *                     // Individual layout frame values can be
     *                     // retrieved from the signal parameter
     *                     console.log("Layout Frame: [" +
     *                                 layoutFrame.x + ", " + layoutFrame.y + ", " +
     *                                 layoutFrame.width + ", " + 
     *                                 layoutFrame.height + "]");
     *                 }
     *             }
     *         ]
     *     }
     * }
     * @endcode
     *
     * @xmlonly
     * <apigrouping group="User interface/Layouts"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT LayoutUpdateHandler : public BaseObject {
    private:
        Q_OBJECT

        /*!
         * @brief A read only property representing the layout frame of the target control.
         *
         * The property changes whenever the layout position and/or size of the 
         * target control is updated.
         *
         * A @c layoutFrameChanged(const QRect&) signal is emitted whenever the property
         * changes.
         *
         * The default value of this property is a null 
         * (QRectF::isNull() returns @c true) rectangle positioned at @c 0,0
         * if the handler doesn't have a target or if the target hasn't been laid out yet.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QRectF layoutFrame READ layoutFrame NOTIFY layoutFrameChanged FINAL);
    
    public:
        /*!
         * @brief Constructs a @c %LayoutUpdateHandler without a specified target control.
         *
         * @note There is no way to specify the target control for a handler constructed with 
         * this constructor.
         *
         * @since BlackBerry 10.0.0
         */
        explicit LayoutUpdateHandler();

        /*!
         * @brief Constructs a @c %LayoutUpdateHandler with a specified control as the 
         * target node.
         *
         * The constructed handler will receive layout frame updates from the
         * control and emit the @c layoutFrameChanged() signal.
         *
         * The passed control will assume ownership of this instance of
         * @c %LayoutUpdateHandler.
         *
         * @param target A control which will be used as a target for this handler.
         *
         * @since BlackBerry 10.0.0
         */
        explicit LayoutUpdateHandler(Control *target);

        /*!
         * @brief Destroys the handler.
         *
         * @since BlackBerry 10.0.0
         */
        virtual ~LayoutUpdateHandler();
    
        /*!
         * @brief Returns the current layout frame (position and dimensions) of the target control.
         *
         * @return A rectangle representing the current layout frame, or a null rectangle 
         * (QRectF::isNull() returns @c true)
         * positioned at @c 0,0 if the target control hasn't been laid out yet.
         *
         * @since BlackBerry 10.0.0
         */
        QRectF layoutFrame() const;

    Q_SIGNALS:
    
        /*!
         * @brief Emitted when target control's layout position and/or size changed.
         *
         * This signal is emitted when the target control's layout is updated. 
         *
         * The parameter is a rectangle with x, y, width, and height values representing the
         * layout position and dimensions of the target control.
         *
         * The layout information that is sent refers to local coordinates, which means that it
         * is relative to the parent's position and does not take transforms into
         * consideration.
         *
         * @param layoutFrame A rectangle representing the size and position of the
         * target control in local coordinates (meaning it is relative
         * to control's parent).
         *
         * @since BlackBerry 10.0.0
         */
        void layoutFrameChanged(const QRectF &layoutFrame);
    
    private:
        /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(LayoutUpdateHandler)
        Q_DISABLE_COPY(LayoutUpdateHandler)
        /*! @endcond */

    public:

        /*!
         * @brief Builder for constructing LayoutUpdateHandler objects
         *
         * @since BlackBerry 10.0.0
         */
        class BBCASCADES_EXPORT Builder {
        private:
            /*! \cond PRIVATE */
            LayoutUpdateHandler &m_instance;
            /*! \endcond */

        public:
            /*! \cond PRIVATE */
            Builder(Control *target);
            ~Builder();
            operator LayoutUpdateHandler*();
            /*! \endcond */

            /*!
             * @brief A convenience method for connecting the receiver object's slot to
             * the handler's @c layoutFrameChanged() signal.
             * 
             * The default connection type @c Qt::AutoConnection.
             *
             * If @c QObject::connect() fails or any of the arguments is @c null an assert 
             * statement is raised.
             *
             * Here's an example of how to connect the @c onLayoutFrameChanged()
             * slot in @c pMyObject to the handler's @c layoutFrameChanged() signal:
             * @code
             * LayoutUpdateHandler::create(pControl)
             *     .onLayoutFrameChanged(pMyObject, SLOT(onLayoutFrameChanged(QRectF)));
             * @endcode
             *
             * @param receiver A non-@c null receiver object.
             * @param method The non-@c null name of the receiver object slot to connect to.
             *
             * @see LayoutUpdateHandler::layoutFrameChanged()
             * @see QObject::connect(const QObject * sender,
             *                       const char * signal, const char * method,
             *                       Qt::ConnectionType type)
             *
             * @since BlackBerry 10.0.0
             */
            Builder& onLayoutFrameChanged(QObject *receiver, const char* method);
        };

        /*!
         * @brief Constructs a Builder for a @c %LayoutUpdateHandler with a specified control as the 
         * target node.
         *
         * The constructed handler will receive layout frame updates from the
         * control and emit the @c layoutFrameChanged() signal.
         *
         * The passed control will assume ownership of this instance of
         * @c %LayoutUpdateHandler.
         *
         * @code
         * LayoutUpdateHandler::create(pControl)
         *     .onLayoutFrameChanged(pMyObject, SLOT(onLayoutFrameChanged(QRectF)));
         * @endcode
         *
         * @param target A non-@c null control that will be used as a target for this handler.
         *
         * @since BlackBerry 10.0.0
         */
        static Builder create(Control *target) {
            return Builder(target);
        }

    };

}
}

QML_DECLARE_TYPE(bb::cascades::LayoutUpdateHandler)

#endif	/* cascades_layoutupdatehandler_h */
