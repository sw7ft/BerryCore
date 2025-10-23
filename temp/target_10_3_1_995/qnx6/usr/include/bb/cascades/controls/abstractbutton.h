/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_abstractbutton_h
#define cascades_abstractbutton_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/controls/control.h>

namespace bb {
    namespace cascades {
    
    class AbstractButtonPrivate;
    class Container;

    /*!
     * @brief A clickable abstract button.
     *
     * @c %AbstractButton is used expose common properties to buttons that inherit it,
     * namely the clicked() signal, which is emitted when a user clicks a button.
     * Typically, this signal is used to trigger some programmatic action in response.
     *
     * The @c %AbstractButton does not interact with the layout system - that task
     * is left to deriving classes.
     *
     * In some cases, you might want the ability to connect a group of buttons to a common click handler.
     * Here's an example of how to do that using @c %AbstractButton. In the @c setupButtonHandling() method,
     * a vector of buttons is created, and the @c clicked() signal for each button is connected to the
     * @c buttonClickHandler() method.
     *
     * @snippet tad/examples/controls/abstractbutton/src/AbstractButtonExamples.cpp abstractbutton1
     * @snippet tad/examples/controls/abstractbutton/src/AbstractButtonExamples.cpp abstractbutton2
     *
     *
     * @xmlonly
     * <apigrouping group="User interface/Core controls"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT AbstractButton : public Control {
    private:
        Q_OBJECT

    public:

        /*!
         * @brief Destructs this abstract button.
         *
         * @since BlackBerry 10.0.0
         */
        virtual ~AbstractButton();

    Q_SIGNALS:

        /*!
         * @brief Emitted when the button is clicked.
         *
         * @since BlackBerry 10.0.0
         */
        void clicked();

    protected:
        /*! @cond PRIVATE */

        /*!
         * @brief Constructs an abstract, clickable button and specifies the
         * parent container.
         * 
         * The ownership of the button is transferred to the parent if a parent
         * is specified.
         *
         * @param _d_ptr The private representation of the object.
         * @param parent The parent container, or @c 0. This parameter is
         * optional. The default is @c 0 if you don't specify a parent.
         */
        explicit AbstractButton(AbstractButtonPrivate &_d_ptr, Container * parent = 0);

        /*! \endcond */

    private:

        Q_DECLARE_PRIVATE(AbstractButton)
        Q_DISABLE_COPY(AbstractButton)

        /*! \cond PRIVATE */
        // The class in which scope we're currently inside.
        typedef AbstractButton ThisClass;
        // References the class which ThisClass derives from.
        typedef Control BaseClass;
        /*! \endcond */

   protected:
        /*!
         * @brief A builder template for constructing a button.
         *
         * The template will only be used by inheriting classes.
         *
         * @since BlackBerry 10.0.0
         */
        template <typename BuilderType, typename BuiltType>
        class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType> {
        protected:
            explicit TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node) {}
        };
    };
    }
}

QML_DECLARE_TYPE(bb::cascades::AbstractButton)

#endif
