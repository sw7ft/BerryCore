/*
 * Copyright (C) 2012 - 2014 BlackBerry Limited. All rights reserved.
 */

#ifndef cascades_colortheme_h
#define cascades_colortheme_h

#include <bb/cascades/bbcascades_global.h>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

#include <bb/cascades/VisualStyle>
#include <bb/cascades/Color>

namespace bb {
    namespace cascades {
    class ColorThemePrivate;

    /*! 
     * @brief A class representing the color configurations of the theme.
     *
     * The @c style property specifies the @c VisualStyle that represents the
     * color of the theme (Bright or Dark). The @c primary() and @c primaryBase()
     * functions return the brand colors for the app. You can read the @c ColorTheme
     * for an app using the @c Application::themeSupport property.
     *
     * @see @c Theme, @c VisualStyle, [Themes](http://developer.blackberry.com/native/documentation/cascades/ui/themes/index.html)
     *
     * @xmlonly
     *     <apigrouping group="User interface/Core controls"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT ColorTheme : public QObject
    {
    private:
        Q_OBJECT

        /*!
         * @brief Specifies the current @c VisualStyle used in the @c %ColorTheme.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::VisualStyle::Type style READ style CONSTANT FINAL)

        /*!
         * @brief Specifies the global primary color of the application.
         *
         * The primary color along with the @c primaryBase color (also known as the
         * [brand colors](http://developer.blackberry.com/native/documentation/cascades/ui/themes/index.html#brandcolors103))
         * are used by the framework to provide accents on the UI components. This
         * property reflects the global primary color and it's recommended to use
         * @c UIPalette::primary instead for getting the correct color value within
         * the current context.
         *
         * Typically the primary color is specified in the bar-descriptor, but it is
         * also possible to change it at run-time by calling @c ThemeSupport::setPrimaryColor()
         * or @c ThemeSupport::setVisualStyleAndPrimaryColor().
         *
         * @xmlonly
         * <qml>
         * <variant type="bb::cascades::Color"/>
         * </qml>
         * @endxmlonly
         *
         * @since BlackBerry 10.3.0
         */
        Q_PROPERTY(QVariant primary READ primaryQml CONSTANT FINAL REVISION 3)

        /*!
         * @brief Specifies the global primary base color of the application.
         *
         * The primary color along with the @c primaryBase color (also known as the
         * [brand colors](http://developer.blackberry.com/native/documentation/cascades/ui/themes/index.html#brandcolors103))
         * are used by the framework to provide accents on the UI components. This
         * property reflects the global primary base color and it's recommended to use
         * @c UIPalette::primaryBase instead for getting the correct color value within
         * the current context.
         *
         * Typically the primary base color is specified in the bar-descriptor, but it is
         * also possible to change it at run-time by calling @c ThemeSupport::setPrimaryColor()
         * or @c ThemeSupport::setVisualStyleAndPrimaryColor().
         *
         * @xmlonly
         * <qml>
         * <variant type="bb::cascades::Color"/>
         * </qml>
         * @endxmlonly
         *
         * @since BlackBerry 10.3.0
         */
        Q_PROPERTY(QVariant primaryBase READ primaryBaseQml CONSTANT FINAL REVISION 3)

    public:

        /*!
         * @brief Retrieves the @c %VisualStyle for the theme.
         *
         * @return The application's @c VisualStyle.
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::VisualStyle::Type style() const;

        /*!
         * @brief Retrieves the global primary color for the application.
         *
         * This reflects the global primary color and whenever
         * possible it's recommended to use @c UIPalette::primary()
         * instead for getting the correct color value within the current context.
         *
         * @return The global primary color for the application.
         *
         * @since BlackBerry 10.3.0
         */
        Q_REVISION(3)
        bb::cascades::Color primary() const;
        /*!
         * @brief Retrieves the global primary base color for the application.
         *
         * This reflects the global primary base color and whenever
         * possible it's recommended to use @c UIPalette::primaryBase()
         * instead for getting the correct color value within the current context.
         *
         * @return The global primary base color for the application.
         *
         * @since BlackBerry 10.3.0
         */
        Q_REVISION(3)
        bb::cascades::Color primaryBase() const;

    private:
        /*! @cond PRIVATE */
        ColorThemePrivate* const d_ptr;
        explicit ColorTheme(const VisualStyle::Type visualStyle, QObject *parent = 0);
        ColorTheme(const VisualStyle::Type visualStyle, const Color& primary, const Color& primaryBase, QObject *parent = 0);
        virtual ~ColorTheme();

        /*!
         * @copydoc ColorTheme::primary()
         */
        Q_REVISION(3)
        QVariant primaryQml() const;

        /*!
         * @copydoc ColorTheme::primaryBase()
         */
        Q_REVISION(3)
        QVariant primaryBaseQml() const;

        Q_DECLARE_PRIVATE(ColorTheme)
        Q_DISABLE_COPY(ColorTheme)
        /*! @endcond */
    };
}
}

QML_DECLARE_TYPE(bb::cascades::ColorTheme)

#endif // cascades_colortheme_h
