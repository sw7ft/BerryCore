/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_imagetracker_h
#define cascades_imagetracker_h

#include <QtCore/QObject>
#include <QtCore/QUrl>
#include <QtCore/QSize>
#include <QtCore/QVariant>

#include <bb/cascades/bbcascades_global.h>

#include <bb/cascades/resources/resourcetracker.h>
#include <bb/cascades/resources/image.h>

namespace bb {
    namespace cascades {
        class ImageTrackerPrivate;

        /*!
         * 
         * @brief Provides access to state and size changes associated with an Image.
         *
         * Since @c Image objects are often loaded or modified at runtime, @c %ImageTracker can be used
         * to verify whether they are loaded correctly.
         *
         * Since the Cascades framework is asynchronous in nature, the state and size of an @c %Image may be
         * unknown when the image tracker is created. It's therefore recommended to listen
         * to the @c stateChanged(), @c sizeChanged(), @c heightChanged(), and @c widthChanged() signals.
         *
         * Here's an example in C++ showing how to load an image and display it when it is successfully loaded:
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
         * @xmlonly
         * <qml>
         * <class register="yes"/>
         * </qml>
         * <apigrouping group="User interface/Resources"/>
         * @endxmlonly
         *
         * @since BlackBerry 10.0.0
         */
        class BBCASCADES_EXPORT ImageTracker : public ResourceTracker {
            Q_OBJECT

            /*!
             * @brief A property containing the tracked Image.
             *
             * If no image is being tracked,
             * an empty @c QVariant will be returned. Writing to this property will change the 
             * tracked image and emit the @c imageChanged() and @c imageSourceChanged() signals.
             *
             * @xmlonly
             * <qml>
             * <variant type="bb::cascades::Image"/>
             * </qml>
             * @endxmlonly
             *
             * @since BlackBerry 10.0.0
             */
            Q_PROPERTY(QVariant image READ trackedImage WRITE setImageQml NOTIFY imageChanged FINAL)

            /*!
             * @brief The source of the tracked Image.
             *
             * Writing to this property will change the tracked image
             * and emit the @c imageChanged() and @c imageSourceChanged() signals.
             *
             * If no image is tracked this property will be read as an empty string.
             *
             * @since BlackBerry 10.0.0
             */
            Q_PROPERTY(QUrl imageSource READ imageSource WRITE setImageSource NOTIFY imageSourceChanged FINAL)

            /*!
             * @brief A read only property containing the image width.
             *
             * Writing to this property
             * will cause the @c widthChanged() and @c sizeChanged() signals to be emitted.
             *
             * If the width is unknown a width of 0 is returned.
             *
             * @since BlackBerry 10.0.0
             */
            Q_PROPERTY(int width READ width NOTIFY widthChanged FINAL)

            /*!
             * @brief Read only property holding the image height.
             *
             * Writing to this property
             * will cause the @c heightChanged() and @c sizeChanged() signals to be emitted.
             *
             * If the height is unknown a height of 0 is returned.
             *
             * @since BlackBerry 10.0.0
             */
            Q_PROPERTY(int height READ height NOTIFY heightChanged FINAL)


            /*!
             * @brief Read only property holding the left nine-slice margin of the image.
             *
             * The value is not guaranteed to be valid until the nineSliceMarginsChanged or nineSliceMarginLeftChanged signal is emitted.
             * If the margin is unknown, or if the image is not a nine-slice image a value of 0 is returned.
             *
             * See @c Image for more information about nine-slice margins.
             *
             * @since BlackBerry 10.0.0
             */
            Q_PROPERTY(int nineSliceMarginLeft READ nineSliceMarginLeft NOTIFY nineSliceMarginLeftChanged FINAL)
            /*!
             * @brief Read only property holding the right nine-slice margin of the image.
             *
             * The value is not guaranteed to be valid until the nineSliceMarginsChanged or nineSliceMarginTopChanged signal is emitted.
             * If the margin is unknown, or if the image is not a nine-slice image a value of 0 is returned.
             *
             * See @c Image for more information about nine-slice margins.
             *
             * @since BlackBerry 10.0.0
             */
            Q_PROPERTY(int nineSliceMarginTop READ nineSliceMarginTop NOTIFY nineSliceMarginTopChanged FINAL)
            /*!
             * @brief Read only property holding the top nine-slice margin of the image.
             *
             * The value is not guaranteed to be valid until the nineSliceMarginsChanged or nineSliceMarginTopChanged signal is emitted.
             * If the margin is unknown, or if the image is not a nine-slice image a value of 0 is returned.
             *
             * See @c Image for more information about nine-slice margins.
             *
             * @since BlackBerry 10.0.0
             */
            Q_PROPERTY(int nineSliceMarginRight READ nineSliceMarginRight NOTIFY nineSliceMarginRightChanged FINAL)
            /*!
             * @brief Read only property holding the bottom nine-slice margin of the image.
             *
             * The value is not guaranteed to be valid until the nineSliceMarginsChanged or nineSliceMarginBottomChanged signal is emitted.
             * If the margin is unknown, or if the image is not a nine-slice image a value of 0 is returned.
             *
             * See @c Image for more information about nine-slice margins.
             *
             * @since BlackBerry 10.0.0
             */
            Q_PROPERTY(int  nineSliceMarginBottom READ nineSliceMarginBottom NOTIFY nineSliceMarginBottomChanged FINAL)

        public:
            /*!
             * @brief Constructs an image tracker without a tracked object.
             *
             * @code
             * ImageTracker *imageTracker = new ImageTracker(parent);
             * @endcode
             *
             * @param parent The parent of this object.
             *
             * @since BlackBerry 10.0.0
             */
            explicit ImageTracker(QObject *parent = 0);

            /*!
             * @brief Constructs an image with the tracked image source.
             *
             * @code
             * ImageTracker *imageTracker = new ImageTracker("a_image.png", parent);
             * @endcode
             *
             * @param source The source of this object.
             * @param parent The parent of this object.
             *
             * @since BlackBerry 10.0.0
             */
            explicit ImageTracker(const QUrl& source, QObject *parent = 0);

            virtual ~ImageTracker();

            /*! 
             * @brief Sets an image to be tracked.
             *
             * If an image is already being tracked, the new image will replace the current image 
             * and cause the @c imageSourceChanged() signal to be emitted.
             *
             * @param source The image source to track.
             *
             * @since BlackBerry 10.0.0
             */
            void setImageSource(const QUrl& source);

            /*! 
             * @brief Returns the source of the tracked image.
             *
             * If no image is being tracked an empty @c QString will be returned.
             *
             * @return The source of the tracked image.
             *
             * @since BlackBerry 10.0.0
             */
            QUrl imageSource() const;

            /*! 
             * @brief Sets an image to be tracked.
             *
             * If an image is already being tracked, the new image will replace the current image 
             * and cause the @c imageChanged() signal to be emitted.
             *
             * @param image The image to track.
             *
             * @since BlackBerry 10.0.0
             */
            void setImage(const Image& image);

            /*! 
             * @brief Returns the tracked image.
             *
             * If no image is tracked a null image will be returned.
             *
             * @return The tracked image, or a null image if no image is being tracked.
             *
             * @since BlackBerry 10.0.0
             */
            Image image() const;

            /*!
            * @brief Returns the width in pixels.
            *
            * @return The width in pixels if available, otherwise 0.
             *
             * @since BlackBerry 10.0.0
            */
            int width() const;

           /*!
            * @brief Returns the height in pixels.
            *
            * @return The height in pixels if available, otherwise 0.
            *
            * @since BlackBerry 10.0.0
            */
            int height() const;

            /*!
             * @brief Returns the left nine-slice margin of the current image.
             *
             * If the image is empty, or if the image is not a nine-slice image, all nine-slice margins are 0.
             *
             * @return The left nine-slice margin of the current image, or 0 if the image is empty, or not a nine-slice image.
             *
             * @since BlackBerry 10.0.0
             */
            int nineSliceMarginLeft() const;
            /*!
             * @brief Returns the right nine-slice margin of the current image.
             *
             * If the image is empty, or if the image is not a nine-slice image, all nine-slice margins are 0.
             *
             * @return The right nine-slice margin of the current image, or 0 if the image is empty, or not a nine-slice image.
             *
             * @since BlackBerry 10.0.0
             */
            int nineSliceMarginRight() const;
            /*!
             * @brief Returns the top nine-slice margin of the current image.
             *
             * If the image is empty, or if the image is not a nine-slice image, all nine-slice margins are 0.
             *
             * @return The top nine-slice margin of the current image, or 0 if the image is empty, or not a nine-slice image.
             *
             * @since BlackBerry 10.0.0
             */
            int nineSliceMarginTop() const;
            /*!
             * @brief Returns the bottom nine-slice margin of the current image.
             *
             * If the image is empty, or if the image is not a nine-slice image, all nine-slice margins are 0.
             *
             * @return The bottom nine-slice margin of the current image, or 0 if the image is empty, or not a nine-slice image.
             *
             * @since BlackBerry 10.0.0
             */
            int nineSliceMarginBottom() const;

        Q_SIGNALS:
            /*!
             * @brief Emitted when the tracked image has changed.
             *
             * @param image @c QVariant containing the new Image.
             *
             * @since BlackBerry 10.0.0
             */
            void imageChanged(const QVariant& image);

            /*!
             * @brief Emitted when the tracked source has changed.
             *
             * @param source New image source.
             *
             * @since BlackBerry 10.0.0
             */
            void imageSourceChanged(const QUrl& source);

            /*!
             * @brief Emitted when the size has changed.
             *
             * For example, this will happen when the tracked image is changed.
             *
             * @param width The width of the loaded image in pixels.
             * @param height The height of the loaded image in pixels.
             *
             * @since BlackBerry 10.0.0
             */
            void sizeChanged(int width, int height);

            /*!
             * @brief Emitted when the width has changed.
             *
             * For example, this will happen when the tracked image is changed.
             *
             * @param width The width of the loaded image in pixels.
             *
             * @since BlackBerry 10.0.0
             */
            void widthChanged(int width);

            /*!
             * @brief Emitted when the height has changed.
             *
             * For example, this will happen when the tracked image is changed.
             *
             * @param height The height of the loaded image in pixels.
             *
             * @since BlackBerry 10.0.0
             */
            void heightChanged(int height);


            /*!
             * @brief Emitted when the nine-slice margins have been changed
             *
             * This will for example happen when the tracked image is changed.
             *
             * @param left The left nine-slice margin of the loaded image in pixels
             * @param right The right nine-slice margin of the loaded image in pixels
             * @param top The top nine-slice margin of the loaded image in pixels
             * @param bottom The bottom nine-slice margin of the loaded image in pixels
             *
             * @since BlackBerry 10.0.0
             */
            void nineSliceMarginsChanged(int left, int right, int top, int bottom);


            /*!
             * @brief Emitted when the left nine-slice margins has changed
             *
             * This will for example happen when the tracked image is changed.
             *
             * @param margin The left nine-slice margin of the loaded image in pixels
             *
             * @since BlackBerry 10.0.0
             */
            void nineSliceMarginLeftChanged(int margin);
            /*!
             * @brief Emitted when the top nine-slice margins has changed
             *
             * This will for example happen when the tracked image is changed.
             *
             * @param margin The top nine-slice margin of the loaded image in pixels
             *
             * @since BlackBerry 10.0.0
             */
            void nineSliceMarginTopChanged(int margin);
            /*!
             * @brief Emitted when the right nine-slice margins has changed
             *
             * This will for example happen when the tracked image is changed.
             *
             * @param margin The right nine-slice margin of the loaded image in pixels
             *
             * @since BlackBerry 10.0.0
             */
            void nineSliceMarginRightChanged(int margin);
            /*!
             * @brief Emitted when the bottom nine-slice margins has changed
             *
             * This will for example happen when the tracked image is changed.
             *
             * @param margin The bottom nine-slice margin of the loaded image in pixels
             *
             * @since BlackBerry 10.0.0
             */
            void nineSliceMarginBottomChanged(int margin);


        private:
            /*! \cond PRIVATE */

            /*! 
             * @brief Sets an image to be tracked by a QVariant.
             *
             * If an image is already being tracked, the new image will replace the current image 
             * and cause the signal @c trackedImageChanged() signal to be emitted.
             *
             * This function accepts both images and @c QUrl.
             *
             * @param image The image to track.
             */
            void setImageQml(const QVariant &image);

            /*!
             * @brief Returns the tracked image as a QVariant.
             *
             * @return The tracked image if available, otherwise an empty @c QVariant.
             */
            QVariant trackedImage() const;

            Q_DECLARE_PRIVATE(ImageTracker);
            Q_DISABLE_COPY(ImageTracker);
            /*! \endcond */
        };
        
    }
}

QML_DECLARE_TYPE(bb::cascades::ImageTracker);

#endif // cascades_imagetracker_h
