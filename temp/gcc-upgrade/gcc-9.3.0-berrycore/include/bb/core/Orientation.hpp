/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CORE_ORIENTATION_HPP
#define BB_CORE_ORIENTATION_HPP

//!@cond PRIVATE

#include <bb/Global>

#include <QObject>

namespace bb
{

/*!
 * @headerfile Orientation.hpp <bb/Orientation>
 *
 * @brief Defines the set of orientations for the device.
 *
 * @xmlonly
 * <apigrouping group="Platform/Home screen"/>
 * <library name="bb"/>
 * @endxmlonly 
 */
class BB_CORE_EXPORT Orientation
{
    Q_GADGET
    Q_ENUMS(Type)

public:

    enum Type {
        /*!
         * @brief BlackBerry logo is upright.
         */
        North = 0,

        /*!
         * @brief BlackBerry logo is sideways - text runs upwards.
         */
        East = 90,

        /*!
         * @brief BlackBerry logo is upside down.
         */
        South = 180,

        /*!
         * @brief BlackBerry logo is sideways - text runs downwards.
         */
        West = 270
    };

private:
//!@cond PRIVATE
    Orientation();
    ~Orientation();
//!@endcond
};

} // namespace bb

//!@endcond

#endif // BB_CORE_ORIENTATION_HPP
