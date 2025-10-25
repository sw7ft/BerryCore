/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_imagebutton_h
#define cascades_imagebutton_h

#include <QtCore/QString>

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/controls/abstractbutton.h>
#include <bb/cascades/resources/image.h>

namespace bb {
  namespace cascades {
    class ImageButtonPrivate;
    class Container;

    /*!
     *
     * @brief A clickable button with a visual representation for each state.
     *
     * @image html image_button.png An image button.
     *
     * A user can interact with an @c %ImageButton just like an ordinary @c Button. Typically, it's
     * used to capture touch events on the screen in order to invoke some sort of
     * programmatic action in response. When pressed, the @c AbstractButton::clicked() signal is emitted.
     * The main difference from the standard button is that the image button does not have a @c text property,
     * and it can have a different graphical representation applied for each of its three visual states:
     *
     *  - Default (the button is enabled, but not actively being pressed)
     *  - Pressed (the button is actively being pressed)
     *  - Disabled (this state is determined by the @c Control::enabled property)
     *
     * It should be noted that the different visual states can't be read by the developer (i.e. there's no
     * property you can check to see whether the button is currently being pressed or not). These are just
     * visual states.
     *
     * The @c %ImageButton class provides methods for setting and resetting its
     * images (if no images are set, the resulting image button will appear
     * transparent). When any of the images are changed, the corresponding
     * signals are emitted (@c defaultImageChanged(), @c pressedImageChanged() or
     * @c disabledImageChanged()). When any of the images are changed by setting a
     * new source URL, the corresponding signals are emitted
     * (@c defaultImageSourceChanged(), @c pressedImageSourceChanged(),
     * @c disabledImageSourceChanged()).
     *
     * The size of the image button behaves as follows:
     * - The properties @c Control::minWidth, @c Control::maxWidth, @c Control::minHeight
     *   and @c Control::maxHeight controls the minimum and maximum size of the
     *   image button.
     * - If set, the @c Control::preferredWidth property determines the width of
     *   the image button (within the minimum and maximum boundaries),
     *   stretching the images in that dimension if necessary.
     * - If set, the @c Control::preferredHeight property determines the height of
     *   the image button (within the minimum and maximum boundaries),
     *   stretching the images in that dimension if necessary.
     * - If any of @c Control::preferredWidth and @c Control::preferredHeight are not
     *   set, the corresponding dimension(s) of the image button is/are
     *   determined by the corresponding dimension(s) of the supplied images.
     * - If the images differ in size, the largest image width and the largest
     *   image height determines the size for the images as a
     *   collection, thus the images will be stretched to fit the collective size if
     *   needed.
     *
     * Creating an @c %ImageButton in C++, using the builder pattern:
     * @snippet tad/examples/controls/imagebutton/src/ImageButtonExamples.cpp imagebutton
     *
     * Creating an @c %ImageButton in QML:
     * @snippet tad/examples/controls/imagebutton/assets/main.qml imagebutton_qml
     *
     * @xmlonly
     * <apigrouping group="User interface/Core controls"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT ImageButton : public AbstractButton {
    private:
      Q_OBJECT

      /*!
       * @brief The image shown when the button is in its default state.
       *
       * If no image is set, an empty @c QImage will be returned. This means that no
       * image will be shown for this state. When changing the image the
       * @c defaultImageChanged() signal will be emitted.
       *
       * @xmlonly
       * <qml>
       * <variant type="bb::cascades::Image"/>
       * </qml>
       * @endxmlonly
       *
       * @since BlackBerry 10.0.0
       */
      Q_PROPERTY(QVariant defaultImage READ defaultImageQml WRITE setDefaultImageQml RESET resetDefaultImage NOTIFY defaultImageChanged FINAL)

      /*!
       * @brief The image shown when the button is in its default state.
       *
       * If no image is set, an invalid @c QUrl will be returned. This means that no
       * image will be shown for this state. When changing the image source the
       * @c defaultImageSourceChanged() signal will be emitted.
       *
       * @since BlackBerry 10.0.0
       */
      Q_PROPERTY(QUrl defaultImageSource READ defaultImageSource WRITE setDefaultImageSource RESET resetDefaultImageSource NOTIFY defaultImageSourceChanged FINAL)

      /*!
       * @brief The image shown when the button is pressed.
       *
       * If no image is set, an empty @c QImage will be returned. This means that no
       * image will be shown for this state. When changing the image the
       * @c pressedImageChanged() signal will be emitted.
       *
       * @xmlonly
       * <qml>
       * <variant type="bb::cascades::Image"/>
       * </qml>
       * @endxmlonly
       *
       * @since BlackBerry 10.0.0
       */
      Q_PROPERTY(QVariant pressedImage READ pressedImageQml WRITE setPressedImageQml RESET resetPressedImage NOTIFY pressedImageChanged FINAL)

      /*!
       * @brief The image shown when the button is pressed.
       *
       * If no image is set, an invalid @c QUrl will be returned. This means that no
       * image will be shown for this state. When changing the image source the
       * @c pressedImageSourceChanged() signal will be emitted.
       *
       * @since BlackBerry 10.0.0
       */
      Q_PROPERTY(QUrl pressedImageSource READ pressedImageSource WRITE setPressedImageSource RESET resetPressedImageSource NOTIFY pressedImageSourceChanged FINAL)

      /*!
       * @brief The image shown when the button is disabled.
       *
       * If no image is set, an empty @c QImage will be returned. This means that no
       * image will be shown for this state. When changing the image the
       * @c disabledImageChanged() signal will be emitted.
       *
       * @xmlonly
       * <qml>
       * <variant type="bb::cascades::Image"/>
       * </qml>
       * @endxmlonly
       *
       * @since BlackBerry 10.0.0
       */
      Q_PROPERTY(QVariant disabledImage READ disabledImageQml WRITE setDisabledImageQml RESET resetDisabledImage NOTIFY disabledImageChanged FINAL)

      /*!
       * @brief The image shown when the button is disabled.
       *
       * If no image is set, an invalid @c QUrl will be returned. This means that no
       * image will be shown for this state. When changing the image source the
       * @c disabledImageSourceChanged() signal will be emitted.
       *
       * @since BlackBerry 10.0.0
       */
      Q_PROPERTY(QUrl disabledImageSource READ disabledImageSource WRITE setDisabledImageSource RESET resetDisabledImageSource NOTIFY disabledImageSourceChanged FINAL)

    public:
      /*!  @brief Constructs an image button and specifies the parent
       * container.
       *
       * The ownership of the button is transferred to the parent if a parent is
       * specified.
       *
       * @param parent The parent container, or @c 0. This parameter is
       * optional. The default is @c 0 if you don't specify a parent.
       *
       * @since BlackBerry 10.0.0
       */
      explicit ImageButton(Container * parent = 0);

      /*!
       * @brief Destructs this image button.
       *
       * @since BlackBerry 10.0.0
       */
      virtual ~ImageButton();


      /*!
       * @brief Returns the image displayed when the image button is in its
       * default state.
       *
       * @return The image displayed in the default state, or an empty image if
       * no image is set.
       *
       * @since BlackBerry 10.0.0
       */
      Image defaultImage() const;

      /*!
       * @brief Sets the image displayed when the image button is in its default state.
       *
       * This function emits a @c defaultImageChanged() signal if the @c image
       * parameter specifies an image different from the image already used for
       * the default state.
       *
       * @param image The image to display on this image button, or an empty
       * image to display no image.
       *
       * @since BlackBerry 10.0.0
       */
      Q_SLOT void setDefaultImage(const bb::cascades::Image& image);

      /*!
       * @brief Resets the image (sets an empty image) displayed when the
       * image button is in its default state.
       *
       * This function emits a @c defaultImageChanged() signal if the image for
       * the default state was not already set to an empty image.
       *
       * @since BlackBerry 10.0.0
       */
      Q_SLOT void resetDefaultImage();

      /*!
       * @brief Returns the source of the image displayed when the image button
       * is in its default state.
       *
       * @return The source of the image displayed in the default state.
       *
       * @since BlackBerry 10.0.0
       */
      QUrl defaultImageSource() const;

      /*!
       * @brief Sets the source of the image displayed when the image button is
       * in its default state.
       *
       * An invalid @c QUrl indicates no image.
       *
       * This function emits a @c defaultImageSourceChanged() signal if the
       * currently set image source changes.
       *
       * @param source The image URL.
       *
       * @since BlackBerry 10.0.0
       */
      Q_SLOT void setDefaultImageSource(const QUrl& source);

      /*!
       * @brief Resets the image (sets an empty image) displayed when the
       * image button is in its default state.
       *
       * This function emits a @c defaultImageSourceChanged() signal if the image for
       * the default state was not already set to an empty image.
       *
       * @since BlackBerry 10.0.0
       */
      Q_SLOT void resetDefaultImageSource();


      /*!
       * @brief Returns the image displayed when the image button is pressed.
       *
       * @return The image displayed in the pressed state, or an empty image if
       * no image is set.
       *
       * @since BlackBerry 10.0.0
       */
      Image pressedImage() const;

      /*!
       * @brief Sets the image displayed when the image button is pressed.
       *
       * This function emits a @c pressedImageChanged() signal if the @c image
       * parameter specifies an image different from the image already used for
       * the pressed state.
       *
       * @param image The image to display on this image button, or an empty
       * image to display no image.
       *
       * @since BlackBerry 10.0.0
       */
      Q_SLOT void setPressedImage(const bb::cascades::Image& image);

      /*!
       * @brief Resets the image (sets an empty image) displayed when the
       * image button is pressed.
       *
       * This function emits a @c pressedImageChanged() signal if the image for
       * the pressed state was not already set to an empty image.
       *
       * @since BlackBerry 10.0.0
       */
      Q_SLOT void resetPressedImage();

      /*!
       * @brief Returns the source of the image displayed when the image button
       * is pressed.
       *
       * @return The source of the image displayed in the pressed state.
       *
       * @since BlackBerry 10.0.0
       */
      QUrl pressedImageSource() const;

      /*!
       * @brief Sets the source of the image displayed when the image button is
       * pressed.
       *
       * An invalid @c QUrl indicates no image.
       *
       * This function emits a @c pressedImageSourceChanged() signal if the
       * currently set image source changes.
       *
       * @param source The image URL.
       *
       * @since BlackBerry 10.0.0
       */
      Q_SLOT void setPressedImageSource(const QUrl& source);

      /*!
       * @brief Resets the image (sets an empty image) displayed when the
       * image button is pressed.
       *
       * This function emits a @c pressedImageSourceChanged() signal if the image for
       * the pressed state was not already set to an empty image.
       *
       * @since BlackBerry 10.0.0
       */
      Q_SLOT void resetPressedImageSource();


      /*!
       * @brief Returns the image displayed when the image button is disabled.
       *
       * @return The image displayed in the disabled state, or an empty image if
       * no image is set.
       *
       * @since BlackBerry 10.0.0
       */
      Image disabledImage() const;

      /*!
       * @brief Sets the image displayed when the image button is disabled.
       *
       * This function emits a @c disabledImageChanged() signal if the @c image
       * parameter specifies an image different from the image already used for
       * the disabled state.
       *
       * @param image The image to display on this image button, or an empty
       * image to display no image.
       *
       * @since BlackBerry 10.0.0
       */
      Q_SLOT void setDisabledImage(const bb::cascades::Image& image);

      /*!
       * @brief Resets the image (sets an empty image) displayed when the
       * image button is disabled.
       *
       * This function emits a @c disabledImageChanged() signal if the image for
       * the disabled state was not already set to an empty image.
       *
       * @since BlackBerry 10.0.0
       */
      Q_SLOT void resetDisabledImage();

      /*!
       * @brief Returns the source of the image displayed when the image button
       * is disabled.
       *
       * @return The source of the image displayed in the disabled state.
       *
       * @since BlackBerry 10.0.0
       */
      QUrl disabledImageSource() const;

      /*!
       * @brief Sets the source of the image displayed when the image button is
       * disabled.
       *
       * An invalid @c QUrl indicates no image.
       *
       * This function emits a @c disabledImageSourceChanged() signal if the
       * currently set image source changes.
       *
       * @param source The image URL.
       *
       * @since BlackBerry 10.0.0
       */
      Q_SLOT void setDisabledImageSource(const QUrl& source);

      /*!
       * @brief Resets the image (sets an empty image) displayed when the
       * image button is disabled.
       *
       * This function emits a @c disabledImageSourceChanged() signal if the image for
       * the disabled state was not already set to an empty image.
       *
       * @since BlackBerry 10.0.0
       */
      Q_SLOT void resetDisabledImageSource();


    Q_SIGNALS:
      /*!
       * @brief Emitted when the image for the default state changes.
       *
       * @param image The new image. If no image is set, an empty image will
       * be returned.
       *
       * @xmlonly
       * <qml>
       * <param name="image" type="QVariant"/>
       * </qml>
       * @endxmlonly
       *
       * @since BlackBerry 10.0.0
       */
      void defaultImageChanged(const bb::cascades::Image& image);

      /*!
       * @brief Emitted when the source of the image for the default state changes.
       *
       * @param source The new source.
       *
       * @since BlackBerry 10.0.0
       */
      void defaultImageSourceChanged(const QUrl& source);

      /*!
       * @brief Emitted when the image for the pressed state changes.
       *
       * @param image The new image. If no image is set, an empty image will
       * be returned.
       *
       * @xmlonly
       * <qml>
       * <param name="image" type="QVariant"/>
       * </qml>
       * @endxmlonly
       *
       * @since BlackBerry 10.0.0
       */
      void pressedImageChanged(const bb::cascades::Image& image);

      /*!
       * @brief Emitted when the source of image for the pressed state changes.
       *
       * @param source The new source.
       *
       * @since BlackBerry 10.0.0
       */
      void pressedImageSourceChanged(const QUrl& source);

      /*!
       * @brief Emitted when the image for the disabled state changes.
       *
       * @param image The new image. If no image is set, an empty image will
       * be returned.
       *
       * @xmlonly
       * <qml>
       * <param name="image" type="QVariant"/>
       * </qml>
       * @endxmlonly
       *
       * @since BlackBerry 10.0.0
       */
      void disabledImageChanged(const bb::cascades::Image& image);

      /*!
       * @brief Emitted when the source of the image for the disabled state changes.
       *
       * @param source The new source.
       *
       * @since BlackBerry 10.0.0
       */
      void disabledImageSourceChanged(const QUrl& source);

      /*! @cond PRIVATE */

      /*!
       * @see defaultImageChanged(const bb::cascades::Image&)
       */
      void defaultImageChanged(const QVariant& image);

      /*!
       * @see pressedImageChanged(const bb::cascades::Image&)
       */
      void pressedImageChanged(const QVariant& image);

      /*!
       * @see disabledImageChanged(const bb::cascades::Image&)
       */
      void disabledImageChanged(const QVariant& image);

      /*! @endcond */

    private:
      /*! @cond PRIVATE */

      /*!
       * @brief Returns the image displayed when the image button is in its
       * default state.
       *
       * This is a private function needed by the QML. The returned @c QVariant is
       * always an Image.
       * @warning The client must not call this function, instead defaultImage()
       * should be called.
       *
       * @return A @c QVariant containing the image for the default state or an
       * empty image if no image was set.
       */
      QVariant defaultImageQml() const;

      /*!
       * @brief Sets the image displayed when the image button is in its
       * default state.
       *
       * The @c QVariant image can either be of type Image or a @c QUrl name. This
       * is a private function encapsulating setDefaultImage() needed by the QML.
       * @warning The client must not call this function, instead
       * setDefaultImage() should be called.
       *
       * @param image A @c QVariant container either the Image or the @c QUrl name of
       * the image to set for the default state.
       */
      Q_SLOT void setDefaultImageQml(const QVariant& image);

      /*!
       * @brief Returns the image displayed when the image button is pressed.
       *
       * This is a private function needed by the QML. The returned @c QVariant is
       * always an Image.
       * @warning The client must not call this function, instead pressedImage()
       * should be called.
       *
       * @return A @c QVariant containing the image for the pressed state or an
       * empty image if no image was set.
       */
      QVariant pressedImageQml() const;

      /*!
       * @brief Sets the image displayed when the image button is pressed.
       *
       * The @c QVariant image can either be of type Image or a @c QUrl name. This
       * is a private function encapsulating setPressedImage() needed by the QML.
       * @warning The client must not call this function, instead
       * setPressedImage() should be called.
       *
       * @param image A @c QVariant container either the Image or the @c QUrl name of
       * the image to set for the pressed state.
       */
      Q_SLOT void setPressedImageQml(const QVariant& image);

      /*!
       * @brief Returns the image displayed when the image button is disabled.
       *
       * This is a private function needed by the QML. The returned @c QVariant is
       * always an Image.
       * @warning The client must not call this function, instead
       * disabledImage() should be called.
       *
       * @return A @c QVariant containing the image for the disabled state or an
       * empty image if no image was set.
       */
      QVariant disabledImageQml() const;

      /*!
       * @brief Sets the image displayed when the image button is disabled.
       *
       * The @c QVariant image can either be of type @c Image or a @c QUrl name. This
       * is a private function encapsulating setDisabledImage() needed by the
       * QML.
       * @warning The client must not call this function, instead
       * setDisabledImage() should be called.
       *
       * @param image A @c QVariant container either the Image or the @c QUrl name of
       * the image to set for the disabled state.
       */
      Q_SLOT void setDisabledImageQml(const QVariant& image);

      /*! \endcond */

      Q_DECLARE_PRIVATE(ImageButton)
      Q_DISABLE_COPY(ImageButton)

      /*! \cond PRIVATE */
      // The class in which scope we're currently inside
      typedef ImageButton ThisClass;
      // References the class which ThisClass derives from
      typedef AbstractButton BaseClass;
      /*! \endcond */

    protected:
      /*!
       * @brief A builder template for constructing an image button.
       *
       * To retrieve the builder, call @c ImageButton::create().
       *
       * @since BlackBerry 10.0.0
       */
      template <typename BuilderType, typename BuiltType>
      class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType> {
      protected:
        TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node) {}
      public:
        /*!
         * @brief Sets the image displayed when the image button is in its
         * default state.
         *
         * @param image The image to set, or an empty image to display no image.
         *
         * @since BlackBerry 10.0.0
         */
        BuilderType& defaultImage(const bb::cascades::Image& image) {
          this->instance().setDefaultImage(image);
          return this->builder();
        }

        /*!
         * @brief Sets the image displayed when the image button is pressed.
         *
         * @param image The image to set, or an empty image to display no image.
         *
         * @since BlackBerry 10.0.0
         */
        BuilderType& pressedImage(const bb::cascades::Image& image) {
          this->instance().setPressedImage(image);
          return this->builder();
        }

        /*!
         * @brief Sets the image displayed when the image button is disabled.
         *
         * @param image The image to set, or an empty image to display no image.
         *
         * @since BlackBerry 10.0.0
         */
        BuilderType& disabledImage(const bb::cascades::Image& image) {
          this->instance().setDisabledImage(image);
          return this->builder();
        }

        /*!
         * @brief Sets the source of the image displayed when the image button is in its
         * default state.
         *
         * This is a convenience function for setting an image for the
         * @c %ImageButton identified by its URL. This is equivalent to calling:
         * @code
         * defaultImage(Image("images/myImage.png"));
         * @endcode
         *
         * @param source The URL of the image to set.
         *
         *
         * @since BlackBerry 10.0.0
         */
        BuilderType& defaultImage(const QUrl& source) {
          return defaultImage(Image(source));
        }

        /*!
         * @brief Sets the source of the image displayed when the image button
         * is pressed.
         *
         * This is a convenience function for setting an image for the
         * @c %ImageButton identified by its URL. This is equivalent to calling:
         * @code
         * pressedImage(Image("images/myImage.png"));
         * @endcode
         *
         * @param source The URL of the image to set.
         *
         *
         * @since BlackBerry 10.0.0
         */
        BuilderType& pressedImage(const QUrl& source) {
          return pressedImage(Image(source));
        }

        /*!
         * @brief Sets the source of the image displayed when the image button
         * is disabled.
         *
         * This is a convenience function for setting an image for the
         * @c %ImageButton identified by its URL. This is equivalent to calling:
         * @code
         * disabledImage(Image("images/myImage.png"));
         * @endcode
         *
         * @param source The URL of the image to set.
         *
         *
         * @since BlackBerry 10.0.0
         */
        BuilderType& disabledImage(const QUrl& source) {
          return disabledImage(Image(source));
        }
      };

    public:
      /*!
       * @brief A builder that constructs an @c %ImageButton.
       *
       * To retrieve the builder, call ImageButton::create().
       *
       * @since BlackBerry 10.0.0
       */
      class Builder : public TBuilder<Builder, ImageButton> {
      public:
        explicit Builder() : TBuilder<Builder, ImageButton>(new ImageButton()) {}
      };

      /*!
       * @brief Creates and returns a builder for constructing an @c %ImageButton.
       *
       * Using the builder to create an @c %ImageButton:
       * @code
       * ImageButton* myImageButton = ImageButton::create().defaultImage("myImage.png");
       * @endcode
       *
       * @return A builder used for constructing an image button.
       *
       * @since BlackBerry 10.0.0
       */
      static Builder create() {
        return Builder();
      }
    };
  }
}

QML_DECLARE_TYPE(bb::cascades::ImageButton)

#endif // cascades_imagebutton_h
