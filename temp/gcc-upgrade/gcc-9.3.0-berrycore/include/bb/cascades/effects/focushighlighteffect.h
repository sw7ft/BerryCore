//Copyright (C) 2014 BlackBerry Limited. All rights reserved.
#ifndef cascades_focushighlighteffect_h
#define cascades_focushighlighteffect_h

#include <bb/cascades/resources/color.h>

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/effects/abstracteffect.h>
#include <bb/cascades/effects/focushighlighteffectstyle.h>

namespace bb {
    namespace cascades {
        class VisualNode;
        class FocusHighlightEffectPrivate;
        class ColorPaint;

        /*!
          * @brief A focus highlight effect that can be set on images and other controls.
          *
          * This effect represents the "focus highlight" effect that's used when a user focuses on a 
          * control by using the trackpad.
          *
          * Here are some examples of how icons appear using different colors and styles of highlights:
          *
          * @image html focushighlight.png Sets of icons that use different focus highlight effects.
          * 
          * And here's an example of how to attach the effect to a control:
          *
          * @snippet tad/examples/controls/effects/assets/effects.qml focushighlight_effect
          *
          * @xmlonly
          * <apigrouping group="User interface/Effects"/>
          * @endxmlonly
          *
          * @since BlackBerry 10.3.1
          */
        class BBCASCADES_EXPORT FocusHighlightEffect : public AbstractEffect {
        private:
            Q_OBJECT

        public:
            /*!
             * @brief Constructs an @c %FocusHighlightEffect object.
             *
             * When you add a focus highlight effect to a control using @c VisualNode::addEffect(),
             * the control assumes ownership of this instance unless it was previously added to a
             * different control, in which case ownership stays with the original control.
             *
             * @param parent The parent visual node. This parameter is optional and defaults to @c 0
             *  if not specified. When the effect is assigned to a node, this value is updated.
             *
             * @since BlackBerry 10.3.1
             */
            FocusHighlightEffect(VisualNode *parent = 0);
            virtual ~FocusHighlightEffect();

            /*!
             * @brief A color to use as the base for this @c %FocusHighlightEffect.
             *
             * The default value is an invalid @c QVariant.
             *
             * @xmlonly
             * <qml>
             * <variant type="bb::cascades::Color"/>
             * <variant type="bb::cascades::ColorPaint"/>
             * </qml>
             * @endxmlonly
             *
             * @since BlackBerry 10.3.1
             */
            Q_PROPERTY(QVariant baseColor READ baseColor WRITE setBaseColor RESET resetBaseColor
                       NOTIFY baseColorChanged FINAL);

            /*!
              * @brief Specifies the style of the @c %FocusHighlightEffect (flat or gradient). 
              *
              * You should note that not all @c VisualNode types support all styles. See @c FocusHighlightEffectStyle
              * for more information. The default value is @c FocusHighlightEffectStyle::Flat.
              *
              * @since BlackBerry 10.3.1
              */
            Q_PROPERTY(bb::cascades::FocusHighlightEffectStyle::Type style READ style WRITE setStyle
                       RESET resetStyle NOTIFY styleChanged FINAL)

            /*!
             * @brief Returns the base color for the @c %FocusHighlightEffect.
             *
             * The returned @c QVariant will either be invalid or contain values of type @c Color or @c ColorPaint.
             * An invalid @c %QVariant signifies that a color has not been set.
             *
             * Use @c QVariant::canConvert<Type T>() to find the type, and
             * then use @c QVariant::value<Type T>() to get the value.
             *
             * @return The @c %Color or @c %ColorPaint that is displayed on the @c %FocusHighlightEffect, or an invalid @c %QVariant.
             *
             * @since BlackBerry 10.3.1
             */
            QVariant baseColor() const;

            /*!
             * @brief Sets the base color for the @c %FocusHighlightEffect.
             *
             * @param color The @c Color or @c ColorPaint to display on this @c %FocusHighlightEffect.
             *
             * @since BlackBerry 10.3.1
             */
            Q_SLOT void setBaseColor(const ColorPaint& color);

            /*!
             * @brief Resets the color for this @c %FocusHighlightEffect to an invalid @c QVariant.
             *
             * @since BlackBerry 10.3.1
             */
            Q_SLOT void resetBaseColor();

            /*!
             * @brief Sets the style of the @c %FocusHighlightEffect.
             *
             * The styleChanged() signal will be emitted if operation was successful.
             *
             * @param style The style of the @c %FocusHighlightEffect.
             *
             * @since BlackBerry 10.3.1
             */
            Q_SLOT void setStyle(bb::cascades::FocusHighlightEffectStyle::Type style);

            /*!
             * @brief Returns the current style of the @c %FocusHighlightEffect.
             *
             * The default style is FocusHighlightEffectStyle::Flat.
             *
             * @return The style of the FocusHighlightEffect.
             *
             * @since BlackBerry 10.3.1
             */
            bb::cascades::FocusHighlightEffectStyle::Type style() const;

            /*!
             * @brief Resets the current style to the default style FocusHighlightEffectStyle::Flat.
             *
             * @since BlackBerry 10.3.1
             */
            Q_SLOT void resetStyle();

        Q_SIGNALS:
            /*!
             * @brief Emitted when the color for this @c %FocusHighlightEffect changes.
             *
             * @param baseColor The new base color for this @c %FocusHighlightEffect
             *
             * @since BlackBerry 10.3.1
             */
            void baseColorChanged(const bb::cascades::ColorPaint& baseColor);

            /*! @cond PRIVATE */
            /*!
             * @brief Emitted when the color changes.
             *
             * @since BlackBerry 10.3.1
             */
            void baseColorChanged(const QVariant& color);
            /*! \endcond */

            /*!
             * @brief Emitted when the style has changed.
             *
             * @param newStyle The new selected style of the @c %FocusHighlightEffect.
             *
             * @since BlackBerry 10.3.1
             */
            void styleChanged(bb::cascades::FocusHighlightEffectStyle::Type newStyle);

            /*! @cond PRIVATE */
        private:
            /*!
             * @brief Sets the color to display on this @c %FocusHighlightEffect.
             *
             * @param color The @c Color or @c ColorPaint to display on this @c %FocusHighlightEffect.
             *
             * @since BlackBerry 10.3.1
             */
            Q_SLOT void setBaseColor(const QVariant& color);

            Q_DECLARE_PRIVATE(FocusHighlightEffect)
            Q_DISABLE_COPY(FocusHighlightEffect)
            /*! @endcond */

        public:
            /*! @cond PRIVATE */
            typedef FocusHighlightEffect ThisClass;
            typedef AbstractEffect BaseClass;
            /*! @endcond */

            /*!
             * @brief A builder template for constructing an @c %FocusHighlightEffect.
             *
             * To retrieve the builder, call @c FocusHighlightEffect::create().
             */
            template <typename BuilderType, typename BuiltType>
            class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType> {
            protected:
                TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node) {
                }

            public:
                /*!
                 * @brief Sets the color for this @c %FocusHighlightEffect, identified by its value.
                 *
                 * @param baseColor The value of the color to set for this @c %FocusHighlightEffect.
                 */
                BuilderType& baseColor(const ColorPaint &baseColor) {
                    this->instance().setBaseColor(baseColor);
                    return this->builder();
                }

                /*!
                 * @brief Sets the style of the @c %FocusHighlightEffect.
                 *
                 * The styleChanged() signal will be emitted if operation was successful.
                 *
                 * @param style The style of the @c %FocusHighlightEffect.
                 *
                 * @since BlackBerry 10.3.1
                 */
                BuilderType& style(bb::cascades::FocusHighlightEffectStyle::Type style)
                {
                    this->instance().setStyle(style);
                    return this->builder();
                }
            };

            /*!
             * @brief A builder for constructing a @c %FocusHighlightEffect.
             *
             * To retrieve the builder, call @c FocusHighlightEffect::create().
             */
            class Builder : public TBuilder<Builder, FocusHighlightEffect>
            {
            public:
                Builder() : TBuilder<Builder, FocusHighlightEffect>(new FocusHighlightEffect()) {
                }
            };

            /*!
             * @brief Creates and returns a builder for constructing an @c %FocusHighlightEffect.
             *
             * Using the builder to create an @c %FocusHighlightEffect object:
             * @code
             * FocusHighlightEffect* pFocusHighlightEffect = FocusHighlightEffect::create()
             * @endcode
             *
             * @return A builder used for constructing an @c %FocusHighlightEffect object.
             */
            static Builder create() {
                return Builder();
            }
        }; // class FocusHighlightEffect
    } // namespace bb::cascades
} //namespace bb
QML_DECLARE_TYPE(bb::cascades::FocusHighlightEffect)
#endif  // cascades_focushighlighteffect_h
