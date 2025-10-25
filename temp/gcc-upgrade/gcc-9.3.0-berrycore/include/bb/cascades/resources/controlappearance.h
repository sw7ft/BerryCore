/* Copyright (c) 2013 BlackBerry. All rights reserved. */

#ifndef cascades_controlappearance_h
#define cascades_controlappearance_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb {
  namespace cascades {

    /*!
    *
    * @brief A class that represents the different types of a @c ControlAppearance.
    *
    * @xmlonly
    * <apigrouping group="User interface/Resources"/>
    * @endxmlonly
    *
    * @since BlackBerry 10.3.0
    */
    class BBCASCADES_EXPORT ControlAppearance {
      Q_GADGET
      Q_ENUMS (Type)

      public:
        enum Type {
            /*! @brief Specifies that the framework should decide the control appearance.
             *
             * @since BlackBerry 10.3.0
             */
            Default = 0,
            /*! @brief Specifies that the control should apply predefined plain appearance.
             *
             * @since BlackBerry 10.3.0
             */
            Plain = 1,
            /*! @brief Specifies that the control should apply changeable primary appearance.
             *
             * @see @c Themes
             *
             * @since BlackBerry 10.3.0
             */
            Primary = 2
          };

      private:
        /*! @cond PRIVATE */
        ControlAppearance();
        ~ControlAppearance();
        /*! @endcond */
    };
  }
}
QML_DECLARE_TYPE(bb::cascades::ControlAppearance::Type)

#endif // cascades_controlappearance_h
