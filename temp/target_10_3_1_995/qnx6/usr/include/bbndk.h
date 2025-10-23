/*
 * Research In Motion Limited. Copyright (C) 2013.
 * Research In Motion Limited. All rights reserved.
 */

/**
 * @file bbndk.h
 *
 * @brief Macros for the BlackBerry Native SDK.
 *
 * This file defines macros that apply to the entire BlackBerry Native SDK.
 */

#ifndef _BBNDK_H_INCLUDED
#define _BBNDK_H_INCLUDED

/**
 * @brief Encode a single version number from the major, minor and patch
 * components.
 *
 * The @c BBNDK_VERSION_ENCODE() macro encodes a single version number from the
 * major, minor and patch components, for example, version 12.34.56 is encoded
 * as 12034056.
 * 
 * @param major The major number of the version to encode.
 * @param minor The minor number of the version to encode.
 * @param patch The patch number of the version to encode.
 *
 * @return The encoded version number, encoded as follows:
 *         (major * 1000000) + (minor * 1000) + patch
 *
 * @since BlackBerry 10.1.0
 */
#define BBNDK_VERSION_ENCODE(major, minor, patch) \
    (((major)*1000000)+((minor)*1000)+(patch))

/**
 * The current major version of the BlackBerry Native SDK.
 *
 * @since BlackBerry 10.1.0
 */
#define BBNDK_VERSION_CURRENT_MAJOR 10

/**
 * The current minor version of the BlackBerry Native SDK.
 *
 * @since BlackBerry 10.1.0
 */
#define BBNDK_VERSION_CURRENT_MINOR 3

/**
 * The current patch version of the BlackBerry Native SDK.
 *
 * @since BlackBerry 10.1.0
 */
#define BBNDK_VERSION_CURRENT_PATCH 1

/**
 * The current encoded version of the BlackBerry Native SDK.
 *
 * For example, version 10.1.0 is 10001000.
 *
 * @since BlackBerry 10.1.0
 */
#define BBNDK_VERSION_CURRENT BBNDK_VERSION_ENCODE(BBNDK_VERSION_CURRENT_MAJOR,BBNDK_VERSION_CURRENT_MINOR,BBNDK_VERSION_CURRENT_PATCH)

/**
 * @brief Check whether the BlackBerry Native SDK is the given version or
 * higher.
 *
 * The @c BBNDK_VERSION_AT_LEAST() macro checks whether the BlackBerry Native
 * SDK is the given version or higher.  For example, to conditionally compile
 * some code only if building with BlackBerry Native SDK 10.1.0 or higher, use:
 *
 * @code
 * 
 * #if BBNDK_VERSION_AT_LEAST(10,1,0)
 *     // code to compile on BBNDK 10.1.0 or higher
 * #else
 *     // code to compile on versions of BBNDK lower than 10.1.0
 * #endif
 * 
 * @endcode
 *
 * @param major The major number of the version to check.
 * @param minor The minor number of the version to check.
 * @param patch The patch number of the version to check.
 *
 * @return true if the current version of the BlackBerry Native SDK is the same
 * or greater than the given version, else false.
 *
 * @since BlackBerry 10.1.0
 */
#define BBNDK_VERSION_AT_LEAST(major, minor, patch) \
    (BBNDK_VERSION_CURRENT >= BBNDK_VERSION_ENCODE(major, minor, patch))

/**
 * @brief Build a version number string from the major, minor and patch
 * components.
 * 
 * The @c BBNDK_VERSION_STRING_BUILD() macro builds a version number string from
 * the major, minor and patch components, for example, "10.1.0".
 * 
 * @param major The major number of the version to build.
 * @param minor The minor number of the version to build.
 * @param patch The patch number of the version to build.
 *
 * @return The version number string, built as follows:
 *         "major.minor.patch"
 *
 * @since BlackBerry 10.1.0
 */
#define BBNDK_VERSION_STRING_BUILD(major, minor, patch) \
    BBNDK_VERSION_STR(major) "." BBNDK_VERSION_STR(minor) "." BBNDK_VERSION_STR(patch)

/**
 * Helper macro for building a version number string.
 *
 * @since BlackBerry 10.1.0
 */
#define BBNDK_VERSION_STR(s) #s

/**
 * The current version of the BlackBerry Native SDK as a string.
 *
 * For example, "10.1.0".
 *
 * @since BlackBerry 10.1.0
 */
#define BBNDK_VERSION_CURRENT_STRING BBNDK_VERSION_STRING_BUILD(BBNDK_VERSION_CURRENT_MAJOR, BBNDK_VERSION_CURRENT_MINOR, BBNDK_VERSION_CURRENT_PATCH)

#endif
