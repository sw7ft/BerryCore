/* Copyright (C) 2013 Research In Motion Limited.  */

#ifndef bb_cascades_fontfacerule_h
#define bb_cascades_fontfacerule_h

#include <bb/cascades/resources/abstracttextstylerule.h>

namespace bb {
namespace cascades {

class FontFaceRulePrivate;

/**
 * Represents the font face rules that define the properties for custom fonts.
 *
 * A @c %FontFaceRule object can be used to add an internal font family name to an external font. The
 * internal name is defined using a name you specify using the @c FontFaceRule::fontFamily property. In
 * addition, a @c %FontFaceRule object also requires a font file specified using the @c FontFaceRule::source
 * property. Currently, @c %FontFaceRule supports TrueType font (TTF) and OpenType font (OTF) formats,
 * and the font file must be located in the "assets" folder of your project.
 *
 * The @c #fontFamily and @c #source properties must be defined for a @c %FontFaceRule object to be valid.
 * If either the @c %fontFamily or @c %source properties are not defined, the rule is ignored.
 *
 * After the font family name is defined, it can be applied to a text control using the
 * @c TextStyleDefinition::fontFamily property.
 *
 * Currently, text style rules can only be applied in QML.
 *
 * The following QML example shows how to define an external font called "MyFont" that is sourced
 * from a font file called "myfont.ttf":
 * @code
 * import bb.cascades 1.2
 *
 * Container {
 *     attachedObjects: [
 *         TextStyleDefinition {
 *             id: myStyle
 *             base: SystemDefaults.TextStyles.BodyText
 *
 *             rules: [
 *                 FontFaceRule {
 *                     source: "myfont.ttf"
 *                     fontFamily: "MyFont"
 *                 }
 *             ]
 *             fontFamily: "MyFont, sans-serif"
 *         }
 *     ]
 *
 *     Label {
 *         text: "Hello, world!"
 *         textStyle.base: myStyle.style
 *     }
 * }
 * @endcode
 *
 * @see @c TextStyleDefinition::rules, @c TextStyleDefinition::fontFamily, @c TextStyle::fontFamily
 *
 * @xmlonly
 * <apigrouping group="User interface/Text"/>
 * <qml>
 * <class abstract="no"/>
 * </qml>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BBCASCADES_EXPORT FontFaceRule : public AbstractTextStyleRule
{
    Q_OBJECT

    /*!
     * @brief The font source URL.
     *
     * The default value is an empty @c QUrl. If no font source URL is specified for this property,
     * the @c %FontFaceRule is ignored. Only assets are supported for @c FontFaceRule::source property.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(QUrl source READ source WRITE setSource RESET resetSource NOTIFY sourceChanged FINAL)

    /*!
     * @brief The font-family name.
     *
     * The font family name can be used to reference this font in text style definition.
     * The default value is an empty string. If no font family name is specified for this property, the
     * @c %FontFaceRule is ignored.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(QString fontFamily READ fontFamily WRITE setFontFamily RESET resetFontFamily NOTIFY fontFamilyChanged FINAL)

public:
    /*!
     * @brief Returns the source of the @c FontFaceRule.
     *
     * @return The source of the @c %FontFaceRule.
     *
     * @since BlackBerry 10.2.0
     */
    QUrl source() const;

    /*!
     * @brief Sets the source on the @c FontFaceRule.
     *
     * @param source The source of the @c %FontFaceRule.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setSource(const QUrl& source);

    /*!
     * @brief Resets the font source on the @c FontFaceRule.
     *
     * The default value is an empty @c QUrl.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetSource();

    /*!
     * @brief Returns the font family of the @c FontFaceRule.
     *
     * @return The font family of the @c %FontFaceRule.
     *
     * @since BlackBerry 10.2.0
     */
    QString fontFamily() const;

    /*!
     * @brief Sets the font family on the @c FontFaceRule.
     *
     * @param fontFamily The font family of the @c %FontFaceRule.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void setFontFamily(const QString& fontFamily);

    /*!
     * @brief Resets the font family on the @c FontFaceRule to the default value.
     *
     * The default value is @c %QString::null.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void resetFontFamily();

Q_SIGNALS:
    /*!
     * @brief Emitted when the font source has changed.
     *
     * @param source The new font source.
     *
     * @since BlackBerry 10.2.0
     */
    void sourceChanged(const QUrl& source);

    /*!
     * @brief Emitted when the font family has changed.
     *
     * @param fontFamily The new font family.
     *
     * @since BlackBerry 10.2.0
     */
    void fontFamilyChanged(const QString& fontFamily);

protected:
    /*! @cond PRIVATE */
    FontFaceRule(QObject *pParent = 0);
    ~FontFaceRule();
    /*! @endcond */

private:
    /*! @cond PRIVATE */
    Q_DECLARE_PRIVATE(FontFaceRule)
    Q_DISABLE_COPY(FontFaceRule)
    /*! @endcond */
};

}
}

/*! @cond PRIVATE */
QML_DECLARE_TYPE(bb::cascades::FontFaceRule)
/*! @endcond */

#endif // bb_cascades_fontfacerule_h
