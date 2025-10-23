/**
 * @copyright
 * Copyright BlackBerry Limited, 2011-2013
 * BlackBerry Limited. All rights reserved.
 */

#ifndef BB_DATA_SQLDATAACCESS_HPP
#define BB_DATA_SQLDATAACCESS_HPP

#include <bb/data/DataAccessError>
#include <bb/Global>
#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QString>
#include <QVariant>

namespace bb {
namespace data {

class SqlDataAccessPrivate;

/*!
 * @headerfile SqlDataAccess.hpp <bb/data/SqlDataAccess>
 *
 * @brief Retrieves and updates data in an SQL database.
 *
 * The @c SqlDataAccess class provides a simple interface for retrieving
 * data from or updating data in an SQL database. You can use this class
 * to provide SQL data to a @c ListView to display the data in your application.
 *
 * Any valid SQL command can be passed as a string to the @c execute(query)
 * function. This includes executing a single DML (data manipulation language)
 * command such as INSERT, UPDATE or DELETE, or a DDL (data definition language)
 * command such as CREATE TABLE or CREATE INDEX, using the same @c execute(query)
 * function.
 *
 * Parameterized queries can be performed using the @c execute(query, valuesByPosition)
 * and the @c execute(query, valuesByName) functions.
 *
 * Batched queries can be performed using the @c executeBatch(query, valuesTable)
 * function.
 *
 * The result data that's returned by a SELECT command is of type @c QVariantList,
 * cast as a @c QVariant. Each item in the list is a @c QVariantMap containing the
 * names and values for fields within a record. The value types are the same as those
 * returned by @c QSqlRecord::value().
 *
 * This examples shows the loading of SQL data from a database file (contacts.db) into
 * a data model for display in a @c %ListView:
 *
 * @snippet libbbdata/examples/SqlDataAccess/src/SqlDataAccessExamples.cpp loadsql1
 *
 * @see bb::cascades::DataModel, bb::cascades::ListView
 *
 * @xmlonly
 * <apigrouping group="Data management/Data Sources"/>
 * <library name="bbdata"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_DLL_PUBLIC SqlDataAccess : public QObject {
    Q_OBJECT

public:
    /*!
     * @brief Constructs an @c SqlDataAccess object with the specified path to a database
     * file and parent.
     *
     * If the specified parent is not 0, the ownership of this object will be transferred to
     * the parent.
     *
     * @param dbPath The path to the SQL database. It is an absolute or relative file path
     * to the local database. This path is also used as the connection name.
     * @param parent The parent owner or 0. Optional and will default to 0 if not specified.
     *
     * @since BlackBerry 10.0.0
     */
    explicit SqlDataAccess(const QString& dbPath, QObject* parent = 0);

    /*!
     * @brief Constructs an @c SqlDataAccess object with the specified path to a database
     * file, connection name, and parent.
     *
     * The connectionName is useful to identify the purpose for a particular
     * connection, especially when there are multiple SQL connections used in an
     * application.
     *
     * If the specified parent is not 0, the ownership of this object will be transferred to
     * the parent.
     *
     * @param dbPath The path to the SQL database. It is an absolute or relative file path
     * to the local database.
     * @param connectionName The name of the database connection.
     * @param parent The parent owner or 0. Optional and will default to 0 if not specified.
     *
     * @since BlackBerry 10.0.0
     */
    SqlDataAccess(const QString& dbPath, const QString& connectionName, QObject* parent = 0);

    /*!
     * @brief Virtual destructor.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~SqlDataAccess();

    /*!
     * @brief Returns the database connection object that's being used for data access.
     *
     * @return A @c QSqlDatabase object representing the database connection.
     *
     * @see QSqlDatabase
     *
     * @since BlackBerry 10.0.0
     */
    QSqlDatabase connection();

    /*!
     * @brief Returns an error object for the most recent operation.
     *
     * @return DataAccessError with error type and error message.
     *
     * @since BlackBerry 10.0.0
     */
    DataAccessError error() const;

    /*!
     * @brief Returns indication of whether or not most recent operation
     * ended with an error.
     *
     * @return true if current error or false if none.
     *
     * @since BlackBerry 10.0.0
     */
    bool hasError() const;

    /*!
     * @brief Executes the specified SQL query.
     *
     * The SQL query can be any valid SQL command. If the query is an SQL SELECT command,
     * then the data is returned as a @c QVariantList and each item in the list is a
     * @c QVariantMap.
     *
     * The query can also be a DML (data manipulation language) command such as
     * INSERT, UPDATE or DELETE, or a DDL (data definition language) command such as
     * CREATE TABLE or CREATE INDEX. In these cases, an empty @c %QVariant is returned.
     *
     * You can use @c DataAccess::hasError() to determine if the most recent operation
     * resulted in an error, and you can use @c DataAccess::error() to retrieve information
     * about the error that occurred.
     *
     * @param query The SQL command to execute.
     *
     * @return A @c QVariant that represents the result of the query. If the query is an
     * SQL SELECT command, the return value is a @c QVariantList of @c QVariantMap objects.
     * Otherwise, the return value is an empty @c %QVariant.
     *
     * @since BlackBerry 10.0.0
     */
    QVariant execute(const QString& query);

    /*!
     * @brief Executes the specified parameterized SQL query after binding the supplied
     * values in the list to placeholders in the query string.
     *
     * If the same query is executed multiple times the prepared query will be cached
     * and reused with new bound values.
     *
     * This form of parameterized query uses positional binding since the first value in
     * the list is bound to the first placeholder in the query, the second value to the
     * second placeholder, and so on.
     *
     * The place holders in the query string can be defined in one of two ways as seen
     * in the following two examples:
     *
     * @snippet libbbdata/examples/SqlDataAccess/src/SqlDataAccessExamples.cpp executepositionalbinding1
     *
     * @snippet libbbdata/examples/SqlDataAccess/src/SqlDataAccessExamples.cpp executepositionalbinding2
     *
     * The SQL query can be any valid SQL command. If the query is an SQL SELECT command,
     * then the data is returned as a @c QVariantList and each item in the list is a
     * @c QVariantMap.
     *
     * The query can also be a DML (data manipulation language) command such as
     * INSERT, UPDATE or DELETE, or a DDL (data definition language) command such as
     * CREATE TABLE or CREATE INDEX. In these cases, an empty @c %QVariant is returned.
     *
     * You can use @c DataAccess::hasError() to determine if the most recent operation
     * resulted in an error, and you can use @c DataAccess::error() to retrieve information
     * about the error that occurred.
     *
     * @param query The parameterized SQL command to execute.
     * @param valuesByPosition The list of values to bind to placeholders by position in query.
     *
     * @return A @c QVariant that represents the result of the query. If the query is an
     * SQL SELECT command, the return value is a @c QVariantList of @c QVariantMap objects.
     * Otherwise, the return value is an empty @c %QVariant.
     *
     * @since BlackBerry 10.0.0
     */
    QVariant execute(const QString& query, const QVariantList& valuesByPosition);

    /*!
     * @brief Executes the specified parameterized SQL query after binding the supplied
     * values in the map to named placeholders in the query string.
     *
     * If the same query is executed multiple times the prepared query will be cached
     * and reused with new bound values.
     *
     * This form of parameterized query uses named binding since each value in the map
     * is bound to a named placeholder in the query using the map key. Here is an example:
     *
     * @snippet libbbdata/examples/SqlDataAccess/src/SqlDataAccessExamples.cpp executenamedbinding1
     *
     * Note that binding to an undefined placeholder will result in undefined behavior.
     *
     * The SQL query can be any valid SQL command. If the query is an SQL SELECT command,
     * then the data is returned as a @c QVariantList and each item in the list is a
     * @c QVariantMap.
     *
     * The query can also be a DML (data manipulation language) command such as
     * INSERT, UPDATE or DELETE, or a DDL (data definition language) command such as
     * CREATE TABLE or CREATE INDEX. In these cases, an empty @c %QVariant is returned.
     *
     * You can use @c DataAccess::hasError() to determine if the most recent operation
     * resulted in an error, and you can use @c DataAccess::error() to retrieve information
     * about the error that occurred.
     *
     * @param query The parameterized SQL command to execute.
     * @param valuesByName The map of named values to bind to placeholders in query.
     *
     * @return A @c QVariant that represents the result of the query. If the query is an
     * SQL SELECT, the return value is a @c QVariantList of @c QVariantMap objects.
     * Otherwise, the return value is an empty @c %QVariant.
     *
     * @since BlackBerry 10.0.0
     */
    QVariant execute(const QString& query, const QVariantMap& valuesByName);

    /*!
     * @brief Executes the specified parameterized SQL query multiple times after binding
     * each value set in the @c valuesTable to placeholders in the query string.
     *
     * The parameterized SQL query is executed once for each item in the @c valuesTable.
     * Each item in the @c valuesTable is either a list or a map, and it represents a set
     * of values which are bound to placeholders in the query string.
     *
     * This method can use either positional binding or named binding. With positional
     * binding, each item in the valuesTable is a @c QVariantList containing a list of
     * values to bind to the corresponding placeholder (first-to-first, second-to-second,
     * and so on) in the query command. With named binding, each item in the @c valuesTable
     * is a @c QVariantMap containing name-value pairs used to bind to named placeholders
     * in the query command.
     *
     * The following examples describe the three different variations:
     *
     * @snippet libbbdata/examples/SqlDataAccess/src/SqlDataAccessExamples.cpp executebatchbinding1
     *
     * @snippet libbbdata/examples/SqlDataAccess/src/SqlDataAccessExamples.cpp executebatchbinding2
     *
     * @snippet libbbdata/examples/SqlDataAccess/src/SqlDataAccessExamples.cpp executebatchbinding3
     *
     * Note that binding to an undefined placeholder will result in undefined behavior.
     *
     * If an error is detected when executing an SQL query for a particular value set then the
     * processing of the batch is stopped at that point. The effects of an error on the current
     * transaction is covered below.
     *
     * The SQL query can be any valid SQL command. If the query is an SQL SELECT command,
     * then the data is returned as a @c QVariantList and each item in the list is a
     * @c QVariantMap.
     *
     * The query can also be a DML (data manipulation language) command such as
     * INSERT, UPDATE or DELETE, or a DDL (data definition language) command such as
     * CREATE TABLE or CREATE INDEX. In these cases, an empty @c %QVariant is returned.
     *
     * <h3>Transactions</h3>
     *
     * A batch operation such as this should always be performed in a transaction.
     * This will perform much better than if each individual query within the
     * batch is a separate transaction. Results show that using @c executeBatch with
     * large value sets and failing to use a transaction can result in performance
     * that can be 100X slower.
     *
     * If a transaction has not been started before this @c executeBatch method is
     * called then it will automatically use a transaction to ensure good performance.
     * In this case it will do the following internally:
     * - Start a new transaction
     * - Execute query for each value set
     * - If an error occurs, rollback the transaction
     * - If no error occurs, commit the transaction
     *
     * If a transaction has already been started before this @c executeBatch method
     * is called then it is up to the calling code to manage the transaction
     * processing. A common case would be when multiple calls to @c execute() and/or
     * @c executeBatch() need to be combined into a single transaction to ensure a
     * consistent result. Here is a simple example (minimal error checking):
     * - sda.connection().transaction();
     * - sda.execute(query1);
     * - sda.execute(query2);
     * - sda.executeBatch(batch1, values);
     * - if sda.hasError()
     *     - sda.connection().rollback();
     * - else
     *     - sda.connection().commit();
     *
     * @param query The parameterized SQL command to execute.
     * @param valuesTable The list of value sets to bind to placeholders in query.
     *
     * @return A @c QVariant that represents the result of the query. If the query is an
     * SQL SELECT, the return value is a @c QVariantList of @c QVariantMap objects.
     * Otherwise, the return value is an empty @c %QVariant.
     *
     * @since BlackBerry 10.0.0
     */
    QVariant executeBatch(const QString& query, const QVariantList& valuesTable);

protected:
    /*! @cond PRIVATE */
    SqlDataAccessPrivate * const d_ptr;

private:
    Q_DECLARE_PRIVATE(SqlDataAccess)
    Q_DISABLE_COPY(SqlDataAccess)
    /*! @endcond */
};

} // namespace bb::data
}

#endif /* BB_DATA_SQLDATAACCESS_HPP */
