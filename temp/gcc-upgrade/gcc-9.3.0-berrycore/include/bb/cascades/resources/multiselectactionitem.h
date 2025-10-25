/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_multiselectactionitem_h
#define cascades_multiselectactionitem_h


#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/resources/abstractactionitem.h>
#include <bb/cascades/resources/multiselecthandler.h>

namespace bb {
    namespace cascades {

        class MultiSelectActionItemPrivate;

       /*!  
        * @brief The multi-select action is used to start a multiple selection session.
        *
        * The multi-select action can, for example, be placed inside the Context Menu or the
        * Action Menu. According to general guidelines this action should be used to 
        * activate a MultiSelectHandler session for multi-selecting in the UI.
        *
        * For convenience, it is possible to set a global multi-select on ListView
        * which will shown in each of its list items.
        * @see ListView.multiSelectAction for setting a global multi-select action.
        * 
        * If the image isn't specified on the multi-select action a default icon will be 
        * displayed, and if the title isn't specified, the default string "Select more" will  
        * be shown.
        *
        * @code
        * ListView {
        *     multiSelectAction: MultiSelectActionItem {
        *         // This MultiSelectHAndler will be set 
        *         // to active when this item gets triggered.
        *         multiSelectHandler: theMultiSelectHandler
        *     }
        * }
        * @endcode
        *
        * @see ActionSet for how to show this action inside the Context Menu and Page for 
        * how to show this inside the Action Menu.
        *
        * @xmlonly
        * <apigrouping group="User interface/Application structure"/>
        * @endxmlonly
        *
        * @since BlackBerry 10.0.0
        */
        class BBCASCADES_EXPORT MultiSelectActionItem : public AbstractActionItem
        {        
            Q_OBJECT
            
            /*!
             * @brief The multi-select handler to be activated when this action is triggered.
             * 
             * If set, this the multi-select handler will be activated when the user selects
             * this action. This is for convenience and is equivalent of manually activating
             * the multi-select handler from the triggered signal.
             *
             * The default value is @c 0, indicating no handler is set.                        
             *
             * @since BlackBerry 10.0.0
             */
            Q_PROPERTY(bb::cascades::MultiSelectHandler* multiSelectHandler 
                       READ multiSelectHandler 
                       WRITE setMultiSelectHandler 
                       RESET resetMultiSelectHandler 
                       NOTIFY multiSelectHandlerChanged 
                       FINAL)
        public:
           /*!
            * @brief Constructs an MultiSelectActionItem.
            *
            * @since BlackBerry 10.0.0
            */
            MultiSelectActionItem();

           /*!
            * @brief The destructor of the MultiSelectActionItem.
            *
            * @since BlackBerry 10.0.0
            */
            virtual ~MultiSelectActionItem();

           /*!
            * @brief Returns the multi-select handler set in this action.
            *
            * @return The multi-select handler or @c 0 if it is not set.
            *
            * @since BlackBerry 10.0.0
            */
            MultiSelectHandler* multiSelectHandler() const;

           /*!
            * @brief Sets the multi-select handler to be activated by this action.
            *
            * The ownership is not transferred, so handlers can be shared. It is the
            * responsibility of the caller to make sure that the handler is not destroyed
            * while this action has a reference to it.
            *
            * @param multiSelectHandler The multi-select handler to set. If @c 0 
            *        nothing will happen. The ownership is not transferred.
            *
            * @since BlackBerry 10.0.0
            */
            Q_SLOT void setMultiSelectHandler(bb::cascades::MultiSelectHandler* multiSelectHandler);

           /*!
            * @brief Resets the multi-select handler to @c 0.
            *
            * This means no multi-selection handler will be set in this action.
            *
            * @since BlackBerry 10.0.0
            */
            Q_SLOT void resetMultiSelectHandler();
            
            
        Q_SIGNALS:        

           /*!
            * @brief Emitted when the multi-select handler has been set or reset.
            *
            * @param multiSelectHandler The new multi-select action or @c 0 if it is not set anymore.
            *
            * @since BlackBerry 10.0.0
            */
            void multiSelectHandlerChanged(bb::cascades::MultiSelectHandler *multiSelectHandler);

        private:
            Q_DECLARE_PRIVATE(MultiSelectActionItem)
            Q_DISABLE_COPY(MultiSelectActionItem)

            /*! \cond PRIVATE */
            typedef MultiSelectActionItem ThisClass;
            typedef AbstractActionItem BaseClass;
            /*! \endcond */

        public:

           /*!
            * @brief A builder template for constructing a %MultiSelectActionItem. 
            *
            * To retrieve the builder, call MultiSelectActionItem::create().      
            *
            * @since BlackBerry 10.0.0
            */
            template <typename BuilderType, typename BuiltType>
            class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType>
            {
            protected:
                TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node) {}
            public:
            
               /*!
                * @brief Sets the multi-select handler to be activated by this action.
                *
                * The ownership is not transferred, so handlers can be shared. It is the
                * responsibility of the caller to make sure that the handler is not destroyed
                * while this action has a reference to it.
                *
                * Using this convenience function in the builder pattern is the equivalent of the
                * following:
                * @code
                * myMultiSelectAction->setMultiSelectHandler(handler);
                * @endcode
                *
                * @param handler The multi-select handler to set. If @c 0 
                *        nothing will happen. The ownership is not transferred.
                *
                * @since BlackBerry 10.0.0
                */
                BuilderType& handler(MultiSelectHandler* handler)
                {
                    this->instance().setMultiSelectHandler(handler);
                    return this->builder();
                }
            };

           /*!
            * @brief A builder template for constructing a %MultiSelectActionItem. 
            * 
            * To retrieve the builder, call MultiSelectActionItem::create().    
            *
            * @since BlackBerry 10.0.0            
            */
            class Builder : public TBuilder<Builder, MultiSelectActionItem>
            {
            public:
                explicit Builder() : TBuilder<Builder, MultiSelectActionItem>(new MultiSelectActionItem()) {}
            };

           /*! 
            * @brief Creates and returns a builder for constructing a %MultiSelectActionItem.
            *
            * Using the builder to create a %MultiSelectActionItem:
            * @code
            * MultiSelectActionItem* multiSelectAction = MultiSelectActionItem::create();            
            * @endcode
            *
            * @return A builder used for constructing a MultiSelectActionItem.
            *
            * @since BlackBerry 10.0.0
            */
            static Builder create() {
                return Builder();
            } 
        };
    } // namespace Cascades
}


QML_DECLARE_TYPE(bb::cascades::MultiSelectActionItem)


#endif	// cascades_multiselectactionitem_h
