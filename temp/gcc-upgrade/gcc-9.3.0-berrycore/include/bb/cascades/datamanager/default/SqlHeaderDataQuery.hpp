/*!
 * @copyright
 * Copyright (C) 2013 BlackBerry Limited. All rights reserved.
 */

#ifndef BB_CASCADES_DATAMANAGER_SQLHEADERDATAQUERY_HPP
#define BB_CASCADES_DATAMANAGER_SQLHEADERDATAQUERY_HPP

#include <bb/cascades/datamanager/Global>
#include <bb/cascades/datamanager/SqlDataQuery>

namespace bb
{
namespace cascades
{
namespace datamanager
{

class SqlHeaderDataQueryPrivate;

/*!
 * @headerfile SqlDataQuery.hpp <bb/cascades/datamanager/SqlDataQuery>
 *
 * @brief The default @c HeaderDataQuery implementation that uses SQL selects to retrieve header and detail data.
 *
 * Headers and items are associated as follows:
 * - The query for headers must include a column named "count". This represents
 * the count of items that belong to each header. The sum of all "count"
 * properties should be equal to the total number of data items.
 * - The query for data must provide the data in an order that aligns with the headers.
 * - The headers and data are associated by grouping the data items into headers
 * based on the "count" properties of the headers.
 *
 * For example, if the first header item has a count of 3, then the first three
 * data items will be grouped under this header.
 *
 * To implement this class, you must decide how to handle error conditions. If there
 * are SQL or other expected or unexpected runtime errors, you must determine
 * which of these errors are catastrophic and which are recoverable.
 * See the @c DataQuery class description for error handling guidelines.
 *
 * Here is a QML example showing the usage of an @c SqlHeaderDataQuery:
 * @snippet libbbcascadesdatamanager/examples/SqlHeaderDataQuery/assets/SqlHeaderDataQueryExamples.qml sqlheaderdataquery1
 *
 * Here is a C++ example showing the usage of an @c %SqlHeaderDataQuery:
 * @snippet libbbcascadesdatamanager/examples/SqlHeaderDataQuery/src/SqlHeaderDataQueryExamples.cpp sqlheaderdataquery1
 *
 * @xmlonly
 * <apigrouping group="Data Management/Large Data Sets"/>
 * <library name="bbcascadesdatamanager"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_CASCADES_DATAMANAGER_EXPORT SqlHeaderDataQuery : public HeaderDataQuery
{
    Q_OBJECT

    /*!
     * @brief The source URL for the path to the local database. This property is
     * mandatory.
     *
     * Once the property is set, it cannot be changed.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(QUrl source READ source WRITE setSource)

    /*!
     * @brief The main SQL query statement. This property is mandatory.
     *
     * Once the property is set, it cannot be changed.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(QString query READ query WRITE setQuery)

    /*!
     * @brief Optional query used for improved performance when scrolling down.
     *
     * Once the property is set, it cannot be changed.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(QString scrollDownQuery READ scrollDownQuery WRITE setScrollDownQuery)

    /*!
     * @brief Optional query used for improved performance when scrolling up.
     *
     * Once the property is set, it cannot be changed.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(QString scrollUpQuery READ scrollUpQuery WRITE setScrollUpQuery)

    /*!
     * @brief The header data query for retrieving header items from the database.
     * This property is mandatory.
     *
     * The query must include a numeric column named "count" or "count(*)" which identifies
     * the count of children for each header. The sum of these counts for all items
     * returned by the query must equal the total count for the data.
     *
     * Once the property is set, it cannot be changed.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(QString headerQuery READ headerQuery WRITE setHeaderQuery)

    /*!
     * @brief The name of the key column in the main query which is returned for each item.
     *
     * This key, if returned for each @c DataItem by the main query, uniquely identifies
     * the data item. It's used by the data model to signal listeners (usually an associated
     * list) that items have changed location or have been deleted.
     *
     * Use of this property is optional, however, without keys, adding and deleting items in
     * the database may result in poor performance of user interface visual updates.
     *
     * Once the property is set, it cannot be changed.
     *
     * Here is an example query:
     * @code
     * "SELECT key_id, revision_id, lastname, firstname FROM contacts"
     * @endcode
     * with the keyColumn: "key_id"
     *
     * @see DataItem
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(QString keyColumn READ keyColumn WRITE setKeyColumn)

    /*!
     * @brief The name of the revision column in the main query which is returned for each item.
     *
     * This revision, if returned for each @c DataItem by the main query, identifies the
     * current state of that item. It's used in conjunction with the overall revision.
     * When a database item is updated, its revision should be updated and the
     * overall database revision should be updated.
     *
     * This property is used to determine when items must be updated in any cached data in memory.
     * Use of this property is optional, however, without item revisions, database changes
     * may result in poor performance of user interface visual updates.
     *
     * Once the property is set, it cannot be changed.
     *
     * Here is an example query:
     * @code
     * "SELECT key_id, revision_id, lastname, firstname FROM contacts"
     * @endcode
     * with the revisionColumn: "revision_id"
     *
     * @see DataItem
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(QString revisionColumn READ revisionColumn WRITE setRevisionColumn)

    /*!
     * @brief An SQL query statement that returns the total count of items.
     *
     * This property is mandatory when the query is being used for async models. It's
     * needed to obtain the total count of database items even when the model retains
     * only a partial cache in memory.
     *
     * Here is an example:
     * @code
     * "SELECT count(*) FROM contacts"
     * @endcode
     *
     * Once the property is set, it cannot be changed.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(QString countQuery READ countQuery WRITE setCountQuery)

    /*!
     * @brief An SQL query statement to return the current overall revision for the source.
     *
     * This revision represents the current state of the database. It's used to ensure
     * that data for different database states is not mixed in memory. If the data model
     * determines that the overall revision of the data has changed then any cached data
     * is refreshed by querying the data source again.
     *
     * Use of this property is optional, however, without an overall revision, database
     * queries will fully refresh the cache so that the data can be guaranteed
     * to be consistent.
     *
     * Here is an example:
     * @code
     * "SELECT revision_id FROM revision"
     * @endcode
     *
     * Once the property is set, it cannot be changed.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(QString revisionQuery READ revisionQuery WRITE setRevisionQuery)

    /*!
     * @brief A map of name-to-value bindings.
     *
     * This property allows values to be inserted for named place holders in each
     * query statement. Once the property is set, it cannot be changed.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(QVariantMap bindValues READ valuesToBind WRITE setValuesToBind)

public:
    /*!
     * @brief Constructs an @c SqlHeaderDataQuery.
     *
     * @param parent The parent owner or 0. Optional and defaults to 0 if not specified.
     *
     * @since BlackBerry 10.2.0
     */
    explicit SqlHeaderDataQuery(QObject *parent = 0);

    /*!
     * @brief Constructs an @c SqlHeaderDataQuery given SQL data item and header
     * query statements.
     *
     * @param query The SQL data item query statement to use for this data query.
     * @param headerQuery The SQL header query statement to use for this data query.
     * @param parent The parent owner or 0. Optional and defaults to 0 if not specified.
     *
     * @since BlackBerry 10.2.0
     */
    SqlHeaderDataQuery(const QString &query, const QString &headerQuery, QObject *parent = 0);

    /*!
     * @brief Destructor.
     *
     * @since BlackBerry 10.2.0
     */
    virtual ~SqlHeaderDataQuery();

    /*!
     * @brief Set the source URL. This property is mandatory.
     *
     * @param source The source URL.
     *
     * @since BlackBerry 10.2.0
     */
    void setSource(const QUrl& source);

    /*!
     * @brief Get the source URL.
     *
     * @return The source URL.
     *
     * @since BlackBerry 10.2.0
     */
    QUrl source() const;

    /*!
     * @brief Set the query string. This property is mandatory.
     *
     * @param query The query string.
     *
     * @since BlackBerry 10.2.0
     */
    void setQuery(const QString& query);

    /*!
     * @brief Set the optional @c scrollDownQuery string used for improved performance when scrolling down.
     *
     * @param scrollDownQuery The query string to use when scrolling down.
     *
     * @since BlackBerry 10.2.0
     */
    void setScrollDownQuery(const QString& scrollDownQuery);

    /*!
     * @brief Set the optional @c scrollUpQuery string used for improved performance when scrolling up.
     *
     * @param scrollUpQuery The query string to use when scrolling up.
     *
     * @since BlackBerry 10.2.0
     */
    void setScrollUpQuery(const QString& scrollUpQuery);

    /*!
     * @brief Get the query.
     *
     * @return The query string.
     *
     * @since BlackBerry 10.2.0
     */
    QString query() const;

    /*!
     * @brief Get the optional @c scrollDownQuery string used when scrolling down.
     *
     * @return The @c scrollDownQuery string.
     *
     * @since BlackBerry 10.2.0
     */
    QString scrollDownQuery() const;

    /*!
     * @brief Get the optional @c scrollUpQuery string used when scrolling up.
     *
     * @return The @c scrollUpQuery string.
     *
     * @since BlackBerry 10.2.0
     */
    QString scrollUpQuery() const;

    /*!
     * @brief Set the SQL header query statement. This property is mandatory.
     *
     * @param query The SQL header query statement to use for this data query.
     *
     * @since BlackBerry 10.2.0
     */
    void setHeaderQuery(const QString &query);

    /*!
     * @brief Get the SQL header query statement.
     *
     * @return The SQL header query.
     *
     * @since BlackBerry 10.2.0
     */
    QString headerQuery() const;

    /*!
     * @brief Set the name of the key column in the main query.
     *
     * @param keyColumn The key column name.
     *
     * @since BlackBerry 10.2.0
     */
    void setKeyColumn(const QString& keyColumn);

    /*!
     * @brief Get the name of the key column in the main query.
     *
     * @return The @c keyColumn name.
     *
     * @since BlackBerry 10.2.0
     */
    QString keyColumn() const;

    /*!
     * @brief Set the name of the revision column in the main query.
     *
     * @param revisionColumn The revision column name.
     *
     * @since BlackBerry 10.2.0
     */
    void setRevisionColumn(const QString& revisionColumn);

    /*!
     * @brief Get the name of the revision column in the main query.
     *
     * @return The @c revisionColumn name.
     *
     * @since BlackBerry 10.2.0
     */
    QString revisionColumn() const;

    /*!
     * @brief Set the count query string.
     *
     * @param countQuery The count query string.
     *
     * @since BlackBerry 10.2.0
     */
    void setCountQuery(const QString& countQuery);

    /*!
     * @brief Get the count query.
     *
     * @return The @c countQuery string.
     *
     * @since BlackBerry 10.2.0
     */
    QString countQuery() const;

    /*!
     * @brief Set the overall revision query string.
     *
     * @param revisionQuery The revision query string.
     *
     * @since BlackBerry 10.2.0
     */
    void setRevisionQuery(const QString& revisionQuery);

    /*!
     * @brief Get the revision query.
     *
     * @return The @c revisionQuery string.
     *
     * @since BlackBerry 10.2.0
     */
    QString revisionQuery() const;

    /*!
     * @brief Bind values to the queries by place holder name.
     *
     * This set of value bindings are used for all queries.
     *
     * @param nameValueMap A map of place holder name to value.
     *
     * @since BlackBerry 10.2.0
     */
    void setValuesToBind(const QVariantMap& nameValueMap);

    /*!
     * @brief Retrieve the map of place holder name to value bindings.
     *
     * This set of value bindings are used for all queries.
     *
     * @return A map of place holder name to value.
     *
     * @since BlackBerry 10.2.0
     */
    QVariantMap valuesToBind() const;

    /*!
     * @brief Fetch the overall revision, total count, and a range of data items from the data source.
     *
     * This is a synchronous call, but it must be possible to safely call this method from any thread.
     * This method emits an error() signal and returns @c false if the data could not be successfully
     * retrieved due to a query error, source not found, or other unexpected condition.
     *
     * For more information about error handling, see the @c DataQuery class description. A return of
     * @c false by this method should be preceded by the query emitting an error signal. This signal
     * should be handled at the application level, leading to some appropriate action.
     *
     * @param offset The index offset within the view.
     * @param limit The number of items to retrieve.
     * @param[out] revision The current revision of the data source. The revision value must match
     * the state of the data items that are returned. This pointer must not be null.
     * @param[out] totalCount The total number of items in the view. This pointer must not be null.
     * @param[out] results The list of data items which is the return data. This pointer must not be null.
     * @return @c True if the data could be successfully retrieved, @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    virtual bool getData(int offset, int limit, DataRevision *revision,
            int *totalCount, QList<DataItem> *results);

    /*!
     * @brief Fetch the data items from the data source if the data source is at the request revision.
     *
     * This is a synchronous call, but it must be safe to call this method from any thread.
     * The error() signal is emitted on any database and query related errors only.
     * The error() signal is not emitted if the data source doesn't match the requested revision; instead
     * this method returns @c false.
     *
     * For more information about error handling, see the @c DataQuery class description. A return of
     * @c false by this method should be preceded by the query emitting an error signal. This signal
     * should be handled at the application level, leading to some appropriate action.
     *
     * @note The return of @c false by this method is always expected and not a catastrophic error since
     * @c false is returned when the data source doesn't match the requested revision. The error() signal
     * should be emitted on database and query related errors only.
     *
     * @param offset The index offset within the view.
     * @param limit The number of items to retrieve.
     * @param requestedRevision The requested revision ID for the data source.
     * If the data source doesn't match this revision, this method returns @c false.
     * @param[out] results The list of data items which is the return data. This pointer must not be null.
     * @return @c True if the data is successfully retrieved at the requested revision,
     * @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    virtual bool getDataForRevision(int offset, int limit,
            const DataRevision& requestedRevision, QList<DataItem> *results);

    /*!
     * @brief Fetch the overall revision, total count, all header items, and a range of data items from the data source.
     *
     * This is a synchronous call, but it must be possible to safely call this method from any thread.
     *
     * This method emits an error() signal and returns @c false if the data could not be successfully
     * retrieved due to a query error, source not found, or other unexpected condition.
     *
     * For more information about error handling, see the @c DataQuery class description. A return of
     * @c false by this method should be preceded by the query emitting an error signal. This signal
     * should be handled at the application level, leading to some appropriate action.
     *
     * @param offset The index offset within the view.
     * @param limit The number of items to retrieve.
     * @param[out] revision The current revision of the data source. This pointer must not be null.
     * @param[out] totalCount The total number of items in the view. This pointer must not be null.
     * @param[out] results The requested items. This pointer must not be null.
     * @param[out] headerResults The header items of the query. This pointer must not be null.
     *
     * @return true if it can fetch  from the revision, otherwise false.
     *
     * @since BlackBerry 10.2.0
     */
    virtual bool getHeaderData(int offset, int limit, DataRevision *revision,
            int *totalCount, QList<DataItem> *results,
            QList<HeaderDataItem> *headerResults);

    /*!
     * @brief Get a string representation of the query, for debugging purposes.
     *
     * @return The string.
     *
     * @since BlackBerry 10.2.0
     */
    virtual QString toString() const;

    /*!
     * @brief Emit the signal for data changes if using the default @c NumericRevision.
     *
     * This method can be called from QML to notify the containing model of a source revision change.
     *
     * @param revision The numeric revision of the latest source data.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void emitDataChanged(int revision);

protected:
    /*! @cond PRIVATE */
    SqlHeaderDataQuery(SqlHeaderDataQueryPrivate &dd, QObject *parent = 0);

private:
    Q_DECLARE_PRIVATE(SqlHeaderDataQuery)
    Q_DISABLE_COPY(SqlHeaderDataQuery)
    /*! @endcond */
};

} // datamanager
} // cascades
} // bb

#endif /* BB_CASCADES_DATAMANAGER_SQLHEADERDATAQUERY_HPP */
