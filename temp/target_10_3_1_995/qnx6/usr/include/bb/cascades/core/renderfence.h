/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 * 
*/

#ifndef BB_CASCADES_RENDERFENCE_H
#define BB_CASCADES_RENDERFENCE_H

#include <bb/cascades/bbcascades_global.h>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

#include <bb/cascades/BaseObject>
#include <bb/cascades/RenderFenceState>

namespace bb {
namespace cascades {

class RenderFencePrivate;

/*!
 * @brief Provides a way to get notified when current changes to the scene
 * associated with particular window have been rendered.
 *
 * @details Fence can be used to ensure the window content has been updated before the
 * application issues "cardReady" reply to @c %InvokeManager for example, or
 * to find out when the set scene has been rendered.
 *
 * When created the fence is in @c RenderFenceState::Created state. From this
 * state it can change to the following end states:
 * - @c RenderFenceState::NotReached : fence becomes NotReached when it was
 *   raised but hasn't yet been @c Reached, @c Aborted or @c TimedOut
 * - @c RenderFenceState::Reached : fence becomes Reached at some point after the changes
 *   made to the scene after it was Raised are rendered and presented. The timing of this state change
 *   is not guaranteed, the only thing that is guaranteed that it the fence will change
 *   the state at some point after the rendering has completed.
 * - @c RenderFenceState::Aborted : if the @c raised property was set to false while
 *   in NotReached state, or if for some reason the fence can not be reached, for
 *   example rendering has been halted due to window or application state change such as
 *   window being minimized, card pooled and so on.
 * - @c RenderFenceState::TimedOut : when the fence was not reached or aborted within 3
 *   seconds.
 *
 * By default the fence is created for the main window (@see Application::mainWindow).
 *
 * The render fence must be raised before it can be reached, which can be done by setting 
 * the @c raised property to @c true.
 * The fence can be re-used by setting the @c raised property to @c true again after it has reached 
 * any of the ending states (RenderFenceState::Reached, RenderFenceState::Aborted,
 * RenderFenceState::TimedOut).
 *
 * The fence can also be explicitly aborted by setting the @c raised property to @c false.
 *
 * @warning Due to backwards compatibility reasons there is one exception when the fence
 * doesn't have to be explicitly raised after creation:
 * if it is created using builder and the builder has been assigned to a variable. In this
 * case the fence will be raised automatically (@c raised property will be set to @c true):
 * @code
 * // Created using constructor, not raised.
 * RenderFence *fence = new RenderFence();
 * // Created with builder but not assigned or explicitly raised(), not raised.
 * RenderFence::create();
 * 
 * // Created with builder and assigned: the following fence WILL be raised.
 * RenderFence *raisedFence = RenderFence::create();
 *
 * // To prevent assigned fence from being raised set raised to @c false.
 * RenderFence *raisedFence = RenderFence::create().raised(false);
 * @endcode
 *
 * An example of creating a render fence and connecting application's slots to its signals.
 * The fence will change its state when the scene has been rendered and presented, and
 * it will automatically delete itself once any of the signals are emitted:
 * @code
 * myScene = //... Create the scene.
 * Application::instance()->setScene(myScene);
 * 
 * RenderFence::create()
 *     .parent(myApplication)
 *     .onReached(myApplication, SLOT(handleReached()))
 *     .onTimedOut(myApplication, SLOT(handleTimedOut()))
 *     .onAborted(myApplication, SLOT(handleAborted()))
 *     .autoDeleted()
 *     .raised(true);
 * @endcode
 *
 * An example of using the fence from QML:
 * @code
 * Button {
 *     text: "Change Button Opacity"
 *     enabled: !fence.raised
 *     onClicked: {
 *         opacity = opacity * 0.9
 *         fence.raised = true
 *     }
 *     attachedObjects: [
 *         RenderFence {
 *             id: fence
 *         }
 *     ]
 * }
 * @endcode
 *
 * @xmlonly
 *     <apigrouping group="User interface/Application structure"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT RenderFence : public BaseObject
{
private:
    Q_OBJECT

    /*!
     * @brief Property indicating the state of the RenderFence.
     * A @c stateChanged() signal is emitted when the value of this property changes.
     *
     * @details In addition a @c reached() signal is emitted when @c RenderFence changes its
     * state to @c RenderFenceState::Reached, @c aborted() signal is emitted when state is
     * @c RenderFenceState::Aborted, and @c timedOut() when state is @c RenderFenceState::TimedOut.
     *
     * The default value is @c RenderFenceState::Created.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::cascades::RenderFenceState::Type state READ state NOTIFY stateChanged FINAL)

    /*!
     * @brief Property indicating whether the fence is raised or not
     *
     * @details When the value is @c true the fence has been raised and it is waiting for the
     * fenced scene changes to be processed (corresponds to @c RenderFenceState::NotReached state).
     *
     * The property value is @c false when the fence is first created (corresponds to
     * @c RenderFenceState::Created state), if it is changed from @c true to @c false explicitly
     * (in which case the @c state property will be set to @c RenderFenceState::Aborted)
     * or the fence was reached (@c RenderFenceState::Reached state), aborted 
     * (@c RenderFenceState::Aborted) or timed out (@c RenderFenceState::TimedOut).
     *
     * A @c raisedChanged() signal will be emitted when the property changes.
     * In addition @c stateChanged() signal may be emitted when this property changes.
     *
     * The default value of this property is @c false.
     *
     * @note For compatibility reasons, one exception is that the property will be set
     * to @c true if render fence is created using builder and assigned to a
     * variable without setting raised property:
     * @code
     * // The created fence is raised.
     * RenderFence *raisedFence = RenderFence::create();
     * // To create a non-raised fence specify the raised property in the builder:
     * RenderFence *notRaisedFence = RenderFence::create().raised(false);
     * @endcode
     *
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bool raised READ isRaised WRITE setRaised RESET resetRaised NOTIFY raisedChanged FINAL)

public:

    /*!
     * @brief Construct a RenderFence instance.
     * If RenderFence created with the constructor the application must use
     * @c raise() method to raise the fence.
     *
     * @since BlackBerry 10.0.0
     */
    explicit RenderFence(QObject *parent = 0);

    /*!
     * @brief Destroys the render fence object.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~RenderFence();

    /*!
     * @brief Returns the state of the render fence.
     *
     * @return The state of the render fence.
     *
     * @since BlackBerry 10.0.0
     */
    bb::cascades::RenderFenceState::Type state() const;

    /*!
     * @brief Returns current value of @c raised property
     *
     * @return @c true if the fence is raised, and @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isRaised() const;

    /*!
     * @brief Changes the value of @c raised property.
     *
     * If set to @c true the fence becomes raised; @c state changes to
     * RenderFenceState::NotReached.
     *
     * If set to @c false the @c state changes to @c RenderFenceState::Aborted.
     *
     * A raisedChanged() signal is emitted when this property changes. In addition
     * stateChanged() may be emitted.
     *
     * @param raised if @c true the fence is raised, otherwise it becomes not raised.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setRaised(bool raised);

    /*!
     * @brief Resets the value of @c raised property to the default value @c false.
     *
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void resetRaised();

Q_SIGNALS:

    /*!
     * Emitted when the renderfence state becomes RenderFenceState::Reached.
     *
     *
     * @since BlackBerry 10.0.0
     */
    void reached();

    /*!
     * Emitted when the RenderFence state becomes RenderFenceState::Aborted.
     *
     * @since BlackBerry 10.0.0
     */
    void aborted();

    /*!
     * Emitted when the RenderFence state becomes RenderFenceState::TimedOut.
     *
     * @since BlackBerry 10.0.0
     */
    void timedOut();

    /*!
     * Emitted when the RenderFence state becomes either RenderFenceState::TimedOut or
     * RenderFenceState::Aborted.
     *
     * This is a convenience signal which can be used to connect single slot to handle
     * both non-reach states.
     *
     * It is emitted in addition to aborted() and timedOut().
     *
     * @since BlackBerry 10.0.0
     */
    void failedToReach();

    /*!
     * Emitted when the state of the RenderFence instance changes
     *
     * @note Due to a work around for a Qt Core issue with accessing enums from QML
     * the argument of this signal doesn't follow naming convention for signals in
     * which the signal arguments are typically named to match the associated property's name.
     * Use the object's property to access current property value instead of the signal argument
     * to avoid runtime errors (i.e. use @c state instead of @c newState).
     *
     * @param newState the new state of the RenderFence
     *
     * @since BlackBerry 10.0.0
     */
    void stateChanged(bb::cascades::RenderFenceState::Type newState);

    /*!
     * Emitted when the raised property changes.
     *
     * @param raised the new value of @c raised property. If it is @c true the fence
     * has been raised (corresponds to @c RenderFenceState::NotReached), if it is @c false
     * the fence is not currently raised.
     *
     * @since BlackBerry 10.0.0
     */
    void raisedChanged(bool raised);

private:
    /*! @cond PRIVATE */
    void setAutoDeleted(bool autoDeleted);
    Q_DECLARE_PRIVATE(RenderFence)
    Q_DISABLE_COPY(RenderFence)
    /*! @endcond */

public:
    /*!
     * A builder template for constructing a @c RenderFence. To retrieve the builder, call
     * @c RenderFence::create().
     *
     * @since BlackBerry 10.0.0
     */
    template <typename BuilderType, typename BuiltType>
    class TBuilder : public BaseObject::TBuilder<BuilderType, BuiltType> {
    protected:
        TBuilder(BuiltType* node) : BaseObject::TBuilder<BuilderType, BuiltType>(node)
        {}

    public:
        /*!
         * A convenience method for connecting passed receiver's slot to
         * the reached() signal with the default connection type
         * Qt::AutoConnection.
         *
         * Example:
         * @code
         * RenderFence *renderFence = RenderFence::create()
         *     .onReached(this, SLOT(onReachedHandler()));
         * @endcode
         *
         * @param receiver A receiver object. This object cannot be @c null.
         * @param method The name of the slot to connect to in the receiver object. This receiver object cannot be @c null.
         *
         * @see BaseObject::TBuilder::connect()
         *
         * @since BlackBerry 10.0.0
         */
        BuilderType& onReached(const QObject* receiver, const char *method) {
            this->connect(SIGNAL(reached()), receiver, method);
            return this->builder();
        }

        /*!
         * A convenience method for connecting passed receiver's slot to
         * the aborted() signal with the default connection type
         * Qt::AutoConnection.
         *
         * Example:
         * @code
         * RenderFence *renderFence = RenderFence::create()
         *     .onAborted(this, SLOT(onAbortedHandler()));
         * @endcode
         *
         * @param receiver A receiver object. This object cannot be @c null.
         * @param method The name of the slot to connect to in the receiver object. 
         *               This receiver object cannot be @c null.
         *
         * @see BaseObject::TBuilder::connect()
         *
         * @since BlackBerry 10.0.0
         */
        BuilderType& onAborted(const QObject* receiver, const char *method) {
            this->connect(SIGNAL(aborted()), receiver, method);
            return this->builder();
        }

        /*!
         * A convenience method for connecting passed receiver's slot to
         * the timedOut() signal with the default connection type
         * Qt::AutoConnection.
         *
         * Example:
         * @code
         * RenderFence *renderFence = RenderFence::create()
         *     .onTimedOut(this, SLOT(onTimedOutHandler()));
         * @endcode
         *
         * @param receiver A receiver object. This object cannot be @c null.
         * @param method The name of the slot to connect to in the receiver object.
         *               This receiver object cannot be @c null.
         *
         * @see BaseObject::TBuilder::connect()
         *
         * @since BlackBerry 10.0.0
         */
        BuilderType& onTimedOut(const QObject* receiver, const char *method) {
            this->connect(SIGNAL(timedOut()), receiver, method);
            return this->builder();
        }

        /*!
         * @brief A convenience method for connecting the slot in the receiver, passed in as a parameter, to
         * the failedToReach() signal with the default connection type @c Qt::AutoConnection.
         *
         * Example:
         * @code
         * RenderFence *renderFence = RenderFence::create()
         *     .onFailedToReach(this, SLOT(onFailedToReachHandler()));
         * @endcode
         *
         * @param receiver A receiver object. This object cannot be @c null.
         * @param method The name of the slot to connect to in the receiver object. This receiver object cannot be @c null.
         *
         * @see BaseObject::TBuilder::connect()
         *
         * @since BlackBerry 10.0.0
         */
        BuilderType& onFailedToReach(const QObject* receiver, const char *method) {
            this->connect(SIGNAL(failedToReach()), receiver, method);
            return this->builder();
        }

        /*!
         * @brief Specifies whether this fence should be automatically deleted
         * when reaches the end state.
         *
         * @details If set to @c true the instance will be automaticlaly deleted using
         * @c QObject::deleteLater().
         *
         * @param autoDeleted Whether instance should be auto deleted (default value
         * of the parameter is @c true)
         *
         * @since BlackBerry 10.0.0
         */
        BuilderType& autoDeleted(bool autoDeleted = true) {
            this->instance().setAutoDeleted(autoDeleted);
            return this->builder();
        }

        /*!
         * @brief Specifies whether this fence should be automatically raised
         * after being created or not.
         *
         * @details If set to @c true, the instance will be automatically raised using
         * @c RenderFence::raise() method, if set to @c false the fence will not be
         * raised.
         *
         * @param raised If @c true the fence will be raised, and not otherwise.
         *
         * @since BlackBerry 10.0.0
         */
        BuilderType& raised(bool raised) {
            this->instance().setRaised(raised);
            return this->builder();
        }
    };

    /*!
     * @brief A builder template for constructing a @c RenderFence. To retrieve the builder, call
     * @c RenderFence::create().
     *
     * @since BlackBerry 10.0.0
     */
    class Builder : public TBuilder<Builder, RenderFence>
    {
    public:
        explicit Builder() : TBuilder<Builder, RenderFence>(new RenderFence()) {
        }
    };

    /*! 
     * @brief Creates and returns a builder for constructing a @c RenderFence.
     *
     * Using the builder to create a @c %RenderFence:
     * @code
     * RenderFence* renderFence = RenderFence::create();
     * @endcode
     *
     * @return A builder used for constructing a @c %RenderFence.
     *
     * @since BlackBerry 10.0.0
     */
    static Builder create() {
        return Builder();
    }

};

} // namespace cascades
} // namespace bb

QML_DECLARE_TYPE(bb::cascades::RenderFence)

#endif
