/*
 * Copyright (C) 2012-2014 BlackBerry Limited. All rights reserved.
 */

/**
 * @file battery.h
 *
 * @brief Functions to receive the state of the battery
 * 
 * This file defines the battery service, which provides notifications of when
 * the state of the device's battery changes. For example, you can use functions
 * from this file to determine whether the device is charging or what percentage
 * of battery charge is left.
 *
 * @since BlackBerry 10.0.0
 */

#ifndef _BPS_BATTERY_H_INCLUDED
#define _BPS_BATTERY_H_INCLUDED

#include <stdbool.h>
#include <sys/platform.h>

#include "bps/bps.h"

__BEGIN_DECLS

/**
 * @brief Battery events
 * 
 * This enumeration defines the possible battery events.  Currently, there is
 * only one event.
 * @anonenum bps_battery_events Battery events
 *
 * @since BlackBerry 10.0.0
 */
enum {
    /**
     * The single battery event, which contains all of the information about the
     * device's battery.
     *
     * @since BlackBerry 10.0.0
     */
    BATTERY_INFO        = 0x01
};

/**
 * @brief Possible battery charger states
 *
 * This enumeration defines the possible battery charger states.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * A battery-related system error.
     *
     * @since BlackBerry 10.0.0
     */
    BATTERY_CHARGER_ERROR      = 0,
    /**
     * The charger is invalid or weak.
     *
     * @since BlackBerry 10.0.0
     */
    BATTERY_CHARGER_BAD        = 1,
    /**
     * No charger is present.
     *
     * @since BlackBerry 10.0.0
     */
    BATTERY_CHARGER_NONE       = 2,
    /**
     * The charger is connected, but not charging since the battery is fully
     * charged.
     *
     * @since BlackBerry 10.0.0
     */
    BATTERY_CHARGER_PLUGGED    = 3,
    /**
     * The charger is connected and the battery is being charged.
     *
     * @since BlackBerry 10.0.0
     */
    BATTERY_CHARGER_CHARGING   = 4,
} battery_charger_info_t;

/**
 * @brief Possible battery charging states
 *
 * This enumeration defines the possible battery charging states.
 *
 * @since BlackBerry 10.2.0
 */
typedef enum {
    /**
     * Not charging.
     *
     * @since BlackBerry 10.2.0
     */
    BATTERY_CHARGING_NOT_CHARGING     = 0,
    /**
     * Trickle charging.
     *
     * @since BlackBerry 10.2.0
     */
    BATTERY_CHARGING_TRICKLE_CHARGING = 1,
    /**
     * Charging with constant current.
     *
     * @since BlackBerry 10.2.0
     */
    BATTERY_CHARGING_CONSTANT_CURRENT = 2,
    /**
     * Charging with constant voltage.
     *
     * @since BlackBerry 10.2.0
     */
    BATTERY_CHARGING_CONSTANT_VOLTAGE = 3,
    /**
     * Done charging.
     *
     * @since BlackBerry 10.2.0
     */
    BATTERY_CHARGING_DONE_CHARGING    = 4,
} battery_charging_state_t;

/**
 * @brief Values returned by battery functions to indicate special conditions
 *
 * @since BlackBerry 10.2.0
 */
typedef enum {
    /**
     * A special value returned by the @c battery_info_get_time_to_empty() and
     * @c battery_info_get_time_to_full() functions to indicate that their value
     * is not applicable.
     *
     * For example, when the device is plugged in, the battery does not
     * discharge, therefore a call to the @c battery_info_get_time_to_empty()
     * function will return @c #BATTERY_TIME_NA. Similarly, when the device is
     * not plugged in, the battery does not charge, therefore, a call to the @c
     * battery_info_get_time_to_full() function will return @c #BATTERY_TIME_NA.
     * 
     * @since BlackBerry 10.0.0
     */
    BATTERY_TIME_NA = 65535,

    /**
     * A special value returned by various battery info functions to indicate
     * that there is no valid value available for the attribute.
     * 
     * @since BlackBerry 10.2.0
     */
    BATTERY_INVALID_VALUE = 80000000

} battery_special_values_t;

/**
 * @typedef struct battery_info_t
 * @brief An opaque data type representing the battery information type
 *
 * The @c #battery_info_t structure is an opaque handle to battery information.
 * You can extract the battery information using Battery API functions.
 *
 * @since BlackBerry 10.0.0
 */
typedef struct battery_info_t battery_info_t;

/**
 * @brief Start receiving battery events
 *
 * The @c battery_request_events() function starts to deliver battery events to
 * the application using BPS.  Events will be posted to the currently active
 * channel.
 *
 * @param flags The types of events to deliver.  A value of zero indicates that
 *              all events are requested. The meaning of non-zero values is
 *              reserved for future use.
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int battery_request_events(int flags);

/**
 * @brief Stop receiving battery events
 *
 * The @c battery_stop_events() function stops battery events from being
 * delivered to the application using BPS.
 *
 * @param flags The types of events to stop. A value of zero indicates that all
 *              events are stopped. The meaning of non-zero values is reserved
 *              for future use.
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int battery_stop_events(int flags);

/**
 * @brief Retrieve the unique domain ID for the battery service
 * 
 * The @c battery_get_domain() function gets the unique domain ID for the
 * battery service.  You can use this function in your application to test
 * whether an event that you retrieve using @c bps_get_event() is a battery
 * event, and respond accordingly.
 *
 * @return The domain ID for the battery service.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int battery_get_domain();

/**
 * @brief Retrieve the battery information structure from a @c
 *        BATTERY_INFO event
 *
 * You call the @c battery_event_get_info() function to retrieve the battery
 * information structure from a @c BATTERY_INFO event. Details about the battery
 * can be determined using the @c battery_info_get_*() functions.  Do not use
 * the @c battery_free_info() function on this @c #battery_info_t pointer. The
 * memory associated with the battery information structure is valid as long as
 * the event is valid and is freed internally by BlackBerry Platform Services
 * (BPS).
 *
 * @param event The @c BATTERY_INFO event to get the battery information
 *              structure from.
 * @return The battery information structure.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API battery_info_t *battery_event_get_info(bps_event_t *event);

/**
 * @brief Retrieve the current the battery information
 *
 * The @c battery_get_info() function gets the current battery information.
 * Details about the battery can be extracted using the @c battery_info_get_*()
 * functions.  @c battery_free_info() must be used on the battery information
 * structure when your application is finished using it.
 *
 * @param info If this function successfully completes, this pointer is
 *             populated with the battery information. The caller must call the
 *             @c battery_free_info() function when finished with using the @c
 *             info value. If the function does not complete successfully, the
 *             pointer is set to NULL.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int battery_get_info(battery_info_t **info);

/**
 * @brief Free the memory that is used by a battery information structure
 *
 * The @c battery_free_info() function releases the memory that is used by the
 * specified battery information structure, @c #battery_info_t. Only use this
 * function on structures retrieved from the @c battery_get_info() function.
 *
 * @param info The structure whose memory needs to be freed.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API void battery_free_info(battery_info_t **info);

/**
 * @brief Determine whether the battery is ready
 *
 * The @c battery_info_is_battery_ready() function determines whether the
 * battery is ready from a @c #battery_info_t structure. If the battery is not
 * ready, then all the other battery-related information in the structure is
 * invalid.
 *
 * @param info The @c #battery_info_t structure to get the battery ready status
 *             from.
 * @return @c true if the battery is ready, @c false otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API bool battery_info_is_battery_ready(battery_info_t *info);

/**
 * @brief Determine whether the battery is present
 *
 * The @c battery_info_is_battery_present() function determines whether the
 * battery is present in a device from a @c #battery_info_t structure.
 *
 * @param info The @c #battery_info_t structure to retrieve the battery presence
 *             from.
 *
 * @return @c true if the battery is present, @c false if the battery is not
 *         present or if the battery was not ready.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API bool battery_info_is_battery_present(battery_info_t *info);

/**
 * @brief Retrieve the battery ID
 *
 * The @c battery_info_get_battery_id() function retrieves the battery ID from a
 * @c #battery_info_t structure.
 *
 * @param info The @c #battery_info_t structure to get the battery ID from.
 * @return The battery ID or @c BPS_FAILURE if the battery was not ready.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int battery_info_get_battery_id(battery_info_t *info);

/**
 * @brief Retrieve status of the battery
 *
 * The @c battery_info_is_battery_ok() function gets whether the battery
 * is OK from a @c #battery_info_t structure. If the battery is not OK, it may
 * indicate a problem with the battery or that the battery is not ready.
 *
 * @param info The @c #battery_info_t structure to get the battery OK status
 *             from.
 * @return @c true if the battery is OK, @c false if the battery is not OK or if
 *         the battery was not ready.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API bool battery_info_is_battery_ok(battery_info_t *info);

/**
 * @brief Retrieve the state of charge from a battery information structure
 *
 * The @c battery_info_get_state_of_charge() function retrieves the state of
 * charge from a @c #battery_info_t structure. The state of charge is reported
 * as a percentage from 0 to 100.
 *
 * @param info The @c #battery_info_t structure to get the state of charge from.
 * @return The state of charging as percentage value, @c BPS_FAILURE otherwise.
 *         Typically, @c BPS_FAILURE is returned if the battery was not ready.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int battery_info_get_state_of_charge(battery_info_t *info);

/**
 * @brief Retrieve the state of health from a battery information structure
 *
 * The @c battery_info_get_state_of_health() function retrieves the state of
 * health from a @c #battery_info_t structure.  The state of health is reported
 * as a percentage from 0 to 100.
 *
 * @param info The @c #battery_info_t structure to get the state of health from.
 * @return The state of health in percent or @c BPS_FAILURE if the battery was
 *         not ready.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int battery_info_get_state_of_health(battery_info_t *info);

/**
 * @brief Retrieve the amount of time before the battery is fully discharged
 *        (empty)
 *
 * The @c battery_info_get_time_to_empty() function gets the retrieves the time
 * the battery has left before becoming fully discharged from a @c
 * #battery_info_t structure.
 *
 * @param info The @c #battery_info_t structure to get the time to empty from.
 * @return The time to empty (in minutes), or @c #BATTERY_TIME_NA if the battery
 *         is not being discharged, or @c BPS_FAILURE on error.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int battery_info_get_time_to_empty(battery_info_t *info);

/**
 * @brief Retrieve the amount of time to fully charge the battery
 *
 * The @c battery_info_get_time_to_full() function gets the time to fully charge
 * the battery from a @c #battery_info_t structure.
 *
 * @param info The @c #battery_info_t structure to get the time to fully charge
 *             from.
 * @return The time to fully charge (in minutes), @c #BATTERY_TIME_NA if the
 *         battery is not being charged, or @c BPS_FAILURE on error.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int battery_info_get_time_to_full(battery_info_t *info);

/**
 * @brief Retrieve the battery name
 *
 * The @c battery_info_get_battery_name() function retrieves the battery name
 * from a @c #battery_info_t structure.
 *
 * @param info The @c #battery_info_t structure to get the battery name from.
 * @return The battery name or @c NULL if the battery name is not available.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API const char *battery_info_get_battery_name(battery_info_t *info);

/**
 * @brief Retrieve the battery voltage
 *
 * The @c battery_info_get_battery_voltage() function retrieves the battery
 * voltage from a @c #battery_info_t structure.  The battery voltage is reported
 * in millivolts (mV).
 *
 * @param info The @c #battery_info_t structure to get the battery voltage from.
 * @return The battery voltage or @c #BATTERY_INVALID_VALUE if the battery
 *         voltage is not available.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int battery_info_get_battery_voltage(battery_info_t *info);

/**
 * @brief Retrieve the available energy remaining in the battery
 *
 * The @c battery_info_get_battery_available_energy() function retrieves the
 * predicted charge or available energy remaining in the battery from a @c
 * #battery_info_t structure.  The available energy remaining in the battery is
 * reported in milliwatt-hours (mWh).
 *
 * @param info The @c #battery_info_t structure to get the available energy
 *             remaining in the battery from.
 * @return The available energy remaining in the battery or @c
 *         #BATTERY_INVALID_VALUE if the available energy remaining in the
 *         battery is not available.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int battery_info_get_battery_available_energy(battery_info_t *info);

/**
 * @brief Retrieve the battery average current
 *
 * The @c battery_info_get_battery_average_current() function retrieves the
 * average current flowing through the sense resistor of the battery from a @c
 * #battery_info_t structure.  The battery average current is reported in
 * milliamperes (mA).
 *
 * @param info The @c #battery_info_t structure to get the battery average
 *             current from.
 * @return The battery average current or @c #BATTERY_INVALID_VALUE if the
 *         battery average current is not available.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int battery_info_get_battery_average_current(battery_info_t *info);

/**
 * @brief Retrieve the battery average power
 *
 * The @c battery_info_get_battery_average_power() function retrieves the
 * average power of the current discharge of the battery from a @c
 * #battery_info_t structure.  It is negative when the battery is discharging
 * and positive when the battery is charging.  The battery average power is
 * reported in milliwatts (mW).
 *
 * @param info The @c #battery_info_t structure to get the battery average power
 *             from.
 * @return The battery average power or @c #BATTERY_INVALID_VALUE if the battery
 *         average power is not available.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int battery_info_get_battery_average_power(battery_info_t *info);

/**
 * @brief Determine whether the battery alert is triggered
 *
 * The @c battery_info_get_battery_alert() function determines whether the
 * battery alert has been triggered from a @c #battery_info_t structure.  The
 * battery alert is triggered if the state of charge goes below a threshold.
 *
 * @param info The @c #battery_info_t structure to get the battery alert status
 *             from.
 * @return @c true if the battery alert is triggered, @c false otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API bool battery_info_get_battery_alert(battery_info_t *info);

/**
 * @brief Retrieve the battery cycle count
 *
 * The @c battery_info_get_battery_cycle_count() function retrieves the cycle
 * count of the battery from a @c #battery_info_t structure.
 *
 * @param info The @c #battery_info_t structure to get the battery cycle count
 *             from.
 * @return The battery cycle count or @c #BATTERY_INVALID_VALUE if the battery
 *         cycle count is not available.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int battery_info_get_battery_cycle_count(battery_info_t *info);

/**
 * @brief Retrieve the battery temperature
 *
 * The @c battery_info_get_battery_temperature() function retrieves the battery
 * temperature from a @c #battery_info_t structure.  The battery temperature is
 * reported in degrees Celsius.
 *
 * @param info The @c #battery_info_t structure to get the battery temperature
 *             from.
 * @return The battery temperature or @c not-a-number (NaN) if the battery
 *         temperature is not available.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API float battery_info_get_battery_temperature(battery_info_t *info);

/**
 * @brief Retrieve the battery design capacity
 *
 * The @c battery_info_get_battery_design_capacity() function retrieves the
 * battery design capacity from a @c #battery_info_t structure.  The battery
 * design capacity is reported in milliampere-hours (mAh).
 *
 * @param info The @c #battery_info_t structure to get the battery design
 *             capacity from.
 * @return The battery design capacity or @c #BATTERY_INVALID_VALUE if the
 *         battery design capacity is not available.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int battery_info_get_battery_design_capacity(battery_info_t *info);

/**
 * @brief Retrieve the battery full available capacity
 *
 * The @c battery_info_get_battery_full_available_capacity() function retrieves
 * the uncompensated capacity of the battery when fully charged from a @c
 * #battery_info_t structure.  The battery full available capacity is reported
 * in milliampere-hours (mAh).
 *
 * @param info The @c #battery_info_t structure to get the battery full
 *             available capacity from.
 * @return The battery full available capacity or @c #BATTERY_INVALID_VALUE if
 *         the battery full available capacity is not available.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int battery_info_get_battery_full_available_capacity(battery_info_t *info);

/**
 * @brief Retrieve the battery full charge capacity
 *
 * The @c battery_info_get_battery_full_charge_capacity() function retrieves the
 * compensated capacity of the battery when fully charged from a @c
 * #battery_info_t structure.  The battery full charge capacity is reported in
 * milliampere-hours (mAh).
 *
 * @param info The @c #battery_info_t structure to get the battery full charge
 *             capacity from.
 * @return The battery full charge capacity or @c #BATTERY_INVALID_VALUE if the
 *         battery full charge capacity is not available.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int battery_info_get_battery_full_charge_capacity(battery_info_t *info);

/**
 * @brief Retrieve the battery maximum load current
 *
 * The @c battery_info_get_battery_max_load_current() function retrieves the
 * current of the maximum load conditions from a @c #battery_info_t structure.
 * The battery maximum load current is reported in milliamperes (mA).
 *
 * @param info The @c #battery_info_t structure to get the battery maximum load
 *             current from.
 * @return The battery maximum load current or @c #BATTERY_INVALID_VALUE if the
 *         battery maximum load current is not available.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int battery_info_get_battery_max_load_current(battery_info_t *info);

/**
 * @brief Retrieve the battery maximum load time to empty
 *
 * The @c battery_info_get_battery_max_load_time_to_empty() function retrieves
 * the time to empty at the maximum load current discharge rate from a @c
 * #battery_info_t structure.  The battery maximum load time to empty is
 * reported in minutes.
 *
 * @param info The @c #battery_info_t structure to get the battery maximum load
 *             time to empty from.
 * @return The battery maximum load time to empty or @c #BATTERY_INVALID_VALUE
 *         if the battery maximum load time to empty is not available.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int battery_info_get_battery_max_load_time_to_empty(battery_info_t *info);

/**
 * @brief Retrieve the battery nominal available capacity
 *
 * The @c battery_info_get_battery_nominal_available_capacity() function
 * retrieves the uncompensated capacity remaining of the battery from a @c
 * #battery_info_t structure.  The battery nominal available capacity is
 * reported in milliampere-hours (mAh).
 *
 * @param info The @c #battery_info_t structure to get the battery nominal
 *             available capacity from.
 * @return The battery nominal available capacity or @c #BATTERY_INVALID_VALUE
 *         if the battery nominal available capacity is not available.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int battery_info_get_battery_nominal_available_capacity(battery_info_t *info);

/**
 * @brief Retrieve the battery time to empty at constant power
 *
 * The @c battery_info_get_battery_time_to_empty_at_constant_power() function
 * retrieves the predicted time to empty if the battery is discharged at the
 * average power value from a @c #battery_info_t structure.  The battery time to
 * empty at constant power is reported in minutes.
 *
 * @param info The @c #battery_info_t structure to get the battery time to empty
 *             at constant power from.
 * @return The battery time to empty at constant power or @c
 *         #BATTERY_INVALID_VALUE if the battery time to empty at constant power
 *         is not available.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int battery_info_get_battery_time_to_empty_at_constant_power(battery_info_t *info);

/**
 * @brief Determine whether the charger is ready
 *
 * The @c battery_info_is_charger_ready() function determines whether the
 * charger is ready from a @c #battery_info_t structure. If the charger is not
 * ready, then all the other charger-related information in the structure is
 * invalid.
 *
 * @param info The @c #battery_info_t structure to get the charger ready status
 *             from.
 * @return @c true if the charger is ready, @c false otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API bool battery_info_is_charger_ready(battery_info_t *info);

/**
 * @brief Retrieve the state of the charger
 *
 * The @c battery_info_get_charger_info() function retrieves information about
 * the charger from a @c #battery_info_t structure.
 *
 * @param info The @c #battery_info_t structure to get the charger info from.
 * @return The charger information as one of the values of the @c
 *         #battery_charger_info_t enumeration or @c BPS_FAILURE on error.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int battery_info_get_charger_info(battery_info_t *info);

/**
 * @brief Retrieve the charger maximum input current
 *
 * The @c battery_info_get_charger_max_input_current() function retrieves
 * the maximum current that can be drawn from the input power source from a @c
 * #battery_info_t structure.  The charger maximum input current is reported in
 * milliamperes (mA).
 *
 * @param info The @c #battery_info_t structure to get the charger maximum input
 *             current from.
 * @return The charger maximum input current or @c #BATTERY_INVALID_VALUE if the
 *         charger maximum input current is not available.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int battery_info_get_charger_max_input_current(battery_info_t *info);

/**
 * @brief Retrieve the charger maximum charge current
 *
 * The @c battery_info_get_charger_max_charge_current() function retrieves
 * the maximum current capacity of the charging circuitry from a @c
 * #battery_info_t structure.  The charger maximum charge current is reported in
 * milliamperes (mA).
 *
 * @param info The @c #battery_info_t structure to get the charger maximum
 *             charge current from.
 * @return The charger maximum charge current or @c #BATTERY_INVALID_VALUE if
 *         the charger maximum charge current is not available.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int battery_info_get_charger_max_charge_current(battery_info_t *info);

/**
 * @brief Retrieve the charger name
 *
 * The @c battery_info_get_charger_name() function retrieves the charger name
 * from a @c #battery_info_t structure.
 *
 * @param info The @c #battery_info_t structure to get the charger name from.
 * @return The charger name or @c NULL if the charger name is not available.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API const char *battery_info_get_charger_name(battery_info_t *info);

/**
 * @brief Determine whether the system is ready
 *
 * The @c battery_info_is_system_ready() function determines whether the system
 * is ready from a @c #battery_info_t structure. If the system is not ready,
 * then all the other system-related information in the structure is invalid.
 *
 * @param info The @c #battery_info_t structure to get the system ready status
 *             from.
 * @return @c true if the system is ready, @c false otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API bool battery_info_is_system_ready(battery_info_t *info);

/**
 * @brief Retrieve the system voltage
 *
 * The @c battery_info_get_system_voltage() function retrieves the system
 * voltage from a @c #battery_info_t structure.  The system voltage is reported
 * in millivolts (mV).
 *
 * @param info The @c #battery_info_t structure to get the system voltage from.
 * @return The system voltage or @c #BATTERY_INVALID_VALUE if the system voltage
 *         is not available.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int battery_info_get_system_voltage(battery_info_t *info);

/**
 * @brief Retrieve the system input current monitor
 *
 * The @c battery_info_get_system_input_current_monitor() function retrieves the
 * actual current drawn from the charger source from a @c #battery_info_t
 * structure. The system input current monitor is reported in milliamperes (mA).
 *
 * @param info The @c #battery_info_t structure to get the system input current
 *             monitor from.
 * @return The system input current monitor or @c #BATTERY_INVALID_VALUE if the
 *         system input current monitor is not available.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int battery_info_get_system_input_current_monitor(battery_info_t *info);

/**
 * @brief Retrieve the system charging state
 *
 * The @c battery_info_get_charger_info() function retrieves the system charging
 * state from a @c #battery_info_t structure.
 *
 * @param info The @c #battery_info_t structure to get the system charging state
 *             from.
 * @return The system charging state as one of the values of the @c
 *         #battery_charging_state_t enumeration or @c BPS_FAILURE on error.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int battery_info_get_system_charging_state(battery_info_t *info);

/**
 * @brief Retrieve the system maximum voltage
 *
 * The @c battery_info_get_system_max_voltage() function retrieves the maximum
 * voltage capacity of the device from a @c #battery_info_t structure.  The
 * system maximum voltage is reported in millivolts (mV).
 *
 * @param info The @c #battery_info_t structure to get the system maximum
 *             voltage from.
 * @return The system maximum voltage or @c #BATTERY_INVALID_VALUE if the system
 *         maximum voltage is not available.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int battery_info_get_system_max_voltage(battery_info_t *info);

/**
 * @brief Retrieve the system minimum voltage
 *
 * The @c battery_info_get_system_min_voltage() function retrieves the minimum
 * voltage required for the device to run from a @c #battery_info_t structure.
 * The system minimum voltage is reported in millivolts (mV).
 *
 * @param info The @c #battery_info_t structure to get the system minimum
 *             voltage from.
 * @return The system minimum voltage or @c #BATTERY_INVALID_VALUE if the system
 *         minimum voltage is not available.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int battery_info_get_system_min_voltage(battery_info_t *info);

/**
 * @brief Retrieve the system charge current
 *
 * The @c battery_info_get_system_charge_current() function retrieves the system
 * charge current from a @c #battery_info_t structure.  The system charge
 * current is reported in milliamperes (mA).
 *
 * @param info The @c #battery_info_t structure to get the system charge current
 *             from.
 * @return The system charge current or @c #BATTERY_INVALID_VALUE if the system
 *         charge current is not available.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int battery_info_get_system_charge_current(battery_info_t *info);

/**
 * @brief Retrieve the device name
 *
 * The @c battery_info_get_device_name() function retrieves the device name
 * from a @c #battery_info_t structure.
 *
 * @param info The @c #battery_info_t structure to get the device name from.
 * @return The device name when available or @c NULL on error.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char * battery_info_get_device_name(battery_info_t *info);

/**
 * @brief Retrieve the Battery API version
 *
 * The @c battery_info_get_version() function retrieves the version from a @c
 * #battery_info_t structure.
 *
 * @param info The @c #battery_info_t structure to retrieve the API version
 *             from.
 * @return The version or @c BPS_FAILURE on error.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int battery_info_get_version(battery_info_t *info);

__END_DECLS

#endif // include guard
