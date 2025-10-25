/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_navigationpaneproperties_h
#define cascades_navigationpaneproperties_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/resources/paneproperties.h>

namespace bb {
    namespace cascades {

    class NavigationPanePropertiesPrivate;
    class ActionItem;
    

   /*!  
    * @brief A class to specify properties on a child pane of a @c NavigationPane.
    * 
    * Even if it's possible to specify a @c %NavigationPaneProperties on any @c AbstractPane,
    * it's ignored unless the parent is a @c NavigationPane.
    * 
    * The @c ActionItem property can be used to customize the appearance and/or behavior of the back button.
    * The image and title properties of the @c ActionItem are shown on the back button. To change the
    * behavior of the Back button the @c triggered() signal can be connected to a slot to a custom slot that
    * modifies the behavior.
    *
    * If a custom Back button is used, a slot that calls the @c pop() function must be connected to the @c triggered()
    * signal since that will no longer be done automatically.
    *
    * C++ implementation:
    *
    * @code
    * ActionItem* backAction = ActionItem::create().title("First page").imageSource(QUrl("back.png"));
    *
    * NavigationPane* navigationPane = NavigationPane::create()
    *     .add(Page::create()
    *         .content(Label::create("First page")))
    *     .add(Page::create()
    *         .content(Label::create("Second page"))
    *         .paneProperties(NavigationPaneProperties::create()
    *             .backButton(backAction)));
    *
    * QObject::connect(navigationPane, SIGNAL(popTransitionEnded(bb::cascades::Page*)),
    *         this, SLOT(popFinished(bb::cascades::Page*)));
    * QObject::connect(backAction, SIGNAL(triggered()), navigationPane, SLOT(pop()));
    *
    * void popFinished(bb::cascades::Page* page)
    * {
    *     delete page;
    * }
    * @endcode
    *
    * QML implementation:
    *
    * @code
    * NavigationPane {
    *     id: navigationPane
    *     Page {
    *         Container {
    *             Button {
    *                 id: button
    *                 text: "Navigate"
    *                 onClicked: {
    *                     var page = pageDef.createObject();
    *                     navigationPane.push(page);
    *                 }
    *             }
    *         }
    *     }
    *     attachedObjects: [
    *         ComponentDefinition {
    *             id: pageDef
    *             Page {
    *                 id: secondPage
    *                 Label {
    *                     text: "Second page"
    *                 }
    *                 paneProperties: NavigationPaneProperties {
    *                     backButton: ActionItem {
    *                         title: "First page"
    *                         imageSource: "back.png"
    *                         onTriggered: {
    *                             navigationPane.pop();
    *                         }
    *                     }
    *                 }
    *             }
    *         }
    *     ]
    *     onPopTransitionEnded: {
    *         page.destroy();
    *         button.text = "Page destroyed"
    *     }
    * }
    * @endcode
    *
    * @xmlonly
    * <qml>
    * <class register="yes"/>
    * </qml>
    * <apigrouping group="User interface/Application structure"/>
    * @endxmlonly
    *
    * @since BlackBerry 10.0.0
    */
    class BBCASCADES_EXPORT NavigationPaneProperties : public PaneProperties
    {
        Q_OBJECT
        
       /*!
        * @brief The back button for this @c %NavigationPaneProperties.
        * 
        * If no back button is specified, the back button will get a default image and 
        * the displayed text will be the title of the previous pane. The default back 
        * button will pop the current pane when it is clicked. When a back button
        * has been explicitly set for a pane, the @c pop() function on the 
        * navigation pane needs to be called in the triggered callback from the back button
        * @c ActionItem.
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(bb::cascades::ActionItem* backButton READ backButton WRITE setBackButton
                   RESET resetBackButton NOTIFY backButtonChanged FINAL)
                   
    public:

       /*!
        * @brief Constructs a @c %NavigationPaneProperties.        
        *
        * @since BlackBerry 10.0.0
        */
        explicit NavigationPaneProperties();
        
       /*!
        * @brief Destroys this @c %NavigationPaneProperties.
        *
        * @since BlackBerry 10.0.0
        */
        virtual ~NavigationPaneProperties();
        
       /*!
        * @brief Sets the back button for this @c %NavigationPaneProperties.
        * 
        * The @c %NavigationPaneProperties takes the ownership of the back button.
        * 
        * If set to @c 0, the default back button is used.
        * 
        * When this function completes, the @c backButtonChanged() signal is emitted.
        *
        * @param backButton The back button to be displayed.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void setBackButton(bb::cascades::ActionItem* backButton);

       /*!
        * @brief Resets the back button for this @c %NavigationPaneProperties.
        * 
        * This function resets the back button to a default back button for this pane.
        * When this function completes, the @c backButtonChanged() signal is emitted.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void resetBackButton();

       /*!
        * @brief Gets the back button for this @c %NavigationPaneProperties.
        *
        * The @c %NavigationPaneProperties keeps the ownership of the back button.
        *
        * @return The back button, or @c 0 if no back button has been specified.
        *
        * @since BlackBerry 10.0.0
        */
        bb::cascades::ActionItem* backButton() const;
        
Q_SIGNALS:

       /*!
        * @brief Emitted when the back button has changed.
        *
        * @param backButton The new back button.
        *
        * @since BlackBerry 10.0.0
        */
        void backButtonChanged(bb::cascades::ActionItem* backButton);
        
    private:
        
        /*! \cond PRIVATE */
        Q_DECLARE_PRIVATE(NavigationPaneProperties)
        Q_DISABLE_COPY(NavigationPaneProperties)

    public:
        typedef NavigationPaneProperties ThisClass;
        typedef PaneProperties BaseClass;
        /*! @endcond */
        
       /*!         
        * @brief A template builder class for constructing a @c %NavigationPaneProperties object.
        * 
        * To retrieve the builder, call @c NavigationPaneProperties::create().
        *
        * @since BlackBerry 10.0.0
        */
        template <typename BuilderType, typename BuiltType>
        class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType> {
        protected:
            TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node) {
            }

        public:

           /*!
            * @brief Sets the back button for this @c %NavigationPaneProperties.
            *  
            * If set to @c 0, the default back button is used.
            *
            * Using this convenience function in the builder pattern is equivalent to the
            * following:
            * 
            * @code
            * myPaneProperties->setBackButton(myBackButton);
            *  @endcode
            * 
            * When this function completes, the @c backButtonChanged() signal is emitted.
            * 
            * @param backButton The back button to be displayed.
            *
            * @since BlackBerry 10.0.0
            */
            BuilderType& backButton(bb::cascades::ActionItem* backButton) {
                this->instance().setBackButton(backButton);
                return this->builder();
            }

        };

       /*!        
        * @brief A builder class for constructing a @c %NavigationPaneProperties object.
        * 
        * To retrieve the builder, call @c NavigationPaneProperties::create().
        *
        * @since BlackBerry 10.0.0
        */
        class Builder : public TBuilder<Builder, NavigationPaneProperties>
        {
        public:
            explicit Builder() : TBuilder<Builder, NavigationPaneProperties>(new NavigationPaneProperties()) {}
        };

        /*!
        * @brief Creates and returns a builder for constructing a @c %NavigationPaneProperties object.
        *
        * Using the builder to create a @c %NavigationPaneProperties object.
        * 
        * @code
        * NavigationPaneProperties* myPaneProperties = NavigationPaneProperties::create()
        *                                               .backButton(myActionItem);
        * @endcode
        *
        * @return A builder used for constructing a @c %NavigationPaneProperties object.
         *
         * @since BlackBerry 10.0.0
        */
        static Builder create() {
            return Builder();
        }
    };
    }

}

QML_DECLARE_TYPE(bb::cascades::NavigationPaneProperties)

#endif //cascades_navigationpaneproperties_h
