/*
 * Copyright (C) 2011-2014 BlackBerry Limited. All rights reserved.
 */

/**
 *
 * @file dialog.h
 *
 * @brief Functions and structures to manipulate dialog windows
 *
 * This file defines the dialog service, which provides an API to create,
 * configure, display, update, and cancel dialog windows.
 *
 * @section dialog_usage_sec Dialog Usage
 *
 * Before you can use the dialog service to show dialogs, you must create a
 * window group. You create a window group by calling @c screen_create_window(),
 * followed by calling @c screen_create_window_group(). Both functions are
 * declared in screen/screen.h. @c screen_create_window_group() should be called
 * immediately after @c screen_create_window(), and before any other screen
 * functions are called. You do not need to provide the dialog service
 * with the window group's ID - the window group must simply exist before you
 * attempt to display dialogs.
 *
 * In general, to display a dialog, use the following steps:
 *
 * - Create a specific type of dialog using the appropriate dialog creation
 *   function.
 *
 * - Customize the dialog by setting its attributes.
 *
 * - Display the dialog.
 *
 * - Clean up dialog resources.
 *
 * For example, to create, customize, and display an alert dialog:
 *
 * @code
 *   dialog_instance_t dialog = 0;
 *   dialog_create_alert(&dialog);
 *   dialog_set_alert_message_text(dialog, "Here's a message...");
 *
 *   dialog_set_group_id(dialog, "yourWindowId");
 *
 *   dialog_add_button(dialog, "CANCEL", true, NULL, true);
 *   dialog_add_button(dialog, "OK", true, NULL, true);
 *   dialog_show(dialog);
 * @endcode
 *
 * To decode the response from a dialog:
 *
 * @code
 *   dialog_instance_t dialog = dialog_event_get_dialog_instance(event);
 *   int selected_index = dialog_event_get_selected_index(event);
 *   const char *label = dialog_event_get_selected_label(event);
 * @endcode
 *
 * To clean up dialog resources:
 *
 * @code
 *   dialog_destroy(dialog);
 * @endcode
 *
 *
 * @since BlackBerry 10.0.0
 */

#ifndef _BPS_DIALOG_H_INCLUDED
#define _BPS_DIALOG_H_INCLUDED

#include <sys/platform.h>
#include <sys/types.h>
#include <stdbool.h>

#include "bps/bps.h"

__BEGIN_DECLS

/**
 * @brief The available dialog events
 *
 * This enumeration defines the available dialog events. Currently, there is
 * only one event.
 *
 * @anonenum bps_dialog_events Dialog events
 *
 * @since BlackBerry 10.0.0
 */
enum {
/**
 * The single dialog event. This event is generated when the user presses a
 * button on a dialog. It contains information about which button was
 * pressed, along with information that is specific to the type of dialog.
 *
 * @since BlackBerry 10.0.0
 */
   DIALOG_RESPONSE = 0x01,
};

/**
 * @brief The available input flags for dialogs.
 *
 * This enumeration defines the available options on input fields for dialogs.
 * These values may be combined through a bitwise-OR operation to enable
 * multiple input options.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * Specify that input will not be changed.
     *
     * @since BlackBerry 10.0.0
     */
    DIALOG_INPUT_NONE            = 0,
    /**
     * Specify that input will be capitalized automatically.
     *
     * @since BlackBerry 10.0.0
     */
    DIALOG_INPUT_AUTO_CAPITALIZE = 1,
    /**
     * Specify that input will be corrected automatically.
     *
     * @since BlackBerry 10.0.0
     */
    DIALOG_INPUT_AUTO_CORRECT    = 1 << 1,
    /**
     * Specify that input will be checked for spelling errors.
     *
     * @since BlackBerry 10.0.0
     */
    DIALOG_INPUT_SPELL_CHECK     = 1 << 2,
} dialog_input_flags_t;

/**
 * @brief The available toast dialog positions
 *
 * This enumeration defines the available positions at which a toast dialog can
 * be displayed on the screen. The default display position for a dialog is @c
 * DIALOG_POSITION_MIDDLE_CENTER, unless otherwise specified for each type of
 * dialog.
 *
 * Specifying the position for non-toast dialogs is deprecated.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * Specify that the toast will appear centered near the top of the screen.
     *
     * @since BlackBerry 10.0.0
     */
    DIALOG_POSITION_TOP_CENTER     = 0,
    /**
     * Specify that the toast will appear centered in the middle of the screen.
     *
     * @since BlackBerry 10.0.0
     */
    DIALOG_POSITION_MIDDLE_CENTER  = 1,
    /**
     * Specify that the toast will appear centered near the bottom of the
     * screen.
     *
     * @since BlackBerry 10.0.0
     */
    DIALOG_POSITION_BOTTOM_CENTER  = 2
} dialog_position_t;

/**
 * @brief The pre-defined icons for context menus
 *
 * This enumeration defines a list of icons that can be displayed on a context
 * menu button.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * The cut icon.
     *
     * @since BlackBerry 10.0.0
     */
    DIALOG_CUT_ICON = 0,
    /**
     * The copy icon.
     *
     * @since BlackBerry 10.0.0
     */
    DIALOG_COPY_ICON = 1,
    /**
     * The paste icon.
     *
     * @since BlackBerry 10.0.0
     */
    DIALOG_PASTE_ICON = 2,
    /**
     * The delete icon.
     *
     * @since BlackBerry 10.0.0
     */
    DIALOG_DELETE_ICON = 3,
    /**
     * The select icon.
     *
     * @since BlackBerry 10.0.0
     */
    DIALOG_SELECT_ICON = 4,
    /**
     * The cancel icon.
     *
     * @since BlackBerry 10.0.0
     */
    DIALOG_CANCEL_ICON = 5,
    /**
     * The view image icon.
     *
     * @since BlackBerry 10.0.0
     */
    DIALOG_VIEW_IMAGE_ICON = 6,
    /**
     * The save image icon.
     *
     * @since BlackBerry 10.0.0
     */
    DIALOG_SAVE_IMAGE_ICON = 7,
    /**
     * The save link as icon.
     *
     * @since BlackBerry 10.0.0
     */
    DIALOG_SAVE_LINK_AS_ICON = 8,
    /**
     * The open link in new tab icon.
     *
     * @since BlackBerry 10.0.0
     */
    DIALOG_OPEN_LINK_NEW_TAB_ICON = 9,
    /**
     * The open link icon.
     *
     * @since BlackBerry 10.0.0
     */
    DIALOG_OPEN_LINK_ICON = 10,
    /**
     * The copy link icon.
     *
     * @since BlackBerry 10.0.0
     */
    DIALOG_COPY_LINK_ICON = 11,
    /**
     * The copy image link icon.
     *
     * @since BlackBerry 10.0.0
     */
    DIALOG_COPY_IMAGE_LINK_ICON = 12,
    /**
     * The clear field icon.
     *
     * @since BlackBerry 10.0.0
     */
    DIALOG_CLEAR_FIELD_ICON = 13,
    /**
     * The cancel selection icon.
     *
     * @since BlackBerry 10.0.0
     */
    DIALOG_CANCEL_SELECTION_ICON = 14,
    /**
     * The bookmark icon.
     *
     * @since BlackBerry 10.0.0
     */
    DIALOG_BOOKMARK_ICON = 15,
    /**
     * No icon.
     *
     * @since BlackBerry 10.0.0
     */
    DIALOG_NO_ICON = 16,
    /**
     * Keep the previously specified icon.
     *
     * @since BlackBerry 10.0.0
     */
    DIALOG_KEEP_ICON = 17
} dialog_context_menu_icon_t;

/**
 * @brief The state of progress in progress dialogs and toasts
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * Specify that progress is on-going.
     *
     * @since BlackBerry 10.0.0
     */
    DIALOG_PROGRESS_PLAY = 0,
    /**
     * Specify that progress has been paused.
     *
     * @since BlackBerry 10.0.0
     */
    DIALOG_PROGRESS_PAUSE = 1,
    /**
     * Specify that an error has occured.
     *
     * @since BlackBerry 10.0.0
     */
    DIALOG_PROGRESS_ERROR = 2,
} dialog_progress_state_t;

/**
 * @brief The format of dates and times in notification dialogs
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * Specify that a short format be used to display the date and time.
     *
     * @since BlackBerry 10.0.0
     */
    DIALOG_DATE_TIME_SHORT = 0,
    /**
     * Specify that a medium format be used to display the date and time.
     *
     * @since BlackBerry 10.0.0
     */
    DIALOG_DATE_TIME_MEDIUM = 1,
    /**
     * Specify that a long format be used to display the date and time.
     *
     * @since BlackBerry 10.0.0
     */
    DIALOG_DATE_TIME_LONG = 2,
    /**
     * Specify that the date and time not be displayed.
     *
     * @since BlackBerry 10.0.0
     */
    DIALOG_DATE_TIME_NONE = 3,
} dialog_date_time_format_t;

/**
 * @brief The available volume directions in volume toast dialogs
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * Specify that the volume has been decreased.
     *
     * @since BlackBerry 10.0.0
     */
    DIALOG_VOLUME_DIRECTION_DOWN = -1,
    /**
     * Specify that the volume has not been changed.
     *
     * @since BlackBerry 10.0.0
     */
    DIALOG_VOLUME_DIRECTION_NO_CHANGE = 0,
    /**
     * Specify that the volume has been increased.
     *
     * @since BlackBerry 10.0.0
     */
    DIALOG_VOLUME_DIRECTION_UP = 1,
} dialog_volume_direction_t;

/**
 * @brief The available volume controls in volume toast dialogs
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * Specify that volume control should not be allowed.
     *
     * @since BlackBerry 10.0.0
     */
    DIALOG_VOLUME_CONTROL_UNSUPPORTED = 0,
    /**
     * Specify that simple volume control be allowed.
     *
     * @since BlackBerry 10.0.0
     */
    DIALOG_VOLUME_CONTROL_SIMPLE = 1,
    /**
     * Specify that percentage volume control be allowed.
     *
     * @since BlackBerry 10.0.0
     */
    DIALOG_VOLUME_CONTROL_PERCENTAGE = 2,
} dialog_volume_control_t;

/**
 * @brief Deprecated: Dialogs are sized automatically by BlackBerry 10 OS
 *
 * @deprecated Dialogs are sized automatically by BlackBerry 10 OS. You can no
 * longer size them.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    DIALOG_SIZE_SMALL    = 0,
    DIALOG_SIZE_MEDIUM   = 1,
    DIALOG_SIZE_LARGE    = 2,
    DIALOG_SIZE_TALL     = 3,
    DIALOG_SIZE_FULL     = 4
} dialog_size_t;

/**
 * @brief Deprecated: User events are never passed through to the application
 * beneath the dialog; the dialog receives all events.
 *
 * @deprecated User events are never passed through to the application beneath
 * the dialog; the dialog receives all events.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum  {
    DIALOG_COVER_SENSITIVITY_ALPHA_TEST  = 0,
    DIALOG_COVER_SENSITIVITY_ALWAYS      = 1,
    DIALOG_COVER_SENSITIVITY_NEVER       = 2
} dialog_cover_sensitivity_t;

/**
 * @name Localized button labels
 *
 * These strings can be used as button labels. They are displayed as
 * localized strings based on the system's locale.
 *
 * @{
 *
 * @since BlackBerry 10.0.0
 */
/**
 * The OK label.
 *
 * @since BlackBerry 10.0.0
 */
#define DIALOG_OK_LABEL                "OK"
/**
 * The Cancel label.
 *
 * @since BlackBerry 10.0.0
 */
#define DIALOG_CANCEL_LABEL            "CANCEL"
/**
 * The Cut label.
 *
 * @since BlackBerry 10.0.0
 */
#define DIALOG_CUT_LABEL               "CUT"
/**
 * The Copy label.
 *
 * @since BlackBerry 10.0.0
 */
#define DIALOG_COPY_LABEL              "COPY"
/**
 * The Paste label.
 *
 * @since BlackBerry 10.0.0
 */
#define DIALOG_PASTE_LABEL             "PASTE"
/**
 * The Select label.
 *
 * @since BlackBerry 10.0.0
 */
#define DIALOG_SELECT_LABEL            "SELECT"
/**
 * The Delete label.
 *
 * @since BlackBerry 10.0.0
 */
#define DIALOG_DELETE_LABEL            "DELETE"
/**
 * The View Image label.
 *
 * @since BlackBerry 10.0.0
 */
#define DIALOG_VIEW_IMAGE_LABEL        "VIEW_IMAGE"
/**
 * The Save Image label.
 *
 * @since BlackBerry 10.0.0
 */
#define DIALOG_SAVE_IMAGE_LABEL        "SAVE_IMAGE"
/**
 * The Save Link As label.
 *
 * @since BlackBerry 10.0.0
 */
#define DIALOG_SAVE_LINK_AS_LABEL      "SAVE_LINK_AS"
/**
 * The Open Link in New Tab label.
 *
 * @since BlackBerry 10.0.0
 */
#define DIALOG_OPEN_LINK_NEW_TAB_LABEL "OPEN_LINK_NEW_TAB"
/**
 * The Copy Link label.
 *
 * @since BlackBerry 10.0.0
 */
#define DIALOG_COPY_LINK_LABEL         "COPY_LINK"
/**
 * The Open Link label.
 *
 * @since BlackBerry 10.0.0
 */
#define DIALOG_OPEN_LINK_LABEL         "OPEN_LINK"
/**
 * The Copy Image Link label.
 *
 * @since BlackBerry 10.0.0
 */
#define DIALOG_COPY_IMAGE_LINK_LABEL   "COPY_IMAGE_LINK"
/**
 * The Clear Field label.
 *
 * @since BlackBerry 10.0.0
 */
#define DIALOG_CLEAR_FIELD_LABEL       "CLEAR_FIELD"
/**
 * The Cancel Selection label.
 *
 * @since BlackBerry 10.0.0
 */
#define DIALOG_CANCEL_SELECTION_LABEL  "CANCEL_SELECTION"
/**
 * The Bookmark Link label.
 *
 * @since BlackBerry 10.0.0
 */
#define DIALOG_BOOKMARK_LINK_LABEL     "BOOKMARK_LINK"
/**@}*/

struct dialog_object_t;

/**
 * @brief Handle to a dialog instance
 *
 * The @c #dialog_instance_t structure defines an opaque handle to a dialog
 * instance.
 *
 * @since BlackBerry 10.0.0
 */
typedef struct dialog_object_t* dialog_instance_t;

/**
 * @name General dialog functions
 *
 * These functions can be used for all types of dialogs.
 *
 * @{
 */

/**
 * @brief Start receiving dialog events
 *
 * The @c dialog_request_events() function starts to deliver dialog events to
 * your application using BPS. Dialog events are sent when a dialog button is
 * pressed. Your application must call this function before calling any other
 * dialog functions. Events are posted to the currently active channel.
 *
 * @param flags The types of events to deliver. A value of zero indicates that
 *        all events are requested. The meaning of non-zero values is reserved
 *        for future use.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_request_events(int flags);

/**
 * @brief Stop receiving dialog events
 *
 * The @c dialog_stop_events() function stops dialog events from being delivered
 * to the application using BPS.
 *
 * @param flags The types of events to stop. A value of zero indicates that all
 *        events are stopped. The meaning of non-zero values is reserved for
          future use.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_stop_events(int flags);

/**
 * @brief Get the unique domain ID for the dialog service
 *
 * The @c dialog_get_domain() function gets the unique domain ID for the dialog
 * service. You can use this function in your application to test whether an
 * event that you retrieve using @c bps_get_event() is a dialog event, and
 * respond accordingly.
 *
 * @return The domain ID for the dialog service.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_get_domain(void);

/**
 * @brief Display a dialog
 *
 * The @c dialog_show() function displays the specified dialog.
 *
 * @param dialog The dialog to display.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_show(dialog_instance_t dialog);

/**
 * @brief Update a dialog
 *
 * The @c dialog_update() function updates the specified dialog that is already
 * displayed. Call this function after an attribute is changed to refresh the
 * currently displayed dialog.
 *
 * @param dialog The dialog to update.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_update(dialog_instance_t dialog);

/**
 * @brief Cancel a dialog
 *
 * The @c dialog_cancel() function cancels the specified dialog that is already
 * displayed.
 *
 * @param dialog The dialog to cancel.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_cancel(dialog_instance_t dialog);

/**
 * @brief Destroy a dialog
 *
 * The @c dialog_destroy() function cleans up resources for the specified
 * dialog. You can provide any type of dialog as an argument to this
 * function. Call this function when the dialog is no longer being used.
 *
 * @param dialog The dialog to destroy.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_destroy(dialog_instance_t dialog);

/**@}*/

/**
 * @name Dialog setters
 *
 * These functions can be used to set attributes that are common to all types of
 * dialogs, unless specifically noted by a particular dialog type.
 *
 * @{
 */

/**
 * @brief Set the title text for a dialog
 *
 * The @c dialog_set_title_text() function sets the text to display as the title
 * of the specified dialog.
 *
 * @param dialog The dialog to update.
 * @param text The text to display as the dialog title.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_title_text(dialog_instance_t dialog, const char *text);

/**
 * @brief Deprecated: This function has no effect
 *
 * @deprecated This function has no effect. Use the @c dialog_set_title_text()
 * function.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_html_title_text(dialog_instance_t dialog, const char *text) BPS_DEPRECATED;

/**
 * @brief Set the window group ID for an application modal dialog
 *
 * The @c dialog_set_group_id() function sets the window group ID for an
 * application modal dialog.
 *
 * @param dialog The dialog to update.
 * @param group_id The window group ID to set. If @c NULL, the dialog is a
 *        system modal dialog.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_group_id(dialog_instance_t dialog, const char *group_id);

/**
 * @brief Specify input flags on the input field
 *
 * The @c dialog_set_input_flags() function specifies the input options to use
 * on input fields for dialogs.  By default input is corrected automatically (@c
 * #DIALOG_INPUT_AUTO_CORRECT) and checked for spelling errors (@c
 * #DIALOG_INPUT_SPELL_CHECK).  To turn off all input options use @c
 * #DIALOG_INPUT_NONE.  Changing the keyboard layout will disable any input
 * flags.
 *
 * @param dialog The dialog to update.
 * @param input_flags The input flags to apply.  Must be a bitwise-OR of the
 *        values of the @c #dialog_input_flags_t enumeration, or @c
 *        #DIALOG_INPUT_NONE to turn off all input options.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int dialog_set_input_flags(dialog_instance_t dialog, int input_flags);

/**
 * @brief Set whether to show an activity indicator in a dialog
 *
 * The @c dialog_set_busy() function sets whether to show an activity indicator
 * in the specified dialog.
 *
 * @param dialog The dialog to update.
 * @param busy If @c true, show the activity indicator; if @c false, do not show
 *        the activity indicator.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int dialog_set_busy(dialog_instance_t dialog, bool busy);

/** @cond internal
 */

/**
 * @brief Specify whether the dialog is a system dialog
 *
 * The @c dialog_set_system() function specifies whether the dialog is a system
 * dialog.  System dialogs are for internal use only.
 *
 * Once the dialog has been shown, updated, or canceled with @c dialog_show(),
 * @c dialog_update(), or @c dialog_cancel(), you cannot change whether the
 * dialog is a system dialog or not.
 *
 * @param dialog The dialog to update.
 * @param system If @c true, set the dialog to be a system dialog; if @c false,
 *        set the dialog to be a non-system dialog.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_system(dialog_instance_t dialog, bool system);

/**
 * @brief Set the priority for a system dialog
 *
 * The @c dialog_set_priority() function sets the priority for a system dialog.
 * System dialogs with priority set appear above the lock screen.
 *
 * @param dialog The dialog to update.
 * @param priority If @c true, set the system dialog to high priority; if @c
 *        false, set to normal priority.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise. Returns @c BPS_FAILURE if the dialog is not a system
 *         dialog.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_priority(dialog_instance_t dialog, bool priority);

/**
 * @brief Set the PID of the process for a system dialog to be associated with
 *
 * The @c dialog_set_pid() function sets the PID of the process for a system
 * dialog to be associated with.
 *
 * @param dialog The dialog to update.
 * @param pid The PID of the process.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise. Returns @c BPS_FAILURE if the dialog is not a system
 *         dialog.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int dialog_set_pid(dialog_instance_t dialog, pid_t pid);

/** @endcond
 */

/**
 * @brief Specify the enter key type to use on the virtual keyboard
 *
 * The @c dialog_set_enter_key_type() function specifies the enter key type to
 * use on the virtual keyboard when it is visible when the dialog is
 * shown.
 *
 * @param dialog The dialog to update.
 * @param enter_key_type The enter key type.  Must be one of the values of the
 * @c #virtualkeyboard_enter_t enumeration.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_enter_key_type(dialog_instance_t dialog, int enter_key_type);

/**
 * @brief Specify whether the application is required to cancel a dialog
 * explicitly
 *
 * The @c dialog_set_cancel_required() function specifies whether the
 * application is required to cancel the dialog or not when the user presses a
 * button. By default, the application is not required to explicitly cancel the
 * dialog but it is no longer displayed once the user presses one of the
 * dialog's buttons. If @c cancel_required is set to @c true, then the dialog
 * continues to be displayed, even after one of its buttons has been
 * pressed, until the application calls @c dialog_cancel() on the dialog.
 *
 * @param dialog The dialog to update.
 * @param cancel_required If @c true, the application must cancel the dialog
 *        explicitly; if @c false, the application doesn't cancel the dialog
 *        explicitly.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_cancel_required(dialog_instance_t dialog, bool cancel_required);

/**
 * @brief Set the default button index for a dialog
 *
 * The @c dialog_set_default_button_index() function sets the index of the
 * button that is actioned when the Enter key is pressed while the dialog is
 * displayed. This action is equivalent to the user pressing the button at the
 * given index.
 *
 * @param dialog The dialog to update.
 * @param default_button_index The default button index to set. Buttons are
 *        indexed in the order that they are added with @c dialog_add_button(),
 *        starting at 0.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_default_button_index(dialog_instance_t dialog, int default_button_index);

/**
 * @brief Set the button limit for a dialog
 *
 * The @c dialog_set_button_limit() function sets the number of buttons allowed
 * per row.  The default is 2.
 *
 * @param dialog The dialog to update.
 * @param button_limit The button limit, must be greater than 0.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int dialog_set_button_limit(dialog_instance_t dialog, int button_limit);

/**
 * @brief Add a button to a dialog
 *
 * The @c dialog_add_button() function adds a button to the specified dialog.
 *
 * @param dialog The dialog to add a button to.
 * @param label The button label.
 * @param enabled If @c true, the button is enabled when the dialog is
 *        displayed; if @c false, the button is disabled when the dialog is
 *        displayed.
 * @param button_context The button context. This can be any data the
 *        application wants to associate with a button. If @c button_context is
 *        set and the button is pressed, the @c button_context is returned in
 *        the @c DIALOG_RESPONSE event.
 * @param visible If @c true, the button is visible when the dialog is
 *        displayed; if @c false, the button is not visible when the dialog is
 *        displayed.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_add_button(dialog_instance_t dialog, const char *label, bool enabled, const char *button_context, bool visible);

/**
 * @brief Update a button with new values
 *
 * The @c dialog_update_button() function updates a button that has already been
 * added to the dialog with new values. If the dialog is currently displayed
 * when the request to update the button is made, the update is not reflected
 * until @c dialog_update() is called.
 *
 * @param dialog The dialog that has the button to update.
 * @param index The index of the button to update.
 * @param label The button label. Pass @c NULL to retain the existing value, if
 *        previously set.
 * @param enabled If @c true, the button is enabled when the dialog is
 *        displayed; if @c false, the button is disabled when the dialog is
 *        displayed.
 * @param button_context The button context. Pass @c NULL to retain the existing
 *        value, if previously set.
 * @param visible If @c true, the button is visible when the dialog is
          displayed; if @c false, the button is not visible when the dialog is
          displayed.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_update_button(dialog_instance_t dialog, int index, const char *label, bool enabled, const char *button_context, bool visible);

/**
 * @brief Remove a button from a dialog
 *
 * The @c dialog_remove_button() function removes a button from the specified
 * dialog. If the dialog is currently displayed when the request to remove the
 * button is made, the update is not reflected until @c dialog_update() is
 * called.
 *
 * @param dialog The dialog to remove the button from.
 * @param index The index of the button to remove. Buttons are indexed in the
 *        order that they are added with @c dialog_add_button() starting at 0.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_remove_button(dialog_instance_t dialog, int index);

/**
 * @brief Deprecated: Dialogs are sized automatically.
 *
 * @deprecated Dialogs are sized automatically. This function has no effect.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_size(dialog_instance_t dialog, dialog_size_t size) BPS_DEPRECATED;

/**
 * @brief Deprecated: Dialogs are positioned automatically.
 *
 * @deprecated Dialogs are positioned automatically. This function has no
 * effect.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_position(dialog_instance_t dialog, dialog_position_t position) BPS_DEPRECATED;

/**
 * @brief Deprecated: Dialogs are always fully opaque.
 *
 * @deprecated Dialogs are always fully opaque. This function has no effect for
 * BlackBerry 10 OS.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_background_alpha(dialog_instance_t dialog, double background_alpha) BPS_DEPRECATED;

/**
 * @brief Deprecated: User events are never passed through to the application
 * beneath the dialog; the dialog receives all events.
 *
 * @deprecated User events are never passed through to the application beneath
 * the dialog; the dialog receives all events. This function has no effect.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_cover_sensitivity(dialog_instance_t dialog, dialog_cover_sensitivity_t sensitivity) BPS_DEPRECATED;

/**@}*/

/**
 * @name Common dialog event getters
 *
 * These functions can be used to get any of the attributes of a @c
 * DIALOG_RESPONSE event that are common to all types of dialogs.
 *
 * @{
 */

/**
 * @brief Get the dialog instance from a @c DIALOG_RESPONSE event
 *
 * The @c dialog_event_get_dialog_instance() function gets the dialog instance
 * that is associated with the specified @c DIALOG_RESPONSE event. This can be
 * used to correlate the event with the dialog that generated the event. The
 * dialog instance returned from this function is one of the dialog instances
 * created with dialog creation functions.
 *
 * @param event The @c DIALOG_RESPONSE event to get the dialog instance from.
 *
 * @return The dialog instance.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API dialog_instance_t dialog_event_get_dialog_instance(bps_event_t *event);

/**
 * @brief Get the error message from a @c DIALOG_RESPONSE event
 *
 * The @c dialog_event_get_error() function gets the error message.
 *
 * @param event The @c DIALOG_RESPONSE event to get the error message from.
 *
 * @return The error message; NULL if no error.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char *dialog_event_get_error(bps_event_t *event);

/**
 * @brief Get the index of the selected button from a @c DIALOG_RESPONSE event
 *
 * The @c dialog_event_get_selected_index() function gets the index of the
 * selected button after a dialog button has been pressed by the user.
 *
 * @param event The @c DIALOG_RESPONSE event to get the selected button index
 *        from.
 *
 * @return The selected button index; BPS_FAILURE upon failure.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_event_get_selected_index(bps_event_t *event);

/**
 * @brief Get the label of the selected button from a @c DIALOG_RESPONSE event
 *
 * The @c dialog_event_get_selected_label() function gets the label of the
 * selected button after a dialog button has been pressed by the user.
 *
 * @param event The @c DIALOG_RESPONSE event to get the selected button label
 *        from.
 *
 * @return The text label of the selected button.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char *dialog_event_get_selected_label(bps_event_t *event);

/**
 * @brief Get the context that is associated with the selected button from a @c
 * DIALOG_RESPONSE event
 *
 * The @c dialog_event_get_selected_context() function gets the context that is
 * associated with the selected button.
 *
 * @param event The @c DIALOG_RESPONSE event to get the selected button context
 *        from.
 *
 * @return The context of the selected button.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char *dialog_event_get_selected_context(bps_event_t *event);

/**@}*/

/**
 * @name Alert dialog functions
 *
 * An alert dialog is a simple dialog that displays a title, message, icon,
 * checkbox and buttons.  Alert dialog functions can also be used on prompt,
 * progress, login, password change, popup list, and notification dialogs.
 *
 * @{
 */

/**
 * @brief Create an alert dialog
 *
 * The @c dialog_create_alert() function creates an alert dialog.
 *
 * @param dialog This will be populated with the newly created dialog instance.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_create_alert(dialog_instance_t *dialog);

/**
 * @brief Set the message text of an alert dialog
 *
 * The @c dialog_set_alert_message_text() function sets the message text of the
 * specified alert dialog.
 *
 * @param dialog The dialog to update.
 *
 * @param text The message text to display.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_alert_message_text(dialog_instance_t dialog, const char *text);

/**
 * @brief Set whether the message text has emoticons
 *
 * The @c dialog_set_alert_message_has_emoticons() function sets whether the
 * message text has emoticons, and that they should be displayed graphically.
 *
 * @param dialog The dialog to update.
 *
 * @param has_emoticons If @c true display emoticons graphically, if @c false,
 *        do not alter the appearance of emoticons.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_alert_message_has_emoticons(dialog_instance_t dialog, bool has_emoticons);

/**
 * @brief Set the initial state of the check box
 *
 * The @c dialog_set_alert_checkbox_checked() function sets the initial state
 * of the check box for the specified alert dialog.
 *
 * @param dialog The dialog to update.
 *
 * @param checked If @c true, the check box is checked initially; if @c false,
 *        the check box is not checked initially.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_alert_checkbox_checked(dialog_instance_t dialog, bool checked);

/**
 * @brief Set the label for the check box
 *
 * The @c dialog_set_alert_checkbox_label() function sets the label for the
 * check box. If this attribute is not set, the check box is not displayed.
 *
 * @param dialog The dialog to update.
 *
 * @param label The check box label.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_alert_checkbox_label(dialog_instance_t dialog, const char *label);

/**
 * @brief Set whether the check box is enabled
 *
 * The @c dialog_set_alert_checkbox_enabled() function sets whether the check
 * box is enabled for the specified alert dialog.
 *
 * @param dialog The dialog to update.
 *
 * @param enabled If @c true, the check box is enabled; if @c false, the check
 *        box is not enabled.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int dialog_set_alert_checkbox_enabled(dialog_instance_t dialog, bool enabled);

/**
 * @brief Set the icon of a alert dialog
 *
 * The @c dialog_set_alert_icon() function sets the icon of the specified
 * alert dialog.
 *
 * @param dialog The dialog to update.
 * @param path The absolute path of the icon to be shown.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int dialog_set_alert_icon(dialog_instance_t dialog, const char *path);

/**
 * @brief Deprecated: This function has no effect
 *
 * @deprecated This function has no effect. Use the @c
 * dialog_set_alert_message_text() function.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_alert_html_message_text(dialog_instance_t dialog, const char *text) BPS_DEPRECATED;

/**
 * @brief Get the state of the alert dialog's check box from a @c
 * DIALOG_RESPONSE event
 *
 * The @c dialog_event_get_alert_checkbox_checked() function gets the state of
 * the check box when the alert dialog is dismissed by the user such as when the
 * user presses a button on the alert dialog.
 *
 * @param event The @c DIALOG_RESPONSE event to get the state of the check box
 *        from.
 *
 * @return @c true if the check box is checked; @c false if it is not checked.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API bool dialog_event_get_alert_checkbox_checked(bps_event_t* event);

/**@}*/

/**
 * @name Context menu functions
 *
 * A context menu dialog shows a menu of buttons, each of which has text and/or
 * icons.
 *
 * Context menu dialogs ignore the size, position, and title attributes, if set.
 *
 * Context menu dialogs offer pre-defined icons and localized labels as options
 * for the menu buttons.
 *
 * @{
 */

/**
 * @brief Create a context menu dialog
 *
 * The @c dialog_create_context_menu() function creates a context menu dialog.
 *
 * @param dialog This will be populated with the newly created dialog instance.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_create_context_menu(dialog_instance_t *dialog);

/**
 * @brief Add a button to a context menu dialog
 *
 * The @c dialog_context_menu_add_button() function adds a button to the
 * specified context menu dialog.
 *
 * @param dialog The dialog to add a button to.
 *
 * @param label The button label.
 * @param enabled If @c true, the button is enabled when the dialog is
 *        displayed; if @c false, the button is disabled when the dialog is
 *        displayed.
 * @param button_context The button context. This can be any data the
 *        application wants to associate with a button. If @c button_context is
 *        set and the button is pressed, the @c button_context is returned in
 *        the @c DIALOG_RESPONSE event.
 * @param visible If @c true, the button is visible when the dialog is
 *        displayed; if @c false, the button is not visible when the dialog is
 *        displayed.
 * @param icon The icon to display on the button.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_context_menu_add_button(dialog_instance_t dialog, const char *label, bool enabled, const char *button_context, bool visible, dialog_context_menu_icon_t icon);

/**
 * @brief Update a context menu button with new values
 *
 * The @c dialog_context_menu_update_button() function updates the specified
 * context menu button that has already been added with new values. If the
 * dialog is currently displayed when the request to update the button is made,
 * the update is not reflected until @c dialog_update() is called.
 *
 * @param dialog The dialog that has the button to update.
 * @param index The index of the button to update.
 * @param label The button label. Pass @c NULL to retain the existing value, if
 *        previously set.
 * @param enabled If @c true, the button is enabled when the dialog is
 *        displayed; if @c false, the button is disabled when the dialog is
 *        displayed.
 * @param button_context The button context. Pass @c NULL to retain the existing
 *        value, if previously set.
 * @param visible If @c true, the button is visible when the dialog is
 *        displayed; if @c false, the button is not visible when the dialog is
 *        displayed.
 * @param icon The icon to display. Pass @c KEEP_ICON to retain the existing
 *        icon, if previously set.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_context_menu_update_button(dialog_instance_t dialog, int index, const char *label, bool enabled, const char *button_context, bool visible, dialog_context_menu_icon_t icon);

/**
 * @brief Deprecated: Context menus are positioned automatically.
 *
 * @deprecated Context menus are positioned automatically. This function has no
 * effect.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_context_menu_coordinates(dialog_instance_t dialog, int x, int y) BPS_DEPRECATED;

/**
 * @brief Deprecated: Context menus are sized automatically.
 *
 * @deprecated Context menus are sized automatically. This function has no
 * effect.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_context_menu_width(dialog_instance_t dialog, int width) BPS_DEPRECATED;

/**
 * @brief Deprecated: Context menus are sized automatically.
 *
 * @deprecated Context menus are sized automatically. This function has no
 * effect.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_context_menu_height(dialog_instance_t dialog, int height) BPS_DEPRECATED;

/**@}*/

/**
 * @name Prompt dialog functions
 *
 * A prompt dialog is a simple dialog with a title, a message, an input field,
 * and buttons.  Alert dialog functions can also be used on prompt dialogs.
 *
 * @{
 */

/**
 * @brief Create a prompt dialog
 *
 * The @c dialog_create_prompt() function creates a prompt dialog.
 *
 * @param dialog This will be populated with the newly created dialog instance.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_create_prompt(dialog_instance_t *dialog);

/**
 * @brief Set a prompt dialog's message text
 *
 * The @c dialog_set_prompt_message_text() function sets the message text of the
 * specified prompt dialog.
 *
 * @param dialog The dialog to update.
 * @param text The message text to display.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_prompt_message_text(dialog_instance_t dialog, const char *text);

/**
 * @brief Set whether the message text has emoticons
 *
 * The @c dialog_set_prompt_message_has_emoticons() function sets whether the
 * message text has emoticons, and that they should be displayed graphically.
 *
 * @param dialog The dialog to update.
 *
 * @param has_emoticons If @c true display emoticons graphically, if @c false,
 * do not alter the appearance of emoticons.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_prompt_message_has_emoticons(dialog_instance_t dialog, bool has_emoticons);

/**
 * @brief Deprecated: This function has no effect
 *
 * @deprecated This message has no effect. Use the @c
 * dialog_set_prompt_message_text() function.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_prompt_html_message_text(dialog_instance_t dialog, const char *text) BPS_DEPRECATED;

/**
 * @brief Set the initial text of the input field of a prompt dialog
 *
 * The @c dialog_set_prompt_input_field() function sets the initial text to
 * display in the input field of the specified prompt dialog.
 *
 * @param dialog The dialog to update.
 * @param text The text to display in the input field.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_prompt_input_field(dialog_instance_t dialog, const char *text);

/**
 * @brief Set the placeholder text of the input field of a prompt dialog
 *
 * The @c dialog_set_prompt_input_placeholder() function sets the text to
 * display when there is no text in the input field and the field does not have
 * the focus.
 *
 * @param dialog The dialog to update.
 * @param input_placeholder The input field placeholder text to display.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_prompt_input_placeholder(dialog_instance_t dialog, const char *input_placeholder);

/**
 * @brief Set the maximum number of characters of the input field of a prompt
 * dialog
 *
 * The @c dialog_set_prompt_maximum_characters() function sets the maximum
 * number of characters that can be entered in the input field of a prompt
 * dialog.
 *
 * @param dialog The dialog to update.
 * @param max_chars The maximum number of characters.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_prompt_maximum_characters(dialog_instance_t dialog, int max_chars);

/**
 * @brief Set whether to display the field as a password input
 *
 * The @c dialog_set_prompt_display_as_password() function sets whether the
 * input field of the prompt dialog appears as a password input field.  That is,
 * the input is obscured.
 *
 * @param dialog The dialog to update.
 *
 * @param display_as_password If @c true display the input field as a password
 * input field, if @c false, display the input field normally.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_prompt_display_as_password(dialog_instance_t dialog, bool display_as_password);

/**
 * @brief Specify input flags on the input field
 *
 * @deprecated Use the dialog_set_input_flags() function.
 * 
 * The @c dialog_set_prompt_input_flags() function specifies the input options
 * to use on input fields for prompt dialogs.  By default input is corrected
 * automatically (@c DIALOG_INPUT_AUTO_CORRECT) and checked for spelling errors
 * (@c DIALOG_INPUT_SPELL_CHECK).  To turn off all input options use @c
 * DIALOG_INPUT_NONE.
 *
 * @param dialog The dialog to update.
 * @param input_flags The input flags to apply.  Must be a bitwise-OR of the
 *        values of the @c #dialog_input_flags_t enumeration, or @c
 *        DIALOG_INPUT_NONE to turn off all input options.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_prompt_input_flags(dialog_instance_t dialog, int input_flags) BPS_DEPRECATED;

/**
 * @brief Specify the layout to use on the virtual keyboard
 *
 * The @c dialog_set_prompt_input_keyboard_layout() function specifies the
 * layout to use on the virtual keyboard when it is visible when the dialog is
 * shown.  Changing the keyboard layout will disable any input flags set with @c
 * dialog_set_input_flags().
 *
 * @param dialog The dialog to update.
 * @param layout The keyboard layout.  Must be one of the values of the @c
 * #virtualkeyboard_layout_t enumeration.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_prompt_input_keyboard_layout(dialog_instance_t dialog, int layout);

/**
 * @brief Get the contents of the prompt dialog input field from a
 * @c DIALOG_RESPONSE event
 *
 * The @c dialog_event_get_prompt_input_field() function gets the contents of
 * the input field when the prompt dialog is dismissed by the user such as
 * when the user presses a button on the prompt dialog.
 *
 * @param event The @c DIALOG_RESPONSE event to get the contents of the prompt
 * dialog input field from.
 *
 * @return The contents of the input field.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char *dialog_event_get_prompt_input_field(bps_event_t *event);

/**@}*/

/**
 * @name Popup list dialog functions
 *
 * A popup list dialog displays a simple popup list along with a title, selected
 * items, and buttons.  Alert dialog functions can also be used on popup list
 * dialogs.
 *
 * @{
 */

/**
 * @brief Create a popup list dialog
 *
 * The @c dialog_create_popuplist() function creates a popup list dialog.
 *
 * @param dialog This will be populated with the newly created dialog instance.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_create_popuplist(dialog_instance_t *dialog);

/**
 * @brief Specify whether users can select multiple items in a popup list dialog
 *
 * The @c dialog_set_popuplist_multiselect() function specifies whether users
 * can select multiple items in the specified popup list dialog.  By default
 * users cannot select multiple items.
 *
 * @param dialog The dialog to update.
 * @param multi_select If @c true, users can select multiple items in the popup
 *        list dialog; if @c false, users can select only one item in the popup
 *        list dialog.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_popuplist_multiselect(dialog_instance_t dialog, bool multi_select);

/**
 * @brief Specify whether users can deselect items in a popup list dialog
 *
 * The @c dialog_set_popuplist_allow_deselect() function specifies whether users
 * can deselect items in the specified popup list dialog.  This only applies on
 * multi-select lists.  By default users can deselect items.
 *
 * @param dialog The dialog to update.
 * @param allow_deselect If @c true, users can deselect items in the popup list
 *        dialog; if @c false, users cannot deselect items in the popup list
 *        dialog.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int dialog_set_popuplist_allow_deselect(dialog_instance_t dialog, bool allow_deselect);

/**
 * @brief Specify whether the popup list dialog is cancelled when an item is
 * selected
 *
 * The @c dialog_set_popuplist_cancel_on_selection() function specifies whether
 * the popup list dialog is cancelled as soon as the user makes a selection from
 * the list.  By default the dialog is not cancelled when an item is selected.
 *
 * @param dialog The dialog to update.
 * @param cancel_on_selection If @c true, the popup list dialog is cancelled
 *        when an item is selected; if @c false, the popup list dialog is not
 *        cancelled when an item is selected.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int dialog_set_popuplist_cancel_on_selection(dialog_instance_t dialog, bool cancel_on_selection);

/**
 * @brief Specify whether to show a basic selection list in the popup list
 * dialog
 *
 * The @c dialog_set_popuplist_show_basic_selection() function specifies whether
 * to show a basic selection list in the popup list dialog.  By default the
 * basic selection list is not used.
 *
 * A basic selection list shows a list of items (as text), and selecting an item
 * highlights the entire item.
 *
 * A non-basic selection list includes a radio button or checkbox on each item
 * in addition to the displayed text. (radio button in the single-select case,
 * checkboxes in the multi-select case). Selecting an item checks the checkbox
 * or radio button.
 *
 * @param dialog The dialog to update.
 * @param show_basic_selection If @c true, a basic selection list is used in the
 *        popup list dialog; if @c false, a basic selection list is not used in
 *        the popup list dialog.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int dialog_set_popuplist_show_basic_selection(dialog_instance_t dialog, bool show_basic_selection);

/**
 * @brief Set the items to display in a popup list dialog
 *
 * The @c dialog_set_popuplist_items() function sets the items to display in the
 * specified popup list dialog.
 *
 * @param dialog The dialog to update.
 * @param items An array of strings, comprising the item list to display.
 * @param num_items The number of strings in the @c items array.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_popuplist_items(dialog_instance_t dialog, const char *items[], int num_items);

/**
 * @brief Set the indices of the initially selected items in a popup list dialog
 *
 * The @c dialog_set_popuplist_selected_indices() function sets the indices of
 * the items in the specified popup list dialog that are selected
 * initially.
 *
 * @param dialog The dialog to update.
 * @param selected_indices The indices of the items to be initially selected.
 * @param num_items The number of indices in the @c selected_indices array.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_popuplist_selected_indices(dialog_instance_t dialog, int selected_indices[], int num_items);

/**
 * @brief Set the indices of the initially disabled items in a popup list dialog
 *
 * The @c dialog_set_popuplist_disabled_indices() function sets the indices of
 * the items in the specified popup list dialog that are disabled initially.
 *
 * @param dialog The dialog to update.
 * @param disabled_indices The indices of the items to be disabled initially.
 * @param num_items The number of indices in the @c disabled_indices array.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_popuplist_disabled_indices(dialog_instance_t dialog, int disabled_indices[], int num_items);

/**
 * @brief Set the indices of the list items that are formatted as headers
 *
 * The @c dialog_set_popuplist_header_indices() function sets the indices of the
 * list items in the specified popup list dialog that are formatted as
 * headers.
 *
 * @param dialog The dialog to update.
 * @param header_indices The indices of the items that are formatted as
 *        headers.
 * @param num_items The number of indices in the @c header_indices array.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_popuplist_header_indices(dialog_instance_t dialog, int header_indices[], int num_items);

/**
 * @brief Set the indices of the list items that are formatted as separators
 *
 * The @c dialog_set_popuplist_separator_indices() function sets the indices of
 * the list items in the specified popup list dialog that are formatted as
 * separators.
 *
 * @param dialog The dialog to update.
 * @param separator_indices The indices of the items to be formatted as
 *        separators.
 * @param num_items The number of indices in the @c separator_indices array.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_popuplist_separator_indices(dialog_instance_t dialog, int separator_indices[], int num_items);

/**
 * @brief Set the index of the first visible item in a popup list dialog
 *
 * The @c dialog_set_popuplist_scroll_to_index() function sets the index of the
 * first visible item in the specified popup list dialog.
 *
 * @param dialog The dialog to update.
 * @param index The index of the first visible item in the list.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_popuplist_scroll_to_index(dialog_instance_t dialog, int index);

/**
 * @brief Get the array of selected indices from a @c DIALOG_RESPONSE event
 *
 * The @c dialog_event_get_popuplist_selected_indices() function gets the array
 * of selected indices from the specified @c DIALOG_RESPONSE event.
 *
 * @param event The @c DIALOG_RESPONSE event to get the array of selected
 *        indices from.
 * @param selected_indices The selected indices. When the memory holding these
 *        values is no longer needed, use @c bps_free() to free the memory.
 * @param num_indices The number of indices in the output array.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_event_get_popuplist_selected_indices(bps_event_t *event, int **selected_indices, int *num_indices);

/**@}*/

/**
 * @name Login dialog functions
 *
 * A login dialog has a title, input fields for username and password, a check
 * box and a label for remembering the username, and buttons.  Alert dialog
 * functions can also be used on login dialogs.
 *
 * @{
 */

/**
 * @brief Create a login dialog
 *
 * The @c dialog_create_login() function creates a login dialog.
 *
 * @param dialog This will be populated with the newly created dialog instance.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_create_login(dialog_instance_t *dialog);

/**
 * @brief Set the message text of a login dialog
 *
 * The @c dialog_set_login_message_text() function sets the message text of the
 * specified login dialog.
 *
 * @param dialog The dialog to update.
 * @param text The message text to display.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_login_message_text(dialog_instance_t dialog, const char *text);

/**
 * @brief Set whether the message text has emoticons
 *
 * The @c dialog_set_login_message_has_emoticons() function sets whether the
 * message text has emoticons, and that they should be displayed graphically.
 *
 * @param dialog The dialog to update.
 *
 * @param has_emoticons If @c true display emoticons graphically, if @c false,
 * do not alter the appearance of emoticons.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_login_message_has_emoticons(dialog_instance_t dialog, bool has_emoticons);

/**
 * @brief Deprecated: This function has no effect
 *
 * @deprecated This function has no effect. Use the @c
 * dialog_set_login_message_text() function.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_login_html_message_text(dialog_instance_t dialog, const char *text) BPS_DEPRECATED;

/**
 * @brief Set the error text of a login dialog
 *
 * The @c dialog_set_login_error_text() function sets the error text of the
 * specified login dialog.
 *
 * @param dialog The dialog to update.
 * @param text The error text to display.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_login_error_text(dialog_instance_t dialog, const char *text);

/**
 * @brief Set the initial text of the username input field
 *
 * The @c dialog_set_login_username() function sets the initial text of the
 * username input field.
 *
 * @param dialog The dialog to update.
 * @param text The text to display.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_login_username(dialog_instance_t dialog, const char *text);

/**
 * @brief Set the placeholder text of the username input field
 *
 * The @c dialog_set_login_username_placeholder() function sets the text to
 * display when there is no text in the username input field and the field does
 * not have the focus.
 *
 * @param dialog The dialog to update.
 * @param placeholder The placeholder text to display in the username input
 * field.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_login_username_placeholder(dialog_instance_t dialog, const char *placeholder);

/**
 * @brief Deprecated: Login dialogs do not have labels on the username input
 * field.
 *
 * @deprecated Login dialogs do not have labels on the username input field.
 * This function has no effect.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_login_username_label(dialog_instance_t dialog, const char *label) BPS_DEPRECATED;

/**
 * @brief Specify the layout to use on the virtual keyboard for the username
 * input field
 *
 * For the username input field, the @c
 * dialog_set_login_username_keyboard_layout() function specifies the layout to
 * use on the virtual keyboard when it is visible and when the dialog is shown.
 * Changing the keyboard layout will disable any input flags set with @c
 * dialog_set_input_flags().
 *
 * @param dialog The dialog to update.
 * @param layout The keyboard layout.  Must be one of the values of the @c
 * #virtualkeyboard_layout_t enumeration.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_login_username_keyboard_layout(dialog_instance_t dialog, int layout);

/**
 * @brief Set the initial text of the password input field
 *
 * The @c dialog_set_login_password() function sets the initial text of the
 * password input field.
 *
 * @param dialog The dialog to update.
 * @param text The text to display.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_login_password(dialog_instance_t dialog, const char *text);

/**
 * @brief Set the placeholder text of the password input field
 *
 * The @c dialog_set_login_password_placeholder() function sets the text to
 * display when there is no text in the password input field and the field does
 * not have the focus.
 *
 * @param dialog The dialog to update.
 * @param placeholder The placeholder text to display in the password input
 *        field.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_login_password_placeholder(dialog_instance_t dialog, const char *placeholder);

/**
 * @brief Deprecated: Login dialogs do not have labels on the password input
 * field.
 *
 * @deprecated Login dialogs do not have labels on the password input
 * field. This function has no effect.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_login_password_label(dialog_instance_t dialog, const char *label) BPS_DEPRECATED;

/**
 * @brief Specify the layout to use on the virtual keyboard for the password
 * input field
 *
 * For the password input field, the @c
 * dialog_set_login_password_keyboard_layout() function specifies the layout to
 * use on the virtual keyboard when it is visible and when the dialog is shown.
 * Changing the keyboard layout will disable any input flags set with @c
 * dialog_set_input_flags().
 *
 * @param dialog The dialog to update.
 * @param layout The keyboard layout.  Must be one of the values of the @c
 * #virtualkeyboard_layout_t enumeration.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_login_password_keyboard_layout(dialog_instance_t dialog, int layout);

/**
 * @brief Deprecated: Login dialogs do not have "Show password" check boxes.
 *
 * @deprecated Login dialogs do not have "Show password" check boxes.  Instead
 * each password field has an integrated password visiblity toggle.  This
 * function has no effect.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_login_show_password(dialog_instance_t dialog, bool show_password) BPS_DEPRECATED;

/**
 * @brief Deprecated: Login dialogs do not have "Show password" check boxes.
 *
 * @deprecated Login dialogs do not have "Show password" check boxes.  Instead
 * each password field has an integrated password visiblity toggle.  This
 * function has no effect.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_login_show_password_label(dialog_instance_t dialog, const char *label) BPS_DEPRECATED;

/**
 * @brief Set the initial state of the "Remember me" check box
 *
 * The @c dialog_set_login_remember_me() function sets the initial state of the
 * "Remember me" check box for the specified login dialog.
 *
 * @param dialog The dialog to update.
 * @param remember_me If @c true, the "Remember me" check box is checked
 *        initially; if @c false, the "Remember me" check box is not checked
 *        initially.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_login_remember_me(dialog_instance_t dialog, bool remember_me);

/**
 * @brief Set the label for the "Remember me" check box
 *
 * The @c dialog_set_login_remember_me_label() function sets the label for the
 * "Remember me" check box. If this attribute is not set, the check box and
 * label are not displayed.
 *
 * @param dialog The dialog to update.
 * @param label The check box label.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_login_remember_me_label(dialog_instance_t dialog, const char *label);

/**
 * @brief Get the contents of the login dialog's username field from a @c
 * DIALOG_RESPONSE event
 *
 * The @c dialog_event_get_login_username() function gets the contents of the
 * username field when the login dialog is dismissed by the user such as when
 * the user presses a button on the login dialog.
 *
 * @param event The @c DIALOG_RESPONSE event to get the contents of the username
 *        field from.
 *
 * @return The contents of the username field.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char *dialog_event_get_login_username(bps_event_t *event);

/**
 * @brief Get the contents of the login dialog's password field from a @c
 * DIALOG_RESPONSE event
 *
 * The @c dialog_event_get_login_password() function gets the contents of the
 * password field when the login dialog is dismissed by the user such as when
 * the user presses a button on the login dialog.
 *
 * @param event The @c DIALOG_RESPONSE event to get the contents of the password
 *        field from.
 *
 * @return The contents of the password field.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char *dialog_event_get_login_password(bps_event_t *event);

/**
 * @brief Get the state of the login dialog's "Remember me" check box from a
 * @c DIALOG_RESPONSE event
 *
 * The @c dialog_event_get_login_remember_me() function gets the state of the
 * "Remember me" check box when the login dialog is dismissed by the user such
 * as when the user presses a button on the login dialog.
 *
 * @param event The @c DIALOG_RESPONSE event to get the state of the "Remember
 *        me" check box from.
 *
 * @return @c true if the "Remember me" check box is checked; @c false if the
 *         "Remember me" check box is not checked.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API bool dialog_event_get_login_remember_me(bps_event_t *event);

/**@}*/

/**
 * @name Password change dialog functions
 *
 * A password change dialog has a title, input fields for the username, the old
 * password, the new password, and to confirm the new password, a check box and
 * a label for remembering the username, and buttons.  Alert dialog functions
 * can also be used on password change dialogs.
 * 
 * @{
 */

/**
 * @brief Create a password change dialog
 *
 * The @c dialog_create_password_change() function creates a password change
 * dialog.
 *
 * @param dialog This will be populated with the newly created dialog instance.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_create_password_change(dialog_instance_t *dialog);

/**
 * @brief Set the error text of a password change dialog
 *
 * The @c dialog_set_password_change_error_text() function sets the error text
 * of the specified password change dialog.
 *
 * @param dialog The dialog to update.
 *
 * @param text The error text to display.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_password_change_error_text(dialog_instance_t dialog, const char *text);

/**
 * @brief Set the initial text of the username input field
 *
 * The @c dialog_set_password_change_username() function sets the initial text
 * of the username input field.
 *
 * @param dialog The dialog to update.
 *
 * @param text The text to display.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_password_change_username(dialog_instance_t dialog, const char *text);

/**
 * @brief Set the placeholder text of the username input field
 *
 * The @c dialog_set_password_change_username_placeholder() function sets the
 * text to display when there is no text in the username input field and the
 * field does not have the focus.
 *
 * @param dialog The dialog to update.
 *
 * @param placeholder The placeholder text to display in the username input
 * field.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_password_change_username_placeholder(dialog_instance_t dialog, const char *placeholder);

/**
 * @brief Specify the layout to use on the virtual keyboard for the username
 * input field
 *
 * The @c dialog_set_password_change_username_keyboard_layout() function
 * specifies, for the username input field, the layout to use on the virtual
 * keyboard when it is visible while the dialog is showing.  Changing the
 * keyboard layout will disable any input flags set with @c
 * dialog_set_input_flags().
 *
 * @param dialog The dialog to update.
 *
 * @param layout The keyboard layout.  Must be one of the values of the @c
 * #virtualkeyboard_layout_t enumeration.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_password_change_username_keyboard_layout(dialog_instance_t dialog, int layout);

/**
 * @brief Set the initial text of the old password input field
 *
 * The @c dialog_set_password_change_old_password() function sets the initial
 * text of the old password input field.
 *
 * @param dialog The dialog to update.
 *
 * @param text The text to display.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_password_change_old_password(dialog_instance_t dialog, const char *text);

/**
 * @brief Set the placeholder text of the old password input field
 *
 * The @c dialog_set_password_change_old_password_placeholder() function sets
 * the text to display when there is no text in the old password input field and
 * the field does not have the focus.
 *
 * @param dialog The dialog to update.
 *
 * @param placeholder The placeholder text to display in the old password input
 * field.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_password_change_old_password_placeholder(dialog_instance_t dialog, const char *placeholder);

/**
 * @brief Specify the layout to use on the virtual keyboard for the old password
 * input field
 *
 * The @c dialog_set_password_change_old_password_keyboard_layout() function
 * specifies, for the old password input field, the layout to use on the virtual
 * keyboard when it is visible while the dialog is showing.  Changing the
 * keyboard layout will disable any input flags set with @c
 * dialog_set_input_flags().
 *
 * @param dialog The dialog to update.
 *
 * @param layout The keyboard layout.  Must be one of the values of the @c
 * #virtualkeyboard_layout_t enumeration.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_password_change_old_password_keyboard_layout(dialog_instance_t dialog, int layout);

/**
 * @brief Set the initial text of the new password input field
 *
 * The @c dialog_set_password_change_new_password() function sets the initial
 * text of the new password input field.
 *
 * @param dialog The dialog to update.
 *
 * @param text The text to display.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_password_change_new_password(dialog_instance_t dialog, const char *text);

/**
 * @brief Set the placeholder text of the new password input field
 *
 * The @c dialog_set_password_change_new_password_placeholder() function sets
 * the text to display when there is no text in the new password input field and
 * the field does not have the focus.
 *
 * @param dialog The dialog to update.
 *
 * @param placeholder The placeholder text to display in the new password input
 * field.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_password_change_new_password_placeholder(dialog_instance_t dialog, const char *placeholder);

/**
 * @brief Specify the layout to use on the virtual keyboard for the new password
 * input field
 *
 * The @c dialog_set_password_change_new_password_keyboard_layout() function
 * specifies, for the new password input field, the layout to use on the virtual
 * keyboard when it is visible while the dialog is showing.  Changing the
 * keyboard layout will disable any input flags set with @c
 * dialog_set_input_flags().
 *
 * @param dialog The dialog to update.
 *
 * @param layout The keyboard layout.  Must be one of the values of the @c
 * #virtualkeyboard_layout_t enumeration.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_password_change_new_password_keyboard_layout(dialog_instance_t dialog, int layout);

/**
 * @brief Set the initial text of the confirm password input field
 *
 * The @c dialog_set_password_change_confirm_password() function sets the
 * initial text of the confirm password input field.
 *
 * @param dialog The dialog to update.
 *
 * @param text The text to display.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_password_change_confirm_password(dialog_instance_t dialog, const char *text);

/**
 * @brief Set the placeholder text of the confirm password input field
 *
 * The @c dialog_set_password_change_confirm_password_placeholder() function
 * sets the text to display when there is no text in the confirm password input
 * field and the field does not have the focus.
 *
 * @param dialog The dialog to update.
 *
 * @param placeholder The placeholder text to display in the confirm password
 * input field.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_password_change_confirm_password_placeholder(dialog_instance_t dialog, const char *placeholder);

/**
 * @brief Specify the layout to use on the virtual keyboard for the confirm
 * password input field
 *
 * The @c dialog_set_password_change_confirm_password_keyboard_layout() function
 * specifies, for the confirm password input field, the layout to use on the
 * virtual keyboard when it is visible while the dialog is showing.  Changing
 * the keyboard layout will disable any input flags set with @c
 * dialog_set_input_flags().
 *
 * @param dialog The dialog to update.
 *
 * @param layout The keyboard layout.  Must be one of the values of the @c
 * #virtualkeyboard_layout_t enumeration.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_password_change_confirm_password_keyboard_layout(dialog_instance_t dialog, int layout);

/**
 * @brief Deprecated: Password change dialogs do not have "Show password" check
 * boxes.
 *
 * @deprecated Password change dialogs do not have "Show password" check boxes.
 * Instead each password field has an integrated password visiblity toggle.
 * This function has no effect.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_password_change_show_password(dialog_instance_t dialog, bool show_password) BPS_DEPRECATED;

/**
 * @brief Deprecated: Password change dialogs do not have "Show password" check
 * boxes.
 *
 * @deprecated Password change dialogs do not have "Show password" check boxes.
 * Instead each password field has an integrated password visiblity toggle.
 * This function has no effect.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_password_change_show_password_label(dialog_instance_t dialog, const char *label) BPS_DEPRECATED;

/**
 * @brief Set the initial state of the "Remember me" check box
 *
 * The @c dialog_set_password_change_remember_me() function sets the initial
 * state of the "Remember me" check box for the specified password change
 * dialog.
 *
 * @param dialog The dialog to update.
 *
 * @param remember_me If @c true the "Remember me" check box is checked
 * initially, if @c false the "Remember me" check box is not checked initially.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_password_change_remember_me(dialog_instance_t dialog, bool remember_me);

/**
 * @brief Set the label for the "Remember me" check box
 *
 * The @c dialog_set_password_change_remember_me_label() function sets the label
 * for the "Remember me" check box. If this attribute is not set, the check box
 * and label are not displayed.
 *
 * @param dialog The dialog to update.
 *
 * @param label The check box label.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_password_change_remember_me_label(dialog_instance_t dialog, const char *label);

/**
 * @brief Get the contents of the password change dialog's username field from a
 * @c DIALOG_RESPONSE event
 *
 * The @c dialog_event_get_password_change_username() function gets the contents
 * of the username field when the password change dialog is dismissed by the
 * user (for example, when the user presses a button on the password change
 * dialog).
 *
 * @param event The @c DIALOG_RESPONSE event to get the contents of the username
 * field from.
 *
 * @return The contents of the username field.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char *dialog_event_get_password_change_username(bps_event_t *event);

/**
 * @brief Get the contents of the password change dialog's old password field
 * from a @c DIALOG_RESPONSE event
 *
 * The @c dialog_event_get_password_change_old_password() function gets the
 * contents of the old password field when the password change dialog is
 * dismissed by the user (for example, when the user presses a button on the
 * password change dialog).
 *
 * @param event The @c DIALOG_RESPONSE event to get the contents of the old
 * password field from.
 *
 * @return The contents of the old password field.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char *dialog_event_get_password_change_old_password(bps_event_t *event);

/**
 * @brief Get the contents of the password change dialog's new password field
 * from a @c DIALOG_RESPONSE event
 *
 * The @c dialog_event_get_password_change_new_password() function gets the
 * contents of the new password field when the password change dialog is
 * dismissed by the user (for example, when the user presses a button on the
 * password change dialog).
 *
 * @param event The @c DIALOG_RESPONSE event to get the contents of the new
 * password field from.
 *
 * @return The contents of the new password field.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char *dialog_event_get_password_change_new_password(bps_event_t *event);

/**
 * @brief Get the contents of the password change dialog's confirm password
 * field from a @c DIALOG_RESPONSE event
 *
 * The @c dialog_event_get_password_change_confirm_password() function gets the
 * contents of the confirm password field when the password change dialog is
 * dismissed by the user (for example, when the user presses a button on the
 * password change dialog).
 *
 * @param event The @c DIALOG_RESPONSE event to get the contents of the confirm
 * password field from.
 *
 * @return The contents of the confirm password field.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char *dialog_event_get_password_change_confirm_password(bps_event_t *event);

/**
 * @brief Get the state of the password change dialog's "Remember me" check box
 * from a @c DIALOG_RESPONSE event
 *
 * The @c dialog_event_get_password_change_remember_me() function gets the state
 * of the "Remember me" check box when the password change dialog is dismissed
 * by the user (for example, when the user presses a button on the password
 * change dialog).
 *
 * @param event The @c DIALOG_RESPONSE event to get the state of the "Remember
 * me" check box from.
 *
 * @return @c true if the "Remember me" check box is checked, @c false if the
 * "Remember me" check box is not checked.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API bool dialog_event_get_password_change_remember_me(bps_event_t *event);

/**
 * @brief Deprecated.
 *
 * @deprecated Use @c dialog_event_get_password_change_old_password()
 *
 * @param event The @c DIALOG_RESPONSE event to get the contents of the password
 * field from.
 *
 * @return The contents of the password field.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char *dialog_event_get_password_change_password(bps_event_t *event) BPS_DEPRECATED;


/**@}*/

/**
 * @name Progress dialog functions
 *
 * A progress dialog has a title, message, progress bar, progress details (left
 * and right), icon, and buttons.  Alert dialog functions can also be used on
 * prompt dialogs.
 *
 * @{
 */

/**
 * @brief Create a progress dialog
 *
 * The @c dialog_create_progress() function creates a progress dialog.
 *
 * @param dialog This will be populated with the newly created dialog instance.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_create_progress(dialog_instance_t *dialog);

/**
 * @brief Set the message text of a progress dialog
 *
 * The @c dialog_set_progress_message_text() function sets the message text of
 * the specified progress dialog.
 *
 * @param dialog The dialog to update.
 * @param text The message text to display.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_progress_message_text(dialog_instance_t dialog, const char *text);

/**
 * @brief Set whether the message text has emoticons
 *
 * The @c dialog_set_progress_message_has_emoticons() function sets whether the
 * message text has emoticons, and that they should be displayed graphically.
 *
 * @param dialog The dialog to update.
 *
 * @param has_emoticons If @c true display emoticons graphically, if @c false,
 * do not alter the appearance of emoticons.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_progress_message_has_emoticons(dialog_instance_t dialog, bool has_emoticons);

/**
 * @brief Set the progress level of a progress dialog
 *
 * The @c dialog_set_progress_level() function sets the progress level of the
 * specified progress dialog.
 *
 * @param dialog The dialog to update.
 * @param progress The progress level. A value representing the current level of
 *        progress from 0 to 100. To show an activity spinner indicating
 *        indefinite progress, specify -1.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_progress_level(dialog_instance_t dialog, int progress);

/**
 * @brief Set the icon of a progress dialog
 *
 * The @c dialog_set_progress_icon() function sets the icon of the specified
 * progress dialog.
 *
 * @param dialog The dialog to update.
 * @param path The absolute path of the icon to be shown.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_progress_icon(dialog_instance_t dialog, const char *path);

/**
 * @brief Set the progress state of a progress dialog
 *
 * The @c dialog_set_progress_state() function sets the progress state of the
 * specified progress dialog.
 *
 * @param dialog The dialog to update.
 * @param state The progress state to display.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_progress_state(dialog_instance_t dialog, dialog_progress_state_t state);

/**
 * @brief Set the left side details text of a progress dialog
 *
 * The @c dialog_set_progress_left_details() function sets the text to be
 * displayed on the left side underneath the progress bar of the specified
 * progress dialog. This text is not shown if the progress level is indefinite.
 *
 *
 * @param dialog The dialog to update.
 * @param text The left side details text to display.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_progress_left_details(dialog_instance_t dialog, const char *text);

/**
 * @brief Set the right side details text of a progress dialog
 *
 * The @c dialog_set_progress_right_details() function sets the text to be
 * displayed on the right side underneath the progress bar of the specified
 * progress dialog. This text is not shown if the progress level is indefinite.
 *
 *
 * @param dialog The dialog to update.
 * @param text The right side details text to display.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_progress_right_details(dialog_instance_t dialog, const char *text);

/**@}*/

/**
 * @name Notification dialog functions
 *
 * A notification dialog has a title, message, subject, start and end dates and
 * times, and an icon.  Alert dialog functions can also be used on notification
 * dialogs.
 *
 * @{
 */

/**
 * @brief Create a notification dialog
 *
 * The @c dialog_create_notification() function creates a notification dialog.
 *
 * @param dialog This will be populated with the newly created dialog instance.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_create_notification(dialog_instance_t *dialog);

/**
 * @brief Set the message text of a notification dialog
 *
 * The @c dialog_set_notification_message_text() function sets the message text
 * of the specified notification dialog.
 *
 * @param dialog The dialog to update.
 * @param text The message text to display.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_notification_message_text(dialog_instance_t dialog, const char *text);

/**
 * @brief Set whether the message text has emoticons
 *
 * The @c dialog_set_notification_message_has_emoticons() function sets whether the
 * message text has emoticons, and that they should be displayed graphically.
 *
 * @param dialog The dialog to update.
 *
 * @param has_emoticons If @c true display emoticons graphically, if @c false,
 * do not alter the appearance of emoticons.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_notification_message_has_emoticons(dialog_instance_t dialog, bool has_emoticons);

/**
 * @brief Set the subject text of a notification dialog
 *
 * The @c dialog_set_notification_subject_text() function sets the subject text
 * of the specified notification dialog.
 *
 * @param dialog The dialog to update.
 * @param text The subject text to display.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_notification_subject_text(dialog_instance_t dialog, const char *text);

/**
 * @brief Set the icon of a notification dialog
 *
 * The @c dialog_set_notification_icon() function sets the icon of the specified
 * notification dialog.
 *
 * @param dialog The dialog to update.
 * @param path The absolute path of the icon to be shown.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_notification_icon(dialog_instance_t dialog, const char *path);

/**
 * @brief Set the start date/time of a notification dialog
 *
 * The @c dialog_set_notification_start_date_time() function sets the start-date
 * time of the specified notification dialog.
 *
 * @param dialog The dialog to update.
 * @param time The start date/time. If specifying absolute time (for use with
 *        @c dialog_set_notification_start_date_format()) then in milliseconds
 *        since the epoch. If specifying relative time (for use with @c
 *        dialog_set_notification_start_date_format_elapsed()) then in
 *        milliseconds of elapsed time.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_notification_start_date_time(dialog_instance_t dialog, long long time);

/**
 * @brief Set the start-date format of a notification dialog
 *
 * The @c dialog_set_notification_start_date_format() function sets the start
 * date format of the specified notification dialog.
 *
 * @param dialog The dialog to update.
 * @param date_format The format of the date portion of the start date/time.
 * @param time_format The format of the time portion of the start date/time.
 * @param week_format The format of the week portion of the start date/time.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_notification_start_date_format(dialog_instance_t dialog, dialog_date_time_format_t date_format, dialog_date_time_format_t time_format, dialog_date_time_format_t week_format);

/**
 * @brief Set the start-date format of elapsed time of a notification dialog
 *
 * The @c dialog_set_notification_start_date_format_elapsed() function sets the
 * start-date format of elapsed time of the specified notification dialog.
 *
 * @param dialog The dialog to update.
 * @param elapsed_format The format of the relative start date/time.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_notification_start_date_format_elapsed (dialog_instance_t dialog, dialog_date_time_format_t elapsed_format);

/**
 * @brief Set the end date/time of a notification dialog
 *
 * The @c dialog_set_notification_end_date_time() function sets the end-date
 * time of the specified notification dialog.
 *
 * @param dialog The dialog to update.
 * @param time The end date/time. If specifying absolute time (for use with @c
 *        dialog_set_notification_end_date_format()) then in milliseconds since
 *        the epoch. If specifying relative time (for use with @c
 *        dialog_set_notification_end_date_format_elapsed()) then in
 *        milliseconds of elapsed time.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_notification_end_date_time(dialog_instance_t dialog, long long time);

/**
 * @brief Set the end-date format of a notification dialog
 *
 * The @c dialog_set_notification_end_date_format() function sets the end-date
 * format of the specified notification dialog.
 *
 * @param dialog The dialog to update.
 * @param date_format The format of the date portion of the end date/time.
 * @param time_format The format of the time portion of the end date/time.
 * @param week_format The format of the week portion of the end date/time.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_notification_end_date_format(dialog_instance_t dialog, dialog_date_time_format_t date_format, dialog_date_time_format_t time_format, dialog_date_time_format_t week_format);

/**
 * @brief Set the end-date format of elapsed time of a notification dialog
 *
 * The @c dialog_set_notification_end_date_format_elapsed() function sets the
 * end-date format of elapsed time of the specified notification dialog.
 *
 * @param dialog The dialog to update.
 * @param elapsed_format The format of the relative end date/time.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_notification_end_date_format_elapsed (dialog_instance_t dialog, dialog_date_time_format_t elapsed_format);

/**
 * @brief Set whether the content is locked in a notification dialog
 *
 * The @c dialog_set_notification_content_locked() function sets whether the
 * content is locked in the specified notification dialog.
 *
 * @param dialog The dialog to update.
 * @param locked If @c true, the content is locked; if @c false, the content is
 *        not locked.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_notification_content_locked(dialog_instance_t dialog, bool locked);

/**
 * @brief Set whether the content is selectable in a notification dialog
 *
 * The @c dialog_set_notification_content_selectable() function sets whether the
 * content is selectable in the specified notification dialog.
 *
 * @param dialog The dialog to update.
 * @param selectable If @c true, the content is selectable; if @c false, the
 *        content is not selectable.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_notification_content_selectable(dialog_instance_t dialog, bool selectable);

/**@}*/

/**
 * @name Toast Dialog setters
 *
 * These functions can be used to set attributes that are common to all types of
 * toast dialogs, unless specifically noted by a particular toast dialog type.
 *
 * @{
 */

/**
 * @brief Set the message text of a toast dialog
 *
 * The @c dialog_set_toast_message_text() function sets the message text of the
 * specified toast dialog.
 *
 * @param dialog The dialog to update.
 * @param text The message text to display.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_toast_message_text(dialog_instance_t dialog, const char *text);

/**
 * @brief Set the position of a toast dialog
 *
 * The @c dialog_set_toast_position() function sets the position of the
 * specified toast dialog. If the toast dialog position is not set, the position
 * of the toast dialog is set to the default value of @c
 * DIALOG_POSITION_MIDDLE_CENTER.
 *
 * @param dialog The dialog to update.
 * @param position The position to set.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_toast_position(dialog_instance_t dialog, dialog_position_t position);

/**@}*/

/**
 * @name Toast dialog functions
 *
 * A toast dialog is a simple toast dialog that displays a message and an
 * optional button.
 *
 * @{
 */

/**
 * @brief Create a toast dialog
 *
 * The @c dialog_create_toast() function creates a toast dialog.
 *
 * @param dialog This will be populated with the newly created dialog instance.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_create_toast(dialog_instance_t *dialog);

/**@}*/

/**
 * @name Icon Toast dialog functions
 *
 * An icon toast dialog is a simple toast dialog that displays a message, an
 * icon, and an optional button.
 *
 * @{
 */

/**
 * @brief Create an icon toast dialog
 *
 * The @c dialog_create_icon_toast() function creates an icon toast dialog.
 *
 * @param dialog This will be populated with the newly created dialog instance.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_create_icon_toast(dialog_instance_t *dialog);

/**
 * @brief Set the icon of an icon toast dialog
 *
 * The @c dialog_set_toast_icon() function sets the icon of the specified icon
 * toast dialog.
 *
 * @param dialog The dialog to update.
 * @param path The absolute path of the icon to be shown.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_toast_icon(dialog_instance_t dialog, const char *path);

/**@}*/

/**
 * @name Progress Toast dialog functions
 *
 * A progress toast dialog is a simple toast dialog that displays a message, a
 * progress indicator, and an optional button.
 *
 * @{
 */

/**
 * @brief Create a progress toast dialog
 *
 * The @c dialog_create_progress_toast() function creates a progress toast
 * dialog.
 *
 * @param dialog This will be populated with the newly created dialog instance.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_create_progress_toast(dialog_instance_t *dialog);

/**
 * @brief Set the progress state of a progress toast dialog
 *
 * The @c dialog_set_progress_toast_state() function sets the progress state of
 * the specified progress toast dialog.
 *
 * @param dialog The dialog to update.
 * @param state The progress state to display.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_progress_toast_state(dialog_instance_t dialog, dialog_progress_state_t state);

/**
 * @brief Set the progress level of a progress toast dialog
 *
 * The @c dialog_set_progress_toast_level() function sets the progress level of
 * the specified progress toast dialog.
 *
 * @param dialog The dialog to update.
 * @param progress The progress level. A value representing the current level of
 *        progress from 0 to 100. To show an activity spinner indicating
 *        indefinite progress, specify -1.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_progress_toast_level(dialog_instance_t dialog, int progress);

/**
 * @brief Set the details text of a progress toast dialog
 *
 * The @c dialog_set_progress_toast_details() function sets the text to be
 * displayed on the right side underneath the progress bar of the specified
 * progress toast dialog.
 *
 * @param dialog The dialog to update.
 * @param text The details text to display.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_progress_toast_details(dialog_instance_t dialog, const char *text);

/**@}*/

/**
 * @name Volume Toast dialog functions
 *
 * A volume toast dialog is a simple toast dialog that displays a message and a
 * volume indicator.
 *
 * @{
 */

/**
 * @brief Create a volume toast dialog
 *
 * The @c dialog_create_volume_toast() function creates a volume toast dialog.
 *
 * @param dialog This will be populated with the newly created dialog instance.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_create_volume_toast(dialog_instance_t *dialog);

/**
 * @brief Set the device text of a volume toast dialog
 *
 * The @c dialog_set_volume_toast_device_text() function sets the text
 * describing the the device currently playing audio on the specified volume
 * toast dialog.
 *
 * @param dialog The dialog to update.
 * @param text The device text to display.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_volume_toast_device_text(dialog_instance_t dialog, const char *text);

/**
 * @brief Set whether to indicate that volume is muted on a volume toast dialog
 *
 * The @c dialog_set_volume_toast_device_text() function sets whether to
 * indicate that volume is muted on the specified volume toast dialog.
 *
 * @param dialog The dialog to update.
 * @param muted If @c true, the volume is muted; if @c false, the volume is not
 *        muted.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_volume_toast_muted(dialog_instance_t dialog, bool muted);

/**
 * @brief Set the volume level on a volume toast dialog
 *
 * The @c dialog_set_volume_toast_device_text() function sets the volume level
 * on the specified volume toast dialog.
 *
 * @param dialog The dialog to update.
 * @param level The volume level.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_volume_toast_level(dialog_instance_t dialog, int level);

/**
 * @brief Set the volume direction on a volume toast dialog
 *
 * The @c dialog_set_volume_toast_device_text() function sets the volume
 * direction on the specified volume toast dialog.
 *
 * @param dialog The dialog to update.
 * @param direction The volume direction.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_volume_toast_direction(dialog_instance_t dialog, dialog_volume_direction_t direction);

/**
 * @brief Set the volume control on a volume toast dialog
 *
 * The @c dialog_set_volume_toast_device_text() function sets the volume control
 * on the specified volume toast dialog.
 *
 * @param dialog The dialog to update.
 * @param control The volume control.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_volume_toast_control(dialog_instance_t dialog, dialog_volume_control_t control);

/**@}*/

/**
 * @name File browse dialog functions
 *
 * @deprecated File browse dialogs no longer appear. Attempting to show a file
 * browse dialog generates a @c DIALOG_RESPONSE event containing an error
 * message that can be retrieved using the @c dialog_event_get_error() function.
 *
 * @{
 */

/**
 * @brief Deprecated: File browse dialogs no longer appear.
 *
 * @deprecated File browse dialogs no longer appear. Attempting to show a file
 * browse dialog generates a @c DIALOG_RESPONSE event containing an error
 * message that can be retrieved using the @c dialog_event_get_error() function.
 * This function has no effect.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_create_filebrowse(dialog_instance_t *dialog) BPS_DEPRECATED;

/**
 * @brief Deprecated: File browse dialogs no longer appear.
 *
 * @deprecated File browse dialogs no longer appear. Attempting to show a file
 * browse dialog generates a @c DIALOG_RESPONSE event containing an error
 * message that can be retrieved using the @c dialog_event_get_error() function.
 * This function has no effect.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_filebrowse_multiselect(dialog_instance_t dialog, bool multi_select) BPS_DEPRECATED;

/**
 * @brief Deprecated: File browse dialogs no longer appear.
 *
 * @deprecated File browse dialogs no longer appear. Attempting to show a file
 * browse dialog generates a @c DIALOG_RESPONSE event containing an error
 * message that can be retrieved using the @c dialog_event_get_error() function.
 * This function has no effect.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_filebrowse_filter(dialog_instance_t dialog, const char *extensions[], int num_items) BPS_DEPRECATED;

/**
 * @brief Deprecated: File browse dialogs no longer appear.
 *
 * @deprecated File browse dialogs no longer appear. Attempting to show a file
 * browse dialog generates a @c DIALOG_RESPONSE event containing an error
 * message that can be retrieved using the @c dialog_event_get_error() function.
 * This function has no effect.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_event_get_filebrowse_filepaths(bps_event_t *event, char **file_paths[], int *num_paths) BPS_DEPRECATED;

/**@}*/

/**
 * @name File save dialog functions
 *
 * @deprecated File save dialogs no longer appear. Attempting to show a file
 * save dialog generates a @c DIALOG_RESPONSE event containing an error
 * message that can be retrieved using the @c dialog_event_get_error() function.
 *
 * @{
 */

/**
 * @brief Deprecated: File save dialogs no longer appear.
 *
 * @deprecated File save dialogs no longer appear. Attempting to show a file
 * save dialog generates a @c DIALOG_RESPONSE event containing an error
 * message that can be retrieved using the @c dialog_event_get_error() function.
 * This function has no effect.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_create_filesave(dialog_instance_t *dialog) BPS_DEPRECATED;

/**
 * @brief Deprecated: File save dialogs no longer appear.
 *
 * @deprecated File save dialogs no longer appear. Attempting to show a file
 * save dialog generates a @c DIALOG_RESPONSE event containing an error
 * message that can be retrieved using the @c dialog_event_get_error() function.
 * This function has no effect.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int dialog_set_filesave_filename(dialog_instance_t dialog, const char *filename) BPS_DEPRECATED;

/**
 * @brief Deprecated: File save dialogs no longer appear.
 *
 * @deprecated File save dialogs no longer appear. Attempting to show a file
 * save dialog generates a @c DIALOG_RESPONSE event containing an error
 * message that can be retrieved using the @c dialog_event_get_error() function.
 * This function has no effect.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char *dialog_event_get_filesave_filepath(bps_event_t *event) BPS_DEPRECATED;

/**@}*/

__END_DECLS

#endif /* _BPS_DIALOG_H_INCLUDED */
