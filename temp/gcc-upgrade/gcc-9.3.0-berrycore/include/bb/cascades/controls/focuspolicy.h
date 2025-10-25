/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_focuspolicy_h
#define cascades_focuspolicy_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
  namespace cascades {

    /*!
    * 
    * @brief Represents different focus policies, which specify how a control can receive focus
    * from a user's interation.
    *
    * Whether or not a control can receive focus during a user interaction, it can always
    * receive focus programmatically (i.e. by calling the @c Control::requestFocus function).
    *
    * @see @c Control::focusPolicy
    *
    * @xmlonly
    * <apigrouping group="User interface/Core controls"/>
    * @endxmlonly
     *
     * @since BlackBerry 10.0.0
    */
    class BBCASCADES_EXPORT FocusPolicy
    {
      Q_GADGET
        Q_ENUMS(Type)

    public:
      /*!
       * @brief Specifies the different focus policy for a control.
       *
       * @since BlackBerry 10.0.0
       */
      enum Type
      {
        /*! @brief The default focus policy preferred by the Control
         *
         * @since BlackBerry 10.0.0
         */
        Default = 0x0,
        /*! @brief Control is only focusable programmatically.
         *
         * @since BlackBerry 10.0.0
         */
        None = 0x1,
        /*! @brief Control can be focused by touch input.
         *
         * @since BlackBerry 10.0.0
         */
        Touch = 0x2,
        /*! @brief Control can be focused by key input.
         *
         * @since BlackBerry 10.0.0
         */
        Key = 0x4,
        /*! @brief Control can be focused by both touch and key input.
         *
         * @since BlackBerry 10.0.0
         */
        KeyAndTouch = Touch | Key
      };

    private:       
      FocusPolicy();
      ~FocusPolicy();
    };
  }
}

#endif // cascades_focuspolicy_h

