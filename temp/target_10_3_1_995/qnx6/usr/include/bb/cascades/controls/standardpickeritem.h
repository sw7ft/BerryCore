/* Copyright (C) 2012-2013 Research In Motion Limited.  */

#ifndef CASCADES_STANDARDPICKERITEM_H
#define CASCADES_STANDARDPICKERITEM_H

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/controls/control.h>
#include <bb/cascades/resources/image.h>

namespace bb {
    namespace cascades {

    class Container;
    class Paint;
    class StandardPickerItemPrivate;

    /*!
     * @brief An item with a set of common properties to be displayed in a @c Picker.
     *
     * @c %StandardPickerItem consists of an image, title text and background color.
     * Each property is optional.
     *
     * The size of the @c %StandardPickerItem behaves as follows:
     * - By default, the width of the control is adjusted automatically to fill its parent container.
     * - The width is adjustable using the @c Control::preferredWidth, @c Control::minWidth and
     * @c Control::maxWidth properties.
     * - The height is fixed, so the properties @c Control::preferredHeight, @c Control::minHeight and
     * @c Control::maxHeight are not used.
     *
     * @xmlonly
     * <apigrouping group="User interface/Core controls"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.1.0
     */
    class BBCASCADES_EXPORT StandardPickerItem : public Control
    {
        Q_OBJECT

    public:
        /*!
         * @brief A title text set on this picker item.
         *
         * The default value is @c QString::NULL, indicating no title text is set.
         *
         * @since BlackBerry 10.1.0
         */
        Q_PROPERTY(QString title READ title WRITE setTitle RESET resetTitle
                   NOTIFY titleChanged FINAL)

        /*!
         * @brief The image set on the @c %StandardPickerItem.
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
         * @since BlackBerry 10.1.0
         */
        Q_PROPERTY(QVariant image READ imageQml WRITE setImageQml
                   RESET resetImage NOTIFY imageChanged FINAL)

        /*!
         * @brief An image set on this picker item.
         *
         * If no image is set, an invalid @c QUrl will be returned.
         * When changing the image source the @c imageSourceChanged() signal will be emitted.
         *
         *
         * @since BlackBerry 10.1.0
         */
        Q_PROPERTY(QUrl imageSource READ imageSource WRITE setImageSource
                   RESET resetImageSource NOTIFY imageSourceChanged FINAL)

        /*!
         * @brief A Paint object that specifies the background fill for the container.
         *
         * The default is the
         * paint returned by @c SystemDefaults::containerBackground().
         *
         * @xmlonly
         * <qml>
         * <variant type="bb::cascades::Paint"/>
         * </qml>
         * @endxmlonly
         *
         * @since BlackBerry 10.1.0
         */
        Q_PROPERTY(QVariant background READ background WRITE setBackgroundQML RESET resetBackground NOTIFY backgroundChanged FINAL)

        /*!
         * @brief Constructs a picker item that is owned by the specified parent.
         *
         * If parent is @c 0 or is not specified, this picker item will not have an owner.
         *
         * @param parent The parent container that will be the owner of this picker item or 0.
         *
         * @since BlackBerry 10.1.0
         */
        explicit StandardPickerItem(Container * parent = 0);

        /*!
         * @brief Destructs this picker item.
         *
         * @since BlackBerry 10.1.0
         */
        virtual ~StandardPickerItem();

        /*!
         * @brief Returns the @c Image displayed in the picker item.
         *
         * @return The image being displayed, or an invalid image if none is set.
         *
         * @since BlackBerry 10.1.0
         */
        bb::cascades::Image image() const;

        /*!
         * @brief Sets the @c Image for the picker item.
         *
         * An invalid image indicates no image.
         *
         * @param image The image to set.
         *
         * @since BlackBerry 10.1.0
         */
        Q_SLOT void setImage(const bb::cascades::Image& image);

        /*!
         * @brief Resets the @c Image in the picker item to its default, meaning that no image is set.
         *
         * @since BlackBerry 10.1.0
         */
        Q_SLOT void resetImage();

        /*!
         * @brief Returns the image source.
         *
         * @return The source of the displayed image.
         *
         * @since BlackBerry 10.1.0
         */
        QUrl imageSource() const;

        /*!
         * @brief Sets the new image on this picker item.
         *
         * An invalid @c QUrl indicates no image.
         * This function emits an @c imageSourceChanged() signal if the currently set image source changes.
         *
         * @param source The image url.
         *
         * @since BlackBerry 10.1.0
         */
        Q_SLOT void setImageSource(const QUrl &source);

        /*!
         * @brief Resets the image in this picker item to its default, meaning that no image is set.
         *
         * This function emits an @c imageSourceChanged() signal if the currently set image source changes.
         *
         * @since BlackBerry 10.1.0
         */
        Q_SLOT void resetImageSource();

        /*!
         * @brief Returns the status text set on this picker item.
         *
         * @c QString::NULL is returned when status text was not set.
         *
         * \return The status set on this picker item.
         *
         * @since BlackBerry 10.1.0
         */
        QString title() const;

        /*!
         * @brief Sets the new title text on this picker item to a passed in string.
         *
         * The @c titleChanged() signal is emitted if the title text gets changed.
         *
         * \param title The new title text for this picker item.
         *
         * @since BlackBerry 10.1.0
         */
        Q_SLOT void setTitle(const QString & title);

        /*!
         * @brief Resets the title text on this picker item to a default value of Qstring::NULL.
         *
         * The @c titleChanged() signal is emitted if the title text gets reset.
         *
         * @since BlackBerry 10.1.0
         */
        Q_SLOT void resetTitle();

        /*!
         * @brief Sets the #background for the picker item.
         *
         * Setting a @c null paint is equivalent to calling #resetBackground();
         *
         * Valid subclasses to use as paint:
         *
         * - ColorPaint
         * - ImagePaint
         *
         * @param paint The new background.
         *
         * @since BlackBerry 10.1.0
         */
        Q_SLOT void setBackground(const bb::cascades::Paint& paint);

        /*!
         * @brief Returns the current #background of the picker item.
         *
         * Use @c QVariant::canConvert<Type T>() to find actual type, and then @c QVariant::value<Type T>()
         * to get the value.
         *
         * For example:
         * @code
         * QVariant v = pickerItem->background();
         * if (v.canConvert<Color>()) {
         *   Color c = v.value<Color>();
         * }
         * @endcode
         *
         * @return The current background paint, wrapped in a @c QVariant.
         *
         * @since BlackBerry 10.1.0
         */
        QVariant background() const;

        /*!
         * @brief Resets the picker item's #background to the default returned
         * by @c SystemDefaults::containerBackground().
         *
         * @since BlackBerry 10.1.0
         */
        Q_SLOT void resetBackground();

    Q_SIGNALS:
        /*!
         * @brief Emitted when this picker item's title text changes.
         *
         * @param title The new title string or @c QString::Null if changed to an empty @c title.
         *
         * @since BlackBerry 10.1.0
         */
        void titleChanged(const QString &title);

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
         * @since BlackBerry 10.1.0
         */
        void imageChanged(const bb::cascades::Image &image);

        /*! @cond PRIVATE */
        void imageChanged(const QVariant &image);
        /*! @endcond */

        /*!
         * @brief Emitted when the image source changes.
         *
         * @param imageSource The new image source or an invalid @c QUrl if no image is set.
         *
         * @since BlackBerry 10.1.0
         */
        void imageSourceChanged(const QUrl& imageSource);

        /*!
         * @brief Emitted when the #background has changed.
         *
         * @param background The new background.
         *
         * @xmlonly
         * <qml>
         * <param name="background" type="QVariant"/>
         * </qml>
         * @endxmlonly
         *
         * @since BlackBerry 10.1.0
         */
        void backgroundChanged(const bb::cascades::Paint& background);

        /*! @cond PRIVATE */
        /*!
         * @brief Emitted when the #background has changed.
         *
         * @param background The new background.
         */
        void backgroundChanged(const QVariant &background);
        /*! @endcond */

    private:
        Q_DECLARE_PRIVATE(StandardPickerItem)
        Q_DISABLE_COPY(StandardPickerItem)

        Q_SLOT void setBackgroundQML(const QVariant &paint);

    public:
        /*! @cond PRIVATE */

        /*!
         * Returns the image for the @c StandardPickerItem.
         *
         * This is a private function needed by the QML. The returned QVariant is always an Image.
         * @warning The client must not call this function, instead @c image() should be called.
         *
         * @return A @c QVariant containing the Image for the @c StandardPickerItem or @c 0 if no image was set (or was reset).
         */
        QVariant imageQml() const;

        /*!
         * Sets the image for the @c StandardPickerItem.
         * The @c QVariant image can either be of type Image or a @c QString name. This is a private function
         * encapsulating @c setImage() needed by the QML.
         * @warning The client must not call this function, instead @c %setImage() should be called.
         *
         * @param image A @c %QVariant container either the @c Image or @c %QString name of the image to set for
         * the @c %StandardPickerItem.
         */
        Q_SLOT void setImageQml(const QVariant & image);

        typedef StandardPickerItem ThisClass;
        typedef Control BaseClass;
        /*! @endcond */

        /*!
         * @brief A builder template for constructing a @c StandardPickerItem.
         *
         * See @c StandardPickerItem::create() for getting a concrete Builder for
         * constructing a @c %StandardPickerItem.
         *
         * @since BlackBerry 10.1.0
         */
        template <typename BuilderType, typename BuiltType>
        class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType> {
        protected:
            explicit TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node) {}

            /*!
             * @copydoc bb::cascades::StandardPickerItem::setImage(const Image &)
             */
            BuilderType& image(const bb::cascades::Image& image)
            {
                this->instance().setImage(image);
                return this->builder();
            }

            /*!
             * @copydoc bb::cascades::StandardPickerItem::setBackground(const bb::cascades::Paint &)
             */
            BuilderType& background(const bb::cascades::Paint& paint)
            {
                this->instance().setBackground(paint);
                return this->builder();
            }

            /*!
             * @brief Sets the image to a new image created from the passed url.
             */
            BuilderType& imageSource(const QUrl &imageSource)
            {
                this->instance().setImage(Image(imageSource));
                return this->builder();
            }

            /*!
             * @copydoc bb::cascades::StandardPickerItem::setTitle(const QString &)
             */
            BuilderType& title(const QString &title)
            {
                this->instance().setTitle(title);
                return this->builder();
            }
        };

    public:
        /*!
         * @brief A Builder class for constructing a @c StandardPickerItem builder.
         *
         * @since BlackBerry 10.1.0
         */
        class Builder : public TBuilder<Builder, StandardPickerItem> {
        public:
            explicit Builder() : TBuilder<Builder, StandardPickerItem>(new StandardPickerItem()) {}
        };

        /*!
         * @brief Creates a @c StandardPickerItem and wraps it into a builder that
         * allows for "build pattern" initialization.
         *
         * @code
         * StandardPickerItem::create().title(myTitleText);
         * @endcode
         *
         * @return A builder for setting @c %StandardPickerItem values
         *
         * @since BlackBerry 10.1.0
         */
        static Builder create()
        {
            return Builder();
        }
    };

    } // cascades
} // bb


QML_DECLARE_TYPE(bb::cascades::StandardPickerItem)


#endif /* CASCADES_STANDARDPICKERITEM_H */
