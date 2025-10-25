/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_INVOKETARGET_HPP
#define BB_SYSTEM_INVOKETARGET_HPP

#include <bb/system/Global>

#include <bb/system/SecurityPerimeter>

#include <QFlags>
#include <QScopedPointer>
#include <QString>
#include <QUrl>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace system
{

class InvokeTargetPrivate;

/*!
 * @headerfile InvokeTarget.hpp <bb/system/InvokeTarget>
 *
 * @brief The @c InvokeTarget class represents a remote application, card, or service that can be invoked.
 *
 * @xmlonly
 * <apigrouping group="App Integration/Invocation framework"/>
 * <library name="bbsystem"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT InvokeTarget
{
    Q_GADGET
    Q_ENUMS(Type)

public:

    /*!
     * @brief The kinds of processes that can be targets.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief No target is specified.
         *
         * @since BlackBerry 10.0.0
         */
        Unspecified = 0x0,

        /*!
         * @brief The target is an application accessible from the home screen.
         *
         * @since BlackBerry 10.0.0
         */
        Application = 0x1,

        /*!
         * @brief The target is an application that runs using the full screen of the
         * device, on top of any windows of the invoking parent application.
         *
         * @details When an application is invoked as a card, it is considered
         * to be part of the invoking application rather than a separately-running
         * application.  As such, an application running as a card does not appear in
         * the list of running applications on the home screen.
         *
         * @since BlackBerry 10.0.0
         */
        Card        = 0x2,

        //!@cond PRIVATE
        /**
         * @brief The target renders its UI into a window hosted by the client.
         *
         * @note Deprecated. To maintain binary compatibility, do not remove or renumber.
         */
        Viewer      = 0x4,
        //!@endcond

        /*!
         * @brief The target is a background process in the operating system.
         *
         * @since BlackBerry 10.0.0
         */
        Service     = 0x8,

        /*!
         * @brief Include a target even if the target is the same as the client.
         *
         * @details This value is valid only for specifying target types for
         * invocation target queries. An @c InvokeTarget will not
         * have type @c InvokeTarget::Self.
         *
         * @since BlackBerry 10.0.0
         */
        Self        = 0x10,

        /*!
         * @brief The target is a headless application.
         *
         * @since BlackBerry 10.3.0
         */
        Headless    = 0x40,
    };

    Q_DECLARE_FLAGS(Types, Type)

    /*!
     * @brief Creates a new @c InvokeTarget object.
     *
     * @since BlackBerry 10.0.0
     */
    InvokeTarget();

    /*!
     * @brief Creates a copy of an existing @c InvokeTarget object.
     *
     * @param other The source @c InvokeTarget object to copy.
     *
     * @since BlackBerry 10.0.0
     */
    InvokeTarget(const InvokeTarget &other);

    /*!
     * @brief Destroys this @c InvokeTarget object.
     *
     * @since BlackBerry 10.0.0
     */
    ~InvokeTarget();

    /*!
     * @brief Copies the data of an existing @c InvokeTarget object to this object.
     *
     * @param other The source @c InvokeTarget object to copy.
     *
     * @return The @c InvokeTarget instance.
     *
     * @since BlackBerry 10.0.0
     */
    InvokeTarget& operator=(const InvokeTarget &other);

    /*!
     * @brief Returns the identity of the target as stated in its BAR manifest.
     *
     * Use value with @c InvokeRequest::setTarget().
     *
     * @return The identity of the target.
     *
     * @since BlackBerry 10.0.0
     */
    QString name() const;

    /*!
     * @brief Returns a path to a localized icon file that represents the target.
     *
     * @return A path to a localized icon file that represents the target.
     *
     * @since BlackBerry 10.0.0
     */
    QUrl icon() const;

    //!@cond PRIVATE
    /*!
     * @brief Returns a path to a localized splash screen file that may be shown while a
     * viewer is loading.
     *
     * @details If the invocation target in a viewer, then the splash screen URI will always be
     * non-empty.  If the target is not a viewer, then the splash screen URI will always be empty.
     *
     * @return A path to a localized splash screen file that represents the viewer or an
     *         empty URI if the target is not a viewer.
     */
    QUrl splash() const BB_DEPRECATED;
    //!@endcond

    /*!
     * @brief Returns the localized name of the target.
     *
     * @return The localized name of the target.
     *
     * @since BlackBerry 10.0.0
     */
    QString label() const;

    /*!
     * @brief Returns whether the target is an application, or a card.
     *
     * @return The kind of process represented by the target.  See @c InvokeTarget::Type for the
     * list of invocation target types.
     *
     * @since BlackBerry 10.0.0
     */
    Type type() const;

    /*!
     * @brief Returns the security perimeter of the target.
     *
     * @return The target's security perimeter.  See @c bb::system::SecurityPerimeter for the list
     * of perimeters.
     *
     * @since BlackBerry 10.0.0
     *
     */
    bb::system::SecurityPerimeter::Type perimeter() const;

private:
//!@cond PRIVATE
    QScopedPointer<InvokeTargetPrivate> const d_ptr;
    Q_DECLARE_PRIVATE(InvokeTarget)
//!@endcond
};

Q_DECLARE_OPERATORS_FOR_FLAGS(InvokeTarget::Types)

} // namespace system
} // namespace bb

QML_DECLARE_TYPE(bb::system::InvokeTarget)
#endif // BB_SYSTEM_INVOKETARGET_HPP


