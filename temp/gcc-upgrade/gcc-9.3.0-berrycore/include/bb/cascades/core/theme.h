/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 * 
*/

#ifndef cascades_theme_h
#define cascades_theme_h

#include <bb/cascades/bbcascades_global.h>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb {
    namespace cascades {

    class ColorTheme;
    class ThemePrivate;

    /*!
     * @brief A class representing the application theme, which can consist of different elements, such as color values.
     *
     * The visual style of a theme is represented in it's @c ColorTheme, and that @c VisualStyle can be changed from @c ThemeSupport.
     * The current @c Theme is available from the @c Application::themeSupport property.
     *
     * @see @c ThemeSupport, @c ColorTheme, @c VisualStyle
     *
     * @xmlonly
     *     <apigrouping group="User interface/Core controls"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT Theme : public QObject
    {
    private:
        Q_OBJECT

        /*!
         * @brief Retrieves the current @c ColorTheme.
         *
         * Ownership of the returned object is not transferred.
         *
         * @return The application's ColorTheme.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::ColorTheme* colorTheme READ colorTheme CONSTANT FINAL);

    public:

        /*!
         * @brief Retrieves the @c %ColorTheme object.
         *
         * Ownership of the returned object is not transferred.
         *
         * @return The application's @c %ColorTheme object.
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::ColorTheme* colorTheme() const;

    private:
        /*! @cond PRIVATE */
        ThemePrivate * const d_ptr;
        explicit Theme(ColorTheme* pColorTheme, QObject* parent = 0);
        virtual ~Theme();
        Q_DECLARE_PRIVATE(Theme)
        Q_DISABLE_COPY(Theme)
        /*! @endcond */
    };
}
}

QML_DECLARE_TYPE(bb::cascades::Theme)

#endif // cascades_theme_h
