/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_stacklistlayout_h
#define cascades_stacklistlayout_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/layouts/layoutorientation.h>
#include <bb/cascades/layouts/listlayout.h>
#include <bb/cascades/layouts/listheadermode.h>


namespace bb {
    namespace cascades {

    class StackListLayoutPrivate;

    /*!
     * @brief A layout used with @c ListView to lay out children in a simple stack.
     *
     * @image html cascades_stacklistlayout.png A StackListLayout with ten entries
     *
     * Setting a @c %StackListLayout on the @c ListView::layout property causes
     * the items in that @c %ListView to be positioned as a simple stack
     * (one item after another in the orientation that's specified).
     *
     * Margin-properties on root nodes of item visuals affect the spacing
     * between items in a @c %StackListLayout. The distance between two
     * items in the orientation direction will be the largest margin of the
     * two adjacent margins in the layout orientation.
     *
     * You can specify a preferred size for list items, but these are limited
     * by the width or height (minus padding) of the @c %ListView (width is limited
     * in vertical lists, height is limited in horizontal lists).
     *
     * The following C++ example demonstrates adding three @c %StandardListItem items
     * to a @c %StackListLayout, with "Hey", "Hello" and "Bye" as title texts.
     * Since @c %StackListLayout is the default layout for @c %ListView, it's not
     * necessary to explicitly specify the layout type.
     *
     * @code
     * ListView *pListView = new ListView(new QListDataModel<QString>(
     *         QList<QString>() << "Hey" << "Hello" << "Bye"));
     * @endcode
     *
     * This example demonstrates when it is necessary to set the @c #headerMode to
     * @c None on the @c %StackListLayout. The example displays an outer vertical
     * @c %ListView which has horizontal grid lists as items. Setting
     * @c headerMode to @c None on the @c %StackListLayout causes the outer
     * @c %ListView to use only the top level items from the @c DataModel, leaving
     * the items on the second level for the grid lists.
     *
     * @code
     * ListView {
     *     topPadding: -6
     *
     *     layout: StackListLayout {
     *         headerMode: ListHeaderMode.None
     *     }
     *     dataModel: XmlDataModel {
     *         source: "headersModel.xml"
     *     }
     *
     *     listItemComponents: [
     *         ListItemComponent {
     *             type: "folder"
     *
     *             Container {
     *                 id: root
     *                 topPadding: 6
     *                 layout: DockLayout {}
     *                 maxHeight: 206
     *
     *                 ListView {
     *                     dataModel: root.ListItem.view.dataModel
     *                     rootIndexPath: root.ListItem.indexPath
     *                     layout: GridListLayout {
     *                          orientation: Orientation.LeftToRight
     *                          columnCount: 2
     *                     }
     *
     *                     listItemComponents: [
     *                         ListItemComponent {
     *                             type: "image"
     *
     *                             ImageView {
     *                                 imageSource: ListItemData.source
     *                                 scalingMethod: ScalingMethod.AspectFill
     *                             }
     *                         }
     *                     ]
     *                 }
     *
     *                 Header {
     *                     maxWidth: 400
     *                     title: ListItemData.title
     *                     opacity: 0.75
     *                 }
     *             }
     *         }
     *     ]
     * }
     * @endcode
     *
     * @xmlonly
     * <apigrouping group="User interface/Layouts"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT StackListLayout : public ListLayout {
    private:
        Q_OBJECT

        /*!
         * @brief The orientation for the stack layout.
         *
         * The orientation determines the direction in which list items
         * are added to the list (for example, when using @c TopToBottom, items
         * are added starting from the top).
         * If items exist outside of the visible area,
         * it is possible to scroll down the list to view them.
         *
         * Item sizes have no limitation in the orientation direction, but are limited
         * in the opposite direction.
         * For example, in a @c %ListView that uses a @c %StackListLayout with
         * @c %orientation of @c TopToBottom or @c BottomToTop, the height of
         * the items is only limited by the item themselves. But the width of items
         * is limited by the width of the @c %ListView, minus any @c leftPadding and
         * @c rightPadding that might be applied on the @c %ListView.
         *
         * The default orientation is @c TopToBottom, but @c LeftToRight,
         * @c RightToLeft, and @c BottomToTop can also be used.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::LayoutOrientation::Type orientation
                   READ orientation
                   WRITE setOrientation
                   RESET resetOrientation
                   NOTIFY orientationChanged
                   FINAL)

        /*!
         * @brief Determines if and how headers are shown by the @c %StackListLayout.
         *
         * If set to @c None, only the top level of items are used from the @c %DataModel.
         * Otherwise the top level items under the root item are used as
         * headers, and child items are placed after their header.
         *
         * The default value is @c ListHeaderMode::Standard.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::ListHeaderMode::Type headerMode
                   READ headerMode
                   WRITE setHeaderMode
                   RESET resetHeaderMode
                   NOTIFY headerModeChanged
                   FINAL)

    public:
        /*!
         * @brief Constructs a @c %StackListLayout instance.
         *
         * @since BlackBerry 10.0.0
         */
        StackListLayout();
        virtual ~StackListLayout();

        /*!
         * @brief Returns the @c #orientation for the @c %StackListLayout.
         *
         * @return The orientation of the layout.
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::LayoutOrientation::Type orientation() const;

        /*!
         * @brief Sets the @c #orientation for the @c %StackListLayout.
         *
         * If the orientation is changed, the @c orientationChanged() signal is emitted.
         *
         * @param orientation The new orientation.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setOrientation(bb::cascades::LayoutOrientation::Type orientation);

        /*!
         * @brief Resets the @c #orientation to its default.
         *
         * The default orientation is @c LayoutOrientation::TopToBottom.
         *
         * If the orientation is changed, the @c orientationChanged() signal is emitted.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetOrientation();

        /*!
         * @brief Returns the value of the @c #headerMode property.
         *
         * @return The value of the @c #headerMode property.
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::ListHeaderMode::Type headerMode() const;

        /*!
         * @brief Sets a value on the @c #headerMode property.
         *
         * @param newHeaderMode The value to set on the @c #headerMode property.
         *
         * If the property value is changed, the @c headerModeChanged() signal is emitted.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setHeaderMode(bb::cascades::ListHeaderMode::Type newHeaderMode);

        /*!
         * @brief Resets the @c #headerMode property to its default value.
         *
         * The default value is @c ListHeaderMode::Standard.
         *
         * If the property value is changed, the @c headerModeChanged() signal is emitted.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetHeaderMode();

    Q_SIGNALS:
        /*!
         * @brief Emitted when the @c #orientation property has changed.
         *
         * @note Due to a workaround for a Qt Core issue with accessing enums from QML
         * the argument of this signal doesn't follow naming convention for signals in
         * which the signal arguments are typically named to match the associated property's name.
         * Use the object's property to access current property value instead of the signal argument
         * to avoid runtime errors (i.e. use @c orientation instead of @c newOrientation).
         *
         * @param newOrientation The new orientation.
         *
         * @since BlackBerry 10.0.0
         */
        void orientationChanged(bb::cascades::LayoutOrientation::Type newOrientation);

        /*!
         * @brief Emitted when the @c #headerMode property has changed.
         *
         * @note Due to a workaround for a Qt Core issue with accessing enums from QML
         * the argument of this signal doesn't follow naming convention for signals in
         * which the signal arguments are typically named to match the associated property's name.
         * Use the object's property to access current property value instead of the signal argument
         * to avoid runtime errors (i.e. use @c headerMode instead of @c newHeaderMode).
         *
         * @param newHeaderMode The new value for the @c %headerMode property.
         *
         * @since BlackBerry 10.0.0
         */
        void headerModeChanged(bb::cascades::ListHeaderMode::Type newHeaderMode);

    private:
        Q_DECLARE_PRIVATE(StackListLayout)
        Q_DISABLE_COPY(StackListLayout)

    public:
        /*! @cond PRIVATE */
        typedef StackListLayout ThisClass;
        typedef ListLayout BaseClass;
        /*! @endcond */


        /*!
         * @brief A template builder class for constructing a @c %StackListLayout.
         *
         * To retrieve the builder, call StackListLayout::create().
         *
         * @since BlackBerry 10.0.0
         */
        template <typename BuilderType, typename BuiltType>
        class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType> {
        protected:
            TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node) {
            }

        public:

            /*!
             * @copydoc bb::cascades::StackListLayout::setOrientation(bb::cascades::LayoutOrientation::Type)
             */
            BuilderType& orientation(bb::cascades::LayoutOrientation::Type orientation) {
                this->instance().setOrientation(orientation);
                return this->builder();
            }

            /*!
             * @copydoc bb::cascades::StackListLayout::setHeaderMode(bb::cascades::ListHeaderMode::Type)
             */
            BuilderType& headerMode(bb::cascades::ListHeaderMode::Type newHeaderMode) {
                this->instance().setHeaderMode(newHeaderMode);
                return this->builder();
            }
        };

        /*!
         * @brief A concrete builder class for constructing a @c %StackListLayout.
         *
         * To retrieve the builder, call StackListLayout::create().
         *
         * @since BlackBerry 10.0.0
         */
        class Builder : public TBuilder<Builder, StackListLayout>
        {
        public:
            Builder() : TBuilder<Builder, StackListLayout>(new StackListLayout()) {
            }
        };

        /*!
        * @brief Creates and returns a builder for constructing a stack list layout.
        *
        * Using the builder to create a stack list layout:
        * @code
        * StackListLayout* stackListLayout = StackListLayout::create()
        *         .orientation(LayoutOrientation::LeftToRight);
        * @endcode
        *
        * @return A builder used for constructing a stack list layout.
        *
        * @since BlackBerry 10.0.0
        */
        static Builder create() {
            return Builder();
        }

    }; // class StackListLayout
} // namespace bb::cascades
}

QML_DECLARE_TYPE(bb::cascades::StackListLayout)

#endif	// cascades_stacklistlayout_h
