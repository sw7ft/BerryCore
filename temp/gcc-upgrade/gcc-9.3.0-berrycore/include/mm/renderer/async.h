/*
 * $QNXLicenseC:
 * Copyright 2013, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable license fees to QNX
 * Software Systems before you may reproduce, modify or distribute this software,
 * or any work that includes all or part of this software.   Free development
 * licenses are available for evaluation and non-commercial purposes.  For more
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *
 * This file may contain contributions from others.  Please review this entire
 * file for other proprietary rights or license notices, as well as the QNX
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 * $
 */


#if !defined(MM_RENDERER_ASYNC_H_INCLUDED)
#define MM_RENDERER_ASYNC_H_INCLUDED

/** @file async.h
 *  mm-renderer async API functions
 *  @ingroup ClientAPI Async API
 */

#if !defined(MM_RENDERER_H_INCLUDED)
#include <mm/renderer.h>
#endif

__BEGIN_DECLS

/**
 * @addtogroup AsyncAPI Async API
 */
/*@{*/

/**
 *  @brief Asynchronously create a context
 *
 *  @details Send a request to create a context and return a handle.
 *
 *  @param connection An @e mm-renderer connection handle.
 *  @param udata      User data to be returned with the result.
 *  @param name       The name of the context.
 *  @param flags      Must be zero.  No flags are defined for now.
 *  @param mode       File permission flags for the new context directory.
 *
 *  @return A handle on success, or a null pointer on failure (check @e errno).
 */
mmr_context_t *mmr_async_context_create( mmr_connection_t *connection, void *udata, const char *name, unsigned flags, mode_t mode );

/**
 *  @brief Asynchronously open an existing context
 *
 *  @details Send a request to open an existing context and return a handle.
 *
 *  @param connection An @e mm-renderer connection handle.
 *  @param udata      User data to be returned with the result.
 *  @param name       The context name.
 *
 *  @return A handle on success, or a null pointer on failure (check @e errno).
 */
mmr_context_t *mmr_async_context_open( mmr_connection_t *connection, void *udata, const char *name );


/**
 *  @brief Asynchronously destroy a context
 *
 *  @details Send a request to destroy the context the handle refers to. The
 *  handle becomes invalid and must not be used after this call. The completion
 *  of this request is reported by @c mmr_async_nextcomplete() with a NULL
 *  context handle in @c #mmr_async_result_t.
 *
 *  @param ctxt   A context handle.
 *  @param udata  User data to be returned with the result.
 *
 *  @return Zero on success, -1 on failure (check @e errno).
 */
int mmr_async_context_destroy( mmr_context_t *ctxt, void *udata );

/**
 *  @brief Asynchronously close a context
 *
 *  @details Asynchronously close the context handle. The handle becomes invalid
 *  and must not be used after this call. The completion of this request is
 *  reported by @c mmr_async_nextcomplete() with a NULL context handle in @c
 *  #mmr_async_result_t. Depending on the configuration, the context the handle
 *  refers to might also be destroyed.
 *
 *  @param ctxt   A context handle.
 *  @param udata  User data to be returned with the result.
 *
 *  @return Zero on success, -1 on failure (check @e errno).
 */
int mmr_async_context_close( mmr_context_t *ctxt, void *udata );

/**
 *  @brief Asynchronously set context parameters
 *
 *  @details Send a request to set parameters associated with the context.
 *
 *  @param ctxt  A context handle.
 *  @param udata User data to be returned with the result.
 *  @param parms A dictionary object containing the parameters to set (handle is
 *               consumed by this call, even on failure).
 *
 *  @return Zero on success, -1 on failure (check @e errno).
 */
int mmr_async_context_parameters( mmr_context_t *ctxt, void *udata, strm_dict_t *parms );

/**
 *  @brief Asynchronously attach an input
 *
 *  @details Send a request to attach an input file, device, or playlist. If the
 *  context already has an input, it is detached first.
 *
 *  @param ctxt  A context handle.
 *  @param udata User data to be returned with the result.
 *  @param url   The URL of the new input.
 *  @param type  The type of the input.
 *
 *  @return Zero on success, -1 on failure (check @e errno).
 */
int mmr_async_input_attach( mmr_context_t *ctxt, void *udata, const char *url, const char *type );

/**
 *  @brief Asynchronously detach an input
 *
 *  @details Send a request to detach an input.
 *
 *  @param ctxt  A context handle.
 *  @param udata User data to be returned with the result.
 *
 *  @return Zero on success, -1 on failure (check @e errno).
 */
int mmr_async_input_detach( mmr_context_t *ctxt, void *udata );

/**
 *  @brief Asynchronously set input parameters
 *
 *  @details Send a request to set parameters associated with the attached input
 *  media.
 *
 *  @param ctxt  A context handle.
 *  @param udata User data to be returned with the result.
 *  @param parms A dictionary object containing the parameters to set (handle
 *               is consumed by this call, even on failure).
 *
 *  @return Zero on success, -1 on failure (check @e errno).
 */
int mmr_async_input_parameters( mmr_context_t *ctxt, void *udata, strm_dict_t *parms );

/**
 *  @brief Asynchronously attach an output
 *
 *  @details Send a request to attach an output and return its output ID.
 *
 *  @param ctxt  A context handle.
 *  @param udata User data to be returned with the result.
 *  @param url   The URL of the new output.
 *  @param type  The output type ("audio", "video", etc.).
 *
 *  @return Zero on success, -1 on failure (check @e errno).
 */
int mmr_async_output_attach( mmr_context_t *ctxt, void *udata, const char *url, const char *type );

/**
 *  @brief Asynchronously detach an output
 *
 *  @details Send a request to detach an output.
 *
 *  @param ctxt      A context handle.
 *  @param udata     User data to be returned with the result.
 *  @param output_id An output ID.
 *
 *  @return Zero on success, -1 on failure (check @e errno).
 */
int mmr_async_output_detach( mmr_context_t *ctxt, void *udata, unsigned output_id );

/**
 *  @brief Asynchronously set output parameters
 *
 *  @details Send a request to set parameters for the specified output device.
 *
 *  @param ctxt      A context handle.
 *  @param udata     User data to be returned with the result.
 *  @param output_id An output ID.
 *  @param parms     A dictionary object containing the parameters to set
 *                   (handle is consumed by this call, even on failure).
 *
 *  @return Zero on success, -1 on failure (check @e errno).
 */
int mmr_async_output_parameters( mmr_context_t *ctxt, void *udata, unsigned output_id, strm_dict_t *parms );

/**
 *  @brief Asynchronously start playing
 *
 *  @details Send a request to start playing. A no-op if already playing.
 *
 *  @param ctxt  A context handle.
 *  @param udata User data to be returned with the result.
 *
 *  @return Zero on success, -1 on failure (check @e errno).
 */
int mmr_async_play( mmr_context_t *ctxt, void *udata );

/**
 *  @brief Asynchronously stop playing
 *
 *  @details Send a request to stop playing. A no-op if already stopped.
 *
 *  @param ctxt  A context handle.
 *  @param udata User data to be returned with the result.
 *
 *  @return Zero on success, -1 on failure (check @e errno).
 */
int mmr_async_stop( mmr_context_t *ctxt, void *udata );

/**
 *  @brief Asynchronously seek to a position
 *
 *  @details Send a request to seek to a position.
 *
 *  @param ctxt     A context handle.
 *  @param udata    User data to be returned with the result.
 *  @param position The position to seek to, in a media-specific format.
 *
 *  @return Zero on success, -1 on failure (check @e errno).
 */
int mmr_async_seek( mmr_context_t *ctxt, void *udata, const char *position );

/**
 *  @brief Asynchronously set the play speed
 *
 *  @details Send a request to set the play speed.
 *
 *  @param ctxt  A context handle.
 *  @param udata User data to be returned with the result.
 *  @param speed The new speed.
 *
 *  @return Zero on success, -1 on failure (check @e errno).
 */
int mmr_async_speed_set( mmr_context_t *ctxt, void *udata, int speed );

/**
 *  @brief Asynchronously send a remote control command to the context
 *
 *  @details Send a request to send a remote control command to the context.
 *
 *  @param ctxt  A context handle.
 *  @param udata User data to be returned with the result.
 *  @param cmd   The command.
 *
 *  @return Zero on success, -1 on failure (check @e errno).
 */
int mmr_async_command_send( mmr_context_t *ctxt, void *udata, const char *cmd );

/**
 *  @brief Asynchronously set a new playlist
 *
 *  @details Send a request to set a new playlist without interrupting playback.
 *
 *  @param ctxt  A context handle.
 *  @param udata User data to be returned with the result.
 *  @param url   The URL of a new playlist.
 *  @param delta The difference between the position of the current track on the
 *               two lists.
 *
 *  @return Zero on success, -1 on failure (check @e errno).
 */
int mmr_async_list_change( mmr_context_t *ctxt, void *udata, const char *url, int delta );

/**
 *  @brief Asynchronously set track parameters
 *
 *  @details Send a request to set track parameters. This function can only be
 *  used when the input is a playlist.
 *
 *  @param ctxt  A context handle.
 *  @param udata User data to be returned with the result.
 *  @param index Zero to set the default parameters, or an index within the
 *               current playlist window.
 *  @param parms The parameters, or NULL to reset to the default (handle is
 *               consumed by this call, even on failure).
 *
 *  @return Zero on success, -1 on failure (check @e errno).
 */
int mmr_async_track_parameters( mmr_context_t *ctxt, void *udata, unsigned index, strm_dict_t *parms );

struct sigevent;

/**
 *  @brief Results of an asynchronous request
 */
typedef struct mmr_async_result {
	mmr_context_t *ctxt;           ///<  The context this result is from (NULL if it was a close/destroy or a failed open/create).
	void *udata;                   ///<  The udata that was given to the async call.
	int result;                    ///<  -1 if failed, >= 0 if succeeded (according to the request).
	int errnum;                    ///<  Error code if it was a failed open/close/create/destroy.
	const mmr_error_info_t *error; ///<  NULL if succeeded, or if it was an open/close/create/destroy.
    /** @cond internal **/
	int reserved[4];
    /** @endcond       **/
} mmr_async_result_t;

/**
 *  @brief Modes of operation for @c mmr_async_nextcomplete()
 */
typedef enum mmr_async_mode {
	MMR_ASYNC_BLOCK     = 0, ///< Block until there's a result
	MMR_ASYNC_NOBLOCK   = 1, ///< Just return 0 if there's no result
} mmr_async_mode_t;

/**
 *  @brief Set an event for asynchronous requests
 *
 *  @details This function sets an event to deliver whenever asynchronous
 *  results become available.
 *
 *  Note that spurious events are possible.
 *
 *  @param connection A connection handle.
 *  @param sigevent   A pointer to the event, or NULL to disarm.
 *
 *  @return 0 on success, -1 on error (check @e errno).
 */
int mmr_async_setevent( mmr_connection_t *connection, const struct sigevent *sigevent );

/** @brief Find a completed asynchronous operation
 *
 *  @details This function optionally blocks until the result of an asynchronous
 *  operation is available, and then returns it in the buffer provided. If the
 *  request was a close or destroy, or if it was an open or create and it
 *  failed, the context handle becomes invalid and you must not attempt to use
 *  it.
 *
 *  If the result contains a pointer to error info, the error info is only valid
 *  until another request is issued to the same context.
 *
 *  @param connection A connection handle.
 *  @param mode       Mode to control blocking.
 *  @param result     Pointer to a buffer to store the result in.
 *
 *  @retval >0 if a new result is returned in @c *result.
 *  @retval 0  if @c mode is @c #MMR_ASYNC_NOBLOCK and there is no new result to
 *          return (@c sigevent is armed).
 *  @retval -1 on error (check @e errno).
 */
int mmr_async_nextcomplete( mmr_connection_t *connection, mmr_async_mode_t mode, mmr_async_result_t *result );


/*@}*/

__END_DECLS

#endif

__SRCVERSION("$URL$ $Rev$")
