/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_fontstyle_h
#define cascades_fontstyle_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
namespace cascades {

/*!
 * 
 * @brief Represents a set of font styles for a @c TextStyle.
 *
 * Font styles include normal and italic.
 *
 * @xmlonly
 * <apigrouping group="User interface/Text"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT FontStyle {
  Q_GADGET
  Q_ENUMS (Type)
public:
    /*!
     * @brief The available font styles.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
      /*!
       * @brief The default font style.
       *
       * The default font style varies among systems and controls. Setting to default leaves
       * the choice of font style to the system.
       *
       * @since BlackBerry 10.0.0
       */      
      Default,      
      /*!
       * @brief Normal font.
       *
       * @since BlackBerry 10.0.0
       */
      Normal,
      /*!
       * @brief Italic font.
       *
       * @since BlackBerry 10.0.0
       */
      Italic
    };
private:
  /*! @cond PRIVATE */
  FontStyle();
  ~FontStyle();
  /*! @endcond */
};

}
}

#endif // cascades_fontstyle_h
