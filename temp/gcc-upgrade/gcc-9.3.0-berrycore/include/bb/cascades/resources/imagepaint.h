/* Copyright (C) 2012-2013-2013 Research In Motion Limited.  */

#ifndef cascades_imagepaint_h
#define cascades_imagepaint_h

#include <bb/cascades/bbcascades_global.h>

#include <QMetaType>
#include <QDebug>

#include <bb/cascades/resources/paint.h>
#include <bb/cascades/resources/repeatpattern.h>

namespace bb {
    namespace cascades {

    class ImagePaintDataPrivate;
    class Image;    

    /*!
     * 
     * @brief A representation of a image that can be used as a fill.
     *
     * @c %ImagePaint is typically used for tileable images. A tileable
     * image is one that can be repeated as a pattern over a surface.
     *
     * If set as a background of a @c Container the paint will fill the area
     * occupied by the container. Depending on the specified repeat pattern
     * the image will either be repeated in particular direction or stretched
     * to fill the available area. The anchor point of the repeat is the top left corner
     * of the fillable area.
     * 
     * This class uses @c RepeatPattern to specify how and if the image should
     * be repeated over the surface. In order to construct ImagePaint objects
     * from QML, the @c ImagePaintDefinition class is available.
     *
     * The provided image must have a width and height that
     * is a power of two in order to be tileable (for example, 
     * 4x4, 8x8, 16x16, 32x32, 64x64, 128x128, 256x256, 128x64, 32x16). It also needs to
     * have the "repeatable: true|false" property set in the asset metadata
     * file. The asset metadata file is an .amd file with the same name as
     * the image itself. This file can also contain nine-slicing attributes, however
     * the tiling of nine-sliced images is not currently supported.
     *
     * Here's an example of an .amd file called tiled_image.amd that has the repeatable property set to true.
     *
     * @code
     * #RimCascadesAssetMetaData version=1.0
     * source: "tiled_image.png"
     * repeatable: true
     * @endcode
     *
     * When referencing the image from your application, you reference the .amd file
     * instead of the image itself. Here's an example of how to tile the background image
     * in a container in C++:
     *
     * @code
     * pContainer->setBackground(ImagePaint("asset:///tiled_image.amd", RepeatPattern::XY));
     * @endcode
     * 
     * <h2>Tiling images using ImageData</h2>
     *
     * You can also tile images defined by the @c ImageData class:
     *
     * @code
     * #include <bb/ImageData>
     *
     * int w = 0x33333333;
     * int b = 0000000000;
     * int data[8][8] =
     *     { { w, b, b, b, b, b, b, w },
     *       { b, w, b, b, b, b, w, b },
     *       { b, b, w, w, w, w, b, b },
     *       { b, b, w, b, b, w, b, b },
     *       { b, b, w, b, b, w, b, b },
     *       { b, b, w, w, w, w, b, b },
     *       { b, w, b, b, b, b, w, b },
     *       { w, b, b, b, b, b, b, w } };
     * 
     * Image image(bb::ImageData::fromPixels((const unsigned char*)data, bb::PixelFormat::RGBX, 8, 8, 8*4));
     * ImagePaint paint(image, RepeatPattern::XY);
     * pContainer->setBackground(paint);
     * @endcode
     * 
     * <h2>Tiling images in QML</h2>
     *
     * In order to tile images in QML, you must use the associated definition class @c ImagePaintDefinition.
     * Here's an example of how to use @c %ImagePaintDefinition to add a background image to a container in QML:
     *
     * @code 
     * Container {
     *     id: rootContainer
     *     background: back.imagePaint
     *     attachedObjects: [
     *         ImagePaintDefinition {
     *             id: back
     *             repeatPattern: RepeatPattern.XY
     *             imageSource: "asset:///container/tiled/core16x16.amd"
     *         }
     *     ]
     * }   
     * @endcode
     * 
     * @see @c Image, @c ImagePaintDefinition, @c bb::ImageData
     *
     * @xmlonly
     * <apigrouping group="User interface/Resources"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT ImagePaint : public Paint
    {
    public:
        
        /*! 
         * @brief Default constructor which creates a @c null image and
         * RepeatPattern::Fill repeat pattern.
         *
         * @since BlackBerry 10.0.0
         */
        ImagePaint();

        /*! 
         * @brief Creates an @c ImagePaint object using a @c QUrl pointing to
         * a valid (power of two-sized) image.
         *
         * @param url The URL to load the image from.
         * @param pattern The repeating pattern of the image. Requires certain
         *                properties of the @c %ImagePaint to be set.
         *
         * @since BlackBerry 10.0.0
         */
        explicit ImagePaint(const QUrl& url,
                            RepeatPattern::Type pattern = RepeatPattern::Fill);
        
        /*! 
         * @brief Creates an ImagePaint object using an @c Image as painting source.
         *
         * @param image The image to use as source for the @c %ImagePaint.
         * @param pattern The repeating pattern of the image. Requires certain
         *                properties of the @c %ImagePaint to be set
         *
         * @see ImagePaint
         *
         * @since BlackBerry 10.0.0
         */
        explicit ImagePaint(const Image& image,
                            RepeatPattern::Type pattern = RepeatPattern::Fill);
        
        /*! 
         * @brief Creates an ImagePaint object using an @c Image as the source.
         * 
         * @brief A copy constructor which creates a copy of the passed @c %ImagePaint object.
         *
         * @param orig ImagePaint object to create a copy of.
         *
         * @since BlackBerry 10.0.0
         */
        ImagePaint(const ImagePaint& orig);

        /*!
         * @brief Assignment operator that makes this paint a copy of the passed paint.
         *
         * @param other The @c ImagePaint object to make a copy of.
         *
         * @since BlackBerry 10.0.0
         */
        virtual ImagePaint& operator=(const ImagePaint& other);

        /*!
         * @brief Destructor for @c ImagePaint objects.
         *
         * @since BlackBerry 10.0.0
         */
        virtual ~ImagePaint();

        /*!
         * @brief An @c == operator for ImagePaint objects.
         *
         * The objects are equal if they stem from the same original object 
         * or if they are both @c null paints.
         *
         * Subclasses can override these criteria in their own implementation.
         * 
         * @see SystemDefaults
         *
         * @return @c true if the objects stem from the same original object, or
         * if both paints are @c null, @c false otherwise.
         *
         * @since BlackBerry 10.0.0
         */
        virtual bool operator==(const Paint &other) const;

        /*!
         * @brief A @c != operator for paint objects
         *
         * This is equivalent to !operator==();
         *
         * @see ImagePaint::operator==()
         *
         * @return @c true if the objects are not equal, @c false otherwise.
         *
         * @since BlackBerry 10.0.0
         */
        virtual bool operator!=(const Paint &other) const;
        
        /*!
         * @brief Returns the repeat pattern of this @c %ImagePaint.
         *
         * @return The @c %RepeatPattern  of this paint.
         *
         * @since BlackBerry 10.0.0
         */
        RepeatPattern::Type repeatPattern() const;

        /*!
         * @brief Returns the image of this @c %ImagePaint.
         *
         * @return The @c %Image of this paint.
         *
         * @since BlackBerry 10.0.0
         */
        Image image() const;
    };

    /*!
      * @brief Streams debug output about the paint to the QDebug stream object.
      *
      * @code
      * ImagePaint ip(Image("core16x16"), RepeatPattern::XY);
      * qDebug() << ip;
      * @endcode
      *
      * @param dbg     The QDebug stream.
      * @param paint   The paint to output debug information about.
      * @return        The QDebug stream.
      */
    BBCASCADES_EXPORT QDebug operator<<(QDebug dbg, const ImagePaint &paint);

    }
}

Q_DECLARE_METATYPE(bb::cascades::ImagePaint)

#endif	/* cascades_imagepaint_h */
