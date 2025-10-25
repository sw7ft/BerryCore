/* Copyright (C) 2013 Research In Motion Limited.  */
#ifndef BB_CASCADES_TEXTFIELDTEXTFITPROPERTIES_H
#define BB_CASCADES_TEXTFIELDTEXTFITPROPERTIES_H

#include <bb/cascades/bbcascades_global.h>
#include <QtDeclarative/QtDeclarative>
#include <bb/cascades/controls/textfitproperties.h>

namespace bb {
    namespace cascades {
        class TextFieldTextFitPropertiesPrivate;

        /*!
         * @brief Represents the auto fit properties of a @c TextField
         *
         * The @c TextFieldTextFitProperties configures how the @c TextField content adapts
         * its size to the @c TextField size
         *
         * @xmlonly
         * <apigrouping group="User interface/Text"/>
         * @endxmlonly
         *
         * @since BlackBerry 10.2.0
         */
        class BBCASCADES_EXPORT TextFieldTextFitProperties : public TextFitProperties
        {
            Q_OBJECT

        protected:
            /*! @cond PRIVATE */
            TextFieldTextFitProperties(BaseObject *parent = 0);
            virtual ~TextFieldTextFitProperties();
            /*! @endcond */

        private:
            /*! @cond PRIVATE */
            Q_DECLARE_PRIVATE(TextFieldTextFitProperties)
            Q_DISABLE_COPY(TextFieldTextFitProperties)
            /*! @endcond */
        };
    }
}

/*! @cond PRIVATE */
QML_DECLARE_TYPE(bb::cascades::TextFieldTextFitProperties)
/*! @endcond */

#endif // BB_CASCADES_TEXTFIELDTEXTFITPROPERTIES_H
