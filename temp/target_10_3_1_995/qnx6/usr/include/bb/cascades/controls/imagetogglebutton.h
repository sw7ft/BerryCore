/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_imagetogglebutton_h
#define cascades_imagetogglebutton_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/controls/abstracttogglebutton.h>
#include <bb/cascades/resources/image.h>

namespace bb {
  namespace cascades {

    class ImageToggleButtonPrivate;
    class Container;

    /*!
    * @brief A toggle button with a visual representation for each state.
    *
    * @image html image_button.png The three states of an ImageToggleButton
    *
    * A user can interact with an @c %ImageToggleButton just like an ordinary @c ToggleButton. Typically, it's
    * used to switch between two states (for example, On and Off). The AbstractToggleButton::checked state
    * indicates whether the toggle button has been checked or not.
    * When pressed, the @c AbstractToggleButton::checkedChanged() signal is emitted.
    *
    * The only difference from the standard toggle button is that @c %ImageToggleButton
    * can have a different image applied for each of its six visual states:
    *
    *  \li default (unchecked and enabled)
    *  \li checked and enabled
    *  \li unchecked and disabled
    *  \li checked and disabled
    *  \li unchecked and pressed
    *  \li checked and pressed
    *
    * The 'pressed' state refers to the state when a user is actively pressing the button, intending to change between checked and unchecked.
    * Note that the 'pressed' state implies that the control is enabled, since the user can't press a disabled button.
    *
    * If an image is missing for a state, a transparent image is shown.
    *
    * The size of the @c %ImageToggleButton and the state images follow these rules:
    *  - The intended usage is that the size of the @c %ImageToggleButton should be defined, and all the supplied images should scale to that size.
    *  - The @c %ImageToggleButton is designed to handle missing data gracefully:
    *    - If either dimension of the @c %ImageToggleButton is set (i.e., @c Control::preferredWidth or @c Control::preferredHeight is set), that value is used.
    *    - If either dimension of the @c %ImageToggleButton is NOT set, the size of the @c %ImageToggleButton is set to the maximum size over all images for that dimension.
    *    - When scaling an image, the aspect ratio is NOT preserved (i.e., the image is stretched as required to fit the size of the @c %ImageToggleButton).
    * .
    * Missing images:
    *  - A missing  image is considered a "soft error". The control will work, but the visual appearance of the control for the corresponding state is undefined.
    *  - If all images are missing, and no preferred size is defined for a dimension, the size in that dimension will be the minimum control size.
    *
    * Here's an example for how to create an @c %ImageToggleButton in C++.
    *
    * @snippet tad/examples/controls/imagetogglebutton/src/ImageToggleButtonExamples.cpp imagetogglebutton
    *
    * And here's how to create one in QML and display current status.
    *
    * @snippet tad/examples/controls/imagetogglebutton/assets/main.qml imagetogglebutton_qml
    *
    * @xmlonly
    * <apigrouping group="User interface/Core controls"/>
    * @endxmlonly
     *
     * @since BlackBerry 10.0.0
    */
    class BBCASCADES_EXPORT ImageToggleButton : public AbstractToggleButton
    {
    private:
      Q_OBJECT

        /*!
        * @brief The image used for the default state.
        *
        * If no image is set, an @c NULL @c QImage will be returned.
        * When changing image the @c imageDefaultChanged() signal will be emitted.
        *
        * @xmlonly
        * <qml>
        * <variant type="bb::cascades::Image"/>
        * </qml>
        * @endxmlonly
         *
         * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(QVariant imageDefault READ imageQmlDefault WRITE setImageQmlDefault RESET resetImageDefault NOTIFY imageDefaultChanged FINAL)

        /*!
        * @brief The image used for the default state.
        *
        * If no image is set, an invalid @c QUrl will be returned.
        * When changing the image source the @c imageSourceDefaultChanged() signal will be emitted.
         *
         * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(QUrl imageSourceDefault READ imageSourceDefault WRITE setImageSourceDefault RESET resetImageSourceDefault NOTIFY imageSourceDefaultChanged FINAL)


        /*!
        * @brief The image used for the checked state.
        *
        * If no image is set, an @c NULL @c QImage will be returned.
        * When changing image the @c imageCheckedChanged() signal will be emitted.
        *
        * @xmlonly
        * <qml>
        * <variant type="bb::cascades::Image"/>
        * </qml>
        * @endxmlonly
         *
         * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(QVariant imageChecked READ imageQmlChecked WRITE setImageQmlChecked RESET resetImageChecked NOTIFY imageCheckedChanged FINAL)
        /*!
        * @brief The image used for the checked state.
        *
        * If no image is set, an invalid @c QUrl will be returned.
        * When changing the image source the @c imageSourceCheckedChanged() signal will be emitted.
         *
         * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(QUrl imageSourceChecked READ imageSourceChecked WRITE setImageSourceChecked RESET resetImageSourceChecked NOTIFY imageSourceCheckedChanged FINAL)


        /*!
        * @brief The image used for the disabled and unchecked state.
        *
        * If no image is set, an @c NULL @c QImage will be returned.
        * When changing image the @c imageDisabledUncheckedChanged() signal will be emitted.
        *
        * @xmlonly
        * <qml>
        * <variant type="bb::cascades::Image"/>
        * </qml>
        * @endxmlonly
         *
         * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(QVariant imageDisabledUnchecked READ imageQmlDisabledUnchecked WRITE setImageQmlDisabledUnchecked RESET resetImageDisabledUnchecked NOTIFY imageDisabledUncheckedChanged FINAL)
        /*!
        * @brief The image used for the disabled and unchecked state.
        *
        * If no image is set, an invalid @c QUrl will be returned.
        * When changing the image source the @c imageSourceDisabledCheckedChanged() signal will be emitted.
         *
         * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(QUrl imageSourceDisabledUnchecked READ imageSourceDisabledUnchecked WRITE setImageSourceDisabledUnchecked RESET resetImageSourceDisabledUnchecked NOTIFY imageSourceDisabledUncheckedChanged FINAL)

        /*!
        * @brief The image used for the disabled and checked state.
        *
        * If no image is set, an NULL @c QImage will be returned.
        * When changing image the @c imageDisabledCheckedChanged() signal will be emitted.
        *
        * @xmlonly
        * <qml>
        * <variant type="bb::cascades::Image"/>
        * </qml>
        * @endxmlonly
         *
         * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(QVariant imageDisabledChecked READ imageQmlDisabledChecked WRITE setImageQmlDisabledChecked RESET resetImageDisabledChecked NOTIFY imageDisabledCheckedChanged FINAL)
        /*!
        * @brief The image used for the disabled and checked state.
        *
        * If no image is set, an invalid @c QUrl will be returned.
        * When changing the image source the @c imageSourceDisabledCheckedChanged() signal will be emitted.
         *
         * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(QUrl imageSourceDisabledChecked READ imageSourceDisabledChecked WRITE setImageSourceDisabledChecked RESET resetImageSourceDisabledChecked NOTIFY imageSourceDisabledCheckedChanged FINAL)

        /*!
        * @brief The image used for the pressed and unchecked state.
        *
        * If no image is set, an @c NULL @c QImage will be returned.
        * When changing image the @c imagePressedUncheckedChanged() signal will be emitted.
        *
        * @xmlonly
        * <qml>
        * <variant type="bb::cascades::Image"/>
        * </qml>
        * @endxmlonly
         *
         * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(QVariant imagePressedUnchecked READ imageQmlPressedUnchecked WRITE setImageQmlPressedUnchecked RESET resetImagePressedUnchecked NOTIFY imagePressedUncheckedChanged FINAL)
        /*!
        * @brief The image used for the pressed and unchecked state.
        *
        * If no image is set, an invalid @c QUrl will be returned.
        * When changing the image source the @c imageSourcePressedUncheckedChanged() signal will be emitted.
         *
         * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(QUrl imageSourcePressedUnchecked READ imageSourcePressedUnchecked WRITE setImageSourcePressedUnchecked RESET resetImageSourcePressedUnchecked NOTIFY imageSourcePressedUncheckedChanged FINAL)
        /*!
        * @brief The image used for the pressed and checked state.
        *
        * If no image is set, an @c NULL @c QImage will be returned.
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
        Q_PROPERTY(QVariant imagePressedChecked READ imageQmlPressedChecked WRITE setImageQmlPressedChecked RESET resetImagePressedChecked NOTIFY imagePressedCheckedChanged FINAL)
        /*!
        * @brief The image used for the pressed and checked state.
        *
        * If no image is set, an invalid @c QUrl will be returned.
        * When changing the image source the @c imageSourcePressedCheckedChanged() signal will be emitted.
        *
         *
         * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(QUrl imageSourcePressedChecked READ imageSourcePressedChecked WRITE setImageSourcePressedChecked RESET resetImageSourcePressedChecked NOTIFY imageSourcePressedCheckedChanged FINAL)

    public:
      /*!
      * @brief Constructs an @c %ImageToggleButton with a parent.
      *
      * If not @c 0, the ownership of the constructed @c %ImageToggleButton will be transferred to the parent.
      *
      * @param parent The parent container or @c 0. Optional and will default to @c 0 if not specified.
       *
       * @since BlackBerry 10.0.0
      */
      explicit ImageToggleButton(Container * parent = 0);

      /*!
      * @brief Destroys the @c %ImageToggleButton.
       *
       * @since BlackBerry 10.0.0
      */
      virtual ~ImageToggleButton();


      /*---  getters, setters, resetters for all 6 images ---*/


      /*!
      * @brief Returns the @c Image displayed for the default and unchecked state.
      *
      * @return The image being displayed, or an invalid image if none is set.
       *
       * @since BlackBerry 10.0.0
      */
      Image imageDefault() const;
      /*!
      * @brief Sets the @c Image for the default state
      *
      * An invalid image indicates no image.
      *
      * @param image The image to set.
       *
       * @since BlackBerry 10.0.0
      */
      Q_SLOT void setImageDefault(const bb::cascades::Image& image);
      /*!
      * @brief Resets the @c Image for the default state to its default, meaning that no image is set.
       *
       * @since BlackBerry 10.0.0
      */
      Q_SLOT void resetImageDefault();
      /*!
      * @brief Returns the image source for the default state
      *
      * @return The source of the displayed image.
       *
       * @since BlackBerry 10.0.0
      */
      QUrl imageSourceDefault() const;
      /*!
      * @brief Sets the @c Image used for the default state by providing a source.
      *
      * An invalid @c QUrl indicates no image.
      * This function emits an @c imageSourceChangedDefault() signal if the currently set image source changes.
      *
      * @param source The image url.
       *
       * @since BlackBerry 10.0.0
      */
      Q_SLOT void setImageSourceDefault(const QUrl &source);
      /*!
      * @brief Resets the @c Image for the default state to its default, meaning that no image is set.
      *
      * This function emits an @c imageSourceChangedDefault() signal if the currently set image source changes.
       *
       * @since BlackBerry 10.0.0
      */
      Q_SLOT void resetImageSourceDefault();



      /*!
      * @brief Returns the @c Image displayed for the checked state.
      *
      * @return The image being displayed, or an invalid image if none is set.
       *
       * @since BlackBerry 10.0.0
      */
      Image imageChecked() const;
      /*!
      * @brief Sets the @c Image for the checked state
      *
      * An invalid image indicates no image.
      *
      * @param image The image to set.
       *
       * @since BlackBerry 10.0.0
      */
      Q_SLOT void setImageChecked(const bb::cascades::Image& image);
      /*!
      * @brief Resets the @c Image for the checked state to its Default, meaning that no image is set.
       *
       * @since BlackBerry 10.0.0
      */
      Q_SLOT void resetImageChecked();
      /*!
      * @brief Returns the @c image source for the checked state
      *
      * @return The source of the displayed image.
       *
       * @since BlackBerry 10.0.0
      */
      QUrl imageSourceChecked() const;

      /*!
      * @brief Sets the @c Image used for the checked state by providing a source.
      *
      * An invalid @c QUrl indicates no image.
      * This function emits an @c imageSourceChangedChecked() signal if the currently set image source changes.
      *
      * @param source The image url.
       *
       * @since BlackBerry 10.0.0
      */
      Q_SLOT void setImageSourceChecked(const QUrl &source);

      /*!
      * @brief Resets the @c Image for the checked state to its default, meaning that no image is set.
      *
      * This function emits an @c imageSourceChangedChecked() signal if the currently set image source changes.
       *
       * @since BlackBerry 10.0.0
      */
      Q_SLOT void resetImageSourceChecked();




      /*!
      * @brief Returns the @c Image displayed for the disabled and unchecked state
      *
      * @return The image being displayed, or an invalid image if none is set.
       *
       * @since BlackBerry 10.0.0
      */
      Image imageDisabledUnchecked() const;
      /*!
      * @brief Sets the @c Image for the disabled and unchecked state
      *
      * An invalid image indicates no image.
      *
      * @param image The image to set.
       *
       * @since BlackBerry 10.0.0
      */
      Q_SLOT void setImageDisabledUnchecked(const bb::cascades::Image& image);
      /*!
      * @brief Resets the @c Image for the disabled and unchecked state to its default, meaning that no image is set.
       *
       * @since BlackBerry 10.0.0
      */
      Q_SLOT void resetImageDisabledUnchecked();
      /*!
      * @brief Returns the image source for the disabled and unchecked state
      *
      * @return The source of the displayed image.
       *
       * @since BlackBerry 10.0.0
      */
      QUrl imageSourceDisabledUnchecked() const;

      /*!
      * @brief Sets the @c Image used for the disabled and unchecked state by providing a source.
      *
      * An invalid @c QUrl indicates no image.
      * This function emits an @c imageSourceChangedDisabledUnchecked() signal if the currently set image source changes.
      *
      * @param source The image url.
       *
       * @since BlackBerry 10.0.0
      */
      Q_SLOT void setImageSourceDisabledUnchecked(const QUrl &source);

      /*!
      * @brief Resets the Image for the disabled and unchecked state to its default, meaning that no image is set.
      *
      * This function emits an @c imageSourceChangedDisabledUnchecked() signal if the currently set image source changes.
       *
       * @since BlackBerry 10.0.0
      */
      Q_SLOT void resetImageSourceDisabledUnchecked();



      /*!
      * @brief Returns the @c Image displayed for the disabled and checked state.
      *
      * @return The image being displayed, or an invalid image if none is set.
       *
       * @since BlackBerry 10.0.0
      */
      Image imageDisabledChecked() const;
      /*!
      * @brief Sets the @c Image for the disabled and checked state
      *
      * An invalid image indicates no image.
      *
      * @param image The image to set.
       *
       * @since BlackBerry 10.0.0
      */
      Q_SLOT void setImageDisabledChecked(const bb::cascades::Image& image);
      /*!
      * @brief Resets the @c Image for the disabled and checked state to its default, meaning that no image is set.
       *
       * @since BlackBerry 10.0.0
      */
      Q_SLOT void resetImageDisabledChecked();
      /*!
      * @brief Returns the image source for the disabled and checked state.
      *
      * @return The source of the displayed image.
       *
       * @since BlackBerry 10.0.0
      */
      QUrl imageSourceDisabledChecked() const;

      /*!
      * @brief Sets the Image used for the disabled and checked state by providing a source.
      *
      * An invalid @c QUrl indicates no image.
      * This function emits an @c imageSourceChangedDisabledChecked() signal if the currently set image source changes.
      *
      * @param source The image url.
       *
       * @since BlackBerry 10.0.0
      */
      Q_SLOT void setImageSourceDisabledChecked(const QUrl &source);

      /*!
      * @brief Resets the @c Image for the disabled and checked state to its default, meaning that no image is set.
      *
      * This function emits an @c imageSourceChangedDisabledChecked() signal if the currently set image source changes.
       *
       * @since BlackBerry 10.0.0
      */
      Q_SLOT void resetImageSourceDisabledChecked();



      /*!
      * @brief Returns the @c Image displayed for the pressed and unchecked state.
      *
      * @return The image being displayed, or an invalid image if none is set.
       *
       * @since BlackBerry 10.0.0
      */
      Image imagePressedUnchecked() const;
      /*!
      * @brief Sets the @c Image for the pressed and unchecked state.
      *
      * An invalid image indicates no image.
      *
      * @param image The image to set.
       *
       * @since BlackBerry 10.0.0
      */
      Q_SLOT void setImagePressedUnchecked(const bb::cascades::Image& image);
      /*!
      * @brief Resets the @c Image for the pressed and unchecked state to its default, meaning that no image is set.
       *
       * @since BlackBerry 10.0.0
      */
      Q_SLOT void resetImagePressedUnchecked();
      /*!
      * @brief Returns the image source for the pressed and unchecked state.
      *
      * @return The source of the displayed image.
       *
       * @since BlackBerry 10.0.0
      */
      QUrl imageSourcePressedUnchecked() const;

      /*!
      * @brief Sets the @c Image used for the pressed and unchecked state by providing a source.
      *
      * An invalid @c QUrl indicates no image.
      * This function emits an @c imageSourceChangedPressedUnchecked() signal if the currently set image source changes.
      *
      * @param source The image url.
       *
       * @since BlackBerry 10.0.0
      */
      Q_SLOT void setImageSourcePressedUnchecked(const QUrl &source);

      /*!
      * @brief Resets the @c Image for the pressed and unchecked state to its default, meaning that no image is set.
      *
      * This function emits an @c imageSourceChangedPressedUnchecked() signal if the currently set image source changes.
       *
       * @since BlackBerry 10.0.0
      */
      Q_SLOT void resetImageSourcePressedUnchecked();



      /*!
      * @brief Returns the @c Image displayed for the pressed and checked state.
      *
      * @return The image being displayed, or an invalid image if none is set.
       *
       * @since BlackBerry 10.0.0
      */
      Image imagePressedChecked() const;
      /*!
      * @brief Sets the @c Image for the pressed and checked state
      *
      * An invalid image indicates no image.
      *
      * @param image The image to set.
       *
       * @since BlackBerry 10.0.0
      */
      Q_SLOT void setImagePressedChecked(const bb::cascades::Image& image);
      /*!
      * @brief Resets the @c Image for the pressed and checked state to its default, meaning that no image is set.
       *
       * @since BlackBerry 10.0.0
      */
      Q_SLOT void resetImagePressedChecked();
      /*!
      * @brief Returns the image source for the pressed and checked state
      *
      * @return The source of the displayed image.
       *
       * @since BlackBerry 10.0.0
      */
      QUrl imageSourcePressedChecked() const;

      /*!
      * @brief Sets the @c Image used for the pressed and checked state by providing a source.
      *
      * An invalid @c QUrl indicates no image.
      * This function emits an @c imageSourceChangedPressedChecked() signal if the currently set image source changes.
      *
      * @param source The image url.
       *
       * @since BlackBerry 10.0.0
      */
      Q_SLOT void setImageSourcePressedChecked(const QUrl &source);

      /*!
      * @brief Resets the @c Image for the pressed and checked state to its default, meaning that no image is set.
      *
      * This function emits an @c imageSourceChangedPressedChecked() signal if the currently set image source changes.
       *
       * @since BlackBerry 10.0.0
      */
      Q_SLOT void resetImageSourcePressedChecked();



Q_SIGNALS:
      /*!
      * @brief Emitted when the @c Image that is used for the default state changes.
      *
      * @param image The new image. If no image is set, an empty image will be returned (see Image::isNull()).
      *
      * @xmlonly
      * <qml>
      * <param name="image" type="QVariant"/>
      * </qml>
      * @endxmlonly
       *
       * @since BlackBerry 10.0.0
      */
      void imageDefaultChanged(const bb::cascades::Image& image);
      /*!
      * @brief Emitted when the source of @c Image that is used for the default state changes.
      *
      * @param imageSource The new source.
       *
       * @since BlackBerry 10.0.0
      */
      void imageSourceDefaultChanged(const QUrl& imageSource);

      /*! @cond PRIVATE */
      void imageDefaultChanged(QVariant image);
      /*! @endcond */

      /*!
      * @brief Emitted when the @c Image that is used for the checked state changes.
      *
      * @param image The new image. If no image is set, an empty image will be returned (see Image::isNull()).
      *
      * @xmlonly
      * <qml>
      * <param name="image" type="QVariant"/>
      * </qml>
      * @endxmlonly
       *
       * @since BlackBerry 10.0.0
      */
      void imageCheckedChanged(const bb::cascades::Image& image);
      /*!
      * @brief Emitted when the source of @c Image that is used for the checked state changes.
      *
      * @param imageSource The new source.
       *
       * @since BlackBerry 10.0.0
      */
      void imageSourceCheckedChanged(const QUrl& imageSource);

      /*! @cond PRIVATE */
      void imageCheckedChanged(QVariant image);
      /*! @endcond */

      /*!
      * @brief Emitted when the @c Image that is used for the disabled and unchecked state changes.
      *
      * @param image The new image. If no image is set, an empty image will be returned (see Image::isNull()).
      *
      * @xmlonly
      * <qml>
      * <param name="image" type="QVariant"/>
      * </qml>
      * @endxmlonly
       *
       * @since BlackBerry 10.0.0
      */
      void imageDisabledUncheckedChanged(const bb::cascades::Image& image);
      /*!
      * @brief Emitted when the source of @c Image that is used for the disabled and unchecked state changes.
      *
      * @param imageSource The new source.
       *
       * @since BlackBerry 10.0.0
      */
      void imageSourceDisabledUncheckedChanged(const QUrl& imageSource);

      /*! @cond PRIVATE */
      void imageDisabledUncheckedChanged(QVariant image);
      /*! @endcond */

      /*!
      * @brief Emitted when the @c Image that is used for the disabled and checked state changes.
      *
      * @param image The new image. If no image is set, an empty image will be returned (see Image::isNull()).
      *
      * @xmlonly
      * <qml>
      * <param name="image" type="QVariant"/>
      * </qml>
      * @endxmlonly
       *
       * @since BlackBerry 10.0.0
      */
      void imageDisabledCheckedChanged(const bb::cascades::Image& image);
      /*!
      * @brief Emitted when the source of @c Image that is used for the disabled and checked state changes.
      *
      * @param imageSource The new source.
       *
       * @since BlackBerry 10.0.0
      */
      void imageSourceDisabledCheckedChanged(const QUrl& imageSource);

      /*! @cond PRIVATE */
      void imageDisabledCheckedChanged(QVariant image);
      /*! @endcond */

      /*!
      * @brief Emitted when the @c Image that is used for the pressed unchecked state changes.
      *
      * @param image The new image. If no image is set, an empty image will be returned (see Image::isNull()).
      *
      * @xmlonly
      * <qml>
      * <param name="image" type="QVariant"/>
      * </qml>
      * @endxmlonly
       *
       * @since BlackBerry 10.0.0
      */
      void imagePressedUncheckedChanged(const bb::cascades::Image& image);
      /*!
      * @brief Emitted when the source of @c Image that is used for the pressed and unchecked state changes.
      *
      * @param imageSource The new source.
       *
       * @since BlackBerry 10.0.0
      */
      void imageSourcePressedUncheckedChanged(const QUrl& imageSource);

      /*! @cond PRIVATE */
      void imagePressedUncheckedChanged(QVariant image);
      /*! @endcond */

      /*!
      * @brief Emitted when the @c Image that is used for the pressed and checked state changes.
      *
      * @param image The new image. If no image is set, an empty image will be returned (see Image::isNull()).
      *
      * @xmlonly
      * <qml>
      * <param name="image" type="QVariant"/>
      * </qml>
      * @endxmlonly
       *
       * @since BlackBerry 10.0.0
      */
      void imagePressedCheckedChanged(const bb::cascades::Image& image);
      /*!
      * @brief Emitted when the source of @c Image that is used for the pressed and checked state changes.
      *
      * @param imageSource The new source.
       *
       * @since BlackBerry 10.0.0
      */
      void imageSourcePressedCheckedChanged(const QUrl& imageSource);

      /*! @cond PRIVATE */
      void imagePressedCheckedChanged(QVariant image);
      /*! @endcond */



    private:
      Q_DECLARE_PRIVATE(ImageToggleButton)
      Q_DISABLE_COPY(ImageToggleButton)

      /*! @cond PRIVATE */
      typedef ImageToggleButton ThisClass;
      typedef AbstractToggleButton BaseClass;
      /*! @endcond */


      /*! @cond PRIVATE */

      /*!
      * Returns the image used in the Default state
      *
      * This is a private function needed by the QML. The returned @c QVariant is always an @c Image.
      *
      * @warning The client must not call this function, @c image() should be called instead.
      *
      * @return A QVariant containing the Image for the ImageVIew or 0 if no image was set (or was reset).
      */
      const QVariant imageQmlDefault() const;
      /*!
      * Sets the image for the in the Default state
      * The QVariant image can either be of type Image or a QString name. This is a private function
      * encapsulating setImage() needed by the QML.
      * @warning The client must not call this function, instead setImage() should be called.
      *
      * @param image A QVariant container either the Image or QString name of the image to set for
      * the ImageView.
      */
      Q_SLOT void setImageQmlDefault(const QVariant & image);

      /*!
      * Returns the image used in the Checked state
      *
      * This is a private function needed by the QML. The returned QVariant is always an Image.
      * @warning The client must not call this function, instead image() should be called.
      *
      * @return A QVariant containing the Image for the ImageVIew or 0 if no image was set (or was reset).
      */
      const QVariant imageQmlChecked() const;
      /*!
      * Sets the image for the in the Checked state
      * The QVariant image can either be of type Image or a QString name. This is a private function
      * encapsulating setImage() needed by the QML.
      * @warning The client must not call this function, instead setImage() should be called.
      *
      * @param image A QVariant container either the Image or QString name of the image to set for
      * the ImageView.
      */
      Q_SLOT void setImageQmlChecked(const QVariant & image);

      /*!
      * Returns the image used in the Disabled, Unchecked state
      *
      * This is a private function needed by the QML. The returned QVariant is always an Image.
      * @warning The client must not call this function, instead image() should be called.
      *
      * @return A QVariant containing the Image for the ImageVIew or 0 if no image was set (or was reset).
      */
      const QVariant imageQmlDisabledUnchecked() const;
      /*!
      * Sets the image for the in the Disabled, Unchecked state
      * The QVariant image can either be of type Image or a QString name. This is a private function
      * encapsulating setImage() needed by the QML.
      * @warning The client must not call this function, instead setImage() should be called.
      *
      * @param image A QVariant container either the Image or QString name of the image to set for
      * the ImageView.
      */
      Q_SLOT void setImageQmlDisabledUnchecked(const QVariant & image);

      /*!
      * Returns the image used in the Disabled, Checked state
      *
      * This is a private function needed by the QML. The returned QVariant is always an Image.
      * @warning The client must not call this function, instead image() should be called.
      *
      * @return A QVariant containing the Image for the ImageVIew or 0 if no image was set (or was reset).
      */
      const QVariant imageQmlDisabledChecked() const;
      /*!
      * Sets the image for the in the Disabled, Checked state
      * The QVariant image can either be of type Image or a QString name. This is a private function
      * encapsulating setImage() needed by the QML.
      * @warning The client must not call this function, instead setImage() should be called.
      *
      * @param image A QVariant container either the Image or QString name of the image to set for
      * the ImageView.
      */
      Q_SLOT void setImageQmlDisabledChecked(const QVariant & image);

      /*!
      * Returns the image used in the Pressed, Unchecked state
      *
      * This is a private function needed by the QML. The returned QVariant is always an Image.
      * @warning The client must not call this function, instead image() should be called.
      *
      * @return A QVariant containing the Image for the ImageVIew or 0 if no image was set (or was reset).
      */
      const QVariant imageQmlPressedUnchecked() const;
      /*!
      * Sets the image for the in the Pressed, Unchecked state
      * The QVariant image can either be of type Image or a QString name. This is a private function
      * encapsulating setImage() needed by the QML.
      * @warning The client must not call this function, instead setImage() should be called.
      *
      * @param image A QVariant container either the Image or QString name of the image to set for
      * the ImageView.
      */
      Q_SLOT void setImageQmlPressedUnchecked(const QVariant & image);

      /*!
      * Returns the image used in the Pressed, Checked state
      *
      * This is a private function needed by the QML. The returned QVariant is always an Image.
      * @warning The client must not call this function, instead image() should be called.
      *
      * @return A QVariant containing the Image for the ImageVIew or 0 if no image was set (or was reset).
      */
      const QVariant imageQmlPressedChecked() const;
      /*!
      * Sets the image for the in the Pressed, Checked state
      * The QVariant image can either be of type Image or a QString name. This is a private function
      * encapsulating setImage() needed by the QML.
      * @warning The client must not call this function, instead setImage() should be called.
      *
      * @param image A QVariant container either the Image or QString name of the image to set for
      * the ImageView.
      */
      Q_SLOT void setImageQmlPressedChecked(const QVariant & image);

      /*! @endcond */

    public:
      /*!
      * @brief A builder template for constructing a @c %ImageToggleButton.
      *
      * See @c %ImageToggleButton::create() for getting a concrete Builder for constructing a ImageToggleButton.
      *
      * @since BlackBerry 10.0.0
      */ 
      template <typename BuilderType, typename BuiltType>
      class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType>
      {
      protected:
        TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node)
        {
        }
      public:
        /*!
        * @brief Sets the image for the Default state.
        *
        * @param image The image to display.
        *
        * @since BlackBerry 10.0.0
        */
        BuilderType& imageDefault(const Image& image) {
          this->instance().setImageDefault(image);
          return this->builder();
        }
        /*!
        * @brief Sets the image for the Default state, identified by its filePath.
        *
        * This is a convenience function for setting an image
        * identified by its filePath.
        *
        * @param imageFilePath The filePath of the image to display.
        *
        * @since BlackBerry 10.0.0
        */
        BuilderType& imageDefault(const QUrl &imageFilePath) {
          return imageDefault(Image(imageFilePath));
        }


        /*!
        * @brief Sets the image for the checked state.
        *
        * @param image The image to display.
        *
        * @since BlackBerry 10.0.0
        */
        BuilderType& imageChecked(const Image& image) {
          this->instance().setImageChecked(image);
          return this->builder();
        }
        /*!
        * @brief Sets the image for the checked state, identified by its filePath.
        *
        * This is a convenience function for setting an image
        * identified by its filePath.
        *
        * @param imageFilePath The filePath of the image to display.
        *
        * @since BlackBerry 10.0.0
        */
        BuilderType& imageChecked(const QUrl &imageFilePath) {
          return imageChecked(Image(imageFilePath));
        }


        /*!
        * @brief Sets the image for the disabled and unchecked state.
        *
        * @param image The image to display.
        *
        * @since BlackBerry 10.0.0
        */
        BuilderType& imageDisabledUnchecked(const Image& image) {
          this->instance().setImageDisabledUnchecked(image);
          return this->builder();
        }

        /*!
        * @brief Sets the image for the disabled and unchecked state, identified by its filePath.
        *
        * This is a convenience function for setting an image
        * identified by its filePath.
        *
        * @param imageFilePath The filePath of the image to display.
        *
        * @since BlackBerry 10.0.0
        */
        BuilderType& imageDisabledUnchecked(const QUrl &imageFilePath) {
          return imageDisabledUnchecked(Image(imageFilePath));
        }
        /*!
        * @brief Sets the image for the disabled and checked state.
        *
        * @param image The image to display.
        *
        * @since BlackBerry 10.0.0
        */
        BuilderType& imageDisabledChecked(const Image& image) {
          this->instance().setImageDisabledChecked(image);
          return this->builder();
        }

        /*!
        * @brief Sets the image for the disabled and checked state, identified by its filePath.
        *
        * This is a convenience function for setting an image
        * identified by its filePath.
        *
        * @param imageFilePath The filePath of the image to display.
        *
        * @since BlackBerry 10.0.0
        */
        BuilderType& imageDisabledChecked(const QUrl &imageFilePath) {
          return imageDisabledChecked(Image(imageFilePath));
        }

        /*!
        * @brief Sets the image for the pressed and unchecked state.
        *
        * @param image The image to display.
        *
        * @since BlackBerry 10.0.0
        */
        BuilderType& imagePressedUnchecked(const Image& image) {
          this->instance().setImagePressedUnchecked(image);
          return this->builder();
        }

        /*!
        * @brief Sets the image for the pressed and unchecked state, identified by its filePath.
        *
        * This is a convenience function for setting an image
        * identified by its filePath.
        *
        * @param imageFilePath The filePath of the image to display.
        *
        * @since BlackBerry 10.0.0
        */
        BuilderType& imagePressedUnchecked(const QUrl &imageFilePath) {
          return imagePressedUnchecked(Image(imageFilePath));
        }
        /*!
        * @brief Sets the image for the pressed and checked state.
        *
        * @param image The image to display.
        *
        * @since BlackBerry 10.0.0
        */
        BuilderType& imagePressedChecked(const Image& image) {
          this->instance().setImagePressedChecked(image);
          return this->builder();
        }

        /*!
        * @brief Sets the image for the pressed and checked state, identified by its filePath.
        *
        * This is a convenience function for setting an image
        * identified by its filePath.
        *
        * @param imageFilePath The filePath of the image to display.
        *
        * @since BlackBerry 10.0.0
        */
        BuilderType& imagePressedChecked(const QUrl &imageFilePath) {
          return imagePressedChecked(Image(imageFilePath));
        }

      };

      /*!
      * @brief A concrete builder class for constructing a @c %ImageToggleButton.
      *
      * @see ImageToggleButton::create() for getting a concrete Builder for constructing a ImageToggleButton.
      *
      * @since BlackBerry 10.0.0
      */ 
      class Builder : public TBuilder<Builder, ImageToggleButton>
      {
      public:
        explicit Builder() : TBuilder<Builder, ImageToggleButton>(new ImageToggleButton())
        {
        }
      };

      /*!
      * @brief Creates and returns a Builder for constructing a @c %ImageToggleButton.
      *
      * @return A Builder for constructing a ImageToggleButton.
       *
       * @since BlackBerry 10.0.0
      */
      static Builder create()
      {
        return Builder();
      }
    };
  }
}

QML_DECLARE_TYPE(bb::cascades::ImageToggleButton)

#endif

