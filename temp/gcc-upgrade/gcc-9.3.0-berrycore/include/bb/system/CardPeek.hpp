/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_CARDPEEK_HPP
#define BB_SYSTEM_CARDPEEK_HPP

#include <bb/system/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace system
{

/*!
 * @headerfile CardPeek.hpp <bb/system/CardPeek>
 *
 * @brief The types of peek a card can request.
 *
 * @details When an application has presented a stack of one or
 * more cards, the device user has the ability to drag the topmost
 * card in order to "peek" to the content below. The type of
 * peek determines which parent, lower in the stack, the user
 * will see.
 *
 * If the peek type is @c CardPeek::Parent, the parent card directly
 * underneath the current card (the card being dragged) is shown.
 *
 * If the peek type is @c CardPeek::Root, the root application will be
 * shown.
 *
 * @xmlonly
 * <apigrouping group="App Integration/Invocation framework"/>
 * <library name="bbsystem"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT CardPeek
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief The types of peek a card can request.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        
        /*!
         * @brief Peek to the application or card directly under the
         * card in the foreground.
         *
         * @since BlackBerry 10.0.0
         */
        Parent = 0,
        
        /*!
         * @brief Peek to the root application in the stack.
         *
         * @since BlackBerry 10.0.0
         */
        Root = 1,
    };

private:
//!@cond PRIVATE
    CardPeek();
    ~CardPeek();
//!@endcond
};

} // namespace system
} // namespace bb

QML_DECLARE_TYPE(bb::system::CardPeek)
#endif // BB_SYSTEM_CARDPEEK_HPP
