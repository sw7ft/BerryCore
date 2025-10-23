/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#include <bb/pim/Global>

#ifndef BB_PIM_MESSAGE_MESSAGECLASS_HPP
#define BB_PIM_MESSAGE_MESSAGECLASS_HPP

namespace bb {
namespace pim {
namespace message {
/*!
 * @headerfile MessageClass.hpp <bb/pim/message/MessageClass>
 * 
 * @brief The @c MessageClass class includes possible class types for a message.
 *
 * @details A @c Message can have a class type associated with it. This class type indicates
 * what kind of message it is, such as a meeting invitation, note, and so on. You can use
 * the enumeration values in this class to determine the class type of a @c %Message.
 * 
 * @see Message
 *
 * @xmlonly
 * <apigrouping group="App Integration/Message"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */

class BB_PIM_EXPORT MessageClass
{

public:
    /*!
     * @brief An enumeration of supported class types for a message.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type{
        /*!
         * @brief Indicates an unknown message type.
         *
         * @since BlackBerry 10.0.0
         */
        Unknown=0,
        /*!
         * @brief Indicates that the message is a note.
         *
         * @since BlackBerry 10.0.0
         */
        Note = 1,
        /*!
         * @brief Indicates that the message is an S/MIME note.
         *
         * @since BlackBerry 10.0.0
         */
        NoteSmime = 2,
        /*!
         * @brief Indicates that the message is an S/MIME multipart signed note.
         *
         * @since BlackBerry 10.0.0
         */
        NoteSmimeMultiPartSigned = 3,
        /*!
         * @brief Indicates that the message is an S/MIME note receipt.
         *
         * @since BlackBerry 10.0.0
         */
        NoteReceiptSmime=4,
        /*!
         * @brief Indicates that the message is an info path form.
         *
         * @since BlackBerry 10.0.0
         */
        InfoPathForm = 5,
        /*!
         * @brief Indicates that the message is a scheduled meeting.
         *
         * @since BlackBerry 10.0.0
         */
        ScheduleMeeting = 6,
        /*!
         * @brief Indicates that the message is a notification meeting.
         *
         * @since BlackBerry 10.0.0
         */
        NotificationMeeting = 7,
        /*!
         * @brief Indicates that the message is a post.
         *
         * @since BlackBerry 10.0.0
         */
        Post = 8,
        /*!
         * @brief Indicates that the message is an Octel voicemail message.
         *
         * @since BlackBerry 10.0.0
         */
        OctelVoice = 9,
        /*!
         * @brief Indicates that the message is a voice note.
         *
         * @since BlackBerry 10.0.0
         */
        VoiceNotes = 10,
        /*!
         * @brief Indicates that the message is a sharing type.
         *
         * @since BlackBerry 10.0.0
         */
        Sharing = 11
    };

private:
    /*! @cond PRIVATE */
    MessageClass();
    ~MessageClass();
    /*! @endcond */

};

} /* namespace message */
} /* namespace pim */
} /* namespace bb */

#endif // BB_PIM_MESSAGE_CLASS_TYPE_HPP
