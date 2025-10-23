/* Copyright (C) 2012-2013-2013 Research In Motion Limited.  */

#ifndef cascades_repeatpattern_h
#define cascades_repeatpattern_h

#include <bb/cascades/bbcascades_global.h>

#include <QObject>
#include <QDebug>

namespace bb {
    namespace cascades {

        /*!
         * @brief Specifies how and if an image should be repeated within a container.
         *
         * The @c %RepeatPattern::Type is used by @c ImagePaint and @c ImagePaintDefinition to specify if and how the image
         * should be repeated over the filled area.
         *
         * The possible values are
         * - Fill: stretches the image to fit assigned area without preserveing image's aspect ratio
         * - X: image is repeated along X-axis and is stretched in the Y-axis direction
         * - Y: image is repeated along Y-axis and is stretched in the X-axis direction
         * - XY: image is repeated along X-axis and Y-axis
         *
         * If repeat is set and the area dimensions are not exact multiples of the source
         * image dimensions, the final images in the repeat sequence will be
         * cut off in order to preserve the area.
         *
         * The provided image must also have a width and height that
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
         * @xmlonly
         * <apigrouping group="User interface/Resources"/>
         * @endxmlonly
         *
         * @since BlackBerry 10.0.0
         */
        class BBCASCADES_EXPORT RepeatPattern {
            Q_GADGET
            Q_ENUMS(Type)
        public:
            /*!
             * @brief The different repeat methods.
             *
             * @since BlackBerry 10.0.0
             */
            enum Type {
                /*! @brief Image is stretched to fill the area without preserving aspect ratio.
                 *
                 * @since BlackBerry 10.0.0
                 */
                Fill = 0x0,
                /*! @brief Image is repeated along the X-axis, stretched along Y-axis.
                 *
                 * @since BlackBerry 10.0.0
                 */
                X = 0x1,
                /*! @brief Image is repeated along the Y-axis, stretched along X-axis
                 *
                 * @since BlackBerry 10.0.0
                 */
                Y = 0x2,
                /*! @brief Image is repeated along both the X- and Y-axis.
                 *
                 *
                 * @since BlackBerry 10.0.0
                 */
                XY = 0x3,
            };
        private:
            /*! \cond PRIVATE */
            RepeatPattern();
            ~RepeatPattern();
            /*! \endcond */
        };

        /*!
         * @brief Streams debug output about the pattern to the QDebug stream object.
         *
         * @param dbg     The QDebug stream.
         * @param pattern The pattern to output debug information about.
         * @return        The QDebug stream.
         */
        BBCASCADES_EXPORT QDebug operator<<(QDebug dbg, RepeatPattern::Type pattern);

    } // cascades

} // bb

#endif /* cascades_repeatpattern_h */
