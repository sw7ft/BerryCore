/*!
 * @copyright
 * Copyright (C) 2013 BlackBerry Limited. All rights reserved.
 */

#ifndef BB_CASCADES_DATAMANAGER_QUERYDATAMODEL_HPP_
#define BB_CASCADES_DATAMANAGER_QUERYDATAMODEL_HPP_

#include <bb/cascades/datamanager/Global>
#include <bb/cascades/datamanager/DataQuery>
#include <bb/cascades/DataModel>
#include <QObject>

namespace bb
{
namespace cascades
{
namespace datamanager
{

class QueryDataModelPrivate;

/*!
 * @headerfile QueryDataModel.hpp <bb/cascades/datamanager/QueryDataModel>
 *
 * @brief A data model that loads its data from a @c DataQuery.
 *
 * The @c QueryDataModel class is the base class for data models which
 * can use a @c DataQuery to allow them to query and load data.
 *
 * @xmlonly
 * <apigrouping group="Data Management/Large Data Sets"/>
 * <library name="bbcascadesdatamanager"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_CASCADES_DATAMANAGER_EXPORT QueryDataModel : public bb::cascades::DataModel
{
    Q_OBJECT

    /*!
     * @brief The data query to use for obtaining data.
     * @note Ownership of the query object is taken over by this model.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bb::cascades::datamanager::DataQuery* query READ query WRITE setQuery NOTIFY queryChanged)

public:
    /*!
     * @brief Constructs a @c QueryDataModel.
     *
     * @param parent The parent owner or 0. Optional and defaults to 0 if not specified.
     *
     * @since BlackBerry 10.2.0
     */
    explicit QueryDataModel(QObject *parent = 0);

    /*!
     * @brief Destructor.
     *
     * @since BlackBerry 10.2.0
     */
    virtual ~QueryDataModel();

    /*!
     * @brief Set the data query that this model uses to load data.
     *
     * @note Ownership of the query object is taken over by this model.
     *
     * @param query The data query to use with this data model.
     *
     * @since BlackBerry 10.2.0
     */
    virtual void setQuery(bb::cascades::datamanager::DataQuery *query) = 0;

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
    virtual bb::cascades::datamanager::DataQuery* query() = 0;

    /*!
     * @brief Loads data.
     *
     * After setting the data query and other properties, call this method
     * to load the data.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE virtual void load() = 0;

Q_SIGNALS:
    /*!
     * @brief Emitted when the query has changed.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.2.0
     */
    void queryChanged();

    /*!
     * @brief Emitted when the @c DataModel is first loaded after calling the @c load() method.
     *
     * The number of @c loaded() signals may not equal the number of @c load() method calls but it's always
     * guaranteed that a call to @c %load() results in a @c %loaded() signal being emitted. For example, two
     * consecutive @c %load() method calls could result in only one @c %loaded() signal.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.2.0
     */
    void loaded();

protected:
    /*! @cond PRIVATE */
    QueryDataModel(QueryDataModelPrivate &dd, QObject *parent = 0);
    QueryDataModelPrivate * const d_ptr;

    Q_DECLARE_PRIVATE(QueryDataModel)
    Q_DISABLE_COPY(QueryDataModel)
    /*! @endcond */
};

} // datamanager
} // cascades
} // bb


#endif /* BB_CASCADES_DATAMANAGER_QUERYDATAMODEL_HPP_ */
