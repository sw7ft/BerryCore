/* Copyright (C) 2013 BlackBerry. All rights reserved. */

#ifndef cascades_gridlayout_h
#define cascades_gridlayout_h


#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/layouts/layout.h>


namespace bb {
    namespace cascades {

    class GridLayoutPrivate;

    /*!
     *
     * @brief A layout that arranges a container's children in a grid.
     *
     * A grid layout uses cells to arrange components in the order they are added
     * in your code. You specify the number of vertical columns in the grid using the
     * @c #columnCount property, and the OS determines the number of rows automatically
     * based on the total number of components in your grid layout. For example, if you add
     * five components and specify a @c %columnCount of 2, your grid layout will
     * have three rows total, with two components in the first row, two in the second, and one in the third.
     *
     * Each cell of a @c %GridLayout behaves in a similar fashion as a @c Container with a single child control
     * regarding padding and alignment properties.
     *
     * You can use the @c Control::horizontalAlignment and @c Control::verticalAlignment properties
     * to specify how controls are aligned horizontally (left, center, or right) and
     * vertically (top, center, bottom) within the control's grid cell. Controls can also
     * expand or contract to fill the cell in a specified direction.
     *
     * For instance, setting the @c %horizontalAlignment property to @c %HorizontalAlignment.Fill and setting
     * a @c %leftPadding of 10 causes a child control to fill the cell area, but leave 10 units of spacing to the
     * left of the child within the cell's area. Additionally, setting a @c %leftPadding of 5 on the parent container
     * causes all the cells in the grid layout to be inset by 5 units from the left edge of the parent container.
     *
     * The following examples demonstrate how to use @c %GridLayout to positigon buttons within a @c Container.
     *
     * @image html gridlayout.png
     *
     * QML:
     *
     * @code
     * Container {
     *     layout: GridLayout {
     *         columnCount: 2
     *     }
     *
     *     Button {
     *         text: "Button1"
     *         horizontalAlignment: HorizontalAlignment.Center
     *         verticalAlignment: VerticalAlignment.Top
     *     }
     *
     *     Button {
     *         text: "Button2"
     *         horizontalAlignment: HorizontalAlignment.Right
     *         verticalAlignment: VerticalAlignment.Center
     *     }
     *
     *     Button {
     *         text: "Button3"
     *         horizontalAlignment: HorizontalAlignment.Fill
     *         verticalAlignment: VerticalAlignment.Center
     *     }
     * }
     * @endcode
     *
     * C++:
     *
     * @code
     * Container* pContainer = new Container();
     * GridLayout *pGridLayout = new GridLayout();
     * pGridLayout->setColumnCount(2);
     * pContainer->setLayout(pGridLayout);
     *
     * Button* pButton1 = Button::create().text("Button1");
     *
     * pButton1->setHorizontalAlignment(HorizontalAlignment::Center);
     * pButton1->setVerticalAlignment(VerticalAlignment::Top);
     *
     * Button* pButton2 = Button::create().text("Button2");
     *
     * pButton2->setHorizontalAlignment(HorizontalAlignment::Right);
     * pButton2->setVerticalAlignment(VerticalAlignment::Center);
     *
     * Button* pButton3 = Button::create().text("Button3");
     *
     * pButton3->setHorizontalAlignment(HorizontalAlignment::Fill);
     * pButton3->setVerticalAlignment(VerticalAlignment::Center);
     *
     * pContainer->add( pButton1 );
     * pContainer->add( pButton2 );
     * pContainer->add( pButton3 );
     * @endcode
     *
     * @xmlonly
     * <apigrouping group="User interface/Layouts"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.3.0
     */
    class BBCASCADES_EXPORT GridLayout : public Layout {
    private:
        Q_OBJECT

    public:
        /*!
         * @brief Constructs a @c %GridLayout object.
         *
         * When you set a layout on a container using @c Container::setLayout(),
         * the container assumes ownership of the layout.
         *
         * @since BlackBerry 10.3.0
         */
        GridLayout();
        virtual ~GridLayout();

    Q_SIGNALS:
        /*! \cond PRIVATE */
    private:
        Q_DECLARE_PRIVATE(GridLayout)
        Q_DISABLE_COPY(GridLayout)
        /*! \endcond */

        /*!
         * @brief The number of columns for the grid layout.
         *
         * The default value is 2. Setting the value to 0 creates as many columns as
         * there are child components in the grid layout, and each component is placed
         * in a separate column. The value of the property however is not recalculated
         * but will remain as 0 for that case.
         *
         * QML example
         *
         * @code
         * Container {
         *     layout: GridLayout {
         *         columnCount: 2
         *     }
         * }
         * @endcode
         *
         * @since BlackBerry 10.3.0
         */
        Q_PROPERTY(int columnCount
                   READ columnCount
                   WRITE setColumnCount
                   RESET resetColumnCount
                   NOTIFY columnCountChanged
                   FINAL)

    public:
        /*! @cond PRIVATE */
        typedef GridLayout ThisClass;
        typedef Layout BaseClass;
        /*! @endcond */

        /*!
         * @brief Returns the @c #columnCount for the grid layout.
         *
         * @return The number of columns in the grid layout, or 0 if the layout is set to use as many
         *         columns as there are children.
         *
         * @since BlackBerry 10.3.0
         */
        int columnCount() const;

        /*!
         * @brief Sets the @c #columnCount for the grid layout.
         *
         * After the @c %columnCount is set, the @c columnCountChanged() signal is emitted.
         *
         * @param columnCount The number of columns in the grid layout.
         *
         * @since BlackBerry 10.3.0
         */
        Q_SLOT void setColumnCount(int columnCount);

        /*!
         * @brief Resets the @c #columnCount to its default value.
         *
         * The default value is 2.
         *
         * After the @c %columnCount is reset, the @c columnCountChanged() signal is emitted.
         *
         * @since BlackBerry 10.3.0
         */
        Q_SLOT void resetColumnCount();

    Q_SIGNALS:
        /*!
         * @brief Emitted when the @c #columnCount property changes.
         *
         * @param columnCount The new value of the property.
         *
         * @note If columnCount is set to zero, adding or removing children and thus changing the internal
         *       number of columns in the layout, will not trigger a columnCountChanged signal.
         *
         * @since BlackBerry 10.3.0
         */
        void columnCountChanged(int columnCount);

    public:
        /*!
         * @brief A template builder class for constructing a @c %GridLayout.
         *
         * To retrieve the builder, call @c GridLayout::create().
         *
         * @since BlackBerry 10.3.0
         */
        template <typename BuilderType, typename BuiltType>
        class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType> {
        protected:
            TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node) {
            }

        public:

            /*!
             * @copydoc bb::cascades::GridLayout::setColumnCount(int)
             */
            BuilderType& columnCount(int columnCount) {
              this->instance().setColumnCount(columnCount);
              return this->builder();
            }
        };


        /*!
         * @brief A concrete builder class for constructing a @c %GridLayout.
         *
         * To retrieve the builder, call @c GridLayout::create().
         *
         * @since BlackBerry 10.3.0
         */
        class Builder : public TBuilder<Builder, GridLayout>
        {
        public:
            Builder() : TBuilder<Builder, GridLayout>(new GridLayout()) {
            }
        };

        /*!
        * @brief Creates and returns a builder for constructing a grid layout.
        *
        * Using the builder to create a grid layout:
        *
        * @code
        * GridLayout* pGridLayout = GridLayout::create()
        * @endcode
        *
        * @return A builder used for constructing a @c %GridLayout.
        *
        * @since BlackBerry 10.3.0
        */
        static Builder create() {
            return Builder();
        }
    }; // class GridLayout
} // namespace bb::cascades
}


QML_DECLARE_TYPE(bb::cascades::GridLayout)


#endif	// cascades_gridlayout_h

