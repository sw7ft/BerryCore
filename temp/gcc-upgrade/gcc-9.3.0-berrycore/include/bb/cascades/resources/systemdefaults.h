/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_systemdefaults_h
#define cascades_systemdefaults_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/resources/textstyle.h>
namespace bb {
namespace cascades {

    class ColorPaint;
    class Paint;

/*!
 * 
 * @brief Provides access to system defaults for texts and colors.
 *
 * System defaults are colors, paints, text styles and and other resources used to define 
 * the system's look and feel. This class provide high level access to those resources.
 *
 * @note At this point the collection of SystemDefaults is very limited and only
 *       gives access to a couple of default resources. This makes it difficult to give
 *       a really meaningful example. SystemDefaults still serve to train the developer
 *       to not have access to the actual color values in the default appearance.
 *
 * Here's a scenario for where system defaults are useful.
 * In a UI scene, there's a container that the developer wants to color using the 
 * same color as labels use for text, for whatever reason. If the actual color of 
 * label text would be known, the developer could just set that as the background 
 * of his container. However, if the visual appearance is updated (in a new release 
 * of the UI framework), his container would no longer have the same color as labels, 
 * and his application would be broken. So what he needs to do is:
 *
 * @code
 * Container *container = Container::create()
 *         .background(SystemDefaults::Paints::defaultText());
 * @endcode
 *
 * The container will now always have the same color as the default labels.
 *
 * This example shows how to access SystemDefaults from QML:
 * @code
 * Container {
 *     background: SystemDefaults.Paints.DefaultText
 * }
 * @endcode
 *
 * @warning The set of paints and colors in this collection will change.
 *
 * @xmlonly
 * <apigrouping group="User interface/Resources"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT SystemDefaults
{
public:

    /*!
     * @brief Provides access to the system's defaults for colors.
     *
     * This class can be used to find the system's default colors for text
     * and for a container's background.
     *
     * @see SystemDefaults
     *
     * @xmlonly
     * <apigrouping group="User interface/Resources"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT Paints
    {
    public:
        /*! 
         * @brief Returns the default text color.
         *
         * @return The default text color.
         *
         * @since BlackBerry 10.0.0
         */
        static const ColorPaint & defaultText();
    
        /*!
         * @brief Returns the default container background paint.
         *
         * @return The default container background paint.
         *
         * @since BlackBerry 10.0.0
         */
        static const Paint & containerBackground();

    private:
        /*! @cond PRIVATE */
        Paints();
        ~Paints();
        /*! @endcond */
    };


    /*!
     *
     * @brief Provides access to the system's defaults for text styles.
     *
     * This class can be used to find the system's default text styles for different 
     * types of text, including body text and title text.
     *
     * @see SystemDefaults
     *
     * @xmlonly
     * <apigrouping group="User interface/Resources"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT TextStyles
    {
    public:
        /*! 
         * @brief Returns the default style for large text.
         * 
         * @return The default style for big text.
         *
         * @since BlackBerry 10.0.0
         */
        static TextStyle bigText();

        /*!
         * @brief Returns the default style for body text.
         *
         * @return The default style for body text.
         *
         * @since BlackBerry 10.0.0
         */
        static TextStyle bodyText();
      
        /*!
        * @brief Returns the default style for primary text.
        *        
        * @note  This default style uses FontSize::PercentageValue
        *        for it's fontSize setting.
        * 
        * @return The default style for primary text.
         *
         * @since BlackBerry 10.0.0
        */
        static TextStyle primaryText();
    
        /*!
         * @brief Returns the default style for title text.
         *
         * @return The default style for title text.
         *
         * @since BlackBerry 10.0.0
         */
        static TextStyle titleText();

        /*! 
         * @brief Returns the default style for subtitle text.
         *
         * @return The default style for subtitle text.
         *
         * @since BlackBerry 10.0.0
         */
        static TextStyle subtitleText();

        /*! 
         * @brief Returns the default style for small text.
         *
         * @return The default style for small text.
         *
         * @since BlackBerry 10.0.0
         */
        static TextStyle smallText();

    private:
        /*! @cond PRIVATE */
        TextStyles();
        ~TextStyles();
        /*! @endcond */
    };

private:
    /*! @cond PRIVATE */
    SystemDefaults();
    ~SystemDefaults();
    /*! @endcond */
};



}
}
#endif   // cascades_systemdefaults_h
