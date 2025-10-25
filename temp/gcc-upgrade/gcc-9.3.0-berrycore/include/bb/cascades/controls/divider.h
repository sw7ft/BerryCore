/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_divider_h
#define cascades_divider_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/controls/control.h>

namespace bb {
    namespace cascades {
    
    class DividerPrivate;
    class Container;

    /*!
     * 
     * @brief A horizontal divider.
     *
     * @image html divider.png This is how you can use a divider.
     *
     * The divider is typically used when there is a desire to visually "divide" items 
     * within a container or list.
     *
     * The size of the divider behaves as follows:
     * - By default, the width of the control is adjusted automatically to fill its parent container.
     * - The width is adjustable using the @c Control::preferredWidth, @c Control::minWidth and @c Control::maxWidth properties.
     * - The height is fixed, so the properties @c Control::preferredHeight, @c Control::minHeight and 
     * @c Control::maxHeight are not used.
     *
     * @xmlonly
     * <apigrouping group="User interface/Core controls"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT Divider : public Control
    {
    private:
        Q_OBJECT
    public:
        /*!
         * @brief Constructs a horizontal divider.
         *
         * The passed in parent (if any) becomes the owner of created divider.
         * If the parent is 0 or is not specified, this list divider will not have an owner.
         *
         * @param parent The parent container that will be the owner of this list divider.
         *
         * @since BlackBerry 10.0.0
         */
        explicit Divider(Container * parent = 0);

        /*!
         * @brief Destructs this list divider.
         *
         * @since BlackBerry 10.0.0
         */
        virtual ~Divider();

    private:
        Q_DECLARE_PRIVATE(Divider)
        Q_DISABLE_COPY(Divider)

    public:

        typedef Divider ThisClass;
        typedef Control BaseClass;

        /*!
         * @brief A builder template for constructing a Divider.
         *
         * See Divider::create() for getting a concrete Builder for constructing
         *      a Divider.
         *
         * @since BlackBerry 10.0.0
         */
        template <typename BuilderType, typename BuiltType>
        class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType>
        {
        protected:
            explicit TBuilder(BuiltType* node) :
            BaseClass::TBuilder<BuilderType, BuiltType>(node)
            { }
        };

        /*!
         * @brief A Builder class for constructing a Divider.
         *
         * @since BlackBerry 10.0.0
         */
        class Builder : public TBuilder<Builder, Divider>
        {
        public:
            Builder() : TBuilder<Builder, Divider>(new Divider())
            { }
        };

        /*!
         * @brief Creates a Divider and wraps it into a builder that
         * allows for "builder pattern" initialization:
         *
         * \code
         *     Divider::create();
         * \endcode
         * \return A builder for Divider.
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

QML_DECLARE_TYPE(bb::cascades::Divider)


#endif	// cascades_divider_h

