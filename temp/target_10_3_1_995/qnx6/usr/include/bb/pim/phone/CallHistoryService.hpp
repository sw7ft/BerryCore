/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2014
 * Research In Motion Limited. All rights reserved.
 */
#ifndef BB_PIM_PHONE_CALL_HISTORY_SERVICE_HPP
#define BB_PIM_PHONE_CALL_HISTORY_SERVICE_HPP

#include <bb/pim/account/Account>
#include <bb/pim/phone/CallEntry>
#include <bb/pim/phone/CallHistoryFilter>
#include <bb/pim/phone/CallHistoryParam>
#include <bb/pim/phone/CallEntryResult>
#include <bb/pim/phone/CallHistoryError>

namespace bb {
namespace pim {
namespace phone {

class CallHistoryServicePrivate;
/*!
 * @brief @c CallHistoryService provides a way to inspect into the history of recently made calls.
 *
 * @details @c CallHistoryService provides a way to fetch @c CallEntry objects. These objects represent a history of
 * calls that have been made. These objects are also known as call logs.
 *
 * @xmlonly
 * <apigrouping group="App Integration/Phone"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.3.0
 */
class BB_PIM_EXPORT CallHistoryService : public QObject
{
Q_OBJECT
public:
    /*!
     * @brief Retrieves the default call log account
     *
     * @return An account object that represents the default Call History account
     *
     * @since BlackBerry 10.3.0
     */
    static bb::pim::account::Account defaultAccount();

    /*!
     * @brief Construct a new @c CallHistoryService.
     *
     * @since BlackBerry 10.3.0
     */
    CallHistoryService();

    /*!
     * @brief Destroys this @c CallHistoryService.
     *
     * @since BlackBerry 10.3.0
     */
    ~CallHistoryService();

    /*!
     * @brief Fetch a list of made calls.
     *
     * @details Retrieve a list of calls based on the criteria set out by filter.
     *
     * @param accountId The ID of the account that is responsible for logging this call.
     *
     * @param filter A @c CallHistoryFilter that represents the criteria of calls to be fetched
     * If you want all of the calls, pass in a default constructed @c CallHistoryFilter.
     *
     * @param extra A @c CallHistoryParam that represents extra parameters that do not
     * pertain to filtering.
     *
     * @param [out] presult An optional parameter to store the result of the operation. The values
     * for the result are defined in @c CallHistoryError.
     * Supply NULL if you don't care about the error value.
     * Possible values:
     *  - CallHistoryError::Unknown
     *  - CallHistoryError::None
     *
     * @return A list of @c CallEntryResult under the provided filter
     *
     * @see CallHistoryFilter, CallHistoryParam
     *
     * @since BlackBerry 10.3.0
     */
    QList<CallEntryResult> callHistory(bb::pim::account::AccountKey accountId,
                                const CallHistoryFilter &filter,
                                const CallHistoryParam& extra=CallHistoryParam(),
                                CallHistoryError::Type *presult=NULL) const;
    /*!
     * @brief Fetch a particular @c CallEntry by ID.
     *
     * @details This version is equivalent to calling @c CallHistoryService::callHistory that
     * accepts a @c CallHistoryFilter, where the @c CallHistoryFilter contains a ID filter of the targeted ID.
     *
     * @param accountId The ID of the account that is responsible for logging this call.
     *
     * @param extra A @c CallHistoryParam that represents extra parameters that do not
     * pertain to filtering.
     *
     * @param [out] presult An optional parameter to store the result of the operation. The values
     * for the result are defined in @c CallHistoryError.
     * Supply NULL if you don't care about the error value.
     * Possible values:
     *  - CallHistoryError::Unknown
     *  - CallHistoryError::DoesNotExist
     *  - CallHistoryError::None
     *
     * @see CallHistoryFilter, CallHistoryParam
     *
     * @return A @c CallEntryResult with @C CallEntryId id. If the ID is invalid,
     * the returned @c CallEntryResult will contain an invalid @c CallEntry
     *
     * @since BlackBerry 10.3.0
     */
    CallEntryResult callHistory(bb::pim::account::AccountKey accountId,
                                  CallEntryId id,
                                  const CallHistoryParam& extra=CallHistoryParam(),
                                  CallHistoryError::Type *presult=NULL) const;
Q_SIGNALS:
    /*!
     * @brief Emitted when new calls are logged.
     *
     * @param accountId The ID of the account where the call is being logged.
     *
     * @param idList The list of IDs corresponding to the new calls.
     *
     * @since BlackBerry 10.3.0
     */
    void callHistoryAdded(bb::pim::account::AccountKey accountId,
                          bb::pim::phone::CallEntryIdList idList);
    /*!
     * @brief Emitted when call logs are deleted.
     *
     * @param accountId The ID of the account where the call log is being deleted.
     *
     * @param idList The list of IDs corresponding to the deleted call logs.
     *
     * @since BlackBerry 10.3.0
     */
    void callHistoryDeleted(bb::pim::account::AccountKey accountId,
                            bb::pim::phone::CallEntryIdList idList);
private:
    QScopedPointer<CallHistoryServicePrivate> d_ptr;
    Q_DISABLE_COPY(CallHistoryService);
    Q_DECLARE_PRIVATE(CallHistoryService);
};


} // namespace phone
} // namespace pim
} // namespace bb

#endif /* BB_PIM_PHONE_CALL_HISTORY_SERVICE_HPP */