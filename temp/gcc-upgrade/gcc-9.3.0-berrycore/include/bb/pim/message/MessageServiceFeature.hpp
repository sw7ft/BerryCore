/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#include <bb/pim/Global>

#ifndef BB_PIM_MESSAGE_MESSAGESERVICEFEATURE_HPP
#define BB_PIM_MESSAGE_MESSAGESERVICEFEATURE_HPP

namespace bb {
namespace pim {
namespace message {
/*!
 *
 * @brief The @c MessageServiceFeature class includes message service features for an account.
 *
 * @details You can use this class to determine if a message service feature is supported for an
 * account. For example, you can determine if folder management is supported for a specific account.
 * You can determine if a feature is supported by calling @c MessageService::isFeatureSupported().
 * 
 * @see MessageService
 *
 * @xmlonly
 * <apigrouping group="App Integration/Message"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */

class BB_PIM_EXPORT MessageServiceFeature
{

public:
    /*!
     * @brief An enumeration of supported message service features.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type{
        /*!
         * @brief Indicates whether the folder management feature is available for an account.
         *
         * @since BlackBerry 10.0.0
         */
        FolderManagement=0,
        /*!
         * @brief Indicates whether the remote search feature is available for an account.
         *
         * @since BlackBerry 10.0.0
         */
        RemoteSearch=1
    };

private:
    /*! @cond PRIVATE */
    MessageServiceFeature();
    ~MessageServiceFeature();
    /*! @endcond */

};

} /* namespace message */
} /* namespace pim */
} /* namespace bb */

#endif // BB_PIM_MESSAGE_MESSAGESERVICEFEATURE_HPP
