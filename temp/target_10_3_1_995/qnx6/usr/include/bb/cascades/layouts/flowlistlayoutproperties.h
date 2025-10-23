/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_flowlayoutproperties_h
#define cascades_flowlayoutproperties_h


#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/layouts/layoutproperties.h>


namespace bb {
    namespace cascades {

    class FlowListLayoutPropertiesPrivate;
    class Control;

    /*!
     * @brief Layout properties that are assigned to controls in a @c FlowListLayout.
     *
     * This class represents layout properties that you can assign to controls in
     * a @c ListView. The @c %ListView must use a @c %FlowListLayout as its layout.
     *
     * @c %FlowListLayoutProperties can be used to link the size of items
     * in a @c %FlowListLayout to the size of the @c %ListView, with padding
     * and margins taken into consideration.
     *
     * This QML example demonstrates how to use @c %FlowListLayoutProperties
     * on the root node of an item visual declared in a @c ListItemComponent.
     * If all items in this example are of the type "item", the items
     * are arranged in a grid containing three square-shaped images per row.
     * Note that this particular example could have been implemented more easily by
     * using @c GridListLayout, since all items are the same size.
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
     * This class can only be used with children of a @c %ListView that uses a
     * @c %FlowListLayout. If you attempt to use this class with another type of
     * Layout, it is ignored.
     *
     * @see ListView, FlowListLayout
     *
     * @xmlonly
     * <apigrouping group="User interface/Layouts"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT FlowListLayoutProperties : public LayoutProperties {
    private:
        Q_OBJECT

        /*!
         * @brief The aspect ratio (width divided by height) for the @c Control.
         *
         * If set, @c FlowListLayout ignores the value set on either @c preferredWidth
         * (in horizontal lists) or @c preferredHeight (in vertical lists) on the item visual
         * root node, and instead calculates the preferredWidth or preferredHeight from the
         * layout height or width of the @c %Control by using one of these equations:
         *
         * Horizontal list:  width = height * @c aspectRatio
         * Vertical list:  height = width / @c aspectRatio
         *
         * For example, a value of 1.3333 (or simply 4/3) for the @c aspectRatio ensures that
         * width = 1.3333 * height for the item visual, regardless of whether the
         * list orientation is vertical or horizontal.
         *
         * The properties @c minWidth, @c maxWidth, @c minHeight, and @c maxHeight on the
         * item visual root are not affected by this property. They still limit
         * the size of the item visual.
         *
         * If this property is set to 0 or less, no aspect ratio is taken into account.
         *
         * The default value is -1.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float aspectRatio
                   READ aspectRatio
                   WRITE setAspectRatio
                   RESET resetAspectRatio
                   NOTIFY aspectRatioChanged
                   FINAL)

        /*!
         * @brief The size of the @c Control, as a fraction of the @c ListView size.
         *
         * This property specifies the desired width or height (width in vertical lists,
         * height in horizontal lists) of the item visual, expressed as a fraction of
         * the @c %ListView width or height (minus padding and item margins). If set,
         * @c FlowListLayout ignores the value set for @c preferredWidth or @c preferredHeight
         * on the item visual root node, and instead uses a value calculated using @c fillRatio.
         *
         * For example, a value of 0.3333 (or simply 1/3) for @c fillRatio causes the item to use
         * one third of the available size in the row/column, so that there's
         * room for two more items of the same size in that row/column.
         *
         * There's room for three items on a row when @c fillRatio is 0.3333 for all
         * of them, even if the items have margins. This is because the available
         * size on a row is reduced by the size of the margins between the items,
         * before calculating the size of each item using the @c fillRatio.
         *
         * The properties @c minWidth, @c maxWidth, @c minHeight, and @c maxHeight on the
         * item visual root are not affected by this property. They still limit
         * the size of the item visual.
         *
         * If this property is set to 0 or less, no size ratio is taken into account.
         *
         * The default value is -1.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float fillRatio
                   READ fillRatio
                   WRITE setFillRatio
                   RESET resetFillRatio
                   NOTIFY fillRatioChanged
                   FINAL)


    public:
        /*!
         * @brief Constructs a @c %FlowListLayoutProperties object.
         *
         * @since BlackBerry 10.0.0
         */
        FlowListLayoutProperties();
        virtual ~FlowListLayoutProperties();

        /*!
         * @brief Returns the aspect ratio of the @c Control.
         *
         * @return The aspect ratio of the @c %Control.
         *
         * @since BlackBerry 10.0.0
         */
        float aspectRatio() const;

        /*!
         * @brief Sets the aspect ratio of the @c Control.
         *
         * After the aspect ratio is set, the @c aspectRatioChanged() signal is emitted.
         *
         * @param _aspectRatio The new aspect ratio of the @c %Control.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setAspectRatio(float _aspectRatio);

        /*!
         * @brief Resets the aspect ratio to its default value.
         *
         * The default aspect ratio is a negative value.
         *
         * After the aspect ratio is reset, the @c aspectRatioChanged() signal is emitted.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetAspectRatio();

        /*!
         * @brief Returns the fill ratio of the @c Control.
         *
         * @return The fill ratio of the @c %Control.
         *
         * @since BlackBerry 10.0.0
         */
        float fillRatio() const;

        /*!
         * @brief Sets the fill ratio of the @c Control.
         *
         * After the fill ratio is set, the @c fillRatioChanged() signal is emitted.
         *
         * @param _fillRatio The fill ratio of the @c %Control.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setFillRatio(float _fillRatio);

        /*!
         * @brief Resets the fill ratio to its default value.
         *
         * The default fill ratio is a negative value.
         *
         * After the fill ratio is reset, the @c fillRatioChanged() signal is emitted.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetFillRatio();

    Q_SIGNALS:
        /*!
         * @brief Emitted when the @c #aspectRatio property changes.
         *
         * @param aspectRatio The new aspect ratio of the @c Control.
         *
         * @since BlackBerry 10.0.0
         */
        void aspectRatioChanged(float aspectRatio);

        /*!
         * @brief Emitted when the @c #fillRatio property changes.
         *
         * @param fillRatio The new fill ratio of the @c Control.
         *
         * @since BlackBerry 10.0.0
         */
        void fillRatioChanged(float fillRatio);

        /*! \cond PRIVATE */
    private:
        Q_DECLARE_PRIVATE(FlowListLayoutProperties)
        Q_DISABLE_COPY(FlowListLayoutProperties)
        /*! \endcond */

    public:
        /*! \cond PRIVATE */
        typedef FlowListLayoutProperties ThisClass;
        typedef LayoutProperties BaseClass;
        /*! \endcond */

        /*!
         * @brief A template builder class for constructing a @c %FlowListLayoutProperties object.
         *
         * To retrieve the builder, call @c FlowListLayoutProperties::create().
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
             * @copydoc bb::cascades::FlowListLayoutProperties::setAspectRatio(float)
             */
            BuilderType& aspectRatio(float _aspectRatio) {
                this->instance().setAspectRatio(_aspectRatio);
                return this->builder();
            }

            /*!
             * @copydoc bb::cascades::FlowListLayoutProperties::setFillRatio(float)
             */
            BuilderType& fillRatio(float _fillRatio) {
                this->instance().setFillRatio(_fillRatio);
                return this->builder();
            }
        };

        /*!
         * @brief A concrete builder class for constructing a @c %FlowListLayoutProperties object.
         *
         * To retrieve the builder, call @c FlowListLayoutProperties::create().
         *
         * @since BlackBerry 10.0.0
         */
        class Builder : public TBuilder<Builder, FlowListLayoutProperties> {
        public:
            Builder(QObject *parent, FlowListLayoutProperties *pInstance = new FlowListLayoutProperties()) : TBuilder<Builder, FlowListLayoutProperties>(pInstance) {
                if (!pInstance->parent())
                {
                    pInstance->setParent(parent);
                }
            }
        };

        /*!
         * @brief Creates and returns a builder for constructing flow list layout properties.
         *
         * Using the builder to create a @c %FlowListLayoutProperties object:
         * @code
         * FlowListLayoutProperties* layoutProperties = FlowListLayoutProperties::create()
         *         .aspectRatio(0.5);
         *         .fillRatio(0.5);
         * @endcode
         *
         * @return A builder used for constructing a @c %FlowListLayoutProperties object.
         *
         * @since BlackBerry 10.0.0
         */
        static Builder create(QObject *parent = 0) {
            return Builder(parent);
        }

        /*!
         * @brief Builds and sets the flow list layout properties for a control.
         *
         * If the control already has a @c %FlowListLayoutProperties set on it, the original
         * layout properties remain as is. Otherwise, a new @c %FlowListLayoutProperties
         * object is created and set as the layout properties for the control.
         *
         * Using the builder to set a control's @c %FlowListLayoutProperties:
         * @code
         * Label *pLabel = Label::create().text("Hello World!");
         * FlowListLayoutProperties::updateFor(pLabel).fillRatio(2.0f);
         * @endcode
         *
         * @param targetControl The control to set the layout properties for.
         *
         * @return A builder used for constructing a @c %FlowListLayoutProperties object.
         *
         * @since BlackBerry 10.0.0
         */
        static Builder updateFor(Control *targetControl);

    }; // FlowListLayoutProperties
} // namespace cascades
} // namespace bb


QML_DECLARE_TYPE(bb::cascades::FlowListLayoutProperties)


#endif	// cascades_flowlayoutproperties_h

