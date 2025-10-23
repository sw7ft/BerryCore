/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_MESSAGE_MESSAGETRANSACTION_HPP
#define BB_PIM_MESSAGE_MESSAGETRANSACTION_HPP

#include <bb/pim/Global>
#include <bb/pim/message/Keys>
#include <bb/pim/account/Account>
#include <QSharedDataPointer>

namespace bb {
namespace pim {
namespace message {

class MessageTransactionPrivate;

/*!
 * @headerfile MessageTransaction.hpp <bb/pim/message/MessageTransaction>
 *
 * @brief The @c MessageTransaction class represents an action that can take place on a particular
 * message in the message database.
 * 
 * @details For example, messages can be added to, removed from, or updated in the message database, and you
 * can use this class to determine the type of change that a particular transaction represents. You can also
 * use this class to synchronize any changes between your app's local cache of transactions and the message
 * database.
 *
 * @xmlonly
 * <apigrouping group="App Integration/Message"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT MessageTransaction
{

public:

    /*!
     * @brief An enumeration of possible message transaction types.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief Indicates an unknown transaction type.
         *
         * @since BlackBerry 10.0.0
         */
        Unknown=0,
        /*!
         * @brief Indicates that a message was added.
         *
         * @since BlackBerry 10.0.0
         */
        Add = 1,
        /*!
         * @brief Indicates that a message was updated.
         *
         * @since BlackBerry 10.0.0
         */
        Update = 2,
        /*!
         * @brief Indicates that a message was deleted.
         *
         * @since BlackBerry 10.0.0
         */
        Delete = 3
    };

    /*!
     * @brief Constructs a new @c MessageTransaction.
     *
     * @since BlackBerry 10.0.0
     */
    MessageTransaction();

    /*!
     * @brief Copy constructor.
     * 
     * @details This function constructs a @c MessageTransaction containing exactly the same values as
     * the provided @c %MessageTransaction.
     * 
     * @param other The @c %MessageTransaction to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    MessageTransaction(const MessageTransaction &other);

    /*!
     * @brief Constructs a new @c MessageTransaction using the provided @c MessageTransactionPrivate object.
     *
     * @param messageTransactionPrivate The @c %MessageTransactionPrivate object to use to construct the
     * @c %MessageTransaction.
     *
     * @since BlackBerry 10.0.0
     */
    explicit MessageTransaction(MessageTransactionPrivate* messageTransactionPrivate);


    /*!
     * @brief Assignment operator.
     * 
     * @details This operator copies all values from the provided @c MessageTransaction into this
     * @c %MessageTransaction.
     * 
     * @param other The @c %MessageTransaction from which to copy all values.
     *
     * @return A @c %MessageTransaction with all copied data.
     *
     * @since BlackBerry 10.0.0
     */
    MessageTransaction& operator=(const MessageTransaction &other);

    /*!
     * @brief Destroys this @c MessageTransaction.
     *
     * @since BlackBerry 10.0.0
     */
    ~MessageTransaction();

    /*!
     * @brief Returns the transaction ID of this @c MessageTransaction.
     *
     * @return The transaction ID as a @c TransactionKey object.
     *
     * @since BlackBerry 10.0.0
     */
    bb::pim::message::TransactionKey id() const;

    /*!
     * @brief Returns the account ID of this @c MessageTransaction.
     *
     * @return The account ID as an @c AccountKey object.
     *
     * @since BlackBerry 10.0.0
     */
    bb::pim::account::AccountKey accountId() const;

    /*!
     * @brief Returns the message ID of this @c MessageTransaction.
     * 
     * @return The message ID as a @c MessageKey object.
     *
     * @since BlackBerry 10.0.0
     */
    MessageKey messageId() const;

    /*!
     * @brief Returns the folder ID of this @c MessageTransaction.
     * 
     * @return The folder ID as a @c FolderKey object.
     *
     * @since BlackBerry 10.0.0
     */
    FolderKey folderId() const;


    /*!
     * @brief Returns the conversation ID of this @c MessageTransaction.
     *
     * @return The conversation ID as a @c ConversationKey object.
     *
     * @since BlackBerry 10.0.0
     */
    ConversationKey conversationId() const;

    /*!
     * @brief Returns the type of transaction that this @c MessageTransaction represents.
     * 
     * @details You can use this function to determine if the transaction was a message
     * addition, update, or deletion.
     * 
     * @return The transaction type as a value from the @c MessageTransaction::Type
     * enumeration.
     *
     * @since BlackBerry 10.0.0
     */
    MessageTransaction::Type type() const;

    /*!
     * @brief Indicates whether this @c MessageTransaction is a valid transaction.
     *
     * @return @c true if this @c %MessageTransaction is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

private:
    QSharedDataPointer<MessageTransactionPrivate> d_ptr;
};

} /* namespace message */
} /* namespace pim */
} /* namespace bb */


#endif // BB_PIM_MESSAGE_MESSAGETRANSACTION_HPP
