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

/***************************************************************************//** 
 * \brief
 * This is a generic library that may be used to get attribute values from
 * PPS objects.
 *
 * The library takes care of updating the cache as PPS objects are changed; it
 * creates a single subscriber thread for all needed objects.
 *
 * Callers can get the values from the cache by asked for a string map; this
 * creates a snapshot of the object at that time.
 *
 * Using the Library
 * =================
 *
 * The library must be initialized with the pps_cache_init() function.
 *
 * To start monitoring of a specific PPS object, a reference handle to that
 * object must be created. Additional references may be created as well.
 *
 * Then, snapshots of the object may be retrieved until all reference to the
 * object are deleted.
 *
 * Additionally, directories may be monitored. In this case, callbacks are
 * provided to handle actions associated with complete objects.
 *
 * NOTE: These call back run in the context of the single monitor thread, so
 * will delay handling of updates of all monitored objects.
 *
 */

#ifndef _H_PPS_CACHE_H_
#define _H_PPS_CACHE_H_

#include <stdint.h>
#include "mm/mmsupport.h"
#include "sys/strm.h"

__BEGIN_DECLS


/**
 * Initial (default) library logging verbosity setting.
 */
#ifndef PPS_CACHE_INIT_VERBOSITY
#define	PPS_CACHE_INIT_VERBOSITY	1
#endif

/**
 * Initial (default) library log flag setting.
 */
#ifndef PPS_CACHE_INIT_LOG_FLAGS
#define PPS_CACHE_INIT_LOG_FLAGS	0
#endif

/**
 * Reference to a cache.
 */
struct pps_cache;
typedef struct pps_cache pps_cache_t;

/**
 * Initialize the PPS cache.
 * 
 * This function starts a PPS monitor thread. The thread's priority is inherited
 * from the priority of the caller of this function the priority is 0 and the
 * thread has not yet been started.
 * 
 * This function may be called multiple times; each caller should consider
 * the returned handle their own.
 * 
 * Current behaviour: if it is called more than once
 * and the specified priority is non-zero and the current priority is less
 * than the specified value, the thread's priority is changed to the specified
 * value.
 *
 * @param Priority	If non-zero, minimum priority thread should be running at.
 * @return non-NULL on success
 * @return NULL on failure
 */
pps_cache_t *pps_cache_init(int priority);

/**
 * Initialize the PPS cache.
 * 
 * This function starts a PPS monitor thread. The thread's priority is inherited
 * from the priority of the caller of this function the priority is 0 and the
 * thread has not yet been started.
 * 
 * This function may be called multiple times; each caller should consider
 * the returned handle their own.
 * 
 * Current behaviour: if it is called more than once
 * and the specified priority is non-zero and the current priority is less
 * than the specified value, the thread's priority is changed to the specified
 * value.
 *
 * @param Priority	If non-zero, minimum priority thread should be running at.
 * @param pps_root      PPS mountpoint.
 * @return non-NULL on success
 * @return NULL on failure
 */
pps_cache_t *pps_cache_init_with_root(int priority, const char *pps_root);

/**
 * Terminate use of the PPS cache. This call be considered as having freed
 * all other handles associated with the cache handle.
 *
 * @return 0 on success
 * @return -1 on failure
 */
int pps_cache_terminate(pps_cache_t *cache);

/**
 * Reference to a cached PPS object.
 */
struct pps_obj;
typedef struct pps_obj pps_obj_t;

/**
 * This function starts the monitoring of a PPS object.
 * 
 * @param name	The name of the PPS object to start getting values for.
 * @return non-NULL on success
 * @return NULL on failure.
 */
pps_obj_t *pps_cache_object_start(pps_cache_t *cache, const char *name);

/**
 * This function stops the monitoring of a PPS object.
 * 
 * @param cache Cache handle
 * @param obj	The object to stop monitoring.
 * @return 0 on success
 * @return -1 on failure
 */
int pps_cache_object_stop(pps_cache_t *cache, pps_obj_t *obj);

/**
 * Get a PPS object, formatted as a string map dictionary.
 *
 * Each PPS attribute is a key-value pair in the dictionary, where the
 * attribute name is the key and the attribute's encoding and value are treated
 * as a single unit and become the key's value.
 * 
 * When done, call strm_dict_destroy() to release the string map dictionary.
 *
 * @param cache Cache handle
 * @param obj	The object that the values are wanted from.
 * @return non-NULL on success
 * @return NULL on failure
 */
strm_dict_t *pps_cache_object_get(pps_cache_t *cache, pps_obj_t *obj);

/**
 * This function gets a map value string from the specified object for the
 * specified attribute.
 * 
 * Note that the attribute's encoding and value appear concatenated as the
 * value part of the string object.
 * 
 * More generically, the attribute encoding is the part of the string before
 * the first ':' character in the string, and the value is the part of the
 * string after the first ':' character in the string.
 * 
 * The returned structure should be released by using strm_string_destroy().
 * 
 * @param cache Cache handle
 * @param obj	The object the attribute is in.
 * @param attr	The name of the attribute to get the value of.
 * @return non-NULL on success
 * @return NULL on failure
 */
strm_string_t *pps_cache_object_attr_get(pps_cache_t *cache, pps_obj_t *obj,
										 const char *attr);

/**
 * Get a PPS object, formatted as a string map dictionary, from the specified
 * object. Do not monitor the object.
 *
 * Each PPS attribute is a key-value pair in the dictionary, where the
 * attribute name is the key and the attribute's encoding and value are treated
 * as a single unit and become the key's value.
 * 
 * When done, call strm_dict_destroy() to release the string map dictionary.
 *
 * @param name	Name of the object that is wanted.
 * @return non-NULL on success
 * @return NULL on failure
 */
strm_dict_t *pps_cache_object_get_once(const char *name);


/**
 * Get the name of the first PPS object in the specified directory that has the
 * specified attribute with the specified value. Do not monitor the object.
 *
 * @param dirname	Name of the PPS directory to look for the object.
 * @param attr	Name of the attribute whose value is known.
 * @param value	The value the attribute must have.
 * @param name	Place to put name.	May be NULL.
 * @param length	Length of name buffer.	May be 0.
 * @return -1 on failure
 * @return >0 on success; length of name.
 */
int pps_cache_object_name_get_with_attr_value(const char *dirname,
											  const char *attr,
											  const char *value,
											  char *const name, size_t length);

/**
 * Force the cache to be updated. A specific object may be specified; otherwise
 * all objects are updated.
 *
 * Normally it is not necessary to force update the cache since it will 
 * automatically be kept up to date. However, if a client were to write a
 * configuration change and wanted to read it back immediately without a race
 * condition then this API should be called in between the write and the read.
 *
 * @param cache 	Cache handle
 * @param object	Optional name of object to be updated if want only the one.
 * @return 0 on success
 * @return -1 on failure
 */
int pps_cache_forceupdate(pps_cache_t *cache, const char *object);

/**
 * The events that may be reported about objects in a monitored directory.
 */
typedef enum {
	pps_obj_event_unknown = 0,
	pps_obj_event_new,
	pps_obj_event_change,
	pps_obj_event_trunc,
	pps_obj_event_delete
} pps_obj_event_t;

/**
 * This function returns a string version of the events.
 * 
 * @param event	The event to convert to a string.
 * @return A string (always)
 */
const char *pps_cache_obj_event_string(pps_obj_event_t event);


/**
 * Object handling function definition.
 * 
 * @param name		Name of the object to be handled.
 * @param event		The event type.
 * @param dict		A dictionary of the object; NULL if the object is deleted,
 *              	and empty if the object is truncated.
 * @param userdata	Data to pass to the function.
 * @return -1 on catastrophic failure (monitor will exit).
 * @return >=0 on success; see below for meanings.
 */
typedef int (* pps_dir_func_t)(const char *name, pps_obj_event_t event,
							   const strm_dict_t *dict, void *userdata);

/**
 * Directory monitor instance reference. Opaque to callers.
 */
struct pps_dir;
typedef struct pps_dir pps_dir_t;

/**
 * This function starts monitoring of a PPS directory.
 * 
 * @param cache 	Cache handle
 * @param path		PPS path to monitor.
 * @param obj_hndlr	Function to handle object events.
 * @param userdata	Data to pass to each function.
 * @param flags		Flags (to be determined).
 * @return 0 on success
 * @return -1 on failure (logged and errno set)
 */
pps_dir_t *pps_dir_start(pps_cache_t *cache, const char *path,
						 pps_dir_func_t obj_hndlr, void *userdata,
						 uint32_t flags);

/** 
 * This function stops monitoring of a PPS directory. This also de-allocates
 * the directory pointer, so it must not be used after this call exits.
 * 
 * @param cache 	Cache handle
 * @param ppsdir	Handle to the PPS directory instance.
 * @return 0 on success.
 * @return -1 on failure.
 */
int pps_dir_stop(pps_cache_t *cache, pps_dir_t *ppsdir);

__END_DECLS

__SRCVERSION("$URL$ $Rev$")

#endif /* _H_PPS_CACHE_H_ */
