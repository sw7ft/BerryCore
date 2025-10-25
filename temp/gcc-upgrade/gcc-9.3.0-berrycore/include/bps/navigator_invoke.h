/*
 * Copyright (C) 2012-2014 BlackBerry Limited. All rights reserved.
 */

/**
 * @file navigator_invoke.h
 *
 * @brief Functions and structures to create, configure, and send application or
 *        card invocations and queries
 *
 * The Navigator Invoke API defines the invocation framework service, which
 * allows you to send and receive application or card invocations, to send
 * queries to the invocation framework, and to send data between a parent
 * application and the corresponding card.
 *
 * This has a number of uses, including:
 *
 * Creating, customizing, and sending a handler invocation using the action and
 * the type, and passing necessary data directly to the handler:
 * @code
 *   // create handler invocation
 *   navigator_invoke_invocation_t *invoke = NULL;
 *   navigator_invoke_invocation_create(&invoke);
 *
 *   // set invocation action and type
 *   navigator_invoke_invocation_set_action(invoke,
 *       "com.example.action.SET_SCREEN_COLOR");
 *   navigator_invoke_invocation_set_type(invoke,
 *       "application/com.example.type");
 *
 *   // pass arbitrary data (in this example, set screen color value to yellow)
 *   int screen_color = 0xffffff00;
 *   navigator_invoke_invocation_set_data(invoke, &screen_color, sizeof(int));
 *
 *   // invoke the target
 *   navigator_invoke_invocation_send(invoke);
 *
 *   // clean up resources
 *   navigator_invoke_invocation_destroy(invoke);
 * @endcode
 *
 * Decoding an invocation request from a BPS event on the target handler's side:
 * @code
 *   switch (bps_event_get_code(event)) {
 *     case NAVIGATOR_INVOKE_TARGET: {
 *       const navigator_invoke_invocation_t *invoke =
 *           navigator_invoke_event_get_invocation(event);
 *       // an invocation has been received
 *       if(invoke) {
 *         // retrieve invocation action
 *         const char *action = navigator_invoke_invocation_get_action(invoke);
 *
 *         // if invocation includes data, retrieve data
 *         if(navigator_invoke_invocation_get_data_length(invoke) > 0) {
 *           // set color to value passed by invocation
 *           const int *p;
 *           p = navigator_invoke_invocation_get_data(invoke);
 *           change_color(*p);
 *         }
 *       }
 *     }
 *     break;
 *   }
 * @endcode
 *
 * Decoding the invocation target response's ID and the error from a BPS event:
 * @code
 *   switch (bps_event_get_code(event)) {
 *     case NAVIGATOR_INVOKE_TARGET_RESULT: {
 *       const char *id = navigator_event_get_id(event);
 *       const char *err = navigator_event_get_err(event);
 *     }
 *     break;
 *   }
 * @endcode
 *
 * Creating, customizing, and sending a handler invocation using the action and
 * the type, and passing the URI location of the data to be passed to the
 * handler:
 * @code
 *   // create handler invocation
 *   navigator_invoke_invocation_t *invoke = NULL;
 *   navigator_invoke_invocation_create(&invoke);
 *
 *   // set action and type (in this example, view a jpeg image)
 *   navigator_invoke_invocation_set_action(invoke, "com.example.action.VIEW");
 *   navigator_invoke_invocation_set_type(invoke, "image/jpeg");
 *
 *   // pass URI pointing to the data (in this example, the image to view)
 *   navigator_invoke_invocation_set_uri(invoke, "file:///accounts/1000/appdata/com.example.application.123456789123456789123456789/data/image%201.jpg");
 *
 *   // invoke the target
 *   navigator_invoke_invocation_send(invoke);
 *
 *   // clean up resources
 *   navigator_invoke_invocation_destroy(invoke);
 * @endcode
 *
 * Decoding the URI path to the invocation data from a BPS event on the target
 * handler's side:
 * @code
 *   switch (bps_event_get_code(event)) {
 *     case NAVIGATOR_INVOKE_TARGET: {
 *       const navigator_invoke_invocation_t *invoke =
 *           navigator_invoke_event_get_invocation(event);
 *       // an invocation has been received
 *       if(invoke) {
 *         // retrieve action, MIME type, and URI of the image from the
 *         // invocation
 *         const char *action = navigator_invoke_invocation_get_action(invoke);
 *         const char *mime_type = navigator_invoke_invocation_get_type(invoke);
 *         const char *image_uri = navigator_invoke_invocation_get_uri(invoke);
 *         // view image located at the defined URI
 *         view_image(image_uri);
 *       }
 *     }
 *     break;
 *   }
 * @endcode
 *
 * Invoking a handler with a known target ID:
 * @code
 *   // create handler invocation
 *   navigator_invoke_invocation_t *invoke = NULL;
 *   navigator_invoke_invocation_create(&invoke);
 *
 *   // set action
 *   navigator_invoke_invocation_set_action(invoke,
 *       "com.example.action.SET_SCREEN_COLOR");
 *   // set handler ID
 *   navigator_invoke_invocation_set_target(invoke,
 *       "com.example.DefaultHandler");
 *
 *   // invoke the target
 *   navigator_invoke_invocation_send(invoke);
 *
 *   // clean up resources
 *   navigator_invoke_invocation_destroy(invoke);
 * @endcode
 *
 * Sending a query for a find a specific action and type:
 * @code
 *   // create query
 *   navigator_invoke_query_t *query = NULL;
 *   navigator_invoke_query_create(&query);
 *
 *   // set query ID
 *   navigator_invoke_query_set_id(query, "123");
 *   // set action and type to query for
 *   navigator_invoke_query_set_action(query, "bb.action.SHARE");
 *   navigator_invoke_query_set_type(query, "image/png");
 *
 *   // send query
 *   navigator_invoke_query_send(query);
 * @endcode
 *
 * Handling a query response:
 * @code
 *   switch (bps_event_get_code(event)) {
 *     case NAVIGATOR_INVOKE_QUERY_RESULT: {
 *       const char *id = navigator_event_get_id(event);
 *
 *       // create integer holding the number of actions returned by the query
 *       int action_count =
 *           navigator_invoke_event_get_query_result_action_count(event);
 *       int i=0;
 *       // loop listing all actions returned by the query
 *       for (; i < action_count; i++) {
 *         const navigator_invoke_query_result_action_t *action =
 *             navigator_invoke_event_get_query_result_action(event, i);
 *
 *         // retrieve action attributes
 *         const char *name =
 *             navigator_invoke_query_result_action_get_name(action);
 *         const char *icon =
 *             navigator_invoke_query_result_action_get_icon(action);
 *         const char *label =
 *             navigator_invoke_query_result_action_get_label(action);
 *
 *         // create integer holding the number of targets in the action
 *         int target_count =
 *             navigator_invoke_query_result_action_get_target_count(action);
 *
 *         int j=0;
 *         // loop listing all targets in the action
 *         for (; j < target_size; j++) {
 *           const navigator_invoke_query_result_target_t *target =
 *               navigator_invoke_query_result_action_get_target(action, j);
 *
 *           // retrieve target attributes
 *           const char *target_key =
 *               navigator_invoke_query_result_target_get_key(target);
 *           const char *target_icon =
 *               navigator_invoke_query_result_target_get_icon(target);
 *           const char *target_splash =
 *               navigator_invoke_query_result_target_get_splash(target);
 *           const char *target_label =
 *               navigator_invoke_query_result_target_get_label(target);
 *           navigator_invoke_target_type_t target_type =
 *               navigator_invoke_query_result_target_get_type(target);
 *           navigator_invoke_perimeter_type_t perimeter =
 *               navigator_invoke_query_result_target_get_perimeter(target);
 *         }
 *       }
 *     }
 *   }
 * @endcode
 *
 * Registering a recurrence rule as a timer trigger for a headless application:
 *
 * A recurrence rule specifies the interval at which to trigger a headless
 * application. The recurrence is invoked by a timer registration.
 * A recurrence rule has one of the frequencies enumerated in
 * @c #navigator_invoke_recurrence_rule_frequency_t.
 * It can have a date limit or a count limit.
 * The date limit specifies the date at which the recurrence ends.
 * The count limit specifies the number of times of the recurrence.
 * The interval is a positive integer identifying the interval of repetition for
 * the rule. The default interval is related to the interval type. For example,
 * the default interval for a @c
 * NAVIGATOR_INVOKE_RECURRENCE_RULE_FREQUENCY_HOURLY rule is every hour, and the
 * default interval for a @c NAVIGATOR_INVOKE_RECURRENCE_RULE_FREQUENCY_WEEKLY
 * rule is every week. Setting a @c
 * NAVIGATOR_INVOKE_RECURRENCE_RULE_FREQUENCY_DAILY rule to an interval of 2
 * sets the interval to every other day.
 * The start date specifies the date at which the recurrence starts. It defaults
 * to the present date.
 * Additionally, the rule can be further modified by specifying recurrences such
 * as minutes of the hour, hours of the day, days of the week and months of the
 * year.
 *
 * The following sample code demonstrates how to register a daily recurrent
 * timer that fires at 10AM and 5PM, beginning January 1st, 2014. The headless
 * target is invoked on the specified time slot with the action
 * 'bb.action.system.TIMER_FIRED'. Note that error handling is omitted for
 * clarity.
 *
 * @code
 *  navigator_invoke_timer_registration_t *reg = NULL;
 *  navigator_invoke_recurrence_rule_t *rule = NULL;
 *  navigator_invoke_specific_time_t *start_date = NULL;
 *
 *  navigator_invoke_timer_registration_create(&reg, NAVIGATOR_INVOKE_TIMER_TRIGGER_RECURRENT);
 *  navigator_invoke_recurrence_rule_create(&rule, NAVIGATOR_INVOKE_RECURRENCE_RULE_FREQUENCY_DAILY);
 *
 *  int hours_of_day[] = {10, 17};
 *  // 10 and 17 correspond to 10AM and 5PM, respectively.
 *  // These are the times the timer trigger will be activated.
 *  navigator_invoke_recurrence_rule_set_hours_of_day(rule, hours_of_day, 2);
 *
 *  // specify a start date from when the trigger should activate - mandatory
 *  // January 1st, 2014 at 00:00 (America/New_York timezone)
 *  navigator_invoke_specific_time_create(&start_date);
 *  navigator_invoke_specific_time_set_year(start_date, 2014);
 *  navigator_invoke_specific_time_set_month(start_date, 1);
 *  navigator_invoke_specific_time_set_day(start_date, 1);
 *  navigator_invoke_specific_time_set_hour(start_date, 0);
 *  navigator_invoke_specific_time_set_minute(start_date, 0);
 *  navigator_invoke_specific_time_set_time_zone(start_date, "America/New_York");
 *  navigator_invoke_recurrence_rule_set_start_date(rule, start_date);
 *
 *  navigator_invoke_timer_registration_set_id(reg, "123");
 *  navigator_invoke_timer_registration_set_action(reg, NAVIGATOR_INVOKE_TIMER_ACTION_REGISTER);
 *  navigator_invoke_timer_registration_set_target(reg, "com.example.MyHeadlessTarget");
 *  navigator_invoke_timer_registration_set_recurrence_rule(reg, rule);
 *  navigator_invoke_timer_registration_send(reg);
 *
 *  navigator_invoke_specific_time_destroy(start_date);
 *  navigator_invoke_recurrence_rule_destroy(rule);
 *  navigator_invoke_timer_registration_destroy(reg);
 * @endcode
 *
 * @since BlackBerry 10.0.0
 */

#ifndef _BPS_NAVIGATOR_INVOKE_H_INCLUDED
#define _BPS_NAVIGATOR_INVOKE_H_INCLUDED

#include <stdbool.h>
#include <unistd.h>
#include "bps/bps.h"

__BEGIN_DECLS

/**
 * @brief The opaque invocation argument type
 *
 * This type defines the @c #navigator_invoke_invocation_t structure used by
 * several functions in the invocation framework. Use this to create and control
 * invocations. The @c #navigator_invoke_invocation_t structure is opaque, but
 * includes the following members:
 *     - @b ID: the ID used to identify the invocation
 *              (@c navigator_invoke_invocation_set_id())
 *     - @b Target: the target to which the invocation is sent
 *              (@c navigator_invoke_invocation_set_target())
 *     - @b Source: the location where response messages to the invocation
 *              should be sent (@c navigator_invoke_invocation_set_source())
 *     - @b Action: the action the invoked target should perform
 *              (@c navigator_invoke_invocation_set_action())
 *     - @b Type: the MIME type of the data the invoked target should act on
 *              (@c navigator_invoke_invocation_set_type())
 *     - @b URI: the URI to the data the invoked target should act on
 *              (@c navigator_invoke_invocation_set_uri())
 *     - @b Transfer @b mode: the transfer mode for the URI file
 *              (@c navigator_invoke_invocation_set_file_transfer_mode())
 *     - @b Data: the data the invoked target should act on
 *              (@c navigator_invoke_invocation_set_data())
 *     - @b Data @b length: the length of the data the invoked target should act
 *              on (@c navigator_invoke_invocation_set_data())
 *     - @b Perimeter: the perimeter the target should be invoked in
 *              (@c navigator_invoke_invocation_set_perimeter())
 *     - @b List @b ID: the id of the list the invocation is associated with
 *              (@c navigator_invoke_invocation_set_list_id())
 *
 * To perform an invocation, you must:
 *     1. Instantiate a @c #navigator_invoke_invocation_t structure with the @c
 *        navigator_invoke_invocation_create() function.
 *     2. Set all desired members with the @c
 *        navigator_invoke_invocation_set_*() functions to match the purpose of
 *        the @c invocation. A minimum of either a @c target, @c action, or @c
 *        type member is required for the @c invocation to be recognised by the
 *        framework (though further members may be required for more specific
 *        invocations, such as including a @c uri or @c data member for
 *        invocations that require input data to be successfully performed.)
 *     3. Send the @c invocation with the @c navigator_invoke_invocation_send()
 *        function. Depending on the members you set to the @c
 *        #navigator_invoke_invocation_t structure, the invocation is sent
 *        either directly to a target handler or the brokering system to
 *        determine which target to use based on the provided information.
 *     4. Retrieve the data from an @c invocation in an event handler by using
 *        the navigator_invoke_invocation_get_*() functions.
 *     5. Deallocate the memory reserved for the @c
 *        #navigator_invoke_invocation_t structure with the @c
 *        navigator_invoke_invocation_destroy() function.
 *
 * @since BlackBerry 10.0.0
 */
typedef struct navigator_invoke_invocation_t navigator_invoke_invocation_t;

/**
 * @brief The opaque query argument type
 *
 * This type defines the @c #navigator_invoke_query_t structure used by several
 * functions in the invocation framework. Use this to create and control
 * queries. The @c #navigator_invoke_query_t structure is opaque, but includes
 * the following members:
 *     - @b ID: the ID used to identify the query
 *              (@c navigator_invoke_query_set_id())
 *     - @b Action: the action query results should be able to perform
 *              (@c navigator_invoke_query_set_action())
 *     - @b Type: the MIME type the query results should be able to act on
 *              (@c navigator_invoke_query_set_type())
 *     - @b File @b URI: the URI to the type interface the query results should
 *              be able to act on (@c navigator_invoke_query_get_file_uri())
 *     - @b Target @b type: the type of targets the query should filter for
 *              (@c navigator_invoke_query_set_target_type_mask())
 *     - @b Action @b type: the type of actions the query should filter for
 *              (@c navigator_invoke_query_set_action_type())
 *     - @b Perimeter: the perimeter the query results should be invoked in
 *              (@c navigator_invoke_query_set_perimeter())
 *
 * To perform an invocation query, you must:
 *     1. Instantiate a @c #navigator_invoke_query_t structure with the @c
 *        navigator_invoke_query_create() function.
 *     2. Set all desired members with the @c navigator_invoke_query_set_*()
 *        functions to match the purpose of the @c query.
 *     3. Send the @c query with the @c navigator_invoke_query_send()
 *        function. The query is sent to the brokering system, which returns a
 *        set of results that correspond to the @c #navigator_invoke_query_t
 *        structure parameters.
 *     4. Deallocate the memory reserved for the @c #navigator_invoke_query_t
 *        structure with the @c navigator_invoke_query_destroy() function.
 *
 * @since BlackBerry 10.0.0
 */
typedef struct navigator_invoke_query_t navigator_invoke_query_t;

/**
 * @brief The opaque query result action argument type
 *
 * This type defines the @c #navigator_invoke_query_result_action_t structure
 * used by several functions in the invocation framework. Use this to retrieve
 * actions returned from invocation query results. The @c
 * #navigator_invoke_query_result_action_t structure is opaque, but includes the
 * following members:
 *     - @b Name: the name of the action
 *                (@c navigator_invoke_query_result_action_get_name())
 *     - @b Icon: an image associated with the action
 *                (@c navigator_invoke_query_result_action_get_icon())
 *     - @b Label: the label or name associated with the action
 *                (@c navigator_invoke_query_result_action_get_label())
 *     - @b Default @b target: the target that will provide this action by
 *                default
 *                (@c navigator_invoke_query_result_action_get_default_target())
 *     - @b Target @b count: the number of viable targets that can perform the
 *                action (@c navigator_invoke_query_result_action_get_target())
 *     - @b Targets: an array of all viable targets that can perform the
 *                action (@c navigator_invoke_query_result_action_get_target())
 *
 * The @c #navigator_invoke_query_result_action_t structure is returned by an
 * invocation query. Extract values from this structure using the @c
 * navigator_invoke_query_result_action_get_*() functions.
 *
 * @since BlackBerry 10.0.0
 */
typedef struct navigator_invoke_query_result_action_t navigator_invoke_query_result_action_t;

/**
 * @brief The opaque query result target argument type
 *
 * This type defines the @c #navigator_invoke_query_result_target_t structure
 * used by several functions in the invocation framework. Use this to retrieve
 * targets returned from invocation query results, and contained within @c
 * #navigator_invoke_query_result_action_t structures. The @c
 * #navigator_invoke_query_result_target_t structure is opaque, but includes the
 * following members:
 *     - @b Key: the name of the target
 *               (@c navigator_invoke_query_result_target_get_key())
 *     - @b Icon: an image associated with the target
 *               (@c navigator_invoke_query_result_target_get_icon())
 *     - @b Splash: an image to be displayed by a target when loading
 *               (@c navigator_invoke_query_result_target_get_splash())
 *     - @b Label: the label or name associated with the target
 *               (@c navigator_invoke_query_result_target_get_label())
 *     - @b Type: the target's type
 *               (@c navigator_invoke_query_result_target_get_type())
 *     - @b Perimeter: the perimeter in which the target should reside
 *               (@c navigator_invoke_query_result_target_get_perimeter())
 *
 * The @c #navigator_invoke_query_result_target_t structures are contained
 * within @c #navigator_invoke_query_result_action_t structures that are
 * returned by an invocation query. Extract values from this structure using the
 * @c navigator_invoke_query_result_target_get_*() functions.
 *
 * @since BlackBerry 10.0.0
 */
typedef struct navigator_invoke_query_result_target_t navigator_invoke_query_result_target_t;

/**
 * @brief The use of viewers has been deprecated - use applications or cards as
 *        invocation targets instead
 *
 * @deprecated The use of viewers has been deprecated - use applications or
 *             cards as invocation targets instead.
 *
 * This type defines the @c #navigator_invoke_viewer_t structure used by several
 * functions in the invocation framework. Use this to create and control
 * viewers. The @c #navigator_invoke_viewer_t structure is opaque, but includes
 * the following members:
 *     - @b Invocation: the invocation associated with the viewer
 *                 (@c navigator_invoke_viewer_create())
 *     - @b Window @b ID: the ID used to identify the viewer
 *                 (@c navigator_invoke_viewer_set_window_id())
 *     - @b Width: the width of the viewer
 *                 (@c navigator_invoke_viewer_set_width())
 *     - @b Height: the height of the viewer
 *                 (@c navigator_invoke_viewer_set_height())
 *
 * To create an invocation viewer, you must:
 *     1. Instantiate a @c #navigator_invoke_viewer_t structure with the @c
 *        navigator_invoke_viewer_create() function.
 *     2. Set all desired members with the @c navigator_invoke_viewer_set_*()
 *        functions to match the purpose of the @c viewer.
 *     3. Send the @c viewer with the @c navigator_invoke_viewer_send()
 *        function. The invocation is sent to an event handler, triggering the
 *        NAVIGATOR_INVOKE_VIEWER event.
 *     4. Retrieve the data from a @c viewer in an event handler by using
 *        the navigator_invoke_viewer_get_*() functions, within this, further
 *        data from the invocation can be retrieved through the @c
 *        #navigator_invoke_invocation_t structure using the @c
 *        navigator_invoke_viewer_get_invocation() function followed by the @c
 *        navigator_invoke_invocation_get_*() functions.
 *     5. Deallocate the memory reserved for the @c #navigator_invoke_viewer_t
 *        with the @c navigator_invoke_viewer_destroy() function.
 *
 * @since BlackBerry 10.0.0
 */
typedef struct navigator_invoke_viewer_t navigator_invoke_viewer_t;

/**
 * @brief The opaque recurrence rule argument type
 *
 * This type defines the @c #navigator_invoke_recurrence_rule_t structure
 * used by timer trigger registration requests. Use the recurrence rule to
 * define when a target should be invoked.
 *
 * @since BlackBerry 10.3.0
 */
typedef struct navigator_invoke_recurrence_rule_t
            navigator_invoke_recurrence_rule_t;

/**
 * @brief The opaque specific time argument type
 *
 * This type defines the @c #navigator_invoke_specific_time_t structure
 * used by timer trigger registration requests. Use an instance of this
 * structure to define the specific time a target should be invoked.
 *
 * @since BlackBerry 10.3.0
 */
typedef struct navigator_invoke_specific_time_t
            navigator_invoke_specific_time_t;


/**
 * @brief The opaque timer registration request type
 *
 * This type defines the @c #navigator_invoke_timer_registration_t structure
 * used by timer trigger registration requests.
 *
 * @since BlackBerry 10.3.0
 */
typedef struct navigator_invoke_timer_registration_t
            navigator_invoke_timer_registration_t;

/**
 * @brief The possible invocation target types
 *
 * This enumeration defines the possible types of targets to query for with the
 * @c #navigator_invoke_query_t structure. This is used by the brokering system
 * to filter for targets that are of the given type.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * Indicates that the target type is unspecified.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_INVOKE_TARGET_TYPE_UNSPECIFIED = 0x00,
    /**
     * Indicates that the target is an application. Applications are software
     * designed to perform specific tasks.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_INVOKE_TARGET_TYPE_APPLICATION = 0x01,
    /**
    * Indicates that the target is a card. Cards are compact windows that allow
    * an application to expose functionality so that it can be imported in to
    * the flow of another application. Cards may be stacked multiple layers
    * when one card uses another. However, each layer of the stack can stack
    * only one child card at a time. For example, the Universal Inbox list may
    * stack a card to preview an email message. The message card may in turn
    * stack a card to preview an image attachment. The attachment card may
    * then also stack a card to share the image, and so on. The peeking
    * feature exclusive to cards allows users to "peek" back behind the current
    * card to reveal its parent's content using a swipe gesture. Peeking is
    * handled in the Navigator API.
     *
     * @since BlackBerry 10.0.0
    */
   NAVIGATOR_INVOKE_TARGET_TYPE_CARD         = 0x02,
   /**
    * @deprecated The use of viewers has been deprecated - use applications or
    *             cards as invocation targets instead.
    *
    * Indicates that the target is a viewer. Viewers are embedded applications
    * that can render a certain content type (images for example). They appear
    * as part of the root application rather than as a separate application.
    *
    * @since BlackBerry 10.0.0
    */
    NAVIGATOR_INVOKE_TARGET_TYPE_VIEWER      = 0x04,
    /**
     * Indicates that the target is a service. The meaning of a service value is
     * reserved for future use.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_INVOKE_TARGET_TYPE_SERVICE     = 0x08,
    /**
     * Indicates that the matched targets belonging to the current application
     * should be returned in the query result.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_INVOKE_TARGET_TYPE_SELF        = 0x10,
    /**
     * Indicates that the target is a headless application.
     *
     * @since BlackBerry 10.3.0
     */
    NAVIGATOR_INVOKE_TARGET_TYPE_HEADLESS    = 0x40
} navigator_invoke_target_type_t;


/**
 * @brief The possible invocation query action type values
 *
 * This enumeration defines the possible types of actions to query for with the
 * @c #navigator_invoke_query_t structure. This is used by the brokering system
 * to filter for targets that use the given action type.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * Indicates that the query action type is unspecified.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_INVOKE_QUERY_ACTION_TYPE_UNSPECIFIED = 0,
    /**
     * Indicates that the query results are filtered to only include those
     * that support menu actions. Menu actions have a defined icon and label
     * associated with them.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_INVOKE_QUERY_ACTION_TYPE_MENU        = 1,
    /**
     * Indicates that the query results include all viable targets regardless of
     * their action type(s).
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_INVOKE_QUERY_ACTION_TYPE_ALL         = 2
} navigator_invoke_query_action_type_t;

/**
 * The possible application perimeter type values
 *
 * This enumeration defines the possible types of perimeters in which a targeted
 * or queried application can reside. This is used to determine where a target
 * application should invoke, primarily in cases where the application is a
 * "hybrid" that can run in both enterprise and personal perimeters.
 *
 * Your app should not explicitly set the perimeter, as the Invocation Framework
 * will automatically take care of this across all device configurations (e.g.
 * Personal-only, Balance, Corporate Liable, etc.). If your app sets the
 * perimeter, it may not be able to invoke applications in particular device
 * configurations.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * Indicates that the perimeter type is unspecified.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_INVOKE_PERIMETER_TYPE_UNSPECIFIED = 0,
    /**
     * Indicates that the application should run in the personal perimeter.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_INVOKE_PERIMETER_TYPE_PERSONAL    = 1,
    /**
     * Indicates that the application should run in the enterprise perimeter.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_INVOKE_PERIMETER_TYPE_ENTERPRISE  = 2
} navigator_invoke_perimeter_type_t;

/**
 * @brief The possible transfer modes for files specified in invocation requests
 *
 * This enumeration defines the supported modes for handling file transfer when
 * a file URI is provided that does not point to a file in the shared area.
 * Unless @c NAVIGATOR_INVOKE_FILE_TRANSFER_MODE_LINK is specified, file
 * transfer handling will transfer the file via the target's private inbox.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * Indicates that the file transfer mode has not been specified and the
     * default logic should apply
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_INVOKE_FILE_TRANSFER_MODE_UNSPECIFIED = 0,
    /**
     * Indicates that the file transfer handling should be skipped and the
     * specified file URI should be passed to the target as-is
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_INVOKE_FILE_TRANSFER_MODE_PRESERVE    = 1,
    /**
     * Indicates that the file should be transfered as a read only copy of the
     * file specified in the URI attribute
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_INVOKE_FILE_TRANSFER_MODE_COPY_RO     = 2,
    /**
     * Indicates that the file should be transfered as a read/write copy of the
     * file specified in the URI attribute.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_INVOKE_FILE_TRANSFER_MODE_COPY_RW     = 3,
    /**
     * Indicates that the file should be transfered as a link to the file
     * specified in the URI attribute. Note that link mode requires that the
     * original file support o+r. In addition, if the file has o+w then the
     * sender must be the owner of the file.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_INVOKE_FILE_TRANSFER_MODE_LINK        = 4
} navigator_invoke_file_transfer_mode_t;

/**
 * The possible directions of movement for an invoke list cursor
 *
 * This enumeration defines the possible directions in which an invoke
 * list cursor may move relative to the current selection.
 *
 * @since BlackBerry 10.2.0
 */
typedef enum {
    /**
     * Indicates that the cursor's direction is determined by the application.
     *
     * @since BlackBerry 10.2.0
     */
    NAVIGATOR_INVOKE_LIST_CURSOR_UNSPECIFIED    = 0,

    /**
     * Indicates that the cursor's direction is towards the next list item.
     *
     * @since BlackBerry 10.2.0
     */
    NAVIGATOR_INVOKE_LIST_CURSOR_NEXT           = 1,
    /**
     * Indicates that the cursor's direction is towards the previous list item.
     *
     * @since BlackBerry 10.2.0
     */
    NAVIGATOR_INVOKE_LIST_CURSOR_PREVIOUS       = 2
} navigator_invoke_list_cursor_direction_t;

/**
 * @brief Enumeration values for timer trigger control
 *
 * Used along with @c #navigator_invoke_timer_registration_t structure to request
 * updates to timer trigger.
 *
 * @since BlackBerry 10.3.0
 */
typedef enum {
    /**
     * Indicates that timer registration action was not set
     *
     * @since BlackBerry 10.3.0
     */
    NAVIGATOR_INVOKE_TIMER_ACTION_NOT_SET       = 0,
    /**
     * Action to install a new timer trigger or update an existing trigger
     *
     * @since BlackBerry 10.3.0
     */
    NAVIGATOR_INVOKE_TIMER_ACTION_REGISTER      = 1,
    /**
     * Action to deregister an existing timer trigger
     *
     * @since BlackBerry 10.3.0
     */
    NAVIGATOR_INVOKE_TIMER_ACTION_UNREGISTER    = 2
} navigator_invoke_timer_registration_action_t;

/**
 * @brief Enumeration values for the Timer trigger types
 *
 * These types are used with a @c #navigator_invoke_timer_registration_t
 * structure to specify the timer trigger type.
 *
 * @since BlackBerry 10.3.0
 */
typedef enum {
    /**
     * The timer trigger is an unknown type of trigger.
     *
     * @since BlackBerry 10.3.0
     */
    NAVIGATOR_INVOKE_TIMER_TRIGGER_UNKNOWN_TYPE       = 0,
    /**
     * The timer trigger is recurrent.
     *
     * @since BlackBerry 10.3.0
     */
    NAVIGATOR_INVOKE_TIMER_TRIGGER_RECURRENT          = 1,
    /**
     * The timer trigger is for a specific local time.
     *
     * @since BlackBerry 10.3.0
     */
    NAVIGATOR_INVOKE_TIMER_TRIGGER_SPECIFIC_LOCAL     = 2,
    /**
     * The timer trigger is for a specific global time.
     *
     * @since BlackBerry 10.3.0
     */
    NAVIGATOR_INVOKE_TIMER_TRIGGER_SPECIFIC_GLOBAL    = 3
} navigator_invoke_timer_trigger_type_t;

/**
 * @brief Enumeration values for the recurrence rule frequencies
 *
 * These values specify the frequency in a
 * @c #navigator_invoke_recurrence_rule_t structure.
 * The frequency used to define a recurrence rules may generate recurrence
 * instances with an invalid date (e.g., February 30) or nonexistent local time
 * (e.g., 1:30 AM on a day where the local time is moved forward by an hour at
 * 1:00 AM). These invalid recurrence instances will be skipped.
 *
 * @since BlackBerry 10.3.0
 */
typedef enum {
    /**
     * Yearly.
     * The yearly frequency corresponds to a calendar year.
     * eg. A rule with a yearly frequency starting on January 1, 2014 will have
     * its first recurrence on January 1, 2015.
     *
     * @since BlackBerry 10.3.0
     */
    NAVIGATOR_INVOKE_RECURRENCE_RULE_FREQUENCY_YEARLY       = 1,
    /**
     * Monthly.
     * The monthly frequency corresponds to a calendar month.
     * eg. A rule with a monthly frequency starting on March 20, 2015 will have
     * its first recurrence on April 20, 2015.
     *
     * @since BlackBerry 10.3.0
     */
    NAVIGATOR_INVOKE_RECURRENCE_RULE_FREQUENCY_MONTHLY      = 2,
    /**
     * Weekly.
     * A rule with this frequency will have a weekly recurrence.
     *
     * @since BlackBerry 10.3.0
     */
    NAVIGATOR_INVOKE_RECURRENCE_RULE_FREQUENCY_WEEKLY       = 3,
    /**
     * Daily.
     * A rule with this frequency will have a daily recurrence.
     *
     * @since BlackBerry 10.3.0
     */
    NAVIGATOR_INVOKE_RECURRENCE_RULE_FREQUENCY_DAILY        = 4,
    /**
     * Hourly.
     * A rule with this frequency will have an hourly recurrence.
     *
     * @since BlackBerry 10.3.0
     */
    NAVIGATOR_INVOKE_RECURRENCE_RULE_FREQUENCY_HOURLY       = 5,
    /**
     * Minutely.
     * A rule with this frequency will have a recurrence every minute.
     *
     * @since BlackBerry 10.3.0
     */
    NAVIGATOR_INVOKE_RECURRENCE_RULE_FREQUENCY_MINUTELY     = 6
} navigator_invoke_recurrence_rule_frequency_t;

/**
 * @brief Create an invocation structure and allocate all necessary memory
 *
 * The @c navigator_invoke_invocation_create() function creates an instance of a
 * @c #navigator_invoke_invocation_t structure called @c invocation to be used
 * by the invocation framework. Destroy all invocation instances created through
 * this function once they are no longer needed by using the @c
 * navigator_invoke_invocation_destroy() function to prevent memory leaks.
 *
 * @param invocation The @c #navigator_invoke_invocation_t structure to
 *        populate.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_invocation_create(navigator_invoke_invocation_t **invocation);

/**
 * @brief Deallocate the memory used by an invocation structure
 *
 * The @c navigator_invoke_invocation_destroy() function deallocates any memory
 * set to a given @c invocation. Use this function to deallocate memory used by
 * a @c #navigator_invoke_invocation_t structure (created by the @c
 * navigator_invoke_invocation_create() function) that's no longer in use.
 * Failing to do so will result in a memory leak.
 *
 * @param invocation The @c #navigator_invoke_invocation_t structure to
 *                   deallocate.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_invocation_destroy(
        navigator_invoke_invocation_t *invocation);

/**
 * @brief Set the ID of an @c invocation
 *
 * The @c navigator_invoke_invocation_set_id() function sets the invocation ID
 * of a given @c #navigator_invoke_invocation_t structure. Assign an @c id
 * member to any invocation for which you would like to receive a delivery
 * receipt response. The @c id member you assign through a sender appears in its
 * corresponding delivery receipt. The receipt is returned once the invocation
 * is dispatched to a target, but does not imply that the target has processed
 * the invocation. If the sender terminates before receiving a receipt response
 * then it is forfeit.
 *
 * Assigning an @c id member to an invocation is not mandatory, but if you do
 * not assign one there is no way to determine the result of the invocation
 * request. Don't assign an invocation ID if you don't want to receive a
 * delivery receipt response.
 *
 * @param invocation A pointer to the @c #navigator_invoke_invocation_t
 *                   structure whose @c id you want to set.
 *
 * @param id The invocation ID you want to display on the delivery receipt
 *           response. This value must be in numerical format. For example, a
 *           valid @c id would be "42".
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_invocation_set_id(
        navigator_invoke_invocation_t *invocation, const char* id);

/**
 * @brief Set the target of an @c invocation
 *
 * The @c navigator_invoke_invocation_set_target() function sets the target of a
 * given @c #navigator_invoke_invocation_t structure. The @c target member is an
 * identifier to the target (as stated in its BAR manifest) handler to which the
 * invocation is sent.
 *
 * If you assign a @c target member to an invocation then brokering is bypassed
 * and an attempt is made to invoke the specified target. If you don't call this
 * function, the invocation framework uses brokering along with the @c action
 * and/or @c type member (assigned with the @c
 * navigator_invoke_invocation_set_action() and @c
 * navigator_invoke_invocation_set_type() functions respectively) to find the
 * corresponding handler(s).
 *
 * The format of a @c target member must conform to the following guidelines:
 *      - Maximum 50 characters
 *      - Target: [Domain][Sub-domain]
 *      - Sub-domain:  NUL | .[Domain][Sub-domain]
 *      - Domain: [a-zA-Z]([a-zA-Z0-9_])*
 *
 * Example: "com.example.invoke.target"
 *
 * @param invocation A pointer to the @c #navigator_invoke_invocation_t
 *                   structure whose @c target you want to set.
 *
 * @param target The target you want the invocation to be sent to. The value
 *               must conform to the "[Domain][Sub-domain]" format (see
 *               description for further information).
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_invocation_set_target(
        navigator_invoke_invocation_t *invocation, const char* target);

/**
 * @brief Set the source of an @c invocation
 *
 * The @c navigator_invoke_invocation_set_source() function sets the source of a
 * given @c #navigator_invoke_invocation_t structure. The @c source member is an
 * identifier to a target (as stated in its BAR manifest) to which the results
 * of an invocation are sent. If you assign a @c source member to an invocation
 * then the receiving target may send a response with the corresponding results.
 *
 * Assigning a @c source member to an invocation is not mandatory, but if you do
 * not assign one then the invoked target won't be able to communicate with
 * the caller. Don't assign an invocation source if the sender doesn't support
 * results.
 *
 * The format of a @c target member must conform to the following guidelines:
 *      - Maximum 50 characters
 *      - Source: [Domain][Sub-domain]
 *      - Sub-domain:  NUL | .[Domain][Sub-domain]
 *      - Domain: [a-zA-Z]([a-zA-Z0-9_])*
 *
 * Example: "com.example.result.target"
 *
 * @param invocation A pointer to the @c #navigator_invoke_invocation_t
 *                   structure whose @c source you want to set.
 *
 * @param source The target you want the invocation target to be send results
 *               to. The value must conform to the "[Domain][Sub-domain]" format
 *               (see description for further information).
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_invocation_set_source(
        navigator_invoke_invocation_t *invocation, const char* source);

/**
 * @brief Set the action of an @c invocation
 *
 * The @c navigator_invoke_invocation_set_action() function sets the action of a
 * given @c #navigator_invoke_invocation_t structure. The @c action member
 * identifies the action to be performed by the invocation target.
 *
 * If you assign an @c action member to an invocation but don't assign a @c
 * target (using the @c navigator_invoke_invocation_set_target() function), the
 * brokering system uses the @c action value to filter for target handlers that
 * support that action. If a @c type member is also assigned (using the @c
 * navigator_invoke_invocation_set_type() function), the brokering system uses
 * that information to filter for handler(s) that support both the given
 * action and type. If only a @c type member is assigned, the brokering system
 * doesn't filter for any specific action.
 *
 * The format of an @c action member must conform to the following guidelines:
 *      - Maximum 50 characters
 *      - Action: [Domain][Sub-domain]
 *      - Sub-domain:  NUL | .[Domain][Sub-domain]
 *      - Domain: [a-zA-Z]([a-zA-Z0-9_])*
 *
 * Example: "bb.action.SHARE"
 *
 * @param invocation A pointer to the @c #navigator_invoke_invocation_t
 *                   structure whose @c action member you want to set.
 *
 * @param action The action you want the invocation target to perform. The value
 *               must conform to the "[Domain][Sub-domain]" format (see
 *               description for further information).
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_invocation_set_action(
        navigator_invoke_invocation_t *invocation, const char* action);

/**
 * @brief Set the type of an @c invocation
 *
 * The @c navigator_invoke_invocation_set_type() function sets the @c type
 * member of a given @c #navigator_invoke_invocation_t structure. The @c type
 * member identifies the MIME type of the data the invoked handler is to perform
 * an action on.
 *
 * If you assign a @c type member to an invocation but don't assign a @c target
 * (using the @c navigator_invoke_invocation_set_target() function), the
 * brokering system uses the @c type value to filter for target handlers that
 * support that MIME type. If an @c action member is also assigned (using the @c
 * navigator_invoke_invocation_set_action() function), the brokering system uses
 * that information to filter for handler(s) that support both the given type
 * and action. If only an @c action member is assigned, the brokering system
 * doesn't filter for any specific MIME type.
 *
 * The format of a @c type member must conform to the following guidelines:
 *      - MIME type: Type Subtype
 *      - Type: [a-zA-Z0-9-_\.]+
 *      - Subtype: NUL | / Type Subtype
 *
 * Example: "image/png"
 *
 * @param invocation A pointer to the @c #navigator_invoke_invocation_t
 *                   structure whose @c type member you want to set.
 *
 * @param type The MIME type of the data being sent to the invocation handler.
 *               The value must conform to the "Type Subtype" format (see
 *               description for further information).
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_invocation_set_type(
        navigator_invoke_invocation_t *invocation, const char* type);

/**
 * @brief Set the URI of an @c invocation
 *
 * The @c navigator_invoke_invocation_set_uri() function sets the URI pointing
 * to the data of a given @c #navigator_invoke_invocation_t structure. The @c
 * uri member identifies the location of the data the invoked handler is to
 * perform an action on.
 *
 * If you don't call this function, the URI is assumed to be "data://local",
 * indicating that the invocation data is provided through the @c data member
 * (using the @c navigator_invoke_invocation_set_data() function).
 *
 * @param invocation A pointer to the @c #navigator_invoke_invocation_t
 *                   structure whose @c uri member you want to set.
 *
 * @param uri The URI to the data being sent to the invocation handler. The
 *            value of this member should be a percent-encoded URI. For example,
 *            file:///accounts/1000/appdata/com.example.application.123456789123456789123456789/data/image%201.jpg
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_invocation_set_uri(
        navigator_invoke_invocation_t *invocation, const char* uri);

/**
 * @brief Set the file transfer mode of an @c invocation
 *
 * The @c navigator_invoke_invocation_set_file_transfer_mode() function sets the
 * file transfer mode.
 *
 * The transfer_mode identifies how the file transfer should be handled. By
 * default, private file transfer will be applied if the URI is a file URI that
 * points to a file that is not in the shared area. The file will be transfered
 * by creating a read-only copy in the target's private inbox.
 *
 * Setting the @c transfer_mode allows the sender to control the transfer by
 * specifying that no handling should be applied, or that the file should be
 * copied read/write, or should be hard-linked.
 *
 * If @c NAVIGATOR_INVOKE_FILE_TRANSFER_MODE_LINK is specified the file must
 * have o+r permissions. In addition, if the file is o+w then the sender must be
 * the owner of the file.
 *
 * @param invoke A pointer to the @c #navigator_invoke_invocation_t structure
 *                   whose @c transfer_mode member you want to set.
 *
 * @param transfer_mode The mode that should control the transfer of the data if
 *            the URI is a file URI that does not refer to a file in the shared
 *            area.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_invocation_set_file_transfer_mode(
        navigator_invoke_invocation_t *invoke,
        navigator_invoke_file_transfer_mode_t transfer_mode);

/**
 * @brief Set the arbitrary data of an @c invocation
 *
 * The @c navigator_invoke_invocation_set_data() function sets the @c data and
 * @c data_length of a given @c #navigator_invoke_invocation_t structure. The @c
 * data member is the data the invoked handler is to perform an action on. Upon
 * sending the invocation, the data is delivered to the target in its unchanged
 * form.
 *
 * If you don't call this function, the action and/or type information (which
 * can be set using the @c navigator_invoke_invocation_set_action() and @c
 * navigator_invoke_invocation_set_type() functions respectively) must be
 * sufficient to carry out the invocation.
 *
 * @param invocation A pointer to the @c #navigator_invoke_invocation_t
 *                   structure whose @c data you want to set.
 *
 * @param data The arbitrary data being sent to the invocation handler. The
 *            value of this member can take the form of any binary data.
 *
 * @param data_length The size of the @c data member in bytes.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_invocation_set_data(
        navigator_invoke_invocation_t *invocation, const void* data,
        int data_length);

/**
 * @cond internal
 */

/**
 * @brief Set the perimeter of an @c invocation
 *
 * This function should not be used by third-party developers. The Invocation
 * Framework will automatically take care of setting the perimeter across all
 * device configurations (e.g. Personal-only, Balance, Corporate Liable, etc.).
 * If you use this function to set the perimeter, your app may not be able to
 * invoke applications in particular device configurations.
 *
 * The @c navigator_invoke_invocation_set_perimeter() function sets the @c
 * perimeter member of a given @c #navigator_invoke_invocation_t structure. The
 * @c perimeter member identifies the perimeter (either personal or enterprise)
 * in which the application should be invoked. Use this function in instances
 * where the target application is a "hybrid" that can run in both enterprise
 * and personal perimeters. In all cases, the perimeter is mandated to be the
 * same as the sender.
 *
 * If you don't call this function for a hybrid application, then the invocation
 * will be rejected and an error will be returned.
 *
 * The possible values that you can set to this member are:
 *     - @c NAVIGATOR_INVOKE_PERIMETER_TYPE_PERSONAL
 *     - @c NAVIGATOR_INVOKE_PERIMETER_TYPE_ENTERPRISE
 *
 * See the @c #navigator_invoke_perimeter_type_t enumeration for details.
 *
 * @param invocation A pointer to the @c #navigator_invoke_invocation_t
 *                   structure whose @c perimeter member you want to set.
 *
 * @param perimeter The perimeter in which you want the application to be
 *                  invoked. This value must correspond to an entry in the @c
 *                  #navigator_invoke_perimeter_type_t enumeration.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_invocation_set_perimeter(
        navigator_invoke_invocation_t *invocation,
        navigator_invoke_perimeter_type_t perimeter);

/**
 * @endcond
 */

/**
 * @brief Set the metadata with which the application should be invoked
 *
 * The @c navigator_invoke_invocation_set_metadata() function sets the
 * metadata with which the application should be invoked.
 *
 * @param invocation The invocation to update.
 * @param metadata The JSON string carrying optional metadata.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_invocation_set_metadata(
        navigator_invoke_invocation_t *invocation, const char* metadata);

/**
 * @brief Set the target type mask of an invocation
 *
 * The @c navigator_invoke_invocation_set_target_type_mask() function sets the
 * target type mask of a given @c #navigator_invoke_invocation_t structure.
 * The @c target_type_mask member is a bitwise-OR value that indicates which
 * targets the invocation selection should include: applications, cards
 * and/or services.
 *
 * The invoke target type values you can use to set this member are:
 *     - @c NAVIGATOR_INVOKE_TARGET_TYPE_APPLICATION
 *     - @c NAVIGATOR_INVOKE_TARGET_TYPE_CARD
 *     - @c NAVIGATOR_INVOKE_TARGET_TYPE_SERVICE
 *     - @c NAVIGATOR_INVOKE_TARGET_TYPE_HEADLESS
 *     - a bitwise @c OR of any combination of the above values.
 *
 * See the @c #navigator_invoke_target_type_t enumeration for details.
 *
 * If you don't assign a @c target_type_mask member, or you assign
 * @c NAVIGATOR_INVOKE_TARGET_TYPE_UNSPECIFIED to an @c invocation, then all of
 * the target types will be considered in the brokering system.
 *
 * @param invoke A pointer to the @c #navigator_invoke_invocation_t structure
 *               whose @c target_type_mask member you want to set.
 *
 * @param target_type_mask  A target type corresponding to an entry in the @c
 *                          #navigator_invoke_target_type_t enumeration.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_invocation_set_target_type_mask(
        navigator_invoke_invocation_t *invoke,
        int target_type_mask);

/**
 * @brief Set the list id to associate with the invocation
 *
 * The @c navigator_invoke_invocation_set_list_id() function sets the
 * list id of the list that @c invoke should be associated with.
 * If @c list_id is 0, @c invoke is disassociated from any lists.
 *
 * @param invoke  The invocation to update.
 * @param list_id The id of the list to associate the invocation with.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int navigator_invoke_invocation_set_list_id(
        navigator_invoke_invocation_t *invoke,
        int list_id);

/**
 * @brief Get the ID from an @c invocation
 *
 * The @c navigator_invoke_invocation_get_id() function extracts the invocation
 * ID of a given @c #navigator_invoke_invocation_t structure. The @c id member
 * is used by the invocation handler to create delivery receipt responses to be
 * returned when an invocation is sent (see the @c
 * navigator_invoke_invocation_set_id() function for further details). This
 * function doesn't copy members and the returned values are released once the
 * @c #navigator_invoke_invocation_t structure is destroyed with the @c
 * navigator_invoke_invocation_destroy() function.
 *
 * @param invocation A pointer to the @c #navigator_invoke_invocation_t
 *                   structure whose @c id member you want to retrieve.
 *
 * @return The invocation ID if one was provided by the sender, @c NULL
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_invocation_get_id(
        const navigator_invoke_invocation_t *invocation);

/**
 * @brief Get the target from an @c invocation
 *
 * The @c navigator_invoke_invocation_get_target() function extracts the target
 * of a given @c #navigator_invoke_invocation_t structure. The @c target member
 * is used by the invocation framework to identify the target application or
 * card meant to perform an action based on the invocation (see the @c
 * navigator_invoke_invocation_set_target() function for further details). This
 * function doesn't copy members and the returned values are released once the
 * @c #navigator_invoke_invocation_t structure is destroyed with the @c
 * navigator_invoke_invocation_destroy() function.
 *
 * @param invocation A pointer to the @c #navigator_invoke_invocation_t
 *                   structure whose @c target member you want to retrieve.
 *
 * @return The invocation target if one was provided by the sender, @c NULL
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_invocation_get_target(
        const navigator_invoke_invocation_t *invocation);

/**
 * @brief Get the source from an @c invocation
 *
 * The @c navigator_invoke_invocation_get_source() function extracts the source
 * of a given @c #navigator_invoke_invocation_t structure. The @c source member
 * is used by the invoked handler to direct resopnse messages to the invocator
 * (see the @c navigator_invoke_invocation_set_source() function for further
 * details). This function doesn't copy members and the returned values are
 * released once the @c #navigator_invoke_invocation_t structure is destroyed
 * with the @c navigator_invoke_invocation_destroy() function.
 *
 * @param invocation A pointer to the @c #navigator_invoke_invocation_t
 *                   structure whose @c source member you want to retrieve.
 *
 * @return The invocation source if one was provided by the sender, @c NULL
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_invocation_get_source(
        const navigator_invoke_invocation_t *invocation);

/**
 * @brief Get the action from an @c invocation
 *
 * The @c navigator_invoke_invocation_get_action() function extracts the @c
 * action member of a given @c #navigator_invoke_invocation_t structure. The @c
 * action member is used by the brokering system and invocation framework to
 * identify what action an invoked handler is meant to perform (see the @c
 * navigator_invoke_invocation_set_action() function for further details). This
 * function doesn't copy members and the returned values are released once the
 * @c #navigator_invoke_invocation_t structure is destroyed with the @c
 * navigator_invoke_invocation_destroy() function.
 *
 * @param invocation A pointer to the @c #navigator_invoke_invocation_t
 *                   structure whose @c action member you want to retrieve.
 *
 * @return The invocation action if one was provided by the sender, @c NULL
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_invocation_get_action(
        const navigator_invoke_invocation_t *invocation);

/**
 * @brief Get the type from an @c invocation
 *
 * The @c navigator_invoke_invocation_get_type() function extracts the MIME type
 * of a given @c #navigator_invoke_invocation_t structure. The @c type member is
 * used by the brokering system and invocation framework to identify the MIME
 * type of the data an invoked handler is meant to perform an action on (see the
 * @c navigator_invoke_invocation_set_type() function for further details). This
 * function doesn't copy members and the returned values are released once the
 * @c #navigator_invoke_invocation_t structure is destroyed with the @c
 * navigator_invoke_invocation_destroy() function.
 *
 * @param invocation A pointer to the @c #navigator_invoke_invocation_t
 *                   structure whose @c type member you want to retrieve.
 *
 * @return The invocation type if one was provided by the sender, @c NULL
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_invocation_get_type(
        const navigator_invoke_invocation_t *invocation);

/**
 * @brief Get the URI from an @c invocation
 *
 * The @c navigator_invoke_invocation_get_uri() function extracts the URI
 * pointing the data of a given @c #navigator_invoke_invocation_t structure. The
 * @c uri member is used by the invocation handler to identify the location of
 * the data the invoked handler is to perform an action on (see the @c
 * navigator_invoke_invocation_set_uri() function for further details). This
 * function doesn't copy members and the returned values are released once the
 * @c #navigator_invoke_invocation_t structure is destroyed with the @c
 * navigator_invoke_invocation_destroy() function.
 *
 * @param invocation A pointer to the @c #navigator_invoke_invocation_t
 *                   structure whose @c uri member you want to retrieve.
 *
 * @return The URI pointing to invocation data if one was provided by the
 *         sender, @c NULL otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_invocation_get_uri(
        const navigator_invoke_invocation_t *invocation);

/**
 * @brief Get the file transfer mode of an @c invocation
 *
 * The @c navigator_invoke_invocation_get_file_transfer_mode() function extracts
 * the @c #navigator_invoke_file_transfer_mode_t file transfer mode of a given
 * @c #navigator_invoke_invocation_t structure.
 *
 * The @c transfer mode member is used to control how files are passed between
 * sender and target (see the @c
 * navigator_invoke_invocation_set_file_transfer_mode() function for further
 * details).
 *
 * @param invoke A pointer to the @c #navigator_invoke_invocation_t structure
 *                   whose transfer mode member you want to retrieve.
 *
 * @return The file transfer mode that describes how the file will be transfered
 *         in the case that it points to a file URI that is not in the shared
 *         area, or @c BPS_FAILURE with @c errno set if an error occurs.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_invocation_get_file_transfer_mode(
        const navigator_invoke_invocation_t * invoke);

/**
 * @brief Get the data length from an @c invocation
 *
 * The @c navigator_invoke_invocation_get_data_length() function extracts the
 * length in bytes of the data of a given @c #navigator_invoke_invocation_t
 * structure. The @c data_length member is used by the invocation handler to
 * identify the size of the data the invoked handler is to perform an action on
 * (see the @c navigator_invoke_invocation_set_data() function for further
 * details). This function doesn't copy members and the returned values are
 * released once the @c #navigator_invoke_invocation_t structure is destroyed
 * with the @c navigator_invoke_invocation_destroy() function.
 *
 * @param invocation A pointer to the @c #navigator_invoke_invocation_t
 *                   structure whose @c data_length member you want to retrieve.
 *
 * @return The size in bytes of the invocation data if one was provided by the
 *         sender, -1 otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_invocation_get_data_length(
        const navigator_invoke_invocation_t *invocation);

/**
 * @brief Get the data from an @c invocation
 *
 * The @c navigator_invoke_invocation_get_data() function extracts the binary
 * data of a given @c #navigator_invoke_invocation_t structure. The @c data
 * member is used by the invocation handler to perform an action (see the @c
 * navigator_invoke_invocation_set_data() function for further details). This
 * function doesn't copy members and the returned values are released once the
 * @c #navigator_invoke_invocation_t structure is destroyed with the @c
 * navigator_invoke_invocation_destroy() function.
 *
 * @param invocation A pointer to the @c #navigator_invoke_invocation_t
 *                   structure whose @c data member you want to retrieve.
 *
 * @return The invocation data if one was provided by the sender, @c NULL
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const void* navigator_invoke_invocation_get_data(
        const navigator_invoke_invocation_t *invocation);

/**
 * @brief Get the perimeter from an @c invocation
 *
 * The @c navigator_invoke_invocation_get_perimeter() function extracts the @c
 * perimeter member of a given @c #navigator_invoke_invocation_t structure. The
 * @c perimeter member is used by the invocation framework to identify what
 * perimeter the target application is to be invoked (see the @c
 * navigator_invoke_invocation_set_perimeter() function for further details).
 *
 * @param invocation A pointer to the @c #navigator_invoke_invocation_t
 *                   structure whose @c perimeter member you want to retrieve.
 *
 * @return The invocation perimeter if one was provided by the sender.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API navigator_invoke_perimeter_type_t navigator_invoke_invocation_get_perimeter(
        const navigator_invoke_invocation_t *invocation);

/**
 * @brief Get the metadata with which the application should be invoked
 *
 * The @c navigator_invoke_invocation_get_metadata() function gets the
 * metadata with which the application should be invoked.
 *
 * @param invocation A pointer to the @c #navigator_invoke_invocation_t
 *                   structure whose @c metadata member you want to retrieve.
 *
 * @return The metadata if it was provided by sender.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_invocation_get_metadata(
        const navigator_invoke_invocation_t *invocation);

/**
 * @brief Get the list ID with which the invocation should be associated with
 *
 * The @c navigator_invoke_invocation_get_list_id() function gets the
 * list ID with which @c invoke is associated.
 *
 * @param invocation A pointer to the @c #navigator_invoke_invocation_t
 *                   structure whose list ID you want to retrieve.
 *
 * @return The id of the list this invocation should be associated with,
 *         or 0 if no such association exists.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int navigator_invoke_invocation_get_list_id(
        const navigator_invoke_invocation_t *invocation);


/**
 * @brief Get the target type mask from an @c invocation
 *
 * The @c navigator_invoke_invocation_get_target_type_mask() function extracts
 * the target type mask of a given @c #navigator_invoke_invocation_t structure.
 * The @c target_type_mask member indicates which target types should be
 * included by the invocation selection (see
 * @c navigator_invoke_invocation_set_target_type_mask() and
 * @c #navigator_invoke_target_type_t for further details).
 *
 * @param invocation A pointer to the @c #navigator_invoke_invocation_t
 *                   structure whose @c target_type_mask member you want to
 *                   retrieve.
 *
 * @return The invocation target type mask.
 *         @c NAVIGATOR_INVOKE_TARGET_TYPE_UNSPECIFIED is returned when the
 *         @c target_type_mask is not specified, which implies
 *         that all the target types are considered by the brokering system.
 *         @c NAVIGATOR_INVOKE_TARGET_TYPE_UNSPECIFIED is returned with @c errno
 *         set upon error.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_invocation_get_target_type_mask(
        const navigator_invoke_invocation_t *invocation);

/**
 * @brief Retrieve the invocation structure pointer from the BPS event
 *
 * The @c navigator_invoke_event_get_invocation() function extracts the
 * invocation properties from a @c #navigator_invoke_invocation_t structure sent
 * with the @c navigator_invoke_invocation_send() function. You should call this
 * function upon receiving the @c NAVIGATOR_INVOKE_TARGET event from the event
 * handler to perform the task defined by the invocation.
 *
 * We recommend that you use the @c navigator_event_get_err() function after
 * calling this function in case of an error in processing. The possible errors
 * for an invocation are:
 *      - @c INVOKE_NO_TARGET_ERROR: There is no target identified by the
 *                                   invocation.
 *      - @c INVOKE_BAD_REQUEST_ERROR: The invocation request specifications do
 *                                     not conform to the permitted parameters
 *                                     of the handler. For example, an image
 *                                     sharing invocation being sent to a
 *                                     target application that cannot share
 *                                     images would result in this error.
 *      - @c INVOKE_INTERNAL_ERROR: A generic error occured in the internal
 *                                  framework while attempting to retrieve the
 *                                  @c #navigator_invoke_invocation_t structure.
 *      - @c INVOKE_TARGET_ERROR: A generic error occured with the target
 *                                handler.
 *
 * "Ownership" of an event is not transferred to a handler upon its invocation.
 * A handler must not call the @c navigator_invoke_invocation_destroy() function
 * on invocation pointers that are retrieved using the @c
 * navigator_invoke_event_get_invocation() function.  The pointer to the
 * @c #navigator_invoke_invocation_t structure is valid until the @c
 * bps_get_event() function is called again.
 *
 * @param event The @c NAVIGATOR_INVOKE_TARGET event to extract the invocation
 * from.
 *
 * @return A pointer to the @c #navigator_invoke_invocation_t structure on
 *         success, NULL on failure with @c errno set.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const navigator_invoke_invocation_t* navigator_invoke_event_get_invocation(
        bps_event_t *event);

/**
 * @brief Request an @c invocation to a target
 *
 * The @c navigator_invoke_invocation_send() function invokes a target handler
 * that is specified by the given @c #navigator_invoke_invocation_t structure.
 * The target of an invocation can be determined in the following manners:
 *      - If you specified a @c target member (using the @c
 *        navigator_invoke_invocation_set_target() function, the target is
 *        invoked directly using the given information.
 *      - If you didn't specify a @c target member, the brokering system infers
 *        a target handler using the information from the @c action and/or @c
 *        type members, set with the @c navigator_invoke_invocation_set_action()
 *        and @c navigator_invoke_invocation_set_type() functions respectively.
 *
 * @param invocation The @c #navigator_invoke_invocation_t structure to send.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_invocation_send(
        const navigator_invoke_invocation_t *invocation);

/**
 * @brief Create an invoke query structure and allocate all necessary memory
 *
 * The @c navigator_invoke_query_create() function creates an instance of a @c
 * #navigator_invoke_query_t structure called @c query to be used by the
 * invocation framework. Destroy all invocation query instances created through
 * this function once they are no longer needed by using the @c
 * navigator_invoke_query_destroy() function to prevent memory leaks.
 *
 * @param query The @c #navigator_invoke_query_t structure to populate.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_query_create(navigator_invoke_query_t **query);

/**
 * @brief Deallocate the memory used by an invoke query structure
 *
 * The @c navigator_invoke_invocation_destroy() function deallocates any memory
 * set to a given @c query. Use this function to deallocate memory used by
 * a @c #navigator_invoke_query_t structure (created by the @c
 * navigator_invoke_query_create() function) that's no longer in use.
 * Failing to do so will result in a memory leak.
 *
 * @param query The @c #navigator_invoke_query_t structure to deallocate.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_query_destroy(navigator_invoke_query_t *query);

/**
 * @brief Set the ID of a @c query
 *
 * The @c navigator_invoke_query_set_id() function sets the invocation query ID
 * of a given @c #navigator_invoke_query_t structure. Assign an @c id member to
 * an invocation query to receive a delivery receipt response. The @c id member
 * you assign through a sender appears in its corresponding delivery receipt.
 *
 * Assigning an @c id member to an invocation is mandatory. If you don't assign
 * an @c id, there is no way to determine the result of the invocation query
 * request.
 *
 * @param query A pointer to the @c #navigator_invoke_query_t structure whose @c
 *              id you want to set.
 *
 * @param id The invocation query ID you want to display on the delivery receipt
 *           response. This value must be in numerical format. For example, a
 *           valid @c id would be "42".
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.

 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_query_set_id(navigator_invoke_query_t *query,
        const char* id);

/**
 * @brief Set the action of a @c query
 *
 * The @c navigator_invoke_query_set_action() function sets the @c action member
 * of a given @c #navigator_invoke_query_t structure. The @c action member
 * identifies the action the invocation query results must be able to perform.
 *
 * If you don't assign an @c action member to an invocation query, the
 * brokering system doesn't filter for any specific action.
 *
 * The format of an @c action member must conform to the following guidelines:
 *      - Maximum 50 characters
 *      - Action: [Domain][Sub-domain]
 *      - Sub-domain:  NUL | .[Domain][Sub-domain]
 *      - Domain: [a-zA-Z]([a-zA-Z0-9_])*
 *
 * Example: "bb.action.SHARE"
 *
 * @param query A pointer to the @c #navigator_invoke_query_t structure whose @c
 *              action member you want to set.
 *
 * @param action The action you want to query for. The value must conform to the
 *               "[Domain][Sub-domain]" format (see description for further
 *               information).
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_query_set_action(navigator_invoke_query_t *query,
        const char* action);

/**
 * @brief Set the type of a @c query
 *
 * The @c navigator_invoke_query_set_type() function sets the MIME type of a
 * given @c #navigator_invoke_query_t structure. The @c type member identifies
 * the MIME type the invocation query results must be able to parform an action
 * on.
 *
 * If you don't assign a @c type member to an invocation query, the brokering
 * system doesn't filter for any specific MIME type. You must assign this
 * member if you don't assign the @c file_uri member (using the @c
 * navigator_invoke_query_set_file_uri() function).
 *
 * The format of a @c type member must conform to the following guidelines:
 *      - MIME type: Type Subtype
 *      - Type: [a-zA-Z0-9-_\.]+
 *      - Subtype: NUL | / Type Subtype
 *
 * Example: "image/png"
 *
 * @param query A pointer to the @c #navigator_invoke_query_t structure whose @c
 *              type member you want to set.
 *
 * @param type The MIME type you want to query for. The value must conform to
 *             the "Type Subtype" format (see description for further
 *             information).
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_query_set_type(navigator_invoke_query_t *query,
        const char* type);

/**
 * @brief Set the URI of a @c query
 *
 * The @c navigator_invoke_query_set_file_uri() function sets the URI of a given
 * @c #navigator_invoke_query_t structure. The @c file_uri member identifies the
 * type interface the invocation query results must be able to perform an action
 * on.
 *
 * You must assign this member if the @c type member (assinged wih the @c
 * navigator_invoke_query_set_type() function) is not provided.
 *
 * @param query A pointer to the @c #navigator_invoke_query_t structure whose @c
 *              file_uri member you want to set.
 *
 * @param file_uri The URI to the type interface you want to query for. The
 *            value of this member should be a percent-encoded URI. For example,
 *            file:///accounts/1000/appdata/com.example.application.123456789123456789123456789/data/image%201.jpg
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_query_set_file_uri(navigator_invoke_query_t *query,
        const char* file_uri);

/**
 * @brief Set the target type mask of a @c query
 *
 * The @c navigator_invoke_query_set_target_type_mask() function sets the target
 * type mask of a given @c #navigator_invoke_query_t structure. The
 * @c target_type_mask member is a bitwise @c OR value that determines which
 * targets the invocation query should include in its results.
 *
 * The invoke target type values you can use to set this member are:
 *     - @c NAVIGATOR_INVOKE_TARGET_TYPE_APPLICATION
 *     - @c NAVIGATOR_INVOKE_TARGET_TYPE_CARD
 *     - @c NAVIGATOR_INVOKE_TARGET_TYPE_SERVICE
 *     - @c NAVIGATOR_INVOKE_TARGET_TYPE_HEADLESS
 *     - @c a bitwise @c OR of any combination of the above values.
 *
 * If you don't assign a @c target_type_mask member or assign
 * @c NAVIGATOR_INVOKE_TARGET_TYPE_UNSPECIFIED to a query, then all the target
 * types will be considered in the query.
 *
 * See the @c #navigator_invoke_target_type_t enumeration for details.
 *
 * @param query A pointer to the @c #navigator_invoke_query_t structure whose @c
 *              target_type_mask member you want to set.
 *
 * @param target_type_mask  A target type corresponding to an entry in the @c
 *                          #navigator_invoke_target_type_t enumeration. The @c
 *                          NAVIGATOR_INVOKE_TARGET_TYPE_SERVICE value is
 *                          reserved for future use.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_query_set_target_type_mask(
        navigator_invoke_query_t *query,
        int target_type_mask);

/**
 * @brief Set the action type of a @c query
 *
 * The @c navigator_invoke_query_set_action_type() function sets the action type
 * of a given @c #navigator_invoke_query_t structure. The @c action_type member
 * indicates whether the invocation query returns only menu actions (actions
 * that have an icon and label) or both brokered and menu actions (which may not
 * all have an icon and label).
 *
 * If you don't assign an @c action_type member to an invocation query, the
 * brokering system doesn't filter for any specific action type.
 *
 * The possible values that you can set to this member are:
 *     - @c NAVIGATOR_INVOKE_QUERY_ACTION_TYPE_MENU
 *     - @c NAVIGATOR_INVOKE_QUERY_ACTION_TYPE_ALL
 *
 * See the @c #navigator_invoke_query_action_type_t enumeration for details.
 *
 * @param query A pointer to the @c #navigator_invoke_query_t structure whose @c
 *              action_type member you want to set.
 *
 * @param action_type An action type corresponding to an entry in the @c
 *                    #navigator_invoke_query_action_type_t enumeration.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_query_set_action_type(
        navigator_invoke_query_t *query,
        navigator_invoke_query_action_type_t action_type);

/**
 * @cond internal
 */

/**
 * @brief Set the perimeter of a @c query
 *
 * This function should not be used by third-party developers. The Invocation
 * Framework will automatically take care of setting the perimeter across all
 * device configurations (e.g. Personal-only, Balance, Corporate Liable, etc.).
 * If you use this function to set the perimeter, your app may not be able to
 * invoke applications in particular device configurations.
 *
 * The @c navigator_invoke_query_set_perimeter() function sets the @c perimeter
 * member of a given @c #navigator_invoke_query_t structure. The @c perimeter
 * member indicates in which perimeter the resulting targets should reside. Use
 * this function in instances where the query results include "hybrid"
 * applications that can run in both enterprise and personal perimeters. In all
 * cases, the perimeter is mandated to be the same as the sender.
 *
 * If you don't call this function for a hybrid application, then the query will
 * be rejected and an error will be returned.
 *
 * The possible values that you can set to this member are:
 *     - @c NAVIGATOR_INVOKE_PERIMETER_TYPE_PERSONAL
 *     - @c NAVIGATOR_INVOKE_PERIMETER_TYPE_ENTERPRISE
 *
 * See the @c #navigator_invoke_perimeter_type_t enumeration for details.
 *
 * @param query A pointer to the @c #navigator_invoke_query_t structure whose @c
 *              perimeter member you want to set.
 *
 * @param perimeter The perimeter in which you want the application to be
 *                  invoked. This value must correspond to an entry in the @c
 *                  #navigator_invoke_perimeter_type_t enumeration.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_query_set_perimeter(
        navigator_invoke_query_t *query,
        navigator_invoke_perimeter_type_t perimeter);

/**
 * @endcond
 */

/**
 * @brief Get the ID from a @c query
 *
 * The @c navigator_invoke_query_get_id() function extracts the invocation query
 * ID of a given @c #navigator_invoke_query_t structure. The @c id member is
 * used by the query handler to create delivery receipt responses to be returned
 * when an invocation query is sent (see the @c navigator_invoke_query_set_id()
 * function for further details). This function doesn't copy members and the
 * returned values are released once the @c #navigator_invoke_query_t structure
 * is destroyed with the @c navigator_invoke_query_destroy() function.
 *
 * @param query A pointer to the @c #navigator_invoke_query_t structure whose @c
 *              id member you want to retrieve.
 *
 * @return The invocation query ID if one was provided by the sender, @c NULL
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_query_get_id(
        const navigator_invoke_query_t *query);

/**
 * @brief Get the action from a @c query
 *
 * The @c navigator_invoke_query_get_action() function extracts the @c action
 * member of a given @c #navigator_invoke_query_t structure. The @c action
 * member is used by the brokering system to identify what action the invocation
 * query results must be able to perform (see the @c
 * navigator_invoke_query_set_action() function for further details). This
 * function doesn't copy members and the returned values are released once the
 * @c #navigator_invoke_query_t structure is destroyed with the @c
 * navigator_invoke_query_destroy() function.
 *
 * @param query A pointer to the @c #navigator_invoke_query_t structure whose @c
 *              action member you want to retrieve.
 *
 * @return The action to query for if one was provided by the sender, @c NULL
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_query_get_action(
        const navigator_invoke_query_t *query);

/**
 * @brief Get the type from a @c query
 *
 * The @c navigator_invoke_query_get_type() function extracts the MIME type
 * of a given @c #navigator_invoke_query_t structure. The @c type member is used
 * by the brokering system to identify what MIME type the invocation query
 * results must be able to perform an action on (see the @c
 * navigator_invoke_query_set_type() function for further details). This
 * function doesn't copy members and the returned values are released once the
 * @c #navigator_invoke_query_t structure is destroyed with the @c
 * navigator_invoke_query_destroy() function.
 *
 * @param query A pointer to the @c #navigator_invoke_query_t structure whose @c
 *              type member you want to retrieve.
 *
 * @return The MIME type to query for if one was provided by the sender, @c NULL
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_query_get_type(
        const navigator_invoke_query_t *query);

/**
 * @brief Get the URI from a @c query
 *
 * The @c navigator_invoke_query_get_file_uri() function extracts the URI of a
 * given @c #navigator_invoke_query_t structure. The @c file_uri member is used
 * by the brokering system to identify what type interface the invocation query
 * results must be able to perform an action on (see the @c
 * navigator_invoke_query_set_file_uri() function for further details). This
 * function doesn't copy members and the returned values are released once the
 * @c #navigator_invoke_query_t structure is destroyed with the @c
 * navigator_invoke_query_destroy() function.
 *
 * @param query A pointer to the @c #navigator_invoke_query_t structure whose @c
 *              file_uri member you want to retrieve.
 *
 * @return The URI to the type interface to query for if one was provided by the
 *         sender, @c NULL otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_query_get_file_uri(
        const navigator_invoke_query_t *query);

/**
 * @brief Get the target type mask from a @c query
 *
 * The @c navigator_invoke_query_get_target_type_mask() function extracts the
 * target type of a given @c #navigator_invoke_query_t structure. The
 * @c target_type_mask member is a bitwise @c OR value that determines which
 * targets the invocation query should include in its results.
 * (see @c navigator_invoke_query_set_target_type_mask() and
 * @c #navigator_invoke_target_type_t for further details).
 *
 * @param query A pointer to the @c #navigator_invoke_query_t structure whose @c
 *              target_type_mask member you want to retrieve.
 *
 * @return The invocation query target type mask to query for if one was
 *         provided by the sender.  @c NAVIGATOR_INVOKE_TARGET_TYPE_UNSPECIFIED
 *         is returned when the @c target_type_mask is not specified, which
 *         implies that all possible target types are considered in the query.
 *         @c NAVIGATOR_INVOKE_TARGET_TYPE_UNSPECIFIED is returned with @c errno
 *         set upon error.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_query_get_target_type_mask(
        const navigator_invoke_query_t *query);

/**
 * @brief Get the action type from a @c query
 *
 * The @c navigator_invoke_query_get_action_type() function extracts the action
 * type of a given @c #navigator_invoke_query_t structure. The @c action_type
 * member is used by the brokering system to identify whether the invocation
 * query should return only menu actions or both brokered and menu actions (see
 * the @c navigator_invoke_query_set_action_type() function and the @c
 * #navigator_invoke_query_action_type_t enumeration for further details).
 *
 * @param query A pointer to the @c #navigator_invoke_query_t structure whose @c
 *              action_type member you want to retrieve.
 *
 * @return The invocation query target type to query for if one was provided
 *         by the sender.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API navigator_invoke_query_action_type_t navigator_invoke_query_get_action_type(
        const navigator_invoke_query_t *query);

/**
 * @brief Get the perimeter from a @c query
 *
 * The @c navigator_invoke_query_get_perimeter() function extracts the @c
 * perimeter member of a given @c #navigator_invoke_query_t structure. The @c
 * perimeter member is used by the invocation framework to identify in which
 * perimeter the resulting targets should reside (see the @c
 * #navigator_invoke_perimeter_type_t enumeration for further details).
 *
 * @param query A pointer to the @c #navigator_invoke_query_t structure whose @c
 *              perimeter member you want to retrieve.
 *
 * @return The perimeter in which the query target should be invoked if one was
 *         provided by the sender, @c NULL otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API navigator_invoke_perimeter_type_t navigator_invoke_query_get_perimeter(
        const navigator_invoke_query_t *query);

/**
 * @brief Send a @c query request to the invocation framework
 *
 * The @c navigator_invoke_query_send() function deploys an invocation query
 * that is specified by the given @c #navigator_invoke_query_t structure. Viable
 * candidates conforming to the specifications set through the various members
 * of the @c #navigator_invoke_query_t structure (using the @c
 * navigator_invoke_query_set_*() functions) are returned as results of the
 * query.
 *
 * @param query The @c #navigator_invoke_query_t structure to send.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_query_send(const navigator_invoke_query_t *query);

/**
 * @brief Get the number of @c action values in an invocation query result
 *
 * The @c navigator_invoke_event_get_query_result_action_count() function
 * extracts the number of @c #navigator_invoke_query_result_action_t structure
 * results that are returned from an invocation query. The @c
 * #navigator_invoke_query_result_action_t action structures returned are
 * considered viable actions based on the information supplied through the @c
 * #navigator_invoke_query_t structure that invoked the query. Call this
 * function from an event handler upon receiving the @c
 * NAVIGATOR_INVOKE_QUERY_RESULT event to determine how many viable actions were
 * returned. You can use this value to create a loop of the returned values.
 *
 * If you encounter an error in processing the query, we recommend that you call
 * the @c navigator_event_get_err() function to determine the nature of the
 * error. The possible errors are:
 *     - @c invalid_argument
 *     - @c response_too_large
 *     - @c server_error
 *
 * @param event The @c NAVIGATOR_INVOKE_QUERY_RESULT event targeted by the query
 *              result.
 *
 * @return The number of actions inside the invocation query result, -1
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_event_get_query_result_action_count(
        bps_event_t *event);

/**
 * @brief Get an @c action from an invocation query result
 *
 * The @c navigator_invoke_event_get_query_result_action() function extracts one
 * of the @c #navigator_invoke_query_result_action_t structure results returned
 * from an invocation query, identified by a given @c index value. The @c
 * #navigator_invoke_query_result_action_t action structures returned are
 * considered viable actions based on the information supplied through the @c
 * #navigator_invoke_query_t structure that invoked the query. This function
 * doesn't copy members and the returned values are released once the @c
 * bps_get_event() function is called again.
 *
 * Note that "ownership" of the event is not passed to the handler. For this
 * reason, don't call the free function on invocation query result action
 * pointers that are retrieved using this function.
 *
 * @param event The @c NAVIGATOR_INVOKE_QUERY_RESULT event targeted by the query
 *              result.
 *
 * @param index The numerical index value of the @c
 *              #navigator_invoke_query_result_action_t structure inside the
 *              invocation query result.
 *
 * @return The pointer to the returned action, @c NULL if the query result is
 *         @c NULL or the @c index is out of bounds.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const navigator_invoke_query_result_action_t* navigator_invoke_event_get_query_result_action(
        bps_event_t *event, int index);

/**
 * @brief Get the name of an @c action from an invocation query result
 *
 * The @c navigator_invoke_query_result_action_get_name() function extracts the
 * action name of a given @c #navigator_invoke_query_result_action_t structure.
 * The @c name member is used by the query result handler to identify a given @c
 * action that is supported for the specified query. This function doesn't copy
 * members and the returned values are released once the @c bps_get_event()
 * function is called again. You must call this function to display the returned
 * @c action value(s).
 *
 * Each @c action @c name conforms to the following guidelines:
 *      - Maximum 50 characters
 *      - Action: [Domain][Sub-domain]
 *      - Sub-domain:  NUL | .[Domain][Sub-domain]
 *      - Domain: [a-zA-Z]([a-zA-Z0-9_])*
 *
 * Example: "bb.action.SHARE"
 *
 * @param action The @c #navigator_invoke_query_result_action_t structure whose
 *               @c name member you want to retrieve.
 *
 * @return The name of the given action, in the "[Domain][Sub-domain]" format
 *         (see description for further information), @c NULL otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_query_result_action_get_name(
        const navigator_invoke_query_result_action_t *action);

/**
 * @brief Get the icon of an @c action from an invocation query result
 *
 * The @c navigator_invoke_query_result_action_get_icon() function extracts the
 * URI to an icon of a given @c #navigator_invoke_query_result_action_t
 * structure. The @c icon member is a path to an icon to be identified with the
 * corresponding action. This function doesn't copy members and the returned
 * values are released once the @c bps_get_event() function is called again.
 *
 * @param action The @c #navigator_invoke_query_result_action_t structure whose
 *               @c icon member you want to retrieve.
 *
 * @return The icon URI of the given @c action, @c NULL otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_query_result_action_get_icon(
        const navigator_invoke_query_result_action_t *action);

/**
 * @brief Get the label of an @c action from an invocation query result
 *
 * The @c navigator_invoke_query_result_action_get_label() function extracts the
 * label to an icon of a given @c #navigator_invoke_query_result_action_t
 * structure. The @c label member allows the action to be identified with a
 * localized label name in UTF-8 format. For example, a suitable label for the
 * "bb.action.SHARE" action would be "Share". This function doesn't copy members
 * and the returned values are released once the @c bps_get_event() function is
 * called again.
 *
 * @param action The @c #navigator_invoke_query_result_action_t structure whose
 *               @c label member you want to retrieve.
 *
 * @return The label of the given @c action, @c NULL otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_query_result_action_get_label(
        const navigator_invoke_query_result_action_t *action);

/**
 * @brief Get the default target of an @c action from an invocation query result
 *
 * The @c navigator_invoke_query_result_action_get_default_target() function
 * extracts the default target of a given @c
 * #navigator_invoke_query_result_action_t structure. The @c default_target
 * member is the name of a target handler that is considered as the default
 * provider for the given @c action. This function doesn't copy members and the
 * returned values are released once the @c bps_get_event() function is called
 * again.
 *
 * Each @c action @c default_target conforms to the following guidelines:
 *      - Maximum 50 characters
 *      - Target: [Domain][Sub-domain]
 *      - Sub-domain:  NUL | .[Domain][Sub-domain]
 *      - Domain: [a-zA-Z]([a-zA-Z0-9_])*
 *
 * Example: "com.example.target"
 *
 * @param action The @c #navigator_invoke_query_result_action_t structure whose
 *               @c default_target member you want to retrieve.
 *
 * @return The default target of the given @c action, in the
 *         "[Domain][Sub-domain]" format (see description for further
 *         information), @c NULL otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_query_result_action_get_default_target(
        const navigator_invoke_query_result_action_t *action);

/**
 * @brief Get the number of @c target values in an @c action
 *
 * The @c invoke_get_query_result_target_count() function extracts the number of
 * @c #navigator_invoke_query_result_target_t structures contained within a @c
 * #navigator_invoke_query_result_action_t structure. The @c
 * #navigator_invoke_query_result_target_t target structures contained are
 * considered viable targets to perform the given action.
 *
 * @param action The @c #navigator_invoke_query_result_action_t structure
 *               holding the @c target values.
 *
 * @return The number of targets inside the @c action, -1 otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_query_result_action_get_target_count(
        const navigator_invoke_query_result_action_t *action);

/**
 * @brief Get a @c target from an @c action
 *
 * The @c navigator_invoke_query_result_action_get_target() function extracts
 * one of the @c #navigator_invoke_query_result_target_t structures inside of a
 * @c #navigator_invoke_query_result_action_t structure, identified by a given
 * @c index value. The @c #navigator_invoke_query_result_target_t target
 * structures contained are considered viable targets to perform the given
 * action. This function doesn't copy members and the returned values are
 * released once the @c bps_get_event() function is called again.
 *
 * @param action The @c #navigator_invoke_query_result_action_t structure
 *               holding the @c target values.
 *
 * @param index The numerical index value of the @c
 *              #navigator_invoke_query_result_target_t structure inside the
 *              given @c #navigator_invoke_query_result_action_t structure.
 *
 * @return The pointer to the returned target, @c NULL otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const navigator_invoke_query_result_target_t* navigator_invoke_query_result_action_get_target(
        const navigator_invoke_query_result_action_t *action, int index);

/**
 * @brief Get the key of a @c target for an @c action
 *
 * The @c navigator_invoke_query_result_target_get_key() function extracts the
 * target key of a given @c #navigator_invoke_query_result_target_t structure.
 * The @c key member is an identifier to a target (as stated in its BAR
 * manifest) that is capable of performing the specified action. This function
 * doesn't copy members and the returned values are released once the @c
 * bps_get_event() function is called again. You must call this function to
 * display returned @c target value(s).
 *
 * Each @c target @c key conforms to the following guidelines:
 *      - Maximum 50 characters
 *      - Target: [Domain][Sub-domain]
 *      - Sub-domain:  NUL | .[Domain][Sub-domain]
 *      - Domain: [a-zA-Z]([a-zA-Z0-9_])*
 *
 * Example: "com.example.invoke.target"
 *
 * @param target The @c #navigator_invoke_query_result_target_t structure whose
 *               @c key member you want to retrieve.
 *
 * @return The location key of the given target, in the "[Domain][Sub-domain]"
 *         format (see description for further information), @c NULL otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_query_result_target_get_key(
        const navigator_invoke_query_result_target_t *target);

/**
 * @brief Get the icon of an @c target for an @c action
 *
 * The @c navigator_invoke_query_result_target_get_icon() function extracts the
 * URI to an icon of a given @c #navigator_invoke_query_result_target_t
 * structure. The @c icon member is a path to an icon to be identified with the
 * corresponding target. This function doesn't copy members and the returned
 * values are released once the @c bps_get_event() function is called again. You
 * must call this function to display returned @c target value(s).
 *
 * @param target The @c #navigator_invoke_query_result_target_t structure whose
 *               @c icon member you want to retrieve.
 *
 * @return The icon URI of the given @c target, @c NULL otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_query_result_target_get_icon(
        const navigator_invoke_query_result_target_t *target);

/**
 * @brief The use of viewers has been deprecated - use applications or cards as
 *        invocation targets instead
 *
 * @deprecated The use of viewers has been deprecated - use applications or
 *             cards as invocation targets instead.
 *
 * The @c navigator_invoke_query_result_target_get_splash() function extracts
 * the URI to a splash icon of a given @c
 * #navigator_invoke_query_result_target_t structure. The @c splash member is a
 * path to an icon to be displayed to represent the given target while loading.
 * This function doesn't copy members and the returned values are released once
 * the @c bps_get_event() function is called again.
 *
 * You must call this function if the @c target @c type is a viewer. To test
 * this, call the @c navigator_invoke_query_result_target_get_type() function.
 * If the function returns @c NAVIGATOR_INVOKE_TARGET_TYPE_VIEWER, the given
 * target is a viewer).
 *
 * @param target The @c #navigator_invoke_query_result_target_t structure whose
 *               @c splash member you want to retrieve.
 *
 * @return The splash icon URI of the given @c target, @c NULL otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_query_result_target_get_splash(
        const navigator_invoke_query_result_target_t *target) BPS_DEPRECATED;

/**
 * @brief Get the label of a @c target for an @c action
 *
 * The @c navigator_invoke_query_result_target_get_label() function extracts the
 * label to an icon of a given @c #navigator_invoke_query_result_target_t
 * structure. The @c label member allows the target to be identified with a
 * localized label name in UTF-8 format. For example, "Example Target" would be
 * a suitable label for a target. This function doesn't copy members and the
 * returned values are released once the @c bps_get_event() function is called
 * again. You must call this function to display returned @c target value(s).
 *
 * @param target The @c #navigator_invoke_query_result_target_t structure whose
 *               @c label member you want to retrieve.
 *
 * @return The label of the given @c target, @c NULL otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_query_result_target_get_label(
        const navigator_invoke_query_result_target_t *target);

/**
 * @brief Get the type of a @c target for an @c action
 *
 * The @c navigator_invoke_query_result_target_get_type() function extracts the
 * target type of a given @c #navigator_invoke_query_result_target_t structure.
 * The @c type member allows the target to be identified as an
 * application, service, or card. You must call this function to display returned
 * @c target value(s).
 *
 * The possible values that you can receive from this member are:
 *     - @c NAVIGATOR_INVOKE_TARGET_TYPE_APPLICATION
 *     - @c NAVIGATOR_INVOKE_TARGET_TYPE_SERVICE
 *     - @c NAVIGATOR_INVOKE_TARGET_TYPE_HEADLESS
 *     - @c NAVIGATOR_INVOKE_TARGET_TYPE_CARD
 *
 * @param target The @c #navigator_invoke_query_result_target_t structure whose
 *               @c type member you want to retrieve.
 *
 * @return The type of the given @c target.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API navigator_invoke_target_type_t navigator_invoke_query_result_target_get_type(
        const navigator_invoke_query_result_target_t *target);

/**
 * @brief Get the perimeter of a @c target for an @c action
 *
 * The @c navigator_invoke_query_result_target_get_perimeter() function extracts
 * the @c perimeter member of a given @c #navigator_invoke_query_result_target_t
 * structure. The @c perimeter member indicates in which perimeter the given
 * target should reside. You must call this function to display returned @c
 * target value(s).
 *
 * The possible values that you can receive from this member are:
 *     - @c NAVIGATOR_INVOKE_PERIMETER_TYPE_PERSONAL
 *     - @c NAVIGATOR_INVOKE_PERIMETER_TYPE_ENTERPRISE
 *
 * @param target The @c #navigator_invoke_query_result_target_t structure whose
 *               @c perimeter member you want to retrieve.
 *
 * @return The perimeter in which the given @c target should reside.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API navigator_invoke_perimeter_type_t navigator_invoke_query_result_target_get_perimeter(
        const navigator_invoke_query_result_target_t *target);

/**
 * @brief The use of viewers has been deprecated - use applications or cards as
 *        invocation targets instead
 *
 * @deprecated The use of viewers has been deprecated - use applications or
 *             cards as invocation targets instead.
 *
 * The @c navigator_invoke_viewer_create() function creates an instance of a @c
 * #navigator_invoke_viewer_t structure called @c viewer to be used by the
 * invocation framework, and associates it to a @c
 * #navigator_invoke_invocation_t invocation structure. Destroy all viewer
 * instances created through this function once they are no longer needed by
 * using the @c navigator_invoke_viewer_destroy() function to prevent memory
 * leaks.
 *
 * @param viewer The @c #navigator_invoke_viewer_t structure to populate.
 *
 * @param invocation The @c #navigator_invoke_invocation_t structure to
 *                   associate with the given @c viewer. The @c invocation
 *                   member cannot be @c NULL. When you call this function,
 *                   ownership of the @c #navigator_invoke_invocation_t
 *                   structure is passed to the @c #navigator_invoke_viewer_t
 *                   structure, and is destroyed once you call the @c
 *                   navigator_invoke_viewer_destroy() function. For this
 *                   reason, don't call the @c
 *                   navigator_invoke_invocation_destroy() function once you
 *                   call the @c navigator_invoke_viewer_create() function.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_viewer_create(navigator_invoke_viewer_t **viewer,
        navigator_invoke_invocation_t *invocation) BPS_DEPRECATED;

/**
 * @brief The use of viewers has been deprecated - use applications or cards as
 *        invocation targets instead
 *
 * @deprecated The use of viewers has been deprecated - use applications or
 *             cards as invocation targets instead.
 *
 * The @c navigator_invoke_viewer_destroy() function deallocates any memory set
 * to a given @c viewer. Use this function to deallocate memory used by a @c
 * #navigator_invoke_viewer_t structure (created by the @c
 * navigator_invoke_viewer_create() function) that's no longer in use. Failing
 * to do so will result in a memory leak.
 *
 * Note that calling this function will also destroy the @c
 * #navigator_invoke_invocation_t structure associated with the given @c
 * #navigator_invoke_viewer_t structure. For this reason, don't call the @c
 * navigator_invoke_invocation_destroy() function on a @c
 * #navigator_invoke_invocation_t structure that has been associated with a
 * viewer using the @c navigator_invoke_viewer_create() function.
 *
 * @param viewer The @c #navigator_invoke_viewer_t structure to deallocate.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_viewer_destroy(
        navigator_invoke_viewer_t *viewer) BPS_DEPRECATED;

/**
 * @brief The use of viewers has been deprecated - use applications or cards as
 *        invocation targets instead
 *
 * @deprecated The use of viewers has been deprecated - use applications or
 *             cards as invocation targets instead.
 *
 * The @c navigator_invoke_event_get_viewer() function extracts a pointer to the
 * @c #navigator_invoke_viewer_t structure that has been sent to the handler
 * calling this function. Call this function from the event handler upon
 * receiving the @c NAVIGATOR_INVOKE_VIEWER event to extract the invocation
 * viewer properties (see the @c navigator_invoke_viewer_*() functions for
 * further details about the @c #navigator_invoke_viewer_t structure). The
 * pointer to the @c #navigator_invoke_viewer_t structure is valid until the @c
 * bps_get_event() function is called again.
 *
 * If you encounter an error in processing the viewer invocation, we recommend
 * that you call the @c navigator_event_get_err() function to determine the
 * nature of the error. The possible errors are:
 *     - @c INVOKE_NO_TARGET_ERROR
 *     - @c INVOKE_BAD_REQUEST_ERROR
 *     - @c INVOKE_INTERNAL_ERROR
 *     - @c INVOKE_TARGET_ERROR
 *
 * Note that "ownership" of the event is not passed to the handler. For this
 * reason, don't call the @c navigator_invoke_viewer_destroy() function from the
 * handler on @c #navigator_invoke_viewer_t structures that are retrieved using
 * this function.
 *
 * @param event The @c NAVIGATOR_INVOKE_VIEWER event targeted by the @c viewer.
 *
 * @return A pointer to the @c #navigator_invoke_viewer_t structure upon
 *         success, @c NULL with @c errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const navigator_invoke_viewer_t* navigator_invoke_event_get_viewer(
        bps_event_t *event) BPS_DEPRECATED;

/**
 * @brief The use of viewers has been deprecated - use applications or cards as
 *        invocation targets instead
 *
 * @deprecated The use of viewers has been deprecated - use applications or
 *             cards as invocation targets instead.
 *
 * The @c navigator_invoke_viewer_get_invocation() function extracts a pointer
 * to the @c #navigator_invoke_invocation_t structure that has been assigned to
 * the given @c #navigator_invoke_viewer_t structure. This can be used to
 * retrieve invocation members assigned to a given @c viewer. For example, call
 * this function from the event handler upon calling the @c
 * navigator_invoke_event_get_viewer() function to extract the invocation
 * properties of the viewer (see the @c navigator_invoke_invocation_set_*()
 * functions for further details about the @c #navigator_invoke_invocation_t
 * structure parameters).
 *
 * If you retrieved the given @c viewer using the @c
 * navigator_invoke_event_get_viewer() function, the pointer to the @c
 * #navigator_invoke_viewer_t structure remains valid until the @c
 * bps_get_event() function is called again. If you created the @c viewer using
 * @c navigator_invoke_viewer_create(), the pointer will be valid until the @c
 * navigator_invoke_viewer_destroy() function is called.
 *
 * Note that "ownership" of the invocation is not passed to the handler. For
 * this reason, don't call the @c navigator_invoke_invocation_destroy() function
 * on @c #navigator_invoke_invocation_t structures that are retrieved using this
 * function.
 *
 * @param viewer The @c #navigator_invoke_viewer_t structure to extract the @c
 *               #navigator_invoke_invocation_t structure from.
 *
 * @return A pointer to the @c #navigator_invoke_invocation_t structure upon
 *         success, @c NULL with @c errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const navigator_invoke_invocation_t* navigator_invoke_viewer_get_invocation(
        const navigator_invoke_viewer_t *viewer) BPS_DEPRECATED;

/**
 * @brief The use of viewers has been deprecated - use applications or cards as
 *        invocation targets instead
 *
 * @deprecated The use of viewers has been deprecated - use applications or
 *             cards as invocation targets instead.
 *
 * The @c navigator_invoke_viewer_set_window_id() function sets the window ID of
 * a given @c #navigator_invoke_viewer_t structure. The @c window_id member
 * identifies a window created by the viewer. You may use this for application
 * to viewer communication. You must set a @c window_id to all @c
 * #navigator_invoke_viewer_t structures.
 *
 * @param viewer A pointer to the @c #navigator_invoke_viewer_t structure whose
 *               @c window_id you want to set.
 *
 * @param window_id The window ID you want to associate with a window created by
 *                  the viewer. The value can be any string of characters. For
 *                  example, "window#123" is an acceptable window ID.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_viewer_set_window_id(
        navigator_invoke_viewer_t *viewer, const char* window_id) BPS_DEPRECATED;

/**
 * @brief The use of viewers has been deprecated - use applications or cards as
 *        invocation targets instead
 *
 * @deprecated The use of viewers has been deprecated - use applications or
 *             cards as invocation targets instead.
 *
 * The @c navigator_invoke_viewer_set_width() function sets the window width of
 * a given @c #navigator_invoke_viewer_t structure. The @c width member
 * identifies the width of a window created by the viewer. You must set a @c
 * width to all @c #navigator_invoke_viewer_t structures.
 *
 * @param viewer A pointer to the @c #navigator_invoke_viewer_t structure whose
 *               @c width you want to set.
 *
 * @param width The width in pixels you want to set to a window created by the
 *              viewer. The value must be an integer. For example, "100" is an
 *              acceptable width.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_viewer_set_width(
        navigator_invoke_viewer_t *viewer, int width) BPS_DEPRECATED;

/**
 * @brief The use of viewers has been deprecated - use applications or cards as
 *        invocation targets instead
 *
 * @deprecated The use of viewers has been deprecated - use applications or
 *             cards as invocation targets instead.
 *
 * The @c navigator_invoke_viewer_set_height() function sets the window height
 * of a given @c #navigator_invoke_viewer_t structure. The @c height member
 * identifies the height of a window created by the viewer. You must set a @c
 * height to all @c #navigator_invoke_viewer_t structures.
 *
 * @param viewer A pointer to the @c #navigator_invoke_viewer_t structure whose
 *               @c height you want to set.
 *
 * @param height The height in pixels you want to set to a window created by the
 *               viewer. The value must be an integer. For example, "100" is an
 *               acceptable height.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_viewer_set_height(
        navigator_invoke_viewer_t *viewer, int height) BPS_DEPRECATED;

/**
 * @brief The use of viewers has been deprecated - use applications or cards as
 *        invocation targets instead
 *
 * @deprecated The use of viewers has been deprecated - use applications or
 *             cards as invocation targets instead.
 *
 * The @c navigator_invoke_viewer_get_window_id() function extracts the window
 * ID of a given @c #navigator_invoke_viewer_t structure. The @c window_id
 * member is used to identify the window created by a viewer invocation (see the
 * @c navigator_invoke_viewer_set_window_id() function for further details).
 * This function doesn't copy members and the returned values are released once
 * the @c #navigator_invoke_viewer_t structure is destroyed with the @c
 * navigator_invoke_viewer_destroy() function.
 *
 * @param viewer A pointer to the @c #navigator_invoke_viewer_t structure whose
 *               @c window_id member you want to retrieve.
 *
 * @return The invocation viewer window ID if was provided by the sender, @c
 *         NULL with @c errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_viewer_get_window_id(
        const navigator_invoke_viewer_t *viewer) BPS_DEPRECATED;

/**
 * @brief The use of viewers has been deprecated - use applications or cards as
 *        invocation targets instead
 *
 * @deprecated The use of viewers has been deprecated - use applications or
 *             cards as invocation targets instead.
 *
 * The @c navigator_invoke_viewer_get_width() function extracts the window width
 * of a given @c #navigator_invoke_viewer_t structure. The @c width member is
 * used to set the width of the window created by a viewer invocation (see the
 * @c navigator_invoke_viewer_set_width() function for further details).
 *
 * @param viewer A pointer to the @c #navigator_invoke_viewer_t structure whose
 *               @c width member you want to retrieve.
 *
 * @return The invocation viewer width if was provided by the sender, -1 with @c
 *         errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_viewer_get_width(
        const navigator_invoke_viewer_t *viewer) BPS_DEPRECATED;

/**
 * @brief The use of viewers has been deprecated - use applications or cards as
 *        invocation targets instead
 *
 * @deprecated The use of viewers has been deprecated - use applications or
 *             cards as invocation targets instead.
 *
 * The @c navigator_invoke_viewer_get_height() function extracts the window
 * height of a given @c #navigator_invoke_viewer_t structure. The @c height
 * member is used to set the height of the window created by a viewer invocation
 * (see the @c navigator_invoke_viewer_set_height() function for further
 * details).
 *
 * @param viewer A pointer to the @c #navigator_invoke_viewer_t structure whose
 *               @c height member you want to retrieve.
 *
 * @return The invocation viewer height if was provided by the sender, -1 with
 *         @c errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_viewer_get_height(
        const navigator_invoke_viewer_t *viewer) BPS_DEPRECATED;

/**
 * @brief The use of viewers has been deprecated - use applications or cards as
 *        invocation targets instead
 *
 * @deprecated The use of viewers has been deprecated - use applications or
 *             cards as invocation targets instead.
 *
 * The @c navigator_invoke_viewer_send() function invokes a target handler
 * that is specified by the given @c #navigator_invoke_invocation_t structure
 * within the @c #navigator_invoke_viewer_t structure (see the @c
 * navigator_invoke_invocation_send() function for more details regarding how
 * a target for an invocation is determined). The handler uses the information
 * provided in the @c #navigator_invoke_viewer_t structure to invoke an instance
 * of a viewer with the given parameters.
 *
 * @param viewer The @c #navigator_invoke_viewer_t structure to send.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_viewer_send(
        const navigator_invoke_viewer_t *viewer) BPS_DEPRECATED;

/**
 * @brief The use of viewers has been deprecated - use applications or cards as
 *        invocation targets instead
 *
 * @deprecated The use of viewers has been deprecated - use applications or
 *             cards as invocation targets instead.
 *
 * The @c navigator_invoke_close_viewer() function closes the viewer window of a
 * given @c #navigator_invoke_viewer_t structure that was started with the
 * @c navigator_invoke_viewer_send() function.
 *
 * @param window_id The window ID associated with the viewer window you want to
 *        close. The @c window_id member cannot be @c NULL.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_close_viewer(const char *window_id) BPS_DEPRECATED;

/**
 * @brief The use of viewers has been deprecated - use applications or cards as
 *        invocation targets instead
 *
 * @deprecated The use of viewers has been deprecated - use applications or
 *             cards as invocation targets instead.
 *
 * The @c navigator_invoke_viewer_relay() function enables two way communication
 * between the parent application and the viewer in the form of request/response
 * messages. Both the viewer and the parent application use this function to
 * send the data to each other.
 *
 * If you call this function, the target application or viewer receives the @c
 * NAVIGATOR_INVOKE_VIEWER_RELAY request event, and can retrieve the sent data.
 * The sender gets a @c NAVIGATOR_INVOKE_VIEWER_RELAY_RESULT response event as a
 * response to the sent message.
 *
 * If you encounter an error in processing the message delivery, we recommend
 * that you call the @c navigator_event_get_err() function to determine the
 * nature of the error. The possible errors are:
 *     - @c INVALID_WINDOW_ID
 *     - @c INVALID_MESSAGE
 *
 * @param window_id The window ID associated with the viewer. The @c window_id
 *                  member must not be NULL.
 * @param message_name The name or title of the message you want to send. The @c
 *                     message_name member must not be NULL.
 * @param data The data you want to send the viewer relay message target. The @c
 *             data member can be NULL.
 * @param id The ID of the message. This is used to correlate the request with
 *           the peer's response. If you don't set this member, the sender
 *           doesn't receive a response to the sent message. Use the @c
 *           navigator_event_get_id() function to retrieve the @c id from the
 *           @c NAVIGATOR_INVOKE_VIEWER_RELAY_RESULT response event.
 * @param is_response The request/response type of the message. If this member
 *                    is @c false, the message type is a request, otherwise it's
 *                    a response. The request messages are received by peer
 *                    through @c NAVIGATOR_INVOKE_VIEWER_RELAY events. The
 *                    responses from the peer are received through @c
 *                    NAVIGATOR_INVOKE_VIEWER_RELAY_RESULT events.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_viewer_relay(const char *window_id,
        const char *message_name, const char *data, const char *id,
        bool is_response) BPS_DEPRECATED;

/**
 * @brief The use of viewers has been deprecated - use applications or cards as
 *        invocation targets instead
 *
 * @deprecated The use of viewers has been deprecated - use applications or
 *             cards as invocation targets instead.
 *
 * The @c navigator_invoke_event_get_viewer_relay_window_id() function extracts
 * the window ID of a given viewer relay message (created and sent using the @c
 * navigator_invoke_viewer_relay() function). The @c window_id member is used by
 * the receiving target to identify the @c viewer that sent the message. Call
 * this function in the parent application upon receiving the @c
 * NAVIGATOR_INVOKE_VIEWER_RELAY event to identify the corresponding @c viewer.
 * This function doesn't copy data and the returned values are released once the
 * @c bps_get_event() function is called again.
 *
 * @param event The @c NAVIGATOR_INVOKE_VIEWER_RELAY event targeted by the @c
 *              viewer.
 *
 * @return The window ID of the viewer that sent the relay data, @c NULL with @c
 *         errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_event_get_viewer_relay_window_id(
        bps_event_t *event) BPS_DEPRECATED;

/**
 * @brief The use of viewers has been deprecated - use applications or cards as
 *        invocation targets instead
 *
 * @deprecated The use of viewers has been deprecated - use applications or
 *             cards as invocation targets instead.
 *
 * The @c navigator_invoke_event_get_viewer_relay_message_name() function
 * extracts the name of a given viewer relay message (created and sent using the
 * @c navigator_invoke_viewer_relay() function). The @c name member is used by
 * the receiving target (either the viewer or parent application) to identify
 * the name of the message sent by the sender (if the receiver is the viewer,
 * then the sender is the parent application, and vice versa). Call this
 * function upon receiving the @c NAVIGATOR_INVOKE_VIEWER_RELAY event to
 * identify the message name. This function doesn't copy data and the returned
 * values are released once the @c bps_get_event() function is called again.
 *
 * @param event The @c NAVIGATOR_INVOKE_VIEWER_RELAY event targeted by the
 *              sender of the viewer relay message.
 *
 * @return The name of the message set by the viewer relay sender, @c NULL with
 *         @c errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_event_get_viewer_relay_message_name(
        bps_event_t *event) BPS_DEPRECATED;

/**
 * @brief The use of viewers has been deprecated - use applications or cards as
 *        invocation targets instead
 *
 * @deprecated The use of viewers has been deprecated - use applications or
 *             cards as invocation targets instead.
 *
 * The @c navigator_invoke_event_get_viewer_relay_data() function extracts the
 * data of a given viewer relay message (created and sent using the @c
 * navigator_invoke_viewer_relay() function). The @c data member is used by
 * the receiving target (either the viewer or parent application) to identify
 * the data content of the message sent by the sender (if the receiver is the
 * viewer, then the sender is the parent application, and vice versa). Call this
 * function upon receiving the @c NAVIGATOR_INVOKE_VIEWER_RELAY event to
 * identify the data of the message. This function doesn't copy data and the
 * returned values are released once the @c bps_get_event() function is called
 * again.
 *
 * @param event The @c NAVIGATOR_INVOKE_VIEWER_RELAY event targeted by the
 *              sender of the viewer relay message.
 *
 * @return The data of the message set by the viewer relay sender, @c NULL with
 *         @c errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_event_get_viewer_relay_data(
        bps_event_t *event) BPS_DEPRECATED;

/**
 * @brief The use of viewers has been deprecated - use applications or cards as
 *        invocation targets instead
 *
 * @deprecated The use of viewers has been deprecated - use applications or
 *             cards as invocation targets instead.
 *
 * The @c navigator_invoke_event_get_window_id() function extracts the window ID
 * of a given viewer that has been terminated. The @c window_id member is used
 * by the parent application to identify the @c viewer that was terminated. Call
 * this function in the parent application upon receiving a @c
 * NAVIGATOR_INVOKE_VIEWER_STOPPED event to identify the terminated @c viewer.
 * This function doesn't copy data and the returned values are released once the
 * @c bps_get_event() function is called again.
 *
 * @param event The @c NAVIGATOR_INVOKE_VIEWER_STOPPED event triggered by the
 *              terminated @c viewer.
 *
 * @return The window ID of the terminated @c viewer, @c NULL with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_event_get_window_id(bps_event_t *event) BPS_DEPRECATED;

/**
 * @brief Get the key of an invoked @c target from the BPS event
 *
 * The @c navigator_invoke_event_get_target() function extracts the target key
 * of an invoked target application. The target key is an identifier to a
 * target (as stated in its BAR manifest) that had been invoked. Call this
 * function in the application upon receiving a @c
 * NAVIGATOR_INVOKE_TARGET_RESULT event to identify the target that was invoked.
 * This function doesn't copy data and the returned value is released once the
 * @c bps_get_event() function is called again.
 *
 * @param event The @c NAVIGATOR_INVOKE_TARGET_RESULT event triggered by the
 *              invoked target.
 *
 * @return The key of the target that was invoked, NULL with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_event_get_target(bps_event_t *event);

/**
 * @brief Get the type of an invoked @c target from the BPS event
 *
 * The @c navigator_invoke_event_get_target() function extracts the target type
 * of an invoked target application. The @c type member allows the target to be
 * identified as an application, service, or card.
 *
 * The possible values that you can receive from this member are:
 *     - @c NAVIGATOR_INVOKE_TARGET_TYPE_APPLICATION
 *     - @c NAVIGATOR_INVOKE_TARGET_TYPE_CARD
 *     - @c NAVIGATOR_INVOKE_TARGET_TYPE_SERVICE
 *     - @c NAVIGATOR_INVOKE_TARGET_TYPE_HEADLESS
 *
 * @param event The @c NAVIGATOR_INVOKE_TARGET_RESULT event triggered by the
 *              invoked target.
 *
 * @return The type of the target that was invoked upon success, @c BPS_FAILURE
 *         with @c errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_event_get_target_type(bps_event_t *event);

/**
 * @brief Get the group ID of an invocation source application from the BPS
 *        event
 *
 * The @c navigator_invoke_event_get_group_id() function extracts the group ID
 * of an
 * invocation source application. The group ID is an identifier to the client
 * application that sent the invocation. Call this function in the application
 * upon receiving a @c NAVIGATOR_INVOKE_TARGET event to identify the source
 * of the invocation.
 *
 * @param event The @c NAVIGATOR_INVOKE_TARGET event triggered by the
 *              source application.
 *
 * @return The group ID of the invocation source application upon success, @c
 *         BPS_FAILURE with @c errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int64_t navigator_invoke_event_get_group_id(bps_event_t *event);

/**
 * @brief Get the error code associated with an invoke request
 *
 * The @c navigator_invoke_event_get_error_code() function returns the
 * error code of invoke request responses. The error code is set when
 * @c navigator_event_get_err() is not @c NULL and @c bps_event_get_code()
 * is one of:
 *  - @c NAVIGATOR_INVOKE_TARGET_RESULT
 *  - @c NAVIGATOR_INVOKE_SET_FILTERS_RESULT
 *  - @c NAVIGATOR_INVOKE_QUERY_RESULT
 *  - @c NAVIGATOR_INVOKE_GET_FILTERS_RESULT
 *
 * @param event The event associated with the invoke request whose
 *              result has an error code set.
 *
 * @return The error code of the request upon success,
 *         @c BPS_FAILURE with @c errno set otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int navigator_invoke_event_get_error_code(bps_event_t *event);

/**
 * @brief Get the dname of an invocation source application from the BPS event
 *
 * The @c navigator_invoke_event_get_dname() function extracts the dname of an
 * invocation source application. The dname is an identifier to a package, and
 * contains the package name and package ID attributes. Call this function in
 * the application upon receiving a @c NAVIGATOR_INVOKE_TARGET event to
 * identify the source of the invocation.
 * This function doesn't copy data and the returned value is released once the
 * @c bps_get_event() function is called again.
 *
 * @param event The @c NAVIGATOR_INVOKE_TARGET event triggered by
 *              the source application.
 *
 * @return The dname of the invocation source application.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_event_get_dname(bps_event_t *event);

/**
 * @brief Sends the set target filters request to the invocation framework.
 *
 * The @c navigator_invoke_set_filters() function sends the set target filters
 * request to the invocation framework.
 *
 * @param id The ID you want to display on the delivery receipt response. This
 *           value must be in numerical format. For example, a valid @c id
 *           would be "42".
 *
 * @param target The target key of the target whose filters are to be set.
 *
 * @param filters The array of filters to be set.
 *
 * @param filters_count The size of the filters array.
 *
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_set_filters(const char *id, const char *target,
        const char *filters[], size_t filters_count);

/**
 * @brief Sends the get target filters invocation request to the invocation
 * framework.
 *
 * The @c navigator_invoke_get_filters() function sends the get target filters
 * invocation request to the invocation framework.
 *
 * @param id The ID you want to display on the delivery receipt response. This
 *           value must be in numerical format. For example, a valid @c id
 *           would be "42".
 *
 * @param target The target key of the target whose filters are to be retrieved.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_get_filters(const char *id, const char *target);

/**
 * @brief Get the target of the get target filters invocation result
 *
 * The function doesn't copy the data and the returned value will be released
 * once the @c bps_get_event() function is called again.
 *
 * The @c navigator_invoke_event_get_filters_target()
 * function should be called by the application upon receiving the
 * @c NAVIGATOR_INVOKE_GET_FILTERS_RESULT event to extract the
 * target of the get target filters invocation.
 *
 * @param event The @c NAVIGATOR_INVOKE_GET_FILTERS_RESULT event.
 *
 * @return The the target of the get target filters invocation result.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_event_get_filters_target(
        bps_event_t *event);

/**
 * @brief Get the filters count of the get target filters invocation result
 *
 * The function doesn't copy the data and the returned value will be released
 * once the @c bps_get_event() function is called again.
 *
 * The
 * @c navigator_invoke_event_get_filters_count()
 * function should be called by the application upon receiving the
 * @c NAVIGATOR_INVOKE_GET_FILTERS_RESULT event to extract the
 * filters count of the get target filters invocation.
 *
 * @param event The @c NAVIGATOR_INVOKE_GET_FILTERS_RESULT
 * event.
 *
 * @return The the filters count of the get target filters invocation result.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_event_get_filters_count(bps_event_t *event);

/**
 * @brief Get the filter of the get target filters invocation result
 *
 * The function doesn't copy the data and the returned value will be released
 * once the @c bps_get_event() function is called again.
 *
 * The @c navigator_invoke_event_get_filter()
 * function should be called by the application upon receiving the
 * @c NAVIGATOR_INVOKE_GET_FILTERS_RESULT event to extract the
 * filter of the get target filters invocation.
 *
 * @param event The @c NAVIGATOR_INVOKE_GET_FILTERS_RESULT event.
 *
 * @param index The index of the filter in the filters array
 *
 * @return The filter at the index from the get target filters invocation result.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_event_get_filter(bps_event_t *event,
        int index);

/**
 * @brief Request that the list item specified by @c selection is invoked to
 * replace the current list item that this application belongs to
 *
 * The @c navigator_invoke_select_list_item() function sends a request to the
 * Navigator to invoke the list item @c selection from the list that this
 * application belongs to.
 *
 * The requesting application must be launched as an invoke list item. Success
 * is determined by whether the request has been sent.
 *
 * @param selection  The list item to invoke. This is either @c
 *                   NAVIGATOR_INVOKE_LIST_CURSOR_DIRECTION_NEXT to invoke the
 *                   next list item or @c
 *                   NAVIGATOR_INVOKE_LIST_CURSOR_DIRECTION_PREVIOUS to invoke
 *                   the previous list item. @c
 *                   NAVIGATOR_INVOKE_LIST_CURSOR_DIRECTION_UNSPECIFIED is
 *                   unsupported.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int navigator_invoke_select_list_item(
        navigator_invoke_list_cursor_direction_t selection);

/**
 * @brief Get the list id of @c NAVIGATOR_INVOKE_LIST_ITEM_SELECTED and
 * @c NAVIGATOR_INVOKE_LIST_CURSOR_MOVED events
 *
 * The @c navigator_invoke_event_get_list_id() function returns the list ID
 * of the list that the event corresponds to.
 *
 * @param event The @c NAVIGATOR_INVOKE_LIST_ITEM_SELECTED or
 *              @c NAVIGATOR_INVOKE_LIST_CURSOR_MOVED event.
 *
 * @return list ID upon success, @c BPS_FAILURE with @c errno set otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int navigator_invoke_event_get_list_id(bps_event_t *event);

/**
 * @brief Get the direction of movement from
 * @c NAVIGATOR_INVOKE_LIST_CURSOR_MOVED events
 *
 * The @c navigator_invoke_event_get_list_cursor_direction() function returns
 * the direction in which the list item cursor should move.
 *
 * @param event The @c NAVIGATOR_INVOKE_LIST_CURSOR_MOVED event.
 *
 * @return The direction of movement in the list upon success,
 *         @c BPS_FAILURE with @c errno set otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int navigator_invoke_event_get_list_cursor_direction(bps_event_t *event);

/**
 * @brief Get which list item to select from
 * @c NAVIGATOR_INVOKE_LIST_ITEM_SELECTED events
 *
 * The @c navigator_invoke_event_get_list_item_selection() function returns
 * which list item to select.
 *
 * @param event The @c NAVIGATOR_INVOKE_LIST_ITEM_SELECTED event.
 *
 * @return The @c #navigator_invoke_list_cursor_direction_t of the list item to
 *         select upon success, @c BPS_FAILURE with @c errno set otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int navigator_invoke_event_get_list_item_selection(bps_event_t *event);

/**
 * @brief Convert a percent-encoded file URI to a file path
 *
 * The @c navigator_invoke_uri_to_local_path() function can be called to convert
 * file URIs retrieved from invocation events to file paths. This function
 * expects @c uri to start with "file:///", and handles percent-encoded URIs.
 *
 * This function allocates memory that needs to be freed by the @c bps_free()
 * function.
 *
 * For example:
 * @code
 *   char *file_path =
 *        navigator_invoke_uri_to_local_path("file:///path/to/some%20file.txt");
 *
 *   // file_path is "/path/to/some file.txt"
 *
 *   bps_free(file_path);
 * @endcode
 *
 * @param uri The URI encoded file path.  It needs to start with "file:///".
 *
 * @return The local file path upon success; NULL with @c errno set upon
 *         failure.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API char* navigator_invoke_uri_to_local_path(const char* uri);

/**
 * @brief Convert an absolute file path to a percent-encoded file URI
 *
 * The @c navigator_invoke_local_path_to_uri() function should be called by the
 * application to ensure that a file path is converted to a percent-encoded file
 * URI for use with invocation functions.
 *
 * This function expects @c path to start with "/".
 *
 * The function allocates memory that needs to be freed by the @c bps_free()
 * function.
 *
 * For example:
 * @code
 *   char *file_uri =
 *                navigator_invoke_local_path_to_uri("/path/to/some file.txt");
 *
 *   // file_uri is "file:///path/to/some%20file.txt"
 *
 *   bps_free(file_uri);
 * @endcode
 *
 * @param path The absolute file path.  It needs to start with "/".
 *
 * @return A percent-encoded file URI that corresponds to @c path upon success;
 *         NULL with @c errno set upon failure.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API char* navigator_invoke_local_path_to_uri(const char* path);

/**
 * @brief Create an opaque structure to register a specific time trigger
 *
 * This function creates an instance of a @c #navigator_invoke_specific_time_t
 * structure to use for timer registration.
 * Destroy each invocation instance created by this function once it is no
 * longer needed by calling @c navigator_invoke_specific_time_destroy() to
 * prevent memory leaks.
 *
 * @param specific_time A pointer to the @c #navigator_invoke_specific_time_t
 *        structure to populate.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API int navigator_invoke_specific_time_create(
        navigator_invoke_specific_time_t **specific_time);

/**
 * @brief Deallocate the memory used by a @c navigator_invoke_specific_time_t
 *        structure
 *
 * This function deallocates memory used by a
 * @c #navigator_invoke_specific_time_t structure.
 *
 * Use this function to deallocate memory used by a structure created by
 * @c #navigator_invoke_specific_time_create() is no longer in use. Failure to
 * do so will result in memory leaks.
 *
 * @param specific_time The @c #navigator_invoke_specific_time_t structure to
 *        deallocate.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API int navigator_invoke_specific_time_destroy(
        navigator_invoke_specific_time_t *specific_time);

/**
 * @brief Create an opaque structure that represents a recurrence rule
 *
 * This function creates an instance of a
 * @c #navigator_invoke_recurrence_rule_t structure to use for timer
 * registration.
 *
 * Destroy each instance created by this function once they are no longer
 * needed by calling @c #navigator_invoke_recurrence_rule_destroy() to prevent
 * memory leaks.
 *
 * @param recurrence_rule A pointer to the new
 *        @c #navigator_invoke_recurrence_rule_t structure to populate.
 * @param frequency The frequency of the recurrence.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API int navigator_invoke_recurrence_rule_create(
        navigator_invoke_recurrence_rule_t **recurrence_rule,
        navigator_invoke_recurrence_rule_frequency_t frequency);

/**
 * @brief Deallocate the memory used by a @c navigator_invoke_recurrence_rule_t
 *        structure
 *
 * This function deallocates memory used by a
 * @c #navigator_invoke_recurrence_rule_t structure. Use this function to
 * deallocate memory used by structures created by
 * @c navigator_invoke_recurrence_rule_create() that are no longer in use.
 * Failure to do so will result in memory leaks.
 *
 * @param recurrence_rule The @c #navigator_invoke_recurrence_rule_t structure
 *                        to deallocate.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API int navigator_invoke_recurrence_rule_destroy(
        navigator_invoke_recurrence_rule_t *recurrence_rule);


/**
 * @brief Create an invoke timer registration request
 *
 * The @c navigator_invoke_timer_registration_create() function creates an
 * instance of a @c #navigator_invoke_timer_registration_t structure,
 * @c reg to be used for timer registration and deregistration. Destroy all
 * invocation instances created through this function once they are no longer
 * needed by using the @c navigator_invoke_timer_registration_destroy() function
 * to prevent memory leaks.
 *
 * @param reg The @c #navigator_invoke_timer_registration_t structure to
 *        populate.
 *
 * @param type The type of trigger to register.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API int navigator_invoke_timer_registration_create(
        navigator_invoke_timer_registration_t **reg,
        navigator_invoke_timer_trigger_type_t type);

/**
 * @brief Deallocate the memory used by a
 *        @c navigator_invoke_timer_registration_t structure
 *
 * The @c navigator_invoke_timer_registration_destroy() function deallocates
 * memory allocated for a given @c navigator_invoke_timer_registration_t.
 * Use this function to clean up resources used by a
 * @c #navigator_invoke_timer_registration_t structure (created by
 * @c navigator_invoke_timer_registration_create()) that's no longer in use.
 * Failure to do so will result in a memory leak.
 *
 * @param reg The @c #navigator_invoke_timer_registration_t structure to
 *        deallocate.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API int navigator_invoke_timer_registration_destroy(
        navigator_invoke_timer_registration_t *reg);

/**
 * @brief Set the year slot of a specific time structure
 *
 * This function sets the @c year slot of a
 * @c #navigator_invoke_specific_time_t structure.
 *
 * @param specific_time The @c #navigator_invoke_specific_time_t structure to
 *        modify.
 * @param year The year to set.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API int navigator_invoke_specific_time_set_year(
        navigator_invoke_specific_time_t *specific_time, int year);

/**
 * @brief Set the month of a specific time structure
 *
 * This function sets the @c month value of a
 * @c #navigator_invoke_specific_time_t structure.
 *
 * @param specific_time The @c #navigator_invoke_specific_time_t structure to
 *        modify.
 * @param month The month to set, from 1 to 12, inclusive.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API int navigator_invoke_specific_time_set_month(
        navigator_invoke_specific_time_t *specific_time, int month);

/**
 * @brief Set the day of a specific time structure
 *
 * This function sets the @c day value of a
 * @c #navigator_invoke_specific_time_t structure.
 *
 * @param specific_time The @c #navigator_invoke_specific_time_t structure to
 *        modify.
 * @param day The day to set, from 1 to 31, inclusive.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API int navigator_invoke_specific_time_set_day(
        navigator_invoke_specific_time_t *specific_time, int day);

/**
 * @brief Set the hour of a specific time structure
 *
 * This function sets the @c hour value of a
 * @c #navigator_invoke_specific_time_t structure.
 *
 * @param specific_time The @c #navigator_invoke_specific_time_t structure to
 *        modify.
 * @param hour The hour to set, from 0 to 23, inclusive.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API int navigator_invoke_specific_time_set_hour(
        navigator_invoke_specific_time_t *specific_time, int hour);

/**
 * @brief Set the minute of a specific time structure
 *
 * This function sets the @c minute value of a
 * @c #navigator_invoke_specific_time_t structure.
 *
 * @param specific_time The @c #navigator_invoke_specific_time_t
 *        structure to modify.
 * @param minute The minute to set, from 0 to 59, inclusive.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API int navigator_invoke_specific_time_set_minute(
        navigator_invoke_specific_time_t *specific_time, int minute);

/**
 * @brief Set the time_zone of a specific time structure
 *
 * This function sets the @c time_zone of a
 * @c #navigator_invoke_specific_time_t structure.
 *
 * The time zone ID can be a programmatic ID such as "America/Los_Angeles"
 * which is defined in the standard Olson/IANA timezone database used by UNIX
 * systems. The programmatic ID has the format continent/city or ocean/city.
 * The time zone ID can also be a custom ID such as "GMT-8:00". The custom ID
 * has the syntax "GMT[+|-]hh[[:]mm]". A list of supported time zone IDs can be
 * obtained by calling @c ucal_openTimeZones() declared in header file
 * <unicode/ucal.h> The wikipedia link
 * http://en.wikipedia.org/wiki/List_of_tz_database_time_zones has a list of
 * time zones in the programmatic ID format. Please use the latter with
 * caution, as some of these may or may not be supported on your platform.
 *
 * @param specific_time The @c #navigator_invoke_specific_time_t structure to
 *        modify.
 * @param time_zone The time zone ID to set.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API int navigator_invoke_specific_time_set_time_zone(
        navigator_invoke_specific_time_t *specific_time, const char* time_zone);

/**
 * @brief Retrieve the year value from a navigator_invoke_specific_time_t
 *
 * This function retrieves the year value from the given
 * @c #navigator_invoke_specific_time_t.
 *
 * @param specific_time The @c #navigator_invoke_specific_time_t structure to
 *        query.
 *
 * @return The year upon success, @c BPS_FAILURE with @c errno set otherwise.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API int navigator_invoke_specific_time_get_year(
        const navigator_invoke_specific_time_t *specific_time);

/**
 * @brief Retrieve the month value from a navigator_invoke_specific_time_t
 *
 * This function retrieves the month value from the given
 * @c #navigator_invoke_specific_time_t.
 *
 * @param specific_time The @c #navigator_invoke_specific_time_t structure to
 *        query.
 *
 * @return The month upon success, @c BPS_FAILURE with @c errno set otherwise.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API int navigator_invoke_specific_time_get_month(
        const navigator_invoke_specific_time_t *specific_time);

/**
 * @brief Retrieve the day value from a navigator_invoke_specific_time_t
 *
 * This function retrieves the day value from the given
 * @c #navigator_invoke_specific_time_t.
 *
 * @param specific_time The @c #navigator_invoke_specific_time_t structure to
 *        query.
 *
 * @return The day upon success, @c BPS_FAILURE with @c errno set otherwise.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API int navigator_invoke_specific_time_get_day(
        const navigator_invoke_specific_time_t *specific_time);

/**
 * @brief Retrieve the hour value from a navigator_invoke_specific_time_t
 *
 * This function retrieves the hour value from the given
 * @c #navigator_invoke_specific_time_t.
 *
 * @param specific_time The @c #navigator_invoke_specific_time_t structure to
 *        query.
 *
 * @return The hour upon success, @c BPS_FAILURE with @c errno set otherwise.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API int navigator_invoke_specific_time_get_hour(
        const navigator_invoke_specific_time_t *specific_time);

/**
 * @brief Retrieve the minute value from a navigator_invoke_specific_time_t
 *
 * This function retrieves the minute value from the given
 * @c #navigator_invoke_specific_time_t.
 *
 * @param specific_time The @c #navigator_invoke_specific_time_t structure to
 *        query.
 *
 * @return The minute upon success, @c BPS_FAILURE with @c errno set otherwise.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API int navigator_invoke_specific_time_get_minute(
        const navigator_invoke_specific_time_t *specific_time);

/**
 * @brief Retrieve the time zone ID from a navigator_invoke_specific_time_t
 *
 * This function retrieves the time zone ID value from the given
 * @c #navigator_invoke_specific_time_t.
 *
 * @param specific_time The @c #navigator_invoke_specific_time_t structure to
 *        query.
 *
 * @return The time zone ID if it was set, @c NULL otherwise.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API const char* navigator_invoke_specific_time_get_time_zone(
        const navigator_invoke_specific_time_t *specific_time);

/**
 * @brief Set the count limit of a recurrence rule structure
 *
 * This function sets the count limit of a
 * @c #navigator_invoke_recurrence_rule_t structure.
 *
 * A recurrence rule can have either a count limit or a date limit.
 * Setting a count limit deletes any previously set date limit.
 *
 * @param recurrence_rule The @c #navigator_invoke_recurrence_rule_t
 *        structure to modify.
 * @param count_limit The count limit to set. A value of zero will reset the
 *                    count limit. A negative value will cause @c BPS_FAILURE
 *                    to be returned.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API int navigator_invoke_recurrence_rule_set_count_limit(
        navigator_invoke_recurrence_rule_t *recurrence_rule, int count_limit);

/**
 * @brief Set the date limit of a recurrence rule structure
 *
 * This function sets the date limit of a
 * @c #navigator_invoke_recurrence_rule_t structure.
 *
 * The date limit is the time at which the recurrence rule will no longer be
 * applied. A recurrence rule can have either a count limit or a date limit.
 * Setting a date limit deletes any previously set count limit.
 *
 * If either the start date or date limit field of a recurrence rule has a
 * time-zone set, the other field must also have a time-zone set. Otherwise
 * this function fails and returns @c BPS_FAILURE. The two fields do not have
 * to be set to the same time-zone.
 *
 * This function doesn't transfer ownership of @c date_limit to
 * @c recurrence_rule. A copy of @c date_limit is kept by @c recurrence_rule.
 * @c date_limit must be freed to avoid memory leaks. If you change the
 * value of @c date_limit after calling this function, the updated time will not
 * be used unless you call this function again.
 *
 * @param recurrence_rule The @c #navigator_invoke_recurrence_rule_t
 *        structure to modify.
 * @param date_limit The date limit to set.  A @c NULL value will reset the date
 *        limit.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API int navigator_invoke_recurrence_rule_set_date_limit(
        navigator_invoke_recurrence_rule_t *recurrence_rule,
        const navigator_invoke_specific_time_t* date_limit);

/**
 * @brief Set the interval of a recurrence rule structure
 *
 * This function sets the @c interval of a
 * @c #navigator_invoke_recurrence_rule_t structure.
 *
 * The interval is along with the frequency to specify a period for the
 * recurrence rule. For instance, setting the interval to @c 2 and the
 * frequency to @c NAVIGATOR_INVOKE_RECURRENCE_RULE_FREQUENCY_WEEKLY will
 * produce a rule that is applied every other week.
 *
 * @param recurrence_rule The @c #navigator_invoke_recurrence_rule_t structure
 *        to modify.
 * @param interval The interval to set. @c BPS_FAILURE is returned when zero or
 *        a negative value is passed as the interval.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API int navigator_invoke_recurrence_rule_set_interval(
        navigator_invoke_recurrence_rule_t *recurrence_rule, int interval);

/**
 * @brief Set the start date of a recurrence rule structure
 *
 * This function sets the start date of a
 * @c #navigator_invoke_recurrence_rule_t structure.
 *
 * The start date is the time from which the recurrence rule can be applied.
 *
 * This is a mandatory field for recurrent timers.
 *
 * If either the start date or date limit field of a recurrence rule has a
 * time-zone set, the other field must also have a time-zone set. Otherwise
 * this function fails and returns @c BPS_FAILURE. The two fields do not have
 * to be set to the same time-zone.
 *
 * This function doesn't transfer ownership of @c start_date to
 * @c recurrence_rule. @c recurrence_rule keeps a copy of @c start_date.
 * @c start_date must be freed to avoid memory leaks. If you change the
 * value of @c start_date after calling this function, you must call this
 * function again to use the new start date.
 *
 * @param recurrence_rule The @c #navigator_invoke_recurrence_rule_t
 *        structure to modify.
 * @param start_date The start date to set.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API int navigator_invoke_recurrence_rule_set_start_date(
        navigator_invoke_recurrence_rule_t *recurrence_rule,
        const navigator_invoke_specific_time_t* start_date);

/**
 * @brief Sets the minutes of an hour of a recurrence rule structure
 *
 * This function sets the @c minutes_of_hour of a
 * @c #navigator_invoke_recurrence_rule_t structure.
 *
 * Starting from the start date of the recurrence rule, the trigger will be
 * applied at @c minutes_of_hour per the frequency of the recurrence rule, as
 * allowed by other recurrence conditions, until the count limit or date limit
 * are reached, if applicable.
 *
 * This function doesn't transfer ownership of @c minutes_of_hour to
 * @c recurrence_rule. @c recurrence_rule keeps a copy of @c minutes_of_hour.
 * If applicable, @c minutes_of_hour must be freed to avoid memory leaks. If
 * you change the value of @c minutes_of_hour calling this function, you must
 * call this function again to use the new value.
 *
 * @param recurrence_rule The @c #navigator_invoke_recurrence_rule_t structure
 *        to modify.
 * @param minutes_of_hour An array containing the minutes to be set, within the
 *        range 0 to 59, inclusive.
 * @param count The size of the @c minutes_of_hour array.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API int navigator_invoke_recurrence_rule_set_minutes_of_hour(
        navigator_invoke_recurrence_rule_t *recurrence_rule,
        int minutes_of_hour[], size_t count);

/**
 * @brief Sets the hours of a day of a recurrence rule structure
 *
 * This function sets the @c hours_of_day of a
 * @c #navigator_invoke_recurrence_rule_t structure.
 *
 * Starting from the start date of the recurrence rule, the trigger will be
 * applied at @c hours_of_day per the frequency of the recurrence rule, as
 * allowed by other recurrence conditions, until the count limit or date limit
 * are reached, if applicable.
 *
 * This function doesn't transfer ownership of @c hours_of_day to
 * @c recurrence_rule. @c recurrence_rule keeps a copy of @c hours_of_day. If
 * applicable, @c hours_of_day must be freed to avoid memory leaks. If you
 * change the value of @c hours_of_day calling this function, you must call
 * this function again to use the new value.
 *
 * @param recurrence_rule The @c #navigator_invoke_recurrence_rule_t structure
 *        to modify.
 * @param hours_of_day An array containing the hours to be set, within the
 *        range 0 to 23, inclusive.
 * @param count The size of the @c hours_of_day array.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API int navigator_invoke_recurrence_rule_set_hours_of_day(
        navigator_invoke_recurrence_rule_t *recurrence_rule,
        int hours_of_day[], size_t count);

/**
 * @brief Sets the days of a week of a recurrence rule structure
 *
 * This function sets the @c days_of_week of a
 * @c #navigator_invoke_recurrence_rule_t structure.
 *
 * Starting from the start date of the recurrence rule, the trigger will be
 * applied at @c days_of_week per the frequency of the recurrence rule, as
 * allowed by other recurrence conditions, until the count limit or date limit
 * are reached, if applicable.
 *
 * This function doesn't transfer ownership of @c days_of_week to
 * @c recurrence_rule. @c recurrence_rule keeps a copy of @c days_of_week. If
 * applicable, @c days_of_week must be freed to avoid memory leaks. If you
 * change the value of @c days_of_week calling this function, you must call
 * this function again to use the new value.
 *
 * @param recurrence_rule The @c #navigator_invoke_recurrence_rule_t structure
 *        to modify.
 * @param days_of_week An array containing the days to be set, within the range
 *        1 (Sunday) to 7 (Saturday), inclusive.
 * @param count The size of the @c days_of_week array.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API int navigator_invoke_recurrence_rule_set_days_of_week(
        navigator_invoke_recurrence_rule_t *recurrence_rule,
        int days_of_week[], size_t count);

/**
 * @brief Sets the days of a month of a recurrence rule structure
 *
 * This function sets the @c days_of_month of a
 * @c #navigator_invoke_recurrence_rule_t structure.
 *
 * Starting from the start date of the recurrence rule, the trigger will be
 * applied at @c days_of_month per the frequency of the recurrence rule, as
 * allowed by other recurrence conditions, until the count limit or date limit
 * are reached, if applicable.
 *
 * Using this recurrence condition with
 * @c NAVIGATOR_INVOKE_RECURRENCE_RULE_FREQUENCY_WEEKLY frequency will fail.
 *
 * This function doesn't transfer ownership of @c days_of_month to
 * @c recurrence_rule. @c recurrence_rule keeps a copy of @c days_of_month. If
 * applicable, @c days_of_month must be freed to avoid memory leaks. If you
 * change the value of @c days_of_month calling this function, you must call
 * this function again to use the new value.
 *
 * @param recurrence_rule The @c #navigator_invoke_recurrence_rule_t
 *        structure to modify.
 * @param days_of_month An array containing the days to be set, within the
 *        range 1 to 31, inclusive.
 * @param count The size of the @c days_of_month array.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c
 *         errno set otherwise.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API int navigator_invoke_recurrence_rule_set_days_of_month(
        navigator_invoke_recurrence_rule_t *recurrence_rule,
        int days_of_month[], size_t count);

/**
 * @brief Sets the months of a year of a recurrence rule structure
 *
 * This function sets the @c months_of_year of a
 * @c #navigator_invoke_recurrence_rule_t structure.
 *
 * Starting from the start date of the recurrence rule, the trigger will be
 * applied at @c months_of_year per the frequency of the recurrence rule, as
 * allowed by other recurrence conditions, until the count limit or date limit
 * are reached, if applicable.
 *
 * This function doesn't transfer ownership of @c months_of_year to
 * @c recurrence_rule. @c recurrence_rule keeps a copy of @c months_of_year. If
 * applicable, @c months_of_year must be freed to avoid memory leaks. If you
 * change the value of @c months_of_year calling this function, you must call
 * this function again to use the new value.
 *
 * @param recurrence_rule The @c #navigator_invoke_recurrence_rule_t
 *        structure to modify.
 * @param months_of_year An array containing the months to be set, within the
 *        range 1 to 12, inclusive.
 * @param count The size of the @c months_of_year array.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c
 *         errno set otherwise.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API int navigator_invoke_recurrence_rule_set_months_of_year(
        navigator_invoke_recurrence_rule_t *recurrence_rule,
        int months_of_year[], size_t count);

/**
 * @brief Retrieve the count limit from a @c navigator_invoke_recurrence_rule_t
 *
 * This function retrieves the count limit from the given
 * @c #navigator_invoke_recurrence_rule_t.
 *
 * @param recurrence_rule The @c #navigator_invoke_recurrence_rule_t structure
 *        to query.
 *
 * @return The count limit upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API int navigator_invoke_recurrence_rule_get_count_limit(
        const navigator_invoke_recurrence_rule_t *recurrence_rule);

/**
 * @brief Retrieve the date limit from a @c navigator_invoke_recurrence_rule_t
 *
 * This function retrieves the date limit from the given
 * @c #navigator_invoke_recurrence_rule_t.
 *
 * The recurrence rule structure continues to own the returned
 * @c #navigator_invoke_specific_time_t structure. You must not destroy the
 * returned structure.
 *
 * @param recurrence_rule The @c #navigator_invoke_recurrence_rule_t structure
 *        to query.
 *
 * @return The date limit upon success, or @c NULL with @c errno set otherwise.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API const navigator_invoke_specific_time_t*
        navigator_invoke_recurrence_rule_get_date_limit(
        const navigator_invoke_recurrence_rule_t *recurrence_rule);


/**
 * @brief Retrieve the interval from a @c navigator_invoke_recurrence_rule_t
 *
 * This function retrieves the interval from the given
 * @c #navigator_invoke_recurrence_rule_t.
 *
 * @param recurrence_rule The @c #navigator_invoke_recurrence_rule_t structure
 *        to query.
 *
 * @return The interval upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API int navigator_invoke_recurrence_rule_get_interval(
        const navigator_invoke_recurrence_rule_t *recurrence_rule);

/**
 * @brief Retrieve the start date from a @c navigator_invoke_recurrence_rule_t
 *
 * This function retrieves the start date from the given
 * @c #navigator_invoke_recurrence_rule_t.
 *
 * The recurrence rule structure continues to own the returned
 * @c #navigator_invoke_specific_time_t structure. You must not destroy the
 * returned structure.
 *
 * @param recurrence_rule The @c #navigator_invoke_recurrence_rule_t structure
 *        to query.
 *
 * @return The start date upon success, or @c NULL with @c errno set otherwise.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API const navigator_invoke_specific_time_t*
        navigator_invoke_recurrence_rule_get_start_date(
        const navigator_invoke_recurrence_rule_t *recurrence_rule);

/**
 * @brief Retrieve the minutes of an hour from a
 *       @c navigator_invoke_recurrence_rule_t
 *
 * This function retrieves the minutes of the hour from the given
 * @c #navigator_invoke_recurrence_rule_t.
 *
 * The recurrence rule structure continues to own the returned array. You must
 * not modify or destroy the returned array.
 *
 * @param recurrence_rule The @c #navigator_invoke_recurrence_rule_t structure
 *        to query.
 * @param[out] count The number of items returned upon success, @c BPS_FAILURE
 *             with @c errno set otherwise.
 *
 * @return The minutes of an hour set for the recurrence rule.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API const int * navigator_invoke_recurrence_rule_get_minutes_of_hour(
        const navigator_invoke_recurrence_rule_t *recurrence_rule, int *count);

/**
 * @brief Retrieve the hours in a day that an event should occur
 *
 * This function retrieves the hours of the day from the given
 * @c #navigator_invoke_recurrence_rule_t.
 *
 * The recurrence rule structure continues to own the returned array. You must
 * not modify or destroy the returned array.
 *
 * @param recurrence_rule The @c #navigator_invoke_recurrence_rule_t structure
 *        to query.
 * @param[out] count The number of items returned upon success, @c BPS_FAILURE
 *             with @c errno set otherwise.
 *
 * @return The hours in a day set for the recurrence rule.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API const int * navigator_invoke_recurrence_rule_get_hours_of_day(
        const navigator_invoke_recurrence_rule_t *recurrence_rule, int *count);

/**
 * @brief Retrieve the days of the week that an event should occur
 *
 * This function retrieves @c days_of_week from the given
 * @c #navigator_invoke_recurrence_rule_t.
 *
 * The recurrence rule structure continues to own the returned array. You must
 * not modify or destroy the returned array.
 *
 * @param recurrence_rule The @c #navigator_invoke_recurrence_rule_t structure
 *        to query.
 * @param[out] count The number of items returned upon success, @c BPS_FAILURE
 *             with @c errno set otherwise.
 *
 * @return The days of a week set for the recurrence rule.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API const int * navigator_invoke_recurrence_rule_get_days_of_week(
        const navigator_invoke_recurrence_rule_t *recurrence_rule, int *count);

/**
 * @brief Retrieve the days of the month that an event should occur
 *
 * This function retrieves @c days_of_month from the given
 * @c #navigator_invoke_recurrence_rule_t.
 *
 * The recurrence rule structure continues to own the returned array. You must
 * not modify or destroy the returned array.
 *
 * @param recurrence_rule The @c #navigator_invoke_recurrence_rule_t structure
 *        to query.
 * @param[out] count The number of items returned upon success, @c BPS_FAILURE
 *             with @c errno set otherwise.
 *
 * @return The days of a month set for the recurrence rule.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API const int * navigator_invoke_recurrence_rule_get_days_of_month(
        const navigator_invoke_recurrence_rule_t *recurrence_rule, int *count);

/**
 * @brief Retrieve the months of a year that an event should occur
 *
 * This function retrieves the @c months_of_year from the given
 * @c #navigator_invoke_recurrence_rule_t.
 *
 * The recurrence rule structure continues to own the returned array. You must
 * not modify or destroy the returned array.
 *
 * @param recurrence_rule The @c #navigator_invoke_recurrence_rule_t structure
 *        to query.
 * @param[out] count The number of items returned upon success, @c BPS_FAILURE
 *             with @c errno set otherwise.
 *
 * @return The months of a year set for the recurrence rule.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API const int * navigator_invoke_recurrence_rule_get_months_of_year(
        const navigator_invoke_recurrence_rule_t *recurrence_rule, int *count);

/**
 * @brief Assign given target key to the timer registration
 *
 * The @c navigator_invoke_timer_registration_set_target() function sets the
 * given @c target to the timer registration request. The target key must
 * correspond to the key declared in the application BAR manifest file as
 * 'application.headless' type.
 *
 * @param reg The @c #navigator_invoke_timer_registration_t structure to
 *        modify.
 * @param target The target key to assign.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API int navigator_invoke_timer_registration_set_target(
        navigator_invoke_timer_registration_t *reg, const char* target);

/**
 * @brief Retrieve target key from the timer registration
 *
 * The @c navigator_invoke_timer_registration_get_target() function retrieves
 * target key from the timer registration request.
 *
 * @param reg The @c #navigator_invoke_timer_registration_t structure to query.
 *
 * @return The target key set through @c
 *         #navigator_invoke_timer_registration_set_target().
 *
 * @since BlackBerry 10.3.0
 */
BPS_API const char *navigator_invoke_timer_registration_get_target(
        const navigator_invoke_timer_registration_t *reg);

/**
 * @brief Assign request message ID the timer registration
 *
 * The @c navigator_invoke_timer_registration_set_id() function stores the
 * message ID in the given @c navigator_invoke_timer_registration_t structure.
 * The message ID is a required attribute when there is a need to verify the
 * registration status. It is used for correlating with incoming registration
 * response messages.
 *
 * @param reg The @c #navigator_invoke_timer_registration_t structure to
 *        modify.
 * @param id The registration message ID to assign.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API int navigator_invoke_timer_registration_set_id(
        navigator_invoke_timer_registration_t *reg, const char *id);

/**
 * @brief Retrieve request message ID from timer registration
 *
 * The @c navigator_invoke_timer_registration_get_id() function retrieves the
 * stored message ID from the given @c navigator_invoke_timer_registration_t
 * structure.
 *
 * @param reg The @c #navigator_invoke_timer_registration_t structure to query.
 *
 * @return The registration message ID if it was set, @c NULL otherwise.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API const char* navigator_invoke_timer_registration_get_id(
        const navigator_invoke_timer_registration_t *reg);

/**
 * @brief Set the timer ID of a timer registration request
 *
 * This function sets the timer ID of a
 * @c #navigator_invoke_timer_registration_t.
 * A timer is required to have a timer ID attribute. The timer ID can be used to
 * identify and deregister the timer.
 *
 * @param reg The @c #navigator_invoke_timer_registration_t structure to
 *        modify.
 * @param id The timer ID to assign to the timer.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API int navigator_invoke_timer_registration_set_timer_id(
        navigator_invoke_timer_registration_t *reg, const char *id);

/**
 * @brief Retrieve the timer ID from a timer
 *
 * This function retrieves the timer ID from a
 * @c #navigator_invoke_timer_registration_t object.
 *
 * @param reg The @c #navigator_invoke_timer_registration_t structure to query.
 *
 * @return The registration timer ID if one was set, @c NULL otherwise.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API const char* navigator_invoke_timer_registration_get_timer_id(
        const navigator_invoke_timer_registration_t *reg);

/**
 * @brief Retrieve the trigger type from a timer
 *
 * This function retrieves the trigger type from a
 * @c #navigator_invoke_timer_registration_t structure.
 *
 * @param reg The @c #navigator_invoke_timer_registration_t structure to query.
 *
 * @return The trigger type of the registration timer.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API navigator_invoke_timer_trigger_type_t
        navigator_invoke_timer_registration_get_type(
        const navigator_invoke_timer_registration_t *reg);

/**
 * @brief Set action on the given registration structure
 *
 * The @c navigator_invoke_timer_registration_set_action() function sets the
 * request action in the given @c navigator_invoke_timer_registration_t
 * structure.
 *
 * The action indicates whether the request is to register or unregister the
 * timer trigger.
 *
 * @param reg The @c #navigator_invoke_timer_registration_t structure to
 *        modify.
 * @param action The action to perform during @c
 *        navigator_invoke_timer_registration_send() call.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API int navigator_invoke_timer_registration_set_action(
        navigator_invoke_timer_registration_t *reg,
        navigator_invoke_timer_registration_action_t action);

/**
 * @brief Assign a specific time to a timer registration structure
 *
 * This function sets a specific time value in a
 * @c #navigator_invoke_timer_registration_t structure.
 *
 * This function is used to register a specific time for a headless target.
 * If registration action is set to @c #NAVIGATOR_INVOKE_TIMER_ACTION_UNREGISTER
 * then the specific time will be ignored during the request.
 *
 * A timer registration can have either a specific time or a recurrence rule.
 * Setting a specific time deletes any previously set recurrence rule.
 *
 * This function doesn't transfer ownership of @c specific_time to @c reg. It
 * must be freed to avoid memory leaks. This function sets @c reg using the
 * value of @c specific_time. If you change the value of @c specific_time after
 * calling this function, the updated time will not be used unless you call
 * this function again.
 *
 * @param reg The @c #navigator_invoke_timer_registration_t structure to
 *        modify.
 * @param specific_time The specific time to set.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API int navigator_invoke_timer_registration_set_specific_time(
        navigator_invoke_timer_registration_t *reg,
        const navigator_invoke_specific_time_t* specific_time);

/**
 * @brief Assign a recurrence rule to a timer registration
 *
 * The @c navigator_invoke_timer_registration_set_recurrence_rule() function
 * stores @c rule in the given registration structure. This function is used
 * to register or re-register a recurrent rule for a headless target.
 *
 * If registration action is set to
 * @c #NAVIGATOR_INVOKE_TIMER_ACTION_UNREGISTER, then the rule will be ignored
 * during the request.
 *
 * A timer registration can have either a specific time or a recurrence rule.
 * Setting a recurrence rule deletes any previously set specific time.
 *
 * Valid recurrence rules must have a start date set.
 *
 * This function doesn't transfer ownership of the @c rule to @c reg. It must
 * be freed to avoid memory leaks. Any modifications to the @c rule after the
 * @c navigator_invoke_timer_registration_set_recurrence_rule() function was
 * called will not be reflected in the registration structure. Call this
 * function only after the @c rule has been formed.
 *
 * @param reg The @c #navigator_invoke_timer_registration_t structure to
 *        modify.
 * @param rule A valid @c #navigator_invoke_recurrence_rule_t structure to set.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API int navigator_invoke_timer_registration_set_recurrence_rule(
        navigator_invoke_timer_registration_t *reg,
        const navigator_invoke_recurrence_rule_t *rule);

/**
 * @brief Retrieve the action from a timer registration structure
 *
 * This function retrieves the action from a @c navigator_timer_registration_t
 * structure.
 *
 * @param reg The @c #navigator_invoke_timer_registration_t structure to
 *        query.
 *
 * @return An action from @c #navigator_invoke_timer_registration_t, or
 *         @c #NAVIGATOR_INVOKE_TIMER_ACTION_NOT_SET if no action is set in the
 *         timer registration structure.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API navigator_invoke_timer_registration_action_t
        navigator_invoke_timer_registration_get_action(
        const navigator_invoke_timer_registration_t *reg);

/**
 * @brief Retrieve the specific time from a timer registration structure
 *
 * This function retrieves the specific time from a
 * @c #navigator_invoke_timer_registration_t
 * structure. If no specific time is set in the structure, then @c NULL is
 * returned.
 *
 * The registration structure continues to own the returned @c
 * navigator_invoke_specific_time_t structure. The application must not destroy
 * the returned structure.
 *
 * @param reg The @c #navigator_invoke_timer_registration_t structure to
 *        query.
 *
 * @return A specific time, or @c NULL if one was not set. @c errno will be set
 *         in case of failure.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API const navigator_invoke_specific_time_t*
        navigator_invoke_timer_registration_get_specific_time(
        const navigator_invoke_timer_registration_t *reg);

/**
 * @brief Retrieve the recurrence rule from a timer registration structure
 *
 * This function retrieves @c rule from the given registration structure. If
 * the recurrence rule is not set, then @c NULL is returned. Note that the
 * registration structure continues to own the returned
 * @c #navigator_invoke_recurrence_rule_t structure. You must not destroy the
 * returned structure.
 *
 * @param reg The @c #navigator_invoke_timer_registration_t structure to
 *        query.
 *
 * @return A previously set @c #navigator_invoke_recurrence_rule_t, or @c NULL
 *         if it was not set. @c errno will be set in case of failure.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API const navigator_invoke_recurrence_rule_t*
        navigator_invoke_timer_registration_get_recurrence_rule(
        const navigator_invoke_timer_registration_t *reg);

/**
 * @brief Send the timer registration @c reg to service
 *
 * This function instructs the timer invocation service to install, update, or
 * uninstall the given timer trigger.
 *
 * The @c #navigator_invoke_timer_registration_action_t request attribute
 * indicates whether the application intends to register or de-register the
 * trigger. If the trigger timer for the target is already registered, then the
 * new registration replaces the current one. Timer registration is persistent
 * and will survive device reboots. The recurrent timer is not notified in the
 * current time slot if it matches the recurrence rule; it will be notified
 * starting from the next match only. The target is launched through the invoke
 * framework with the action 'bb.action.system.TIMER_FIRED'.
 *
 * The application should listen for asynchronous responses to the registration
 * request to determine if it was successful. Refer to the
 * @c navigator_event_get_err() function to retrieve error messages from bps
 * event.
 *
 * Currently, timer triggers only support headless targets. The following
 * request attributes are required to register a timer trigger:
 *         - action (either register or unregister)
 *         - non-empty target key
 *         - non-empty timer id
 *         - type (valid timer trigger type)
 *         - valid recurrence rule(for recurrent timer registrations)
 *         - valid specific time (for specific time registrations)
 *
 * Currently, you can register a maximum of 5 timers, of which only 1 can be a
 * recurrent timer. If you attempt to register a specific timer for a time that
 * occurs within 6 minutes of a previously registered timer, the registration
 * will fail.
 * 
 * Specific timers are automatically deregistered when they expire. You can
 * deregister them prior to expiration by calling
 * @c navigator_invoke_timer_set_action with action()
 * @c NAVIGATOR_INVOKE_TIMER_ACTION_UNREGISTER. You must deregister
 * recurrence timers.
 *
 * @param reg The @c #navigator_invoke_timer_registration_t request to send.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API int navigator_invoke_timer_registration_send(
        const navigator_invoke_timer_registration_t *reg);

/**
 * @brief Retrieve request action from BPS event structure
 *
 * The @c navigator_invoke_timer_registration_get_action() function retrieves
 * an action from a given BPS event structure.
 *
 * Use this function to retrieve the action from a service response after
 * firing a request through @c navigator_invoke_timer_registration_send().
 *
 * The request is not sent if the action is not specified and there will be no
 * corresponding BPS event in such case.
 *
 * @param event The @c #bps_event_t structure to query.
 *
 * @return The action retrieved from the BPS event.
 *
 * @since BlackBerry 10.3.0
 */
BPS_API navigator_invoke_timer_registration_action_t
        navigator_invoke_timer_registration_event_get_action(bps_event_t *event);

__END_DECLS

#endif // include guard
