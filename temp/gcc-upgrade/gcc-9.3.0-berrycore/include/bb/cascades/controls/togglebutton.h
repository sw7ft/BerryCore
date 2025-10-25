/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_togglebutton_h
#define cascades_togglebutton_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/controls/abstracttogglebutton.h>

namespace bb {
    namespace cascades {

    class ToggleButtonPrivate;
    class Container;


    /*!
     *
     * @brief A fixed-size switch control with two states: checked or unchecked.
     * @image html toggle_on_off.png Toggle buttons on and off.
     *
     * The size of the toggle button behaves as follows:
     * - The width is fixed, so the properties Control::preferredWidth, Control::minWidth and Control::maxWidth are not used.
     * - The height is fixed, so the properties Control::preferredHeight, Control::minHeight and Control::maxHeight are not used.
     *
     * Creating a %ToggleButton using the builder pattern:
     *
     * @snippet tad/examples/controls/togglebutton/src/ToggleButtonExamples.cpp togglebutton
     *
     * Creating a %ToggleButton in QML and displaying current status:
     *
     * @snippet tad/examples/controls/togglebutton/assets/main.qml togglebutton_qml
     *
     * @xmlonly
     * <apigrouping group="User interface/Core controls"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT ToggleButton : public AbstractToggleButton
    {
    private:
        Q_OBJECT


    public:
        /*!
         * @brief Constructs a toggle button with the specified parent container.
         *
         * If the specified parent is not @c 0, the ownership of the constructed toggle button is
         * transferred to the parent.
         *
         * @param parent The parent container, or @c 0. This parameter is optional.
         * The default is 0 if you don't specify a parent.
         *
         * @since BlackBerry 10.0.0
         */
        explicit ToggleButton(Container * parent = 0);

        /*!
        * @brief Destructs this toggle button.
         *
         * @since BlackBerry 10.0.0
        */
        virtual ~ToggleButton();

    private:
        Q_DECLARE_PRIVATE(ToggleButton)
        Q_DISABLE_COPY(ToggleButton)
        /*! @cond PRIVATE */
        typedef ToggleButton ThisClass;
        typedef AbstractToggleButton BaseClass;
        /*! @endcond */
    public:
        /*!
         * @brief A builder template for constructing a ToggleButton.
         *
         * See ToggleButton::create() for getting a concrete builder for constructing a %ToggleButton.
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
        };

        /*!
         * @brief A concrete builder class used to construct a ToggleButton.
         *
         * See ToggleButton::create() for more information about using the builder.
         *
         * @since BlackBerry 10.0.0
         */
        class Builder : public TBuilder<Builder, ToggleButton>
        {
         public:
            Builder() : TBuilder<Builder, ToggleButton>(new ToggleButton())
            {
            }
         };

        /*!
         * @brief Constructs a builder used to construct a ToggleButton.
         *
         * @return A builder used to construct a %ToggleButton.
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

QML_DECLARE_TYPE(bb::cascades::ToggleButton)

#endif
