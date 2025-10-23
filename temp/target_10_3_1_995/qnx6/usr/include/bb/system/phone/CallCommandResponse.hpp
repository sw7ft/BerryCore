/*!
 * @file CallCommandResponse.hpp
 * @copyright
 * Copyright (C) 2013 BlackBerry Limited. All rights reserved.
 */


#ifndef BB_SYSTEM_PHONE_CALLCOMMANDRESPONSE_HPP
#define BB_SYSTEM_PHONE_CALLCOMMANDRESPONSE_HPP

#include <bb/system/Global>

#include <QSharedDataPointer>

namespace bb
{
namespace system
{
namespace phone
{

class CallCommandResponsePrivate;

/*!
 * @headerfile CallCommandResponse.hpp <bb/system/phone/CallCommandResponse>
 *
 * @brief Provides information about a call command response.
 *
 * An instance of the @c CallCommandResponse class is provided through the @c Phone::callCommandResponseReceived() signal
 * to deliver information to the client about the network response to a call command.
 *
 * The call command response includes information such as the call command, response ID,
 * call ID, and error.
 *
 * @permissions You must specify the @c control_phone permission in your bar-descriptor.xml file.
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Phone"/>
 * <library name="bbsystem"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2
 */

class BB_SYSTEM_EXPORT CallCommandResponse
{
public:

    /*!
     * @brief Constructs an invalid @c CallCommandResponse object.
     *
     * @since BlackBerry 10.2
     */
    CallCommandResponse();

    /*!
     * @brief Creates a copy of @c other.
     *
     * @param other The source @c CallCommandResponse object.
     *
     * @since BlackBerry 10.2
     */
    CallCommandResponse(const CallCommandResponse &other);

    /*!
     * @brief Copies another @c CallCommandResponse to this object.
     *
     * @param other The source @c CallCommandResponse object.
     * @return The @c CallCommandResponse instance.
     *
     * @since BlackBerry 10.2
     */
    CallCommandResponse& operator=(const CallCommandResponse &other);

    /*!
     * @brief Compares another @c CallCommandResponse to this object.
     *
     * @param other A @c CallCommandResponse object for comparison.
     * @return @c true if call id matches, @c false otherwise.
     *
     * @since BlackBerry 10.2
     */
    bool operator==(const CallCommandResponse &other);

    /*!
     * @brief Destroys this @c CallCommandResponse object.
     *
     * @since BlackBerry 10.2
     */
    ~CallCommandResponse();

    /*!
      * @brief Returns the command that the response is for.
      *
      * @return The call command.
      *
      * @since BlackBerry 10.2
      */
    QString callCommand() const;
    /*!
      * @brief  Returns the command response ID that matches the ID used to send the call command.
      *
      * The returned ID will match the ID used to send the call command.
      *
      * @return The command ID.
      *
      * @since BlackBerry 10.2
      */
    int responseId() const;
    /*!
     * @brief Returns the unique ID of the call that the response is for.
     *
     * @return A non-negative ID of the call if the @c CallCommandResponse object is
     * valid, or @c -1 if the object is invalid.
     *
     * @since BlackBerry 10.2
     */
    int callId() const;
    /*!
     * @brief Returns the error code related to a command executed on a call.
     *
     * @return The error returned when executing the call command, or an empty string
     * if the command was executed successfully.
     *
     * @since BlackBerry 10.2
     *
     */
    QString error() const;

private:
    //!@cond PRIVATE
    friend class CallCommandResponsePrivate;

    QSharedDataPointer<CallCommandResponsePrivate> d_ptr;  /*!< private implementation */
    //!@endcond

};

} // phone
} // system
} // bb

Q_DECLARE_METATYPE(bb::system::phone::CallCommandResponse)

#endif /* BB_SYSTEM_PHONE_CALLCOMMANDRESPONSE_HPP */

