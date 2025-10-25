/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 * 
*/

#ifndef BB_CASCADES_RENDERFENCESTATE_H
#define BB_CASCADES_RENDERFENCESTATE_H

#include <bb/cascades/bbcascades_global.h>

#include <QObject>
#include <QDebug>

namespace bb {
namespace cascades {

/*!
 * @brief A class representing RenderFence states
 * 
 * This class represents different states the @c RenderFence 
 * goes through.
 *
 * @see RenderFence
 *
 * @xmlonly
 *     <apigrouping group="User interface/Core controls"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT RenderFenceState {
    Q_GADGET
    Q_ENUMS(Type)

public:

   /*!
    * @brief Specifies different states of a @c %RenderFence.
    *
    *
    * @since BlackBerry 10.0.0
    */
    enum Type {

        /*!
         * @brief The @c %RenderFence has been created but not raised.
         *
         * @since BlackBerry 10.0.0
         */
        Created = 4,

        /*!
         * @brief The @c %RenderFence has been raised but not yet reached.
         *
         * @since BlackBerry 10.0.0
         */
        NotReached = 0,

        /*!
         * @brief The @c %RenderFence has been reached.
         *
         * @since BlackBerry 10.0.0
         */
        Reached = 1,

        /*!
         * @brief The @c %RenderFence has been aborted.
         * This state can be reached if the application interrupted rendering for some reason
         * (such as card being pooled, application going into background and so on) or if
         * @c RenderFence::raised property has been explicitly set to @c false.
         *
         * @since BlackBerry 10.0.0
         */
        Aborted = 2,

        /*!
         * @brief The @c %RenderFence has been timed out.
         * Issued if a raised fence hasn't been reached or aborted in 3 seconds.
         *
         * @since BlackBerry 10.0.0
         */
        TimedOut = 3,
    };

private:
    /*! @cond PRIVATE */
    RenderFenceState();
    virtual ~RenderFenceState();
    /*! @endcond */
};

/*!
 * @brief Streams debug output about the pattern to the QDebug stream object.
 *
 * @param dbg     The QDebug stream.
 * @param state   The state to output debug information about.
 * 
 * @return        The QDebug stream.
 */
BBCASCADES_EXPORT QDebug operator<<(QDebug dbg, RenderFenceState::Type state);

} // namespace cascades
} // namespace bb

#endif // BB_CASCADES_RENDERFENCESTATE_H
