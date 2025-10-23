/*
 * Copyright (C) 2014 Research In Motion Limited.
 * Proprietary and confidential. All rights reserved.
 *
 * mm/mmsuppl.h
 *
 * This API allows the client to write specific multimedia statistics to the
 * supplemental multimedia database (db/mm_suppl.db).
 *
 * To use the multimedia write service, the mmsuppl library is required
 *     LIBS += -lmmsuppl
 */

#ifndef MM_MMSUPPL_H_
#define MM_MMSUPPL_H_

#include <stdint.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__GNUC__)
#define MMSUPPL_API __attribute__((visibility("default")))
#else
#define MMSUPPL_API
#endif

/**
 * The perimeter location for storing supplemental data.
 */

#define MMSUPPL_PERSONAL                    1
#define MMSUPPL_ENTERPRISE                  2

#define MMSUPPL_PERIMETER_TYPES \
X(PERSONAL) \
X(ENTERPRISE)

typedef enum {
    #define X(a) MMSUPPL_PERIMETER_##a = MMSUPPL_##a,
    MMSUPPL_PERIMETER_TYPES
    #undef X
} mmsuppl_perimeter_t;

/**
 * The specific meta types as they are stored in the mm_suppl database.
 */

#define MMSUPPL_TYPE_BOOKMARK                  1000
#define MMSUPPL_TYPE_DATE_PLAYED               1001
#define MMSUPPL_TYPE_EDIT_COUNT                1002
#define MMSUPPL_TYPE_FAVORITE                  1003
#define MMSUPPL_TYPE_FULLY_PLAYED              1004
#define MMSUPPL_TYPE_PLAY_COUNT                1005
#define MMSUPPL_TYPE_PLAYLIST_PLAY_COUNT       1006
#define MMSUPPL_TYPE_SHARE_COUNT               1007
#define MMSUPPL_TYPE_SET_AS_COUNT              1008
#define MMSUPPL_TYPE_YEAR_PLAY_COUNT           1009
#define MMSUPPL_TYPE_DECADE_PLAY_COUNT         1010
#define MMSUPPL_TYPE_SMART_SCORE               1011
#define MMSUPPL_TYPE_CONSECUTIVE_PLAY_COUNT    1012
#define MMSUPPL_TYPE_HIDDEN_FLAG               1013

#define MMSUPPL_METADATA_TYPES \
X(BOOKMARK) \
X(DATE_PLAYED) \
X(EDIT_COUNT) \
X(FAVORITE) \
X(FULLY_PLAYED) \
X(PLAY_COUNT) \
X(PLAYLIST_PLAY_COUNT) \
X(SHARE_COUNT) \
X(SET_AS_COUNT) \
X(HIDDEN_FLAG) \
X(YEAR_PLAY_COUNT) \
X(DECADE_PLAY_COUNT) \
X(SMART_SCORE) \
X(CONSECUTIVE_PLAY_COUNT)

typedef enum {
    #define X(a) MMSUPPL_METATYPE_##a = MMSUPPL_TYPE_##a,
    MMSUPPL_METADATA_TYPES
    #undef X
} mmsuppl_metatype_t;

/**
 * An opaque structure defining a supplemental data connection.
 */
typedef struct mmsuppl_service_t mmsuppl_service_t;

/**
 *  Stores the bookmark position in milliseconds (ms) for the given file hash.
 *  Any existing bookmark position is overridden.
 *
 *  @param service  The active service connection handle.
 *  @param hash     The file hash as stored in the mmlibrary database.
 *  @param ms       The position of the bookmark in milliseconds (ms).
 *
 *  @return EOK on success, EAGAIN if the the service is unavailable, EINVAL if
 *          the message payload could not be encoded, EINTR if communication
 *          was interrupted or ETIMEDOUT if the service timed out.
 */
MMSUPPL_API int mmsuppl_bookmark(
    mmsuppl_service_t *service,
    int64_t hash,
    uint32_t ms);

/**
 * Closes the supplemental service connection.
 *
 * @param service  The active service connection handle.
 */
MMSUPPL_API void mmsuppl_close(
    mmsuppl_service_t *service);

/**
 *  Stores the timestamp for the given file hash.
 *
 *  @param service  The active service connection handle.
 *  @param hash     The file hash as stored in the mmlibrary database.
 *  @param datetime The date/time structure representing the last played
 *                  timestamp.
 *
 *  @return EOK on success, EAGAIN if the the service is unavailable, EINVAL if
 *          the message payload could not be encoded, EINTR if communication
 *          was interrupted or ETIMEDOUT if the service timed out.
 */
MMSUPPL_API int mmsuppl_date_played(
    mmsuppl_service_t *service,
    int64_t hash,
    struct tm * datetime);

/**
 *  Flags the given file hash as a user favorite.
 *
 *  @param service  The active service connection handle.
 *  @param hash     The file hash as stored in the mmlibrary database.
 *
 *  @return EOK on success, EAGAIN if the the service is unavailable, EINVAL if
 *          the message payload could not be encoded, EINTR if communication
 *          was interrupted or ETIMEDOUT if the service timed out.
 */
MMSUPPL_API int mmsuppl_favorite(
    mmsuppl_service_t *service,
    int64_t hash);

/**
 *  Flags the given file hash as hidden.
 *
 *  @param service  The active service connection handle.
 *  @param hash     The file hash as stored in the mmlibrary database.
 *
 *  @return EOK on success, EAGAIN if the the service is unavailable, EINVAL if
 *          the message payload could not be encoded, EINTR if communication
 *          was interrupted or ETIMEDOUT if the service timed out.
 */
MMSUPPL_API int mmsuppl_hidden_flag(
    mmsuppl_service_t *service,
    int64_t hash);

/**
 *  Flags the given file hash as having been fully played on the system. It is
 *  up to the client to determine if the content of the file has been fully
 *  played.
 *
 *  @param service  The active service connection handle.
 *  @param hash     The file hash as stored in the mmlibrary database.
 *
 *  @return EOK on success, EAGAIN if the the service is unavailable, EINVAL if
 *          the message payload could not be encoded, EINTR if communication
 *          was interrupted or ETIMEDOUT if the service timed out.
 */
MMSUPPL_API int mmsuppl_fully_played(
    mmsuppl_service_t *service,
    int64_t hash);

/**
 *  Increments the edit count for a given file hash. It is up to the
 *  client to determine that the user performed this action.
 *
 *  @param service  The active service connection handle.
 *  @param hash     The file hash as stored in the mmlibrary database.
 *
 *  @return EOK on success, EAGAIN if the the service is unavailable, EINVAL if
 *          the message payload could not be encoded, EINTR if communication
 *          was interrupted or ETIMEDOUT if the service timed out.
 */
MMSUPPL_API int mmsuppl_increment_edit_count(
    mmsuppl_service_t *service,
    int64_t hash);

/**
 *  Increments the play count for a given file hash. It is up to the
 *  client to determine that the user performed this action.
 *
 *  @param service  The active service connection handle.
 *  @param hash     The file hash as stored in the mmlibrary database.
 *
 *  @return EOK on success, EAGAIN if the the service is unavailable, EINVAL if
 *          the message payload could not be encoded, EINTR if communication
 *          was interrupted or ETIMEDOUT if the service timed out.
 */
MMSUPPL_API int mmsuppl_increment_play_count(
    mmsuppl_service_t *service,
    int64_t hash);

/**
 *  Increments the playlist play count for a given file hash. It is up to the
 *  client to determine that the user performed this action.
 *
 *  @param service  The active service connection handle.
 *  @param hash     The file hash as stored in the mmlibrary database.
 *
 *  @return EOK on success, EAGAIN if the the service is unavailable, EINVAL if
 *          the message payload could not be encoded, EINTR if communication
 *          was interrupted or ETIMEDOUT if the service timed out.
 */
MMSUPPL_API int mmsuppl_increment_playlist_play_count(
    mmsuppl_service_t *service,
    int64_t hash);

/**
 *  Increments the year play count for a given file hash. It is up to the
 *  client to determine that the user performed this action.
 *
 *  @param service  The active service connection handle.
 *  @param hash     The file hash as stored in the mmlibrary database.
 *
 *  @return EOK on success, EAGAIN if the the service is unavailable, EINVAL if
 *          the message payload could not be encoded, EINTR if communication
 *          was interrupted or ETIMEDOUT if the service timed out.
 */
MMSUPPL_API int mmsuppl_increment_year_play_count(
    mmsuppl_service_t *service,
    int64_t hash);

/**
 *  Increments the decade play count for a given file hash. It is up to the
 *  client to determine that the user performed this action.
 *
 *  @param service  The active service connection handle.
 *  @param hash     The file hash as stored in the mmlibrary database.
 *
 *  @return EOK on success, EAGAIN if the the service is unavailable, EINVAL if
 *          the message payload could not be encoded, EINTR if communication
 *          was interrupted or ETIMEDOUT if the service timed out.
 */
MMSUPPL_API int mmsuppl_increment_decade_play_count(
    mmsuppl_service_t *service,
    int64_t hash);

/**
 *  Increments the share count for a given file hash. It is up to the
 *  client to determine that the user performed this action.
 *
 *  @param service  The active service connection handle.
 *  @param hash     The file hash as stored in the mmlibrary database.
 *
 *  @return EOK on success, EAGAIN if the the service is unavailable, EINVAL if
 *          the message payload could not be encoded, EINTR if communication
 *          was interrupted or ETIMEDOUT if the service timed out.
 */
MMSUPPL_API int mmsuppl_increment_share_count(
    mmsuppl_service_t *service,
    int64_t hash);

/**
 *  Increments the "set as" count for a given file hash. It is up to the
 *  client to determine that the user performed this action. For example,
 *  setting a picture as wallpaper or audio as a ringtone.
 *
 *  @param service  The active service connection handle.
 *  @param hash     The file hash as stored in the mmlibrary database.
 *
 *  @return EOK on success, EAGAIN if the the service is unavailable, EINVAL if
 *          the message payload could not be encoded, EINTR if communication
 *          was interrupted or ETIMEDOUT if the service timed out.
 */
MMSUPPL_API int mmsuppl_increment_set_as_count(
    mmsuppl_service_t *service,
    int64_t hash);

/**
 * Modify's the consecutive count for the given file hash. It is used in the music
 * app to track how many times a song have been fully played or skipped. In the music
 * app it is implemented to decrease (to 0) exponentially, and increase by 1 at a time.
 * Counts below 0 indicate consecutive skips, and visa versa consecutive plays.
 *
 *  @param service  The active service connection handle.
 *  @param hash     The file hash as stored in the mmlibrary database.
 *
 *  @return EOK on success, EAGAIN if the the service is unavailable, EINVAL if
 *          the message payload could not be encoded, EINTR if communication
 *          was interrupted or ETIMEDOUT if the service timed out.
 */
MMSUPPL_API int mmsuppl_modify_consecutive_play_count(
    mmsuppl_service_t *service,
    int64_t hash,
    uint32_t consecutivePlayCount);

/**
 * Modify's the score for the given file hash. It is used to track how likely
 * a user is to want to listen to the song (The lower the score the more often
 * they have skipped the song)
 *
 *  @param service  The active service connection handle.
 *  @param hash     The file hash as stored in the mmlibrary database.
 *
 *  @return EOK on success, EAGAIN if the the service is unavailable, EINVAL if
 *          the message payload could not be encoded, EINTR if communication
 *          was interrupted or ETIMEDOUT if the service timed out.
 */
MMSUPPL_API int mmsuppl_modify_smart_score(
    mmsuppl_service_t *service,
    int64_t hash,
    uint32_t smartScore);

/**
 *  Create and open a connection to the platform supplemental service.
 *
 *  @param service  The active service connection handle.
 *  @param perimeter The perimeter to open the service connection against.
 *  @param mmsuppl   A handle to the supplemental service connection.
 *
 *  @return EOK on success, EAGAIN if the the service is unavailable.
 */
MMSUPPL_API int mmsuppl_open(
    mmsuppl_perimeter_t perimeter,
    mmsuppl_service_t **service);

/**
 *  Resets the entry on the given file hash for the specified metatype.
 *
 *  @param service  The active service connection handle.
 *  @param hash     The file hash as stored in the mmlibrary database.
 *  @param metatype The metatype to reset.
 *
 *  @return EOK on success, EAGAIN if the the service is unavailable, EINVAL if
 *          the message payload could not be encoded, EINTR if communication
 *          was interrupted or ETIMEDOUT if the service timed out.
 */
MMSUPPL_API int mmsuppl_reset(
    mmsuppl_service_t *service,
    int64_t hash,
    mmsuppl_metatype_t metatype);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MM_MMSUPPL_H_ */
