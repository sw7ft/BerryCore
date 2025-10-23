/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_textareascrollmode_h
#define cascades_textareascrollmode_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
namespace cascades {

/*!
 * 
 * @brief Represents a scoll mode for the @c TextArea.
 *
 * The @c %TextAreaScrollMode determines how the @c TextArea behaves when scrolling in the vertical direction.
 *
 * @xmlonly
 * <apigrouping group="User interface/Text"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT TextAreaScrollMode {
  Q_GADGET
  Q_ENUMS (Type)
public:
    /*!
     * @brief Scroll modes for a @c TextArea
     *
     * @since BlackBerry 10.0.0
     */  
    enum Type {
      /*!
        * @brief The platform decides scrolling behavior based on content and context. Typically this will 
        * behave according to the standard scroll mode. 
        *
       *
       * @since BlackBerry 10.0.0
        */
      Default = 0,
      /*!
        * @brief Elastic scrolling.
        *
        * Trying to scroll outside the content area will be result in an elastic behaviour.
       *
       * @since BlackBerry 10.0.0
        */
      Elastic = 1,
      /*!
        * @brief Stiff scrolling. 
        *
        * Trying to scroll outside the content area will halt the scrolling resulting in a stiff behaviour.
       *
       * @since BlackBerry 10.0.0
        */
      Stiff = 2
    };
private:
  /*! @cond PRIVATE */
  TextAreaScrollMode();
  ~TextAreaScrollMode();
  /*! @endcond */
};

}
}

#endif // cascades_textareascrollmode_h
