/*
 * Copyright (C) 2012 - 2014 BlackBerry Limited. All rights reserved.
 */

#ifndef cascades_themesupport_h
#define cascades_themesupport_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/core/visualstyle.h>
#include <bb/cascades/resources/color.h>

#include <QObject>
#include <QtDeclarative/QtDeclarative>


namespace bb {
    namespace cascades {
    class Theme;
    class ThemeSupportPrivate;

    /*!
     * @brief A class containing theme related functionality.
     *
     * This class offers functionality to obtain the current theme and listen
     * for theme related changes.
     *
     * Each theme has a @c VisualStyle that determines the colors used for
     * controls and the default container background. The two visual
     * styles are @c VisualStyle::Bright and @c VisualStyle::Dark, the default
     * being @c Bright.
     *
     * @image html theme_examples.png
     *
     * To change the application's theme to Dark specify the following configuration value
     * in the application's bar-descriptor.xml file.
     *
     * @code
     * <env var="CASCADES_THEME" value="dark"/>
     * @endcode
     *
     * Here are some examples for how to check the @c VisualStyle of the currently
     * set theme for the application:
     *
     * C++:
     * @code
     * void ThemeTest()
     * {
     *     Label* pLabel = Label::create();
     *
     *     ThemeSupport* pThemeSupport = Application::instance()->themeSupport();
     *     Theme* pTheme = pThemeSupport->theme();
     *     ColorTheme* pColTheme = pTheme->colorTheme();
     *
     *     switch(pColTheme->style()) {
     *         case VisualStyle::Bright:
     *             pLabel->setText("Theme: Bright");
     *             break;
     *
     *         case VisualStyle::Dark:
     *             pLabel->setText("Theme: Dark");
     *             break;
     *
     *         default:
     *             pLabel->setText("Theme: Unknown");
     *             break;
     *     }
     * }
     * @endcode
     *
     * QML:
     * @code
     * Container {
     *     id: cont1
     *
     *     function themeStyleToString(style){
     *         switch(style) {
     *             case VisualStyle.Bright:    return "Theme: Bright"
     *             case VisualStyle.Dark:      return "Theme: Dark"
     *         }
     *         return "Theme: UNKNOWN :("
     *     }
     *
     *     Label {
     *         id: themeLabel;
     *         text: cont1.themeStyleToString(Application.themeSupport.theme.colorTheme.style)
     *     }
     * }
     * @endcode
     *
     * @see @c Application, @c Theme, @c VisualStyle, [Themes](http://developer.blackberry.com/native/documentation/cascades/ui/themes/index.html)
     *
     * @xmlonly
     *     <apigrouping group="User interface/Core controls"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT ThemeSupport : public QObject
    {
    private:
        Q_OBJECT

        /*!
         * @brief Provides access to the current theme used in the application.
         *
         * Typically connected from @c %Application:
         * @code
         *     QObject::connect((Application*)Application::instance()->themeSupport(),
         *                      SIGNAL(themeChanged(const bb::cascades::Theme*)),
         *                      this,
         *                      SLOT(onThemeChanged(const bb::cascades::Theme*)));
         * @endcode
         *
         * @see Theme, [Themes](http://developer.blackberry.com/native/documentation/cascades/ui/themes/index.html)
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::Theme* theme READ theme NOTIFY themeChanged FINAL)

    public:

        /*!
         * @brief Retrieves the current theme.
         *
         * Ownership of the returned object is not transferred.
         *
         * @return The application's theme.
         * @see Theme
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::Theme* theme() const;

        /*!
         * @brief Sets the visual style and primary color for the application.
         *
         * The visual style defines most of the visual characteristics of the theme.
         * The @c primary color along with the @c primaryBase color (also known as the
         * [brand colors](http://developer.blackberry.com/native/documentation/cascades/ui/themes/index.html#brandcolors103))
         * are used by the framework to provide accents on the UI components. Typically
         * these values are specified in the bar-descriptor, but you can also call this
         * function to change them at run-time.
         *
         * @warning Changing the visual style and primary colors is resource intensive.
         *          Whenever possible specify these values in the bar-descriptor and
         *          refrain from excessive use of this function.
         *
         * @param visualStyle The @c VisualStyle to set.
         *
         * @param primary The primary color used to provide accents on the UI components. The
         *                alpha channel of the color is always ignored. If it is a @c null color,
         *                niether the primary or primary base color is changed.
         *
         * @param primaryBase An optional color used together with the @c primary color. It should
         *                    always be darker than the primary color. The alpha channel of the
         *                    color is always ignored. By default, it is a @c null color, letting
         *                    the framework calculate it for you.
         *
         * @since BlackBerry 10.3.0
         */
        Q_REVISION(3)
        Q_INVOKABLE void setVisualStyleAndPrimaryColor(bb::cascades::VisualStyle::Type visualStyle,
                                                       const bb::cascades::Color& primary,
                                                       const bb::cascades::Color& primaryBase = bb::cascades::Color());

        /*!
         * @brief Sets the visual style for the application.
         *
         * The visual style defines most of the visual characteristics of the theme.
         * Typically it is specified in the bar-descriptor, but you can also call this
         * function to change it at run-time.
         *
         * @warning Changing the visual style is resource intensive. Whenever possible
         *          specify the primary colors in the bar-descriptor and refrain from
         *          excessive use of this function.
         *
         * @see setVisualStyleAndPrimaryColor() if you also want to change the primary
         *                                      color at the same time.
         *
         * This does not affect any default global settings for the platform
         * and so must be used every time the application is started
         * or otherwise intended to change it's appearance.
         * You typically do this after creating the @c Application and
         * before creating any controls.
         *
         * The application developer is responsible for reading and
         * writing this setting on app startup if necessary.
         *
         * @param visualStyle The @c VisualStyle to set.
         *
         * @see VisualStyle
         *
         * @since BlackBerry 10.3.0
         */
        Q_REVISION(3)
        Q_INVOKABLE void setVisualStyle(bb::cascades::VisualStyle::Type visualStyle);

        /*!
         * @brief Sets the primary color for the application.
         *
         * The @c primary color along with the @c primaryBase color (also known as the
         * [brand colors](http://developer.blackberry.com/native/documentation/cascades/ui/themes/index.html#brandcolors103))
         * are used by the framework to provide accents on the UI components. Typically
         * these colors are specified in the bar-descriptor, but you can also call this
         * function to change them at run-time.
         *
         * @warning Changing the primary colors is resource intensive. Whenever possible
         *          specify the primary colors in the bar-descriptor and refrain from
         *          excessive use of this function.
         *
         * @see setVisualStyleAndPrimaryColor() if you also want to change the visual
         *                                      style at the same time.
         *
         * @param primary The primary color used to provide accents on the UI components. The
         *                alpha channel of the color is always ignored. If it is a @c null color,
         *                niether the primary or primary base color is changed.
         *
         * @param primaryBase An optional color used together with the @c primary color. It should
         *                    always be darker than the primary color. The alpha channel of the
         *                    color is always ignored. By default, it is a @c null color, letting
         *                    the framework calculate it for you.
         *
         * @since BlackBerry 10.3.0
         */
        Q_REVISION(3)
        Q_INVOKABLE void setPrimaryColor(const bb::cascades::Color& primary,
                                         const bb::cascades::Color& primaryBase = bb::cascades::Color());

    Q_SIGNALS:

        /*!
         * @brief Emitted when the theme for this application has changed.
         *
         * @param theme a new theme or @c 0 if there was an error
         *
         * @since BlackBerry 10.0.0
         */
        void themeChanged(const bb::cascades::Theme* theme);

    private:
        /*! @cond PRIVATE */
        ThemeSupportPrivate* const d_ptr;
        explicit ThemeSupport(QObject *parent = 0);
        virtual ~ThemeSupport();
        Q_DECLARE_PRIVATE(ThemeSupport)
        Q_DISABLE_COPY(ThemeSupport)
        /*! @endcond */

    public:
      /*! @cond PRIVATE */
      /*!
       * @copydoc ThemeSupport::setVisualStyleAndPrimaryColor(bb::cascades::VisualStyle::Type, const bb::cascades::Color&, const bb::cascades::Color&)
       *
       * Workaround for the Qt bug that prevents our enums from being function arguments in QML.
       *
       * @since BlackBerry 10.3.0
       */
      Q_REVISION(3)
      Q_INVOKABLE void setVisualStyleAndPrimaryColor(int visualStyle, QVariant primary = QVariant(), QVariant primaryBase = QVariant());

      /*!
       * @copydoc ThemeSupport::setVisualStyle(bb::cascades::VisualStyle::Type)
       *
       * Workaround for the Qt bug that prevents our enums from being function arguments in QML.
       * @since BlackBerry 10.3.0
       */
      Q_REVISION(3)
      Q_INVOKABLE void setVisualStyle(int visualStyle);

      /*!
       * @copydoc ThemeSupport::setPrimaryColor(const bb::cascades::Color&, const bb::cascades::Color&)
       *
       * @since BlackBerry 10.3.0
       */
      Q_REVISION(3)
      Q_INVOKABLE void setPrimaryColor(QVariant primary, QVariant primaryBase = QVariant());
      /*! @endcond */
    };
}
}

QML_DECLARE_TYPE(bb::cascades::ThemeSupport)

#endif // cascades_themesupport_h
