/*
 * Copyright (C) 2014 BlackBerry Limited. All rights reserved.
 */
#ifndef cascades_expandableview_h
#define cascades_expandableview_h

#include <QObject>

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/controls/control.h>
#include <bb/cascades/controls/expandmode.h>
#include <bb/cascades/controls/collapsemode.h>

namespace bb {
    namespace cascades {

    class Container;
    class ExpandableViewPrivate;
   /*!
    *
    * @brief An expandable control that can be used to show a portion of its contents within a fixed height, and expanded to display
    * its entire contents.
    *
    * The @c %ExpandableView control consists of an expandable content area and a button to expand the control. The contents
    * of an @c %ExpandableView can include other controls.
    *
    * When you add a control to an @c %ExpandableView, it is added as the first child in the @c %ExpandableView.
    * If an @c %ExpandableView is removed from the scene, all of its children are removed as well.
    *
    * The size of the @c %ExpandableView behaves as follows:
    * - By default, the width and the height are adjusted automatically to fit the contents of the control
    * - In the collapsed state,
    * -- the width can be adjustable using the @c Control::minWidth and @c Control::maxWidth properties
    * -- the height can be adjustable using the @c ExpandableView::maxCollapsedHeight property.
    * - In the expanded state,
    * -- the width can be adjustable using the @c Control::preferredWidth @c Control::minWidth and @c Control::maxWidth properties
    * -- the height can be adjustable using the @c Control::preferredHeight @c Control::minHeight and @c Control::maxHeight properties
    *
    * Collapse modes:
    * See the documentation for the @c CollapseMode property for further information.
    *
    * Expand modes:
    * See the documentation for the @c ExpandMode property for further information.
    *
    * @xmlonly
    * <apigrouping group="User interface/Core controls"/>
    * @endxmlonly
    *
    * @since BlackBerry 10.3.0
    */
    class BBCASCADES_EXPORT ExpandableView : public Control {
        Q_OBJECT

        /*!
         * @brief The root content for the @c %ExpandableView.
         *
         * The content can be any control. Typically, it is a @c Container with controls, images, and text.
         *
         * @since BlackBerry 10.3.0
         *
         * @xmlonly
         * <qml>
         * <property defaultProperty="yes"/>
         * </qml>
         * @endxmlonly
         */
        Q_PROPERTY(bb::cascades::Control* content READ content WRITE setContent RESET resetContent NOTIFY contentChanged FINAL);

        Q_CLASSINFO("DefaultProperty", "content");

        /*!
         * @brief The maximum collapsed height of the @c %ExpandableView.
         *
         * By default, the @c %maxCollapsedHeight property is not set and the @c %ExpandableView shows the full height of its contents when collapsed.
         *
         * If the @c %maxCollapsedHeight property is set and the height of the contents exceeds the set maximum height, an expand button is displayed
         * which can be tapped to expand the control. If the contents of an @c %ExpandableView are smaller than the set maximum height in the collapsed state,
         * the full contents of the control are shown and the expand button is not displayed.
         */
        Q_PROPERTY(float maxCollapsedHeight READ maxCollapsedHeight WRITE setMaxCollapsedHeight RESET resetMaxCollapsedHeight NOTIFY maxCollapsedHeightChanged FINAL)

        /*!
         * @brief The expanded state.
         *
         * A returned value of @c %true means that the control is expanded, @c %false means that the control is collapsed.
         *
         * The default value of this property is @c %false (collapsed).
         */
         Q_PROPERTY(bool expanded READ isExpanded WRITE setExpanded RESET resetExpanded NOTIFY expandedChanged FINAL)
        /*!
         * The @c %collapseMode of the @c %ExpandableView.
         *
         * Possible values for this property are @c Default, @c None, and @c UserCollapse.
         *
         * - @c %Default mode: Cascades determines the collapse mode based on the content.
         * - @c %None mode: The @c %ExpandableView cannot collapse after expanded.
         * - @c %UserCollapse mode: The @c %ExpandableView can be collapsed by the user tapping the arrow button.
         */
         Q_PROPERTY(bb::cascades::CollapseMode::Type collapseMode READ collapseMode WRITE setCollapseMode RESET resetCollapseMode NOTIFY collapseModeChanged FINAL)

        /*!
         * The @c %expandMode of the @c ExpandableView.
         *
         * Possible values for this property are @c Default, @c AutoExpand, and @c UserExpand.
         *
         * - @c %Default mode: Cascades determines the expand mode based on the content.
         * - @c %AutoExpand mode: The @c %ExpandableView is non-interactable and expands when the user interacts with content (or touches the view).
         * - @c %UserExpand mode: The @c %ExpandableView can be interactable.
         */
         Q_PROPERTY(bb::cascades::ExpandMode::Type expandMode READ expandMode WRITE setExpandMode RESET resetExpandMode NOTIFY expandModeChanged FINAL)

    public:

        explicit ExpandableView(Container* parent = 0);
        virtual ~ExpandableView();

      /*!
         * @brief Gets the active content of this @c %ExpandableView.
         *
         * Ownership will not be transferred.
         *
         * @return The content of this @c %ExpandableView.
         *
         * @since BlackBerry 10.3.0
         */
        bb::cascades::Control* content() const;

        /*!
         * @brief Sets the content of this @c %ExpandableView.
         *
         * Ownership of the content will always be transferred to this @c %ExpandableView.
         * If this @c %ExpandableView already has content, the existing content is still owned by this @c %ExpandableView
         * and is destroyed when this @c %ExpandableView is destroyed.
         *
         * If content is successfully set using this function, the @c contentChanged()
         * signal is emitted.
         *
         * @param content The content to set. You can specify @c 0 to remove content (the existing content
         * is still owned by this @c %ExpandableView).
         *
         * @since BlackBerry 10.3.0
         */
        Q_SLOT void setContent(bb::cascades::Control* content);

        /*!
         * @brief Resets the content of this @c %ExpandableView to a default value of @c NULL.
         *
         * If the content is successfully reset using this function, the @c contentChanged()
         * signal is emitted.
         *
         * @since BlackBerry 10.3.0
         */
        Q_SLOT void resetContent();
        /*!
         * @brief Returns the @c maxCollapsedHeight for the @c %ExpandableView.
         *
         * @since BlackBerry 10.3.0
         */
        float maxCollapsedHeight() const;
        /*!
         * @brief Sets the maximum collapsed height of @c %ExpandableView.
         *
         * @param maxHeight The new maximum collapsed height of @c %ExpandableView.
         *
         * @since BlackBerry 10.3.0
         */
        Q_SLOT void setMaxCollapsedHeight(float maxHeight);
        /*!
         * @brief Resets the max collapsed height of this @c %ExpandableView to a default value
         * of @c no-height.
         *
         * If the collapsed height is successfully reset using this function, the @c maxCollapsedHeightChanged()
         * signal is emitted.
         *
         * @since BlackBerry 10.3.0
         */
        Q_SLOT void resetMaxCollapsedHeight();

        /*!
         * @brief Returns the @c expanded state for the @c ExpandableView.
         *
         * @return @c %true if the @c %ExpandableView is expanded, @c %false if the @c %ExpandableView is collapsed.
         *
         * @since BlackBerry 10.3.0
         */
        bool isExpanded() const;

        /*!
         * @brief Sets the expanded state.
         *
         * If the expanded state is successfully changed using this function, the @c expandedChanged() signal is emitted.
         *
         * @param expanded If @c true, the @c %ExpandableView is expanded; if @c false, the @c %ExpandableView is
         * collapsed.
         *
         * @since BlackBerry 10.3.0
         */
        Q_SLOT void setExpanded(bool expanded);

        /*!
         * @brief Resets the expanded state to @c false (collapsed).
         *
         * If the expanded state is successfully reset using this function, the @c expandedChanged() signal is emitted.
         *
         * @since BlackBerry 10.3.0
         */
        Q_SLOT void resetExpanded();

        /*!
         * @brief Returns the collapse mode for the @c ExpandableView.
         *
         * See the documentation for the @c collapseMode property for further information.
         *
         * @return The collapse mode of @c %ExpandableView, specified using the @c CollapseMode::Type enumeration.
         *
         * @since BlackBerry 10.3.0
         */
        bb::cascades::CollapseMode::Type collapseMode() const;
        /*!
         * @brief Sets the collapse mode of the @c %ExpandableView to the specified mode.
         *
         * In the case of a successful change, the @c collapseModeChanged() signal is emitted.
         *
         * @param newMode The new collapse mode to be set on this @c %ExpandableView.
         *
         * @since BlackBerry 10.3.0
         */
        Q_SLOT void setCollapseMode(bb::cascades::CollapseMode::Type newMode);
        /*!
         * @brief Resets the collapse mode to a default value of @c CollapseMode::Default.
         *
         * If the collapse mode was successfully reset using this function, the @c collapseModeChanged()
         * signal is emitted.
         *
         * @since BlackBerry 10.3.0
         */
        Q_SLOT void resetCollapseMode();
        /*!
         * @brief Returns the expand mode for the @c %ExpandableView.
         *
         * See the documentation for the @c expandMode property for further information.
         *
         * @return The expand mode of @c %ExpandableView, specified using the @c ExpandMode::Type enumeration.
         *
         * @since BlackBerry 10.3.0
         */
        bb::cascades::ExpandMode::Type expandMode() const;
        /*!
         * @brief Sets the expand mode of the @c %ExpandableView to the specified mode.
         *
         * In the case of a successful change, the @c expandModeChanged() signal is emitted.
         *
         * @param newMode The new expand mode to be set on this @c %ExpandableView.
         *
         * @since BlackBerry 10.3.0
         */
        Q_SLOT void setExpandMode(bb::cascades::ExpandMode::Type newMode);
        /*!
         * @brief Resets the expand mode to a default value of @c ExpandMode::Default.
         *
         * If the expand mode is successfully reset using this function, the @c expandModeChanged()
         * signal is emitted.
         *
         * @since BlackBerry 10.3.0
         */
        Q_SLOT void resetExpandMode();


    Q_SIGNALS:
        /*!
         * @brief Emitted when the content of this @c %ExpandableView is changed.
         *
         * @param content The new content of this @c %ExpandableView.
         *
         * @since BlackBerry 10.3.0
         */
        void contentChanged(bb::cascades::Control* content);
        /*!
         * @brief Emitted when the @c %maxCollapsedHeight of this @c %ExpandableView is changed.
         *
         * @param maxCollapsedHeight The new maximum collapsed height of this @c %ExpandableView.
         *
         * @since BlackBerry 10.3.0
         */
        void maxCollapsedHeightChanged(float maxCollapsedHeight);
        /*!
         * @brief Emitted when the expanded state of this @c %ExpandableView is changed.
         *
         * @param expanded  If @c true the control is expanded; if @c false, the control is collapsed.
         *
         * @since BlackBerry 10.3.0
         */
        void expandedChanged(bool expanded);
        /*!
         * @brief Emitted when the @c %expandMode of this @c %ExpandableView is changed.
         *
         * @param newExpandMode The new expand mode.
         *
         * @since BlackBerry 10.3.0
         */
        void expandModeChanged(bb::cascades::ExpandMode::Type newExpandMode);
        /*!
         * @brief Emitted when the @c %collapseMode of this @c %ExpandableView is changed.
         *
         * @param newCollapseMode The new collapse mode.
         *
         * @since BlackBerry 10.3.0
         */
        void collapseModeChanged(bb::cascades::CollapseMode::Type newCollapseMode);
    private:
        Q_DECLARE_PRIVATE(ExpandableView)
        Q_DISABLE_COPY(ExpandableView)

    public:
        /*! @cond PRIVATE */
        typedef ExpandableView ThisClass;
        typedef Control BaseClass;
        /*! @endcond */


        /*!
         * @brief A builder template for constructing an @c %ExpandableView.
         *
         * See @c ExpandableView::create() for getting a concrete @c Builder for constructing an @c %ExpandableView.
         *
         * @since BlackBerry 10.3.0
         */
        template <typename BuilderType, typename BuiltType>
        class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType> {
        protected:
            TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node) {}
        public:

            /*!
             * @copydoc bb::cascades::ExpandableView::setContent(bb::cascades::Control*)
             */
            BuilderType& content(bb::cascades::Control* content) {
                this->instance().setContent(content);
                return this->builder();
            }
            /*!
             * @copydoc bb::cascades::ExpandableView::setMaxCollapsedHeight(float maxHeight)
             */
            BuilderType& maxCollapsedHeight(float maxHeight)
            {
                this->instance().setMaxCollapsedHeight(maxHeight);
                return this->builder();
            }
            /*!
             * @copydoc bb::cascades::ExpandableView::setExpanded(bool expanded)
             */
            BuilderType& expanded(bool expanded)
            {
                this->instance().setExpanded(expanded);
                return this->builder();
            }
            /*!
             * @copydoc bb::cascades::ExpandableView::setExpandMode(bb::cascades::ExpandMode::Type newMode)
             */
            BuilderType& expandMode(bb::cascades::ExpandMode::Type newMode)
            {
                this->instance().setExpandMode(newMode);
                return this->builder();
            }
            /*!
             * @copydoc bb::cascades::ExpandableView::setCollapseMode(bb::cascades::CollapseMode::Type newMode)
             */
            BuilderType& collapseMode(bb::cascades::CollapseMode::Type newMode)
            {
                this->instance().setCollapseMode(newMode);
                return this->builder();
            }
        };

        /*!
         * @brief A concrete builder class for constructing an @c %ExpandableView.
         *
         * See @c ExpandableView::create() for getting a concrete @c Builder for constructing an @c %ExpandableView.
         *
         * @since BlackBerry 10.3.0
         */
        class Builder : public TBuilder<Builder, ExpandableView> {
        public:
            explicit Builder() : TBuilder<Builder, ExpandableView>(new ExpandableView()) {}
        };

        /*!
         * @brief Creates and returns a @c Builder for constructing an @c %ExpandableView.
         *
         * @return A @c %Builder for constructing an @c %ExpandableView.
         *
         * @since BlackBerry 10.3.0
         */
        static Builder create() {
            return Builder();
        }
    };

} // namespace cascades
} // namespace bb

QML_DECLARE_TYPE(bb::cascades::ExpandableView)

#endif // cascades_expandableview_h
