/*!
 * @copyright
 * Copyright (C) 2012-2014 BlackBerry Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_PHONE_PHONE_HPP
#define BB_SYSTEM_PHONE_PHONE_HPP

#include <bb/system/phone/Line>
#include <bb/system/phone/Call>
#include <bb/system/phone/LineType>
#include <bb/system/phone/CallCommandResponse>
#include <bb/system/Global>
#include <QObject>
#include <QMap>
#include <QtDeclarative/QtDeclarative>


namespace bb
{
namespace system
{
namespace phone
{

class PhonePrivate;

/*!
 * @headerfile Phone.hpp <bb/system/phone/Phone>
 *
 * @brief Provides phone-related functionality.
 *
 * The @c Phone class is the entry point for phone-related functionality, such as showing the dial pad,
 * starting an outgoing call, checking the available lines supported on the phone, listening to call related
 * notifications, and so on.
 *
 * The following example shows how to start a cellular call to the phone number "519-555-0100":
 *
 * @code
 * bb::system::phone::Phone phone;
 * phone.initiateCellularCall("519-555-0100");
 * @endcode
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Phone"/>
 * <library name="bbsystem"/>
 * @endxmlonly
 *
 * @permissions You must also specify the @c access_phone and @c control_phone permissions in your bar-descriptor.xml file.
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT Phone: public QObject {
    Q_OBJECT
public:

    /*!
     * @brief Creates a new @c Phone object.
     *
     * @param parent If not @c 0, the supplied parent will be responsible for deleting this instance.
     *
     * @since BlackBerry 10.0.0
     */
    explicit Phone(QObject *parent = 0);

    /*!
     * @brief Destroys this @c Phone object.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~Phone();

    /*!
     * @brief Returns a map of lines supported on the device.
     *
     * @return A map of lines keyed on the line identifier supported on the device.
     *
     * @since BlackBerry 10.0.0
     */
    QMap<QString, Line> lines() const;

    /*!
     * @brief Returns the currently active line.
     *
     * @return The currently active line. If there is no active line, an invalid @c Line object is returned.
     *
     * @since BlackBerry 10.0.0
     */
    Line activeLine() const;

    /*!
     * @brief Checks whether a given line is available.
     *
     * @param type The type of the line to check.  See @c LineType for the list of line types.
     * @return @c true if the given line type is available, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isLineAvailable(LineType::Type type) const;

    /*!
     * @brief Returns a list of phone lines that are currently available to make a call.
     * The lines are sorted based on priority.
     *
     * For a given address (a phone number, a PIN, or an email address), more than one line may be
     * available to make a call. For instance a cellular number can be called using MVS, SecuVOICE, or
     * a cellular line. This method returns the list of available lines that can be used to call the
     * given address. The lines are sorted according to their priority. For example, cellular line has higher
     * priority over MVS line when both lines are available, so cellular will be the first item in the
     * list followed by MVS and so on. Note that in a region where a phone number is 8 digits long,
     * a phone number and a digits-only PIN cannot be differentiated by this API. In this case, @c availableLines()
     * returns a list of available lines that may be used to call a phone number followed by the available
     * lines that may be used to call a PIN.
     *
     * @param address The phone number (for example, 3125559678) or PIN (for example, A564BBD1),
     * or BBID (for example, test@blackberry.com) that can be used to make a call.
     * @return A list of currently available lines that can be used to make the call. The lines are
     * sorted based on their priority.
     *
     * @since BlackBerry 10.2.0
     */
    QList<Line> availableLines(const QString &address) const;

public Q_SLOTS:

    /*!
     * @brief Brings the phone dial pad to the foreground with the number field pre-populated with the given address.
     *
     * The @c callUpdated() signal will not be emitted for calls resulting from the @c requestDialpad() method.
     *
     * @param address The address with which to populate the number field.
     * @param type The phone line to use when making the call. The default is @c LineType::Cellular.
     *        See @c LineType for the complete list of line types.
     *
     * @since BlackBerry 10.0.0
     */
    void requestDialpad(const QString &address, bb::system::phone::LineType::Type type =
        bb::system::phone::LineType::Cellular);

    // @cond PRIVATE
    /*!
     * @brief This function has been deprecated.
     *
     * @details Invokes the Phone app to either assign a phone number to an unassigned key for speed dial or dial the phone number of an assigned key.
     * If the key is not assigned, the user is prompted to assign the key to a contact as a new speed dial item.
     * If the key has been assigned already, the associated speed dial number is dialed.
     *
     * @note This function works only for devices that have a physical keyboard. It is up to the application that calls this function to verify that the current device has a physical keyboard.
     *
     * @param keycap The ASCII code of the physical key that is pressed to invoke speed dial. The value of @c keycap can be retrieved from @c KeyEvent.
     *
     * @deprecated BlackBerry 10.3.0.
     *
     * @since BlackBerry 10.3.0
     */
    void requestKeypressSpeedDial(int keycap) BB_DEPRECATED;
    // @endcond

    /*!
     * @brief Initiates an outgoing cellular call.
     * @details Subsequent updates for the initiated call are indicated by the @c callUpdated() signal.
     *
     * @param phoneNumber The phone number to call.
     * @param applySmartDialing Whether to apply smart dialing or not. The default is @c false.
     *
     * @since BlackBerry 10.0.0
     */
    void initiateCellularCall(const QString &phoneNumber,
            bool applySmartDialing = false);

    /*!
     * @brief Initiates an outgoing call.
     *
     * @param address The address (for example, phone number for cellular call, BBID for video chat, and so on) to call.
     * @param lineType The phone line to use when making the call. The default is @c LineType::Cellular.
     * See @c LineType for the list of line types.
     *
     * @since BlackBerry 10.0.0
     */
    void initiateCall(const QString &address,
        bb::system::phone::LineType::Type lineType = bb::system::phone::LineType::Cellular);

    /*!
     * @brief Initiates an outgoing video call.
     *
     * @param address The address (for example, phone number for video call over Cellular line, BBID for BBM Video Chat with BBM line selected, and so on) to call.
     * @param lineType The phone line to use when making the video call. The default is @c LineType::Cellular.
     * See @c LineType for the list of line types.
     *
     * @since BlackBerry 10.3.0
     */
    void initiateVideoCall(const QString &address,
        bb::system::phone::LineType::Type lineType = bb::system::phone::LineType::Cellular);

    /*!
     * @brief Sends DTMF tones to the active call.
     *
     * The DTMF tones are sent in the order in which they appear in the @c QByteArray.
     *
     * @param tones The DTMF tones to send. Each element in @c tones should correspond to a DTMF tone.
     * @param lineType The phone line to which the DTMF tones should be sent.  The default is @c LineType::Cellular.
     *        See @c LineType::Type for the complete list of line types.
     * @return @c true if the tones were successfully sent to the active call, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool sendDTMFTones(const QByteArray &tones,
        bb::system::phone::LineType::Type lineType = bb::system::phone::LineType::Cellular);

    /*!
     * @brief Ends an ongoing call.
     *
     * Returns a Boolean that indicates whether the end call command was sent successfully.
     * To determine the response of the execution of the call command, listen to
     * @c callCommandResponseReceived signal.
     *
     * @param callId Unique call session identifier.
     * @return @c true if the end call command was sent successfully,
     *         @c false otherwise.
     *
     * @since BlackBerry 10.2
     */
    bool endCall(int callId);

    /*!
     * @brief Holds a call.
     *
     * Returns a Boolean that indicates whether the hold call command was sent successfully.
     * To determine the response of the execution of the call command, listen to
     * @c callCommandResponseReceived signal.
     *
     * @param callId Unique call session identifier.
     * @return @c true if the hold call command was sent successfully,
     *         @c false otherwise.
     *
     * @permissions The application must have the @c read_phonecall_details permission to use this feature.
     *
     * @since BlackBerry 10.3.0
     */
    bool holdCall(int callId);

    /*!
     * @brief Resumes a call.
     *
     * Returns a Boolean that indicates whether the resume call command was sent successfully.
     * To determine the response of the execution of the call command, listen to
     * @c callCommandResponseReceived signal.
     *
     * @param callId Unique call session identifier.
     * @return @c true if the resume call command was sent successfully,
     *         @c false otherwise.
     *
     * @permissions The application must have the @c read_phonecall_details permission to use this feature.
     *
     * @since BlackBerry 10.3.0
     */
    bool resumeCall(int callId);

    /*!
     * @brief Merges two calls into a conference call.
     *
     * Returns a Boolean that indicates whether the merge call command was sent successfully.
     * To determine the response of the execution of the call command, listen to
     * @c callCommandResponseReceived signal.
     *
     * @details If @c callId1 and @c callId2 are single-party calls, after the two calls are merged,
     * a new call ID is generated to represent the conference call. At this point, @c callId1 and @c callId2
     * still exist and they become participants in the conference call identified by the new call ID.
     * Clients can listen to the @c callUpdated() signal for the new call ID.
     *
     * @see @c bb::system::Phone::splitCall
     *
     * @param callId1 Unique call session identifier of the first call to be merged.
     * @param callId2 Unique call session identifier of the second call to be merged.
     * @return @c true if the merge call command was sent successfully,
     *         @c false otherwise.
     *
     * @permissions The application must have the @c read_phonecall_details permission to use this feature.
     *
     * @since BlackBerry 10.3.0
     */
    bool mergeCall(int callId1, int callId2);

    /*!
     * @brief Splits the given call from a conference call.
     *
     * Returns a Boolean that indicates whether the split call command was sent successfully.
     * To determine the response of the execution of the call command, listen to
     * @c callCommandResponseReceived signal.
     *
     * @details @c callId should refer to a participant in a conference call. After the split,
     * the call identified by @c callId becomes the current active call.
     * If the conference call has only two participants prior to the split, the other participant will be on hold,
     * while the conference call itself will cease to exist.
     * If the conference call has more than two participants prior to the split, the other participants will
     * continue to be in the conference call, and the conference call will be on hold.
     *
     * Clients can listen to the @c callUpdated() signal for updates.
     *
     * To disconnect all participants in a conference call, use @c endCall() and pass in the conference call ID.
     *
     * @see @c bb::system::Phone::endCall
     * @see @c bb::system::Phone::mergeCall
     *
     * @param callId Unique call session identifier of a conference call participant.
     * @return @c true if the split call command was sent successfully,
     *         @c false otherwise.
     *
     * @permissions The application must have the @c read_phonecall_details permission to use this feature.
     *
     * @since BlackBerry 10.3.0
     */
    bool splitCall(int callId);

Q_SIGNALS:

    /*!
     * @brief Emitted when an incoming call is received or updated, or an
     * outgoing call initiated through this @c Phone object instance is updated.
     *
     * @param call A @c Call object with updated information.
     *
     * @since BlackBerry 10.0.0
     */
    void callUpdated(const bb::system::phone::Call &call);

    /*!
     * @brief Emitted when the response of a call command (for example,
     * end call) initiated through this @c Phone object instance is returned.
     *
     * @param commandResponse A @c CallCommandResponse object with updated information.
     *
     * @since BlackBerry 10.2
     */
    void callCommandResponseReceived(const bb::system::phone::CallCommandResponse &commandResponse);

    /*!
     * @brief Emitted when a line is updated.
     *
     * @param line A @c Line object with updated information.
     *
     * @since BlackBerry 10.0.0
     */
    void lineUpdated(const bb::system::phone::Line &line);

    /*!
     * @brief Emitted when a line is removed.
     *
     * @param line A @c Line object that was removed.
     *
     * @since BlackBerry 10.0.0
     */
    void lineRemoved(const bb::system::phone::Line &line);


    //!@cond PRIVATE
    /*!
     *  Emitted when a call is updated.
     */
    void callUpdated(const QVariant &call);

    /*!
     * Emitted when the response to a call command is updated.
     */
    void callCommandResponseReceived(const QVariant &commandResponse);

    /*!
     * Emitted when a line is updated.
     */
    void lineUpdated(const QVariant &line);

    /*!
     * Emitted when a line is removed.
     */
    void lineRemoved(const QVariant &line);
    //!@endcond

private:
    //!@cond PRIVATE
    Q_DECLARE_PRIVATE(Phone);

    PhonePrivate* const d_ptr;   /**< private implementation */
    Q_DISABLE_COPY(Phone);
    //!@endcond
};

} // phone
} // system
} // bb

QML_DECLARE_TYPE(bb::system::phone::Phone)
#endif /* BB_SYSTEM_PHONE_PHONE_HPP */
