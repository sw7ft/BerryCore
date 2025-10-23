/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_textstyle_h
#define cascades_textstyle_h

#include <QString>

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/resources/resource.h>

#include <bb/cascades/resources/fontstyle.h>
#include <bb/cascades/resources/fontweight.h>
#include <bb/cascades/resources/fontsize.h>
#include <bb/cascades/resources/textalign.h>
#include <bb/cascades/resources/colorpaint.h>

namespace bb {
    namespace cascades {
    
class TextStylePrivate;
class TextStyleData;

/*!   
 * @brief Represents a text style that defines how a text is rendered.
 *
 * Each text style has a different set of visual characteristics associated with it like weight, font style etc. 
 * If set to other values than their default values, these values will override the default characteristic of
 * controls that they are applied on. For example setting fontFamily to "helvetica" on a textstyle applied to a 
 * label will override the default system font with a font from the Helvetica family.
 *
 * @xmlonly
 * <apigrouping group="User interface/Text"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT TextStyle : public Resource { 

public:
    /*!
      * @brief Constructs a null @c %TextStyle.
     *
     * @since BlackBerry 10.0.0
      */
    TextStyle();
    virtual ~TextStyle();

    /*!
      * @brief Constructs a copy of another @c %TextStyle.
      *
      * @code
      * TextStyle a = SystemDefaults::TextStyles::bigText();
      * TextStyle b(a);
      * @endcode
      *
      * @param other The @c %TextStyle to be copied.
     *
     * @since BlackBerry 10.0.0
      */
    TextStyle(const TextStyle &other);

    /*!
      * @brief Assigns another @c %TextStyle to this @c %TextStyle.
      *
      * @param other The @c %TextStyle to be assigned.
      * @return A reference to the @c %TextStyle.
     *
     * @since BlackBerry 10.0.0
      */
    TextStyle& operator=(const TextStyle &other);

    /*!
     * @brief Sets the font family name to use for font matching in the @c %TextStyle.
     *
     * For example setting font family to "helvetica" will make the TextStyle try to find a font of the helvetica family.
     * The font family name can be specified with multiple fallbacks specified as either
     * ordinary font familys (times, arial etc.) or generic family names (serif, sans-serif)
     * The names should be separated by a comma and family names containing multiple word like Times New Roman should be enclosed
     * by quotations. Start by specifying specific font families and end with generic font families.
     * Currently only one specific font family is supported.
     *
     * Example:
     * @code
     * style.setFontFamily("\"Times New Roman\", serif");
     * @endcode
     *
     * @param fontFamily The font family name.
     *
     * @since BlackBerry 10.0.0
     */
    void setFontFamily(const QString &fontFamily);

    /*!
     * @brief Returns the font family for the @c %TextStyle.
     *
     * @return The font family if set, otherwise QString::null is returned.
     *
     * @since BlackBerry 10.0.0
     */
    QString fontFamily() const;

    /*!
     * @brief Resets the font family to its default.
     *
     * The default value is a QString::null.
     *
     * @since BlackBerry 10.0.0
     */
    void resetFontFamily();


    /*!
     * @brief Sets the font style.
     *
     * @param fontStyle The style to use.
     *
     * @since BlackBerry 10.0.0
     */
    void setFontStyle(FontStyle::Type fontStyle);

    /*!
     * @brief Returns the font style.
     *
     * @return The font style if set, otherwise FontStyle::Default is returned.
     *
     * @since BlackBerry 10.0.0
     */
    FontStyle::Type fontStyle() const;

    /*!
     * @brief Resets the font style to its default value.
     *
     * @since BlackBerry 10.0.0
     */
    void resetFontStyle();

    /*!
     * @brief Set the font weight.
     *
     * @param fontWeight The weight to use.
     *
     * @since BlackBerry 10.0.0
     */
    void setFontWeight(bb::cascades::FontWeight::Type fontWeight);

    /*!
     * @brief Returns the font weight.
     *
     * @return The weight if set, otherwise FontWeight::Default is returned.
     *
     * @since BlackBerry 10.0.0
     */
    bb::cascades::FontWeight::Type fontWeight() const;

    /*!
     * @brief Resets the font weight to its default value.
     *
     * @since BlackBerry 10.0.0
     */
    void resetFontWeight();

    /*!
     * @brief Sets the text color.
     *
     * Setting an invalid color is equivalent to calling resetColor().
     *
     * @param color The color to use.
     *
     * @since BlackBerry 10.0.0
     */
    void setColor(const bb::cascades::ColorPaint& color);

    /*!
     * @brief Convenience method for setting the text color for colors wrapped in QVariant
     *
     * Passed QVariant can either be invalid or contain values of type Color or PaintColor 
     * or it will be ignored.
     *
     * Setting an invalid @c QVariant or a QVariant containing invalid color is equivalent
     * to calling resetColor().
     *
     * Example:
     * @code
     * style2.setColor(style1.color());
     * @endcode
     * @param color A QVariant containing the color to use or an invalid QVariant
     *
     * @since BlackBerry 10.0.0
     */
    void setColor(const QVariant& color);

    /*!
     * @brief Returns the text color.
     *
     * Returned QVariant will be either invalid or contain values of type Color or
     * ColorPaint. Invalid QVariant signifies an unset color.
     *
     * Use @c QVariant::canConvert<Type T>() to find actual type, and 
     * then @c QVariant::value<Type T>() to get the value.
     *
     * For example:
     * @code
     * QVariant v = style->textColor();
     * if (v.canConvert<Color>()) {
     *   Color c = v.value<Color>();
     * } else if (v.canConvert<ColorPaint>()) {
     *   ColorPaint cp = v.value<ColorPaint>();
     * }
     * @endcode
     *
     * @return The current font color, wrapped in a QVariant or invalid QVariant
     * if text color wasn't set
     *
     * @since BlackBerry 10.0.0
     */
    QVariant color() const;

    /*!
     * @brief Resets the color to its default value as an invalid @c Color
     *
     * @since BlackBerry 10.0.0
     */
    void resetColor();

    /*!
     * @brief Sets the line height.
     *
     * Distance between rows of text. 1.0 is equal to 1 ordinary row height. 
     * 1.5 would make the distance between rows 1.5 ordinary row heights.
     * The default value is -1.0. 
     *
     * @param lineHeight The line height to use.
     *
     * @since BlackBerry 10.0.0
     */
    void setLineHeight(float lineHeight);

    /*!
     * @brief Returns the line height.
     *
     * The default value is -1.0.
     *
     * @return Line height if set. If not set the default value will be returned.
     *
     * @since BlackBerry 10.0.0
     */
    float lineHeight() const;

    /*!
     * @brief Resets the line height to its default value of -1.0
     *
     * @since BlackBerry 10.0.0
     */
    void resetLineHeight();

    /*!
     * @brief Sets the font size value.
     *
     * Font size in post script units or percent, depending on the FontSize setting.
     * Valid ranges are >= 0.
     * Sizes < 0 will be clamped to 0
     * The default value is 0.0.
     *
     * If FontSize is set to PercentageValue, size value 100.0 corresponds to the size of 
     * the parent style element. If there is no parent element, the size will be in relation
     * to the system default size, which typically matches the logical size Medium.
     * Note, this value will take effect only when font size is set to @c FontSize::PointValue 
     * or @c FontSize::PercentageValue
     *
     * @param size The font size value to use.
     *
     * @since BlackBerry 10.0.0
     */
    void setFontSizeValue(float size);

    /*!
     * @brief Returns the font size value in points or percent
     *        The unit of the return value depends on the current
     *        setting of the fontSize property. If it is set to 
     *        FontSize::PointValue, the unit is post script points.
     *        If it is set to FontSize::PercentageValue, the unit is
     *        percent and the size is relative to the point size of
     *        parent style element. If there is no parent element, the 
     *        size will be in relation to the system default size, which 
     *        typically matches the logical size Medium.
     *
     * @return Font size value.
     *
     * @since BlackBerry 10.0.0
     */
    float fontSizeValue() const;

    /*!
     * @brief Resets the font size value to its default value 0.0.
     *
     * @since BlackBerry 10.0.0
     */
    void resetFontSizeValue();

    /*!
     * @brief Sets the logical font size.
     *
     * Logical font size will be translated to actual font size according to font size set in accessibility settings.
     *
     * @param size The font size to use.
     *
     * @since BlackBerry 10.0.0
     */
    void setFontSize(FontSize::Type size);

    /*!
     * @brief Returns the logical font size.
     *
     * @return Font size.
     *
     * @since BlackBerry 10.0.0
     */
    FontSize::Type fontSize() const;

    /*!
     * @brief Resets the logical font size to its default value.
     *
     * @since BlackBerry 10.0.0
     */
    void resetFontSize();

    /*!
     * @brief Sets the horizontal alignment for the text.
     *
     * @param alignment The horizontal text alignment to use.
     *
     * @since BlackBerry 10.0.0
     */
    void setTextAlign(bb::cascades::TextAlign::Type alignment);

    /*! 
     * @brief Returns the horizontal alignment for the text.
     *
     * @return The text alignment if set, otherwise TextAlign::Default is returned.
     *
     * @since BlackBerry 10.0.0
     */
    bb::cascades::TextAlign::Type textAlign() const;

    /*!
     * @brief Resets the horizontal alignment to its default value.
     *
     * @since BlackBerry 10.0.0
     */
    void resetTextAlign();

protected:
  /*! @cond PRIVATE */
    Q_DECLARE_PRIVATE(TextStyle)
  /*! @endcond */

private:
    /*! @cond PRIVATE */
    Q_DECL_HIDDEN TextStyle(TextStyleData *p);
    /*! @endcond */
};

}
}

Q_DECLARE_METATYPE(bb::cascades::TextStyle);

#endif // cascades_textstyle_h
