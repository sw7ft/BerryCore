/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */
#ifndef BB_SYSTEM_SYSTEMUIMODALITY_HPP
#define BB_SYSTEM_SYSTEMUIMODALITY_HPP

#include <bb/system/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace system
{

/*!
 * @headerfile SystemUiModality.hpp <bb/system/SystemUiModality>
 *
 * @brief The possible modality values for a UI request.
 *
 * @xmlonly
 * <apigrouping group="User Interface/System UI"/>
 * <library name="bbsystem"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT SystemUiModality
{
    Q_GADGET
    Q_ENUMS (Type)

public:
    /*!
     * @brief The possible modality values for a UI request.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {

        /*!
         * @brief The UI is application-modal.
         *
         * @since BlackBerry 10.0.0
         */
        Application = 1,

        /*!
         * @brief The UI is modal across all applications.
         * @details Elevated permissions are required to use global modality.
         *
         * @since BlackBerry 10.0.0
         */
        Global      = 2
    };

private:
//!@cond PRIVATE
    SystemUiModality();
    ~SystemUiModality();
//!@endcond
};

} // namespace system
} // namespace bb

QML_DECLARE_TYPE(bb::system::SystemUiModality)
#endif // BB_SYSTEM_SYSTEMUIMODALITY_HPP
