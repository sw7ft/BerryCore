/* Copyright (C) 2011 - 2014 BlackBerry Limited. All rights reserved. */

#ifndef cascades_option_h
#define cascades_option_h

#include <QtCore/QString>

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/resources/image.h>
#include <bb/cascades/controls/control.h>

namespace bb {
    namespace cascades {

    class OptionPrivate;

    /*!
     * 
     *
     * @brief An option that can be used in a list of selectable items.
     *
     * The @c #text, @c #description, and @c #image properties are displayed on the 
     * screen with the intention to give visual feedback to the user regarding 
     * the option. The @c #value property is not visible and is intended as a 
     * utility for associating the option with a certain value.
     *
     * An @c %Option is intended to be used by any control that needs to display options as 
     * selectable items in some sort of list (e.g. the @c %DropDown control). 
     *
     * Not all properties in the @c %Option control need to be visually represented by a certain control.
     * It is up to the control that uses it to implement whatever properties it needs to and determine how
     * they are presented.
     * 
     * Here's a simple QML example demonstrating how a @c %DropDown uses options:
     * @snippet tad/examples/controls/option/assets/main.qml option_qml
     *
     * And another example in C++:
     * @snippet tad/examples/controls/option/src/OptionExamples.cpp option_1_cpp
     *
     * @xmlonly
     * <apigrouping group="User interface/Core controls"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT Option : public UIObject {
    private:
        Q_OBJECT

        /*!
         * @brief An image set on this option.
         * 
         * This image can be used for giving the user additional 
         * information on this option (e.g. a contact image).
         * The default value is a null image, indicating that no image is set.
         * The imageChanged() signal is emitted when the image changes.
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
        * @brief An image to display on the option.
        *
        * If no image is set, an invalid QUrl will be returned.
        * When changing the image source the imageSourceChanged() signal will be emitted.
        *
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(QUrl imageSource READ imageSource WRITE setImageSource 
                  RESET resetImageSource NOTIFY imageSourceChanged FINAL) 

        /*!
         * @brief A title text set on this option.
         * 
         * This is the primary textual representation of the option and should reflect what this option is.
         * The default value is @c QString::null, indicating that no title text is set.
         * The textChanged() signal is emitted when the text changes.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QString text READ text WRITE setText
                   RESET resetText NOTIFY textChanged FINAL)

        /*!
         * @brief A description text set on this option.
         * 
         * This is the secondary textual representation of the option (the primary being the #text property)
         * and can be used for giving the user additional information.
         * The default value is @c QString::null, indicating that no description is set.
         * The descriptionChanged() signal is emitted when the description changes.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QString description READ description WRITE setDescription
                   RESET resetDescription NOTIFY descriptionChanged FINAL)


        /*!
         * @brief A value set on this option.
         * 
         * The value is intended to associate the option with a 
         * value and thus isn't visually represented. The value in question can be
         * anything application specific, such as a pointer to a record set in a database.
         * The default value is @c QVariant::Invalid, indicating that no value is set.
         * The valueChanged() signal is emitted when the value changes.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QVariant value READ value WRITE setValue
                   RESET resetValue NOTIFY valueChanged FINAL)

        /*!
         * @brief Indicates the selected state of the option.
         *
         * @c true if the option is selected, @c false otherwise. The default value is @c false
         * (not selected).
         * The selectedChanged() signal is emitted when the selected state changes.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bool selected READ isSelected WRITE setSelected
                   RESET resetSelected NOTIFY selectedChanged FINAL)

        /*!
         * @brief Indicates whether the option is enabled.
         * 
         * When the option is disabled, it cannot be selected by interaction. 
         * However, the programmatic API allows selection updates even for disabled options. 
         * 
         * If @c true the option is enabled, if @c false it is disabled. The default value is @c true
         * (enabled).
         * The enabledChanged() signal is emitted when the enabled state changes.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled RESET resetEnabled NOTIFY enabledChanged FINAL)

        /*!
         * @brief Indicates the focused state of the option.
         *
         * @c true if the option is focused, @c false otherwise. The default value is @c false
         * (not focused).
         * The focusedChanged() signal is emitted when the focused state changes.
         *
         * @since BlackBerry 10.3.1
         */
        Q_PROPERTY(bool focused READ isFocused NOTIFY focusedChanged REVISION 4 FINAL)

    public:
        /*!
         * @brief Constructs an Option.
         * 
         * @param parent The parent Control of this %Option. The default is 0 if you don't specify a parent. 
         * If not 0, the ownership of the constructed option will be transferred to the parent.
         *
         * @since BlackBerry 10.0.0
         */
        explicit Option(Control *parent = 0);

        /*!
         * @brief Destructs the Option.
         *
         * @since BlackBerry 10.0.0
         */
        virtual ~Option();

        /*!
         * @brief Returns the image set on this option.
         * 
         * @c A null Image is returned when an image is not set.
         *
         * @return The image set on this option.
         *
         * @since BlackBerry 10.0.0
         */
        Image image() const;

        /*!
         * @brief Sets the image on this option.
         * 
         * The imageChanged() signal is emitted if the image is changed.
         *
         * @param image The new image for this option.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setImage(const Image& image);

        /*!
         * @brief Resets the image on this option to a default value of a null Image.
         * 
         * The imageChanged() signal is emitted if the image is reset.
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
          * @brief Sets the Image for the option.
          *
          * An invalid QUrl indicates no image.
          * This function emits an imageSourceChanged() signal if the currently set image source changes.
          *
          * @param source The image url.
         *
         * @since BlackBerry 10.0.0
          */
        Q_SLOT void setImageSource(const QUrl &source);

        /*!
          * @brief Resets the Image on the option to its default, meaning that no image is set.
          * This function emits an imageSourceChanged() signal if the currently set image source changes.
         *
         * @since BlackBerry 10.0.0
          */
        Q_SLOT void resetImageSource();


        /*!
         * @brief Returns the text set on this option.
         * 
         * @c QString::null is returned when text was not set.
         *
         * @return The text set on this option.
         *
         * @since BlackBerry 10.0.0
         */
        const QString text() const;

        /*!
         * @brief Sets the new text on this option.
         * 
         * The textChanged() signal is emitted if the text is changed.
         *
         * @param text The new text for this option.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setText(const QString & text);

        /*!
         * @brief Resets the text on this option to a default value of @c QString::null.
         * 
         * The textChanged() signal is emitted if the text is reset.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetText();

        /*!
         * @brief Returns the description text set on this option.
         * 
         * @c QString::null is returned when description text was not set.
         *
         * @return The description text set on this option.
         *
         * @since BlackBerry 10.0.0
         */
        const QString description() const;

        /*!
         * @brief Sets the description text on this option.
         * 
         * The descriptionChanged() signal is emitted if the description text is changed.
         *
         * @param description The new description text for this option.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setDescription(const QString & description);

        /*!
         * @brief Resets the description text on this option to a default value of @c QString::null.
         * 
         * The descriptionChanged() signal is emitted if the description text is changed.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetDescription();
        
        /*!
         * @brief Returns the value set on this option.
         *
         * @return The value set on this option.
         *
         * @since BlackBerry 10.0.0
         */
        const QVariant value() const;

        /*!
         * @brief Sets the value on this option.
         * 
         * The valueChanged() signal is emitted if the value is changed.
         *
         * @param value The new value for this option.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setValue(const QVariant & value);

        /*!
         * @brief Resets the value of this option.
         * 
         * The valueChanged() signal is emitted if the value is changed.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetValue();

        /*!
         * @brief Returns the selected state for the option.
         *
         * @return @c true if this option is selected, @c false if it is not selected.
         *
         * @since BlackBerry 10.0.0
         */
        bool isSelected() const;
  
        /*!
         * @brief Sets the selected state for the option.
         *
         * @param selected If @c true this option is selected, if @c false this option is not
         * selected.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setSelected(bool selected);
  
        /*!
         * @brief Resets the option to the default state (not selected).
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetSelected();


        /*!
         * @brief Returns the focused state of the option.
         *
         * @return @c true if this option is focused, @c false otherwise.
         *
         * @since BlackBerry 10.3.1
         */
        Q_REVISION(4)
        bool isFocused() const;

        /*!
         * @brief Requests focus for the option.
         *
         * @since BlackBerry 10.3.1
         */
        Q_REVISION(4)
        Q_SLOT void requestFocus();

        /*!
         * @brief Resets the option to the default state (not focused).
         *
         * @since BlackBerry 10.3.1
         */
        Q_REVISION(4)
        Q_SLOT void loseFocus();

        /*!
         * @brief Returns the #enabled state of the option (i.e. if it is enabled or not).
         *
         * @return @c true if the option is enabled, @c false otherwise.
         *
         * @since BlackBerry 10.0.0
         */
        bool isEnabled() const;

        /*!
         * @brief Sets the #enabled state of the option (i.e. if it is enabled or not).
         *
         * @param enabled If @c true the option is enabled, if @c false the option is disabled.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setEnabled(bool enabled);

        /*!
         * @brief Resets the #enabled state of the option to @c true.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetEnabled();

    Q_SIGNALS:
        /*!
         * @brief Emitted when this option's image changes.
         *
         * @param image The new image, or a null image if no image is shown.
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
         * @param imageSource The new image source, or an invalid QUrl if no source is set.
         *
         * @since BlackBerry 10.0.0
         */
        void imageSourceChanged(const QUrl& imageSource);

        /*! \cond PRIVATE */
        /*!
         * @brief Emitted when this options image changes.
         *
         * @param image The new Image or a null image if no image is shown.
         */
        void imageChanged(const QVariant& image);
        /*! \endcond */

        /*!
         * @brief Emitted when this option's title text changes.
         *
         * @param text The new text string, or @c QString::null if changed to an empty text.
         *
         * @since BlackBerry 10.0.0
         */
        void textChanged(QString text);

        /*!
         * @brief Emitted when this option's description text changes.
         *
         * @param description The new description string, or @c QString::null if changed to an empty description.
         *
         * @since BlackBerry 10.0.0
         */
        void descriptionChanged(QString description);

        /*!
         * @brief Emitted when this option's value changes.
         *
         * @param value The new value, or @c QString::null if changed to an empty value.
         *
         * @since BlackBerry 10.0.0
         */
        void valueChanged(QVariant value);

        /*!
         * @brief Emitted when the selected state changes.
         *
         * @param selected The new selected state. If @c true this option is selected, if
         * @c false this option is not selected.
         *
         * @since BlackBerry 10.0.0
         */
        void selectedChanged(bool selected);

        /*!
         * @brief Emitted when the @c #focused state changes.
         *
         * @param focused The new focused state. If @c true this option is focused, if
         * @c false this option is not focused.
         *
         * @since BlackBerry 10.3.1
         */
        Q_REVISION(4)
        void focusedChanged(bool focused);

        /*!
         * @brief Emitted when the #enabled property on the option changes.
         *
         * @param enabled If @c true the option is enabled, if @c false the option is disabled.
         *
         * @since BlackBerry 10.0.0
         */
        void enabledChanged(bool enabled);

    private:
        /*! \cond PRIVATE */
        const QVariant imageQml() const;
        Q_SLOT void setImageQml(const QVariant &image);

        typedef Option ThisClass;
        typedef UIObject BaseClass;

        Q_DECLARE_PRIVATE(Option)
        Q_DISABLE_COPY(Option)
        /*! @endcond */

    public:

        /*!
         * @brief A builder that constructs an @c Option.
         * 
         * To retrieve the builder, call @c Option::create().
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
             * @brief Sets the image on this option.
             * 
             * The imageChanged() signal is emitted if the image is changed.
             *
             * @param image The new image for this option.
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& image(const Image& image) {
                this->instance().setImage(image);
                return this->builder();
            }

            /*!
             * @brief Sets an image for the option, identified by its name.
             *
             * This a convenience function for setting an image for the option
             * identified by its name:
             *
             * @snippet tad/examples/controls/option/src/OptionExamples.cpp option_4_cpp
             *
             * @param url The name of the image to load.
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& imageSource(const QUrl &url) {
                return image(Image(url));
            }

            /*!
             * @brief Sets the new text on this option.
             * 
             * The textChanged() signal is emitted if the text is changed.
             *
             * @param text The new text for this option.
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& text(const QString &text)
            {
                this->instance().setText(text);
                return this->builder();
            }

            /*!
             * @brief Sets the description text on this option.
             * 
             * The descriptionChanged() signal is emitted if the description text is changed.
             *
             * @param description The new description text for this option.
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& description(const QString &description) 
            {
                this->instance().setDescription(description);
                return this->builder();
            }

            /*!
             * @brief Sets the value on this option.
             * 
             * The valueChanged() signal is emitted if the value is changed.
             *
             * @param value The new value for this option.
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& value(const QVariant &value) 
            {
                this->instance().setValue(value);
                return this->builder();
            }

            /*!
             * @brief Sets the selected state for the option.
             *
             * @param selected If @c true this option is selected, if @c false this option is not
             * selected.
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& selected(bool selected)
            {
                this->instance().setSelected(selected);
                return this->builder();
            }

            /*!
             * @brief Sets the bb::cascades::Option#enabled state of the option (i.e. if it is enabled or not).
             *
             * @param enabled If @c true the option is enabled, if @c false the option is disabled.
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& enabled(bool enabled) {
                this->instance().setEnabled(enabled);
                return this->builder();
            }

            /*!
             * A convenience method for connecting passed receiver's slot to
             * the @c selectedChanged(bool) signal with the default connection type
             * Qt::AutoConnection.
             *
             * Example:
             * @snippet tad/examples/controls/option/src/OptionExamples.cpp option_2_cpp
             *
             * @param receiver a non-@c null receiver object
             * @param method a non-null name of the slot in the receiver object to connect to
             *
             * @see BaseObject::TBuilder::connect()
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& onSelectedChanged(const QObject* receiver, const char *method) {
                this->connect(SIGNAL(selectedChanged(bool)), receiver, method);
                return this->builder();
            }
        };

        /*!
         * @brief A builder that constructs an @c Option.
         * 
         * To retrieve the builder, call @c Option::create().
         *
         * @since BlackBerry 10.0.0
         */ 
        class Builder : public TBuilder<Builder, Option>
        {
        public:
            explicit Builder() : TBuilder<Builder, Option>(new Option())
            {
            }
        };

        /*!
         * @brief Creates and returns a builder for constructing a Option.
         *
         * Using the builder to create a Option:
         * 
         * @snippet tad/examples/controls/option/src/OptionExamples.cpp option_3_cpp
         *
         * @return A builder used for constructing an Option.
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

QML_DECLARE_TYPE(bb::cascades::Option)


#endif
