/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_tab_h
#define cascades_tab_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/resources/abstractactionitem.h>
#include <bb/cascades/resources/image.h>

namespace bb {
    namespace cascades {

      class TabPrivate;
      class AbstractPane;
      class TabbedPane;

     /*!
      *
      * @brief A tab that can be added to a @c TabbedPane.
      * 
      * The @c %Tab objects in the @c %TabbedPane are added to the Action bar, which is a 
      * horizontal bar displayed at the bottom of the screen. By pressing the tabs on the Action bar 
      * the user can switch the content that is currently being displayed on the screen. The @c %Tab objects take an 
      * @c %AbstractPane as their @c %content. If the content is not @c 0, it will be 
      * displayed in the @c %TabbedPane when the corresponding tab is selected.
      *
      * Even though a @c %Tab takes @c %AbstractPane as its @c %content, not all classes deriving 
      * from @c %AbstractPane are valid as the @c %content. The valid classes are @c Page and
      * @c NavigationPane.
      *
      * QML example:
      *
      * @code
      * TabbedPane {
      *     Tab {
      *         title : "tab1"
      *         description : "This is only shown in the side bar"
      *         imageSource : "tab.png"
      *         Page {}
      *     }
      * }
      *
      * @endcode
      * 
      * C++ example:
      *
      * @code
      * TabbedPane* tabbedPane = TabbedPane::create();
      * Page* page = Page::create();
      * Tab* tab = Tab::create()
      *              .title("tab1")
      *              .description("This is only shown in the side bar")
      *              .image(Image("tab.png"));
      * tab->setContent(page);
      * tabbedPane->add(tab);
      * @endcode
      *
      * As of 10.3, the default behavior for tab images is to adopt the colors of the current theme.
      * To allow your images to adapt to changes in the theme, the image asset should be a grayscale image (preferably white)
      * with the alpha channel set. You can turn off this behavior by using the type "normal" in the image's .amd file.
      *
      * These images show the behavior of actionitem icon colorization.
      * -The "Dashboard" tab is using the white default icon and adopts to theme, but the tab is selected and therefore colored with the system primary color (blue)
      * -The "Controls" tab is using the white default icon and adopts to theme.
      * -The "More controls" tab is using a colored icon where the .amd @c type property is set to @c normal and left uncolorized by the system.
      * @image html actionitem_colorization_dark.png
      * @image html actionitem_colorization_bright.png
      *
      * These are the assets used (without dropshadows):
      * @image html actionitem_default_icon.png
      * @image html actionitem_colored_icon.png
      *
      * @see Image (Image colorization)
      *
      * @xmlonly
      * <qml>
      * <class register="yes" abstract="yes"/>
      * </qml>
      * @endxmlonly
      *
      * @xmlonly
      * <apigrouping group="User interface/Application structure"/>
      * @endxmlonly
      *
      * @since BlackBerry 10.0.0
      */
      class BBCASCADES_EXPORT Tab : public AbstractActionItem
      {
          Q_OBJECT
        
         /*!
          * @brief The description text to be displayed for tabs placed in the side bar of a @c TabbedPane.
          *
          * The description text displayed for tabs placed in the side bar. The description is
          * not shown for tabs placed on the Action bar.
          * The default value is @c QString::Null, indicating that no description is set.
          *
          * @since BlackBerry 10.0.0
          */
          Q_PROPERTY(QString description READ description WRITE setDescription RESET resetDescription NOTIFY descriptionChanged FINAL)

         /*!
          * @brief The content to show when the tab is activated.
          *
          * The content to display in the @c %TabbedPane when this @c %Tab becomes active. Valid content 
          * is @c NavigationPane and @c Page. If @c 0 the content displayed in the @c %TabbedPane will
          * remain unchanged. The default value is @c 0.
          *
          * This is the default property of the tab, so it does not need to be explicitly 
          * declared in the QML. 
          *
          * @code
          * Tab {
          *     Page {
          *         Container {}
          *     }
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
          Q_PROPERTY(bb::cascades::AbstractPane* content READ content WRITE setContent NOTIFY contentChanged FINAL)
          Q_CLASSINFO("DefaultProperty", "content") 

         /*!
          * @brief A visual notification to show on the tab if there is new content.
          *
          * The default value is @c false, indicating that there is no new content.
          *
          * @since BlackBerry 10.0.0
          */
          Q_PROPERTY(bool newContentAvailable READ isNewContentAvailable 
                    WRITE setNewContentAvailable RESET resetNewContentAvailable
                    NOTIFY newContentAvailableChanged FINAL)
       
         /*!
          * @brief The unread content count to show on the %Tab in the Side bar.
          *
          * If value is between @c  1 and @c 9999, the number is displayed on the tab 
          * in the Side bar. If the value is 10000 or greater the text "9999+"
          * is showing. If the value is @c 0 or less the number is not displayed.
          *
          * The default value is @c 0.
          *
          * @since BlackBerry 10.0.0
          */
          Q_PROPERTY(int unreadContentCount READ unreadContentCount 
                    WRITE setUnreadContentCount RESET resetUnreadContentCount
                    NOTIFY unreadContentCountChanged FINAL)
      public:

         /*!
          * @brief Constructs a new @c %Tab object and adds it to an optional @c %TabbedPane.
          *
          * The ownership of the tab is transferred to the parent if a parent is specified.
          *
          * @param parent The @c %TabbedPane to add this tab to. This parameter is optional.
          *
          * @since BlackBerry 10.0.0
          */
          explicit Tab(TabbedPane * parent = 0);
        
         /*!
          * @brief Destructs this @c %Tab.
          *
          * @since BlackBerry 10.0.0
          */
          virtual ~Tab();

         /*!
          * @brief Sets the description text of this @c %Tab.
          *
          * The description text displayed for tabs placed in the side bar. The description is
          * not shown for tabs placed on the Action bar.
          *
          * @param description The description of this %Tab.
          *
          * @since BlackBerry 10.0.0
          */
          Q_SLOT void setDescription(const QString& description);

         /*!
          * @brief Resets the description text of this @c %Tab to @c QString::Null.
          *
          * @since BlackBerry 10.0.0
          */
          Q_SLOT void resetDescription();

         /*!
          * @brief Gets the description text of this @c %Tab.
          *
          * @return The description text of this @c %Tab.
          *
          * @since BlackBerry 10.0.0
          */
          QString description() const;


         /*!
          * @brief Gets the content of this @c %Tab.
          * 
          * Ownership will not be transferred.
          *
          * @return The content of this @c %Tab.
          *
          * @since BlackBerry 10.0.0
          */
          bb::cascades::AbstractPane* content() const;

         /*!
          * @brief Sets the content of this @c %Tab.
          * 
          * Ownership of the content will always be transferred to this @c %Tab.
          * If this @c %Tab already has content, the old content is still owned by this @c %Tab
          * and will be destroyed when this @c %Tab is destroyed.
          * 
          * If content was successfully set using this function, the @c contentChanged()
          * signal is emitted.
          *
          * @param content The content to set. Can be @c 0 to remove content (old content
          * will still be owned by this @c %Tab).
          *
          * @since BlackBerry 10.0.0
          */
          Q_SLOT void setContent(bb::cascades::AbstractPane* content);

         /*!
          * @brief Resets the content for this @c %Tab.
          * 
          * This function resets the content for this @c %Tab.
          * Content will be removed and content property set to @c 0.
          * This is equivalent to calling @c setContent(0).
          * When this function completes, the @c contentChanged() signal is emitted.
          *
          * @since BlackBerry 10.0.0
          */
          Q_SLOT void resetContent();


          /*!
          * @brief Sets the newContentAvailable flag of this %Tab.
          *
          * The @c newContentAvailable indicator is shown on the top right corner of the @c %Tab icon.
          * It will show on the @c %Tab in the sidebar and on the Action bar if the @c %Tab is 
          * forced to the @c Action bar.
          *
          * @param isNewContentAvailable The flag to tell if there is new content or not.
           *
           * @since BlackBerry 10.0.0
          */
          Q_SLOT void setNewContentAvailable(bool isNewContentAvailable);

         /*!
          * @brief Resets the flag to @c false, which means no new content in the tab.
          *
          * @since BlackBerry 10.0.0
          */
          Q_SLOT void resetNewContentAvailable();

         /*!
          * @brief Gets the @c newContentAvailable flag of this @c %Tab.
          *
          * @return The @c newContentAvailable flag of this @c %Tab.
          *
          * @since BlackBerry 10.0.0
          */
          bool isNewContentAvailable() const;

          /*!
          * @brief Sets the unread content count to show on the %Tab.
          *
          * If value is between @c  1 and @c 9999, that number is displayed on the tab 
          * in the Side bar. If the value is 10000 or greater the text "9999+"
          * is shown. If the value is @c 0 or less the number is not displayed.
          *
          * @param unreadContentCount The number to show on the tab. 
           *
           * @since BlackBerry 10.0.0
          */
          Q_SLOT void setUnreadContentCount(int unreadContentCount);

         /*!
          * @brief Hides the unread content count by resetting it to @c 0.
          *
          * @since BlackBerry 10.0.0
          */
          Q_SLOT void resetUnreadContentCount();

         /*!
          * @brief Gets the unread content count shown on the @c %Tab.
          *
          * @return The unread content count shown on the @c %Tab. @c 0 if no content count is shown.
          *
          * @since BlackBerry 10.0.0
          */
          int unreadContentCount() const;

Q_SIGNALS:

         /*!
          * @brief Emitted when the description of this @c %Tab changes.
          *
          * @param description The new description.
          *
          * @since BlackBerry 10.0.0
          */
          void descriptionChanged(QString description);

         /*!
          * @brief Emitted when the content of this @c %Tab has changed.
          *
          * @param content The new content of this @c %Tab.
          *
          * @since BlackBerry 10.0.0
          */
          void contentChanged(bb::cascades::AbstractPane* content);

         /*!
          * @brief Emitted when the @c newContentAvailable flag of this @c %Tab changes.
          *
          * @param isNewContentAvailable The new value of the @c newContentAvailable flag.
          *
          * @since BlackBerry 10.0.0
          */
          void newContentAvailableChanged(bool isNewContentAvailable);

         /*!
          * @brief Emitted when the @c newContentCount value of this @c %Tab changes.
          *
          * @param unreadContentCount The new value of the @c unreadContentCount flag.
          *
          * @since BlackBerry 10.0.0
          */
          void unreadContentCountChanged(int unreadContentCount);

      protected:
          /*! @cond PRIVATE */
          Tab(TabPrivate &_d_ptr, TabbedPane *parent = 0);
          /*! @endcond */

      private:
        /*! @cond PRIVATE */
          Q_DECLARE_PRIVATE(Tab)
          Q_DISABLE_COPY(Tab)
          /*! @endcond */

      public:
          /*! @cond PRIVATE */
          typedef Tab ThisClass;
          typedef AbstractActionItem BaseClass;
          /*! @endcond */

          /*!
           * @brief A builder template for constructing a @c %Tab object.
           * 
           * To retrieve the builder, call @c Tab::create().
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
              * @brief Sets the description for this @c %Tab.
              *
              * @param title The description of this @c %Tab.
              *
              * @since BlackBerry 10.0.0
              */
              BuilderType& description(const QString &title) {
                  this->instance().setDescription(title);
                  return this->builder();
              }

             /*!
              * @brief Sets the content for the @c %Tab.
              *
              * Using this convenience function in the builder pattern is equivalent to the following:
              * @code
              * myTab->setContent(content);
              * @endcode
              *
              * @param content The content for the @c %Tab.
              *
              * @since BlackBerry 10.0.0
              */
              BuilderType& content(AbstractPane *content)
              {
                  this->instance().setContent(content);
                  return this->builder();
              }


              /*!
              * @brief Sets the @c newContentAvailable flag on this @c %Tab.
              *
              * @param isNewContentAvailable The value of the @c newContentAvailable flag.
              *
              * @since BlackBerry 10.0.0
              */
              BuilderType& newContent(bool isNewContentAvailable) {
                  this->instance().setNewContentAvailable(isNewContentAvailable);
                  return this->builder();
              }

              /*!
              * @brief Sets the unread content count to show on the %Tab.
              *
              * If value is between @c  1 and @c 9999, the number is displayed on the tab 
              * in the Side bar. If the value is 10000 or greater the text "9999+"
              * is showing. If the value is @c 0 or less the number is not displayed.
              *
              * @param unreadContentCount The number to show on the tab.
              *
              * @since BlackBerry 10.0.0
              */
              BuilderType& unreadContent(int unreadContentCount) {
                this->instance().setUnreadContentCount(unreadContentCount);
                return this->builder();
              }

          };

         /*!        
          * @brief A builder for constructing a @c %Tab object.
          * 
          * To retrieve the builder, call @c Tab::create().
          *
          * @since BlackBerry 10.0.0
          */
          class Builder : public TBuilder<Builder, Tab>
          {
          public:
              explicit Builder() : TBuilder<Builder, Tab>(new Tab()) {}
          };

          /*!
          * @brief Creates and returns a builder for constructing a @c %Tab object.
          *
          * Using the builder to create a @c %Tab object.
          * 
          * Example:
          * @code
          * Tab::create()
          *     .title("tab1")
          *     .subtitle("This is only shown in the overflow menu")
          *     .image(Image("tab.png"));
          *     .content(Page::create());
          * @endcode
          *
          * @return A builder used for constructing a @c %Tab object.
           *
           * @since BlackBerry 10.0.0
          */
          static Builder create() {
              return Builder();
          }
      };
    }

}

#endif 
