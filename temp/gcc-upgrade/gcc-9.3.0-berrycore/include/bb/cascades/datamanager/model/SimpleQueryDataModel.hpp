/*!
 * @copyright
 * Copyright (C) 2013 BlackBerry Limited. All rights reserved.
 */

#ifndef BB_CASCADES_DATAMANAGER_SIMPLEQUERYDATAMODEL_HPP_
#define BB_CASCADES_DATAMANAGER_SIMPLEQUERYDATAMODEL_HPP_

#include <bb/cascades/datamanager/Global>
#include <bb/cascades/datamanager/QueryDataModel>
#include <bb/cascades/DataModel>

namespace bb
{
namespace cascades
{
namespace datamanager
{

class SimpleQueryDataModelPrivate;

/*!
 * A simple data model that loads data from a @c DataQuery.
 *
 * This data model provides a flat list and does not support hierarchical
 * data.
 *
 * This data model supports automatic update notifications, but in a
 * very simplistic way: all updates force a full reload of the data and
 * notify listeners of a full init each time.
 *
 * Here is a QML example showing the usage of a @c SimpleQueryDataModel:
 *
 * @snippet libbbcascadesdatamanager/examples/SimpleQueryDataModel/assets/SimpleQueryDataModelExamples.qml simplequerydatamodel1
 *
 * @xmlonly
 * <apigrouping group="Data Management/Large Data Sets"/>
 * <library name="bbcascadesdatamanager"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_CASCADES_DATAMANAGER_EXPORT SimpleQueryDataModel: public QueryDataModel
{
Q_OBJECT

public:
    /*!
     * Constructs a @c SimpleQueryDataModel.
     *
     * @param parent The parent owner or 0. Optional and defaults to 0 if not specified.
     *
     * @since BlackBerry 10.2.0
     */
    explicit SimpleQueryDataModel(QObject *parent = 0);

    /*!
     * Destructor.
     *
     * @since BlackBerry 10.2.0
     */
    virtual ~SimpleQueryDataModel();

    /*!
     * @brief Call the @c childCount() method of the @c DataModel being decorated.
     *
     * @param indexPath The path to the data item to get the child count for.
     *
     * @return The number of children. The return value for invalid index paths is undefined.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE virtual int childCount(const QVariantList &indexPath);

    /*!
     * @brief Call the @c hasChildren() method of the @c DataModel being decorated.
     *
     * @param indexPath The path to the data item to query for children.
     *
     * @return @c True if the data item has one or more children, @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE virtual bool hasChildren(const QVariantList &indexPath);

    /*!
     * @brief Call the @c itemType() method of the @c DataModel being decorated.
     *
     * @param indexPath The path to the item in the model.
     *
     * @return A string identifying the type for this item.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE virtual QString itemType(const QVariantList &indexPath);

    /*!
     * @brief Call the @c data() method of the @c DataModel being decorated.
     *
     * @param indexPath The path to the item in the model.
     *
     * @return The data for this item.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE virtual QVariant data(const QVariantList &indexPath);

    /*!
     * @brief Set the data query that this model uses to load data.
     *
     * @note Ownership of the query object is taken over by this model.
     *
     * @param query The data query to use with this data model.
     *
     * @since BlackBerry 10.2.0
     */
    virtual void setQuery(bb::cascades::datamanager::DataQuery *query);

    /*!
     * @brief Get the data query for this model.
     *
     * The data model owns this pointer and destroys it when the data
     * model is destroyed or the query is changed.
     *
     * @return The data query to use with this data model.
     *
     * @since BlackBerry 10.2.0
     */
    virtual bb::cascades::datamanager::DataQuery* query();

    /*!
     * @brief Return the total count of the data items in the model.
     *
     * @return The total count of items.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE int totalSize();

    /*!
     * @brief Loads data.
     *
     * After setting the data query and other properties, call this method
     * to load the data.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE virtual void load();

private:
    /*! @cond PRIVATE */
    Q_DECLARE_PRIVATE(SimpleQueryDataModel);
    Q_DISABLE_COPY(SimpleQueryDataModel);
    /*! @endcond */
};

} // datamanager
} // cascades
} // bb

#endif /* BB_CASCADES_DATAMANAGER_SIMPLEQUERYDATAMODEL_HPP_ */
