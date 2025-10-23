/*!
 * @copyright
 * Copyright BlackBerry Limited, 2014
 * BlackBerry Limited. All rights reserved.
 */

#ifndef BB_PLATFORM_ADARPDOMAIN_HPP
#define BB_PLATFORM_ADARPDOMAIN_HPP

#include <bb/platform/Global>
#include <bb/platform/DataLockState>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace platform
{

class AdarpDomainPrivate;

/**
 * @headerfile AdarpDomain.hpp <bb/platform/AdarpDomain>
 *
 * @brief A class that provides status and command control for AdarpDomain.
 *
 * @details Adarp, or Advanced Data At Rest Protection, is a feature
 *          that locks an enterprise work space when a device has
 *          been idle for a specified time period.  The AdarpDomain
 *          class provides functions to monitor status and request
 *          triggering DataLock.  All AdarpDomain objects provide
 *          access to a single instance of the underlying interface.
 *          This means that any AdarpDomain object requesting DataLock
 *          would trigger DataLock for all other AdarpDomain objects
 *          if any, as an example.
 *
 * @xmlonly
 * <apigrouping group="Platform/Security"/>
 * <library name="bbplatform"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.3.1
 */
class BB_PLATFORM_EXPORT AdarpDomain : public QObject
{
    Q_OBJECT

    /*!
     * @brief The current DataLock state.
     *
     * @see @c bb::platform::DataLockState
     *
     * @since BlackBerry 10.3.1
     */
    Q_PROPERTY( bb::platform::DataLockState::Type dataLockState READ dataLockState NOTIFY dataLockStateChanged FINAL )

    /*!
     * @brief The next DataLock time.
     *
     * @details The @c nextDataLockTime is the timestamp when the
     *          DataLock state will switch from @c LockPending to
     *          @c DataLocked.  If the DataLock state is not @c LockPending,
     *          this will be a null (invalid) timestamp.  Also @see
     *          @c DataLockState.
     *
     * @since BlackBerry 10.3.1
     */
    Q_PROPERTY( QDateTime nextDataLockTime READ nextDataLockTime NOTIFY nextDataLockTimeChanged FINAL )

public:

    /*!
     * @brief Constructs an @c AdarpDomain object.
     *
     * @details Information about the AdarpDomain status may be retrieved
     *          from the @c AdarpDomain object.
     *
     * @param parent The supplied parent is responsible for deleting this instance.
     *
     * @since BlackBerry 10.3.1
     */
    explicit AdarpDomain(QObject * parent = 0);

    /*!
     * @brief Destroys this @c AdarpDomain object.
     *
     * @since BlackBerry 10.3.1
     */
    virtual ~AdarpDomain();

    /*!
     * @brief Gets the current DataLock state.
     *
     * @details If DataLock is not enabled, this function returns @c NotLocked.
     *
     * @return DataLock state.
     *
     * @see @c bb::platform::DataLockState.
     *
     * @since BlackBerry 10.3.1
     */
    bb::platform::DataLockState::Type dataLockState() const;

    /*!
     * @brief Gets the timestamp for when the DataLock state will
     *        switch from @c LockPending to @c DataLocked.
     *
     * @details If DataLock state is not @c LockPending, function
     *          returns a null (invalid) timestamp.
     *
     * @return DataLock timestamp.
     *
     * @since BlackBerry 10.3.1
     */
    QDateTime nextDataLockTime() const;

Q_SIGNALS:

    /*!
     * @brief Emitted when the DataLock state has changed.
     *
     * @param oldState Previous DataLock state
     * @param newState New DataLock state
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.3.1
     */
    void dataLockStateChanged( bb::platform::DataLockState::Type oldState, bb::platform::DataLockState::Type newState );

    /*!
     * @brief Emitted when nextDataLockTime has changed.
     *
     * @param newDataLockTime The value of nextDataLockTime, or a
     *                        null (invalid) timestamp if DataLock
     *                        state has switched out of @c PendingLock
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.3.1
     */
    void nextDataLockTimeChanged( QDateTime newDataLockTime );

    /*!
     * @brief Emitted when a status response to a request has been received.
     *
     * @details The requestId is a unique identifier to be used to
     *          match this response to a previous request.
     *
     * @param requestId Unique identifier corresponding to a specific request
     * @param requestStatus Resultant status of request identified by @c requestId
     *                      @see errno.h
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.3.1
     */
    void responseReceived( QString requestId, int requestStatus );

public Q_SLOTS:

    /*!
     * @brief Sends a request to set DataLock.
     *
     * @details This function is called to set the DataLock state
     *          to @c DataLocked.
     *
     * @permission The caller must have the @c allow_request_lock
     *             permission to set DataLock.
     *
     * @param requestId A unique identifier for each requestDataLock request
     *
     * @ingroup Slots
     *
     * @return 0 if the request was sent successfully, -1 otherwise.
     *
     * @since BlackBerry 10.3.1
     */
    int requestDataLock( QString requestId );

    /*!
     * @brief Sends a request to extend the DataLock time.
     *
     * @details This function is called to request to extend the time
     *          before dataLockState will switch to the @c DataLocked
     *          state (i.e. delay the triggering to DataLocked state).
     *
     * @permission The caller must have the @c _sys_allow_extend_data_lock
     *             permission to extend the DataLock time.
     *
     * @param requestId A unique identifier for each extendDataLockTime request
     * @param interval Time by which to extend DataLock time, in seconds
     *
     * @ingroup Slots
     *
     * @return 0 if the request was sent successfully, -1 otherwise.
     *
     * @since BlackBerry 10.3.1
     */
    int extendDataLockTime( QString requestId, unsigned int interval );

private:
//!@cond PRIVATE
    Q_DISABLE_COPY(AdarpDomain)
    Q_DECLARE_PRIVATE(AdarpDomain)
    AdarpDomainPrivate * const d_ptr; // not a scoped ptr. see constructor.
//!@endcond
};

} // namespace platform
} // namespace bb

QML_DECLARE_TYPE(bb::platform::AdarpDomain)
#endif // BB_PLATFORM_ADARPDOMAIN_HPP
