/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_animationstate_h
#define cascades_animationstate_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
    namespace cascades {

/*!
 * @brief States of an animation, like stopped, started, and ended.
 *
 * @since BlackBerry 10.0.0
 *
 * @xmlonly
 * <apigrouping group="User interface/Animations"/>
 * @endxmlonly
 */
class BBCASCADES_EXPORT AnimationState {
    Q_GADGET
    Q_ENUMS(Type)

public:

    /*!
    * @brief States of an animation.
    *
    * @xmlonly
    * <apigrouping group="User interface/Animations"/>
    * @endxmlonly
     *
     * @since BlackBerry 10.0.0
    */
    enum Type {
            /*! @brief Indicates whether the animation was interruped by the stop function.
             *
             * @since BlackBerry 10.0.0
             */
            Stopped,
            /*! @brief Indicates whether the animation is currently playing.
             *
             * @since BlackBerry 10.0.0
             */
            Playing,
            /*! @brief Indicates that the animation has ended.
             *
             * @since BlackBerry 10.0.0
             */
            Ended,
            /*! @brief Indicates that the animation is started, but not yet playing.
             *
             * @since BlackBerry 10.0.0
             */
            Started,
            /*! @brief Indicates that the animation is about to stop, but hasent stopped yet.
             *
             * @since BlackBerry 10.0.0
             */
            Stopping
        };

private:

    /*! @cond PRIVATE */
    AnimationState();
    ~AnimationState();
    /*! @endcond */
};

    }
}
#endif //cascades_animationstate_h
