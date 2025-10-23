/* Copyright (C) 2013 Research In Motion Limited.  */

#ifndef cascades_customlistitem_h
#define cascades_customlistitem_h

#include <QObject>

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/controls/control.h>

#include <bb/cascades/controls/highlightappearance.h>

namespace bb {
    namespace cascades {

    class Container;
    class CustomListItemPrivate;

    /*!
     * @brief Represents a list item with a highlight, a divider, and user-specified content.
     *
     * The @c %CustomListItem class represents a customizable list item that you can use in a
     * @c ListView. This type of list item consists of three components:
     * - A highlight, which determines what the list item looks like when it's selected. The
     *   highlight is represented by the @c highlightAppearance property.
     * - A divider, which is used to separate the list item from adjacent items in the list. A
     *   flag to indicate whether the divider should be shown is represented by the
     *   @c dividerVisible property.
     * - User-specified content, which appears as the body of the list item and can be any
     *   Cascades control. The content is represented by the @c content property.
     *
     * The size of the @c %CustomListItem behaves as follows:
     * - By default, the width of the @c %CustomListItem is adjusted automatically to fill its parent container.
     * - The width is adjustable using the @c Control::preferredWidth, @c Control::minWidth, and
     *   @c Control::maxWidth properties.
     * - By default, the height of the @c %CustomListItem has a device-dependent built-in value, but it is increased
     * automatically to fit the content if necessary.
     * - Setting the preferred height does not affect the size of the @c %CustomListItem if the preferred height
     * is smaller than is necessary to fit the content.
     * - The height is adjustable using the @c Control::preferredHeight, @c Control::minHeight, and
     *   @c Control::maxHeight properties.
     *
     * This class also supports a builder pattern to create new @c %CustomListItem objects and
     * set the values of their properties.
     *
     * Example of creating a %CustomListItem, in QML:
     *
     * @snippet tad/examples/controls/customlistitem/assets/main.qml customlistitem1_qml
     *
     * @xmlonly
     * <apigrouping group="User interface/List"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.2.0
     */
    class BBCASCADES_EXPORT CustomListItem : public Control {
        Q_OBJECT

        /*!
         * @brief The root content for the @c %CustomListItem.
         *
         * The content can be any control. Typically, it is a @c Container with images and text.
         *
         * @since BlackBerry 10.2.0
         *
         * @xmlonly
         * <qml>
         * <property defaultProperty="yes"/>
         * </qml>
         * @endxmlonly
         */
        Q_PROPERTY(bb::cascades::Control* content READ content WRITE setContent RESET resetContent NOTIFY contentChanged FINAL);

        /*!
         * @brief The highlight mode.
         *
         * This property specifies what type of highlight should be used when the list item is
         * selected. For example, the item could use full highlighting (the entire item is highlighted),
         * frame highlighting (only a small frame on top of the item is highlighted), or no
         * highlighting.
         *
         * This property can be set only when creating the @c %CustomListItem initially, and its value
         * can't be changed afterwards. The default value of this property is @c HighlightAppearance::Default.
         *
         * @xmlonly
         * <qml>
         * <property writable="init-only"/>
         * </qml>
         * @endxmlonly
         *
         * @since BlackBerry 10.2.0
         */
        Q_PROPERTY(bb::cascades::HighlightAppearance::Type highlightAppearance READ highlightAppearance WRITE setHighlightAppearance FINAL);

        /*!
         * @brief Indicates whether a divider should be shown on the @c %CustomListItem.
         *
         * A thin divider can appear on a @c %CustomListItem, which will separate other possible items that
         * are adjacent to this one. The default value of this property is @c true.
         *
         * @since BlackBerry 10.2.0
         */
        Q_PROPERTY(bool dividerVisible READ dividerVisible WRITE setDividerVisible RESET resetDividerVisible NOTIFY dividerVisibleChanged FINAL);

        Q_CLASSINFO("DefaultProperty", "content");

    public:
        /*!
         * @brief Creates a new @c %CustomListItem that is owned by the specified parent.
         *
         * If a parent is not specified, or if the specified parent is @c 0, this @c %CustomListItem
         * will not have an owner. The value of the @c highlightAppearance property is set to its
         * default value of @c HighlightAppearance::Full.
         *
         * @param parent The parent container that will be the owner of this @c %CustomListItem, or
         * @c 0 if no parent is specified.
         *
         * @since BlackBerry 10.2.0
         */
        explicit CustomListItem(Container* parent = 0);

        /*!
         * @brief Creates a new @c %CustomListItem that is owned by the specified parent and uses
         * the specified highlight appearance.
         *
         * If a parent is not specified, or if the specified parent is @c 0, this @c %CustomListItem
         * will not have an owner.
         *
         * @param highlightAppearance The highlight appearance for this @c %CustomListItem.
         * @param parent The parent container that will be the owner of this @c %CustomListItem, or
         * @c 0 if no parent is specified.
         *
         * @since BlackBerry 10.2.0
         */
        explicit CustomListItem(HighlightAppearance::Type highlightAppearance, Container* parent = 0);

        /*!
         * @brief Destroys this @c %CustomListItem.
         *
         * @since BlackBerry 10.2.0
         */
        virtual ~CustomListItem();

        /*!
         * @brief Gets the active content of this @c %CustomListItem.
         *
         * Ownership will not be transferred.
         *
         * @return The content of this @c %CustomListItem.
         *
         * @since BlackBerry 10.2.0
         */
        bb::cascades::Control* content() const;

        /*!
         * @brief Sets the content of this @c %CustomListItem.
         *
         * Ownership of the content will always be transferred to this @c %CustomListItem.
         * If this @c %CustomListItem already has content, the old content is still owned by this @c %CustomListItem
         * and will be destroyed when this @c %CustomListItem is destroyed.
         *
         * If content was successfully set using this function, the @c contentChanged()
         * signal is emitted.
         *
         * @param content The content to set. You can specify @c 0 to remove content (the old content
         * will still be owned by this @c %CustomListItem).
         *
         * @since BlackBerry 10.2.0
         */
        Q_SLOT void setContent(bb::cascades::Control* content);

        /*!
         * @brief Resets the content of this @c %CustomListItem to a default value of @c NULL.
         *
         * If the content was successfully reset using this function, the @c contentChanged()
         * signal is emitted.
         *
         * @since BlackBerry 10.2.0
         */
        Q_SLOT void resetContent();

        /*!
         * @brief Gets the current highlight appearance of this @c %CustomListItem.
         *
         * @return The highlight appearance of this @c %CustomListItem.
         *
         * @since BlackBerry 10.2.0
         */
        bb::cascades::HighlightAppearance::Type highlightAppearance() const;

        /*!
         * @brief Indicates whether this @c %CustomListItem has a divider enabled.
         *
         * @return @c true if this @c %CustomListItem has a divider enabled, @c false otherwise.
         *
         * @since BlackBerry 10.2.0
         */
        bool dividerVisible() const;

        /*!
         * @brief Sets whether this @c %CustomListItem should show the divider.
         *
         * @param dividerVisible If @c true the divider should be shown, if @c false the divider
         * should not be shown.
         *
         * @since BlackBerry 10.2.0
         */
        Q_SLOT void setDividerVisible(bool dividerVisible);

        /*!
         * @brief Resets the divider visibility of this @c %CustomListItem to a default value
         * of @c true.
         *
         * If the divider visibility was successfully reset using this function, the @c dividerVisibleChanged()
         * signal is emitted.
         *
         * @since BlackBerry 10.2.0
         */
        Q_SLOT void resetDividerVisible();

    Q_SIGNALS:
        /*!
         * @brief Emitted when the content of this @c %CustomListItem has changed.
         *
         * @param content The new content of this @c %CustomListItem.
         *
         * @since BlackBerry 10.2.0
         */
        void contentChanged(bb::cascades::Control* content);

        /*!
         * @brief Emitted when the divider visibility of this @c %CustomListItem is changed
         * to enabled or disabled.
         *
         * @param dividerVisible If @c true the divider is enabled, if @c false the divider is disabled.
         *
         * @since BlackBerry 10.2.0
         */
        void dividerVisibleChanged(bool dividerVisible);

    private:
        /* @cond PRIVATE */
        void setHighlightAppearance(bb::cascades::HighlightAppearance::Type highlightAppearance);
        /* @endcond */

        Q_DECLARE_PRIVATE(CustomListItem)
        Q_DISABLE_COPY(CustomListItem)

    public:
        /*! @cond PRIVATE */
        typedef CustomListItem ThisClass;
        typedef Control BaseClass;
        /*! @endcond */


        /*!
         * @brief A builder template for constructing a @c %CustomListItem.
         *
         * See @c CustomListItem::create() for getting a concrete @c Builder for constructing a @c %CustomListItem.
         *
         * @since BlackBerry 10.2.0
         */
        template <typename BuilderType, typename BuiltType>
        class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType> {
        protected:
            TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node) {}
        public:

            /*!
             * @copydoc bb::cascades::CustomListItem::setContent(bb::cascades::Control*)
             */
            BuilderType& content(bb::cascades::Control* content) {
                this->instance().setContent(content);
                return this->builder();
            }

            /*!
             * @copydoc bb::cascades::CustomListItem::setDividerVisible(bool)
             */
            BuilderType& dividerVisible(bool dividerVisible) {
                this->instance().setDividerVisible(dividerVisible);
                return this->builder();
            }

        };

        /*!
         * @brief A concrete builder class for constructing a @c %CustomListItem.
         *
         * See @c CustomListItem::create() for getting a concrete @c Builder for constructing a @c %CustomListItem.
         *
         * @since BlackBerry 10.2.0
         */
        class Builder : public TBuilder<Builder, CustomListItem> {
        public:
            explicit Builder() : TBuilder<Builder, CustomListItem>(new CustomListItem()) {}
            explicit Builder(HighlightAppearance::Type highlightAppearance) : TBuilder<Builder, CustomListItem>(new CustomListItem(highlightAppearance, 0)) {}
        };

        /*!
         * @brief Creates and returns a @c Builder for constructing a @c %CustomListItem.
         *
         * @param highlightAppearance The highlight appearance to use for this @c %CustomListItem.
         *
         * @return A @c %Builder for constructing a @c %CustomListItem.
         *
         * @since BlackBerry 10.2.0
         */
        static Builder create(HighlightAppearance::Type highlightAppearance) {
            return Builder(highlightAppearance);
        }

        /*!
         * @brief Creates and returns a @c Builder for constructing a @c %CustomListItem.
         *
         * @return A @c %Builder for constructing a @c %CustomListItem.
         *
         * @since BlackBerry 10.2.0
         */
        static Builder create() {
            return Builder(HighlightAppearance::Default);
        }
    };

} // namespace cascades
} // namespace bb

QML_DECLARE_TYPE(bb::cascades::CustomListItem)

#endif // cascades_customlistitem_h
