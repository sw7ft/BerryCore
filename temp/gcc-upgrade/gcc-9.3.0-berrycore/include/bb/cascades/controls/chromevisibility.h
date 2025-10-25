/* Copyright (C) 2012-2013 Research In Motion Limited.  */

#ifndef cascades_chromevisibility_h
#define cascades_chromevisibility_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
    namespace cascades {

   /*!
    * 
    * @brief A set of visibility modes for the action bar and @c TitleBar.
    * 
    * This class represents different types of visibility modes that you can use
    * for the action bar and title bar on a @c Page, @c NavigationPane, or @c TabbedPane.
    * 
    * The following images demonstrate how the @c TitleBar appears using the different
    * visibility modes.
    *
    * @image html visibility_modes.png
    * 
    * @xmlonly
    * <apigrouping group="User interface/Application structure"/>
    * @endxmlonly
    *
    * @since BlackBerry 10.0.0
    */
    class BBCASCADES_EXPORT ChromeVisibility {
        Q_GADGET
        Q_ENUMS (Type)
    
    public:

       /*!
        * @brief Specifies the visibility modes used with the action bar and @c TitleBar.
        *
        * @since BlackBerry 10.0.0
        */
        enum Type {
            /*! @brief The default visibility.
             *
             * @since BlackBerry 10.0.0
             */
            Default,
            /*! @brief The item should be visible.
             *
             * @since BlackBerry 10.0.0
             */
            Visible,
            /*! @brief The item is overlaid on top of the content and made semi-transparent.
             *
             * @since BlackBerry 10.0.0
             */
            Overlay,
            /*! @brief The item should be hidden.
             *
             * @since BlackBerry 10.0.0
             */
            Hidden,
            /*! @brief The item should be shown in a compact mode.
             *
             * This mode keeps the chrome to a minimum while the essential content is still shown. E.g. the action bar will only show overflow buttons, back button and a signature action.
             *
             * @since BlackBerry 10.3.0
             */
            Compact
        };
    
    private:

      ChromeVisibility();
      ~ChromeVisibility();
    };
}
}

#endif // cascades_chromevisibility_h
