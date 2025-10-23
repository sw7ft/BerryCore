/* Copyright (C) 2011-2013-2013 Research In Motion Limited.  */

#ifndef cascades_color_h
#define cascades_color_h

#include <bb/cascades/bbcascades_global.h>

#include <QtCore/QDebug>

#include <bb/cascades/resources/colorpaint.h>

namespace bb {
    namespace cascades {

    class ColorDataPrivate;

    /*!
     * @brief An implementation of Paint that represents a color with alpha channel.
     *
     * At this point the @c Color objects are immutable.
     *
     * Creating a color in C++:
     * @code
     * Color c1 = Color::fromRGBA(0.5f, 1.0f, 0.2f, 0.8f);
     * Color c2 = Color::fromARGB(0xff996633);
     * @endcode
     *
     * <h2>Predefined color constants</h2>
     *
     * The predefined constants are helpful when you quickly need to specify 
     * a color that stands out (for example, if you are debugging and wondering 
     * how a specific Container is laid out).
     *
     * @image html predefined_colors.png These are the 18 predefined colors.
     *
     * Using predefined color constants in C++:
     * @code
     * Container container = Container::create()
     *              .background(Color::DarkGreen)
     *              .preferredSize(100.0f, 100.0f);
     * @endcode
     * @image html green_container.png This is the result of the example above.
     *
     * <h2>Using Color in QML</h2>
     *
     * Operating Color in QML using the exposed functions in QML only:
     *
     * @code
     * Container {
     *     // specify r, g, b components using hex string
     *     background: Color.create("#ff808080")
     *     preferredWidth: 100
     *     preferredHeight: 50
     * }
     * Container {
     *     // specify r, g, b components using floats
     *     background: Color.create(0.2, 0.4, 0.5)
     *     preferredWidth: 100
     *     preferredHeight: 50
     * }
     * Container {
     *     // specify the color using one of predefined constants
     *     background: Color.Green
     *     preferredWidth: 100
     *     preferredHeight: 50
     * }
     * @endcode
     *
     * @image html three_colors.png This is the result of the example above (assuming an outer container and layout).
     *
     * @code
     * Button {
     *     id: button
     *     text : "Change Color"
     *     color: Color.Red
     *     onClicked : {
     *         if (Color.areEqual(button.color, "#ffff0000")) {
     *             button.color = Color.Black;
     *         } else if (Color.areEqual(button.color, Color.Black)) {
     *             button.resetColor();
     *         } else {
     *             button.color = Color.Red;
     *         }
     *     }
     *     onColorChanged: textArea.text = "onColorChanged - " + Color.toHexString(color) + "\n" + textArea.text
     * }
     * @endcode
     *
     * @xmlonly
     * <apigrouping group="User interface/Resources"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT Color : public ColorPaint {
    public:

        /*! @brief Predefined opaque white color
         *
         * @since BlackBerry 10.0.0
         */
        static const Color White;
        /*! @brief Predefined opaque black color
         *
         * @since BlackBerry 10.0.0
         */
        static const Color Black;
        /*! @brief Predefined opaque red color
         *
         * @since BlackBerry 10.0.0
         */
        static const Color Red;
        /*! @brief Predefined opaque dark red color
         *
         * @since BlackBerry 10.0.0
         */
        static const Color DarkRed;
        /*! @brief Predefined opaque green color
         *
         * @since BlackBerry 10.0.0
         */
        static const Color Green;
        /*! @brief Predefined opaque dark green color
         *
         * @since BlackBerry 10.0.0
         */
        static const Color DarkGreen;
        /*! @brief Predefined opaque blue color
         *
         * @since BlackBerry 10.0.0
         */
        static const Color Blue;
        /*! @brief Predefined opaque dark blue color
         *
         * @since BlackBerry 10.0.0
         */
        static const Color DarkBlue;
        /*! @brief Predefined opaque cyan color
         *
         * @since BlackBerry 10.0.0
         */
        static const Color Cyan;
        /*! @brief Predefined opaque dark cyan color
         *
         * @since BlackBerry 10.0.0
         */
        static const Color DarkCyan;
        /*! @brief Predefined opaque magenta color
         *
         * @since BlackBerry 10.0.0
         */
        static const Color Magenta;
        /*! @brief Predefined opaque dark magenta color
         *
         * @since BlackBerry 10.0.0
         */
        static const Color DarkMagenta;
        /*! @brief Predefined opaque yellow color
         *
         * @since BlackBerry 10.0.0
         */
        static const Color Yellow;
        /*! @brief Predefined opaque dark yellow color
         *
         * @since BlackBerry 10.0.0
         */
        static const Color DarkYellow;
        /*! @brief Predefined opaque gray color
         *
         * @since BlackBerry 10.0.0
         */
        static const Color Gray;
        /*! @brief Predefined opaque dark gray color
         *
         * @since BlackBerry 10.0.0
         */
        static const Color DarkGray;
        /*! @brief Predefined opaque light gray color
         *
         * @since BlackBerry 10.0.0
         */
        static const Color LightGray;
        /*! @brief Predefined transparent color
         *
         * @since BlackBerry 10.0.0
         */
        static const Color Transparent;

        /*! 
         * @brief Default constructor which creates a @c null color. 
         *
         * @see Paint::isNull()
         *
         * @since BlackBerry 10.0.0
         */
        Color();

        /*!
         * @brief Creates a @c Color with specified red, green, blue and 
         * alpha components.
         * 
         * Values must be in the [0.0 - 1.0] range.
         * If alpha is not specified it is assumed to be 1.0f.
         * If components are not in the @c [0.0 - 1.0] range they
         * are clamped to it.
         *
         * @code 
         * // Creates a nice yellow color. Alpha is left out and
         * // thus gets the default value 1.0f.
         * Color c = Color::fromRGBA(1.0f, 0.8f, 0.2f);
         * @endcode
         *
         * @param red The red component.
         * @param green The green component.
         * @param blue The blue component.
         * @param alpha The alpha component (optional, defaults to @c 1.0f).
         *
         * @return The created color object.
         *
         * @since BlackBerry 10.0.0
         */
        static Color fromRGBA(float red, float green, float blue, float alpha = 1.0f);

        /*!
         * @brief Creates a @c Color from the 32 bit value specified.
         *
         * The format is ARGB8888.
         *
         * @code
         * //Creates a nice purple color.
         * Color c = Color::fromARGB(0xff993399);
         * @endcode
         *
         * @param argb The color in ARGB888 format as an integer.
         *
         * @return The created color object.
         *
         * @since BlackBerry 10.0.0
         */
        static Color fromARGB(unsigned int argb);

        /*!
         * @brief A copy constructor which creates a copy of the passed @c Color object.
         *
         * Allows instantiation of a color based on another color object:
         * @code
         * Color c = Color::Green;
         *        or
         * Color c(Color::Green);
         * @endcode
         * 
         * @param orig The color object to create a copy of.
         *
         * @since BlackBerry 10.0.0
         */
        Color(const Color& orig);

        /*!
         * @brief An assignment operator which sets this instance to
         * have the same color and alpha components as the passed one.
         *
         * @param other The color object to create a copy of.
         *
         * @since BlackBerry 10.0.0
         */
        Color& operator=(const Color& other);

        /*!
         * @brief Destructor for Color objects
         *
         * @since BlackBerry 10.0.0
         */
        virtual ~Color();

        /*!
         * @brief An @c == operator for Color objects.
         *
         * The objects are equal if both are of type Color, and have the same color and alpha values.
         *
         * @return @c true if the objects are both of type Color, and have the same color and alpha values, @c false otherwise.
         *
         * @since BlackBerry 10.0.0
         */
        virtual bool operator==(const Paint &other) const;

        /*!
         * @brief A @c != operator for Color objects.
         *
         * This is equivalent to !operator==();
         *
         * @see ColorPaint::operator==()
         *
         * @return @c true if the objects are not equal, @c false otherwise.
         *
         * @since BlackBerry 10.0.0
         */
        virtual bool operator!=(const Paint &other) const;

        /*!
         * @brief Returns the alpha component of this color.
         *
         * @return The alpha component.
         *
         * @since BlackBerry 10.0.0
         */
        float alpha() const;

        /*!
         * @brief Returns the red component of this color.
         *
         * @return The red component.
         *
         * @since BlackBerry 10.0.0
         */
        float red() const;

        /*!
         * @brief Returns the green component of this color.
         *
         * @return The green component.
         *
         * @since BlackBerry 10.0.0
         */
        float green() const;

        /*!
         * @brief Returns the blue component of this color.
         *
         * @return The blue component.
         *
         * @since BlackBerry 10.0.0
         */
        float blue() const;
    
    private:
        /*! \cond PRIVATE */
        Color(float r, float g, float b, float alpha = 1.0f);
        friend class ColorDataPrivate;
        /*! \endcond */
    };
    /* @} */

}
}

Q_DECLARE_METATYPE(bb::cascades::Color)

namespace bb {
    namespace cascades {
        /*!
         * @brief Streams debug output about the color to the QDebug stream object.
         *
         * @code
         * Color c = Color::Red;
         * qDebug() << c;
         * @endcode
         *
         * @param dbg     The QDebug stream.
         * @param color   The color to output debug information about.
         * @return        The QDebug stream.
         */
        BBCASCADES_EXPORT QDebug operator<<(QDebug dbg, const Color &color);
    }
}
#endif	/* cascades_color_h */

