//Copyright (C) 2014 BlackBerry Limited. All rights reserved.

#ifndef cascades_brightnesseffect_h
#define cascades_brightnesseffect_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/effects/abstracteffect.h>

namespace bb {
    namespace cascades {
        class VisualNode;
        class BrightnessEffectPrivate;

        /*!
          * @brief A brightness effect that can brighten or darken images
          * and other controls.
          *
          * Here are some examples of how icons appear using different levels of brightness.
          *
          * @image html brightness.png Sets of icons that use different brightness values.
          *
          * And here's an example of how to attach the effect to a control: 
          *
          * @snippet tad/examples/controls/effects/assets/effects.qml brightness_effect
          *
          * @xmlonly
          * <apigrouping group="User interface/Effects"/>
          * @endxmlonly
          *
          * @since BlackBerry 10.3.1
          */
        class BBCASCADES_EXPORT BrightnessEffect : public AbstractEffect {
        private:
            Q_OBJECT

        public:
            /*!
             * @brief Constructs a @c %BrightnessEffect object.
             *
             * When you add a brightness effect to a control using @c VisualNode::addEffect(),
             * the control assumes ownership of this instance unless it was previously added to a
             * different control, in which case ownership stays with the original control.
             *
             * @param parent The parent visual node. This parameter is optional and defaults to @c 0
             *  if not specified. When the effect is assigned to a node, this value is updated.
             */
            BrightnessEffect(VisualNode *parent = 0);
            virtual ~BrightnessEffect();

            /*!
             * @brief The brightness of the @c %BrightnessEffect.
             *
             * The range of valid values is from -150.0 (all pixels darkened to be black or transparent) 
             * to 150.0 (all pixels brightened to be white or transparent). If set to @c 0.0, this property has no effect.
             * 
             * The default value is @c 0.0
             *
             * @since BlackBerry 10.3.1
             */
            Q_PROPERTY(float brightness READ brightness WRITE setBrightness RESET resetBrightness NOTIFY brightnessChanged FINAL);

             /*!
              * @brief Gets the brightness for the @c %BrightnessEffect.
              *
              * @return The @c brightness of the @c %BrightnessEffect. Valid values range from -150.0
              * (all pixels darkened to be black or transparent) to 150.0 (all pixels brightened to be white or transparent).
              *
              * @since BlackBerry 10.3.1
              */
            float brightness() const;

            /*!
              * @brief Sets the brightness level for the @c %BrightnessEffect.
              *
              * @param brightness The @c brightness to use on this @c %BrightnessEffect.
              *
              * @since BlackBerry 10.3.1
              */
            Q_SLOT void setBrightness(float brightness);

            /*!
              * @brief Resets the brightness for this @c %BrightnessEffect to 0.0.
              *
              * @since BlackBerry 10.3.1
              */
            Q_SLOT void resetBrightness();

        Q_SIGNALS:
            /*!
             * @brief Emitted when the brightness level changes.
             *
             * @param brightness The new brightness level for the @c %BrightnessEffect.
             *
             * @since BlackBerry 10.3.1
             */
            void brightnessChanged(float brightness);

            /*! @cond PRIVATE */
        private:
            Q_DECLARE_PRIVATE(BrightnessEffect)
            Q_DISABLE_COPY(BrightnessEffect)
            /*! @endcond */

        public:
            /*! @cond PRIVATE */
            typedef BrightnessEffect ThisClass;
            typedef AbstractEffect BaseClass;
            /*! @endcond */

            /*!
              * @brief A builder template for constructing an @c %BrightnessEffect.
              *
              * To retrieve the builder, call @c BrightnessEffect::create().
              */
            template <typename BuilderType, typename BuiltType>
            class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType> {
            protected:
                TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node) {
                }

            public:
                /*!
                 * @brief Sets the brightness to display on this BrightnessEffect.
                 *
                 * @param brightness The @c brightness to use on this BrightnessEffect.
                 *
                 * @since BlackBerry 10.3.1
                 */
                BuilderType& brightness(float brightness) {
                    this->instance().setBrightness(brightness);
                    return this->builder();
                }
            };

            /*!
              * @brief A builder for constructing a @c %BrightnessEffect.
              *
              * To retrieve the builder, call @c BrightnessEffect::create().
              */
            class Builder : public TBuilder<Builder, BrightnessEffect>
            {
            public:
                Builder() : TBuilder<Builder, BrightnessEffect>(new BrightnessEffect()) {
                }
            };

            /*!
              * @brief Creates and returns a builder for constructing an @c %BrightnessEffect.
              *
              * Using the builder to create an @c %BrightnessEffect object:
              * @code
              * BrightnessEffect* pBrightnessEffect = BrightnessEffect::create()
              * @endcode
              *
              * @return A builder used for constructing an @c %BrightnessEffect object.
              */
            static Builder create() {
              return Builder();
            }
        }; // class BrightnessEffect
    } // namespace bb::cascades
} //namespace bb
QML_DECLARE_TYPE(bb::cascades::BrightnessEffect)
#endif  // cascades_brightnesseffect_h