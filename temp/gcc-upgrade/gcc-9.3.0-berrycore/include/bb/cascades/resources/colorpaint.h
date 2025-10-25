/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_colorpaint_h
#define cascades_colorpaint_h

#include <QMetaType>
#include <QSharedDataPointer>

#include <bb/cascades/bbcascades_global.h>

#include <bb/cascades/resources/paint.h>

namespace bb {
    namespace cascades {

    class ColorPaintDataPrivate;

    /*!
     * 
     * @brief A representation of a color.
     *
     * The actual value of the color is not exposed through this API.
     *
     * @note This class currently has a limited purpose. In the future we may want to represent 
     *       "theme colors" rather than colors with specific RGB values, and then this class
     *       provides the appropriate level of abstraction. We already make use of it in SystemDefaults.
     *
     * @see Color
     *
     * @xmlonly
     * <apigrouping group="User interface/Resources"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT ColorPaint : public Paint {
    public:

        /*! 
         * @brief Creates a null ColorPaint object.
         *
         * The resulting paint is a @c null paint until initialized with another 
         * (non-@c null) ColorPaint object.
         * There is no public API for creating a non-@c null ColorPaint directly
         * without using the copy constructor.
         *
         * @code
         * // creates a null paint
         * ColorPaint c;     
         *     ...
         * // Initializes c with the value of label.textColor().
         * c = SystemDefaults::Paints::defaultText();
         * @endcode
         *
         * @see Paint::isNull()
         *
         * @since BlackBerry 10.0.0
         */
        ColorPaint();

        /*!
         * @brief A copy constructor which creates a copy of the passed @c ColorPaint object.
         *
         * Allows instantiation of a ColorPaint based on another ColorPaint object:
         * @code
         * ColorPaint c = SystemDefaults::Paints::defaultText();
         *        or
         * ColorPaint c(SystemDefaults::Paints::defaultText());
         * @endcode
         * 
         *
         * @param orig The ColorPaint object to create a copy of.
         *
         * @since BlackBerry 10.0.0
         */
        ColorPaint(const ColorPaint& orig);

        /*!
         * @brief Assignment operator that makes this color a copy of the passed color.
         *
         * @param other The ColorPaint object to make a copy of.
         *
         * @since BlackBerry 10.0.0
         */
        virtual ColorPaint& operator=(const ColorPaint& other);

        /*!
         * @brief Destructor for ColorPaint objects.
         *
         * @since BlackBerry 10.0.0
         */
        virtual ~ColorPaint();

        /*!
         * @brief An @c == operator for ColorPaint objects.
         *
         * The objects are equal if they stem from the same original object 
         * (for example, if they represent the same SystemDefault color) or
         * if they are both @c null paints.
         *
         * Subclasses can override this criteria in their own implementation.
         * 
         * @see SystemDefaults
         *
         * @return @c true if the objects stem from the same original object, or if both paints are @c null, @c false otherwise.
         *
         * @since BlackBerry 10.0.0
         */
        virtual bool operator==(const Paint &other) const;

        /*!
         * @brief A @c != operator for paint objects.
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

        /*! @cond PRIVATE */
    protected:
        friend class ColorPaintDataPrivate;
        ColorPaint(ColorPaintDataPrivate *data);
        Q_DECL_HIDDEN ColorPaint(QSharedDataPointer<PaintDataPrivate> d);
        /*! @endcond */
    };

    
}
}

Q_DECLARE_METATYPE(bb::cascades::ColorPaint)

#endif	/* cascades_colorpaint_h */
