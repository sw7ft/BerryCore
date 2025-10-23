/* Copyright (c) 2013 BlackBerry. All rights reserved. */

#ifndef cascades_button_h
#define cascades_button_h

#include <QtCore/QString>

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/controls/abstractbutton.h>
#include <bb/cascades/resources/image.h>
#include <bb/cascades/resources/controlappearance.h>

namespace bb {
  namespace cascades {

    class ButtonPrivate;
    class Container;
    class ColorPaint;

    /*!
     *
     * @brief A clickable button with a fixed height and an optional image, text, color and appearance.
     *
     * A @c Button is used to intercept touch events on the screen in order to affect app
     * behavior. When a button is tapped it emits a @c Button::clicked() signal that you can
     * capture and respond to in your app. For example, you can connect the @c clicked() signal to
     * the slot of another object, or use the @c onClicked() signal handler in QML to respond
     * to the button click.
     *
     * The @c %Button class provides functions for setting or resetting the text, image, color and
     * appearance of a button (the default state is no text, no image, no color and default appearance).
     * When the text, image, color or appearance of a button is changed, corresponding signals are emitted
     * (@c Button::textChanged(), @c Button::imageChanged(), @c Button::colorChanged() or
     * @c Button::appearanceChanged(), respectively).
     *
     * The appearance of a button behaves as follows:
     * - By default, the appearance of a button is the @c ControlAppearance::Default.
     * - Changing appearance does not override the @c Button::color property.
     * For example, if the color is set to red,
     * setting the appearance to @c ControlAppearance::Primary will not change the buttons color.
     * But if the @c Button::color property is reset to @ null, the appearance will affect the buttons color.
     *
     * A button with a primary appearance:
     * @image html button_default_primary.png
     *
     * Button text has a predefined font and font size.
     * The text color is auto-adjusted to be contrasted background color.
     * The aspect ratio of the button's image scales to fit inside the button. A button with text but
     * no image, or an image with no text, will display the text or
     * image centered on the button, whereas a button with both text and image will be
     * left-aligned, as can be seen in the examples below.
     *
     * A button with text:
     * @image html button_txt.png
     *
     * A button with an image and text:
     * @image html button_str_img.png
     *
     * A button with only an image:
     * @image html button_img.png
     *
     * The color property can be used to specify a specific color for a @c %Button.
     * If the color is set it overrides the color associated with the appearance.
     * see an example,
     *
     * A button with red color:
     * @image html button_red_color.png
     *
     * The size of a button behaves as follows:
     * - By default, the width of a button has a device-dependent built-in value. It is increased
     * automatically to fit an image and text if necessary.
     * - The width is adjustable using the @c Control::preferredWidth, @c Control::minWidth,
     * and @c Control::maxWidth properties.
     * - @c Control::preferredWidth is ignored if the preferred width is smaller
     * than is necessary to fit an image and text.
     * - Setting the maximum width allows the width of the button to be smaller than the width required
     * to show the whole button text (and image, if it is also
     *   visible), causing the text to be truncated. However, the maximum width cannot be set
     * small enough to cause the image to be truncated.
     * - The height of the button is fixed, so the properties @c Control::preferredHeight, @c Control::minHeight,
     * and @c Control::maxHeight are not used.
     *
     * Here's how to create a @c %Button with some text, color, and an image, using the builder pattern:
     *
     * @snippet tad/examples/controls/button/src/ButtonExamples.cpp button1
     *
     * Here's how to create a @c %Button and then set the text, color, and image properties:
     *
     * @snippet tad/examples/controls/button/src/ButtonExamples.cpp button2
     *
     * Here's how to create a @c %Button with some text, red color, and an image, in QML:
     *
     * @snippet tad/examples/controls/button/assets/main.qml button_qml
     *
     * Here's how to set and reset the color of a @c %Button:
     *
     * @snippet tad/examples/controls/button/src/ButtonExamples.cpp button5
     *
     * Here's how to create a @c %Button with primary appearance, using the builder pattern:
     *
     * @snippet tad/examples/controls/button/src/ButtonExamples.cpp button6
     *
     * @xmlonly
     * <apigrouping group="User interface/Core controls"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT Button : public AbstractButton {
    private:
      Q_OBJECT

      /*!
       * @brief The visual appearance of the button.
       *
       * The default value is @c %ControlAppearance::Default
       *
       * @since BlackBerry 10.3.0
       */
      Q_PROPERTY(bb::cascades::ControlAppearance::Type appearance READ appearance WRITE setAppearance NOTIFY appearanceChanged REVISION 3 FINAL)

      /*!
       * @brief A text string to display on the button.
       *
       * The default value is @c QString::Null, indicating that no text is set.
       *
       * @since BlackBerry 10.0.0
       */
      Q_PROPERTY(QString text READ text WRITE setText
                 RESET resetText NOTIFY textChanged FINAL)

      /*!
       * @brief An image to display on the button.
       *
       * The default value is an empty image, indicating that no image is set.
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
       * @brief The location of an image to display on the button.
       *
       * If no image is set, an invalid @c QUrl is returned.
       * When the image source changes, the @c imageSourceChanged() signal is emitted.
       *
       * @since BlackBerry 10.0.0
       */
      Q_PROPERTY(QUrl imageSource READ imageSource WRITE setImageSource
                 RESET resetImageSource NOTIFY imageSourceChanged FINAL)

      /*!
       * @brief A color to display on the button.
       *
       * The default value is an invalid @c QVariant.
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
      Q_PROPERTY(QVariant color READ color WRITE setColor RESET resetColor NOTIFY colorChanged REVISION 3 FINAL)
    public:
      /*!
       * @brief Constructs a clickable button and assigns a parent container.
       *
       * The ownership of the button is transferred to the parent if a parent is specified.
       *
       * @param parent The parent container, or @c 0. This parameter is optional. The default is @c 0 if you don't specify a parent.
       *
       * @since BlackBerry 10.0.0
       */
      explicit Button(Container * parent = 0);

      /*!
       * @brief Destroys the button.
       *
       *
       * @since BlackBerry 10.0.0
       */
      virtual ~Button();

      /*!
       * @brief Returns the text that is displayed on this button.
       *
       * @return A string that represents the text on the button, or @c QString::Null if no text is set.
       *
       * @since BlackBerry 10.0.0
       */
      const QString text() const;

      /*!
       * @brief Sets the text to display on this button.
       *
       * A button will attempt to resize itself to accommodate the text, if necessary.
       * The button may not be able to resize depending on the @c Control::maxWidth property
       * and other layout restrictions (for example, not enough space among other controls).
       * In this case, the text is truncated.
       *
       * @param text A text string to set as the text on the button, or QString::Null to display no text.
       *
       * @since BlackBerry 10.0.0
       */
      Q_SLOT void setText(const QString & text);

      /*!
       * @brief Resets the text for this button to @c QString::Null.
       *
       * @since BlackBerry 10.0.0
       */
      Q_SLOT void resetText();

      /*!
       * @brief Returns the image that is displayed on this button.
       *
       * @return The @c Image that is displayed on the button, or an empty image if no image is set.
       *
       * @since BlackBerry 10.0.0
       */
      Image image() const;

      /*!
       * @brief Sets the image to display on this button.
       *
       * The @c imageChanged() signal is emitted if the @c image parameter specifies an image
       * that is different than the previously set image for this button.
       *
       * @param image The @c Image to display on this button, or an empty image to display no image.
       *
       * @since BlackBerry 10.0.0
       */
      Q_SLOT void setImage(const bb::cascades::Image& image);

      /*!
       * @brief Resets the image for this button to an empty image.
       *
       * The @c imageChanged() signal is emitted if a valid image was set on the button and this
       * function successfully resets the image.
       *
       * @since BlackBerry 10.0.0
       */
      Q_SLOT void resetImage();


      /*!
       * @brief Returns the image source set on the button.
       *
       * @return The source of the displayed image.
       *
       * @since BlackBerry 10.0.0
       */
      QUrl imageSource() const;

      /*!
       * @brief Sets the image source for the button.
       *
       * The @c imageSourceChanged() signal is emitted if the currently set image source changes.
       *
       * An invalid @c QUrl indicates no image has been set.
       *
       * @param source The image URL.
       *
       * @since BlackBerry 10.0.0
       */
      Q_SLOT void setImageSource(const QUrl &source);

      /*!
       * @brief Resets the @c Image on the button to its default, meaning that no image is set.
       *
       * The @c imageSourceChanged() signal is emitted if the currently set image source changes.
       *
       * @since BlackBerry 10.0.0
       */
      Q_SLOT void resetImageSource();

      /*!
       * @brief Returns the color that is displayed on this button.
       *
       * The returned @c QVariant will either be invalid or contain values of type @c Color or @c ColorPaint.
       * An invalid @c %QVariant signifies a color has not been set.
       *
       * Use @c QVariant::canConvert<Type T>() to find the type, and
       * then use @c QVariant::value<Type T>() to get the value.
       *
       * @return The @c %Color or @c %ColorPaint that is displayed on the button, or an invalid @c %QVariant.
       *
       * @since BlackBerry 10.3.0
       */
      Q_REVISION(3)
      QVariant color() const;

      /*!
       * @brief Sets the color to display on this button.
       *
       * @param color The @c Color or @c ColorPaint to display on this button.
       *
       * @since BlackBerry 10.3.0
       */
      Q_REVISION(3)
      Q_SLOT void setColor(const ColorPaint& color);

      /*!
       * @brief Resets the color for this button to an invalid @c QVariant.
       *
       * @since BlackBerry 10.3.0
       */
      Q_REVISION(3)
      Q_SLOT void resetColor();

      /*!
       * @brief Returns the @c ControlAppearance::Type that is displayed on this button.
       *
       * @return The @c %ControlAppearance::Type that is displayed on the button.
       *
       * @since BlackBerry 10.3.0
       */
      Q_REVISION(3)
      bb::cascades::ControlAppearance::Type appearance() const;

      /*!
       * @brief Sets the @c ControlAppearance::Type to display on this button.
       *
       * @param newAppearance The @c %ControlAppearance::Type to display on this button.
       *
       * @since BlackBerry 10.3.0
       */
      Q_REVISION(3)
      Q_SLOT void setAppearance(bb::cascades::ControlAppearance::Type newAppearance);

      /*!
       * @brief Resets the @c %ControlAppearance::Type for this button.
       * The appearance property will be set to default value, @c %ControlAppearance::Default
       *
       * @since BlackBerry 10.3.0
       */
      Q_REVISION(3)
      Q_SLOT void resetAppearance();

    Q_SIGNALS:
      /*!
       * @brief Emitted when the text on the button changes.
       *
       * @param text The new text string for this button, or @c QString::Null if no text is set.
       *
       * @since BlackBerry 10.0.0
       */
      void textChanged(QString text);

      /*!
       * @brief Emitted when the image for this button changes.
       *
       * @param image The new image for this button, or an empty image if no image is set.
       *
       * @xmlonly
       * <qml>
       * <param name="image" type="QVariant"/>
       * </qml>
       * @endxmlonly
       *
       * @since BlackBerry 10.0.0
       */
      void imageChanged(const bb::cascades::Image& image);

      /*!
       * @brief Emitted when the image source changes.
       *
       * @param image The image URL.
       *
       * @since BlackBerry 10.0.0
       */
      void imageSourceChanged(const QUrl& image);

      /*! @cond PRIVATE */
      /*!
       * Emitted when the image for the button changes. This is used for QML.
       */
      void imageChanged(const QVariant& image);
      /*! @endcond */

      /*!
       * @brief Emitted when the color for this button changes.
       *
       * @param color The new color for this button
       *
       * @since BlackBerry 10.3.0
       */
      Q_REVISION(3)
      void colorChanged(const bb::cascades::ColorPaint& color);

      /*! @cond PRIVATE */
      /*!
       * @brief Emitted when the color changes.
       *
       * @since BlackBerry 10.3.0
       */
      Q_REVISION(3)
      void colorChanged(const QVariant& color);
      /*! \endcond */

      /*!
       * @brief Emitted when the appearance changes.
       *
       * @param newAppearance The new appearance type for this button.
       *
       * @since BlackBerry 10.3.0
       */
      Q_REVISION(3)
      void appearanceChanged(bb::cascades::ControlAppearance::Type newAppearance);
    private:
      /*! @cond PRIVATE */

      /*!
       * @brief Sets the color to display on this button.
       *
       * @param color The color to display on this button.
       *
       * @since BlackBerry 10.3.0
       */
      Q_REVISION(3)
      Q_SLOT void setColor(const QVariant& color);

      /*!
       * @brief Returns the image for the button.
       *
       * This is a private function needed by the QML. The returned @c QVariant is always an @c Image object.
       * @warning The client must not call this function, instead @c image() should be called.
       *
       * @return A @c QVariant containing the image for the button, or an empty image if no image was set (or was reset).
       */
      QVariant imageQml() const;

      /*!
       * @brief Sets the image for the button.
       *
       * The @c QVariant image can either be an @c Image or a @c QString name. This is a private function
       * encapsulating @c setImage() needed by the QML.
       * @warning The client must not call this function, instead @c setImage() should be called.
       *
       * @param image A QVariant container either the Image or QString name of the image to set for
       * the button.
       */
      Q_SLOT void setImageQml(const QVariant & image);

      /*! \endcond */

      Q_DECLARE_PRIVATE(Button)
      Q_DISABLE_COPY(Button)

      /*! \cond PRIVATE */
      typedef Button ThisClass;  // The class in which scope we're currently inside
      typedef AbstractButton BaseClass; // References the class which ThisClass derives from
      /*! \endcond */

    public:
      /*!
       * @brief A builder template for constructing a button.
       *
       * To retrieve the builder, call @c Button::create().
       *
       * @since BlackBerry 10.0.0
       */
      template <typename BuilderType, typename BuiltType>
      class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType> {
      protected:
        TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node) {}
      public:

        /*!
         * @brief Sets the text for this button.
         *
         * @param text The text string to set for the button, or @c QString::Null to display no text on the button.
         *
         * @since BlackBerry 10.0.0
         */
        BuilderType& text(const QString &text) {
          this->instance().setText(text);
          return this->builder();
        }

        /*!
         * @brief Sets the image for this button.
         *
         * The button does not take ownership of the image once it's set.
         *
         * @param image The image to set, or an empty image to display no image.
         *
         * @since BlackBerry 10.0.0
         */
        BuilderType& image(const Image& image) {
          this->instance().setImage(image);
          return this->builder();
        }

        /*!
         * @brief Sets the image for this button, identified by its name.
         *
         * @param url The name of the image to set for this button.
         *
         * @since BlackBerry 10.0.0
         */
        BuilderType& imageSource(const QUrl &url) {
          return image(Image(url));
        }

        /*!
         * @brief Sets the color for this button, identified by its value.
         *
         * @param color The value of the color to set for this button.
         *
         * @since BlackBerry 10.3.0
         */
        BuilderType& color(const bb::cascades::ColorPaint &color) {
          this->instance().setColor(color);
          return this->builder();
        }

        /*!
         * @brief Sets @c %ControlAppearance::Type for this button, identified by its value.
         *
         * @param appearance The appearance type to set for this button.
         *
         * @since BlackBerry 10.3.0
         */
        BuilderType& appearance(bb::cascades::ControlAppearance::Type appearance) {
          this->instance().setAppearance(appearance);
          return this->builder();
        }

        /*!
         * A convenience method for connecting the passed receiver's slot to
         * the @c clicked() signal with the default connection type
         * @c Qt::AutoConnection.
         *
         * Example:
         * @code
         * Button *button = Button::create()
         *     .onClicked(this, SLOT(onClicked()));
         * @endcode
         *
         * @param receiver A non-null receiver object.
         * @param method A non-null name of the slot in the receiver object to connect to.
         *
         * @see BaseObject::TBuilder::connect()
         *
         * @since BlackBerry 10.0.0
         */
        BuilderType& onClicked(const QObject* receiver, const char *method) {
          this->connect(SIGNAL(clicked()), receiver, method);
          return this->builder();
        }
      };

      /*!
       * @brief A builder that constructs a button.
       *
       * To retrieve the builder, call @c Button::create().
       *
       * @since BlackBerry 10.0.0
       */
      class Builder : public TBuilder<Builder, Button> {
      public:
        explicit Builder() : TBuilder<Builder, Button>(new Button()) {}
      };

      /*!
       * @brief Creates and returns a builder for constructing a button.
       *
       * Using the builder to create a @c Button:
       *
       * @snippet tad/examples/controls/button/src/ButtonExamples.cpp button1
       *
       * @return A builder used for constructing a button.
       *
       * @since BlackBerry 10.0.0
       */
      static Builder create() {
        return Builder();
      }

      /*!
       * @brief Creates and returns a builder for constructing a button with text.
       *
       * Using the builder to create a @c %Button:
       *
       * @snippet tad/examples/controls/button/src/ButtonExamples.cpp button3
       *
       * This builder is a convenience constructor for creating a @c %Button with text. This
       * is equivalent to the following:
       *
       * @snippet tad/examples/controls/button/src/ButtonExamples.cpp button4
       *
       * @param text A text string that represents the text to display on the button, or @c QString::Null to
       * display no text on the button.
       *
       * @return A Builder used to create a button with text.
       *
       * @since BlackBerry 10.0.0
       */
      static Builder create(const QString & text) {
        return Builder().text(text);
      }
    };
  }
}

QML_DECLARE_TYPE(bb::cascades::Button)

#endif
