/*
 * BlackBerry Limited, Copyright (C) 2013
 * BlackBerry Limited. All rights reserved.
 */

/**
 * @file push_service.h
 *
 * @brief Manages all interactions with the Push Proxy Gateway (PPG)
 *
 * @since BlackBerry 10.2.0
 */

/**
 * @mainpage Push Service Library
 *
 * @section section1 Overview
 *
 * The Push Service allows a push-enabled application to send requests to the
 * Push Proxy Gateway (PPG). The PPG provides a set of services that enables
 * interaction between content providers and push-enabled applications.
 *
 * The Push Service supports both sending requests to and receiving responses
 * from the PPG. Applications that receive response messages while they are
 * running are notified via the @c push_callback_t function.
 *
 * The following commands are supported by the Push Service:
 * - @c push_service_create_session()
 * - @c push_service_create_channel()
 * - @c push_service_destroy_channel()
 * - @c push_service_register_to_launch()
 * - @c push_service_unregister_from_launch()
 *
 * The application can send an application-level acknowledgment that indicates
 * whether the application accepted or rejected the pushed content (@c
 * push_service_accept_push() or @c push_service_reject_push()).
 *
 * The following steps show the general flow when you use the Push Service:  
 * -# Initialize BlackBerry Platform Services (BPS) (for more information about
 *    BPS, see bps/bps.h)
 * -# Establish Interaction with the Push Notification Service (PNS) Agent. The
 *    PNS Agent is a software component that maintains a connection with the
 *    PPG, and forwards push notifications that it receives from the PPG to the
 *    appropriate instance of the push-enabled application.
 * -# Request navigator events and listen for events
 * -# Receive Push messages
 * -# Shutdown your application
 * -# Shutdown BPS
 *
 * The code below is a sample @c main() function that demonstrates this flow. To
 * see push-specific code snippets and explanations, go to the section mentioned
 * in the comments in the code. For example, where it says:
 * @code
 * // ********************************
 * // See section Establish Interaction with the PNS Agent
 * // ********************************
 * @endcode
 * Go to the section below titled "Establish interaction with the PNS Agent" to
 * see the code snippets and explanations.
 *
 * @code
 * int main(int argc, char *argv[])
 * {
 *   // Initialize BPS
 *   if (bps_initialize() == BPS_FAILURE){
 *     printf("Failed to initialize bps\n");
 *     return EXIT_FAILURE;
 *   }
 *
 *   // ********************************
 *   // See section Establish Interaction with the PNS Agent
 *   // ********************************
 *
 *   // To keep things simple just show a blue screen
 *   show_screen(0xff0000ff);
 *
 *   // Signal BPS library that navigator and screen events will be 
 *   // requested
 *   screen_request_events(screen_ctx);
 *   navigator_request_events(0);
 *
 *   while (!shutdown) {
 *     // Handle user input
 *     handle_event();
 *   }
 *
 *   // ********************************
 *   // See section Application shutdown
 *   // ********************************
 *
 *   // Shutdown BPS
 *   screen_stop_events(screen_ctx);
 *   bps_shutdown();
 *   screen_destroy_window(screen_win);
 *   screen_destroy_context(screen_ctx);
 *
 *   printf("Main Loop exit.\n");
 *   return EXIT_SUCCESS;
 * }
 *
 * void handle_event()
 * {
 *   bps_event_t *event = NULL;
 *   int rc = bps_get_event(&event, -1);
 *
 *   if (rc != BPS_SUCCESS) {
 *     ERR("BPS get event failed.");
 *   }
 *   else if (event) {
 *     int domain = bps_event_get_domain(event);
 *     printf("Got domain[%d]\n", domain);
 *     if (domain == navigator_get_domain()) {
 *       printf("Received Navigator event\n");
 *
 *       // ********************************
 *       // See section Receiving a Push Message
 *       // ********************************
 *       handle_navigator_event(event);
 *     }
 *   }
 * }
 * @endcode
 *
 * @section section2 Establish interaction with the PNS Agent
 *
 * Create a @c #push_service_t structure to invoke the APIs from the Push
 * Service library. Obtain the Push Service file descriptor using @c
 * push_service_get_fd(), and add it to the list of file descriptors monitored
 * by BPS using @c bps_add_fd(). The I/O handler is called by BPS when activity
 * is detected on the Push Service file descriptor.
 *
 * @code
 * int main(int argc, char *argv[])
 * {
 *   // .. omitted for brevity
 *
 *   push_service_t *ps = NULL;
 *   int rc = push_service_initialize(&ps);
 *   if (rc == PUSH_FAILURE || (ps == NULL)) {
 *     printf("start_push_service: failed init push_service  
 *             errno[%d] error[%s]\n", errno,
 *             strerror(errno));
 *     return EXIT_FAILURE;
 *   }
 *
 *   int push_pps_fd = push_service_get_fd(ps);
 *   if (push_pps_fd == PUSH_INVALID_PPS_FILE_DESCRIPTOR) {
 *     printf("invalid push pps file descriptor\n");
 *     return EXIT_FAILURE;
 *   }
 *
 *   // Add the Push Service file descriptor to a list of 
 *   // descriptors monitored by BPS.
 *   if (bps_add_fd(pushPpsFd, BPS_IO_INPUT, &push_io_handler, ps)  
 *                == BPS_FAILURE) {
 *     printf("Failed to add push file descriptor %d to bps\n", 
 *            pushPpsFd);
 *     return EXIT_FAILURE;
 *   }
 *
 *   // .. omitted for brevity
 * }
 *
 * // Push io handler
 * int push_io_handler(int fd, int io_events, void* opaque) {
 * int rc = BPS_FAILURE;
 * push_service_t* ps = (push_service_t*)opaque;
 *
 *    if (ps != NULL) {
 *      int old_fd = push_service_get_fd();
 *      printf("calling push service to process the incoming 
 *              PPS message\n");
 *      if (push_service_process_msg(ps) == PUSH_SUCCESS) {
 *        int new_fd = push_service_get_fd();
 *
 *        // Push connection has been closed.
 *        // Need to remove the Push Service file descriptor from 
 *                              // the list monitored by BPS.
 *        if (new_fd == PUSH_INVALID_PPS_FILE_DESCRIPTOR) {
 *          if (bps_remove_fd(old_fd) == BPS_FAILURE) {
 *            printf("Failed to remove PPS file descriptor\n");
 *          }
 *        }
 *        rc = BPS_SUCCESS;
 *      }
 *    }
 *
 *    return rc;
 *  }
 *
 * @endcode
 *
 * A @c #push_service_t structure interacts with the PNS Agent through a
 * session. You need to pass the Provider Application ID and the Invoke Target
 * Key to create the session. The Application ID is the unique identifier of the
 * client application that you received from BlackBerry when you registered to
 * use the Push Service. The Target Key identifies the client application as the
 * target of push content, and it's a value that you generate.
 * @code
 * rc = push_service_set_provider_application_id(ps, provider_app_id);
 * if (rc == PUSH_FAILURE) {
 *   printf("push_service_set_provider_application_id: errno[%d]"
 *          "error[%s]\n", errno, strerror(errno));
 *   return false;
 * }
 *
 * rc = push_service_set_target_key(ps, target_key);
 * if (rc == PUSH_FAILURE) {
 *   printf("push_service_set_target_key: errno[%d] error[%s]\n",
 *           errno, strerror(errno));
 *   return false;
 * }
 *
 * rc = push_service_create_session(ps, on_create_session_complete);
 * if (rc == PUSH_FAILURE) {
 *   printf("push_service_create_session: errno[%d] error[%s]\n",
 *           errno, strerror(errno));
 *   return false;
 * }
 * @endcode
 *
 * Calls to create sessions are asynchronous. The provided @c
 * on_create_session_complete() callback function will be invoked when the @c
 * push_service_create_session() request is complete.
 *
 * @code
 * void on_create_session_complete(push_service_t* ps, int status_code) {
 *   printf("create_session_complete called status_code[%d]", 
 *           status_code);
 *
 *   if (status_code == PUSH_NO_ERR) {
 *     rc = push_service_set_ppg_url(ps, ppg_url);
 *     if (rc == PUSH_SUCCESS) {
 *       rc = push_service_create_channel(ps, 
 *              on_create_channel_complete, 
 *              create_channel_on_push_transport_ready);
 *     }
 *     else {
 *       printf("push_service_set_ppg_url: errno[%d] error[%s]",  
 *               errno, strerror(errno));
 *     }
 *   }
 * }
 * @endcode
 *
 * @section section3 Create a channel with the PPG
 *
 * You need to create a channel with the PPG so that your application and the
 * device it runs on are enlisted to receive content whenever the PPG sends
 * content. The request to create a channel is sent through the PNS Agent. You
 * need the PPG URL to invoke the call to create a channel.
 *
 * The callback functions cannot be @c NULL. The @c
 * create_channel_on_push_transport_ready() callback function is used to handle
 * the scenario where the @c push_service_create_channel() request failed with a
 * @c #PUSH_ERR_TRANSPORT_FAILURE (10103) or @c #PUSH_ERR_PPG_SERVER_ERROR
 * (10110) status code.
 *
 * @code
 * void on_create_channel_complete(push_service_t* ps, 
 *      int status_code) {
 *   printf("on_create_channel_complete called statusCode[%d]", 
 *          status_code);
 * }
 *
 * void create_channel_on_push_transport_ready(push_service_t* ps, int 
 *        status_code) {
 *   push_service_create_channel(ps, 
 *        on_create_channel_complete, 
 *        create_channel_on_push_transport_ready);
 * }
 *
 * // ...
 *
 * rc = push_service_set_ppg_url(ps, ppg_url);
 *   if (rc == PUSH_SUCCESS) {
 *     rc = push_service_create_channel(ps, on_create_channel_complete, 
 *                create_channel_on_push_transport_ready);
 * }
 * else {
 *   printf("push_service_set_ppg_url: errno[%d] error[%s]",
 *          errno, strerror(errno));
 * }
 *
 * @endcode
 *
 * @section section4 Application shutdown
 * 
 * On application shutdown, you should explicitly deallocate any memory
 * allocated for a given @c #push_service_t structure using @c
 * push_service_cleanup(). You also need to remove the Push Service file
 * descriptor from the list monitored by BPS using @c bps_remove_fd().
 *
 * @code
 * rc = push_service_cleanup(ps);
 * if (rc == PUSH_FAILURE) {
 *   printf("push_service_cleanup: errno[%d] error[%s]\n",
 *          errno, strerror(errno));
 * }
 *
 * if (bps_remove_fd(pushPpsFd) == BPS_FAILURE){
 *   printf("Failed to remove PPS file descriptor\n");
 * }
 * @endcode
 *
 * @section section5 Receiving a Push Message
 * 
 * To receive a push message you need to listen for a navigator invoke event in
 * your main event loop. The action value of this event must be @c
 * #PUSH_INVOCATION_ACTION. If these criteria are met, then you can extract the
 * invoke data into a @c #push_payload_t structure using @c
 * push_payload_create() and @c push_payload_set_payload(). Before using the 
 * structure, check that the data in the structure is valid using @c
 * push_payload_is_valid(). After you finish using the @c #push_payload_t
 * structure, you should explicitly deallocate any memory given to @c
 * #push_payload_t using @c push_payload_destroy().
 *
 * @code
 * void handle_navigator_event(bps_event_t *event) {
 *   int event_type = bps_event_get_code(event);
 *   printf("received event type [%d]\n", event_type);
 *
 *   switch (event_type) {
 *   case NAVIGATOR_EXIT:
 *     printf("NAVIGATOR Exit event\n");
 *     shutdown = true;
 *     break;
 *   case NAVIGATOR_INVOKE_TARGET: {
 *     // Our handler was invoked
 *     const navigator_invoke_invocation_t *invoke = 
 *                     navigator_invoke_event_get_invocation(event);
 *     if(invoke) {
 *
 *       const char *action =
 *             navigator_invoke_invocation_get_action(invoke);
 *       printf("Got invoke: action='%s'\n", action ? action : "NULL");
 *
 *       if (strcmp(action,PUSH_INVOCATION_ACTION) == 0){
 *
 *         // get the jsonData from the invoke object and
 *         // put it into a push_payload_t struct
 *         const unsigned char* raw_invoke_data =
 *               (unsigned char*) 
 *                navigator_invoke_invocation_get_data(invoke);
 *         int invoke_data_len = 
 *               navigator_invoke_invocation_get_data_length(invoke);
 *
 *         printf("Creating push_payload_t from raw_invoke_data\n");
 *         push_payload_t* push_payload;
 *         if(push_payload_create(&push_payload) == PUSH_FAILURE){
 *           printf("failed to create push_payload. errno[%d]\n", 
 *                  errno);
 *           return FAILURE;
 *         }
 *
 *         if (push_payload_set_payload(push_payload,
 *                                      raw_invoke_data,
 *                                      invoke_data_len) ==
 *               PUSH_SUCCESS && push_payload_is_valid(push_payload)){
 *           printf("push_payload_t is valid\n");
 *           process_push_payload(push_payload);
 *         } else {
 *           printf("push_payload_t is NOT valid\n");
 *         }
 *
 *         // cleanup
 *         push_payload_destroy(push_payload);
 *       }
 *     }
 *     break;
 *   }
 *
 *   default:
 *     break;
 *   }
 * }
 *
 * @endcode
 *
 * @section section6 Processing a Push Payload Structure
 *
 * Here is an example of how to retrieve the data from a
 * @c #push_payload_t structure, and how to loop through all of the headers.
 *
 * @code
 *
 * void process_push_payload(const push_payload_t* payload)
 * {
 *   const unsigned char* data = push_payload_get_data(payload);
 *   size_t data_length = push_payload_get_data_length(payload);
 *
 *   printf("data length : [%d]\n", data_length);
 *
 *   size_t headers_length = push_payload_get_headers_length(payload);
 *
 *   for(int i=0; i <headers_length;i++){
 *
 *     const push_header_t* header =
 *                          push_payload_get_header(payload,i);
 *
 *     if (header){
 *       const char* header_name = push_header_get_name(header);
 *       const char* header_value = push_header_get_value(header);
 *
 *       if (header_name){
 *         printf("Header name: [%s]\n", header_name);
 *       }
 *
 *       if (header_value){
 *         printf("Header value: [%s]\n", header_value);
 *       }
 *     }
 *   }
 * }
 * @endcode
 *
 * @section section7 Detecting a changed SIM card
 *
 * When the SIM card is changed on a device, the PNS Agent automatically
 * destroys the channel. You can implement a callback function to handle the
 * SIM change.
 *
 * @code
 * push_service_set_sim_change_callback(on_sim_change);
 * @endcode
 *
 *  A call to @c push_service_create_channel() is recommended.
 *
 * @code
 * void on_sim_change(push_service_t* ps) {
 *   push_service_create_channel(ps, on_create_channel_complete, 
 *                create_channel_on_push_transport_ready);
 * }
 * @endcode
 *
 *
 * @section section8 Detecting when the PNS Agent connection is closed
 *
 * If the connection to the PNS Agent has been closed, the application or
 * service needs to re-establish the connection with the PNS Agent by calling
 * @c push_service_get_fd() periodically until @c push_service_get_fd() returns
 * a valid file descriptor. You can implement a callback function to handle
 * when the connection closes.
 *
 * @code
 * push_service_set_connection_close_callback(ps, on_connection_closed);
 * @endcode
 *
 * Calling @c push_service_get_fd() in a backoff timer is recommended.
 *
 * @code
 * void on_connection_closed(push_service_t* ps) {
 *   // Start backoff timer which periodically calls  
 *   // push_service_get_fd() until push_service_get_fd() returns a 
 *   // valid file descriptor.
 * }
 * @endcode
 *
 */

#ifndef _PUSH_SERVICE_H_INCLUDED
#define _PUSH_SERVICE_H_INCLUDED

#include <sys/platform.h>
#include <push/push_errno.h>

__BEGIN_DECLS

/**
 * Invalid file descriptor.
 *
 * @since BlackBerry 10.2.0
 */
#define PUSH_INVALID_PPS_FILE_DESCRIPTOR        (-1)

/**
 * @brief The opaque push argument type
 *
 * This type defines the @c #push_service_t structure used by several functions
 * in the Push Service. Use this to create and control push requests. The @c
 * #push_service_t structure is opaque, but includes the following members:
 *  - @b providerApplicationId: The unique identifier of the client application
 *       (@c push_service_set_provider_application_id()).
 *  - @b TargetKey: The target to which the push data is sent (@c
 *       push_service_set_target_key()).
 *  - @b pushProxyGatewayUrl: The URL of the Push Proxy Gateway(PPG) (@c
 *       push_service_get_ppg_url()).
 *  - @b token: The token received from the Push Server after successfully
 *       creating the push channel. This token should be communicated to the
 *       Push Initiator (@c push_service_get_token()).
 *  - @b ppsFd: The Push Service file descriptor (@c push_service_get_fd()).
 *
 * @since BlackBerry 10.2.0
 */
typedef struct push_service_t push_service_t;

/**
 * The callback function that gets passed in to @c
 * push_service_create_session(), @c push_service_register_to_launch(), and @c
 * push_service_unregister_from_launch()
 *
 * @since BlackBerry 10.2.0
 */
typedef void (*push_callback_t)(push_service_t* ps, int status_code);

/**
 * The callback function that gets passed in to @c
 * push_service_create_channel(), and @c push_service_destroy_channel()
 *
 * @since BlackBerry 10.2.0
 */
typedef void (*push_transport_ready_callback_t)(push_service_t* ps, int status_code);

/**
 * The callback that is invoked when the SIM card is changed. When this happens,
 * the push is discarded, and a call to @c push_service_create_channel() is
 * recommended.
 *
 * Call @c push_service_set_sim_change_callback() to register this callback.
 *
 * @since BlackBerry 10.2.0
 */
typedef void (*push_sim_change_callback_t)(push_service_t* ps);

/**
 * The callback that is invoked when the connection to the PNS Agent has been
 * closed. When this happens, the application or service needs to re-establish
 * the connection with the PNS Agent by calling @c push_service_get_fd()
 * periodically until @c push_service_get_fd() returns a valid file descriptor.
 *
 * Call @c push_service_set_connection_close_callback() to register this
 * callback.
 *
 * @since BlackBerry 10.2.0
 */
typedef void (*push_connection_close_callback_t)(push_service_t* ps);

/**
 * @brief Initializes the push_service_t structure
 *
 * This function (or @c push_service_initialize()) must be called once before
 * any other calls are made. The ownership of the return value stays with the
 * library. To deallocate this memory, use @c push_service_cleanup().
 *
 * @param ps The @c #push_service_t structure.
 *
 * @return @c #PUSH_SUCCESS upon success, @c #PUSH_FAILURE with @c errno set
 *            otherwise.
 *
 * @since BlackBerry 10.2.0
 */
int push_service_initialize(push_service_t** ps);

/**
 * @brief Releases any resources used by the push_service_t structure
 *
 * @param ps The @c #push_service_t structure.
 *
 * @since BlackBerry 10.2.0
 */
int push_service_cleanup(push_service_t* ps);

/**
 * @brief Changes the provider application ID
 *
 * @param ps A pointer to the @c #push_service_t structure whose @c
 *           provider_application_id you want to set.
 *
 * @param provider_application_id The provider application ID.
 *
 * @return @c #PUSH_SUCCESS upon success, @c #PUSH_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.2.0
 */
int push_service_set_provider_application_id(
        push_service_t *ps, const char* provider_application_id);

/**
 * @brief Changes the invocation target key
 *
 * @param ps A pointer to the @c #push_service_t structure whose @c target_key
 *           you want to set.
 *
 * @param target_key The target key identifies the client application as the
 *                   target of push content.
 *
 * @return @c #PUSH_SUCCESS upon success, @c #PUSH_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.2.0
 */
int push_service_set_target_key(
        push_service_t *ps, const char* target_key);
/**
 * @brief Changes the URL of the Push Proxy Gateway (PPG)
 *
 * @param ps A pointer to the @c #push_service_t structure whose @c
 *           push_proxy_gateway_url you want to set.
 *
 * @param push_proxy_gateway_url The URL of the Push Proxy Gateway.
 *
 * @return @c #PUSH_SUCCESS upon success, @c #PUSH_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.2.0
 */
int push_service_set_ppg_url(push_service_t *ps, const char* push_proxy_gateway_url);

/**
 * @brief Call this function to register a connection closed callback
 *
 * When the connection to the PNS Agent is lost, the application or service
 * needs to re-establish the connection with the PNS Agent by calling @c
 * push_service_get_fd() periodically until @c push_service_get_fd() returns a
 * valid file descriptor.
 *
 * @param ps A pointer to the @c #push_service_t structure whose connection
 *           close callback you want to set.
 *
 * @param cb_func The callback that will be called when the connection to the 
 *                PNS Agent is closed.
 *
 * @return @c #PUSH_SUCCESS upon success, @c #PUSH_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.2.0
 */
int push_service_set_connection_close_callback(push_service_t *ps, push_connection_close_callback_t cb_func);

/**
 * @brief Call this function to register a SIM change callback
 *
 * When a SIM change happens, the PPG stops delivering push messages. To
 * continue receiving push data, you must call @c push_service_create_channel()
 * again.
 *
 * @param cb_func The callback that will be called when a sim change occurs.
 *
 * @return @c #PUSH_SUCCESS upon success, @c #PUSH_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.2.0
 */
int push_service_set_sim_change_callback(push_sim_change_callback_t cb_func);

/**
 * @brief Gets the provider application ID associated with this push_service_t
 *        structure
 *
 * @param ps A pointer to the @c #push_service_t structure whose @c
 *           providerApplicationId you want to retrieve.
 *
 * @return The provider application ID, or @c NULL if one is not present.
 *
 * @since BlackBerry 10.2.0
 */
const char* push_service_get_provider_application_id(push_service_t *ps);

/**
 * @brief Gets the target key associated with this push_service_t structure
 *
 * @param ps A pointer to the @c #push_service_t structure whose @c targetKey
 *           you want to retrieve.
 *
 * @return The target key, or @c NULL if one is not present.
 *
 * @since BlackBerry 10.2.0
 */
const char* push_service_get_target_key(push_service_t *ps);

/**
 * @brief Gets the Push Proxy Gateway URL associated with this push_service_t
 *        structure
 *
 * @param ps A pointer to the @c #push_service_t structure whose @c
 *           pushProxyGatewayUrl you want to retrieve.
 *
 * @return The Push Proxy Gateway URL, or @c NULL if one is not present.
 *
 * @since BlackBerry 10.2.0
 */
const char* push_service_get_ppg_url(push_service_t *ps);

/**
 * @brief Gets the token received from the PPG after successfully creating the
 *        push channel
 *
 * @param ps A pointer to the @c #push_service_t structure whose @c token you
 *           want to retrieve.
 *
 * @return The Push Proxy Gateway URL, or @c NULL if one is not present.
 *
 * @since BlackBerry 10.2.0
 */
const char* push_service_get_token(push_service_t *ps);

/**
 * @brief Gets the Push Service file descriptor associated with this
 *        push_service_t structure
 *
 * @param ps A pointer to the @c #push_service_t structure whose @c ppsFd you
 *           want to retrieve.
 *
 * @return Push Service file descriptor.
 *
 * @since BlackBerry 10.2.0
 */
int push_service_get_fd(push_service_t *ps);

/**
 * @brief Process the incoming PPS message
 *
 * @param ps A pointer to the @c #push_service_t structure contains the @c
 *           ppsFd used to retrieve the push callback message.
 *
 * @return @c #PUSH_SUCCESS upon success, @c #PUSH_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.2.0
 */
int push_service_process_msg(push_service_t *ps);

/**
 * @brief Creates a session between the application and the PNS Agent
 *
 * Creating a session sets up inter-process communication between the
 * application and the PNS Agent. This must be called every time the application
 * is launched.
 *
 * @param ps A pointer to the @c #push_service_t structure used to create the
 *           request.
 *
 * @param cb_func Callback in response to @c push_service_create_session(). This
 *                callback contains a @c status_code parameter to specify the
 *                failure condition. This callback function cannot be @c NULL.
 *
 * @return @c #PUSH_SUCCESS upon success, @c #PUSH_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.2.0
 */
int push_service_create_session(push_service_t *ps, push_callback_t cb_func);

/**
 * @brief Creates a channel for receiving push messages from the Push Initiator
 *
 * Once the channel is successfully established, the application does not have
 * to call it again. The Push Service maintains the channel.
 *
 * @param ps A pointer to the @c #push_service_t structure used to create the
 *           request.
 *
 * @param cb_func Callback in response to @c push_service_create_channel(). This
 *                callback contains a @c status_code parameter to specify the
 *                failure condition. This callback function cannot be @c NULL.
 *
 * @param transport_ready_cb_func Callback in response to @c
 *                                push_service_create_channel(). Sent when a
 *                                previous @c push_service_create_channel()
 *                                request failed with a @c
 *                                #PUSH_ERR_TRANSPORT_FAILURE (10103) or
 *                                #PUSH_ERR_PPG_SERVER_ERROR (10110) status
 *                                code. This callback function cannot be @c
 *                                NULL.
 *
 * @return @c #PUSH_SUCCESS upon success, @c #PUSH_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.2.0
 */
int push_service_create_channel(push_service_t* ps, push_callback_t cb_func,
    push_transport_ready_callback_t transport_ready_cb_func);

/**
 * @brief Destroys the channel when the application no longer needs it
 *
 * @param ps A pointer to the @c #push_service_t structure used to create the
 *           request.
 *
 * @param cb_func Callback in response to @c push_service_destroy_channel().
 *                This callback contains a @c status_code parameter to specify
 *                the failure condition. This callback function cannot be @c
 *                NULL.
 *
 * @param transport_ready_cb_func Callback in response to @c
 *        push_service_destroy_channel(). Sent when a previous @c
 *        push_service_destroy_channel() request failed with a @c
 *        #PUSH_ERR_TRANSPORT_FAILURE (10103) or #PUSH_ERR_PPG_SERVER_ERROR
 *        (10110) status code. This callback function cannot be @c NULL.
 *
 * @return @c #PUSH_SUCCESS upon success, @c #PUSH_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.2.0
 */
int push_service_destroy_channel(push_service_t* ps, push_callback_t cb_func,
    push_transport_ready_callback_t transport_ready_cb_func);

/**
 * @brief Call this API if you want to launch your app in background 
 *        when a push arrives.
 *
 * @param ps A pointer to the @c #push_service_t structure used to create the
 *           request.
 *
 * @param cb_func Callback in response to @c push_service_register_to_launch().
 *                This callback contains a @c status_code parameter to specify
 *                the failure condition. This callback function cannot be @c
 *                NULL.
 *
 * @return @c #PUSH_SUCCESS upon success, @c #PUSH_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.2.0
 */
int push_service_register_to_launch(push_service_t *ps, push_callback_t cb_func);

/**
 * @brief Cancels a previous push_service_register_to_launch() request
 *
 * @param ps A pointer to the @c #push_service_t structure used to create the
 *           request.
 *
 * @param cb_func Callback in response to @c
 *                push_service_unregister_from_launch(). This callback contains
 *                a @c status_code parameter to specify the failure condition.
 *                This callback function cannot be @c NULL.
 *
 * @return @c #PUSH_SUCCESS upon success, @c #PUSH_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.2.0
 */
int push_service_unregister_from_launch(push_service_t *ps, push_callback_t cb_func);

/**
 * @brief Call this API if you want your app to accept a push from the server.
 *
 * This call is required when the push data indicates that it requires
 * application-level acknowledgment for the push.
 *
 * See @c push_payload_is_ack_required().
 *
 * @param ps A pointer to the @c #push_service_t structure used to create the
 *           request.
 *
 * @param payload_id Unique identifier of the push notification which is stored
 *                   in the @c #push_payload_t structure.
 *
 * @return @c #PUSH_SUCCESS upon success, @c #PUSH_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.2.0
 */
int push_service_accept_push(push_service_t *ps, const char* payload_id);

/**
 * @brief Call this API if you want your app to reject a push from the server.
 *
 * This call is required when the push data indicates that it requires
 * application-level acknowledgment for the push.
 *
 * See @c push_payload_is_ack_required().
 *
 * @param ps A pointer to the @c #push_service_t structure used to create the
 *           request.
 *
 * @param payload_id The unique identifier of the push notification which is
 *                   stored in the @c #push_payload_t structure.
 *
 * @return @c #PUSH_SUCCESS upon success, @c #PUSH_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.2.0
 */
int push_service_reject_push(push_service_t *ps, const char* payload_id);

__END_DECLS

#endif /* _PUSH_SERVICE_H_INCLUDED */
