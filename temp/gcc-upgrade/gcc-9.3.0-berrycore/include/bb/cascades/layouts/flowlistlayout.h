/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_flowlistlayout_h
#define cascades_flowlistlayout_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/layouts/layoutorientation.h>
#include <bb/cascades/layouts/listlayout.h>
#include <bb/cascades/layouts/listheadermode.h>


namespace bb {
    namespace cascades {

    class FlowListLayoutPrivate;

    /*!
     * @brief A layout used to fill rows and columns based on available space.
     *
     * @image html cascades_flowlistlayout.png A FlowListLayout with two headers and ten entries
     * 
     * A @c FlowListLayout is used with a @c ListView to fill rows or columns with as
     * many items as there's room for, based on the dimensions of the @c %ListView.
     *
     * You can set the layout of a @c %ListView to a @c %FlowListLayout by using the
     * @c ListView::layout property.
     *
     * The @c #orientation property determines the direction in which list items
     * are added to the list (for example, when using @c TopToBottom, items
     * are added row-by-row starting from the top). Header items always occupy
     * a full row (in vertical lists) or column (in horizontal lists) by
     * themselves, but other items are placed so that rows/columns contain
     * as many items as possible, given the preferred size of those items.
     *
     * If @c #headerMode is set to @c ListHeaderMode::None, @c %FlowListLayout
     * only uses the items that are direct children of @c ListView::rootIndexPath.
     * In that case, all items are placed in one large section without any headers.
     * Other values of @c headerMode cause the first level of items to be
     * used as headers, and children of header items are then placed in flow
     * layout sections after each header. If @c headerMode is set to @c
     * @c ListHeaderMode::Overlay or @c ListHeaderMode::StickyOverlay,
     * headers are placed on top of their children, at the beginning of each
     * section.
     *
     * Margin properties on root nodes of item visuals affect the spacing
     * between items in a @c %FlowListLayout. The distance between two
     * items will be that of the largest of the two adjacent margins.
     *
     * A preferred size can be specified on item visuals, but these are limited
     * by the width or height (minus padding) of the @c %ListView (width is limited
     * in vertical lists, height is limited in horizontal lists).
     *
     * Instead of specifying a preferred size on item visuals, a
     * @c FlowListLayoutProperties object can be assigned to the root node of
     * item visuals. In this way, the size of the items can be linked to the size
     * of the @c %ListView, with padding and margins taken into consideration.
     *
     * This QML example demonstrates how to implement a list containing both
     * stack sections and grid sections by using @c %FlowListLayout. The
     * @c DataModel is expected to contain a single type of item in each section;
     * this example won't look good if item types are mixed inside a section.
     *
     * @code
     * ListView {
     *     topPadding: 6
     *     rightPadding: 6
     *     bottomPadding: 6
     *     leftPadding: 6
     *
     *     layout: FlowListLayout { }
     *     dataModel: XmlDataModel {
     *         source: "model.xml"
     *     }
     *
     *     listItemComponents: [
     *         ListItemComponent {
     *             type: "header"
     *
     *             Header {
     *                 topMargin: 8
     *                 title: ListItemData.title
     *                 subtitle: (ListItem.initialized ?
     *                     ListItem.view.dataModel.childCount(
     *                     ListItem.indexPath) : 0) + " results"
     *             }
     *         },
     *         ListItemComponent {
     *             type: "stack"
     *
     *             StandardListItem {
     *                 imageSource: ListItemData.icon
     *                 title: ListItemData.title
     *             }
     *         },
     *         ListItemComponent {
     *             type: "grid"
     *
     *             ImageView {
     *                 rightMargin: 6
     *                 bottomMargin: 6
     *                 imageSource: ListItemData.imagePath
     *                 layoutProperties: FlowListLayoutProperties {
     *                     aspectRatio: 4/3
     *                     fillRatio: 0.5
     *                 }
     *             }
     *         }
     *     ]
     * }
     * @endcode
     *
     * This QML example demonstrates a flow layout in a list without headers.
     * In this case, the @c #headerMode property must be set to @c ListHeaderMode::None,
     * otherwise the top level items are treated as headers. Headers always
     * occupy a full row or column by themselves, no matter how small they are.
     * Note that this particular example could have been implemented more easily by using
     * @c GridListLayout, since all items are the same size.
     *
     * @code
     * ListView {
     *     dataModel: XmlDataModel { source: "model.xml" }
     *     layout: FlowListLayout { headerMode: ListHeaderMode.None }
     *     listItemComponents: [
     *         ListItemComponent {
     *             type: "item"
     *
     *             ImageView {
     *                 rightMargin: 6
     *                 bottomMargin: 6
     *                 imageSource: ListItemData.imagePath
     *                 layoutProperties: FlowListLayoutProperties {
     *                     aspectRatio: 1
     *                     fillRatio: 1/3
     *                 }
     *             }
     *         }
     *     ]
     * }
     * @endcode
     *
     * @see ListView, FlowListLayoutProperties
     *
     * @xmlonly
     * <apigrouping group="User interface/Layouts"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT FlowListLayout : public ListLayout {
    private:
        Q_OBJECT

        /*!
         * @brief The orientation for the flow layout.
         *
         * The orientation determines the direction in which list items
         * are added to the list (for example, when using @c TopToBottom, items
         * are added row-by-row starting from the top).
         * If items exist outside of the visible area, it is possible to scroll
         * the list to view them.
         *
         * Item sizes have no limitation in the orientation direction, but are limited
         * in the opposite direction.
         * For example, in a @c %ListView that uses a @c %FlowListLayout with an
         * @c orientation of @c TopToBottom or @c BottomToTop, the height of
         * the items is only limited by the items themselves. But, the width of items
         * is limited by the width of the @c %ListView, minus any @c leftPadding and
         * @c rightPadding that might be applied on the @c %ListView.
         *
         * The default @c %orientation is @c TopToBottom, but @c LeftToRight,
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
         * @brief Determines if and how headers are shown by the @c %FlowListLayout.
         *
         * If @c headerMode is set to @c ListHeaderMode::None, @c %FlowListLayout
         * only uses the items that are direct children of @c ListView::rootIndexPath.
         * In that case, all items are placed in one large section without any headers.
         * Other values of @c headerMode cause the first level of items to be
         * used as headers, and children of header items are then placed in flow
         * layout sections after each header. If @c headerMode is set to @c
         * @c ListHeaderMode::Overlay or @c ListHeaderMode::StickyOverlay,
         * headers are placed on top of their children, at the beginning of each
         * section.
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
         * @brief Constructs a @c %FlowListLayout instance.
         *
         * @since BlackBerry 10.0.0
         */
        FlowListLayout();
        virtual ~FlowListLayout();

        /*!
         * @brief Returns the @c #orientation of this @c %FlowListLayout.
         *
         * @return The orientation.
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::LayoutOrientation::Type orientation() const;

        /*!
         * @brief Sets the @c #orientation of this @c %FlowListLayout.
         *
         * If the orientation is changed, the @c orientationChanged() signal is emitted.
         *
         * @param orientation The new orientation.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setOrientation(bb::cascades::LayoutOrientation::Type orientation);

        /*!
         * @brief Resets the @c #orientation to its default value.
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
         * @brief Sets the value of the @c #headerMode property.
         *
         * If the property value is changed, the @c headerModeChanged() signal is emitted.
         * 
         * @param newHeaderMode The value to set for the @c #headerMode property.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setHeaderMode(bb::cascades::ListHeaderMode::Type newHeaderMode);

        /*!
         * @brief Resets the #headerMode property to its default value.
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
         * @note Due to a workaround for a Qt Core issue with accessing enums from QML,
         * the argument of this signal doesn't follow the naming convention for signals, in
         * which the signal arguments are typically named to match the associated property's name.
         * Use the object's property, instead of the signal argument, to access the current
         * property value and avoid runtime errors (use @c orientation instead of
         * @c newOrientation).
         *
         * @param newOrientation The new orientation.
         *
         * @since BlackBerry 10.0.0
         */
        void orientationChanged(bb::cascades::LayoutOrientation::Type newOrientation);

        /*!
         * @brief Emitted when the @c #headerMode property has changed.
         *
         * @note Due to a workaround for a Qt Core issue with accessing enums from QML,
         * the argument of this signal doesn't follow the naming convention for signals, in
         * which the signal arguments are typically named to match the associated property's name.
         * Use the object's property, instead of the signal argument, to access the current
         * property value and avoid runtime errors ( use @c headerMode instead of
         * @c newHeaderMode).
         *
         * @param newHeaderMode The new value for the @c %headerMode property.
         *
         * @since BlackBerry 10.0.0
         */
        void headerModeChanged(bb::cascades::ListHeaderMode::Type newHeaderMode);

    private:
        Q_DECLARE_PRIVATE(FlowListLayout)
        Q_DISABLE_COPY(FlowListLayout)

    public:
        /*! @cond PRIVATE */
        typedef FlowListLayout ThisClass;
        typedef ListLayout BaseClass;
        /*! @endcond */


        /*!
         * @brief A template builder class for constructing a @c %FlowListLayout.
         *
         * To retrieve the builder, call @c FlowListLayout::create().
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
             * @copydoc bb::cascades::FlowListLayout::setOrientation(bb::cascades::LayoutOrientation::Type)
             */
            BuilderType& orientation(bb::cascades::LayoutOrientation::Type orientation) {
                this->instance().setOrientation(orientation);
                return this->builder();
            }

            /*!
             * @copydoc bb::cascades::FlowListLayout::setHeaderMode(bb::cascades::ListHeaderMode::Type)
             */
            BuilderType& headerMode(bb::cascades::ListHeaderMode::Type newHeaderMode) {
                this->instance().setHeaderMode(newHeaderMode);
                return this->builder();
            }
        };

        /*!
         * @brief A concrete builder class for constructing a @c %FlowListLayout.
         *
         * To retrieve the builder, call @c FlowListLayout::create().
         *
         * @since BlackBerry 10.0.0
         */
        class Builder : public TBuilder<Builder, FlowListLayout>
        {
        public:
            Builder() : TBuilder<Builder, FlowListLayout>(new FlowListLayout()) {
            }
        };

        /*!
        * @brief Creates and returns a builder for constructing a flow list layout.
        *
        * Using the builder to create a flow list layout:
        * @code
        * FlowListLayout* flowListLayout = FlowListLayout::create()
        *         .orientation(LayoutOrientation::LeftToRight);
        * @endcode
        *
        * @return A builder used for constructing a flow list layout.
         *
         * @since BlackBerry 10.0.0
        */
        static Builder create() {
            return Builder();
        }

    }; // class FlowListLayout
} // namespace bb::cascades
}

QML_DECLARE_TYPE(bb::cascades::FlowListLayout)

#endif	// cascades_flowlistlayout_h
