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


#if !defined(MM_RENDERER_TYPES_H_INCLUDED)
#define MM_RENDERER_TYPES_H_INCLUDED

#include <mm/mmsupport.h>

/** @file types.h
 *  mm-renderer API types
 *  @ingroup ClientAPI Client API
 */

#if !defined(__TYPES_H_INCLUDED)
#include <sys/types.h>
#endif

#if !defined(_STDINT_H_INCLUDED)
#include <stdint.h>
#endif

#if !defined(_LIMITS_H_INCLUDED)
#include <limits.h>
#endif


#if !defined(SYS_STRM_H_INCLUDED)
#include <sys/strm.h>
#endif

__BEGIN_DECLS

/**
 * @addtogroup ClientAPI Client API
 */
/*@{*/

/**
 * @brief Error codes set by Client API functions
 *
 * @details The enumerated type @c mm_error_code_t defines the error codes
 * returned by Client API functions.
 */
typedef enum mm_error_code {
    /** No error has occurred. This error code is used for the EOF event but is
        never returned as the error code from an API call.                   **/
	MMR_ERROR_NONE,

    /** An unexpected error. **/
	MMR_ERROR_UNKNOWN,

    /** An invalid parameter, such as an invalid output ID or a seek string
        that's incorrectly formatted or out of range.                        **/
	MMR_ERROR_INVALID_PARAMETER,

    /** An illegal operation given the context state, such as an attempt to play
        or seek while no input is attached, to change the playlist when playback
        was stopped, or to access the context after it's been destroyed.     **/
	MMR_ERROR_INVALID_STATE,

    /** An unrecognized input or output type or an out-of-range speed setting.
     **/
	MMR_ERROR_UNSUPPORTED_VALUE,

    /** An unrecognized data format. **/
	MMR_ERROR_UNSUPPORTED_MEDIA_TYPE,

    /** The file is DRM-protected and either it uses an unsupported DRM scheme
        or there's a DRM error not corresponding to any of the errors listed
        below.  **/
	MMR_ERROR_MEDIA_PROTECTED,

    /** An operation that is unsupported for the current piece of media being
        played. This error is returned if you try to seek or to
        set the playback speed on media that doesn't allow it, or you try to
        attach an output after attaching the input but the underlying media
        doesn't support that action sequence. **/
	MMR_ERROR_UNSUPPORTED_OPERATION,

    /** An I/O error at the source. **/
	MMR_ERROR_READ,

    /** An I/O error at the sink. **/
	MMR_ERROR_WRITE,

    /** @c mm-renderer can't open the source. **/
	MMR_ERROR_MEDIA_UNAVAILABLE,

    /** @c mm-renderer found corrupt data on the media. **/
	MMR_ERROR_MEDIA_CORRUPTED,

    /** @c mm-renderer can't write to the output (possibly because the output
        URL or type doesn't match any supported sink). **/
	MMR_ERROR_OUTPUT_UNAVAILABLE,

    /** Insufficient memory to perform the requested operation. **/
	MMR_ERROR_NO_MEMORY,

    /** A required resource such as an encoder or an output feed is presently
        unavailable. **/
	MMR_ERROR_RESOURCE_UNAVAILABLE,

    /** The client lacks the rights to play the file. **/
	MMR_ERROR_MEDIA_DRM_NO_RIGHTS,

	/** The DRM data store is corrupted. **/
	MMR_ERROR_DRM_CORRUPTED_DATA_STORE,

	/** A DRM output protection mismatch on an unspecified output. **/
	MMR_ERROR_DRM_OUTPUT_PROTECTION,

	/** A DRM output protection mismatch on an HDMI output. **/
	MMR_ERROR_DRM_OPL_HDMI,

	/** A DRM output protection mismatch on a DISPLAYPORT output. **/
	MMR_ERROR_DRM_OPL_DISPLAYPORT,

	/** A DRM output protection mismatch on a DVI output. **/
	MMR_ERROR_DRM_OPL_DVI,

	/** A DRM output protection mismatch on a video ANALOG output (for example,
        S-VIDEO, COMPOSITE, RGB, RGBHW, YPbPr). **/
	MMR_ERROR_DRM_OPL_ANALOG_VIDEO,

	/** A DRM output protection mismatch on an audio ANALOG output (for
     example, HEADPHONE, SPEAKER OUT). **/
	MMR_ERROR_DRM_OPL_ANALOG_AUDIO,

	/** A DRM output protection mismatch on a TOSLINK output. **/
	MMR_ERROR_DRM_OPL_TOSLINK,

	/** A DRM output protection mismatch on an S/PDIF output. **/
	MMR_ERROR_DRM_OPL_SPDIF,

	/** A DRM output protection mismatch on a BLUETOOTH output. **/
	MMR_ERROR_DRM_OPL_BLUETOOTH,

	/** A DRM output protection mismatch on a WIRELESSHD output. **/
	MMR_ERROR_DRM_OPL_WIRELESSHD,

	/** A DRM output protection mismatch on a WIFI DIRECT output (for example,
     Wireless Display products such as WiDi and Miracast). **/
	MMR_ERROR_DRM_OPL_WIFI_DIRECT,

	/* Identifier marking the end-of-range for @c MMR_ERROR_DRM_OPL_* values.
       Internal use only - do not use.
     **/
	MMR_ERROR_DRM_OPL_RESERVED_LAST = MMR_ERROR_DRM_OPL_WIRELESSHD + 4,

	/** A license for the DRM file was found but has expired, either because
     the play count has been depleted or the end time has passed. **/
	MMR_ERROR_MEDIA_DRM_EXPIRED_LICENSE,

	/** A playback permission error (for example, user prohibition, region
     mismatch). **/
	MMR_ERROR_PERMISSION,

	/** Playback interrupted by a failed API call.  This error code is used for
        an event but never returned as the error code from an API call. **/
	MMR_ERROR_COMMAND_FAILED,

	/** An end-of-list identifier. Also indicates the number of distinct error
     codes. **/
	MMR_ERROR_COUNT
} mm_error_code_t;

/**
 * @brief The mm-renderer error information
 *
 * @details The structure @c mmr_error_info_t contains error information
 * generated by @c mm-renderer functions. Use the function @c mmr_error_info()
 * to retrieve error information for a particular context and function call.
 *
 * This multifield structure allows plugins to return protocol- or API-specific
 * error information in addition to the MMR error code. The @c extra_type string
 * is a tag that specifies how to interpret the @c extra_value and @c extra_text
 * fields.
 *
 * The values of @c extra_type currently supported are:
 *
 * - an empty string (""): @c extra_value is set to 0, and the @c extra_text is
 *   usually empty, but possibly contains some descriptive text.
 * - "errno": @c extra_value is set to an @c errno value, and @c extra_text is
 *   usually the result of @c strerror(extra_value), but may contain something
 *   more descriptive.
 * - "mmf": @c extra_value is an MMF-specific error code (which is not a valid
 *   @c errno), and @c extra_text is usually empty, but possibly contains
 *   something more descriptive.
 * - "http": @c extra_value is an HTTP response code, and @c extra_text is an
 *   HTTP server response.
 * - "libcurl": @c extra_value is a @c libcurl error code (but not @c
 *   CURLE_HTTP_RETURNED_ERROR), and @c extra_text is the corresponding @c
 *   libcurl error message.
 *
 */
typedef struct mmr_error_info {
    /** One of the @c #mm_error_code_t constants. **/
    uint32_t error_code;
    /** A short string identifying the API or protocol that defines the meaning
     *  of @c extra_value, such as "errno", "http", or "mmf". **/
    char extra_type[ 20 ];
    /** An error number according to @c extra_type. **/
    int64_t extra_value;
    /** Free-form text describing the error. This may or may not have a format
     *  formally defined by a specification. For example, when @c extra_type is
     *  "http", this field contains an HTTP server response string. **/
	char extra_text[ 256 ];
} mmr_error_info_t;

/*@}*/

/*
 * @brief Information about a client.
 */
typedef struct mmr_client_info {
	pid_t creator;
	int creator_nd;
	uid_t uid;
	gid_t gid;
	unsigned nsupp_gids;
	const gid_t *supp_gids;
} mmr_client_info_t;



__END_DECLS

#endif

__SRCVERSION("$URL$ $Rev$")
