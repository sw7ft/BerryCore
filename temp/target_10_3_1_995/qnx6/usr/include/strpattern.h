/*
 * Research In Motion Limited. Copyright (C) 2012-2013.
 * Research In Motion Limited. All rights reserved.
 */
/**
 * @file strpattern.h
 *
 * @brief Functions for the string pattern library
 *
 *
 * @since BlackBerry 10.0.0
 */
/**
 * @mainpage String pattern library
 *
 * The string pattern library provides functions to register strings containing
 * regular expressions, recognizers, and handlers which perform actions based
 * on those strings.
 *
 * Recognizers check for specific string patterns. Currently they check for
 * address, email address, phone number, PIN, SMS, and URL.
 */
#ifndef STRPATTERN_H_
#define STRPATTERN_H_

#include <unicode/utext.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief A return code that indicates that a function completed successfully
 *
 * @since BlackBerry 10.0.0
 */
#define STRPATTERN_EOK (0)
/**
 * @brief A return code that indicates that a function is out of memory
 *
 * @since BlackBerry 10.0.0
 */
#define STRPATTERN_ENOMEM (1)
/**
 * @brief A return code that indicates that a function has an invalid argument
 *
 * @since BlackBerry 10.0.0
 */
#define STRPATTERN_EINVAL (2)
/**
 * @brief A return code that indicates that a function does not have permission
 *
 * @since BlackBerry 10.0.0
 */
#define STRPATTERN_ENOPERMIT (4)
/**
 * @brief A return code that indicates that a function has a connection error
 *
 * @since BlackBerry 10.0.0
 */
#define STRPATTERN_ECONNECT (8)
/**
 * @brief A return code that indicates that a function has an invalid
 *        regular expression
 *
 * @since BlackBerry 10.0.0
 */
#define STRPATTERN_EREGEX (16)
/**
 * @brief A return code that indicates that a function is not found
 *
 * @since BlackBerry 10.0.0
 */
#define STRPATTERN_ENOTFOUND (32)
/**
 * @brief A return code that indicates that a function has a resource error
 *
 * @since BlackBerry 10.0.0
 */
#define STRPATTERN_ERESOURCE (64)
/**
 * @brief A return code that indicates that a function has a not specified error
 *
 * @since BlackBerry 10.0.0
 */
#define STRPATTERN_ENOTSPECIFIED (256)

/**
 * @brief The context for a pattern match
 *
 * The @c strpattern_context structure is an opaque handle. See
 * the corresponding context-related functions for the parameters
 * and their default values.
 *
 * @since BlackBerry 10.0.0
 */
typedef struct strpattern_context strpattern_context;

/**
 * @brief A pattern match
 *
 * The @c strpattern_match structure is an opaque handle obtained as a
 * result of analysis of text by the string pattern library. See the
 * corresponding match-related functions for the parameters and their
 * default values. A match represents a sequence of text that is
 * recognized as having a particular meaning. For example, as a
 * telephone number or address.
 *
 * @since BlackBerry 10.0.0
 */
typedef struct strpattern_match strpattern_match;

/**
 * @brief A regular expression registration
 *
 * The @c strpattern_regex_registration structure is an opaque handle.
 * See the corresponding regular expression registration-related functions
 * for the parameters and their default values.
 *
 *
 * @since BlackBerry 10.0.0
 */
typedef struct strpattern_regex_registration strpattern_regex_registration;

/**
 * @brief The signature of the callback which is called when the pattern
 *        matching of a given text is complete
 *
 * This function has the responsibility to release the
 * list of matches. The eventual release of the matches themselves also has to
 * be ensured. For example, call strpattern_match_delete_all().
 *
 * Note: The callback may be run in a separate thread. Make sure
 * that any data access and function calls from inside the callback are done in
 * a thread-safe way by using locks when appropriate.
 *
 * @param matches An unsorted array of matches; NULL if no matches are found
 *                or there is an error. Ownership is transferred to the
 *                implementation of this function.
 * @param len The number of matches found; zero if an error is encountered.
 * @param user_data The user-defined data supplied when the text is scheduled
 *                  for pattern matching (can be NULL). Memory is managed by the
 *                  client of this library.
 * @param err @c STRPATTERN_EOK if there is no error.
 *
 * @since BlackBerry 10.0.0
 */
typedef void (*strpattern_analyze_callback_func)(strpattern_match** matches,
              int len, void* user_data, int err);

/**
 * @brief Schedule pattern matching for the given text
 *
 * This function analyzes the given string using data specified by the user and
 * returns the results using the given callback function.
 * The callback is called even if there are errors. The callback is not called
 * if the pattern matching is canceled because of a call to
 * @c strpattern_cancel() before the actual matching process has
 * finished. Pattern matching may or may not run in the calling function's
 * thread. For strings with short length (native length less than 10), pattern
 * matching is normally run in the calling function's thread.
 *
 * The text must not be modified in another thread such as during the
 * execution of this function.
 *
 * Note: The callback may be run in a separate thread. Make sure that any data
 * access and function calls from inside the callback are done in
 * a thread-safe way by using locks when appropriate.
 *
 * Each method call returns a unique ID. This ID can be used to cancel the
 * corresponding pattern matching using a call to @c strpattern_cancel().
 *
 * @param text Text to be analyzed for pattern matches, wrapped as an ICU UText
 *             structure. Ownership is retained by the caller.
 * @param callback The callback called to deliver the result of pattern
 *                 matching (cannot be NULL).
 * @param user_data User-defined data passed to the callback (can be NULL).
 *                  Memory is managed by the client of this library.
 * @param context The context used for the pattern matching (can be NULL).
 *                Ownership is retained by the caller.
 * @param err @c STRPATTERN_EOK if there is no error.
 * @return A unique ID assigned to this pattern matching call.
 *
 * @since BlackBerry 10.0.0
 */
long strpattern_analyze(UText* text, strpattern_analyze_callback_func callback,
                        void* user_data, const strpattern_context* context,
                        int* err);

/**
 * @brief Schedule pattern matching for the given UTF-8 text
 *
 * This function is identical to @c strpattern_analyze() except that it operates
 * on UTF-8 encoded text.
 *
 * This function analyzes the given string using data specified by the user and
 * returns the results using the given callback function.
 * The callback is called even if there are errors. The callback is not called
 * if the pattern matching is canceled because of a call to
 * @c strpattern_cancel() before the actual matching process has
 * finished. Pattern matching may or may not run in the calling function's
 * thread. For strings with short length (native length less than 10), pattern
 * matching is normally run in the calling function's thread.
 *
 * The text must not be modified in another thread such as during the
 * execution of this function.
 *
 * Note: The callback may be run in a separate thread. Make sure that any data
 * access and function calls from inside the callback are done in
 * a thread-safe way by using locks when appropriate.
 *
 * Each method call returns a unique ID. This ID can be used to cancel the
 * corresponding pattern matching using a call to @c strpattern_cancel().
 *
 * Sample code:
 *
 * @code
 * char s[] = "sample text";
 * int err;
 * strpattern_analyzeUTF8(s, &your_callback, NULL, NULL, &err);
 * @endcode
 *
 * @param text Text to be analyzed for pattern matches which is UTF-8 encoded
 *             and NULL-terminated. Ownership is retained by the caller.
 * @param callback The callback called to deliver the result of pattern
 *                 matching (cannot be NULL).
 * @param user_data User-defined data passed to the callback (can be NULL).
 *                  Memory is managed by the client of this library.
 * @param context The context used for the pattern matching (can be NULL).
 *                Ownership is retained by the caller.
 * @param err @c STRPATTERN_EOK if there is no error.
 * @return A unique ID assigned to this pattern matching call.
 *
 * @since BlackBerry 10.0.0
 */
long strpattern_analyzeUTF8(const char* text, strpattern_analyze_callback_func
                            callback, void* user_data, const strpattern_context*
                            context, int* err);

/**
 * @brief Cancel the pattern matching of a text
 *
 * This function cancels the pattern matching of a doucment or text with the
 * specified ID. The ID is matched against the IDs assigned when texts are
 * scheduled for pattern matching.
 *
 * A scheduled pattern matching is canceled only if the pattern matching is
 * not completed when this function executes.
 *
 * Successfully cancelling a scheduled pattern matching means that the callback
 * provided at the time of scheduling is not invoked for this instance of
 * pattern matching.
 *
 * @param id The ID of the text whose pattern matching is to be canceled.
 * @param err @c STRPATTERN_EOK if there is no error. @c STRPATTERN_ENOTFOUND
 *            if no text with the given ID is scheduled for pattern matching.
 *
 * @since BlackBerry 10.0.0
 */
void strpattern_cancel(long id, int* err);

/**
 * @brief Initialize the pattern matching subsystem
 *
 * This function initializes the resources for the library. If this function is
 * not called, then the library is initialized automatically when other
 * functions are called if it is required. Initialization can take some time to
 * complete, so you may want to call this function before calling other
 * functions.
 *
 * @param err @c STRPATTERN_EOK if there is no error.
 *
 * @since BlackBerry 10.0.0
 */
void strpattern_init(int* err);

/**
 * @brief Return a simple string describing the specified error code
 *
 * @param err The error code.
 * @return A string with the simple description of the error code.
 *
 * @since BlackBerry 10.0.0
 */
const char* strpattern_errstr(int err);

/**
 * @brief Release the memory of a pattern match allocated on the heap
 *
 * @param match The pattern match to be deallocated.
 * @param err @c STRPATTERN_EOK if there is no error.
 *
 * @since BlackBerry 10.0.0
 */
void strpattern_match_delete(strpattern_match* match, int* err);

/**
 * @brief Release the memory of all pattern matches specified in the given array
 *
 * All pattern matches must be allocated on the heap.
 *
 * @param matches A pointer to the head of the array with pattern matches.
 * @param len The length of the array.
 * @param err @c STRPATTERN_EOK if there is no error.
 *
 * @since BlackBerry 10.0.0
 */
void strpattern_match_delete_all(strpattern_match* const * matches, int len,
                                 int* err);

/**
 * @brief Get the start index of a match
 *
 * This function returns the start index of a match. The start index represents
 * the offset, from the beginning of the string which was analyzed, to the first
 * character of the match. The offset is counted in terms of characters in the
 * analyzed string using Unicode code points. Characters are not reinterpreted
 * in any way. For example, each code point is counted as a character even if it
 * represents a character decoration associated with the preceding character.
 *
 * @param match The match whose start index is returned.
 * @param err @c STRPATTERN_EOK if there is no error.
 * @return The start index of the match (-1 on error).
 *
 * @since BlackBerry 10.0.0
 */
int strpattern_match_start_index(const strpattern_match* match, int* err);

/**
 * @brief Get the end index of a match
 *
 * This function returns the end index of a match. The end index represents the
 * offset, from the beginning of the string which was analyzed, to the character
 * immediately following the last character of the match. This character is
 * after the last character of the string if the last character of the match is
 * the last character of the analyzed string. The offset is counted in terms of
 * characters in the analyzed string using Unicode code points. Characters are
 * not reinterpreted in any way. For example, each code point is counted as a
 * character even if it represents a character decoration associated with the
 * preceding character.
 *
 * @param match The match whose end index is returned.
 * @param err @c STRPATTERN_EOK if there is no error.
 * @return The end index of the match (-1 on error).
 *
 * @since BlackBerry 10.0.0
 */
int strpattern_match_end_index(const strpattern_match* match, int* err);

/**
 * @brief Get the number of invokes associated with a match
 *
 * This function gets the number of invokes associated with a match.
 * There is at least one invoke associated with each match.
 * An invoke means that it was found by a recognizer and a match was created for
 * it. A recognizer is an email address, phone number, PIN, SMS, or URL. For
 * example, if a match has two invokes then two recognizers such as a phone and
 * PIN found it.
 *
 *
 * @param match The match whose invoke count is returned.
 * @param err @c STRPATTERN_EOK if there is no error.
 * @return The number of invokes associated with the match (0 on error).
 *
 * @since BlackBerry 10.0.0
 */
int strpattern_match_invoke_count(const strpattern_match* match, int* err);

/**
 * @brief Get the default invoke for a match
 *
 * This function gets the default invoke for a match. An invoke means that it
 * was found by a recognizer and a match was created for it. A recognizer is an
 * email address, phone number, PIN, SMS, or URL.
 *
 * @param match The match whose default invoke is returned.
 * @param err @c STRPATTERN_EOK if there is no error.
 * @return The default invoke for the match (0 on error).
 *
 * @since BlackBerry 10.0.0
 */
int strpattern_match_invoke_default(const strpattern_match* match, int* err);

/**
 * @brief Get the invocation target of an invoke associated with a pattern match
 *
 * This function gets the invocation target of an invoke associated with a
 * pattern match and returns a NULL-terminated string with the name of the
 * invocation target. An invoke means that it was found by a recognizer and a
 * match was created for it. A recognizer is an email address, phone number,
 * PIN, SMS, or URL.
 *
 * @param match The match containing the invoke whose invocation target is
 *              returned.
 * @param index The index of the invoke associated with the match.
 * @param err @c STRPATTERN_EOK if there is no error.
 * @return A NULL-terminated string with the name of the invocation target.
 *         NULL if no invocation target is set for the invoke or on error.
 *         Ownership is retained by the callee.
 *
 * @since BlackBerry 10.0.0
 */
const char* strpattern_match_invoke_target(const strpattern_match* match,
                                           int index, int* err);

/**
 * @brief Get the action of an invoke associated with a pattern match
 *
 * This function gets the action of an invoke associated with a pattern match
 * and returns a NULL-terminated string with the action. An action is defined
 * by a recognizer on a found match. An invoke means that it was found by a
 * recognizer and a match was created for it. A recognizer is an email address,
 * phone number, PIN, SMS, or URL. Currently, no action is used or set on any
 * of the recognizers.
 *
 * @param match The match containing the invoke whose action is returned.
 * @param index The index of the invoke associated with the match.
 * @param err @c STRPATTERN_EOK if there is no error.
 * @return A NULL-terminated string with the action. NULL if no
 *         action is set for the invoke or on error. Ownership is retained by
 *         the callee.
 *
 * @since BlackBerry 10.0.0
 */
const char* strpattern_match_invoke_action(const strpattern_match* match,
                                           int index, int* err);

/**
 * @brief Get the data type of an invoke associated with a pattern match
 *
 * This function gets the data type of an invoke associated with a pattern match
 * and returns a NULL-terminated string with the data type. An invoke means that
 * it was found by a recognizer and a match was created for it. A recognizer is
 * an email address, phone number, PIN, SMS, or URL.
 *
 * @param match The match containing the invoke whose data type is returned.
 * @param index The index of the invoke associated with the match.
 * @param err @c STRPATTERN_EOK if there is no error.
 * @return A NULL-terminated string with the data type. NULL if no data type
 *         is set for the invoke or on error. Ownership is retained by the
 *         callee.
 *
 * @since BlackBerry 10.0.0
 */
const char* strpattern_match_invoke_data_type(const strpattern_match* match,
                                              int index, int* err);

/**
 * @brief Get the URI of an invoke associated with a pattern match
 *
 * This function gets the URI of an invoke associated with a pattern match and
 * returns a NULL-terminated string with the URI. An invoke means that it was
 * found by a recognizer and a match was created for it. A recognizer is an
 * email address, phone number, PIN, SMS, or URL.
 *
 * @param match The match containing the invoke whose URI is returned.
 * @param index The index of the invoke associated with the match.
 * @param err @c STRPATTERN_EOK if there is no error.
 * @return A NULL-terminated string with the URI. NULL if no
 *         URI is set for the invoke or on error. Ownership is retained by the
 *         callee.
 *
 * @since BlackBerry 10.0.0
 */
const char* strpattern_match_invoke_uri(const strpattern_match* match,
                                        int index, int* err);

/**
 * @brief Get the data of an invoke associated with a pattern match
 *
 * This function gets the data of an invoke associated with a pattern match and
 * returns the length of the data. An invoke means that it was found by a
 * recognizer and a match was created for it. A recognizer is an email address,
 * phone number, PIN, SMS, or URL. If there is no data associated with the
 * invoke, the return value is 0 and @c p_data points to NULL.
 *
 * @param match The match containing the invoke whose data is returned.
 * @param index The index of the invoke associated with the match.
 * @param p_data Pointer to receive the pointer to the data.
 *               Ownership of the data is retained by match.
 * @param err @c STRPATTERN_EOK if there is no error.
 * @return The length of the data in bytes (-1 on error).
 *
 * @since BlackBerry 10.0.0
 */
int strpattern_match_invoke_data(const strpattern_match* match, int index,
                                 const void** p_data, int* err);

/**
 * @brief Construct a context object for pattern matching on the heap
 *
 * The context can be used to specify pattern-matching parameters.
 * See the corresponding context-related functions for information
 * about the parameters and their default values.
 *
 * @param err @c STRPATTERN_EOK if there is no error.
 * @return A pointer to the constructed context object (NULL on error).
 *         Ownership is transferred to the caller.
 *
 * @since BlackBerry 10.0.0
 */
strpattern_context* strpattern_context_new(int* err);

/**
 * @brief Release the memory of a context object allocated on the heap
 *
 * @param context The context object to be deallocated.
 * @param err @c STRPATTERN_EOK if there is no error.
 *
 * @since BlackBerry 10.0.0
 */
void strpattern_context_delete(strpattern_context* context, int* err);

/**
 * @brief Specify automatic selection of synchronous or asynchronous execution
 *        of pattern matching
 *
 * @since BlackBerry 10.0.0
 */
#define STRPATTERN_CONTEXT_EXEC_AUTO (3)

/**
 * @brief Specify synchronous execution of pattern matching
 *
 * @since BlackBerry 10.0.0
 */
#define STRPATTERN_CONTEXT_EXEC_SYNC (1)

/**
 * @brief Specify asynchronous execution of pattern matching
 *
 * @since BlackBerry 10.0.0
 */
#define STRPATTERN_CONTEXT_EXEC_ASYNC (2)

/**
 * @brief Specify synchronous or asynchronous execution of pattern matching
 *
 * Setting the type of execution to @c STRPATTERN_CONTEXT_EXEC_AUTO and
 * passing the context object when calling strpattern_analyze() enables
 * the automatic selection of whether the pattern-matching procedures are
 * executed synchronously or asynchronously.
 *
 * Setting the type of execution to @c STRPATTERN_CONTEXT_EXEC_SYNC and
 * passing the context object when calling strpattern_analyze() results
 * in the synchronous execution of the pattern-matching procedures.
 * The callback which receives the results is called before
 * strpattern_analyze() returns on the thread where strpattern_analyze()
 * was called.
 *
 * Setting the type of execution to @c STRPATTERN_CONTEXT_EXEC_ASYNC and
 * passing the context object when calling strpattern_analyze() results
 * in the asynchronous execution of the pattern-matching procedures.
 * The function strpattern_analyze() only schedules the pattern matching
 * request and returns. The callback which receives the results is called
 * on a library thread different from the thread where strpattern_analyze()
 * was called.
 *
 * By default, a context object specifies @c STRPATTERN_CONTEXT_EXEC_AUTO.
 *
 * @param context The context object where the type of execution is set.
 * @param type The type of execution (STRPATTERN_CONTEXT_EXEC_AUTO, *_SYNC,
 *             and *_ASYNC).
 * @param err @c STRPATTERN_EOK if there is no error.
 *
 * @since BlackBerry 10.0.0
 */
void strpattern_context_set_sync(strpattern_context* context, int type,
                                 int* err);

/**
 * @brief Get the specification of synchronous or asynchronous execution of
 *        pattern matching
 *
 * @see strpattern_context_set_sync(strpattern_context*, int, int*)
 *
 * @param context The context object whose execution setting is returned.
 * @param err @c STRPATTERN_EOK if there is no error.
 * @return The type of pattern matching execution specified.
 *         @c STRPATTERN_CONTEXT_EXEC_AUTO on error.
 *
 * @since BlackBerry 10.0.0
 */
int strpattern_context_sync(const strpattern_context* context, int* err);


#ifdef __cplusplus
} // extern "C"
#endif

#endif /* STRPATTERN_H_ */
