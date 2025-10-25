/* Copyright (C) 2013 Research In Motion Limited.  */
#ifndef BB_CASCADES_TEXTAREATEXTFITPROPERTIES_H
#define BB_CASCADES_TEXTAREATEXTFITPROPERTIES_H

#include <bb/cascades/bbcascades_global.h>
#include <QtDeclarative/QtDeclarative>
#include <bb/cascades/controls/textfitproperties.h>

namespace bb {
    namespace cascades {
        class TextAreaTextFitPropertiesPrivate;

        /*!
         * @brief Represents the auto fit properties of a @c TextArea
         *
         * The @c TextAreaTextFitProperties configures how the @c TextArea content adapts
         * its size to the @c TextArea size
         *
         * @xmlonly
         * <apigrouping group="User interface/Text"/>
         * @endxmlonly
         *
         * @since BlackBerry 10.2.0
         */
        class BBCASCADES_EXPORT TextAreaTextFitProperties : public TextFitProperties
        {
            Q_OBJECT

        protected:
            /*! @cond PRIVATE */
            TextAreaTextFitProperties(BaseObject *parent = 0);
            virtual ~TextAreaTextFitProperties();
            /*! @endcond */

        private:
            /*! @cond PRIVATE */
            Q_DECLARE_PRIVATE(TextAreaTextFitProperties)
            Q_DISABLE_COPY(TextAreaTextFitProperties)
            /*! @endcond */
        };
    }
}

/*! @cond PRIVATE */
QML_DECLARE_TYPE(bb::cascades::TextAreaTextFitProperties)
/*! @endcond */

#endif // BB_CASCADES_TEXTAREATEXTFITPROPERTIES_H
