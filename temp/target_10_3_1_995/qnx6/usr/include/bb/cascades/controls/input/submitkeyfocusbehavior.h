/* Copyright (C) 2012-2013 Research In Motion Limited.  */

#ifndef BB_CASCADES_SUBMITKEYFOCUSBEHAVIOR_H
#define BB_CASCADES_SUBMITKEYFOCUSBEHAVIOR_H

#include <bb/cascades/bbcascades_global.h>

#include <QObject>
#include <QMetaObject>

namespace bb {
namespace cascades {

/*!
 *
 * @brief A class representing different submit key focus behaviors.
 *
 * This class represents different submit key focus behaviors.
 * The behavior is only used when a submit key is set, otherwise
 * it will be ignored. The behavior will control what will happen
 * to the controls focus when the submit key is pressed.
 *
 * @see TextInputProperties
 *
 * @xmlonly
 * <apigrouping group="User interface/Text"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class SubmitKeyFocusBehavior {
    Q_GADGET
    Q_ENUMS(Type)

public:

   /*!
    * @brief Specifies different submit keys focus behaviors.
    *
    * @since BlackBerry 10.0.0
    */
    enum Type {
        /*! @brief Sets the submit key focus behavior to "Default".
         *
         * @since BlackBerry 10.0.0
         */
        Default = 0,

        /*! @brief Sets the submit key focus behavior to "Keep". The control will keep focus if submit is pressed in this control.
         *
         * @since BlackBerry 10.0.0
         */
        Keep = 1,

        /*! @brief Sets the submit key focus behavior to "Next". When submit is pressed in this control, focus will move to the next focusable control, or if none exists. Focus will be lost and the Virtual keyboard will disappear.
         *
         * @since BlackBerry 10.0.0
         */
        Next = 2,

        /*! @brief Sets the submit key focus behavior to "Lose". When submit is pressed in this control, focus will be lost.
         *
         * @since BlackBerry 10.0.0
         */
        Lose = 3,
    };

private:
    /*! \cond PRIVATE */
    SubmitKeyFocusBehavior();
    ~SubmitKeyFocusBehavior();
    /*! \endcond */
};

}
}

#endif // BB_CASCADES_SUBMITKEYFOCUSBEHAVIOR_H
