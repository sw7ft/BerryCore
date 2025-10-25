/*
 * Copyright (C) 2011-2014 BlackBerry Limited. All rights reserved.
 */

/**
 * @file virtualkeyboard.h
 *
 * @brief Functions to control the virtual keyboard
 *
 * This file defines the virtual keyboard service, which controls the on-screen
 * virtual keyboard.  The virtual keyboard service allows an application to show
 * and hide the on-screen keyboard, and receive notifications when the keyboard
 * is displayed or hidden.  Using the virtual keyboard service you can configure
 * various keyboard options.  You can also obtain the dynamic keyboard height.
 *
 * Your app can display the virtual keyboard by calling @c
 * virtualkeyboard_show(). When the device is connected to a keyboard (e.g.,
 * via Bluetooth), the virtual keyboard will not be shown unless the user
 * swipes up with two fingers from the bottom bezel.
 *
 * Your app can hide the virtual keyboard by calling @c virtualkeyboard_hide().
 *
 * To change the keyboard options, call the @c virtualkeyboard_change_options()
 * function and specify the keyboard layout and Enter key text. The enumeration
 * @c #virtualkeyboard_layout_t lists the keyboard layouts, and the enumeration
 * @c #virtualkeyboard_enter_t lists the options for Enter key text. The Enter
 * key text is automatically updated to the correct language if you change the
 * language of the keyboard.
 *
 * Key press events come through the Screen API. For more information, see the
 * Screen API or bps/screen.h.
 *
 * @since BlackBerry 10.0.0
 */

#ifndef _BPS_VIRTUALKEYBOARD_H_INCLUDED
#define _BPS_VIRTUALKEYBOARD_H_INCLUDED

#include <stdbool.h>
#include <sys/platform.h>

#include "bps/bps.h"

__BEGIN_DECLS

/**
 * @brief Event codes for virtual keyboard events
 *
 * This enumeration defines the event codes for the types of events that the
 * virtual keyboard service may return.
 * @anonenum bps_virtualkeyboard_events Virtual keyboard events
 *
 * @since BlackBerry 10.0.0
 */
enum {
    /**
     * The virtual keyboard has become visible.
     *
     * @since BlackBerry 10.0.0
     */
    VIRTUALKEYBOARD_EVENT_VISIBLE   = 0x01,

    /**
     * The virtual keyboard has become hidden.
     *
     * @since BlackBerry 10.0.0
     */
    VIRTUALKEYBOARD_EVENT_HIDDEN    = 0x02,

    /**
     * Contains all the information about the current status of the virtual
     * keyboard.
     *
     * @since BlackBerry 10.0.0
     */
    VIRTUALKEYBOARD_EVENT_INFO      = 0x03
};

/**
 * @brief Virtual keyboard layouts
 *
 * This enumeration defines the virtual keyboard layouts that may be displayed.
 * Possible layouts include those that are designed for typing URLs, email
 * addresses, symbols, and so on. See the "Virtual keyboards" topic for more
 * information.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * The default layout.
     *
     * @since BlackBerry 10.0.0
     */
    VIRTUALKEYBOARD_LAYOUT_DEFAULT  = 0,

    /**
     * Layout for entering URLs.
     *
     * @since BlackBerry 10.0.0
     */
    VIRTUALKEYBOARD_LAYOUT_URL      = 1,

    /**
     * Layout for entering email addresses.
     *
     * @since BlackBerry 10.0.0
     */
    VIRTUALKEYBOARD_LAYOUT_EMAIL    = 2,

    /**
     * Layout for use with the Web.
     *
     * @since BlackBerry 10.0.0
     */
    VIRTUALKEYBOARD_LAYOUT_WEB      = 3,

    /**
     * Layout showing numbers and punctuation.
     *
     * @since BlackBerry 10.0.0
     */
    VIRTUALKEYBOARD_LAYOUT_NUM_PUNC = 4,

    /**
     * Layout showing symbols.
     *
     * @since BlackBerry 10.0.0
     */
    VIRTUALKEYBOARD_LAYOUT_SYMBOL   = 5,

    /**
     * Layout for entering phone numbers.
     *
     * @since BlackBerry 10.0.0
     */
    VIRTUALKEYBOARD_LAYOUT_PHONE    = 6,

    /**
     * Layout for entering PINs.
     *
     * @since BlackBerry 10.0.0
     */
    VIRTUALKEYBOARD_LAYOUT_PIN      = 7,

    /**
     * Layout for entering passwords.
     *
     * @since BlackBerry 10.0.0
     */
    VIRTUALKEYBOARD_LAYOUT_PASSWORD = 8,

    /**
     * @deprecated Use #VIRTUALKEYBOARD_LAYOUT_SIM_PIN
     *
     * @since BlackBerry 10.0.0
     */
    VIRTUALKEYBOARD_LAYOUT_DIAL_PAD = 9,

    /**
     * Layout for entering the PIN of a SIM card.
     *
     * @since BlackBerry 10.2.0
     */
    VIRTUALKEYBOARD_LAYOUT_SIM_PIN = 9,

    /**
     * Layout for entering numbers.
     *
     * @since BlackBerry 10.2.0
     */
    VIRTUALKEYBOARD_LAYOUT_NUMBER   = 10,

    /**
     * Layout for entering alphabetic characters and numbers. (Similar to
     * @c #VIRTUALKEYBOARD_LAYOUT_PASSWORD, but without additional privacy
     * restrictions.)
     *
     * @since BlackBerry 10.3.0
     */
    VIRTUALKEYBOARD_LAYOUT_ALPHANUMERIC   = 11
} virtualkeyboard_layout_t;

/**
 * @brief Text for the Enter key on the virtual keyboard
 *
 * This enumeration defines the specific text that can appear on the Enter key
 * of the virtual keyboard. For example, you can configure this key to display
 * the text "Go", "Send", "Done", and so on.
 *
 * Note that for some virtual keyboard layouts there isn't room to display this
 * text on the Enter key.  In that case, the default Enter key is displayed.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * The default Enter key.
     *
     * @since BlackBerry 10.0.0
     */
    VIRTUALKEYBOARD_ENTER_DEFAULT   = 0,

    /**
     * Display "Go" on the Enter key.
     *
     * @since BlackBerry 10.0.0
     */
    VIRTUALKEYBOARD_ENTER_GO        = 1,

    /**
     * Display "Join" on the Enter key.
     *
     * @since BlackBerry 10.0.0
     */
    VIRTUALKEYBOARD_ENTER_JOIN      = 2,

    /**
     * Display "Next" on the Enter key.
     *
     * @since BlackBerry 10.0.0
     */
    VIRTUALKEYBOARD_ENTER_NEXT      = 3,

    /**
     * Display "Search" on the Enter key.
     *
     * @since BlackBerry 10.0.0
     */
    VIRTUALKEYBOARD_ENTER_SEARCH    = 4,

    /**
     * Display "Send" on the Enter key.
     *
     * @since BlackBerry 10.0.0
     */
    VIRTUALKEYBOARD_ENTER_SEND      = 5,

    /**
     * Display "Submit" on the Enter key.
     *
     * @since BlackBerry 10.0.0
     */
    VIRTUALKEYBOARD_ENTER_SUBMIT    = 6,

    /**
     * Display "Done" on the Enter key.
     *
     * @since BlackBerry 10.0.0
     */
    VIRTUALKEYBOARD_ENTER_DONE      = 7,

    /**
     * Display "Connect" on the Enter key.
     *
     * @since BlackBerry 10.0.0
     */
    VIRTUALKEYBOARD_ENTER_CONNECT   = 8,

    /**
     * Display "Replace" on the Enter key.
     *
     * @since BlackBerry 10.2.0
     */
    VIRTUALKEYBOARD_ENTER_REPLACE   = 9,
} virtualkeyboard_enter_t;

/**
 * @brief Display the virtual keyboard
 *
 * The @c virtualkeyboard_show() function causes the virtual keyboard to be
 * displayed (if it is not already visible).  When this function is called, the
 * @c VIRTUALKEYBOARD_EVENT_VISIBLE event is sent unless the virtual keyboard
 * was already visible.
 *
 * When the device is connected to a keyboard (e.g., via Bluetooth), the
 * virtual keyboard will not be shown unless the user swipes up with two fingers
 * from the bottom bezel. This also applies to the simulator, which interprets
 * the PC keyboard as being connected to the virtual device.
 *
 * Devices that have a built-in keyboard do not support the use of the virtual
 * keyboard. The virtual keyboard can't be displayed on such devices.
 *
 * @return Nothing.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API void virtualkeyboard_show();

/**
 * @brief Hide the virtual keyboard
 *
 * The @c virtualkeyboard_hide() function hides the virtual keyboard (if it is
 * not already hidden).  When this function is called, the
 * @c VIRTUALKEYBOARD_EVENT_HIDDEN event is sent unless the virtual keyboard was
 * already hidden.
 *
 * @return Nothing.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API void virtualkeyboard_hide();

/**
 * @brief Change the virtual keyboard layout, and Enter key options
 *
 * The @c virtualkeyboard_change_options() function changes the virtual keyboard
 * layout and Enter key options, using values that are defined in the
 * @c #virtualkeyboard_layout_t and @c #virtualkeyboard_enter_t enumerations.
 *
 * @param layout The virtual keyboard layout to set.
 * @param enter The Enter key text to set.
 *
 * @return Nothing.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API void virtualkeyboard_change_options(virtualkeyboard_layout_t layout, virtualkeyboard_enter_t enter);

/**
 * @brief Change the virtual keyboard layout, Enter key and help options
 *
 * See @c virtualkeyboard_change_options()
 * 
 * The @c virtualkeyboard_change_options_v2() function has the same
 * functionality as @c virtualkeyboard_change_options(). However, it also tells
 * the virtual keyboard not to show any hints if @c no_help is true. This allows
 * the user to focus on other elements on the screen. The hints are left on by
 * default if @c virtualkeyboard_change_options() is used.
 *  
 * @param layout The virtual keyboard layout to set.
 * @param enter The Enter key text to set.
 * @param no_help Turn off the hints if true.  Otherwise, turn on the hints.
 *
 * @return Nothing.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API void virtualkeyboard_change_options_v2(virtualkeyboard_layout_t layout, virtualkeyboard_enter_t enter, bool no_help);

/**
 * @brief Get the height of the virtual keyboard
 *
 * The @c virtualkeyboard_get_height() function gets the height of the virtual
 * keyboard.
 *
 * @param pixels The height of the virtual keyboard (in pixels).
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int virtualkeyboard_get_height(int *pixels);

/**
 * @brief Start receiving virtual keyboard events
 *
 * The @c virtualkeyboard_request_events() function starts to deliver virtual
 * keyboard events to the application using BPS.
 *
 * @param flags The types of events to deliver. A value of zero indicates that
 * all events are requested. The meaning of non-zero values is reserved for
 * future use.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int virtualkeyboard_request_events(int flags);

/**
 * @brief Stop receiving virtual keyboard events
 *
 * The @c virtualkeyboard_stop_events() function stops virtual keyboard events
 * from being delivered to the application using BPS.
 *
 * @param flags The types of events to stop. A value of zero indicates that all
 * events are stopped. The meaning of non-zero values is reserved for future
 * use.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int virtualkeyboard_stop_events(int flags);

/**
 * @brief Get the unique domain ID for the virtual keyboard service
 *
 * The @c virtualkeyboard_get_domain() function gets the unique domain ID for
 * the virtual keyboard service.  You can use this function in your application
 * to test whether an event that you retrieve using @c bps_get_event() is a
 * virtual keyboard event, and respond accordingly.
 *
 * @return The domain ID for the virtual keyboard service.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int virtualkeyboard_get_domain();

/**
 * @brief Get the virtual keyboard height
 *
 * The @c virtualkeyboard_event_get_height() function gets the keyboard height
 * from a @c VIRTUALKEYBOARD_EVENT_INFO event.  The keyboard height is dynamic
 * and varies depending on whether the device is in portrait or landscape mode.
 *
 * @param event The event to get the virtual keyboard height from.
 *
 * @return The virtual keyboard height (in pixels).
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int virtualkeyboard_event_get_height(bps_event_t *event);

__END_DECLS

#endif // include guard
