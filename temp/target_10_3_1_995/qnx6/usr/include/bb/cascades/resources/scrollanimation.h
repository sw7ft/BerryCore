/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_scrollanimation_h
#define cascades_scrollanimation_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
namespace cascades {

/*!
 * 
 * @brief Represents a set of animations for a @c ScrollView.
 *
 * Scroll animations include @c Smooth and @c None.
 *
 * @xmlonly
 * <apigrouping group="User interface/Resources"/>
 * <qml>
 * <class register="enum-only"/>
 * </qml>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT ScrollAnimation {
    Q_GADGET
    Q_ENUMS(Type)

    public:
        /*!
         * @brief Scroll animation types.
         *
         * @since BlackBerry 10.0.0
         */
        enum Type {
          /*!
            * @brief The default scroll animation.
            *
            * Leaves the choice of scroll animation to the system. Typically it will be a smooth animation.
           *
           * @since BlackBerry 10.0.0
            */
          Default = 0x0,
          /*!
            * @brief No animation.
           *
           * @since BlackBerry 10.0.0
            */
          None = 0x1,
          /*!
            * @brief Smooth animation.
           *
           * @since BlackBerry 10.0.0
            */
          Smooth = 0x2
        };
    private:
        /*! @cond PRIVATE */
        ScrollAnimation();
        ~ScrollAnimation();
        /*! @endcond */
};

}
}

#endif // cascades_scrollanimation_h 
