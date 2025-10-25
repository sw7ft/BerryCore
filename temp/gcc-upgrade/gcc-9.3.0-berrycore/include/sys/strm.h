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

#if !defined(SYS_STRM_H_INCLUDED)
#define SYS_STRM_H_INCLUDED

#if !defined(__TYPES_H_INCLUDED)
#include <sys/types.h>
#endif

/** @file strm.h
 *
 *  @brief Dictionary Object API
 *
 *  A dictionary object is a collection of key-value pairs. Each pair is
 *  considered an entry or a 'named value', where the key acts as the name of
 *  the entry. Keys are unique - you can't add an entry with a duplicate key.
 *
 *  Both the keys and values are represented by shareable string objects. A
 *  shareable string is a data structure that encapsulates a string so that it
 *  can't be modified directly. This design allows multiple threads to read the
 *  string without the risk that the string will be changed inadvertently
 *  between reads. Modifying a shareable string creates a new string and
 *  destroys the original.
 *
 *  The dictionary object API allows the creation of multiple handles to a
 *  dictionary object that can be used and destroyed by independent components
 *  of a program. Since a dictionary, once created, is immutable until
 *  destroyed, components can access it through their handles without worrying
 *  about synchronization.
 *
 *  Different dictionary object handles may be represented by identical
 *  pointers. You should not compare handles. Regardless of how the handles are
 *  represented internally, you must destroy each handle separately to properly
 *  dispose of any resources associated with it.
 *
 */

__BEGIN_DECLS

/**
 *  @brief The dictionary object type
 *
 *  The structure @c strm_dict_t is a private data type representing a
 *  dictionary object.
 *
 *  Dictionaries cannot be modified; they can only be created and destroyed.
 *
 *  Distinct dictionary object handles may be represented by identical pointers.
 *  You should not compare handles. Regardless of how the handles are
 *  represented internally, you have to call @c strm_dict_destroy() separately
 *  for each handle to properly dispose of any resources associated with it.
 *
 *  Use the following functions to manipulate dictionary objects:
 *
 * - @c strm_dict_clone()
 * - @c strm_dict_compare()
 * - @c strm_dict_destroy()
 * - @c strm_dict_find_index()
 * - @c strm_dict_find_rstr()
 * - @c strm_dict_find_value()
 * - @c strm_dict_index_delete()
 * - @c strm_dict_key_delete()
 * - @c strm_dict_key_get()
 * - @c strm_dict_key_rstr()
 * - @c strm_dict_new()
 * - @c strm_dict_set()
 * - @c strm_dict_set_rstr()
 * - @c strm_dict_size()
 * - @c strm_dict_subtract()
 * - @c strm_dict_value_get()
 * - @c strm_dict_value_rstr()
 *
 */
typedef struct strm_dict strm_dict_t;

/**
 *  @brief Create a new handle to an empty dictionary object
 *
 *  This function returns a new handle to an empty dictionary object.
 *
 *  Note that multiple handles may be represented by identical pointer values;
 *  you should not compare handles.
 *
 *  @return  A new dictionary object handle.
 *
 */
strm_dict_t *strm_dict_new( void );

/**
 *  @brief Duplicate a dictionary handle
 *
 *  This function creates a new handle to the dictionary object referenced by
 *  the specified handle.
 *
 *  Note that multiple handles may be represented by identical pointer values;
 *  you should not compare handles.
 *
 *  @param dict  A new dictionary object handle to the dictionary object
 *               referenced by the specified handle.
 */
strm_dict_t *strm_dict_clone( const strm_dict_t *dict );

/**
 *  @brief Destroy a dictionary object handle
 *
 *  This function destroys the specified dictionary object handle and frees the
 *  memory allocated for the dictionary object if this is the last handle.
 *
 *  @param dict  A dictionary object handle.
 *
 *  @retval 0   Success
 *  @retval -1  An error occurred (@e errno is set).
 */
int strm_dict_destroy( strm_dict_t *dict );

/**
 *  @brief Modify a dictionary entry (using key-value strings)
 *
 *  This function creates a new dictionary object that is an exact replica of
 *  the dictionary object specified by the @e dict argument, except that the
 *  entry specified by the @e key and @e value arguments is added or modified.
 *
 *  An entry is added to the dictionary when there is no dictionary object that
 *  exists with @e key as its key. When such a dictionary object does exist, its
 *  value is replaced with @e value.
 *
 *  A handle to the new dictionary object is returned. The original dictionary
 *  handle is destroyed on success.
 *
 *  @param dict  A dictionary object handle.
 *  @param key   The key of the dictionary entry to add or modify.
 *  @param value The value of the dictionary entry to add or modify.
 *
 *  @return A handle to the new dictionary object on success, or a null pointer
 *          on failure.
 *
 */
strm_dict_t *strm_dict_set( strm_dict_t *dict, const char *key, const char *value );

/**
 *  @brief Delete a dictionary entry (by key)
 *
 *  This function creates a new dictionary object that is an exact replica of
 *  the old object, except the entry specified by the key argument is deleted.
 *  The function returns a handle to the new dictionary object, or a null
 *  pointer on failure. On success, the original dictionary handle is destroyed.
 *
 *  @param dict  A dictionary object handle.
 *  @param key   The key of the entry to delete.
 *
 *  @return A handle to the new dictionary object, or a null pointer on failure.
 */
strm_dict_t *strm_dict_key_delete( strm_dict_t *dict, char const *key );

/**
 *  @brief Delete a dictionary entry (by index)
 *
 *  This function creates a new dictionary object that is an exact replica of
 *  the old object, except the entry specified by the @e index argument is
 *  deleted. The function returns a handle to the new dictionary object, or a
 *  null pointer on failure (including when the index is out of range). On
 *  success, the original dictionary handle is destroyed.
 *
 *  @param dict   A handle to the original dictionary object.
 *  @param index  The index of the entry to delete.
 *
 *  @return A handle to the new dictionary object, or a null pointer on failure
 *          (including when the index is out of range).
 */
strm_dict_t *strm_dict_index_delete( strm_dict_t *dict, size_t index );

/**
 *  @brief Find the value of a dictionary entry based on the entry's key
 *         (returns a string)
 *
 *  This function returns the value of the dictionary entry specified by the @e
 *  key argument. The returned string is owned by the dictionary, and remains
 *  valid until the dictionary handle is destroyed.
 *
 *  @param dict  A dictionary object handle.
 *  @param key   The key of the dictionary entry.
 *
 *  @return The value (as a string) of the dictionary entry specified by the @e
 *          key parameter if the entry is found, or a null pointer if it isn't
 *          found.
 */
const char *strm_dict_find_value( const strm_dict_t *dict, const char *key );

/**
 *  @brief Return the index of a dictionary entry
 *
 *  This function returns the index of the entry specified by the @e key
 *  argument, if found in the specified dictionary.
 *
 *  @param dict  A dictionary object handle.
 *  @param key   The key of an entry to look up.
 *
 *  @return The index of the specified entry on success, or @c -1 if the entry
 *          is not found.
 *
 */
ssize_t strm_dict_find_index( const strm_dict_t *dict, const char *key );

/**
 *  @brief Return the number of entries in a dictionary
 *
 *  This function returns the number of entries in the specified dictionary.
 *
 *  @param dict  A dictionary object handle.
 *
 *  @return The number of entries in the specified dictionary.
 *
 */
size_t strm_dict_size( const strm_dict_t *dict );

/**
 *  @brief Find the key of a dictionary entry (returns a string)
 *
 *  This function finds the key of the (@c n + 1)th entry in the specified
 *  dictionary and returns it as a null-terminated string. For example, if @c n
 *  is 3, the key of the fourth entry is returned. The returned string is owned
 *  by the dictionary object, and remains valid until the dictionary handle is
 *  destroyed.
 *
 *  @param dict  A dictionary object handle.
 *  @param n     The 0-based index of the entry whose key is returned.
 *
 *  @return The specified key on success, or a null pointer on failure.
 */
const char *strm_dict_key_get( const strm_dict_t *dict, size_t n );

/**
 *  @brief Find the value of a dictionary entry based on the entry's index
 *         (returns a string)
 *
 *  This function returns the value of the (@c n + 1)th entry in the dictionary
 *  as a null-terminated string. For example, if @c n is 3, the value of the
 *  fourth entry is returned. The returned string is owned by the dictionary
 *  object, and remains valid until the dictionary handle is destroyed.
 *
 *  @param dict  A dictionary object handle.
 *  @param n     The 0-based index of the entry whose key is returned.
 *
 *  @return The specified key on success, or a null pointer on failure.
 *
 */
const char *strm_dict_value_get( const strm_dict_t *dict, size_t n );




/*
  Shareable string handle API.
  Used by the "advanced" verion of the dictionary API.

  This API allows the creation of multiple "handles" to a string
  that can be independently used and destroyed
  by independent components of a program.
  (Note that multiple handles may be represented
  by identical pointer values; you should not compare handles.)
  Since the string represented by a handle is immutable until destroyed,
  components can access it through their handles
  without worrying about synchronization.
 */

/**
 *  @brief Shareable string type
 *
 *  The structure @c strm_string_t is a private data type representing a
 *  shareable string.
 *
 *  Shareable strings cannot be modified; they can only be created and
 *  destroyed. For example, the function @c strm_string_modify() takes a
 *  shareable string object handle, destroys the object, creates a new shareable
 *  string object and returns a new handle to it. It is equivalent to calling @c
 *  strm_string_destroy() and @c strm_string_make(), except that it may reuse
 *  the original object's memory.
 *
 *  Different shareable string object handles may be represented by identical
 *  pointers. You should not compare handles. Regardless of how the handles are
 *  represented internally, you have to call @c strm_string_destroy() separately
 *  for each handle to properly dispose of any resources associated with it.
 *
 *  Use the following functions to manipulate shareable strings:
 *
 *  - @c strm_string_alloc()
 *  - @c strm_string_clone()
 *  - @c strm_string_destroy()
 *  - @c strm_string_get()
 *  - @c strm_string_make()
 *  - @c strm_string_modify()
 *
 */
typedef struct strm_string strm_string_t;

/**
 *  @brief Create a new shareable string object
 *
 *  This function creates a new shareable string object, populating it with the
 *  string passed in the cstring argument, and returning a handle to the new
 *  string object.
 *
 *  @param cstring  A pointer to a null-terminated string.
 *
 *  @return A handle to the new string object.
 */
strm_string_t *strm_string_make( const char *cstring );

/**
 *  @brief Allocate a new shareable string object
 *
 *  This function allocates a new shareable string object to be filled in by the
 *  caller. The caller must put a null-terminated string in the buffer of the
 *  new string object before calling any of the functions @c
 *  strm_string_clone(), @c strm_string_modify(), or @c strm_string_destroy(),
 *  and must not modify the buffer afterwards.
 *
 *  @param len     The length of the string to make room for, not including the
 *                 terminating '\0'
 *  @param handle  A pointer to a variable where the new string handle will be
 *                 stored.
 *
 *  @return A pointer to the first byte of the new string object's string
 *          buffer, or a null pointer on error. The new string handle is stored
 *          in the variable pointed to by @c handle.
 */
char *strm_string_alloc( size_t len, strm_string_t **handle );

/**
 *  @brief Return a pointer to the first character of the string
 *
 *  This function returns a const pointer to the first character of the string
 *  in the shareable string object referenced by the @e sstr argument.
 *
 *  @param sstr  A handle to a shareable string object.
 *
 *  @return A pointer to the first character of the string in the shareable
 *          string object referenced by the @e sstr argument.
 *
 */
const char *strm_string_get( const strm_string_t *sstr );

/**
 *  @brief Create a new handle to an existing shareable string object
 *
 *  This function creates a new string handle to the shareable string object
 *  referenced by the argument @e sstr.
 *
 *  @param sstr  A handle to a shareable string object.
 *
 *  @return A new handle to the shareable string handle on success, or a null
 *          pointer on failure (@e errno is set).
 */
strm_string_t *strm_string_clone( const strm_string_t *sstr );

/**
 *  @ brief Destroy a string handle.
 *
 *  This function destroys the specified string handle, and frees the memory
 *  allocated for the string object if the specified handle is the last one
 *  referencing it.
 *
 *  @param sstr  A handle to a shareable string object.
 *
 *  @retval 0   Success
 *  @retval -1  An error occurred (@e errno is set).
 */
int strm_string_destroy( strm_string_t *sstr );


/**
 *  @brief Modify a shareable string object (destroying the existing handle)
 *
 *  This function creates a new shareable string object from the string passed
 *  in the @e cstring argument, and returns a new handle to the new string
 *  object. Calling @c strm_string_modify() is equivalent to calling @c
 *  strm_string_destroy() and @c strm_string_make(), except that it may reuse
 *  the original object's memory. The shareable string object handle passed in
 *  the @e sstr argument is consumed, even on failure.
 *
 *  @param sstr     A handle to a shareable string object.
 *  @param cstring  A pointer to a null-terminated string.
 *
 *  @return A new handle to the new shareable string object on success, or a
 *          null pointer on failure (@e errno is set).
 */
strm_string_t *strm_string_modify( strm_string_t *sstr, const char *cstring );



/*
   The "advanced" version of the dictionary API.
   It uses shareable string handles instead of regular C strings.
 */

/**
 *  @brief Modify a dictionary entry (using key-value shareable string objects)
 *
 *  This function creates a new dictionary object that is an exact replica of
 *  the dictionary object specified by the @e dict argument, except that the
 *  entry specified by the @e key and @e value arguments is added or modified.
 *  A handle to the new dictionary object is returned.
 *
 *  The original dictionary handle, and the handles to the @e key and @e value
 *  arguments are destroyed on success.
 *
 *  This function is equivalent to @c strm_dict_set(), except that it may be
 *  more efficient if you use clones of the same @e key handle repeatedly.
 *
 *  @param dict   A dictionary object handle.
 *  @param key    The key of the dictionary entry to add or modify.
 *  @param value  The value of the dictionary entry to add or modify.
 *
 *  @return A handle to the new dictionary object on success, or a null pointer
 *          on failure.
 */
strm_dict_t *strm_dict_set_rstr( strm_dict_t *dict, strm_string_t *key, strm_string_t *value );

/**
 *  @brief Find the value of a dictionary entry based on the entry's key
 *         (returns a shareable string object handle)
 *
 *  This function finds the dictionary entry specified by the @e key argument,
 *  returning a handle to the entry's value. The returned shareable string
 *  object handle is owned by the dictionary, and remains valid until the
 *  dictionary handle is destroyed.
 *
 *  You can clone the returned handle to have a handle that exists independently
 *  of the dictionary until you decide to destroy it.
 *
 *  @param dict   A dictionary object handle.
 *  @param key    The name of the dictionary entry.
 *
 *  @return A handle to the value of the dictionary entry specified by the key
 *          parameter if the the entry is found, or a null pointer if it isn't
 *          found.
 */
const strm_string_t *strm_dict_find_rstr( const strm_dict_t *dict, const char *key );

/**
 *  @brief Find the key of a dictionary entry (returns a shareable string
 *         object handle)
 *
 *  This function finds the (@c n + 1)th entry in the specified dictionary and
 *  returns a handle to the entry's key. For example, if @c n is 3, a handle to
 *  the key of the fourth entry is returned. The returned shareable string
 *  object handle is owned by the dictionary, and remains valid until the
 *  dictionary handle is destroyed.
 *
 *  @param dict  A dictionary object handle.
 *  @param n     The 0-based index of the entry whose key is returned.
 *
 *  @return A shareable string object handle to the key of the specified entry
 *          if it's found, or a null pointer if it isn't found.
 */
const strm_string_t *strm_dict_key_rstr( const strm_dict_t *dict, size_t n );

/**
 *  @brief Find the value of a dictionary entry based on the entry's index
 *         (returns a shareable string object handle)
 *
 *  This function finds the (@c n + 1)th entry in the dictionary, and returns a
 *  handle to shareable string object containing the entry's value. For example,
 *  if @c n is 3, a handle to a shareable string object containing the value of
 *  the fourth entry is returned. The returned string handle is owned by the
 *  dictionary object, and remains valid until the dictionary handle is
 *  destroyed.
 *
 *  @param dict  A dictionary object handle.
 *  @param n     The 0-based index of the entry whose key is returned.
 *
 *  @return A shareable string object handle to the key of the specified entry
 *          if it's found, or a null pointer if it isn't found.
 */
const strm_string_t *strm_dict_value_rstr( const strm_dict_t *dict, size_t n );



/**
 *  @brief Subtract one dictionary from another
 *
 *  This function creates a replica of the @c left dictionary object and removes
 *  all those entries that have matching keys in the @c right object regardless
 *  of their value.
 *
 *  Note that the @c left dictionary object handle is consumed by this function,
 *  even on a failure, but the @c right is not. If the same handle is passed for
 *  both arguments, this function destroys that handle and returns a new handle
 *  to an empty dictionary object.
 *
 *  @param left   A handle to the first dictionary object.
 *  @param right  A handle to the second dictionary object.
 *
 *  @return A new handle to the resulting dictionary object on success, or a
 *          null pointer on failure.
 */
strm_dict_t *strm_dict_subtract( strm_dict_t *left, strm_dict_t const *right );

/**
 *  @brief Compare two dictionaries
 *
 *  This function compares two dictionaries. It creates a replica of @e newdict
 *  and removes all those entries that also exist in @e olddict and have the
 *  same value. In other words, if @e olddict is the older version of some
 *  dictionary and @e newdict is the newer version, the resulting dictionary
 *  contains the entries that were changed or added, but not the ones that were
 *  left alone or deleted.
 *
 *  This function destroys the @e newdict handle, even on a failure. If the same
 *  handle is passed for both arguments, this function destroys it and returns a
 *  new handle to an empty dictionary object.
 *
 *  @param newdict  A handle to the newer version of a dictionary object.
 *  @param olddict  A handle to the older version of a dictionary object.
 *
 *  @return A handle to the dictionary object containing the result of the
 *          comparison, or a null pointer on failure.
 */
strm_dict_t *strm_dict_compare( strm_dict_t *newdict, strm_dict_t const *olddict );


__END_DECLS

#endif



__SRCVERSION( "$URL$ $Rev$" )
