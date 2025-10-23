/*!
 * @copyright
 * Copyright (C) 2013 BlackBerry Limited. All rights reserved.
 */

#ifndef BB_CASCADES_DATAMANAGER_ASYNCDATAMODEL_HPP_
#define BB_CASCADES_DATAMANAGER_ASYNCDATAMODEL_HPP_

#include <bb/cascades/datamanager/Global>
#include <bb/cascades/datamanager/DataQuery>
#include <bb/cascades/datamanager/HeaderDataQuery>
#include <bb/cascades/datamanager/QueryDataModel>

#include <QObject>
#include <QModelIndex>
#include <QPair>
#include <QVariant>
#include <QVector>

namespace bb
{
namespace cascades
{
namespace datamanager
{

class AsyncDataModelPrivate;

/*!
 * @headerfile AsyncDataModel.hpp <bb/cascades/datamanager/AsyncDataModel>
 *
 * @brief A data model that manages a partial cache of data from the full data set.
 *
 * The @c AsyncDataModel class is a @c DataModel that manages a contiguous cache
 * window over the full result set. The window is moved with asynchronous
 * database operations, based on access to the data using a data query.  If
 * items are accessed outside the current cache window, an empty container
 * is returned, and @c itemUpdated() is called to notify the UI when the data
 * is available.
 *
 * Here is a QML example showing the usage of an @c %AsyncDataModel:
 *
 * @snippet libbbcascadesdatamanager/examples/AsyncDataModel/assets/AsyncDataModelExamples.qml asyncdatamodel1
 *
 * @xmlonly
 * <apigrouping group="Data Management/Large Data Sets"/>
 * <library name="bbcascadesdatamanager"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_CASCADES_DATAMANAGER_EXPORT AsyncDataModel : public QueryDataModel
{
    Q_OBJECT

    /*!
     * @brief The maximum count of data items maintained in the cache.
     *
     * The default capacity is 200 data items.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(int cacheSize READ cacheSize WRITE setCacheSize NOTIFY cacheSizeChanged FINAL)

public:
    /*!
     * @brief Constructs an @c AsyncDataModel.
     *
     * @param parent The parent owner or 0. Optional and defaults to 0 if not specified.
     *
     * @since BlackBerry 10.2.0
     */
    explicit AsyncDataModel(QObject *parent = 0);

    /*!
     * @brief Destructor.
     *
     * @since BlackBerry 10.2.0
     */
    virtual ~AsyncDataModel();

    /*!
     * @brief Set the capacity for the data cache for this model.
     *
     * The default capacity is 200 data items.
     *
     * @param cacheSize The new data cache capacity.
     *
     * @since BlackBerry 10.2.0
     */
    void setCacheSize(int cacheSize);

    /*!
     * @brief Return the current capacity for the data cache for this model.
     *
     * The default capacity is 200 data items.
     *
     * @return The current data cache capacity.
     *
     * @since BlackBerry 10.2.0
     */
    int cacheSize() const;

    /*!
     * @brief Set the data query that this model uses to load data.
     *
     * @note Ownership of the query is taken over by the model and
     * the query is executed in a secondary thread.
     *
     * @param query The data query to use with this data model.
     *
     * @since BlackBerry 10.2.0
     */
    void setQuery(bb::cascades::datamanager::DataQuery *query);

    /*!
     * @brief Return the data query for this model.
     *
     * @return The data query to use with this data model.
     *
     * @since BlackBerry 10.2.0
     */
    bb::cascades::datamanager::DataQuery* query();

    /*!
     * @brief Returns the number of children for the data item specified by @c indexPath.
     *
     * The root item is represented by an empty index path. This example shows
     * how to get the number of top level items (items having the root item
     * as parent):
     *
     * @code
     * int numberOfHeaders = model->childCount(QVariantList());
     * @endcode
     *
     * @param indexPath The path to the data item to get the child count for.
     *
     * @return The number of children. The return value for invalid index paths is undefined.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE virtual int childCount(const QVariantList &indexPath);

    /*!
     * @brief Indicates whether the data item specified by @c indexPath
     * has children.
     *
     * @param indexPath The path to the data item to query for children.
     *
     * @return @c True if the data item has one or more children, @c false otherwise.
     * @c ListView never calls this function for its root node (but does call
     * @c childCount() for the root node), therefore the return value for
     * an empty index path is undefined.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE virtual bool hasChildren(const QVariantList &indexPath);

    /*!
     * @brief Returns the data associated with the specified item.
     *
     * This method does not transfer any ownership, any returned @c QObject is still owned
     * by its parent. A @c %QObject returned by this function always has a parent.
     * The @c ListView will pass on the data as a parameter to @c ListItemProvider::updateItem().
     *
     * @param indexPath The path to the item in the model.
     *
     * @return A @c QVariantMap wrapped in a @c QVariant.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE virtual QVariant data(const QVariantList &indexPath);

    /*!
     * @brief Returns the type for the specified item.
     *
     * @param indexPath The path to the item in the model.
     *
     * @return A string identifying the type for this item.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE virtual QString itemType(const QVariantList &indexPath);


    /*!
     * @brief Load the initial cache of data.
     *
     * After setting the data query and other properties, call this method
     * to load the data.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE void load();

Q_SIGNALS:
    /*!
     * @brief Emitted when the cache capacity for this data model has changed.
     *
     * @ingroup Signals
     *
     * @param cacheSize The new cache capacity.
     *
     * @since BlackBerry 10.2.0
     */
    void cacheSizeChanged(int cacheSize);

protected:
    /*! @cond PRIVATE */
    AsyncDataModel(AsyncDataModelPrivate &dd, QObject *parent = 0);

    Q_DECLARE_PRIVATE(AsyncDataModel)
    Q_DISABLE_COPY(AsyncDataModel)
    /*! @endcond */
};

} // datamanager
} // cascades
} // bb

#endif /* BB_CASCADES_DATAMANAGER_ASYNCDATAMODEL_HPP_ */
