/**
 * @copyright
 * Copyright BlackBerry Limited, 2011-2013
 * BlackBerry Limited. All rights reserved.
 */


#ifndef BB_DATA_ASYNCDATAACCESS_HPP
#define BB_DATA_ASYNCDATAACCESS_HPP

#include <bb/data/DataAccessReply>
#include <bb/Global>
#include <QObject>
#include <QScopedPointer>
#include <QThread>
#include <QVariant>

namespace bb {
namespace data {

class AsyncDataAccessPrivate;
class AsyncWorker;

/*!
 * @headerfile AsyncDataAccess.hpp <bb/data/AsyncDataAccess>
 *
 * @brief Allows communication with an asynchronous worker in another thread.
 *
 * The @c AsyncDataAccess class allows an application to communicate with
 * an asynchronous worker object that's performing long-running operations
 * while running in another thread.

 * @see @c SqlConnection for examples of usage.
 *
 * @xmlonly
 * <apigrouping group="Data management/Data Sources"/>
 * <library name="bbdata"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_DLL_PUBLIC AsyncDataAccess : public QObject
{
    Q_OBJECT

public:
    /*!
     * @brief Constructs a data access "service" object which will run the given
     * worker task in another thread.
     *
     * If not 0, the ownership of this object will be transferred to the parent.
     * Also, ownership of the worker will always be managed by this async framework
     * and so the ownership of the worker will be transferred to an internal
     * object in this framework which has affinity for the new thread.
     *
     * @param worker The class which will execute work in another thread.
     * @param parent The parent owner or 0. Optional and will default to 0 if not specified.
     *
     * @since BlackBerry 10.0.0
     */
    explicit AsyncDataAccess(AsyncWorker* worker, QObject* parent = 0);

    /*!
     * @brief Virtual destructor
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~AsyncDataAccess();

    /*!
     * @brief Starts the asynchronous worker in another thread, ready to accept work.
     *
     * If not started explicitly, the worker will be started when the first work is
     * executed.
     *
     * @param priority The priority of the thread, specified by @c QThread::Priority.
     * The default value is @c QThread::LowPriority.
     *
     * @since BlackBerry 10.0.0
     */
    void start(QThread::Priority priority = QThread::LowPriority);

    /*!
     * @brief Passes the specified criteria data to the asynchronous worker and
     * queues for execution.
     *
     * This method returns immediately. Results will be returned in a
     * @c DataAccessReply object using the @c reply() signal in this class.
     *
     * If the thread has not been started, this method will call @c start().
     *
     * @param criteria The criteria data that is passed to the worker to specify the
     * work to be done.
     * @param id An ID that's used to help match this request with a particular reply.
     * The @c %DataAccessReply will contain this ID. Defaults to 0 if not specified.
     *
     * @since BlackBerry 10.0.0
     */
    void execute(const QVariant& criteria, int id = 0);

    /*!
     * @brief Passes the specified criteria data to the asynchronous worker for
     * execution.
     *
     * The current thread will block until a @c DataAccessReply object can be returned.
     *
     * If the thread has not been started, this function will call @c start().
     *
     * @param criteria The criteria data that is passed to the worker to specify the
     * work to be done.
     * @param id An ID that's used to help match this request with its reply. The
     * @c %DataAccessReply that's returned will contain this ID. Defaults to 0 if not
     * specified.
     *
     * @return A @c %DataAccessReply containing the results of the operation.
     *
     *
     * @since BlackBerry 10.0.0
     */
    DataAccessReply executeAndWait(const QVariant& criteria, int id = 0);

    /*!
     * @brief Stops the thread that's performing the asynchronous work.
     *
     * You can call @c start() again to initiate a new thread using the same
     * async worker.
     *
     * @since BlackBerry 10.0.0
     */
    void stop();

    /*!
     * @brief Indicates whether the thread that's performing the asynchronous work is
     * currently running.
     *
     * @return @c true if the thread is currently running, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isRunning();


Q_SIGNALS:
    /*!
     * @brief Emitted when an asynchronous execute operation has completed and has
     * results to return.
     *
     * @param replyData The reply data from the execute operation.
     *
     * @since BlackBerry 10.0.0
     */
    void reply(const bb::data::DataAccessReply& replyData);

protected:
    /*! @cond PRIVATE */
    AsyncDataAccess(AsyncDataAccessPrivate &_d_ptr, QObject* parent);
    QScopedPointer<AsyncDataAccessPrivate> d_ptr;

private:
    Q_DECLARE_PRIVATE(AsyncDataAccess)
    Q_DISABLE_COPY(AsyncDataAccess)
    /*! @endcond */

}; // AsyncDataAccess


class AsyncWorkerPrivate;

/*!
 * @headerfile AsyncDataAccess.hpp <bb/data/AsyncWorker>
 *
 * @brief Represents objects that do asynchronous work.
 *
 * You can extend this class and pass it to an @c AsyncDataAccess object
 * and it will perform the work in another thread.
 *
 * An @c %AsyncWorker is expected to perform multiple operations with
 * commands being passed to it using one of the execute functions
 * in @c %AsyncDataAccess.
 *
 * See @c SqlWorker for a concrete example of how this can be used.
 *
 * @xmlonly
 * <apigrouping group="Data management/Data Sources"/>
 * <library name="bbdata"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_DLL_PUBLIC AsyncWorker : public QObject
{
    Q_OBJECT
public:
    /*!
     * @brief Constructs a worker that will perform asynchronous work.
     *
     * Ownership will be managed by the async framework. The object ownership
     * will be transferred to an internal object within this framework.
     *
     * @param parent The parent owner. Do not specify as ownership will be overridden.
     *
     * @since BlackBerry 10.0.0
     */
    explicit AsyncWorker(QObject* parent = 0);

    /*!
     * @brief Virtual destructor.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~AsyncWorker();

    /*!
     * @brief Executes a task asynchronously in another thread provided by
     * @c AsyncDataAccess.
     *
     * This method will ultimately be called when either
     * @c AsyncDataAccess::execute() or @c AsyncDataAccess::executeAndWait() is
     * called.
     *
     * @param criteria The work to be performed such as an SQL query command.
     * @param replyData An output parameter, which is a pointer to an object that is updated
     * with work results.
     *
     * @since BlackBerry 10.0.0
     */
    virtual void execute(const QVariant& criteria, bb::data::DataAccessReply* replyData) = 0;

protected:
    /*! @cond PRIVATE */
    AsyncWorker(AsyncWorkerPrivate &_d_ptr, QObject* parent = 0);
    QScopedPointer<AsyncWorkerPrivate> d_ptr;

private:
    Q_DECLARE_PRIVATE(AsyncWorker)
    Q_DISABLE_COPY(AsyncWorker)
    /*! @endcond */
}; // AsyncWorker

}
}

#endif /* BB_DATA_ASYNCDATAACCESS_HPP */
