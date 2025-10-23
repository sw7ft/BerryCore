/*
 * $QNXLicenseC:
 * Copyright 2010, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable
 * license fees to QNX Software Systems before you may reproduce,
 * modify or distribute this software, or any work that includes
 * all or part of this software.   Free development licenses are
 * available for evaluation and non-commercial purposes.  For more
 * information visit http://licensing.qnx.com or email
 * licensing@qnx.com.
 *
 * This file may contain contributions from others.  Please review
 * this entire file for other proprietary rights or license notices,
 * as well as the QNX Development Suite License Guide at
 * http://licensing.qnx.com/license-guide/ for other information.
 * $
 */

/**
 * @file bucket.h
 *
 * @brief Data types and functions for gesture buckets
 *
 * The bucket.h header file provides data type definitions and functions
 * for the gesture bucket, that is, the set of gestures that haven't
 * yet been processed.
 *
 */ 
 
#include <sys/types.h>
#include <sys/cdefs.h>

#ifndef GESTURES_BUCKET_H_
#define GESTURES_BUCKET_H_

__BEGIN_DECLS

#define GESTURES_BUCKET_GROW_INCREMENT 4
#define EVENTS_BUCKET_GROW_INCREMENT 64

struct gesture_base;

/**
 * @brief Structure representing the gesture bucket
 *
 * The structure @c gestures_bucket_t represents the set of gestures awaiting
 * processing. The gesture bucket grows indefinitely by 
 * GESTURES_BUCKET_GROW_INCREMENT every time it reaches @c size.
 */
typedef struct {
	struct gesture_base** gestures;    /**< The array of gestures */ 
	_Uint32t gestures_count;           /**< The number of gestures currently in the bucket. */
	_Uint32t size;                     /**< The total allocated size of the bucket (measured
	                                        in number of increments of gesture_base_t size) */
} gestures_bucket_t;

/**
 * Not used.
 */
typedef enum {
	EVENTS_BUCKET_COMPRESS_ON_INSERT,
	EVENTS_BUCKET_COMPRESS_ON_FULL,
	EVENTS_BUCKET_GROW
} events_bucket_mode_e;

/**
 * Not used.
 */
typedef struct {
	events_bucket_mode_e mode;
	_Uint32t events_count;
	_Uint32t size;
} events_bucket_t;

/** @brief Initialize a gesture bucket
 *
 * The function @c gestures_bucket_init() initializes the gesture
 * bucket structure. 
 *
 * @param bucket A pointer to the gesture bucket structure to initialize.
 *
 * @return Nothing.
 */
void gestures_bucket_init(gestures_bucket_t* bucket);

/**
 * @brief Add a gesture to a gesture bucket
 *
 * The function @c gestures_bucket_add() adds a gesture to a gestures
 * bucket.
 *
 * @param bucket   A pointer to the gesture bucket.
 * @param gesture  A pointer to the gesture to add.
 *
 * @return 0 on success, or -1 on failure.
 */ 
int gestures_bucket_add(gestures_bucket_t* bucket, struct gesture_base* gesture);

/**
 * @brief Remove a gesture from a gesture bucket
 *
 * The function @c gestures_bucket_del() deletes the gesture at the specified
 * index from the gesture bucket.
 *
 * @param bucket   A pointer to the gesture bucket.
 * @param idx      The index of the gesture to delete.
 *
 * @return 0 on success, or -1 on failure.
 */
int gestures_bucket_del(gestures_bucket_t* bucket, uint_t idx);

/**
 * @brief Clear a gesture bucket
 *
 * The function @c gestures_bucket_clear() removes all entries
 * from the gestures array and sets the gesture count and bucket 
 * size to zero.
 *
 * @param bucket   A pointer to the gesture bucket to clear.
 *
 * @return Nothing.
 */
void gestures_bucket_clear(gestures_bucket_t* bucket);

/**
 * @brief Return the number of gestures in a gesture bucket
 *
 * The function @c gestures_bucket_count() returns the number of gestures
 * in the specified gesture bucket.
 *
 * @param bucket   A pointer to the gesture bucket.
 *
 * @return The number of gestures in the bucket. 
 */
int gestures_bucket_count(gestures_bucket_t* bucket);

/**
 * @brief Return the gesture at the specified index
 *
 * The function gestures_bucket_get() returns a pointer to the gesture
 * at the specified index of the gesture bucket.
 *
 * @param bucket   A pointer to the gesture bucket.
 * @param idx      The index of the gesture to return.
 *
 * @return A pointer to the gesture at the specified index.
 */
struct gesture_base* gestures_bucket_get(gestures_bucket_t* bucket, uint_t idx);

__END_DECLS

#endif /* GESTURES_BUCKET_H_ */

__SRCVERSION( "$URL: $ $Rev: $" );
