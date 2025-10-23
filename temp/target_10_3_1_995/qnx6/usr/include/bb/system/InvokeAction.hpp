/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_INVOKEACTION_HPP
#define BB_SYSTEM_INVOKEACTION_HPP

#include <bb/system/Global>
#include <bb/system/InvokeTarget>

#include <QScopedPointer>
#include <QList>
#include <QString>
#include <QUrl>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace system
{

class InvokeActionPrivate;

/*!
 * @headerfile InvokeAction.hpp <bb/system/InvokeAction>
 *
 * @brief An operation that a remote target can perform.
 *
 * @xmlonly
 * <apigrouping group="App Integration/Invocation framework"/>
 * <library name="bbsystem"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT InvokeAction
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    
    /*!
     * @brief The kinds of actions that can be queried.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief All possible actions.
         *
         * @details Some actions may not have an icon and label.
         *
         * @since BlackBerry 10.0.0
         */
        All = 0,

        /*!
         * @brief Actions with an icon and label that are suitable for display in a menu.
         *
         * @since BlackBerry 10.0.0
         */
        Menu = 1
    };

    /*!
     * @brief Creates a new @c InvokeAction object.
     *
     * @since BlackBerry 10.0.0
     */
    InvokeAction();

    /*!
     * @brief Creates a copy of an existing @c InvokeAction object.
     *
     * @param other The source @c InvokeAction object to copy.
     *
     * @since BlackBerry 10.0.0
     */
    InvokeAction(const InvokeAction &other);

    /*!
     * @brief Destroys this @c InvokeAction object.
     *
     * @since BlackBerry 10.0.0
     */
    ~InvokeAction();
    
    /*!
     * @brief Copies the data of an existing @c InvokeAction object to this object.
     *
     * @param other The source @c InvokeAction object to copy.
     *
     * @return The @c InvokeAction instance.
     *
     * @since BlackBerry 10.0.0
     */
    InvokeAction& operator=(const InvokeAction &other);

    /*!
     * @brief Returns the operation the client can ask the target to perform.
     *
     * @details Use this value with @c InvokeRequest::setAction().
     *
     * @return The operation the client can ask the target to perform.
     *
     * @since BlackBerry 10.0.0
     */
    QString name() const;

    /*!
     * @brief Returns a path to a localized icon file that represents the action.
     *
     * @return A path to a localized icon file that represents the action.
     *
     * @since BlackBerry 10.0.0
     */
    QUrl icon() const;

    /*!
     * @brief Returns the localized name of the action.
     *
     * @return The localized name of the action.
     *
     * @since BlackBerry 10.0.0
     */
    QString label() const;

    /*!
     * @brief Returns the identity of the target (as stated in its BAR manifest) that
     * handles this action for an unbounded invocation.
     *
     * @details If omitted, this action has no default handler.
     *
     * @return The identity of the target that handles this action for an unbounded 
     *         invocation or an empty string if no default exists.
     *
     * @since BlackBerry 10.0.0
     */
    QString defaultTarget() const;

    /*!
     * @brief Returns the list of targets that support this action.
     *
     * @return The list of targets that support this action.
     *
     * @since BlackBerry 10.0.0
     */
    QList<InvokeTarget> targets() const;

private:
//!@cond PRIVATE
    QScopedPointer<InvokeActionPrivate> const d_ptr;
    Q_DECLARE_PRIVATE(InvokeAction)
//!@endcond
};

} // namespace system
} // namespace bb

QML_DECLARE_TYPE(bb::system::InvokeAction)
#endif // BB_SYSTEM_INVOKEACTION_HPP
