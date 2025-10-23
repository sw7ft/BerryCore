/*
 * $QNXLicenseC:
 * Copyright 2009, 2010, QNX Software Systems. All Rights Reserved.
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

#ifndef _PPS_H_INCLUDED
#define _PPS_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#ifndef _STDIO_H_INCLUDED
#include <stdio.h>
#endif

#ifndef _STDINT_H_INCLUDED
#include <stdint.h>
#endif

#ifndef _STDBOOL_H_INCLUDED
#include <stdbool.h>
#endif

__BEGIN_DECLS

struct pps_node;
typedef struct pps_node pps_node_t;

struct pps_node {
    uint8_t type;
    int8_t flags;
    uint16_t reserved;
    pps_node_t *parent;
    pps_node_t *next;
    union {
        int index;
        char *name;
    } id;
    union {
        char *str;
        double number;
        int64_t integer;
        struct {
            int count;
            struct pps_node *first_child;
        } children;
    } value;
};

typedef struct {
    pps_node_t *node;
} pps_decoder_state_t;

typedef enum {
    PPS_DECODER_OK = 0,
    /* Failed to allocate memory during parsing */
    PPS_DECODER_NO_MEM = 1,
    /* Request for the wrong type of data */
    PPS_DECODER_BAD_TYPE = 2,
    /* Requested item was not found */
    PPS_DECODER_NOT_FOUND = 3,
    /* Parse error parsing JSON data */
    PPS_DECODER_PARSE_ERROR = 4,
    /* Requested item had been deleted  */
    PPS_DECODER_DELETED = 5,
    /* Numeric conversion was out of range or would lose precision */
    PPS_DECODER_CONVERSION_FAILED = 6,
    /* Call to pps_decoder_pop while at root of tree */
    PPS_DECODER_POP_AT_ROOT = 7,
} pps_decoder_error_t;


typedef enum {
    PPS_TYPE_NULL,
    PPS_TYPE_BOOL,
    PPS_TYPE_NUMBER,
    PPS_TYPE_STRING,
    PPS_TYPE_ARRAY,
    PPS_TYPE_OBJECT,
    /* Value returned when requesting the type of a non-existent attribute */
    PPS_TYPE_NONE,
    /* Value returned for an attribute that exists but was invalid or not
     *  recognised.
     */
    PPS_TYPE_UNKNOWN,
    /* The type returned by a deleted attribute */
    PPS_TYPE_DELETED,
} pps_node_type_t;

#define PPS_DECODER_INITIAL_NODES 40

typedef struct {
    pps_node_t nodes[PPS_DECODER_INITIAL_NODES];
    pps_node_t *current_node;
    pps_decoder_error_t status;
    char *error;
} pps_decoder_t;

/** Initialize the decoder structure from an unknown state.
 *
 * @param decoder   The pps decoder structure
 * @param str       An initial null terminated string to parse.  This may be NULL in
 *                  which case pps_decoder_parse_pps_str must be called to parse the
 *                  string.
 *
 * @return  PPS_DECODER_OK on success.
 */
pps_decoder_error_t pps_decoder_initialize(pps_decoder_t *decoder, char *str);

/* Deprecated - use pps_decoder_initialize instead */
pps_decoder_error_t pps_decoder_init(pps_decoder_t *decoder, char *buffer, int len) __attribute__((__deprecated__));

/** Parse a string of PPS formatted data.  The function supports a number of
 * PPS attribute encodings including the null encoding, c for C strings, b
 * for Booleans, n for numbers and json for JSON (http://www.json.org).
 * The data passed into pps_decoder_parse_pps_str must be null terminated.
 * For efficiency, data is typically not copied, following a call to 
 * pps_decoder_parse_pps_str the string will have been modified and the pps_decoder_t 
 * structure will contain pointers into it.  If the string is modified in any way after 
 * calling pps_decoder_parse_pps_str the result of calling any data access or navigation
 * function is undefined.
 *
 * @param decoder   The pps decoder structure
 * @param str       A pointer to a string containing PPS data.
 *
 * @return PPS_DECODER_OK on success.
 */
pps_decoder_error_t pps_decoder_parse_pps_str(pps_decoder_t *decoder, char *str);

/* Deprecated - use pps_decoder_parse_pps_str */
pps_decoder_error_t pps_decoder_parse(pps_decoder_t *decoder, char *buffer, int len) __attribute__((__deprecated__));

/** Parse a string of JSON formatted data.  Other than the format of the data
 * the behavior of this function is as for pps_decoder_parse_pps_str.
 * @param decoder   The pps decoder structure
 * @param str       A pointer to a string containing PPS data.
 *
 * @return PPS_DECODER_OK on success.
 */
pps_decoder_error_t pps_decoder_parse_json_str(pps_decoder_t *decoder, char *str);

/* Deprecated - use pps_decoder_parse_json_str */
pps_decoder_error_t pps_decoder_parse_json(pps_decoder_t *decoder, char *buffer, int len) __attribute__((__deprecated__));

/** Cleanup a pps_decoder_t structure freeing any allocated memory.  Calling
 * this is required only when the structure is no longer to be used.  It is
 * not necessary to call pps_decoder_cleanup between calls to pps_decoder_parse_pps_str
 * or pps_decoder_parse_json_str.
 *
 * @param decoder   The pps decoder structure
 */
void pps_decoder_cleanup(pps_decoder_t *decoder);

/** Reset the pps_decoder_t structure so that it is positioned at the root
 * node, the state it is in immediately after parsing data.
 *
 * @param decoder   The pps decoder structure
 */
void pps_decoder_reset(pps_decoder_t *decoder);

/** Return the current error status of the decoder.  Any attempt to extract
 * data or push into objects that results in an error sets the the decoder
 * to an error state.  Rather than checking return codes after every operation
 * one may alternatively perform a series and check if the entire set completed
 * successfully.
 *
 * @param decoder   The pps decoder structure
 * @param clear     If true, the error state is reset following the call.
 *
 * @return The error state of the decoder.
 */
pps_decoder_error_t pps_decoder_status(pps_decoder_t *decoder, bool clear);

/** Searches for the node of the given name in the current object and positions the decoder
 * at that node.
 *
 * @param decoder   The pps decoder structure
 * @param name      The name of the property/attribute to set the position to.
 *
 * @return PPS_DECODER_OK on success or PPS_DECODER_NOT_FOUND if the indicated node did
 *         not exist.
 */
pps_decoder_error_t pps_decoder_set_position(pps_decoder_t *decoder, const char *name);

/** Returns the data type of the current node or the node of the given name (if
 * currently with an object).  The name "." can be used for the current
 * object/array as a means of determining if one is within an object or an
 * array.
 *
 * @param decoder   The pps decoder structure
 * @param name      The name of the property/attribute to provide the type
 *                  for.  If NULL, the type of the current node is returned.
 *
 * @return The data type of the referenced node.
 */
pps_node_type_t pps_decoder_type(pps_decoder_t *decoder, const char *name);

/** Returns true if the current node or the node of the given name (if
 * currently within an object) is an integer.
 *
 * @param decoder   The pps decoder structure
 * @param name      The name of the property/attribute to examine. If NULL, 
 *                  the type of the current node is used.
 *
 * @return true if the referenced node is an integer.
 */
bool pps_decoder_is_integer(pps_decoder_t *decoder, const char *name);

/** Return the flags associated with either the current node or the node
 * of the specified name,
 * @param decoder   The pps decoder structure
 * @param name      The name of the property/attribute to provide the flags
 *                  for.  If NULL, the type of the current node is returned.
 *
 * @return The flags, the values of the flags are given by the
 *  pps_attrib_flags_t enumeration.
 */
int pps_decoder_flags(pps_decoder_t *decoder, const char *name);

/** Descend into an array or object. If successful subsequent data will
 * be returned for properties or elements of that object or array.
 *
 * @param decoder   The pps decoder structure
 * @param name      The name of the property/attribute to descend into.
 *
 * @return PPS_DECODER_OK on success, PPS_DECODER_BAD_TYPE if there was a
 *         type mismatch, PPS_DECODER_DELETED if the attribute is deleted or
 *         PPS_DECODER_NOT_FOUND if the indicated node did not exist.
 */
pps_decoder_error_t pps_decoder_push(pps_decoder_t *decoder, const char *name);

/** Descend into an object. If successful subsequent data will be
 * returned for properties or elements of that object.  This is 
 * identical to pps_decoder_push except that the function will fail if
 * the element is not an object.
 *
 * @param decoder   The pps decoder structure
 * @param name      The name of the property/attribute to descend into.
 *
 * @return PPS_DECODER_OK on success, PPS_DECODER_BAD_TYPE if there was a
 *         type mismatch, PPS_DECODER_DELETED if the attribute is deleted or
 *         PPS_DECODER_NOT_FOUND if the indicated node did not exist.
 */
pps_decoder_error_t pps_decoder_push_object(pps_decoder_t *decoder, const char *name);

/** Descend into an array. If successful subsequent data will be
 * returned for properties or elements of that array.  This is 
 * identical to pps_decoder_push except that the function will fail if
 * the element is not an array.
 *
 * @param decoder   The pps decoder structure
 * @param name      The name of the property/attribute to descend into.
 *
 * @return PPS_DECODER_OK on success, PPS_DECODER_BAD_TYPE if there was a
 *         type mismatch, PPS_DECODER_DELETED if the attribute is deleted or
 *         PPS_DECODER_NOT_FOUND if the indicated node did not exist.
 */
pps_decoder_error_t pps_decoder_push_array(pps_decoder_t *decoder, const char *name);

/** Pop back to an object or array's parent.  Following this call, the
 * current node will be the node that follows the object or array popped out
 * of.
 *
 * @param decoder   The pps decoder structure
 *
 * @return PPS_DECODER_OK on success or PPS_DECODER_POP_AT_ROOT if already 
 *         positioned at the root node.
 */
pps_decoder_error_t pps_decoder_pop(pps_decoder_t *decoder);

/** Return the number of elements or properties in the current object or array.
 *
 * @param decoder   The pps decoder structure
 *
 * @return The property/element count.
 */
int pps_decoder_length(pps_decoder_t *decoder);

/** Return the name of the current node.  This is only applicable if currently
 * within an object.
 *
 * @param decoder   The pps decoder structure
 *
 * @return The current node's name
 */
const char *pps_decoder_name(pps_decoder_t *decoder);

/** Advance to the next node in the current object/array
 *
 * @param decoder   The pps decoder structure
 *
 * @return PPS_DECODER_OK on success, PPS_DECODER_NOT_FOUND if there is no
 *         next property/element.
 */
pps_decoder_error_t pps_decoder_next(pps_decoder_t *decoder);

/** Advance to the indicated element or property of an array or object.
 *
 * @param decoder   The pps decoder structure
 * @param index     The index of the element to go to.  The first element is
 *                  index 0.
 *
 * @return PPS_DECODER_OK on success, PPS_DECODER_NOT_FOUND if the indicated
 *         element does not exist.
 */
pps_decoder_error_t pps_decoder_goto_index(pps_decoder_t *decoder, int index);

/** Return the current state of the decoder. Getting the state allows the
 * decoder to be returned to the same state after a sequence of data extraction
 * or navigation calls.
 *
 * @param decoder   The pps decoder structure
 * @param state     A pointer to a structure to hold the state.
 */
void pps_decoder_get_state(pps_decoder_t *decoder, pps_decoder_state_t *state);

/** Return the decoder to a state obtained by a call to pps_decoder_get_state.
 *
 * @param decoder   The pps decoder structure
 * @param state     A pointer to a structure containing the decoder's state.
 */
void pps_decoder_set_state(pps_decoder_t *decoder, pps_decoder_state_t *state);

/** Extract a Boolean value from the current node or the node of a given name.
 * Following successful extraction, the decoder advances to the next node.
 *
 * @param decoder   The pps decoder structure
 * @param name      The name of the property to extract the value from or NULL
 *                  to extract the data from the current node.
 * @param value     A pointer to take the result.
 *
 * @return PPS_DECODER_OK on success, PPS_DECODER_BAD_TYPE if there was a
 *         type mismatch, PPS_DECODER_DELETED if the attribute is deleted or
 *         PPS_DECODER_NOT_FOUND if the indicated node did not exist.
 */
pps_decoder_error_t pps_decoder_get_bool(pps_decoder_t *decoder, const char *name, bool *value);

/** Extract an integer value from the current node or the node of a given name.
 * Following successful extraction, the decoder advances to the next node.
 *
 * @param decoder   The pps decoder structure
 * @param name      The name of the property to extract the value from or NULL
 *                  to extract the data from the current node.
 * @param value     A pointer to take the result.
 *
 * @return PPS_DECODER_OK on success, PPS_DECODER_BAD_TYPE if there was a
 *         type mismatch, PPS_DECODER_CONVERSION_FAILED if the number was not an 
 *         integer or was out of the range of an int type, PPS_DECODER_DELETED if
 *         the attribute is deleted or PPS_DECODER_NOT_FOUND if the indicated node
 *         did not exist.
 */
pps_decoder_error_t pps_decoder_get_int(pps_decoder_t *decoder, const char *name, int *value);

/** Extract a 64bit integer value from the current node or the node of a given name.
 * Following successful extraction, the decoder advances to the next node.
 *
 * @param decoder   The pps decoder structure
 * @param name      The name of the property to extract the value from or NULL
 *                  to extract the data from the current node.
 * @param value     A pointer to take the result.
 *
 * @return PPS_DECODER_OK on success, PPS_DECODER_BAD_TYPE if there was a
 *         type mismatch, PPS_DECODER_CONVERSION_FAILED if the number was not an 
 *         integer or was out of the range of an int64_t type, PPS_DECODER_DELETED if
 *         the attribute is deleted or PPS_DECODER_NOT_FOUND if the indicated node
 *         did not exist.
 */
pps_decoder_error_t pps_decoder_get_int64(pps_decoder_t *decoder, const char *name, int64_t *value);

/** Extract a double value from the current node or the node of a given name.
 * Following successful extraction, the decoder advances to the next node.
 *
 * @param decoder   The pps decoder structure
 * @param name      The name of the property to extract the value from or NULL
 *                  to extract the data from the current node.
 * @param value     A pointer to take the result.
 *
 * @return PPS_DECODER_OK on success, PPS_DECODER_BAD_TYPE if there was a
 *         type mismatch, PPS_DECODER_CONVERSION_FAILED if the conversion from an integer
 *         would lose precision, PPS_DECODER_DELETED if the attribute is deleted or
 *         PPS_DECODER_NOT_FOUND if the indicated node did not exist.
 */
pps_decoder_error_t pps_decoder_get_double(pps_decoder_t *decoder, const char *name, double *value);

/** Extract a string value from the current node or the node of a given name.
 * Following successful extraction, the decoder advances to the next node.
 *
 * @param decoder   The pps decoder structure
 * @param name      The name of the property to extract the value from or NULL
 *                  to extract the data from the current node.
 * @param value     A pointer to take the result.  Note that the resulting
 *                  string is a pointer into the original buffer.
 *
 * @return PPS_DECODER_OK on success, PPS_DECODER_BAD_TYPE if there was a
 *         type mismatch, PPS_DECODER_DELETED if the attribute is deleted or
 *         PPS_DECODER_NOT_FOUND if the indicated node did not exist.
 */
pps_decoder_error_t pps_decoder_get_string(pps_decoder_t *decoder, const char *name, const char **value);

/** Dump the contents of the decoded data in human readable format to a given
 * file pointer.
 *
 * @param decoder   The pps decoder structure
 * @param fp        The file pointer to write to.
 */
void pps_decoder_dump_tree(pps_decoder_t *decoder, FILE *fp);

typedef enum {
    PPS_ENCODER_OK = 0,
    /* Failed to allocate memory during encoding */
    PPS_ENCODER_NO_MEM = 1,
    /* Improper object/array nesting */
    PPS_ENCODER_BAD_NESTING = 2,
    /* Attempt to add an invalid value to an encoder */
    PPS_ENCODER_INVALID_VALUE = 3,
    /* Attempt to add a PPS attribute with no attribute name */
    PPS_ENCODER_MISSING_ATTRIBUTE_NAME = 4,
    /* Attempt to add a non-existent property of a decoder */
    PPS_ENCODER_NOT_FOUND = 5,
} pps_encoder_error_t;

typedef enum {
    /* Encode entirely as JSON.  Default is to encode as PPS though this automatically switches
       to JSON encoding for complex attributes.
    */
    PPS_ENCODER_ENCODE_JSON = 1,
    /* Clear any allocated memory prior to freeing it. */
    PPS_ENCODER_CLEAR_MEMORY = 2,
} pps_encoder_option_t;

typedef struct {
    char *buffer;
    int allocated;
    int length;
    /* Nesting level for objects.  Determines if objects are encoded PPS or
     * JSON style
     */
    int level;
    int options;
    /* Tracks if pps_encoder_start_object is called with a PPS object name. */
    bool in_pps_obj;
    pps_encoder_error_t status;
} pps_encoder_t;



/** Initialize an encoder structure from an unknown state.
 *
 * @param encoder       The pps encoder structure
 * @param encodeJSON    If true data will be encoded as JSON rather than PPS.
 */
void pps_encoder_initialize(pps_encoder_t *encoder, bool encodeJSON);

/* Deprecated - equivalent to pps_encoder_initialize */
void pps_encoder_init(pps_encoder_t *encoder, bool encodeJSON) __attribute__((__deprecated__));

/** Enable a given option.  Option states typically should only be changed immediately
 * after calling pps_encoder_initialize, pps_encoder_cleanup or pps_encoder_reset
 *
 * @param encoder       The pps encoder structure
 * @param option        The option to enable
 *
 */
void pps_encoder_set_option(pps_encoder_t *encoder, pps_encoder_option_t option);

/** Disable a given option.  Option states typically should only be changed immediately
 * after calling pps_encoder_initialize, pps_encoder_cleanup or pps_encoder_reset
 *
 * @param encoder       The pps encoder structure
 * @param option        The option to disable
 *
 */
void pps_encoder_clear_option(pps_encoder_t *encoder, pps_encoder_option_t option);

/** Cleanup an encoder structure, releasing any allocated memory.
 *
 * @param encoder   The pps encoder structure
 */
void pps_encoder_cleanup(pps_encoder_t *encoder);

/** Reset an encoder prior to encoding new data.  It is typically preferred
 * to call pps_encoder_reset rather than pps_encoder_cleanup if the encoder is
 * to be re-used as by using pps_encoder_reset the encoder will eventually
 * acquire a buffer large enough such that it will require no subsequent
 * memory allocation.
 *
 * @param encoder   The pps encoder structure
 */
void pps_encoder_reset(pps_encoder_t *encoder);

/** Return the current length of the data encoded by the encoder.
 *
 * @param encoder   The pps encoder structure
 *
 * @return The length
 */
int pps_encoder_length(pps_encoder_t *encoder);

/** Return a pointer to the buffer holding the encoded data.  This returns
 * a valid pointer only if there have been no errors and all objects have
 * been closed off, thus a NULL pointer can either indicate an error situation
 * or incomplete data.
 *
 * @param encoder   The pps encoder structure
 *
 * @return A pointer to the encoder buffer or NULL if not available.
 */
const char *pps_encoder_buffer(pps_encoder_t *encoder);

/** Add an attribute to the current object that is marked as being deleted.
 * This call is only valid if encoding PPS data and only when called at the
 * highest level.
 *
 * @param encoder   The pps encoder structure
 * @param name      The name of the deleted attribute
 *
 * @return The encoder status, PPS_ENCODER_OK if no error.  The status is sticky,
 *         if a call to encode something fails, all subsequent calls will show
 *         failure until the encoder is reset.
 */
pps_encoder_error_t pps_encoder_delete_attribute(pps_encoder_t *encoder, const char *name);

/** Start a new object.  Subsequent properties are added to this object.
 *
 * @param encoder   The pps encoder structure
 * @param name      If this object is within another object, name provides
 *                  the object's property name.  If the object is an element
 *                  of an array, this must be NULL.
 *
 * @return The encoder status, PPS_ENCODER_OK if no error.  The status is sticky,
 *         if a call to encode something fails, all subsequent calls will show
 *         failure until the encoder is reset.
 */
pps_encoder_error_t pps_encoder_start_object(pps_encoder_t *encoder, const char *name);

/** End the current object, returning to the object's parent object or array.
 *
 * @param encoder   The pps encoder structure
 *
 * @return The encoder status, PPS_ENCODER_OK if no error.  The status is sticky,
 *         if a call to encode something fails, all subsequent calls will show
 *         failure until the encoder is reset.
 */
pps_encoder_error_t pps_encoder_end_object(pps_encoder_t *encoder);

/** Start a new array.  Subsequent elements are added to this array.
 *
 * @param encoder   The pps encoder structure
 * @param name      The name of this array if it is embedded in an object. This
 *                  must be NULL if contained within an array.
 *
 * @return The encoder status, PPS_ENCODER_OK if no error.  The status is sticky,
 *         if a call to encode something fails, all subsequent calls will show
 *         failure until the encoder is reset.
 */
pps_encoder_error_t pps_encoder_start_array(pps_encoder_t *encoder, const char *name);

/** End the current array, returning to the array's parent object or array.
 *
 * @param encoder   The pps encoder structure
 *
 * @return The encoder status, PPS_ENCODER_OK if no error.  The status is sticky,
 *         if a call to encode something fails, all subsequent calls will show
 *         failure until the encoder is reset.
 */
pps_encoder_error_t pps_encoder_end_array(pps_encoder_t *encoder);

/** Add a null to the current object or array.
 *
 * @param encoder   The pps encoder structure
 * @param name      If currently within an object, the name of the property
 *                  associated with this element.  If within an array, this
 *                  must be null.
 *
 * @return The encoder status, PPS_ENCODER_OK if no error.  The status is sticky,
 *         if a call to encode something fails, all subsequent calls will show
 *         failure until the encoder is reset.
 */
pps_encoder_error_t pps_encoder_add_null(pps_encoder_t *encoder, const char *name);

/** Add a Boolean to the current object or array.
 *
 * @param encoder   The pps encoder structure
 * @param name      If currently within an object, the name of the property
 *                  associated with this element.  If within an array, this
 *                  must be null.
 * @param value     The value to add.
 *
 * @return The encoder status, PPS_ENCODER_OK if no error.  The status is sticky,
 *         if a call to encode something fails, all subsequent calls will show
 *         failure until the encoder is reset.
 */
pps_encoder_error_t pps_encoder_add_bool(pps_encoder_t *encoder, const char *name, bool value);

/** Add an integer to the current object or array.
 *
 * @param encoder   The pps encoder structure
 * @param name      If currently within an object, the name of the property
 *                  associated with this element.  If within an array, this
 *                  must be null.
 * @param value     The value to add.
 *
 * @return The encoder status, PPS_ENCODER_OK if no error.  The status is sticky,
 *         if a call to encode something fails, all subsequent calls will show
 *         failure until the encoder is reset.
 */
pps_encoder_error_t pps_encoder_add_int(pps_encoder_t *encoder, const char *name, int value);

/** Add a 64bit integer to the current object or array.
 *
 * @param encoder   The pps encoder structure
 * @param name      If currently within an object, the name of the property
 *                  associated with this element.  If within an array, this
 *                  must be null.
 * @param value     The value to add.
 *
 * @return The encoder status, PPS_ENCODER_OK if no error.  The status is sticky,
 *         if a call to encode something fails, all subsequent calls will show
 *         failure until the encoder is reset.
 */
pps_encoder_error_t pps_encoder_add_int64(pps_encoder_t *encoder, const char *name, int64_t value);

/** Add a double to the current object or array.
 *
 * @param encoder   The pps encoder structure
 * @param name      If currently within an object, the name of the property
 *                  associated with this element.  If within an array, this
 *                  must be null.
 * @param value     The value to add.
 *
 * @return The encoder status, PPS_ENCODER_OK if no error.  The status is sticky,
 *         if a call to encode something fails, all subsequent calls will show
 *         failure until the encoder is reset.
 */
pps_encoder_error_t pps_encoder_add_double(pps_encoder_t *encoder, const char *name, double value);

/** Add a string to the current object or array.
 *
 * @param encoder   The pps encoder structure
 * @param name      If currently within an object, the name of the property
 *                  associated with this element.  If within an array, this
 *                  must be null.
 * @param value     The value to add.
 *
 * @return The encoder status, PPS_ENCODER_OK if no error.  The status is sticky,
 *         if a call to encode something fails, all subsequent calls will show
 *         failure until the encoder is reset.
 */
pps_encoder_error_t pps_encoder_add_string(pps_encoder_t *encoder, const char *name, const char *value);

/** Add a JSON encoded string to the current object or array.
 *
 * @param encoder   The pps encoder structure
 * @param name      If currently within an object, the name of the property
 *                  associated with this element.  If within an array, this
 *                  must be null.
 * @param value     The value to add.
 *
 * @return The encoder status, PPS_ENCODER_OK if no error.  The status is sticky,
 *         if a call to encode something fails, all subsequent calls will show
 *         failure until the encoder is reset.
 */
pps_encoder_error_t pps_encoder_add_json(pps_encoder_t *encoder, const char *name, const char *value);

/** Add part or all of the contents of a pps decoder.  This allows data to be re-encoded
 *  that was previously decoded.  Upon completion of the call the decoder is left in the 
 *  same state as at the time of the call.
 *
 * @param encoder   The pps encoder structure
 * @param name      If currently within an object, the name of the property
 *                  associated with this element.  If within an array, this
 *                  must be null.
 * @param decoder   A pps decoder structure.
 * @param propName  The name of the property add from the decoder.  If NULL, adds the
 *                  node at the current position.
 *
 * @return The encoder status, PPS_ENCODER_OK if no error.  The status is sticky,
 *         if a call to encode something fails, all subsequent calls will show
 *         failure until the encoder is reset.
 */
pps_encoder_error_t pps_encoder_add_from_decoder(pps_encoder_t *encoder, const char *name, pps_decoder_t *decoder, const char *propName);


typedef enum {
    /** Invalid line of pps data
     */
    PPS_ERROR = -1,
    /** End of data or incomplete line.  When data is from pps itself, will
     * always indicated end of data.
     */
    PPS_END = 0,
    /** Indicates data for the given object follows
     */
    PPS_OBJECT = 1,
    /** Indicates the creation of an object
     */
    PPS_OBJECT_CREATED = 2,
    /** Indicates the deletion of an object
     */
    PPS_OBJECT_DELETED = 3,
    /** Indicates the truncation of an object (removal of all attributes)
     */
    PPS_OBJECT_TRUNCATED = 4,
    /** Indicates the updating of an attribute.
     */
    PPS_ATTRIBUTE = 5,
    /** Indicates the deletion of an attribute.
     */
    PPS_ATTRIBUTE_DELETED = 6,
    /** Indicates that there was an overflow in the data queued for an object.
     */
    PPS_OBJECT_OVERFLOWED = 7,
} pps_status_t;

typedef enum {
    /* Not a complete line */
    PPS_INCOMPLETE = 1,
    PPS_DELETED = 2,
    PPS_CREATED = 4,

    /** An object was truncated thus all attributes have been removed.
     */
    PPS_TRUNCATED = 8,

    /** Non-persistent attributes in object purged due to a critical writer
     * closing its connection.
     */
    PPS_PURGED = 0x10,

    /** Queued data overflowed as it was not read fast enough.
     */
    PPS_OVERFLOWED = 0x20
} pps_attrib_flags_t;

typedef enum {
    PPS_NOPERSIST = 1,
    PPS_ITEM = 2
} pps_options_t;

typedef struct {
    /** Name of last object encountered.  This should be normally be
     * initialized by the caller before the first call to ppsparse as it is set
     * only in the case of an object name being encountered.
     */
    char *obj_name;

    /** Index of obj_name in objnames array or -1 if not found or objnames
     * was NULL.  This should be normally be initialized by the caller before
     * the first call to ppsparse as it is set only in the case of an object
     * name being encountered.
     */
    int obj_index;

    /** Name of attribute from the line of pps data just parsed or NULL in
     * case of an error or if there was no attribute name.
     */
    char *attr_name;

    /** Index of attr_name in attrnames array or -1 if not found or attrnames
    * was NULL.
    */
    int attr_index;

    /** String indicating the encoding of an attribute.  Only meaningful if the
     * return value of ppsparse is PPS_ATTRIBUTE.
     */
    char *encoding;

    /** The value of an attribute.  Only meaningful if the return value of
     * ppsparse is PPS_ATTRIBUTE.
     */
    char *value;

    /** Flags indicating the presence of the '+', '-' or '#' flags on a line
     * or an indication that the line was incomplete.
     */
    int flags;

    /** Indicates non-negated options that were present within square brackets.
     */
    int options;

    /** A mask of the options that were provided in whether negated or
     * non-negated form.
     */
    int option_mask;

    /** The 'quality' of the attribute.
     */
    int quality;

    /** Pointer to the beginning of the line parsed by ppsparse.  This is
     * likely useful only in the case of an error or incomplete line as it will
     * otherwise have had characters changed to NUL characters to delimit names.
     */
    char *line;
    int reserved[3];
} pps_attrib_t;


/** Parse the next line from a buffer of pps data.
 * @param ppsdata   Pointer to a pointer to the current position in the buffer.
 *                  The buffer is modified by ppsparse and the pointer updated
 *                  to point to the start of the next line of data.
 * @param objnames  A NULL terminated array of object name strings.  If non-NULL
 *                  ppsparse will look up any object name it finds and provide
 *                  its index in the pps_attrib_t structure.
 * @params attrnames A NULL terminated array of attribute names.  If non-NULL,
 *                  ppsparse will look up any attribute name it finds and
 *                  provide its index in the pps_attrib_t structure.
 * @params info     A structure for returning information about a line of pps
 *                  data.
 * @param parse_flags  Not currently used.
 *
 * @return          Indication of type of line parsed, error or end of data.
 */
extern pps_status_t ppsparse(char **ppsdata, const char * const *objnames, const char * const *attrnames, pps_attrib_t *info, int parse_flags);

__END_DECLS

#endif


__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/pps/public/sys/pps.h $ $Rev: 731727 $" )
