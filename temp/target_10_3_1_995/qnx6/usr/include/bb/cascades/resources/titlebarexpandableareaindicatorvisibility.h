/* Copyright (C) 2012-2013 Research In Motion Limited.  */

#ifndef cascades_titlebarindicatorvisibility_h
#define cascades_titlebarindicatorvisibility_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
namespace cascades {

   /*!
    *
    * @brief A class that represents different visible states for the expandable indicator on the @c TitleBar.
    * 
    * @xmlonly
    * <apigrouping group="User interface/Resources"/>
    * @endxmlonly
    *
    * @since BlackBerry 10.1.0
    */
  class BBCASCADES_EXPORT TitleBarExpandableAreaIndicatorVisibility {
    Q_GADGET
    Q_ENUMS (Type)

    public:

     /*!
      * @brief Specifies the visibility for the expandable indicator on the @c TitleBar.
      *
      * @since BlackBerry 10.1.0
      */
      enum Type {
        /*! @brief Specifies that the framework should decide the visibility.
         *
         * @since BlackBerry 10.1.0
         */
        Default = 0,
        /*! @brief Specifies that the indicator should be visible.
         *
         * @since BlackBerry 10.1.0
         */
        Visible = 1,
        /*! @brief Specifies that the indicator should be hidden.
         *
         * @since BlackBerry 10.1.0
         */
        Hidden = 2
      };

    private:

      TitleBarExpandableAreaIndicatorVisibility();
      ~TitleBarExpandableAreaIndicatorVisibility();
  };
}
}

#endif // cascades_titlebarindicatorvisibility_h
