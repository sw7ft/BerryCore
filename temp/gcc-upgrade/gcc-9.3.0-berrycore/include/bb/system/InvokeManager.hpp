/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_INVOKEMANAGER_HPP
#define BB_SYSTEM_INVOKEMANAGER_HPP

#include <bb/system/Global>
#include <bb/system/ApplicationStartupMode>
#include <bb/system/CardPeek>
#include <bb/system/InvokeRequest>
#include <bb/system/InvokeListCursorDirection>
#include <bb/system/InvokeTimerRequest>

#include <QObject>
#include <QScopedPointer>

namespace bb
{
namespace system
{

class CardDoneMessage;
class CardResizeMessage;
class InvokeManagerPrivate;
class InvokeQueryTargetsRequest;
class InvokeQueryTargetsReply;
class InvokeReply;
class InvokeRequestTargetFiltersReply;
class InvokeTargetReply;
class InvokeUpdateTargetFiltersRequest;
class InvokeViewerMessage;
class InvokeViewerMessageReply;
class InvokeViewerRequest;

/*!
 * @headerfile InvokeManager.hpp <bb/system/InvokeManager>
 *
 * @brief Manages all interactions with the invocation service.
 *
 * @details Invocation is the process by which a client process can send a message to a target
 * process so it will perform a particular action. Invocation addresses locating a target
 * instance (spawning one if necessary) and delivering the invocation message. Clients
 * may explicitly specify a target (bound invocation) or allow the invocation service to
 * find a "best fit" (unbound invocation). Clients can also request a list of available
 * targets to perform their own selection.
 *
 * Invocation targets can be applications, cards, or services, and must declare
 * themselves as the appropriate target in their BAR manifest so that they are registered
 * as valid invocation targets.
 *
 * The @c InvokeManager supports both sending and receiving invoke messages thus allowing
 * an application to act as a client, a target, or both. Applications and cards receive invoke
 * messages by connecting to the @c invoked(const bb::system::InvokeRequest&) signal.
 * Applications and cards can determine if they were launched as the result of an invoke
 * message using the @c startupMode() method. The data from an invoke message received at
 * startup will arrive via one of the aforementioned signals.
 *
 * To send an invoke message, construct an @c InvokeRequest object and pass it to the
 * @c invoke() method. The returned @c InvokeReply object will contain the result of the
 * invoke operation when it becomes available. To discover which invocation targets are
 * available, construct an @c InvokeQueryTargetsRequest object and pass it to
 * @c queryTargets(). Similar to @c invoke(), the results are returned asynchronously via
 * an instance of @c InvokeQueryTargetsReply.
 *
 * An application target behaves like a typical application. When it is invoked through
 * the invocation framework, the context switches to the invoked application, and it
 * behaves as if it was launched from the home screen (it will appear thumbnailed on the
 * screen that shows running applications).
 *
 * A card is similar to an application, but when a card is invoked, the context does not
 * switch to a separate application. Instead, the card is transitioned into the foreground
 * of the application that invoked it, thus integrating more fluently into the flow of
 * the invoking application. Although a card executes in its own process and renders in
 * its own windows, it can still be considered part of the running application in that
 * the card cannot be minimized on its own (and will not appear separately in the list of running
 * applications on the home screen). A card is intended to provide discrete functionality such as
 * picking a contact, composing an email, or previewing an image. Cards can be "stacked",
 * but a parent (the invoking entity) can only invoke one card at a time.
 *
 * When a card has completed the activity is was invoked to perform, it informs the parent
 * using the @c sendCardDone() method, passing a @c CardDoneMessage to include any results.
 * Results from a card can include the reason the card completed,
 * any data that needs to be sent to the parent, and the data type
 * of the data. The parent will receive the @c childCardDone() signal. After the invocation
 * framework has transitioned the card off-screen, it will emit the @c cardPooled() signal
 * to the card. This indicates that the card process is still running, but has been pooled
 * so that future invocations are optimized. Therefore, when the card receives this signal,
 * it must reset its state so that it is ready to be invoked cleanly again. For example, for
 * a composer, any input should be discarded.
 *
 * A parent can close its child and any stacked cards by calling @c closeChildCard().
 * Each card will be notified with the @c cardPooled() signal, and the parent will receive
 * the @c childCardDone() signal as an acknowledgment. Similarly, the invocation
 * framework can close a stack of cards (for example, if the user navigates away from the cards);
 * if this occurs, the parent receives the @c childCardDone() signal and each card receives
 * a @c cardPooled() signal.
 *
 * Cards can also be invoked as part of a list of invocations by specifying
 * @c bb::system::InvokeRequest::setListId(). Cards that belong to lists can be navigated
 * through using system gestures and keyboard shortcuts. The currently open card of a list
 * may request to be replaced with its previous or next item via @c selectListItem().
 *
 * The application requesting a card to be opened as a list item should
 * connect to the relevant signals (@c listItemSelected(), @c listItemSelectedFromCursor(),
 * @c listCursorMoved()) and if appropriate, issue corresponding invoke requests.
 *
 * An application can have at most one invoke list active at a time.
 *
 * @xmlonly
 * <apigrouping group="App Integration/Invocation framework"/>
 * <library name="bbsystem"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT InvokeManager : public QObject
{
    Q_OBJECT
public:

    /*!
     * @brief Creates a new @c InvokeManager object.
     *
     * @note By default, this instance will be the parent of any futures that it returns.
     * If the lifetime of this instance is shorter than the lifetime of the requests, the
     * parent of the futures should be changed using @c QObject::setParent(). Otherwise,
     * the futures will be destroyed when this instance is destroyed. This will result in
     * signals from the futures not being emitted, though the requests will not be canceled.
     *
     * Futures are returned by:
     * - @c invoke()
     * - @c queryTargets()
     * - @c requestTargetFilters()
     * - @c updateTargetFilters()
     *
     * @param parent If not 0, the supplied parent will be responsible for deleting this instance.
     *
     * @since BlackBerry 10.0.0
     */
    explicit InvokeManager(QObject *parent = 0);

    /*!
     * @brief Destroys this @c InvokeManager object.
     *
     * @details Any futures that have this instance as their parent will be destroyed without
     * canceling the associated requests.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~InvokeManager();

    /*!
     * @brief Constructs an invoke message to send to an application, card or service using
     * the data in the specified request object and sends it to the invocation service.
     *
     * @details The results of the invoke operation will be communicated asynchronously via
     * the returned @c InvokeTargetReply object.
     *
     * @note The returned future has its parent set to this instance. Unless its parent is changed
     * (using @c QObject::setParent()), the future will be destroyed when this instance is destroyed.
     *
     * @note To minimize memory usage, explicitly destroy the returned object using @c QObject::deleteLater()
     * instead of relying on the implicit cleanup that occurs due to the @c QObject parent-child relationship.
     *
     * @param request The data used to construct the invoke message.
     *
     * @return A future representing the result this operation or 0 if the invoke message could not be sent.
     *
     * @since BlackBerry 10.0.0
     */
    InvokeTargetReply* invoke(const InvokeRequest &request);

    /*!
     * @brief Requests that this list item be replaced with the list item determined by @c direction.
     *
     * @details The request will fail if this application was not launched as a result of a list invocation.
     * If the request is successful, the current list item will be closed in the normal manner
     * (including the usual applicable signals such as @c cardPooled).
     *
     * @param direction Whether to activate the previous or next list item.
     *
     * @return @c true if the request was successfully sent, @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool selectListItem(bb::system::InvokeListCursorDirection::Type direction);

    //!@cond PRIVATE
    /*!
     * @brief Constructs an invoke viewer message to send to a viewer using the data in the
     * specified request object and sends it to the invocation service.
     *
     * @details The results of the invoke viewer operation will be communicated asynchronously
     * via the returned @c InvokeTargetReply object.
     *
     * Note that if this application is running as a viewer, it cannot invoke another viewer.
     *
     * @param request The data used to construct the invoke viewer message.
     *
     * @return A future representing the result this operation or 0 if the invoke
     *         viewer message could not be sent. Note the returned object has this @c InvokeManager object
     *         set as its parent. If you want to prevent the returned object from being
     *         automatically destroyed when this object is destroyed, call
     *         @c QObject::setParent() on the returned object. To minimize memory usage,
     *         it's best to explicitly destroy the returned object instead of relying on
     *         the implicit cleanup that occurs due to the @c QObject parent-child
     *         relationship.
     */
    InvokeTargetReply* invoke(const InvokeViewerRequest &request) BB_DEPRECATED;

    /*!
     * @brief Constructs a custom message to send to a viewer (if called by the client) or its
     * client (if called by the viewer) using the data in the specified relay object and
     * relays it via the invocation service.
     *
     * @details If the receiver of the message is not expected to provide a reply, do not set
     * the @c InvokeViewerMessage::id() property in the @c message parameter. Since a reply will not be returned, this
     * method will return 0. The @c ok output parameter can be provided to check if the message was sent.
     * Note that the @c ok output parameter does not indicate whether a client received the message;
     * it only indicates that the message was formatted properly and was successfully processed by the invocation service.
     *
     * If the receiver of the message is expected to provide a response, use the
     * @c InvokeViewerMessage::setId() method to set the identifier in the @c message parameter.
     * The reply will be received asynchronously via the returned @c InvokeViewerMessageReply object.
     *
     * @param message The data used to construct the custom message.
     * @param ok An optional output parameter. If not 0, it will be set to @c true if
     *        the @c InvokeManager was able to send the message, @c false otherwise.
     *
     * @return If the message did not include an @c InvokeViewerMessage::id() value, then 0 is returned.
     *         If the message included the @c InvokeViewerMessage::id() field, then a future representing the
     *         reply to this message is returned if the message was successfully sent;
     *         if sending the message failed, then 0 is returned.
     *         Note the returned object has this @c InvokeManager object set as its parent. If you want
     *         to prevent the returned object from being automatically destroyed
     *         when this object is destroyed, call @c QObject::setParent() on the
     *         returned object. To minimize memory usage, it's best to explicitly
     *         destroy the returned object instead of relying on the implicit cleanup
     *         that occurs due to the @c QObject parent-child relationship.
     */
    InvokeViewerMessageReply* send(const InvokeViewerMessage &message, bool *ok = 0) BB_DEPRECATED;

    /*!
     * @brief Constructs a reply to a custom message received in an emitted @c received()
     * signal, and relays it to the sender of the message through the invocation service.
     *
     * @details The message received in the @c received() signal can be updated to reflect
     * the nature of the reply. Specifically, it can be useful to update the @c InvokeViewerMessage::data()
     * attribute to send back reply data.
     *
     * @param message The data used to construct the custom message reply, as received
     *                in the @c received() signal and modified as required.
     *
     * @return @c true if the reply was successfully sent, @c false otherwise.
     */
    bool reply(const InvokeViewerMessage &message) BB_DEPRECATED;

    /*!
     * @brief Tells a viewer invoked by this application to exit.
     *
     * @details Viewers are referenced by the window ID sent to them when invoked.
     *
     * @param windowId The ID of the viewer's window.
     *
     * @return @c true if the operation was successful, @c false otherwise.
     */
    bool closeViewer(const QString &windowId) BB_DEPRECATED;

    /*!
     * @brief Sends a request from the viewer to the application that invoked it to ask
     * the invoking application to close the viewer.
     *
     * @return @c true if the request was successfully sent, @c false otherwise.
     */
    bool viewerRequestClose() BB_DEPRECATED;
    //!@endcond

    /*!
     * @brief Constructs a query message to search for available actions and targets using the
     * data in the specified request object and sends it to the invocation service.
     *
     * @details The results of the query operation will be communicated asynchronously via the
     * returned @c InvokeQueryTargetsReply object.
     *
     * @note The returned future has its parent set to this instance. Unless its parent is changed
     * (using @c QObject::setParent()), the future will be destroyed when this instance is destroyed.
     *
     * @note To minimize memory usage, explicitly destroy the returned object using @c QObject::deleteLater()
     * instead of relying on the implicit cleanup that occurs due to the @c QObject parent-child relationship.
     *
     * @param request The data used to construct the query message.
     *
     * @return A future representing the result this operation or 0 if the query message could not be sent.
     *
     * @since BlackBerry 10.0.0
     */
    InvokeQueryTargetsReply* queryTargets(const InvokeQueryTargetsRequest &request);

    /*!
     * @brief Constructs a message to request the set of filters that are associated with
     * a target.
     *
     * @details The calling entity can only request filters for targets that it owns.
     *
     * @note The length of @c targetKey must not exceed 50 bytes. If the size limit is exceeded, an
     * @c InvokeRequestTargetFiltersReply shall be returned with @c error() set to
     * @c InvokeReplyError::BadRequest.
     *
     * @note The returned future has its parent set to this instance. Unless its parent is changed
     * (using @c QObject::setParent()), the future will be destroyed when this instance is destroyed.
     *
     * @note To minimize memory usage, explicitly destroy the returned object using @c QObject::deleteLater()
     * instead of relying on the implicit cleanup that occurs due to the @c QObject parent-child relationship.
     *
     * @param targetKey The target key that identifies the target for which filters
     *        will be requested.
     *
     * @return A future representing the result this operation or 0 if the query message could not be sent.
     *
     * @since BlackBerry 10.0.0
     */
    InvokeRequestTargetFiltersReply* requestTargetFilters(const QString &targetKey);

    /*!
     * @brief Constructs a message to update the set of filters that will be applied when
     * determining whether a target should be a candidate for an unbound invocation.
     *
     * @note The returned future has its parent set to this instance. Unless its parent is changed
     * (using @c QObject::setParent()), the future will be destroyed when this instance is destroyed.
     *
     * @note To minimize memory usage, explicitly destroy the returned object using @c QObject::deleteLater()
     * instead of relying on the implicit cleanup that occurs due to the @c QObject parent-child relationship.
     *
     * @param request The data used to construct the request message.
     *
     * @return A future representing the result this operation or 0 if the query message could not be sent.
     *
     * @since BlackBerry 10.0.0
     */
    InvokeReply* updateTargetFilters(const InvokeUpdateTargetFiltersRequest &request);

    /*!
     * @brief Returns the reason this application was launched.
     *
     * @details Use this method to
     * determine if your application was launched as the result of an invoke message.
     *
     * @return The reason this application was launched.  See @c bb::system::ApplicationStartupMode
     * for the list of startup modes.
     *
     * @since BlackBerry 10.0.0
     */
    bb::system::ApplicationStartupMode::Type startupMode() const;

    /*!
     * @brief Tells the parent that a peek has been detected.
     *
     * @param peekType The type of peek that should be initiated.
     * See @c bb::system::CardPeek for the list of possible card peeks.
     *
     * @return @c true if the operation was successful, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool cardPeek(bb::system::CardPeek::Type peekType);

    /*!
     * @brief Responds to a request to be resized.
     *
     * @param message A message describing the resize parameters, as
     * received in the @c cardResizeRequested() signal.
     *
     * @return @c true if the response was sent successfully, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool cardResized(const CardResizeMessage &message);

    /*!
     * @brief Tells a card invoked by this application or card to close.
     *
     * @return @c true if the child card was successfully closed, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool closeChildCard();

    /*!
     * @brief Tells the card's parent that it has completed its intended
     * activity and that the parent can close the card.
     *
     * @details The parent will be notified via the
     * @c childCardDone(const CardDoneMessage&) signal. Once the card has been
     * moved off screen, it will be pooled so that if it is invoked again, it
     * can resume processing quickly. The card will be notified of this via the
     * @c cardPooled(const CardDoneMessage&) signal. Upon reception of this signal,
     * the card should transition to a state in which it is ready to be invoked
     * again.
     *
     * @param message A completion message for the card's parent.
     *
     * @return @c true if operation was successful, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool sendCardDone(const CardDoneMessage &message);

    /*!
     * @brief Tells the invocation framework that the application and its
     * stack of cards have been swiped away.
     *
     * @details  A "swipe away" gesture is a horizontal swipe utilized by
     * the Universal Inbox (UIB) to hide itself and all of its child
     * cards. The UIB can be dismissed using this gesture. Instead of
     * closing, the UIB and any open cards are slid off-screen and
     * remain in the same state so that activity can be resumed when
     * the UIB is brought to the foreground again.
     *
     * Any card that can be invoked directly by the UIB or indirectly
     * as part of the UIB's card stack should detect the swipe away
     * gesture and call @c swipeAway() when detected.
     *
     * @return @c true if the notification was successfully sent,
     * @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool swipeAway();

    /*!
     * @brief Requests that the card be notified before its window is displayed.
     *
     * @details When requested, the @c cardReadyCheck() signal will be emitted before the
     * card's window is shown. The window will not be shown until the card
     * calls @c cardReady() or the system timeout for this operation expires.
     *
     * The request can be made at any time during the card's lifecycle, and applies to
     * all subsequent appearances of the card's window.  If the card wishes to be notified
     * before its first appearance, this request must precede the posting of a window.
     *
     * @param check @c true if the card should be notified before its window is
     * displayed, @c false otherwise.
     * @return @c true if the operation was successful, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool requestCardReadyCheck(bool check);

    /*!
     * @brief Notifies the system that the card's window is ready to be shown.
     *
     * @details If this function is called without first calling @c requestCardReadyCheck(),
     * then the behavior is undefined.
     *
     * @return @c true if the notification was successfully sent, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool cardReady();

    /*!
     * @brief Sends a timer registration request to the invocation service
     *
     * @details The results of the timer request operation will be communicated
     * asynchronously via the returned @c #InvokeReply object. It is important to
     * mention that Recurrence Rule Timers have to be explicitly deregistered.
     * Otherwise, the recurrence rule timer would stay active forever.
     *
     * If a Recurrence Rule defines a schedule that leads to generating time slots
     * that are less than 6 minutes apart, this rule will be rejected and
     * registration will fail.
     *
     * @note The returned future has its parent set to this instance. Unless its
     * parent is changed (using @c #QObject::setParent()), the future will be
     * destroyed when this instance is destroyed.
     *
     * @note To minimize memory usage, explicitly destroy the returned object
     * using @c #QObject::deleteLater() instead of relying on the implicit
     * cleanup that occurs due to the @c #QObject parent-child relationship.
     *
     * @param request The data used to construct the timer request message.
     * If the timer request has a specific time which is of type
     * @c #InvokeDateTime::Anchored, the assigned time zone
     * may or may not be recognized. If the assigned time zone is not
     * recognized the timer registration request will fail.(the returned
     * @c #InvokeReply will contain an error after its finished() signal is
     * emitted).
     *
     * @return A future representing the result this operation or 0 if the
     * register message could not be sent.
     *
     * @since BlackBerry 10.3.0
     */
    InvokeReply* registerTimer(const InvokeTimerRequest &request);

    /*!
     * @brief Sends a timer deregistration request to the invocation service
     *
     * @details The results of the deregistration operation will be communicated
     * asynchronously via the returned @c #InvokeReply object. It is important to
     * mention that Recurrence Rule Timers have to be explicitly deregistered.
     * Otherwise, the recurrence rule timer would stay active forever.
     *
     * @note The returned future has its parent set to this instance. Unless its
     * parent is changed (using @c #QObject::setParent()), the future will be
     * destroyed when this instance is destroyed.
     *
     * @note To minimize memory usage, explicitly destroy the returned object
     * using @c #QObject::deleteLater() instead of relying on the implicit
     * cleanup that occurs due to the @c #QObject parent-child relationship.
     *
     * @param timerId The timerId of the timer to be deregistered.
     *
     * @return A future representing the result this operation or 0 if the
     * register message could not be sent.
     *
     * @since BlackBerry 10.3.0
     */
    InvokeReply* deregisterTimer(const QString &timerId);

Q_SIGNALS:
    /*!
     * @brief Emitted when this application receives an invoke message and should run as an
     * application or as a card.
     *
     * @param request The data contained in the invoke message.
     *
     * @since BlackBerry 10.0.0
     */
    void invoked(const bb::system::InvokeRequest &request);

    /*!
     * @brief Emitted when a transition has been requested
     * from the currently active list item of @c listId to the @c selection item.
     *
     * @details The current list item will be replaced with the next invoke request
     * which belongs to the same list. @c childCardDone will be emitted when the
     * current list item has been transitioned out.
     *
     * @param listId The list this request refers to.
     * @param direction Whether to activate the previous or next list item.
     *
     * @since BlackBerry 10.2.0
     */
    void listItemSelected(int listId, bb::system::InvokeListCursorDirection::Type direction);

    /*!
     * @brief Emitted to indicate the cursor position of list @c listId
     * has moved in the @c direction direction.
     *
     * @details @c listCursorMoved signals are emitted only after @c childPeekStarted has been
     * emitted. The movement is considered to have ended when @c listItemSelectedFromCursor
     * signal is emitted, or when @c childPeekEnded signal is emitted. If @c childPeekEnded
     * signal is emitted first, then the request for list item selection is considered to be
     * canceled.
     *
     * @param listId The list this request refers to.
     * @param direction The direction of movement of the cursor.
     *
     * @since BlackBerry 10.2.0
     */
    void listCursorMoved(int listId, bb::system::InvokeListCursorDirection::Type direction);

    /*!
     * @brief Emitted when a transition has been requested from the currently active list item of
     * @c listId to the item selected based on the previous @c listCursorMoved signals.
     *
     * @details This signal will be emitted during a peek, and will cause the termination of the peek,
     * and closing of the current list item. @c childPeekEnded() and @c childCardDone() will be emitted
     * when those events take place.
     *
     * @param listId The list this request refers to.
     *
     * @since BlackBerry 10.2.0
     */
    void listItemSelectedFromCursor(int listId);

    //!@cond PRIVATE
    /*!
     * @brief Emitted when this application receives an invoke viewer message and should
     * run as a viewer.
     *
     * @param request The data contained in the invoke viewer message.
     */
    void invoked(const bb::system::InvokeViewerRequest &request) BB_DEPRECATED;

    /*!
     * @brief Emitted when this application receives a custom message relayed via the
     * invocation service.
     *
     * @param message The data contained in the custom message.
     */
    void received(const bb::system::InvokeViewerMessage &message) BB_DEPRECATED;

    /*!
     * @brief Emitted on an application when a child viewer requests that it
     * be closed.
     *
     * @param windowId The window ID of the viewer that wants to close.
     */
    void viewerCloseRequestReceived(const QString &windowId) BB_DEPRECATED;

    /*!
     * @brief Emitted on an application when a child viewer has closed.
     *
     * @param windowId The window ID of the viewer that closed.
     */
    void viewerClosed(const QString &windowId) BB_DEPRECATED;
    //!@endcond

    /*!
     * @brief Emitted on an application or card when a child card has been pulled to the
     * side, to peek at this application or card.
     *
     * @param peekType The type of peek that was issued.  See @c bb::system::CardPeek
     * for the list of possible peek types.
     *
     * @since BlackBerry 10.0.0
     */
    void childPeekStarted(bb::system::CardPeek::Type peekType);
//!@cond PRIVATE
    /*!
     * @brief Emitted on an application or card when a child card has been pulled to the
     * side, to peek at this application or card.
     *
     * @param peekType The type of peek that was issued.  See @c bb::system::CardPeek
     * for the list of possible peek types.
     *
     * @note Deprecated. Please use @c childPeekStarted().
     */
    void peekStarted(bb::system::CardPeek::Type peekType) BB_DEPRECATED;
//!@endcond

    /*!
     * @brief Emitted on an application or card when a child card has been released
     * from a peek operation, hiding this application or card.
     *
     * @since BlackBerry 10.0.0
     */
    void childPeekEnded();
//!@cond PRIVATE
    /*!
     * @brief Emitted on an application or card when a child card has been released
     * from a peek operation, hiding this application or card.
     *
     * @note Deprecated. Please use @c childPeekEnded().
     */
    void peekEnded() BB_DEPRECATED;
//!@endcond

    /*!
     * @brief Emitted when a card's window is about to be displayed.
     *
     * @details The window will not be displayed until the card calls
     * @c cardReady() or the system timeout for this operation expires.
     *
     * This signal is only emitted if it has been requested by a previous
     * call to @c requestCardReadyCheck().
     *
     * @since BlackBerry 10.0.0
     */
    void cardReadyCheck();

    /*!
     * @brief Emitted when the card has been pulled to the side, to peek to an
     * application or card under it in the stack.
     *
     * @param peekType The type of peek that was issued.  See @c bb::system::CardPeek
     * for the list of peek types.
     *
     * @since BlackBerry 10.0.0
     */
    void cardPeekStarted(bb::system::CardPeek::Type peekType);

    /*!
     * @brief Emitted when the card has been released from the peek.
     *
     * @since BlackBerry 10.0.0
     */
    void cardPeekEnded();

    /*!
     * @brief Emitted when this card has received a request to resize.
     *
     * @param message A message describing the resize parameters.
     *
     * @since BlackBerry 10.0.0
     */
    void cardResizeRequested(const bb::system::CardResizeMessage &message);

    /*!
     * @brief Emitted when the card has been moved off-screen and has been pooled.
     *
     * @details Upon receipt of this signal, the card should transition to a state
     * in which it is ready to be invoked again.
     *
     * @param message A message describing the reason the card was closed.
     *
     * @since BlackBerry 10.0.0
     */
    void cardPooled(const bb::system::CardDoneMessage &message);

    /*!
     * @brief Emitted to the parent of a card to notify it that the child
     * card has completed its tasks and has been moved off-screen
     * and pooled.
     *
     * @param message A message containing the results from the child.
     *
     * @since BlackBerry 10.0.0
     */
    void childCardDone(const bb::system::CardDoneMessage &message);

private:
//!@cond PRIVATE
    QScopedPointer<InvokeManagerPrivate> const d_ptr;
    Q_DECLARE_PRIVATE(InvokeManager)
    Q_DISABLE_COPY(InvokeManager)
//!@endcond
};

} // namespace system
} // namespace bb

#endif // BB_SYSTEM_INVOKEMANAGER_HPP
