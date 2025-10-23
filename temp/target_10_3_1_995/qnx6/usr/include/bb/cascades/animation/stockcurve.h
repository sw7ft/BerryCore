/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_stockcurve_h
#define cascades_stockcurve_h

#include <QMetaType>
#include <QSharedDataPointer>

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/animation/easingcurve.h>

namespace bb {
    namespace cascades {

    class StockCurveDataPrivate;

    /*!
     * @brief A set of defined easing curves used for animating properties.
     *
     * Easing curves are functions that specify the speed of an animation.
     * You can use them to make animations look more realistic without requiring you to do physics calculations.
     * For example, when you animate a dropping ball, you want the ball to speed up as it drops.
     * An easing curve that eases out would create that effect.
     *
     * An easing curve is defined by two parameters: an interpolator function, 
     * and a type of curve that describes the velocity of the transition 
     * (how quickly it accelerates and decelerates at the beginning and the end of the animation).
     *
     * The velocity easing curve types are:
     * - easing In: animation is fast at the beginning, slow at the end.
     * - easing Out: animation is slow at the beginning, fast at the end.
     * - easing InOut: animation is slow at the beginning, fast in the middle, slow at the end.
     *
     * Not all easing curves are appropriate for every situation. For example,
     * @c Linear curve looks unnatural for most types of movement, but works well when changing
     * opacity. @c QuarticOut is similar to the default implicit animation used for core controls;
     * it works well with user-initiated animations since it's responsive and smooth at the same time.
     *
     * @xmlonly
     * <apigrouping group="User interface/Animations"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT StockCurve : public EasingCurve {
    public:

       /*! 
        * @brief A linear transition.
        *
        * @image html easing_Linear.png
        *
        * This curve has a linear interpolation function and no acceleration.
        * Looks unnatural for most types of movement, but works well for changing
        * opacity.
        *
        * @since BlackBerry 10.0.0
        */
        static const StockCurve Linear;
        /*!
         * @brief Starts abruptly, and ends smoothly.
         *
         * @image html easing_SineOut.png
         *
         * This curve uses a sine interpolation function and an ease out velocity type.
         *
         * @since BlackBerry 10.0.0
         */
        static const StockCurve SineOut;        
        /*! 
         * @brief Starts abruptly, and ends smoothly.
         *
         * @image html easing_QuadraticOut.png
         *
         * This stock curve has a quadratic interpolation function and ease out velocity type. Very similar to SineOut.
         *
         * @since BlackBerry 10.0.0
         */
        static const StockCurve QuadraticOut;
        
        /*! 
         * @brief Starts very abruptly and ends smoothly.
         *
         * @image html easing_CubicOut.png
         *
         * This stock curve has a cubic interpolation function and ease out velocity type.
         *
         * @since BlackBerry 10.0.0
         */
        static const StockCurve CubicOut;        
        /*!
         * @brief Starts very abruptly and ends very smoothly.
         *
         * @image html easing_ExponentialOut.png
         *
         * This stock curve has an exponential interpolation function and ease out velocity type.
         * Very similar to QuarticOut.
         *
         * @since BlackBerry 10.0.0
         */
        static const StockCurve ExponentialOut;
        
        /*!
         * @brief Performance similar to the default implicit animations.
         *
         * @image html easing_QuarticOut.png
         *
         * This stock curve has a quartic interpolation function and ease out velocity type.
         * It works well with animations that are initiated by the user,
         * because it feels responsive and smooth at the same time.
         *
         * @since BlackBerry 10.0.0
         */
        static const StockCurve QuarticOut;
        
        /*! 
         * @brief Starts abruptly and ends very smoothly.
         *
         * @image html easing_QuinticOut.png
         *
         * This stock curve has a quintic interpolation function and ease out velocity type.
         *
         * @since BlackBerry 10.0.0
         */
        static const StockCurve QuinticOut; 
        
        /*! 
         * @brief Starts explosively and ends slowly, like sliding on ice.
         *
         * @image html easing_CircularOut.png
         *
         * This stock curve has a circular interpolation function and ease out velocity type.
         *
         * @since BlackBerry 10.0.0
         */
        static const StockCurve CircularOut;        
        /*! 
         * @brief Goes slightly past the target value before settling on it.
         *
         * @image html easing_BackOut.png
         *
         * This stock curve has a back interpolation function and ease out velocity type.
         * This is the behavior a lot of lists use when you flick scroll and the list reaches the end.
         *
         * @since BlackBerry 10.0.0
         */
        static const StockCurve BackOut;
        
        /*! @brief Similar to BackOut, but with a more springy and physical feel.
         *
         * @image html easing_Elastic1Out.png
         *
         * This stock curve has an elastic bounce interpolation function and ease out velocity type.
         *
         * @since BlackBerry 10.0.0
         */
        static const StockCurve ElasticOut;        
        /*!
         * @brief A cartoonish curve, with lots of energy.
         *
         * @image html easing_Elastic2Out.png
         *
         * This stock curve has a double elastic bounce interpolation function and ease out velocity type.
         *
         * @since BlackBerry 10.0.0
         */
        static const StockCurve DoubleElasticOut;        
        /*!
         * @brief A curve that bounces once, like a marble being dropped on a hard surface.
         *
         * @image html easing_Bounce1Out.png
         *
         * This stock curve has a single bounce interpolation function and ease out velocity type. This curve
         * has a very physical feel to it.
         *
         * @since BlackBerry 10.0.0
         */
        static const StockCurve BounceOut;        
        /*! 
         * @brief A curve that bounces like a rubber ball.
         *
         * @image html easing_Bounce2Out.png
         *
         * This stock curve has a double bounce interpolation function and ease out velocity type. Like DoubleElasticOut,
         * this curve has a very cartoonish feel to it.
         *
         * @since BlackBerry 10.0.0
         */
        static const StockCurve DoubleBounceOut;        
        
        /*!
         * @brief Begins and ends smoothly and moves rather quickly in the middle.
         *
         * @image html easing_SineInOut.png
         *
         * This stock curve has a "sine" interpolation function and ease InOut velocity type.
         * It gives a nice physical feel, but it does not feel as responsive as SineOut.
         *
         * @since BlackBerry 10.0.0
         */
        static const StockCurve SineInOut;
        
        /*!
         * @brief Begins and ends smoothly and moves rather quickly in the middle.
         *
         * @image html easing_QuadraticInOut.png
         *
         * This stock curve has a quadratic interpolation function and ease InOut velocity type.
         * Very similar to SineInOut.
         *
         * @since BlackBerry 10.0.0
         */
        static const StockCurve QuadraticInOut;
        
        /*! 
         * @brief Begins and ends smoothly and moves quickly in the middle.
         *
         * @image html easing_CubicInOut.png
         *
         * This stock curve has a cubic interpolation function and ease InOut velocity type.
         *
         * @since BlackBerry 10.0.0
         */
        static const StockCurve CubicInOut;
        
        /*!
         * @brief Begins and ends very smoothly and moves very quickly in the middle.
         *
         * @image html easing_ExponentialInOut.png
         *
         * This stock curve has an exponential interpolation function and ease InOut velocity type.
         * Very similar to QuarticInout.
         *
         * @since BlackBerry 10.0.0
         */
        static const StockCurve ExponentialInOut;
        
        /*!
         * @brief Begins and ends very smoothly and moves very quickly in the middle.
         *
         * @image html easing_QuarticInOut.png
         *
         * This stock curve has a quartic interpolation function and ease InOut velocity type.
         *
         * @since BlackBerry 10.0.0
         */
        static const StockCurve QuarticInOut;
        
        /*! 
         * @brief Begins and ends super smoothly and moves super quickly in the middle.
         *
         * @image html easing_QuinticInOut.png
         *
         * This stock curve has a quintic interpolation function and ease InOut velocity type.
         *
         * @since BlackBerry 10.0.0
         */
        static const StockCurve QuinticInOut;
        /*! 
         * @brief Begins and ends with glacial slowness and almost skips the middle.
         *
         * @image html easing_CircularInOut.png
         *
         * This stock curve has a circular interpolation function and ease InOut velocity type.
         *
         * @since BlackBerry 10.0.0
         */
        static const StockCurve CircularInOut;
        /*! 
         * @brief Starts in the opposite direction and  moves rather swiftly a bit past the endpoint before it settles.
         *
         * @image html easing_BackInOut.png
         *
         * This stock curve has a "back" interpolation function and ease InOut velocity type.
         * It has an animated and cartoonish feel, like you need both strength and willpower to move this thing.
         *
         * @since BlackBerry 10.0.0
         */
        static const StockCurve BackInOut;
        /*! 
         * @brief Begins and ends very slowly, with an elastic effect in the middle.
         *
         * @image html easing_Elastic1InOut.png
         *
         * This stock curve has a single "elastic" bounce interpolation function and ease InOut velocity type.
         *
         * @since BlackBerry 10.0.0
         */
        static const StockCurve ElasticInOut;
        /*!
         * @brief Begins and ends slowly, with a double elastic effect in the middle.
         *
         * @image html easing_Elastic2InOut.png
         *
         * This stock curve has a double "elastic" bounce interpolation function and ease InOut velocity type.
         *
         * @since BlackBerry 10.0.0
         */
        static const StockCurve DoubleElasticInOut;
        /*! 
         * @brief Begins and ends slowly and bounces in the middle.
         *
         * @image html easing_Bounce1InOut.png
         *
         * This stock curve has a single bounce interpolation function and ease InOut velocity type.
         *
         * @since BlackBerry 10.0.0
         */
        static const StockCurve BounceInOut;
        /*! 
         * @brief Begins and ends slowly and bounces a lot in the middle.
         *
         * @image html easing_Bounce2InOut.png
         *
         * This stock curve has a double bounce interpolation function and ease InOut velocity type.
         *
         * @since BlackBerry 10.0.0
         */
        static const StockCurve DoubleBounceInOut;        
      
        /*! 
         * @brief Starts slowly and ends abruptly.
         *
         * @image html easing_SineIn.png
         *
         * This stock curve has a sine interpolation function and ease in velocity type.
         * This curve is good if you're animating something off screen, because the user has more time to follow
         * the start of the movement. It gives the animated object a feeling of weight.
         *
         * @since BlackBerry 10.0.0
         */
        static const StockCurve SineIn;
        
        /*! 
         * @brief Starts slowly and ends abruptly.
         *
         * @image html easing_QuadraticIn.png
         *
         * This stock curve has a quadratic interpolation function and ease in velocity type. Very similar to SineIn.
         *
         * @since BlackBerry 10.0.0
         */
        static const StockCurve QuadraticIn;
        
        /*! 
         * @brief Starts quite slowly and ends abruptly.
         *
         * @image html easing_CubicIn.png
         *
         * This stock curve has a cubic interpolation function and ease in velocity type. Like SineIn, but feels heavier.
         *
         * @since BlackBerry 10.0.0
         */
        static const StockCurve CubicIn;
        
        /*! 
         * @brief Starts very slowly and ends abruptly.
         *
         * @image html easing_ExponentialIn.png
         *
         * This stock curve has a "exponential" interpolation function and ease In velocity type. Very similar to QuarticIn.
         *
         * @since BlackBerry 10.0.0
         */
        static const StockCurve ExponentialIn;
        
        /*!
         * @brief  Starts very slowly and ends abruptly. 
         *
         * @image html easing_QuarticIn.png
         *
         * This stock curve has a quartic interpolation function and ease In velocity type. Feels heavier than CubicOut.
         *
         * @since BlackBerry 10.0.0
         */
        static const StockCurve QuarticIn;
        
        /*! 
         * @brief Starts very slowly and ends abruptly.
         *
         * @image html easing_QuinticIn.png
         *
         * This stock curve has a quintic interpolation function and ease in velocity type.
         *
         * @since BlackBerry 10.0.0
         */
        static const StockCurve QuinticIn;   
        
        /*!
         * @brief Has a glacial slowness to the start and an explosive end. 
         *
         * @image html easing_CircularIn.png
         *
         * This stock curve has a circular interpolation function and ease in velocity type.
         *
         * @since BlackBerry 10.0.0
         */
        static const StockCurve CircularIn;  
        
        /*!
         * @brief Starts in the opposite direction, and then animates quickly to the end.
         * 
         * @image html easing_BackIn.png
         *
         * This stock curve has a back interpolation function and ease in velocity type. 
         * This animation is similar to a jumping effect.
         * If you want to jump high, you first have to crouch. This move lets the viewer anticipate fast movements.
         * It's great for cartoonish effefcts things that need to move very quickly. Without the crouch,
         * the user might miss a rapid jump entirely and the character may seem to disappear without reason or direction.
         *
         * @since BlackBerry 10.0.0
         */
        static const StockCurve BackIn;
        
        /*! 
         * @brief Starts very slowly with an elastic effect at the end.
         *
         * @image html easing_Elastic1In.png
         *
         * This stock curve has a single elastic bounce interpolation function and ease in velocity type.
         *
         * @since BlackBerry 10.0.0
         */
        static const StockCurve ElasticIn;
        /*! 
         * @brief Like ElasticIn, but with an evenmore springy effect.
         *
         * @image html easing_Elastic2In.png
         *
         * This stock curve has a double elastic bounce interpolation function and ease in velocity type.
         *
         * @since BlackBerry 10.0.0
         */
        static const StockCurve DoubleElasticIn;
        /*! 
         * @brief Eases in and bounces.
         *
         * @image html easing_Bounce1In.png
         *
         * This stock curve has a single bounce interpolation function and ease in velocity type.
         *
         * @since BlackBerry 10.0.0
         */
        static const StockCurve BounceIn;
        
        /*!
         * @brief Eases in and bounces rapidly.
         *
         * @image html easing_Bounce2In.png
         *
         * This stock curve has a double bounce interpolation function and ease in velocity type.
         *
         * @since BlackBerry 10.0.0
         */
        static const StockCurve DoubleBounceIn;


        /*! @cond PRIVATE */
        StockCurve();
        StockCurve(const StockCurve& orig);
        StockCurve& operator=(const StockCurve& other);
        virtual bool operator==(const EasingCurve &other) const;
        virtual bool operator!=(const EasingCurve &other) const;
        /*! @endcond */

        /*!
         * @brief A destructor for this class
         *
         * @since BlackBerry 10.0.0
         */
        virtual ~StockCurve();

    protected:
        /*! @cond PRIVATE */
        StockCurve(StockCurveDataPrivate* d);
        /*! @endcond */
    };



}
}

Q_DECLARE_METATYPE(bb::cascades::StockCurve)

#endif	/* cascades_stockcurve_h */
