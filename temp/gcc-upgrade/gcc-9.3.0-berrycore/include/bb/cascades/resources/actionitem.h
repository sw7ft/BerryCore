/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_actionitem_h
#define cascades_actionitem_h


#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/resources/abstractactionitem.h>

namespace bb {
    namespace cascades {

        class ActionItemPrivate;

       /*!  
        * @brief Represents an action that can be invoked on a page.
        *
        * Action items can be added to        
        * a page to be displayed on a toolbar (the action bar) that is positioned at the bottom
        * of the screen. To specify that an action should appear on the action bar, rather than in the overflow
        * menu the attached property ActionBar.placement can be used.
        *
        * For an email application typical actions might be "write", "forward" or "reply".
        * @image html actionlist.png
        *
        * Here's how to create an @c %ActionItem and add it to the action bar on a @c Page. 
        * The action item has a title and an image, and it's created using the builder pattern.
        * @code
        * ActionItem* aItem = ActionItem::create()
        *    .title("myActionTitle")
        *    .image(Image("asset:///myImage.png"));
        *
        * Page* myPage = Page::create();
        * myPage->addAction(actionItem, ActionBarPlacement::OnBar);
        * @endcode
        *
        * Here's another example of creating an @c %ActionItem, this time by calling the constructor
        * and setting the properties individually.
        * @code
        * QString actionTitleText = "myActionTitle";
        * ActionItem* aItem = new ActionItem();
        * aItem->setTitle(actionTitleText);
        * aItem->setImage(Image("asset:///myImage.png"));
        *
        * Page* myPage = Page::create();
        * myPage->addAction(actionItem, ActionBarPlacement::OnBar);
        * @endcode
        *
        * And here's how to create an action item for a @c %Page using QML:
        * @code
        * Page {
        *     actions: [
        *         ActionItem {
        *             id: action1
        *             title: "myActionTitle"
        *             imageSource: "asset:///myImageName"
        *             ActionBar.placement: ActionBarPlacement.OnBar
        *         }
        *     ]
        * }
        * @endcode
        *
        * If you want to use an image for your action item, there are
        * some guidelines for how large the image should be and how much
        * padding you should use around it. The actual action item image size should be
        * 81x81 pixels, but for the best visual appearance it's recommended
        * that you create a smaller icon in the middle of the image that's 57x57 pixels.
        *
        * These images show the behavior of actionitem icon colorization.
        * -The "Dashboard" tab is using the white default icon and adopts to theme, but the tab is selected and therefore colored with the system primary color (blue)
        * -The "Controls" tab is using the white default icon and adopts to theme.
        * -The "More controls" tab is using a colored icon where the .amd @c type property is set to @c normal and left uncolorized by the system.
        * @image html actionitem_colorization_dark.png
        * @image html actionitem_colorization_bright.png
        *
        * These are the assets used (without dropshadows):
        * @image html actionitem_default_icon.png
        * @image html actionitem_colored_icon.png
        *
        * @see Page
        *
        * As of 10.3, the default behavior for action item images is to adopt the colors of the current theme.
        * To allow your images to adapt to changes in the theme, the image asset should be a grayscale image (preferably white)
        * with the alpha channel set. You can turn off this behavior by using the type "normal" in the image's .amd file.
        *
        * @image html actionitem_image.png
        *
        * @see Image (Image colorization)
        *
        * @xmlonly
        * <apigrouping group="User interface/Application structure"/>
        * @endxmlonly
        *
        * @since BlackBerry 10.0.0
        */
        class BBCASCADES_EXPORT ActionItem : public AbstractActionItem
        {        
            Q_OBJECT


        public:
           /*!
            * @brief Constructs an @c %ActionItem.
            *
            * @since BlackBerry 10.0.0
            */
            explicit ActionItem();

           /*!
            * @brief The destructor of the @c %ActionItem.
            *
            * @since BlackBerry 10.0.0
            */
            virtual ~ActionItem();

        Q_SIGNALS:


        private:
            Q_DECLARE_PRIVATE(ActionItem)
            Q_DISABLE_COPY(ActionItem)

            /*! \cond PRIVATE */
            typedef ActionItem ThisClass;
            typedef AbstractActionItem BaseClass;
            /*! \endcond */

        public:

           /*!
            * @brief A builder template for constructing an @c ActionItem.
            *
            * To retrieve the builder, call ActionItem::create().     
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
            * @brief A builder template for constructing an @c ActionItem.
            *
            * To retrieve the builder, call @c ActionItem::create().     
            *
            * @since BlackBerry 10.0.0            
            */
            class Builder : public TBuilder<Builder, ActionItem>
            {
            public:
                explicit Builder() : TBuilder<Builder, ActionItem>(new ActionItem()) {}
            };

           /*! 
            * @brief Creates and returns a builder for constructing an @c %ActionItem.
            *
            * Using the builder to create an @c %ActionItem:
            * @code
            * ActionItem* actionItem = ActionItem::create();            
            * @endcode
            *
            * @return A builder used for constructing an @c %ActionItem.
            *
            * @since BlackBerry 10.0.0
            */
            static Builder create() {
                return Builder();
            } 
        };
    } // namespace Cascades
}


QML_DECLARE_TYPE(bb::cascades::ActionItem)


#endif  // cascades_actionitem_h
