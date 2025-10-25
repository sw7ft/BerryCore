/**
 * @copyright
 * Copyright Research In Motion Limited, 2012-2012
 * Research In Motion Limited. All rights reserved.
 */

/**
 * @file packageinfo.h
 *
 * @brief Functions to retrieve metadata from the BlackBerry Archive (BAR) manifest.
 * @details Applications can access only their own metadata.
 */

#ifndef _PACKAGEINFO_H_INCLUDED
#define _PACKAGEINFO_H_INCLUDED

#include <sys/platform.h>

__BEGIN_DECLS

/**
 * The version of the packageinfo.
 *
 * The version number is computed as follows:
 * (Major * 1000000) + (Minor * 1000) + Patch
 */
#define PACKAGEINFO_VERSION             (1000001)

/**
 * The version of packageinfo as a string.
 *
 * @c PACKAGEINFO_VERSION
 */
#define PACKAGEINFO_VERSION_STRING      "1.0.1"

/**
 * @brief Retrieve the version of packageinfo.
 *
 * @return The version of packageinfo library using the scheme described for @c
 *         PACKAGEINFO_VERSION.
 */
int packageinfo_version(void);

/**
 * @brief The packageinfo accessor for the package being queried.
 */
typedef struct packageinfo_t packageinfo_t;

/**
 * @brief @c packageinfo_result_t represents the result of function calls.
 */
typedef enum {

    /**
     * @brief No error was detected.
     */
    PACKAGEINFO_ERROR_NONE              = 0,

    /**
     * @brief An unknown error occurred.
     */
    PACKAGEINFO_ERROR_UNKNOWN           = 1,

    /**
     * @brief Memory could not be allocated.
     */
    PACKAGEINFO_ERROR_NO_MEMORY         = 2,

    /**
     * @brief An error occurred during parsing, or the BAR manifest could not be parsed.
     */
    PACKAGEINFO_ERROR_METADATA_PARSE    = 3,

    /**
     * @brief The attribute provided could not be found.
     */
    PACKAGEINFO_ERROR_MISSING_ATTRIBUTE = 4,

} packageinfo_result_t;

/**
 * @brief Initializes the packageinfo accessor.
 *
 * @details This (or @c packageinfo_initialize_from_path) must be called once before any other calls are made.
 * The ownership of the return value stays with the library.
 * To deallocate memory, use @c packageinfo_cleanup.
 *
 * @return Whether the operation succeeded.
 */
packageinfo_result_t packageinfo_initialize(packageinfo_t** pi);

/**
 * @brief Initializes the packageinfo accessor.
 *
 * @details This (or @c packageinfo_initialize) must be called once before any other calls are made.
 * The ownership of the return value stays with the library.
 * To deallocate memory, use @c packageinfo_cleanup.
 * Initialization will fail if you attempt to pass a path for which elevated permissions are required.
 *
 * @param path The path of the directory where the BAR manifest resides.
 * @return Whether the operation succeeded.
 */
packageinfo_result_t packageinfo_initialize_from_path(const char* path, packageinfo_t** pi);

/**
 * @brief Releases any resources used by the packageinfo accessor.
 *
 * @param pi The packageinfo accessor.
 */
void packageinfo_cleanup(packageinfo_t* pi);

/**
 * @brief @c packageinfo_version_t represents the value type for version attributes.
 * @details If major, minor, release and build versions are all zero, the version is considered invalid.
 * If a version attribute does not have all version fragments, the least significant ones will be set to zero.
 */
typedef struct {

    /**
     * @brief The major version.
     * @details Ranges from 0-65535.
     */
    int major;

    /**
     * The minor version.
     * @details Ranges from 0-65535.
     */
    int minor;

    /**
     * The release version.
     * @details Ranges from 0-65535.
     */
    int release;

    /**
     * The build version.
     * @details Ranges from 0-65535.
     */
    int build;

} packageinfo_version_t;

/**
 * @brief @c packageinfo_locale_t represents locales.
 */
typedef struct {

    /**
     * @brief The language of the locale.
     * @details If empty, this is an invalid locale.
     */
    char language[3];

    /**
     * @brief The country of the locale.
     * @details The country may be empty.
     */
    char country[3];

} packageinfo_locale_t;

/**
 * @brief Retrieves the unique token used by the system to represent the package.
 * @param pi The packageinfo accessor.
 * @param value The output parameter for the requested metadata. @c packageinfo_cleanup frees this memory.
 * @return Whether the operation succeeded.
 */
packageinfo_result_t packageinfo_get_install_id(packageinfo_t* pi, char** value);

/**
 * @brief Retrieves the hash assigned by the signing authority for the package.
 * @param pi The packageinfo accessor.
 * @param value The output parameter for the requested metadata. @c packageinfo_cleanup frees this memory.
 * @return Whether the operation succeeded.
 */
packageinfo_result_t packageinfo_get_package_signing_hash(packageinfo_t* pi, char** value);

/**
 * @brief Retrieves the hash assigned by the signing authority for the package version.
 * @param pi The packageinfo accessor.
 * @param value The output parameter for the requested metadata. @c packageinfo_cleanup frees this memory.
 * @return Whether the operation succeeded.
 */
packageinfo_result_t packageinfo_get_package_version_signing_hash(packageinfo_t* pi, char** value);

/**
 * @brief Retrieves the hash assigned by the signing authority for the package author.
 * @param pi The packageinfo accessor.
 * @param value The output parameter for the requested metadata. @c packageinfo_cleanup frees this memory.
 * @return Whether the operation succeeded.
 */
packageinfo_result_t packageinfo_get_package_author_signing_hash(packageinfo_t* pi, char** value);

/**
 * @brief Retrieves the compatibility version for the metadata.
 * @param pi The packageinfo accessor.
 * @param value The output parameter for the requested metadata.
 * @return Whether the operation succeeded.
 */
packageinfo_result_t packageinfo_get_package_compatibility(packageinfo_t* pi, packageinfo_version_t* value);

/**
 * @brief Retrieves the minimum system version declared as a dependency for the package.
 * @param pi The packageinfo accessor.
 * @param value The output parameter for the requested metadata.
 * @return Whether the operation succeeded.
 */
packageinfo_result_t packageinfo_get_package_system_dependency(packageinfo_t* pi, packageinfo_version_t* value);

/**
 * @brief Retrieves the name of the package.
 * @param pi The packageinfo accessor.
 * @param value The output parameter for the requested metadata. @c packageinfo_cleanup frees this memory.
 * @return Whether the operation succeeded.
 */
packageinfo_result_t packageinfo_get_package_name(packageinfo_t* pi, char** value);

/**
 * @brief Retrieves the version of the package.
 * @param pi The packageinfo accessor.
 * @param value The output parameter for the requested metadata. @c packageinfo_cleanup frees this memory.
 * @return Whether the operation succeeded.
 */
packageinfo_result_t packageinfo_get_package_version(packageinfo_t* pi, packageinfo_version_t* value);

/**
 * @brief Retrieves the author of the package.
 * @param pi The packageinfo accessor.
 * @param value The output parameter for the requested metadata. @c packageinfo_cleanup frees this memory.
 * @return Whether the operation succeeded.
 */
packageinfo_result_t packageinfo_get_package_author(packageinfo_t* pi, char** value);

/**
 * @brief Retrieves the description of the package.
 * @param pi The packageinfo accessor.
 * @param value The output parameter for the requested metadata. @c packageinfo_cleanup frees this memory.
 * @return Whether the operation succeeded.
 */
packageinfo_result_t packageinfo_get_package_description(packageinfo_t* pi, char** value);

/**
 * @brief Retrieves the list of locales in which the metadata of the package are localized in.
 * @param pi The packageinfo accessor.
 * @param value The output parameter for the requested metadata.
 * @param arrayLength The length of value. This should be at least as large as @c packageinfo_get_package_locales_length.
 * @return Whether the operation succeeded.
 */
packageinfo_result_t packageinfo_get_package_locales(packageinfo_t* pi, packageinfo_locale_t value[], int arrayLength);

/**
 * @brief Retrieves the number of locales in which the metadata of the package are localized in.
 * @param pi The packageinfo accessor.
 * @param length The number of locales.
 * @return Whether the operation succeeded.
 */
packageinfo_result_t packageinfo_get_package_locales_length(packageinfo_t* pi, int* length);

/**
 * @brief Retrieves the hash assigned by the signing authority for the application contained in the package.
 * @param pi The packageinfo accessor.
 * @param value The output parameter for the requested metadata. @c packageinfo_cleanup frees this memory.
 * @return Whether the operation succeeded.
 */
packageinfo_result_t packageinfo_get_application_signing_hash(packageinfo_t* pi, char** value);

/**
 * @brief Retrieves the hash assigned by the signing authority for the version of the application contained in the package.
 * @param pi The packageinfo accessor.
 * @param value The output parameter for the requested metadata. @c packageinfo_cleanup frees this memory.
 * @return Whether the operation succeeded.
 */
packageinfo_result_t packageinfo_get_application_version_signing_hash(packageinfo_t* pi, char** value);

/**
 * @brief Retrieves the title of the application contained in the package.
 * @param pi The packageinfo accessor.
 * @param value The output parameter for the requested metadata. @c packageinfo_cleanup frees this memory.
 * @return Whether the operation succeeded.
 */
packageinfo_result_t packageinfo_get_application_title(packageinfo_t* pi, char** value);

/**
 * @brief Retrieves the version of the application contained in the package.
 * @param pi The packageinfo accessor.
 * @param value The output parameter for the requested metadata.
 * @return Whether the operation succeeded.
 */
packageinfo_result_t packageinfo_get_application_version(packageinfo_t* pi, packageinfo_version_t* value);

/**
 * @brief Retrieves the description of the application contained in the package.
 * @param pi The packageinfo accessor.
 * @param value The output parameter for the requested metadata. @c packageinfo_cleanup frees this memory.
 * @return Whether the operation succeeded.
 */
packageinfo_result_t packageinfo_get_application_description(packageinfo_t* pi, char** value);

__END_DECLS

#endif // _PACKAGEINFO_H_INCLUDED
