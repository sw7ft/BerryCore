/**
 * @copyright
 * Copyright BlackBerry Limited, 2013-2014
 * BlackBerry Limited. All rights reserved.
 */
#ifndef BB_PLATFORM_GEO_STYLESHEET_HPP
#define BB_PLATFORM_GEO_STYLESHEET_HPP

#include <bb/platform/geo/Global>
#include <bb/platform/geo/Style>

#include <QString>
#include <QStringList>
#include <QSharedDataPointer>
#include <QDebug>

namespace bb
{
namespace platform
{
namespace geo
{
class Geographic;
class StyleSheetPrivate;

/**
 * @headerfile StyleSheet.hpp <bb/platform/geo/StyleSheet>
 *
 * @brief A collection of @c Styles to be used when rendering a set of map
 * content.
 *
 * @c DataProvider and @c MapData use @c StyleSheet instances to gather and
 * store stylistic information about the @c Geographic data they contain.
 * This visual information is used by the @c RenderEngine when drawing the
 * @c Geographic data. The @c Styles within a @c StyleSheet can be applied
 * directly to individual elements, or applied to several elements through
 * a @c Geographic's style family, or applied to several elements through
 * their class type.
 *
 * @c Styles can be registered for a @c StyleSheet in a number of ways:
 * 1. Applied directly to a specific @c Geographic element by association
 * with the @c Geographic's ID (@c Geographic::id()).
 * 2. Applied to several @c Geographic elements by association with a style
 * family (@c Geographic::styleFamily()).
 * 3. Applied to several @c Geographic elements by association with their
 * class type. That is, associating a @c Style with a specific class. For
 * example, applying a @c Style to all instances of @c GeoLocation.
 * 4. Base style for @c StyleSheet.
 * 5. System-wide defaults.
 *
 * An individual @c Style's attributes can be set or "inherited". When an
 * attribute is set to "inherit", the next rule in sequence is used to
 * resolve that value. The sequence of these rules is in the same order
 * listed above.
 *
 * To help illustrate how these rules resolve inherited values, let's use
 * the following styles:
 * - Style for ID "bob"
 *   - edge style = inherited
 *   - edge color = inherited
 *   - fill color = blue
 * - Style for style family "smith"
 *   - edge style = inherited
 *   - edge color = inherited
 *   - fill color = red
 * - Style for instances of class @c GeoPolygon
 *   - edge style = @c EdgeStyle::Medium
 *   - edge color = inherited
 *   - fill color = inherited
 * - Style for instances of class @c GeoPolyline
 *   - edge style = @c EdgeStyle::Large
 *   - edge color = white
 *   - fill color = inherited
 * - Base style for @c StyleSheet
 *   - edge style = @c EdgeStyle::Small
 *   - edge color = purple
 *   - fill color = pink
 *
 *
 * Using the above definitions, the following @c Geographic elements would
 * have the following @c Style definitions:
 * - @c GeoPolyline, ID = "alison", style family = "smith"
 *   - edge style = @c EdgeStyle::Large (from class @c GeoPolyline)
 *   - edge color = white (from class @c GeoPolyline)
 *   - fill color = red (from style family "smith")
 * - @c GeoPolygon, ID = "bob", style family = "smith"
 *   - edge style = @c EdgeStyle::Medium (from class @c GeoPolygon)
 *   - edge color = purple (from base style for @c StyleSheet)
 *   - fill color = blue (from ID "bob")
 * - @c GeoPolyline, ID = "carol", style family = "jones"
 *   - edge style = @c EdgeStyle::Large (from class @c GeoPolyline)
 *   - edge color = white (from class @c GeoPolyline)
 *   - fill color = pink (from base style for @c StyleSheet)
 *
 * @c StyleSheet is an adaption of the
 * [Style Sheet Language](http://en.wikipedia.org/wiki/Style_sheet_language)
 * for the visual representation of @c Geographic data types within the
 * @c MapView control. As such, the
 * @c Style and @c StyleSheet are analogous to how Cascading Style
 * Sheets are used to render HTML documents. In an HTML document, the \<p\>
 * element can contain @c id and @c class attributes.  The accompanying CSS
 * document can designate visual information based on the @c id attribute,
 * by the @c class attribute, by the element type (in this case, \<p\>) or
 * by using a document default.  A @c StyleSheet is analogous to CSS in that
 * its visual information can be stated by ID (@c id in CSS), by style
 * family (@c class in CSS), by class name (element type in CSS) or by
 * using a default.
 *
 * There is a noted difference between the "getter" operations
 * (eg: @c styleForId, @c styleForFamily) and the @c resolveStyle
 * operation. The "getter" operations return the raw @c Style that was
 * registered, including any attributes set to be "inherited". The @c
 * resolveStyle operation ensures that all attributes are fully resolved so
 * that there are no "inherited" values.
 *
 * @xmlonly
 * <apigrouping group="Location/Geographic elements"/>
 * <library name="bbcascadesmaps"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_PLATFORM_GEO_EXPORT StyleSheet
{
public:

    /**
     * @brief Creates a @c StyleSheet instance.
     *
     * @since BlackBerry 10.2.0
     */
    StyleSheet();

    /**
     * @brief Copy constructor.
     *
     * @param src The object from which to copy information.
     *
     * @since BlackBerry 10.2.0
     */
    StyleSheet( const StyleSheet& src );

    /**
     * @brief Destructor.
     *
     * @since BlackBerry 10.2.0
     */
    ~StyleSheet();

    /**
     * @brief Assignment operator.
     *
     * @param src The object from which to copy information.
     *
     * @since BlackBerry 10.2.0
     */
    StyleSheet& operator=( const StyleSheet& src );

    /**
     * @brief Equality operator.
     *
     * @return @c true if all properties are equal.
     *
     * @since BlackBerry 10.2.0
     */
    bool operator==( const StyleSheet& rhs ) const;

    /**
     * @brief Inequality operator.
     *
     * @return @c true if any property is different.
     *
     * @since BlackBerry 10.2.0
     */
    bool operator!=( const StyleSheet& rhs ) const;

    /**
     * @brief Retrieves the base style for this set.
     *
     * @return This set's base style.
     * @since BlackBerry 10.2.0
     */
    Style baseStyle() const;

    /**
     * @brief Sets the base style for this set.
     *
     * @param style The set's new base style.
     * @since BlackBerry 10.2.0
     */
    void setBaseStyle( const Style& style );

    /**
     * @brief Adds a @c Style definition for a @c Geographic ID.
     *
     * This replaces any existing style registered for the given ID.
     *
     * @param id The ID to register against.
     * @param style The style to register.
     * @since BlackBerry 10.2.0
     */
    void addStyleForId( const QString& id, const Style& style );

    /**
     * @brief Retrieves the style for the given ID.
     *
     * @param id The ID upon which to search.
     * @return Returns the requested style, or a null Style if it
     * doesn't exist.
     * @since BlackBerry 10.2.0
     */
    Style styleForId( const QString& id ) const;

    /**
     * @brief Removes the style for the given ID.
     *
     * @param id The id against which the style to be removed was
     * registered.
     * @since BlackBerry 10.2.0
     */
    void removeStyleForId( const QString& id );

    /**
     * @brief Retrieves a list of all registered IDs.
     *
     * @return A list of all IDs that have been used to register
     * styles.
     * @since BlackBerry 10.2.0
     */
    QStringList registeredIds() const;

    /**
     * @brief Adds a @c Style definition for a style family.
     *
     * This replaces any existing style registered for the given
     * family.
     *
     * @param family The style family to register against.
     * @param style The style to register.
     * @since BlackBerry 10.2.0
     */
    void addStyleForFamily( const QString& family, const Style& style );

    /**
     * @brief Retrieves the style for the given style family.
     *
     * @param family The style family name upon which to search.
     * @return Returns the requested style, or a null Style if it
     * doesn't exist.
     * @since BlackBerry 10.2.0
     */
    Style styleForFamily( const QString& family ) const;

    /**
     * @brief Removes the style for the given style family.
     *
     * @param family The name of the style family to remove.
     * @since BlackBerry 10.2.0
     */
    void removeStyleForFamily( const QString& family );

    /**
     * @brief Retrieves a list of all registered style families.
     *
     * @return A list of all family styles that have been used to
     * register styles.
     * @since BlackBerry 10.2.0
     */
    QStringList registeredFamilies() const;

    /**
     * @brief Adds a @c Style definition for a @c Geographic class.
     *
     * This replaces any existing style registered for the given class.
     *
     * @param className The class name to register against.
     * @param style The style to register.
     * @since BlackBerry 10.2.0
     * @see addStyleForClass(Geographic*, Style)
     */
    void addStyleForClass( const QString& className, const Style& style );

    /**
     * @brief Adds a @c Style definition for a @c Geographic class.
     *
     * This replaces any existing style registered for the given class.
     *
     * @param classType The class type derived from @c Geographic to
     * register against.
     * @param style The style to register.
     * @since BlackBerry 10.2.0
     * @see addStyleForClass(QString, Style)
     */
    void addStyleForClass( const Geographic* classType,
                           const Style& style );

    /**
     * @brief Retrieves the style for the given ID.
     *
     * @param classname The name of the class upon which to retrieve.
     * @return Returns the requested style, or a null Style if it
     * doesn't exist.
     * @since BlackBerry 10.2.0
     * @see styleForClass(Geographic*)
     */
    Style styleForClass( const QString& classname ) const;

    /**
     * @brief Retrieves the style for the given ID.
     *
     * @param classType The class type derived from @c Geographic
     * upon which to retrieve.
     * @return Returns the requested style, or a null Style if it
     * doesn't exist.
     * @since BlackBerry 10.2.0
     * @see styleForClass(QString)
     */
    Style styleForClass( const Geographic* classType ) const;

    /**
     * @brief Removes the style for the given class name.
     *
     * @param classname The name of the class for which to remove
     * registered styles.
     * @since BlackBerry 10.2.0
     * @see removeStyleForClass(Geographic*)
     */
    void removeStyleForClass( const QString& classname );

    /**
     * @brief Removes the style for the given class type.
     *
     * @param classType The type of the class for which to remove
     * registered styles.
     * @since BlackBerry 10.2.0
     * @see removeStyleForClass(QString)
     */
    void removeStyleForClass( const Geographic* classType );

    /**
     * @brief Retrieves a list of all registered class names.
     *
     * @return A list of all class names that have been used to
     * register styles.
     * @since BlackBerry 10.2.0
     */
    QStringList registeredClasses() const;

    /**
     * @brief Generates a @c Style applicable for the given element
     * where all unresolved style attributes (inherited attributes)
     * have been resolved.
     *
     * @param element The @c Geographic element to find a complete
     * style for.
     * @return A fully populated @c Style instance for the given
     * element.
     * @since BlackBerry 10.2.0
     */
    Style resolveStyle( const Geographic* element ) const;

private:
    /** @cond PRIVATE */
    QSharedDataPointer<StyleSheetPrivate> d_ptr;
    /** @endcond */

};

} // namespace geo
} // namespace platform
} // namespace bb

Q_DECLARE_METATYPE( bb::platform::geo::StyleSheet );

#endif // BB_PLATFORM_GEO_STYLESHEET_HPP
