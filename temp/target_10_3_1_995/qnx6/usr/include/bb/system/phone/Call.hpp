/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_PHONE_CALL_HPP
#define BB_SYSTEM_PHONE_CALL_HPP

#include <bb/system/phone/CallAction>
#include <bb/system/phone/CallState>
#include <bb/system/phone/CallType>
#include <bb/system/phone/LineType>
#include <bb/system/Global>

#include <QSharedDataPointer>

namespace bb
{
namespace system
{
namespace phone
{

class CallPrivate;


/*!
 * @headerfile Call.hpp <bb/system/phone/Call>
 *
 * @brief Provides a call's ID, state, and type information.
 *
 * When an outgoing call is initiated through a @c Phone object, an instance of this class will be returned to
 * represent the initiated call. If the @c isValid() function of the object returns @c true, the client of this object
 * can start to access other properties of the object.
 *
 * An instance of the @c Call class will also be provided through the @c Phone::callUpdated() signal
 * to provide information about an incoming call or update the state of an existing call.
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Phone"/>
 * <library name="bbsystem"/>
 * @endxmlonly
 *
 * @permissions You must also specify the @c access_phone permission in your bar-descriptor.xml file.
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT Call
{
public:
    /*!
     * @brief Constructs an invalid @c Call object.
     *
     * @since BlackBerry 10.0.0
     */
    Call();

    /*!
     * @brief Creates a copy of @c other.
     *
     * @param other The source @c Call object.
     *
     * @since BlackBerry 10.0.0
     */
    Call(const Call &other);

    /*!
     * @brief Copies another @c Call to this object.
     *
     * @param other The source @c Call object.
     * @return The @c Call instance.
     *
     * @since BlackBerry 10.0.0
     */
    Call& operator=(const Call &other);

    /*!
     * @brief Compares another @c Call to this object.
     *
     * @param other A @c Call object for comparison.
     * @return @c true if call id matches, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool operator==(const Call &other);

    /*!
     * @brief Destroys this @c Call object.
     *
     * @since BlackBerry 10.0.0
     */
    ~Call();

    /*!
     * @brief Returns the unique ID of the call.
     *
     * @return A non-negative ID of the call if the @c Call object is valid, or @c -1 if the object is invalid.
     *
     * @since BlackBerry 10.0.0
     */
    int callId() const;

    /*!
     * @brief Returns the state of the call, as defined by @c CallState::Type.
     *
     * @return The state of the call. If the @c Call object is invalid, the return value is undefined.
     *
     * @since BlackBerry 10.0.0
     */
    CallState::Type callState() const;

    /*!
     * @brief Returns the type of the call, as defined by @c CallType::Type.
     *
     * @return The type of the call. If the @c Call object is invalid, the return value is undefined.
     *
     * @since BlackBerry 10.0.0
     */
    CallType::Type callType() const;

    /*!
     * @brief Returns the line of the call, as defined by @c LineType::Type.
     *
     * @return The line of the call. If the @c Call object is invalid, the return value is undefined.
     *
     * @since BlackBerry 10.3.0
     */
    LineType::Type callLine() const;

    /*!
     * @brief Returns the phone number of the remote end of the call.
     *
     * @details Returns the phone number of the remote end if the client has read_phonecall_details permission,
     * returns an empty string otherwise.The phone number is considered to be sensitive data, it will be delivered
     * to a client which has the permission. The remote number is the number on the other end of the call. In the case
     * of an outgoing call, it is the number that is being called. In the case of an incoming call, it is the number
     * that is doing the calling. If the call type is "multiparty", phoneNumber() will return an empty string.
     * Note: The application that is asking for the phone number needs to be running in the same perimeter as the line
     * that the call is on. As an example, an application running on the work perimeter will not have access to the phone
     * number on a cellular call. Analogously, an application running on the personal perimeter will not have access to
     * the phone number related to a call on a work line, e.g. a SecuVOICE call. Moreover, for an incoming call on the
     * cellular line, the phone number will be delivered formatted. For an outgoing call, the phone number will be first
     * delivered not formatted on the cellular line. After formatting has been applied to it, the subsequent call updates
     * will have the formatted phone number.
     *
     * @return The phone number of the remote end of the call. If the @c Call object is invalid, the return value is undefined.
     *
     * @permissions The application must have the @c read_phonecall_details permission to use this feature.
     *
     * @since BlackBerry 10.3.0
     */
    QString phoneNumber() const;

    /*!
     * @brief Indicates whether this object is valid or not. In general, the properties of this object should be
     * accessed only when the object is valid.
     *
     * @return @c true if this @c Call object contains valid information about a call, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

    /*!
     * @brief Checks whether a given action can be performed on the call.
     *
     * @param action A call action
     *
     * @return @c true if the given @c CallAction can be performed on the call.
     *
     * @permissions The application must have the @c read_phonecall_details permission to use this feature.
     *
     * @since BlackBerry 10.3.0
     */
    bool canPerformAction(CallAction::Type action) const;

private:
    //!@cond PRIVATE
    friend class CallPrivate;

    Call(const QSharedDataPointer<CallPrivate> &d_other);

    QSharedDataPointer<CallPrivate> d_ptr;  /*!< private implementation */
    //!@endcond

//    Q_DECLARE_PRIVATE(Call)
//    Q_DISABLE_COPY(Call)
};

} // bb
} // system
} // phone

Q_DECLARE_METATYPE(bb::system::phone::Call)

#endif /* BB_SYSTEM_PHONE_CALL_HPP */
