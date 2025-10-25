/*!
 * @copyright
 * Copyright (C) 2014 BlackBerry Limited. All rights reserved.
 */

#ifndef cascades_uipalette_h
#define cascades_uipalette_h

#include <bb/cascades/bbcascades_global.h>

#include <QObject>
#include <QtDeclarative/QtDeclarative>
#include <bb/cascades/resources/color.h>


namespace bb {
    namespace cascades {
    class UIPalettePrivate;
    /*!
     * @brief A palette that provides access to color values that are being
     * used within the current context.
     *
     * A palette is comprised of a number of different colors that are dependent on
     * the theme (bright or dark) and the primary colors (blue accent by default) that your app uses.
     * Based on the theme and primary colors, the application creates
     * a palette of complimentary colors and shades for all the different types of components
     * (background, text, controls, and so on).
     *
     * Like the visual style, primary and primary base colors can be customized in the bar-descriptor.xml file
     * for your app. Here's an example of how you could set a custom primary and primary base color
     * to go with a default theme (Depending on the device that your app runs on,
     * either the bright theme or dark theme is applied to your UI controls).
     *
     * @code
     * <env var="CASCADES_THEME" value="default?primaryColor=0xFF3333&amp;primaryBase=0xCC3333"/>
     * @endcode
     *
     * The following image shows where many of the UI palette colors occur in a typical UI,
     * while using the configuration described above:
     * @image html ui_palette.png
     *
     * At runtime, you can retrieve the palette by checking the @c UiObject::ui property
     * of any component within the same context. 
     * Here's how to retrieve the palette colors from a @c Button, using C++:
     *
     * @snippet tad/examples/controls/button/src/ButtonExamples.cpp button7
     *
     * And here's how to retrieve the palette colors from a @c Page, using QML:
     *
     * @snippet tad/examples/applicationstructure/page/assets/main.qml page_qml2
     *
     * @see @c Theme, @c VisualStyle, @c UIConfig
     *
     * @xmlonly
     *     <apigrouping group="User interface/Core controls"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.3.0
     */
    class BBCASCADES_EXPORT UIPalette : public QObject
    {
    private:
        Q_OBJECT
        /*!
         * @brief Specifies the background @c Color of the @c %UIPalette.
         *
         * @xmlonly
         * <qml>
         * <variant type="bb::cascades::Color"/>
         * </qml>
         * @endxmlonly
         *
         * @since BlackBerry 10.3.0
         */
        Q_PROPERTY(QVariant background READ backgroundQml CONSTANT FINAL)
        /*!
         * @brief Specifies the plain @c Color of the @c %UIPalette.
         *
         * @xmlonly
         * <qml>
         * <variant type="bb::cascades::Color"/>
         * </qml>
         * @endxmlonly
         *
         * @since BlackBerry 10.3.0
         */
        Q_PROPERTY(QVariant plain READ plainQml CONSTANT FINAL)
        /*!
         * @brief Specifies the plain base @c Color of the @c %UIPalette.
         *
         * @xmlonly
         * <qml>
         * <variant type="bb::cascades::Color"/>
         * </qml>
         * @endxmlonly
         *
         * @since BlackBerry 10.3.0
         */
        Q_PROPERTY(QVariant plainBase READ plainBaseQml CONSTANT FINAL)
        /*!
         * @brief Specifies the primary @c Color of the @c %UIPalette.
         *
         * @xmlonly
         * <qml>
         * <variant type="bb::cascades::Color"/>
         * </qml>
         * @endxmlonly
         *
         * @since BlackBerry 10.3.0
         */
        Q_PROPERTY(QVariant primary READ primaryQml CONSTANT FINAL)
        /*!
         * @brief Specifies the primary base @c Color of the @c %UIPalette.
         *
         * @xmlonly
         * <qml>
         * <variant type="bb::cascades::Color"/>
         * </qml>
         * @endxmlonly
         *
         * @since BlackBerry 10.3.0
         */
        Q_PROPERTY(QVariant primaryBase READ primaryBaseQml CONSTANT FINAL)
        /*!
         * @brief Specifies the primary soft @c Color of the @c %UIPalette.
         *
         * @xmlonly
         * <qml>
         * <variant type="bb::cascades::Color"/>
         * </qml>
         * @endxmlonly
         *
         * @since BlackBerry 10.3.0
         */
        Q_PROPERTY(QVariant primarySoft READ primarySoftQml CONSTANT FINAL)
        /*!
         * @brief Specifies the text @c Color of the @c %UIPalette.
         *
         * @xmlonly
         * <qml>
         * <variant type="bb::cascades::Color"/>
         * </qml>
         * @endxmlonly
         *
         * @since BlackBerry 10.3.0
         */
        Q_PROPERTY(QVariant text READ textQml CONSTANT FINAL)
        /*!
         * @brief Specifies the primary accent text @c Color of the @c %UIPalette.
         *
         * @xmlonly
         * <qml>
         * <variant type="bb::cascades::Color"/>
         * </qml>
         * @endxmlonly
         *
         * @since BlackBerry 10.3.0
         */
        Q_PROPERTY(QVariant textPrimary READ textPrimaryQml CONSTANT FINAL)
        /*!
         * @brief Specifies the text @c Color on plain @c %Color of the @c %UIPalette.
         *
         * @xmlonly
         * <qml>
         * <variant type="bb::cascades::Color"/>
         * </qml>
         * @endxmlonly
         *
         * @since BlackBerry 10.3.0
         */
        Q_PROPERTY(QVariant textOnPlain READ textOnPlainQml CONSTANT FINAL)
        /*!
         * @brief Specifies the text @c Color on primry @c %Color of the @c %UIPalette.
         *
         * @xmlonly
         * <qml>
         * <variant type="bb::cascades::Color"/>
         * </qml>
         * @endxmlonly
         *
         * @since BlackBerry 10.3.0
         */
        Q_PROPERTY(QVariant textOnPrimary READ textOnPrimaryQml CONSTANT FINAL)
        /*!
         * @brief Specifies the primary dark @c Color of the @c %UIPalette.
         *
         * @since BlackBerry 10.3.1
         */
        Q_PROPERTY(QVariant primaryDark READ primaryDarkQml CONSTANT REVISION 4 FINAL)
        /*!
         * @brief Specifies the text @c Color used with the @c #primaryDark color of the @c %UIPalette.
         *
         * @since BlackBerry 10.3.1
         */
        Q_PROPERTY(QVariant textOnPrimaryDark READ textOnPrimaryDarkQml CONSTANT REVISION 4 FINAL)
        /*!
         * @brief Specifies the secondary text @c Color used with the @c #primary color of the @c %UIPalette.
         *
         * @since BlackBerry 10.3.1
         */
        Q_PROPERTY(QVariant secondaryTextOnPrimary READ secondaryTextOnPrimaryQml CONSTANT REVISION 4 FINAL)
        /*!
         * @brief Specifies the secondary text @c Color used with the @c #primaryDark color of the @c %UIPalette.
         *
         * @since BlackBerry 10.3.1
         */
        Q_PROPERTY(QVariant secondaryTextOnPrimaryDark READ secondaryTextOnPrimaryDarkQml CONSTANT REVISION 4 FINAL)
        /*!
         * @brief Specifies the secondary text @c Color used with the @c #plain color of the @c %UIPalette.
         *
         * @since BlackBerry 10.3.1
         */
        Q_PROPERTY(QVariant secondaryTextOnPlain READ secondaryTextOnPlainQml CONSTANT REVISION 4 FINAL)

    public:
        /*!
         * @brief Retrieves the background color.
         *
         * @return The background @c Color in the ui palette.
         *
         * @since BlackBerry 10.3.0
         */
        Color background() const;
        /*!
         * @brief Retrieves the plain color.
         *
         * @return The plain @c Color in the ui palette.
         *
         * @since BlackBerry 10.3.0
         */
        Color plain() const;
        /*!
         * @brief Retrieves the plain base color.
         *
         * @return The plain base @c Color in the ui palette.
         *
         * @since BlackBerry 10.3.0
         */
        Color plainBase() const;
        /*!
         * @brief Retrieves the primary color.
         *
         * @return The primary @c Color in the ui palette.
         *
         * @since BlackBerry 10.3.0
         */
        Color primary() const;
        /*!
         * @brief Retrieves the primary base color.
         *
         * @return The primary base @c Color in the ui palette.
         *
         * @since BlackBerry 10.3.0
         */
        Color primaryBase() const;
        /*!
         * @brief Retrieves the primary soft color.
         *
         * @return The primary soft @c Color in the ui palette.
         *
         * @since BlackBerry 10.3.0
         */
        Color primarySoft() const;
        /*!
         * @brief Retrieves the standard text color.
         *
         * @return The standard text @c Color in the ui palette.
         *
         * @since BlackBerry 10.3.0
         */
        Color text() const;
        /*!
         * @brief Retrieves the primary accent text color.
         *
         * @return The primary accent text @c Color in the ui palette.
         *
         * @since BlackBerry 10.3.0
         */
        Color textPrimary() const;
        /*!
         * @brief Retrieves the text color for a plain background.
         *
         * @return The text @c Color for a plain background in the ui palette.
         *
         * @since BlackBerry 10.3.0
         */
        Color textOnPlain() const;
        /*!
         * @brief Retrieves the text color for a primary background.
         *
         * @return The text @c Color for a primary background in the ui palette.
         *
         * @since BlackBerry 10.3.0
         */
        Color textOnPrimary() const;
        /*!
         * @brief Retrieves the primary dark color.
         *
         * @return The primary dark @c Color in the ui palette.
         *
         * @since BlackBerry 10.3.1
         */
        Q_REVISION(4)
        Color primaryDark() const;
        /*!
         * @brief Retrieves the text color for a primary dark background.
         *
         * @return The text @c Color for a primary dark background in the ui palette.
         *
         * @since BlackBerry 10.3.1
         */
        Q_REVISION(4)
        Color textOnPrimaryDark() const;
        /*!
         * @brief Retrieves the secondary text color for a plain color background.
         *
         * @return The secondary text @c Color for a plain color background in the ui palette.
         *
         * @since BlackBerry 10.3.1
         */
        Q_REVISION(4)
        Color secondaryTextOnPlain() const;
        /*!
         * @brief Retrieves the secondary text color for a primary color background.
         *
         * @return The secondary text @c Color for a primary color background in the ui palette.
         *
         * @since BlackBerry 10.3.1
         */
        Q_REVISION(4)
        Color secondaryTextOnPrimary() const;
        /*!
         * @brief Retrieves the secondary text color for a primary dark background.
         *
         * @return The secondary text @c Color for a primary dark background in the ui palette.
         *
         * @since BlackBerry 10.3.1
         */
        Q_REVISION(4)
        Color secondaryTextOnPrimaryDark() const;

    private:
        /*! @cond PRIVATE */
        /*!
         * @brief Retrieves the background color for the ui palette.
         *
         * @return The background @c QVariant will either be invalid or contain values of type @c Color.
         *
         * @since BlackBerry 10.3.0
         */
        QVariant backgroundQml() const;
        /*!
         * @brief Retrieves the plain color for the color palette.
         *
         * @return The plain @c QVariant will either be invalid or contain values of type @c Color.
         *
         * @since BlackBerry 10.3.0
         */
        QVariant plainQml() const;
        /*!
         * @brief Retrieves the plain base color for the color palette.
         *
         * @return The plain base @c QVariant will either be invalid or contain values of type @c Color.
         *
         * @since BlackBerry 10.3.0
         */
        QVariant plainBaseQml() const;
        /*!
         * @brief Retrieves the primary color for the ui palette.
         *
         * @return The primary @c QVariant will either be invalid or contain values of type @c Color.
         *
         * @since BlackBerry 10.3.0
         */
        QVariant primaryQml() const;
        /*!
         * @brief Retrieves the primary base color for the ui palette.
         *
         * @return The primary base @c QVariant will either be invalid or contain values of type @c Color.
         *
         * @since BlackBerry 10.3.0
         */
        QVariant primaryBaseQml() const;
        /*!
         * @brief Retrieves the primary soft color for the ui palette.
         *
         * @return The primary soft @c QVariant will either be invalid or contain values of type @c Color.
         *
         * @since BlackBerry 10.3.0
         */
        QVariant primarySoftQml() const;
        /*!
         * @brief Retrieves the text color for the ui palette.
         *
         * @return The text @c QVariant will either be invalid or contain values of type @c Color.
         *
         * @since BlackBerry 10.3.0
         */
        QVariant textQml() const;
        /*!
         * @brief Retrieves the primary accent text color for the ui palette.
         *
         * @return The primary accent text @c QVariant will either be invalid or contain values of type @c Color.
         *
         * @since BlackBerry 10.3.0
         */
        QVariant textPrimaryQml() const;
        /*!
         * @brief Retrieves the text color on plain background for the ui palette.
         *
         * @return The plain text color @c QVariant will either be invalid or contain values of type @c Color.
         *
         * @since BlackBerry 10.3.0
         */
        QVariant textOnPlainQml() const;
        /*!
         * @brief Retrieves the primary text color for the ui palette.
         *
         * @return The primary text @c QVariant will either be invalid or contain values of type @c Color.
         *
         * @since BlackBerry 10.3.0
         */
        QVariant textOnPrimaryQml() const;
        /*!
         * @brief Retrieves the primary dark color for the ui palette.
         *
         * @return The primary dark @c QVariant will either be invalid or contain values of type @c Color.
         *
         * @since BlackBerry 10.3.1
         */
        Q_REVISION(4)
        QVariant primaryDarkQml() const;
        /*!
         * @brief Retrieves the text color for primary dark background in the ui palette.
         *
         * @return The primary dark text color @c QVariant will either be invalid or contain values of type @c Color.
         *
         * @since BlackBerry 10.3.1
         */
        Q_REVISION(4)
        QVariant textOnPrimaryDarkQml() const;
        /*!
         * @brief Retrieves the secondary text color for plain color background in the ui palette.
         *
         * @return The secondary text color @c QVariant for plain color background will either be invalid or contain values of type @c Color.
         *
         * @since BlackBerry 10.3.1
         */
        Q_REVISION(4)
        QVariant secondaryTextOnPlainQml() const;
        /*!
         * @brief Retrieves the secondary text color for primary color background in the ui palette.
         *
         * @return The secondary text color @c QVariant for primary color background will either be invalid or contain values of type @c Color.
         *
         * @since BlackBerry 10.3.1
         */
        Q_REVISION(4)
        QVariant secondaryTextOnPrimaryQml() const;
        /*!
         * @brief Retrieves the secondary text color for primary dark background in the ui palette.
         *
         * @return The secondary text color @c QVariant for primary dark color background will either be invalid or contain values of type @c Color.
         *
         * @since BlackBerry 10.3.1
         */
        Q_REVISION(4)
        QVariant secondaryTextOnPrimaryDarkQml() const;

        UIPalettePrivate* const d_ptr;
        explicit UIPalette(QObject* parent = 0);
        virtual ~UIPalette();
        Q_DECLARE_PRIVATE(UIPalette)
        Q_DISABLE_COPY(UIPalette)

        /*! @endcond */
    };
}
}

QML_DECLARE_TYPE(bb::cascades::UIPalette)

#endif // cascades_uipalette_h
