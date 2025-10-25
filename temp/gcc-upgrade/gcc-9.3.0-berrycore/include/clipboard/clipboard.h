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

#ifndef CLIPBOARD_H_
#define CLIPBOARD_H_

#include <sys/platform.h>
#include <inttypes.h>

__BEGIN_DECLS


/**
 * Returns the path of the clipboard.
 *
 * @param buffer
 *  The pointer to the buffer that will hold the path
 *
 * @param
 *  The length of the buffer.
 *
 * @return
 *  0 on success, -1 otherwise.
 */
int get_clipboard_path(char* buffer, const unsigned int len);

/**
 * Sets the application's clipboard path. There is a system defined clipboard
 * path that is specific to the perimeter where the application is running.
 * However, the application may decide to create another clipboard only for
 * its own use.  Hybrid applications may also use this function to switch
 * to the public clipboard for another perimeter.  Hybrid applications may
 * process content from multiple perimeters.
 *
 * NOTE: The path provided must be exclusively for use by the clipboard.
 * empty_clipboard deletes all the files from the directory regardless of
 * origin.
 *
 * @param new_path
 *  The full directory path pointing to the root of the clipboard. Set to NULL
 *  to restore default path.
 *
 * @param len
 *  The length of the directory path. Must be less then PATH_MAX.
 *
 * @returns
 *  0 on success, -1 otherwise.
 *
 */
int set_clipboard_path(const char* new_path, const unsigned int len);

/**
 * Determines whether the clipboard will restrict clipboard data that can be
 * accessed based on the current clipboard path. To prevent the improper mixing
 * of data from different perimeters, a hybrid application's access to clipboard
 * data is normally denied if the perimeter associated with the current clipboard 
 * contents is incompatible with the destination of that data as determined
 * by the path setby set_clipboard_path.  This function allows an alternative
 * mode where the clipboard will not restrict access to any clipboard data but 
 * instead will not permit any data to be saved as it may contain mixed content. 
 * For single perimeter applications the use of this function has no affect on
 * the ability of the application to access clipboard data.
 *
 * @param check
 *  If non-zero, all read access of clipboard data will verify perimeters, if zero
 *  checks will be not be made but the clipboard will be readonly.
 */
void set_clipboard_check_perimeters(int check);

/**
 * Determines if writes to the clipboard are allowed.
 *
 * @returns
 *  0 if writes are allowed, -1 otherwise
 */
int get_clipboard_can_write();

/**
 * Writes the specified data as the specified type. An application
 * should call empty_clipboard() prior to writing any data to the clipboard.
 * This is required to ensure consistency in the clipboard data.
 *
 * @see empty_clipboard()
 *
 * To get extended error information, read errno.
 *
 * @param type
 *  The type of the data. The type can be any valid string.
 *  There are no built in types. If the type is already in the clipboard
 *  then the existing data of that type gets replaced.
 *
 *  The recommendation is to use Internet Media Types. The three most common
 *  Internet Media Types used on the PlayBook are:
 *      text/plain
 *      text/html
 *      text/rtf
 *
 *  With regards to RTF, text/rtf should be used as application/rtf is not
 *  supported universally on the platform.
 *
 *@param size
 *  The size of the data being written.
 *
 * @param  buffer
 *  The data to add to the clipboard.
 *
 * @return
 *  The number of bytes written, or -1 on error. errno is set.
 */
int set_clipboard_data(
        const char* type,
        const unsigned int size,
        const char* buffer);

/**
 * Reads the clipboard data of the specified type.
 *
 * To get extended error information, read errno.
 *
 * @param type
 *  The type of clipboard data to read.
 *
 * @param pbuffer
 *  The address of the buffer to take the clipboard contents.
 *  The caller must free the memory when they are done.
 *
 * @return
 *  The size of the returned buffer, or -1 on error. errno is set.
 *
 *  An errno of EACCES indicates that the content type exists
 *  but it is not available to the current user; e.g., the
 *  content may be work data that can only be used within
 *  work perimeters.
 */
unsigned int get_clipboard_data(const char* type, char** pbuffer);

/**
 * Reads the clipboard data of the specified type without updating
 * the read time.  Normal reads of the clipboard should use
 * get_clipboard_data, this function is only intended for special
 * circumstances where the clipboard must be read without appearing
 * to have been read.
 *
 * To get extended error information, read errno.
 *
 * @param type
 *  The type of clipboard data to read.
 *
 * @param pbuffer
 *  The address of the buffer to take the clipboard contents.
 *  The caller must free the memory when they are done.
 *
 * @return
 *  The size of the returned buffer, or -1 on error. errno is set.
 *
 *  An errno of EACCES indicates that the content type exists
 *  but it is not available to the current user; e.g., the
 *  content may be work data that can only be used within
 *  work perimeters.
 */
int get_clipboard_data_no_time_update(const char* type, char** pbuffer);

/**
 * Empties the clipboard of all data.
 *
 * To get extended error information, read errno.
 *
 * @return
 *  0 on success, -1 otherwise. errno is set.
 */
int empty_clipboard(void);

/**
 * Deletes the specified clipboard type from the clipboard.
 *
 * @param type
 *  The clipboard type to delete from the clipboard.
 *
 * @return
 *  0 on success, -1 otherwise. errno is set.
 */
int empty_clipboard_by(const char* type);

/**
 * Allows a caller to query the clipboard for a supported type.
 *
 * To get extended error information, read errno.
 *
 * @param type
 *  The type to query for. This can be any user defined type.
 *
 * @return
 *  0 if it exists, -1 otherwise. errno is set.
 *
 *  An errno of EACCES indicates that the content type exists
 *  but it is not available to the current user; e.g., the
 *  content may be work data that can only be used within
 *  work perimeters.
 */
int is_clipboard_format_present(const char* type);

/**
 * Allows a caller to query the clipboard path used for a
 * particular content type.
 *
 * To get extended error information, read errno.
 *
 * @param type
 *  The type to query for. This can be any user defined type.
 *
 * @param buffer
 *  The pointer to the buffer that will hold the path
 *
 * @param
 *  The length of the buffer.
 *
 * @return
 *  0 on success, -1 otherwise.
 */
int get_clipboard_format_path(const char* type, char* buffer, int len);

/**
 * Return the time the clipboard was last read.  The time is returned in nanoseconds
 * based on CLOCK_MONOTONIC.  If the clipboard has not been read since it was 
 * last written, 0 is returned.
 *
 * @return
 *  Time of last read
 */
uint64_t clipboard_read_time();

/**
 * Return the time the clipboard was last written.  The time is returned in nanoseconds
 * based on CLOCK_MONOTONIC.
 *
 * @return
 *  Time of last write
 */
uint64_t clipboard_write_time();

__END_DECLS

#endif /* CLIPBOARD_H_ */
