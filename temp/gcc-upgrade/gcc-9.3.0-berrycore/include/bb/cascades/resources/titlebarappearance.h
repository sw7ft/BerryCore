/* Copyright (C) 2012-2013 Research In Motion Limited.  */

#ifndef cascades_titlebarappearance_h
#define cascades_titlebarappearance_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
namespace cascades {

   /*!
    *
    * @brief A class that represents different appearances for the @c TitleBar.
    * 
    * @xmlonly
    * <apigrouping group="User interface/Resources"/>
    * @endxmlonly
    *
    * @since BlackBerry 10.0.0
    */
  class BBCASCADES_EXPORT TitleBarAppearance {
    Q_GADGET
    Q_ENUMS (Type)

    public:

     /*!
      * @brief Specifies a @c TitleBar appearance.
      *
      * @since BlackBerry 10.0.0
      */
      enum Type {
        /*! @brief Specifies that the framework should decide the appearance of the @c TitleBar.
         *
         * @since BlackBerry 10.0.0
         */
        Default = 0,
        /*! @brief Specifies that the @c %TitleBar should use the application's @c VisualStyle.
         *
         * @since BlackBerry 10.0.0
         */
        Plain = 1,
        /*! @brief Specifies that the @c %TitleBar should have a branded blue color.
         *
         * @since BlackBerry 10.0.0
         */
        Branded = 2
      };

    private:

      TitleBarAppearance();
      ~TitleBarAppearance();
  };
}
}

#endif // cascades_titlebarappearance_h
