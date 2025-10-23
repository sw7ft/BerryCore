/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_gridlistlayout_h
#define cascades_gridlistlayout_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/layouts/listlayout.h>
#include <bb/cascades/layouts/layoutorientation.h>
#include <bb/cascades/layouts/listheadermode.h>


namespace bb {
    namespace cascades {

    class GridListLayoutPrivate;

    /*!
     *
     * @brief A layout used with @c ListView to lay out items in a grid.
     *
     * @image html cascades_gridlistlayout.png A GridListLayout with ten items
     *
     * You can set @c %GridListLayout using the @c ListView::layout property.
     *
     * The @c #orientation property determines the direction in which list items
     * are added to the list (for example, when using @c TopToBottom, items
     * are added row-by-row starting from the top).
     *
     * All margin-properties on item visuals are ignored by @c %GridListLayout.
     *
     * For non-header items, the layout sets the size of the root node in the
     * item visual to the size of a cell in the grid. All cells in the grid
     * are of the same size, a size which is determined by a combination of the
     * size of the @c %ListView and the values of the @c %GridListLayout
     * properties @c #orientation, @c #columnCount, @c #cellAspectRatio and either
     * @c #horizontalCellSpacing, @c ListView::leftPadding and @c ListView::rightPadding
     * (for vertical lists), or @c #verticalCellSpacing, @c ListView::topPadding
     * and @c ListView::bottomPadding (for horizontal lists).
     *
     * Header item visuals are given their preferred size, only limited by the
     * width or height (minus padding) of the @c %ListView (width is limited
     * in vertical lists, height is limited in horizontal lists). Headers never
     * share their row (column in horizontal lists) with any other item, even
     * if the header only occupies a small portion of that row. Headers are
     * placed on top of grid items when @c #headerMode is @c Overlay or
     * @c StickyOverlay, but that does not affect the placement of the grid
     * items. If @c #headerMode is @c None, only one level of items from the
     * @c DataModel is used. You must set @c #headerMode to something other than
     * @c None when using @c #GridListLayout with a @c GroupDataModel.
     *
     * Here's an example in QML of a grid list containing photo thumbnails (without headers):
     *
     * @code
     * ListView {
     *     layout: GridListLayout {}
     *     dataModel: XmlDataModel {
     *         source: "flatmodel.xml"
     *     }
     *
     *     listItemComponents: [
     *         ListItemComponent {
     *             type: "image"
     *
     *             ImageView {
     *                 imageSource: ListItemData
     *                 scalingMethod: ScalingMethod.AspectFill
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
    class BBCASCADES_EXPORT GridListLayout : public ListLayout {
    private:
        Q_OBJECT

        /*!
         * @brief The orientation for the grid layout.
         *
         * The orientation determines the direction in which list items are
         * added to the list.
         *
         * The default orientation is @c TopToBottom, but @c LeftToRight,
         * @c RightToLeft, and @c BottomToTop can also be used.
         *
         * @c TopToBottom and @c BottomToTop causes items to be laid out
         * row-by-row. The value of the #columnCount property determines
         * the number of items in each row. Items are arranged from left to
         * right in the rows. @c TopToBottom causes the first row to be placed
         * at the top of the visible area in the @c ListView, while @c BottomToTop
         * causes the first row to be placed at the bottom.
         *
         * @c LeftToRight and @c RightToLeft causes items to be laid out
         * column-by-column. The value of the #columnCount property determines
         * the number of items in each column. Items are arranged from top to
         * bottom in the columns. @c LeftToRight causes the first column to be
         * placed at the left border of the visible area in the @c %ListView, while
         * @c RightToLeft causes the first column to be placed at the right border.
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
         * @brief The number of columns in the grid (or rows, depending on the orientation).
         *
         * When the @c #orientation is @c TopToBottom or @c BottomToTop,
         * the @c columnCount property determines the number of columns in the
         * grid. If @c orientation is @c LeftToRight or @c RightToLeft,
         * this property instead determines the number of rows.
         *
         * The default value is 3.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(int columnCount
                   READ columnCount
                   WRITE setColumnCount
                   RESET resetColumnCount
                   NOTIFY columnCountChanged
                   FINAL)

        /*!
         * @brief The cell aspect ratio (cell width divided by cell height).
         *
         * If the @c #orientation is @c TopToBottom or @c BottomToTop, the width of a cell
         * in the grid is determined by this formula:
         *
         * ((current width of the @c ListView) - @c ListView::leftPadding -
         * @c ListView::rightPadding) - (#columnCount - 1) * #horizontalCellSpacing) /
         * #columnCount
         *
         * The height of a cell is then determined by the cell width divided by
         * @c %cellAspectRatio.
         *
         * If @c the orientation is @c LeftToRight or @c RightToLeft, the height of a cell
         * in the grid is determined by this formula:
         *
         * ((current height of the @c %ListView) - @c ListView::topPadding -
         * @c ListView::bottomPadding) - (#columnCount - 1) * #verticalCellSpacing) /
         * #columnCount
         *
         * The width of a cell is then determined by the cell height multiplied by
         * @c %cellAspectRatio.
         *
         * The default value is 1.0.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float cellAspectRatio
                   READ cellAspectRatio
                   WRITE setCellAspectRatio
                   RESET resetCellAspectRatio
                   NOTIFY cellAspectRatioChanged
                   FINAL)

        /*!
         * @brief The horizontal distance between cells.
         *
         * The default value is 6.0.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float horizontalCellSpacing
                   READ horizontalCellSpacing
                   WRITE setHorizontalCellSpacing
                   RESET resetHorizontalCellSpacing
                   NOTIFY horizontalCellSpacingChanged
                   FINAL)

        /*!
         * @brief The vertical distance between cells.
         *
         * The default value is 6.0.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float verticalCellSpacing
                   READ verticalCellSpacing
                   WRITE setVerticalCellSpacing
                   RESET resetVerticalCellSpacing
                   NOTIFY verticalCellSpacingChanged
                   FINAL)

        /*!
         * @brief The distance from the end of a grid section to the next header.
         *
         * The default value is 8.0.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float spacingBeforeHeader
                   READ spacingBeforeHeader
                   WRITE setSpacingBeforeHeader
                   RESET resetSpacingBeforeHeader
                   NOTIFY spacingBeforeHeaderChanged
                   FINAL)

        /*!
         * @brief The distance from a header to its grid section.
         *
         * The default value is 6.0.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float spacingAfterHeader
                   READ spacingAfterHeader
                   WRITE setSpacingAfterHeader
                   RESET resetSpacingAfterHeader
                   NOTIFY spacingAfterHeaderChanged
                   FINAL)

        /*!
         * @brief Determines if and how headers are shown by the @c GridListLayout.
         *
         * If set to @c None, only one level of items from the @c DataModel is used.
         * Otherwise the first level of items under the root item are used as
         * headers, and their child items are placed in grids.
         *
         * The default value is @c ListHeaderMode::None.
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
         * @brief Constructs a @c %GridListLayout instance.
         *
         * @since BlackBerry 10.0.0
         */
        GridListLayout();
        virtual ~GridListLayout();

        /*!
         * @brief Returns the @c #orientation for the grid layout.
         *
         * @return The orientation.
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::LayoutOrientation::Type orientation() const;

        /*!
         * @brief Sets the @c #orientation for the grid layout.
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
         * @brief Returns the value of @c #columnCount.
         *
         * @return The number of columns in the grid when @c #orientation is
         * @c TopToBottom or @c BottomToTop. If @c orientation is @c LeftToRight or
         * @c RightToLeft, this function instead returns the number of rows in the grid.
         *
         * @since BlackBerry 10.0.0
         */
        int columnCount() const;

        /*!
         * @brief Sets a value for @c #columnCount.
         *
         * If the property value is changed, the @c columnCountChanged() signal is emitted.
         *
         * @param columnCount The number of columns the grid should have when
         * @c #orientation is @c TopToBottom or @c BottomToTop. Or the number of
         * rows the grid should have, if @c orientation is @c LeftToRight or @c RightToLeft.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setColumnCount(int columnCount);

        /*!
         * @brief Resets the @c #columnCount property to its default value of 3.
         *
         * If the property value is changed, the @c columnCountChanged() signal is emitted.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetColumnCount();

        /*!
         * @brief Returns the value of @c #cellAspectRatio.
         *
         * @return The cell aspect ratio (cell width divided by cell height).
         *
         * @since BlackBerry 10.0.0
         */
        float cellAspectRatio() const;

        /*!
         * @brief Sets a value for @c #cellAspectRatio.
         *
         * If the property value is changed, the @c cellAspectRatioChanged() signal is emitted.
         *
         * @param ratio The new cell aspect ratio (cell width divided by cell height).
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setCellAspectRatio(float ratio);

        /*!
         * @brief Resets the @c #cellAspectRatio property to its default value of 1.0.
         *
         * If the property value is changed, the @c cellAspectRatioChanged() signal is emitted.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetCellAspectRatio();

        /*!
         * @brief Returns the value of @c #horizontalCellSpacing.
         *
         * @return The horizontal distance between cells.
         *
         * @since BlackBerry 10.0.0
         */
        float horizontalCellSpacing() const;

        /*!
         * @brief Sets a value for @c #horizontalCellSpacing.
         *
         * If the property value is changed, the @c horizontalCellSpacingChanged() signal is emitted.
         *
         * @param spacing The new horizontal distance between cells.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setHorizontalCellSpacing(float spacing);

        /*!
         * @brief Resets the @c #horizontalCellSpacing property to its default value of 6.0.
         *
         * If the property value is changed, the @c horizontalCellSpacingChanged() signal is emitted.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetHorizontalCellSpacing();

        /*!
         * @brief Returns the value of @c #verticalCellSpacing.
         *
         * @return The vertical distance between cells.
         *
         * @since BlackBerry 10.0.0
         */
        float verticalCellSpacing() const;

        /*!
         * @brief Sets a value for @c #verticalCellSpacing.
         *
         * If the property value is changed, the @c verticalCellSpacingChanged() signal is emitted.
         *
         * @param spacing The new vertical distance between cells.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setVerticalCellSpacing(float spacing);

        /*!
         * @brief Resets the @c #verticalCellSpacing property to its default value of 6.0.
         *
         * If the property value is changed, the @c verticalCellSpacingChanged() signal is emitted.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetVerticalCellSpacing();

        /*!
         * @brief Returns the value of @c #spacingBeforeHeader.
         *
         * @return Distance from the end of a grid section to the next header.
         *
         * @since BlackBerry 10.0.0
         */
        float spacingBeforeHeader() const;

        /*!
         * @brief Sets a value for @c #spacingBeforeHeader.
         *
         * If the property value is changed, the @c spacingBeforeHeaderChanged() signal is emitted.
         *
         * @param spacing The new distance from the end of a grid section to the next header.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setSpacingBeforeHeader(float spacing);

        /*!
         * @brief Resets the @c #spacingBeforeHeader property to its default value of 8.0.
         *
         * If the property value is changed, the @c spacingBeforeHeaderChanged() signal is emitted.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetSpacingBeforeHeader();

        /*!
         * @brief Returns the value of @c #spacingAfterHeader.
         *
         * @return Distance from a header to its grid section.
         *
         * @since BlackBerry 10.0.0
         */
        float spacingAfterHeader() const;

        /*!
         * @brief Sets a value for @c #spacingAfterHeader.
         *
         * If the property value is changed, the @c spacingAfterHeaderChanged() signal is emitted.
         *
         * @param spacing The new distance from a header to its grid section.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setSpacingAfterHeader(float spacing);

        /*!
         * @brief Resets the @c #spacingAfterHeader property to its default value of 6.0.
         *
         * If the property value is changed, the @c spacingAfterHeaderChanged() signal is emitted.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetSpacingAfterHeader();

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
         * If the property value is changed, the @c headerModeChanged() signal is emitted.
         *
         * @param newHeaderMode The value to set on the @c #headerMode property.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setHeaderMode(bb::cascades::ListHeaderMode::Type newHeaderMode);

        /*!
         * @brief Resets the @c #headerMode property to its default value.
         *
         * The default value is @c ListHeaderMode::None.
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
         * @brief Emitted when the @c #columnCount property has changed.
         *
         * @param columnCount The new number of columns.
         *
         * @since BlackBerry 10.0.0
         */
        void columnCountChanged(int columnCount);

        /*!
         * @brief Emitted when the @c #cellAspectRatio property has changed.
         *
         * @param cellAspectRatio The new value for the @c %cellAspectRatio property.
         *
         * @since BlackBerry 10.0.0
         */
        void cellAspectRatioChanged(float cellAspectRatio);

        /*!
         * @brief Emitted when the @c #horizontalCellSpacing property has changed.
         *
         * @param horizontalCellSpacing The new value for the @c %horizontalCellSpacing property.
         *
         * @since BlackBerry 10.0.0
         */
        void horizontalCellSpacingChanged(float horizontalCellSpacing);

        /*!
         * @brief Emitted when the @c #verticalCellSpacing property has changed.
         *
         * @param verticalCellSpacing The new value for the @c %verticalCellSpacing property.
         *
         * @since BlackBerry 10.0.0
         */
        void verticalCellSpacingChanged(float verticalCellSpacing);

        /*!
         * @brief Emitted when the @c #spacingBeforeHeader property has changed.
         *
         * @param spacingBeforeHeader The new value for the @c %spacingBeforeHeader property.
         *
         * @since BlackBerry 10.0.0
         */
        void spacingBeforeHeaderChanged(float spacingBeforeHeader);

        /*!
         * @brief Emitted when the @c #spacingAfterHeader property has changed.
         *
         * @param spacingAfterHeader The new value for the @c %spacingAfterHeader property.
         *
         * @since BlackBerry 10.0.0
         */
        void spacingAfterHeaderChanged(float spacingAfterHeader);

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
        Q_DECLARE_PRIVATE(GridListLayout)
        Q_DISABLE_COPY(GridListLayout)

    public:
        /*! @cond PRIVATE */
        typedef GridListLayout ThisClass;
        typedef ListLayout BaseClass;
        /*! @endcond */


        /*!
         * @brief A template builder class for constructing a @c %GridListLayout.
         *
         * To retrieve the builder, call @c GridListLayout::create().
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
             * @copydoc bb::cascades::GridListLayout::setOrientation(bb::cascades::LayoutOrientation::Type)
             */
            BuilderType& orientation(bb::cascades::LayoutOrientation::Type orientation) {
                this->instance().setOrientation(orientation);
                return this->builder();
            }

            /*!
             * @copydoc bb::cascades::GridListLayout::setColumnCount(int)
             */
            BuilderType& columnCount(int columnCount) {
                this->instance().setColumnCount(columnCount);
                return this->builder();
            }

            /*!
             * @copydoc bb::cascades::GridListLayout::setCellAspectRatio(float)
             */
            BuilderType& cellAspectRatio(float ratio) {
                this->instance().setCellAspectRatio(ratio);
                return this->builder();
            }

            /*!
             * @copydoc bb::cascades::GridListLayout::setHeaderMode(bb::cascades::ListHeaderMode::Type)
             */
            BuilderType& headerMode(bb::cascades::ListHeaderMode::Type newHeaderMode) {
                this->instance().setHeaderMode(newHeaderMode);
                return this->builder();
            }
        };

        /*!
         * @brief A concrete builder class for constructing a %GridListLayout.
         *
         * To retrieve the builder, call @c GridListLayout::create().
         *
         * @since BlackBerry 10.0.0
         */
        class Builder : public TBuilder<Builder, GridListLayout>
        {
        public:
            Builder() : TBuilder<Builder, GridListLayout>(new GridListLayout()) {
            }
        };

        /*!
        * @brief Creates and returns a builder for constructing a grid list layout.
        *
        * Using the builder to create a grid list layout:
        * @code
        * GridListLayout* gridListLayout = GridListLayout::create()
        *         .orientation(LayoutOrientation::LeftToRight);
        * @endcode
        *
        * @return A builder used for constructing a grid list layout.
         *
         * @since BlackBerry 10.0.0
        */
        static Builder create() {
            return Builder();
        }

    }; // class GridListLayout
} // namespace bb::cascades
}

QML_DECLARE_TYPE(bb::cascades::GridListLayout)

#endif	// cascades_gridlistlayout_h
