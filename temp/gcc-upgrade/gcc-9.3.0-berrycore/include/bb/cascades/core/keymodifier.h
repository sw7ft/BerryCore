/* Copyright (C) 2012-2013 Research In Motion Limited.  */
#ifndef bb_cascades_keymodifier_h
#define bb_cascades_keymodifier_h

#include <bb/cascades/bbcascades_global.h>
#include <QtDeclarative/QtDeclarative>

namespace bb {
    namespace cascades {

        /*!
        * @brief Flags for selecting different key modifiers, such as Shift, Crtl, Alt.
        *
        * @xmlonly
        *     <apigrouping group="User interface/Events"/>
        * @endxmlonly
         *
         * @since BlackBerry 10.2.0
        */
        class BBCASCADES_EXPORT KeyModifier
        {
            Q_GADGET
            Q_ENUMS(Type)
            Q_FLAGS(Types)

        public:
            /*!
            *
            * @xmlonly
            * <qml>
            * <enum flagsType="bb::cascades::KeyModifier::Types"/>
            * </qml>
            * @endxmlonly
             *
             * @since BlackBerry 10.2.0
            */
            enum Type {
                /*! @brief No modifier specified
                 *
                 * @since BlackBerry 10.2.0
                 */
                None = 0x00,
                /*! @brief Enable Shift-key modifier
                 *
                 * @since BlackBerry 10.2.0
                 */
                Shift = (1<<0),
                /*! @brief Enable Ctrl-key modifier
                 *
                 * @since BlackBerry 10.2.0
                 */
                Ctrl = (1<<1),
                /*! @brief Enable Alt-key modifier
                 *
                 * @since BlackBerry 10.2.0
                 */
                Alt = (1<<2)
            };

            Q_DECLARE_FLAGS(Types, Type)

        private:
            /*! @cond PRIVATE */
            KeyModifier() {};
            virtual ~KeyModifier() {};
            /*! @endcond */
        };

    }
}

/*! @cond PRIVATE */
QML_DECLARE_TYPE(bb::cascades::KeyModifier::Types)
Q_DECLARE_OPERATORS_FOR_FLAGS(bb::cascades::KeyModifier::Types)
/*! @endcond */


#endif // bb_cascades_keymodifier_h
