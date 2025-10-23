/* Copyright (C) 2013 Research In Motion Limited.  */

#ifndef cascades_autohidebehavior_h
#define cascades_autohidebehavior_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
    namespace cascades {

   /*!
    * @brief Specifies the auto-hide behavior for a page's action bar.
    *
    * @see @c ListView::scrollRole, @c ScrollView::scrollRole, @c Page::actionBarAutoHideBehavior
    *
    * @since BlackBerry 10.1.0
    *
    * @xmlonly
    * <apigrouping group="User interface/Application structure"/>
    * @endxmlonly
    */
   class BBCASCADES_EXPORT ActionBarAutoHideBehavior {
        Q_GADGET
        Q_ENUMS (Type)

    public:

       /*!
        * @brief Specifies the auto-hide behavior for the action bar.
        *
        * @since BlackBerry 10.1.0
        */
        enum Type {
            /*! 
             * @brief The default auto-hide behavior.
             *
             * @since BlackBerry 10.1.0
             */
            Default,
            /*! 
             * @brief The action bar will be automatically hidden when user scrolls
             * within the main scrollable area of the screen.
             *
             * @since BlackBerry 10.1.0
             */
            HideOnScroll,
            /*! 
             * @brief Auto-hiding of the action bar is disabled.
             *
             * @since BlackBerry 10.1.0
             */
            Disabled
        };

    private:
        /*! @cond PRIVATE */
        ActionBarAutoHideBehavior();
        ~ActionBarAutoHideBehavior();
        /*! @endcond */
    };
}
}

#endif // cascades_autohidebehavior_h
