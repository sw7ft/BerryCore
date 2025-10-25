/*
 * Copyright (C) 2014 BlackBerry Limited. All rights reserved.
 */

#ifndef cascades_textfieldtitlebarkindproperties_h
#define cascades_textfieldtitlebarkindproperties_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/resources/abstracttitlebarkindproperties.h>
namespace bb {
    namespace cascades {

    class TextFieldTitleBarKindPropertiesPrivate;
    class TextField;

    /*!
     * 
     * @brief A class that holds the @c TextField propertie that is associated with the @c TextField type of @c TitleBar.
     * 
     * @c TextFieldTitleBarKindProperties gives access to the text field that is set up to match the style
     * in the TitleBar.
     *
     * @see @c TitleBar::kindProperties, @c TitleBar::kind 
     * 
     * @xmlonly
     * <apigrouping group="User interface/Application structure"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.3.0
     */
    class BBCASCADES_EXPORT TextFieldTitleBarKindProperties : public AbstractTitleBarKindProperties
    {
        Q_OBJECT

       /*!
        * @brief The @c TextField on the @c TitleBar if the @c kind property is @c TextField.
        *
        * If the @c TitleBar::kind property is @c TextField, this property gives access to the
        * @c TextField used on the @c TitleBar.
        *
        * @xmlonly
        * <qml>
        * <property groupedProperty="yes"/>
        * </qml>
        * @endxmlonly
        *
        * @since BlackBerry 10.3.0
        */
        Q_PROPERTY(bb::cascades::TextField* textField READ textField CONSTANT FINAL)

    public:

       /*!
        * @brief Constructs a @c %TextFieldTitleBarKindProperties.   
        *
        * @since BlackBerry 10.3.0        
        */
        explicit TextFieldTitleBarKindProperties();
        
       /*!
        * @brief Destroys this @c %TextFieldTitleBarKindProperties.
        *
        * @since BlackBerry 10.3.0
        */
        virtual ~TextFieldTitleBarKindProperties();

       /*!
        * @brief Returns the @c %TextField on this @c %TitleBar.
        *
        * @return The @c %textField. This is never 0, since @c %textField is
        * a grouped property.
        *
        * @since BlackBerry 10.3.0
        */
        bb::cascades::TextField* textField() const;

    private:
        
        /*! \cond PRIVATE */
        Q_DECLARE_PRIVATE(TextFieldTitleBarKindProperties)
        Q_DISABLE_COPY(TextFieldTitleBarKindProperties)

    public:
        typedef TextFieldTitleBarKindProperties ThisClass;
        typedef AbstractTitleBarKindProperties BaseClass;
        /*! @endcond */
        
       /*!
        * @brief A template builder class for constructing a @c %TextFieldTitleBarKindProperties object.
        * 
        * To retrieve the builder, call @c TextFieldTitleBarKindProperties::create().
        *
        * @since BlackBerry 10.3.0
        */
        template <typename BuilderType, typename BuiltType>
        class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType> {
        protected:
            TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node) {
            }
        };

       /*!        
        * @brief A builder class for constructing a @c %TextFieldTitleBarKindProperties object.
        * 
        * To retrieve the builder, call @c TextFieldTitleBarKindProperties::create().
        *
        * @since BlackBerry 10.3.0
        */
        class Builder : public TBuilder<Builder, TextFieldTitleBarKindProperties>
        {
        public:
            explicit Builder() : TBuilder<Builder, TextFieldTitleBarKindProperties>(new TextFieldTitleBarKindProperties()) {}
        };

        /*!
        * @brief Creates and returns a builder for constructing a @c %TextFieldTitleBarKindProperties object.
        *
        * Using the builder to create a @c %TextFieldTitleBarKindProperties object.
        * 
        * @code
        * TextFieldTitleBarKindProperties* myTextFieldProperties = TextFieldTitleBarKindProperties::create();
        * @endcode
        *
        * @return A builder used for constructing a @c %TextFieldTitleBarKindProperties object.
        *
        * @since BlackBerry 10.3.0
        */
        static Builder create() {
            return Builder();
        }
    };
    }

}

QML_DECLARE_TYPE(bb::cascades::TextFieldTitleBarKindProperties)

#endif //cascades_textfieldtitlebarkindproperties_h
