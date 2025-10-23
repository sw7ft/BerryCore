/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_sheet_h
#define cascades_sheet_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/controls/abstractdialog.h>

namespace bb {
    namespace cascades {

    class AbstractPane;
    class SheetPrivate;

   /*!
    *
    * @brief A class that represents a full-screen view as a layer.
    *
    * @image html cascades_navigation_sheet.png An image showing a sheet moving into view
    * 
    * Sheets are full-screen views that are placed as separate layers on top of
    * the current screen context. A sheet displays a view from within the current
    * application.
    *
    * Sheets are primarily used to display a UI that's related to the creation or
    * selection of content, often as temporary subtasks to the main navigation of
    * the application. You can think of a sheet as representing a separate flow, or
    * detour, from the main application flow.
    * 
    * Some examples of where you might use sheets include composing an email,
    * creating a new contact, creating a meeting, or selecting content by using
    * a picker.
    *
    * A sheet includes a set of buttons at the top, which represent actions that
    * are specific to that sheet. For example, a sheet for composing an email might
    * include actions such as Cancel and Send. In general, a sheet should contain a
    * cancel or back action in the upper-left corner, and a positive action (such as
    * Send, Confirm, or OK) in the upper-right corner.
    *
    * A sheet always occupies the entire screen when it is displayed, and can contain
    * @c NavigationPane, @c TabbedPane, or @c Page components. A sheet can also include
    * actions that appear on the action bar at the bottom of the sheet. An opened sheet
    * will always be placed on top of the current screen context and will cover any
    * previously opened sheets.
    *
    * You can attach a sheet to any @c UIObject by using the @c attachedObjects property.
    *
    * Defining a Sheet in C++:
    * @code
    * Sheet* pMySheet = Sheet::create()
    *                   .content(Page::create())
    *                   .onClosed(this, SLOT(onClosedHandler())
    *                   .open();
    * @endcode
    *
    * Defining a Sheet in QML:
    * @code
    *  Page {
    *      attachedObjects: [
    *          Sheet {
    *              id: mySheet
    *              content: Page {
    *                  Button {
    *                      text: "Close Sheet"
    *                      onClicked: mySheet.close()
    *                  }
    *              }
    *          }
    *      ]
    *      actions: [
    *          ActionItem {
    *              title: "Show Sheet"
    *              ActionBar.placement: ActionBarPlacement.OnBar
    *              onTriggered: {
    *                 mySheet.open();
    *              }
    *          }
    *      ]
    *  }
    * @endcode
    *
    * @xmlonly
    * <qml>
    * <class register="yes"/>
    * </qml>
    * @endxmlonly
    *
    * @xmlonly
    * <apigrouping group="User interface/Application structure"/>
    * @endxmlonly
    *
    * @since BlackBerry 10.0.0
    */
    class BBCASCADES_EXPORT Sheet : public AbstractDialog {
    private:
        Q_OBJECT

       /*!
        * @brief The root control for this @c %Sheet.
        *
        * This property specifies the control that appears as the root control and is
        * displayed on this @c %Sheet. It's often a good idea to use a @c Page as the
        * root control, and add other controls to the @c %Page.
        * 
        * This property is the default property of the @c %Sheet control, so it does not need
        * to be explicitly declared in the QML. A control added inside the @c %Sheet will
        * automatically be assigned to the @c content property.
        *
        * @code
        * Page {
        *     attachedObjects: [
        *         Sheet {
        *             Page {
        *                 Container {
        *                     Button {}
        *                     Button {}
        *                 }
        *             }
        *         }
        *     ]
        * }
        * @endcode
        *
        * The code sample above is equal to the following code sample:
        *
        * @code
        * Page {
        *     attachedObjects: [
        *         Sheet {
        *             content: Page {
        *                 Container {
        *                     Button {}
        *                     Button {}
        *                 }
        *             }
        *         }
        *     ]
        * }
        * @endcode
        *
        * @xmlonly
        * <qml>
        * <property defaultProperty="yes"/>
        * </qml>
        * @endxmlonly
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(bb::cascades::AbstractPane* content READ content WRITE setContent NOTIFY contentChanged RESET resetContent FINAL)
        Q_CLASSINFO("DefaultProperty", "content")

       /*!
        * @brief Indicates whether peeking should be enabled in this @c %Sheet.
        *
        * This property specifies whether dragging and swiping to the right inside the current
        * @c %Sheet should peek. The default value is @c true (enabled). If enabled, the drag and
        * swipe gestures will allow peeking in the @c %Sheet.
        *
        * When enabled, dragging or swiping to the right inside the @c %Sheet will reveal the content
        * directly underneath the @c %Sheet.
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(bool peekEnabled READ isPeekEnabled WRITE setPeekEnabled NOTIFY peekEnabledChanged RESET resetPeekEnabled FINAL)

    public:
       /*!
        * @brief Construct a Sheet instance
        *
        * @since BlackBerry 10.0.0
        */
        explicit Sheet(UIObject *parent = 0);
        virtual ~Sheet();

       /*!
        * @brief Sets the content of this @c %Sheet.
        * 
        * Ownership of the content will always be transferred to this @c %Sheet.        
        * If this @c %Sheet already has content, the old content is still owned by this @c %Sheet
        * and will be destroyed when this @c %Sheet is destroyed.
        * 
        * If content was successfully set using this function, the @c contentChanged()
        * signal is emitted.
        *
        * @param content The content to set. Can be @c 0 to remove content (old content
        * will still be owned by this @c %Sheet).
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void setContent(bb::cascades::AbstractPane* content);

       /*!
        * @brief Gets the active content of this @c %Sheet.
        * 
        * Ownership will not be transferred.
        *
        * @return The content of this @c %Sheet.
        *
        * @since BlackBerry 10.0.0
        */
        bb::cascades::AbstractPane* content() const;

       /*!
        * @brief Resets the content for this @c %Sheet.
        * 
        * This function resets the content for this @c %Sheet.
        * Content will be removed and content property set to 0.
        * This is equivalent to setContent(0).
        *
        * When this function completes, the @c contentChanged() signal is emitted.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void resetContent();

       /*!
        * @brief Sets whether peeking from within the current @c %Sheet should be enabled.
        *
        * If successfully set using this function, the @c peekedEnabledChanged() signal is emitted.
        *
        * @param enabled If @c true peeking is enabled, if @c false peeking is disabled.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void setPeekEnabled(bool enabled);

       /*!
        * @brief Resets the peeking behavior of the @c %Sheet to its default state, which is disabled.
        *
        * @since BlackBerry 10.0.0
        */
        Q_SLOT void resetPeekEnabled();

       /*!
        * @brief Indicates whether peeking from within the current %Sheet should be enabled.
        *
        * @return @c true if peeking is enabled, @c false otherwise.
        *
        * @since BlackBerry 10.0.0
        */
        bool isPeekEnabled() const;

    Q_SIGNALS:

       /*!
        * @brief Emitted when the content of this @c %Sheet has changed.
        *
        * @param content The new content of this @c %Sheet.
        *
        * @since BlackBerry 10.0.0
        */
        void contentChanged(bb::cascades::AbstractPane* content);

       /*!
        * @brief Emitted when peeking on the @c %Sheet is enabled or disabled.
        *
        * @param enabled If @c true peeking is enabled, if @c false peeking is disabled.
        *
        * @since BlackBerry 10.0.0
        */
        void peekEnabledChanged(bool enabled);

    private:
        /*! \cond PRIVATE */
        Q_DECLARE_PRIVATE(Sheet)
        Q_DISABLE_COPY(Sheet)

        typedef Sheet ThisClass;
        typedef AbstractDialog BaseClass;
        /*! \endcond */

    public:
       /*!
        * @brief A builder template for constructing a @c %Sheet.
        *
        * To retrieve the builder, call @c Sheet::create().
        *
        * @since BlackBerry 10.0.0
        */
        template <typename BuilderType, typename BuiltType>
        class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType>
        {
        protected:
            TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node)
            {
            }
        public:

           /*!
            * @brief Sets the content for the @c %Sheet.
            *
            * Using this convenience function in the builder pattern is equivalent to the following:
            * @code
            * mySheet->setContent(content);
            * @endcode
            *
            * @param content The content for the @c %Sheet.
            *
            * @since BlackBerry 10.0.0
            */
            BuilderType& content(AbstractPane *content)
            {
                this->instance().setContent(content);
                return this->builder();
            }

           /*!
            * @brief Sets the peeking behavior of this @c %Sheet.
            *
            * Using this convenience function in the builder pattern is equivalent to the following:
            * @code
            * mySheet->setPeekEnabled(false);
            * @endcode
            *
            * @param enabled If @c true peeking is enabled, if @c false peeking is disabled.
            *
            * @since BlackBerry 10.0.0
            */
            BuilderType& peek(bool enabled) {
                this->instance().setPeekEnabled(enabled);
                return this->builder();
            }
        };

       /*!
        * @brief A builder that constructs a @c %Sheet.
        *
        * To retrieve the builder, call @c Sheet::create().
        *
        * @since BlackBerry 10.0.0
        */
        class Builder : public TBuilder<Builder, Sheet>
        {
        public:
            explicit Builder() : TBuilder<Builder, Sheet>(new Sheet())
            {
            }
        };

       /*!
        * @brief Creates and returns a builder for constructing a @c %Sheet.
        *
        * Using the builder to create a @c %Sheet:
        * @code
        * Sheet* mySheet = Sheet::create();
        * @endcode
        *
        * @return A Builder used for constructing a @c %Sheet.
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

QML_DECLARE_TYPE(bb::cascades::Sheet)

#endif
