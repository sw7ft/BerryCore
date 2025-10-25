/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_imageanimatoranchor_h
#define cascades_imageanimatoranchor_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
namespace cascades {

/*!
 * @brief A set of anchor configurations to use with @c ImageAnimator.
 *
 * @xmlonly
 * <apigrouping group="User interface/Resources"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT ImageAnimatorAnchor {

    Q_GADGET
    Q_ENUMS(Type)

public:

   /*!
    * @brief Specifies the anchor point in an animated image.
    *
    * @since BlackBerry 10.0.0
    */
    enum Type {

        /*!
         * @brief The first frame in an animated image anchor point.
         *
         * @since BlackBerry 10.0.0
         */
        FirstFrame   = 1,

        /*!
         * @brief The current frame in an animated image anchor point.
         *
         * @since BlackBerry 10.0.0
         */
        CurrentFrame = 2,

        /*!
         * @brief The last frame in an animated image anchor point.
         *
         * @since BlackBerry 10.0.0
         */
        LastFrame    = 3
    };

private:
    ImageAnimatorAnchor();
    ~ImageAnimatorAnchor();
};

}
}

#endif // cascades_imageanimatoranchor_h

