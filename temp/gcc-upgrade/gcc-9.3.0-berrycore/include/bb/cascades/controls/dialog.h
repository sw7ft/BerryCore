/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_dialog_h
#define cascades_dialog_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/controls/abstractdialog.h>

namespace bb {
    namespace cascades {

    class Control;
    class DialogPrivate;

   /*!
    *
    * @brief A class that represents a full-screen view as a dialog.
    *
    * @image html cascades_system_dialog_box.png A screen shot showing a dialog box
    *
    * A @c %Dialog is a full-screen view that is displayed as a transparent layer on top
    * of the current screen context. Basically, it's a separate view within the current
    * application.
    *
    * @c %Dialog is primarily used to display UI options that are related to the creation
    * or selection of content, often as a temporary subtask that's outside the main
    * navigation of the application. You can think of a dialog as representing a separate
    * flow, or a detour, from the main application flow.
    *
    * A dialog always occupies the entire screen when it is displayed, and can contain
    * @c Control components. An opened dialog will always be shown on top of the current
    * screen context. Any screen context directly underneath a dialog is still visible
    * when a dialog is shown.
    *
    * You can attach a dialog to any @c UIObject by using the @c attachedObjects property.
    *
    * Defining a Dialog in C++:
    *
    * @code
    * Dialog* pMyDialog = Dialog::create()
    *                     .content(Container::create())
    *                     .onClosed(this, SLOT(onClosedHandler()))
    *                     .open();
    * @endcode
    *
    * Defining a Dialog in QML:
    *
    * @code
    *  Page {
    *      attachedObjects: [
    *          Dialog {
    *             id: myDialog
    *
    *             Container {
    *                 horizontalAlignment: HorizontalAlignment.Fill
    *                 verticalAlignment: VerticalAlignment.Fill
    *
    *                 Button {
    *                     horizontalAlignment: HorizontalAlignment.Center
    *                     text: "Hide Dialog"
    *                     onClicked: myDialog.close()
    *                 }
    *             }
    *         }
    *     ]
    *     actions: [
    *          ActionItem {
    *              title: "Show Dialog"
    *              ActionBar.placement: ActionBarPlacement.OnBar
    *              onTriggered: {
    *                 myDialog.open();
    *              }
    *          }
    *      ]
    *  }
    * @endcode
    *
    * @xmlonly
    * <qml>
    * <class register="yes"/>
    * </qml>
    * @endxmlonly
    *
    * @xmlonly
    * <apigrouping group="User interface/Application structure"/>
    * @endxmlonly
    *
    * @since BlackBerry 10.0.0
    */
    class BBCASCADES_EXPORT Dialog : public AbstractDialog {
    private:
        Q_OBJECT

       /*!
        * @brief The root control for the @c %Dialog.
        *
        * This property is the default property of the @c %Dialog control, so it does not need
        * to be explicitly declared in the QML. A control added inside the @c %Dialog will
        * automatically be assigned to the @c content property.
        *
        * @code
        *  Page {
        *     attachedObjects: [
        *         Dialog {
        *             Container {
        *                 Button {}
        *                 Button {}
        *             }
        *         }
        *     ]
        *  }
        * @endcode
        *
        * The following code sample produces the same result as the one above.
        *
        * @code
        *  Page {
        *       attachedObjects: [
        *           Dialog {
        *               content: Container {
        *                   Button {}
        *                   Button {}
        *               }
        *           }
        *       ]
        *  }
        * @endcode
        *
        * @xmlonly
        * <qml>
        * <property defaultProperty="yes"/>
        * </qml>
        * @endxmlonly
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(bb::cascades::Control* content READ content WRITE setContent NOTIFY contentChanged RESET resetContent FINAL)
        Q_CLASSINFO("DefaultProperty", "content")

    public:
       /*!
        * @brief Constructs a Dialog instance
        *
        * @since BlackBerry 10.0.0
        */
        explicit Dialog(UIObject *parent = 0);
        virtual ~Dialog();

       /*!
        * @brief Sets the content of this @c %Dialog.
        *
        * Ownership of the content will always be transferred to this @c %Dialog.
        * If this @c %Dialog already has content, the old content is still owned by this @c %Dialog
        * and will be destroyed when this @c %Dialog is destroyed.
        *
        * If content was successfully set using this function, the @c contentChanged()
        * signal is emitted.
        *
        * @param content The content to set. Can be @c 0 to remove content (old content
        * will still be owned by this @c %Dialog).
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void setContent(bb::cascades::Control* content);

       /*!
        * @brief Gets the active content of this @c %Dialog.
        *
        * Ownership will not be transferred.
        *
        * @return The content of this @c %Dialog.
        *
        * @since BlackBerry 10.0.0
        */
        bb::cascades::Control* content() const;

       /*!
        * @brief Resets the content for this @c %Dialog.
        *
        * This function resets the content for this @c %Dialog.
        * Content will be removed and content property set to 0.
        * This is equivalent to setContent(0).
        * When this function completes, the @c contentChanged() signal is emitted.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void resetContent();

    Q_SIGNALS:

       /*!
        * @brief Emitted when the content of this @c %Dialog has changed.
        *
        * @param content The new content of this @c %Dialog.
        *
        * @since BlackBerry 10.0.0
        */
        void contentChanged(bb::cascades::Control* content);

    private:
        /*! \cond PRIVATE */
        Q_DECLARE_PRIVATE(Dialog)
        Q_DISABLE_COPY(Dialog)

        typedef Dialog ThisClass;
        typedef AbstractDialog BaseClass;
        /*! \endcond */

    public:
       /*!
        * @brief A builder template for constructing a @c %Dialog.
        *
        * To retrieve the builder, call @c Dialog::create().
        *
        * @since BlackBerry 10.0.0
        */
        template <typename BuilderType, typename BuiltType>
        class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType>
        {
        protected:
            TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node)
            {
            }
        public:

           /*!
            * @brief Sets the content for the @c %Dialog.
            *
            * Using this convenience function in the builder pattern is equivalent to the following:
            * @code
            * myDialog->setContent(content);
            * @endcode
            *
            * @param content The content for the @c %Dialog.
            *
            * @since BlackBerry 10.0.0
            */
            BuilderType& content(Control *content)
            {
                this->instance().setContent(content);
                return this->builder();
            }
        };

       /*!
        * @brief A builder that constructs a @c %Dialog.
        *
        * To retrieve the builder, call @c Dialog::create().
        *
        * @since BlackBerry 10.0.0
        */
        class Builder : public TBuilder<Builder, Dialog>
        {
        public:
            explicit Builder() : TBuilder<Builder, Dialog>(new Dialog())
            {
            }
        };

       /*!
        * @brief Creates and returns a builder for constructing a @c %Dialog.
        *
        * Using the builder to create a @c %Dialog:
        * @code
        * Dialog* myDialog = Dialog::create();
        * @endcode
        *
        * @return A Builder used for constructing a @c %Dialog.
        *
        * @since BlackBerry 10.0.0
        */
        static Builder create()
        {
            return Builder();
        }
    };
}
}

QML_DECLARE_TYPE(bb::cascades::Dialog)

#endif
