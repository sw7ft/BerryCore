/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_deleteactionitem_h
#define cascades_deleteactionitem_h


#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/resources/abstractactionitem.h>

namespace bb {
    namespace cascades {

        class DeleteActionItemPrivate;

       /*!  
        * @brief The DeleteActionItem is used to specify that an action is a "destructive" action.
        * Actions of this type will always be placed in the overflow menu in a fixed position.
        * According to general guidelines all destructive action such as 'delete' should
        * use this action type to ensure a consistent UI experience.
        *
        * If an image isn't specified on the DeleteAction a default delete icon will be displayed.
        * and if a title isn't specified, a default string "Delete" will be shown.
        *
        * @see Page
        *
        * @xmlonly
        * <apigrouping group="User interface/Application structure"/>
        * @endxmlonly
        *
        * @since BlackBerry 10.0.0
        */
        class BBCASCADES_EXPORT DeleteActionItem : public AbstractActionItem
        {        
            Q_OBJECT

        public:
           /*!
            * Constructs an DeleteActionItem.
            *
            * @since BlackBerry 10.0.0
            */
            explicit DeleteActionItem();

           /*!
            * The destructor of the DeleteActionItem.
            *
            * @since BlackBerry 10.0.0
            */
            virtual ~DeleteActionItem();

        private:
            Q_DECLARE_PRIVATE(DeleteActionItem)
            Q_DISABLE_COPY(DeleteActionItem)

            /*! \cond PRIVATE */
            typedef DeleteActionItem ThisClass;
            typedef AbstractActionItem BaseClass;
            /*! \endcond */

        public:

           /*!
            * A builder template for constructing an DeleteActionItem. To retrieve the builder, call
            * DeleteActionItem::create().  
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
            * A builder template for constructing an DeleteActionItem. To retrieve the builder, call
            * DeleteActionItem::create().    
            *
            * @since BlackBerry 10.0.0              
            */
            class Builder : public TBuilder<Builder, DeleteActionItem>
            {
            public:
                explicit Builder() : TBuilder<Builder, DeleteActionItem>(new DeleteActionItem()) {}
            };

           /*! Creates and returns a builder for constructing an DeleteActionItem.
            *
            * Using the builder to create an DeleteActionItem:
            * @code
            * DeleteActionItem* actionItem = DeleteActionItem::create();            
            * @endcode
            *
            * @return A builder used for constructing a DeleteActionItem.
            *
            * @since BlackBerry 10.0.0
            */
            static Builder create() {
                return Builder();
            } 
        };
    } // namespace Cascades
}


QML_DECLARE_TYPE(bb::cascades::DeleteActionItem)


#endif  // cascades_deleteactionitem_h
