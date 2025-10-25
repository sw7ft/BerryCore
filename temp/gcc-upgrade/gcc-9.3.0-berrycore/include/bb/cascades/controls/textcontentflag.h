/* Copyright (C) 2012-2013 Research In Motion Limited.  */
#ifndef BB_CASCADES_TEXTCONTENTFLAG_H
#define BB_CASCADES_TEXTCONTENTFLAG_H

#include <bb/cascades/bbcascades_global.h>
#include <QtDeclarative/QtDeclarative>

namespace bb {
    namespace cascades {

        /*!
        * @brief Flags for enabling or disabling text features.
        *
        * @xmlonly
        * <apigrouping group="User interface/Text"/>
        * @endxmlonly
         *
         * @since BlackBerry 10.0.0
        */
        class BBCASCADES_EXPORT TextContentFlag
        {
            Q_GADGET
            Q_ENUMS(Type)
            Q_FLAGS(Types)

        public:
            /*!
            * @brief Text feature flags used to enable or disable text features.
            *
            * If both the on and off 
            * flags for a feature are set to @c 1 (enabled), the behavior is undefined. 
            * If both are set to @c 0 (disabled), the default behavior for the given control and input mode
            * are used.
            *
            * @xmlonly
            * <qml>
            * <enum flagsType="bb::cascades::TextContentFlag::Types"/>
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
                /*! @brief Turn on active text.
                 *
                 * @since BlackBerry 10.0.0
                 */
                ActiveText = (1<<0),
                /*! @brief Turn off active text.
                 *
                 * @since BlackBerry 10.0.0
                 */
                ActiveTextOff = (1<<1),
                /*! @brief Turn on emoticon substitution.
                 *
                 * @since BlackBerry 10.0.0
                 */
                Emoticons = (1<<2),
                /*! @brief Turn off emoticon substitution.
                 *
                 * @since BlackBerry 10.0.0
                 */
                EmoticonsOff = (1<<3)
            };

            /*!
            * @brief Bitfield containing information of what features are enabled or disabled.
            *
            * Overrides the default beahior for the control.
            * @see bb::cascades::TextContentFlag::Type
            *
            * @since BlackBerry 10.0.0
            */
            Q_DECLARE_FLAGS(Types, Type)

        private:
            /*! @cond PRIVATE */
            TextContentFlag();
            virtual ~TextContentFlag();
            /*! @endcond */
        };

    }
}

/*! @cond PRIVATE */
Q_DECLARE_OPERATORS_FOR_FLAGS(bb::cascades::TextContentFlag::Types)
QML_DECLARE_TYPE(bb::cascades::TextContentFlag::Types)
/*! @endcond */

#endif // BB_CASCADES_TEXTCONTENTFLAG_H
