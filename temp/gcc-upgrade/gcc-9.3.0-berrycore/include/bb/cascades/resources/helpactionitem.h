/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_helpactionitem_h
#define cascades_helpactionitem_h


#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/resources/abstractactionitem.h>

namespace bb {
    namespace cascades {

        class HelpActionItemPrivate;

       /*!  
        * @brief A Help action to add to a @c Menu.
        * 
        * The @c HelpActionItem is used with a @c %Menu to display an action that gives
        * the user access to help functionality.
        * An application should respond to this action's @c triggered() signal by displaying
        * a help screen.
        *
        * If an image isn't specified on the @c %HelpActionItem, a default help icon will be displayed.
        * If a title isn't specified, a default string of "Help" will be shown.
        * 
        * 
        * @see Menu
        *
        * @xmlonly
        * <apigrouping group="User interface/Application structure"/>
        * @endxmlonly
        *
        * @since BlackBerry 10.0.0
        */
        class BBCASCADES_EXPORT HelpActionItem : public AbstractActionItem
        {        
            Q_OBJECT

        public:
           /*!
            * @brief Constructs a @c HelpActionItem.
            *
            * @since BlackBerry 10.0.0
            */
            explicit HelpActionItem();

           /*!
            * @brief The destructor of the @c HelpActionItem.
            *
            * @since BlackBerry 10.0.0
            */
            virtual ~HelpActionItem();

        private:
            Q_DECLARE_PRIVATE(HelpActionItem)
            Q_DISABLE_COPY(HelpActionItem)

            /*! \cond PRIVATE */
            typedef HelpActionItem ThisClass;
            typedef AbstractActionItem BaseClass;
            /*! \endcond */

        public:

           /*!
            * @brief A builder template for constructing a @c HelpActionItem.
            * 
            * To retrieve the builder, call @c HelpActionItem::create(). 
            * 
            * 
            *
            * @since BlackBerry 10.0.0
            */
            template <typename BuilderType, typename BuiltType>
            class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType>
            {
            protected:
                TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node) {}
            public:
            };

           /*!
            * @brief A builder template for constructing a @c HelpActionItem.
            * 
            * To retrieve the builder, call @c HelpActionItem::create().
            *
            * @since BlackBerry 10.0.0
            */
            class Builder : public TBuilder<Builder, HelpActionItem>
            {
            public:
                explicit Builder() : TBuilder<Builder, HelpActionItem>(new HelpActionItem()) {}
            };

           /*! 
            * @brief Creates and returns a builder for constructing a @c HelpActionItem.
            *
            * Using the builder to create a @c %HelpActionItem:
            * @code
            * HelpActionItem* actionItem = HelpActionItem::create();
            * @endcode
            *
            *
            * @return A builder used for constructing a @c HelpActionItem.
            *
            * @since BlackBerry 10.0.0
            */
            static Builder create() {
                return Builder();
            } 
        };
    } // namespace Cascades
}


QML_DECLARE_TYPE(bb::cascades::HelpActionItem)


#endif  // cascades_helpactionitem_h
