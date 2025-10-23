/*!
 * @copyright
 * Copyright (C) 2013 BlackBerry Limited. All rights reserved.
 */

#ifndef BB_CASCADES_DATAMANAGER_DATAQUERYDECORATOR_HPP_
#define BB_CASCADES_DATAMANAGER_DATAQUERYDECORATOR_HPP_

#include <bb/cascades/datamanager/Global>
#include <bb/cascades/datamanager/HeaderDataQuery>

namespace bb
{
namespace cascades
{
namespace datamanager
{

class DataQueryDecoratorPrivate;

/*!
 * @headerfile DataQueryDecorator.hpp <bb/cascades/datamanager/DataQueryDecorator>
 *
 * @brief A @c DataQuery wrapper that extends the behavior of existing queries.
 *
 * To use this wrapper, override the @c processResults() or @c processHeaderResults() method(s) and
 * modify the data prior to it being returned by the underlying query.
 *
 * Here is a QML example showing the usage of a @c DataQueryDecorator:
 *
 * @snippet libbbcascadesdatamanager/examples/DataQueryDecorator/assets/DataQueryDecoratorExamples.qml dataquerydecorator1
 *
 * @xmlonly
 * <apigrouping group="Data Management/Large Data Sets"/>
 * <library name="bbcascadesdatamanager"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_CASCADES_DATAMANAGER_EXPORT DataQueryDecorator : public HeaderDataQuery
{
    Q_OBJECT

    /*!
     * @brief The query to be decorated. This decorator takes ownership of the query.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bb::cascades::datamanager::DataQuery *query READ query WRITE setQuery NOTIFY queryChanged)

public:
    /*!
     * @brief Constructs a @c DataQueryDecorator given a @c DataQuery to decorate.
     *
     * @param query The query to be decorated. This decorator takes ownership of the query.
     * @param parent The parent owner or 0. Optional and defaults to 0 if not specified.
     *
     * @since BlackBerry 10.2.0
     */
    explicit DataQueryDecorator(DataQuery* query, QObject *parent = 0);

    /*!
     * @brief Constructs a @c DataQueryDecorator.
     *
     * @param parent The parent owner or 0. Optional and defaults to 0 if not specified.
     *
     * @since BlackBerry 10.2.0
     */
    explicit DataQueryDecorator(QObject *parent = 0);

    /*!
     * @brief Destructor.
     *
     * @since BlackBerry 10.2.0
     */
    virtual ~DataQueryDecorator();

    /*!
     * @brief Fetch the overall revision, total count, and a range of data items from the data source.
     *
     * This is a synchronous call, but it must be possible to safely call this method from any thread.
     * This method emits an error() signal if the data could not be successfully retrieved due to
     * a query error, source not found, or other unexpected condition.
     *
     * @param offset The index offset within the view.
     * @param limit The number of items to retrieve.
     * @param[out] revision The current revision of the data source. The revision value must match
     * the state of the data items that are returned. This pointer must not be null.
     * @param[out] totalCount The total number of items in the view. This pointer must not be null.
     * @param[out] results The list of data items which is the return data. This pointer must not be null.
     *
     * @return @c True if the data is successfully retrieved, @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    virtual bool getData(int offset, int limit, DataRevision *revision,
            int *totalCount, QList<DataItem> *results);

    /*!
     * @brief Fetch the data items from the data source if the data source is at the requested revision.
     *
     * This is a synchronous call, but it must be possible to safely call this method from any thread.
     * The error() signal is emitted for any database and query related errors only.
     * The error() signal is not emitted if the data source doesn't match the requested revision; instead
     * this method returns @c false.
     *
     * @param offset The index offset within the view.
     * @param limit The number of items to retrieve.
     * @param requestedRevision The requested revision ID for the data source.
     * If the data source doesn't match this revision, this method returns @c false.
     * @param[out] results The list of data items which is the return data. This pointer must not be null.
     *
     * @return @c True if the data is successfully retrieved at the requested revision,
     * @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    virtual bool getDataForRevision(int offset, int limit,
            const DataRevision &requestedRevision, QList<DataItem> *results);

    /*!
     * @brief Fetch the overall revision, total count, all header items, and a range of data items from the data source.
     *
     * This is a synchronous call, but it must be possible to safely call this method from any thread.
     * This method emits an error() signal if the data could not be successfully retrieved.
     *
     * @param offset The index offset within the view.
     * @param limit The number of items to retrieve.
     * @param[out] revision The current revision of the data source. This pointer must not be null.
     * @param[out] totalCount The total number of items in the view. This pointer must not be null.
     * @param[out] results The requested items. This pointer must not be null.
     * @param[out] headerResults The header items of the query. This pointer must not be null.
     *
     * @return @c True if the data is successfully retrieved, @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    virtual bool getHeaderData(int offset, int limit, DataRevision *revision,
            int *totalCount, QList<DataItem> *results, QList<HeaderDataItem> *headerResults);

    /*!
     * @brief Set the query to be decorated.
     *
     * Note that this decorator takes ownership of the query.
     *
     * @param query The query to be decorated. This pointer must not be null.
     *
     * @since BlackBerry 10.2.0
     */
    void setQuery(bb::cascades::datamanager::DataQuery *query);

    /*!
     * @brief Get the delegate query.
     *
     * Note that the query is owned by the decorator and is destroyed when the decorator is destroyed.
     *
     * @return The query.
     *
     * @since BlackBerry 10.2.0
     */
    bb::cascades::datamanager::DataQuery *query() const;

    /*!
     * @brief Get a string representation of the query, for debugging purposes.
     *
     * @return The string.
     *
     * @since BlackBerry 10.2.0
     */
    virtual QString toString() const;

protected:
    /*!
     * @brief Override this function to modify the detail data before its returned to the model.
     *
     * @param[in,out] results The data items fetched by the query.
     *
     * @since BlackBerry 10.2.0
     */
    virtual void processResults(QList<DataItem> *results);

    /*!
     * @brief Override this function to modify the header data before its returned to the model.
     *
     * @param[in,out] headerResults The header items fetched by the query.
     *
     * @since BlackBerry 10.2.0
     */
    virtual void processHeaderResults(QList<HeaderDataItem> *headerResults);

Q_SIGNALS:
    /*!
     * @brief This signal is emitted when the data changes.
     *
     * @param revision The revision of the latest source data.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.2.0
     */
    void dataChanged(DataRevision revision);

    /*!
     * @brief This signal is emitted when the query being decorated has changed.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.2.0
     */
    void queryChanged();

protected:
    /*! @cond PRIVATE */
    DataQueryDecorator(DataQueryDecoratorPrivate &dd, QObject *parent = 0);

    Q_DECLARE_PRIVATE(DataQueryDecorator)
    Q_DISABLE_COPY(DataQueryDecorator)
    /*! @endcond */
};

} // datamanager
} // cascades
} // bb

#endif /* BB_CASCADES_DATAMANAGER_DATAQUERYDECORATOR_HPP_ */
