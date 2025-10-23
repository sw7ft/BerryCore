/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_abstractdialog_h
#define cascades_abstractdialog_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/core/uiobject.h>

namespace bb {
    namespace cascades {

    class AbstractDialogPrivate;
    class AbstractA11yObject;

   /*!
    * @brief A base class for UI elements that represent full-screen view.
    *
    * The @c %AbstractDialog class is an abstract class that is used as a base for
    * UI elements that change the normal flow of an application. For example, in an
    * email application, adding a new contact could be considered a subtask that is
    * separate from the main flow of the application, and so could be implemented
    * using any of AbstractDialog's subclasses e.g. @c Sheet or @c Dialog.
    *
    * This class provides a way for subclasses to open or close the dialog using
    * corresponding @c open() and @c close() functions.
    *
    * The two concrete subclasses of this class are @c Sheet and @c Dialog.
    *
    * @see Sheet, Dialog
    *
    * @xmlonly
    * <apigrouping group="User interface/Application structure"/>
    * @endxmlonly
    *
    * @since BlackBerry 10.0.0
    */
    class BBCASCADES_EXPORT AbstractDialog : public UIObject {
    private:
        Q_OBJECT

       /*!
        * @brief Indicates whether the dialog is currently opened.
        *
        * If the value is @c true, the dialog is opened. If it is @c false, the dialog
        * is closed.
        *
        * The default value of this property is @c false.
        *
        * The @c openedChanged() signal is emitted when this property changes.
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(bool opened READ isOpened NOTIFY openedChanged FINAL)

        /*!
         * @brief Defines this dialog's accessibility objects.
         *
         * Accessibility objects are used by assistive technologies for
         * people with disabilities or special needs (for example, visual impairment).
         *
         * @see @c Control::accessibility
         *
         * @xmlonly
         * <qml>
         * <property groupedProperty="yes"/>
         * </qml>
         * @endxmlonly
         *
         * @since BlackBerry 10.2.0
         */
        Q_PROPERTY(bb::cascades::AbstractA11yObject* accessibility READ accessibility REVISION 2 FINAL)

    public:
        virtual ~AbstractDialog();

       /*!
        * @brief Opens the dialog.
        *
        * When the dialog is opened, the value of the @c #opened property changes to @c true
        * and the @c opened() signal is emitted. The @c opened() signal might not be emitted
        * immediately when this function is called, but could happen asynchronously at a
        * later time.
        *
        * If called when the dialog is already opening or closing, this function has no effect.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void open();

       /*!
        * @brief Closes the dialog.
        *
        * When the dialog is closed, the value of the @c #opened property changes to @c false 
        * and the @c closed() signal is emitted. The @c closed() signal might not be emitted
        * immediately when this function is called, but could happen asynchronously at a
        * later time.
        *
        * If called when the dialog is already opening or closing, this function has no effect.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void close();

       /*!
        * @brief Indicates whether the dialog is opened.
        *
        * @return @c true if the dialog is opened, @c false otherwise.
        *
        * @since BlackBerry 10.0.0
        */
        bool isOpened() const;

       /*!
        * @brief Returns the accessibility object.
        *
        * @return The accessibility object.
        *
        * @since BlackBerry 10.2.0
        */
        bb::cascades::AbstractA11yObject *accessibility() const;

    Q_SIGNALS:

       /*!
        * @brief Emitted when the @c #opened property changes its value.
        *
        * @param opened If @c true the dialog is opened, if @c false the dialog is
        * closed.
        *
        * @since BlackBerry 10.0.0
        */
        void openedChanged(bool opened);

       /*!
        * @brief Emitted when the dialog is opened.
        *
        * The signal is emitted asynchronously when the dialog is completely
        * opened after the open animation is finished.
        *
        * @since BlackBerry 10.0.0
        */
        void opened();

       /*!
        * @brief Emitted when the dialog is closed.
        *
        * The signal is emitted asynchronously when the dialog is completely
        * closed after the close animation is finished.
        *
        * @since BlackBerry 10.0.0
        */
        void closed();

    protected:
        /*! \cond PRIVATE */
        explicit AbstractDialog(AbstractDialogPrivate &_d_ptr, QObject *parent);
        /*! \endcond */

    private:
        /*! \cond PRIVATE */
        Q_DECLARE_PRIVATE(AbstractDialog)
        Q_DISABLE_COPY(AbstractDialog)

        typedef AbstractDialog ThisClass;
        typedef UIObject BaseClass;
        /*! \endcond */

    public:
       /*!
        * @brief A builder template for constructing an @c %AbstractDialog.
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
            * @brief Opens the @c %AbstractDialog.
            *
            * Using this convenience function in the builder pattern is the equivalent of the
            * following:
            * @code
            * myDialog->open();
            * @endcode
            *
            * @since BlackBerry 10.0.0
            */
            BuilderType& open()
            {
                this->instance().open();
                return this->builder();
            }

           /*!
            * @brief A convenience method for connecting the passed receiver's slot to
            * the @c opened() signal with the default connection type @c Qt::AutoConnection.
            *
            * Example:
            * @code
            * Dialog *myDialog = Dialog::create()
            *                    .onOpened(this, SLOT(onOpenedHandler()));
            * @endcode
            *
            * @param receiver A receiver object that is not @c null.
            * @param method The name (that is not @c null) of the slot in the receiver object
            * to connect to.
            *
            * @see BaseObject::TBuilder::connect()
            *
            * @since BlackBerry 10.0.0
            */
            BuilderType& onOpened(const QObject* receiver, const char *method) {
                this->connect(SIGNAL(opened()), receiver, method);
                return this->builder();
            }

           /*!
            * @brief A convenience method for connecting the passed receiver's slot to
            * the @c closed() signal with the default connection type @c Qt::AutoConnection.
            *
            * Example:
            * @code
            * Dialog *myDialog = Dialog::create()
            *                    .onClosed(this, SLOT(onClosedHandler()));
            * @endcode
            *
            * @param receiver A receiver object that is not @c null.
            * @param method The name (that is not @c null) of the slot in the receiver object
            * to connect to.
            *
            * @see BaseObject::TBuilder::connect()
            *
            * @since BlackBerry 10.0.0
            */
            BuilderType& onClosed(const QObject* receiver, const char *method) {
                this->connect(SIGNAL(closed()), receiver, method);
                return this->builder();
            }
            /*!
            * @brief Sets the accessibility name property of the @c %AbstractDialog.
            *
            * @param name The text string to use as the accessibility name of the control.
            *
            * @see Control::accessibility
            *
            * @since BlackBerry 10.2.0
            */
            BuilderType& accessibilityName(const QString & name) {
                this->instance().accessibility()->setName(name);
                return this->builder();
            }

           /*!
            * @brief Sets the accessibility description property of the @c %AbstractDialog.
            *
            * @param description The text string to use as the accessibility description of the control.
            *
            * @see Control::accessibility
            *
            * @since BlackBerry 10.2.0
            */
            BuilderType& accessibilityDescription(const QString & description) {
                this->instance().accessibility()->setDescription(description);
                return this->builder();
            }

           /*!
            * @brief Adds a label object to the list of labels in the accessibility object.
            *
            * @param labelledBy The object to add as an accessibility label for the @c AbstractDialog.
            *
            * @see Control::accessibility
            *
            * @since BlackBerry 10.2.0
            */
            BuilderType& accessibilityAddLabel(bb::cascades::UIObject* labelledBy) {
                this->instance().accessibility()->addLabel(labelledBy);
                return this->builder();
            }
        };
    };
}
}

QML_DECLARE_TYPE(bb::cascades::AbstractDialog)

#endif
