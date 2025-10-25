/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_fontweight_h
#define cascades_fontweight_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
namespace cascades {

/*!
 * 
 * @brief Represents the types of font weights for a @c TextStyle.
 *
 * The font weight is a value between 100 and 900, with 100 being a very light and
 * 900 being very heavy. The @c Normal and @c Bold weights are the equivalent to
 * @c W400 and @c W700.
 *
 * @xmlonly
 * <apigrouping group="User interface/Text"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT FontWeight {
private:
  Q_GADGET
  Q_ENUMS (Type)
public:
    /*!
     * @brief The available font weights for a @c TextStyle.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
      /*!
       * @brief The default font weight.
       *
       * The default font weight varies among systems and controls. Setting to default leaves
       * the choice of font weight to the system.
       *
       * @since BlackBerry 10.0.0
       */      
      Default = 0,
      /*!
       * @brief Normal font.
       *
       * This weight is the equivalent to W400.
       *
       * @since BlackBerry 10.0.0
        */
      Normal,
      /*!
       * @brief Bold font.
       *
       * This weight is the equivalent to W700
       *
       * @since BlackBerry 10.0.0
       */
      Bold,

      /*!
        * @brief Weight of 100.
        * 
        * @since BlackBerry 10.0.0
        */
      W100,

      /*!
       * @brief Weight of 200.
       *
       * @since BlackBerry 10.0.0
       */
      W200,

      /*!
       * @brief Weight of 300.
       *
       * @since BlackBerry 10.0.0
       */
      W300,

      /*!
       * @brief Weight of 400.
       *
       * This weight is the equivalent to @c Normal.
       *
       * @since BlackBerry 10.0.0
       */
      W400,

      /*!
       * @brief Weight of 500.
       *
       * @since BlackBerry 10.0.0
       */
      W500,

      /*!
       * @brief Weight of 600.
       *
       * @since BlackBerry 10.0.0
       */
      W600,

      /*!
       * @brief Weight of 700.
       *
       * This weight is the equivalent to @c Bold.
       *
       * @since BlackBerry 10.0.0
       */
      W700,

      /*!
       * @brief Weight of 800.
       *
       * @since BlackBerry 10.0.0
       */
      W800,

      /*!
       * @brief Weight of 900.
       *
       * @since BlackBerry 10.0.0
       */
      W900

    };
private:
  /*! @cond PRIVATE */
  FontWeight();
  ~FontWeight();
  /*! @endcond */
};

}
}

#endif // cascades_fontweight_h
