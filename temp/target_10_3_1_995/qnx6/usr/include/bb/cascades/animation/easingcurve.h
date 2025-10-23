/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_easingcurve_h
#define cascades_easingcurve_h

#include <QSharedDataPointer>
#include <bb/cascades/bbcascades_global.h>

namespace bb {
    namespace cascades {

    class EasingCurveDataPrivate;
        
    /*!
     * 
     * @brief An abstract class for easing curves that are used with animations.
     *
     * Easing curves are functions that specify the speed of an animation.
     * You can use them to make animations look more realistic without requiring you to do physics calculations.
     * For example, when you animate a dropping ball, you want the ball to speed up as it drops.
     * An easing curve that eases out would create that effect.
     *
     * See StockCurve for a list of constants representing different easing curves.
     *
     * @xmlonly
     * <apigrouping group="User interface/Animations"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT EasingCurve {
    public:
        /*!
         * @brief Copy constructor for @c %EasingCurve objects.
         *
         * @since BlackBerry 10.0.0
         */
        EasingCurve(const EasingCurve &orig);

        /*!
         * @brief A @c = operator  for @c %EasingCurve objects.
         *
         * @since BlackBerry 10.0.0
         */
        EasingCurve& operator=(const EasingCurve& other);
        
        /*!
         * Destructor for this class
         *
         * @since BlackBerry 10.0.0
         */ 
        virtual ~EasingCurve() = 0;
        /*! \cond PRIVATE */
        virtual bool operator==(const EasingCurve &) const;
        virtual bool operator!=(const EasingCurve &) const;
        /*! \endcond */
    protected:
        /*! @cond PRIVATE */
        EasingCurve(EasingCurveDataPrivate *data);

        friend class EasingCurveDataPrivate;
        QSharedDataPointer<EasingCurveDataPrivate> d;
        /*! @endcond */
    };




}
}


#endif	/* cascades_easingcurve_h */
