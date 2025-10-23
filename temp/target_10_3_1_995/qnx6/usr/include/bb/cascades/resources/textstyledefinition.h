/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_textstyledefinition_h
#define cascades_textstyledefinition_h

#include <bb/cascades/bbcascades_global.h>
#include <QtDeclarative/QtDeclarative>
#include <QString>
#include <bb/cascades/resources/colorpaint.h>
#include <bb/cascades/resources/textstyle.h>

#include <bb/cascades/BaseObject>

namespace bb {
namespace cascades {

class AbstractTextStyleRule;
class TextStyleDefinitionPrivate;

/*!
 * @brief Used to define style sets for sets of text nodes in an application.
 *
 * The @c %TextStyleDefinition class is used to modify the look and feel of the
 * text displayed in your app. Instead of specifying each style characteristic for each
 * individual control, you can create a @c %TextStyleDefinition and apply it to all of the text controls
 * in your app.
 *
 * The @c %TextStyleDefinition class constructs a text style based on a base text
 * style in combination with its own parameters.
 * All parameters that are set to non default values are used to override
 * the base text style. The resulting text style can be queried using the @c #style property.
 *
 * When you create a @c %TextStyleDefinition, you can base the style on one of the existing system defaults
 * specified in @c SystemDefaults::TextStyle. For example, if you create a custom title, you can
 * base the @c %TextStyleDefinition on the @c SystemDefaults::TextStyles::titleText() text style. You can then override
 * the individual style properties with style properties of your own. The resulting text style
 * can be queried using the @c #style property.
 *
 * The following C++ example shows you how to create a text style based on @c SystemDefaults::TextStyle::bodyText(),
 * with the @c #fontWeight property being overridden to bold and @c #fontSize being overridden to "small":
 * @code
 * TextStyleDefinition *pTSD = new TextStyleDefinition();
 * pTSD->setBase(SystemDefaults::TextStyles::bodyText());
 * pTSD->setFontWeight(FontWeight::Bold);
 * pTSD->setFontSize(FontSize::Small);
 * TextStyle boldBodyText = pTSD->style();
 *
 * @endcode
 *
 * Here's how to do the same thing in QML:
 * @code
 *
 * import bb.cascades 1.0
 *
 * Container {
 *
 *   attachedObjects: [
 *     TextStyleDefinition
 *     {
 *       id: tsd
 *       base: SystemDefaults.TextStyles.BodyText
 *       fontWeight: FontWeight.Bold
 *       fontSize: FontSize.Small
 *     }
 *   ]
 *
 *   Label{
 *     id: label
 *     text: "Hello, world!"
 *     textStyle
 *     {
 *       base: tsd.style
 *     }
 *   }
 *
 * }
 *
 * @endcode
 *
 * @xmlonly
 * <apigrouping group="User interface/Text"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT TextStyleDefinition : public BaseObject {
    Q_OBJECT

    /*!
     * @brief The base text style.
     *
     * The parameters of this text style are used if not explicitly overidden.
     *
     * The default value is a null @c %TextStyle.
     *
     * @xmlonly
     * <qml>
     * <variant type="bb::cascades::TextStyle"/>
     * </qml>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QVariant base READ baseQML WRITE setBaseQML NOTIFY baseChanged RESET resetBase FINAL)

    /*!
     * @brief The style constructed by the text style definition.
     *
     * The style is constructed from the base text style. All parameters that are set to non default values
     * will override the corresponding parameter from the base text style.
     *
     * @xmlonly
     * <qml>
     * <variant type="bb::cascades::TextStyle"/>
     * </qml>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QVariant style READ styleQML NOTIFY styleChanged FINAL)

    /*!
     * @brief The font family name.
     *
     * Example: Helvectica
     *
     * The default value is @c %QString::null. If the @c %fontFamily property is not specified, the
     * value from the base text style is used.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString fontFamily READ fontFamily WRITE setFontFamily NOTIFY fontFamilyChanged RESET resetFontFamily FINAL)

    /*!
     * @brief The font style.
     *
     * Font styles are defined in @c FontStyle, which includes options
     * such as normal and italic.
     *
     * The default value is @c FontStyle::Default. If the @c %fontStyle property is not specified, the
     * value from the base text style is used.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::cascades::FontStyle::Type fontStyle READ fontStyle WRITE setFontStyle NOTIFY fontStyleChanged RESET resetFontStyle FINAL)

    /*!
     * @brief The font weight.
     *
     * Font weights are defined in @c FontWeight, which includes options
     * such as W100, W200, ..., W800, W900, normal and bold.
     *
     * The default value is @c FontWeight::Default. If the @c %fontWeight property is not specified, the
     * value from the base text style is used.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::cascades::FontWeight::Type fontWeight
               READ fontWeight WRITE setFontWeight NOTIFY fontWeightChanged RESET resetFontWeight FINAL)

    /*!
     * @brief The color of the text.
     *
     * The default value is an invalid color. If the @c %color property is not specified, the value
     * from the base text style is used.
     *
     * Valid value types for this propety are @c Color and @c ColorPaint, and an invalid @c QVariant.
     *
     * @xmlonly
     * <qml>
     * <variant type="bb::cascades::Color"/>
     * <variant type="bb::cascades::ColorPaint"/>
     * </qml>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QVariant color READ color WRITE setColor NOTIFY colorChanged RESET resetColor FINAL)

    /*!
     * @brief The line height.
     *
     * This property indicates the distance between rows of text, with 1.0 being equal to 1 standard row height.
     * A @c %lineHeight of 1.5 sets the distance between rows to the height of 1.5 standard rows.
     *
     * The default value is -1.0. If the @c %lineHeight property is not specified, the value
     * from the base text style is used.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(float lineHeight
               READ lineHeight WRITE setLineHeight NOTIFY lineHeightChanged RESET resetLineHeight FINAL)

    /*!
     * @brief The font size value.
     *
     * This property indicates the font size in post script units or percentage, depending on the @c %fontSize.
     * Valid ranges are >= 0. Sizes < 0 will be clamped to 0.
     *
     * The default value is 0.0. If the @c %fontSizeValue is not specified, the value
     * from the base text style is used.
     *
     * If @c FontSize is set to @c PercentageValue, the size value 100.0 corresponds to the size of the
     * parent style element. If there is no parent element, the size is in relation to
     * the system default size, which typically matches the Medium logical size.
     * Note, this value will take effect only when font size is set to @c FontSize::PointValue
     * or @c FontSize::PercentageValue.
     *
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(float fontSizeValue READ fontSizeValue WRITE setFontSizeValue NOTIFY fontSizeValueChanged RESET resetFontSizeValue FINAL)


    /*!
     * @brief The logical font size.
     *
     * Logical font sizes are defined in @c FontSize.
     * Logical size will be translated to the actual size according to system font settings.
     *
     * E.g. the Large size can vary from 12pt to 20pt depending on the font size set in accesibility settings
     *
     * The default value is @c FontSize::Default. If the @c %fontSize property is not specified, the value
     * from the base text style is used.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::cascades::FontSize::Type fontSize READ fontSize WRITE setFontSize NOTIFY fontSizeChanged RESET resetFontSize FINAL)

    /*!
     * @brief The horizontal alignment.
     *
     * Horizontal alignment is defined in @c TextAlign, which includes options
     * such as center, left, right and justify.
     *
     * The default value is TextAlign::Default. If the @c %textAlign property is not specified, the value
     * from the base text style is used.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::cascades::TextAlign::Type textAlign
               READ textAlign WRITE setTextAlign NOTIFY textAlignChanged RESET resetTextAlign FINAL)

    /*!
     * A list of text style rules that define the properties for custom fonts.
     *
     * @see @c AbstractTextStyleRule, @c FontFaceRule
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(QDeclarativeListProperty<bb::cascades::AbstractTextStyleRule> rules READ rules REVISION 2 FINAL)

Q_SIGNALS:
    /*!
      * @brief Emitted when the style has changed.
      *
      * This is emitted when any of the parameters of
      * the @c %TextStyleDefinition has changed.
      *
     *
     * @since BlackBerry 10.0.0
      */
    void styleChanged();

    /*!
      * @brief Emitted when the base @c TextStyle has changed.
      *
      * @param textStyle The new base @c %TextStyle.
      *
      * @xmlonly
      * <qml>
      * <param name="textStyle" type="QVariant"/>
      * </qml>
      * @endxmlonly
     *
     * @since BlackBerry 10.0.0
      */
    void baseChanged(const bb::cascades::TextStyle &textStyle);

    /*! @cond PRIVATE */
    /*!
      * @brief Emitted when the base @c TextStyle has changed.
      *
      * @param textStyle The new base @c %TextStyle.
      */
    void baseChanged(const QVariant &textStyle);
    /*! @endcond */

    /*!
      * @brief Emitted when @c fontFamily has been changed.
      *
      * @param fontFamily The new font family name.
     *
     * @since BlackBerry 10.0.0
      */
    void fontFamilyChanged(const QString &fontFamily);

    /*!
      * @brief Emitted when @c fontStyle has been changed.
      *
      * @param newFontStyle The new font style.
     *
     * @since BlackBerry 10.0.0
      */
    void fontStyleChanged(bb::cascades::FontStyle::Type newFontStyle);

    /*!
      * @brief Emitted when @c fontWeight has been changed.
      *
      * @param newFontWeight The new font weight.
     *
     * @since BlackBerry 10.0.0
      */
    void fontWeightChanged(bb::cascades::FontWeight::Type newFontWeight);

    /*!
      * @brief Emitted when color has been changed.
      *
      * @param color The new color.
      *
      * @xmlonly
      * <qml>
      * <param name="color" type="QVariant"/>
      * </qml>
      * @endxmlonly
     *
     * @since BlackBerry 10.0.0
      */
    void colorChanged(const bb::cascades::ColorPaint &color);

    /*! @cond PRIVATE */
    /*!
      * @brief Emitted when color has been changed.
      *
      * @param color A @c QVariant containing the new color, or an invalid @c %QVariant if
      * the color was reset.
      */
    void colorChanged(const QVariant &color);
    /*! @endcond */

    /*!
      * @brief Emitted when @c lineHeight has been changed.
      *
      * @param lineHeight The new line height.
     *
     * @since BlackBerry 10.0.0
      */
    void lineHeightChanged(float lineHeight);

    /*!
      * @brief Emitted when font size value has been changed.
      *
      * @param fontSizeValue The new font size value.
     *
     * @since BlackBerry 10.0.0
      */
    void fontSizeValueChanged(float fontSizeValue);

    /*!
      * @brief Emitted when logical size has been changed.
      *
      * @param newFontSize The new logical font size.
     *
     * @since BlackBerry 10.0.0
      */
    void fontSizeChanged(bb::cascades::FontSize::Type newFontSize);

    /*!
      * @brief Emitted when alignment has been changed.
      *
      * @param newAlignment The new alignment.
     *
     * @since BlackBerry 10.0.0
      */
    void textAlignChanged(bb::cascades::TextAlign::Type newAlignment);

public:
    TextStyleDefinition();
    virtual ~TextStyleDefinition();

    /*!
     * @brief Returns the base @c TextStyle.
     *
     * @return The base @c %TextStyle if set, otherwise a null @c %TextStyle.
     *
     * @since BlackBerry 10.0.0
     */
     bb::cascades::TextStyle base();

    /*!
     * @brief Returns the constructed @c TextStyle.
     *
     * The style is constructed from a #base @c %TextStyle, along
     * with any specified style parameters that are used to override
     * the values of the base text style.
     *
     * @return The constructed @c TextStyle.
     *
     * @since BlackBerry 10.0.0
     */
    bb::cascades::TextStyle style();

    /*!
     * @brief Sets the base @c TextStyle.
     *
     * The base text style is combined with any specified style parameters
     * that are used to override the values of the base text style.
     *
     * The resulting @c %TextStyle can be queried via the @c #style property.
     *
     * @param base The base text style.
     *
     * @since BlackBerry 10.0.0
     */
    void setBase(const bb::cascades::TextStyle &base);

    /*!
     * @brief Resets the base @c TextStyle to its default value of null.
     *
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void resetBase();

    /*!
     * @brief Sets the font family name to use for font matching.
     *
     * Setting this value to anything other than the default value of QString::null
     * will make the @c TextStyleDefinition construct its style with this value
     * instead of the one provided from the base text style.
     *
     * @param fontFamily The font family name.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setFontFamily(const QString &fontFamily);

    /*!
     * @brief Returns the font family.
     *
     * @returns The font family if set, otherwise a null @c %QString is returned.
     *
     * @since BlackBerry 10.0.0
     */
    QString fontFamily() const;

    /*!
     * @brief Resets the #fontFamily to its default value of QString::null.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void resetFontFamily();

    /*!
     * @brief Sets the font style to use for font matching.
     *
     * Setting this value to anything other than the default value of @c FontStyle::Default
     * will make the @c TextStyleDefinition construct its style with this value
     * instead of the one provided from the base text style.
     *
     * @param fontStyle The font style.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setFontStyle(bb::cascades::FontStyle::Type fontStyle);

    /*!
     * @brief Returns the font style.
     *
     * @return The @c fontstyle if set, otherwise @c FontStyle::Default is returned.
     *
     * @see bb::cascades::FontStyle
     *
     * @since BlackBerry 10.0.0
     */
    bb::cascades::FontStyle::Type fontStyle() const;

    /*!
     * @brief Resets the @c #fontStyle to its default value.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void resetFontStyle();

    /*!
     * @brief Sets the font weight.
     *
     * Setting this value to anything other than the default value of @c FontWeight::Default
     * will make the @c TextStyleDefinition construct its style with this value
     * instead of the one provided from the base text style.
     *
     * @param fontWeight The font weight.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setFontWeight(bb::cascades::FontWeight::Type fontWeight);

    /*!
     * @brief Returns the font weight.
     *
     * @return The weight if set, otherwise @c FontWeight::Default will be returned.
     *
     * @see bb::cascades::FontWeight
     *
     * @since BlackBerry 10.0.0
     */
    bb::cascades::FontWeight::Type fontWeight() const;

    /*!
     * @brief Resets the #fontWeight to its default value.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void resetFontWeight();

    /*!
     * @brief Sets the text color.
     *
     * Setting this value to anything other than the default value of an invalid color
     * will make the @c TextStyleDefinition construct it's style with this value
     * instead of the one provided from the base text style.
     *
     * @param color The text color.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setColor(const bb::cascades::ColorPaint &color);

    /*!
     * @brief Sets the text color.
     *
     * Setting this value to anything other than the default value of an invalid color
     * will make the @c TextStyleDefinition construct it's style with this value
     * instead of the one provided from the base text style.
     *
     * The passed @c QVariant can either be invalid or contain values of type @c Color or @c PaintColor,
     * or it will be ignored.
     *
     * Setting an invalid @c %QVariant or a @c %QVariant containing invalid color is equivalent
     * to calling @c #resetColor().
     *
     * Example:
     * @code
     * styleDef2->setColor(styleDef1->color());
     * @endcode

     * @param color A @c QVariant containing the color to use or an invalid @c %QVariant.
     *
     * @xmlonly
     * <qml>
     * <variant type="bb::cascades::Color"/>
     * <variant type="bb::cascades::ColorPaint"/>
     * </qml>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setColor(const QVariant &color);

    /*!
     * @brief Returns the text color.
     *
     * The returned @c %QVariant will be either invalid or contain values of type @c Color or
     * @c ColorPaint.
     *
     * Use @c QVariant::canConvert<Type T>() to find actual type, and
     * then @c QVariant::value<Type T>() to get the value.
     *
     * For example:
     * @code
     * QVariant v = style->color();
     * if (v.canConvert<Color>()) {
     *   Color c = v.value<Color>();
     *   // use the color
     * } else if (v.canConvert<ColorPaint>()) {
     *   ColorPaint cp = v.value<ColorPaint>();
     *   // must be a system default paint
     * }
     * @endcode
     *
     * @return The text color if set, otherwise an invalid color is returned.
     *
     * @xmlonly
     * <qml>
     * <variant type="bb::cascades::Color"/>
     * <variant type="bb::cascades::ColorPaint"/>
     * </qml>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    QVariant color();

    /*!
     * @brief Resets the color to its default value as an invalid color.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void resetColor();

    /*!
     * @brief Sets the line height.
     *
     * Setting this value to anything other than the default value of 0.0
     * will make the @c TextStyleDefinition construct its style with this value
     * instead of the one provided from the base text style.
     *
     * @param lineHeight The line height.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setLineHeight(float lineHeight);

    /*!
     * @brief Returns the line height.
     *
     * The default value is 0.0.
     *
     * @return The line height if set, otherwise the default value is returned.
     *
     * @since BlackBerry 10.0.0
     */
    float  lineHeight() const;

    /*!
     * @brief Resets the #lineHeight to its default value of -1.0.
     *
     * @since BlackBerry 10.0.0
     */
     Q_INVOKABLE void resetLineHeight();

    /*!
     * @brief Sets the font size value.
     *
     * Setting this value to anything other than the default value of 0.0
     * will make the @c TextStyleDefinition construct its style with this value
     * instead of the one provided from the base text style.
     *
     * If @c FontSize is set to @c PercentageValue, size value 100.0 corresponds to the logical
     * size of the parent style element. If there is no parent element, the size is
     * in relation to the system default size, which typically matches the logical size of Medium.
     *
     * Note, this value will take effect only when font size is set to @c FontSize::PointValue or @c FontSize::PercentageValue
     *
     * @param size The font size value.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setFontSizeValue(float size);

    /*!
     * @brief Returns the font size value.
     *
     * The default value is 0.0.
     *
     * @return Font size value if set, otherwise the default value is returned.
     *
     * @since BlackBerry 10.0.0
     */
    float fontSizeValue() const;

    /*!
     * @brief Resets the #fontSizeValue to its default value of 0.0.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void resetFontSizeValue();

    /*!
     * @brief Sets the logical font size.
     *
     * @param size The logical font size.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setFontSize(bb::cascades::FontSize::Type size);

    /*!
     * @brief Returns the logical font size.
     *
     * @return The logical font size, if set.
     *
     * @since BlackBerry 10.0.0
     */
    bb::cascades::FontSize::Type fontSize() const;

    /*!
     * @brief Resets the logical size to its default value.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void resetFontSize();

    /*!
     * @brief Sets the horizontal text alignment.
     *
     * Setting this value to anything other than the default value of @c TextAlign::Default
     * will make the @c TextStyleDefinition construct its style with this value
     * instead of the one provided from the base text style.
     *
     * @param alignment The horizontal text alignment.
     *
     * @since BlackBerry 10.0.0
     */
    Q_SLOT void setTextAlign(bb::cascades::TextAlign::Type alignment);

    /*!
     * @brief Returns the horizontal text alignment.
     *
     * @return The text alignment if set, otherwise @c bb::cascades::TextAlign::Default is returned.
     *
     * @since BlackBerry 10.0.0
     */
    bb::cascades::TextAlign::Type textAlign();

    /*!
     * @brief Resets #textAlign to its default value.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void resetTextAlign();

private:
    /*! @cond PRIVATE */
    QDeclarativeListProperty<bb::cascades::AbstractTextStyleRule> rules() const;
    Q_DECLARE_PRIVATE(TextStyleDefinition)
    Q_DISABLE_COPY(TextStyleDefinition)

    QVariant baseQML();

    QVariant styleQML();

    Q_SLOT void setBaseQML(const QVariant textStyle);
    /*! @endcond */

};

}
}

QML_DECLARE_TYPE(bb::cascades::TextStyleDefinition)

#endif // cascades_textstyledefinition_h
