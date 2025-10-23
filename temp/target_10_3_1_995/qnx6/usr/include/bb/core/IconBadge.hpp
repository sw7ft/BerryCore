/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CORE_ICONBADGE_HPP
#define BB_CORE_ICONBADGE_HPP

#include <bb/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{

/*!
 * @headerfile IconBadge.hpp <bb/IconBadge>
 *
 * @brief The set of badges that can be applied to an application icon on the home screen.
 *
 * @see bb::Application::setIconBadge
 *
 * @xmlonly
 * <apigrouping group="Platform/Home screen"/>
 * <library name="bb"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_CORE_EXPORT IconBadge
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief The set of badges that can be applied to an application icon on the home screen.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief No badge.
         *
         * @since BlackBerry 10.0.0
         */
        None = 0,

        /*!
         * @brief A splat badge (a white asterisk in a red circle).
         *
         * @since BlackBerry 10.0.0
         */
        Splat = 1
    };

private:
//!@cond PRIVATE
    IconBadge();
    ~IconBadge();
//!@endcond
};

} // namespace bb

QML_DECLARE_TYPE(bb::IconBadge)
#endif // BB_CORE_ICONBADGE_HPP
