/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_listitemprovider_h
#define cascades_listitemprovider_h

#include <QObject>
#include <QVariant>
#include <QtDeclarative/QtDeclarative>

#include <bb/cascades/bbcascades_global.h>


namespace bb {
namespace cascades {

    class ListView;
    class VisualNode;

   /*!
    *
    * @brief An interface for providing @c VisualNode objects as items in a @c ListView.
    *
    * Using @c %ListItemProvider is the C++ approach for
    * customizing list item visuals. In QML, list item visuals are customized by declaring
    * one or several @c ListItemComponent objects on the @c ListView::listItemComponents property.
    *
    * By default, if no @c %ListItemProvider is attached to a @c ListView,
    * the @c %ListView uses @c Header for items of type "header" and
    * @c StandardListItem for all other items.
    *
    * When you implement @c %ListItemProvider, these two functions are required:
    * - @c createItem(): creates a @c VisualNode object for the @c ListView, to be used as a list item
    * - @c updateItem(): called whenever an item is about to be shown, and when the data representation
    * of the item (in the @c DataModel) has changed
    *
    * A single @c %ListItemProvider can be used by any number of @c %ListView objects.
    *
    * Here's an example of how to extend @c %ListItemProvider and override its
    * @c %createItem() and @c %updateItem() functions. The class is called
    * @c MyItemClassFactory and it's used to create list items for each object
    * in the list.
    *
    * @code
    * class MyItemClassFactory: public bb::cascades::ListItemProvider
    * {
    * public:
    *     MyItemClassFactory();
    *
    *     VisualNode * createItem(ListView* list, const QString &type);
    *
    *     void updateItem(ListView* list, VisualNode *listItem, const QString &type,
    *                     const QVariantList &indexPath, const QVariant &data);
    * };
    * @endcode
    *
    * Within the definition for @c createItem(), a @c MyItemClass object is created. @c MyItemClass
    * is a custom class that implements @c ListItemListener, and its constructor returns a @c VisualNode
    * object representing the list item. Within
    * the definition for @c updateItem(), @c MyItemClass::updateItem() is called to update the visual
    * control with new data.
    *
    * @code
    * MyItemClassFactory::MyItemClassFactory()
    * {
    * }
    *
    * VisualNode * MyItemClassFactory::createItem(ListView* list, const QString &type)
    * {
    *     //We only have one item type so we do not need to check the type variable.
    *     MyItemClass *myItem = new MyItemClass();
    *     return myItem;
    * }
    *
    * void MyItemClassFactory::updateItem(ListView* list, bb::cascades::VisualNode *listItem,
    *         const QString &type, const QVariantList &indexPath, const QVariant &data)
    * {
    *     // Update the control with correct data.
    *     QVariantMap map = data.value<QVariantMap>();
    *     MyItemClass *myItem = static_cast<MyItemClass *>(listItem);
    *     // Call  the instance of our CustomContrlol MyItemClass and provide the data we want it to layout
    *     myItem->updateItem(map["title"].toString(), map["image"].toString());
    * }
    * @endcode
    *
    * Here is how the @c %ListItemProvider is attached to the @c %ListView.
    *
    * @code
    * ListView *listView = new ListView();
    * MyItemClassFactory *myItemProvider = new MyItemClassFactory();
    * listView->setListItemProvider(myItemProvider);
    * @endcode
    *
    * To see how the @c MyItemClass class is created, see the @c ListItemListener API documentation.
    *
    * For a complete example, download the <a href="/native/sampleapps/">Cascades Cookbook C++</a> sample app.
    *
    * @see ListView, ListItemListener, DataModel
    *
    * @xmlonly
    * <apigrouping group="User interface/List"/>
    * @endxmlonly
    *
    * @since BlackBerry 10.0.0
    */
    class BBCASCADES_EXPORT ListItemProvider : public QObject {
        Q_OBJECT

    public:
       /*!
        * @brief Constructs a @c ListItemProvider instance with the specified parent.
        *
        * If the specified parent is not @c 0, the ownership of the constructed @c %ListItemProvider
        * is transferred to the parent.
        *
        * @param parent The parent @c QObject, or @c 0. Optional and will default to @c 0 if not
        * specified.
        *
        * @since BlackBerry 10.0.0
        */
        explicit ListItemProvider(QObject *parent = 0);

        /*!
         * @brief Destructs this @c ListItemProvider.
         *
         * @since BlackBerry 10.0.0
         */
        virtual ~ListItemProvider();

       /*!
        * @brief Creates a @c VisualNode for the specified @c ListView, to be used as a list item.
        *
        * The type of list item is determined based on the @c type parameter, which corresponds
        * to the type returned by the @c DataModel (through @c DataModel::itemType). The @c %ListView
        * takes ownership of the returned @c %VisualNode.
        *
        * @param list The @c %ListView for which the item should be created.
        * @param type The list item type, corresponding to the type provided by the @c %DataModel
        * that is used by @c list.
        *
        * @return The newly created @c %VisualNode.
        *
        * @since BlackBerry 10.0.0
        */
        virtual VisualNode *createItem(ListView *list, const QString &type) = 0;

       /*!
        * @brief Updates the specified list item based on the provided type, index path, and data.
        *
        * This function is called whenever an item is about to be shown, and also
        * when the data representation of the item (in the @c DataModel) has changed.
        *
        * @param list The @c ListView that contains the item to be updated.
        * @param listItem The list item to be updated.
        * @param type The list item type, corresponding to the type provided by the @c %DataModel
        * that is used by @c list.
        * @param indexPath The index path to the item that is to be updated.
        * @param data The data from the @c %DataModel that corresponds to @c listItem.
        *
        * @since BlackBerry 10.0.0
        */
        virtual void updateItem(ListView *list, VisualNode *listItem, const QString &type,
            const QVariantList &indexPath, const QVariant &data) = 0;

    Q_SIGNALS:
        /*!
         * @brief Emitted when the @c ListView that uses this @c ListItemProvider should call
         * @c updateItem() for all of its cached items.
         *
         * The @c %ListItemProvider implementation should typically emit this signal
         * when an application wants to change the visual appearance of all
         * items in a @c %ListView.
         *
         * @since BlackBerry 10.0.0
         */
        void itemUpdatesNeeded();

    private:
        Q_DISABLE_COPY(ListItemProvider)
    };
}
}

QML_DECLARE_TYPE(bb::cascades::ListItemProvider)

#endif // cascades_listitemprovider_h
