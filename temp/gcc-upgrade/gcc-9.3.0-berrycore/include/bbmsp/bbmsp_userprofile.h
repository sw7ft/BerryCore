/**
 * @file bbmsp_userprofile.h
 *
 * @brief Functions and structures to access a user's BlackBerry Messenger
 * profile information.
 * @details This file declares functions and structures that are used to access
 * the user's BBM profile.
 * You can retrieve or change the user's display name, display picture,
 * status, and personal message.
 *
 * @copyright Copyright (C) Research In Motion Limited 2012. All rights
 * reserved.
 */

#ifndef BBMSP_USERPROFILE_H_
#define BBMSP_USERPROFILE_H_

#include "bbmsp.h"
#include "bbmsp_presence.h"
#include "bbmsp_util.h"

#include <sys/platform.h>

#include <stdio.h>

__BEGIN_DECLS

/**
 * The maximum length of a user's display name, including one extra character
 * for the null terminating character. This can be used in
 * @c bbmsp_profile_get_display_name().
 *
 * @since BlackBerry 10.0.0
 */
#define BBMSP_PROFILE_DISPLAY_NAME_MAX (257)

/**
 * The maximum length of a user's personal message, including one extra
 * character for the null terminating character. This can be used in
 * @c bbmsp_profile_get_personal_message().
 *
 * @since BlackBerry 10.0.0
 */
#define BBMSP_PROFILE_PERSONAL_MSG_MAX (161)

/**
 * The maximum length of a contact's status message, including one extra
 * character for the null terminating character. This can be used in
 * @c bbmsp_profile_get_status_message().
 *
 * @since BlackBerry 10.0.0
 */
#define BBMSP_PROFILE_STATUS_MSG_MAX (257)

/**
 * The maximum length of a user's @c ppid, including one extra character
 * for the null terminating character. This can be used in
 * @c bbmsp_profile_get_ppid().
 *
 * @since BlackBerry 10.0.0
 */
#define BBMSP_PROFILE_PPID_MAX (257)

/**
 * The maximum length of a user's @c handle, including one extra character
 * for the null terminating character. This can be used in
 * @c bbmsp_profile_get_handle().
 *
 * @since BlackBerry 10.0.0
 */
#define BBMSP_PROFILE_HANDLE_MAX (257)

/**
 * The maximum size of a user's display picture in bytes. This can be used in
 * @c bbmsp_set_user_profile_display_picture().
 *
 * @since BlackBerry 10.0.0
 */
#define BBMSP_PROFILE_DISPLAY_PICTURE_MAX (32768)

/**
 * @brief The user's BBM profile.
 *
 * @details A user's BBM profile contains a display name, personal message,
 * status, status message, and BBM Social Platform version.
 *
 * @since BlackBerry 10.0.0
 */
typedef struct bbmsp_profile_t bbmsp_profile_t;

/**
 * @brief Retrieve the user's BBM profile information and
 * user's BBM display picture.
 *
 * @details You can retrieve the user's profile information, for example,
 * display name, status, personal message and display picture.
 *
 * @param profile A pointer to the user's BBM profile.
 *
 * @return @c BBMSP_SUCCESS if successful, @c BBMSP_FAILURE otherwise.
 * @see bbmsp_profile_t, BBMSP_SUCCESS, BBMSP_FAILURE
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t bbmsp_get_user_profile(bbmsp_profile_t* profile);

/**
 * @brief Send a request to set the user's BBM status message.
 *
 * @details A user's BBM status can be either available or busy.
 *
 * @param status The user's BBM status.
 * @param custom_status_message A pointer to the custom status message array.
 *
 * @return @c BBMSP_ASYNC if successful, @c BBMSP_FAILURE
 * otherwise.
 * @see bbmsp_presence_status_t, BBMSP_ASYNC, BBMSP_FAILURE
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t
bbmsp_set_user_profile_status(bbmsp_presence_status_t status,
                              const char* custom_status_message);

/**
 * @brief Send a request to set the user's BBM personal message.
 * @details Sets the user's BBM personal message. A dialog displays to allow the
 * user to accept or reject the change. A personal message is limited to 160
 * characters; anything longer is truncated. If null is passed in, the personal
 * message is cleared.
 *
 * @param personal_message A pointer to the personal message array, encoded as
 * UTF-8.
 *
 * @return @c BBMSP_ASYNC if successful in sending the request,
 * @c BBMSP_FAILURE otherwise.
 * @see BBMSP_ASYNC, BBMSP_FAILURE
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t
bbmsp_set_user_profile_personal_message(const char* personal_message);

/**
 * @brief Send a request to set the user's BBM display picture.
 *
 * @details A dialog displays to allow the user to accept or reject the change
 * to the user's BBM display picture. The display picture is limited to 32kB of
 * data; an attempt to set a display picture that exceeds this limit will fail
 * and will not display the dialog.
 *
 * @param image A pointer to the display picture.
 *
 * @return @c BBMSP_ASYNC if successful in sending the request,
 * @c BBMSP_FAILURE otherwise.
 * @see BBMSP_ASYNC, BBMSP_FAILURE, BBMSP_PROFILE_DISPLAY_PICTURE_MAX
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t
bbmsp_set_user_profile_display_picture(bbmsp_image_t* image);

/**
 * @brief Create a user profile.
 *
 * @details Creates a new user profile. When the user profile is no longer
 * required, call @c bbmsp_profile_destroy() to free up the associated memory.
 *
 * @param profile An updated pointer to the new profile.
 *
 * @return @c BBMSP_SUCCESS if successful, @c BBMSP_FAILURE otherwise.
 * @see bbmsp_profile_destroy(), BBMSP_SUCCESS, BBMSP_FAILURE
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t bbmsp_profile_create(bbmsp_profile_t** profile);

/**
 * @brief Destroy a user profile.
 * @details Destroys a user profile and frees up the associated memory.
 * @param profile A pointer to the profile to destroy.
 *
 * @return @c BBMSP_SUCCESS if successful, @c BBMSP_FAILURE otherwise.
 * @see BBMSP_SUCCESS, BBMSP_FAILURE
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t bbmsp_profile_destroy(bbmsp_profile_t** profile);

/**
 * @brief Retrieve the user's BBM display name.
 *
 * @param profile A pointer to the user's BBM profile.
 * @param display_name A pointer to the array that contains the user's display
 * name, encoded as UTF-8.
 * @param buffer_size The size of the @c display_name buffer array.
 *
 * @return @c BBMSP_SUCCESS if successful, @c BBMSP_FAILURE otherwise.
 * @see BBMSP_SUCCESS, BBMSP_FAILURE, BBMSP_PROFILE_DISPLAY_NAME_MAX
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t
bbmsp_profile_get_display_name(bbmsp_profile_t* profile,
                               char* display_name,
                               size_t buffer_size);

/**
 * @brief Retrieve the user's BBM personal message.
 * @details A personal message is limited to 160 characters; anything longer is
 * truncated.
 *
 * @param profile A pointer to the user's BBM profile.
 * @param personal_message An updated pointer to the array that contains the
 * user's personal message, encoded as UTF-8.
 * @param buffer_size The size of the @c personal_message buffer array.
 *
 * @return @c BBMSP_SUCCESS if successful, @c BBMSP_FAILURE otherwise.
 * @see BBMSP_SUCCESS, BBMSP_FAILURE, BBMSP_PROFILE_PERSONAL_MSG_MAX
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t
bbmsp_profile_get_personal_message(bbmsp_profile_t* profile,
                                   char* personal_message,
                                   size_t buffer_size);

/**
 * @brief Retrieve the user's BBM status.
 *
 * @param profile A pointer to the user's BBM profile.
 * @param status An updated pointer to the user's status.
 *
 * @return @c BBMSP_SUCCESS if successful, @c BBMSP_FAILURE otherwise.
 * @see bbmsp_presence_status_t, BBMSP_SUCCESS, BBMSP_FAILURE
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t
bbmsp_profile_get_status(bbmsp_profile_t* profile,
                         bbmsp_presence_status_t* status);

/**
 * @brief Retrieve the user's BBM status message.
 *
 * @param profile A pointer to the user's BBM profile.
 * @param status_message An updated pointer to the buffer array that contains
 * the user's status message, encoded as UTF-8.
 * @param buffer_size The size of the @c status_message buffer array.
 *
 * @return @c BBMSP_SUCCESS if successful, @c BBMSP_FAILURE otherwise.
 * @see BBMSP_SUCCESS, BBMSP_FAILURE, BBMSP_PROFILE_STATUS_MSG_MAX
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t
bbmsp_profile_get_status_message(bbmsp_profile_t* profile,
                                 char* status_message,
                                 size_t buffer_size);

/**
 * @brief Retrieve the device-independent @c PPID of the user.
 * @details The user's @c PPID is the same across multiple instances of BBM (for
 * example, on a BlackBerry smartphone and a BlackBerry tablet), when the user
 * signs in with the same BlackBerry ID. @c PPID is encoded as a base64 string
 * using the ASCII character set.
 *
 * @param profile A pointer to the user's BBM profile.
 * @param ppid An updated pointer to the @c PPID buffer array, encoded as UTF-8.
 * @param buffer_size The size of the @c PPID buffer array.
 *
 * @return @c BBMSP_SUCCESS if successful, @c BBMSP_FAILURE otherwise.
 * @see BBMSP_SUCCESS, BBMSP_FAILURE, BBMSP_PROFILE_PPID_MAX
 * @ref contactlist_ids
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t
bbmsp_profile_get_ppid(bbmsp_profile_t* profile,
                       char* ppid,
                       size_t buffer_size);

/**
 * @brief Retrieve the handle of the user.
 * @details The @c handle is an identifier for a user on the BBM Social Platform
 * whose device is running BlackBerry 7 or earlier. It is provided for backwards
 * compatibility and should NOT be used as a persistent identifier for a user.
 * Use the @c PPID instead.
 *
 * The user's @c handle is the same for each instance of BBM (for example, on a
 * BlackBerry smartphone and a BlackBerry tablet). @c Handle is encoded as a
 * Base64 string using the ASCII character set.
 *
 * @param profile A pointer to the user's BBM profile.
 * @param handle An updated pointer to the @c handle buffer array, encoded as
 * UTF-8.
 * @param buffer_size The size of the @c handle buffer array.
 *
 * @return @c BBMSP_SUCCESS if successful, @c BBMSP_FAILURE otherwise.
 * @see BBMSP_SUCCESS, BBMSP_FAILURE, BBMSP_PROFILE_HANDLE_MAX,
 * bbmsp_profile_get_ppid()
 * @ref contactlist_ids
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t
bbmsp_profile_get_handle(bbmsp_profile_t* profile,
                         char* handle,
                         size_t buffer_size);

/**
 * @brief Retrieve the version of the BBM connected app that the user is
 * running.
 *
 * @param profile A pointer to the contact's BBM profile.
 * @param app_version An updated pointer to the app version array, encoded as
 * UTF-8.
 * @param buffer_size The size of the @c app_version buffer array.
 *
 * @return @c BBMSP_SUCCESS if successful, @c BBMSP_FAILURE otherwise.
 * @see BBMSP_SUCCESS, BBMSP_FAILURE
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t
bbmsp_profile_get_app_version(bbmsp_profile_t* profile,
                              char* app_version,
                              size_t buffer_size);

/*!@cond PRIVATE
 * @deprecated  Use bbmsp_get_version() to get the version of the BBM Social 
 * Platform library.
 * @brief Retrieves the version of the BBM Social Platform library
 * that your application is using.
 * @details You can use the version number to check whether your application is
 * compatible with this version of the BBM Social Platform.
 *
 * @see BBMSP_VERSION, BBMSP_SUCCESS, BBMSP_FAILURE, bbmsp_get_version()
 * @since BlackBerry 10.0.0
 */
BBMSP_API BBMSP_API_DEPRECATED bbmsp_result_t
bbmsp_profile_get_platform_version(bbmsp_profile_t* profile,
                                   int* platform_version);
//!@endcond PRIVATE

/**
 * @brief Retrieve the version of BBM that is running on the user's
 * device.
 *
 * @param profile A pointer to the user's BBM profile.
 * @param bbm_version An updated pointer to the version of BBM.
 *
 * @details Possible BBM versions are:
 * <ul>
 *    <li>0x0100 for BBM version 1.0 on devices running BlackBerry Device Software 5.0 or earlier</li>
 *    <li>0x0200 for BBM version 2.0 on devices running BlackBerry Device Software 5.0 or earlier</li>
 *    <li>0x0201 for BBM version 2.1 on devices running BlackBerry Device Software 5.0 or earlier</li>
 *    <li>0x0202 for BBM version 2.2 on devices running BlackBerry Device Software 5.0 or earlier</li>
 *    <li>0x0205 for BBM version 2.5 on devices running BlackBerry Device Software 5.0 or earlier</li>
 *    <li>0x0206 for BBM version 2.6 on devices running BlackBerry Device Software 5.0 or earlier</li>
 *    <li>0x0600 for BBM version 6.0 on devices running BlackBerry Device Software 5, BlackBerry 6, or BlackBerry 7</li>
 *    <li>0x0601 for BBM version 6.1 on devices running BlackBerry Device Software 5, BlackBerry 6, or BlackBerry 7</li>
 *    <li>0x0700 for BBM version 7.0 on devices running BlackBerry Device Software 5, BlackBerry 6, or BlackBerry 7</li>
 *    <li>0x0a00 for BBM version 10.0 on devices running BlackBerry 10</li>
 *    <li>0x00 for unknown version</li>
 * </ul>
 * @return @c BBMSP_SUCCESS if successful, @c BBMSP_FAILURE otherwise.
 * @see BBMSP_SUCCESS, BBMSP_FAILURE
 * @since BlackBerry 10.2.0
 */
BBMSP_API bbmsp_result_t
bbmsp_profile_get_bbm_version(bbmsp_profile_t* profile,
                              int* bbm_version);

/**
 * @brief Retrieve the user's display picture.
 *
 * @param profile A pointer to the user's profile.
 * @param display_picture An updated pointer to the user's display picture.
 *
 * @return @c BBMSP_SUCCESS if successful, @c BBMSP_FAILURE otherwise.
 * @see BBMSP_SUCCESS, BBMSP_FAILURE
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t
bbmsp_profile_get_display_picture(bbmsp_profile_t* profile,
                                  bbmsp_image_t* display_picture);

/**
 * @brief Set the status and status message in the current user's BBM profile.
 *
 * @details A dialog displays to allow the user to accept or reject the change.
 *
 * @param profile A pointer to the user's BBM profile.
 * @param status The user's BBM status.
 * @param custom_status_message A pointer to the custom status message array.
 *
 * @return @c BBMSP_SUCCESS if successful, @c BBMSP_FAILURE otherwise.
 * @see bbmsp_presence_status_t, BBMSP_SUCCESS, BBMSP_FAILURE
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t
bbmsp_profile_set_status(bbmsp_profile_t* profile,
                         bbmsp_presence_status_t status,
                         const char* custom_status_message);

/**
 * @brief Set the personal message in the current user's BBM profile.
 *
 * @details A personal message is limited to 160 characters; anything beyond is
 * truncated. If null is passed in, the personal message is cleared. A dialog
 * displays to allow the user to accept or reject the change.
 *
 *
 * @param profile A pointer to the user's BBM profile.
 * @param personal_message A pointer to the user's personal message as an array,
 * encoded as UTF-8.
 *
 * @return @c BBMSP_SUCCESS if successful, @c BBMSP_FAILURE otherwise.
 * @see BBMSP_SUCCESS, BBMSP_FAILURE
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t
bbmsp_profile_set_personal_message(bbmsp_profile_t* profile,
                                   const char* personal_message);

/**
 * @brief Sets the display picture in the current user's BBM profile.
 *
 * @details The display picture change only affects the profile
 * data structure passed in.
 *
 * @param profile A pointer to the user's BBM profile.
 * @param display_picture A pointer to the display picture.
 *
 * @return @c BBMSP_SUCCESS if successful, @c BBMSP_FAILURE otherwise.
 * @see BBMSP_SUCCESS, BBMSP_FAILURE
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t
bbmsp_profile_set_display_picture(bbmsp_profile_t* profile,
                                  bbmsp_image_t* display_picture);

/**
 * @brief Retrieve the BBM user profile that was changed.
 *
 * @details When a user's profile is changed, a
 * @c BBMSP_SP_EVENT_PROFILE_CHANGED event is triggered.
 *
 * @param event A pointer to the @c bbmsp event that was triggered when the user
 * profile was changed.
 * @param profile An updated pointer to the BBM user profile that was changed.
 *
 * @return @c BBMSP_SUCCESS if successful, @c BBMSP_FAILURE otherwise.
 * @see bbmsp_event_category_t, bbmsp_event_type_t, BBMSP_SUCCESS, BBMSP_FAILURE
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t
bbmsp_event_profile_changed_get_profile(bbmsp_event_t* event,
                                        bbmsp_profile_t** profile);

/**
 * @brief Retrieve the field that was changed in the user's BBM profile.
 *
 * @details When a user's profile is changed, a
 * @c BBMSP_SP_EVENT_PROFILE_CHANGED event is triggered.
 *
 * @param event A pointer to the @c bbmsp event that was triggered when the
 * field was changed.
 * @param update_type An updated pointer identifying the field that was updated.
 *
 * @return @c BBMSP_SUCCESS if successful, @c BBMSP_FAILURE otherwise.
 * @see bbmsp_event_t, bbmsp_presence_update_types_t, BBMSP_SUCCESS,
 * BBMSP_FAILURE
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t
bbmsp_event_profile_changed_get_presence_update_type(
  bbmsp_event_t* event,
  bbmsp_presence_update_types_t* update_type);

/**
 * @brief Does not update the user's display name. Only updates the provided
 * @c profile instance.
 *
 * @details Upon receiving an update to the user's display name, you can update
 * your own copy of the @c profile with the new display name by using this
 * function. Your app cannot trigger a change to the user's display name through
 * this function.
 *
 * @param profile A pointer to the user's BBM profile.
 * @param display_name A pointer to the user's display name as an array,
 * encoded as UTF-8.
 *
 * @return @c BBMSP_SUCCESS if successful, @c BBMSP_FAILURE otherwise.
 * @see BBMSP_SUCCESS, BBMSP_FAILURE
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t
bbmsp_profile_set_display_name(bbmsp_profile_t* profile,
                               const char* display_name);

__END_DECLS

#endif /* BBMSP_USERPROFILE_H_ */
