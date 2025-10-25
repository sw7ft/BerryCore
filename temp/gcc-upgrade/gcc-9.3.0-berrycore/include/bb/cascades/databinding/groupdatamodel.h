/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_groupdatamodel_h
#define cascades_groupdatamodel_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/databinding/datamodel.h>
#include <bb/cascades/databinding/itemgrouping.h>

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QVariantMap>


namespace bb {
namespace cascades {

    class GroupDataModelPrivate;

    /*!
     *
     * @brief A data model to be used with a @c ListView.
     *
     * A @c %GroupDataModel represents an ordered map of @c QVariantMap objects and/or @c QObject*
     * pointers, to be used as data for @c ListView.
     *
     * Each item in this model is a @c %QVariantMap or a @c %QObject*. The items are ordered by comparing
     * the values of a specified list of keys (property names) in all of the items. The keys are
     * specified on the property @c #sortingKeys. Values are compared in the
     * same order as the keys appear in the @c %sortingKeys list (for example in a contacts
     * list: compare contact last names if first names are equal). If an item in a
     * @c %GroupDataModel lacks the key found first in @c %sortingKeys, or if the value for that
     * key is an empty string, the remaining keys are shifted up in priority
     * until a usable key is found. Example: if @c %sortingKeys = [firstName, lastName, date],
     * and item A and B are compared where A has both firstName and lastName but B
     * only has lastName, the lastName of B would be compared to firstName of A
     * when sorting them. If the lastName of B is equal to the firstName of A the dates
     * would then be compared, since the next property comparison always starts with
     * an equal number of keys skipped for both items. Values of different types are
     * never compared.
     *
     * The key in a @c %QVariantMap is always of the type @c QString. For @c QObject property names,
     * @c QString::toLatin1() is called for the sorting keys. The value used for sorting
     * must be of the same type in all items in @c %GroupDataModel (for that specific key,
     * different keys can have different value types). The @c %GroupDataModel can sort items,
     * using all of these @c QVariant types:
     *
     * @c Char, @c Date, @c DateTime, @c Double, @c Int, @c LongLong, @c String,
     * @c Time, @c UInt, @c ULongLong, @c Url.
     *
     * Items can be automatically grouped, with a header for each group. When grouping is
     * active (when @c #grouping is set to @c ItemGrouping::ByFirstChar or
     * @c ItemGrouping::ByFullValue), only headers are found on the first level of items in
     * the @c %GroupDataModel (first level = items for which the index path is a single index).
     * The non-header items are then children to headers, which means that the non-header
     * items are second level items (have index paths containing two indexes).
     *
     * Normally grouping is done by exact comparison of values. But if the values are
     * @c QString, grouping can be done by only comparing (case insensitive) the first
     * @c QChar in every @c %QString. This behavior is controlled by the @c %grouping property.
     *
     * For the headers, @c GroupDataModel::data() returns a @c QVariant containing the
     * value that all children of that header have in common. In the illustration
     * below, @c GroupDataModel::data() has returned a @c %QVariant containing the
     * @c %QString "A" for the first header, "B" for the second header, and so on.
     *
     * @image html listview_sorted.png A list of names sorted by the first letter
     *
     * The function @c GroupDataModel::itemType() returns @c GroupDataModel::Header
     * ("header") for header items and @c GroupDataModel::Item ("item") for all
     * other items. The example code below shows how a list like the one
     * in the illustration above can be declared in QML, by having one
     * @c ListItemComponent for "header" and one for "item". Also note that
     * @c ListItemData is a @c %QString (there's no properties on it) for headers,
     * but a @c %QVariantMap (with @c %QString properties "firstName" and "lastName")
     * for other items. In this example, the @c %GroupDataModel is assumed to be
     * filled with @c %QVariantMap items from C++.
     *
     * @code
     * ListView {
     *     dataModel: GroupDataModel {
     *         id: theModel
     *         sortingKeys: ["firstName", "lastName"]
     *     }
     *     listItemComponents: [
     *         ListItemComponent {
     *             type: "header"
     *             
     *             Header {
     *                 title: ListItemData
     *             }
     *         },
     *
     *         ListItemComponent {
     *             type: "item"
     *
     *             StandardListItem {
     *                 title: ListItemData.firstName + ' ' + ListItemData.lastName
     *             }
     *         }
     *     ]
     * }
     * @endcode
     *
     * When specifying a certain item in the model (for example as argument to the function
     * @c %GroupDataModel::data(), or the returned value from functions like
     * @c %GroupDataModel::find()), index paths are used. An index path is a @c QVariantList
     * object containing a number of @c QVariant integers, one for each ancestor (including the root
     * item) of the specified item. For an item that is a direct child of the root item,
     * the index path contains a single integer. A child of that item would instead have
     * an index path consisting of two integers, etc.
     *
     * See [Index paths](http://developer.blackberry.com/native/documentation/cascades/ui/lists/list_view_selection.html#indexpaths) for more information.
     *
     * Here's an example of how to create a @c %GroupDataModel with a @c %QVariantMap,
     * and use it in a @c ListView:
     *
     * @code
     * GroupDataModel *model = new GroupDataModel(QStringList() << "country" << "continent");
     *
     * QVariantMap map;
     * map["country"] = "Italy"; map["continent"] = "Europe"; model->insert(map);
     * map["country"] = "Japan"; map["continent"] = "Asia"; model->insert(map);
     * map["country"] = "Egypt"; map["continent"] = "Africa"; model->insert(map);
     *
     * ListView *listView = new ListView();
     * listView->setDataModel(model);
     * @endcode
     *
     * And here's an implementation of a @c %ListItemProvider that could use the
     * @c %GroupDataModel defined in the example above:
     *
     * @code
     * class GroupListItemManager : public ListItemProvider
     * {
     * public:
     *     VisualNode * createItem(ListView* list, QString type)
     *     {
     *         Q_UNUSED(list);
     *
     *         if (type.compare(GroupDataModel::Header) == 0) {
     *             return new Header();
     *         } else {
     *             return new StandardListItem();
     *         }
     *     }
     *
     *     void updateItem(ListView* list, VisualNode *control, QString type,
     *         QVariantList indexPath, QVariant data)
     *     {
     *         Q_UNUSED(list);
     *         Q_UNUSED(indexPath);
     *
     *         if (type.compare(GroupDataModel::Header) == 0) {
     *             QString caption = data.value<QString>();
     *             static_cast<Header*>(control)->setTitle(caption);
     *         } else {
     *             QVariantMap map = data.value<QVariantMap>();
     *             static_cast<StandardListItem*>(control)->setTitle(QString("%1, %2").arg(
     *                 map["country"].toString(), map["continent"].toString()));
     *         }
     *     }
     * };
     * @endcode
     *
     * @c %GroupDataModel also supports the use of @c QObject* pointers. Here's an
     * example of a @c %QObject subclass called @c Person. It contains first name
     * and last name properties, both of which could be displayed in a list item.
     *
     * @code
     * class Person : public QObject {
     *     Q_OBJECT
     *
     *     Q_PROPERTY(QString firstName READ firstName WRITE setFirstName NOTIFY firstNameChanged FINAL)
     *     Q_PROPERTY(QString lastName READ lastName WRITE setLastName NOTIFY lastNameChanged FINAL)
     *
     * public:
     *     Person(QObject *parent = 0) : QObject(parent) {}
     *
     *     Person(QString firstname, QString lastname)
     *         : QObject(), m_firstName(firstname), m_lastName(lastname)
     *     {
     *     }
     *
     *     QString firstName() const {
     *         return m_firstName;
     *     }
     *
     *     QString lastName() const{
     *         return m_lastName;
     *     }
     *
     *     void setFirstName(QString newName) {
     *         if ( newName != m_firstName ) {
     *             m_firstName = newName;
     *             emit firstNameChanged(newName);
     *         }
     *     }
     *
     *     void setLastName(QString newName) {
     *         if ( newName != m_lastName ) {
     *             m_lastName = newName;
     *             emit lastNameChanged(newName);
     *         }
     *     }
     *
     * Q_SIGNALS:
     *     void firstNameChanged(QString firstName);
     *     void lastNameChanged(QString lastName);
     *
     * private:
     *     QString m_firstName;
     *     QString m_lastName;
     *
     *     Q_DISABLE_COPY(Person)
     * };
     * @endcode
     *
     * This is how @c Person objects can be created and added to the @c %GroupDataModel.
     *
     * @code
     * GroupDataModel *model = new GroupDataModel(QStringList() << "firstName" << "lastName");
     *
     * model->insert(new Person ("Wes", "Barichak"));
     * model->insert(new Person ("Mike", "Chepesky"));
     * @endcode
     *
     * @see ListView, DataModel, QListDataModel
     *
     * @xmlonly
     * <qml>
     * <class register="yes"/>
     * <apigrouping group="Data management/Data models"/>
     * </qml>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT GroupDataModel : public DataModel {
        Q_OBJECT

        /*!
         * @brief Determines if and how items are grouped together.
         *
         * The grouping is based on their value for the first sorting key
         * (@c GroupDataModel::sortingKeys) that has a value in that item.
         * The items in each group are made children of a header item constructed
         * from the value that the items have in common.
         * If set to @c ItemGrouping::ByFirstChar, only the first @c QChar in @c QString values is used
         * for comparison when grouping together items, and for creating headers.
         * The default value is @c ByFirstChar.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::ItemGrouping::Type grouping READ grouping WRITE setGrouping NOTIFY groupingChanged FINAL)

        /*!
         * @brief Determines the order in which items are sorted in this @c GroupDataModel.
         *
         * If @c true, items are sorted in ascending order. If @c false, items are
         * sorted in descending order.
         * The default value is @c true.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bool sortedAscending READ isSortedAscending WRITE setSortedAscending NOTIFY sortedAscendingChanged FINAL)

        /*!
         * @brief The sorting keys that are used for this @c GroupDataModel.
         *
         * Item @c QVariantMap objects and @c QObject* pointers in this @c %GroupDataModel are sorted by their values
         * for these keys, in the order they appear on this property. Values
         * for the second key are only compared if values for the first key
         * are equal, etc. If an item in this
         * @c %GroupDataModel lacks the key found first in @c sortingKeys, or if the
         * value for that key is an empty string, the remaining keys
         * are shifted up in priority until a usable key is found.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QStringList sortingKeys READ sortingKeys WRITE setSortingKeys NOTIFY sortingKeysChanged FINAL)

    public:
        /*!
         * @brief The string "item", which is returned by @c itemType() for non-header items.
         *
         * @since BlackBerry 10.0.0
         */
        static const QString Item;

        /*!
         * @brief The string "header", which is returned by @c itemType() for header items.
         *
         * @since BlackBerry 10.0.0
         */
        static const QString Header;

        /*!
        * @brief Constructs an empty @c %GroupDataModel.
        *
        * @param parent The data model owner or @c 0. Optional and defaults to @c 0 if not specified.
         *
         * @since BlackBerry 10.0.0
        */
        explicit GroupDataModel(QObject *parent = 0);

        /*!
        * @brief Constructs an empty @c %GroupDataModel with the specified sorting keys.
        *
        * @code
        * GroupDataModel *model = new GroupDataModel(QStringList() << "firstName" << "lastName");
        * @endcode
        *
        * @param keys A @c QStringList of sorting keys.
        * @param parent The data model owner or @c 0. Optional and defaults to @c 0 if not specified.
         *
         * @since BlackBerry 10.0.0
        */
        explicit GroupDataModel(const QStringList &keys, QObject *parent = 0);

        /*!
        * @brief Constructs a @c %GroupDataModel containing the provided @c QVariantMap items.
        *
        * Also specifies which keys to sort the items by.
        *
        * @code
        * GroupDataModel *model = new GroupDataModel(items, keys);
        * @endcode
        *
        * @param initialItems A list of items that the @c %GroupDataModel should contain.
        * @c %GroupDataModel does not take ownership of any content.
        * @param keys A @c QStringList of sorting keys.
        * @param parent The data model owner or @c 0. Optional and defaults to @c 0 if not specified.
         *
         * @since BlackBerry 10.0.0
        */
        GroupDataModel(const QList<QVariantMap> &initialItems, const QStringList &keys, QObject *parent = 0);

        virtual ~GroupDataModel();

        /*!
         * @brief Returns the number of children for the data item specified by the @c indexPath.
         *
         * The root item is represented by an empty index path. This example shows
         * how to get the number of top level items (items having the root item
         * as parent) in a @c %GroupDataModel:
         *
         * @code
         * int numberOfHeaders = model->childCount(QVariantList());
         * @endcode
         *
         * @param indexPath The path to the data item to get child count for. See [Index paths](http://developer.blackberry.com/native/documentation/cascades/ui/lists/list_view_selection.html#indexpaths) for more information.
         * 
         * @return The number of children. The return value for invalid index paths is undefined.
         *
         * @since BlackBerry 10.0.0
         */
        virtual int childCount(const QVariantList &indexPath);

        /*!
         * @brief Indicates whether the data item specified by the @c indexPath
         * has children.
         *
         * @param indexPath The path to the data item to query for children. See [Index paths](http://developer.blackberry.com/native/documentation/cascades/ui/lists/list_view_selection.html#indexpaths) for more information.
		 * 
         * @return @c true if the data item has one or more children, @c false otherwise.
         * @c ListView never calls this function for its root node (but does call
         * @c childCount() for the root node), therefore the return-value for
         * an empty index path is undefined.
         *
         * @since BlackBerry 10.0.0
         */
        virtual bool hasChildren(const QVariantList &indexPath);

        /*!
        * @brief Returns the data associated with the specified item.
        *
        * Does not transfer any ownership, any returned @c QObject is still owned
        * by its parent. A @c QObject returned by this function always have a parent.
        * The ListView will pass on the data as a parameter to ListItemProvider::updateItem().
        *
        * @param indexPath The path to the item in the model.
        *        See [Index paths](http://developer.blackberry.com/native/documentation/cascades/ui/lists/list_view_selection.html#indexpaths) for more information.
        * 
        * @return A @c QVariantMap or @c QObject* (one of those inserted into
        * this model) wrapped in a @c QVariant, or @c QVariant::Invalid if the argument
        * @c indexPath is invalid.
         *
         * @since BlackBerry 10.0.0
        */
        virtual QVariant data(const QVariantList &indexPath);

        /*!
        * @brief Returns the type for the specified item.
        *
        * @param indexPath The path to the item in the model.
        *        See [Index paths](http://developer.blackberry.com/native/documentation/cascades/ui/lists/list_view_selection.html#indexpaths) for more information.
        * 
        * @return @c GroupDataModel::Header for any headers and @c GroupDataModel::Item
        * for the actual items.
         *
         * @since BlackBerry 10.0.0
        */
        virtual QString itemType(const QVariantList &indexPath);

        /*!
        * @brief Gets the current value of @c GroupDataModel::grouping.
        *
        * @return The current value of the property @c grouping.
        *
        * @see setGrouping()
         *
         * @since BlackBerry 10.0.0
        */
        bb::cascades::ItemGrouping::Type grouping() const;

        /*!
        * @brief Sets the value of @c GroupDataModel::grouping.
        *
        * Emits the signal @c groupingChanged() if the new property value differs
        * from the old one.
        *
        * @param itemGrouping The new value for the property @c grouping.
        *
        * @see grouping()
         *
         * @since BlackBerry 10.0.0
        */
        Q_SLOT void setGrouping(bb::cascades::ItemGrouping::Type itemGrouping);

        /*!
         * @brief Gets the current value of @c GroupDataModel::sortedAscending.
         *
         * @return @c true if items are sorted in ascending order, @c false if
         * items are sorted in descending order.
         *
         * @see setSortedAscending()
         *
         * @since BlackBerry 10.0.0
         */
        bool isSortedAscending() const;

        /*!
         * @brief Sets the value of @c GroupDataModel::sortedAscending.
         *
         * Emits the signal @c sortedAscendingChanged() if the new property value differs
         * from the old one.
         *
         * @param ascending @c true if items should be sorted in ascending order,
         * @c false if items should be sorted in descending order.
         *
         * @see isSortedAscending()
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setSortedAscending(bool ascending);

        /*!
         * @brief Gets the value of @c GroupDataModel::sortingKeys.
         *
         * @return A list of the keys specified for sorting, in the order they are used.
         *
         * @see setSortingKeys()
         *
         * @since BlackBerry 10.0.0
         */
        QStringList sortingKeys() const;

        /*!
        * @brief Sets the value of @c GroupDataModel::sortingKeys.
        *
        * Emits the signal @c sortingKeysChanged() if the new property value differs
        * from the old one.
        *
        * If an item in this @c %GroupDataModel lacks the specified key, or if the
        * value for that key is an empty string, any remaining keys are
        * shifted up in priority until a usable key is found. This behavior
        * happens in all internal item comparison in @c %GroupDataModel.
        *
        * @param keys Items (@c QVariantMap and/or @c QObject*) in this @c %GroupDataModel
        * are sorted by their values for these keys.
        *
        * @see sortingKeys()
         *
         * @since BlackBerry 10.0.0
        */
        Q_SLOT void setSortingKeys(const QStringList &keys);

        /*!
        * @brief Inserts a @c QObject* into the @c %GroupDataModel.
        *
        * @c %GroupDataModel listens to changes in the object properties defined
        * by GroupDataModel::sortingKeys, if the object emits notification-signals for them.
        * @c %GroupDataModel emits the DataModel::itemUpdated() signal when needed, and moves
        * items if changes in their property values affect the sorting order.
        *
        * @param object @c QObject* to be inserted. If object has no parent, this
        * @c %GroupDataModel takes ownership of it. Otherwise the caller must ensure
        * that object stays alive for as long as this @c %GroupDataModel is alive.
        * Must not be @c 0, but the same object can be inserted more than once.
         *
         * @since BlackBerry 10.0.0
        */
        Q_SLOT void insert(QObject *object);

        /*!
        * @brief Inserts a @c QVariantMap into the @c %GroupDataModel.
        *
        * @param item @c QVariantMap to be inserted. Ownership of the content in
        * item is not transferred to @c %GroupDataModel.
         *
         * @since BlackBerry 10.0.0
        */
        Q_SLOT void insert(const QVariantMap &item);

        /*!
        * @brief Inserts a @c QVariantList into the @c %GroupDataModel. The items of the
        * list are QVariants which contain either a @c QVariantMap or @c QObject*.
        * The two types cannot be mixed in the same list.
        *
        * @param items Either a list of @c QVariantMap or list of @c QObject* to
        * be inserted. Ownership of the content of QVariantMaps is not transferred
        * to @c %GroupDataModel. If QObject* items have no parent, this
        * @c %GroupDataModel takes ownership of those items.
         *
         * @since BlackBerry 10.0.0
        */
        Q_SLOT void insertList(const QVariantList &items);

        /*!
        * @brief Inserts a list of @c QVariantMap into the @c %GroupDataModel.
        *
        * @param items List of @c QVariantMap to be inserted. Ownership of the content
        * in each item is not transferred to @c %GroupDataModel.
         *
         * @since BlackBerry 10.0.0
        */
        Q_INVOKABLE void insertList(const QList<QVariantMap> &items);

        /*!
        * @brief Inserts a list of @c QObject* into the @c %GroupDataModel.
        *
        * @param items List of @c QObject* to be inserted. If an object has no parent,
        * this @c %GroupDataModel takes ownership of it. Otherwise the caller must
        * ensure that object stays alive for as long as this @c %GroupDataModel is alive.
        * Must not be @c 0, but the same object can be inserted more than once.
         *
         * @since BlackBerry 10.0.0
        */
        void insertList(const QList<QObject*> &items);

        /*!
         * @brief Removes the item specified by the index path.
         *
         * Trying to remove a header has no effect.
         *
         * Emits the signal DataModel::itemRemoved() if an item is successfully removed.
         *
         * If the item to remove contains a @c QObject* that @c %GroupDataModel owns
         * (is parent of) and there is only one item in this @c %GroupDataModel
         * containing that object, then that object is destroyed.
         *
         * @param indexPath The index path for the item to remove. See [Index paths](http://developer.blackberry.com/native/documentation/cascades/ui/lists/list_view_selection.html#indexpaths) for more information.
         * @return @c true if an item was removed, @c false otherwise
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT bool removeAt(const QVariantList &indexPath);

        /*!
         * @brief Removes the first item found in this @c %GroupDataModel that is
         * identical (as described in findExact()) to the supplied item.
         *
         * Emits the signal DataModel::itemRemoved() if an item is successfully removed.
         *
         * @param object Item to remove. If this @c %GroupDataModel owns (is parent of) object and
         * there is only one item in this @c %GroupDataModel containing object, then object is destroyed.
         * @return @c true if an item was removed, @c false otherwise.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT bool remove(QObject *object);

        /*!
         * @brief Removes the first item found in this @c %GroupDataModel that is
         * identical (as described in findExact()) to the supplied item.
         *
         * Emits the signal DataModel::itemRemoved() if an item is successfully removed.
         *
         * @param item Item to remove.
         * @return @c true if an item was removed.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT bool remove(const QVariantMap &item);

        /*!
         * @brief Replaces the item on the specified index path with the supplied @c QObject*.
         *
         * Causes the @c %GroupDataModel to either emit the signal DataModel::itemUpdated()
         * (if the item wasn't updated in a way that caused it to change position) or to
         * first emit DataModel::itemRemoved() and then DataModel::itemAdded().
         *
         * If the existing item contains a @c QObject* that @c %GroupDataModel owns
         * (is parent of) and there is only one item in this @c %GroupDataModel
         * containing that object, then that object is destroyed.
         *
         * @param indexPath Index path for the item that is to be updated.
         *        See [Index paths](http://developer.blackberry.com/native/documentation/cascades/ui/lists/list_view_selection.html#indexpaths) for more information.
         * @param object A @c QObject* that is to replace the existing one on indexPath.
         * If the supplied object doesn't have a parent, then this @c %GroupDataModel
         * takes ownership of it. Which means that the object is destroyed when
         * no longer needed by this @c %GroupDataModel.
         * @return @c true if the item was successfully updated, @c false if indexPath is invalid.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT bool updateItem(const QVariantList &indexPath, QObject *object);

        /*!
         * @brief Replaces the item on the specified index path with the supplied @c QVariantMap.
         *
         * Causes the @c %GroupDataModel to either emit the signal DataModel::itemUpdated()
         * (if the item wasn't updated in a way that caused it to change position) or to
         * first emit DataModel::itemRemoved() and then DataModel::itemAdded().
         *
         * If the existing item contains a @c QObject* that @c %GroupDataModel owns
         * (is parent of) and there is only one item in this @c %GroupDataModel
         * containing that object, then that object is destroyed.
         *
         * @param indexPath Index path for the item that is to be updated.
         *        See [Index paths](http://developer.blackberry.com/native/documentation/cascades/ui/lists/list_view_selection.html#indexpaths) for more information.
         * @param item A @c QVariantMap that is to replace the existing one on indexPath.
         * @return @c true if the item was successfully updated, @c false if indexPath is invalid.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT bool updateItem(const QVariantList &indexPath, const QVariantMap &item);

        /*!
         * @brief Removes all items from this @c %GroupDataModel.
         *
         * Destroys all items of type @c QObject* that this @c %GroupDataModel owns (is parent of).
         *
         * Emits DataModel::itemsChanged().
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void clear();

        /*!
        * @brief Checks if the @c %GroupDataModel is empty.
        *
        * @return @c true if the model doesn't contain any items, @c false otherwise.
         *
         * @since BlackBerry 10.0.0
        */
        Q_INVOKABLE bool isEmpty() const;

        /*!
        * @brief Returns the number of items in this @c %GroupDataModel. In case headers are
        * enabled, the number of headers are excluded from the result.
        *
        * @return Number of (non-header) items in this @c %GroupDataModel.
         *
         * @since BlackBerry 10.0.0
        */
        Q_INVOKABLE int size() const;

        /*!
         * @brief Returns an index path to the first item.
         *
         * Useful when iterating through the items in this @c %GroupDataModel.
         *
         * Example:
         *
         * @code
         * for ( QVariantList indexPath = model->first(); !indexPath.isEmpty();
         *     indexPath = model->after(indexPath) )
         * {
         *     QVariant item = model->data(indexPath);
         *     // Do something with the item here.
         * }
         * @endcode
         *
         * @return An index path to the item placed first according to current
         * sorting settings (ignoring header items). Possible values are [0]
         * (if headers are disabled), [0, 0] (if headers are enabled) or
         * an empty @c QVariantList if this @c %GroupDataModel is empty.
         * See [Index paths](http://developer.blackberry.com/native/documentation/cascades/ui/lists/list_view_selection.html#indexpaths) for more information.
         *
         * @see last(), before(), after()
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE QVariantList first() const;

        /*!
         * @brief Returns an index path to the last item.
         *
         *
         * Useful when iterating through the items in this @c %GroupDataModel.
         *
         * Example:
         *
         * @code
         * for ( QVariantList indexPath = model->last(); !indexPath.isEmpty();
         *     indexPath = model->before(indexPath) )
         * {
         *     QVariant item = model->data(indexPath);
         *     // Do something with the item here.
         * }
         * @endcode
         *
         * @return An index path to the item placed last according to current
         * sorting settings (ignoring header items). Returns an empty
         * @c QVariantList if this @c %GroupDataModel is empty. See [Index paths](http://developer.blackberry.com/native/documentation/cascades/ui/lists/list_view_selection.html#indexpaths) for more information.
         *
         * @see first(), before(), after()
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE QVariantList last() const;

        /*!
         * @brief Returns an index path to the item placed before the specified one.
         *
         * Headers are ignored. The order is decided by current sorting settings.
         *
         * Useful when iterating through the items in this @c %GroupDataModel.
         *
         * Example:
         *
         * @code
         * for ( QVariantList indexPath = model->last(); !indexPath.isEmpty();
         *     indexPath = model->before(indexPath) )
         * {
         *     QVariant item = model->data(indexPath);
         *     // Do something with the item here.
         * }
         * @endcode
         *
         * @param indexPath An index path specifying the item right after the
         * requested one (ignoring headers). See [Index paths](http://developer.blackberry.com/native/documentation/cascades/ui/lists/list_view_selection.html#indexpaths) for more information.
         * @return An index path to the item placed before the one specified by
         * indexPath, ignoring headers. Or an empty @c QVariantList if no such
         * item exists.
         *
         * @see first(), last(), after()
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE QVariantList before(const QVariantList &indexPath) const;

        /*!
         * @brief Returns an index path to the item placed after the specified one.
         *
         * Headers are ignored. The order is decided by current sorting settings.
         *
         * Useful when iterating through the items in this @c %GroupDataModel.
         *
         * Example:
         *
         * @code
         * for ( QVariantList indexPath = model->first(); !indexPath.isEmpty();
         *     indexPath = model->after(indexPath) )
         * {
         *     QVariant item = model->data(indexPath);
         *     // Do something with the item here.
         * }
         * @endcode
         *
         * @param indexPath An index path specifying the item right before the
         * requested one (ignoring headers). See [Index paths](http://developer.blackberry.com/native/documentation/cascades/ui/lists/list_view_selection.html#indexpaths) for more information.
         * @return An index path to the item placed after the one specified by
         * indexPath, ignoring headers. Or an empty @c QVariantList if no such
         * item exists.
         *
         * @see first(), last(), before()
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE QVariantList after(const QVariantList &indexPath) const;

        /*!
         * @brief Finds the index path for the first item in this @c %GroupDataModel
         * with property values matching the supplied ones.
         *
         * If the number of values supplied to this function is less than the
         * number of keys in GroupDataModel::sortingKeys, items that have values
         * for all @c %sortingKeys won't be found by this function. For example,
         * if @c %sortingKeys = ["firstName", "lastName"], no item that has values
         * for both "firstName" and "lastName" can be found by calling this function
         * with a single value as argument. For use cases like that, lowerBound()
         * should be called instead.
         *
         * @param values The search aims to find an item for which the values of
         * the properties specified by GroupDataModel::sortingKeys equals these values.
         * If an item in this @c %GroupDataModel lacks one of the keys, or if the
         * value for that key is an empty string, any remaining keys are
         * shifted up in priority until a usable key is found.
         * @return If no item matching the arguments is found, an empty
         * @c QVariantList is returned. Otherwise an index path for a valid item
         * (not a header) is returned.
         *
         * @see findExact(), lowerBound(), upperBound()
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE QVariantList find(const QVariantList &values) const;

        /*!
         * @brief Finds the index path for the first item in this @c %GroupDataModel
         * that matches the supplied @c QObject*.
         *
         * @param object The search aims to find an item that according to
         * current sorting settings (the property GroupDataModel::sortingKeys) is equal to object.
         * @return If no item matching the arguments is found, an empty
         * @c QVariantList is returned. Otherwise an index path for a valid item
         * (not a header) is returned. See [Index paths](http://developer.blackberry.com/native/documentation/cascades/ui/lists/list_view_selection.html#indexpaths) for more information.
         *
         * @see findExact(), lowerBound(), upperBound()
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE QVariantList find(QObject *object) const;

        /*!
         * @brief Finds the index path for the first item in this @c %GroupDataModel*
         * that matches the supplied @c QVariantMap.
         *
         * @param matchMap The search aims to find an item that according to
         * current sorting settings (the property GroupDataModel::sortingKeys) is equal to matchMap.
         * @return If no item matching the arguments is found, an empty
         * @c QVariantList is returned. Otherwise an index path for a valid item
         * (not a header) is returned. See [Index paths](http://developer.blackberry.com/native/documentation/cascades/ui/lists/list_view_selection.html#indexpaths) for more information.
         *
         * @see findExact(), lowerBound(), upperBound()
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE QVariantList find(const QVariantMap &matchMap) const;

        /*!
         * @brief Finds the index path for the first occurrence of the supplied object in this @c %GroupDataModel.
         *
         * @param object The object to find. The search aims to find this exact
         * object instance, and not just an object with the same property values.
         * @return If no item containing object is found, an empty
         * @c QVariantList is returned. Otherwise an index path for a valid item
         * (not a header) is returned. See [Index paths](http://developer.blackberry.com/native/documentation/cascades/ui/lists/list_view_selection.html#indexpaths) for more information.
         *
         * @see find(), lowerBound(), upperBound()
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE QVariantList findExact(QObject *object) const;

        /*!
         * @brief Finds the index path for the first item in this @c %GroupDataModel that is == matchMap.
         *
         * @param matchMap The search aims to find an item that returns @c true
         * when doing a == comparison to matchMap. Which means that all properties
         * must have exactly the same values on the two maps, not only the
         * properties defined by GroupDataModel::sortingKeys.
         * @return If no item matching the arguments is found, an empty
         * @c QVariantList is returned. Otherwise an index path for a valid item
         * (not a header) is returned. See [Index paths](http://developer.blackberry.com/native/documentation/cascades/ui/lists/list_view_selection.html#indexpaths) for more information.
         *
         * @see find(), lowerBound(), upperBound()
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE QVariantList findExact(const QVariantMap &matchMap) const;

        /*!
         * @brief Finds the index path for the first item in this @c %GroupDataModel
         * that would not have been placed before an item having the supplied
         * property values (which means that the found item might have property
         * values identical to the supplied ones).
         *
         * Example showing how to in a ListView using a @c %GroupDataModel scroll
         * to the first item that has a value starting with the letter "M", or
         * any letter after "M" if no such item is found in the @c %GroupDataModel.
         *
         * @code
         * listView->scrollToItem(model->lowerBound(QVariantList() << "M");
         * @endcode
         *
         * @param values The search aims to find the first item for which the values of
         * the properties specified by GroupDataModel::sortingKeys would cause
         * it to be placed after an item having these values on the same properties.
         * If an item in this @c %GroupDataModel lacks the specified key, or if the
         * value for that key is an empty string, any remaining keys are
         * shifted up in priority until a usable key is found.
         * @return If no item matching the arguments is found, an empty
         * @c QVariantList is returned. Otherwise an index path for a valid item
         * (not a header) is returned. See [Index paths](http://developer.blackberry.com/native/documentation/cascades/ui/lists/list_view_selection.html#indexpaths) for more information.
         *
         * @see find(), findExact(), upperBound()
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE QVariantList lowerBound(const QVariantList &values) const;

        /*!
         * @brief Finds the first item in this @c %GroupDataModel that would not have been
         * placed before the supplied one (which means that the found item
         * might be identical to the supplied one).
         *
         * Example showing how to get the index path for the first item in the
         * @c %GroupDataModel "model" that will be pushed down in the list if
         * the @c QObject* "newItem" is inserted into the model.
         *
         * @code
         * QVariantList() firstPushedDown = model->lowerBound(newItem);
         * @endcode
         *
         * @param object The search aims to find the first item in this
         * @c %GroupDataModel that would not have been placed before object,
         * using the current sorting settings on this @c %GroupDataModel.
         * @return If no item matching the arguments is found, an empty
         * @c QVariantList is returned. Otherwise an index path for a valid item
         * (not a header) is returned. See [Index paths](http://developer.blackberry.com/native/documentation/cascades/ui/lists/list_view_selection.html#indexpaths) for more information.
         *
         * @see find(), findExact(), upperBound()
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE QVariantList lowerBound(QObject *object) const;

        /*!
         * @brief Finds the first item in this @c %GroupDataModel that would not have been
         * placed before the supplied one (which means that the found item
         * might be identical to the supplied one).
         *
         * Example showing how to get the index path for the first item in the
         * @c %GroupDataModel "model" that will be pushed down in the list if
         * the @c QVariantMap "newItem" is inserted into the model.
         *
         * @code
         * QVariantList() firstPushedDown = model->lowerBound(newItem);
         * @endcode
         *
         * @param matchMap The search aims to find the first item in this
         * @c %GroupDataModel that would not have been placed before matchMap,
         * using the current sorting settings on this @c %GroupDataModel.
         * @return If no item matching the arguments is found, an empty
         * @c QVariantList is returned. Otherwise an index path for a valid item
         * (not a header) is returned. See [Index paths](http://developer.blackberry.com/native/documentation/cascades/ui/lists/list_view_selection.html#indexpaths) for more information.
         *
         * @see find(), findExact(), upperBound()
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE QVariantList lowerBound(const QVariantMap &matchMap) const;

        /*!
         * @brief Finds the first item in this @c %GroupDataModel that would not have been
         * placed before an item having the supplied property values, and also
         * doesn't have property values identical to the supplied ones.
         *
         * Example showing how to iterate through all items in the
         * @c %GroupDataModel "model" having the values "Tom" and "Hanks" for
         * the keys specified by GroupDataModel::sortingKeys:
         *
         * @code
         * QVariantList endIndexPath = model->upperBound(QVariantList() << "Tom" << "Hanks");
         *
         * for ( QVariantList indexPath = model->lowerBound(QVariantList() << "Tom" << "Hanks");
         *     indexPath != endIndexPath; indexPath = model->after(indexPath) )
         * {
         *     QVariant item = model->data(indexPath);
         *     // Do something with the item here.
         * }
         * @endcode
         *
         * @param values The search aims to find the first item for which the values of
         * the properties specified by GroupDataModel::sortingKeys are not identical
         * to the supplied ones and would cause the item to be placed after an item
         * having these values on the same properties.
         * If an item in this @c %GroupDataModel lacks the specified key, or if the
         * value for that key is an empty string, any remaining keys are
         * shifted up in priority until a usable key is found.
         * @return If no item matching the arguments is found, an empty
         * @c QVariantList is returned. Otherwise an index path for a valid item
         * (not a header) is returned. See [Index paths](http://developer.blackberry.com/native/documentation/cascades/ui/lists/list_view_selection.html#indexpaths) for more information.
         *
         * @see find(), findExact(), lowerBound()
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE QVariantList upperBound(const QVariantList &values) const;

        /*!
         * @brief Finds the first item in this @c %GroupDataModel that would not have been
         * placed before the supplied one, and also doesn't have identical
         * property values for the sorting keys.
         *
         * Example showing how to iterate through all items in the
         * @c %GroupDataModel "model" having the same values as the
         * @c QObject* "myItem" for the keys specified by GroupDataModel::sortingKeys:
         *
         * @code
         * QVariantList endIndexPath = model->upperBound(myItem);
         *
         * for ( QVariantList indexPath = model->lowerBound(myItem);
         *     indexPath != endIndexPath; indexPath = model->after(indexPath) )
         * {
         *     QVariant item = model->data(indexPath);
         *     // Do something with the item here.
         * }
         * @endcode
         *
         * @param object The search aims to find the first item in this
         * @c %GroupDataModel that would not have been placed before object
         * (and also is not considered equal), using the current sorting
         * settings on this @c %GroupDataModel.
         * @return If no item matching the arguments is found, an empty
         * @c QVariantList is returned. Otherwise an index path for a valid item
         * (not a header) is returned. See [Index paths](http://developer.blackberry.com/native/documentation/cascades/ui/lists/list_view_selection.html#indexpaths) for more information.
         *
         * @see find(), findExact(), lowerBound()
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE QVariantList upperBound(QObject *object) const;

        /*!
         * @brief Finds the first item in this @c %GroupDataModel that would not have been
         * placed before the supplied one, and also doesn't have identical
         * property values for the sorting keys.
         *
         * Example showing how to iterate through all items in the
         * @c %GroupDataModel "model" having the same values as the
         * @c QVariantMap "myItem" for the keys specified by GroupDataModel::sortingKeys:
         *
         * @code
         * QVariantList endIndexPath = model->upperBound(myItem);
         *
         * for ( QVariantList indexPath = model->lowerBound(myItem);
         *     indexPath != endIndexPath; indexPath = model->after(indexPath) )
         * {
         *     QVariant item = model->data(indexPath);
         *     // Do something with the item here.
         * }
         * @endcode
         *
         * @param matchMap The search aims to find the first item in this
         * @c %GroupDataModel that would not have been placed before matchMap
         * (and also is not considered equal), using the current sorting
         * settings on this @c %GroupDataModel.
         * @return If no item matching the arguments is found, an empty
         * @c QVariantList is returned. Otherwise an index path for a valid item
         * (not a header) is returned. See [Index paths](http://developer.blackberry.com/native/documentation/cascades/ui/lists/list_view_selection.html#indexpaths) for more information.
         *
         * @see find(), findExact(), lowerBound()
         *
         * @since BlackBerry 10.0.0
         */
        Q_INVOKABLE QVariantList upperBound(const QVariantMap &matchMap) const;

        /*!
         * @brief Returns a list of all @c QVariantMap objects contained by this %GroupDataModel,
         * in current sorting order.
         *
         * The @c QObject* items are returned as @c QVariantMap objects containing
         * property values for the keys specified by GroupDataModel::sortingKeys.
         *
         * @return A list containing all items (except headers).
         *
         * @since BlackBerry 10.0.0
         */
        QList<QVariantMap> toListOfMaps() const;

        /*!
         * @brief Returns a list of all @c QObject* pointers contained by this %GroupDataModel,
         * in current sorting order.
         *
         * The value for @c QVariantMap items is @c 0. The ownership of item objects
         * is not changed by this function (any objects owned by this @c %GroupDataModel
         * remain owned by this @c %GroupDataModel even if the objects are included
         * in the list returned by this function).
         *
         * @return A list containing all items (except headers).
         *
         * @since BlackBerry 10.0.0
         */
        QList<QObject*> toListOfObjects() const;

    Q_SIGNALS:
        /*!
         * @brief Emitted when @c GroupDataModel::grouping is changed.
         *
         * @param newGrouping The new value for @c GroupDataModel::grouping.
         *
         * @since BlackBerry 10.0.0
         */
        void groupingChanged(bb::cascades::ItemGrouping::Type newGrouping);

        /*!
         * @brief Emitted when @c GroupDataModel::sortedAscending is changed.
         *
         * @param sortedAscending @c true if items now will be sorted in ascending
         * order, @c false if items now will be sorted in descending order.
         *
         * @since BlackBerry 10.0.0
         */
        void sortedAscendingChanged(bool sortedAscending);

        /*!
         * @brief Emitted when @c GroupDataModel::sortingKeys is changed.
         *
         * @param sortingKeys The new keys to sort items by.
         *
         * @since BlackBerry 10.0.0
         */
        void sortingKeysChanged(QStringList sortingKeys);

    private:
        /*! @cond PRIVATE */
        GroupDataModelPrivate* const d_ptr;
        Q_DECLARE_PRIVATE(GroupDataModel)
        Q_DISABLE_COPY(GroupDataModel)
        /*! @endcond */
    };
}
}

QML_DECLARE_TYPE(bb::cascades::GroupDataModel)

#endif // cascades_groupdatamodel_h

