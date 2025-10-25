/**
 * @copyright
 * Copyright BlackBerry Limited, 2013-2014
 * BlackBerry Limited. All rights reserved.
 */
#ifndef BB_PLATFORM_GEO_STYLE_HPP
#define BB_PLATFORM_GEO_STYLE_HPP

#include <bb/platform/geo/Global>
#include <bb/platform/geo/EdgeSize>
#include <bb/platform/geo/EdgeStyle>

#include <QSharedDataPointer>
#include <QDebug>

namespace bb
{
namespace platform
{
namespace geo
{
class StylePrivate;

/**
 * @headerfile Style.hpp <bb/platform/geo/Style>
 *
 * @brief Visual information that can be applied to a @c Geographic.
 *
 * A @c Style is a collection of information determining how a @c
 * Geographic is visually displayed.
 *
 * A @c Geographic's style is separated from its data in an analogous way
 * to how an HTML document's visual characteristics are captured in a
 * separate Cascading Style Sheet document. As such, @c Styles can be
 * inherited, they can be applied directly to an element through its ID,
 * they can be applied to several elements through a style family or they
 * can be applied to several elements through the element's class.
 *
 * See the class-level documentation for @c StyleSheet for how a style is
 * resolved at render time.
 *
 * Colors in @c Style are defined through ARGB8888 integers. See @c
 * bb::cascades::Color for how to generate color integers.
 *
 * @xmlonly
 * <apigrouping group="Location/Geographic elements"/>
 * <library name="bbcascadesmaps"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_PLATFORM_GEO_EXPORT Style
{
public:

    /**
     * @brief Creates a @c Style using the system default values for
     * the edge and fill attributes.
     *
     * The current system default values are:
     * - @c EdgeSize::Small edge size
     * - @c EdgeStyle::Solid edge pattern
     * - blue with 75% opaqueness for the edge color
     * - blue with 25% opaqueness for the fill color
     * As such, this style is fully populated.
     *
     * @return A @c Style showing the system defaults.
     */
    static Style systemDefault();

    /**
     * @brief Creates an empty @c Style instance.
     *
     * @see isEmpty()
     * @see isComplete()
     * @since BlackBerry 10.2.0
     */
    Style();

    /**
     * @brief Creates a completed @c Style instance.
     *
     * @param edgeSize The style's edge size.
     * @param edgeStyle The style's edge style.
     * @param edgeColor The style's edge color.
     * @param fillColor The style's fill color.
     * @see isComplete()
     * @since BlackBerry 10.2.0
     */
    Style( EdgeSize::Type edgeSize, EdgeStyle::Type edgeStyle, int edgeColor, int fillColor );

    /**
     * @brief Copy constructor.
     *
     * @param src The object from which to copy information.
     *
     * @since BlackBerry 10.2.0
     */
    Style( const Style& src );

    /**
     * @brief Destructor.
     *
     * @since BlackBerry 10.2.0
     */
    ~Style();

    /**
     * @brief Assignment operator.
     *
     * @param src The object from which to copy information.
     *
     * @since BlackBerry 10.2.0
     */
    Style& operator=( const Style& src );

    /**
     * @brief Equality operator.
     *
     * @return @c true if all properties are equal.
     *
     * @since BlackBerry 10.2.0
     */
    bool operator==( const Style& rhs ) const;

    /**
     * @brief Inequality operator.
     *
     * @return @c true if any property is different.
     *
     * @since BlackBerry 10.2.0
     */
    bool operator!=( const Style& rhs ) const;

    /**
     * @brief Retrieves the style's edge size.
     *
     * @return The style's edge size.
     * @since BlackBerry 10.2.0
     */
    EdgeSize::Type edgeSize() const;

    /**
     * @brief Sets the style's edge size.
     *
     * @param newSize The new edge size.
     * @since BlackBerry 10.2.0
     */
    void setEdgeSize( EdgeSize::Type newSize );

    /**
     * @brief Retrieves the style's edge style.
     *
     * @return The style's edge style.
     * @since BlackBerry 10.2.0
     */
    EdgeStyle::Type edgeStyle() const;

    /**
     * @brief Sets the style's edge style.
     *
     * @param newStyle The new edge style.
     * @since BlackBerry 10.2.0
     */
    void setEdgeStyle( EdgeStyle::Type newStyle );

    /**
     * @brief Determines if this style's @c edgeColor() attribute
     * should be used, or if its value should be inherited from other
     * styles.
     *
     * @return @c true if the edge color attribute within this instance
     * is ignored because it is inherited from other styles, @c false
     * otherwise.
     * @since BlackBerry 10.2.0
     */
    bool isEdgeColorInherited() const;

    /**
     * @brief Sets this style's edge color attribute to be inherited.
     *
     * @param inherited @c true if the edge color is inherited, or @c
     * false if the edge color is explicitly set.
     * @since BlackBerry 10.2.0
     */
    void setEdgeColorInherited( bool inherited );

    /**
     * @brief Retrieves the style's edge color.
     *
     * @note If @c isEdgeColorInherited is @c true, this value is
     * undefined.
     * @return The style's edge color.
     * @since BlackBerry 10.2.0
     */
    unsigned int edgeColor() const;

    /**
     * @brief Sets the style's edge color.
     *
     * See the class-level documentation for how colors are defined.
     *
     * @note Setting this attribute will also set @c
     * setEdgeColorInherited to @c false.
     * @param newEdgeColor The new edge color.
     * @since BlackBerry 10.2.0
     */
    void setEdgeColor( unsigned int newEdgeColor );

    /**
     * @brief Determines if this style's @c fillColor() attribute
     * should be used, or if its value should be inherited from other
     * styles.
     *
     * @return @c true if the fill color attribute within this instance
     * is ignored because it is inherited from other styles, @c false
     * otherwise.
     * @since BlackBerry 10.2.0
     */
    bool isFillColorInherited() const;

    /**
     * @brief Sets this style's fill color attribute to be inherited.
     *
     * @param inherited @c true if the fill color is inherited, or @c
     * false if the fill color is explicitly set.
     * @since BlackBerry 10.2.0
     */
    void setFillColorInherited( bool inherited );

    /**
     * @brief Retrieves the style's fill color.
     *
     * @note If @c isFillColorInherited is @c true, this value is
     * undefined.
     * @return The style's fill color.
     * @since BlackBerry 10.2.0
     */
    unsigned int fillColor() const;

    /**
     * @brief Sets the style's fill color.
     *
     * See the class-level documentation for how colors are defined.
     *
     * @note Setting this attribute will also set @c
     * setEdgeColorInherited to @c false.
     * @param newFillColor The new fill color.
     * @since BlackBerry 10.2.0
     */
    void setFillColor( unsigned int newFillColor );

    /**
     * @brief Determines if this style has all of its properties set.
     *
     * @return @c true if all properties have been set, @c false
     * if at least one attribute is set to "inherit".
     * @since BlackBerry 10.2.0
     */
    bool isComplete() const;

    /**
     * @brief Determines if this style has all of its properties set
     * to "inherit".
     *
     * @return @c true if this @c Style has no properties set, @c false
     * otherwise.
     * @since BlackBerry 10.2.0
     */
    bool isEmpty() const;

    /**
     * @brief Superimpose the parameter's attributes over this style's
     * attributes.
     *
     * This operation modifies this instance such that all explicitly
     * stated attributes in the parameter override the local
     * attributes. If the parameter's attribute is set to "inherit",
     * then this class's attribute is unmodified.
     *
     * @param other The instance of @c Style to superimpose on this
     * instance.
     */
    void superimpose( const Style& other );

    /**
     * @brief Subimpose the parameter's attributes under this style's
     * attributes.
     *
     * This operation modifies this instance such that all inherited
     * attributes in this class are replaced with the attributes from
     * the parameter. If this instance's attribute is not set to
     * inherit, then it is unmodified.
     *
     * @param other The instance of @c Style to subimpose on this
     * instance.
     */
    void subimpose( const Style& other );

private:
    /** @cond PRIVATE */
    QSharedDataPointer<StylePrivate> d_ptr;
    /** @endcond */

};

BB_PLATFORM_GEO_EXPORT QDebug operator<<( QDebug dbg, const Style& style );

} // namespace geo
} // namespace platform
} // namespace bb

Q_DECLARE_METATYPE( bb::platform::geo::Style );

#endif // BB_PLATFORM_GEO_STYLE_HPP
