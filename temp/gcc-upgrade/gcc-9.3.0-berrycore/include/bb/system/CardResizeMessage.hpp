/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_CARDRESIZEEMESSAGE_HPP
#define BB_SYSTEM_CARDRESIZEEMESSAGE_HPP

#include <bb/system/Global>

#include <bb/system/CardEdge>
#include <bb/system/CardOrientation>

#include <QMetaType>
#include <QScopedPointer>
#include <QString>

namespace bb
{
namespace system
{

class CardResizeMessagePrivate;

/*!
 * @headerfile CardResizeMessage.hpp <bb/system/CardResizeMessage>
 *
 * @brief Encapsulates information sent to a card to instruct it to resize.
 *
 * @xmlonly
 * <apigrouping group="App Integration/Invocation framework"/>
* <library name="bbsystem"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT CardResizeMessage
{
public:
    /*!
     * @brief Creates a new @c CardResizeMessage object.
     *
     * @since BlackBerry 10.0.0
     */
    CardResizeMessage();

    /*!
     * @brief Creates a copy of an existing @c CardResizeMessage object.
     *
     * @param other The source @c CardResizeMessage object to copy.
     *
     * @since BlackBerry 10.0.0
     */
    CardResizeMessage(const CardResizeMessage &other);

    /*!
     * @brief Destroys this @c CardResizeMessage object.
     *
     * @since BlackBerry 10.0.0
     */
    ~CardResizeMessage();

    /*!
     * @brief Copies the data of an existing @c CardResizeMessage object to
     * this object.
     *
     * @param other The source @c CardResizeMessage object to copy.
     *
     * @return The @c CardResizeMessage instance.
     *
     * @since BlackBerry 10.0.0
     */
    CardResizeMessage& operator=(const CardResizeMessage &other);
    
    /*!
     * @brief Returns the unique identifier of the message.
     *
     * @return The unique identifier of the message.
     *
     * @since BlackBerry 10.0.0
     */
    QString id() const;

    /*!
     * @brief Returns the width to which the card should resize.
     *
     * @return The width.
     *
     * @since BlackBerry 10.0.0
     */
    int width() const;
    
    /*!
     * @brief Returns the height to which the card should resize.
     *
     * @return The height.
     *
     * @since BlackBerry 10.0.0
     */
    int height() const;

    /*!
     * @brief Returns the edge of the device that is pointing up.
     *
     * @return The edge now facing up.  See @c bb::system::CardEdge for the list of edges.
     *
     * @since BlackBerry 10.0.0
     */
    CardEdge::Type upEdge() const;

    /*!
     * @brief Returns the orientation of the device (portrait
     * or landscape).
     *
     * @return The orientation of the device.  See @c bb::system::CardOrientation for the list
     * of orientations.
     *
     * @since BlackBerry 10.0.0
     */
    CardOrientation::Type orientation() const;

private:
//!@cond PRIVATE
    QScopedPointer<CardResizeMessagePrivate> const d_ptr;
    Q_DECLARE_PRIVATE(CardResizeMessage)
//!@endcond
};

} // namespace system
} // namespace bb

Q_DECLARE_METATYPE(bb::system::CardResizeMessage)


#endif // BB_SYSTEM_CARDRESIZEEMESSAGE_HPP
