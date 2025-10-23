/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_settingsactionitem_h
#define cascades_settingsactionitem_h


#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/resources/abstractactionitem.h>

namespace bb {
    namespace cascades {

        class SettingsActionItemPrivate;

       /*!  
        * @brief A Settings action to add to a @c Menu.
        * 
        * The @c SettingsActionItem is used with the @c %Menu to display an action that gives
        * the user access to the application settings.
        * The application should respond to the @c triggered() signal to display the application's help
        * screen.
        *
        * If an image isn't specified on the @c %SettingsActionItem, a default settings icon will be
        * displayed. If a title isn't specified, a default string of "Settings" will be shown.
        *
        * @see Menu
        *
        * @xmlonly
        * <apigrouping group="User interface/Application structure"/>
        * @endxmlonly
        *
        * @since BlackBerry 10.0.0
        */
        class BBCASCADES_EXPORT SettingsActionItem : public AbstractActionItem
        {        
            Q_OBJECT

        public:
           /*!
            * @brief Constructs a @c SettingsActionItem.
            *
            * @since BlackBerry 10.0.0
            */
            explicit SettingsActionItem();

           /*!
            * @brief The destructor of the @c SettingsActionItem.
            *
            * @since BlackBerry 10.0.0
            */
            virtual ~SettingsActionItem();

        private:
            Q_DECLARE_PRIVATE(SettingsActionItem)
            Q_DISABLE_COPY(SettingsActionItem)

            /*! \cond PRIVATE */
            typedef SettingsActionItem ThisClass;
            typedef AbstractActionItem BaseClass;
            /*! \endcond */

        public:

           /*!
            * @brief A builder template for constructing a @c SettingsActionItem.
            * 
            * To retrieve the builder, call @c SettingsActionItem::create().
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
            * @brief A builder template for constructing a @c SettingsActionItem.
            * 
            * To retrieve the builder, call @c SettingsActionItem::create(). 
            *
            * @since BlackBerry 10.0.0            
            */
            class Builder : public TBuilder<Builder, SettingsActionItem>
            {
            public:
                explicit Builder() : TBuilder<Builder, SettingsActionItem>(new SettingsActionItem()) {}
            };

           /*! 
            * @brief Creates and returns a builder for constructing a @c SettingsActionItem.
            *
            * Using the builder to create a @c %SettingsActionItem:
            * @code
            * SettingsActionItem* actionItem = SettingsActionItem::create();
            * @endcode
            *
            * @return A builder used for constructing a @c %SettingsActionItem.
            *
            * @since BlackBerry 10.0.0
            */
            static Builder create() {
                return Builder();
            } 
        };
    } // namespace Cascades
}


QML_DECLARE_TYPE(bb::cascades::SettingsActionItem)


#endif  // cascades_settingsactionitem_h
