/* Copyright (C) 2012-2014 Research In Motion Limited.  */

#ifndef cascades_deviceshortcuts_h
#define cascades_deviceshortcuts_h

#include <QObject>
#include <bb/cascades/bbcascades_global.h>

namespace bb {
    namespace cascades {

        /*!
         * 
         * @brief Enumeration for device shortcuts
         *
         * @see DeviceShortcut
         *
         * @xmlonly
         * <apigrouping group="User interface/Events"/>
         * @endxmlonly
         *
         * @since BlackBerry 10.3.1
         */
        class BBCASCADES_EXPORT DeviceShortcuts {
            Q_GADGET
                Q_ENUMS (Type)
            public:

                /*!
                 * @brief Enumeration for device shortcuts
                 *
                 * @since BlackBerry 10.3.1
                 */
                enum Type {

                    /*! 
                     * @brief None is used as the shortcut type for default constructed @c DeviceShortcuts.
                     *
                     * @since BlackBerry 10.3.1
                     * The shortcut cannot be triggered. 
                     */
                    None = 0,
                    
                    /*! 
                     * @brief Shortcut triggered when user taps the send key
                     *
                     * @since BlackBerry 10.3.1
                     */
                    SendTap,
                    
                    /*! 
                     * @brief Shortcut triggered when user taps the menu key
                     *
                     * @since BlackBerry 10.3.1
                     */
                    MenuTap,
                    
                    /*! 
                     * @brief Shortcut triggered when user taps the back key
                     *
                     * @since BlackBerry 10.3.1
                     */
                    BackTap,
                    
                    /*! 
                     * @brief Shortcut triggered when user taps the end key
                     *
                     * @since BlackBerry 10.3.1
                     */
                    EndTap,
                    
                    /*! 
                     * @brief Shortcut triggered when user long presses the menu key
                     *
                     * @since BlackBerry 10.3.1
                     */
                    MenuLongPress,

                };

            private:
                /*! @cond PRIVATE */
                DeviceShortcuts();
                ~DeviceShortcuts();
                /*! @endcond */
        };

    } // namespace cascades
} // namespace bb

#endif // cascades_deviceshortcuts_h
