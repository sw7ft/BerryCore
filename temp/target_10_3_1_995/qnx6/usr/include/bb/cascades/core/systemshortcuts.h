/* Copyright (c) 2014 BlackBerry. All rights reserved. */

#ifndef cascades_systemshortcuts_h
#define cascades_systemshortcuts_h

#include <QObject>
#include <bb/cascades/bbcascades_global.h>
#include <sys/keycodes.h>

namespace bb {
    namespace cascades {

        /*!
         * 
         * @brief Enumeration for shortcuts defined in the QNX platform.
         *
         * These shortcuts are localized, meaning each shortcut will
         * be triggered by a key that is intuitive for each locale. Use of
         * these shortcuts over key shortcuts (where applicable) is strongly
         * recommended, and application developers are encouraged to map these
         * shortcuts to their own actions in a logical way. 
         *
         * If there is a conflict between a @c SystemShortcut and a @c Shortcut,
         * the @c %SystemShortcut will get priority.
         *
         * @see SystemShortcut
         *
         * @note This set of shortcuts is a preliminary estimation of what
         * shortcuts will be available. The set of available shortcuts may
         * change when they are provided by the platform.
         *
         * @xmlonly
         * <apigrouping group="User interface/Events"/>
         * @endxmlonly
         *
         * @since BlackBerry 10.1.0
         */
        class BBCASCADES_EXPORT SystemShortcuts {
            Q_GADGET
                Q_ENUMS (Type)
            public:

                /*!
                 * @brief Enumeration for shortcuts defined in the QNX platform.
                 *
                 * @since BlackBerry 10.1.0
                 */
                enum Type {
                    /*! 
                     * @brief None is used as the shortcut type for default constructed @c SystemShortcuts.
                     *
                     * @since BlackBerry 10.1.0
                     * The shortcut cannot be triggered. 
                     */
                    None = 0,

                    /*! 
                     * @brief Shortcut to scroll down one screen. Triggered by 'Space' in English locale.
                     *
                     * @since BlackBerry 10.1.0
                     */
                    ScrollDownOneScreen = KEYCODE_PG_DOWN,

                    /*! 
                     * @brief Shortcut to scroll up one screen. Triggered by 'Shift+Space' in English locale.
                     *
                     * @since BlackBerry 10.1.0
                     */
                    ScrollUpOneScreen = KEYCODE_PG_UP,

                    /*! 
                     * @brief Shortcut to zoom in. Triggered by 'I' in English locale.
                     *
                     * @since BlackBerry 10.1.0
                     */
                    ZoomIn = KEYCODE_AC_ZOOM_IN,

                    /*! 
                     * @brief Shortcut to zoom out. Triggered by 'O' in English locale.
                     *
                     * @since BlackBerry 10.1.0
                     */
                    ZoomOut = KEYCODE_AC_ZOOM_OUT,

                    /*! 
                     * @brief Shortcut to jump to top. Triggered by 'T' in English locale.
                     *
                     * @since BlackBerry 10.1.0
                     */
                    JumpToTop = KEYCODE_HOME,

                    /*! 
                     * @brief Shortcut to jump to bottom. Triggered by 'B' in English locale.
                     *
                     * @since BlackBerry 10.1.0
                     */
                    JumpToBottom = KEYCODE_END,

                    /*! 
                     * @brief Shortcut to jump to the next section. Triggered by 'N' in English locale.
                     *
                     * @since BlackBerry 10.1.0
                     */
                    NextSection = KEYCODE_AC_FORWARD,

                    /*! 
                     * @brief Shortcut to jump to the previous section. Triggered by 'P' in English locale.
                     *
                     * @since BlackBerry 10.1.0
                     */
                    PreviousSection = KEYCODE_AC_BACK,

                    /*! 
                     * @brief Shortcut to reply to a message. Triggered by 'R' in English locale.
                     *
                     * @since BlackBerry 10.1.0
                     */
                    Reply = KEYCODE_AC_REPLY,

                    /*! 
                     * @brief Shortcut to forward a message. Triggered by 'F' in English locale.
                     *
                     * @since BlackBerry 10.1.0
                     */
                    Forward = KEYCODE_AC_FORWARD_MSG,

                    /*! 
                     * @brief Shortcut to edit current content. Triggered by 'E' in English locale.
                     *
                     * @since BlackBerry 10.1.0
                     */
                    Edit = KEYCODE_AC_OPEN,

                    /*! 
                     * @brief Shortcut to start a search. Triggered by 'S' in English locale.
                     *
                     * @since BlackBerry 10.1.0
                     */
                    Search = KEYCODE_AC_FIND,

                    /*! 
                     * @brief Shortcut to undo. Triggered by 'U' in English locale.
                     *
                     * @since BlackBerry 10.1.0
                     */
                    Undo = KEYCODE_AC_UNDO,

                    /*! 
                     * @brief Shortcut to create new. Triggered by 'C' in English locale.
                     *
                     * @since BlackBerry 10.1.0
                     */
                    CreateNew = KEYCODE_AC_NEW,
                };

            private:
                /*! @cond PRIVATE */
                SystemShortcuts();
                ~SystemShortcuts();
                /*! @endcond */
        };
    }
}

#endif     // cascades_systemshortcuts_h
