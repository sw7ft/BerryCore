/* Copyright (C) 2012-2014 Research In Motion Limited.  */
#ifndef BB_CASCADES_TEXTINPUTFLAG_H
#define BB_CASCADES_TEXTINPUTFLAG_H

#include <bb/cascades/bbcascades_global.h>
#include <QtDeclarative/QtDeclarative>

namespace bb {
    namespace cascades {

        /*!
        * @brief Flags for turning on and off different text features (for example, spell check).
        *
        * @xmlonly
        * <apigrouping group="User interface/Text"/>
        * @endxmlonly
         *
         * @since BlackBerry 10.0.0
        */
        class TextInputFlag
        {
            Q_GADGET
                Q_ENUMS(Type)
                Q_FLAGS(Types)

        public:
            /*!
            * @brief Text feature flags used to turn on and turn off text features.
            *
            * If both the on and off flag for a certain feature is set to @c 1 at
            * the same time, the behavior is undefined. 
            * If both flags are set to @c 0, the default behavior for the given control and input mode
            * are used.
            *
            * @xmlonly
            * <qml>
            * <enum flagsType="bb::cascades::TextInputFlag::Types"/>
            * </qml>
            * @endxmlonly
             *
             * @since BlackBerry 10.0.0
            */
            enum Type {
                /*! @brief Default settings for all features will be used.
                 *
                 * @since BlackBerry 10.0.0
                 */
                Default = 0x00,
                /*! @brief Turns on spell checking.
                 *
                 * @since BlackBerry 10.0.0
                 */
                SpellCheck = (1<<0),
                /*! @brief Turns off spell checking.
                 *
                 * @since BlackBerry 10.0.0
                 */
                SpellCheckOff = (1<<1),
                /*! @brief Turns on word predictions.
                 *
                 * @since BlackBerry 10.0.0
                 */
                Prediction = (1<<2),
                /*! @brief Turns off word predictions.
                 *
                 * @since BlackBerry 10.0.0
                 */
                PredictionOff = (1<<3),
                /*! @brief Turns on auto correction.
                 *
                 * @since BlackBerry 10.0.0
                 */
                AutoCorrection = (1<<4),
                /*! @brief Turns off auto correction.
                 *
                 * @since BlackBerry 10.0.0
                 */
                AutoCorrectionOff = (1<<5),
                /*! @brief Turns on auto capitalization.
                 *
                 * @since BlackBerry 10.0.0
                 */
                AutoCapitalization = (1<<6),
                /*! @brief Turns off auto capitaliztion.
                 *
                 * @since BlackBerry 10.0.0
                 */
                AutoCapitalizationOff = (1<<7),
                /*! @brief Turns on auto period.
                 *
                 * @since BlackBerry 10.0.0
                 */
                AutoPeriod = (1<<8),
                /*! @brief Turns off auto period.
                 *
                 * @since BlackBerry 10.0.0
                 */
                AutoPeriodOff = (1<<9),
                /*! @brief Turns on word substitution.
                 *
                 * @since BlackBerry 10.0.0
                 */
                WordSubstitution = (1<<10),
                /*! @brief Turns off word substitution.
                 *
                 * @since BlackBerry 10.0.0
                 */
                WordSubstitutionOff = (1<<11),
                /*! @brief Turns on virtual keyboard.
                 *
                 * @since BlackBerry 10.0.0
                 */
                VirtualKeyboard = (1<<12),
                /*! @brief Turns off virtual keyboard.
                 *
                 * @since BlackBerry 10.0.0
                 */
                VirtualKeyboardOff = (1<<13),
                /*! @brief Forces the keyboard to Latin-1. This affects the VKB layout and 
                 *         language predictions but does not filter non keyboard input such
                 *         as paste or setting the text programmatically.
                 *
                 * @since BlackBerry 10.2.0
                 */
                LatinOnly = (1<<14),
                /*! @brief Turns off force Latin-1 keyboard.
                 *
                 * @since BlackBerry 10.2.0
                 */
                LatinOnlyOff= (1<<15),
                /*! @brief Turns on keyboard usage hints to help users learn how to use
                 * the features of the keyboard.
                 *
                 * @since BlackBerry 10.3.0
                 */
                KeyboardUsageHints = (1<<16),
                /*! @brief Suppresses keyboard usage hints.
                 *
                 * This suppresses instructions to the end user on how to use the keyboard.
                 * For example, instructions on how to accept word predictions won't show up when
                 * this flag is set. Note that these kind of instructions will automatically
                 * be suppressed as the user gains experience with using the keyboard, so you
                 * rarely need to use this flag.
                 *
                 * @since BlackBerry 10.3.0
                 */
                KeyboardUsageHintsOff = (1<<17)
            };

            /*!
            * @brief Bitfield containing information about what features are enabled or disabled.
            *v
            * Overrides the default beahior for the control.
            * @see bb::cascades::TextInputFlag::Type
            *
            * @since BlackBerry 10.0.0
            */
            Q_DECLARE_FLAGS(Types, Type)

        private:
            /*! @cond PRIVATE */
            TextInputFlag();
            virtual ~TextInputFlag();
            /*! @endcond */
        };

    }
}

/*! @cond PRIVATE */
QML_DECLARE_TYPE(bb::cascades::TextInputFlag::Types)
Q_DECLARE_OPERATORS_FOR_FLAGS(bb::cascades::TextInputFlag::Types)
/*! @endcond */


#endif // BB_CASCADES_TEXTINPUTFLAG_H
