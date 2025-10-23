/* Copyright (C) 2011-2013-2013 Research In Motion Limited.  */

#ifndef cascades_image_h
#define cascades_image_h

#include <bb/cascades/bbcascades_global.h>

#include <QtCore/QString>
#include <QtCore/QUrl>
#include <QDebug>

#include <bb/ImageData>

#include <bb/cascades/resources/resource.h>

namespace bb {
    namespace cascades {

        class ImagePrivate;

        /*!
         * @brief An image resource, the source of which might not be known.
         *
         * Images can come from a number of different sources, the most common of
         * which is as an asset that is packaged with the application. This is the
         * type of image that is commonly used in the user interface.
         *
         * One of the benefits of packaging an image with the application is that it allows the tool
         * to verify the images and optimize them for the devices they are targeting. Because they
         * are packaged with the application, it should be assumed that they are instantly available,
         * and should never fail to load. If an incorrect @c name is provided when an asset is created,
         * an null image is returned.
         *
         * As long as the image is placed in the assets folder in your
         * project, you can refer to it using a relative path to the assets directory (@c asset:///)
         * followed by the file name. For example:
         *
         * @code
         * Image imageAsset = Image(QUrl("asset:///myasset.png"));
         * @endcode
         *
         * The absolute path to the assets directory is 
         *
         * @code
         * file:///<em>app_working_directory</em>/app/native
         * @endcoe
         *
         * <h2>Images outside the assets directory</h2>
         *
         * Each application has access to its own working directory in the file system.
         * The working directory is where application is started, and is also known as the
         * "current directory" and the "sandbox."
         *
         * Within the application working directory, there are a number of folders that
         * your application has access to. The @c data folder (otherwise known as the
         * "home" directory) contains your application's private data. Here's an example
         * of how to use a path relative to the application working directory to load an
         * image from the home directory:
         *
         * @code
         * Image image = Image(QUrl("file://" + QDir::homePath() + "/image2.png"));
         * @endcode
         *
         * Your application can also access folders outside the application working directory, in
         * a shared folder. Here's an example of how to load an image from the shared/camera folder
         * (provided that you set the appropriate permissions for it in your bar-descriptor.xml file).
         * In this example, an absolute path is used:
         *
         * @code
         * Image image = Image(QUrl("file:///accounts/1000/shared/camera/camera0001.jpg"));
         * @endcode
         *
         * <h2>Images in QML</h2>
         *
         * Here are some examples of how to use an @c %Image in QML:
         *
         * @code
         * ImageView {
         *     imageSource: "asset:///myAsset.png"
         * }
         * 
         * Button {
         *     imageSource: "images/button.png"
         * }
         *    
         * ImageTracker {
         *     id: anImage
         *     imageSource: "asset:///myAsset.png"
         * }
         *    
         * ImageView {
         *     image: anImage.image
         * }
         * @endcode
         *
         * <h2>Loading an image</h2>
         *
         * When dealing with images that are not assets (i.e. not packaged with the application),
         * it should be assumed that the image might take a considerable time to load, or may
         * not load at all. To account for this, an @c %Image goes through a 
         * series of states indicating when the image is loaded and if 
         * an error occurred. The state of an image and information about its size are accessible through 
         * @c ImageTracker, which encapsulates the asynchronous parts of the Image.
         *
         * Here's an example showing how to load an image and display it when it is
         * successfully loaded, in C++:
         *
         *
         * @code
         * void MyApp::setup() {
         *     mImageView = new ImageView();
         *     mImageTracker = new ImageTracker(QUrl("assets/image.png"));
         *
         *     bool result = connect(mImageTracker,
         *         SIGNAL(stateChanged(bb::cascades::ResourceState::Type)),
         *         this,
         *         SLOT(onStateChanged(bb::cascades::ResourceState::Type)));
         *
         *     Q_ASSERT(result);
         *     Q_UNUSED(result);
         *   
         *     // ...
         * }
         *
         * void MyApp::onStateChanged(ResourceState::Type state)
         * {
         *     if(state == ResourceState::Loaded)
         *     {
         *         mImageView->setImage(mImageTracker->image());
         *     }
         * }
         * @endcode
         *
         * Here's an example in QML showing how to load an image and display it when it is successfully loaded:
         *         
         * @code
         * ImageView {
         *     id: myImageView
         *     attachedObjects: [
         *         ImageTracker {
         *             id: tracker
         *             imageSource: "images/image.png"
         *       
         *             onStateChanged: { 
         *                 if (state == ResourceState.Loaded)
         *                 {
         *                     myImageView.image = tracker.image
         *                 }
         *             }
         *         }
         *     ]
         * }
         * @endcode
         *
         * <h2>Creating images from data</h2>
         *
         * It's also possible to create images from raw pixel data using @c ImageData::fromPixels().
         * In order to create the image from a set of data, all you need to specify is the source of the data,
         * the format of the pixel data (as specified by @c PixelFormat), the width and height of the image, and
         * the number of bytes per line in the data source.
         *
         * Here's an example of how to create an image from a random set of pixel data. The pixel format used is RGBX.
         *
         * @image html image_from_data.png
         *
         * @code
         * int data[8][8];
         * for (int y=0;y<8;y++) {
         *     for (int x=0;x<8;x++) {
         *         data[x][y] = rand();
         *     }
         * }
         * Image m_image = bb::ImageData::fromPixels((
         *         const unsigned char*)data, 
         *         bb::PixelFormat::RGBX, 
         *         8, 8, 8*4);
         * @endcode
         *
         * <h2>Nine-slice scaling</h2>
         *
         * @c Image resources can be specified to have nine-slice margins, which can be retrieved using the nineSliceMargin*() methods. 
         * A nine-sliced image will, when displayed, be stretched according to nine-slice rules instead of being simply scaled. 
         *
         * @image html what-is-nine-slice_animation.gif Animated example of a nine-slice image
         *
         * In the animated image above,
         * @li the four corners (1,3,7,9) are not scaled, 
         * @li the left and right 'margins' (4,6) are scaled only vertically (i.e., their width is not touched), 
         * @li and the top and bottom 'margins' (2,8) are scaled only horizontally (i.e., their height is not touched).
         * The center area (5) is the only one that's scaled both horizontally and vertically.
         *
         * To specify that the image is nine-sliced place a metadata file with the same name but ".amd" extension next to 
         * the image (i.e., in the same directory) and specify the nine-slices with the following format: 
         * @code
         * sliceMargins: l r t b
         * @endcode
         * Where "l" is the left slice margin, "r" is the right margin, "t" is the top margin and "b" is the bottom margin. 
         *
         * With reference to the animated image above:
         * @li  the 'l' parameter is the horizontal size of the areas 1,4, and 7
         * @li  the 'r' parameter is the horizontal size of the areas 3,6, and 9
         * @li  the 't' parameter is the vertical size of the areas 1,2, and 3 
         * @li  the 'b' parameter is the vertical size of the areas 7,8, and 9 
         *
         * For example, if there's a nine-sliced image called "nine_sliced_background.png", the metadata file must be 
         * called "nine_sliced_background.amd" and placed in the same directory as the image. The contents of the
         * file might look something like this depending on the nine-slice margin values for your image:
         * 
         * @code
         * #RimCascadesAssetMetaData version=1.0
         * source: "nine_sliced_background.png"
         * sliceMargins: 63 62 51 123
         * @endcode
         *
         * In your application, you simply reference the .amd file instead of the image and whenever it's scaled
         * the image will maintain its edges.
         *
         * @code
         * ImageView {
         *     imageSource: "asset:///nine_sliced_background.amd"
         *     preferredWidth: 500
         *     preferredHeight: 500
         * }
         * @endcode
         *
         * <h2>Tiling images</h2>
         *
         * Using the @c ImagePaint (C++) and @c ImagePaintDefinition (QML) classes you can use images
         * as background fill for a container. The @c RepeatPattern class determines how/if the image
         * is tiled on the container.
         *
         * In order for an image to be tileable, it must have the "repeatable: true|false" property set in the asset metadata
         * file. This is the same .amd file that can contain nine-slicing attributes, however
         * the tiling of nine-sliced images is not currently supported.
         *
         * <h2>Image colorization</h2>
         *
         * As of 10.3, Cascades supports image colorization. One method of colorization allows the image node to adopt
         * colors from the current theme. With some images, like those used in action items, this happens by default.
         * You can turn on and turn off this behavior in the .amd file for this image by using the @c type property.
         * The version of the .amd file must be 1.1 for this feature to work.
         *
         * Currently, the @c type property supports three different values:
         * -@c unspecified: This is the default value. The interpretation varies from case to case.
         * For most images it's interpreted as @c normal, but in some contexts (for example, @c ActionItem),
         * it's interpreted as @c template and is therefore colorized.
         * -@c normal: The image will always be presented as is with no colorization.
         * -@c template: The image is considered suitable for colorization (should be a white/grayscale image with alpha channel).
         *
         * @code
         * #RimCascadesAssetMetaData version=1.1
         * source: "my_icon_image.png"
         * type: template
         * @endcode
         *
         * Another method of colorization allows you to set a color filter directly on a @c ImageView.
         * This form of colorization can only occur if the value of @c type in the image's .amd file
         * is not set to template. For more information, see @c ImageView::filterColor.
         *
         * In the metadata file, lines beginning with '#' are ignored, and can be used for comments.
         * The exception is the first line with version info.
         *
         * @xmlonly
         * <apigrouping group="User interface/Resources"/>
         * @endxmlonly
         *
         * @since BlackBerry 10.0.0
         */
        class BBCASCADES_EXPORT Image : public Resource {
        public:
            /*!
             * @brief Constructs a null image.
             *
             * @code
             * Image image();
             * @endcode
             *
             * @since BlackBerry 10.0.0
             */
            Image();

            /*!
             * @brief Constructs an image from the given URL.
             *
             * @code
             * Image image(QUrl("images/a_image.png"));
             * @endcode
             *
             * Since it is not known at the time of creation whether the image will load
             * successfully, the creation process cannot fail. In other words, this constructor
             * will always create a non-null image. To check for errors, use @c ImageTracker.
             *
             * If the image is loaded from the asset collection it will fail at once and return an
             * null image if the asset is not found.
             *
             * Here's an example of how to load an image from the asset collection.
             * @code
             * Image img(QUrl("asset:///myAsset.png"));
             * @endcode
             *
             * @param source The relative path to the image.
             *
             * @since BlackBerry 10.0.0
             */
            Image(const QUrl& source);

            /*!
             * @brief Constructs an image from the given URL.
             *
             * @code
             * Image image("images/a_image.png");
             * @endcode
             *
             * Since it is not known at the time of creation whether the image will load
             * successfully, the creation process cannot fail. In other words, this constructor
             * will always create a non-null image. To check for errors, use @c ImageTracker.
             *
             * If the image is loaded from the asset collection it will fail at once and return an
             * null image if the asset is not found.
             *
             * Here's an example of how to load an image from the asset collection.
             * @code
             * Image img("asset:///myAsset.png");
             * @endcode
             *
             * @param source The relative path to the image.
             *
             * @since BlackBerry 10.0.0
             */
            Image(const char* source);

            /*!
             * @brief Constructs a copy of another @c %Image.
             *
             * @code
             * Image a("images/a_image.png");
             * Image b(a);
             * @endcode
             *
             * @param other The Image to be copied.
             *
             * @since BlackBerry 10.0.0
             */
            Image(const Image &other);

            /*!
             * @brief Creates an image based on already decoded pixel data.
             *
             * The caller is responsible for creating the @c bb::ImageData instance.
             *
             * Only bb::PixelFormat::RGBA_Premultiplied and bb::PixelFormat::RGBX formats
             * are supported at the moment. If ImageData with a different format is
             * passed it will be ignored and a warning will be printed out.
             *
             * @note Once an Image is created from a particular instance of bb::ImageData 
             * updating the data contained by bb::ImageData will have no effect
             * on the contents of the @c Image since the data is copied on creation.
             *
             * @c ImageData based images are different from other images in that they don't
             * report state changes and they are not trackable through @c ImageTracker.
             * They are also not available from QML.
             *
             * @code
             * #include <bb/ImageData>
             *
             * // create ImageData from pixel data stored in pBuffer
             * bb::ImageData imageData =
             *     bb::ImageData::fromPixels(pBuffer, 
             *                               bb::PixelFormat::RGBA_Premultiplied,
             *                               100, 100, 400);
             * // pBuffer can be freed now if needed as ImageData::fromPixels made a copy
             *
             * // create an Image from the data
             * Image image( imageData );
             *
             * // allocate pixel data by creating an ImageData, modify and then create an image
             * bb::ImageData imageData1(bb::PixelFormat::RGBX, 100, 100);
             * unsigned char* pixels = imageData1.pixels();
             * // modify the pixels
             *
             * // now create an image from the data
             * Image image( imageData1 );
             *
             * // imageData, imageData1 are implicitly shared, data will be freed when
             * // there are no more references to it
             * @endcode
             * 
             * @param imageData The ImageData object to construct the image from.
             *
             * @see @c bb::ImageData
             *
             * @since BlackBerry 10.0.0
             */
            Image(const ImageData& imageData);

            /*!
             * @brief Creates an image based on a buffer containing encoded image data
             *
             * The user provided QByteArray should contain the raw data of a png, jpeg or gif file.
             *
             * @note Once an Image is created from a particular QByteArray, updating the data contained 
             * by the QByteArray will have no effect on the contents of the @c Image since the data is 
             * copied on creation.
             *
             * QByteArray based images are different from other images in that they don't
             * report state changes and they are not trackable through @c ImageTracker.
             * They are also not available from QML.
             *
             * @code
             * 
             * // read file into QByteArray
             * QFile file("myfile.png");
             * file.open(QIODevice::ReadOnly);
             * QByteArray data = file.readAll();
             * 
             * Image image(data);
             * @endcode
             * 
             * @param encodedImageData The encoded image data to construct the image from.
             *
             * @since BlackBerry 10.0.0
             */
            Image(const QByteArray &encodedImageData);

            virtual ~Image();

            /*!
             * @brief Assigns another @c %Image to this @c %Image.
             *
             * @param other The image to be assigned to this image.
             * @return A reference to the image.
             *
             * @since BlackBerry 10.0.0
             */
            Image& operator=(const Image &other);

            /*!
             * @brief Returns the image source.
             *
             * @return The image source.
             *
             * @since BlackBerry 10.0.0
             */
            QUrl source() const;

            /*!
             * @brief Returns the left nine-slice margin of the current image.
             *
             * If the image is empty, or if the image is not a nine-slice image, all nine-slice margins are @c 0.
             *
             * @return The left nine-slice margin of the current image, or @c 0 if the image is empty, or not a nine-slice image.
             *
             * @since BlackBerry 10.0.0
             */
            int nineSliceMarginLeft() const;
            /*!
             * @brief Returns the right nine-slice margin of the current image.
             *
             * If the image is empty, or if the image is not a nine-slice image, all nine-slice margins are 0.
             *
             * @return The right nine-slice margin of the current image, or @c 0 if the image is empty, or not a nine-slice image.
             *
             * @since BlackBerry 10.0.0
             */
            int nineSliceMarginRight() const;
            /*!
             * @brief Returns the top nine-slice margin of the current image.
             *
             * If the image is empty, or if the image is not a nine-slice image, all nine-slice margins are 0.
             *
             * @return The top nine-slice margin of the current image, or @c 0 if the image is empty, or not a nine-slice image.
             *
             *
             * @since BlackBerry 10.0.0
             */
            int nineSliceMarginTop() const;
            /*!
             * @brief Returns the bottom nine-slice margin of the current image.
             *
             * If the image is empty, or if the image is not a nine-slice image, all nine-slice margins are @c 0.
             *
             * @return The bottom nine-slice margin of the current image, or @c 0 if the image is empty, or not a nine-slice image.
             *
             * @since BlackBerry 10.0.0
             */
            int nineSliceMarginBottom() const;

        protected:

            /*! \cond PRIVATE */
            Q_DECLARE_PRIVATE(Image) 
            /*! \endcond */
        };
        
        /*!
         * @brief Streams debug output about the image to the QDebug stream object.
         *
         * @param dbg     The QDebug stream.
         * @param image   The image to output debug information about.
         * @return        The QDebug stream.
         */
        BBCASCADES_EXPORT QDebug operator<<(QDebug dbg, const Image &image);
    }
}

Q_DECLARE_METATYPE(bb::cascades::Image);

#endif    // cascades_image_h


