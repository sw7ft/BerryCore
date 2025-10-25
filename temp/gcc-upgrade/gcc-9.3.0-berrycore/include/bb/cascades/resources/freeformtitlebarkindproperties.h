/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_freeformtitlebarkindproperties_h
#define cascades_freeformtitlebarkindproperties_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/resources/abstracttitlebarkindproperties.h>
#include <bb/cascades/resources/titlebarexpandableareaindicatorvisibility.h>
#include <bb/cascades/resources/titlebarexpandableareatogglearea.h>
namespace bb {
    namespace cascades {

    class FreeFormTitleBarKindPropertiesPrivate;
    class Control;
    class TitleBarExpandableArea;

    /*!
     * 
     * @brief A class that groups properties associated with the @c FreeForm type of @c TitleBar.
     * 
     * @c FreeFormTitleBarKindProperties has two properties that determine the visual components for
     * of a free-form @c TitleBar. The default property @c #content contains the content displayed
     * directly on the title bar. The group property @c #expandableArea
     * contains content that can be expanded and collapsed by tapping the title bar.
     *
     * @see @c TitleBar::kindProperties, @c TitleBar::kind 
     * 
     * @xmlonly
     * <apigrouping group="User interface/Application structure"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.1.0
     */
    class BBCASCADES_EXPORT FreeFormTitleBarKindProperties : public AbstractTitleBarKindProperties
    {
        Q_OBJECT

       /*!
        * @brief The content of the @c TitleBar if the @c kind property is @c FreeForm.
        *
        * If the @c TitleBar::kind property is @c FreeForm, the title bar
        * uses the @c Control specified by @c freeFormContent as its content.
        *
        * @since BlackBerry 10.1.0
        *
        * @xmlonly
        * <qml>
        * <property defaultProperty="yes"/>
        * </qml>
        * @endxmlonly
        */
        Q_PROPERTY(bb::cascades::Control* content READ content WRITE setContent RESET resetContent NOTIFY contentChanged FINAL)

       /*!
        * @brief A group property for properties associated with the expandable area.
        *
        * If the @c TitleBar::kind property is @c FreeForm, the title bar will use the
        * properties from @c expandableArea to create a drop-down like title bar.
        *
        * @code
        * TitleBar {
        *     kind: TitleBarKind.FreeForm
        *     kindProperties: FreeFormTitleBarKindProperties {
        *         Container {
        *             layout: StackLayout { orientation: LayoutOrientation.LeftToRight }
        *             leftPadding: 10
        *             Label {
        *                 text: "Tap the indicator to expand and collapse"
        *                 textStyle {
        *                     color: Color.White
        *                 }
        *                 verticalAlignment: VerticalAlignment.Center
        *             }
        *         }
        *         expandableArea {
        *             content: Label {
        *                 text: "This is the expandable area"
        *             }
        *             expanded: true
        *             toggleArea: TitleBarExpandableAreaToggleArea.IndicatorOnly
        *         }
        *     }
        * }
        * @endcode
        *
        * @see TitleBarExpandableArea
        *
        * @since BlackBerry 10.1.0
        *
        * @xmlonly
        * <qml>
        * <property groupedProperty="yes"/>
        * </qml>
        * @endxmlonly
        */
        Q_PROPERTY(bb::cascades::TitleBarExpandableArea* expandableArea READ expandableArea FINAL)

        Q_CLASSINFO("DefaultProperty", "content")
    public:

       /*!
        * @brief Constructs a @c %FreeFormTitleBarKindProperties.   
        *
        * @since BlackBerry 10.1.0        
        */
        explicit FreeFormTitleBarKindProperties();
        
       /*!
        * @brief Destroys this @c %FreeFormTitleBarKindProperties.
        *
        * @since BlackBerry 10.1.0
        */
        virtual ~FreeFormTitleBarKindProperties();

       /*!
        * @brief Returns the free-form content of the @c TitleBar.
        *
        * @return The free-form content of the @c TitleBar.
        *
        * @since BlackBerry 10.1.0
        */
        bb::cascades::Control* content() const;

       /*!
        * @brief Sets the free-form content of the @c TitleBar.
        *
        * Ownership will always be transferred to the @c %FreeFormTitleBarKindProperties.
        * If @c %FreeFormTitleBarKindProperties already has @c content, the old @c content is still
        * owned by @c %FreeFormTitleBarKindProperties and destroyed when @c %FreeFormTitleBarKindProperties
        * is destroyed.
        *
        * @param content The free-form content of the @c TitleBar.
        *
        * @since BlackBerry 10.1.0
        */
        Q_SLOT void setContent(bb::cascades::Control* content);

       /*!
        * @brief Resets the free-form content of the @c TitleBar to @c 0.
        *
        * @since BlackBerry 10.1.0
        */
        Q_SLOT void resetContent();

       /*!
        * @brief Returns the @c expandableArea of the @c TitleBar.
        *
        * @return The expandable area of the @c TitleBar.
        *
        * @since BlackBerry 10.1.0
        */
        bb::cascades::TitleBarExpandableArea* expandableArea() const;

Q_SIGNALS:

       /*!
        * @brief Emitted when the free-form content of the @c TitleBar changes.
        *
        * @param newContent The new free-form content.
        *
        * @since BlackBerry 10.1.0
        */
        void contentChanged(bb::cascades::Control* newContent);

    private:
        
        /*! \cond PRIVATE */
        Q_DECLARE_PRIVATE(FreeFormTitleBarKindProperties)
        Q_DISABLE_COPY(FreeFormTitleBarKindProperties)

    public:
        typedef FreeFormTitleBarKindProperties ThisClass;
        typedef AbstractTitleBarKindProperties BaseClass;
        /*! @endcond */
        
       /*!         
        * @brief A template builder class for constructing a @c %FreeFormTitleBarKindProperties object.
        * 
        * To retrieve the builder, call @c FreeFormTitleBarKindProperties::create().
        *
        * @since BlackBerry 10.1.0
        */
        template <typename BuilderType, typename BuiltType>
        class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType> {
        protected:
            TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node) {
            }

        public:

           /*!
            * @brief Sets the back button for this @c %FreeFormTitleBarKindProperties.
            *  
            * If set to @c 0, the default back button is used.
            *
            * Using this convenience function in the builder pattern is equivalent to the
            * following:
            * 
            * @code
            * myFreeFormProperties->setContent(myTitleBarContent);
            *  @endcode
            * 
            * When this function completes, the @c contentChanged() signal is emitted.
            * 
            * @param content The content to be displayed.
            *
            * @since BlackBerry 10.1.0
            */
            BuilderType& content(Control* content) {
                this->instance().setContent(content);
                return this->builder();
            }

           /*!
            * @brief The content of the expandable area of the @c TitleBar.
            *
            * If the @c expandableArea expanded property is @c true the control specified by content will be shown.
            * @param content The free form content of the @c TitleBar.
            *
            * @since BlackBerry 10.1.0
            */
            BuilderType& expandableContent(Control* content) {
                this->instance().expandableArea()->setContent(content);
                return this->builder();
            }

           /*!
            * @brief The state of the expandable area of the title bar. True means that the expandable area is shown, false means that the expandable area
            * is hidden.
            *
            * The default value of this property is false, i.e. the expandable area is hidden.
            * @param expanded The new state to set: true means expanded, false means collapsed.
            *
            * @since BlackBerry 10.1.0
            */
            BuilderType& expanded(bool expanded) {
                this->instance().expandableArea()->setExpanded(expanded);
                return this->builder();
            }

           /*!
            * @brief The visibility of the expandable indicator. The indicator hints that the title bar can be expanded. 
            *
            * The default value of this property is Default, i.e. the indicator is visible if content is set on @c expandableArea.
            * @param visibility The visibility of the expandable indicator.
            *
            * @since BlackBerry 10.1.0
            */
            BuilderType& expandableIndicator(TitleBarExpandableAreaIndicatorVisibility::Type visibility) {
                this->instance().expandableArea()->setIndicatorVisibility(visibility);
                return this->builder();
            }

           /*!
            * @brief The toggle area for expanding and collapsing the expandable area.
            *
            * The toggle area is only active if the expandable indicator is visible.
            *
            * The default value of this property is Default, i.e. if content is set on @c expandableArea the entire title bar will
            * be used for toggling the expandable area.
            * @param area The toggle area for expanding and collapsing the expandable area.
            *
            * @since BlackBerry 10.1.0
            */
            BuilderType& expandableAreaToggleArea(TitleBarExpandableAreaToggleArea::Type area) {
                this->instance().expandableArea()->setToggleArea(area);
                return this->builder();
            }
        };

       /*!        
        * @brief A builder class for constructing a @c %FreeFormTitleBarKindProperties object.
        * 
        * To retrieve the builder, call @c FreeFormTitleBarKindProperties::create().
        *
        * @since BlackBerry 10.1.0
        */
        class Builder : public TBuilder<Builder, FreeFormTitleBarKindProperties>
        {
        public:
            explicit Builder() : TBuilder<Builder, FreeFormTitleBarKindProperties>(new FreeFormTitleBarKindProperties()) {}
        };

        /*!
        * @brief Creates and returns a builder for constructing a @c %FreeFormTitleBarKindProperties object.
        *
        * Using the builder to create a @c %FreeFormTitleBarKindProperties object.
        * 
        * @code
        * FreeFormTitleBarKindProperties* myFreeFormProperties = FreeFormTitleBarKindProperties::create()
        *                                               .content(myTitleBarContent);
        * @endcode
        *
        * @return A builder used for constructing a @c %FreeFormTitleBarKindProperties object.
        *
        * @since BlackBerry 10.1.0
        */
        static Builder create() {
            return Builder();
        }
    };
    }

}

QML_DECLARE_TYPE(bb::cascades::FreeFormTitleBarKindProperties)

#endif //cascades_freeformtitlebarkindproperties_h
