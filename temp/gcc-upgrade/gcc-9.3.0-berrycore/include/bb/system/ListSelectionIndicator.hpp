/*!
 * @copyright
 * Copyright BlackBerry Limited, 2013-2013
 * BlackBerry Limited. All rights reserved.
 */
#ifndef BB_SYSTEM_LISTSELECTIONINDICATOR_HPP
#define BB_SYSTEM_LISTSELECTIONINDICATOR_HPP

#include <bb/system/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace system
{

/*!
 * @headerfile ListSelectionIndicator.hpp <bb/system/ListSelectionIndicator>
 *
 * @brief Controls the highlighting of selected list items.
 *
 * @xmlonly
 * <apigrouping group="User Interface/System UI"/>
 * <library name="bbsystem"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.2.0
 */
class BB_SYSTEM_EXPORT ListSelectionIndicator
{
    Q_GADGET
    Q_ENUMS (Type)

public:
    /*!
     * @brief Controls the highlighting of selected list items.
     *
     * @since BlackBerry 10.2.0
     */
    enum Type {

        /*!
         * @brief The selected items will be indicated by highlighting the list item.
         * 
         * @since BlackBerry 10.2.0
         */
        Highlight = 0,
        
        /*!
         * @brief The selected items will be indicated using a button beside the item.
         * 
         * @details For multi-select lists, a checkbox will appear beside each item to indicate if the
         * item has been selected.  For single-select lists, a radio button will appear beside each item,
         * and the currently selected item will be checked.
         *
         * @since BlackBerry 10.2.0
         */
        Button = 1
    };

private:
//!@cond PRIVATE
    ListSelectionIndicator();
    ~ListSelectionIndicator();
//!@endcond
};

} // namespace system
} // namespace bb

QML_DECLARE_TYPE(bb::system::ListSelectionIndicator)
#endif // BB_SYSTEM_LISTSELECTIONINDICATOR_HPP
