//Copyright (C) 2014 BlackBerry Limited. All rights reserved.

#ifndef cascades_saturateeffect_h
#define cascades_saturateeffect_h


#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/effects/abstracteffect.h>

namespace bb {
    namespace cascades {
        class VisualNode;
        class SaturateEffectPrivate;

        /*!
          * @brief A saturate/desaturate effect that can increase or decrease
          * the color intensity of images and other visual nodes.
          *
          * Here are some examples of how icons appear using different saturation levels.
          * 
          * @image html saturation.png Sets of icons that use different saturation values.
          *
          * And here's an example of how to attach the effect to a control:
          *
          * @snippet tad/examples/controls/effects/assets/effects.qml saturate_effect
          *
          * @xmlonly
          * <apigrouping group="User interface/Effects"/>
          * @endxmlonly
          *
          * @since BlackBerry 10.3.1
          */
        class BBCASCADES_EXPORT SaturateEffect : public AbstractEffect {
        private:
            Q_OBJECT

        public:
            /*!
             * @brief Constructs a @c %SaturateEffect object.
             *
             * When you add a saturate effect to a control using @c VisualNode::addEffect(),
             * the control assumes ownership of this instance unless it was previously added to a
             * different control, in which case ownership stays with the original control.
             *
             * Specifying the parent node is optional.
             *
             * @param parent The parent visual node. This parameter is optional and defaults to @c 0
             *  if not specified. When the effect is assigned to a node, this value is updated.
             *
             * @since BlackBerry 10.3.1
             */
            SaturateEffect(VisualNode *parent = 0);
            virtual ~SaturateEffect();

             /*!
              * @brief Specifies the saturation level of the @c %SaturateEffect.
              *
              * The range of valid values is from -100.0 (full desaturation) to 100.0 (full saturation).
              * If set to @c 0.0 (the default), this property has no effect.
              *
              * @since BlackBerry 10.3.1
              */
            Q_PROPERTY(float saturation READ saturation WRITE setSaturation RESET resetSaturation
                       NOTIFY saturationChanged FINAL);

             /*!
              * @brief Gets the saturation level of the @c %SaturateEffect.
              *
              * The range of valid values is from -100.0 (full desaturation) to 100.0 (full saturation).
              * If set to @c 0.0 (the default), this property has no effect.
              *
              * @since BlackBerry 10.3.1
              */
            float saturation() const;

            /*!
              * @brief Sets the saturation for the @c %SaturateEffect.
              *
              * @param saturation The @c saturation to use on this @c %SaturateEffect.
              *
              * @since BlackBerry 10.3.1
              */
            Q_SLOT void setSaturation(float saturation);

            /*!
              * @brief Resets the saturation for this @c %SaturateEffect to 0.0
              *
              * @since BlackBerry 10.3.1
              */
            Q_SLOT void resetSaturation();

        Q_SIGNALS:
            /*!
             * @brief Emitted when the saturation for this @c %SaturateEffect changes.
             *
             * @param saturation The new saturation for the @c %SaturateEffect
             *
             * @since BlackBerry 10.3.1
             */
            void saturationChanged(float saturation);

            /*! @cond PRIVATE */
        private:
            Q_DECLARE_PRIVATE(SaturateEffect)
            Q_DISABLE_COPY(SaturateEffect)
            /*! @endcond */

        public:
            /*! @cond PRIVATE */
            typedef SaturateEffect ThisClass;
            typedef AbstractEffect BaseClass;
            /*! @endcond */

            /*!
              * @brief A builder template for constructing a @c %SaturateEffect.
              *
              * To retrieve the builder, call @c SaturateEffect::create().
              */
            template <typename BuilderType, typename BuiltType>
            class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType> {
            protected:
                TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node) {
                }

            public:
                /*!
                 * @brief Sets the saturation to display on the @c %SaturateEffect.
                 *
                 * @param saturation The @c saturation to use on this @c %SaturateEffect.
                 *
                 * @since BlackBerry 10.3.1
                 */
                BuilderType& saturation(float saturation) {
                    this->instance().setSaturation(saturation);
                    return this->builder();
                }
            };

            /*!
              * @brief A builder for constructing a @c %SaturateEffect.
              *
              * To retrieve the builder, call @c SaturateEffect::create().
              */
            class Builder : public TBuilder<Builder, SaturateEffect>
            {
            public:
                Builder() : TBuilder<Builder, SaturateEffect>(new SaturateEffect()) {
                }
            };

            /*!
              * @brief Creates and returns a builder for constructing a @c %SaturateEffect.
              *
              * Using the builder to create a @c %SaturateEffect object:
              * @code
              * SaturateEffect* pSaturateEffect = SaturateEffect::create()
              * @endcode
              *
              * @return A builder used for constructing an @c %SaturateEffect object.
              *
              * @since BlackBerry 10.3.1
              */
            static Builder create() {
                return Builder();
            }
        }; // class SaturateEffect
    } // namespace bb::cascades
} //namespace bb
QML_DECLARE_TYPE(bb::cascades::SaturateEffect)

#endif  // cascades_saturateeffect_h