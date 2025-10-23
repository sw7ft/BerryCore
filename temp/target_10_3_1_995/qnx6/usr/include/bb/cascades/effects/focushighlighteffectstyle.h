//Copyright (C) 2014 BlackBerry Limited. All rights reserved.

#ifndef cascades_focushighlighteffectstyle_h
#define cascades_focushighlighteffectstyle_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
    namespace cascades {

       /*!
        * @brief Represents the styles used for the @c FocusHighlightEffect.
        *
        * Use the @c %FocusHighlightEffectStyle::Type enum values to set a specific style for the @c %FocusHighlightEffect.
        * The default style is @c FocusHighlightEffectStyle::Flat, which is supported by all types of controls and can
        * be set on any type of @c VisualNode.
        * The @c LinearGradient type is currently only supported by the @c ImageView control.
        * If the @c Image provided to an @c ImageView is nine-sliced, the 
        * displayed linear gradient can appear inconsistent and might not look as desired.
        *
        * Here's an example of how to specify the @c %FocusHighlightEffectStyle, in QML.
        * @code
        * FocusHighlightEffect {
        *     style: FocusHighlightEffectStyle.Flat
        * }
        * @endcode
        *
        * Here's an example of setting the style in C++:
        * @code
        * FocusHighlightEffect* FocusHighlightEffect::create()
        *         .style(FocusHighlightEffectStyle::Flat);
        * @endcode
        *
        * It's also possible to change the style at any time during runtime:
        * @code
        * FocusHighlightEffect->setStyle(FocusHighlightEffectStyle::Flat);
        * @endcode
        *
        * @xmlonly
        * <apigrouping group="User interface/Core controls"/>
        * @endxmlonly
        *
        * @since BlackBerry 10.3.1
        */
        class BBCASCADES_EXPORT FocusHighlightEffectStyle {
            Q_GADGET
            Q_ENUMS (Type)
        public:

            /*!
            * @brief Different styles available for the @c FocusHighlightEffect:
            *
            * @since BlackBerry 10.3.1
            */
            enum Type {
                /*!
                 * @brief The default @c %FocusHighlightEffect.
                 *
                 * @since BlackBerry 10.3.1
                 */
                Default = 0,
                /*!
                 * @brief A flat @c %FocusHighlightEffect.
                 *
                 * @since BlackBerry 10.3.1
                 */
                Flat = 1,
                /*! 
                 * @brief A linear gradient @c %FocusHighlightEffect.
                 *
                 * @since BlackBerry 10.3.1
                 */
                LinearGradient = 2
            };
    
        private:
            /*! @cond PRIVATE */
            FocusHighlightEffectStyle();
            virtual ~FocusHighlightEffectStyle();
            /*! @endcond */
        }; //class FocusHighlightEffectStyle
    } // namespace cascades
} //namespace bb

#endif // cascades_focushighlighteffectstyle_h
