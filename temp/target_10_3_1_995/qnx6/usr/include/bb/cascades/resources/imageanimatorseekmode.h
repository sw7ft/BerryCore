/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_imageanimatorseekmode_h
#define cascades_imageanimatorseekmode_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
namespace cascades {

/*!
 * @brief A set of seek mode configurations to use with @c ImageAnimator.
 *
 * @xmlonly
 * <apigrouping group="User interface/Resources"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT ImageAnimatorSeekMode {
    Q_GADGET
    Q_ENUMS(Type)
public:

    /*!  
     * @brief Specifies the anchor when controlling an animated image.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {

        /*!
         * @brief The default seek mode when controlling an image.
         *
         * @since BlackBerry 10.0.0
         */
        Default   = 0,

        /*!
         * @brief A seek mode that makes the image jump immediately to the anchor when
         * controlling an image.
         *
         * @since BlackBerry 10.0.0
         */
        Immediate = 1,

        /*!
         * @brief A seek mode that makes the image continue animating until it reaches
         * the anchor when controlling an image.
         *
         * @since BlackBerry 10.0.0
         */
        Animate   = 2,
    };

private:
    ImageAnimatorSeekMode();
    ~ImageAnimatorSeekMode();
};

}
}

#endif // cascades_imageanimatorseekmode_h

