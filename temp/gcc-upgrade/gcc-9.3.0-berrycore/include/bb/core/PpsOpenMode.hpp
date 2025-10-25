/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CORE_PPSOPENMODE_HPP
#define BB_CORE_PPSOPENMODE_HPP

#include <bb/Global>

#include <QObject>
#include <QFlags>

namespace bb
{

/*!
 * @headerfile PpsOpenMode.hpp <bb/PpsOpenMode>
 *
 * @brief Bitfield values passed to the @c PpsObject::open() method.
 *
 * @details Either @c Publish, @c Subscribe, or @c PublishSubscribe must
 * always be used. @c Create and @c DeleteContents are optional.
 *
 * @xmlonly
 * <apigrouping group="Platform/Utility"/>
 * <library name="bb"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_CORE_EXPORT PpsOpenMode
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief Bitfield values passed to the @c PpsObject::open() method.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief The PPS object will open for writing only.
         *
         * @since BlackBerry 10.0.0
         */
        Publish = 1,

        /*!
         * @brief The PPS object will open for reading only.
         *
         * @since BlackBerry 10.0.0
         */
        Subscribe = 2,

        /*!
         * @brief The PPS object will open for reading and writing.
         *
         * @since BlackBerry 10.0.0
         */
        PublishSubscribe = Publish | Subscribe,

        /*!
         * @brief The PPS object does not currently exist and will be created on open.
         *
         * @details If the PPS object does exist, @c open() will fail.
         *
         * @since BlackBerry 10.0.0
         */
        Create = 4,

        /*!
         * @brief All existing attributes of the PPS object will be deleted on open.
         *
         * @since BlackBerry 10.0.0
         */
        DeleteContents = 8
    };
    Q_DECLARE_FLAGS(Types, Type)

private:
//!@cond PRIVATE
    PpsOpenMode();
    ~PpsOpenMode();
//!@endcond
};

Q_DECLARE_OPERATORS_FOR_FLAGS(PpsOpenMode::Types)

} // namespace bb

#endif // BB_CORE_PPSOPENMODE_HPP
