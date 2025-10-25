/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CORE_LOWMEMORYWARNINGLEVEL_HPP
#define BB_CORE_LOWMEMORYWARNINGLEVEL_HPP

#include <bb/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{

/*!
 * @headerfile LowMemoryWarningLevel.hpp <bb/LowMemoryWarningLevel>
 *
 * @brief The set of possible low memory warning levels.
 *
 * @see @c bb::MemoryInfo::lowMemory
 *
 * @xmlonly
 * <apigrouping group="Platform/Info"/>
 * <library name="bb"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_CORE_EXPORT LowMemoryWarningLevel
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief The set of possible low memory warning levels.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {

        /*!
         * @brief The device is no longer running low on memory.
         *
         * @since BlackBerry 10.3.0
         */
        Clear = 0,

        /*!
         * @brief The device is running low on memory.
         *
         * @details Applications should delete objects that they no longer require, in order to free up memory.
         *
         * @since BlackBerry 10.0.0
         */
        LowPriority = 1,

        /*!
         * @brief The device is running critically short of memory.
         *
         * @details Applications should delete all objects that they no longer require, in order to free up memory. If the
         * device continues to run low on memory, applications will be
         * asked to exit. If this fails, applications will be terminated.
         *
         * @since BlackBerry 10.0.0
         */
        HighPriority = 2
    };

private:
//!@cond PRIVATE
    LowMemoryWarningLevel();
    ~LowMemoryWarningLevel();
//!@endcond
};

} // namespace bb

QML_DECLARE_TYPE(bb::LowMemoryWarningLevel)
#endif // BB_CORE_LOWMEMORYWARNINGLEVEL_HPP
