/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */
#ifndef BB_SYSTEM_LISTSELECTIONMODE_HPP
#define BB_SYSTEM_LISTSELECTIONMODE_HPP

#include <bb/system/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace system
{

/*!
 * @headerfile ListSelectionMode.hpp <bb/system/ListSelectionMode>
 *
 * @brief Specifies whether one item or multiple items may be chosen in the list.
 *
 * @xmlonly
 * <apigrouping group="User Interface/System UI"/>
 * <library name="bbsystem"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT ListSelectionMode
{
    Q_GADGET
    Q_ENUMS (Type)

public:
    /*!
     * @brief Controls whether one item or multiple items may be chosen in the list.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {

        /*!
         * @brief Only one item may be chosen in the list.
         *
         * @since BlackBerry 10.0.0
         */
        Single = 1,
        
        /*!
         * @brief Any number of items may be chosen in the list.
         *
         * @since BlackBerry 10.0.0
         */
        Multiple = 2
    };

private:
//!@cond PRIVATE
    ListSelectionMode();
    ~ListSelectionMode();
//!@endcond
};

} // namespace system
} // namespace bb

QML_DECLARE_TYPE(bb::system::ListSelectionMode)
#endif // BB_SYSTEM_LISTSELECTIONMODE_HPP
