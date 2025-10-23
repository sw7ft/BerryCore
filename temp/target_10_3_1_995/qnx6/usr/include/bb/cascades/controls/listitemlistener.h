/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_listitemlistener_h
#define cascades_listitemlistener_h

#include <QtCore/QString>

#include <bb/cascades/bbcascades_global.h>


namespace bb {
namespace cascades {

    /*!
     *
     * @brief An optional interface for VisualNodes used as items in a ListView.
     *
     * The functions in this interface are called by @c %ListView in order
     * to visualize different item states. The interface contains three functions
     * that you can override if you want to customize the behavior that occurs
     * when they're invoked: @c select() is called whenever a visible list item is selected,
     * @c activate() is called when an already visible item becomes activated, and @c reset()
     * is called when a list item is about to be shown.
     *
     * A @c %ListView only calls the functions if the object implementing this interface
     * is the root node in an item visual. For example, if the implemented object is placed
     * as a child to a @c Container in the item visual, the @c %ListView won't call any functions on it.
     *
     * Here's a declaration for a class called @c MyItemClass that implements
     * @c %ListItemListener. In addition to overriding the member functions of @c %ListItemListener,
     * an additional function called @c updateItem() is declared.
     *
     * @code
     * class MyItemClass: public bb::cascades::CustomControl, public ListItemListener
     * {
     * Q_OBJECT
     *
     * public:
     *     MyItemClass(Container *parent=0);
     *
     *     void updateItem(const QString text, const QString imagePath);
     *
     *     void select(bool select);
     *
     *     void reset(bool selected, bool activated);
     *
     *     void activate(bool activate);
     *
     * private:
     *     ImageView *mItemImage;
     *     Label *mItemLabel;
     *     Container *mHighlighContainer;
     * };     
     * @endcode
     *
     * In the constructor for @c MyItemClass, a @c VisualNode object is created representing
     * the list item. It contains an image and a label as well as an overlay that is used to show
     * when an item is highlighted.
     *
     * @code
     * MyItemClass::MyItemClass(Container *parent) :
     *         CustomControl(parent)
     * {
     *     // Dock layout with margins inside.
     *     Container *itemContainer = new Container();
     *     DockLayout *itemLayout = new DockLayout();
     *     itemContainer->setLayout(itemLayout);
     *
     *     // A background Container that will hold the item content Container.
     *     Container *backgroundContainer = new Container();
     *     DockLayout *backgroundLayout = new DockLayout();
     *     backgroundContainer->setLayout(backgroundLayout);
     *     backgroundContainer->setHorizontalAlignment(HorizontalAlignment::Center);
     *
     *     // A Colored Container will be used to show if an item is highlighted.
     *     mHighlighContainer = new Container();
     *     mHighlighContainer->setBackground(Color::fromARGB(0xff75b5d3));
     *     mHighlighContainer->setHorizontalAlignment(HorizontalAlignment::Center);
     *     mHighlighContainer->setOpacity(0.0);
     *     mHighlighContainer->setPreferredWidth(760.0f);
     *     mHighlighContainer->setPreferredHeight(168.0f);
     *
     *     // Content Container, Image + text with padding to get alignment on background image.
     *     Container *contentContainer = new Container();
     *     StackLayout *contentLayout = new StackLayout();
     *     contentLayout->setOrientation(LayoutOrientation::LeftToRight);
     *     contentContainer->setLayout(contentLayout);
     *
     *     // The list item image, docked to the top, the actual image is set in updateItem.
     *     mItemImage =
     *             ImageView::create("").preferredSize(250.0f, 168.0f).layoutProperties(
     *                     StackLayoutProperties::create().vertical(VerticalAlignment::Top));
     *
     *     // A list item label, docked to the center, the text is set in updateItem.
     *     mItemLabel = Label::create().text(" ").layoutProperties(
     *     StackLayoutProperties::create().vertical(VerticalAlignment::Center));
     *     mItemLabel->textStyle()->setBase(SystemDefaults::TextStyles::titleText());
     *    
     *     // Add the Image and Label to the content.
     *     contentContainer->add(mItemImage);
     *     contentContainer->add(mItemLabel);
     *
     *     // Add the content to the full item container.
     *     backgroundContainer->add(mHighlighContainer);
     *     backgroundContainer->add(contentContainer);
     *
     *     // Finally add the background Container to the item Container.
     *     itemContainer->add(backgroundContainer);
     *
     *     setRoot(itemContainer);
     * }
     * @endcode
     *
     * When the application invokes @c updateItem(), the label and the image are updated
     * with new data from the data model. Each of the @c %select(), @c %reset(), and @c %activate()
     * functions are overridden to provide custom functionality when they're
     * invoked.
     *
     * @code
     * void MyItemClass::updateItem(const QString text, const QString imagePath)
     * {
     *     // Update image and text for the current item.
     *     mItemImage->setImage(Image(imagePath));
     *     mItemLabel->setText(text);
     * }
     *
     * void MyItemClass::select(bool select)
     * {
     *     // When an item is selected show the colored highlight Container
     *     if(select) {
     *         mHighlighContainer->setOpacity(0.9f);
     *     } else {
     *         mHighlighContainer->setOpacity(0.0f);
     *     }
     * }
     *
     * void MyItemClass::reset(bool selected, bool activated)
     * {
     *     Q_UNUSED(activated);
     *
     *     // Since items are recycled the reset function is where we have
     *     // to make sure that item state, defined by the arguments, is correct.
     *     select(selected);
     * }
     *
     * void MyItemClass::activate(bool activate)
     * {
     *     // There is no special activate state, select and activated looks the same.
     *     select(activate);
     * }
     * @endcode
     *
     * @xmlonly
     * <apigrouping group="User interface/List"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT ListItemListener {

    public:
        
        virtual ~ListItemListener();

        /*!
         * @brief Called by ListView when an already visible item becomes selected.
         *
         * When updating the visuals for the item, animations may be used.
         *
         * @param select @c true if the item has been selected, @c false if deselected
         *
         * @since BlackBerry 10.0.0
         */
        virtual void select(bool select) = 0;

        /*!
         * @brief Called by ListView when an already visible item is active.
         *
         * A list item is "active" while a user is actively pressing the list item
         * or when the item is target for a context menu operation.
         * Once released, or when no longer a context menu target, the item is no
         * longer active. With a @c StandardListItem, the active visual will have a
         * outline around the item border.
         *
         * When updating the visuals for the item, animations may be used.
         *
         * @param activate @c true if the item is active, @c false if deactivated
         *
         * @since BlackBerry 10.0.0
         */
        virtual void activate(bool activate) = 0;

        /*!
         * @brief Called by ListView when an item is about to be shown.
         *
         * When updating the visuals for the item, animations may NOT be used.
         * 
         * @param selected @c true if the item should appear selected, @c false if deselected
         * @param activated @c true if the item should appear active, @c false if deactivated
         *
         * @since BlackBerry 10.0.0
         */
        virtual void reset(bool selected, bool activated) = 0;


    protected:
        ListItemListener();

    };
}
}


#endif	// cascades_listitemlistener_h

