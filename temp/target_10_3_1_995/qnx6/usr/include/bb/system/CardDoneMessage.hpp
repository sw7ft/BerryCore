/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_CARDDONEMESSAGE_HPP
#define BB_SYSTEM_CARDDONEMESSAGE_HPP

#include <bb/system/Global>

#include <QMetaType>
#include <QScopedPointer>
#include <QString>

namespace bb
{
namespace system
{

class CardDoneMessagePrivate;

/*!
 * @headerfile CardDoneMessage.hpp <bb/system/CardDoneMessage>
 *
 * @brief Encapsulates information sent from a card to the entity that invoked it
 *        when the card has completed its activity or has been closed.
 *
 *
 * @xmlonly
 * <apigrouping group="App Integration/Invocation framework"/>
 * <library name="bbsystem"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT CardDoneMessage
{
public:
    /*!
     * @brief Creates a new @c CardDoneMessage object.
     *
     * @since BlackBerry 10.0.0
     */
    CardDoneMessage();

    /*!
     * @brief Creates a copy of an existing @c CardDoneMessage object.
     *
     * @param other The source @c CardDoneMessage object to copy.
     *
     * @since BlackBerry 10.0.0
     */
    CardDoneMessage(const CardDoneMessage &other);

    /*!
     * @brief Destroys this @c CardDoneMessage object.
     *
     * @since BlackBerry 10.0.0
     */
    ~CardDoneMessage();

    /*!
     * @brief Copies the data of an existing @c CardDoneMessage object to this object.
     *
     * @param other The source @c CardDoneMessage object to copy.
     *
     * @return The @c CardDoneMessage instance.
     *
     * @since BlackBerry 10.0.0
     */
    CardDoneMessage& operator=(const CardDoneMessage &other);
    
    /*!
     * @brief Returns the reason that the card was closed.
     *
     * @return The reason the card was closed.
     *
     * @since BlackBerry 10.0.0
     */
    QString reason() const;

    /*!
     * @brief Returns the type of data the message holds.
     *
     * @return The type of the data included in the message.
     *
     * @since BlackBerry 10.0.0
     */
    QString dataType() const;
    
    /*!
     * @brief Returns the payload of this message.
     *
     * @details The type of the data can be determined using @c dataType().
     *
     * @return The payload of this message or an empty string if the receiver does not
     *         require any data.
     *
     * @since BlackBerry 10.0.0
     */
    QString data() const;

    /*!
     * @brief Sets the reason the card was closed.
     *
     * @param reason The reason the card was closed.
     *
     * @since BlackBerry 10.0.0
     */
    void setReason(const QString &reason);

    /*!
     * @brief Sets the type of the data included in the message
     *
     * @param dataType The type of the data in the message.
     *
     * @since BlackBerry 10.0.0
     */
    void setDataType(const QString &dataType);

    /*!
     * @brief Sets the payload of this message.
     *
     * @param data The payload of this message. The type of the data can be
              set using @c setDataType().
     *
     * @since BlackBerry 10.0.0
     */
    void setData(const QString &data);

private:
//!@cond PRIVATE
    QScopedPointer<CardDoneMessagePrivate> const d_ptr;
    Q_DECLARE_PRIVATE(CardDoneMessage)
//!@endcond
};

} // namespace system
} // namespace bb

Q_DECLARE_METATYPE(bb::system::CardDoneMessage)


#endif // BB_SYSTEM_CARDDONEMESSAGE_HPP
