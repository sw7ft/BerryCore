/* Copyright (c) 2014 BlackBerry. All rights reserved. */

#ifndef cascades_shortcuttriggermode_h
#define cascades_shortcuttriggermode_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
    namespace cascades {

/*!
 * @brief A class representing different shortcut trigger modes.
 *
 * A shortcut trigger mode represents the user input needed to trigger
 * a key shortcut.
 *
 * @see AbstractShortcut::setTriggerMode()
 *
 * @xmlonly
 *     <apigrouping group="User interface/Application structure"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.3.0
 */
class BBCASCADES_EXPORT ShortcutTriggerMode {
    Q_GADGET
    Q_ENUMS (Type)
public:

    /*!
     * @brief The different shorcut trigger modes
     *
     * @see VisualNode::setTouchPropagationMode()
     *
     * @since BlackBerry 10.3.0
     */
    enum Type {
        /*! @brief The system decides which user input triggers the shortcut.
         *
         * @since BlackBerry 10.3.0
         */
        Default = 0,

        /*! @brief The shortcut is triggered when the user taps the shortcut key.
         *
         * @since BlackBerry 10.3.0
         */
        Tap = 1,

        /*! @brief The shortcut is triggered when the user presses the shortcut key.
         *
         * @since BlackBerry 10.3.0
         */
        Press = 2,

        /*! @brief The shortcut is triggered when the user presses and hold the shortcut key.
         *
         * @since BlackBerry 10.3.0
         */
        LongPress = 3
    };

private:
    /*! @cond PRIVATE */
    ShortcutTriggerMode();
    ~ShortcutTriggerMode();
    /*! @endcond */
};
}
}

#endif // cascades_shortcuttriggermode_h
