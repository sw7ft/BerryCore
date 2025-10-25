/**
 * @file spellcheck_client.h
 *
 * @brief Functions to perform spell checks and provide suggested spellings
 *
 * The spell check client library reference defines the spell check service,
 * which includes functions to verify the spelling of words and provide spelling
 * suggestions using dictionaries identified in the system input locale
 * settings.
 *
 * @copyright Copyright BlackBerry, 2012-2013.
 */

#ifndef SPELLCHECK_CLIENT_H_
#define SPELLCHECK_CLIENT_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

__BEGIN_DECLS

/**
 * The version of the spell check library
 *
 * The version number is computed as follows:
 * (Major * 1000000) + (Minor * 1000) + Patch
 */
#define SPELLCHECK_VERSION (1000000)

/**
 * The version of the spell check library as a string
 */
#define SPELLCHECK_VERSION_STRING "1.0.0"

/**
 * A return code that indicates that a function completed successfully
 */
#define SPELLCHECK_CHECK_SPELLING_SUCCESS (0)

/**
 * A return code that indicates that a function did not complete successfully.
 * When the @c errno value is set, it indicates the reason for the failure.
 */
#define SPELLCHECK_FAILURE (-1)


/**
 * TODO
 */
struct spellcheck_suggestions_t;

/**
 * The opaque spell check suggestions type.
 *
 * This type represents the @c spellcheck_suggestions_t structure used by
 * several functions in the spell check client. Use this to hold lists of
 * spelling suggestions generated for misspelled words.
 */
typedef struct spellcheck_suggestions_t spellcheck_suggestions_t;

struct spellcheck_context_t;

/**
 * The opaque spell check context type.
 *
 * This type represents the @c spellcheck_context_t structure used by several
 * functions in the spell check client. Use this to identify instances of the
 * spell check client.
 */
typedef struct spellcheck_context_t spellcheck_context_t;

/**
 * Get the version number of the spell check client.
 *
 * The @c spellcheck_get_version() function retrieves the version of the spell
 * check client library that your application is using.
 *
 * @return The version of the spell check client library used by the
 *         application.
 */
int spellcheck_get_version(void);

/**
 * Initialize and connect an instance of the spell check client.
 *
 * The @c spellcheck_init() function initializes the spell check client and
 * connects it with the application for use. This also allocates memory to a @c
 * spellcheck_context_t structure for use in the @c spellcheck_check_spelling(),
 * @c spellcheck_get_suggestions(), and @c spellcheck_destroy() functions.
 * Destroy all @c spellcheck_context_t structures no longer needed by using the
 * @c spellcheck_destroy() function to prevent memory leaks.
 *
 * @return A @c spellcheck_context_t structure to be used by the spell check
 *         client instance or null, if failure.
 */
spellcheck_context_t* spellcheck_init(void);

/**
 * Disconnect an instance of the spell check client and deallocate memory
 *        used by the @c spellcheck_context structure.
 *
 * The @c spellcheck_destroy() function deallocates any memory set to a given
 * instance of the spell check client. Use this function to deallocate memory
 * used by a @c spellcheck_context structure (created by the @c
 * spellcheck_init() function) that's no longer in use. Failing to do so will
 * result in a memory leak.
 *
 * @param spellcheck_context The @c spellcheck_context structure to deallocate.
 */
void spellcheck_destroy(spellcheck_context_t *spellcheck_context);

/**
 * Check the spelling of a word.
 *
 * The @c spellcheck_check_spelling() function verifies the spelling of a single
 * word and identifies whether the word is misspelled or not. The dictionaries
 * used by the spell check client to determine spelling correctness is based on
 * the system input locale settings.
 *
 * @param spellcheck_context The spell check client instance in which the check
 *                           is performed.
 * @param text_to_check The word to check for spelling, in utf-8 encoding.
 * @param is_misspelled The spelling correctness of the word. The value is true
 *                      if the word is misspelled, or false otherwise.
 * @param max_timeout The maximum amount of time in milliseconds for the
 *                    function to complete before the @c ETIMEDOUT error occurs.
 *
 * @return @c SPELLCHECK_CHECK_SPELLING_SUCCESS if the word was successfully
 *         checked for spelling, or @c SPELLCHECK_FAILURE with @c errno set
 *         otherwise. @c errno=ETIMEDOUT occurs if the timeout exceeds @c
 *         max_timeout.
 */
int spellcheck_check_spelling(spellcheck_context_t *spellcheck_context, const char *text_to_check,
    bool *is_misspelled, unsigned int max_timeout);

/**
 * Get spelling suggestions for a word.
 *
 * The @c spellcheck_get_suggestions() function retrieves spelling suggestions
 * for a single word. The dictionaries used by the spell check client to
 * determine spelling correctness is based on the system input locale settings.
 * Destroy all @c spellcheck_suggestions_t structures no longer needed by using
 * the @c spellcheck_suggestions_destroy() function to prevent memory leaks.
 *
 * @param spellcheck_context The spell check client instance in which the
 *                           function is performed.
 * @param misspelled_word The misspelled word to provide spelling suggestions
 *                        for.
 * @param max_num_suggestions The maximum number of spelling suggestions to
 *                            provide for the misspelled word.
 * @param word_suggestions A @c spellcheck_suggestions_t structure containing
 *                         the spelling suggestions for the misspelled word.
 * @param max_timeout The maximum amount of time in milliseconds for the
 *                    function to complete before the @c ETIMEDOUT error occurs.
 *
 * @return The number of spelling suggestions found for the misspelled word, @c
 *         SPELLCHECK_FAILURE with @c errno set otherwise. @c errno=ETIMEDOUT
 *         occurs if the timeout exceeds @c max_timeout.
 */
int spellcheck_get_suggestions(spellcheck_context_t *spellcheck_context, const char *misspelled_word,
    size_t max_num_suggestions, spellcheck_suggestions_t **word_suggestions, unsigned int max_timeout);

/**
 * Get an indexed spelling suggestion for a word.
 *
 * The @c spellcheck_get_suggestion_at_index() function retrieves a single
 * spelling suggestion for a misspelled word from a @c spellcheck_suggestions_t
 * structure, identified by a given @c index value. The returned pointer is
 * owned by the corresponding @c spellcheck_suggestions_t structure and remains
 * valid for the lifetime of that structure.
 *
 * @param word_suggestions The @c spellcheck_suggestions_t structure from which
 *                         you want to retrieve the spelling suggestion.
 * @param index The index value of the spelling suggestion you want to retrieve.
 *
 * @return A pointer to the spelling suggestion at the given @c index value in
 *         utf-8 encoding, @c NULL with @c errno set otherwise.
 */
const char * spellcheck_get_suggestion_at_index(spellcheck_suggestions_t *word_suggestions, int index);

/**
 * Get the total number of spelling suggestions for a word.
 *
 * The @c spellcheck_get_number_of_suggestions() function retrieves the total
 * number of spelling suggestion for a misspelled word from a @c
 * spellcheck_suggestions_t structure.
 *
 * @param word_suggestions The @c spellcheck_suggestions_t structure from which
 *                         you want to retrieve the total number of spelling
 *                         suggestions.
 *
 * @return The total number of spelling suggestion in the @c
 *         spellcheck_suggestions_t structure, @c SPELLCHECK_FAILURE with @c
 *         errno set otherwise.
 */
int spellcheck_get_number_of_suggestions(spellcheck_suggestions_t *word_suggestions);

/**
 * Deallocate memory used by a @c spellcheck_suggestions_t structure.
 *
 * The @c spellcheck_suggestions_destroy() function deallocates any memory set
 * to a given instance of a @c spellcheck_suggestions_t structure, destroying
 * the spelling suggestions contained within. Use this function to deallocate
 * memory used by a @c spellcheck_suggestions_t structure that's no longer in
 * use. Failing to do so will result in a memory leak.
 *
 * @param word_suggestions The @c spellcheck_suggestions_t structure to
 *                         deallocate.
 */
void spellcheck_suggestions_destroy(spellcheck_suggestions_t *word_suggestions);

__END_DECLS

#endif // SPELLCHECK_CLIENT_H_
