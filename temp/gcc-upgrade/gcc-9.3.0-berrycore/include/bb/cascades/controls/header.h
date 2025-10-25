/* Copyright (C) 2011 - 2014 BlackBerry Limited. All rights reserved. */

#ifndef cascades_header_h
#define cascades_header_h

#include <QtCore/QString>

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/controls/control.h>
#include <bb/cascades/controls/headermode.h>

namespace bb {
    namespace cascades {
    
    class HeaderPrivate;

    /*!
     * 
     * @brief A header that is used for grouping or clustering items in a list.
     *
     * @image html header.png
     *
     * For example, in a messaging application, you might want to group together "Today's emails"
     * and "Older emails" in separate visual groups.
     *
     * @c %Header has two labels (@c title and @c subtitle). The title text is displayed with
     * a bold font.
     *
     * Here's a simple example demonstrating the use of a @c %Header, in QML:
     *
     * @snippet tad/examples/controls/header/assets/main.qml header1_qml
     *
     * The size of the @c %Header behaves as follows:
     * - By default, the width of the control is adjusted automatically to fill its parent container.
     * - The width is adjustable using the @c Control::preferredWidth, @c Control::minWidth and @c Control::maxWidth properties.
     * - The height is fixed, so the properties @c Control::preferredHeight, @c Control::minHeight and @c Control::maxHeight are not used.
     *
     * Header modes:
     * Since Cascades 10.3.0, you can specify the mode of a @c %Header
     * using the @c HeaderMode::Type enumeration. The @c HeaderMode enumeration
     * lets you create an interactive header that supports an arrow icon that can be tapped. You can
     * tap the arrow icon on the header to trigger specific behavior in your app.
     * Since Cascades 10.3.1, an interactive header allows you to tap the full size of the header
     * and if no action is connected to the header the arrow will be invisible.
     * Note that the visual representation of the interactive element may change in the future.
     * See the documentation for the @c mode property for further information.
     *
     * @image html header_interactive.png
     *
     * Here's a simple example demonstrating the use of @c Interactive mode in a @c %Header, in QML:
     *
     * @snippet tad/examples/controls/header/assets/main.qml header2_qml
     *
     * @xmlonly
     * <apigrouping group="User interface/List"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT Header : public Control
    {
    private:
        Q_OBJECT


        /*!
        * @brief The mode of the @c Header to create.
        *
        * Possible values for this property are @c Default, @c Plain, and @c Interactive.
        *
        * In @c Default mode, the header selects the mode automatically based on
        * whether there's a slot connected to the @c onClicked() signal or not.
        *
        * In @c Plain mode, the header has a title to the left and a subtitle aligned to the right. Both are optional.
        *
        * In @c Interactive mode, a @c subtitle appears to the left of an arrow button.
        * The button is used to intercept touch events on the screen to affect app
        * behavior. When the arrow icon is tapped, it emits a @c Header::clicked() signal that you can
        * capture and respond to in your app. For example, you can connect the @c clicked() signal to
        * the slot of another object, or use the @c onClicked() signal handler in QML to respond
        * to the button being tapped. Note that the visual representation of the interactive element
        * may change in the future.
        * The title and subtitle are optional in @c Interactive mode.
        *
        * @note Since 10.3.1, the full size of an interactive header can be tapped to emit the @c %Header::clicked() signal.
        * The arrow is only visible when an action is connected to the header item.
        *
        * @since BlackBerry 10.3.0
        */
        Q_PROPERTY(bb::cascades::HeaderMode::Type mode READ mode WRITE setMode RESET resetMode NOTIFY modeChanged REVISION 3 FINAL)

        /*!
         * @brief A title string set on this header list item.
         *
         * @c QString::NULL is the default value for title text.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QString title READ title WRITE setTitle
                   RESET resetTitle NOTIFY titleChanged FINAL)

        /*!
         * @brief A subtitle string set on this header list item (displayed with a smaller font).
         *
         * @c QString::NULL is the default value for subtitle text.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QString subtitle READ subtitle WRITE setSubtitle
                   RESET resetSubtitle NOTIFY subtitleChanged FINAL)

    public:
        /*!
         * @brief Constructs a @c %Header.
         *
         * Caller is responsible for properly setting the parent of this @c %Header.
         *
         * @since BlackBerry 10.0.0
         */
        Header();

        /*!
         * @brief Destructs this @c %Header.
         *
         * @since BlackBerry 10.0.0
         */
        virtual ~Header();

        /*!
         * @brief Returns the mode of the @c %Header.
         *
         * See the documentation for the @c mode property for further information.
         *
         * @return The mode of @c %Header, specified using the @c HeaderMode::Type enumeration.
         *
         * @since BlackBerry 10.3.0
         */
        Q_REVISION(3)
        bb::cascades::HeaderMode::Type mode() const;

        /*!
         * @brief Returns the title text set on this header list item.
         *
         * @c QString::NULL is returned when title text was not set.
         *
         * @since BlackBerry 10.0.0
         */
        const QString title() const;

        /*!
         * @brief Sets title text to a passed in title text.
         *
         * Title text will be empty if set to @c QString::NULL.
         * The @c titleChanged() signal is emitted if the title text is changed.
         *
         * @param title The new title text to be set on this header list item.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setTitle(const QString & title);

        /*!
         * @brief Resets title text to a default value of QString::NULL.
         *
         * The @c titleChanged() signal is emitted if the title text is changed.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetTitle();

        /*!
         * @brief Returns the subtitle text set on this header list item.
         *
         * @c QString::NULL is returned when subtitle text is not set.
         *
         * @since BlackBerry 10.0.0
         */
        const QString subtitle() const;

        /*!
         * @brief Sets subtitle text to a passed in text.
         *
         * Subtitle text will be empty if set to @c QString::NULL.
         * The @c subtitleChanged() signal is emitted if the subtitle text is changed.
         *
         * @param subtitle The new subtitle text to be set on this header list item.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setSubtitle(const QString & subtitle);

        /*!
         * @brief Resets subtitle text to a default value of QString::NULL.
         *
         * The @c subtitleChanged() signal is emitted if the subtitle text is changed.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetSubtitle();

        /*!
         * @brief Resets mode to a default value of @c HeaderMode::Default.
         *
         * The @c modeChanged() signal is emitted if the mode changes.
         *
         * @since BlackBerry 10.3.0
         */
        Q_REVISION(3)
        Q_SLOT void resetMode();

        /*!
         * @brief Sets header mode to the specified mode.
         *
         * The @c modeChanged() signal is emitted if the mode changes.
         *
         * @param newMode The new mode to be set on this header list item.
         *
         * @since BlackBerry 10.3.0
         */
        Q_REVISION(3)
        Q_SLOT void setMode(bb::cascades::HeaderMode::Type newMode);

    Q_SIGNALS:

        /*!
         * @brief Emitted when the title text changes in this header list item.
         *
         * @param title The new title text or 
         *                     QString::NULL if changed to an empty title.
         *
         * @since BlackBerry 10.0.0
         */
        void titleChanged(QString title);


        /*!
         * @brief Emitted when the subtitle text changes in this header list item.
         *
         * @param subtitle The new subtitle text or 
         *        QString::NULL if changed to an empty subtitle.
         *
         * @since BlackBerry 10.0.0
         */
        void subtitleChanged(QString subtitle);

         /*!
         * @brief Emitted when the mode changes in this header list item.
         *
         * @param newMode The new mode.
         *
         * @note Due to a workaround for a Qt Core issue with accessing enums from QML,
         * the argument of this signal doesn't follow naming convention for signals in
         * which the signal arguments are typically named to match the associated property's name.
         * Use the object's property to access current property value instead of the signal argument
         * to avoid runtime errors (that is, use @c mode instead of @c newMode).
         *
         * @since BlackBerry 10.3.0
         */
        Q_REVISION(3)
        void modeChanged(bb::cascades::HeaderMode::Type newMode);

       /*!
         * @brief Emitted when the header button area is tapped.
         *
         * @since BlackBerry 10.3.0
         */
        Q_REVISION(3)
        void clicked();

        /*! @cond PRIVATE */
    protected:
        explicit Header(HeaderPrivate &_d_ptr);
        /*! @endcond */

    private:
        /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(Header)
        Q_DISABLE_COPY(Header)
        /*! @endcond */

    public:

        typedef Header ThisClass;
        typedef Control BaseClass;

        /*!
         * @brief A builder template for constructing a Header.
         *
         * See Header::create() for getting a concrete Builder for
         * constructing a Header.
         *
         * @since BlackBerry 10.0.0
         */
        template <typename BuilderType, typename BuiltType>
        class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType>
        {
        protected:
            explicit TBuilder(BuiltType* node) :
            BaseClass::TBuilder<BuilderType, BuiltType>(node)
            { }
        public:
            /*!
             * @brief Sets the title text on the Header that is being constructed.
             *
             * @param title The new title text to be set on this header list item.
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& title(const QString &title)
            {
                this->instance().setTitle(title);
                return this->builder();
            }

            /*!
             * @brief Sets the subtitle text on the Header that is being constructed.
             *
             * @param subtitle The new subtitle text to be set on this header list item.
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& subtitle(const QString &subtitle)
            {
                this->instance().setSubtitle(subtitle);
                return this->builder();
            }

            /*!
             * @brief Sets the mode on the Header that is being constructed.
             *
             * @param mode The mode to be set on this header list item.
             *
             * @since BlackBerry 10.3.0
             */
            BuilderType& mode(bb::cascades::HeaderMode::Type mode)
            {
                this->instance().setMode(mode);
                return this->builder();
            }

            /*!
             * A convenience method for connecting the specified receiver's slot to
             * the @c clicked() signal with the default connection type
             * @c Qt::AutoConnection.
             *
             * Example:
             * @code
             * Header *header = Header::create()
             *     .onClicked(this, SLOT(onClicked()));
             * @endcode
             *
             * @param receiver A non-null receiver object.
             * @param method A non-null name of the slot in the receiver object to connect to.
             *
             * @see BaseObject::TBuilder::connect()
             *
             * @since BlackBerry 10.3.0
             */
            BuilderType& onClicked(const QObject* receiver, const char *method) {
              this->connect(SIGNAL(clicked()), receiver, method);
              return this->builder();
            }
        };

       /*!
        * @brief A builder for constructing a @c Header control.
        *
        * To retrieve the builder, call @c Header::create().
        *
        * @since BlackBerry 10.0.0
        */
        class Builder : public TBuilder<Builder, Header>
        {
        public:
            explicit Builder() : TBuilder<Builder, Header>(new Header()) {}
        };

        /*!
         * @brief Creates a Header and wraps it into a builder that
         * allows for "builder pattern" initialization:
         *
         * @snippet tad/examples/controls/header/src/HeaderExamples.cpp header1
         *
         * @since BlackBerry 10.0.0
         */
        static Builder create() {
            return Builder();
        }
    };
}
}

QML_DECLARE_TYPE(bb::cascades::Header)


#endif // cascades_header_h


