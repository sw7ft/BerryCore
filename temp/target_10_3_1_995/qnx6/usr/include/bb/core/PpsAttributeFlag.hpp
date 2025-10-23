/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CORE_PPSATTRIBUTEFLAG_HPP
#define BB_CORE_PPSATTRIBUTEFLAG_HPP

#include <bb/Global>

#include <QObject>
#include <QFlags>

namespace bb
{

/*!
 * @headerfile PpsAttributeFlag.hpp <bb/PpsAttributeFlag>
 * 
 * @brief Additional state information about a PPS attribute.
 *
 * @xmlonly
 * <apigrouping group="Platform/Utility"/>
 * <library name="bb"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_CORE_EXPORT PpsAttributeFlag
{
    Q_GADGET
    Q_ENUMS(Type)
    Q_FLAGS(Types)

public:
    /*!
     * @brief Additional state information about a PPS attribute.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief The object or attribute line is incomplete.
         *
         * @since BlackBerry 10.0.0
         */
        Incomplete = 0x01,

        /*!
         * @brief The object or attribute has been deleted.
         *
         * @since BlackBerry 10.0.0
         */
        Deleted    = 0x02,

        /*!
         * @brief The object has been created.
         *
         * @since BlackBerry 10.0.0
         */
        Created    = 0x04,

        /*!
         * @brief The object or attribute has been truncated.
         *
         * @since BlackBerry 10.0.0
         */
        Truncated  = 0x08,

        /*!
         * @brief A critical publisher has closed its connection and all non-persistent attributes have been deleted.
         *
         * @since BlackBerry 10.0.0
         */
        Purged     = 0x10
    };
    Q_DECLARE_FLAGS(Types, Type)

private:
//!@cond PRIVATE
    PpsAttributeFlag();
    ~PpsAttributeFlag();
//!@endcond
};

Q_DECLARE_OPERATORS_FOR_FLAGS(PpsAttributeFlag::Types)

} // namespace bb

#endif // BB_CORE_PPSATTRIBUTEFLAGS_HPP
