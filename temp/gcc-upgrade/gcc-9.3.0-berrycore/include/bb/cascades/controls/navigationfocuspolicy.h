/* Copyright (C) 2014 Research In Motion Limited.  */

#ifndef cascades_navigationfocuspolicy_h
#define cascades_navigationfocuspolicy_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
    namespace cascades {

        /*!
        * @brief Represents different navigation focus policies, which specify if a control can receive focus
        * when a user navigates with a trackpad or similar input.
        *
        * @see @c Control::navigationFocusPolicy
        *
        * @xmlonly
        * <apigrouping group="User interface/Core controls"/>
        * @endxmlonly
        *
        * @since BlackBerry 10.3.1
        */
        class BBCASCADES_EXPORT NavigationFocusPolicy
        {
            Q_GADGET
            Q_ENUMS(Type)

        public:
            /*!
            * @brief Specifies the different navigation focus policies for a control.
            *
            * @since BlackBerry 10.3.1
            */
            enum Type
            {
                /*! @brief The default navigation focus policy preferred by the Control
                *
                * @since BlackBerry 10.3.1
                */
                Default = 0x0,
                /*! @brief Control is not focusable through navigation.
                *
                * @since BlackBerry 10.3.1
                */
                NotFocusable = 0x1,
                /*! @brief Control can be focused through navigation.
                *
                * @since BlackBerry 10.3.1
                */
                Focusable = 0x2,
            };

        private:
            NavigationFocusPolicy();
            ~NavigationFocusPolicy();
        };
    }
}

#endif // cascades_navigationfocuspolicy_h

