/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_listview_h
#define cascades_listview_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

#include <bb/cascades/controls/control.h>
#include <bb/cascades/databinding/datamodel.h>
#include <bb/cascades/controls/listitemprovider.h>
#include <bb/cascades/controls/listitemtypemapper.h>
#include <bb/cascades/controls/snapmode.h>
#include <bb/cascades/controls/flickmode.h>
#include <bb/cascades/controls/listviewsticktoedgepolicy.h>
#include <bb/cascades/controls/scrollposition.h>
#include <bb/cascades/controls/scrollindicatormode.h>
#include <bb/cascades/core/visualnode.h>
#include <bb/cascades/layouts/listlayout.h>
#include <bb/cascades/resources/scrollanimation.h>
#include <bb/cascades/resources/scrollrole.h>

namespace bb {
    namespace cascades {
    class Container;
    class ListViewPrivate;
    class MultiSelectHandler;
    class MultiSelectActionItem;
    class RearrangeHandler;

    /*!
     * @brief A scrollable container used to display a list of items.
     *
     * @image html listview_sorted.png A list of names sorted by the first letter
     *
     * The implementation of a @c ListView follows an MVC (model-view-controller)
     * architecture, with the @c %ListView representing the controller. It
     * accepts input from the user (such as item selections or scrolling) and instructs the model
     * and view to perform actions based on that input. The model for a @c %ListView is provided
     * by the @c DataModel, and is a requirement for every @c %ListView. The view for a @c %ListView
     * can be handled a few different ways, and the implementation is different whether you're using
     * C++ or QML. If you're using C++, the visuals are managed by @c ListItemProvider. If you're
     * using QML, you'll likely use @c ListItemComponent (though it's also possible to use @c %ListItemProvider).
     *
     * A @c %ListView must have a @c %DataModel connected to it in order to show any list items.
     * The @c %DataModel is used to provide data for each item, which can be displayed in the view.
     * The @c %DataModel can contain items in a tree structure many
     * levels deep, but @c %ListView only shows items from the first two levels
     * below the root element (see #rootIndexPath).
     *
     * A @c %DataModel can come in a number of different forms, including @c XmlDataModel
     * (data from an XML file), @c QListDataModel (a @c %DataModel template that is very similar to
     * a @c QList), and @c GroupDataModel (can contain @c %QVariantMap objects and/or @c %QObject pointers).
     *
     * @c %ListView takes ownership of any @c QObject object returned (wrapped in
     * @c QVariant) by @c DataModel::data(), if the returned object doesn't already
     * have a parent, and if the user type of the @c %QVariant is @c QMetaType::QObjectStar.
     * Custom @c %QVariant types are ignored, even if the type in question inherits
     * @c %QObject. @c %QObject objects owned by @c %ListView are deleted when the item they belong
     * to is scrolled out of the visible area, or when the @c %ListView itself is deleted.
     *
     * <h2>Creating a list</h2>
     *
     * Here's how to create a simple list from an @c XmlDataModel. The XML source would be located in a file
     * called model.xml. The root index path is changed to [1] so that only the European cities
     * are displayed in the list,
     * with no header item.
     *
     * @code
     * Page {
     *     content: Container {
     *         background: Color.White
     *         ListView {
     *             rootIndexPath: [1]
     *             dataModel: XmlDataModel { source: "model.xml" }
     *         }
     *     }
     * }
     * @endcode
     *
     * @code
     * <model>
     *   <header title="North America">
     *     <item title="Toronto" />
     *     <item title="New York" />
     *   </header>
     *   <header title="Europe">
     *     <item title="Copenhagen" />
     *     <item title="Malmo" />
     *   </header>
     * </model>
     * @endcode
     *
     * <h3>List visuals in QML</h3>
     * 
     * @image html listview_qml.png A diagram demonstrating how list items are created in QML
     *
     * In QML, it's possible to define list item visuals in two ways: using @c ListItemProvider
     * or @c ListItemComponent. Because of the declarative nature of QML, using @c %ListItemComponent
     * is the preferred method.
     *
     * A @c %ListItemComponent is a QML template that's used by the @c %ListView to present
     * data from the model. A @c %ListItemComponent can be attached to a @c %ListView using
     * the @c ListView::listItemComponents property, and it can contain
     * whatever visual controls that you want to display in your list item.
     *
     * If item visuals are created from a @c %ListItemComponent,
     * @c %ListView makes the following properties available on the root element of the item
     * visual:
     *
     * - @c ListItem.initialized - States whether the item visual is initialized or not.
     * @c true when initialization of the item visual is finished (all
     * properties have been updated to reflect the current item), @c false
     * when the item visuals become disconnected due to recycling. Explicit
     * animations etc must not be started when the value of @c initialized
     * is @c false.
     *
     * - @c ListItem.data - The @c QVariant returned by DataModel::data() for this item.
     * Typically a @c QVariantMap or @c QObject* which means that @c data
     * has properties of its own (e.g. @c ListItem.data.firstName), but
     * could also be just a @c QString if that's the kind of @c %QVariant
     * the currently connected @c %DataModel returns.
     *
     * - @c ListItem.indexInSection - The index for this item amongst its siblings.
     * The siblings are those items that have the same parent as this item.
     *
     * - @c ListItem.indexPath - The index path identifying this item in its @c %DataModel.
     *
     * - @c ListItem.sectionSize - The number of child items that the parent item of this item has.
     *
     * - @c ListItem.view - The @c %ListView in which this item is visible.
     * The item is in a context separate from the @c %ListView, so any symbols
     * from the @c %ListView context that are to be accessible from items must
     * be placed as dynamic properties on the @c %ListView.
     *
     * - @c ListItem.component - The @c %ListItemComponent that this item visual has been
     * created from. The item visuals are in a context of their own, so any symbols
     * from the @c %ListItemComponent context that are to be accessible from item
     * visuals must be placed as dynamic properties on the @c %ListItemComponent.
     *
     * - @c ListItem.active - @c true if this item is active, @c false otherwise.
     * An item is typically active if the user is holding a finger on it.
     *
     * - @c ListItem.selected - @c true if this item is selected, @c false otherwise.
     * An item is typically selected if the user intends to access details
     * for the item, or to perform an action on the item.
     *
     * The @c ListItem.* symbols listed above only have values on the root element
     * in the item visuals, so they must be prefixed by the id of the root
     * element if used on any element further down in the tree. For convenience,
     * @c %ListView therefore also makes the symbol @c ListItemData available as
     * an alias for @c ListItem.data. In contrast to @c ListItem.data, @c ListItemData
     * is available in the entire context of the item visual, so no prefix is needed.
     *
     * Here's how to create a list in QML, with a @c contact list item:
     *
     * @code
     * ListView {
     *     dataModel: XmlDataModel { source: "model.xml" }
     *     listItemComponents: [
     *         ListItemComponent {
     *             type: "contact"
     *
     *             Container {
     *                 id: itemRoot
     *
     *                 ImageView {
     *                     image: ListItemData.imagePath
     *                     opacity: itemRoot.ListItem.selected ? 1.0 : 0.5
     *                 }
     *
     *                 Label { text: ListItemData.name }
     *             }
     *         }
     *     ]
     * }
     * @endcode
     *
     * @note A @c ListItemComponent has a different scope than the rest of a QML document. If you
     * create a list in QML and need to access variables placed in the @c %ListView in a @c %ListItemComponent, you can
     * access the variables using the @c %ListItem.view property. If you need to access a property that
     * is outside the scope of the @c %ListView, you need to alias the property in the @c %ListView before you can
     * access it.
     *
     * Here's how to create a list in QML and access a variable inside the @c %ListView:
     *
     * @code
     * ListView {
     *     property string myText: "Example text"
     *     dataModel: XmlDataModel {
     *         source: "model.xml"
     *     }
     *     listItemComponents: [
     *         ListItemComponent {
     *             type: "listItem"
     *             CustomListItem {
     *                 id: itemRoot
     *                 dividerVisible: true
     *                 highlightAppearance: HighlightAppearance.Frame
     *                 Container {
     *                     Label {
     *                         text: ListItemData.title + " " + itemRoot.ListItem.view.myText
     *                     }
     *                 }
     *             }
     *         }
     *     ]
     * }
     * @endcode
     *
     * <h3>List visuals in C++</h3>
     * 
     * @image html listview_cpp.png A diagram demonstrating how list items are created in C++
     *
     * A @c ListItemProvider can be assigned to the @c %ListView in order to provide
     * @c VisualNode objects to be shown as items in the @c %ListView.
     * @c ListItemProvider::updateItem() is then called whenever an item visual should be
     * updated with data for a specific item.
     *
     * The @c %VisualNode objects are recycled when scrolling in a @c %ListView. Those
     * scrolled out of the visible area are kept in an internal cache by @c %ListView,
     * in order to be connected to new data and used again when another item of the
     * same type scrolls into the visible area. Therefore, it is not possible to store
     * any states in the @c %VisualNode objects, as all item specific data must be stored
     * in the @c %DataModel.
     *
     * If the @c %VisualNode objects implement the @c ListItemListener interface, @c %ListView
     * calls @c ListItemListener::reset() on them right before they are shown.
     * @c %ListView also calls @c ListItemListener::select() and @c ListItemListener::activate()
     * whenever those visualization states should change for an already visible item.
     *
     * <h3>The default list visuals</h3>
     *
     * If no @c %ListItemProvider is assigned and no @c %ListItemComponent of a matching
     * type can be found, the default behavior for @c %ListView is to
     * use @c Header for items of the type "header" and @c StandardListItem for all other
     * types of items. This approach works great if you want just a standard list
     * without any major visual customizations. @c %Header and @c %StandardListItem
     * contain a standard set of visuals, including titles, descriptions, and images.
     *
     * In this scenario the @c %ListView tries to assign the data returned from
     * @c DataModel::data() to @c Header::title or @c StandardListItem::title.
     *
     * Here's a C++ example of a very simple @c %ListView showing three @c %StandardListItem items
     * with "Hey", "Hello" and "Bye" as title texts:
     *
     * @code
     * ListView *pListView = new ListView();
     * pListView->setDataModel(new QListDataModel<QString>
     *        (QList<QString>() << "Hey" << "Hello" << "Bye"));
     * @endcode
     *
     * @c %ListView calls @c DataModel::itemType() for each item in order to know its type.
     * In QML this can be overridden by declaring the function @c itemType(data, indexPath) on the
     * @c %ListView element. The @c %ListView then calls that function instead
     * of the @c %DataModel function.
     *
     * Here's how to create a list in QML that creates a @c %Header for all items on the top level,
     * and a @c %StandardListItem for each item below the top level:
     *
     * @code
     * ListView {
     *     dataModel: XmlDataModel { source: "model.xml" }
     *
     *     function itemType(data, indexPath) {
     *         return (indexPath.length == 1 ? 'header' : 'item');
     *     }
     * }
     * @endcode
     *
     * If no @c itemType() function has been declared in QML, @c DataModel::itemType() can
     * instead be overridden by assigning a @c ListItemTypeMapper in C++ by calling
     * setListItemTypeMapper(). The @c %ListView then calls @c ListItemTypeMapper::itemType()
     * instead of the @c %DataModel function.
     *
     * <h2>Index paths</h2>
     *
     * Index paths are used for identifying items in @c %ListView, @c %DataModel
     * and all related classes. In C++, an index path is a @c QVariantList
     * object containing a number of @c QVariant integers, one for each ancestor (including the root
     * item) of the specified item. The reason for index paths being @c QVariantList
     * objects in C++ is that @c QVariantList objects are the C++ equivalent of QML JavaScript arrays.
     *
     * In QML, an index path is simply an array containing integers.
     * For an item that is a direct child of the root item,
     * the index path contains a single integer. A child of that item would instead have
     * an index path consisting of two integers, etc.
     *
     * Examples of index paths:
     *
     * - [3] - index path for the fourth child of the root item
     * - [3,0] - index path for the first child of the fourth child of the root item
     *
     * Example of accessing indexes from index paths in C++:
     *
     * - indexPath[0].toInt() - gets the top level index from this index path
     * - indexPath[1].toInt() - gets the second level index from this index path (if the index
     * path contains that many levels)
     *
     * In the graphic below, the index path for 'A' would be [0] while the index
     * for Astaroff Krytinisz would be [0,3], if the @c rootIndexPath is [] (an empty index path,
     * i.e. the root of the @c DataModel).     
     *
     * @image html listview_hierarchy.png A list showing two levels in the hierarchy
     *
     * See [Index paths](http://developer.blackberry.com/native/documentation/cascades/ui/lists/list_view_selection.html#indexpaths) for more information.
     *
     * <h2>Multi selection</h2>
     * 
     * By default, selection is handled by the @c #multiSelectHandler. Within the @c multiSelectHandler, 
     * you can define a set of actions that are invoked when multi selection occurs. These actions are 
     * used to populate the context menu that's displayed when you long-press on a control 
     * (in this case, the list item). For example, in an application that displays a list of images, 
     * the user might want to be able to select multiple pictures and delete them. In this case, you 
     * could use the @c multiSelectHandler to populate the context menu with the number of pictures 
     * that are being selected for deletion
     *
     * <h2>Sizing</h2>
     *
     * The size of the @c %ListView behaves as follows:
     * - By default, the width and height are adjusted automatically to fill its parent container.
     * - The width is adjustable using the @c Control::preferredWidth, @c Control::minWidth and @c Control::maxWidth properties.
     * - The height is adjustable using the @c Control::preferredHeight, @c Control::minHeight and @c Control::maxHeight and properties.
     *
     * @c %ListView contains padding properties. Padding is applied to each side of the @c %ListLayout used by the @c %ListView,
     * to create space between the list and any surrounding components. These padding properties can also support negative padding values.
     *
     * @see DataModel, ListItemProvider, ListItemTypeMapper, ListItemListener, QListDataModel, GroupDataModel, XmlDataModel, ListLayout
     *
     * @xmlonly
     * <qml>
     * <class abstract="yes" />
     * </qml>
     * <apigrouping group="User interface/List"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT ListView : public Control {
        Q_OBJECT

       /*!
        * @brief The @c ListLayout for the @c %ListView.
        *
        * How a @c %ListView positions its items is determined by the type
        * of layout it has. The default layout for a @c %ListView is a @c StackListLayout, but you can also use
        * @c GridListLayout and @c FlowListLayout.
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(bb::cascades::ListLayout * layout READ layout WRITE setLayout RESET resetLayout NOTIFY layoutChanged FINAL)

        /*!
         * @brief Specifies a @c DataModel to use as source for item data in this @c %ListView.
         *
         * The default value is @c 0, which means that no items are shown.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::DataModel *dataModel READ dataModel WRITE setDataModel NOTIFY dataModelChanged FINAL)

        /*!
         * @brief Specifies a @c ListItemProvider to use as source for item visualizations
         * in this @c %ListView.
         *
         * The default value is @c 0, which means that this @c %ListView creates a
         * @c Header for items of the type "header" and a @c StandardListItem
         * for all other types of items. In that case this @c %ListView also tries
         * to assign the data returned from @c DataModel::data() to
         * @c Header::title or @c StandardListItem::title.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::ListItemProvider *listItemProvider READ listItemProvider WRITE setListItemProvider NOTIFY listItemProviderChanged FINAL)

        /*!
         * @brief Specifies which node in the connected @c DataModel this @c %ListView should
         * use as the root.
         *
         * The default value is an empty @c QVariantList, which means that the
         * root node of the @c %DataModel is used as root node by this @c %ListView.
         *
         * See [Index paths](http://developer.blackberry.com/native/documentation/cascades/ui/lists/list_view_selection.html#indexpaths) for more information.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QVariantList rootIndexPath READ rootIndexPath WRITE setRootIndexPath NOTIFY rootIndexPathChanged FINAL)

        /*!
         * @brief Specifies if and how the scroll position should snap to items in the list.
         *
         * If set to @c SnapMode::LeadingEdge, the @c %ListView makes sure that, in a top-to-bottom layout,
         * the first visible item is always aligned to the top of the @c ListView when the list is
         * not in motion (that is, when the user is not touching and dragging the list). In a bottom-to-top
         * layout, the bottom of the last visible item is aligned to the bottom of the @c %ListView, and so on.
         *
         * @image html snapping_list.png Illustration showing snapping behavior.
         *
         * The illustration shows how the user can drag the list to a point where
         * the top item is not aligned with the top of the visible area. If @c snapMode
         * is set to @c SnapMode::LeadingEdge, @c %ListView continues the scrolling after
         * the user lifts their finger, until an item is aligned with the top of the visible area.
         *
         * If the list is currently scrolled all the way to the beginning, or all the way
         * to the end, @c %ListView will not snap away from that position, regardless
         * of what snap mode is currently set on this property.
         *
         * The default value is @c SnapMode::Default, which lets the framework decide the snap mode.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::SnapMode::Type snapMode READ snapMode WRITE setSnapMode NOTIFY snapModeChanged FINAL)

        /*!
         * @brief Specifies the scroll behavior of the list in response to a flick gesture.
         *
         * The default value is @c FlickMode::Default, which lets the framework decide the flick mode.
         *
         * @see FlickMode
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::FlickMode::Type flickMode READ flickMode WRITE setFlickMode NOTIFY flickModeChanged FINAL)

        /*!
         * @brief Specifies how the list should stick to its edges when the list or 
         * its content changes size.
         *
         * Changes in the @c DataModel, changing item size, list size or padding can trigger
         * an instantaneous change in scroll position without the user interacting with the list. 
         * This property can be used to enable specific behavior in those cases when the 
         * scroll position is at the beginning or end.
         *
         * The default value is @c ListViewStickToEdgePolicy::Default, which lets the framework 
         * decide.
         *
         * @see @c ListViewStickToEdgePolicy
         *
         * @since BlackBerry 10.1.0
         */
        Q_PROPERTY(bb::cascades::ListViewStickToEdgePolicy::Type stickToEdgePolicy READ stickToEdgePolicy WRITE setStickToEdgePolicy NOTIFY stickToEdgePolicyChanged FINAL);

        /*!
         * @brief The handler used during multiple selection to populate the Context menu.
         * 
         * Activating the multi-select handler will put the @c %ListView in multiple selection
         * mode, which shows the context menu populated with the actions from this handler. 
         *
         * This is a grouped property, meaning there is always a multi-select handler
         * attached to a @c %ListView. For convenience this object has a default 
         * @c MultiSelectHandler::multiSelectAction object set on it. If this is not needed, 
         * you will need to remove or reset it manually. 
         * 
         * @code
         * ListView {
         *     id: theListView
         *
         *     // This multi-select action will be placed inside the ActionSets of each 
         *     // list item that doesn't have a MultiSelectActionItem of its own.
         *     multiSelectAction: MultiSelectActionItem {}
         *
         *     multiSelectHandler {
         *         // These actions will be shown during multiple selection, while this 
         *         // multiSelectHandler is active
         *         actions: [
         *             ActionItem {title: "Multi-select action"},
         *             DeleteActionItem {}
         *         ]
         *
         *         status: "None selected"
         *     
         *         onActiveChanged: {
         *             if (active == true) {
         *                 console.log("Multiple selection is activated");
         *             }
         *             else {
         *                 console.log("Multiple selection is deactivated");
         *             }
         *         }
         *     }
         *
         *     // Change the status text in the multiSelectHandler to show how many items
         *     // are selected
         *     onSelectionChanged: {
         *         if(selectionList().length > 1) {
         *             multiSelectHandler.status = selectionList().length + " items selected";
         *         }
         *         else if(selectionList().length == 1) {
         *             multiSelectHandler.status = "1 item selected";
         *         }
         *         else {
         *             multiSelectHandler.status = "None selected";
         *         }
         *     }
         *
         *     listItemComponents: [
         *         ListItemComponent {
         *             id: photo
         *             
         *             // These actions will be shown in the Context Menu this list item is
         *             // long-pressed
         *             contextActions: [
         *                 ActionSet {
         *                     ActionItem {title: "Single-select action"}
         *                     DeleteActionItem {}
         *                 }
         *             ]
         *         }
         *     ]
         * }
         * @endcode
         *
         * @xmlonly
         * <qml>
         * <property groupedProperty="yes"/>
         * </qml>
         * @endxmlonly
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::MultiSelectHandler* multiSelectHandler READ multiSelectHandler FINAL)

        /*!
         * @brief A global multi-select action to show in the context menu for the list items.
         * 
         * This property is mainly for convenience. Typically, when you want to show 
         * a multi-select action, you add it to an @c ActionSet on each list item.
         * But for convenience, you can use this property to add a multi-select action 
         * for all the list items.
         *
         * If a list item already has a @c %MultiSelectActionItem added to it, this property will 
         * be ignored and the one added to the item will be used.
         *
         * @warning The list item must have an @c %ActionSet in order for this multi-select action
         * to be added to it. The @c %ActionSet can be empty.
         *
         * The default value is @c 0.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::MultiSelectActionItem* multiSelectAction 
                   READ multiSelectAction 
                   WRITE setMultiSelectAction 
                   RESET resetMultiSelectAction 
                   NOTIFY multiSelectActionChanged 
                   FINAL)

        /*!
         * @brief Specifies if and how a scroll indicator should be shown.
         *
         * The default value is @c ScrollIndicatorMode::Default, which means
         * that the framework decides if and how a scroll indicator is shown.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::ScrollIndicatorMode::Type scrollIndicatorMode READ scrollIndicatorMode WRITE setScrollIndicatorMode RESET resetScrollIndicatorMode NOTIFY scrollIndicatorModeChanged FINAL)

        /*!
         * @brief An optional @c VisualNode that the @c %ListView can use as a leading visual.
         *
         * The leading visual is placed before the first item in the list and can be reached by
         * dragging towards the beginning of the list.
         *
         * The default value is @c 0.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::VisualNode* leadingVisual READ leadingVisual WRITE setLeadingVisual RESET resetLeadingVisual NOTIFY leadingVisualChanged FINAL)

        /*!
         * @brief A fraction of the @c %ListView size that determines if the @c %ListView should
         * snap back from its leading visual to its leading edge when scrolling ends.
         *
         * The leading visual snap threshold is the fraction of the @c %ListView size that determines
         * how much of the leading visual that must be visible to prevent the @c %ListView from snapping
         * back to its leading edge when scrolling ends. For example a value of @c 0 will cause the 
         * @c %ListView to never snap back from the leading visual, a value of @c 0.5 will cause the list
         * view to snap back to its leading edge if scrolling ends with the leading visual occupying
         * less than half of the @c %ListView size in the layout direction.
         *
         * The default value is @c 0.2.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float leadingVisualSnapThreshold
                   READ leadingVisualSnapThreshold
                   WRITE setLeadingVisualSnapThreshold
                   RESET resetLeadingVisualSnapThreshold
                   NOTIFY leadingVisualSnapThresholdChanged FINAL)


        /*!
         * @brief Enables the @c ListView to prebuffer item data during certain scroll operations in order to optimize
         * quality and speed of layout operations.
         *
         * @warning This functionality is currently in an experimental stage and is disabled by default. It should
         * be used with caution and followed up with thorough testing. Examples of risks involved when when using it:
         * 
         *  - Degraded performance. For example, if the contents of a @c %ListView change continuously and rapidly, 
         *    the buffered data can become unusable.
         *  - Scroll latency. Items of considerable byte size (e.g. containing large images) will introduce higher 
         *    latency from the point of the API call to actually reaching visible target. 
         * 
         * @note Currently doesn't support %GridListLayout. When using this type of layout the buffering property
         * will be silently ignored. For all other layout types, the buffering functionality (once enabled) will be 
         * effective for the remainder of the lifetime of the @c %ListView.
         *
         * When enabled, the following scrolling scenarios are affected:
         *
         * - scrollToItem(), scrollToPosition
         * When scrolling to items or named positions with @c ScrollAnimation::None, all items required to fill the 
         * visible area of the listview will be transferred to the server cache before performing the actual scroll 
         * operation. The actual layout will be perceived as instant. However the latency until jumping to the target 
         * location is dependent on the workload of transferring the items to the server. 
         *
         * For any other kind of scroll operation or scroll animation, the buffer functionality is disabled.
         *
         * @see @c scrollToItem(), @c scrollToPosition
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bool bufferedScrollingEnabled READ isBufferedScrollingEnabled WRITE setBufferedScrollingEnabled RESET resetBufferedScrollingEnabled NOTIFY bufferedScrollingEnabledChanged FINAL)

      /*!
       * @brief Indicates this control's scroll role on the page. Scroll role is an abstract concept that indicates to the framework
       * which scrollable control can be considered as main/root scrollable and therefore connected to various appropriate features such as
       * automatically hiding the action bar. Typical characteristics for a main scrollable is that it covers
       * a big part of the screen, that it doesn't have any siblings and that it doesn't have any other scrollable
       * controls as ancestors.
       * The action bar might not hide automatically when user scrolls list if there is not much content left to scroll list down.
       * Controls with scrollRole set to bb::cascades::ScrollRole::None are ignored and can't become a main scrollable control of the page.
       * All scrollable controls with scrollRole set to @c bb::cascades::ScrollRole::Main are considered as main scrollable controls of the page.
       * Scrollable control with scrollRole set to @c bb::cascades::ScrollRole::Default might be considered as the main scrollable control of the page
       * if it satisfies default requirements.
       *
       * The default value is bb::cascades::ScrollRole::Default.
       *
       * @see Page::actionBarAutoHideBehavior
       *
       * @since BlackBerry 10.1.0
       */
      Q_PROPERTY(bb::cascades::ScrollRole::Type scrollRole READ scrollRole WRITE setScrollRole RESET resetScrollRole NOTIFY scrollRoleChanged FINAL)


        /*!
         * @brief The handler used for managing interactive rearrange sessions controlled by user touch input.
         * 
         * Activating the rearrange handler will put the @c %ListView in rearrange mode. Visual "grabber" overlays
         * appears on all leaf items which then can be lifted and dragged by the user.
         * 
         * This is a grouped property, meaning there is always a rearrange handler attached to a @c %ListView. 
         *
         * For more information about rearranging lists, see
         * the [Rearranging lists documentation]("https://developer.blackberry.com/native/documentation/cascades/ui/lists/list_view_selection.html#rearranginglists").
         *
         * @see @c RearrangeHandler
         *
         * @since BlackBerry 10.3.0
         */
        Q_PROPERTY(bb::cascades::RearrangeHandler* rearrangeHandler READ rearrangeHandler REVISION 3 FINAL);

    public:
        /*!
         * @brief A parameter sent by the @c selectionChanged() signal in response to
         * the @c selectAll() and @c clearSelection() functions.
         *
         * @since BlackBerry 10.0.0
         */
        static const QVariantList AllItems;

        /*!
         * @brief Constructs a @c %ListView with a parent.
         *
         * If parent is not @c 0, the ownership of the constructed @c %ListView is
         * transfered to the parent.
         *
         * @param parent The parent container or @c 0. The parent is optional and will default to @c 0 if not specified.
         *
         * @since BlackBerry 10.0.0
         */
        explicit ListView(Container *parent = 0);

        /*!
         * @brief Constructs a @c %ListView with an optional parent using a specified @c DataModel.
         * If parent is not 0, the ownership of the constructed @c %ListView is
         * transfered to the parent.
         *
         * @param dataModel The @c DataModel this @c %ListView will use for its
         * #dataModel property.
         * @param parent The parent container or 0. parent is optional and will default to 0 if not specified.
         *
         * @since BlackBerry 10.0.0
         */
        explicit ListView(bb::cascades::DataModel *dataModel, Container *parent = 0);

        virtual ~ListView();

       /*!
        * @brief Returns the #layout for the @c ListView.
        * 
        * If the layout has not been set to anything else, the default @c StackListLayout will be returned.
        *
        * @return The layout of the @c %ListView, or @c 0 if there's no layout associated with the @c %ListView.
        *
        * @since BlackBerry 10.0.0
        */
        bb::cascades::ListLayout* layout() const;

       /*!
        * @brief Sets a layout on the @c %ListView.
        *
        * Once completed, ownership of the layout is assigned to the @c %ListView.
        *
        * @param layout The layout to be set on the @c %ListView.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void setLayout(bb::cascades::ListLayout *layout);

       /*!
        * @brief Resets the layout to the default layout.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void resetLayout();

        /*!
         * @brief Assigns a @c DataModel to this @c %ListView.
         *
         * This @c %ListView will use the @c DataModel to populate itself with list items.
         * If @c %pDataModel has no parent, this @c %ListView takes ownership of it and
         * sets itself as parent to it (which means that @c %ListView deletes it
         * when @c %ListView is deleted). Any previously set @c %DataModel is
         * unaffected by this call, its parent won't change, and it won't be
         * deleted as a result of calling @c setDataModel().
         *
         * @param pDataModel The @c %DataModel to assign to this @c %ListView.
         *
         * @see dataModel(), resetDataModel()
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setDataModel(bb::cascades::DataModel *pDataModel);

        /*!
         * @brief Gets the @c DataModel assigned to this @c %ListView.
         *
         * @return The @c DataModel assigned to this @c %ListView.
         *
         * @see setDataModel(), resetDataModel()
         *
         * @since BlackBerry 10.0.0
         */
        DataModel *dataModel() const;

        /*!
         * @brief Resets the @c DataModel reference in this @c %ListView, effectively leaving
         * the @c %ListView without an assigned @c %DataModel.
         *
         * @see setDataModel(), dataModel()
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetDataModel();

        /*!
         * @brief Assigns a @c ListItemProvider to this @c %ListView.
         *
         * This @c %ListView will use @c %ListItemProvider when it needs to create
         * or update its list items.
         * If @c pItemProvider has no parent, @c %ListView takes ownership of it and
         * sets itself as parent of it (which means that @c %ListView deletes it
         * when @c %ListView is deleted). Any previously set @c %ListItemProvider is
         * unaffected by this call, its parent won't change, and it won't be
         * deleted as a result of calling @c setListItemProvider().
         *
         * @param pItemProvider The @c %ListItemProvider to assign to this @c %ListView.
         *
         * @see @c listItemProvider(), @c resetListItemProvider()
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setListItemProvider(bb::cascades::ListItemProvider *pItemProvider);

        /*!
         * @brief Gets the @c ListItemProvider assigned to this @c %ListView.
         *
         * @return The @c %ListItemProvider assigned to this @c %ListView.
         *
         * @see @c setListItemProvider(), @c resetListItemProvider()
         *
         * @since BlackBerry 10.0.0
         */
        ListItemProvider *listItemProvider() const;

        /*!
         * @brief Resets the @c ListItemProvider reference for this @c %ListView, effectively
         * leaving this @c %ListView without an assigned @c %ListItemProvider.
         *
         * @see @c setListItemProvider(), @c listItemProvider()
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetListItemProvider();

        /*!
         * @brief Assigns a @c ListItemTypeMapper to this @c %ListView.
         *
         * If this @c %ListView has a @c %ListItemTypeMapper, it calls
         * @c ListItemTypeMapper::itemType() instead of @c DataModel::itemType()
         * whenever the type of an item is needed.
         *
         * @c %ListView does not take ownership of the supplied @c %ListItemTypeMapper.
         * Instead, the caller of this function is responsible for deleting the
         * @c %ListItemTypeMapper when it is no longer needed. This can
         * be accomplished by implementing the @c %ListItemTypeMapper
         * as a @c QObject, and setting this @c %ListView as parent.
         *
         * @param pItemTypeMapper The @c %ListItemTypeMapper to assign to this @c %ListView.
         *
         * @see @c listItemTypeMapper(), @c resetListItemTypeMapper()
         *
         * @since BlackBerry 10.0.0
         */
        void setListItemTypeMapper(ListItemTypeMapper *pItemTypeMapper);

        /*!
         * @brief Gets the @c ListItemTypeMapper assigned to this @c %ListView.
         *
         * @return The @c %ListItemTypeMapper assigned to this @c %ListView.
         *
         * @see @c setListItemTypeMapper(), @c resetListItemTypeMapper()
         *
         * @since BlackBerry 10.0.0
         */
        ListItemTypeMapper *listItemTypeMapper() const;

        /*!
         * @brief Resets @c ListView::listItemTypeMapper, effectively leaving
         * this @c %ListView without an assigned @c %ListItemTypeMapper.
         *
         * @see @c setListItemTypeMapper(), @c listItemTypeMapper()
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetListItemTypeMapper();

        /*!
         * @brief Sets the @c rootIndexPath for the @c %ListView when it references
         * data in the @c DataModel.
         * 
         * The default value is an empty @c QVariantList,
         * which causes this @c %ListView to reference the top level of the @c %DataModel.
         *
         * @param rootIndexPath The @c %rootIndexPath to use. See [Index paths](http://developer.blackberry.com/native/documentation/cascades/ui/lists/list_view_selection.html#indexpaths) for more information.
         *
         * @see @c rootIndexPath(), @c resetRootIndexPath()
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setRootIndexPath(const QVariantList &rootIndexPath);

        /*!
         * @brief Gets the @c rootIndexPath used by the @c %ListView when referencing data
         * in the @c DataModel.
         *
         * @return The @c rootIndexPath used by this @c %ListView.
         *
         * @see @c setRootIndexPath(), @c resetRootIndexPath(), [Index paths](http://developer.blackberry.com/native/documentation/cascades/ui/lists/list_view_selection.html#indexpaths)
         *
         * @since BlackBerry 10.0.0
         */
        QVariantList rootIndexPath() const;

        /*!
         * @brief Resets the @c rootIndexPath to its default value.
         *
         * This causes the @c %ListView to reference the top level of its @c %DataModel.
         *
         * @see @c setRootIndexPath(), @c rootIndexPath(), [Index paths](http://developer.blackberry.com/native/documentation/cascades/ui/lists/list_view_selection.html#indexpaths)
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetRootIndexPath();

        /*!
         * @brief Sets the @c snapMode to be used by the @c %ListView.
         *
         * @param mode The new @c %snapMode to use.
         *
         * @see @c snapMode(), @c resetSnapMode()
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setSnapMode( bb::cascades::SnapMode::Type mode );

        /*!
         * @brief Gets the @c snapMode used by the @c %ListView.
         *
         * @return The @c %snapMode currently used by the @c %ListView.
         *
         * @see @c setSnapMode(), @c resetSnapMode()
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::SnapMode::Type snapMode() const;

        /*!
         * @brief Resets the @c snapMode for the @c %ListView to the default value
         * (@c SnapMode::Default).
         *
         * @see @c setSnapMode(), @c snapMode()
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetSnapMode();

        /*!
         * @brief Sets the @c flickMode to be used by the @c %ListView.
         *
         * @param mode The new @c %flickMode to use.
         *
         * @see @c flickMode(), @c resetFlickMode()
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setFlickMode( bb::cascades::FlickMode::Type mode );

        /*!
         * @brief Gets the @c flickMode used by the @c %ListView.
         *
         * @return The @c %flickMode currently used by the @c %ListView.
         *
         * @see @c setFlickMode(), @c resetFlickMode()
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::FlickMode::Type flickMode() const;

        /*!
         * @brief Resets the @c flickMode for the @c %ListView to the default value
         * (@c FlickMode::Default).
         *
         * @see @c setFlickMode(), @c flickMode()
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetFlickMode();

        /*!
         * @brief Sets the @c stickToEdgePolicy to be used by this @c %ListView.
         *
         * @param policy The new @c %stickToEdgePolicy policy to use.
         *
         * @see @c stickToEdgePolicy(), @c resetStickToEdgePolicy()
         *
         * @since BlackBerry 10.1.0
         */
        Q_SLOT void setStickToEdgePolicy( bb::cascades::ListViewStickToEdgePolicy::Type policy );

        /*!
         * @brief Gets the @c stickToEdgePolicy used by this @c %ListView
         *
         * @return The @c %stickToEdgePolicy currently used by this @c %ListView.
         *
         * @see @c setStickToEdgePolicy(), @c resetStickToEdgePolicy()
         *
         * @since BlackBerry 10.1.0
         */
        bb::cascades::ListViewStickToEdgePolicy::Type stickToEdgePolicy() const;

        /*!
         * @brief Resets the @c stickToEdgePolicy used by this @c %ListView to the default value
         * (@c ListViewStickToEdgePolicy::Default).
         *
         * @see @c setStickToEdgePolicy(), @c stickToEdgePolicy()
         *
         * @since BlackBerry 10.1.0
         */
        Q_SLOT void resetStickToEdgePolicy();

        /*!
        * @brief Returns the @c multiSelectHandler set in this action.
        *
        * @return The @c %multiSelectHandler. This is never 0, since @c %multiSelectHandler
        * is a grouped property.
        *
        * @since BlackBerry 10.0.0
        */
        bb::cascades::MultiSelectHandler* multiSelectHandler() const;

       /*!
        * @brief Returns the @c multiSelectAction to show in the context menu for the list items.
        *
        * @return The @c %multiSelectActionn or @c 0 if it is not set.
        *
        * @since BlackBerry 10.0.0
        */
        bb::cascades::MultiSelectActionItem* multiSelectAction() const;

       /*!
        * @brief Sets the @c multiSelectAction to show in the context menu for the list items.
        *
        * The @c %ListView will take the ownership of the multi-select action, so actions
        * cannot be shared. If the action already has a parent or if
        * @c %multiSelectAction is @c 0, nothing will happen.
        *
        * @param multiSelectAction The @c %multiSelectAction to set.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void setMultiSelectAction(bb::cascades::MultiSelectActionItem* multiSelectAction);

       /*!
        * @brief Resets the @c multiSelectAction to @c 0.
        *
        * This means no @c %multiSelectAction will be displayed in the context menu.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void resetMultiSelectAction();


        /*!
         * @brief Sets a value for the property @c ListView::scrollIndicatorMode.
         *
         * @param mode The new value for the property.
         *
         * @see @c scrollIndicatorMode(), @c resetScrollIndicatorMode()
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setScrollIndicatorMode(bb::cascades::ScrollIndicatorMode::Type mode);

        /*!
         * @brief Returns the current value of the property @c ListView::scrollIndicatorMode.
         *
         * @return The scroll indicator mode currently used by this @c %ListView.
         *
         * @see @c setScrollIndicatorMode(), @c resetScrollIndicatorMode()
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::ScrollIndicatorMode::Type scrollIndicatorMode() const;

        /*!
         * @brief Resets the property @c ListView::scrollIndicatorMode to its
         * default value, which is @c ScrollIndicatorMode::Default.
         *
         * @see @c setScrollIndicatorMode(), @c scrollIndicatorMode()
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetScrollIndicatorMode();

        /*!
         * @brief Checks if a specific item is currently selected.
         *
         * @param indexPath Specifies an item in the @c DataModel connected to this @c %ListView.
         *        See [Index paths](http://developer.blackberry.com/native/documentation/cascades/ui/lists/list_view_selection.html#indexpaths) for more information.
         * @return @c true if the specified item is selected, @c false otherwise.
         *
         * @see @c select(), @c toggleSelection(), @c selected(), @c selectionList()
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE bool isSelected( const QVariantList &indexPath ) const;

        /*!
         * @brief Selects or deselects the specified item.
         *
         * If the selection state of an item changes, the signal @c selectionChanged()
         * is emitted.
         *
         * @param indexPath Specifies an item in the @c DataModel connected to this @c %ListView. 
         *        See [Index paths](http://developer.blackberry.com/native/documentation/cascades/ui/lists/list_view_selection.html#indexpaths) for more information.
         * @param select The value to set for the selected state of the specified item.
         *
         * @see @c toggleSelection(), @c isSelected(), @c selected(), @c selectionList()
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void select( const QVariantList &indexPath, bool select = true );

        /*!
         * @brief Toggles selection on an item.
         *
         * If the item is selected, it becomes deselected. If the item is deselected, it
         * becomes selected.
         *
         * After the selection is toggled, the signal @c selectionChanged() is emitted.
         *
         * @param indexPath Specifies an item in the @c DataModel connected to this @c %ListView.
         *        See [Index paths](http://developer.blackberry.com/native/documentation/cascades/ui/lists/list_view_selection.html#indexpaths) for more information.
         *
         * @see @c select(), @c isSelected(), @c selected(), @c selectionList()
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void toggleSelection( const QVariantList &indexPath );

        /*!
         * @brief Makes all items deselected.
         *
         * This function does not cause signals to be emitted for individual items. Instead,
         * a single @c selectionChanged() is emitted with @c ListView::AllItems
         * and @c false as parameters.
         *
         * @see selectAll(), selected(), selectionList()
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void clearSelection();

        /*!
         * @brief Makes all items selected.
         *
         * Does not cause signals to be emitted for individual items. Instead
         * a single @c selectionChanged() is emitted with @c ListView::AllItems
         * and @c true as parameters.
         *
         * @see @c clearSelection(), @c selected(), @c selectionList()
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void selectAll();

        /*!
         * @brief Gets the index path of the selected item.
         *
         * @return Index path of the first found selected item, or an empty
         * @c QVariantList if no item is currently selected in this @c %ListView.
         *
         * @see @c select(), @c toggleSelection(), @c selectAll(), @c clearSelection(), @c isSelected(), @c selectionList()
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE QVariantList selected() const;

        /*!
         * @brief Gets a list of all selected items.
         *
         * @return Returns a list of index paths for all the selected items.
         * The returned list is of the type @c QVariantList so that it can be
         * used in QML. Index paths are also @c %QVariantList objects,
         * so they can be used in QML. The returned object is a
         * @c %QVariantList containing other @c %QVariantList objects (one such
         * object for each selected item). The selection list is cleared when
         * the @c MultiSelectHandler becomes inactive.
         *
         * @see @c select(), @c toggleSelection(), @c selectAll(), @c clearSelection(), @c isSelected(), @c selected()
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE QVariantList selectionList() const;

        /*!
         * @brief Scrolls the list with the specified pixel offset.
         *
         * Specifying a positive offset value will scroll the list forward in scroll space regardless of item
         * sort order. For example, in a vertical list positive offsets will always move scroll position from
         * top to bottom, even if item sort order is set to bottom-to-top.
         *
         * IMPORTANT: This function is intended to be used for short scrolling distances, preferably not targeting 
         * positions or items outside the current view. For longer scrolling operations it is recommended to use 
         * either scrollToItem() or scrollTo().
         *
         * @param offset The positive or negative pixel offset to scroll the list.
         * @param scrollAnimation The type of animation to be used when scrolling.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void scroll(float offset, bb::cascades::ScrollAnimation::Type scrollAnimation = bb::cascades::ScrollAnimation::Default);

        /*!
         * @brief Scrolls to an item so that the item is placed in the top of the visible
         * area of this @c %ListView.
         * When this function is called on a device with a trackpad or similar input, and the ListView is focused or has a focused descendant,
         * scrollToItem will try setting focus on the item being scrolled to at the end of the programmatic scroll.
         *
         * @param indexPath Specifies which item to jump to. See [Index paths](http://developer.blackberry.com/native/documentation/cascades/ui/lists/list_view_selection.html#indexpaths) for more information.
         * @param scrollAnimation Specifies which animation type to use when scrolling.
         *
         * @see @c scrollToPosition()
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void scrollToItem(const QVariantList &indexPath, bb::cascades::ScrollAnimation::Type scrollAnimation = bb::cascades::ScrollAnimation::Default);

        /*!
         * @brief Scrolls to a predefined position in this @c %ListView.
         *
         * @param position Specifies which position to scroll to.
         * @param scrollAnimation Specifies which animation type to use when scrolling.
         *
         * @see @c scrollToItem()
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void scrollToPosition(bb::cascades::ScrollPosition::Type position, bb::cascades::ScrollAnimation::Type scrollAnimation = bb::cascades::ScrollAnimation::Default);

        /*! @cond PRIVATE
         * Workaround for the Qt bug that prevents our enums from being
         * function arguments in QML.
         */
        Q_SLOT void scroll(float offset, int scrollAnimation );
        Q_SLOT void scrollToItem(const QVariantList &indexPath, int scrollAnimation );
        Q_SLOT void scrollToPosition(int position, int scrollAnimation );
        /*! @endcond */

        /*!
         * @brief Gets the @c leadingVisual property for the @c %ListView.
         *
         * Ownership of the leading visual will not be transferred from the @c %ListView.
         *
         * @return The leading visual.
         *
         * @see @c setLeadingVisual(), @c resetLeadingVisual()
         *
         * @since BlackBerry 10.0.0
         */
         bb::cascades::VisualNode* leadingVisual() const;

        /*!
         * @brief Resets the @c leadingVisual property to its default value of @c 0.
         *
         * @see @c leadingVisual(), @c setLeadingVisual()
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetLeadingVisual();

        /*!
         * @brief Sets the @c leadingVisual property to be used by this @c %ListView.
         *
         * If @c pLeadingVisual has no parent, this @c %ListView takes ownership of it and
         * sets itself as parent to it (which means that @c %ListView deletes it
         * when @c %ListView is deleted). Any previously set leading visual is
         * unaffected by this call; its parent won't change and it won't be
         * deleted as a result of calling @c setLeadingVisual().
         *
         * @param pLeadingVisual The new @c #leadingVisual.
         *
         * @see @c leadingVisual(), @c resetLeadingVisual()
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setLeadingVisual(bb::cascades::VisualNode* pLeadingVisual);

        /*!
         * @brief Gets the @c leadingVisualSnapThreshold property for the @c %ListView.
         *
         * @return The leading visual snap threshold.
         *
         * @see @c setLeadingVisualSnapThreshold(), @c resetLeadingVisualSnapThreshold()
         *
         * @since BlackBerry 10.0.0
         */
        float leadingVisualSnapThreshold() const;

        /*!
         * @brief Resets the @c leadingVisualSnapThreshold property to its default value of @c 0.2f.
         *
         * @see @c leadingVisualSnapThreshold(), @c setLeadingVisualSnapThreshold()
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetLeadingVisualSnapThreshold();

        /*!
         * @brief Sets the @c leadingVisualSnapThreshold property to be used by this @c %ListView.
         *
         * @param leadingVisualSnapThreshold The new @c leadingVisualSnapThreshold.
         *
         * @see @c leadingVisualSnapThreshold(), @c resetLeadingVisualSnapThreshold()
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setLeadingVisualSnapThreshold(float leadingVisualSnapThreshold);

        /*!
         * @brief Gets the @c bufferedScrollingEnabled property for the @c %ListView.
         *
         * @return The @c %bufferedScrollingEnabled flag.
         *
         * @see @c setBufferedScrollingEnabled(), @c resetBufferedScrollingEnabled()
         *
         * @since BlackBerry 10.0.0
         */
        bool isBufferedScrollingEnabled() const;

        /*!
         * @brief Resets the @c bufferedScrollingEnabled property to its default value of @c false.
         *
         * @see @c isBufferedScrollingEnabled(), @c setBufferedScrollingEnabled()
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetBufferedScrollingEnabled();

        /*!
         * @brief Sets the @c bufferedScrollingEnabled property to be used by this @c %ListView.
         *
         * @param bufferedScrollingEnabled The new value for the buffered scrolling property.
         *
         * @see @c isBufferedScrollingEnabled(), @c resetBufferedScrollingEnabled()
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setBufferedScrollingEnabled(bool bufferedScrollingEnabled);

        /*!
        * @brief Get the @c scrollStops currently specified for the @c %ListView.
        *
        * Note that the index paths retrieved by this method might differ from the list
        * earlier passed to @c %setScrollStops.
        *
        * @return The @c %scrollStops index paths as a @c QVariantList of @c QVariantList objects.
        *
        * @see @c setScrollStops()
         *
         * @since BlackBerry 10.0.0
        */
        Q_INVOKABLE QVariantList scrollStops() const;

       /*!
        * @brief Sets the @c scrollStops index paths for the list.
        *
        * Scrolling in the list will stop at the positions of the items located at the given index paths. 
        *
        * When items are added or removed in the list, the server will internally compensate by modifying 
        * the index paths to match the original items. As a result, the original list of 
        * index paths might differ from the actual one used on the server. In order to make changes in the 
        * list of stop items, it is recommended to first aquire it by using scrollStops() and make any 
        * modifications accordingly, rather than keeping the list that was originally passed to this function.
        *
        * Here's a C++ example of setting two scroll stops on index path 0,2 and 2,2:
        *
        * @code
        * QVariantList stopIndexPaths, firstStop, secondStop;
        * firstStop << 0 << 2;
        * secondStop << 2 << 2;
        * stopIndexPaths.push_back(firstStop);
        * stopIndexPaths.push_back(secondStop);
        *
        * mListView->setScrollStops(stopIndexPaths);
        * @endcode
        *
        * Here's how to set the same scroll stops in QML:
        *
        * @code
        * setScrollStops([[0, 2], [2, 2]]);
        * @endcode
        *
        * The list will not make any compensation when signal DataModel::itemsChanged is received. 
        * In this case the client itself needs to provide an updated list of index paths.
        *
        * @param indexPaths  The list of index paths specifying the items to use as scroll stop points. This list
        *                    is a nested QVariantList, i.e. each element of the list is in itself a 
        *                    QVariantList representing the index paths. Passing an empty list will remove
        *                    all stop points. See [Index paths](http://developer.blackberry.com/native/documentation/cascades/ui/lists/list_view_selection.html#indexpaths) for more information.
        *
        * @see @c scrollStops()
        *
        * @since BlackBerry 10.0.0
        */
        Q_INVOKABLE void setScrollStops( const QVariantList& indexPaths );

        /*!
         * @brief Gets the current @c %ListView scrollRole.
         *
         * @return The @c %ListView scrollRole.
         *
         * @since BlackBerry 10.1.0
         */
        bb::cascades::ScrollRole::Type scrollRole() const;

        /*!
         * @brief Sets the @c %ListView scrollRole.
         *
         * Signal @c scrollRoleChanged() is emitted if value is changed.
         * @param scrollRole Specifies a control's ScrollRole value.
         *
         * @since BlackBerry 10.1.0
         */
        Q_SLOT void setScrollRole(bb::cascades::ScrollRole::Type scrollRole);

        /*!
         * @brief Resets a control's scrollRole property.
         *
         * Default value is @c ScrollRole::Default.
         *
         * @since BlackBerry 10.1.0
         */
        Q_SLOT void resetScrollRole();

        /*!
         * @brief Retrieves the rearrange handler attached to the @c ListView.
         *
         * The rearrange handler is used for 2-way communication between the application
         * and the @c ListView during rearrange mode.
         *
         * @since BlackBerry 10.3.0
         */
        Q_REVISION(3)
        Q_SLOT RearrangeHandler* rearrangeHandler();

    Q_SIGNALS:

        /*!
         * @brief Emitted when @c ListView::scrollRole has changed.
         *
         * @param newScrollRole new scrollRole value.
         *
         * @since BlackBerry 10.1.0
         */
        void scrollRoleChanged(bb::cascades::ScrollRole::Type newScrollRole);

       /*!
        * @brief Emitted when a new @c #layout is set on the @c %ListView.
        *
        * @param layout The new layout.
        *
        * @since BlackBerry 10.0.0
        */
        void layoutChanged(bb::cascades::ListLayout *layout);

        /*!
         * @brief Emitted when @c ListView::dataModel has changed.
         *
         * @param dataModel The new @c DataModel.
         *
         * @since BlackBerry 10.0.0
         */
        void dataModelChanged(bb::cascades::DataModel *dataModel);

        /*!
         * @brief Emitted when @c ListView::listItemProvider has changed.
         *
         * @param listItemProvider The new @c ListItemProvider.
         *
         * @since BlackBerry 10.0.0
         */
        void listItemProviderChanged(bb::cascades::ListItemProvider *listItemProvider);

        /*!
         * @brief Emitted when @c ListView::rootIndexPath has changed.
         *
         * @param rootIndexPath The new @c rootIndexPath. See [Index paths](http://developer.blackberry.com/native/documentation/cascades/ui/lists/list_view_selection.html#indexpaths) for more information.
         *
         * @since BlackBerry 10.0.0
         */
        void rootIndexPathChanged(QVariantList rootIndexPath);

        /*!
         * @brief Emitted when @c ListView::scrollIndicatorMode has changed.
         *
         * @note Due to a work around for a Qt Core issue with accessing enums from QML,
         * the argument of this signal doesn't follow the usual naming convention for signals. 
         * Typically, signal arguments are named to match the associated property's name.
         * In this case, you must use the object's property to access the current 
         * property value instead of the signal argument to avoid runtime errors 
         *(use @c scrollIndicatorMode instead of @c newScrollIndicatorMode).
         *
         * @param newScrollIndicatorMode The new value of the @c scrollIndicatorMode property.
         *
         * @since BlackBerry 10.0.0
         */
        void scrollIndicatorModeChanged(bb::cascades::ScrollIndicatorMode::Type newScrollIndicatorMode);

        /*!
         * @brief Emitted when @c ListView::snapMode has changed.
         *
         * @note Due to a work around for a Qt Core issue with accessing enums from QML,
         * the argument of this signal doesn't follow the usual naming convention for signals. 
         * Typically, signal arguments are named to match the associated property's name.
         * In this case, you must use the object's property to access the current 
         * property value instead of the signal argument to avoid runtime errors 
         * (use @c snapMode instead of @c newSnapMode).
         *
         * @param newSnapMode The new snap mode.
         *
         * @since BlackBerry 10.0.0
         */
        void snapModeChanged(bb::cascades::SnapMode::Type newSnapMode);

        /*!
         * @brief Emitted when @c ListView::flickMode has changed.
         *
         * @note Due to a work around for a Qt Core issue with accessing enums from QML,
         * the argument of this signal doesn't follow the usual naming convention for signals. 
         * Typically, signal arguments are named to match the associated property's name.
         * In this case, you must use the object's property to access the current 
         * property value instead of the signal argument to avoid runtime errors 
         * (use @c flickMode instead of @c newFlickMode).
         *
         * @param newFlickMode The new flick mode.
         *
         * @since BlackBerry 10.0.0
         */
        void flickModeChanged(bb::cascades::FlickMode::Type newFlickMode);

        /*!
         * @brief Emitted when @c ListView::stickToEdgePolicy has changed.
         *
         * @note Due to a work around for a Qt Core issue with accessing enums from QML,
         * the argument of this signal doesn't follow the usual naming convention for signals. 
         * Typically, signal arguments are named to match the associated property's name.
         * In this case, you must use the object's property to access the current 
         * property value instead of the signal argument to avoid runtime errors 
         * (use @c stickToEdgePolicy instead of @c newStickToEdgePolicy).
         *
         * @param newStickToEdgePolicy The new stick to edge policy.
         *
         * @since BlackBerry 10.1.0
         */
        void stickToEdgePolicyChanged(bb::cascades::ListViewStickToEdgePolicy::Type newStickToEdgePolicy);

       /*!
        * @brief Emitted when @c multiSelectAction has changed.
        *
        * @param multiSelectAction The new @c %multiSelectAction or @c 0 if it is not set.
        *
        * @since BlackBerry 10.0.0
        */
        void multiSelectActionChanged(bb::cascades::MultiSelectActionItem *multiSelectAction);


        /*!
         * @brief Emitted when the activation state has changed for a list item.
         *
         * A list item is typically active while the user is pressing the item.
         * Once released, the item is no longer active.
         *
         * If the item implements the @c ListItemListener interface, @c %ListView also 
         * calls @c ListItemListener::active() whenever the active state of the item
         * is changed.
         *
         * @param indexPath The index path to the item. See [Index paths](http://developer.blackberry.com/native/documentation/cascades/ui/lists/list_view_selection.html#indexpaths) for more information. 
         * @param active @c true if the new state is active, @c false otherwise.
         *
         * @since BlackBerry 10.0.0
         */
        void activationChanged(QVariantList indexPath, bool active);

        /*!
         * @brief Emitted before one or more items are about to be selected. 
         *
         * This signal is emitted right before any item selection(s) take place. 
         * The number of selections that will follow is undefined and depends on how selection
         * is made.
         * 
         * For example, if one item is selected by the user via screen touch, this signal will 
         * first be emitted, then follows one @c selectionChanged() signal and then a @c selectionChangeEnded()
         * signal concludes the selection. In other cases, such as when the user is able to select items
         * more rapidly, several selectionChanged() signals may be emitted in between @c selectionChangeStarted()
         * and @c selectionChangeEnded().
         *
         * @see selectionChangeEnded()
         * @see selectionChanged()
         *
         * @since BlackBerry 10.3.1
         */
        Q_REVISION(4)
        void selectionChangeStarted();

        /*!
         * @brief Emitted after one or more items have been selected. 
         *
         * This signal always follows when one or more items have been selected. Typically, any generic 
         * processing tasks that apply to a selection change as a whole, can be carried out when receiving 
         * this signal in order to maintain performance. 
         * For instance, extraction of the current set of selected items, by calling @c selectionList(), is 
         * recommended to be carried out when this signal is received rather than every time the 
         * @c selectionChanged() signal is received.
         *
         * @see selectionChangeStarted()
         * @see selectionChanged()
         *
         * @since BlackBerry 10.3.1
         */
        Q_REVISION(4)
        void selectionChangeEnded();

        /*!
         * @brief Emitted when the selection state has changed for a list item.
         *
         * An item which opens the context menu is for example selected. The context menu is 
         * opened by long pressing the item. Multiple items can be selected when the 
         * @c multiSelectHandler is active. It is also possible to select and deselect items 
         * programmatically using, for example, @c select(), @c toggleSelection(), 
         * @c selectAll() and @c clearSelection().
         *
         * If the item implements the @c ListItemListener interface, @c %ListView also 
         * calls @c ListItemListener::select() whenever the selection state of the item
         * is changed.
         *
         * @see Signal triggered() if you want to be notified when the user taps on
         * a list item with the intention to trigger an action.
         *
         * @param indexPath The index path to the item. See [Index paths](http://developer.blackberry.com/native/documentation/cascades/ui/lists/list_view_selection.html#indexpaths) for more information.
         * @param selected @c true if the new state is selected, @c false otherwise.
         *
         * @since BlackBerry 10.0.0
         */
        void selectionChanged(QVariantList indexPath, bool selected);

        /*!
        * @brief Emitted when a list item is triggered by the user.
        *
        * Typically, this signal is emitted when an item is tapped by the user 
        * with the intention to execute some action associated with it. 
        * This signal is, for example, not emitted when items are tapped 
        * during multiple selection, where the intention is to select the 
        * tapped item and not trigger an action associated with it.
        *
        * @param indexPath The index path to the triggered item. See [Index paths](http://developer.blackberry.com/native/documentation/cascades/ui/lists/list_view_selection.html#indexpaths) for more information.
         *
         * @since BlackBerry 10.0.0
        */
        void triggered(QVariantList indexPath);

       /*!
        * @brief Emitted when the @c #leadingVisual for the @c %ListView has changed.
        *
        * @param pLeadingVisual The new @c #leadingVisual.
        *
        * @since BlackBerry 10.0.0
        */
        void leadingVisualChanged(bb::cascades::VisualNode* pLeadingVisual);

       /*!
        * @brief Emitted when the @c leadingVisualSnapThreshold has changed.
        *
        * @param leadingVisualSnapThreshold The new @c %leadingVisualSnapThreshold.
        *
        * @since BlackBerry 10.0.0
        */
        void leadingVisualSnapThresholdChanged(float leadingVisualSnapThreshold);

       /*!
        * @brief Emitted when the bufferedScrollingEnabled property has changed.
        *
        * @param bEnabled The new buffered scrolling value.
        *
        * @since BlackBerry 10.0.0
        */
        void bufferedScrollingEnabledChanged(bool bEnabled);

    protected:
        /*! @cond PRIVATE */
        ListView(ListViewPrivate &_d_ptr, Container *parent = 0);
        /*! @endcond */

    private:
        /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(ListView)
        Q_DISABLE_COPY(ListView)
        /*! @endcond */

    public:
        /*! @cond PRIVATE */
        typedef ListView ThisClass;
        typedef Control BaseClass;
        /*! @endcond */

        /*!
         * @brief A builder template for constructing a @c %ListView.
         *
         * See ListView::create() for getting a concrete builder for constructing a @c %ListView.
         *
         * @since BlackBerry 10.0.0
         */
        template <typename BuilderType, typename BuiltType>
        class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType> {
        protected:
            TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node) {}
        public:

            /*!
             * @brief Convenience method for @c setLayout.
             *
             * @see setLayout.
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& layout(bb::cascades::ListLayout *_layout)
            {
                this->instance().setLayout(_layout);
                return this->builder();
            }

            /*!
             * @brief Assigns a @c DataModel to this @c %ListView.
             *
             * This is a convenience method for @c setDataModel.
             *
             * This @c %ListView will use the @c %DataModel to populate itself with list items.
             * If pDataModel has no parent, this @c %ListView takes ownership of it and
             * sets itself as parent to it (which means that @c %ListView deletes it
             * when @c %ListView is deleted). Any previously set @c %DataModel is
             * unaffected by this call, its parent won't change and it won't be
             * deleted as a result of calling setDataModel().
             *
             * @param pDataModel The @c %DataModel to assign to this @c %ListView.
             *
             * @see setDataModel()
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& dataModel(DataModel *pDataModel) {
                this->instance().setDataModel(pDataModel);
                return this->builder();
            }

            /*!
             * @brief Assigns a @c ListItemProvider to this @c %ListView.
             *
             * This @c %ListView will use the @c %ListItemProvider when it needs to create
             * or update its list items.
             * If @c pItemProvider has no parent, @c %ListView takes ownership of it and
             * sets itself as parent of it (which means that @c %ListView deletes it
             * when @c %ListView is deleted). Any previously set @c %ListItemProvider is
             * unaffected by this call, its parent won't change and it won't be
             * deleted as a result of calling setListItemProvider().
             *
             * @param pItemProvider The @c %ListItemProvider to assign to this @c %ListView.
             *
             * @see listItemProvider(), resetListItemProvider()
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& listItemProvider(ListItemProvider *pItemProvider) {
                this->instance().setListItemProvider(pItemProvider);
                return this->builder();
            }

            /*!
             * @brief Sets the @c rootIndexPath for this @c %ListView to use when it references
             * data in the @c DataModel.
             * 
             * The default value is an empty @c QVariantList,
             * which causes this @c %ListView to reference the top level of the @c %DataModel.
             *
             * @param rootIndexPath The root index path to use.
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& rootIndexPath(const QVariantList &rootIndexPath) {
                this->instance().setRootIndexPath(rootIndexPath);
                return this->builder();
            }

            /*!
             * @brief Sets a value for the property @c ListView::scrollIndicatorMode.
             *
             * @param eMode The new value for the property.
             *
             * @see @c scrollIndicatorMode(), @c resetScrollIndicatorMode()
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& scrollIndicatorMode(bb::cascades::ScrollIndicatorMode::Type eMode) {
                this->instance().setScrollIndicatorMode(eMode);
                return this->builder();
            }

            /*!
             * @brief Sets the @c flickMode to be used by this @c %ListView.
             *
             * @param eMode The new @c %flickMode to use.
             *
             * @see @c flickMode(), @c resetFlickMode()
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& flickMode(bb::cascades::FlickMode::Type eMode) {
                this->instance().setFlickMode(eMode);
                return this->builder();
            }

            /*!
             * @brief Sets the @c stickToEdgePolicy to be used by this @c %ListView.
             *
             * @param eStickToEdgePolicy The new @c %stickToEdgePolicy to use.
             *
             * @see @c stickToEdgePolicy(), @c resetStickToEdgePolicy()
             *
             * @since BlackBerry 10.1.0
             */
            BuilderType& stickToEdgePolicy(bb::cascades::ListViewStickToEdgePolicy::Type eStickToEdgePolicy) {
                this->instance().setStickToEdgePolicy(eStickToEdgePolicy);
                return this->builder();
            }

            /*!
             * @brief Sets the @c snapMode to be used by this @c %ListView.
             *
             * @param eMode The new @c %snapMode to use.
             *
             * @see @c snapMode(), @c resetSnapMode()
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& snapMode(bb::cascades::SnapMode::Type eMode) {
                this->instance().setSnapMode(eMode);
                return this->builder();
            }

            /*!
             * @brief Sets the scroll role for this @c %ListView.
             *
             * Using this convenience function in the builder pattern is equivalent to the following:
             * @code
             * myListView->setScrollRole(role);
             * @endcode
             *
             * @param role The scroll role of the %ListView.
             *
             * @see @c scrollRole(), @c resetScrollRole()
             *
             * @since BlackBerry 10.1.0
             */
            BuilderType& scrollRole(bb::cascades::ScrollRole::Type role) {
              this->instance().setScrollRole(role);
                return this->builder();
            }

            /*!
             * @brief Sets the @c leadingVisual to be used by this @c %ListView.
             *
             * @param pLeadingVisual The new @c %leadingVisual.
             *
             * @see @c leadingVisual(), @c resetLeadingVisual()
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& leadingVisual(VisualNode *pLeadingVisual) {
                this->instance().setLeadingVisual(pLeadingVisual);
                return this->builder();
            }
        };

        /*!
         * @brief A concrete builder class for constructing a @c %ListView.
         *
         * See @c ListView::create() for getting a concrete builder for constructing a @c %ListView.
         *
         * @since BlackBerry 10.0.0
         */
        class Builder : public TBuilder<Builder, ListView> {
        public:
            explicit Builder() : TBuilder<Builder, ListView>(new ListView()) {}
        };

        /*!
         * @brief Creates and returns a builder for constructing a @c %ListView.
         *
         * This creator takes no @c ListLayout parameter. This is the equivalent to using the @c %ListView constructor, which takes
         * a @c %ListLayout parameter and passes a @c StackListLayout with @c LayoutOrientation::TopToBottom.
         *
         * @return A builder for constructing a @c %ListView.
         *
         * @since BlackBerry 10.0.0
         */
        static Builder create() {
            return Builder();
        }
    };
}
}

QML_DECLARE_TYPE(bb::cascades::ListView)

#endif /* cascades_listview_h */
