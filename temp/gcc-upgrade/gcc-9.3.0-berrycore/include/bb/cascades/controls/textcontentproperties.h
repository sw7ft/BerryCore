/* Copyright (C) 2012-2013 Research In Motion Limited.  */
#ifndef BB_CASCADES_TEXTCONTENTPROPERTIES_H
#define BB_CASCADES_TEXTCONTENTPROPERTIES_H

#include <bb/cascades/bbcascades_global.h>
#include <QtDeclarative/QtDeclarative>
#include <Qt/qobject.h>
#include <bb/cascades/controls/textcontentflag.h>

namespace bb {
    namespace cascades {

        class TextContentPropertiesPrivate;

        /*!
        * @brief Use for specifying different text content properties for text controls.
        *
        * @xmlonly
        * <apigrouping group="User interface/Text"/>
        * @endxmlonly
         *
         * @since BlackBerry 10.0.0
        */
        class BBCASCADES_EXPORT TextContentProperties : public QObject
        {
            Q_OBJECT

                /*!
                * @brief Text feature flags.
                *
                * A bit field used to turn on and off text features.
                *
                * @code
                * TextField {
                *    content.flags: TextContentFlag.ActiveText | TextContentFlag.EmoticonsOff;
                * }
                * @endcode
                *
                * @see bb::cascades::TextContentFlag::Types
                 *
                 * @since BlackBerry 10.0.0
                */
                Q_PROPERTY(bb::cascades::TextContentFlag::Types flags 
                READ flags 
                WRITE setFlags 
                RESET resetFlags 
                NOTIFY flagsChanged 
                FINAL)


        public:
            /*!
            * @brief Returns the text content flags.
            *
            * The content flags are a bit field used to turn on and off text features.
            *
            * @see bb::cascades::TextContentFlag::Types
            * @return The flags bit field.
             *
             * @since BlackBerry 10.0.0
            */
            bb::cascades::TextContentFlag::Types flags() const;

            /*!
            * @brief Sets the text content flags.
            *
            * The content flags are a bit field used to turn on and off text features. This function
            * will emit the flagsChanged signal.
            *
            * @code
            * pTextField->content()->setFlags(TextContentFlag::Emoticons | TextContentFlag::ActiveTextOff);
            * @endcode
            *
            * @see bb::cascades::TextContentFlag::Types
            * @param flags The new flags.
             *
             * @since BlackBerry 10.0.0
            */
            void setFlags(bb::cascades::TextContentFlag::Types flags);

            /*!
            * @brief Reset the content flags to the default state.
            *
            * The default state is @c TextContentFlag::Default.
             *
             * @since BlackBerry 10.0.0
            */
            Q_SLOT void resetFlags();

        Q_SIGNALS:
            /*!
            * @brief Emitted when the flags field has changed.
            *
            * @param newFlags The new flag bit field.
             *
             * @since BlackBerry 10.0.0
            */
            void flagsChanged(bb::cascades::TextContentFlag::Types newFlags);

        protected:
            /*! @cond PRIVATE */
            TextContentProperties(QObject *parent = 0);
            virtual ~TextContentProperties();
            /*! @endcond */

        private:
            /*! @cond PRIVATE */
            Q_DECLARE_PRIVATE(TextContentProperties)
            Q_DISABLE_COPY(TextContentProperties)
            TextContentPropertiesPrivate *d_ptr;
            /*! @endcond */
        };

    }
}

/*! @cond PRIVATE */
QML_DECLARE_TYPE(bb::cascades::TextContentProperties)
/*! @endcond */

#endif // BB_CASCADES_TEXTCONTENTPROPERTIES_H
