/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2012
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_MESSAGEUPDATETYPE_HPP
#define BB_PIM_MESSAGEUPDATETYPE_HPP

#include <bb/pim/Global>

namespace bb {
namespace pim {
namespace message {

/*!
 *
 * @brief ...
 */
class BB_PIM_EXPORT MessageUpdateType
{
public:
    enum Type {
        None = 1 << 0,
        StatusChange = 1 << 1,
        FolderMove = 1 << 2,
        TransmissionStatus = 1 << 3
    };

private:
    /*! @cond PRIVATE */
    MessageUpdateType();
    ~MessageUpdateType();
    /*! @endcond */
};

} /* namespace message */
} /* namespace pim */
} /* namespace bb */

#endif // BB_PIM_MESSAGEUPDATETYPE_HPP
