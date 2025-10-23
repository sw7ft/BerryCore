//Copyright (C) 2014 BlackBerry Limited. All rights reserved.

#ifndef cascades_abstracteffect_h
#define cascades_abstracteffect_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/core/uiobject.h>

namespace bb {
    namespace cascades {
        class VisualNode;
        class AbstractEffectPrivate;

        /*!
          * @brief Abstract base class inherited by all effects.
          *
          * Effects can be attached to a node through the @c VisualNode::effects property.
          *
          * See @c BrightnessEffect, @c FocusHighlightEffect, and @c SaturateEffect.
          *
          * @xmlonly
          * <apigrouping group="User interface/Effects"/>
          * @endxmlonly
          */
        class BBCASCADES_EXPORT AbstractEffect : public UIObject {
        private:
            Q_OBJECT
            /*!
              * @brief Whether the effect is enabled out or not.
              *
              * If the enabled property is set to @c false, the effect is not rendered.
              * The default enabled value is @c true.
              *
              * @since BlackBerry 10.3.1
              */
            Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled RESET resetEnabled NOTIFY enabledChanged FINAL)

        public:
            /*! @brief Destructor. */
            virtual ~AbstractEffect();

            /*!
              * @brief Specifies whether the effect is enabled or not.
              *
              * @copydetails AbstractEffect::enabled
              *
              * @return @c true if the effect is enabled, @c false otherwise.
              *
              * @since BlackBerry 10.3.1
              */
            bool isEnabled() const;

            /*!
              * @brief Sets whether the effect should be enabled or not.
              *
              * @copydetails AbstractEffect::enabled
              *
              * @param enabled @c true to make the effect enabled, @c false otherwise.
              *
              * @since BlackBerry 10.3.1
              */
            Q_SLOT void setEnabled(bool enabled);

            /*!
              * @brief Resets the effect to be enabled.
              *
              * @copydetails AbstractEffect::enabled
              *
              * @since BlackBerry 10.3.1
              */
            Q_SLOT void resetEnabled();

        Q_SIGNALS:
            /*!
              * @brief Emitted when the enabled property of the effect is changed.
              * 
              * @copydetails AbstractEffect::enabled
              *
              * @param enabled The new enabled value for the effect.
              *
              * @since BlackBerry 10.3.1
              */
            void enabledChanged(bool enabled);

        protected:
            /*! @cond PRIVATE */
            AbstractEffect(AbstractEffectPrivate &_d_ptr, VisualNode *parent = 0);

        private:
            Q_DECLARE_PRIVATE(AbstractEffect)
            Q_DISABLE_COPY(AbstractEffect)
            /*! @endcond */

        // BUILDER ---------------------------------
        public:
            /*! @cond PRIVATE */
            typedef AbstractEffect ThisClass;  // The class in which scope we're currently inside
            typedef UIObject BaseClass; // References the class which ThisClass derives from
            /*! @endcond */

            /*!
             * @brief A builder template for constructing an AbstractEffect.
             *
             * @since BlackBerry 10.3.1
             */
            template <typename BuilderType, typename BuiltType>
            class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType> {
            protected:
                TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node) {
                }

            public:
                BuilderType& enabled(bool enabled) {
                    this->instance().setEnabled(enabled);
                    return this->builder();
                }
            };
        }; // class AbstractEffect
    } // namespace bb::cascades
}
QML_DECLARE_TYPE(bb::cascades::AbstractEffect)

#endif // cascades_abstracteffect_h