/**
 * @file bbmsp_contactlist.h
 *
 * @brief Functions and structures to access a user's BlackBerry Messenger
 * contact information. Your application will only have access to those contacts
 * that have your application installed.
 * @details This file declares functions and structures that you can use to
 * access a user's BBM contact information, such as display name, status, and
 * personal message.
 * <p>
 *
 * @section contactlist_ids Identifying Users
 * <h3>PPID</h3>
 * Users are identified by their @c PPID. A user's @c PPID is the same across
 * multiple instances of BBM (for example, on a BlackBerry smartphone and a
 * BlackBerry tablet), when the user signs in with the same BlackBerry ID. @c
 * PPID is encoded as a base64 string using the ASCII character set.
 *
 * <h3>Handle</h3>
 * The @c handle is an identifier for a user on the BBM Social Platform whose
 * device is running BlackBerry 7 or earlier. It is provided for backwards
 * compatibility and should NOT be used as a persistent identifier for a user.
 * Use the @c PPID instead.
 *
 * A user's @c handle is the same for each instance of BBM (for example, on a
 * BlackBerry smartphone and a BlackBerry tablet). @c Handle is encoded as a
 * Base64 string using the ASCII character set.
 */

#ifndef BBMSP_CONTACTLIST_H_
#define BBMSP_CONTACTLIST_H_

#include <sys/platform.h>

#include "bbmsp.h"
#include "bbmsp_presence.h"
#include "bbmsp_util.h"

__BEGIN_DECLS

/**
 * The maximum length of a contact's display name. This can be used in
 * @c bbmsp_contact_get_display_name().
 * @since BlackBerry 10.0.0
 */
#define BBMSP_CONTACT_DISPLAY_NAME_MAX (257)

/**
 * The maximum length of a contact's personal message. This can be used in
 * @c bbmsp_contact_get_personal_message().
 * @since BlackBerry 10.0.0
 */
#define BBMSP_CONTACT_PERSONAL_MSG_MAX (161)

/**
 * The maximum length of a contact's status message. This can be used in
 * @c bbmsp_contact_get_status_message().
 * @since BlackBerry 10.0.0
 */
#define BBMSP_CONTACT_STATUS_MSG_MAX (257)

/**
 * The maximum length of a contact's ppid. This can be used in
 * @c bbmsp_contact_get_ppid().
 * @since BlackBerry 10.0.0
 */
#define BBMSP_CONTACT_PPID_MAX (257)

/**
 * The maximum length of a contact's handle. This can be used in
 * @c bbmsp_contact_get_handle().
 * @since BlackBerry 10.0.0
 */
#define BBMSP_CONTACT_HANDLE_MAX (257)

/**
 * The maximum length of a contact's app version. This can be used in
 * @c bbmsp_contact_get_app_version().
 * @since BlackBerry 10.0.0
 */
#define BBMSP_CONTACT_APP_VERSION_MAX (30)

/**
 * @brief A user's BBM contact information.
 * @since BlackBerry 10.0.0
 */
typedef struct bbmsp_contact_t bbmsp_contact_t;

/**
 * @brief Create a new BBM contact structure.
 * @details Creates a BBM contact structure. When the contact is no longer required,
 * call @c bbmsp_contact_destroy() to free up the associated memory.
 * @param contact An updated pointer to the new contact.
 *
 * @return @c BBMSP_SUCCESS if successful, @c BBMSP_FAILURE otherwise.
 * @see bbmsp_contact_destroy(), BBMSP_SUCCESS, BBMSP_FAILURE
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t bbmsp_contact_create(bbmsp_contact_t** contact);

/**
 * @brief Destroy a BBM contact structure.
 * @details Destroys this BBM contact structure and frees up the associated memory.
 * @param contact A pointer to the contact to destroy.
 *
 * @return @c BBMSP_SUCCESS if successful, @c BBMSP_FAILURE otherwise.
 * @see BBMSP_SUCCESS, BBMSP_FAILURE
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t bbmsp_contact_destroy(bbmsp_contact_t** contact);

/**
 * @brief Copy a source contact to a destination contact.
 * @details Copies the source contact to the destination contact.
 * @param destination A pointer to destination contact, which can be created
 * using @c bbmsp_contact_create().
 * @param source A pointer to source contact.
 *
 * @return @c BBMSP_SUCCESS if successful, @c BBMSP_FAILURE otherwise.
 * @see BBMSP_SUCCESS, BBMSP_FAILURE
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t
bbmsp_contact_copy(bbmsp_contact_t* destination, const bbmsp_contact_t* source);

/**
 * @brief Compare two contacts by display name.
 * @details You can use this function to create a list of contacts that are
 * sorted alphabetically.
 * @param contact A pointer to the first contact name.
 * @param other_contact A pointer to the contact name to compare to.
 *
 * @return A negative integer if @c contact display name is lexicographically
 * less than @c other_contact display name; zero if @c contact display name is
 * lexicographically equal to @c other_contact display name; a positive
 * integer if @c contact display name is lexicographically greater than
 * @c other_contact display name. -1 is returned if invalid parameters are
 * provided.
 * @since BlackBerry 10.0.0
 */
BBMSP_API int
bbmsp_contact_compare(const bbmsp_contact_t* contact,
                      const bbmsp_contact_t* other_contact);

/**
 * @brief Retrieve a contact's display name.
 *
 * @param contact The contact whose display name to retrieve.
 * @param display_name A buffer that will be updated with the display name
 * encoded as UTF-8. The resulting buffer will be null-terminated on success.
 * @param display_name_buffer_size The size of the display name buffer. This
 * should be @c BBMSP_CONTACT_DISPLAY_NAME_MAX.
 *
 * @return @c BBMSP_SUCCESS if successful, @c BBMSP_FAILURE otherwise.
 * @see BBMSP_SUCCESS, BBMSP_FAILURE, BBMSP_CONTACT_DISPLAY_NAME_MAX
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t
bbmsp_contact_get_display_name(const bbmsp_contact_t* contact,
                               char* display_name,
                               size_t display_name_buffer_size);

/**
 * @brief Retrieve a contact's personal message.
 * @param contact A pointer to the contact whose personal message to retrieve.
 * @param personal_message A buffer that will be updated with the personal
 * message encoded as UTF-8. The resulting buffer will be null-terminated on
 * success.
 * @param personal_message_buffer_size The size of the personal message buffer.
 * This should be @c BBMSP_CONTACT_PERSONAL_MSG_MAX.
 *
 * @return @c BBMSP_SUCCESS if successful, @c BBMSP_FAILURE otherwise.
 * @see BBMSP_SUCCESS, BBMSP_FAILURE, BBMSP_CONTACT_PERSONAL_MSG_MAX
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t
bbmsp_contact_get_personal_message(const bbmsp_contact_t* contact,
                                   char* personal_message,
                                   size_t personal_message_buffer_size);

/**
 * @brief Retrieve a contact's status.
 * @details A contact's status can be either busy or available.
 * @param contact A pointer to the contact whose status to get.
 * @param status is updated with the contact's status.
 *
 * @return @c BBMSP_SUCCESS if successful, @c BBMSP_FAILURE otherwise.
 * @see BBMSP_SUCCESS, BBMSP_FAILURE, bbmsp_presence_status_t
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t
bbmsp_contact_get_status(const bbmsp_contact_t* contact,
                         bbmsp_presence_status_t* status);

/**
 * @brief Retrieve a contact's status message.
 * @param contact A pointer to the contact whose status message to get.
 * @param status_message A buffer that will be updated with the status message
 * encoded as UTF-8. The resulting buffer will be null-terminated on success.
 * @param status_message_buffer_size The size of the @c status_message buffer.
 * This should be @c BBMSP_CONTACT_STATUS_MSG_MAX.
 *
 * @return @c BBMSP_SUCCESS if successful, @c BBMSP_FAILURE otherwise.
 * @see BBMSP_SUCCESS, BBMSP_FAILURE, BBMSP_CONTACT_STATUS_MSG_MAX
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t
bbmsp_contact_get_status_message(const bbmsp_contact_t* contact,
                                 char* status_message,
                                 size_t status_message_buffer_size);

/**
 * @brief Retrieve a contact's PPID.
 * @details The user's PPID is the same across multiple instances of BBM (for
 * example, on a BlackBerry smartphone and a BlackBerry tablet), when the user
 * signs in with the same BlackBerry ID. PPID is encoded as a Base64 string
 * using the ASCII character set.
 *
 * @param contact A pointer to the contact whose PPID to get.
 * @param ppid A buffer that will be updated with the PPID encoded as Base64.
 * The resulting buffer will be null-terminated on success.
 * @param ppid_buffer_size The size of the @c ppid buffer. This should be @c
 * BBMSP_CONTACT_PPID_MAX.
 *
 * @return @c BBMSP_SUCCESS if successful, @c BBMSP_FAILURE otherwise.
 * @see BBMSP_SUCCESS, BBMSP_FAILURE, BBMSP_CONTACT_PPID_MAX
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t bbmsp_contact_get_ppid(const bbmsp_contact_t* contact,
                                                char* ppid,
                                                size_t ppid_buffer_size);

/**
 * @brief Retrieve a contact's handle.
 * @details The @c handle is an identifier for a user on the BBM Social Platform
 * whose device is running BlackBerry 7 or earlier. It is provided for backwards
 * compatibility and should NOT be used as a persistent identifier for a user.
 * Use the @c PPID instead.
 *
 * A user's @c handle is the same for each instance of BBM (for example, on a
 * BlackBerry smartphone and a BlackBerry tablet). @c Handle is encoded as a
 * Base64 string using the ASCII character set.
 *
 * @param contact A pointer to the contact whose handle to get.
 * @param handle A buffer that will be updated with the handle encoded as Base64.
 * The resulting buffer will be null-terminated on success.
 * @param handle_buffer_size The size of the @c handle buffer. This should be
 * @c BBMSP_CONTACT_HANDLE_MAX.
 *
 * @return @c BBMSP_SUCCESS if successful, @c BBMSP_FAILURE otherwise.
 * @see BBMSP_SUCCESS, BBMSP_FAILURE, BBMSP_CONTACT_HANDLE_MAX,
 * @ref contactlist_ids
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t
bbmsp_contact_get_handle(const bbmsp_contact_t* contact,
                         char* handle,
                         size_t handle_buffer_size);

/**
 * @brief Retrieve a contact's version of the app that they have installed.
 * @param contact A pointer to the contact whose app version to get.
 * @param app_version A buffer that will be updated with the app version encoded
 * as UTF-8. The resulting buffer will be null-terminated on success.
 * @param app_version_buffer_size The size of the @c app_version buffer. This
 * should be @c BBMSP_CONTACT_APP_VERSION_MAX.
 *
 * @return @c BBMSP_SUCCESS if successful, @c BBMSP_FAILURE otherwise.
 * @see BBMSP_SUCCESS, BBMSP_FAILURE, BBMSP_CONTACT_APP_VERSION_MAX
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t
bbmsp_contact_get_app_version(const bbmsp_contact_t* contact,
                              char* app_version,
                              size_t app_version_buffer_size);

/**
 * @brief Retrieve a contact's version of the BBM Social Platform.
 * @param contact A pointer to the contact whose BBM Social Platform version to
 * get.
 * @param platform_version is updated to the BBM Social Platform version of the
 * contact.
 *
 * @return @c BBMSP_SUCCESS if successful, @c BBMSP_FAILURE otherwise.
 * @see BBMSP_SUCCESS, BBMSP_FAILURE
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t
bbmsp_contact_get_platform_version(const bbmsp_contact_t* contact,
                                   int* platform_version);

/**
 * @brief Retrieve the version of BBM that is running on a contact's device.
 * @param contact A pointer to the contact whose BBM version to
 * get.
 * @param bbm_version Updated with the BBM version of the contact.
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
bbmsp_contact_get_bbm_version(const bbmsp_contact_t* contact,
                              int* bbm_version);

/**
 * @brief Retrieve a contact's display picture.
 * @details If the contact's display picture has been previously retrieved, this
 * function will return @c BBMSP_SUCCESS. If the contact's display picture has
 * not been retrieved, this will return @c BBMSP_ASYNC and the data will come
 * back through an event of category @c BBMSP_CONTACT_LIST, type @c
 * BBMSP_SP_EVENT_CONTACT_CHANGED, and the field @c BBMSP_DISPLAY_PICTURE. If
 * there is an error, @c BBMSP_FAILURE will be returned.
 * @param contact A pointer to the contact whose display picture to get.
 * @param display_picture is updated to the contact's display picture, created
 * with @c bbmsp_image_create(). If a null pointer is provided, this method
 * returns @c BBMSP_FAILURE.
 *
 * @return @c BBMSP_SUCCESS if successful, @c BBMSP_ASYNC if the response will
 * come back asynchronously, and @c BBMSP_FAILURE otherwise.
 * @see bbmsp_image_t, BBMSP_SUCCESS, BBMSP_FAILURE
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t
bbmsp_contact_get_display_picture(const bbmsp_contact_t* contact,
                                  bbmsp_image_t* display_picture);

/**
 * @brief Retrieve the contact whose contact information has changed.
 * @details When a contact changes their contact information, a
 * @c BBMSP_SP_EVENT_CONTACT_CHANGED event is triggered.
 * @param event A pointer to the @c bbmsp event that was triggered.
 * @param contact is populated with the contact data whose information was
 * changed. The memory allocated by this function needs to be freed using @c
 * bbmsp_contact_destroy() when no longer needed.
 *
 * @return @c BBMSP_SUCCESS if successful, @c BBMSP_FAILURE otherwise.
 * @see bbmsp_event_t, BBMSP_SUCCESS, BBMSP_FAILURE
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t
bbmsp_event_contact_changed_get_contact(bbmsp_event_t* event,
                                        bbmsp_contact_t** contact);

/**
 * @brief Retrieve the field that was modified when a contact's profile is
 * changed.
 * @details When a contact changes their profile information, a
 * @c BBMSP_SP_EVENT_PROFILE_CHANGED event is triggered.
 * @param event A pointer to the @c bbmsp event that was triggered.
 * @param update_type is updated with the field that was changed.
 *
 * @return @c BBMSP_SUCCESS if successful, @c BBMSP_FAILURE otherwise.
 * @see bbmsp_event_t, bbmsp_presence_update_types_t, BBMSP_SUCCESS,
 * BBMSP_FAILURE
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t
bbmsp_event_contact_changed_get_presence_update_type(
  bbmsp_event_t* event,
  bbmsp_presence_update_types_t* update_type);

/**
 * @brief A user's contact list.
 * @since BlackBerry 10.0.0
 */
typedef struct bbmsp_contact_list_t bbmsp_contact_list_t;

/**
 * @brief Asynchronously retrieve the user's contact list containing the contacts
 * that have your application installed.
 * @details A @c BBMSP_SP_EVENT_CONTACT_LIST_FULL event is triggered when the
 * contact list is available.
 *
 * @return @c BBMSP_ASYNC if successful, @c BBMSP_FAILURE otherwise.
 * @see bbmsp_event_contact_list, BBMSP_ASYNC, BBMSP_FAILURE
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t bbmsp_contact_list_get(void);

/**
 * @brief Create a new contact list.
 * @details Creates a new, empty contact list. When the contact list is no longer
 * required, call @c bbmsp_contact_list_destroy() to free up the associated
 * memory.
 * @param contact_list is updated to an empty contact list.
 *
 * @return @c BBMSP_SUCCESS if successful, @c BBMSP_FAILURE otherwise.
 * @see bbmsp_contact_list_destroy(), bbmsp_contact_list_t, BBMSP_SUCCESS,
 * BBMSP_FAILURE
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t
bbmsp_contact_list_create(bbmsp_contact_list_t** contact_list);

/**
 * @brief Destroy a contact list.
 * @details Destroys this contact list and frees up the associated memory.
 *
 * @param contact_list A pointer to the contact list to destroy.
 *
 * @return @c BBMSP_SUCCESS if successful, @c BBMSP_FAILURE otherwise.
 * @see bbmsp_contact_list_t, BBMSP_SUCCESS, BBMSP_FAILURE
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t
bbmsp_contact_list_destroy(bbmsp_contact_list_t** contact_list);

/**
 * @brief Add a contact to this contact list.
 * @details If the contact already exists it is replaced with this new value.
 *
 * @param contact_list A pointer to the contact list to add the contact to.
 * @param contact A pointer to the contact to add.
 *
 * @return @c BBMSP_SUCCESS if successful, @c BBMSP_FAILURE otherwise.
 * @see BBMSP_SUCCESS, BBMSP_FAILURE
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t
bbmsp_contact_list_add_contact(bbmsp_contact_list_t* contact_list,
                               bbmsp_contact_t* contact);

/**
 * @brief Check if a contact is in a contact list.
 * @details The contact's handle is used to determine equality.
 * @param contact_list A pointer to the contact list to check.
 * @param contact A pointer to the contact to search for.
 *
 * @return @c BBMSP_SUCCESS if found, @c BBMSP_FAILURE otherwise.
 * @see bbmsp_contact_list_t, bbmsp_contact_t, @ref contactlist_ids
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t
bbmsp_contact_list_contains_contact(bbmsp_contact_list_t* contact_list,
                                    bbmsp_contact_t* contact);

/**
 * @brief Retrieve a contact with the handle from a contact list.
 * @param contact_list A pointer to the contact list to search.
 * @param handle A null-terminated pointer to the handle.
 * @param contact is created using @c bbmsp_contact_create() and updated to the
 * found contact.
 *
 * @return @c BBMSP_SUCCESS if found, @c BBMSP_FAILURE otherwise.
 * @see bbmsp_contact_list_t, bbmsp_contact_t, BBMSP_SUCCESS, BBMSP_FAILURE,
 * @ref contactlist_ids
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t
bbmsp_contact_list_get_contact(const bbmsp_contact_list_t* contact_list,
                               char* handle,
                               bbmsp_contact_t* contact);

/**
 * @brief Return all contacts in the contact list.
 * @details @c contact_array should be created to point to an array of @c
 * bbmsp_contact_t pointers as large as the number of elements in the contact
 * list.
 * @param contact_list A pointer to the contact list.
 * @param contact_array An updated array of @c bbmsp_contact_t pointers.
 *
 * @return @c BBMSP_SUCCESS if successful, @c BBMSP_FAILURE otherwise.
 * @see BBMSP_SUCCESS, BBMSP_FAILURE
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t
bbmsp_contact_list_get_all_contacts(const bbmsp_contact_list_t* contact_list,
                                    bbmsp_contact_t** contact_array);

/**
 * @brief Remove a contact from a contact list.
 * @param contact_list A pointer to the contact list to remove the contact from.
 * @param contact A pointer to the contact to remove.
 *
 * @return @c BBMSP_SUCCESS if successful, @c BBMSP_FAILURE otherwise.
 * @see BBMSP_SUCCESS, BBMSP_FAILURE, @ref contactlist_ids
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t
bbmsp_contact_list_remove_contact(bbmsp_contact_list_t* contact_list,
                                  const bbmsp_contact_t* contact);

/**
 * @brief Retrieve the total number of contacts in the contact list.
 *
 * @param contact_list A pointer to the contact list.
 *
 * @return The size of the contact list.
 * @since BlackBerry 10.0.0
 */
BBMSP_API size_t
bbmsp_contact_list_get_size(const bbmsp_contact_list_t* contact_list);

/**
 * @brief Retrieve all the contacts in the contact list.
 * @details Use this to retrieve contacts that were received as a response to
 * @c bbmsp_contact_list_get() through a @c BBMSP_SP_EVENT_CONTACT_LIST_FULL
 * event.
 *
 * @param event A pointer to the @c bbmsp event that was triggered.
 * @param contact_list An updated pointer to the contact list.
 *
 * @return @c BBMSP_SUCCESS if successful, @c BBMSP_FAILURE otherwise.
 * @see bbmsp_event_t, BBMSP_SUCCESS, BBMSP_FAILURE
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t
bbmsp_event_contact_list_get_full_contact_list(
  bbmsp_event_t* event,
  bbmsp_contact_list_t** contact_list);

/**
 * @brief Registers with BlackBerry Platform Services (BPS) to receive contact
 * list related events.
 *
 * @return @c BBMSP_SUCCESS if successful, @c BBMSP_FAILURE otherwise.
 * @see bbmsp_event_t, BBMSP_SUCCESS, BBMSP_FAILURE
 * @since BlackBerry 10.0.0
 */
BBMSP_API bbmsp_result_t bbmsp_event_contact_list_register_event(void);


__END_DECLS

#endif /* BBMSP_CONTACTLIST_H_ */
