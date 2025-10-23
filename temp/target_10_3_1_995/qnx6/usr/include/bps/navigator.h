/*
 * Copyright (C) 2011-2014 BlackBerry Limited. All rights reserved.
 */

/**
 * @file navigator.h
 *
 * @brief Functions for communication with the navigator
 *
 * This file contains function definitions for receiving and sending messages to
 * the navigator. The navigator controls how applications appear on the device.
 * For example, application windows can occupy the full screen, be reduced to a
 * thumbnail image while a user scrolls through active applications, or be
 * invisible to the user. All of these states are reported by the navigator
 * service. The navigator also responds to events (such as swipe events), and
 * the navigator service allows your application to respond to these events.
 *
 * You can also use the navigator service to open files that are located locally
 * on the device, as well as open URIs that you specify (including URIs that
 * correspond to applications on the device), by calling the
 * @c navigator_invoke() function. For example, you can use the navigator
 * service to launch applications such as the browser, camera, calendar, and so
 * on.
 *
 * @since BlackBerry 10.0.0
 */

#ifndef _BPS_NAVIGATOR_H_INCLUDED
#define _BPS_NAVIGATOR_H_INCLUDED

#include <stdbool.h>
#include <sys/platform.h>
#include "bps/bps.h"

__BEGIN_DECLS

/**
 * @brief Event codes for navigator service events
 *
 * This enumeration defines the event codes for the types of events that the
 * navigator service may return. Note that a reply is expected when your
 * application receives a @c NAVIGATOR_ORIENTATION or @c
 * NAVIGATOR_ORIENTATION_CHECK event. See the @c
 * navigator_orientation_check_response() and @c navigator_done_orientation()
 * functions for more information.
 *
 * @anonenum bps_navigator_events Navigator events
 *
 * @since BlackBerry 10.0.0
 */
enum {
    /**
     * Indicates that the application is a registered URL handler, and the
     * navigator is invoking a URL type on the application. For example, a web
     * browser might need to handle an http invoke request from another
     * application, and load the website that is associated with the request.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_INVOKE                      = 0x01,

    /**
     * Indicates that the user has quit the application, the device is
     * rebooting, or some other event has occurred that results in the
     * application needing to terminate. After this type of event is received,
     * the application has a short amount of time (3 seconds) to terminate
     * itself. If the application has not terminated after this time has
     * elapsed, the navigator terminates the application.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_EXIT                        = 0x02,

    /**
     * Indicates that the state of the application window has changed. For
     * example, the application window might have changed to full screen from a
     * thumbnail. The @c #navigator_window_state_t enumeration defines the
     * possible states that an application window can be in.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_WINDOW_STATE                = 0x03,

    /**
     * Indicates that the user has performed a downward swipe gesture from the
     * top of the device screen. By convention, this gesture displays a menu.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_SWIPE_DOWN                  = 0x04,

    /**
     * Indicates that the user has started a swipe gesture. This type of event
     * is generated if the application has requested swipe start events by
     * calling @c navigator_request_swipe_start(). For example, if an
     * application calls @c navigator_request_swipe_start() and the user
     * performs a downward swipe gesture from the top of the device screen, the
     * application receives a @c NAVIGATOR_SWIPE_START event followed by a
     * series of touch events. This functionality can be useful if the
     * application wants to respond more appropriately to swipe gestures (for
     * example, by displaying the menu in sync with the user's downward swipe
     * gesture).
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_SWIPE_START                 = 0x05,

    /**
     * Indicates that the device is low on memory. To prevent degraded
     * performance and a potentially poor user experience, an application should
     * respond to this event by freeing any memory that it isn't using.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_LOW_MEMORY                  = 0x06,

    /**
     * Indicates that the device has rotated. An application should respond to
     * this event by calling @c navigator_orientation_check_response() and
     * indicating whether it intends to rotate along with the device rotation.
     * If the application indicates that it intends to rotate, the navigator
     * sends a follow-up @c NAVIGATOR_ORIENTATION event when it is time for the
     * application to resize its screen.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_ORIENTATION_CHECK           = 0x07,

    /**
     * Indicates that an application should resize its screen in response to the
     * rotation of the device. This event is generated if the application has
     * called @c navigator_orientation_check_response() and indicated that it
     * intends to rotate. After the application is finished resizing its screen,
     * the application should call @c navigator_done_orientation() to let the
     * navigator know that the application is finished rotating.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_ORIENTATION                 = 0x08,

    /**
     * Indicates that the user has performed a swipe gesture from the bottom
     * left of the device screen towards the top right.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_BACK                        = 0x09,

    /**
     * Indicates that the application window has become active (for example, if
     * the application window changes to full screen from being hidden).
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_WINDOW_ACTIVE               = 0x0a,

    /**
     * Indicates that the application window has become inactive (for example,
     * if the application window changes to hidden from being full screen).
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_WINDOW_INACTIVE             = 0x0b,

    /**
     * Indicates that the device has finished rotating.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_ORIENTATION_DONE            = 0x0c,

    /**
     * Indicates that a request to change the orientation with @c
     * navigator_set_orientation() has completed.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_ORIENTATION_RESULT          = 0x0d,

    /**
     * Indicates that the corporate or enterprise application is locked. When
     * locked, the window changes to a lock icon and cannot be used. To use the
     * window again, the user must unlock it by touching the window and then
     * typing a password.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_WINDOW_LOCK                 = 0x0e,

    /**
     * Indicates that the corporate or enterprise application is unlocked. When
     * an application is first launched, it is considered unlocked. No message
     * is sent when the application starts.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_WINDOW_UNLOCK               = 0x0f,

    /**
     * Indicates an invocation for the target was received. The application
     * should retrieve the invocation properties through the @c
     * navigator_invoke_event_get_invocation() function.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_INVOKE_TARGET               = 0x10,

    /**
     * Indicates an invocation query result was received. The application should
     * retrieve the invocation query result actions through the
     * @c navigator_invoke_event_get_query_result_action() and
     * @c navigator_invoke_event_get_query_result_action_count() functions.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_INVOKE_QUERY_RESULT         = 0x11,

    /**
     * Indicates a viewer invocation was received. The application should
     * retrieve the viewer invocation through the
     * @c navigator_invoke_event_get_viewer() function.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_INVOKE_VIEWER               = 0x12,

    /**
     * Indicates an invocation target response was received. The application
     * should retrieve the invocation ID through the
     * @c navigator_event_get_id() function and the error through the
     * @c navigator_event_get_err() function.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_INVOKE_TARGET_RESULT        = 0x13,

    /**
     * Indicates an invocation viewer response was received. The application
     * should retrieve the invocation viewer ID through the
     * @c navigator_event_get_id() function and the error through the
     * @c navigator_event_get_err() function.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_INVOKE_VIEWER_RESULT        = 0x14,

    /**
     * If the current process is the parent application of the viewer it
     * indicates that the request message from the viewer was received. If the
     * current process is the viewer it indicates that the request message from
     * the parent application was received. To retrieve the message name use the
     * @c navigator_invoke_event_get_viewer_relay_message_name() function. To
     * retrieve the data use the
     * @c navigator_invoke_event_get_viewer_relay_data() function. To retrieve
     * the window ID of the viewer use the
     * @c navigator_invoke_event_get_viewer_relay_window_id() function.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_INVOKE_VIEWER_RELAY         = 0x15,

    /**
     * Indicates that the invocation viewer has terminated. To retrieve the
     * window ID use the @c navigator_invoke_event_get_window_id() function.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_INVOKE_VIEWER_STOPPED       = 0x16,

    /**
     * Indicates that the the keyboard has changed state. The @c
     * #navigator_keyboard_state_t enumeration defines the possible states that
     * the keyboard can be in.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_KEYBOARD_STATE              = 0x17,

    /**
     * Indicates that the keyboard has changed position.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_KEYBOARD_POSITION           = 0x18,

    /**
     * If the current process is the parent application of the viewer it
     * indicates that the response message from the viewer was received. If the
     * current process is the viewer it indicates that the response message from
     * the parent application was received. In case of an error in delivering
     * the request message to the peer the event contains an error message. To
     * retrieve the error message use @c navigator_event_get_err() function.
     * If the error message is NULL in the event the following functions should
     * be used to retrieve the message name, the data and the window ID of the
     * viewer:
     * - @c navigator_invoke_event_get_viewer_relay_message_name()
     * - @c navigator_invoke_event_get_viewer_relay_data()
     * - @c navigator_invoke_event_get_viewer_relay_window_id()
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_INVOKE_VIEWER_RELAY_RESULT  = 0x19,

    /**
     * Indicates that the device has been locked or unlocked.
     * @c navigator_event_get_device_lock_state()
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_DEVICE_LOCK_STATE           = 0x1a,

    /**
     * Provide details about the window cover.  Occurs on application startup.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_WINDOW_COVER                = 0x1b,

    /**
     * Occurs when navigator displays the application's window cover.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_WINDOW_COVER_ENTER          = 0x1c,

    /**
     * Occurs when the navigator removes the application's window cover.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_WINDOW_COVER_EXIT           = 0x1d,

    /**
     * Indicates that the card peek action has started. Card peeking is the
     * ability to see behind a card using a gesture to drag the card off screen
     * to expose the card's parent or root.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_CARD_PEEK_STARTED           = 0x1e,

    /**
     * Indicates that the card peek action has stopped. Call the @c
     * navigator_event_get_card_peek_stopped_swipe_away function upon receiving
     * this event to determine if the peeking action was stopped due to a "swipe
     * away" gesture or not.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_CARD_PEEK_STOPPED           = 0x1f,

    /**
     * Indicates that the card application should resize its buffer and call the
     * @c navigator_card_resized() function when finished. When this event is
     * triggered, the Navigator delivers a message to the card containing the
     * resize data, which the card extracts and uses to execute the
     * transformation.
     *
     * The members contained in the message and the functions the card
     * application must use to retrive them are as follows:
     *     - @b Event @b ID: the ID of the message to identify the event
     *                     (@c navigator_event_get_id())
     *     - @b Width: the new width of the card
     *                     (@c navigator_event_get_card_width())
     *     - @b Height: the new height of the card
     *                     (@c navigator_event_get_card_height())
     *     - @b Device @b orientation @b type: the orientation of the device
     *                     (either portrait or landscape)
     *                     (@c navigator_event_get_card_orientation())
     *     - @b Card @b edge: the orientation of the card relative to the
     *                     device (@c navigator_event_get_card_edge())
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_CARD_RESIZE                 = 0x20,

    /**
     * Indicates to the parent of a card application that the child card has
     * been closed. When this event is triggered, the Navigator delivers a
     * message to the parent of the closed child card containing information
     * about the closure as well as any response data sent by the card (if the
     * card requested the closure).
     *
     * The members contained in the message and the functions the parent
     * application must use to retrieve them are as follows:
     *     - @b Reason: the reason why the child card closed
     *                    (@c navigator_event_get_card_closed_reason())
     *     - @b Data @b type: the MIME type of the data sent by the child card
     *                    (@c navigator_event_get_card_closed_data_type())
     *     - @b Data: the data sent by the child card
     *                    (@c navigator_event_get_card_closed_data())
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_CHILD_CARD_CLOSED           = 0x21,

    /**
     * Indicates that the card has been closed and is being pooled. Pooling is a
     * feature that allows a card of a certain type to be opened multiple times
     * in quick sucession, such as when viewing a series of emails one after the
     * other. This event informs the card that it should clean-up its state
     * and listen for further invocations. When a card receives the event it
     * should assume that its child card is also closed. A card may retrieve the
     * reason for its closure by calling the @c
     * navigator_event_get_card_closed_reason() function.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_CARD_CLOSED                 = 0x22,

    /**
     * Indicates a get invoke target filters result was received. The
     * application should retrieve the get invoke target filters result filters
     * through @c navigator_invoke_get_filters()
     * function.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_INVOKE_GET_FILTERS_RESULT   = 0x23,

    /**
     * Occurs when the Adaptive Partition Scheduler will move the application
     * to a different partition (background, foreground, or stopped).
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_APP_STATE                   = 0x24,

    /*
     * Indicates a set invoke target filters result was received. The
     * application should retrieve the ID through @c navigator_event_get_id()
     * function and any error message through @c navigator_event_get_err()
     * function.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_INVOKE_SET_FILTERS_RESULT   = 0x25,

    /**
     * Indicates that the peek action of this card has started. Card peeking
     * is the ability to see behind a card using a gesture to drag the card off
     * screen to expose the card's parent or root.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_PEEK_STARTED                = 0x26,

    /**
     * Indicates that the peek action of this card has stopped. Call the @c
     * navigator_event_get_peek_stopped_swipe_away function upon receiving
     * this event to determine if the peeking action was stopped due to a "swipe
     * away" gesture or not.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_PEEK_STOPPED                = 0x27,

    /**
     * Indicates that the Navigator is ready to display the card's window.
     * Call @c navigator_card_send_card_ready() to notify the navigator
     * when the card is ready to be shown.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_CARD_READY_CHECK            = 0x28,

    /**
     * Indicates that the navigator would like to pool your application or
     * card. Pooled means that the application is still running as a process but
     * its window is not visible to the user.
     *
     * If an application would like to be pooled it must reply to this message
     * by calling @c navigator_pooled_response() within 1 second. If there is no
     * response within 1 second, the application will be terminated. When
     * pooled, an application is also put into the stopped partition after 10
     * seconds. An application that supports pooling is responsible for closing
     * files, connections and resources and is also responsible for restoring
     * them when the the application gets the active signal again. This means
     * that an application has 10 seconds to prepare itself to sit dormant in
     * the pool.
     *
     * The application decides if it wants to return to the last state it was in
     * or to reset the state to something else. These decisions should be made
     * when the application receives the @c NAVIGATOR_POOLED event so that it's
     * ready to be displayed when it pulled from the pool later. Trying to
     * change scenes/render new graphics, etc., when the application is made
     * active again may result in flicker or stale data when the window is made
     * visible again. So it's best to put the application in its "restore" state
     * when it goes into the pool.
     *
     * If the application wants to be pooled, extract the ID from this event
     * with @c navigator_event_get_id() and then call @c
     * navigator_pooled_response() with that ID.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_POOLED                      = 0x29,

    /**
     * Informs the app what the rotated window's width and height will be.
     *
     * This event will occur after a @c NAVIGATOR_ORIENTATION_CHECK event and
     * before a @c NAVIGATOR_ORIENTATION event.  It will indicate what the
     * window size will be after the rotation is completed.  For the vast
     * majority of apps, the width and height will simply be swapped from the
     * current width and height.
     *
     * Use @c navigator_event_get_orientation_size_width() and @c
     * navigator_event_get_orientation_size_height() to extract the width and
     * height from the event.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_ORIENTATION_SIZE            = 0x2a,

    /**
     * Informs the app that the cursor of an invoke list is being moved
     *
     * This event will occur after a @c NAVIGATOR_CARD_PEEK_STARTED event and
     * before a @c NAVIGATOR_CARD_PEEK_STOPPED or
     * @c NAVIGATOR_INVOKE_LIST_ITEM_SELECTED event. It will indicate that
     * the application should select the next available item in the invoke list
     * as a candidate for the next invoke request.
     *
     * Use @c navigator_invoke_get_list_id() to extract the id of the list
     * that this request corresponds to, and
     * @c navigator_invoke_get_list_cursor_direction() to extract the direction
     * of movement.
     *
     * @since BlackBerry 10.2.0
     */
    NAVIGATOR_INVOKE_LIST_CURSOR_MOVED    = 0x2b,

    /**
     * Informs the app that an invoke list item has been selected
     *
     * This event may occur after a @c NAVIGATOR_CARD_PEEK_STARTED event and
     * before a @c NAVIGATOR_CARD_PEEK_STOPPED event.  It will indicate that
     * the application should invoke the currently selected invoke item
     * belonging to the list in question based on previous
     * @c NAVIGATOR_INVOKE_LIST_CURSOR_MOVED events. In these instances,
     * @c navigator_invoke_get_list_item_selection() returns
     * @c NAVIGATOR_INVOKE_LIST_CURSOR_DIRECTION_UNSPECIFIED.
     *
     * This event may also occur outside of peeking, in which case
     * @c navigator_invoke_get_list_item_selection() returns the item that
     * should be selected.
     *
     * Use @c navigator_invoke_get_list_id() to extract the list ID of the list
     * that this request corresponds to, and
     * @c navigator_invoke_get_list_item_selection() to extract the direction of
     * movement.
     *
     * @since BlackBerry 10.2.0
     */
    NAVIGATOR_INVOKE_LIST_ITEM_SELECTED   = 0x2c,

    /**
     * Indicates a timer registration result was received. The application
     * should retrieve the registration action through the
     * @c navigator_invoke_timer_registration_get_action() function and the
     * action error code through the @c navigator_event_get_err() function.
     *
     * @since BlackBerry 10.3.0
     */
    NAVIGATOR_INVOKE_TIMER_REGISTRATION   = 0x2d,

    /**
     * Indicates the user pressed a system key.  The application should
     * indicate whether it will handle the key press by calling the
     * @c navigator_syskey_press_response() function as soon as possible.
     *
     * @since BlackBerry 10.3.1
     */
    NAVIGATOR_SYSKEY_PRESS                = 0x2e,

    /**
     * Indicates that the event is not any of the above event types.  It could
     * be a custom event.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_OTHER                       = 0xff
};

/**
 * @brief Navigator window states
 *
 * This enumeration defines the different states that an application window can
 * be in.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * The application occupies the full display and should be operating
     * normally.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_WINDOW_FULLSCREEN   = 0,

    /**
     * The application is reduced to a thumbnail as the user switches
     * applications.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_WINDOW_THUMBNAIL    = 1,

    /**
     * The application is no longer visible to the user, for any reason.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_WINDOW_INVISIBLE    = 2
} navigator_window_state_t;

/**
 * @brief The different run partitions an application can be placed into.
 *
 * This enumeration defines the different run partitions that an application
 * can be placed into.  Use @c navigator_event_get_app_state() to retrieve the
 * @c #navigator_app_state_t from a @c NAVIGATOR_APP_STATE event.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * The application is placed into the foreground partition.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_APP_FOREGROUND      = 0,

    /**
     * The application is placed into the background partition.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_APP_BACKGROUND      = 1,

    /**
     * The application will shortly be placed into the stopped partition.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_APP_STOPPING        = 2
} navigator_app_state_t;

/**
 * @brief Extended data enabling
 *
 * This enumeration defines whether extended data is enabled when events are
 * requested by the @c navigator_request_events() function.
 *
 * @anonenum bps_navigator_extendeddata Navigator extended data
 *
 * @since BlackBerry 10.0.0
 */
enum {
    /**
     * Enables extended data.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_EXTENDED_DATA           = 0x01

};

/**
 * @brief Navigator card peeking types
 *
 * This enumeration defines the type of peek that is executed when a card peek
 * action is called. Peeking is the ability to see behind a card using a gesture
 * to drag the card off screen and expose the card's parent or root (depending
 * on the type of peek action). This determines if the peek applies to only
 * the single parent of the card or to the entire stack.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * Indicates that the peek action is to the bottom of the card stack. The
     * root of the selected card is revealed.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_PEEK_ROOT             = 0,

    /**
     * Indicates that the peek action is to the previous card. The parent of the
     * selected card is revealed.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_PEEK_PARENT         = 1
} navigator_peek_type_t;

/**
 * @brief Screen orientation modes
 *
 * This enumeration defines the different orientation modes that the screen of
 * the device can be in.
 *
 * @anonenum bps_navigator_orientation_screen Navigator screen orientation
 *
 * @since BlackBerry 10.0.0
 */
enum {
    /**
     * Indicates that the screen is in landscape mode (the longer sides of the
     * device are positioned at the bottom and top while the shorter sides are
     * on the sides).
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_LANDSCAPE             = 0,

    /**
     * Indicates that the screen is in portrait mode. (the shorter sides of the
     * device are positioned at the bottom and top while the longer sides are
     * on the sides).
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_PORTRAIT              = 1
};

/**
 * @brief Application orientations
 *
 * This enumeration defines the different orentations that the application can
 * be in relative to the screen of the device.
 *
 * @anonenum bps_navigator_orientation_application Navigator application
 *           orientation
 *
 * @since BlackBerry 10.0.0
 */
enum {
    /**
     * Indicate that the "top" edge of the application is facing up on the
     * screen (the application appears to be correctly oriented).
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_TOP_UP                = 0,

    /**
     * Indicate that the "right" edge of the application is facing up on the
     * screen (the application appears to be lying on its left side).
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_RIGHT_UP              = 90,

    /**
     * Indicate that the "bottom" edge of the application is facing up on the
     * screen (the application appears to be upside-down).
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_BOTTOM_UP             = 180,

    /**
     * Indicate that the "left" edge of the application is facing up on the
     * screen (the application appears to be lying on its right side).
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_LEFT_UP               = 270
};

/**
 * @brief Keyboard state
 *
 * This enumeration defines the different states the keyboard can be in.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * Indicates that the keyboard is in an unrecognized state (not one of the
     * states below).
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_KEYBOARD_UNRECOGNIZED = 0,

    /**
     * Indicates that the keyboard is opening.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_KEYBOARD_OPENING      = 1,

    /**
     * Indicates that the keyboard is opened.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_KEYBOARD_OPENED       = 2,

    /**
     * Indicates that the keyboard is closing.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_KEYBOARD_CLOSING      = 3,

    /**
     * Indicates that the keyboard is closed.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_KEYBOARD_CLOSED       = 4,
} navigator_keyboard_state_t;

/**
 * @brief Navigator window and icon badges
 *
 * This enumeration defines the different badges that can be applied to an
 * application window and icon.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * Indicates that the badge is a splat. A splat appears as a white star in a
     * red circle.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_BADGE_SPLAT = 0
} navigator_badge_t;

/**
 * @brief Device lock states
 *
 * This enumeration defines the different lock states that a device can be in.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * The device is unlocked.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_DEVICE_LOCK_STATE_UNLOCKED            = 0,

    /**
     * The device is locked.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_DEVICE_LOCK_STATE_SCREEN_LOCKED       = 1,

    /**
     * The device is locked, and a password is required to unlock.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_DEVICE_LOCK_STATE_PASSWORD_LOCKED     = 2,
} navigator_device_lock_state_t;

/**
 * @brief Window cover transitions
 *
 * This enumeration defines the different transition effects that a window can
 * perform when drawing the cover.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * Use the default effect when drawing the cover.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_WINDOW_COVER_TRANSITION_DEFAULT   = 0,

    /**
     * Don't use a transition effect when drawing the cover.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_WINDOW_COVER_TRANSITION_NONE      = 1,

    /**
     * Use a slide effect when drawing the cover.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_WINDOW_COVER_TRANSITION_SLIDE     = 2,

    /**
     * Use a fade effect when drawing the cover.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_WINDOW_COVER_TRANSITION_FADE      = 3,
} navigator_window_cover_transition_t;

/**
 * @brief Navigator system keys
 *
 * This enumeration defines the different system keys. Not all system keys
 * are available on every device; some devices have no system keys. Note
 * that the 'Menu' key is not a system key. For documentation on the 'Menu' key
 * and the trackpad, please see the API documentation for the Screen library.
 *
 * @since BlackBerry 10.3.1
 */
typedef enum {
    /**
     * The 'Send' system key.
     *
     * @since BlackBerry 10.3.1
     */
    NAVIGATOR_SYSKEY_SEND = 0,
    /**
     * The 'End' system key.
     *
     * @since BlackBerry 10.3.1
     */
    NAVIGATOR_SYSKEY_END  = 1,
    /**
     * The 'Back' system key.
     *
     * @since BlackBerry 10.3.1
     */
    NAVIGATOR_SYSKEY_BACK = 2
} navigator_syskey_t;

/**
 * @brief The window cover image attribute structure
 *
 * Handle to a @c #navigator_window_cover_attribute_t struct which is used for
 * updating the window cover image.
 *
 * @since BlackBerry 10.0.0
 */
typedef struct navigator_window_cover_attribute_t navigator_window_cover_attribute_t;

/**
 * @brief The window cover text attribute structure
 *
 * Handle to a @c #navigator_window_cover_label_t struct which is used for
 * updating window cover text.
 *
 * @since BlackBerry 10.0.0
 */
typedef struct navigator_window_cover_label_t navigator_window_cover_label_t;


/**
 * @brief Start receiving navigator events
 *
 * The @c navigator_request_events() function starts to deliver navigator events
 * to your application using BPS. Events will be posted to the currently
 * active channel.
 *
 * @param flags The types of events to deliver. A value of zero indicates that
 * all regular events are requested. A value of @c NAVIGATOR_EXTENDED_DATA
 * indicates all regular events are requested with extended data being
 * available and @c navigator_raw_write() being able to send data.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_request_events(int flags);

/**
 * @brief Stop receiving navigator events
 *
 * The @c navigator_stop_events() function stops navigator events from being
 * delivered to the application using BPS.
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
BPS_API int navigator_stop_events(int flags);

/**
 * @brief Get the unique domain ID for the navigator service
 *
 * The @c navigator_get_domain() function gets the unique domain ID for the
 * navigator service. You can use this function in your application to test
 * whether an event that you retrieve using @c bps_get_event() is a navigator
 * event, and respond accordingly.
 *
 * @return The domain ID for the navigator service.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_get_domain();

/**
 * @brief Deprecated: Use the invocation framework APIs instead
 *
 * @deprecated The use of @c navigator_invoke() has been deprecated in
 * BlackBerry 10. Use the invocation framework APIs from navigator_invoke.h
 * instead.
 *
 * The @c navigator_invoke() function sends a navigator invoke request to
 * display the contents of the specified URI in the navigator.
 *
 * When you specify an application URI, the URI also indicates the context that
 * you want to open the application in. For example, to open the camera app, you
 * can call @c navigator_invoke() with an argument of @c camera://
 *
 * The following sections list the application URIs that you can use when you
 * call @c navigator_invoke(). @e Note: Spaces or line breaks have been
 * inserted in the URIs before the & in query strings for readability purposes
 * and should not be passed into @c navigator_invoke().
 *
 * <b>BlackBerry World</b>
 * - <tt>appworld://myworld</tt> - Opens BlackBerry World storefront and loads
 *   the My World screen
 * - <tt>appworld://content/12345</tt> - Opens BlackBerry World and loads
 *   the Application Details screen for the content with content ID 12345. This
 *   is the preferred format to invoke BlackBerry World content
 * - <tt>appworld://search/s=<em>searchterm</em></tt> - Searches BlackBerry
 *   World and returns all items that match <em>searchterm</em>, organized by
 *   category
 *
 * <b>Browser</b>
 * - <tt>http</tt><tt>://<em>URL</em></tt> - Opens the browser and displays the
 *   content at the specified URL
 * - <tt>https</tt><tt>://<em>URL</em></tt> - Opens the browser and displays the
 *   content at the specified URL
 *
 * <b>Camera</b>
 * - <tt>camera://</tt> - Opens the camera in the last mode used
 *
 * <b>Calendar</b>
 * - <tt>calendar://</tt> - Opens the calendar
 * - <tt>calendar://showEvent?accountId=<em>account_ID</em>
 *   &eventId=<em>event_ID</em></tt> - Opens the calendar and displays the event
 *   with the specified event ID
 * - <tt>calendar://editEvent?accountId=<em>account_ID</em>
 *   &eventId=<em>event_ID</em></tt> - Opens the calendar and displays the edit
 *   screen for the event with the specified event ID
 * - <tt>calendar://newEvent?accountId=<em>account_ID</em>
 *   &dateStart=<em>YYYY-MM-DD HH:MM:SS</em>
 *   &dateEnd=<em>YYYY-MM-DD HH:MM:SS</em>
 *   &attd=<em>comma_delimited_list_of_email_addresses</em>
 *   &subj=<em>subject</em>
 *   &loc=<em>location</em>
 *   &body=<em>body_of_message</em></tt> - Opens the calendar and displays the
 *   new event screen with the specified event properties (for example, start
 *   date, end date, and so on) pre-populated. All properties are optional and
 *   must be URL encoded
 *
 * <b>Maps</b>
 * - <tt>maps://</tt> - Opens BlackBerry Maps and displays the current location
 *
 * <b>Music</b>
 * - <tt>music://albums</tt> - Opens the music application and displays the
 *   Albums screen
 * - <tt>music://artists</tt> - Opens the music application and displays the
 *   Artists screen
 * - <tt>music://file_URL</tt> - Opens the music application and plays the
 *   specified file
 * - <tt>music://genres</tt> - Opens the music application and displays the
 *   Genres screen
 * - <tt>music://playlists</tt> - Opens the music application and displays the
 *   Playlists screen
 * - <tt>music://songs</tt> - Opens the music application and displays the All
 *   Songs screen
 *
 * <b>Photos</b>
 * - <tt>photos://</tt> - Opens the pictures application in the default view
 *
 * <b>Videos</b>
 * - <tt>videos://library</tt> - Opens the videos application and displays the
 *   Library tab
 * - <tt>videos://recorded</tt> - Opens the videos application and displays the
 *   Recorded Videos tab
 * - <tt>videos://<em>file_URL</em></tt> - Opens the videos application and
 *   plays the specified file
 *
 * <b>Settings</b>
 * - <tt>settings://about</tt> - Displays the About screen
 * - <tt>settings://wifi</tt> - Displays the Wi-Fi screen
 * - <tt>settings://softwareupdate</tt> - Displays the Software Updates screen
 * - <tt>settings://bluetooth</tt> - Displays the Bluetooth screen
 * - <tt>settings://tethering</tt> - Displays the Internet Tethering screen
 * - <tt>settings://sound</tt> - Displays the Sounds screen
 * - <tt>settings://storage</tt> - Displays the Storage and Access screen
 * - <tt>settings://sharing</tt> - Displays the Media Sharing screen
 * - <tt>settings://security</tt> - Displays the Security screen
 * - <tt>settings://language</tt> - Displays the Language and Input screen
 * - <tt>settings://language/keyboard</tt> - Displays the Keyboard screen
 * - <tt>settings://datetime</tt> - Displays the Date and Time screen
 * - <tt>settings://pim</tt> - Displays the PIM Account screen
 * - <tt>settings://pim/listAccounts</tt> - Displays the PIM Account screen
 * - <tt>settings://pim/defaultAccounts</tt> - Displays the PIM Default Accounts
 *                                             screen
 * - <tt>settings://pim/createAccount</tt> - Displays the PIM New Account screen
 * - <tt>settings://pim/showAccount?id=<em>account_ID</em></tt> - Displays the
 *   PIM Edit Account screen for the specified account ID (e.g., jim@email.com)
 *
 * @param url The URI to invoke.
 * @param err If this function fails, and if @c err is not null, it will be set
 * to a short description of the error. The caller must free this buffer using
 * @c bps_free().
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE upon failure with a short
 * description of the error in @c err.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke(const char *url, char **err);

/**
 * @brief Deprecated: Use the invocation framework APIs instead
 *
 * @deprecated The use of @c navigator_open_file() has been deprecated in
 * BlackBerry 10. Use the invocation framework APIs from navigator_invoke.h
 * instead.
 *
 * The @c navigator_open_file() function sends a navigator openFile request to
 * open the specified file in the navigator.
 *
 * @param filepath The path of the file to open.
 * @param err If this function fails, and if @c err is not null, it will be set
 * to a short description of the error. The caller must free this buffer using
 * @c bps_free().
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE upon failure with a short
 * description of the error in @c err.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_open_file(const char *filepath, char **err);


/**
 * @brief Create a navigator icon that, when launched, invokes the corresponding
 * application based on the URI value
 *
 * The @c navigator_add_uri() function creates an icon in one of the navigator
 * trays that, when launched, starts an application based on the value of @c
 * url.
 *
 * @param icon_path         The path to the icon image.
 * @param icon_label        The label to apply to the icon image.
 * @param default_category  The navigator tray that the icon should appear in.
 * @param url               The URI of the application to launch.
 * @param err               If this function fails, and if @c err is not NULL,
 *                          it will be set to a short description of the error.
 *                          The caller must free this buffer using @c
 *                          bps_free().
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE upon failure with a short
 * description of the error in @c err.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_add_uri(const char *icon_path, const char *icon_label, const char *default_category, const char *url, char **err);

/**
 * @brief Extend the time allowed for the application to create its application
 * window at application start
 *
 * The @c navigator_extend_timeout() function sends a navigator extendTimeout
 * request to extend the time allowed for the application to create its
 * application window at application start. Normally, the application gets 30
 * seconds to create its application window. If the application is unable to
 * create windows in this time frame due to initialization or loading issues, it
 * must request an extension to the normal timeout, otherwise it will be
 * terminated.
 *
 * @param extension The total time in milliseconds that the application expects
 * to need before it can create its application window.
 * @param err If this function fails, and if @c err is not null, it will be set
 * to a short description of the error. The caller must free this buffer using
 * @c bps_free().
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE upon failure with a short
 * description of the error in @c err.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_extend_timeout(int extension, char **err);

/**
 * @brief Extend the time allowed for the application to exit before it is
 * forcibly terminated
 *
 * The @c navigator_extend_terminate() function sends a navigator
 * extendTerminate request to extend the time allowed for the application to
 * exit before it is forcibly terminated. Normally, the application gets 3
 * seconds after receiving a @c NAVIGATOR_EXIT message to exit properly. If the
 * application requires more than this amount of time, it should call this
 * function to get additional time. Each time this function is called, the
 * application will receive another 2 seconds before it is terminated. This
 * function can be called in a loop during the exit cleanup procedure to prevent
 * premature termination. It allows the application to save its state properly.
 *
 * Note that @c navigator_extend_terminate() can only be used to delay
 * termination for up to 30 seconds, after which the application will be
 * terminated.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_extend_terminate(void);

/**
 * @brief Send a navigator SWIPE_START request
 *
 * The @c navigator_request_swipe_start() function sends a navigator SWIPE_START
 * request. The navigator will send SWIPE_START events instead of SWIPE_DOWN
 * events.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_request_swipe_start();

/**
 * @brief Stop the navigator from sending SWIPE_START events
 *
 * The @c navigator_stop_swipe_start() function stops the navigator from sending
 * SWIPE_START events. The navigator will return to sending SWIPE_DOWN events.
 * (see @c navigator_request_swipe_start())
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_stop_swipe_start();

/**
 * @brief Specify the orientation of your application as locked or not locked
 *
 * The @c navigator_rotation_lock() function specifies to the navigator whether
 * your application's orientation is locked or not locked.
 *
 * @param locked If @c true the orientation of your application is locked, if @c
 * false the orientation of your application is not locked.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_rotation_lock(bool locked);

/**
 * @brief Set the orientation in the navigator based on angle
 *
 * The @c navigator_set_orientation() function sends a navigator orientation
 * request to set the orientation in the navigator.
 *
 * @param angle The angle of the orientation to set: @c NAVIGATOR_TOP_UP,
 * @c NAVIGATOR_RIGHT_UP, @c NAVIGATOR_LEFT_UP, @c NAVIGATOR_BOTTOM_UP.
 * @param id If not null, the ID used in the orientation request will be
 * returned in @c id. The caller must free this buffer using @c bps_free().
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_set_orientation(int angle, char **id);

/**
 * @brief Set the orientation in the navigator based on landscape or portrait
 *
 * The @c navigator_set_orientation_mode() function sends a navigator
 * orientation request to set the orientation in the navigator to the chosen
 * mode (@c NAVIGATOR_LANDSCAPE, or @c NAVIGATOR_PORTRAIT).
 *
 * @param mode @c NAVIGATOR_LANDSCAPE, @c NAVIGATOR_PORTRAIT.
 * @param id If not null, the ID used in the orientation request will be
 * returned in @c id. The caller must free this buffer using @c bps_free().
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_set_orientation_mode(int mode, char **id);

/**
 * @brief Set the window angle in the navigator
 *
 * The @c navigator_set_window_angle() function sends a navigator windowAngle
 * request to set the angle of the application window in the navigator. When
 * using this function, it is expected that the application does its rotation
 * internally. In this case, the application should maintain a @c
 * SCREEN_PROPERTY_ROTATION value of 0, do its rotations internally, and report
 * back the angle of rotation to the navigator so that it remains in sync.
 *
 * @param angle The angle of the window to set.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_set_window_angle(int angle);

/**
 * @brief Set the rotation effect in the navigator
 *
 * The @c navigator_rotation_effect() function enables or disables the system's
 * standard rotation effect when the application is rotated.  When set to false,
 * the device rotation will occur instantly and the application will need to
 * provide its own rotation animation if desired.  The application starts with
 * the rotation effect enabled.
 *
 * @param effect If @c true the rotation effect is enabled; if @c false the
 * rotation effect is disabled.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_rotation_effect(bool effect);

/**
 * @brief Set the close prompt in the navigator
 *
 * The @c navigator_set_close_prompt() function sends a navigator closePrompt
 * request to set the contents of the close prompt dialog. This function allows
 * an application to prevent the user from closing the application without
 * warning. If the user tries to close the application, a dialog will be
 * displayed with the title and message specified. The user will have 2 buttons:
 * "Cancel" and "Close". If the user selects Close, the application will receive
 * an "exit" message. If the user selects Cancel, the dialog will close and the
 * application will continue running. This function can be called as many times
 * as needed if the application's state changes.
 *
 * Neither @c title nor @c message support the use of commas (,) or quotes (").
 * Inserting either of these characters may make it impossible to close your
 * application using the Navigator.
 *
 * @param title The title of the close prompt dialog to set.
 * @param message The message of the close prompt dialog to set.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_set_close_prompt(const char *title, const char *message);

/**
 * @brief Clear the close prompt in the navigator
 *
 * The @c navigator_clear_close_prompt() function sends a navigator closePrompt
 * request to clear the contents of the close prompt dialog. If the close
 * prompt dialog has been cleared, no close prompt dialog will appear when the
 * user tries to close the application. (see @c navigator_set_close_prompt())
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_clear_close_prompt();

/**
 * @brief Set a badge on the application's icon and window frame in the
 * navigator
 *
 * The @c navigator_set_badge() function sends a navigator addBadge request to
 * place a badge on the application's icon and window frame in the navigator.
 *
 * @param badge The badge to set.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_set_badge(navigator_badge_t badge);

/**
 * @brief Clears a badge from the application's icon and window frame in the
 * navigator
 *
 * The @c navigator_clear_badge() function sends a navigator removeBadge request
 * to remove a badge from the application's icon and window frame in the
 * navigator. (see @c navigator_set_badge())
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_clear_badge();

/**
 * @brief Turns keyboard tracking on or off.
 *
 * The @c navigator_set_keyboard_tracking() function turns keyboard tracking on
 * or off. When keyboard tracking is on, the application will receive
 * additional @c NAVIGATOR_KEYBOARD_POSITION events as the keyboard is sliding.
 * These additional events are only sent if the application is currently
 * full-screen.
 *
 * @param track Whether to turn tracking on or off.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_set_keyboard_tracking(bool track);

/**
 * @brief Get the severity of a NAVIGATOR_LOW_MEMORY event
 *
 * The @c navigator_event_get_severity() function extracts the current
 * severity from a @c NAVIGATOR_LOW_MEMORY event.
 *
 * @param event The @c NAVIGATOR_LOW_MEMORY event to extract the severity
 * from.
 *
 * @return The severity (increasing amounts indicates a higher level of
 * severity) from the event.  BPS_FAILURE if the severity cannot be retrieved
 * from the given event.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_event_get_severity(bps_event_t *event);

/**
 * @brief Get the current window state from an event
 *
 * The @c navigator_event_get_window_state() function extracts the current
 * window state from a @c NAVIGATOR_WINDOW_STATE event.
 *
 * @param event The @c NAVIGATOR_WINDOW_STATE event to extract the window state
 * from.
 *
 * @return The window state from the event.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API navigator_window_state_t navigator_event_get_window_state(bps_event_t *event);

/**
 * @brief Get the group ID from an event
 *
 * The @c navigator_event_get_groupid() function extracts the group ID from a @c
 * NAVIGATOR_WINDOW_STATE, @c NAVIGATOR_WINDOW_ACTIVE, or @c
 * NAVIGATOR_WINDOW_INACTIVE event.
 *
 * @param event The @c NAVIGATOR_WINDOW_STATE, @c NAVIGATOR_WINDOW_ACTIVE, or @c
 * NAVIGATOR_WINDOW_INACTIVE event to extract the group ID from.
 *
 * @return The group ID from the event.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char *navigator_event_get_groupid(bps_event_t *event);

/**
 * @brief Get the orientation angle from a navigator event
 *
 * The @c navigator_event_get_orientation_angle() function extracts the
 * orientation angle from a @c NAVIGATOR_ORIENTATION, @c
 * NAVIGATOR_ORIENTATION_CHECK, @c NAVIGATOR_ORIENTATION_DONE, or @c
 * NAVIGATOR_ORIENTATION_RESULT event.
 *
 * @param event The @c NAVIGATOR_ORIENTATION, @c NAVIGATOR_ORIENTATION_CHECK, @c
 * NAVIGATOR_ORIENTATION_DONE, or @c NAVIGATOR_ORIENTATION_RESULT event to
 * extract the orientation angle from.
 *
 * @return The orientation angle from the event.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_event_get_orientation_angle(bps_event_t *event);

/**
 * @brief Get the orientation mode from a navigator event
 *
 * The @c navigator_event_get_orientation_mode() functions extracts the
 * orientation mode from a @c NAVIGATOR_ORIENTATION, or @c
 * NAVIGATOR_ORIENTATION_CHECK event. The result is one of @c
 * NAVIGATOR_LANDSCAPE or @c NAVIGATOR_PORTRAIT.
 *
 * @param event The @c NAVIGATOR_ORIENTATION, or @c NAVIGATOR_ORIENTATION_CHECK
 * event.
 *
 * @return @c NAVIGATOR_LANDSCAPE, or @c NAVIGATOR_PORTRAIT
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_event_get_orientation_mode(bps_event_t *event);

/**
 * @brief Get the width from a navigator orientation size event
 *
 * The @c navigator_event_get_orientation_size_width() function extracts
 * the width from a @c NAVIGATOR_ORIENTATION_SIZE event.
 *
 * @param event The @c NAVIGATOR_ORIENTATION_SIZE event.
 *
 * @return The width of the window after rotation, in pixels.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_event_get_orientation_size_width(bps_event_t *event);

/**
 * @brief Get the height from a navigator orientation size event
 *
 * The @c navigator_event_get_orientation_size_height() function extracts
 * the height from a @c NAVIGATOR_ORIENTATION_SIZE event.
 *
 * @param event The @c NAVIGATOR_ORIENTATION_SIZE event.
 *
 * @return The height of the window after rotation, in pixels.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_event_get_orientation_size_height(bps_event_t *event);

/**
 * @brief Get the keyboard state from a navigator event
 *
 * The @c navigator_event_get_keyboard_state() function extracts the keyboard
 * state from a @c NAVIGATOR_KEYBOARD_STATE event. The result is one of the
 * values of the @c #navigator_keyboard_state_t enum.
 *
 * @param event The @c NAVIGATOR_KEYBOARD_STATE event.
 *
 * @return The state of the keyboard or @c BPS_FAILURE if there was an error.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_event_get_keyboard_state(bps_event_t *event);

/**
 * @brief Get the keyboard position from a navigator event
 *
 * The @c navigator_event_get_keyboard_position() function extracts the keyboard
 * position from a @c NAVIGATOR_KEYBOARD_POSITION event. The keyboard position
 * is the y offset in pixels of the top of the keyboard.
 *
 * @param event The @c NAVIGATOR_KEYBOARD_POSITION event.
 *
 * @return The y offset in pixels of the top of the keyboard or @c BPS_FAILURE
 * if there was an error.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_event_get_keyboard_position(bps_event_t *event);

/**
 * @brief Get the height of the window cover
 *
 * The function @c navigator_event_get_window_cover_height() extracts the
 * height of the window cover from a @c NAVIGATOR_WINDOW_COVER event.
 *
 * @param event The @c NAVIGATOR_WINDOW_COVER event.
 * @return On success, the height of the window cover. Otherwise, @c
 * BPS_FAILURE with errno set.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_event_get_window_cover_height(bps_event_t *event);

/**
 * @brief Get the width of the window cover
 *
 * The function @c navigator_event_get_window_cover_width() extract the width
 * of the window cover from a @c NAVIGATOR_WINDOW_COVER event.
 *
 * @param event The @c NAVIGATOR_WINDOW_COVER event.
 * @return On success, the width of the window cover. Otherwise, @c
 * BPS_FAILURE with errno set.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_event_get_window_cover_width(bps_event_t *event);

/**
 * @brief Get the data from a navigator invoke event
 *
 * The @c navigator_event_get_data() function extracts the data from a @c
 * NAVIGATOR_INVOKE event.
 *
 * @param event The @c NAVIGATOR_INVOKE event to extract the data from.
 *
 * @return The data field from the event.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char *navigator_event_get_data(bps_event_t *event);

/**
 * @brief Get the ID from a navigator event
 *
 * The @c navigator_event_get_id() function extracts the ID from the
 * following events:
 * - @c NAVIGATOR_ORIENTATION
 * - @c NAVIGATOR_ORIENTATION_CHECK
 * - @c NAVIGATOR_ORIENTATION_RESULT
 * - @c NAVIGATOR_INVOKE_TARGET_RESULT
 * - @c NAVIGATOR_INVOKE_QUERY_RESULT
 * - @c NAVIGATOR_INVOKE_VIEWER_RESULT
 * - @c NAVIGATOR_INVOKE_VIEWER_RELAY
 * - @c NAVIGATOR_INVOKE_VIEWER_RELAY_RESULT
 * - @c NAVIGATOR_INVOKE_GET_FILTERS_RESULT
 * - @c NAVIGATOR_INVOKE_SET_FILTERS_RESULT
 * - @c NAVIGATOR_POOLED
 * - @c NAVIGATOR_INVOKE_TIMER_REGISTRATION
 *
 * @param event The event to extract the ID from.
 *
 * @return The ID field from the event.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char *navigator_event_get_id(bps_event_t *event);

/**
 * @brief Get the error message from a navigator event
 *
 * The @c navigator_event_get_err() function extracts the error message from the
 * the following events:
 * - @c NAVIGATOR_ORIENTATION_RESULT
 * - @c NAVIGATOR_INVOKE_TARGET_RESULT
 * - @c NAVIGATOR_INVOKE_QUERY_RESULT
 * - @c NAVIGATOR_INVOKE_VIEWER_RESULT
 * - @c NAVIGATOR_INVOKE_VIEWER_RELAY_RESULT
 * - @c NAVIGATOR_INVOKE_GET_FILTERS_RESULT
 * - @c NAVIGATOR_INVOKE_SET_FILTERS_RESULT
 * - @c NAVIGATOR_INVOKE_TIMER_REGISTRATION
 *
 * @param event The event to extract the error message from.
 *
 * @return The error message from the event, or @c NULL if there is no
 * error message.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char *navigator_event_get_err(bps_event_t *event);

/**
 * @brief Specify whether your application intends to rotate
 *
 * The @c navigator_orientation_check_response() function specifies to the
 * navigator whether or not your application intends to rotate. If you respond
 * with @c true (that your application intends to rotate) then the navigator
 * will send you a follow-up @c NAVIGATOR_ORIENTATION event when it is time for
 * your application to resize its screen.
 *
 * @param event The @c NAVIGATOR_ORIENTATION_CHECK event.
 * @param will_rotate If @c true your application intends to rotate, if @c false
 * your application does not intend to rotate.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API void navigator_orientation_check_response(bps_event_t *event, bool will_rotate);

/**
 * @brief Specify whether your application intends to rotate
 *
 * The @c navigator_orientation_check_response_id() function specifies to the
 * navigator whether or not your application intends to rotate. If you respond
 * with @c true (that your application intends to rotate) then the navigator
 * will send you a follow-up @c NAVIGATOR_ORIENTATION event when it is time for
 * your application to resize its screen.
 *
 * This function provides an alternative to the
 * @c navigator_orientation_check_response() function, which requires the
 * @c NAVIGATOR_ORIENTATION_CHECK event to be passed in. In the case where the
 * @c NAVIGATOR_ORIENTATION_CHECK event will no longer be available to be passed
 * in, the @c id can be retrieved from it, stored, and used in this function.
 *
 * @param id The ID, as retrieved from the @c NAVIGATOR_ORIENTATION_CHECK event
 * using @c navigator_event_get_id().
 * @param will_rotate If @c true your application intends to rotate, if @c false
 * your application does not intend to rotate.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_orientation_check_response_id(const char *id, bool will_rotate);

/**
 * @brief Indicate that your application is finished rotating
 *
 * The @c navigator_done_orientation() function indicates to the navigator that
 * your application is finished rotating. After receiving a @c
 * NAVIGATOR_ORIENTATION event, and after your application has resized its
 * screen, this function lets the navigator know that you are finished your
 * rotation.
 *
 * @param event The original @c NAVIGATOR_ORIENTATION event.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API void navigator_done_orientation(bps_event_t *event);

/**
 * @brief Indicate that your application is finished rotating
 *
 * The @c navigator_done_orientation_id() function indicates to the navigator
 * that your application is finished rotating. After receiving a @c
 * NAVIGATOR_ORIENTATION event, and after your application has resized its
 * screen, this function lets the navigator know that you are finished your
 * rotation.
 *
 * This function provides an alternative to the @c navigator_done_orientation()
 * function, which requires the @c NAVIGATOR_ORIENTATION event to be
 * passed in. In the case where the @c NAVIGATOR_ORIENTATION event will no
 * longer be available to be passed in, the @c id can be retrieved from it,
 * stored, and used in this function.
 *
 * @param id The ID, as retrieved from the original @c NAVIGATOR_ORIENTATION
 * event using @c navigator_event_get_id().
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_done_orientation_id(const char *id);

/**
 * @brief Inform navigator that the app wishes to exit
 *
 * An application should call this function when it is ready to terminate.
 * The application should then wait until it receives a @c NAVIGATOR_EXIT
 * event before shutting down.
 *
 * @return @c BPS_SUCCESS upon succes, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_close_window(void);

/**
 * @brief Indicate that your application wants to be pooled
 *
 * The @c navigator_pooled_response() function indicates to the navigator that
 * your application wants to be pooled.
 *
 * @param id The ID, as retrieved from the @c NAVIGATOR_POOLED event using @c
 * navigator_event_get_id().
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_pooled_response(const char *id);

/**
 * @brief Query the navigator to determine the lock state
 *
 * An application can call this function to determine if the device is
 * currently @c NAVIGATOR_DEVICE_LOCK_STATE_UNLOCKED, @c
 * NAVIGATOR_DEVICE_LOCK_STATE_SCREEN_LOCKED, or @c
 * NAVIGATOR_DEVICE_LOCK_STATE_PASSWORD_LOCKED. An application can also
 * monitor @c NAVIGATOR_DEVICE_LOCK_STATE events.
 *
 * @return On success, one of @c NAVIGATOR_DEVICE_LOCK_STATE_UNLOCKED, @c
 * NAVIGATOR_DEVICE_LOCK_STATE_SCREEN_LOCKED, or @c
 * NAVIGATOR_DEVICE_LOCK_STATE_PASSWORD_LOCKED. Otherwise, return @c
 * BPS_FAILURE with errno set.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_get_device_lock_state(void);

/**
 * @brief Sends data to the navigator service
 *
 * The data will only be sent if @c navigator_request_events() was called
 * with @c NAVIGATOR_EXTENDED_DATA.
 *
 * @param data The data to be sent.
 * @param length The length of the data.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_raw_write(const char * data, unsigned int length);

/**
 * @brief Gets extended data from the event if it is available
 *
 * @param event The original event.
 *
 * @return A buffer of extended data, @c NULL if no data was available and
 * with @c errno set if there was some other error. The BPS library holds
 * ownership of the returned buffer and will destroy it upon destruction
 * of the event.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char * navigator_event_get_extended_data(bps_event_t *event);

/**
 * @brief Gets the extended data's length from the event if it is available
 *
 * @param event The original event.
 *
 * @return The number of bytes of extended data that is available, 0 if no
 * data is available. Note that if you wish to allocate a buffer and copy
 * the extended data with a null terminator, you should add 1 to the
 * value returned.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API unsigned int navigator_event_get_extended_data_length(bps_event_t *event);

/**
 * @brief Get the device lock state from a @c NAVIGATOR_DEVICE_LOCK_STATE
 * event.
 *
 * @param event A @c NAVIGATOR_DEVICE_LOCK_STATE event
 * @return On success, one of @c #navigator_device_lock_state_t, otherwise @c
 * BPS_FAILURE with errno set.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_event_get_device_lock_state(bps_event_t *event);

/**
 * @brief Get the app state from a NAVIGATOR_APP_STATE event.
 *
 * This function can be called when a @c NAVIGATOR_APP_STATE event occurs.  The
 * result tells the caller which run partition the application is in (for the
 * case of @c NAVIGATOR_APP_BACKGROUND, or @c NAVIGATOR_APP_FOREGROUND) or which
 * partititon the application will be put into shortly (in the case of
 * @c NAVIGATOR_APP_STOPPING).
 *
 * @param event The @c NAVIGATOR_APP_STATE event.
 * @return One of @c navigator_app_state_t, or @c BPS_FAILURE with errno set.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_event_get_app_state(bps_event_t *event);

/**
 * @brief Create a navigator window cover attribute
 *
 * Create a handle to be used with @c navigator_window_cover_update().
 *
 * @param attribute To be filled with the attribute handle
 * @return On success returns @c BPS_SUCCESS with the attribute set.
 * Otherwise, @c BPS_FAILURE with errno set.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_window_cover_attribute_create(navigator_window_cover_attribute_t **attribute);

/**
 * @brief Destroy a window cover attribute handle
 *
 * The attribute handle is not needed after a call to @c
 * navigator_window_cover_update() so it can be safely destroyed. If any label
 * handles exist, they should be destroyed by calling @c
 * navigator_window_cover_label_destroy() before calling this function.
 *
 * @param attribute The window cover attribute handle.
 * @return On success, @c BPS_SUCCESS. On failure, @c BPS_FAILURE with errno set
 *         and attribute will still be valid.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_window_cover_attribute_destroy(navigator_window_cover_attribute_t *attribute);

/**
 * @brief Set the window cover to live
 *
 * There are 4 modes for covers. Live, file, capture, or alternate window.
 * If live is set, file and capture attributes are disabled. Note, special
 * permission is required to be able to set the window cover to live.
 *
 * @param attribute The window cover attribute handle.
 * @return On success, return @c BPS_SUCCESS. Otherwise, @c BPS_FAILURE with
 *         errno set, and the attribute will not be changed.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_window_cover_attribute_set_live(navigator_window_cover_attribute_t *attribute);

/**
 * @brief Set the window cover to use an alternate window
 *
 * There are 4 modes for covers. Live, file, capture, or alternate window.
 * If alternate window is set, capture and file path attributes are discarded.
 * The alternate window is specified by using the
 * SCREEN_PROPERTY_ALTERNATE_WINDOW property.
 *
 * @param attribute The window cover attribute handle.
 * @return On success, return @c BPS_SUCCESS. Otherwise, @c BPS_FAILURE with
 *         errno set, and the attribute will not be changed.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_window_cover_attribute_set_alternate_window(navigator_window_cover_attribute_t *attribute);

/**
 * @brief Set the window cover image using a file
 *
 * There are 4 modes for covers: live, file, capture, or alternate window. If
 * an image file is being used, live and capture will be disabled.
 *
 * @param attribute The window cover attribute handle.
 * @param file Path to an image file that will be used as the cover.
 * @return On success return @c BPS_SUCCESS. Otherwise, return @c BPS_FAILURE
 *         with errno set, the file will not be changed.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_window_cover_attribute_set_file(navigator_window_cover_attribute_t *attribute, const char *file);

/**
 * @brief Set the window cover capture size
 *
 * There are 4 modes for covers: live, file, capture, or alternate window. If
 * a capture is being used, live and image file will be disabled. When using a
 * capture, the portion of the screen to use is provided by x, y, width, and
 * height parameters. Navigator will scale the image appropriately if it
 * doesn't correspond to the proper window cover width and height.
 *
 * @param attribute The window cover attribute handle.
 * @param x The X-axis origin
 * @param y The Y-axis origin
 * @param width The capture width
 * @param height The capture height
 * @return On success, @c BPS_SUCCESS. Otherwise, @c BPS_FAILURE with errno set,
 *         and attribute will be unchanged.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_window_cover_attribute_set_capture(navigator_window_cover_attribute_t *attribute, int x, int y, int width, int height);

/**
 * @brief Set whether badges will be allowed on the window cover
 *
 * Choose whether to allow badges on the window cover.
 *
 * @param attribute The window cover attribute handle.
 * @param is_allowed True if badges are to be allowed. False if no badges are
 * allowed.
 * @return On success, @c BPS_SUCCESS. Otherwise, @c BPS_FAILURE with errno set,
 *         and the attribute will be unchanged.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_window_cover_attribute_set_allow_badges(navigator_window_cover_attribute_t *attribute, bool is_allowed);


/**
 * @brief Set the type of transition to use when displaying a new window cover
 *
 * Determines which transition to use when displaying a new window cover. The
 * transition will only occur when an application already has a window cover
 * being displayed, and it is being replaced by this new window cover. The new
 * cover is displayed on a call to @c navigator_window_cover_update().
 *
 * @param attribute The window cover attribute handle.
 * @param transition One of @c navigator_window_cover_transition_t. The
 * transition is applied when the existing cover is updated with this cover
 * through @c navigator_window_cover_update().
 * @return On success, @c BPS_SUCCESS. Otherwise, @c BPS_FAILURE with errno set,
 *         and the attribute will be unchanged.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_window_cover_attribute_set_transition(navigator_window_cover_attribute_t *attribute, int transition);

/**
 * @brief Add a label to the window cover
 *
 * Add a label to the window cover. This function will set a handle to the
 * newly added label. With the label handle, the user can change various label
 * settings.
 *
 * @param attribute The window cover attribute handle.
 * @param text The text for the label.
 * @param label The window cover label handle.
 * @return On success, @c BPS_SUCCESS. Otherwise, @c BPS_FAILURE with errno set,
 *         the attribute will be unchanged, and the label will be invalid.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_window_cover_attribute_add_label(navigator_window_cover_attribute_t *attribute, const char *text, navigator_window_cover_label_t **label);

/**
 * @brief Destroy the window cover label handle
 *
 * Destroys the label handle that was created by @c
 * navigator_window_cover_attribute_add_label()
 *
 * @param label The window cover label handle.
 * @return On success, @c BPS_SUCCESS. Otherwise, @c BPS_FAILURE with errno set,
 *         and label will still be valid.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_window_cover_label_destroy(navigator_window_cover_label_t *label);

/**
 * @brief Set the label text color
 *
 * Sets the color to use for the label text.
 *
 * @param label The window cover label handle.
 * @param red Red color component.
 * @param green Green color component.
 * @param blue Blue color component.
 * @return On success, @c BPS_SUCCESS. Otherwise, @c BPS_FAILURE with errno set
 *         and the label will not be changed.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_window_cover_label_set_color(navigator_window_cover_label_t *label, uint8_t red, uint8_t green, uint8_t blue);

/**
 * @brief Set the label text
 *
 * Changes the text for the label.
 *
 * @param label The window cover label handle.
 * @param text The window cover text to use.
 * @return On success, @c BPS_SUCCESS. Otherwise, @c BPS_FAILURE with errno set,
 *         and the label will remain unchanged.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_window_cover_label_set_text(navigator_window_cover_label_t *label, const char *text);

/**
 * @brief Set the size of the label's text
 *
 * Set the font size for the label's text. Must be a value larger than 0.
 *
 * @param label The window cover label handle.
 * @param size The size of the text.
 * @return On success, @c BPS_SUCCESS. Otherwise, @c BPS_FAILURE with errno set,
 *         and the label will remain unchanged.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_window_cover_label_set_size(navigator_window_cover_label_t *label, int size);

/**
 * @brief Set whether text will wrap
 *
 * If true, long text will wrap. If false, long text will be truncated.
 *
 * @param label The window cover label handle.
 * @param wrap_text True for text to wrap. False for text not to wrap.
 * @return On success, @c BPS_SUCCESS. Otherwise, @c BPS_FAILURE with errno set,
 *         and the label will remain unchanged.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_window_cover_label_set_wrap_text(navigator_window_cover_label_t *label, bool wrap_text);

/**
 * @brief Update the window cover used by the navigator
 *
 * When a @c NAVIGATOR_WINDOW_COVER_ENTER event occurs the app has a window
 * cover being displayed. By default, this is a scaled down version of the
 * application's screen. An application can call this function to change
 * what is used for the app's window cover.
 *
 * @param attribute A window cover attribute handle.
 * @return On success, @c BPS_SUCCESS. Otherwise, @c BPS_FAILURE with errno set
 *         and the window cover will not be changed.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_window_cover_update(navigator_window_cover_attribute_t *attribute);

/**
 * @brief Reset the window cover to the system default
 *
 * This will reset the window to the system default. Any changes that were
 * applied using calls to navigator_window_cover_update() will be reset.
 *
 * @return On success, @c BPS_SUCCESS. Otherwise, @c BPS_FAILURE with errno
 * set and the window cover will not be reset.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_window_cover_reset(void);

/**
 * @brief Request the Navigator to perform the card peek action
 *
 * The @c navigator_card_peek() function sends a request to the Navigator to
 * perform a card peek action of a given type. Peeking is the ability to see
 * behind a card using a gesture to drag the card off screen and expose the
 * card's parent or root (depending on the type of peek action). Call this
 * function from the card application to trigger a @c
 * NAVIGATOR_CARD_PEEK_STARTED event.
 *
 * @param peek_type The type of peek to perform. The choices are @c
 *                  NAVIGATOR_PEEK_ROOT to peek to the bottom root of the card
 *                  stack or @c NAVIGATOR_PEEK_PARENT to peek to only the
 *                  parent of the selected card.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_card_peek(navigator_peek_type_t peek_type);

/**
 * @brief Request the Navigator to notify the card when its window is ready
 *
 * The @c navigator_card_request_card_ready_check() function sends a request
 * to the Navigator so that when the navigator is ready to show the card's
 * window, e.g., after being brought back from pooling, it will send a
 * @c NAVIGATOR_CARD_READY_CHECK event. This allows the card to delay its
 * window being shown until it sends a @c navigator_card_send_card_ready()
 * message.
 *
 * Note that the Navigator will show the window after some timeout regardless
 * of whether @c navigator_card_send_card_ready() is called.
 *
 * The request can be made at any time during the card's lifecycle, and applies to
 * all subsequent times that the card's window is shown. If requesting for the
 * first run of the card, this request must proceed the posting of a window.
 *
 * @param check Whether to be notified by navigator before the card's window
 *              is shown.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_card_request_card_ready_check(bool check);

/**
 * @brief Notify the Navigator to display the card's window
 *
 * The @c navigator_card_send_card_ready() function notifies the navigator
 * that the card is ready to be shown. If this function is called without
 * first requesting for Navigator to notify the card when its window is about
 * to be shown (via @c navigator_card_request_card_ready_check()), then the
 * behaviour is undefined.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_card_send_card_ready(void);

/**
 * @brief Retrieve the type of the card peek action
 *
 * The @c navigator_event_get_card_peek_type() function retrieves the type of
 * peek action that a card stack should perform. The choices are @c
 * NAVIGATOR_PEEK_ROOT to peek to the bottom root of the card stack or @c
 * NAVIGATOR_PEEK_PARENT to peek to only the parent of the selected card. Call
 * this function from the card application upon receiving the @c
 * NAVIGATOR_CARD_PEEK_STARTED event to extract the peek type.
 *
 * @param event The @c NAVIGATOR_CARD_PEEK_STARTED event.
 *
 * @return The peek type upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_event_get_card_peek_type(bps_event_t* event);

/**
 * @brief Retrieve the type of the peek action initiated on this card
 *
 * The @c navigator_event_get_peek_type() function retrieves the type of
 * peek action intiated on this card's stack. The choices are @c
 * NAVIGATOR_PEEK_ROOT to peek to the bottom root of the card stack or @c
 * NAVIGATOR_PEEK_PARENT to peek to only the parent of the selected card. Call
 * this function from the card application upon receiving the @c
 * NAVIGATOR_PEEK_STARTED event to extract the peek type.
 *
 * @param event The @c NAVIGATOR_PEEK_STARTED event.
 *
 * @return The peek type upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_event_get_peek_type(bps_event_t* event);

/**
 * @brief Retrieve whether a card peek stopped due to a swipe away gesture
 *
 * The @c navigator_event_get_card_peek_stopped_swipe_away() function determines
 * whether a card peek action stopped due to the user swiping away the card to
 * navigate to the content being peeked at, or whether the card peek action
 * stopped due to the user returning the card to the stack, resuming the
 * activity on the current card. Call this function from the card application
 * upon receiving the @c NAVIGATOR_CARD_PEEK_STOPPED event to extract the
 * manner in which the peek was stopped.
 *
 * @param event The @c NAVIGATOR_CARD_PEEK_STOPPED event.
 * @param is_swipe_away If @c true the card peek action stopped due to a swipe
 *                      away gesture, if @c false the card peek was stopped
 *                      normally.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_event_get_card_peek_stopped_swipe_away(bps_event_t* event, bool* is_swipe_away);

/**
 * @brief Retrieve whether this card's peek stopped due to a swipe away gesture
 *
 * The @c navigator_event_get_peek_stopped_swipe_away() function determines
 * whether a peek action of this card stopped due to the user swiping away the card
 * to navigate to the content being peeked at, or whether the peek action of this
 * card stopped due to the user returning the card to the stack, resuming the
 * activity on the current card. Call this function from the card application
 * upon receiving the @c NAVIGATOR_PEEK_STOPPED event to extract the
 * manner in which the peek was stopped.
 *
 * @param event The @c NAVIGATOR_PEEK_STOPPED event.
 * @param is_swipe_away If @c true the peek action of the card stopped due to a
 *                      swipe away gesture, if @c false the card peek was stopped
 *                      normally.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_event_get_peek_stopped_swipe_away(bps_event_t* event, bool* is_swipe_away);

/**
 * @brief Retrieve the card width from the card resize event
 *
 * The @c navigator_event_get_card_width() function retrieves the width of a
 * card that has been targeted by a card resize event. Call this function from
 * the card application upon receiving the @c NAVIGATOR_CARD_RESIZE event to
 * extract the card's width.
 *
 * @param event The @c NAVIGATOR_CARD_RESIZE event.
 *
 * @return The card width upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_event_get_card_width(bps_event_t* event);

/**
 * @brief Retrieve the card height from the card resize event
 *
 * The @c navigator_event_get_card_height() function retrieves the height of a
 * card that has been targeted by a card resize event. Call this function from
 * the card application upon receiving the @c NAVIGATOR_CARD_RESIZE event to
 * extract the card's height.
 *
 * @param event The @c NAVIGATOR_CARD_RESIZE event.
 *
 * @return The card height upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_event_get_card_height(bps_event_t* event);

/**
 * @brief Retrieve the card edge type from the card resize event
 *
 * The @c navigator_event_get_card_edge() function retrieves the edge type of a
 * card that has been targeted by a card resize event. Call this function from
 * the card application upon receiving the @c NAVIGATOR_CARD_RESIZE event to
 * extract the card's edge type. The possible return values are:
 *     - @c NAVIGATOR_TOP_UP
 *     - @c NAVIGATOR_BOTTOM_UP
 *     - @c NAVIGATOR_LEFT_UP
 *     - @c NAVIGATOR_RIGHT_UP
 *
 * @param event The @c NAVIGATOR_CARD_RESIZE event.
 *
 * @return The card edge type upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_event_get_card_edge(bps_event_t* event);

/**
 * @brief Retrieve the orientation type from the card resize event
 *
 * The @c navigator_event_get_card_orientation() function retrieves the
 * resize type of a card that has been targeted by a card resize event. Call
 * this function from the card application upon receiving the @c
 * NAVIGATOR_CARD_RESIZE event to extract the card's resize type. The possible
 * return values are:
 *     - @c NAVIGATOR_PORTRAIT
 *     - @c NAVIGATOR_LANDSCAPE
 *
 * @param event The @c NAVIGATOR_CARD_RESIZE event.
 *
 * @return The card resize type upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_event_get_card_orientation(bps_event_t* event);

/**
 * @brief Close the card
 *
 * The @c navigator_card_close() function sends a request to the Navigator to
 * perform a card close action, along with response data to return to the
 * parent. Call this function from the card application to close the card and
 * have the Navigator notify the parent with a @c NAVIGATOR_CHILD_CARD_CLOSED
 * event. The closed card may also be pooled instead for later use, at which
 * point the Navigator will send a @c NAVIGATOR_CARD_CLOSED event to the card
 * application.
 *
 * @param reason The application level description of why the card was closed.
 *               The @c reason member can be NULL.
 * @param type The type and encoding of the closed card's response data. The @c
 *             type member can't be NULL if the @c data member isn't NULL.
 * @param data The data being returned to the parent from the closed card. The
 *             @c data member can be NULL.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_card_close(const char *reason, const char *type,
        const char *data);

/**
 * @brief Retrieve the reason for a card closure
 *
 * The @c navigator_event_get_card_closed_reason() function extracts the reason
 * for which a card has been closed using the @c navigator_card_close()
 * function. Call this function in the application upon receiving a @c
 * NAVIGATOR_CHILD_CARD_CLOSED event to identify why the child card was closed,
 * or upon receiving a @c NAVIGATOR_CARD_CLOSED event to identify why the card
 * itself was closed. This function doesn't copy data and the returned value is
 * released once the @c bps_get_event() function is called again.
 *
 * @param event The @c NAVIGATOR_CHILD_CARD_CLOSED or @c NAVIGATOR_CARD_CLOSED
 *              event that informed the application of the card closure.
 *
 * @return The reason why the card was closed upon success, NULL with @c errno
 *         set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_event_get_card_closed_reason(bps_event_t *event);

/**
 * @brief Retrieve the type of data passed by the child card upon closure
 *
 * The @c navigator_event_get_card_closed_data_type() function extracts the type
 * of data sent by the child card upon calling the @c navigator_card_close()
 * function. Call this function in the parent application upon receiving a @c
 * NAVIGATOR_CHILD_CARD_CLOSED event to identify the type of data in the child
 * card's response message. This function doesn't copy data and the returned
 * value is released once the @c bps_get_event() function is called again.
 *
 * @param event The @c NAVIGATOR_CHILD_CARD_CLOSED event that informed the
 *              parent application of the child card closure.
 *
 * @return The type of the data passed from the child card upon success, NULL
 *         with @c errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_event_get_card_closed_data_type(
        bps_event_t *event);

/**
 * @brief Retrieve the data passed by the child card upon closure
 *
 * The @c navigator_event_get_card_closed_data() function extracts the data sent
 * by the child card upon calling the @c navigator_card_close() function. Call
 * this function in the parent application upon receiving a @c
 * NAVIGATOR_CHILD_CARD_CLOSED event to retrieve the data in the child card's
 * response message. This function doesn't copy data and the returned value is
 * released once the @c bps_get_event() function is called again.
 *
 * @param event The @c NAVIGATOR_CHILD_CARD_CLOSED event that informed the
 *              parent application of the child card closure.
 *
 * @return The data passed from the child card upon success, NULL with @c errno
 *         set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_event_get_card_closed_data(bps_event_t *event);

/**
 * @brief Close the card
 *
 * The @c navigator_card_close_child() function sends a request to the Navigator
 * to perform a card close action on the child card of the application. Call
 * this function from the parent application to close the child card and have
 * the Navigator notify the child with a @c NAVIGATOR_CARD_CLOSED event.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_card_close_child(void);

/**
 * @brief Inform the Navigator that the card has been resized
 *
 * The @c navigator_card_resized() function sends a notification to the
 * Navigator to indicate that the given card application has resized its screen
 * buffer.
 *
 * @param id The ID retrieved from the @c NAVIGATOR_CARD_RESIZE event
 *           corresponding to the card resize instance.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_card_resized(const char *id);

/**
 * @brief Inform the Navigator that a swipe away gesture has been performed
 *
 * The @c navigator_card_swipe_away() function sends a notification to the
 * Navigator to indicate that the given card application has detected a "swipe
 * away" gesture (performed by swiping from the card application outwards). This
 * informs the Navigator that it should dismiss the application (by means of a
 * transition out past the left side of the screen). This function is exclusive
 * to the BlackBerry Hub.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_card_swipe_away(void);

/**
 * @brief Change the device's wallpaper
 *
 * Set the device's wallpaper using the image file provided in filepath.
 *
 * @param filepath Path to an image file that will be used as the wallpaper.
 * @return On success return @c BPS_SUCCESS.  Otherwise, return @c BPS_FAILURE
 *         with errno set, the wallpaper will not be changed.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_set_wallpaper(const char *filepath);

/**
 * @brief Change the device's lockscreen wallpaper
 *
 * Set the device's lockscreen wallpaper using the image file provided in
 * filepath.
 *
 * @param filepath Path to an image file that will be used as the lockscreen
 *                 wallpaper.
 *
 * @return On success return @c BPS_SUCCESS.  Otherwise, return @c BPS_FAILURE
 *         with errno set, the lockscreen wallpaper will not be changed.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API int navigator_set_lockscreen_wallpaper(const char *filepath);

/**
 * @brief Get the system key from a navigator system key event
 *
 * The @c navigator_event_get_syskey_key() function extracts the system
 * key from a @c #NAVIGATOR_SYSKEY_PRESS event.
 *
 * @param event The @c #NAVIGATOR_SYSKEY_PRESS event to extract the
 *              system key from.
 *
 * @return The system key from the event. Otherwise, return @c BPS_FAILURE with
 *         @c errno set.
 *
 * @since BlackBerry 10.3.1
 */
BPS_API int navigator_event_get_syskey_key(bps_event_t *event);

/**
 * @brief Get the system key id from a navigator system key event
 *
 * The @c navigator_event_get_syskey_id() function extracts the id from
 * a @c #NAVIGATOR_SYSKEY_PRESS event.  This is the id that should be
 * passed into @c navigator_syskey_press_response() which should be called as
 * soon as possible after receiving the @c #NAVIGATOR_SYSKEY_PRESS event.
 * This function does not copy data and the returned value is
 * released once the @c bps_get_event() function is called again.
 *
 * @param event The @c #NAVIGATOR_SYSKEY_PRESS event to extract the
                system key id from.
 *
 * @return The system key id from the event. Otherwise, return NULL
 *         with @c errno set.
 *
 * @since BlackBerry 10.3.1
 */
BPS_API const char * navigator_event_get_syskey_id(bps_event_t *event);

/**
 * @brief Indicate whether the app handles a system key event
 *
 * This function should be called in response to receiving a
 * @c #NAVIGATOR_SYSKEY_PRESS event to indicate whether the app will handle
 * that event. This should be called as soon as possible to avoid delays and
 * performance issues.
 *
 * @param id this is the id that was returned in the @ #NAVIGATOR_SYSKEY_PRESS
 *           event.
 * @param will_handle If @c true, your app will handle the
 *                    @c #NAVIGATOR_SYSKEY_PRESS event. If @c false, your app
 *                    will not handle the @c #NAVIGATOR_SYSKEY_PRESS event.
 *
 * @return @c BPS_SUCCESS upon success. Otherwise, this function returns
 *         @c BPS_FAILURE.
 *
 * @since BlackBerry 10.3.1
 */
BPS_API int navigator_syskey_press_response(const char *id, bool will_handle);

__END_DECLS

#endif // include guard
