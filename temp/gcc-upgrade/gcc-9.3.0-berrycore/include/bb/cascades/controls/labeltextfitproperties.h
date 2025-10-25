/* Copyright (C) 2013 Research In Motion Limited.  */
#ifndef BB_CASCADES_LABELTEXTFITPROPERTIES_H
#define BB_CASCADES_LABELTEXTFITPROPERTIES_H

#include <bb/cascades/bbcascades_global.h>
#include <QtDeclarative/QtDeclarative>
#include <bb/cascades/controls/textfitproperties.h>
#include <bb/cascades/resources/labeltextfitmode.h>

namespace bb {
    namespace cascades {
        class LabelTextFitPropertiesPrivate;

        /*!
         * @brief Represents the auto fit properties of the text in a @c Label.
         *
         * The @c LabelTextFitProperties configure how the text in a @c Label adapts
         * its size to the @c Label size.
         *
         * @xmlonly
         * <apigrouping group="User interface/Text"/>
         * @endxmlonly
         *
         * @since BlackBerry 10.2.0
         */
        class BBCASCADES_EXPORT LabelTextFitProperties : public TextFitProperties
        {
            Q_OBJECT

            /*!
             * @brief The text fit mode.
             *
             * See @c LabelTextFitMode
             *
             * The default value is @c Default.
             *
             * The following example creates a @c %Label with a @c LabelTextFitMode of @c FitToBounds:
             * @code
             *
             * Label {
             *     textFit {
             *         mode: LabelTextFitMode.FitToBounds
             *     }
             * }
             * @endcode
             *
             * @since BlackBerry 10.2.0
             */
            Q_PROPERTY(bb::cascades::LabelTextFitMode::Type mode
                       READ mode
                       WRITE setMode
                       RESET resetMode
                       NOTIFY modeChanged
                       FINAL)

        public:
            /*!
             * @brief Returns the text fit mode.
             *
             * @return The text fit mode.
             *
             * @since BlackBerry 10.2.0
             */
            bb::cascades::LabelTextFitMode::Type mode() const;

            /*!
             * @brief Sets the text fit mode.
             *
             * Use @c resetMode() to reset the property to the default value.
             *
             * @param mode The new @c mode.
             *
             * @since BlackBerry 10.2.0
             */
            Q_SLOT void setMode(bb::cascades::LabelTextFitMode::Type mode);

            /*!
             * @brief Resets text fit mode to its default value.
             *
             * The default value is @c Default, which lets the framework decide the text fit mode.
             *
             * @since BlackBerry 10.2.0
             */
            Q_SLOT void resetMode();

        Q_SIGNALS:
            /*!
             * @brief Emitted when the text fit mode changes.
             *
             * @note Due to a workaround for a Qt Core issue with accessing enums from QML,
             * the argument of this signal doesn't follow the usual naming convention for signals.
             * Typically, signal arguments are named to match the associated property's name.
             * In this case, you must use the object's property to access the current
             * property value instead of the signal argument to avoid runtime errors
             * (i.e. use @c mode instead of @c newMode).
             *
             * @param newMode The new text fit mode.
             *
             * @since BlackBerry 10.2.0
             */
            void modeChanged(bb::cascades::LabelTextFitMode::Type newMode);



        protected:
            /*! @cond PRIVATE */
            LabelTextFitProperties(BaseObject *parent = 0);
            virtual ~LabelTextFitProperties();
            /*! @endcond */

        private:
            /*! @cond PRIVATE */
            Q_DECLARE_PRIVATE(LabelTextFitProperties)
            Q_DISABLE_COPY(LabelTextFitProperties)
            /*! @endcond */
        };
    }
}

/*! @cond PRIVATE */
QML_DECLARE_TYPE(bb::cascades::LabelTextFitProperties)
/*! @endcond */

#endif // BB_CASCADES_LABELTEXTFITPROPERTIES_H
