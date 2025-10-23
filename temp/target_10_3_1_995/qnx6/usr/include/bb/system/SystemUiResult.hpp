/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */
#ifndef BB_SYSTEM_SYSTEMUIRESULT_HPP
#define BB_SYSTEM_SYSTEMUIRESULT_HPP

#include <bb/system/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace system
{

/*!
 * @headerfile SystemUiResult.hpp <bb/system/SystemUiResult>
 *
 * @brief The possible results of a UI request.
 *
 * @xmlonly
 * <apigrouping group="User Interface/System UI"/>
 * <library name="bbsystem"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT SystemUiResult
{
    Q_GADGET
    Q_ENUMS (Type)

public:
    /*!
     * @brief The possible results of a UI request.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {

        /*!
         * @brief No result is available.
         * 
         * @details This result is returned when a dialog raised using the @c exec()
         * method is dismissed using the @c cancel() method.
         *
         * @since BlackBerry 10.0.0
         */
        None                    = 0,

        /*!
         * @brief A button other than the confirm, custom, or cancel buttons was selected.
         *
         * @since BlackBerry 10.0.0
         */
        ButtonSelection         = 1,

        /*!
         * @brief Confirm button was selected.
         *
         * @since BlackBerry 10.0.0
         */
        ConfirmButtonSelection  = 2,

        /*!
         * @brief Cancel button was selected.
         *
         * @since BlackBerry 10.0.0
         */
        CancelButtonSelection   = 3,

        /*!
         * @brief The request timed out.
         *
         * @since BlackBerry 10.0.0
         */
        TimeOut                 = 4,

        /*!
         * @brief The request failed due to an error.
         *
         * @since BlackBerry 10.0.0
         */
        Error                   = 5,

        /*!
         * @brief Custom button was selected.
         *
         * @since BlackBerry 10.0.0
         */
        CustomButtonSelection   = 6,

        /*!
         * @brief A call to @c exec() cannot block because
         * the dialog is already on the screen.
         *
         * @since BlackBerry 10.2.0
         */
        DialogCannotBlock  		= 7,

        /*!
         * @brief The dialog was dismissed because an item was selected.
         * 
         * @details This result can be produced by a @c SystemListDialog with the
         * @c dismissOnSelection property set to @c true.
         * 
         * @since BlackBerry 10.2.0
         */
        ItemSelection = 8

    };

private:
//!@cond PRIVATE
    SystemUiResult();
    ~SystemUiResult();
//!@endcond
};

} // namespace system
} // namespace bb

QML_DECLARE_TYPE(bb::system::SystemUiResult)
#endif // BB_SYSTEM_SYSTEMUIRESULT_HPP
