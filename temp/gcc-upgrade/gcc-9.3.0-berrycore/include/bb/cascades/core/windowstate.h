/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 * 
*/

#ifndef BB_CASCADES_WINDOWSTATE_H
#define BB_CASCADES_WINDOWSTATE_H

#include <bb/cascades/bbcascades_global.h>

#include <QObject>
#include <QDebug>

namespace bb {
namespace cascades {

/*!
 * @brief A class representing window lifecycle states.
 * 
 * This class represents different states the @c libscreen window 
 * goes through.
 *
 * @see Window
 *
 * @xmlonly
 *     <apigrouping group="User interface/Core controls"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT WindowState {
    Q_GADGET
    Q_ENUMS(Type)

public:

   /*!
    * @brief Specifies different states of a @c %Window.
    *
    *
    * @since BlackBerry 10.0.0
    */
    enum Type {

        /*!
         * @brief @c %Window has been created but not yet posted.
         *
         * @since BlackBerry 10.0.0
         */
        Created = 0,

        /*! 
         * @brief @c %Window has been posted.
         *
         * See @c libscreen documentation for more information on window's posted event
         * and its meaning in the window lifecycle.
         *
         * @since BlackBerry 10.0.0
         */
        Posted = 1
    };

private:
    /*! @cond PRIVATE */
    WindowState();
    virtual ~WindowState();
    /*! @endcond */
};

/*!
 * @brief Streams debug output about the pattern to the QDebug stream object.
 *
 * @param dbg     The QDebug stream.
 * @param state   The state to output debug information about.
 * @return        The QDebug stream.
 */
BBCASCADES_EXPORT QDebug operator<<(QDebug dbg, WindowState::Type state);

}
}

#endif // BB_CASCADES_WINDOWSTATE_H
