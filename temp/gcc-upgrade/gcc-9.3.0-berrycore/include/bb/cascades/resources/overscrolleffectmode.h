/* Copyright (C) 2011-2013 Research In Motion Limited.  */
#ifndef cascades_overscrolleffectmode_h
#define cascades_overscrolleffectmode_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
namespace cascades {

/*!
 * 
 * @brief Represents a set of states for overscroll effects in a @c ScrollView.
 *
 * @xmlonly
 * <apigrouping group="User interface/Resources"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT OverScrollEffectMode {
    Q_GADGET
    Q_ENUMS(Type)

    public:
        /*!
         * @brief The overscroll effect mode type.
         *
         * @since BlackBerry 10.0.0
         */
        enum Type {
          /*!
           * @brief The default overscroll effect.
           *
           * The system determines the overscroll effect for the @c ScrollView.
           *
           * @since BlackBerry 10.0.0
           */
          Default = 0x0,
          /*!
           * @brief No effect is applied.
           *
           * @since BlackBerry 10.0.0
           */
          None = 0x1,
          /*!
           * @brief The effect is applied only when the user is scrolling.
           *
           * @since BlackBerry 10.0.0
           */
          OnScroll = 0x2,
           /*!
            * @brief The effect is applied only when the user pinch to zoom.
            *
            * @since BlackBerry 10.0.0
            */
          OnPinch = 0x3,
           /*!
            * @brief The effect is applied for both pinch and scroll.
            *
            * @since BlackBerry 10.0.0
            */
          OnPinchAndScroll = 0x4,
        };
    private:
        /*! @cond PRIVATE */
        OverScrollEffectMode();
        ~OverScrollEffectMode();
        /*! @endcond */
};

}
}

#endif // cascades_overscrolleffectmode_h
