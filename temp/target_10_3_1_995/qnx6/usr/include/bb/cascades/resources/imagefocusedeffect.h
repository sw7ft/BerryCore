/* Copyright (c) 2014 BlackBerry. All rights reserved. */

#ifndef cascades_imagefocusedeffect_h
#define cascades_imagefocusedeffect_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb {
  namespace cascades {

    /*!
    *
    * @brief A class that represents the different types of an @c ImageFocusedEffect.
    *
    * @xmlonly
    * <apigrouping group="User interface/Resources"/>
    * @endxmlonly
    *
    * @since BlackBerry 10.3.1
    */
    class BBCASCADES_EXPORT ImageFocusedEffect {
      Q_GADGET
      Q_ENUMS (Type)

      public:
        enum Type {
            /*! @brief Specifies that the framework should decide the image focused effect.
             *
             * @since BlackBerry 10.3.1
             */
            Default = 0,
            /*! @brief Specifies that the image should not apply any effect.
             *
             * @since BlackBerry 10.3.1
             */
            None = 1,
            /*! @brief Specifies that the image should use text color on non-tranparent pixels.
             *
             * @since BlackBerry 10.3.1
             */
            TextColor = 2
          };

      private:
        /*! @cond PRIVATE */
        ImageFocusedEffect();
        ~ImageFocusedEffect();
        /*! @endcond */
    };
  }
}
QML_DECLARE_TYPE(bb::cascades::ImageFocusedEffect::Type)

#endif // cascades_imagefocusedeffect_h
