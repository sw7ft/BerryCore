/**
 * @file number.h
 *
 * Copyright (c) Research In Motion Limited. All rights reserved.
 *
 * @brief Phone number utility functions.
 *
 * To retrieve the options associated with the phone you can use the
 * convenience method phone_number_get_options() but this call is expensive
 * and intended for infrequent use only.  If you need to monitor these
 * options the recommended approach is to use phone_number_open_options() to
 * get an FD to the options PPS object.  You then wait for changes on this
 * FD and call phone_number_update_options() to have your config structure
 * updated with the changes in the PPS object.  Use phone_number_close_options()
 * when you are done.
 */

#ifndef _PHONE_NUMBER_H_
#define _PHONE_NUMBER_H_

#include <stdio.h>
#include <stdbool.h>

__BEGIN_DECLS

/** Types & Definitions **/

#define PHONE_NUMBER_LENGTH    (80)

/* num of signatures plus delimiters and null terminator */
#define MAX_SIGNATURE_LENGTH   (PHONE_NUMBER_LENGTH * 3 + 4)

/**
 * @typedef phone_number_t Holds a phone number
 */
typedef char phone_number_t[PHONE_NUMBER_LENGTH];

/**
 * @typedef phone_sig_t signature of a phone number - all numbers that are
 *  equal will have the same signature
 */
typedef char phone_sig_t[MAX_SIGNATURE_LENGTH];

/**
 * @typedef phone_number_options_t Contains all parameters connected to
 * phone numbers
 */
typedef struct {
    int country_code; /* Code for region being called from (North
                       * America is 1) */
    char area_code[PHONE_NUMBER_LENGTH]; /* Default area code */
    int national_number_length; /* Length of a phone number in the region */
    phone_number_t corp_number; /* Corporate switchboard number */
    int corp_wait; /* How long to wait before dialing corporate extension */
    int corp_ext_len; /* Length of a corporate extension */
    int corp_ext_wait; /* how long to wait before dialing outside extensions */
    int user_select_idd;
    bool auto_append_ndd;
    bool roaming;
    bool customized_setting;
    bool cpd_capable;
    int local_cc;
} phone_number_options_t;

/** API Function Prototypes **/

/**
 * @brief Open the phone options pps object with "wait,delta"
 *
 * @return file descriptor to the PPS object
 */
int
phone_number_open_options(void);

/**
 * @brief Closes the phone options pps object FD
 * @param[in] fd
 *
 * @return Returns void.
 */
void
phone_number_close_options(int fd);

/**
 * @brief When a delta is received, call this function to update your
 *  local copy of the config
 *
 * @param[out] config  input configuration to be modified
 * @param[in] readBuffer  Delta Buffer given
 * @return True if successful
 */
bool
phone_number_update_options(phone_number_options_t *config, char *read_buf);

/**
* @brief Opens the phone options PPS object and uses it to populate the
*  config structure.
* @warning This is an expensive call - meant for infrequent usage.
*
* @param[out] config input configuration to be modified
* @return True if successful
*/
bool
phone_number_get_options(phone_number_options_t *config);

/**
* @brief Convenience method that returns the size of the config structure.
*
* @return sizeof the phone_number_options_t structure
*/
int
phone_number_sizeof_options(void);

/**
 *  Convert phone number to international form using the Smart Dialing Options.
 *
 *  This algorithm is able to detect phone numbers in the following patterns:
 *     NDD AC LOCAL
 *         AC LOCAL
 *            LOCAL
 *
 *  and convert them to the standard form:
 *    +CC AC LOCAL
 *
 *  @param[in] config The smart dialing options
 *  @param[in] original_number The raw number to be converted
 *  @param[out] converted_number The converted number.
 *  @return true if smart dialing was applied successfully
 */
bool
phone_number_apply_smart_dialing(const phone_number_options_t *config,
                                 const phone_number_t original_number,
                                 phone_number_t converted_number);

/**
 * @brief Takes a phone number as an input and returns a number formatted for
 * transmission (extra characters removed, smart dialing optionally applied,
 * "+1 (519) 888 7465" becomes "15198887465").
 * @param[in] config Options that control smart dialing
 * @param[in] inNumber The input for the formatted number
 * @param[out] outNumber The string where the converted output will go
 * @param[in] smart_dial true if smart dialing is to be applied
 * @return true if formatting was successful
*/
bool
phone_number_format_for_transmission(const phone_number_options_t *config,
                                     const phone_number_t inNumber,
                                     phone_number_t outNumber, bool smart_dial);

/**
 * @brief Takes a phone number as an input and returns a number formatted for
 * SMS (extra charaters removed, smart dialing optionally applied,
 * "+1 (519) 888 7465" becomes "15198887465").
 * @param[in] config Options that control smart dialing
 * @param[in] inNumber The input for the formatted number
 * @param[out] outNumber The string where the converted output will go
 * @param[in] smart_dial true if smart dialing is to be applied
 * @return true if formatting was successful
*/
bool
phone_number_format_for_sms(const phone_number_options_t *config,
                            const phone_number_t inNumber,
                            phone_number_t outNumber, bool smart_dial);

/**
 * @brief Takes a phone number as an input and returns a number formatted for
 * MMS (extra charaters removed, smart dialing optionally applied,
 * "+1 (519) 888 7465" becomes "15198887465").
 * @param[in] config Options that control smart dialing
 * @param[in] inNumber The input for the formatted number
 * @param[out] outNumber The string where the converted output will go
 * @param[in] smart_dial true if smart dialing is to be applied
 * @return true if formatting was successful
*/
bool
phone_number_format_for_mms(const phone_number_options_t *config,
                            const phone_number_t inNumber,
                            phone_number_t outNumber, bool smart_dial);

/**
 *  @brief Converts the two numbers to a canonical format (format for
 *  transmission) and then compares them.
 *
 * @param[in] config The smart dialing options
 * @param[in] first_number First number to compare
 * @param[in] second_number Second Number to compare.
 *
 * @return true if the numbers are the same
 */
bool
phone_number_compare(const phone_number_options_t *config,
                     const phone_number_t first_number,
                     const phone_number_t second_number);

/**
 * @brief Takes the input phone number, and formats it like a phone number
 * based on the home country code ("15198887465" becomes "+1 (519) 888 7465").
 * @param[in] config The smart dialing settings to use for the comparison
 * @param[in] input_number The number to format
 * @param[out] output_number The formatted number
 * @return true if formatting was successful
*/
bool
phone_number_format_for_display(const phone_number_options_t *config,
                                const phone_number_t input_number,
                                phone_number_t output_number);

/**
 * @brief Calculates a phone number's signature using the configured
 * smart dialing settings. All numbers that are considered 'equal'  within the
 * context of the options (such as 8887465, 5198887465, +15198887465) will
 * map to the same signature.  The signature will include the extension if
 * there is one.
 *
 * @param[in] config The smart dialing options
 * @param[in] number number to calculate signature for
 * @param[out] signature signature of number provided
 *
 * @return true if valid signature was generated
 */
bool
phone_number_get_signature(const phone_number_options_t *config,
                           const phone_number_t number, phone_sig_t signature);

/**
 * @brief This is the same as phone_number_get_signature except that it will
 * contain multiple (space delimited) variations on the signature to allow
 * the best chance of matching.  Variations include with & without extensions,
 * country code and area code.  The string generated by this method is
 * appropriate for putting into a database as a key for future searching.
 *
 * @param[in] config The smart dialing options
 * @param[in] number number to calculate signature for
 * @param[out] signatures signatures of number provided (space delimited)
 *
 * @return true if valid signature(s) were generated
 */
bool
phone_number_get_all_signatures(const phone_number_options_t *config,
                           const phone_number_t number, phone_sig_t signatures);

/**
 * @brief This method generates the counterpart to
 * phone_number_get_all_signatures.  Use this method when it's time to search
 * for a number in a database.  For example, when a call comes in this
 * method will be called to generate a signature that is searched for in
 * the database.
 *
 * @param[in] config The smart dialing options
 * @param[in] number number to calculate signature for
 * @param[out] signatures signatures of number provided (space delimited)
 *
 * @return true if valid signature(s) were generated
 */
bool
phone_number_get_search_signatures(const phone_number_options_t *config,
                                   const phone_number_t number,
                                   phone_sig_t signatures);

/**
 * @brief Compares two phone number signatures for equality.  This is a
 *  string compare of the signatures with tests for NULL.  A signature can
 *  have multiple strings within it.  If any one string within the first
 *  signature is in the second signature it is considered a match.  This is
 *  a broad match. The signature of a number with an extension will match the
 *  signature of the same number without the extension, for example.
 *
 * @param[in] sig1  First signature to compare
 * @param[in] sig2  Second signature to compare
 *
 * @return true if signatures are equal.
 */
bool
phone_number_compare_signatures(phone_sig_t sig1, phone_sig_t sig2);

/**
 * @brief Compares two phone number signatures for equality.  This is a
 *  string compare of the signatures with tests for NULL.  Unlike
 *  phone_number_compare_signatures() this is a strict match.  The numbers
 *  must be identical (including extension) to match.
 *
 * @param[in] sig1  First signature to compare
 * @param[in] sig2  Second signature to compare
 *
 * @return true if signatures are equal.
 */
bool
phone_number_compare_signatures_exact(phone_sig_t sig1, phone_sig_t sig2);

/**
 * @brief Formats a phone number to replace all the digits with 'x' except for
 * the first 4 digits and the last 2 digits
 *
 * @param[in] input_number The number to format
 * @param[out] output_number A buffer to store the output in.
 *
 * @return true if obfuscation was successful
 */
bool
phone_number_obfuscate(const phone_number_t input_number,
                       phone_number_t output_number);

/**
 * @brief Strips formatting characters out of a number.
 *
 * @param[in] input The number to strip
 * @param[out] output A buffer to store the output in.
 *
 * @return true if stripping was successful
 */
bool
phone_number_remove_formatting(const phone_number_t input,
                               phone_number_t output);

/**
 * @brief Removes invalid characters from a number.
 *
 * Valid characters are: uppercase letters, digits, whitespace,
 *  'p', 'w', 'x', '#', '*', '!', ',', '(', ')', '-', '.', and '+'
 *
 * @param[in] input The input number to remove invalid characters
 * @param[out] output The outnumber to store the new number
 *
 * @return true if removing invalid characters was successful
 */
bool
phone_number_remove_invalid_characters(const phone_number_t input_number,
                                       phone_number_t output_number);

/**
 * Convert CDMA Plus Dialing rules to the original number by
 * given local and home country codes
 */
bool
phone_number_apply_cpd(const phone_number_t dialed_number,
                       const phone_number_options_t *config,
                       phone_number_t output_number);

/**
 * @brief Get default number of digits in national dialing patterns
 *
 * @param[in] country_code The input country code
 * @return default number of digits in national dialing patterns by given country code.
 *         -1 when national number length can not be determined for given country.
 */
int
phone_number_get_default_national_number_length(int country_code);

/**
 * @brief Get the range of digits in national dialing patterns
 *
 * @param[in] country_code The input country code
 * @param[out] min The minimum length
 * @param[out] max The maximum length
 * @return True if NNL for country is know, false otherwise
 */
bool
phone_number_get_national_number_length_range(int country_code, int *min,
                                              int *max);

/**
 * @brief Get national dialing digits for a specific country code
 *
 * @param[in] country_code The given input country code
 * @return the national dialing digits for a specific country code
 */
const char *
phone_number_get_national_dialing_digits(int country_code);

/**
 * @brief quick and dirty - needs improvement (only works for NA)
 * @param[in] countryCode - the national country code
 * @param[in] localNumber - the device's local number
 * @param[out] areaCode - the output area code
 * @return 0 if successful, -1 otherwise
 */
int
phone_number_parse_area_code(int country_code, char *local_number,
                             char *area_code);

/**
 * @brief
 * @param[in] in_number - phone number in international format
 * @param[out] country code that pared from phone number,
 *     -1 means failed to parse
 * @param[out] area_code -area code that parsed from phone number
 */
void
phone_number_parse_international_number(const phone_number_t in_number,
                                        int* cc, phone_number_t area_code);


int
phone_number_options_get_local_mcc();


__END_DECLS

#endif /* _PHONE_NUMBER_H_ */

