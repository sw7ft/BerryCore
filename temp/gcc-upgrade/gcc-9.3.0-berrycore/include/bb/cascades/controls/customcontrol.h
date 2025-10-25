/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_customcontrol_h
#define cascades_customcontrol_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/controls/control.h>


namespace bb {
    namespace cascades {

    class VisualNode;
    class Container;
    class CustomControlPrivate;
    class Spacings;

    /*!
     * @brief A base class that is used for creating custom controls.
     *
     * Custom controls are designed to behave like the core controls that come with the Cascades framework.
     * To create a custom control you must first extend the @c %CustomControl class. In this example, a class called
     * @c CustomTextControl is created which has a property called @c text, functions for getting and setting the text, and
     * a signal that is emitted when the text changes.
     *
     * @snippet tad/examples/controls/customcontrol/src/CustomTextControl.h customcontrol1
     *
     * The constructor for @c CustomTextControl creates a simple background and a @c TextField as the visuals for
     * the control. The visuals are set by calling @c setRoot().
     *
     * @snippet tad/examples/controls/customcontrol/src/CustomTextControl.cpp customcontrol2
     *
     * In order to expose the class to be used from within QML you must call @c qmlRegisterType() from
     * the application.
     *
     * @snippet tad/examples/controls/customcontrol/src/CustomControlExamples.cpp customcontrol3
     *
     * From QML you can import the library that you've defined and use the control as you normally would.
     *
     * @snippet tad/examples/controls/customcontrol/assets/main.qml customcontrol_qml
     *
     * The size of the custom control behaves as follows:
     * - By default, the width and height are adjusted automatically to fit the root node.
     * - The width is adjustable using the @c Control::preferredWidth, @c Control::minWidth and 
     * @c Control::maxWidth properties.
     * - The height is adjustable using the @c Control::preferredHeight, @c Control::minHeight and 
     * @c Control::maxHeight and properties.
     *
     * @xmlonly
     * <apigrouping group="User interface/Core controls"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT CustomControl : public Control
    {
        Q_OBJECT

    public:
      virtual ~CustomControl();

      /*!
         * @brief Get the soft margin for Custom Control object
         *
         * Using the returned Spacings object it is possible to get or set the soft margin offset values.
         *
         * @return A pointer to a Spacings object.
         *
         * @since BlackBerry 10.2.0
         */
      bb::cascades::Spacings *softMargin();

    protected:
        /*!
         * @brief Constructs a @c %CustomControl.
         * If not @c 0, the ownership of the constructed @c %CustomControl will be transferred to the parent.
         *
         * @param parent The parent container or @c 0. The parameter is optional and will default to @c 0 if not specified.
         *
         * @since BlackBerry 10.0.0
         */
        explicit CustomControl(Container * parent = 0);

       /*!
        * @brief Gets the root @c VisualNode of the @c %CustomControl.
        *
        * @return The root of the @c VisualNode tree of the @c %CustomControl. The @c %CustomControl still 
        * owns the root @c VisualNode.
        *
        * @since BlackBerry 10.0.0
        */
        bb::cascades::VisualNode *root() const;

       /*!
        * @brief Sets the root @c VisualNode of the @c %CustomControl.
        *
        * The @c %CustomControl will take over ownership of the new root. The old root, if there is one, will 
        * be replaced but is not deleted. The @c %CustomControl will still retain ownership of the old root.
        *
        * @param root The root of the @c VisualNode tree of the @c %CustomControl.
        *
        * @since BlackBerry 10.0.0
        */
        void setRoot(VisualNode *root);

       /*!
        * @brief Sets an accessibility object for this control.
        *
        * Once completed, ownership of the accessibility object is assigned to the custom control.
        *
        * Unlike controls with built-in accessibility objects which can't overridden, this class
        * allows overriding the default accessibility object with a custom one, typically a
        * @c CustomA11yObject
        *
        * The accessibility object is expected to be set once (for example when assistive technology
        * is enabled).
        *
        * @param accessibility new accessibility object
        * @since BlackBerry 10.2.0
        */
        void setAccessibility(bb::cascades::AbstractA11yObject *accessibility);

      /*! @cond PRIVATE */

    private:
        Q_DECLARE_PRIVATE(CustomControl)
        Q_DISABLE_COPY(CustomControl)
       /*! @endcond */

    };
} // namespace bb::cascades
}

QML_DECLARE_TYPE(bb::cascades::CustomControl)

#endif // ifndef cascades_customcontrol_h

