/* Copyright (C) 2013 Research In Motion Limited.  */
#ifndef BB_CASCADES_TEXTFITPROPERTIES_H
#define BB_CASCADES_TEXTFITPROPERTIES_H

#include <bb/cascades/bbcascades_global.h>
#include <QtDeclarative/QtDeclarative>
#include <bb/cascades/UIObject>

namespace bb {
    namespace cascades {
        class TextFitPropertiesPrivate;

        /*!
         * @brief Represents the base auto fit properties of a text control
         *
         * The @c TextFitProperties configures how the control content adapts
         * its size to the control size.
         *
         * @xmlonly
         * <apigrouping group="User interface/Text"/>
         * @endxmlonly
         *
         * @since BlackBerry 10.2.0
         */
        class BBCASCADES_EXPORT TextFitProperties : public BaseObject
        {
            Q_OBJECT

            /*!
             * @brief The minimum font size value.
             *
             * This indicates the minimum font size in post script units.
             *
             * The default value is @c -1.0 which means that the system default
             * value will be used instead.
             *
             * If both @c minFontSizeValue and @c maxFontSizeValue are specified then @c maxFontSizeValue
             * must be greater than or equal to @c minFontSizeValue.
             *
             * @note For each control the default minimal font size value is defined
             * at system level. The system value takes precedence if @c minFontSizeValue
             * is less than system one.
             *
             * @since BlackBerry 10.2.0
             */
            Q_PROPERTY(float minFontSizeValue
                       READ minFontSizeValue
                       WRITE setMinFontSizeValue
                       RESET resetMinFontSizeValue
                       NOTIFY minFontSizeValueChanged
                       FINAL)

            /*!
             * @brief The maximum font size value.
             *
             * This indicates the maximum font size in post script units.
             *
             * The default value is @c -1.0 which means that the system default
             * value will be used instead.
             *
             * If both @c minFontSizeValue and @c maxFontSizeValue are specified then @c maxFontSizeValue
             * must be greater than or equal to @c minFontSizeValue.
             *
             * @note For each control the default maximum font size value is defined
             * at system level. The system value takes precedence if @c maxFontSizeValue
             * is bigger than system one.
             *
             * @since BlackBerry 10.2.0
             */
            Q_PROPERTY(float maxFontSizeValue
                       READ maxFontSizeValue
                       WRITE setMaxFontSizeValue
                       RESET resetMaxFontSizeValue
                       NOTIFY maxFontSizeValueChanged
                       FINAL)

        public:
            /*!
             * @brief Returns the minimum font size value.
             *
             * @return The minimum font size value.
             *
             * @since BlackBerry 10.2.0
             */
            float minFontSizeValue() const;

            /*!
             * @brief Sets the minimum font size value.
             *
             * The value must be @c -1.0, @c 0.0f or positive otherwise it will be ignored.
             * Use @c resetMinFontSizeValue() to reset the property to the default value.
             *
             * @param minFontSizeValue The new @c minFontSizeValue value
             *
             * @since BlackBerry 10.2.0
             */
            Q_SLOT void setMinFontSizeValue(float minFontSizeValue);

            /*!
             * @brief Resets @c minFontSizeValue to its default value.
             *
             * The default value is @c -1.0.
             *
             * @since BlackBerry 10.2.0
             */
            Q_SLOT void resetMinFontSizeValue();

            /*!
             * @brief Returns the maximum font size value.
             *
             * @return The maximum font size value.
             *
             * @since BlackBerry 10.2.0
             */
            float maxFontSizeValue() const;

            /*!
             * @brief Sets the maximum font size value.
             *
             * The value must be @c -1.0, @c 0.0f or positive otherwise it will be ignored.
             * Use resetMaxFontSizeValue() to reset the property to the default value.
             *
             * @param maxFontSizeValue The new @c maxFontSizeValue value
             *
             * @since BlackBerry 10.2.0
             */
            Q_SLOT void setMaxFontSizeValue(float maxFontSizeValue);

            /*!
             * @brief Resets @c maxFontSizeValue to its default value.
             *
             * The default value is @c -1.0.
             *
             * @since BlackBerry 10.2.0
             */
            Q_SLOT void resetMaxFontSizeValue();

        Q_SIGNALS:
            /*!
             * @brief Emitted when the @c minFontSizeValue is changed.
             *
             * @param minFontSizeValue The new @c minFontSizeValue.
             *
             * @since BlackBerry 10.2.0
             */
            void minFontSizeValueChanged(float minFontSizeValue);

            /*!
             * @brief Emitted when the @c maxFontSizeValue is changed.
             *
             * @param maxFontSizeValue The new @c maxFontSizeValue.
             *
             * @since BlackBerry 10.2.0
             */
            void maxFontSizeValueChanged(float maxFontSizeValue);

        protected:
            /*! @cond PRIVATE */
            TextFitProperties(TextFitPropertiesPrivate& _d_ptr, BaseObject *parent = 0);
            virtual ~TextFitProperties();
            /*! @endcond */

        private:
            /*! @cond PRIVATE */
            Q_DECLARE_PRIVATE(TextFitProperties)
            Q_DISABLE_COPY(TextFitProperties)
            /*! @endcond */
        };
    }
}

/*! @cond PRIVATE */
QML_DECLARE_TYPE(bb::cascades::TextFitProperties)
/*! @endcond */

#endif // BB_CASCADES_TEXTFITPROPERTIES_H
