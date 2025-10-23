/* Copyright (C) 2012-2013 Research In Motion Limited.  */

#ifndef cascades_focusautoshow_h
#define cascades_focusautoshow_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
    namespace cascades {

       /*!
        * @brief Represents different behaviors for a control when it receives
        * focus.
        *
        * By default, a control is automatically displayed once it receives focus.
        * You can override this behavior by specifying @c FocusAutoShow::None on a
        * control's @c focusAutoShow property.
        *
        * @see @c Control::focusAutoShow
        *
        * @xmlonly
        * <apigrouping group="User interface/Core controls"/>
        * @endxmlonly
        *
        * @since BlackBerry 10.0.0
        */
        class BBCASCADES_EXPORT FocusAutoShow
        {
            Q_GADGET
            Q_ENUMS(Type)

        public:
            /*!
            * @brief Specifies the FocusAutoShow modes a Control can have.
             *
             * @since BlackBerry 10.0.0
            */
            enum Type
            {
                /*! @brief The default FocusAutoShow preferred by the Control
                 *
                 * @since BlackBerry 10.0.0
                 */
                Default = 0x0,
                /*! @brief The Control will not be scrolled to and showed automatically when focused
                 *
                 * @since BlackBerry 10.0.0
                 */
                None    = 0x1
            };

        private:
            FocusAutoShow();
            ~FocusAutoShow();
        };
    }
}

#endif // cascades_focusautoshow_h

