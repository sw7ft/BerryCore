/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_ACCOUNT_RESULT_HPP
#define BB_PIM_ACCOUNT_RESULT_HPP

#include <bb/pim/Global>
#include <QString>
#include <QSharedDataPointer>
#include <QVariantMap>

namespace bb {
namespace pim {
namespace account {

class ResultPrivate;

/*!
 * @brief This class is used to return the outcome
 * of an operation requested from @c AccountService.
 *
 * @xmlonly
 * <apigrouping group="App Integration/Account"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT Result
{
public:
    /*!
     * @brief Represents the successful result.
     *
     * @details This error code is used when an operation was successful.
     *
     * @since BlackBerry 10.2.0
     */
    static const int NoError = 0;
    /*!
     * @brief Represents the internal error.
     *
     * @details This error code is used when an internal error occurred during an operation.
     *
     * @since BlackBerry 10.2.0
     */
    static const int InternalError = 10001;
    /*!
     * @brief Represents the "Invalid Provider" error.
     *
     * @details This error code is used when an operation was performed for an invalid provider.
     *
     * @since BlackBerry 10.2.0
     */
    static const int InvalidProvider = 10002;
    /*!
     * @brief Represents the "Unsupported API call" error.
     *
     * @details This error code is used when an unsupported API call was made.
     *
     * @since BlackBerry 10.2.0
     */
    static const int UnsupportedApiCall = 10003;
    /*!
     * @brief Represents the "Invalid Account Data" error.
     *
     * @details This error code is used when an invalid account data was provided.
     *
     * @since BlackBerry 10.2.0
     */
    static const int InvalidAccountData = 10004;

    /*!
     * @brief Creates a @c Result object.
     *
     * @param success The outcome of the requested operation.
     *
     * @param message A detailed error message when @c success is false,
     * and an empty string when @c success is true.
     *
     *
     * @since BlackBerry 10.0.0
     */
    Result(bool success, const QString &message = "");

    /*!
     * @brief Creates a @c Result object.
     *
     * @param success The outcome of the requested operation.
     *
     * @param message A detailed error message when @c success is false,
     * and an empty string when @c success is true.
     *
     * @param errorCode The code of an error occurred during the operation.
     * If there was no error then @c errorCode is 0.
     *
     * @since BlackBerry 10.2.0
     */
    Result(bool success, const QString &message, int errorCode);

    /*!
    * @brief Creates a @c Result object.
    *
    * @param success The outcome of the requested operation.
    *
    * @param message A detailed error message when @c success is false,
    * and an empty string when @c success is true.
    *
    * @param errorCode The code of an error occurred during the operation.
    * If there was no error then @c errorCode is 0.
    *
    * @param errorChallengeUrl Contains a string of the errorChallengeUrl.
    *
    * @since BlackBerry 10.2.0
    */
    Result(bool success, const QString &message, int errorCode, const QString &errorChallengeUrl);


    /*!
     * @brief Destructor.
     *
     * @since BlackBerry 10.0.0
     */
    ~Result();

    /*!
     * @brief Creates a copy of an existing @c Result object.
     *
     * @return other The @c Result object to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    Result(const Result &other);

    /*!
     * @brief Copies the data of an existing @c Result object to this object.
     *
     * @param other The @c Result object to be copied.
     *
     * @return Returns the @c Result instance.
     *
     * @since BlackBerry 10.0.0
     */
    Result& operator=(const Result &other);

    /*!
     * @brief Provides access to the @c Result object's @c message property.
     *
     * @return Returns the value of the @c Result object's @c message property.
     *
     * @since BlackBerry 10.0.0
     */
    QString message() const;

    /*!
     * @brief Provides access to the @c Result object's @c success property.
     *
     * @return Returns true when the operation is successful, and false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isSuccess() const;

    /*!
     * @brief Provides access to the @c Result object's @c errorCode property.
     *
     * @return Returns the value of the @c Result object's @c errorCode property.
     *
     * @since BlackBerry 10.2.0
     */
    int errorCode() const;

    /*!
     * @brief Provides access to the @c Result object's @c errorChallengeUrl. This will be set
     * in the event that an authentication attempt has been challenged.
     *
     * @return Returns the value of the @c Result object's @c errorChallengeUrl property.
     *
     * @since BlackBerry 10.2.0
     */
    QString errorChallengeUrl() const;

private:
    Result();
    void setSuccess(bool success);
    void setMessage(const QString &message);
    void setErrorCode(int);
    void setErrorChallengeUrl(const QString &errorChallengeUrl);
    bool unused;
    QSharedDataPointer<ResultPrivate> d_ptr;
};

} // namespace account
} // namespace pim
} // namespace bb

#endif // BB_PIM_ACCOUNT_RESULT_HPP
