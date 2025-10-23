/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2014
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_PHONE_CALL_HISTORY_FILTER_HPP
#define BB_PIM_PHONE_CALL_HISTORY_FILTER_HPP

#include <bb/pim/phone/CallAttribute>
#include <bb/pim/phone/CallEntry>
#include <bb/pim/phone/CallType>
#include <bb/pim/phone/SortOrder>

#include <QDateTime>
#include <QStringList>
#include <QSharedDataPointer>

namespace bb {
namespace pim {
namespace phone {

class CallHistoryFilterPrivate;

/*!
 * @brief @c CallHistoryFilter provides a way to parameterize which calls are fetched.
 *
 * @details This class allows you to specify which @c CallEntry you care about during
 * a fetch via @c CallHistoryService::callHistory.
 *
 * @see CallHistoryService
 *
 * @xmlonly
 * <apigrouping group="App Integration/Phone"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.3.0
 */
class BB_PIM_EXPORT CallHistoryFilter
{
public:
    /*!
    * @brief Creates an new filter.
    *
    * @details A default constructed filter will not filter out any calls.
     *
     * @since BlackBerry 10.3.0
    */
    CallHistoryFilter();

    /*!
     * @brief Copy constructor.
     *
     * @details This operator copies all values from the provided @c CallHistoryFilter into this
     * @c CallHistoryFilter
     *
     * @param other The @c CallHistoryFilter to be copied.
     *
     * @since BlackBerry 10.3.0
     */
    CallHistoryFilter(const CallHistoryFilter& other);

    /*!
     * @brief Destroys this @c CallHistoryFilter.
     *
     * @since BlackBerry 10.3.0
     */
    ~CallHistoryFilter();

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c CallHistoryFilter into this
     * @c CallHistoryFilter
     *
     * @param other The @c CallHistoryFilter to be copied.
     *
     * @since BlackBerry 10.3.0
     */
    CallHistoryFilter& operator=(const CallHistoryFilter& other);

    /*!
     * @brief Apply a "latest" filter.
     *
     * @details When a valid datetime is set, the filter will cause fetch operations to return
     * CallEntry whose start date occured on or before dt.
     * A default constructed @c CallHistoryFilter has this filter disabled
     *
     * @param dt The QDateTime to apply for the "latest" filter. An invalid QDateTime
     * (i.e. a default constructed QDateTime) disables this filter
     *
     * @since BlackBerry 10.3.0
     */
    void setLatest(const QDateTime& dt);

    /*!
     * @brief Get the QDateTime that represents the "latest" filter.
     *
     * @return the QDateTime value of the "latest" filter
     *
     * @see CallHistoryFilter::setLatest
     *
     * @since BlackBerry 10.3.0
     */
    QDateTime latest() const;

    /*!
     * @brief Apply an "earliest" filter.
     *
     * @details When a valid datetime is set, the filter will cause fetch operations to return
     * CallEntry whose start date occured on or after dt.
     * A default constructed @c CallHistoryFilter has this filter disabled.
     *
     * @param dt The QDateTime to apply for the "earliest" filter. An invalid QDateTime
     * (i.e. a default constructed QDateTime) disables this filter.
     *
     * @since BlackBerry 10.3.0
     */
    void setEarliest(const QDateTime& dt);

    /*!
     * @brief Get the QDateTime that represents the "earliest" filter
     *
     * @return the QDateTime value of the "earliest" filter
     *
     * @see CallHistoryFilter::setEarliest
     *
     * @since BlackBerry 10.3.0
     */
    QDateTime earliest() const;

    /*!
     * @brief Conveniently set the earliest and latest filter in one API call.
     *
     * @param earliest The QDateTime to apply for the "earliest" filter.
     *
     * @param latest The QDateTime to apply for the "latest" filter.
     *
     * @see CallHistoryFilter::setEarliest, CallHistoryFilter::setLatest
     *
     * @since BlackBerry 10.3.0
     */
    void setDateRange(const QDateTime& earliest, const QDateTime& latest);

    /*!
     * @brief Apply call log type filter.
     *
     * @details See @c CallType for the available types.
     *
     * @param typeList A list of accepted types. If list is empty, this filter is not applied.
     * By default, this is empty.
     *
     * @warning CallType::Unknown is ignored; it will not affect the filtering process
     *
     * @see CallType, CallTypeList
     *
     * @since BlackBerry 10.3.0
     */
    void setTypeFilter(const CallTypeList& typeList);
    /*!
     * @brief Fetch the type filter.
     *
     * @details See @c CallType for the available types.
     *
     * @return the list that represents the "type" filter.
     *
     * @see CallType, CallTypeList
     *
     * @since BlackBerry 10.3.0
     */
    CallTypeList typeFilter() const;

    /*!
     * @brief Apply an ID filter.
     *
     * @details The filter will exclude any calls whose IDs are not in the list.
     *
     * @param idList List of CallEntry Log IDs. If this list is empty, this filter is not applied
     * By default, this is empty.
     *
     * @since BlackBerry 10.3.0
     */
    void setIdFilter(const QList<CallEntryId>& idList);

    /*!
     * @brief Fetch the ID filter.
     *
     * @return the list that represents the "ID" filter.
     *
     * @since BlackBerry 10.3.0
     *
     */
    QList<CallEntryId> idFilter() const;

    /*!
     * @brief Set offset to start query of this @c CallHistoryFilter.
     *
     * @details Offset filters out the results of the fetch whose rank value is less than
     * the offset.
     *
     * Rank in this context refers to the order in which the results *would* have been
     * returned based on the filter and sorting criteria.
     *
     * Offset and limit together allows your program to fetch @c CallEntry
     * in a paginated manner.
     *
     * @param offset The offset number to start searching from.
     *
     * @since BlackBerry 10.3.0
     */
    void setOffset(int offset);

    /*!
     * @brief Retrieve the offset of the query.
     *
     * @see CallHistoryFilter::setOffset
     *
     * @return the offset of the query.
     *
     * @since BlackBerry 10.3.0
     */
    int offset() const;

    /*!
     * @brief Sets the result limit of this @c CallHistoryFilter.
     *
     * @details This value represents the maximum number of results that are returned.
     * By default, this value is 0; a value of 0 represents no limit.
     *
     * @param limit The upper bound on the number of results to retrieve.
     *
     * @since BlackBerry 10.3.0
     */
    void setLimit(int limit);

    /*!
     * @brief Retrieve the limit of the query.
     *
     * @details This value represents the maximum number of results that are returned for the result.
     * By default, this value is 0; a value of 0 represents no limit.
     *
     * @return the limit of the query.
     *
     * @since BlackBerry 10.3.0
     */
    int limit() const;

    /*!
     * @brief Set the Sort order
     *
     * @details This value represents the direction in which the results will be sorted.
     * The default order is SortOrder::Ascending.
     *
     * @see CallAttribute::Type, SortOrder::Type
     *
     * @since BlackBerry 10.3.0
     */
    void setSortOrder(SortOrder::Type type);

    /*!
     * @brief Retrieve the Sort order.
     *
     * @details This value represents the direction in which the results will be sorted.
     *
     * @return the Sort order.
     *
     * @see CallAttribute::Type, SortOrder::Type
     *
     * @since BlackBerry 10.3.0
     */
    SortOrder::Type sortOrder() const;

    /*!
     * @brief Set the attribute in which the results will be sorted upon.
     *
     * @warning When the chosen sort is by @c CallAttribute::CallType, the sorting order may not necessarily
     * be the based on the ordinal value of enum @c CallType; however, the calls of the same type will be
     * placed together.
     *
     * @see CallAttribute::Type, SortOrder::Type
     *
     * @since BlackBerry 10.3.0
     */
    void setSortAttribute(CallAttribute::Type type);

    /*!
     * @brief Retrieve the attribute in which the results will be sorted upon.
     *
     * @return the attribute in which the results will be sorted upon.
     *
     * @see CallAttribute::Type, SortOrder::Type
     *
     * @since BlackBerry 10.3.0
     */
    CallAttribute::Type sortAttribute() const;

private:
    QSharedDataPointer<CallHistoryFilterPrivate> d_ptr;
    friend class CallHistoryFilterPrivate;
};

} // namespace phone
} // namespace pim
} // namespace bb

#endif /* BB_PIM_PHONE_CALL_HISTORY_FILTER_HPP */