/* Copyright (C) 2014 Research In Motion Limited.  */

#ifndef cascades_childrennavigationbehavior_h
#define cascades_childrennavigationbehavior_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
  namespace cascades {

   /*!
    * 
    * @brief Represents different navigation behaviors for a control with children.
    *
    * @see @c Navigation::childrenBehavior
    *
    * @xmlonly
    * <apigrouping group="User interface/Core controls"/>
    * @endxmlonly
    *
    * @since BlackBerry 10.3.1
    */
    class BBCASCADES_EXPORT ChildrenNavigationBehavior
    {
      Q_GADGET
      Q_ENUMS(Type)

    public:
      /*!
       * @brief Specifies the different navigation behavior of the children controls.
       *
       * @since BlackBerry 10.3.1
       */
      enum Type
      {
        /*! @brief The default navigation behavior for a Control is typically Continue
         *
         * @since BlackBerry 10.3.1
         */
        Default = 0x0,
        /*! @brief When there are no more children in the navigation direction, focus will leave the container.
         *
         * @since BlackBerry 10.3.1
         */
        Continue = 0x1,
        /*! @brief When there are no more children in the navigation direction, focus will not move.
         *
         * @since BlackBerry 10.3.1
         */
        Contained = 0x2,
        /*! @brief Children of this control will not get focus when navigating.
         *
         * @since BlackBerry 10.3.1
         */
        None = 0x4
      };

    private:
      /*! @cond PRIVATE */
      ChildrenNavigationBehavior();
      ~ChildrenNavigationBehavior();
      /*! @endcond */
    };

  }
}

#endif // cascades_childrennavigationbehavior_h

