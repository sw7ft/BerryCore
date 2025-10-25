/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_datamodel_h
#define cascades_datamodel_h

#include <QtCore/QObject>
#include <QtDeclarative/QtDeclarative>
#include <QtCore/QList>
#include <QtCore/QVariant>
#include <QSharedPointer>
#include <bb/cascades/bbcascades_global.h>

#include <bb/cascades/databinding/datamodelchangetype.h>


namespace bb {
namespace cascades {
    /*!
     *
     * @brief An abstract class that can be used to provide a @c ListView with data.
     *
     * Any data that can be contained in a @c QVariant can be provided to the @c %ListView.
     * Typical examples of @c QVariant content are @c QString, @c QVariantMap and @c QObject*.
     * The data can also be an empty @c %QVariant for each item, if the @c %ListView has a
     * @c ListItemProvider with access to all relevant data.
     *
     * When a @c %DataModel implementation is attached to a @c %ListView, the @c %ListView will call the
     * @c %DataModel implementation when model data is needed and will listen to the various signals
     * emitted from the @c %DataModel implementation. @c %ListView takes ownership
     * of any @c %QObject* (wrapped in @c %QVariant) returned by @c data(), if the returned object
     * doesn't already have a parent.
     *
     * A single @c %DataModel can be connected to any number of @c %ListView objects. @c %ListView has
     * a property @c ListView::rootIndexPath that allows it to choose which node in the @c %DataModel
     * to use as the root node.
     *
     * <h2>Index paths</h2>
     *
     * Index paths are used for identifying items in @c %ListView, @c %DataModel
     * and all related classes. In C++ an index path is a @c QVariantList
     * object containing a number of @c QVariant integers, one for each ancestor (including the root
     * item) of the specified item. The reason for index paths being @c %QVariantList
     * objects in C++ is that @c %QVariantList objects are the C++ equivalent of QML JavaScript arrays.
     * So in QML an index path is simply an array containing integers.
     * For an item that is a direct child of the root item,
     * the index path contains a single integer. A child of that item would instead have
     * an index path consisting of two integers, and so on.
     *
     * Examples of index paths:
     *
     * - [3] - index path for the fourth child of the root item
     * - [3,0] - index path for the first child of the fourth child of the root item
     * - [] - index path for the root item (an empty array)
     *
     * Example of accessing indexes from index paths in C++:
     *
     * - indexPath[0].toInt() - gets the top level index from this index path
     * - indexPath[1].toInt() - gets the second level index from this index path (if the index
     * path contains that many levels)
     *
     * See [Index paths](http://developer.blackberry.com/native/documentation/cascades/ui/lists/list_view_selection.html#indexpaths) for more information.
     *
     * @xmlonly
     * <qml>
     * <class abstract="yes"/>
     * </qml>
     * <apigrouping group="Data management/Data models"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT DataModel : public QObject {
        Q_OBJECT

    public:
        /*!
         * @brief Indicates whether a @c ListView can translate cached items to new indexes.
         *
         * An instance of this class can be sent along with the
         * new indexes class that can be sent along with the @c DataModel::itemsChanged signal so that
         * the listening @c %ListView can translate all of the items in its cache to the new indexes
         * (and won't have to do a full refresh of the items). Items in the @c %ListView cache that
         * have no such translation are removed from the @c %ListView.
         *
         * @xmlonly
         * <apigrouping group="Data management/Data models"/>
         * @endxmlonly
         *
         * @since BlackBerry 10.0.0
         */
        class BBCASCADES_EXPORT IndexMapper {
        public:
            virtual ~IndexMapper();

            /*!
             * @brief Called by @c ListView for every item in its cache in response to the
             * @c DataModel::itemsChanged signal.
             *
             * This function is called only when the @c DataModel::itemsChanged signal is emitted,
             * so the old indexing won't be needed anymore when all listeners to the
             * signal are finished, unless the @c eChangeType argument of the signal
             * is @c INSTANT.
             *
             * @param pOutIndexPath An output parameter. If the return value of this function
             * is @c false, the content of @c *pOutIndexPath is undefined. Otherwise, it's
             * a new index path specifying the placement of the item in question in the
             * model after the update.
             * @param pOutReplacementIndex An output parameter. If the return value of this
             * function is @c true, the value of @c *pOutReplacementIndex is undefined.
             * Otherwise, it's the index amongst its siblings (that is, the last index in
             * the index path) that the item in question would have had in the updated model,
             * had the item not been removed. This parameter affects placement of the
             * item-visuals that are animated out of the list. This parameter can be a
             * negative value if the ItemRemoved-animated visuals can be placed after its
             * parent's remaining children.
             * @param oldIndexPath The index path for listItem before the change in the model.
             *
             * @return @c true if the item in question remains in the model after the update,
             * @c false if the item has been removed.
             *
             * @since BlackBerry 10.0.0
             */
            virtual bool newIndexPath(QVariantList *pOutIndexPath, int *pOutReplacementIndex,
                const QVariantList &oldIndexPath) const = 0;
        };

       /*!
        * @brief Constructs a @c DataModel instance with the specified parent.
        *
        * If the specified parent is not @c 0, the ownership of the constructed @c %DataModel is
        * transferred to the parent.
        *
        * @param parent The data model owner, or @c 0. Optional and will default to @c 0 if not
        * specified.
        *
        * @since BlackBerry 10.0.0
        */
        explicit DataModel(QObject *parent = 0);

        /*!
         * @brief Destructs this @c DataModel.
         *
         * @since BlackBerry 10.0.0
         */
        virtual ~DataModel();

       /*!
        * @brief Returns the number of children to the data item specified by @c indexPath.
        *
        * @param indexPath The index path to the data item to get child count for.
        *
        * @return The number of children.
        *
        * @since BlackBerry 10.0.0
        */
        Q_INVOKABLE virtual int childCount(const QVariantList &indexPath) = 0;

       /*!
        * @brief Indicates whether the data item specified by @c indexPath has children.
        *
        * @c ListView never calls this function for its root node (but does call
        * @c childCount(QVariantList) for the root node), so if this @c DataModel only
        * contains one level of items (no child items), this function can always return
        * @c false.
        *
        * Here's an example of how to override @c hasChildren().
        *
        * @code
        * bool SmartViewModel::hasChildren(const QVariantList &indexPath)
        * {
        *     // Checks whether the indexPath is an empty array.
        *     // An empty array indicates the the index path is for the
        *     // root element.
        *     if(indexPath.empty())
        *         return true; // The root node always has children
        *
        *     // ...Check for other index paths...
        * }
        * @endcode
        *
        * @param indexPath The index path to the data item to query for children.
        *
        * @return @c true if the data item has one or more children, @c false otherwise.
        *
        * @since BlackBerry 10.0.0
        */
        Q_INVOKABLE virtual bool hasChildren(const QVariantList &indexPath) = 0;

       /*!
        * @brief Returns the item type for the data item at @c indexPath.
        *
        * The item type will then be used when the @c ListView requests items from its
        * @c ListItemProvider. It will also be used when the @c DataModel has 
        * indicated that items have been updated using the signals @c DataModel::itemUpdated or
        * @c DataModel::itemsChanged with @c DataModelChangeType::Update.
        *
        * If a @c ListItemTypeMapper has been provided to a @c %ListView, the @c %ListView
        * calls @c ListItemTypeMapper::itemType() instead of @c DataModel::itemType().
        *
        * @param indexPath The index path to the data item.
        *
        * @return A string representing the user-defined type of the item. The
        * default implementation returns an empty string.
        *
        * @since BlackBerry 10.0.0
        */
        Q_INVOKABLE virtual QString itemType(const QVariantList &indexPath);

       /*!
        * @brief Returns the data item that is associated with @c indexPath.
        *
        * This function transfers ownership for @c QObject objects, if the returned
        * object doesn't have any parent.
        *
        * The @c ListView will pass the data item as a parameter to
        * @c ListItemProvider::updateItem(). If item visuals are created by using
        * @c ListItemComponent in QML, @c %ListView makes the data returned from
        * this function available in the item visuals as the context property
        * @c ListItemData, and also as the property @c ListItem.data attached to the
        * item visual root node.
        *
        * @param indexPath The index path to the data item.
        *
        * @return The data item associated with the @c indexPath. The caller
        * must take ownership of any returned @c QObject objects, if the returned
        * object doesn't already have a parent.
        *
        * @see ListItemProvider
        *
        * @since BlackBerry 10.0.0
        */
        Q_INVOKABLE virtual QVariant data(const QVariantList &indexPath) = 0;

    Q_SIGNALS:

       /*!
        * @brief Emitted when a data item has been added to this @c DataModel.
        *
        * @param indexPath The index path to the new item.
        *
        * @since BlackBerry 10.0.0
        */
        void itemAdded(QVariantList indexPath);

       /*!
        * @brief Emitted when a data item in this @c DataModel has been updated.
        *
        * @param indexPath IndexPath to the updated item.
        *
        * @since BlackBerry 10.0.0
        */
        void itemUpdated(QVariantList indexPath);

       /*!
        * @brief Emitted when a data item has been removed from this @c DataModel.
        *
        * @param indexPath The index path to the removed item.
        *
        * @since BlackBerry 10.0.0
        */
        void itemRemoved(QVariantList indexPath);

       /*!
        * @brief Emitted when a data item has been moved within the @c DataModel.
        * 
        * A moved item will retain its visual appearance and data on the server.
        *
        * @param fromIndexPath The original index path of the moved item.
        * @param toIndexPath The new index path of the moved item.
        *
        * @since BlackBerry 10.3.0
        */
        void itemMoved(QVariantList fromIndexPath, QVariantList toIndexPath);

       /*!
        * @brief Emitted when the model has changed in a way that would be inefficient
        * to describe with single instances of the other signals.
        *
        * No other signals (@c DataModel::itemAdded, @c DataModel::itemUpdated, 
        * or @c DataModel::itemRemoved) are emitted if this signal is emitted
        * when a change occurs in this @c DataModel.
        *
        * Typical examples of when this signal is emitted: data has been sorted (so
        * that many items have changed places), the @c %DataModel has been cleared
        * (all items have been removed), or a batch of items has been added.
        *
        * If @c eChangeType is @c DataModelChangeType::Init, or if @c eChangeType
        * is @c DataModelChangeType::AddRemove and @c indexMapper is @c 0, a
        * @c ListView reacts to this signal by releasing all of the items in its cache.
        *
        * If @c eChangeType is @c AddRemove and an @c IndexMapper is provided, the
        * @c %ListView instead calls @c IndexMapper::newIndexPath() for each item in its cache.
        *
        * If @c eChangeType is @c DataModelChangeType::Update, a @c %ListView reacts to
        * this signal by calling @c DataModel::data() again for every item in its
        * cache.
        *
        * @param eChangeType The type of change.
        * @param indexMapper An index mapper that contains update information.
        *
        * @since BlackBerry 10.0.0
        */
        void itemsChanged(bb::cascades::DataModelChangeType::Type eChangeType = bb::cascades::DataModelChangeType::Init,
            QSharedPointer<bb::cascades::DataModel::IndexMapper> indexMapper =
            QSharedPointer<bb::cascades::DataModel::IndexMapper>(0));

    private:
        Q_DISABLE_COPY(DataModel)
    };
}
}

QML_DECLARE_TYPE(bb::cascades::DataModel)

#endif // cascades_datamodel_h
