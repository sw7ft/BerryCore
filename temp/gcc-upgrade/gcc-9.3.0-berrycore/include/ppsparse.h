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

#ifndef _PPS_H_INCLUDED
#define _PPS_H_INCLUDED

#include "mm/mmsupport.h"

__BEGIN_DECLS

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
} pps_status_t;

typedef enum {
	// Not a complete line 
	PPS_INCOMPLETE = 1,
	PPS_DELETED = 2,
	PPS_CREATED = 4,

	/** An object was truncated thus all attributes have been removed.
	 */
	PPS_TRUNCATED = 8,

	/** Non-persistent attributes in object purged due to a critical writer
	 * closing its connection.
	 */
	PPS_PURGED = 0x10
} pps_attrib_flags_t;

typedef enum {
	PPS_NOPERSIST = 1,
	PPS_ITEM = 2
} pps_options_t;

typedef struct {
	/** Name of last object encountered.  This should be normally be 
	 * initialised by the caller before the first call to ppsparse as it is set
	 * only in the case of an object name being encountered.
	 */
	char *obj_name;

	/** Index of obj_name in objnames array or -1 if not found or objnames
	 * was NULL.  This should be normally be initialised by the caller before 
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
	int	quality;

	/** Pointer to the beginning of the line parsed by ppsparse.  This is 
	 * likely useful only in the case of an error or incomplete line as it will
	 * otherwise have had characters changed to NUL characters to delimit names.
	 */
	char *line;
	int reserved[3];
} pps_attrib_t;


/** Parse the next line from a buffer of pps data.
 * @param ppsdata	Pointer to a pointer to the current position in the buffer.
 *					The buffer is modified by ppsparse and the pointer updated
 *					to point to the start of the next line of data.
 * @param objnames	A NULL terminated array of object name strings.  If non-NULL
 *					ppsparse will look up any object name it finds and provide
 *					its index in the pps_attrib_t structure.
 * @params attrnames A NULL terminated array of attribute names.  If non-NULL,
 *					ppsparse will look up any attribute name it finds and
 *					provide its index in the pps_attrib_t structure.
 * @params info		A structure for returning information about a line of pps 
 *					data.
 * @param parse_flags  Not currently used.
 *
 * @return 			Indication of type of line parsed, error or end of data.
 */
extern pps_status_t ppsparse(char **ppsdata, const char * const *objnames, 
							 const char * const *attrnames, pps_attrib_t *info, 
							 int parse_flags);


/* Temporary inclusion for compatibility */
extern int psparse(char **optionp, char * const *tokens, char **valuep, char **encoding);

__END_DECLS

#endif


__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/trunk/lib/pps/public/sys/pps.h $ $Rev: 219996 $" )

