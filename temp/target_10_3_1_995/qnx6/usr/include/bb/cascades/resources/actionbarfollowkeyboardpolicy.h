/* Copyright (C) 2013 Research In Motion Limited.  */

#ifndef cascades_actionbarfollowkeyboardpolicy_h
#define cascades_actionbarfollowkeyboardpolicy_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
    namespace cascades {

    /*!
     * @brief Specifies the action bar's follow the virtual keyboard
     * policy.
     *
     * @see @c Page::actionBarFollowKeyboardPolicy
     *
     * @since BlackBerry 10.3.0
     *
     * @xmlonly
     * <apigrouping group="User interface/Application structure"/>
     * @endxmlonly
     */
    class BBCASCADES_EXPORT ActionBarFollowKeyboardPolicy {
        Q_GADGET
        Q_ENUMS (Type)

    public:

       /*!
        * @brief Specifies the action bar's follow the virtual keyboard
        * policy.
        *
        * @since BlackBerry 10.3.0
        */
        enum Type {
            /*!
             * @brief The action bar's default follow keyboard policy.
             *
             * @since BlackBerry 10.3.0
             */
            Default,
            /*!
             * @brief The action bar never follows the virtual keyboard.
             *
             * @since BlackBerry 10.3.0
             */
            Never,
            /*!
             * @brief The action bar follows the virtual keyboard only in Portrait mode.
             * When the virtual keyboard is invoked, the action bar follows the virtual keyboard
             * and stays visible on the screen only if the device is in Portrait mode.
             *
             * @since BlackBerry 10.3.0
             */
            Portrait
        };

    private:
        /*! @cond PRIVATE */
        ActionBarFollowKeyboardPolicy();
        virtual ~ActionBarFollowKeyboardPolicy();
        /*! @endcond */
    };
}
}

#endif // cascades_actionbarfollowkeyboardpolicy_h
