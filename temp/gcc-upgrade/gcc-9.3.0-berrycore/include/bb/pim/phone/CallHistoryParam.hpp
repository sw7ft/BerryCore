/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2014
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_PHONE_CALL_HISTORY_PARAM_HPP
#define BB_PIM_PHONE_CALL_HISTORY_PARAM_HPP

#include <QSharedDataPointer>

#include <bb/pim/Global>

namespace bb {
namespace pim {
namespace phone {

class CallHistoryParamPrivate;

/*!
 * @brief Supplemental parameters for querying call history
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
class BB_PIM_EXPORT CallHistoryParam
{
public:
    /*!
     * @brief Default Constructor.
     *
     * @since BlackBerry 10.3.0
     */
    CallHistoryParam();

    /*!
     * @brief Destroys this @c CallHistoryParam.
     *
     * @since BlackBerry 10.3.0
     */
    ~CallHistoryParam();

    /*!
     * @brief Copy constructor.
     *
     * @details This constructor initializes this @c CallHistoryParam with the values
     * from the provided @c CallHistoryParam.
     *
     * @param other The @c CallHistoryParam to be copied.
     *
     * @since BlackBerry 10.3.0
     */
    CallHistoryParam(const CallHistoryParam& other);

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c CallHistoryParam into this
     * @c CallHistoryParam.
     *
     * @param other The @c CallHistoryParam to be copied.
     *
     * @since BlackBerry 10.3.0
     */
    CallHistoryParam& operator=(const CallHistoryParam& other);

    /*!
     * @brief Set whether or not the fetch will search for potential contacts for the resulting CallEntry objects.
     *
     * @param search if true, then the fetch operation will attempt to search and return the candidate contacts that might
     * have made the call.
     *
     * By default, this is false.
     *
     * @since BlackBerry 10.3.0
     */
    void setContactSearchEnabled(bool search);


    /*!
     * @brief Retrieve whether or not the fetch will search for potential contacts for the resulting CallEntry objects.
     *
     * @return Whether or not the fetch will search for potential contacts for the resulting CallEntry objects.
     *
     * @since BlackBerry 10.3.0
     */
    bool contactSearchEnabled() const;

    // add more here...
private:
    QSharedDataPointer<CallHistoryParamPrivate> d_ptr;
    friend class CallHistoryParamPrivate;
};

} // namespace phone
} // namespace pim
} // namespace bb

#endif /* BB_PIM_PHONE_CALL_HISTORY_PARAM_HPP */