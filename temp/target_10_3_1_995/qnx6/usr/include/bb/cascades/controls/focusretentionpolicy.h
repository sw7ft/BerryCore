/* Copyright (C) 2012-2013 Research In Motion Limited.  */

#ifndef cascades_focusretentionpolicy_h
#define cascades_focusretentionpolicy_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>
#include <QFlags>

namespace bb {
  namespace cascades {

    /*!
    * 
    * @brief Specifies the conditions under which a control can lose focus when the
    * user interacts with other controls.
    *
    * @see @c Control::focusRetentionPolicyFlags
    *
    * @xmlonly
    * <apigrouping group="User interface/Core controls"/>
    * @endxmlonly
     *
     * @since BlackBerry 10.0.0
    */
    class BBCASCADES_EXPORT FocusRetentionPolicy
    {
      Q_GADGET
      Q_ENUMS(Type)
      Q_FLAGS(Types)

    public:
      /*!
      * @brief The available focus retention policies for a control.
      *
      * @xmlonly
      * <qml>
      * <enum flagsType="bb::cascades::FocusRetentionPolicy::Types"/>
      * </qml>
      * @endxmlonly
       *
       * @since BlackBerry 10.0.0
      */
      enum Type
      {
        /*! 
         * @brief The default policy preferred by the @c Control.
         *
         * @since BlackBerry 10.0.0
         */
        Default            = (0 << 0),
        /*! 
         * @brief The control loses focus when the user scrolls within a scrollable control, like
         * a @c ListView or @c ScrollView.
         *
         * @since BlackBerry 10.0.0
         */
        LoseOnScroll       = (1 << 0),
        /*! 
         * @brief The control loses focus if another focusable control is requesting focus.
         *
         * @since BlackBerry 10.0.0
         */
        LoseToFocusable    = (1 << 1),
        /*! 
         * @brief The control loses focus if the user touches a non-focusable control.
         *
         * @since BlackBerry 10.0.0
         */
        LoseToNonFocusable = (1 << 2)
      };

     /*!
      * @brief Defines combinations of focus retention policies.
      * 
      * This flag overrides the default @c FocusRetentionPolicy for a control.
      *
      * @see bb::cascades::FocusRetentionPolicy::Type
      *
      * @since BlackBerry 10.0.0
      */
      Q_DECLARE_FLAGS(Types, Type);

    private:       
      FocusRetentionPolicy();
      ~FocusRetentionPolicy();
    };

    /*! @cond PRIVATE */
    Q_DECLARE_OPERATORS_FOR_FLAGS(bb::cascades::FocusRetentionPolicy::Types)
    /*! @endcond */
  }
}

#endif // cascades_focusretentionpolicy_h

