/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 * 
*/

#ifndef cascades_visualstyle_h
#define cascades_visualstyle_h

#include <bb/cascades/bbcascades_global.h>

#include <QObject>
#include <QDebug>

namespace bb {
namespace cascades {

/*!
 * @brief A class representing a theme's overall visual color style.
 *
 * Each @c ColorTheme has a @c VisualStyle that determines the colors used for
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
 * @xmlonly
 *     <apigrouping group="User interface/Core controls"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT VisualStyle {
    Q_GADGET
    Q_ENUMS(Type)

public:

   /*!
    * @brief Specifies the @c %VisualStyle the application uses.
    *
    * @since BlackBerry 10.0.0
    */
    enum Type {

        /*!
         * @brief The @c %VisualStyle is set to Bright.
         *
         * @since BlackBerry 10.0.0
         */
        Bright = 1,

        /*!
         * @brief The @c %VisualStyle is set to Dark.
         *
         * @since BlackBerry 10.0.0
         */
        Dark = 2
    };

private:
    /*! @cond PRIVATE */
    VisualStyle();
    virtual ~VisualStyle();
    /*! @endcond */
};

/*!
 * @brief Streams debug output about the pattern to the @c QDebug stream object.
 *
 * @param dbg           The @c %QDebug stream.
 * @param visualStyle   The @c %VisualStyle to output debug information about.
 * @return              The @c %QDebug stream.
 */
BBCASCADES_EXPORT QDebug operator<<(QDebug dbg, bb::cascades::VisualStyle::Type visualStyle);

}
}

#endif // cascades_visualstyle_h
