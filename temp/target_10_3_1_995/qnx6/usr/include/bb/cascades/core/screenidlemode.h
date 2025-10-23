/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CASCADES_SCREENIDLEMODE_H
#define BB_CASCADES_SCREENIDLEMODE_H

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
namespace cascades {
    
/*!
 * @brief Represents the choices in how the screen idle behavior can be controlled.
 * 
 * @xmlonly
 *     <apigrouping group="User interface/Core controls"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT ScreenIdleMode
{
private:
    Q_GADGET
    Q_ENUMS (Type)
        
public:
    /*!
     * @brief The different screen idle modes
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief Idle behaviour of the screen is unaltered.
         *
         * @since BlackBerry 10.0.0
         */
        Normal = 0,
        /*!
         * @brief Prevent the idle behaviour from occurring.
         *
         * @since BlackBerry 10.0.0
         */
        KeepAwake = 1
    };
        
private:
//! @cond PRIVATE
    ScreenIdleMode();
    ~ScreenIdleMode();
//! @endcond PRIVATE
};

/*!
 * @brief Streams debug output about the pattern to the QDebug stream object.
 *
 * @param dbg               The QDebug stream.
 * @param screenIdleMode    The state to output debug information about.
 * @return                  The QDebug stream.
 */
BBCASCADES_EXPORT QDebug operator<<(QDebug dbg, ScreenIdleMode::Type screenIdleMode);
    
} // namespace cascasdes
} // namespace bb

#endif // BB_CASCADES_SCREENIDLEMODE_H
