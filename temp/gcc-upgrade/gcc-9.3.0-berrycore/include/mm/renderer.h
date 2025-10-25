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


#if !defined(MM_RENDERER_H_INCLUDED)
#define MM_RENDERER_H_INCLUDED

/** @file renderer.h
 *
 * The multimedia renderer Client API exposes the functions you can use to
 * connect to @c mm-renderer, create contexts, attach inputs and outputs, and
 * manage playback.
 *
 * The Client API lets you manage the flow of media content with functions for
 * setting the input, for directing the output to an audio or video device or to
 * a file, and for starting or stopping the media flow. You can also define
 * parameters for inputs, outputs, contexts, and tracks. These parameters are
 * specified with dictionary objects that are passed in to API calls (see the
 * Dictionary Object API for details on dictionary objects).
 *
 * The header file that defines the Client API functions, @c renderer.h, is
 * located in @c /usr/include/mm/. The header file that defines the enumerated
 * error codes and the Client API data types, @c types.h, is located in @c
 * /usr/include/mm/renderer/.
 *
 */

/**
 * @mainpage Multimedia Renderer Client API
 *
 * @section mmrenderer_intro mm-renderer Introduction
 *
 * The multimedia rendering component, @c mm-renderer, allows multimedia
 * applications to request and control the playback of audio and video media
 * from files and devices.
 *
 * The @c mm-renderer service provides mechanisms for:
 *
 * - specifying the set of media to play
 * - issuing playback control commands
 * - retrieving the current playback status
 * - requesting notifications when the status changes
 * - providing dynamic metadata (such as position in a track or playlist) for
 *   some media content
 *
 * @note The BlackBerry 10 Device Simulator doesn't include any codecs other
 * than those that support @c .wav files. To play media files of other formats
 * (for example, @c .mp3, @c .aac), you must use real hardware.
 *
 * The multimedia renderer API allows you to control media playback and
 * recording, and to receive events to monitor your media operations.
 *
 * When performing permission-sensitive operations such as opening files, the
 * multimedia renderer uses the client's user ID and group IDs.
 */

#if defined(MM_RENDERER_PLUGIN_HEADERS_INCLUDED)
#error "Please don't mix plugin headers with <mm/renderer.h>"
#endif

#if !defined(MM_RENDERER_TYPES_H_INCLUDED)
#include <mm/renderer/types.h>
#endif

__BEGIN_DECLS

/**
 * @addtogroup ClientAPI Client API
 */
/*@{*/

/**
 *  @brief The @c mm-renderer connection handle type
 *
 *  @details The structure @c #mmr_connection_t is a private data type
 *  representing the connection to @c mm-renderer.
 */
typedef struct mmr_connection mmr_connection_t;

/**
 *  @brief The @c mm-renderer context handle type
 *
 *  @details The structure @c mmr_context_t is a private data type representing
 *  a context handle.
 *
 *  Your application can monitor changes to the context state by using the Event
 *  API functions from events.h.
 *
 */
typedef struct mmr_context mmr_context_t;

/**
 *  @brief Connect to @c mm-renderer
 *
 *  @details Connect to @c mm-renderer, using the specified name if @c name
 *  isn't @c NULL, returning a valid connection handle on success.
 *
 *  @param name The name of the @c mm-renderer service to connect to (use NULL
 *              for the default service).
 *
 *  @return A connection handle, or NULL on failure (@e errno is set).
 */
mmr_connection_t *mmr_connect( const char *name );

/**
 *  @brief Disconnect from @c mm-renderer
 *
 *  @details Disconnect from @c mm-renderer. Close any existing context handles
 *  associated with the connection being closed and free their memory.
 *
 *  Each context handle is associated with the connection handle used to create
 *  it. This means that if you have multiple connections to @c mm-renderer,
 *  calling @c mmr_disconnect() to close one of those connections doesn't
 *  necessarily close all your context handles.
 *
 *  You shouldn't use these handles again, not even in an API call to close
 *  them. If any of them are primary handles, their contexts also get destroyed.
 *
 *  The same happens in terms of contexts being destroyed if your application
 *  exits without explicitly disconnecting. This means you don't have to clean
 *  up old contexts when you restart the application.
 *
 *  This function is asynchronous, and may return before the destruction of any
 *  related contexts is complete. Calling @c mmr_context_destroy() for each
 *  context associated with the connection ensures that the context is destroyed
 *  before returning.
 *
 *  @param connection An @c mm-renderer connection handle.
 */
void mmr_disconnect( mmr_connection_t *connection );

/**
 *  @brief Open an existing context
 *
 *  @details Open a handle to an existing context. The handle returned by this
 *  function is called a @e secondary handle.
 *
 *  The @c mm-renderer service allows you to open as many secondary handles as
 *  you like. If the context is destroyed or the primary handle is closed, the
 *  secondary handles are still valid, but they should be closed; you can pass
 *  them to other API calls, but those calls will fail.
 *
 *  To avoid memory leaks, you must close every handle opened with @c
 *  mmr_context_open(), either explicitly by calling one of the following:
 *
 *  - @c mmr_context_close()
 *  - @c mmr_context_destroy()
 *  - @c mmr_disconnect()
 *
 *  or implicitly by terminating the process.
 *
 *  @param connection An @c mm-renderer connection handle
 *  @param name       The context name.
 *
 *  @return A handle on success, or a null pointer on failure (check @e errno).
 */
mmr_context_t *mmr_context_open( mmr_connection_t *connection, const char *name );

/**
 *  @brief Create a context
 *
 *  @details Create and open a new context with the specified name. Fail if a
 *  context with that name already exists. The name must be a valid filename and
 *  will show up in the pathname space, with its file mode flags set based on
 *  the @c mode argument. Note that there's not a direct mapping between the
 *  value given in @c mode and the file permissions assigned to the context
 *  directory. The description of @c mode explains how permissions specified in
 *  the function call are interpreted.
 *
 * When successful, the function returns a handle, called the @e primary handle,
 * for accessing the newly created context. You can create any number of
 * secondary handles by calling @c mmr_context_open(), passing the same @c
 * name used to create the primary handle.
 *
 * To avoid memory leaks, every handle opened with @c mmr_context_create() needs
 * to be closed, either explicitly through an API call or implicitly by
 * terminating the process. When you close a primary handle, @c mm-renderer
 * destroys the associated context. At this point, you can no longer use any
 * secondary handles to that context, so you must close those handles by calling
 * @c mmr_context_close() on each one.
 *
 *  @param connection An @c mm-renderer connection handle.
 *  @param name       The name of the context.  This must be a valid filename
 *                    that is unique system wide.
 *  @param flags      Must be zero.  No flags are defined for now.
 *  @param mode       Permission flags controlling which processes can access
 *                    the context. These flags are specified in a standard
 *                    POSIX permissions bitfield.
 *                    <br>
 *                    The @c w bits control which processes can open secondary
 *                    handles to access the context. The @c r and @c x bits
 *                    provide access to @c mm-renderer events related to the
 *                    context.
 *                    <br>
 *                    In this bitfield, the user permissions apply to the caller
 *                    and to any process with the same effective user ID (@c
 *                    euid). You must set these permissions appropriately to
 *                    grant your application (or other applications running with
 *                    the same @c euid) sufficient access to the context being
 *                    created. The group permissions apply to processes with an
 *                    effective group ID (@c egid) or a supplementary group ID
 *                    matching the caller's @c egid. The other permissions apply
 *                    to all other processes.
 *
 *  @return A handle on success, or a null pointer on failure (check @e errno).
 */
mmr_context_t *mmr_context_create( mmr_connection_t *connection, const char *name, unsigned flags, mode_t mode );


/**
 *  @brief Destroy a context
 *
 *  @details Destroy the context the handle refers to and close the handle.
 *  Implicitly stop any playback and detach any inputs or outputs.
 *
 *  In addition to explicitly calling @c mmr_context_destroy() with a primary or
 *  secondary handle, a context is also destroyed when the primary handle is
 *  closed for any reason, including:
 *
 *  - calling @c mmr_context_close() using the primary handle
 *  - calling @c mmr_disconnect() with the connection that the primary handle is
 *    associated with
 *  - terminating the process that has the primary handle
 *
 *  If any other handles to this context still exist, attempts to use them will
 *  fail. At this point, you should close those handles by calling @c
 *  mmr_context_close() on each one, disconnecting by calling @c
 *  mmr_disconnect(), or terminating the process.
 *
 *  @param ctxt A context handle.
 *
 *  @return Zero on success, -1 on failure (check @e errno). The handle becomes
 *          invalid either way.
 */
int mmr_context_destroy( mmr_context_t *ctxt );

/**
 *  @brief Close a context
 *
 *  @details Close and invalidate the context handle. The handle is always
 *  closed and becomes invalid, even if the function returns an error.
 *
 *  If a primary handle (which was returned by @c mmr_context_create()) is
 *  passed in, the associated context is destroyed, and the function fails and
 *  sets the global variable @e errno to @c EPERM.
 *
 *  @param ctxt A context handle.
 *
 *  @return Zero on success, -1 on failure (check errno). The handle becomes
 *          invalid either way.
 */
int mmr_context_close( mmr_context_t *ctxt );

/**
 *  @brief Get the context path
 *
 *  @details Get the context path. Builds the full path to the context PPS
 *  directory. If the function fails, or the buffer is too small and @c len is
 *  nonzero, @c buf is set to an empty string.
 *
 *  @param ctxt  A context handle
 *  @param buf   The buffer to store the path in (not used if len==0)
 *  @param len   The length of the buffer
 *  @return The full length of the path (not counting the null terminator),
 *          or -1 on on failure (use @c mmr_error_info()).
 */
ssize_t mmr_context_path( mmr_context_t *ctxt, char buf[], size_t len );

/**
 *  @brief Get error information
 *
 *  @details Return error information. Return a pointer to an internal buffer
 *  containing error information about the most recent API call made using the
 *  same context handle. The pointer and the error information it points to are
 *  valid only until another API call is made.
 *
 *  @param ctxt A context handle.
 *  @return Pointer to error information, or a null pointer if the most recent
 *  API call succeeded.
 */
const mmr_error_info_t *mmr_error_info( mmr_context_t *ctxt );

/**
 *  @brief Set context parameters
 *
 *  @details Set parameters associated with the specified context. BlackBerry 10
 *  OS supports the following parameter:
 *
 *  @b updateinterval
 *
 *  Allows an application to request a particular frequency in status updates
 *  from @c mm-renderer. How accurately this delivery reflects the @e
 *  updateinterval setting depends on the plugin handling the media flow.
 *  Currently, this parameter is supported only for the MMF audio/video player
 *  routing plugin. The default update interval is 1000 ms, but your client code
 *  should dynamically adjust this parameter based on the application's state,
 *  such as fullscreen versus minimized versus when the screen is off.
 *
 *  BlackBerry 10 supports the following HTTP input parameters that map to @c
 *  libcurl options:
 *
 * - @c OPT_CONNECTTIMEOUT_MS
 * - @c OPT_LOW_SPEED_LIMIT
 * - @c OPT_LOW_SPEED_TIME
 * - @c OPT_USERAGENT
 * - @c OPT_USERNAME
 * - @c OPT_PASSWORD
 * - @c OPT_PROXYUSERNAME
 * - @c OPT_PROXYPASSWORD
 * - @c OPT_COOKIE
 * - @c OPT_COOKIEFILE
 * - @c OPT_COOKIEJAR
 * - @c OPT_COOKIESESSION
 * - @c OPT_CAINFO
 * - @c OPT_CAPATH
 * - @c OPT_SSL_VERIFYPEER
 * - @c OPT_SSL_VERIFYHOST
 * - @c OPT_PROXY
 * - @c OPT_NOPROXY
 * - @c OPT_HTTPPROXYTUNNEL
 * - @c OPT_PROXYPORT
 * - @c OPT_PROXYTYPE
 * - @c OPT_PROXYAUTH
 * - @c OPT_HTTPAUTH
 * - @c OPT_HTTPHEADER
 * - @c OPT_DNSCACHETIMEOUT
 *
 * Blackberry 10 OS supports the following parameters that map to socket options
 * (see the @c getsockopt() function in the @e C @e Library @e Reference for
 * more information):
 *
 * - @c OPT_SO_RCVBUF
 * - @c OPT_SO_SNDBUF
 *
 *  @param ctxt A context handle.
 *  @param parms A dictionary containing the context parameters to set. Any
 *               previous parameters are overridden. Do not use or destroy the
 *               dictionary after passing it to this function, even if the call
 *               fails.
 *  @return Zero on success, -1 on failure (use @c mmr_error_info()).
 */
int mmr_context_parameters( mmr_context_t *ctxt, strm_dict_t *parms );

/**
 *  @brief Attach an input
 *
 *  @details Attach an input file, device, or playlist. If the context already
 *  has an input, detach it first.
 *
 *  The input type is one of:
 *
 *  - @c track - This input type tells @e mm-renderer that the input URL refers
 *               to a track (that is, a media file or stream). For this input
 *               type, @e mm-renderer uses a simple interface with no playlist
 *               window, no track parameters or track metadata, and positions
 *               expressed as a single number.
 *  - @c playlist - This input type tells @e mm-renderer that the input URL
 *                  refers to a playlist file. For this input type, @e
 *                  mm-renderer uses a rich interface with a playlist window,
 *                  track parameters and track metadata, and positions expressed
 *                  as a pair of numbers.
 *  - @c autolist - This input type tells @e mm-renderer that the app wants the
 *                  same rich interface that the @c playlist type provides.
 *                  Currently, the input URL has to refer to a track (that is a
 *                  media file or a stream) rather than an actual playlist file,
 *                  but the interface behaves as if that track is the only entry
 *                  in a playlist.
 *
 *  The input type determines how @c mm-renderer responds to certain playback
 *  requests. For example, when seeking to track positions using @c mmr_seek(),
 *  you must specify the desired position differently for each of the supported
 *  input types. Also, @c mmr_list_change() applies to "playlist" only.
 *
 *  Currently, valid input URLs for the "track" or "autolist" input types are:
 *
 *  - A URL starting with @c http:. HLS (HTTP Live Streaming) is supported just
 *    as any HTTP stream, with the following caveats:
 *    - For HLS realtime broadcast the seek operation is disabled. Therefore, if
 *      your application issues a seek command it will fail.
 *    - Pause (play speed of 0) is supported but the playback may jump forward
 *      when resumed because the current stream may have become unavailable.
 *    - For HLS Video on Demand, the seek operation places the play position at
 *      the start of the video chunk that is closest to the requested time. The
 *      pause operation works as expected.
 *
 *    The @e mm-renderer service supports HLS version 3, with media segments
 *    encoded as follows:
 *    - Transport stream MPEG2-TS with H.264 Video, with either MP3 or AAC
 *      Audio (when the appropriate codecs are available on the platform)
 *    - Video only and audio only when embedded in the MPEG2-TS stream
 *
 *      @note To offer secure playback of video and audio content from HTTP Live
 *      Streaming and other HTTP sources, @c mm-renderer supports cookies, SSL,
 *      and authentication. The client must provide the necessary information
 *      (for example, username and password) using the @c OPT_* context
 *      parameters to use these security features.
 *
 *  - A @c file: or @c http: prefix. You can play audio and video files through
 *    @c mm-renderer.
 *  - A pathname starting with "/".
 *  - A @c file2b: URL containing the full path name of a dynamically growing
 *    file (a progressive download). Not all formats are supported. If parsing
 *    the file requires knowing the file size or reading more data than
 *    currently in the file, the input attachment operation may fail. If it does
 *    succeed, any attempt to play from beyond the end of file will cause the
 *    playback to underrun. Your application must pay attention to the
 *    buffering status and appropriately present the state to the user,
 *    depending on whether the download is happening at the time.
 *
 *  - An @c audio: URL naming an audio capture device (microphone) whose name is
 *    defined by the @c AUDIO_DEVICE_NAMES set of string constants, which is
 *    listed in the Audio Manager Library reference. The URL can specify any of
 *    the options supported for @c snd: URLs, for example:
 *    <tt>audio:voice?nchan=1&frate=44100&depth=16</tt>
 *
 *    - Supported options include:
 *      - frate - the sampling rate, in Hertz
 *      - frag_ms - the fragment size, in milliseconds
 *      - nchan - the number of channels (1 for mono, 2 for stereo)
 *      - depth - the number of bits per sample (for example, 16)
 *      - bsize - the preferred read size, in bytes
 *
 *    Currently, this URL format works only with the "file" output type.
 *    Client applications should use @c audio:default to specify automated
 *    routing for the audio stream unless there's a good reason to use one
 *    particular device. When a non-default device is named, the audio stream
 *    routing depends solely on that device. For instance, the removal of the
 *    device could result in no audio being output or an error returned to the
 *    client.
 *
 *    On the BlackBerry 10 OS, use @c audio: where possible rather than @c
 *    snd.
 *
 *  - An @c snd: URL targeting an audio capture device (microphone) whose device
 *    file is located in @c /dev/snd. The URL can specify device configuration
 *    options in a comma-separated list, as follows:
 *    <tt>snd:/dev/snd/pcmPreferredc?frate=44100&nchan=2</tt>
 *
 *    - Supported options include:
 *      - frate - the sampling rate, in Hertz
 *      - frag_ms - the fragment size, in milliseconds
 *      - nchan - the number of channels (1 for mono, 2 for stereo)
 *      - depth - the number of bits per sample (for example, 16)
 *      - bsize - the preferred read size, in bytes
 *
 *    Currently, this URL format works only with the "file" output type. The
 *    resulting behavior is identical to that for the audio: URL format except
 *    that the Audio Manager is bypassed, which means you can't provide hints
 *    such as audio type to control audio routing.
 *
 *  Valid input URLs for the "playlist" input type are:
 *
 *  - A full pathname of an M3U playlist file, with or without a @c file: or
 *    @c http: prefix
 *  - An SQL URL in the form <tt>sql:database?query=query</tt>, where:
 *    - @e database is the full path to the database file
 *    - @e query must return a single column containing URLs in a form
 *      acceptable for the "track" input type
 *    - any special characters in the query must be URL-encoded (for example,
 *      spaces encoded as @c %20, and so on)
 *
 *  @note Not all defined audio devices may work with the current application.
 *  It's the client's responsibility to determine if a particular device is
 *  supported before trying to use it. See the @c mmr_output_attach() example
 *  for a demo of how to check if an audio device is supported before
 *  configuring the audio routing.
 *
 *  @param ctxt A context handle
 *  @param url The URL of the new input
 *  @param type The input type.
 *
 *  @return Zero on success, -1 on failure (use @c mmr_error_info()).
 */
int mmr_input_attach( mmr_context_t *ctxt, const char *url, const char *type );

/**
 *  @brief Detach an input
 *
 *  @details Detach an input. If the context is playing, stop it. If there is no
 *  input already, this is a no-op.
 *
 *  @param ctxt A context handle
 *  @return Zero on success, -1 on failure (use @c mmr_error_info()).
 */
int mmr_input_detach( mmr_context_t *ctxt );

/**
 *  @brief Set input parameters
 *
 *  @details Set parameters associated with the attached input media.
 *
 * The input type and the URL format determine which input parameters you can
 * set. Some parameters must be set before the input is attached, because
 * setting them after attaching the input has no effect. All input parameters
 * are cleared when the input is detached, whether explicitly through a call to
 * @c mmr_input_detach() or implicitly when @c mmr_input_attach() is called to
 * attach a new input, which causes @c mm-renderer to detach the current input.
 *
 * In the case where closed captioning data from an external file is used, the
 * @c strm_dict_t object must contain a "subpicture_url" entry with its value
 * set to the path of the file. Otherwise, @e mm-renderer will look for embedded
 * subtitles in the main video file. This parameter must be set before the main
 * input is attached, as you can't switch between internal and embedded
 * "subpicture_url"s. However, you can set this parameter to a different URL
 * later to select a different file (for example, a different language). The new
 * file must be the same format as the initial file.
 *
 * Some @c mm-renderer plugins don't return errors when you provide unacceptable
 * values for input parameters. Some input parameters control internal values,
 * such as volume, repeat, update interval, and so on.
 *
 * If you provide an invalid value in the dictionary, @e mm-renderer may remove
 * it and apply its internal default (for example, 100% for volume, none for
 * repeat).  Alternatively, @e mm-renderer could replace the invalid value with
 * the previous value of the parameter, and keep the internal value unchanged.
 * To see which values were accepted or changed, client applications can examine
 * the parameters that the Event API returned.
 *
 * @note An individual playlist item isn't considered an input but the whole
 * playlist is.  To set parameters for individual playlist items, you must use
 * @c mmr_track_parameters().
 *
 * When your input has the "playlist" type, input parameters apply to the
 * playlist and not to the individual tracks; use track parameters to specify
 * parameters for tracks.
 *
 * When your input has the "autolist" type, any input parameters you specified
 * before attaching the input become the track parameters. After the input is
 * attached, use track parameters, just like you would for a real playlist.
 *
 * When your input has the "track" type, the input parameters apply to the
 * track. Do not use @c mmr_track_parameters() with the "track" type.
 *
 * The "playlist" and "autolist" input types support the following parameter:
 *
 * @b repeat
 *
 * Specifies whether to repeat a track or tracks. Acceptable values are "none"
 * (default), "track", or "all".
 *
 * When using the "autolist" or "track" input types with a URL that starts with
 * @c audio:, you can set one of the following two parameters:
 *
 * @b audio_type
 *
 * Specifies the audio type to use with the track. The audio type is specified
 * as a string that's set to one of the audio types defined by @c
 * AUDIO_TYPE_NAMES, which is documented in the Audio Manager Library reference.
 * Acceptable values include "multimedia" and "notification"; consult the Audio
 * Manager for the complete list of defined audio types and their meanings.
 *
 * This parameter provides a shortcut for setting the audio type, thereby
 * simplifying your client code. You can use this parameter instead of using
 * the Audio Manager API to obtain an audio manager handle, and then passing
 * that handle to @e mm-renderer as the "audioman_handle" parameter.
 *
 * @b audioman_handle
 *
 * Associate an audio manager handle with the audio stream that the current
 * context manages. To obtain a value for this parameter, call the @c
 * audio_manager_get_handle() API function and pass in the desired audio type.
 *
 * You can then use this handle to change the audio type and other audio stream
 * characteristics through the Audio Manager API. For more information, refer to
 * the audio routing functions described in the Audio Manager Library reference.
 *
 * When the input URL starts with @c http: or @c https:, you can set the
 * following parameters that map to @c libcurl options:
 * - @c OPT_VERBOSE
 * - @c OPT_CONNECTTIMEOUT_MS
 * - @c OPT_LOW_SPEED_LIMIT
 * - @c OPT_LOW_SPEED_TIME
 * - @c OPT_USERAGENT
 * - @c OPT_USERNAME
 * - @c OPT_PASSWORD
 * - @c OPT_PROXYUSERNAME
 * - @c OPT_PROXYPASSWORD
 * - @c OPT_COOKIE
 * - @c OPT_COOKIEFILE
 * - @c OPT_COOKIEJAR
 * - @c OPT_COOKIESESSION
 * - @c OPT_CAINFO
 * - @c OPT_CAPATH
 * - @c OPT_SSL_VERIFYPEER
 * - @c OPT_SSL_VERIFYHOST
 * - @c OPT_PROXY
 * - @c OPT_NOPROXY
 * - @c OPT_HTTPPROXYTUNNEL
 * - @c OPT_PROXYPORT
 * - @c OPT_PROXYTYPE
 * - @c OPT_PROXYAUTH
 * - @c OPT_HTTPAUTH
 * - @c OPT_HTTPHEADER
 * - @c OPT_DNSCACHETIMEOUT
 *
 * @note When a track is played, it has access to its track parameters and the
 * context parameters. For any @c OPT_ parameters that exist in both the context
 * and track parameters, the track parameter is used.
 *
 *  @param ctxt A context handle.
 *  @param parms A dictionary containing the input parameters to set (must not
 *               be NULL). Any previous parameters are overridden. Do not use or
 *               destroy the dictionary after passing it to this function, even
 *               if the call fails.
 *  @return Zero on success, -1 on failure (use @c mmr_error_info()).
 */
int mmr_input_parameters( mmr_context_t *ctxt, strm_dict_t *parms );

/**
 *  @brief Attach an output
 *
 *  @details Attach an output and return its output ID (a non-negative integer,
 *  unique for this context). An output can be an audio or video device, or a
 *  file. The types of outputs attached to a context may affect the set of
 *  operations that the context will allow. For instance, when "playing" to a
 *  file, seeking or trick play may not be supported.
 *
 *  Attaching multiple outputs of the same type is not supported. Attaching or
 *  detaching outputs while the context has an input is not supported, either.
 *
 *  To set up a video with closed captions, you need to attach two outputs to
 *  the context, one of the "video" type and the other of the "subpicture" type,
 *  where the subpicture window is positioned on top of the output window. The
 *  captions are sent to the subpicture output, which allows the closed caption
 *  text to be seen in front of the video, which can still be seen through the
 *  transparent background of the subpicture.
 *
 *  Valid URLs for the "audio" output type are in one of the following forms:
 *
 *  - @c audio:name, where @e name is one of the audio device names defined by
 *  the @c AUDIO_DEVICE_NAMES set of string constants, which is listed in the
 *  Audio Manager Library reference.
 *
 *  - @c snd:device, where @e device is the path of an audio output device, such
 *  as @c /dev/snd/pcmPreferredp. This URL format produces behavior similar to
 *  the @c audio: format, except that the Audio Manager is bypassed and so you
 *  can't provide hints such as the audio type to control audio routing.
 *
 *  The @c mm-renderer service opens the device named in the URL. Client
 *  applications can use @c audio:default to specify automated routing for the
 *  audio stream. When a non-default device is named, the audio stream routing
 *  depends solely on that device. For instance, the removal of the device could
 *  result in no audio being output, or an error returned to the client.
 *
 *  @note Not all defined audio devices may work with the current application.
 *  It is the client's responsibility to determine if a particular device is
 *  supported before trying to use it.
 *
 *  Valid output URLs for the "video" and "subpicture" output types are of the
 *  following form:
 *
 *  @c screen:?wingrp=window_group&winid=window_id&nodstviewport=1&initflags=invisible
 *
 *  In the video URL:
 *
 *  - @e window_group is the window group name of the application's top-level
 *    window
 *  - @e window_id is the window ID for the window where the video output will
 *    be rendered
 *  - The parameter setting @c nodstviewport=1 is optional, and forces @c
 *    mm-renderer to never directly modify the destination viewport of the
 *    window. This avoids conflicts between simultaneous application
 *    manipulation and @c mm-renderer manipulation of the destination viewport.
 *  - The parameter setting @c initflags=invisible is optional, and causes the
 *    window to be invisible upon creation. This flag allows you to adjust
 *    window properties such as size, position, and z-order before making it
 *    visible.
 *
 *  Valid output URLs for the "file" output type are of the form @c file:path,
 *  where @e path is the full filepath. The @c file: prefix is optional. The
 *  following file types (and their extensions, which must be present in the
 *  URL) are supported:
 *
 *  - Waveform Audio File Format (.wav)
 *  - MPEG 4 Audio (.m4a)
 *  - Adaptive Multi-Rate (.amr)
 *  - 3GPP file format (.3gp)
 *  - Adaptive Multi-Rate Wideband (.awb)
 *  - Qualcomm PureVoice (.qcp)
 *
 *  @e mm-renderer will reject any @c file: output URLs that do not contain one
 *  of the listed file extensions.
 *
 *  @note When using the BlackBerry 10 Device Simulator, the output file must be
 *  a @c .wav file. To test other output file formats, you must use real
 *  hardware.
 *
 *  @param ctxt A context handle.
 *  @param url The URL of the new output.
 *  @param type The output type. Possible values are "audio", "video",
 *  "subpicture" and "file".
 *  @return A non-negative output ID on success, -1 on failure (use @c
 *  mmr_error_info()).
 */
int mmr_output_attach( mmr_context_t *ctxt, const char *url, const char *type );

/**
 *  @brief Detach an output
 *
 *  @details Detach the specified output.
 *
 *  @param ctxt A context handle.
 *  @param output_id An output ID.
 *  @return Zero on success, -1 on failure (use @c mmr_error_info()).
 */
int mmr_output_detach( mmr_context_t *ctxt, unsigned output_id );

/**
 *  @brief Set output parameters
 *
 *  @details
 *
 *  Set parameters for an output device. The acceptable parameter values depend
 *  on the plugins loaded for the attached output and the attached input, if
 *  any. Unlike input and track parameters, the values of output parameters
 *  won't be changed by @c mm-renderer plugins. If the provided values aren't
 *  supported for the current output and input combination, the function call
 *  fails.
 *
 *  The output type determines which output parameters you can set. At present,
 *  there are no output parameters for the "file" output type.
 *
 *  For the "audio" output type, the following parameter is available for any
 *  URL format:
 *
 *  @b volume
 *
 *  Set the volume for this audio stream. The volume must be an integer in
 *  decimal format in the range of 0 to 100.
 *
 *  When using the "audio" output type with a URL that starts with @c audio:,
 *  you can set one of the following two parameters:
 *
 *  @b audio_type
 *
 *  Specifies the audio type to use with the track. The audio type is specified
 *  as a string that's set to one of the audio types defined by @c
 *  AUDIO_TYPE_NAMES, which is documented in the Audio Manager Library
 *  reference. Acceptable values include "multimedia" and "notification";
 *  consult the Audio Manager for the complete list of defined audio types and
 *  their meanings.
 *
 *  This parameter provides a shortcut for setting the audio type, thereby
 *  simplifying your client code. You can use this parameter instead of using
 *  the Audio Manager API to obtain an audio manager handle, and then using that
 *  handle to set the audio type.
 *
 *  @b audioman_handle
 *
 *  Associate an audio manager handle with the audio stream that the current
 *  context manages. To obtain a value for this parameter, call the
 *  @c audio_manager_get_handle() API function and pass in the desired audio
 *  type.
 *
 *  You can then use this handle to change the audio type and other audio stream
 *  characteristics through the Audio Manager API. For more information, refer
 *  to the audio routing functions described in the Audio Manager Library
 *  reference.
 *
 *  For the "video" output type, your application should modify the output
 *  window directly by using the libscreen library, as demonstrated in "Managing
 *  video windows".
 *
 *  @note The legacy video output parameters @c video_dest_*, @c video_src_*,
 *  and @c video_clip_* have been deprecated. Using @c libscreen is the proper
 *  way to configure video output.
 *
 *  The @c mmr_output_attach() function sets the parameters @e url and @e type.
 *  Some plugins allow you to modify the URL with @c mmr_output_parameters().
 *  For instance, you can ask @c mm-renderer to switch output devices by calling
 *  @c mmr_output_parameters() with a new URL in the parameters.
 *
 *  @param ctxt A context handle.
 *  @param output_id An output ID.
 *  @param parms A dictionary object containing the parameters to set (must not
 *               be NULL). Any previous parameters are overridden. The @c
 *               strm_dict_t object becomes API property after this call, even
 *               if the call fails. You should not use or destroy the dictionary
 *               after passing it to this function.
 *  @return Zero on success, -1 on failure (use @c mmr_error_info()).
 */
int mmr_output_parameters( mmr_context_t *ctxt, unsigned output_id, strm_dict_t *parms );

/**
 *  @brief Start playing
 *
 *  @details Start playing. A no-op if already playing.
 *
 *  When @c mm-renderer is playing media, you can adjust the play speed, seek to
 *  another position, change playlists, or stop playback.
 *
 *  @param ctxt A context handle.
 *  @return Zero on success, -1 on failure (use @c mmr_error_info()).
 */
int mmr_play( mmr_context_t *ctxt );

/**
 *  @brief Stop playing
 *
 *  @details Stop playing. A no-op if already stopped. Depending on the input
 *  media, stopping the playback may cause the playing position to change or
 *  even become indeterminate. Unless you know the behaviour of the media being
 *  played, use the function @c mmr_seek() to seek to a known position before
 *  restarting the playback.
 *
 *  When the playback is explicitly stopped using @c mmr_stop(), a @c
 *  MMR_EVENT_STATE event is generated and the context state is set to @c
 *  MMR_STATE_STOPPED.
 *
 *  @param ctxt A context handle.
 *  @return Zero on success, -1 on failure (use @c mmr_error_info()).
 */
int mmr_stop( mmr_context_t *ctxt );

/**
 *  @brief Seek to a position
 *
 *  @details Seek to a known position in the currently attached input. The
 *  required format of the position string depends on the type of the attached
 *  input.
 *
 *  For the track type, the position is simply the number of milliseconds from
 *  the start of the track (for example, "2500").
 *
 *  For the @e playlist and @e autolist types, the position must be specified as
 *  two numbers separated by a colon (for example, "2:1200"), where the first
 *  number is the track index within the playlist and the second number is the
 *  number of milliseconds from the start of the track. The first number must be
 *  1 for an autolist input.
 *
 *  @param ctxt A context handle.
 *  @param position The position to seek to, in a media-specific format.
 *  @return Zero on success, -1 on failure (use @c mmr_error_info()).
 */
int mmr_seek( mmr_context_t *ctxt, const char *position );

/**
 *  @brief Set the play speed, in units of 1/1000 of normal speed
 *
 *  @details Set the play speed, in units of 1/1000 of normal speed. If the
 *  context is playing (including if it's paused), the new speed is applied
 *  immediately; otherwise it's stored in the context and applied the next time
 *  @c mmr_play() is called.
 *
 *  Use a speed of zero (0) to pause playback. Depending on the input media,
 *  speeds other than the normal speed (1000), also known as @e trick @e play,
 *  may be unsupported or forbidden, either completely or only for some portions
 *  of the media. For instance, a playlist may contain some tracks that don't
 *  support trick play; some devices have only one fast-forward speed; and some
 *  media forbids pausing or fast-forwarding through menus and some portions of
 *  titles.
 *
 *  If an @c mmr_speed_set() call requests a trick-play speed (negative, slower
 *  than normal, or faster than normal) and the exact value is completely
 *  unsupported by the current input, the speed may be rounded to a supported
 *  value in the same category (that is, negative, slow, or fast). If the entire
 *  category is unsupported, the call fails (for more information, see Playing
 *  media).
 *
 *  If the call was made during playback, and the speed (after the rounding
 *  described above) is unsupported or forbidden at the current playing
 *  position, the speed is changed to an allowed value and the call succeeds. A
 *  similar speed change may occur in the @c mmr_play() call, based on the
 *  current speed and position, and during playback if a position is reached (by
 *  playing or by an explicit seek request) where the current play speed is
 *  unsupported or forbidden. The navigation rules for the input media may also
 *  specify other circumstances that cause the speed to change to normal during
 *  playback. In particular, on some platforms you can configure whether the
 *  speed reverts to normal when track boundaries are reached during playback.
 *
 *  @param ctxt A context handle.
 *  @param speed The new speed.
 *  @return Zero on success, -1 on failure (use @c mmr_error_info()).
 */
int mmr_speed_set( mmr_context_t *ctxt, int speed );

/**
 *  @brief Send a remote control command to the context
 *
 *  @details Send a remote control command to the context. The commands
 *  available depend on the plugin in use.
 *
 *  This function is offered for future use; currently, no commands are defined.
 *
 *  @param ctxt A context handle.
 *  @param cmd  The command to send.
 *
 *  @return Zero on success, -1 on failure (use @c mmr_error_info()).
 */
int mmr_command_send( mmr_context_t *ctxt, const char *cmd );

/**
 *  @brief Set a new playlist
 *
 *  @details Set a new playlist without interrupting playback. This function can
 *  be used only during playback of a playlist (including when it's paused, but
 *  not stopped). The new playlist must contain the currently playing track at
 *  position @e n+delta, where @e n is its position on the old playlist. Note
 *  that @e delta is a signed value, so it can be negative.
 *
 *  Common errors returned by this function and their recommended follow-up
 *  actions are:
 *
 *  @b MMR_ERROR_INVALID_STATE
 *
 *  The context was stopped, not playing. The playback might have reached the
 *  end of the old playlist and so it was too late to switch playlists without
 *  interrupting playback. To fix, attach the new playlist as an input, seek to
 *  the beginning of the appropriate track, and start playback.
 *
 *  @b MMR_ERROR_INVALID_PARAMETER
 *
 *  The location in the new list you indicated (@e n + @e delta) is out of range
 *  or refers to a different URL. This error could be caused by a stale @e delta
 *  value, which results when the track you thought was playing just ended and a
 *  different track is playing now. To fix, recalculate the difference between
 *  the position of the current track on the two lists and call this function
 *  again.
 *
 *  @param ctxt A context handle.
 *  @param url The URL of a new playlist.
 *  @param delta The difference between the position of the current track on the
 *               two lists.
 *  @return Zero on success, -1 on failure (use @c mmr_error_info()).
 */
int mmr_list_change( mmr_context_t *ctxt, const char *url, int delta );

/**
 *  @brief Set track parameters
 *
 *  @details Set track parameters. This function can be used when the input type
 *  is "playlist" or "autolist".
 *
 *  When the input type is "playlist", the input parameters only apply to the
 *  playlist file, and the default track parameters are empty. You can call @c
 *  mmr_track_parameters(ctxt,0,parms) to set the default track parameters
 *  before attaching the input.
 *
 *  When the input type is "autolist", any input parameters you set before
 *  attaching the input become the track parameters for track 1. You set the
 *  track parameters for an autolist by calling @c
 *  mmr_track_parameters(ctxt,1,parms). After the input is attached, input
 *  parameters are ignored, and any changes to them will have no effect.
 *
 *  The index specifies the track that these parameters are applied to. The
 *  index value must be within range of the current playlist window; otherwise,
 *  the function call fails. An index of zero specifies the default parameters
 *  given to a new track that enters the playlist window. You can set the
 *  default parameters by calling @c mmr_track_parameters(ctxt,0,parms) before
 *  attaching the input.
 *
 *  Some @c mm-renderer plugins don't return errors when you provide
 *  unacceptable values for track parameters. Instead, these plugins revert bad
 *  parameters to their previous values or to their default values (for
 *  parameters that you set for the first time). To see which values were
 *  accepted or changed, client applications can examine the parameters that the
 *  Event API returned.
 *
 *  When the input URL starts with @c audio:, you can set one of the following
 *  two parameters:
 *
 *  @b audio_type
 *
 *  Classify the audio track based on its content (voice, ring tones, video
 *  chat, etc.). This parameter provides a shortcut for setting the audio type,
 *  thereby simplifying your client code. You can use this parameter instead of
 *  using the Audio Manager API to obtain an audio manager handle, and then
 *  using that handle to set the audio type.
 *
 *  The audio type is specified as a string that's set to one of the audio types
 *  defined by @c AUDIO_TYPE_NAMES, which is documented in the Audio Manager
 *  Library reference.
 *
 *  @b audioman_handle
 *
 *  Associate an audio manager handle with the audio stream that the current
 *  context manages. To obtain a value for this parameter, call the @c
 *  audio_manager_get_handle() API function and pass in the desired audio type.
 *
 *  You can then use this handle to change the audio type and other audio stream
 *  characteristics through the Audio Manager API. For more information, refer
 *  to the audio routing functions described in the Audio Manager Library
 *  reference.
 *
 * When the input URL starts with @c http: or @c https:, you can set the
 * following parameters that map to @c libcurl options:
 *
 * - @c OPT_VERBOSE
 * - @c OPT_CONNECTTIMEOUT_MS
 * - @c OPT_LOW_SPEED_LIMIT
 * - @c OPT_LOW_SPEED_TIME
 * - @c OPT_USERAGENT
 * - @c OPT_USERNAME
 * - @c OPT_PASSWORD
 * - @c OPT_PROXYUSERNAME
 * - @c OPT_PROXYPASSWORD
 * - @c OPT_COOKIE
 * - @c OPT_COOKIEFILE
 * - @c OPT_COOKIEJAR
 * - @c OPT_COOKIESESSION
 * - @c OPT_CAINFO
 * - @c OPT_CAPATH
 * - @c OPT_SSL_VERIFYPEER
 * - @c OPT_SSL_VERIFYHOST
 * - @c OPT_PROXY
 * - @c OPT_NOPROXY
 * - @c OPT_HTTPPROXYTUNNEL
 * - @c OPT_PROXYPORT
 * - @c OPT_PROXYTYPE
 * - @c OPT_PROXYAUTH
 * - @c OPT_HTTPAUTH
 * - @c OPT_HTTPHEADER
 * - @c OPT_DNSCACHETIMEOUT
 *
 * You can set these same @c libcurl options through the context or input
 * parameters. For any options defined in either the context or input parameters
 * but also in the track parameters, the track parameter settings take
 * precedence.
 *
 *  @param ctxt A context handle.
 *  @param index Zero to set the default parameters, or a nonzero index within
 *  the current playlist window.
 *  @param parms A dictionary containing the track parameters to set. Use NULL
 *  to reset the parameters of the specified track to the default values
 *  assigned to track 0. Any previous parameters are overridden. The @c
 *  strm_dict_t object becomes API property after this call, even if the call
 *  fails. You should not use or destroy the dictionary after passing it to this
 *  function.
 *
 *  @return Zero on success, -1 on failure (use @c mmr_error_info()).
 */
int mmr_track_parameters( mmr_context_t *ctxt, unsigned index, strm_dict_t *parms );

/*@}*/

__END_DECLS

#endif

__SRCVERSION("$URL$ $Rev$")
