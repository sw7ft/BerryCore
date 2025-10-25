/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_imageview_h
#define cascades_imageview_h

#include <QtCore/QString>

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/controls/control.h>
#include <bb/cascades/resources/image.h>
#include <bb/cascades/controls/scalingmethod.h>
#include <bb/cascades/controls/imageviewloadeffect.h>
#include <bb/cascades/resources/colorpaint.h>

namespace bb {
    namespace cascades {
        class Container;
        class ImageViewPrivate;

        /*!
         *
         * @brief A visual control that is used for displaying images.
         *
         * @image html image_carl_larsson_1898.png
         *
         * The image itself can be set using either an @c Image object or a path
         * specifying the location of an image. A @c ScalingMethod can be set on
         * the @c %ImageView to specify how or if the image should be scaled in any way to
         * fit the dimensions of the image view.
         *
         * Here's how to create an image view in QML:
         *
         * @snippet tad/examples/controls/imageview/assets/main.qml imageview_qml1
         *
         * And here's how to do so in C++:
         *
         * @snippet tad/examples/controls/imageview/src/ImageViewExamples.cpp imageview1
         *
         * If the image is not already loaded, an implicit animation will be triggered as soon as the image
         * is ready to be displayed, causing the image to fade in.
         *
         * The size of the %ImageView behaves as follows:
         * - By default, the width and height of the ImageView are equal to the dimensions (in pixels)
         * of the displayed image.
         * - The width is adjustable using the @c Control::preferredWidth, @c Control::minWidth and
         * @c Control::maxWidth properties.
         * - The height is adjustable using the @c Control::preferredHeight, @c Control::minHeight
         * and @c Control::maxHeight and properties.
         * - The scaling method can be adjusted using the @c #scalingMethod property. The scaling method
         * determines how an image is rescaled when the width and height are adjusted.
         *
         * Due to memory constraints, there are limits on the pixel size
         * of an image that's displayed in an @c ImageView. This limit changes
         * from device to device and can also be affected by other
         * operations that are using the GPU. If you are loading a large image,
         * you should track how it's loading using @c ImageTracker. You can
         * monitor the state of the image that's being loaded by listening to
         * the @c stateChanged() signal. If the image fails to load due to
         * memory issues, you should load a smaller image.
         *
         * @see ImageTracker
         *
         * @xmlonly
         * <apigrouping group="User interface/Core controls"/>
         * @endxmlonly
         *
         * @since BlackBerry 10.0.0
         */
        class BBCASCADES_EXPORT ImageView : public Control {
        private:
            Q_OBJECT

            /*!
             * @brief The image set on the @c %ImageView.
             *
             * If no image is set, an empty @c QVariant will be returned.
             * When changing image the @c imageChanged() signal will be emitted.
             *
             * @xmlonly
             * <qml>
             * <variant type="bb::cascades::Image"/>
             * </qml>
             * @endxmlonly
             *
             * @since BlackBerry 10.0.0
             */
            Q_PROPERTY(QVariant image READ imageQml WRITE setImageQml
                      RESET resetImage NOTIFY imageChanged FINAL)


            /*!
             * @brief The image set on the %ImageView.
             *
             * If no image is set, an empty @c QVariant will be returned.
             * When changing the image source the @c imageSourceChanged() signal will be emitted.
             *
             *
             * @since BlackBerry 10.0.0
             */
            Q_PROPERTY(QUrl imageSource READ imageSource WRITE setImageSource
                      RESET resetImageSource NOTIFY imageSourceChanged FINAL)


            /*!
             * @brief The scaling method for the image.
             *
             * The default value is @c ScalingMethod::Fill.
             * When changing scaling method the @c scalingMethodChanged() signal will be emitted.
             *
             * @note Scaling method @c None is not yet supported by the @c %ImageView
             *
             * @since BlackBerry 10.0.0
             */
             Q_PROPERTY(bb::cascades::ScalingMethod::Type scalingMethod
                       READ scalingMethod
                       WRITE setScalingMethod
                       RESET resetScalingMethod
                       NOTIFY scalingMethodChanged FINAL)

            /*!
             * @brief The load effect for the image.
             *
             * The default value is ImageViewLoadEffect::Default.
             * When changing load effect the loadEffectChanged() signal will be emitted.
             *
             * @since BlackBerry 10.0.0
             */
             Q_PROPERTY(bb::cascades::ImageViewLoadEffect::Type loadEffect
                       READ loadEffect
                       WRITE setLoadEffect
                       RESET resetLoadEffect
                       NOTIFY loadEffectChanged FINAL)

            /*!
             * @brief A filter color for the image.
             *
             * The image view will get filtered with this color. The default value is an invalid @c QVariant.
             * This property will not have any effect if the type settings in the .amd file is set to "normal".
             * Note that using filter color on a non gray scale image doesn't always render correct colors.
             *
             * @see Image
             *
             * @xmlonly
             * <qml>
             * <variant type="bb::cascades::Color"/>
             * <variant type="bb::cascades::ColorPaint"/>
             * </qml>
             * @endxmlonly
             *
             * @since BlackBerry 10.3.0
             */
          Q_PROPERTY(QVariant filterColor READ filterColor WRITE setFilterColor RESET resetFilterColor NOTIFY filterColorChanged REVISION 3 FINAL)

        public:
            /*!
             * @brief Constructs an image view with a parent container.
             *
             * If no image is set the
             * image view will be transparent.
             *
             * @snippet tad/examples/controls/imageview/src/ImageViewExamples.cpp imageview2
             *
             * @param parent The parent container.
             *
             * @since BlackBerry 10.0.0
             */
            explicit ImageView(Container * parent = 0);

            virtual ~ImageView();

            /*!
             * @brief Returns the @c Image displayed in the image view.
             *
             * @return The image being displayed, or an invalid image if none is set.
             *
             * @since BlackBerry 10.0.0
             */
            Image image() const;

            /*!
             * @brief Sets the @c Image for the image view.
             *
             * An invalid image indicates no image.
             *
             * @param image The image to set.
             *
             * @since BlackBerry 10.0.0
             */
            Q_SLOT void setImage(const Image& image);

            /*!
             * @brief Resets the @c Image in the image view to its default, meaning that no image is set.
             *
             * @since BlackBerry 10.0.0
             */
            Q_SLOT void resetImage();


            /*!
             * @brief Returns the image source.
             *
             * @return The source of the displayed image.
             *
             * @since BlackBerry 10.0.0
             */
            QUrl imageSource() const;

            /*!
             * @brief Sets the Image for the image view by providing a source.
             *
             * An invalid @c QUrl indicates no image.
             * This function emits an @c imageSourceChanged() signal if the currently set image source changes.
             *
             * @param source The image url.
             *
             * @since BlackBerry 10.0.0
             */
            Q_SLOT void setImageSource(const QUrl &source);

            /*!
             * @brief Resets the @c Image in the image view to its default, meaning that no image is set.
             * This function emits an @c imageSourceChanged() signal if the currently set image source changes.
             *
             * @since BlackBerry 10.0.0
             */
            Q_SLOT void resetImageSource();

            /*!
             * @brief Returns the current scaling method used for the image view.
             *
             * @return The current scaling method.
             *
             * @since BlackBerry 10.0.0
             */
            bb::cascades::ScalingMethod::Type scalingMethod() const;

            /*!
             * @brief Sets the @c ScalingMethod for the image view.
             *
             * @param scalingMethod The scaling method to use.
             *
             * @since BlackBerry 10.0.0
             */
            Q_SLOT void setScalingMethod(bb::cascades::ScalingMethod::Type scalingMethod);

            /*!
             * @brief Resets the @c ScalingMethod to @c ScalingMethod::Fill.
             *
             * @since BlackBerry 10.0.0
             */
            Q_SLOT void resetScalingMethod();


            /*!
             * @brief Returns the current image load effect used for the image view.
             *
             * @return The current image load effect.
             *
             * @since BlackBerry 10.0.0
             */
            bb::cascades::ImageViewLoadEffect::Type loadEffect() const;

            /*!
             * @brief Sets the ImageViewLoadEffect for the image view.
             *
             * @param loadEffect The load effect to use.
             *
             * @since BlackBerry 10.0.0
             */
            Q_SLOT void setLoadEffect(bb::cascades::ImageViewLoadEffect::Type loadEffect);

            /*!
             * @brief Resets the loadEffect to ImageViewLoadEffect::None.
             *
             * @since BlackBerry 10.0.0
             */
            Q_SLOT void resetLoadEffect();

            /*!
             * @brief Returns the current filter color for the image view.
             *
             * @return The current filter color.
             *
             * @since BlackBerry 10.3.0
             */
            Q_REVISION(3)
            QVariant filterColor() const;

            /*!
             * @brief Sets the filter color for the image view.
             *
             * @param filterColor The filter color to use.
             *
             * @since BlackBerry 10.3.0
             */
            Q_REVISION(3)
            Q_SLOT void setFilterColor(const bb::cascades::ColorPaint& filterColor);

            /*!
             * @brief Sets the filter color for the image view.
             *
             * @param filterColor The filter color to use.
             *
             * @xmlonly
             * <qml>
             * <variant type="bb::cascades::Color"/>
             * <variant type="bb::cascades::ColorPaint"/>
             * </qml>
             * @endxmlonly
             *
             * @since BlackBerry 10.3.0
             */
            Q_REVISION(3)
            Q_SLOT void setFilterColor(const QVariant& filterColor);

            /*!
             * @brief Resets the filter color to the default value (invalid color).
             *
             * @since BlackBerry 10.3.0
             */
            Q_REVISION(3)
            Q_SLOT void resetFilterColor();

        Q_SIGNALS:
             /*!
             * @brief Emitted when the @c Image that is being displayed changes.
             *
             * @param image The new image. If no image is set, an empty image will be returned (see @c Image::isNull()).
             *
             * @xmlonly
             * <qml>
             * <param name="image" type="QVariant"/>
             * </qml>
             * @endxmlonly
              *
              * @since BlackBerry 10.0.0
             */
            void imageChanged(const bb::cascades::Image image);

            /*!
             * @brief Emitted when the imageSource changes
             *
             * @since BlackBerry 10.0.0
             */
            void imageSourceChanged(const QUrl& imageSource);

            /*! @cond PRIVATE */
            void imageChanged(QVariant image);
            /*! @endcond */

             /*!
             * @brief Emitted when the @c ScalingMethod changes
             *
             * @param newScalingMethod The new scaling method.
              *
              * @since BlackBerry 10.0.0
             */
            void scalingMethodChanged(bb::cascades::ScalingMethod::Type newScalingMethod);

             /*!
             * @brief Emitted when the loadEffect changes
             *
             * @param newLoadEffect The new load effect.
              *
              * @since BlackBerry 10.0.0
             */
            void loadEffectChanged(bb::cascades::ImageViewLoadEffect::Type newLoadEffect);

            /*!
             * @brief Emitted when the filter color for this image view changes.
             *
             * @param filterColor The new filter color for this image view.
             *
             * @xmlonly
             * <qml>
             * <param name="filterColor" type="QVariant"/>
             * </qml>
             * @endxmlonly
             *
             * @since BlackBerry 10.3.0
             */
            Q_REVISION(3)
            void filterColorChanged(const bb::cascades::ColorPaint& filterColor);

            /*! @cond PRIVATE */
            /*!
             * @brief Emitted when the filter color for this image view changes.
             *
             * @param filterColor The new filter color for this image view.
             *
             * @since BlackBerry 10.3.0
             */
            Q_REVISION(3)
            void filterColorChanged(const QVariant& filterColor);
            /*! @endcond */

        private:
            /*! @cond PRIVATE */

            /*!
             * Returns the image for the ImageView.
             *
             * This is a private function needed by the QML. The returned QVariant is always an Image.
             * @warning The client must not call this function, instead image() should be called.
             *
             * @return A QVariant containing the Image for the ImageVIew or 0 if no image was set (or was reset).
             */
            const QVariant imageQml() const;

            /*!
            * Sets the image for the Image.
            * The QVariant image can either be of type Image or a QString name. This is a private function
            * encapsulating setImage() needed by the QML.
            * \warning The client must not call this function, instead setImage() should be called.
            *
            * \param image A QVariant container either the Image or QString name of the image to set for
            * the ImageView.
            */
            Q_SLOT void setImageQml(const QVariant & image);

            Q_DECLARE_PRIVATE(ImageView)
            Q_DISABLE_COPY(ImageView)

            typedef ImageView ThisClass;  // The class in which scope we're currently inside
            typedef Control BaseClass; // References the class which ThisClass derives from
            /*! @endcond */

       public:


            /*!
             * @brief A builder template for constructing an image view. To retrieve the builder,
             * call @c ImageView::create().
             *
             * @since BlackBerry 10.0.0
             */
            template <typename BuilderType, typename BuiltType>
            class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType> {
            protected:
                TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node) {}
            public:
                /*!
                 * @brief Sets the image for the ImageView.
                 *
                 * @param image The image to display.
                 *
                 * @since BlackBerry 10.0.0
                 */
                BuilderType& image(const Image& image) {
                    this->instance().setImage(image);
                    return this->builder();
                }

                /*!
                 * @brief Sets the image for the @c ImageView, identified by its file path.
                 *
                 * This is a convenience function for setting an image for the ImageView
                 * identified by its filePath. This is equivalent to calling:
                 *
                 * @snippet tad/examples/controls/imageview/src/ImageViewExamples.cpp imageview3
                 *
                 * @param imageSource The image source of the image to display.
                 *
                 * @since BlackBerry 10.0.0
                 */
                BuilderType& imageSource(const QUrl &imageSource) {
                    return image(Image(imageSource));
                }

                /*!
                 * @brief Sets the @c scalingMethod for the image view.
                 *
                 * @see ScalingMethod
                 *
                 * @param scalingMethod The scaling method to set.
                 *
                 * @since BlackBerry 10.0.0
                 */
                BuilderType& scalingMethod(bb::cascades::ScalingMethod::Type scalingMethod) {
                    this->instance().setScalingMethod(scalingMethod);
                    return this->builder();
                }

                /*!
                 * @brief Sets the loadEffect for the image view.
                 *
                 * @see ImageViewLoadEffect
                 *
                 * @param loadEffect The load effect to set.
                 *
                 * @since BlackBerry 10.0.0
                 */
                BuilderType& loadEffect(bb::cascades::ImageViewLoadEffect::Type loadEffect) {
                    this->instance().setLoadEffect(loadEffect);
                    return this->builder();
                }

                /*!
                 * @brief Sets the filter color for the image view.
                 *
                 * @param filterColor The filter color to use.
                 *
                 * @since BlackBerry 10.3.0
                 */
                BuilderType& filterColor(const bb::cascades::ColorPaint &filterColor) {
                    this->instance().setFilterColor(filterColor);
                    return this->builder();
                }
            };

            /*!
             * @brief A builder for constructing an image view. To retrieve the builder,
             * call @c ImageView::create().
             *
             * @since BlackBerry 10.0.0
             */
             class Builder : public TBuilder<Builder, ImageView> {
             public:
               explicit Builder() : TBuilder<Builder, ImageView>(new ImageView()) {}
             };

            /*!
             * @brief Creates and returns a builder for constructing a @c ImageView.
             *
             * @snippet tad/examples/controls/imageview/src/ImageViewExamples.cpp imageview4
             *
             * @return A builder class for constructing an image view.
             *
             * @since BlackBerry 10.0.0
             */
             static Builder create() {
               return Builder();
             }

            /*!
             * @brief Creates and returns a builder that constructs an @c ImageView and sets the image.
             *
             * Example:
             *
             * @snippet tad/examples/controls/imageview/src/ImageViewExamples.cpp imageview5
             *
             * @param filePath The image path.
             * @return An image view builder.
             *
             * @since BlackBerry 10.0.0
             */
            static Builder create(const QString & filePath) {
                return Builder().imageSource(filePath);
            }

        };
    }
}

QML_DECLARE_TYPE(bb::cascades::ImageView)


#endif	// cascades_imageview_h


