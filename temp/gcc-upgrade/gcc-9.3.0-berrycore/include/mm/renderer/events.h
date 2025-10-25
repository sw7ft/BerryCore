/*
 * $QNXLicenseC:
 * Copyright 2009, QNX Software Systems. All Rights Reserved.
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


#if !defined(MM_RENDERER__EVENTS_H_INCLUDED)
#define MM_RENDERER_EVENTS_H_INCLUDED

/** @file events.h
 *  mm-renderer event API functions
 *  @ingroup EventAPI Event API
 */

#if !defined(MM_RENDERER_H_INCLUDED)
#include <mm/renderer.h>
#endif

__BEGIN_DECLS

/**
 * @addtogroup EventAPI Event API
 */
/*@{*/

/**
 *  The event type.
 */
typedef enum mmr_event_type {
		MMR_EVENT_NONE,     ///< No pending events.
		MMR_EVENT_ERROR,    ///< Playback has stopped due to an error or EOF.
		MMR_EVENT_STATE,    ///< State or speed change, other than an error or EOF.
		MMR_EVENT_OVERFLOW, ///< Some state changes lost; the event contains most the recent state.
		MMR_EVENT_WARNING,  ///< Warning event.
		MMR_EVENT_STATUS,   ///< Status update (position, buffer level, etc).
		MMR_EVENT_METADATA, ///< Metadata update for the attached input, or one track referenced by the attached input
				    ///< (such as a playlist entry).
		MMR_EVENT_PLAYLIST, ///< Playlist window update.
		MMR_EVENT_INPUT,    ///< An input has been attached or detached, or input parameters changed.
		MMR_EVENT_OUTPUT,   ///< An output has been attached or detached, or output parameters changed.
		MMR_EVENT_CTXTPAR,  ///< Context parameters have changed.
		MMR_EVENT_TRKPAR,   ///< Track parameters for an individual track or a playlist entry have changed.
		MMR_EVENT_OTHER,    ///< None of the above, but something has changed. You can typically ignore this event type.
} mmr_event_type_t;

/**
 *  @brief The context state
 */
typedef enum mmr_state {
    MMR_STATE_DESTROYED,  ///< The context has been destroyed.
    MMR_STATE_IDLE,       ///< The context has no input.
    MMR_STATE_STOPPED,    ///< The context has an input but is not playing.
    MMR_STATE_PLAYING,    ///< The context is playing or paused.
} mmr_state_t;

/**
 *  @brief The event structure.
 */
typedef struct mmr_event {
	mmr_event_type_t    type;       ///< The event type.
	mmr_state_t         state;      ///< The new context state (valid even
                                    ///< when type is @c MMR_EVENT_NONE).
	int                 speed;      ///< The playback speed (0 means paused).

	union mmr_event_details {
		struct mmr_event_state {
			mmr_state_t oldstate;     ///< The state before the event.
			int oldspeed;             ///< The speed before the event.
		}               state;        ///< When type is @c MMR_EVENT_STATE.
		struct mmr_event_error {
			mmr_error_info_t info;    ///< The error information.
		}               error;        ///< When type is @c MMR_EVENT_ERROR.
		struct mmr_event_warning {
			const char *str;            ///< The warning string, as a C string.
			const strm_string_t *obj;   ///< The warning string, as a
                                        ///< strm_string_t (dictionary string).
		}               warning;        ///< When type is @c MMR_EVENT_WARNING.
		struct mmr_event_metadata {
			unsigned index;           ///< The playlist index for
                                      ///< playlist-related events; otherwise,
                                      ///< zero.
		}               metadata;     ///< When type is METADATA.
		struct mmr_event_trkparam {
			unsigned index;           ///< The playlist index.
		}               trkparam;     ///< When type is TRKPAR.
		struct mmr_event_playlist {
			unsigned start;           ///< The index of the first item in the
                                      ///< playlist window.
			unsigned end;             ///< The index of the last item in the
                                      ///< playlist window.
			unsigned length;          ///< The playlist length.
		}               playlist;     ///< When type is PLAYLIST.
		struct mmr_event_output {
			unsigned id;              ///< Output ID.
		}               output;       ///< When type is OUTPUT.
	} details;                        ///< The event details (varies by type).

	const strm_string_t *pos_obj;     ///< The playback position when the event
                                      ///< occurred, stored as a shareable
                                      ///< string, for @c MMR_EVENT_STATUS, @c
                                      ///< MMR_EVENT_ERROR, and @c
                                      ///< MMR_EVENT_WARNING events; otherwise
                                      ///< NULL.
	const char          *pos_str;     ///< The playback position when the event
                                      ///< occurred, stored as a shareable
                                      ///< string, for STATUS, ERROR, and
                                      ///< WARNING events; otherwise NULL. The
                                      ///< position is expressed in the same
                                      ///< media-specific format used by the @c
                                      ///< mmr_seek() function.
	const strm_dict_t   *data;        ///< The full set of mm-renderer
                                      ///< properties reported by the event,
                                      ///< stored in a dictionary object. When
                                      ///< this field is NULL, the set of
                                      ///< properties no longer exists; for
                                      ///< example, the input parameters, URL,
                                      ///< and type are deleted when the input
                                      ///< is detached.
	const char          *objname;     ///< The name of the internal mm-renderer
                                      ///< object that updated the dictionary in
                                      ///< response to user activity or a
                                      ///< playback state change.
	void                *usrdata;     ///< The user data associated with the
                                      ///< object that manages the dictionary
                                      ///< referenced in the event information.
} mmr_event_t;

/**
 *  @brief Get the next available event
 *
 *  @details Get the next available event. The function returns a pointer to an
 *  @c #mmr_event_t structure, which contains detailed event information such as
 *  the new context state (see @c #mmr_event_t for details). Typically, you
 *  would call this function within an event-processing loop, after calling
 *  either @c mmr_event_arm() or @c mmr_event_wait().
 *
 *  The data returned in the @c #mmr_event_t structure is valid only until the
 *  next @c mmr_event_get() call. If you want to keep the data longer, copy the
 *  @c mmr_event_t contents into other program variables, cloning any @c
 *  strm_string_t fields within the structure.
 *
 *  @note In any playback state, @c mmr_event_get() might return the @c
 *  #MMR_EVENT_NONE event. Applications must gracefully handle this event,
 *  perhaps simply by ignoring it. For an example of a situation when @c
 *  #MMR_EVENT_NONE might be returned, see @c mmr_event_wait() .
 *
 *  @param ctxt A context handle.
 *  @return A pointer to an event, or NULL on error (check @c errno).
 */
const mmr_event_t *mmr_event_get( mmr_context_t *ctxt );

/**
 *  @brief Set user data for the dictionary returned with the last event
 *
 *  @details Set a pointer to the user data to associate with the dictionary
 *  returned with the last event. The dictionary is stored in the @c
 *  #mmr_event_t structure's @c data field and contains all the @e mm-renderer
 *  properties reported by the event.
 *
 *  The @c MMR_EVENT_STATUS, @c MMR_EVENT_CTXTPAR, @c MMR_EVENT_PLAYLIST, and
 *  @c MMR_EVENT_INPUT events have one user data pointer each, whose index is
 *  always zero. So, if you set the user data after receiving, say, an @c
 *  MMR_EVENT_STATUS event, the same user data pointer is returned with any
 *  subsequent @c MMR_EVENT_STATUS event.
 *
 *  The @c MMR_EVENT_STATE, @c MMR_EVENT_ERROR, and @c MMR_EVENT_WARNING, share
 *  a single dictionary and therefore have a common user data pointer. So, if
 *  you set the user data after receiving, say, an @c MMR_EVENT_STATE event, the
 *  same user data pointer is returned with any subsequent @c MMR_EVENT_STATE,
 *  @c MMR_EVENT_ERROR, or @c MMR_EVENT_WARNING event.
 *
 *  The @c MMR_EVENT_METADATA, @c MMR_EVENT_OUTPUT, and @c MMR_EVENT_TRKPAR
 *  events each have multiple dictionaries, distinguished by an index stored in
 *  the @c #mmr_event_t @c details field. So, if you set the user data after
 *  receiving say, an @c MMR_EVENT_METADATA event with an index of 2, the same
 *  user data is returned only for other @c MMR_EVENT_METADATA events whose
 *  index is also 2.
 *
 *  The @c MMR_EVENT_OTHER event indicates that something has changed, but you
 *  can typically ignore this event. In any case, it's better to not attach user
 *  data to this type of event.
 *
 *  @param ctxt A context handle.
 *  @param usrdata A pointer to the user data to associate with the dictionary.
 *  @return Zero on success, or -1 if the event was an @c #MMR_EVENT_NONE or a
 *          deletion.
 */
int mmr_event_data_set( mmr_context_t *ctxt, void *usrdata );


/**
 *  @brief Wait until an event is available
 *
 *  @details Wait for an event. This function usually blocks until an event
 *  occurs, at which point it unblocks and you can call @c mmr_event_get() to
 *  get the event details.
 *
 *  Occasionally, @c mmr_event_wait() may unblock or not block at all even
 *  though no events are available. For example, suppose a track enters the
 *  playlist range but then exits soon afterwards. The @e mm-renderer service
 *  creates metadata for the track when it comes in range and this activity
 *  generates an event. If the track exits the playlist range before the
 *  application calls @c mmr_event_get(), the track's metadata and the
 *  corresponding event are deleted. In the subsequent call to @c
 *  mmr_event_get(), the function will return the @c #MMR_EVENT_NONE event.
 *
 *  Typically, you call @c mmr_event_wait() within an event-processing loop,
 *  right before you call @c mmr_event_get().
 *
 *  @param ctxt A context handle.
 *  @return Zero on success, or -1 on error (check @c errno).
 */
int mmr_event_wait( mmr_context_t *ctxt );

/**
 *  @brief Set a sigevent to deliver when a new event becomes available
 *
 *  @details Set a sigevent to deliver when a new @e mm-renderer event becomes
 *  available. The @c mmr_event_arm() function is helpful if your program
 *  already has an event-processing loop that uses signals or pulses as
 *  notifications and you simply want to add code that processes @e mm-renderer
 *  events. To do this, you must first call @c mmr_event_arm() to request
 *  notification of the next @e mm-renderer event. Then, in the new
 *  event-handling code, you must call @c mmr_event_get() to retrieve the event
 *  information.
 *
 *  Because @c mmr_event_arm() enables notification of only one event, you may
 *  want to call @c mmr_event_get() in a loop until it runs out of events to
 *  report and returns @c MMR_EVENT_NONE. Consider the following code snippet:
 *
 *  @code
 *  // Only arm after MMR_EVENT_NONE:
 *  int havemore = 1;
 *  do {
 *      event =  mmr__event_get(ctxt); // Error handling omitted
 *      if ( event->type != MMR_EVENT_NONE ) {
 *          process( event );
 *      } else {
 *          havemore = mmr_event_arm(ctxt, &sev); // Error handling omitted
 *      }
 *  } while ( havemore );
 *  // We've processed all pending events, sev is armed
 *  @endcode
 *
 *  If @e mm-renderer already has an event waiting when you call @c
 *  mmr_event_arm(), the function doesn't arm a sigevent but immediately returns
 *  a value greater than zero. If you receive such a value, you must call @c
 *  mmr_event_get() and process the event.
 *
 *  Occasionally, the @c mmr_event_get() function can't retrieve any meaningful
 *  event data and instead returns the @c #MMR_EVENT_NONE event. This can happen
 *  if the sigevent wasn't armed (because an event was already waiting) or if
 *  the sigevent was armed and then delivered by the system (because an event
 *  occurred after the last @c mmr_event_arm() call). For an example of a
 *  situation when @c #MMR_EVENT_NONE might be returned, see @c
 *  mmr_event_wait().
 *
 *  @param ctxt A context handle.
 *  @param sev A sigevent to send; set to NULL to disarm.
 *  @return A positive number if the sigevent isn't armed, 0 on success, or -1
 *          on failure (check @c errno).
 */
int mmr_event_arm( mmr_context_t *ctxt, struct sigevent const *sev );

/**
 *  @brief Find and split track or image metadata
 *
 *  @param md A dictionary object containing complete metadata
 *  @param type Track type ("video", "audio", "subpicture"), or "image" for
 *  embedded images
 *  @param idx Index to look for (0 for the first track or image)
 *  @return A new dictionary object containing the parsed properties on success,
 *          or NULL if not found or error (check @e errno). @e errno could be
 *          one of
 *          @c ENOENT - attribute not found,
 *          @c EINVAL - @c md or @c type is a null pointer or has an invalid
 *          value,
 *          @c ENOMEM - no memory
 */
strm_dict_t *mmr_metadata_split( strm_dict_t const *md, const char *type, unsigned idx );

/*@}*/

__END_DECLS

#endif

__SRCVERSION("$URL$ $Rev$")
