/*
 * Copyright (C) 2013-2014 BlackBerry Limited. All rights reserved.
 */

/**
 * @file removablemedia.h
 *
 * @brief Functions to determine changes to the state of the removable media on
 * the device
 *
 * This file defines the Removable Media service, which provides functions for
 * notification of when the state of the device's removable media changes.
 *
 * @since BlackBerry 10.2.0
 */

#ifndef _BPS_REMOVABLEMEDIA_H_INCLUDED
#define _BPS_REMOVABLEMEDIA_H_INCLUDED

#include <stdbool.h>
#include <sys/platform.h>

#include "bps/bps.h"

__BEGIN_DECLS

/**
 * @brief Possible Removable Media events
 *
 * This enumeration defines the possible Removable Media events.  Currently,
 * there is only one event.
 *
 * @anonenum bps_removablemedia_events Removable Media events
 *
 * @since BlackBerry 10.2.0
 */
enum {
    /**
     * The Removable Media info event, which contains all of the information
     * about changes to the device's removable media.
     *
     * @since BlackBerry 10.2.0
     */
    REMOVABLEMEDIA_INFO        = 0x01
};

/**
 * @brief Possible device types
 *
 * This enumeration defines the possible types of the underlying removable media
 * device.
 *
 * @since BlackBerry 10.2.0
 */
typedef enum {
    /**
     * The device type is unknown.
     *
     * @since BlackBerry 10.2.0
     */
    REMOVABLEMEDIA_TYPE_UNKNOWN          = 0,
    /**
     * Secure Digital (SD) memory card.
     *
     * @since BlackBerry 10.2.0
     */
    REMOVABLEMEDIA_TYPE_SD               = 1,
    /**
     * Embedded MultiMedia Card (EMMC).
     *
     * @since BlackBerry 10.2.0
     */
    REMOVABLEMEDIA_TYPE_EMMC             = 2,
    /**
     * USB Mass Storage device.
     *
     * @since BlackBerry 10.2.0
     */
    REMOVABLEMEDIA_TYPE_USB_MASS_STORAGE = 3,
} removablemedia_type_t;

/**
 * @brief Possible media states of presence
 *
 * This enumeration defines the possible states of presence or availability of
 * the removable media.
 *
 * @since BlackBerry 10.2.0
 */
typedef enum {
    /**
     * The removable media is physically disconnected from the device and
     * unavailable for use.
     *
     * @since BlackBerry 10.2.0
     */
    REMOVABLEMEDIA_PRESENCE_REMOVED  = 0,
    /**
     * The removable media is connected and available for use.
     *
     * @since BlackBerry 10.2.0
     */
    REMOVABLEMEDIA_PRESENCE_INSERTED = 1,
    /**
     * The removable media is not available for use and may require additional
     * actions to enable availability.
     *
     * @since BlackBerry 10.2.0
     */
    REMOVABLEMEDIA_PRESENCE_OFFLINE  = 2,
} removablemedia_presence_t;

/**
 * @brief Possible formats of the file system on the removable media
 *
 * This enumeration defines the possible formats of the file system on the
 * removable media.
 *
 * @since BlackBerry 10.2.0
 */
typedef enum {
    /**
     * Unknown, unsupported, or indeterminate file system format.
     *
     * @since BlackBerry 10.2.0
     */
    REMOVABLEMEDIA_FORMAT_UNKNOWN =  0,
    /**
     * File Allocation Table (FAT) file system, one of FAT12, FAT16, FAT32.
     *
     * @since BlackBerry 10.2.0
     */
    REMOVABLEMEDIA_FORMAT_FAT     =  1,
    /**
     * Extended File Allocation Table (exFAT) file system.
     *
     * @since BlackBerry 10.2.0
     */
    REMOVABLEMEDIA_FORMAT_EXFAT   =  2,
    /**
     * Microsoft NT file system (NTFS).
     *
     * @since BlackBerry 10.2.0
     */
    REMOVABLEMEDIA_FORMAT_NTFS    =  3,
    /**
     * Linux Second Extended (ext2) file system.
     *
     * @since BlackBerry 10.2.0
     */
    REMOVABLEMEDIA_FORMAT_EXT2    =  4,
    /**
     * Apple Hierarchical file system (HFS).
     *
     * @since BlackBerry 10.2.0
     */
    REMOVABLEMEDIA_FORMAT_HFS     =  5,
    /**
     * QNX6 file system.
     *
     * @since BlackBerry 10.2.0
     */
    REMOVABLEMEDIA_FORMAT_QNX6    =  6,
    /**
     * QNX4 file system.
     *
     * @since BlackBerry 10.2.0
     */
    REMOVABLEMEDIA_FORMAT_QNX4    =  7,
    /**
     * QNX Read-only Compressed file system (RCFS).
     *
     * @since BlackBerry 10.2.0
     */
    REMOVABLEMEDIA_FORMAT_RCFS    =  8,
    /**
     * Universal Disk Format (UDF) file system.
     *
     * @since BlackBerry 10.2.0
     */
    REMOVABLEMEDIA_FORMAT_UDF     =  9,
    /**
     * Unformatted media with no file system.
     *
     * @since BlackBerry 10.2.0
     */
    REMOVABLEMEDIA_FORMAT_RAW     = 10,
    /**
     * A file system backed by non-local media.
     *
     * @since BlackBerry 10.2.0
     */
    REMOVABLEMEDIA_FORMAT_REMOTE  = 11,
} removablemedia_format_t;

/**
 * @typedef struct removablemedia_info_t
 * @brief An opaque data type representing the removable media information type
 *
 * The @c #removablemedia_info_t structure is an opaque handle to removable
 * media information.  You can extract the removable media information using
 * Removable Media API functions.
 *
 * @since BlackBerry 10.2.0
 */
typedef struct removablemedia_info_t removablemedia_info_t;

/**
 * @brief Start receiving Removable Media events
 *
 * The @c removablemedia_request_events() function starts to deliver Removable
 * Media events to the application using BPS.  Events will be posted to the
 * currently active channel.
 *
 * @param flags The types of events to deliver.  A value of zero indicates that
 *              all events are requested. The meaning of non-zero values is
 *              reserved for future use.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int removablemedia_request_events(int flags);

/**
 * @brief Stop receiving Removable Media events
 *
 * The @c removablemedia_stop_events() function stops Removable Media events
 * from being delivered to the application using BPS.
 *
 * @param flags The types of events to stop. A value of zero indicates that all
 *              events are stopped. The meaning of non-zero values is reserved
 *              for future use.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int removablemedia_stop_events(int flags);

/**
 * @brief Get the unique domain ID for the Removable Media service
 *
 * The @c removablemedia_get_domain() function gets the unique domain ID for the
 * Removable Media service.  You can use this function in your application to
 * test whether an event that you retrieve using @c bps_get_event() is a
 * Removable Media event, and respond accordingly.
 *
 * @return The domain ID for the Removable Media service.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int removablemedia_get_domain();

/**
 * @brief Retrieve the Removable Media information structure from a @c
 * REMOVABLEMEDIA_INFO event
 *
 * You call the @c removablemedia_event_get_info() function to retrieve the
 * Removable Media information structure from a @c REMOVABLEMEDIA_INFO event.
 * Details about the removable media can be determined using the @c
 * removablemedia_info_get_*() functions.  Do not use the @c
 * removablemedia_free_info() function on this @c #removablemedia_info_t
 * pointer. The memory associated with the Removable Media information structure
 * is valid as long as the event is valid and is freed internally by BlackBerry
 * Platform Services (BPS).
 *
 * @param event The @c REMOVABLEMEDIA_INFO event to get the Removable Media
 *              information structure from.
 *
 * @return The Removable Media information structure.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API removablemedia_info_t *removablemedia_event_get_info(bps_event_t *event);

/**
 * @brief Retrieve the current Removable Media information
 *
 * The @c removablemedia_get_info() function gets the current Removable Media
 * information.  Details about the removable media can be extracted using the @c
 * removablemedia_info_get_*() functions.  @c removablemedia_free_info() must be
 * used on the Removable Media information structure when your application is
 * finished using it.
 *
 * Information for multiple removable media devices or partitions on removable
 * media devices may be available.  Use @c removablemedia_info_get_next() to
 * retrieve this information.  However, @c removablemedia_free_info() must be
 * called on the @c #removablemedia_info_t structure retrieved from this
 * function, to ensure no memory is leaked.
 *
 * @param pinfo If this function successfully completes, this pointer is
 *              populated with the Removable Media information. The caller must
 *              call the @c removablemedia_free_info() function when finished
 *              using the @c info value. If the function does not complete
 *              successfully, the pointer is set to NULL.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int removablemedia_get_info(removablemedia_info_t **pinfo);

/**
 * @brief Free the memory that is used by a Removable Media information
 * structure
 *
 * The @c removablemedia_free_info() function releases the memory that is used
 * by the specified Removable Media information structure, @c
 * #removablemedia_info_t. Only use this function on structures retrieved from
 * the @c removablemedia_get_info() function.
 *
 * @param pinfo The structure whose memory needs to be freed.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE if the @c
 *            #removablemedia_info_t did not come from @c
 *            removablemedia_get_info().  If @c BPS_FAILURE is returned, no
 *            memory has been freed.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int removablemedia_free_info(removablemedia_info_t **pinfo);

/**
 * @brief Retrieve the next Removable Media information

 * The @c removablemedia_info_get_next() function retrieves the next @c
 * #removablemedia_info_t structure from a @c #removablemedia_info_t structure.
 * Only use this function on structures retrieved from the @c
 * removablemedia_get_info() function, or a previous call to this function.
 *
 * @param info The @c #removablemedia_info_t structure to get the next Removable
 *             Media information structure from.
 *
 * @return The next Removable Media information structure or @c NULL if there is
 *         no more Removable Media information structures.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API removablemedia_info_t *removablemedia_info_get_next(removablemedia_info_t *info);

/**
 * @brief Retrieve the media name
 *
 * The @c removablemedia_info_get_name() function retrieves the media name from
 * a @c #removablemedia_info_t structure.
 *
 * @param info The @c #removablemedia_info_t structure to get the media name
 *             from.
 *
 * @return The media name or @c NULL on error.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API const char *removablemedia_info_get_name(removablemedia_info_t *info);

/**
 * @brief Retrieve the volume label
 *
 * The @c removablemedia_info_get_volume_label() function retrieves the volume
 * label from a @c #removablemedia_info_t structure.
 *
 * @param info The @c #removablemedia_info_t structure to get the volume label
 *             from.
 *
 * @return The volume label or @c NULL on error.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API const char *removablemedia_info_get_volume_label(removablemedia_info_t *info);

/**
 * @brief Retrieve the ID
 *
 * The @c removablemedia_info_get_id() function retrieves the ID from a @c
 * #removablemedia_info_t structure.  The ID is a universally unique identifier
 * for the media made of up to 64 hexadecimal digits.
 *
 * @param info The @c #removablemedia_info_t structure to get the ID from.
 *
 * @return The ID or @c NULL on error.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API const char *removablemedia_info_get_id(removablemedia_info_t *info);

/**
 * @brief Retrieve the type of the underlying device
 *
 * The @c removablemedia_info_get_type() function retrieves the type of the
 * underlying device from a @c #removablemedia_info_t structure.
 *
 * @param info The @c #removablemedia_info_t structure to get the type from.
 *
 * @return The type as one of the values of the @c #removablemedia_type_t
 *         enumeration or @c BPS_FAILURE on error.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int removablemedia_info_get_type(removablemedia_info_t *info);

/**
 * @brief Retrieve the state of presence of the media
 *
 * The @c removablemedia_info_get_presence() function retrieves the state of
 * presence or availability of the removable media from a @c
 * #removablemedia_info_t structure.
 *
 * @param info The @c #removablemedia_info_t structure to get the presence from.
 *
 * @return The presence as one of the values of the @c
 *         #removablemedia_presence_t enumeration or @c BPS_FAILURE on error.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int removablemedia_info_get_presence(removablemedia_info_t *info);

/**
 * @brief Determine whether the removable media is mounted
 *
 * The @c removablemedia_info_is_mounted() function determines whether the media
 * is mounted from a @c #removablemedia_info_t structure.
 *
 * @param info The @c #removablemedia_info_t structure to get the mounted status
 *             from.
 *
 * @return @c true if the removable media is mounted, @c false otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API bool removablemedia_info_is_mounted(removablemedia_info_t *info);

/**
 * @brief Determine whether the removable media is busy
 *
 * The @c removablemedia_info_is_busy() function determines whether the media is
 * busy from a @c #removablemedia_info_t structure.
 *
 * @param info The @c #removablemedia_info_t structure to get the busy status
 *             from.
 *
 * @return @c true if the removable media is busy, @c false otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API bool removablemedia_info_is_busy(removablemedia_info_t *info);

/**
 * @brief Retrieve the path where the removable media is mounted at
 *
 * The @c removablemedia_info_get_mount_path() function retrieves the path where
 * the removable media is mounted from a @c #removablemedia_info_t structure.
 *
 * @param info The @c #removablemedia_info_t structure to get the mount path
 *             from.
 *
 * @return The mount path or @c NULL on error.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API const char *removablemedia_info_get_mount_path(removablemedia_info_t *info);

/**
 * @brief Retrieve the path of the device where the removable media is mounted
 *        on
 *
 * The @c removablemedia_info_get_device_path() function retrieves the path of
 * the device where the removable media is mounted from a @c
 * #removablemedia_info_t structure.
 *
 * @param info The @c #removablemedia_info_t structure to get the device path
 *             from.
 *
 * @return The device path or @c NULL on error.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API const char *removablemedia_info_get_device_path(removablemedia_info_t *info);

/**
 * @brief Determine whether the removable media is online
 *
 * The @c removablemedia_info_is_online() function determines whether the
 * removable media is online from a @c #removablemedia_info_t structure.
 *
 * @param info The @c #removablemedia_info_t structure to get the online status
 *             from.
 *
 * @return @c true if the removable media is online, @c false otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API bool removablemedia_info_is_online(removablemedia_info_t *info);

/**
 * @brief Determine whether the removable media is removable
 *
 * The @c removablemedia_info_is_removable() function determines whether the
 * media is removable from a @c #removablemedia_info_t structure.
 *
 * @param info The @c #removablemedia_info_t structure to get the removable
 *             status from.
 *
 * @return @c true if the removable media is removable, @c false otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API bool removablemedia_info_is_removable(removablemedia_info_t *info);

/**
 * @brief Determine whether the removable media is write protected
 *
 * The @c removablemedia_info_is_write_protected() function determines whether
 * the removable media is hardware write protected from a @c
 * #removablemedia_info_t structure.
 *
 * @param info The @c #removablemedia_info_t structure to get the write
 *             protected status from.
 *
 * @return @c true if the removable media is write protected, @c false
 *            otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API bool removablemedia_info_is_write_protected(removablemedia_info_t *info);

/**
 * @brief Determine whether the removable media is formatted
 *
 * The @c removablemedia_info_is_formatted() function determines whether the
 * removable media is formatted with a recognized file system from a @c
 * #removablemedia_info_t structure.
 *
 * @param info The @c #removablemedia_info_t structure to get the formatted
 *             status from.
 *
 * @return @c true if the removable media is formatted, @c false otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API bool removablemedia_info_is_formatted(removablemedia_info_t *info);

/**
 * @brief Retrieve the format of the file system
 *
 * The @c removablemedia_info_get_format() function retrieves the format of the
 * filesystem on the removable media from a @c #removablemedia_info_t structure.
 *
 * @param info The @c #removablemedia_info_t structure to get the format from.
 *
 * @return The format as one of the values of the @c #removablemedia_format_t
 *         enumeration or @c BPS_FAILURE on error.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int removablemedia_info_get_format(removablemedia_info_t *info);

/**
 * @brief Retrieve the total capacity of the removable media
 *
 * The @c removablemedia_info_get_capacity() function retrieves the total
 * capacity of the removable media from a @c #removablemedia_info_t structure.
 * The capacity is reported in Mebibytes (MiB) where 1 MiB = 1024*1024 bytes.
 *
 * @param info The @c #removablemedia_info_t structure to get the capacity from.
 *
 * @return The capacity or @c BPS_FAILURE on error.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API long long removablemedia_info_get_capacity(removablemedia_info_t *info);

/**
 * @brief Retrieve the amount of the total capacity of the removable media that
 *        is free
 *
 * The @c removablemedia_info_get_free_space() function retrieves the amount of
 * total capacity of the removable media that is free from a @c
 * #removablemedia_info_t structure.  The free space is reported in Mebibytes
 * (MiB) where 1 MiB = 1024*1024 bytes.
 *
 * @param info The @c #removablemedia_info_t structure to get the free space
 *             from.
 *
 * @return The amount of free space on the removable media or @c BPS_FAILURE on
 *         error.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API long long removablemedia_info_get_free_space(removablemedia_info_t *info);

/**
 * @brief Determine whether the removable media is read only
 *
 * The @c removablemedia_info_is_read_only() function determines whether the
 * removable media has been mounted as read only from a @c
 * #removablemedia_info_t structure.
 *
 * @param info The @c #removablemedia_info_t structure to get the read only
 *             status from.
 *
 * @return @c true if the removable media is read only, @c false otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API bool removablemedia_info_is_read_only(removablemedia_info_t *info);

/**
 * @brief Retrieve the manufacturer ID
 *
 * The @c removablemedia_info_get_manufacturer_id() function retrieves the
 * hardware-specific manufacturer identifier from a @c #removablemedia_info_t
 * structure.
 *
 * @param info The @c #removablemedia_info_t structure to get the manufacturer
 *             ID from.
 *
 * @return The manufacturer ID or @c BPS_FAILURE on error.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int removablemedia_info_get_manufacturer_id(removablemedia_info_t *info);

/**
 * @brief Retrieve the speed class
 *
 * The @c removablemedia_info_get_speed_class() function retrieves the minimum
 * performance claimed by the removable media from a @c #removablemedia_info_t
 * structure.
 *
 * @param info The @c #removablemedia_info_t structure to get the speed class
 *             from.
 *
 * @return The speed class or @c BPS_FAILURE on error.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int removablemedia_info_get_speed_class(removablemedia_info_t *info);

__END_DECLS

#endif
