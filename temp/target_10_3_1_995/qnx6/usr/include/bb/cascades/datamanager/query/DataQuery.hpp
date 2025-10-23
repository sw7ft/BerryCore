/*!
 * @copyright
 * Copyright (C) 2013 BlackBerry Limited. All rights reserved.
 */

#ifndef BB_CASCADES_DATAMANAGER_DATAQUERY_HPP_
#define BB_CASCADES_DATAMANAGER_DATAQUERY_HPP_

#include <bb/cascades/datamanager/Global>
#include <bb/cascades/datamanager/DataItem>
#include <QDebug>
#include <QObject>
#include <QVariant>

namespace bb
{
namespace cascades
{
namespace datamanager
{

class DataQueryPrivate;

/*!
 * @headerfile DataQuery.hpp <bb/cascades/datamanager/DataQuery>
 *
 * @brief Retrieve data for a particular view of a data source.
 *
 * This class supports concepts like keys, overall revisions, item revisions,
 * and partial caching (using offset and limit) so that data models
 * can use this to maintain a window of data in memory (the cache)
 * consistent with a potentially much larger overall set of data
 * in persistent storage.
 *
 * To implement this class, you must decide how to handle error conditions. If there
 * are SQL or other expected or unexpected runtime errors, you must determine
 * which of these errors are catastrophic and which are recoverable.
 *
 * Catastrophic errors can be dealt with by these steps:
 * - Connect the application to the @c error() signal
 * - @c Query issues an error signal and returns @c false
 * - The application detects that the error is unrecoverable
 * - The application informs the users of the issue and remedies (if any)
 * - The user is instructed to terminate the application
 *
 * Recoverable errors may be dealt with in a few ways. It may depend
 * on whether the data is required or optional for the application to
 * function. It may also depend on whether retries might be effective, either
 * immediately, after a certain time has elapsed, or when the user wishes
 * to trigger a retry.
 *
 * For recoverable errors handled by @c Query, the steps may look like this:
 * - @c Query detects an error and performs a finite number (N) of retries
 * - If retry is successful then query returns @c true
 * - If N retries fail, then query emits an error and returns @c false
 * - The application informs the users of the issue and remedies (if any)
 * - The user is instructed to ignore the error (if optional data) or to
 *    terminate the application
 *
 * For recoverable errors handled by the application, the steps may look like this:
 * - Connect the application to the @c error() signal
 * - @c Query issues an error signal and returns @c false
 * - The application detects that the error is recoverable
 * - The application informs the users of the issue and remedies (if any)
 * - The user is instructed to initiate retries or ignore the error (if optional data)
 *    or to terminate the application
 *
 * To trigger a retry for a recoverable error, use one of these methods:
 * - Emit the @c DataQuery::dataChanged() signal.
 * - Call the model @c load() method.
 *
 * @xmlonly
 * <apigrouping group="Data Management/Large Data Sets"/>
 * <library name="bbcascadesdatamanager"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_CASCADES_DATAMANAGER_EXPORT DataQuery : public QObject
{
    Q_OBJECT

public:
    /*!
     * @brief Constructs a @c DataQuery.
     *
     * @param parent The parent owner or 0. Optional and defaults to 0 if not specified.
     *
     * @since BlackBerry 10.2.0
     */
    explicit DataQuery(QObject *parent = 0);

    /*!
     * @brief Destructor.
     *
     * @since BlackBerry 10.2.0
     */
    virtual ~DataQuery();

    /*!
     * @brief Fetch the overall revision, total count, and a range of data items from the data source.
     *
     * This is a synchronous call, but it must be possible to safely call this method from any thread.
     *
     * See the discussion about error handling in the class description. A return of
     * @c false by this method should be preceded by the query emitting an error signal. This signal
     * should be handled at the application level, leading to some appropriate action.
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
            int *totalCount, QList<DataItem> *results) = 0;

    /*!
     * @brief Fetch the data items from the data source if the data source is at the requested revision.
     *
     * This is a synchronous call, but it must be safe to call this method from any thread.
     *
     * See the discussion about error handling in the class description. A return of
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
     * If the data source does not match this revision, this method returns @c false.
     * @param[out] results The list of data items which is the return data. This pointer must not be null.
     *
     * @return @c True if the data could be successfully retrieved at the requested revision,
     * @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    virtual bool getDataForRevision(int offset, int limit,
            const DataRevision &requestedRevision, QList<DataItem> *results) = 0;

    /*!
     * @brief Get a string representation of the query, for debugging purposes.
     *
     * @return The string.
     *
     * @since BlackBerry 10.2.0
     */
    virtual QString toString() const = 0;

Q_SIGNALS:
    /*!
     * @brief Emitted when the data changes.
     *
     * @param revision The revision of the latest source data.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.2.0
     */
    void dataChanged(DataRevision revision);

    /*!
     * @brief Emitted when an error occurs when executing the query.
     *
     * @param code The error code.
     * @param message The error message.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.2.0
     */
    void error(int code, const QString& message);

protected:
    /*! @cond PRIVATE */
    DataQuery(DataQueryPrivate &dd, QObject *parent = 0);
    DataQueryPrivate * const d_ptr;

    Q_DECLARE_PRIVATE(DataQuery)
    Q_DISABLE_COPY(DataQuery)
    /*! @endcond */
};

QDebug operator<<(QDebug dbg, const DataQuery *p);

} // datamanager
} // cascades
} // bb

#endif /* BB_CASCADES_DATAMANAGER_DATAQUERY_HPP_ */
