/* Copyright (c) 2011-2014 BlackBerry. All rights reserved. */

#ifndef cascades_standardlistitem_h
#define cascades_standardlistitem_h

#include <QtCore/QString>
#include <QtCore/QUrl>
#include <QtCore/QVariant>

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/controls/control.h>
#include <bb/cascades/resources/image.h>
#include <bb/cascades/controls/textformat.h>

#include <bb/cascades/controls/listitemlistener.h>
#include <bb/cascades/resources/imagefocusedeffect.h>

namespace bb {
    namespace cascades {

    class Container;
    class StandardListItemPrivate;

    /*!
     * 
     * @brief An item with a set of common properties to be displayed in a list.
     *
     * @image html standard_list_item.png A standard list item.
     *
     * @c %StandardListItem consists of an image, bold title text,
     * description text and status text. Each property is optional.
     *
     * The size of the @c %StandardListItem behaves as follows:
     * - By default, the width of the control is adjusted automatically to fill its parent container.
     * - The width is adjustable using the @c Control::preferredWidth, @c Control::minWidth and
     * @c Control::maxWidth properties.
     * - The height is fixed, so the properties @c Control::preferredHeight, @c Control::minHeight and
     * @c Control::maxHeight are not used.
     *
     * @xmlonly
     * <apigrouping group="User interface/List"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT StandardListItem : public Control, public ListItemListener
    {
        Q_OBJECT

        /*!
         * @brief An image set on this list item.
         *
         * The default value is an empty image, indicating no image is set.
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
         * @brief An image set on this list item.
         *
         * If no image is set, an invalid @c QUrl will be returned.
         * When changing the image source the @c imageSourceChanged() signal will be emitted.
         *
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QUrl imageSource READ imageSource WRITE setImageSource 
                  RESET resetImageSource NOTIFY imageSourceChanged FINAL) 


        /*!
         * @brief A title text set on this list item.
         *
         * The default value is @c QString::NULL, indicating no title text is set.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QString title READ title WRITE setTitle
                   RESET resetTitle NOTIFY titleChanged FINAL)

        /*!
         * @brief A status text set on this list item.
         *
         * The default value is @c QString::NULL, indicating no status text is set.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QString status READ status WRITE setStatus
                   RESET resetStatus NOTIFY statusChanged FINAL)

        /*!
         * @brief A description text set on this list item.
         *
         * The default value is @c QString::NULL, indicating no description text is set.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QString description READ description WRITE setDescription
                   RESET resetDescription NOTIFY descriptionChanged FINAL)

        /*!
         * @brief List item setting indicating if this list item should reserve
         * space for its image or not.
         *
         * The default value is @c false, indicating that the item should not reserve space for its image.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bool imageSpaceReserved READ isImageSpaceReserved WRITE setImageSpaceReserved
                   RESET resetImageSpaceReserved NOTIFY imageSpaceReservedChanged FINAL)

        /*!
        * @brief The @c TextFormat decides how the provided text data should be interpreted,
        * e.g as plain text or HTML. The property applies to all the text properties of this control. i.e title, status and description.
        * It is not possible to apply this property individually on either title, status or description.
        * The default value of the textFormat property is TextFormat.Auto.
        *
        * @snippet tad/examples/controls/standardlistitem/assets/main.qml standardlistitem_qml
        *
         *
         * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(bb::cascades::TextFormat::Type textFormat READ textFormat WRITE setTextFormat RESET resetTextFormat NOTIFY textFormatChanged FINAL);

        /*!
        * @brief The effect that is applied to a list item image that is in focus.
        *
        * The default value is @c %ImageFocusedEffect::Default
        *
        * @since BlackBerry 10.3.1
        */
        Q_PROPERTY(bb::cascades::ImageFocusedEffect::Type imageFocusedEffect READ imageFocusedEffect WRITE setImageFocusedEffect
                   RESET resetImageFocusedEffect NOTIFY imageFocusedEffectChanged REVISION 4 FINAL)

    public:
        /*!
         * @brief Constructs a list item that is owned by the specified parent.
         *
         * If parent is @c 0 or is not specified, this list item will not have an owner.
         *
         * @param parent The parent container that will be the owner of this list item or 0.
         *
         * @since BlackBerry 10.0.0
         */
        explicit StandardListItem(Container * parent = 0);

        /*!
         * @brief Destructs this list item.
         *
         * @since BlackBerry 10.0.0
         */
        virtual ~StandardListItem();

        /*!
         * @brief Returns the image set on this list item.
         *
         * An empty image is returned when image was not set.
         *
         * @return The image set on this list item.
         *
         * @since BlackBerry 10.0.0
         */
        Image image() const;

        /*!
         * @brief Sets the new image on this list item.
         *
         * The @c imageChanged signal is emitted if the image gets changed.
         *
         * @param image The new image for this list item.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setImage(const Image& image);

        /*!
         * @brief Resets the image on this list item to a default value of an empty image.
         *
         * The @c imageChanged signal is emitted if the image gets reset.
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
          * @brief Sets the new image on this list item.
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
          * @brief Resets the image in this list item to its default, meaning that no image is set.
          *
          * This function emits an @c imageSourceChanged() signal if the currently set image source changes.
         *
         * @since BlackBerry 10.0.0
          */
        Q_SLOT void resetImageSource();

        /*!
         * @brief Returns the status text set on this list item.
         *
         * @c QString::NULL is returned when status text was not set.
         *
         * \return The status set on this list item.
         *
         * @since BlackBerry 10.0.0
         */
        const QString title() const;

        /*!
         * @brief Sets the new title text on this list item to a passed in string.
         *
         * The @c titleChanged() signal is emitted if the title text gets changed.
         *
         * \param title The new title text for this list item.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setTitle(const QString & title);

        /*!
         * @brief Resets the title text on this list item to a default value of Qstring::NULL.
         *
         * The @c titleChanged() signal is emitted if the title text gets reset.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetTitle();


        /*!
         * @brief Returns the status text set on this list item.
         *
         * @c QString::NULL is returned when status text was not set.
         *
         * @return The status text set on this list item.
         *
         * @since BlackBerry 10.0.0
         */
        const QString status() const;

        /*!
         * @brief Sets the new status text on this list item to a passed in string.
         *
         * The @c statusChanged() signal is emitted if the status text gets changed.
         *
         * @param status The new status text for this list item.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setStatus(const QString & status);

        /*!
         * @brief Resets the status text on this list item to a default value of QString::NULL.
         *
         * The @c statusChanged() signal is emitted if the status text gets reset.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetStatus();

        /*!
         * @brief Returns the description text set on this list item.
         *
         * @c QString::NULL is returned when description text was not set.
         *
         * @return The description text set on this list item.
         *
         * @since BlackBerry 10.0.0
         */
        const QString description() const;

        /*!
         * @brief Sets the description text on this list item to a passed in string.
         *
         * The @c descriptionChanged() signal is emitted if the description text gets changed.
         *
         * @param description The new description text for this list item.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setDescription(const QString & description);

        /*!
         * @brief Resets the description text on this list item to a default value of Qstring::NULL.
         *
         * The @c descriptionChanged() signal is emitted if the description text gets changed.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetDescription();

        /*!
         * @brief Returns whether space is reserved for the image (even if no image is set).
         *
         * @return @c true if space is reserved for the image and @c false otherwise.
         *
         * @since BlackBerry 10.0.0
         */
        bool isImageSpaceReserved() const;

        /*!
         * @brief Sets the setting of whether space is reserved for the image or not when there is no image set.
         *
         * Space will be reserved for the image if true is passed in (even if there is no image).
         * Space will not be reserved for the image if false is passed.
         * The @c imageSpaceReservedChanged signal is emitted if the setting got changed.
         *
         * @param imageSpaceReserved The setting of whether space is reserved for the image or not.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setImageSpaceReserved(bool imageSpaceReserved);

        /*!
         * @brief Resets the setting of whether space is reserved for the image or not.
         *
         * By default it is set to true.
         * The @c imageSpaceReservedChanged() signal is emitted if the setting got changed.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetImageSpaceReserved();

        /*!
         * @brief Return the @c bb:cascades::TextFormat used to decide how the provided text is to be
         * interpreted.
         *
         * @returns The current text format for this control.
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::TextFormat::Type textFormat() const;

        /*!
         * @brief Sets the @c bb:cascades::TextFormat for this control.
         *
         * Changes this control's way of interpreting the provided text, i.e.
         * if the text should be interpreted as plain text or HTML.
         *
         * @param textFormat The text format that the control will use to interpret the provided text.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setTextFormat(bb::cascades::TextFormat::Type textFormat);

        /*!
         * @brief Resets the @c format property to the default value of @c bb::cascades::TextFormat::Auto.
         *
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetTextFormat();

        /*!
         * @brief Returns the @c ImageFocusedEffect::Type that is applied on its image when the item is focused.
         *
         * @return The @c %ImageFocusedEffect::Type that is applied effect on the image when the item is focused.
         *
         * @since BlackBerry 10.3.1
         */
        Q_REVISION(4)
        bb::cascades::ImageFocusedEffect::Type imageFocusedEffect() const;

        /*!
         * @brief Sets the @c ImageFocusedEffect::Type to apply on its image when the item is focused.
         *
         * @param type The @c %ImageFocusedEffect::Type to apply on its image when the item is focused.
         *
         * @since BlackBerry 10.3.1
         */
        Q_REVISION(4)
        Q_SLOT void setImageFocusedEffect(bb::cascades::ImageFocusedEffect::Type type);

        /*!
         * @brief Resets the @c %ImageFocusedEffect::Type for its image.
         * The @c imageFocusedEffect is set to the default value
         *
         * @since BlackBerry 10.3.1
         */
        Q_REVISION(4)
        Q_SLOT void resetImageFocusedEffect();
    Q_SIGNALS:
        /*!
         * @brief Emitted when this list item's image changes.
         *
         * @param image The new @c Image or @c 0 (if no image should be shown).
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
         * @param imageSource The new image source or an invalid @c QUrl if no image is set.
         *
         * @since BlackBerry 10.0.0
         */
        void imageSourceChanged(const QUrl& imageSource);

        /*! \cond PRIVATE */
        /*!
         * @brief Emitted when this list item's image changes.
         *
         * @param image The new @c Image or @c 0 (if no image should be shown).
         */
        void imageChanged(QVariant image);
        /*! \endcond */

        /*!
         * @brief Emitted when this list item's title text changes.
         *
         * @param title The new title string or @c QString::Null if changed to an empty @c title.
         *
         * @since BlackBerry 10.0.0
         */
        void titleChanged(QString title);

        /*!
         * @brief Emitted when his list item's status text changes.
         *
         * @param status The new @c status string or @c QString::Null if changed to an empty @c status.
         *
         * @since BlackBerry 10.0.0
         */
        void statusChanged(QString status);

        /*!
         * @brief Emitted when this list item's description text changes.
         *
         * @param description The new @c description string or @c QString::Null if
         * changed to an empty @c description.
         *
         * @since BlackBerry 10.0.0
         */
        void descriptionChanged(QString description);

        /*!
         * @brief Emitted when the setting to reserve space for its image changes.
         *
         * @param imageSpaceReserved If @c true space should be reserved for the image, @c false otherwise.
         *
         * @since BlackBerry 10.0.0
         */
        void imageSpaceReservedChanged(bool imageSpaceReserved);

        /*!
         * @brief Emitted when the @c format property is changed.
         *
         * @param newTextFormat The @c %bb::cascades::TextFormat that has been set.
         *
         * @since BlackBerry 10.0.0
         */
         void textFormatChanged(bb::cascades::TextFormat::Type newTextFormat);

        /*!
         * @brief Emitted when the image focused effect for the image changes.
         *
         * @param newImageFocusedEffect The new effect type for the image when the item is focused.
         *
         * @since BlackBerry 10.3.1
         */
        Q_REVISION(4)
        void imageFocusedEffectChanged(bb::cascades::ImageFocusedEffect::Type newImageFocusedEffect);

    private:
        /*! \cond PRIVATE */
        void select(bool select);
        void activate(bool activate);
        void reset(bool selected, bool activated);

        const QVariant imageQml() const;
        Q_SLOT void setImageQml(const QVariant &image);

        /*! \endcond */

        Q_DECLARE_PRIVATE(StandardListItem)
        Q_DISABLE_COPY(StandardListItem)

    public:
        /*! \cond PRIVATE */
        typedef StandardListItem ThisClass;
        typedef Control BaseClass;
         /*! \endcond */
         
        /*!
         * @brief A builder template for constructing a StandardListItem.
         *
         * See @c StandardListItem::create() for getting a concrete Builder for
         * constructing a StandardListItem.
         *
         * @since BlackBerry 10.0.0
         */
        template <typename BuilderType, typename BuiltType> 
        class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType> {
        protected:
            explicit TBuilder(BuiltType* node) :
                     BaseClass::TBuilder<BuilderType, BuiltType>(node)
            {
            }
    public:

        /*!
         * @copydoc bb::cascades::StandardListItem::setImage(const Image &)
         */
        BuilderType& image(const Image& image)
        {
            this->instance().setImage(image);
            return this->builder();
        }

        /*!
         * @brief Sets the image to a new image created from the passed url.
         *
         * @since BlackBerry 10.0.0
         */
        BuilderType& imageSource(const QUrl &imageSource)
        {
            this->instance().setImage(Image(imageSource));
            return this->builder();
        }

        /*!
         * @copydoc bb::cascades::StandardListItem::setTitle(const QString &)
         */
        BuilderType& title(const QString &title)
        {
            this->instance().setTitle(title);
            return this->builder();
        }

        /*!
         * @copydoc bb::cascades::StandardListItem::setStatus(const QString &)
         */
        BuilderType& status(const QString &status)
        {
            this->instance().setStatus(status);
            return this->builder();
        }

        /*!
         * @copydoc bb::cascades::StandardListItem::setDescription(const QString &)
         */
        BuilderType& description(const QString &description) 
        {
            this->instance().setDescription(description);
            return this->builder();
        }

        /*!
         * @copydoc bb::cascades::StandardListItem::setTextFormat(bb::cascades::TextFormat::Type textFormat);
         */
        BuilderType& textFormat(bb::cascades::TextFormat::Type textFormat)
        {
            this->instance().setTextFormat(textFormat);
            return this->builder();
        }

        /*!
         * @brief Sets the @c ImageFocusedEffect::Type to apply on its image when the item is focused
         *
         * @since BlackBerry 10.3.1
         */
        BuilderType& imageFocusedEffect(const bb::cascades::ImageFocusedEffect::Type type)
        {
          this->instance().setImageFocusedEffect(type);
          return this->builder();
        }
    };

    /*!
     * @brief A Builder class for constructing a StandardListItem builder.
     *
     * @since BlackBerry 10.0.0
     */
    class Builder : public TBuilder<Builder, StandardListItem> {
        public:
           explicit Builder() : TBuilder<Builder, StandardListItem>(new StandardListItem())
           {}
        };

        /*!
         * @brief Creates a StandardListItem and wraps it into a builder that 
         * allows for "build pattern" initialization.
         *
         * @snippet tad/examples/controls/standardlistitem/src/StandardListItemExamples.cpp standardlistitem
         *
         * @return A builder for setting StandardListItem values
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

QML_DECLARE_TYPE(bb::cascades::StandardListItem)


#endif    // cascades_standardlistitem_h

