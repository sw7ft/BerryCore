/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_NETWORK_PUSHSTATUS_HPP
#define BB_NETWORK_PUSHSTATUS_HPP

#include <bb/network/Global>

#include <QMetaType>
#include <QString>

namespace bb
{
namespace network
{

class PushStatusPrivate;

/*!
 * @headerfile PushStatus.hpp <bb/network/PushStatus>
 *
 * @brief Describes the status of a Push request.
 *
 * The @c code attribute, when greater than @c 0, indicates the reason
 * for the failure. The complete set of codes are defined in @c PushErrorCode.
 *
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Push"/>
 * <library name="bbnetwork"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */

class BB_NETWORK_EXPORT PushStatus {
public:
    /*!
     * @brief Constructs a @c PushStatus object.
     *
     * @return The @c PushStatus object.
     *
     *
     * @since BlackBerry 10.0.0
     */
    PushStatus();

    /*!
     * @brief Creates a new @c PushStatus object to store the response code from the PPG.
     *
     * @param code     The response code associated with the status.
     *
     *
     * @since BlackBerry 10.0.0
     */
    explicit PushStatus(int code);

    /*!
	 * @brief Creates a copy of of an existing @c PushStatus object.
	 *
	 * @param other The existing @c PushStatus object that will be copied.
	 *
     *
     * @since BlackBerry 10.0.0
	 */
    PushStatus(const PushStatus &other);

    /*!
     * @brief Copies the data from an existing @c PushStatus object.
     *
     * @param other The existing @c PushStatus object that will be copied.
     *
     * @return A new @c PushStatus object containing the copied data.
     *
     *
     * @since BlackBerry 10.0.0
     */
    PushStatus& operator=(const PushStatus &other);

    /*!
     * @brief Destroys this @c PushStatus object.
     *
     *
     * @since BlackBerry 10.0.0
     */
    ~PushStatus();

    /*! 
     * @brief Gets the response code associated with the @c PushStatus object.
     *
     * @return code    Returns the response code associated with the @c PushStatus.
     *                      @c 0 indicates a success, while any other value indicates a failure.
     *                      By calling @c errorDescription() on the @c PushStatus you can find out more
     *                      information about the error.
     *
     *
     * @since BlackBerry 10.0.0
     */
    int code() const;

    /*! 
     * @brief Gets the error description associated with the @c PushStatus object.
     *
     * @return errorDescription    Additional information about the error.
     *
     *
     * @since BlackBerry 10.0.0
     */
    QString errorDescription() const;

    /*! 
     * @brief Sets the response code.
     *
     * @param code     The response code associated with the status.
     *
     *
     * @since BlackBerry 10.0.0
     */
    void setCode(int code);

    /*! 
     * @brief Sets the error description.
     *
     * @param errorDescription     Error details associated with the status.
     *
     *
     * @since BlackBerry 10.0.0
     */
    void setErrorDescription(const QString &errorDescription);

    /*!
     * @brief Specifies whether the @c PushStatus contains an error.
     *
     * @return @c true if there is an error, @c false otherwise
     *
     *
     * @since BlackBerry 10.0.0
     */
    bool isError() const;

private:
    QScopedPointer<PushStatusPrivate> const d_ptr;
    Q_DECLARE_PRIVATE(PushStatus)
};

} // namespace network
} // namespace bb

Q_DECLARE_METATYPE(bb::network::PushStatus)

#endif /* BB_NETWORK_PUSHSTATUS_HPP */
