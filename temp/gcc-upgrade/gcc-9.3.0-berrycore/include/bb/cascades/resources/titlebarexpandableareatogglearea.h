/* Copyright (C) 2012-2013 Research In Motion Limited.  */

#ifndef cascades_titlebarexpandableareatogglearea_h
#define cascades_titlebarexpandableareatogglearea_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
namespace cascades {

   /*!
    *
    * @brief A class that represents different toggle area for the title bar expandable area.
    * 
    * @xmlonly
    * <apigrouping group="User interface/Resources"/>
    * @endxmlonly
    *
    * @since BlackBerry 10.1.0
    */
  class BBCASCADES_EXPORT TitleBarExpandableAreaToggleArea {
    Q_GADGET
    Q_ENUMS (Type)

    public:

     /*!
      * @brief Specifies a toggle area for the title bar expandable area.
      *
      * @since BlackBerry 10.1.0
      */
      enum Type {
        /*! @brief Specifies that the framework should decide the toggle area.
         *
         * @since BlackBerry 10.1.0
         */
        Default = 0,
        /*! @brief Specifies that the entire title bar is used for toggling the expandable area.
         *
         * @since BlackBerry 10.1.0
         */
        EntireTitleBar = 1,
        /*! @brief Specifies that only the area of the expandable indicator is used for toggling the expandable area.
         *
         * @since BlackBerry 10.1.0
         */
        IndicatorOnly = 2,
      };

    private:

      TitleBarExpandableAreaToggleArea();
      ~TitleBarExpandableAreaToggleArea();
  };
}
}

#endif // cascades_titlebarappearance_h
