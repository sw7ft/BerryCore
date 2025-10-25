/*!
 * @copyright
 * Copyright (C) 2013 BlackBerry Limited. All rights reserved.
 */

#ifndef BB_CASCADES_DATAMANAGER_SQLQUERYUTILS_HPP
#define BB_CASCADES_DATAMANAGER_SQLQUERYUTILS_HPP

#include <bb/cascades/datamanager/Global>
#include <bb/cascades/datamanager/DataItem>
#include <bb/cascades/datamanager/HeaderDataItem>
#include <QList>
#include <QScopedPointer>
#include <QString>
#include <QUrl>
#include <QVariant>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

namespace bb
{
namespace cascades
{
namespace datamanager
{

class SqlQueryUtilsPrivate;

/*!
 * @headerfile SqlQueryUtils.hpp <bb/cascades/datamanager/SqlQueryUtils>
 *
 * @brief Utility methods for performing common operations in SQL data queries.
 *
 * @see SqlDataQuery
 * @see SqlHeaderDataQuery
 *
 * @xmlonly
 * <apigrouping group="Data Management/Large Data Sets"/>
 * <library name="bbcascadesdatamanager"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_CASCADES_DATAMANAGER_EXPORT SqlQueryUtils
{
public:
    /*!
     * @brief Constructs an @c SqlQueryUtils.
     *
     * @since BlackBerry 10.2.0
     */
    SqlQueryUtils();

    /*!
     * @brief Destructor.
     *
     * @since BlackBerry 10.2.0
     */
    virtual ~SqlQueryUtils();

    /*!
     * @brief Return an existing or new database connection for the database at the source URL.
     *
     * @param source The path to the local database.
     * @param[out] error The error object to update with the status. This pointer must not be null.
     * If the method is successful, @c QSqlError::type() will be @c QSqlError::NoError.
     *
     * @return The @c QSqlDatabase object to use as an open connection to the database.
     *
     * @since BlackBerry 10.2.0
     */
    QSqlDatabase connection(const QUrl &source, QSqlError *error);

    /*!
     * @brief Execute the supplied SQL query after binding any values and return a single result value.
     *
     * If there are multiple rows and/or multiple columns returned by the query, the first column value from
     * the first row is returned.
     *
     * @param connection The open database connection.
     * @param query The SQL query.
     * @param bindValues A map used to replace any named placeholders in the query with values.
     * @param resultName The name of the result column. If not provided, the first value is returned.
     * @param[out] resultValue The query result value being returned. This pointer must not be null.
     * @param[out] error The error object to update with the status. This pointer must not be null.
     *
     * @return @c True if the data is successfully retrieved, @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool getSingleQueryValue(QSqlDatabase &connection, const QString &query, const QVariantMap &bindValues,
            const QString &resultName, QVariant *resultValue, QSqlError *error);

    /*!
     * @brief Execute the supplied SQL data query after applying a limit and an offset and binding any values.
     *
     * @param connection The open database connection.
     * @param query The SQL data query.
     * @param offset The index offset within the view. A negative offset is ignored.
     * @param limit The number of items to retrieve. A negative limit means both @c limit and @c offset are ignored.
     * @param bindValues A map used to replace any named placeholders in the query with values.
     * @param keyColumn The key column name used in the query. This can be empty.
     * @param revisionColumn The revision column name used in the query. This can be empty.
     * @param[out] results The list of data items which is the return data. This pointer must not be null.
     * @param[out] error The error object to update with the status. This pointer must not be null.
     *
     * @return @c True if the data is successfully retrieved, @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool getQueryData(QSqlDatabase &connection, const QString &query, int offset, int limit,
         const QVariantMap &bindValues, const QString &keyColumn, const QString &revisionColumn,
         QList<DataItem> *results, QSqlError *error);

    /*!
     * @brief Extend the given query string with an offset and/or limit and return the modified string.
     * The offset cannot be used without a limit.
     *
     * For example, this query:
     * @code
     * extendQuery("select * from contact", 100, 200);
     * @endcode
     * returns:
     * @code
     * "select * from contact limit 200 offset 100"
     * @endcode
     *
     * @param query The SQL query to extend.
     * @param offset The index offset within the view. A negative offset is ignored.
     * @param limit The number of items to retrieve. A negative limit means both @c limit and @c offset are ignored.
     *
     * @return The query string with @c offset and @c limit parameters added.
     *
     * @since BlackBerry 10.2.0
     */
    QString extendQuery(const QString &query, int offset, int limit);

    /*!
     * @brief Use this method to normalize @c DataItem into @c HeaderDataItem.
     *
     * If the header child count is zero, the item is removed.
     *
     * @param data The list of @c DataItem objects to normalize.
     *
     * @return A new list of @c HeaderDataItem objects.
     *
     * @since BlackBerry 10.2.0
     */
    QList<HeaderDataItem> normalizeHeaderData(const QList<DataItem> &data);

    /*!
     * @brief Prepare the given @c QSqlQuery object using the query string and @c bindValues map.
     *
     * @note This method does a better job of preparing the query and binding values
     * than using the equivalent Qt code. Unlike the Qt code, this method works correctly:
     * 1. When a query has no parameters but @c bindValues is supplied.
     * 2. When a query uses the same named parameter more than once in query string.
     *
     * @param query The SQL query string using a named placeholder such as :name.
     * @param bindValues A map of names to values for supplying values to the query.
     * @param[out] sqlQuery The SQL query object to prepare.
     *
     * @since BlackBerry 10.2.0
     */
    void prepareQuery(const QString &query, const QVariantMap &bindValues, QSqlQuery *sqlQuery);

private:
    /*! @cond PRIVATE */
    // for future use
    QScopedPointer<SqlQueryUtilsPrivate> d_ptr;
    /*! @endcond */
};

} // datamanager
} // cascades
} // bb

#endif /* BB_CASCADES_DATAMANAGER_SQLQUERYUTILS_HPP */
