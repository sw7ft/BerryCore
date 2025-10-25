/**
 * @copyright
 * Copyright BlackBerry Limited, 2011-2013
 * BlackBerry Limited. All rights reserved.
 */

#ifndef BB_DATA_SQLCONNECTION_HPP
#define BB_DATA_SQLCONNECTION_HPP

#include <bb/data/AsyncDataAccess>
#include <bb/data/DataAccessReply>
#include <bb/Global>
#include <QString>
#include <QVariant>

namespace bb {
namespace data {

class SqlWorker;
class SqlConnectionPrivate;

/*!
 * @headerfile SqlConnection.hpp <bb/data/SqlConnection>
 *
 * @brief Connects to an SQL database and executes commands asynchronously.
 *
 * The @c SqlConnection class is the public class that applications use to create a
 * connection to an SQL database and execute SQL commands asynchronously in another thread.
 *
 * Performing long operations in a separate (non-main) thread will ensure that the
 * overall application responsiveness (for example, swift response to button clicks)
 * is maintained even when database operations are being performed. Also, since
 * SQLite has limitations with the use of multiple connections, having all access
 * to an SQLite database working through a single SqlConnection object is a good
 * pattern.
 *
 * Here's an example of how to connect to an SQL database using @c %SqlConnection and handle
 * the results:
 *
 * @snippet libbbdata/examples/SqlConnection/src/SqlConnectionExamples.cpp loadsql1
 *
 * @xmlonly
 * <apigrouping group="Data management/Data Sources"/>
 * <library name="bbdata"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_DLL_PUBLIC SqlConnection : public AsyncDataAccess {
    Q_OBJECT

public:
    /*!
     * @brief Constructs an @c SqlConnection object with the specified path to a database file
     * and parent.
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
    explicit SqlConnection(const QString& dbPath, QObject* parent = 0);

    /*!
     * @brief Constructs an @c SqlConnection object with the specified path to a database file,
     * connection name, and parent.
     *
     * The connectionName is useful to identify the purpose for a particular connection,
     * especially when there are multiple SQL connections used in an application.
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
    SqlConnection(const QString& dbPath, const QString& connectionName, QObject* parent = 0);

    /*!
     * @brief Constructs an @c SqlConnection object with the specified @c SqlWorker object and
     * parent.
     *
     * If the specified parent is not 0, the ownership of this object will be transferred to
     * the parent. Also, ownership of the worker will always be managed by this async framework
     * and so the ownership of the worker will be transferred to an internal object in this
     * framework which has affinity for the new thread.
     *
     * You can customize the standard @c %SqlWorker class by extending @c %SqlWorker and
     * overriding the @c execute() function to specify your custom behavior.
     *
     * @param worker The worker object that performs work in another thread.
     * @param parent The parent owner or 0. Optional and will default to 0 if not specified.
     *
     * @since BlackBerry 10.0.0
     */
    explicit SqlConnection(SqlWorker* worker, QObject* parent = 0);

    /*!
     * @brief Virtual destructor.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~SqlConnection();

    /*!
     * @brief Provide access to (unhide) the execute and executeAndWait methods in the base class.
     */
    using AsyncDataAccess::execute;
    using AsyncDataAccess::executeAndWait;

    /*!
     * @brief SQL query parameters that are passed to the @c SqlWorker object for execution
     * in another thread.
     *
     * The @c SqlWorker executes the parameterized SQL query after binding the supplied
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
     * @snippet libbbdata/examples/SqlConnection/src/SqlConnectionExamples.cpp executepositionalbinding1
     *
     * @snippet libbbdata/examples/SqlConnection/src/SqlConnectionExamples.cpp executepositionalbinding2
     *
     * The SQL query can be any valid SQL command. If the query is an SQL SELECT command,
     * then the data is returned as a @c QVariantList and each item in the list is a
     * @c QVariantMap.
     *
     * The query can also be a DML (data manipulation language) command such as
     * INSERT, UPDATE or DELETE, or a DDL (data definition language) command such as
     * CREATE TABLE or CREATE INDEX. In these cases, an empty @c %QVariant is returned.
     *
     * This method returns immediately. Results will be returned later in a
     * @c DataAccessReply object using the @c reply() signal.
     *
     * If the thread has not been started, this method will call @c start().
     *
     * @param query The parameterized SQL command to execute.
     * @param valuesByPosition The list of values to bind to placeholders by position in query.
     * @param id An ID that's used to help match this request with a particular reply.
     * The @c %DataAccessReply will contain this ID. Defaults to @c 0 if not specified.
     *
     * @since BlackBerry 10.0.0
     */
    void execute(const QString& query, const QVariantList& valuesByPosition, int id = 0);

    /*!
     * @brief SQL query parameters are passed to the @c SqlWorker object for execution
     * in another thread.
     *
     * The @c SqlWorker executes the parameterized SQL query after binding the supplied
     * values in the map to named placeholders in the query string.
     *
     * If the same query is executed multiple times the prepared query will be cached
     * and reused with new bound values.
     *
     * This form of parameterized query uses named binding since each value in the map
     * is bound to a named placeholder in the query using the map key. Here is an example:
     *
     * @snippet libbbdata/examples/SqlConnection/src/SqlConnectionExamples.cpp executenamedbinding1
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
     * This method returns immediately. Results will be returned later in a
     * @c DataAccessReply object using the @c reply() signal.
     *
     * If the thread has not been started, this method will call @c start().
     *
     * @param query The parameterized SQL command to execute.
     * @param valuesByName The map of named values to bind to placeholders in query.
     * @param id An ID that's used to help match this request with a particular reply.
     * The @c %DataAccessReply will contain this ID. Defaults to @c 0 if not specified.
     *
     * @since BlackBerry 10.0.0
     */
    void execute(const QString& query, const QVariantMap& valuesByName, int id = 0);

    /*!
     * @brief SQL query parameters are passed to the @c SqlWorker object for execution
     * in another thread.
     *
     * The @c SqlWorker executes the parameterized SQL query after binding the supplied
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
     * @snippet libbbdata/examples/SqlConnection/src/SqlConnectionExamples.cpp executeandwaitpositionalbinding1
     *
     * @snippet libbbdata/examples/SqlConnection/src/SqlConnectionExamples.cpp executeandwaitpositionalbinding2
     *
     * The SQL query can be any valid SQL command. If the query is an SQL SELECT command,
     * then the data is returned as a @c QVariantList and each item in the list is a
     * @c QVariantMap.
     *
     * The query can also be a DML (data manipulation language) command such as
     * INSERT, UPDATE or DELETE, or a DDL (data definition language) command such as
     * CREATE TABLE or CREATE INDEX. In these cases, an empty @c %QVariant is returned.
     *
     * The current thread will block until a @c DataAccessReply object can be returned.
     *
     * If the thread has not been started, this function will call @c start().
     *
     * @param query The parameterized SQL command to execute.
     * @param valuesByPosition The list of values to bind to placeholders by position in query.
     * @param id An ID that's used to help match this request with its reply. The
     * @c %DataAccessReply that's returned will contain this ID. Defaults to @c 0 if not
     * specified.
     *
     * @return A @c %DataAccessReply containing the results of the operation.
     *
     * @since BlackBerry 10.0.0
     */
    DataAccessReply executeAndWait(const QString& query, const QVariantList& valuesByPosition, int id = 0);

    /*!
     * @brief SQL query parameters are passed to the @c SqlWorker object for execution
     * in another thread.
     *
     * The @c SqlWorker executes the parameterized SQL query after binding the supplied
     * values in the map to named placeholders in the query string.
     *
     * If the same query is executed multiple times the prepared query will be cached
     * and reused with new bound values.
     *
     * This form of parameterized query uses named binding since each value in the map
     * is bound to a named placeholder in the query using the map key. Here is an example:
     *
     * @snippet libbbdata/examples/SqlConnection/src/SqlConnectionExamples.cpp executeandwaitnamedbinding1
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
     * The current thread will block until a @c DataAccessReply object can be returned.
     *
     * If the thread has not been started, this function will call @c start().
     *
     * @param query The parameterized SQL command to execute.
     * @param valuesByName The map of named values to bind to placeholders in query.
     * @param id An ID that's used to help match this request with its reply. The
     * @c %DataAccessReply that's returned will contain this ID. Defaults to @c 0 if not
     * specified.
     *
     * @return A @c %DataAccessReply containing the results of the operation.
     *
     * @since BlackBerry 10.0.0
     */
    DataAccessReply executeAndWait(const QString& query, const QVariantMap& valuesByName, int id = 0);

    /*!
     * @brief SQL query parameters are passed to the @c SqlWorker object for batch execution
     * in another thread.
     *
     * The @c SqlWorker executes the parameterized SQL query once for each item in the
     * @c valuesTable. Each item in the @c valuesTable is either a list or a map and it represents
     * a set of values which are bound to placeholders in the query string.
     *
     * This method can use either positional binding or named binding. With positional
     * binding, each item in the @c valuesTable is a @c QVariantList containing a list of
     * values to bind to the corresponding placeholder (first-to-first, second-to-second,
     * and so on) in the query command. With named binding, each item in the @c valuesTable is a
     * @c QVariantMap containing name-value pairs used to bind to named placeholders in
     * the query command.
     *
     * The following three examples describe the different variations:
     *
     * @snippet libbbdata/examples/SqlConnection/src/SqlConnectionExamples.cpp executebatchbinding1
     *
     * @snippet libbbdata/examples/SqlConnection/src/SqlConnectionExamples.cpp executebatchbinding2
     *
     * @snippet libbbdata/examples/SqlConnection/src/SqlConnectionExamples.cpp executebatchbinding3
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
     * This method returns immediately. Results will be returned later in a
     * @c DataAccessReply object using the @c reply() signal.
     *
     * If the thread has not been started, this method will call @c start().
     *
     * <h3>Transactions</h3>
     *
     * A batch operation such as this should always be performed in a transaction.
     * This will perform much better than if each individual query within the
     * batch is a separate transaction. Results show that using executeBatch with
     * large value sets and failing to use a transaction can result in performance
     * that can be 100X slower.
     *
     * If a transaction has not been started before this @c executeBatch method is
     * called then it will automatically use a transaction to ensure good
     * performance. In this case it will do the following internally:
     * - Start a new transaction
     * - Execute a query for each value set
     * - If an error occurs, rollback the transaction
     * - If no error occurs, commit the transaction
     *
     * If a transaction has already been started before this @c executeBatch method
     * is called then it is up to the calling code to manage the transaction
     * processing. A common case would be when multiple calls to execute() and/or
     * @c executeBatch() need to be combined into a single transaction to ensure
     * a consistent result. Here is a simple example (minimal error checking):
     * - sc.beginTransaction();
     * - sc.execute(query1);
     * - sc.execute(query2);
     * - sc.executeBatch(batch1, values);
     * - if sc.hasError()
     *     - sc.rollbackTransaction();
     * - else
     *     - sc.endTransaction();
     *
     * @param query The parameterized SQL command to execute.
     * @param valuesTable The list of value sets to bind to placeholders in query.
     * @param id An ID that's used to help match this request with a particular reply.
     * The @c %DataAccessReply will contain this ID. Defaults to 0 if not specified.
     *
     * @since BlackBerry 10.0.0
     */
    void executeBatch(const QString& query, const QVariantList& valuesTable, int id = 0);

    /*!
     * @brief Begins an SQL transaction that contains multiple commands.
     *
     * Typically, each SQL command is executed as an independent transaction (that is,
     * commands are executed in autocommit mode). Any changes are committed when the command
     * ends, or are rolled back (discarded) if the command ends with an error. The
     * beginTransaction() function will take this database connection out of autocommit mode
     * for the duration of this transaction.
     *
     * @param id An ID that's used to help match this request with its reply. The
     * @c DataAccessReply will contain this ID. Defaults to 0 if not specified.
     *
     * @since BlackBerry 10.0.0
     */
    void beginTransaction(int id = 0);

    /*!
     * @brief Completes an SQL transaction as successful.
     *
     * Any changes will be committed to the database. The database connection will return
     * to autocommit mode (that is, each command will be a separate transaction).
     *
     * @param id An ID that's used to help match this request with its reply. The
     * @c DataAccessReply will contain this ID. Defaults to 0 if not specified.
     *
     * @since BlackBerry 10.0.0
     */
    void endTransaction(int id = 0);

    /*!
     * @brief Completes an SQL transaction as a failure and discards any changes.
     *
     * The database connection will return to autocommit mode (that is, each command
     * will be a separate transaction).
     *
     * @param id An ID that's used to help match this request with its reply. The
     * @c DataAccessReply will contain this ID. Defaults to 0 if not specified.
     *
     * @since BlackBerry 10.0.0
     */
    void rollbackTransaction(int id = 0);

private:
    /*! @cond PRIVATE */
    Q_DECLARE_PRIVATE(SqlConnection)
    Q_DISABLE_COPY(SqlConnection)
    /*! @endcond */
}; // SqlConnection


class SqlWorkerPrivate;

/*!
 * @headerfile SqlConnection.hpp <bb/data/SqlWorker>
 *
 * @brief A worker that executes SQL commands in another thread.
 *
 * @xmlonly
 * <apigrouping group="Data management/Data Sources"/>
 * <library name="bbdata"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_DLL_PUBLIC SqlWorker : public AsyncWorker {
Q_OBJECT

public:
    /*!
     * @brief Constructs an @c SqlWorker object with the specified path to a database file
     * and parent.
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
    explicit SqlWorker(const QString& dbPath, QObject* parent = 0);

    /*!
     * @brief Constructs an @c SqlWorker object with the specified path to a database file,
     * connection name, and parent.
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
    SqlWorker(const QString& dbPath, const QString& connectionName, QObject* parent = 0);

    /*!
     * @brief Virtual destructor.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~SqlWorker();

    /*!
     * @brief Executes the specified SQL command.
     *
     * This function will ultimately be called when any of these functions are called:
     *   - @c AsyncDataAccess::execute()
     *   - @c AsyncDataAccess::executeAndWait()
     *   - @c SqlConnection::execute()
     *   - @c SqlConnection::executeAndWait()
     *   - @c SqlConnection::executeBatch()
     *   - @c SqlConnection::beginTransaction()
     *   - @c SqlConnection::endTransaction()
     *   - @c SqlConnection::rollbackTransaction()
     *
     * Internally, an instance of @c SqlDataAccess is used to execute SQL commands and, for
     * queries, to return the results in the @c replyData parameter.
     *
     * @param command The SQL string to be executed (other than transaction-related commands,
     * which are not strings).
     * @param replyData A previously created @c %DataAccessReply with the ID value populated
     * from the original call.
     *
     * @see AsyncWorker::execute(), SqlDataAccess::execute()
     *
     * @since BlackBerry 10.0.0
     */
    virtual void execute(const QVariant& command, bb::data::DataAccessReply* replyData);

private:
    /*! @cond PRIVATE */
    Q_DECLARE_PRIVATE(SqlWorker)
    Q_DISABLE_COPY(SqlWorker)
    /*! @endcond */
}; // SqlWorker

}
}

#endif /* BB_DATA_SQLCONNECTION_HPP */
