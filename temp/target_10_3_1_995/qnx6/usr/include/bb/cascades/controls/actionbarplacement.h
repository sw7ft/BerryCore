/* Copyright (C) 2012-2013 Research In Motion Limited.  */

#ifndef cascades_actionbarplacement_h
#define cascades_actionbarplacement_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
    namespace cascades {

   /*!
    * 
    * @brief A class representing action bar placement options.
    * 
    * By default, a page's actions are always displayed in the action menu. By using this class,
    * you can specify whether an action should appear on the action bar as well.
    *
    * If you specify that an action should appear on the action bar and it doesn't fit, it's ignored.
    *
    * @xmlonly
    * <apigrouping group="User interface/Application structure"/>
    * @endxmlonly
    *
    * @since BlackBerry 10.0.0
    */
    class BBCASCADES_EXPORT ActionBarPlacement {
        Q_GADGET
        Q_ENUMS (Type)
    
    public:

       /*!
        * @brief Specifies the action bar behavior.
        *
        * @since BlackBerry 10.0.0
        */
        enum Type {
            /*! @brief The default value, which is typically the same as @c InOverflow.
             *
             * @since BlackBerry 10.0.0
             */
            Default,
            /*! @brief Specifies that the action should be placed in the action menu only.
             *
             * @since BlackBerry 10.0.0
             */
            InOverflow,
            /*! @brief  Specifies that the action should be placed on the action bar.
             *
             * The action will also be placed in the action menu.
             *
             * @since BlackBerry 10.0.0
             */
            OnBar,
            /*!
             * @brief  Specifies that the action could be used as a Signature Action.
             *
             * The action will also be placed in the action menu.
             *
             * @note It is possible to show only one action as a Signature Action on an action bar at the same
             * time. If more then one action in an @c ActionSet has @c ActionBarPlacement set to @c Signature
             * then last action in a set with such @c ActionBarPlacement will be shown as a Signature Action.
             *
             * @since BlackBerry 10.3.0
             */
            Signature
        };
    
    private:

      ActionBarPlacement();
      virtual ~ActionBarPlacement();
    };
}
}

#endif // cascades_actionbarplacement_h
