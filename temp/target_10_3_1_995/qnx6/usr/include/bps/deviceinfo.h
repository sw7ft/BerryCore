/*
 * Copyright (C) 2012-2014 BlackBerry Limited. All rights reserved.
 */

/**
 * @file deviceinfo.h
 *
 * @brief Functions to determine device information
 *
 * This file defines the device information service, which provides functions
 * for reading information about the device, such as model name, operating
 * system, and PIN.
 *
 * @since BlackBerry 10.0.0
 */

#ifndef _BPS_DEVICEINFO_H_INCLUDED
#define _BPS_DEVICEINFO_H_INCLUDED

#include <stdbool.h>
#include <sys/platform.h>

#include "bps/bps.h"

__BEGIN_DECLS

/**
 * @brief This enumeration defines the states for the presence of a physical
 * keyboard on the device
 *
 * @since BlackBerry 10.1.0
 */
typedef enum {
    /**
     * A physical keyboard is not present on the device.
     *
     * @since BlackBerry 10.1.0
     */
    DEVICEINFO_KEYBOARD_NOT_PRESENT = 0,

    /**
     * A physical keyboard is present on the device.
     *
     * @since BlackBerry 10.1.0
     */
    DEVICEINFO_KEYBOARD_PRESENT = 1,
} deviceinfo_keyboard_t;

/**
 * @brief This enumeration defines the type of HDMI connector on the device
 *
 * @since BlackBerry 10.2.0
 */
typedef enum {
    /**
     * An HDMI connector is not present on the device.
     *
     * @since BlackBerry 10.2.0
     */
    DEVICEINFO_HDMI_CONNECTOR_NONE = 0,

    /**
     * A Micro HDMI connector is present on the device.
     *
     * @since BlackBerry 10.2.0
     */
    DEVICEINFO_HDMI_CONNECTOR_MICRO = 1,
} deviceinfo_hdmi_connector_t;

/**
 * @typedef struct deviceinfo_details_t
 * @brief Opaque device information details type
 *
 * The @c #deviceinfo_details_t structure is an opaque handle to information
 * pertaining to the device.  You can extract device information using accessor
 * functions.
 * 
 * @since BlackBerry 10.0.0
 */
typedef struct deviceinfo_details_t deviceinfo_details_t;

/**
 * @typedef struct deviceinfo_identifying_details_t
 * @brief Opaque device identifying information type
 *
 * The @c #deviceinfo_identifying_details_t structure is an opaque handle to
 * information that uniquely identifies the device.  You can extract device
 * identifying information using accessor functions.
 *
 * The application must have the @c read_device_identifying_information
 * capability to access this information. To grant an application the @c
 * read_device_identifying_information capability, the bar-descriptor.xml file
 * in the application's project must contain the line
 * "<permission>read_device_identifying_information</permission>".
 *
 * @since BlackBerry 10.0.0
 */
typedef struct deviceinfo_identifying_details_t deviceinfo_identifying_details_t;

/**
 * @brief Retrieve the current device information
 *
 * The @c deviceinfo_get_details() function gets the current device information.
 *
 * @param details This will be populated with the device information.  The
 *                caller must call @c deviceinfo_free_details() when done with
 *                this structure.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int deviceinfo_get_details(deviceinfo_details_t **details);

/**
 * @brief Free the memory that is used by a device information structure
 *
 * The @c deviceinfo_free_details() function frees the memory that is used by
 * the specified device information structure.
 *
 * @param details The structure whose memory needs to be freed.  Note that the
 *                pointer to the structure is not freed.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API void deviceinfo_free_details(deviceinfo_details_t **details);

/**
 * @brief Retrieve the hardware ID
 *
 * The @c deviceinfo_details_get_hardware_id() function gets the hardware ID
 * from the specified @c #deviceinfo_details_t structure.
 *
 * @param details The @c #deviceinfo_details_t structure to get the hardware ID
 *                from.
 *
 * @return The hardware ID.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char * deviceinfo_details_get_hardware_id(deviceinfo_details_t *details);

/**
 * @brief Retrieve the device name
 *
 * The @c deviceinfo_details_get_device_name() function gets the device name from
 * the specified @c #deviceinfo_details_t structure.
 *
 * @param details The @c #deviceinfo_details_t structure to get the device name
 *                from.
 *
 * @return The device name.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API const char *deviceinfo_details_get_device_name(deviceinfo_details_t *details);

/**
 * @brief Retrieve the model name
 *
 * The @c deviceinfo_details_get_model_name() function gets the model name from
 * the specified @c #deviceinfo_details_t structure.
 *
 * @param details The @c #deviceinfo_details_t structure to get the model name
 *                from.
 *
 * @return The model name.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API const char *deviceinfo_details_get_model_name(deviceinfo_details_t *details);

/**
 * @brief Retrieve the model number
 *
 * The @c deviceinfo_details_get_model_number() function gets the model number
 * from the specified @c #deviceinfo_details_t structure.
 *
 * @param details The @c #deviceinfo_details_t structure to get the model number
 *                from.
 *
 * @return The model number.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API const char *deviceinfo_details_get_model_number(deviceinfo_details_t *details);

/**
 * @brief Retrieve the device OS
 *
 * The @c deviceinfo_details_get_device_os() function gets the device OS from
 * the specified @c #deviceinfo_details_t structure.
 *
 * @param details The @c #deviceinfo_details_t structure to get the device OS
 *                from.
 *
 * @return The device OS.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char * deviceinfo_details_get_device_os(deviceinfo_details_t *details);

/**
 * @brief Retrieve the device OS version
 *
 * The @c deviceinfo_details_get_device_os_version() function gets the device OS
 * version from the specified @c #deviceinfo_details_t structure.  The device OS
 * version is the version number of the operating system on the device.
 *
 * @param details The @c #deviceinfo_details_t structure to get the device OS
 *                version from.
 *
 * @return The device OS version.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char * deviceinfo_details_get_device_os_version(deviceinfo_details_t *details);

/**
 * @brief Retrieve the processor name
 *
 * The @c deviceinfo_details_get_processor_name() function gets the processor
 * name from the specified @c #deviceinfo_details_t structure.
 *
 * @param details The @c #deviceinfo_details_t structure to get the processor
 *                name from.
 *
 * @return The processor name.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API const char *deviceinfo_details_get_processor_name(deviceinfo_details_t *details);

/**
 * @brief Retrieve the number of processor cores
 *
 * The @c deviceinfo_details_get_processor_core_count() function gets the number
 * of processor cores from the specified @c #deviceinfo_details_t structure.
 *
 * @param details The @c #deviceinfo_details_t structure to get the processor
 *                core count from.
 *
 * @return The processor core count.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int deviceinfo_details_get_processor_core_count(deviceinfo_details_t *details);

/**
 * @brief Retrieve the name of a processor core
 *
 * The @c deviceinfo_details_get_processor_core_name() function gets the name of
 * the indexed processor core from the specified @c #deviceinfo_details_t
 * structure.
 *
 * @param details The @c #deviceinfo_details_t structure to get the processor
 *                core name from.
 *
 * @param index The index of the processor core to get the name of.  Must be
 *              less than @c deviceinfo_details_get_processor_core_count().
 *
 * @return The processor core name.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API const char *deviceinfo_details_get_processor_core_name(deviceinfo_details_t *details, int index);

/**
 * @brief Retrieve the speed of a processor core
 *
 * The @c deviceinfo_details_get_processor_core_speed() function gets the speed
 * of the indexed processor core from the specified @c #deviceinfo_details_t
 * structure.  The processor core speed is reported in megahertz (MHz).
 *
 * @param details The @c #deviceinfo_details_t structure to get the processor
 *                core speed from.
 *
 * @param index The index of the processor core to get the speed of.  Must be
 *              less than @c deviceinfo_details_get_processor_core_count().
 *
 * @return The processor core speed or @c BPS_FAILURE on error.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int deviceinfo_details_get_processor_core_speed(deviceinfo_details_t *details, int index);

/**
 * @brief Indicate whether the device is a simulator
 *
 * The @c deviceinfo_details_is_simulator() function indicates whether the
 * device is a simulator from the specified @c #deviceinfo_details_t structure.
 *
 * @param details The @c #deviceinfo_details_t structure to get simulator status
 *                from.
 *
 * @return @c true if the device is the simulator, @c false otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API bool deviceinfo_details_is_simulator(deviceinfo_details_t *details);

/**
 * @brief Indicate whether the device has a physical keyboard
 *
 * The @c deviceinfo_details_get_keyboard() function indicates whether the
 * device has a physical keyboard from the specified @c #deviceinfo_details_t
 * structure.
 *
 * @param details The @c #deviceinfo_details_t structure to get the physical
 *                keyboard status from.
 *
 * @return One of the values of the @c #deviceinfo_keyboard_t enumeration, or @c
 * BPS_FAILURE if it is unknown if the device has a physical keyboard or not.
 *
 * @since BlackBerry 10.1.0
 */
BPS_API int deviceinfo_details_get_keyboard(deviceinfo_details_t *details);

/**
 * @brief Retrieve the type of HDMI connector on the device
 *
 * The @c deviceinfo_details_get_hdmi_connector() function gets the type of HDMI
 * connector on the device from the specified @c #deviceinfo_details_t
 * structure.
 *
 * @param details The @c #deviceinfo_details_t structure to get the HDMI
 *                connector type from.
 *
 * @return One of the values of the @c #deviceinfo_hdmi_connector_t enumeration,
 * or @c BPS_FAILURE if it is unknown.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int deviceinfo_details_get_hdmi_connector(deviceinfo_details_t *details);

/**
 * @brief Retrieve the device identifying information
 *
 * The @c deviceinfo_get_identifying_details() function gets the device
 * identifying information. This function requires the application to have the
 * @c read_device_identifying_information capability. To grant an application
 * the @c read_device_identifying_information capability, the bar-descriptor.xml
 * file in the application's project must contain the line
 * "<permission>read_device_identifying_information</permission>".
 *
 * @param details This will be populated with the device identifying information.
 *        The caller must call @c deviceinfo_free_identifying_details() when
 *        done with this structure.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int deviceinfo_get_identifying_details(deviceinfo_identifying_details_t **details);

/**
 * @brief Free the memory that is used by a device identifying information
 * structure
 *
 * The @c deviceinfo_free_identifying_details() function frees the memory that
 * is used by the specified device identifying information structure.
 *
 * @param details The structure whose memory needs to be freed.  Note that the
 *                pointer to the structure is not freed.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API void deviceinfo_free_identifying_details(deviceinfo_identifying_details_t **details);

/**
 * @brief Retrieve the PIN
 *
 * The @c deviceinfo_identifying_details_get_pin() function gets the PIN from
 * the specified @c #deviceinfo_identifying_details_t structure.
 *
 * @param details The @c #deviceinfo_identifying_details_t structure to get the
 *                PIN from.
 *
 * @return The PIN.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int deviceinfo_identifying_details_get_pin(deviceinfo_identifying_details_t *details);

/**
 * @brief Retrieve the PIN as a string
 *
 * The @c deviceinfo_identifying_details_get_pin_string() function gets the PIN
 * as a string from the specified @c #deviceinfo_identifying_details_t
 * structure.
 *
 * @param details The @c #deviceinfo_identifying_details_t structure to get the
 *                PIN from.
 *
 * @return The PIN as a string.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API const char *deviceinfo_identifying_details_get_pin_string(deviceinfo_identifying_details_t *details);

/**
 * @brief Retrieve the serial number of the device
 *
 * The @c deviceinfo_identifying_details_get_serial_number() function gets the
 * serial number of the device from the specified @c
 * #deviceinfo_identifying_details_t structure.
 *
 * @param details The @c #deviceinfo_identifying_details_t structure to get the
 *                serial number from.
 *
 * @return The serial number of the device.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API long long deviceinfo_identifying_details_get_serial_number(deviceinfo_identifying_details_t *details);

/**
 * @brief Retrieve the serial number of the device as a string
 *
 * The @c deviceinfo_identifying_details_get_serial_number_string() function
 * gets the serial number of the device as a string from the specified @c
 * #deviceinfo_identifying_details_t structure.
 *
 * @param details The @c #deviceinfo_identifying_details_t structure to get the
 *                serial number of the device from.
 *
 * @return The serial number of the device as a string.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API const char *deviceinfo_identifying_details_get_serial_number_string(deviceinfo_identifying_details_t *details);

/**
 * @brief Retrieve the IMEI
 *
 * The @c deviceinfo_identifying_details_get_imei() function gets the IMEI from
 * the specified @c #deviceinfo_identifying_details_t structure.
 *
 * @param details The @c #deviceinfo_identifying_details_t structure to get the
 *                IMEI from.
 *
 * @return The IMEI or @c NULL if it is not available.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API const char *deviceinfo_identifying_details_get_imei(deviceinfo_identifying_details_t *details);

/**
 * @brief Retrieve the MEID
 *
 * The @c deviceinfo_identifying_details_get_meid() function gets the MEID from
 * the specified @c #deviceinfo_identifying_details_t structure.
 *
 * @param details The @c #deviceinfo_identifying_details_t structure to get the
 *                MEID from.
 *
 * @return The MEID or @c NULL if it is not available.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API const char *deviceinfo_identifying_details_get_meid(deviceinfo_identifying_details_t *details);

/**
 * @brief Device information
 *
 * @deprecated Use @c #deviceinfo_details_t instead.
 *
 * The @c deviceinfo_data_t structure contains information pertaining to the
 * device.
 *
 * @since BlackBerry 10.0.0
 */
struct deviceinfo_data_t {
    /**
     * The device's hardware ID.
     *
     * @since BlackBerry 10.0.0
     */
    int hardware_id;

    /**
     * The device's OS.
     *
     * @since BlackBerry 10.0.0
     */
    char *device_os;

    /**
     * The device's SCM bundle.
     *
     * @since BlackBerry 10.0.0
     */
    char *scm_bundle;
};

/**
 * @deprecated Use @c #deviceinfo_details_t
 * A data type that contains information about the device, which includes:
 * - the identifier for the hardware
 * - the operating on the device
 * - the software control module bundle
 *
 * @since BlackBerry 10.0.0
 */
typedef struct deviceinfo_data_t deviceinfo_data_t;

/**
 * @brief Device identifying information
 *
 * @deprecated Use @c #deviceinfo_identifying_details_t instead.
 *
 * The @c deviceinfo_identifying_data_t structure contains information that
 * uniquely identifies the device.  The application must have the @c
 * read_device_identifying_information capability to access this information. To
 * grant an application the @c read_device_identifying_information capability,
 * the bar-descriptor.xml file in the application's project must contain the
 * line "<permission>read_device_identifying_information</permission>".
 *
 * @since BlackBerry 10.0.0
 */
struct deviceinfo_identifying_data_t {
    /**
     * The device's PIN.
     *
     * @since BlackBerry 10.0.0
     */
    int pin;

    /**
     * The device's serial number.
     *
     * @since BlackBerry 10.0.0
     */
    long long serial_number;
};
/**
 * @deprecated Use @c #deviceinfo_identifying_details_t
 * @typedef struct deviceinfo_identifying_data_t
 * A data type for the @c struct @c deviceinfo_identifying_data_t, which
 * stores the PIN and serial number of the device.
 *
 * @since BlackBerry 10.0.0
 */
typedef struct deviceinfo_identifying_data_t deviceinfo_identifying_data_t;

/**
 * @brief Retrieve the current device information
 *
 * @deprecated Use @c deviceinfo_get_details() instead.
 *
 * The @c deviceinfo_get_data() function gets the current device information.
 *
 * @param data This will be populated with the device information.  The caller
 *             must call the @c deviceinfo_free_data() function when done with
 *             this structure.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int deviceinfo_get_data(deviceinfo_data_t *data) BPS_DEPRECATED;

/**
 * @brief Free the memory that is used by a device information structure
 *
 * @deprecated This function is deprecated.
 *
 * The @c deviceinfo_free_data() function frees the memory that is used by the
 * specified device information structure.
 *
 * @param data The structure whose memory needs to be freed.  Note that the
 *             pointer to the structure is not freed.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API void deviceinfo_free_data(deviceinfo_data_t *data) BPS_DEPRECATED;

/**
 * @brief Retrieve the device identifying information
 *
 * @deprecated Use @c deviceinfo_get_identifying_details()
 *
 * The @c deviceinfo_get_identifying_data() function gets the device identifying
 * information.  This function requires the application to have the @c
 * read_device_identifying_information capability. To grant an application the
 * @c read_device_identifying_information capability, the bar-descriptor.xml
 * file in the application's project must contain the line
 * "<permission>read_device_identifying_information</permission>".
 *
 * @param data This will be populated with the device identifying information.
 *             The caller must call the @c deviceinfo_free_identifying_data()
 *             function when done with this structure.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int deviceinfo_get_identifying_data(deviceinfo_identifying_data_t *data) BPS_DEPRECATED;

/**
 * @brief Free the memory that is used by a device identifying information
 * structure
 *
 * @deprecated This function is deprecated.
 *
 * The @c deviceinfo_free_identifying_data() function frees the memory that is
 * used by the specified device identifying information structure.
 *
 * @param data The structure whose memory needs to be freed.  Note that the
 *             pointer to the structure is not freed.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API void deviceinfo_free_identifying_data(deviceinfo_identifying_data_t *data) BPS_DEPRECATED;

__END_DECLS

#endif /* include guard */
