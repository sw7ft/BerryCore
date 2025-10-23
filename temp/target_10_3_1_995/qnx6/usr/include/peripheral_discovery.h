/*
 * Research In Motion Limited. Copyright (C) 2013.
 * Research In Motion Limited. All rights reserved.
 */

/**
@file peripheral_discovery.h

@since BlackBerry 10.2.0

@brief Peripheral Discovery API

This file defines the peripheral discovery API, which provides functions for
your app to receive notifications about the insertion or removal of peripheral
devices. This API also allows you to retrieve information about inserted
peripherals. This API supports USB, Bluetooth, DisplayPort, and HDMI
peripherals.

The following code sample shows how to use the peripheral discovery API to
detect the insertion and removal of peripheral devices:
@code
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/neutrino.h>
#include <sys/siginfo.h>

#include <peripheral_discovery.h>

static void print_peripheral_properties( pd_peripheral_t *peripheral ) {
  pd_peripheral_properties_t *properties;
  pd_peripheral_property_t *property;
  pd_property_type_t type;
  const char *name;
  const char *strvalue;
  int intval;

  if( (properties = pd_alloc_property_list()) == NULL ) {
    printf( "Couldn't allocate properties\n" );
    return;
  }

  if( pd_get_peripheral_properties( peripheral, properties ) == EOK ) {
    while( pd_get_next_property( properties, &property ) == EOK ) {
      type = pd_get_property_type( property );
      switch( type ) {
        case PD_STRING_TYPE:
          pd_get_property_as_string( property, &name, &strvalue );
          printf("  property: %s, value: %s\n", name, strvalue);
          break;
        case PD_INTEGER_TYPE:
          pd_get_property_as_integer( property, &name, &intval );
          printf("  property: %s, value: %d\n", name, intval);
          break;
      }
    }
  } else {
    printf( "Couldn't get properties\n" );
  }

  pd_free_property_list( &properties );
}

#define MY_PD_PULSE_CODE 1

int main( int argc, char *argv[] ) {
  bool usb_host_mode_supported;
  bool serial_is_supported, vendor_defined_is_supported;
  struct sigevent ev1, ev2;
  pd_peripheral_t *peripheral;
  int chid, coid;

  if( pd_initialize( 0 ) ) {
    printf( "Couldn't connect to peripheral discovery API\n" );
    return 1;
  }

  if( pd_is_bus_supported( PD_BUS_USB_HOST_MODE,
                             &usb_host_mode_supported ) != EOK ) {
    printf( "Error determining if usb host mode is supported\n" );
    pd_uninitialize();
    return 1;
  }
  if( pd_is_class_supported( PD_CLASS_SERIAL,
                             &serial_is_supported ) != EOK ) {
    printf( "Error determining if serial class is supported\n" );
    pd_uninitialize();
    return 1;
  }
  if( pd_is_class_supported( PD_CLASS_VENDOR_DEFINED,
                             &vendor_defined_is_supported ) != EOK ) {
    printf( "Error determining if vendor defined class is supported\n" );
    pd_uninitialize();
    return 1;
  }

  if( !usb_host_mode_supported ) {
    printf( "USB host mode is not supported.\n
             No sense trying to find peripherals\n" );
    pd_uninitialize();
    return 1;
  }
  if( !serial_is_supported && !vendor_defined_is_supported ) {
    printf( "None of the classes I'm interested in are supported.\n
             No sense trying to find peripherals\n" );
    pd_uninitialize();
    return 1;
  }

  chid = ChannelCreate( 0 );
  coid = ConnectAttach( 0, 0, chid, 0, 0 );

  // Initialize pulse sigevent.
  // You can add the class id to help identify events later, if you're
  // registering for multiple classes.
  if( serial_is_supported ) {
    SIGEV_PULSE_INIT( &ev1, coid, SIGEV_PULSE_PRIO_INHERIT, MY_PD_PULSE_CODE,
                    PD_CLASS_SERIAL );
  }
  if( vendor_defined_is_supported ) {
    SIGEV_PULSE_INIT( &ev2, coid, SIGEV_PULSE_PRIO_INHERIT, MY_PD_PULSE_CODE,
                    PD_CLASS_VENDOR_DEFINED );
  }

  if( serial_is_supported ) {
    pd_register_event( PD_CLASS_SERIAL, &ev1 );
  }
  if( vendor_defined_is_supported ) {
    pd_register_event( PD_CLASS_VENDOR_DEFINED, &ev2 );
  }

  // You need to allocate a pd_peripheral_t to get events, but you only need to
  // do it once.
  peripheral = pd_alloc_peripheral();

  // A message receive thread.
  while (1) {
    struct _pulse pulse;
    pd_event_type_t type;
    int peripheral_id;
    pd_class_t event_class;

    MsgReceive(chid, &pulse, sizeof(pulse), NULL);

    if( pulse.code == MY_PD_PULSE_CODE ) {
      // If you populated the sigevent value pointer, retrieve it now.
      event_class = (pd_class_t) pulse.value.sival_ptr;

      // Get the event that woke this thread up.
      if( pd_get_event( &type, &peripheral_id, peripheral ) == EOK ) {
        switch( type ) {
          case PD_EVENT_INSERTION:
            printf( "Peripheral Insertion. id=0x%X, class=%d\n", peripheral_id,
                    event_class );
            print_peripheral_properties( peripheral );
            break;
          case PD_EVENT_REMOVAL:
            printf( "Peripheral Removal. id=0x%X, class=%d\n", peripheral_id,
                    event_class );
            break;
        }
      }
    }
  }

  pd_free_peripheral( &peripheral );

  pd_uninitialize();

  return 0;
}
@endcode
 */

/**
 * @page property_names Property names for peripheral discovery API
 *
 * @section common Common properties
 * These properties are for every class of peripheral.
 *
 * - "class"
 *  - The class of the peripheral
 *  - @c PD_INTEGER_TYPE, will be @c pd_class_t
 *
 * - "bus"
 *  - The bus that the peripheral is attached to.
 *  - @c PD_INTEGER_TYPE, will be @c pd_bus_t
 *
 * - "peripheral_id"
 *  - The unique peripheral id
 *  - @c PD_INTEGER_TYPE
 *
 * @section bus Bus specific properties
 * There may be properties that are specific to the bus that a peripheral is
 * using. Currently, only USB host mode has such properties.
 *
 * @subsection usb_host USB Host Mode
 * The following properties are specific to USB host mode (i.e., @c
 * PD_BUS_USB_HOST_MODE)
 *
 * - "vendor_id"
 *  - USB vendor id
 *  - @c PD_INTEGER_TYPE
 *
 * - "product_id"
 *  - USB product id
 *  - @c PD_INTEGER_TYPE
 *
 * - "device_class"
 *  - USB device class
 *  - @c PD_INTEGER_TYPE
 *
 * - "device_subclass"
 *  - USB device subclass
 *  - @c PD_INTEGER_TYPE
 *
 * - "device_protocol"
 *  - USB device protocol
 *  - @c PD_INTEGER_TYPE
 *
 * @section class Class specific properties
 *
 * @subsection simple Simple peripherals
 * @c PD_CLASS_SERIAL
 *
 * @c PD_CLASS_PRINTER
 *
 * @c PD_CLASS_VENDOR_DEFINED
 *
 * - "path"
 *  - The path to the peripheral. This peripheral can be opened and read/write
 *    operations can be performed on it.
 *  - @c PD_STRING_TYPE
 */

#ifndef __PERIPHERAL_DISCOVERY_H__
#define __PERIPHERAL_DISCOVERY_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

/**
 * @brief The struct used to represent a peripheral
 */
typedef struct pd_peripheral_t pd_peripheral_t;

/**
 * @brief The struct used to represent a list of peripherals
 */
typedef struct pd_peripheral_list_t pd_peripheral_list_t;


/**
 * @brief The struct used to represent a property
 */
typedef struct pd_peripheral_property_t pd_peripheral_property_t;

/**
 * @brief The struct used to represent a list of properties
 */
typedef struct pd_peripheral_properties_t pd_peripheral_properties_t;

/**
 * @brief The different types of events
 */
typedef enum {
    /**
     * A new peripheral was inserted
     */
    PD_EVENT_INSERTION = 0,
    /**
     * A peripheral was removed
     */
    PD_EVENT_REMOVAL = 1,
    /**
     * A peripheral was updated
     */
    PD_EVENT_UPDATE = 2
} pd_event_type_t;

/**
 * @brief The different classes of peripherals
 *
 * @see pd_is_class_supported()
 */
typedef enum {
    /**
     * Serial communication
     */
    PD_CLASS_SERIAL = 0,
    /**
     * Printers
     */
    PD_CLASS_PRINTER = 1,
    /**
     * Peripherals that have vendor defined protocols
     */
    PD_CLASS_VENDOR_DEFINED = 2,
    /**
     * Peripherals using the Android Open Accessory Protocol
     */
    PD_CLASS_ANDROID_OPEN_ACCESSORY_PROTOCOL = 3,
    /**
     * Networking
     */
    PD_CLASS_NETWORKING = 4,
    /**
     * Audio
     */
    PD_CLASS_AUDIO = 5,
    /**
     * Displays
     */
    PD_CLASS_DISPLAY = 6,
    /**
     * Peripherals that are recognized but aren't classified into a Peripheral
     * Discovery class
     */
    PD_CLASS_UNKNOWN = 7,
    /**
     * Human Interface Device class
     */
    PD_CLASS_HID = 8,
    /**
     * Peripherals that offer a filesystem
     */
    PD_CLASS_FILESYSTEM = 9
} pd_class_t;

/**
 * @brief The different bus types that connect to peripherals
 *
 * @see pd_is_bus_supported()
 */
typedef enum {
    /**
     * Peripherals connected when device is in USB device mode (i.e., connected
     * to a host)
     */
    PD_BUS_USB_DEVICE_MODE = 0,
    /**
     * Peripherals connected when device is in USB host mode
     */
    PD_BUS_USB_HOST_MODE = 1,
    /**
     * Peripherals connected to Bluetooth
     */
    PD_BUS_BLUETOOTH = 2,
    /**
     * Peripherals connected to DisplayPort
     */
    PD_BUS_DISPLAYPORT = 3,
    /**
     * Peripherals connected to HDMI
     */
    PD_BUS_HDMI = 4,
} pd_bus_t;

/**
 * @brief The types of properties
 */
typedef enum {
    /**
     * String property. Represented as @c char*.
     */
    PD_STRING_TYPE = 0,
    /**
     * Integer property. Represented as @c int.
     */
    PD_INTEGER_TYPE = 1,
} pd_property_type_t;

/**
 *
 * @brief Initializes the peripheral discovery API
 *
 * This function must be called before calling any other peripheral discovery
 * functions.
 *
 * This code sample shows how to initialize the peripheral discovery API:
 * @code
 * if( pd_initialize( 0 ) != EOK ) {
 *     printf( "Couldn't connect to peripheral discovery API\n" );
 * }
 * @endcode
 *
 * @param flags     Must be set to 0 (reserved for future use)
 * @return @c EOK on success.
 */
int pd_initialize( unsigned int flags );

/**
 * @brief Retrieve the version of the peripheral discovery API
 *
 * @return The version of the peripheral discovery API.
 */
int pd_get_api_version( void );

/**
 * @brief Uninitializes the peripheral discovery API
 *
 * This function must be called when the peripheral discovery API is no longer
 * needed by the application.
 *
 * @return @c EOK on success.
 */
int pd_uninitialize( void );

/**
 * @brief Checks if a class of peripheral is supported by the device
 *
 * This function should be called before calling any functions that take a @c
 * #pd_class_t as a parameter.
 *
 * This code sample shows how to check if serial peripherals are supported:
 * @code
 * bool is_supported;
 * if( pd_is_class_supported( PD_CLASS_SERIAL, &is_supported ) == EOK ) {
 *     if( !is_supported ) {
 *         printf( "Class not supported\n" );
 *     }
 * } else {
 *     printf( "Error determining if class is supported\n" );
 * }
 * @endcode
 *
 * @param class_id      The class of peripherals to be checked.
 * @param is_supported  @c true if the class is supported, @c false if it is
 *                      not.
 *
 * @return @c EOK on success.
 */
int pd_is_class_supported( pd_class_t class_id, bool *is_supported );

/**
 * @brief Checks if a bus type is supported by the device
 *
 * You can use function to determine if devices will appear on the specified
 * bus. For example, if the peripheral to support is a USB peripheral that will
 * be connected when the device is in host mode, this function should be called
 * to check if USB host mode is actually supported.
 *
 * This code sample shows how to check if USB host mode is supported:
 * @code
 * bool is_supported;
 * if( pd_is_bus_supported( PD_BUS_USB_HOST_MODE, &is_supported ) == EOK ) {
 *     if( !is_supported ) {
 *         printf( "Bus not supported\n" );
 *     }
 * } else {
 *     printf( "Error determining if bus is supported\n" );
 * }
 * @endcode
 *
 * @param bus_id        The bus to be checked.
 * @param is_supported  @c true if the bus is supported, @c false if it is not.
 *
 * @return @c EOK on success.
 */
int pd_is_bus_supported( pd_bus_t bus_id, bool *is_supported );

/**
 * @brief Registers an event for notifications
 *
 * This event is delivered when peripherals are inserted or removed for a
 * specific class. On registration, you will get a separate notification for
 * each currently connected peripheral. After receiving a notification event,
 * call @c pd_get_event() to get the event data.
 *
 * This code sample shows how to register a pulse event for serial peripherals:
 * @code
 * #define MY_PULSE_CODE 1
 * struct sigevent ev;
 * // Initialize pulse sigevent.
 * // You can add the class id to help identify events later, if you're
 * // registering for multiple classes.
 * SIGEV_PULSE_INIT( &ev, coid, SIGEV_PULSE_PRIO_INHERIT,
 *                   MY_PULSE_CODE, PD_CLASS_SERIAL );
 *
 * pd_register_event( PD_CLASS_SERIAL, &ev );
 * @endcode
 *
 * @param class_id  The class of peripherals you want to be notified of.
 * @param event     The sigevent to use as a notification.
 *
 * @return @c EOK on success.
 */
int pd_register_event( pd_class_t class_id, struct sigevent *event );

/**
 * @brief Stops all notification events for a specific class
 *
 * This code sample shows how to stop callbacks for serial peripherals:
 * @code
 * pd_unregister_event( PD_CLASS_SERIAL );
 * @endcode
 *
 * @param class_id  The class of peripherals to stop notifications for.
 *
 * @return @c EOK on success.
 */
int pd_unregister_event( pd_class_t class_id );


/**
 * @brief Allocates memory for a peripheral
 *
 * This function must be called before calling @c pd_get_event().
 * You can pass the returned pointer to @c pd_get_event() multiple times without
 * allocating another @c #pd_peripheral_t. This memory must be freed by @c
 * pd_free_peripheral() when finished.
 *
 * @return A pointer to a peripheral. Will be NULL on error.
 */
pd_peripheral_t *pd_alloc_peripheral( void );

/**
 * @brief Gets the event from the server
 *
 * Call this function after getting a notification event.
 *
 * This code sample shows how to get an event:
 * @code
 * MsgReceive(chid, &pulse, sizeof(pulse), NULL);
 *
 * // If you populated the sigevent value pointer, retrieve it now.
 * event_class = (pd_class_t) pulse.value.sival_ptr;
 *
 * // Get the event that woke this thread up.
 * if( pd_get_event( &type, &peripheral_id, peripheral ) == EOK ) {
 *   switch( type ) {
 *     case PD_EVENT_INSERTION:
 *       printf( "Peripheral Insertion. id=%d, class=%d\n",
 *               peripheral_id, event_class );
 *       // do something with peripheral
 *       break;
 *     case PD_EVENT_REMOVAL:
 *       printf( "Peripheral Removal. id=%d, class=%d\n",
 *               peripheral_id, event_class );
 *       break;
 *   }
 * }
 * @endcode
 *
 * @param type              The type of event.
 * @param peripheral_id     The peripheral id.
 * @param peripheral        The peripheral from @c pd_alloc_peripheral() to
 *                          populate. This will not be populated on @c
 *                          #PD_EVENT_REMOVAL.
 *
 * @return @c EOK on success.
 */
int pd_get_event( pd_event_type_t *type, int *peripheral_id, pd_peripheral_t *peripheral );

/**
 * @brief Frees memory for a peripheral
 *
 * @param peripheral  The peripheral from @c pd_alloc_peripheral().
 *
 * @return @c EOK on success.
 */
int pd_free_peripheral( pd_peripheral_t **peripheral );

/**
 * @brief Allocates memory for a list of peripherals
 *
 * The list must be freed by @c pd_free_peripheral_list() when finished.
 *
 * @return A pointer to a peripheral list. Will be NULL on error.
 */
pd_peripheral_list_t *pd_alloc_peripheral_list( void );

/**
 * @brief Retrieve all the peripherals connected to the device
 *
 * @b Note: You can call this function multiple times without allocating another
 * list.
 *
 * @param class_id  The class of peripherals to return.
 * @param list      The list of peripherals from @c pd_alloc_peripheral_list().
 *
 * @return @c EOK on success.
 */
int pd_get_peripherals( pd_class_t class_id, pd_peripheral_list_t *list );

/**
 * @brief Retrieve the next peripheral from a list of peripherals
 *
 * This code sample shows how to retrieve a peripheral:
 * @code
 * pd_peripheral_list_t *peripheral_list;
 * pd_peripheral_t *peripheral;
 * int peripheral_id;
 *
 * if( (peripheral_list = pd_alloc_peripheral_list()) == NULL ) {
 *   printf( "Couldn't allocate peripheral list\n" );
 *   return;
 * }
 *
 * if( pd_get_peripherals( PD_CLASS_SERIAL, peripheral_list ) == EOK ) {
 *   while( pd_get_next_peripheral( peripheral_list, &peripheral_id,
 *                                  &peripheral ) == EOK ) {
 *     printf( "Peripheral %d:\n", peripheral_id );
 *     // do something with peripheral
 *   }
 * } else {
 *   printf( "Couldn't get peripherals\n" );
 * }
 *
 * pd_free_peripheral_list( &peripheral_list );
 * @endcode
 *
 * @param list          The list of peripherals created by @c
 *                      pd_alloc_peripheral_list() and populated by @c
 *                      pd_get_peripherals().
 * @param peripheral_id The retrieved ID of the peripheral.
 * @param peripheral    The peripheral to pass to @c
 *                      pd_get_peripheral_properties() to get more information.
 *
 * @return @c EOK on success, -1 if there are no further peripherals.
 */
int pd_get_next_peripheral( pd_peripheral_list_t *list, int *peripheral_id, pd_peripheral_t **peripheral );

/**
 * @brief Frees memory for a list of peripherals
 *
 * @param list  The list of peripherals.
 * @return @c EOK on success.
 */
int pd_free_peripheral_list( pd_peripheral_list_t **list );


/**
 * @brief Allocate memory for the list of properties of a peripheral
 *
 * The list must be freed by @c pd_free_property_list() when finished.
 *
 * @return A pointer to a property list. Will be NULL on error.
 */
pd_peripheral_properties_t *pd_alloc_property_list( void );

/**
 * @brief Retrieve the properties of a peripheral
 *
 * @b Note: You can call this function multiple times without allocating another
 * list.
 *
 * @param peripheral    The peripheral from @c pd_get_next_peripheral() or @c
 *                      pd_get_event().
 * @param properties    The list of properties from @c pd_alloc_property_list().
 *
 * @return @c EOK on success.
 */
int pd_get_peripheral_properties( pd_peripheral_t *peripheral, pd_peripheral_properties_t *properties );

/**
 * @brief Retrieve the next property from a list of properties
 *
 * @param properties    The list of properties created by @c
 *                      pd_alloc_property_list() and populated by @c
 *                      pd_get_peripheral_properties().
 * @param property      The property to pass to @c pd_get_property_as_string()
 *                      or @c pd_get_property_as_integer().
 *
 * @return @c EOK on success, -1 if there's no more properties.
 */
int pd_get_next_property( pd_peripheral_properties_t *properties, pd_peripheral_property_t **property );

/**
 * @brief Frees memory for a list of properties
 *
 * @param properties    The properties to be freed.
 *
 * @return @c EOK on success.
 */
int pd_free_property_list( pd_peripheral_properties_t **properties );

/**
 * @brief Retrieve the type of a property.
 *
 * @param property      The property from @c pd_get_next_property().
 *
 * @return The property type.
 */
pd_property_type_t pd_get_property_type( pd_peripheral_property_t *property );

/**
 * @brief Retrieve the property as a string.
 *
 * @b Note: @c name and @c value don't need to be freed, and are still valid
 * after subsequent calls to @c pd_get_next_property(). They will be freed and
 * become invalid when @c pd_free_property_list() is called.
 *
 * @param property  The property from @c pd_get_next_property().
 * @param name      The retrieved name of the property.
 * @param value     The retrieved value of the property.
 *
 * @return @c EOK on success.
 */
int pd_get_property_as_string( pd_peripheral_property_t *property, const char **name, const char **value );

/**
 * @brief Retrieve the property as an integer.
 *
 * @b Note: @c name and @c value don't need to be freed, and are still valid
 * after subsequent calls to @c pd_get_next_property(). They will be freed and
 * become invalid when @c pd_free_property_list() is called.
 *
 * @param property  The property from @c pd_get_next_property().
 * @param name      The retrieved name of the property.
 * @param value     The retrieved value of the property.
 *
 * @return @c EOK on success.
 */
int pd_get_property_as_integer( pd_peripheral_property_t *property, const char **name, int *value );

#ifdef __cplusplus
}
#endif

#endif
