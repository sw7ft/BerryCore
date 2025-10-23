#include <sys/cdefs.h>
/*
Research In Motion Limited. Copyright (C) 2012.
Research In Motion Limited. All rights reserved.
*/

/**
@file sensor.h
@brief Functions and structures to control sensors.

This file contains the interface to the sensor service.

The following are the available sensors and their corresponding file paths.
Not all sensors are available on all systems; use @c access() to determine the
existence of a sensor.

Sensor Type: Sensor Path
-    Accelerometer:              /dev/sensor/accel
-    Magnetometer:               /dev/sensor/mag
-    Gyroscope:                  /dev/sensor/gyro
-    Altimeter:                  /dev/sensor/alt
-    Temperature:                /dev/sensor/temp
-    Proximity:                  /dev/sensor/prox
-    Light:                      /dev/sensor/light
-    Gravity:                    /dev/sensor/gravity
-    Linear Acceleration:        /dev/sensor/linAccel
-    Rotation Vector:            /dev/sensor/rotVect
-    Orientation:                /dev/sensor/orientation
-    Rotation Matrix:            /dev/sensor/rotMatrix
-    Azimuth, Pitch and Roll:    /dev/sensor/apr
-    Face Detect:                /dev/sensor/faceDetect
-    Pressure:                   /dev/sensor/pressure
-    Holster:                    /dev/sensor/holster
-    Compass:                    /dev/sensor/compass

This file also defines device-specific commands (e.g.,
@c DCMD_SENSOR_SKIPDUPEVENT) that are used with calls to @c devctl() to control
the sensors.

The following example demonstrates using elements from @c sensor.h to read the
accelerometer sensor:

@code
void sensor_read(void)
{
    const char* sensor_path = "/dev/sensor/accel";
    sensor_event_t se;
    int len = 0;

    // Check if this system contains the specified sensor.
    int rc = access(sensor_path, F_OK);
    if (-1 == rc) {
        fprintf(stderr, "error(%s) accessing path(%s)\n", strerror(errno),
	        sensor_path);
        return;
    }

    // Open the sensor with read only access.
    // Leave the default for blocking read.
    int fd = open(sensor_path, O_RDONLY);
    if (-1 == fd) {
        fprintf(stderr, "error(%s) opening path(%s)\n", strerror(errno),
                sensor_path);
        return;
    }

    // Send the skip duplicate event device control.
    // The device must be moved for a new event to be sent.
    sensor_devctl_skipdupevent_u a_devctl;
    memset(&a_devctl, 0, sizeof(a_devctl));
    a_devctl.tx.enable = 1;
    rc = devctl(fd, DCMD_SENSOR_SKIPDUPEVENT, &a_devctl, sizeof(a_devctl),
                NULL);
    if (EOK != rc) {
        fprintf(stderr, "error(%s) attempting to skip duplicates\n",
                strerror(rc));
    }

    // Start an infinite loop.
    for (;;) {
        memset(&se, 0, sizeof(se));

        // Block waiting for new sensor data.
        len = read(fd, &se, sizeof(se));

        // Check for errors.
        if (-1 == len) {
            fprintf(stderr, "read error(%s)\n", strerror(errno));
            break;
        }
        if (len < sizeof(se)) {
            fprintf(stderr, "read size(%d) less than expected(%d)", len,
                    sizeof(se));
            continue;
        }
        if (SENSOR_TYPE_ACCELEROMETER != se.type) {
            fprintf(stderr, "received type(%d) different than expected(%d)",
                    se.type, SENSOR_TYPE_ACCELEROMETER);
            continue;
        }

        // Print out the payload by indexing into common structure.
        fprintf(stdout, "Acceleration->\tx:%+.2f\ty:%+.2f\tz:%+.2f\n",
                se.motion.dsp.x, se.motion.dsp.y, se.motion.dsp.z);
    }
}
@endcode
 */

#ifndef SENSOR_H_
#define SENSOR_H_

__BEGIN_DECLS

#include <stddef.h>
#include <stdint.h>

/** Sensor types */
typedef enum {
    SENSOR_TYPE_ACCELEROMETER = 0,        /**< Accelerometer sensor        */
    SENSOR_TYPE_MAGNETOMETER = 1,         /**< Magnetometer sensor         */
    SENSOR_TYPE_GYROSCOPE = 2,            /**< Gyroscope sensor            */
    SENSOR_TYPE_ALTIMETER = 3,            /**< Altimeter sensor            */
    SENSOR_TYPE_TEMPERATURE = 4,          /**< Temperature sensor          */
    SENSOR_TYPE_PROXIMITY = 5,            /**< Proximity sensor            */
    SENSOR_TYPE_LIGHT = 6,                /**< Light sensor                */
    SENSOR_TYPE_GRAVITY = 7,              /**< Gravity sensor              */
    SENSOR_TYPE_LINEAR_ACCEL = 8,         /**< Linear acceleration sensor  */
    SENSOR_TYPE_ROTATION_VECTOR = 9,      /**< Rotation vector sensor      */
    SENSOR_TYPE_ORIENTATION = 10,         /**< Orientation sensor          */
    SENSOR_TYPE_ROTATION_MATRIX = 12,     /**< Rotation sensor matrix      */
    SENSOR_TYPE_AZIMUTH_PITCH_ROLL = 14,  /**< Azimuth pitch/roll sensor   */
    SENSOR_TYPE_FACE_DETECT = 15,         /**< Face detection sensor       */
    SENSOR_TYPE_PRESSURE = 16,            /**< Pressure sensor             */
    SENSOR_TYPE_HOLSTER = 17,             /**< Holster sensor              */
    SENSOR_TYPE_COMPASS = 21,             /**< Compass sensor              */
} sensor_type_e;

/** Sensor accuracy */
typedef enum {
    SENSOR_ACCURACY_UNRELIABLE, /**< Sensor is unreliable      */
    SENSOR_ACCURACY_LOW,        /**< Sensor accuracy is low    */
    SENSOR_ACCURACY_MEDIUM,     /**< Sensor accuracy is medium */
    SENSOR_ACCURACY_HIGH,       /**< Sensor accuracy is high   */
} sensor_accuracy_e;

/** Structure to store sensor information */
typedef struct {
    float resolution;        /**< Sensor resolution     */
    float range_min;         /**< Minimum sensor range  */
    float range_max;         /**< Maximum sensor range  */
    uint32_t delay_min;      /**< Minimum sensor delay  */
    uint32_t delay_max;      /**< Maximum sensor delay  */
    uint32_t delay_default;  /**< Sensor delay          */
    float power;             /**< Sensor power          */
} sensor_info_t;

/**
 * Structure to store a sensor event, which is obtained during a read.
 */
typedef struct {
    size_t size;                /**< The size of this structure, which you can
				     use to determine the version of the
				     library you're using */
    sensor_type_e type;         /**< The sensor type, used to index into appropriate payload */
    uint32_t flags;             /**< Flags */
    sensor_accuracy_e accuracy; /**< The accuracy associated with this sample */
    uint64_t timestamp;         /**< Time stamp of data acquisition, value in nanoseconds */
    union {
        struct {
            struct {
                /** Accelerometer, Linear Acceleration, Gravity: m/s/s
                 *                                      (meters/second/second)
                 * Magnetometer:                        uT (micro Tesla)
                 * Gyroscope:                           r/s (radians/second)
                 */
                float x, y, z;      /**< data of sensor for x, y and z axis */
            } dsp, raw;             /**< dsp values are signal processed/calibrated, raw is not */
            union {
                struct {
                    float temperature; /**< The temperature of the gyroscope sensor (in degrees Celsius) */
                } gyro;
            };
        } motion;                   /**< Used by motion sensors such as Accelerometer, Magnometer, Gyroscope, Linear Acceleration and Gravity */
        float raw_data[18];         /**< Misc bucket for data payload */
        float rotation_matrix[3*3]; /**< Rotation Matrix */
        struct {
            int screen;             /**< Screen rotation in degrees: 0, 90, 180 or 270 */
            char face[64];          /**< String-based representation of device face (LEFT_UP, RIGHT_UP, TOP_UP, BOTTOM_UP, FACE_UP, or FACE_DOWN) */
        } orientation;              /**< Used by the orientation sensor */
        struct {
            float azimuth;          /**< 0 to 359 degrees */
            float pitch;            /**< -180 to 180 degrees */
            float roll;             /**< -90 to 90 degrees */
        } apr;                      /**< Used by the azimuth/pitch/roll sensor */
        struct {
            float distance;         /**< range_min to range_max, discrete steps of distance or actual value in cm */
            float normalized;       /**< 0.0 to 1.0 (close to far), normalized unit-less signal from raw sensor */
        } proximity_s;              /**< Used by the proximity sensor */
        struct {
            float pressure;         /**< Pressure in pascals (Pa) */
            float temperature;      /**< Temperature in degrees Celsius */
        } pressure_s;               /**< Used by the pressure sensor */
        struct {
            float altitude;         /**< Altitude in meters relative to mean sea level */
        } altitude_s;
        struct {
            float illuminance;      /**< Illuminance in lux */
        } light_s;                  /**< Used by the light sensor */
        struct {
            int face_detect;        /**< 1 if a face is detected, 0 otherwise */
        } face_detect_s;            /**< Used by the face-detection sensor */
        struct {
            float temperature;      /**< Temperature in degree Celsius */
        } temperature_s;            /**< Used by the temperature sensor */
        struct {
            int holstered;          /**< Holster status, 0 for not holstered, 1 for holstered */
        } holster_s;                /**< Used by the holster sensor */
        struct {
            float azimuth;          /**< Azimuth from 0 to 359 degrees from magnetic north */
            int is_face_down;       /**< 1 if the device's face is down and compass heading is flipped, 0 otherwise */
        } compass_s;                /**< Used by the compass sensor */

        /**
         * @deprecated Use the structures instead (e.g., @c proximity_s, etc.):
         */
        float proximity;            /**< @see proximity_s.distance       */
        float pressure;             /**< @see pressure_s.pressure        */
        float altitude;             /**< @see altitude_s.altitude        */
        float illuminance;          /**< @see light_s.illuminance        */
        int face_detect;            /**< @see face_detect_s.face_detect  */
        float temperature;          /**< @see temperature_s.temperature  */
        struct {
            float x,y,z;
            struct {
                float x,y,z;
            } raw;
        } axis_s;                   /**< @see motion                     */
    };
} sensor_event_t;


/*
 * The following devctl()s are common to all sensor paths
 */

/**
 * This structure is reused for all the "enable" type controls
 */
typedef struct {
    unsigned int enable; /**< Enable flag. Set to 1 for enable, 0 to disable. */
} sensor_devctl_enable_tx_t;        /**< Whether to enable the sensor */

/** 
 Structure for setting the sensor delay period (DCMD_SENSOR_DELAY)

 Example:
 @code
 sensor_devctl_delay_u delaySet;
 delaySet.tx.delay = myValue;
 result = devctl(fd, DCMD_SENSOR_DELAY, &delaySet, sizeof(delaySet),
                 NULL);
 @endcode
  where
  -   @c delaySet.tx.delay = Delay period in micro-seconds

  -   @c delaySet.rx.delay = The delay period in microseconds the system
                             granted.
  -   @c result = @c EOK - success, or see @c errno return code descriptions
                = @c EINVAL - invalid delay parameter, sensor will use the
                           closest valid delay
 */
typedef union {
    struct {
        uint32_t delay;
    } tx /**< Request */, rx /**< Response */;
} sensor_devctl_delay_u;

/** 
 Structure for setting the sensor's update period rate (DCMD_SENSOR_RATE)

 @deprecated Use DCMD_SENSOR_DELAY instead

 */
typedef union {
    struct {
        unsigned int rate;
    } tx /**< Request */, rx /**< Response */;
} sensor_devctl_rate_u;


/** 
 Structure for enabling and disabling sensor (DCMD_SENSOR_ENABLE)

 Example:
 @code
 sensor_devctl_enable_u enSensor;
 enSensor.tx.enable = 1;  //  1 = enable, 0 = disable 
 result = devctl(fd, DCMD_SENSOR_ENABLE, &enSensor, sizeof(enSensor),
                 NULL);
 @endcode
  where
  -   @c result = @c EOK - success, or see @c errno return code descriptions
 */
typedef union {
    sensor_devctl_enable_tx_t tx; /**< Enable (set to 1) / disable (set to 0) */
} sensor_devctl_enable_u;

#define SENSOR_MAX_NAME_SIZE    20 /**< Maximum size of a sensor name. */
/** 
 Structure for getting the sensor name (DCMD_SENSOR_NAME)

 Example:
 @code
 sensor_devctl_name_u sensorName;
 result = devctl(fd, DCMD_SENSOR_NAME, &sensorName, sizeof(sensorName),
                 NULL);
 printf("My name is %s", sensorName.rx.name);
 @endcode
  where
  -   @c result = @c EOK - success, or see @c errno return code descriptions
 */
typedef union {
    struct {
        char name[SENSOR_MAX_NAME_SIZE];
    } rx; /**< Response */
} sensor_devctl_name_u;


/** 
 Structure for requesting sensor calibration (DCMD_SENSOR_CALIBRATE)

 Example:
 @code
 sensor_devctl_calibrate_u sensorCal;
 sensorCal.tx.enable = 1;  // 1 = start calibration, 0 = stop
                           // calibration
 result = devctl(fd, DCMD_SENSOR_CALIBRATE, &sensorCal,
                 sizeof(sensorCal), NULL);
 @endcode
  where
  -   @c result = @c EOK - success, or see @c errno return code descriptions
 */
typedef union {
    sensor_devctl_enable_tx_t tx; /**< Calibrate (set to 1) / stop (set to 0) */
} sensor_devctl_calibrate_u;


/** 
 Structure for enabling or disabling sensor event queuing (DCMD_SENSOR_QUEUE)

 Sensor services queues only one event by default. If a new event arrives
 before the client reads the last event, the previous event is overwritten.
 When event queuing is enabled, up to X events will be queued by the system.
 Client can set their read buffers up to @c X @c * @c sizeof(sensor_event_t)
 to be able to read all events queued.

 Example:
 @code
 sensor_devctl_queue_u sensorQue;
 sensorQue.tx.enable = 1;  // 1 = enable, 0 = disable
 result = devctl(fd, DCMD_SENSOR_QUEUE, &sensorQue, sizeof(sensorQue),
                 NULL);
 @endcode
  where
  -   @c sensorQue.rx.size - number of events that will be queued
  -   @c result = @c EOK - success, or see @c errno return code descriptions
 */
typedef union {
    sensor_devctl_enable_tx_t tx; /**< Enable (set to 1) / disable (set to 0) */
    struct {
        unsigned int size; /**< The number of events to be queued */
    } rx; /**< Response */
} sensor_devctl_queue_u;


/** 
 Structure for getting sensor information (DCMD_SENSOR_INFO)

 Example:
 @code
 sensor_devctl_info_u sensorInfo;
 result = devctl(fd, DCMD_SENSOR_INFO, &sensorInfo, sizeof(sensorInfo),
                 NULL);
 @endcode
  where
  -   @c result = @c EOK - success, or see @c errno return code descriptions
  -   @c sensorInfo.rx.info = sensor info, see @c sensor_info_t
 */
typedef union {
    struct {
        sensor_info_t info; /**< Sensor information */
    } rx; /**< Response **/
} sensor_devctl_info_u;


/** 
 Structure for enabling or disabling sensor event duplicate event filtering 
 (DCMD_SENSOR_SKIPDUPEVENT)

 When enabled, any exactly duplicate events from the sensor are filtered. Some
 sensor hardware supports reduced reporting, which filters events that are the
 same within a certain threshold.

 Example:
 @code
 sensor_devctl_skipdupevent_u sensorSkipDup;
 sensorSkipDup.tx.enable = 1;  // 1 = enable filtering, 0 = disable
 result = devctl(fd, DCMD_SENSOR_SKIPDUPEVENT, &sensorSkipDup,
                 sizeof(sensorSkipDup), NULL);
 @endcode
  where
  -   @c result = @c EOK - success, or see @c errno return code descriptions
 */
typedef union {
    sensor_devctl_enable_tx_t tx; /**< Enable filtering (set to 1) / disable
				       filtering (set to 0) */
} sensor_devctl_skipdupevent_u;


/** 
 Structure for enabling and disabling background mode (sensor works when system 
 is in user standby mode (DCMD_SENSOR_BKGRND))

 By default, when the system is put in standby, all sensors are turned off, and
 no events are sent to clients.

 If you enable background mode, the sensor will stay active when the system is
 in standby. This will reduce battery life.

 Example:
 @code
 sensor_devctl_bkgrnd_u sensorBkgrnd;
 sensorBkgrnd.tx.enable = 1;  // 1 = enable, 0 = disable
 result = devctl(fd, DCMD_SENSOR_BKGRND, &sensorBkgrnd,
                 sizeof(sensorBkgrnd), NULL);
 @endcode
  where
  -   @c result = @c EOK - success, or see @c errno return code descriptions
 */
typedef union {
    sensor_devctl_enable_tx_t tx; /**< Enable background mode (set to 1) /
				       disable (set to 0) */
} sensor_devctl_bkgrnd_u;

/** 
 Structure for unblocking a blocked read (DCMD_SENSOR_UNBLOCK)

 Example:
 @code
 sensor_devctl_unblock_u sensorUnblock;
 sensorUnblock.tx.option = 0;         // unblock client read with EINTR,
                                      // zero bytes returned
 sensorUnblock.tx.option = reserved;  // for future use
 result = devctl(fd, DCMD_SENSOR_UNBLOCK, &sensorUnblock,
                 sizeof(sensorUnblock), NULL);
 @endcode
  where
  -   @c result = @c EOK - success, or see @c errno return code descriptions
 */
typedef union {
    struct {
        int option; /**< Unblock read (set to 0) */
    } tx; /**< Request */
} sensor_devctl_unblock_u;

/**
 Structure for enabling or disabling sensor event batching
 (DCMD_SENSOR_BATCHING). 

 When enabled and supported by the hardware, sensors will report samples in
 hardware-specific batch sizes to conserve power.

 Example:
 @code
 sensor_devctl_batching_u sensorBatching;
 sensorBatching.tx.enable = 1;  // 1 = enable, 0 = disable
 result = devctl(fd, DCMD_SENSOR_BATCHING, &sensorBatching,
                 sizeof(sensorBatching), NULL);
 @endcode
  where
  -   @c result = @c EOK - success, or see @c errno return code descriptions
 */
typedef union {
    sensor_devctl_enable_tx_t tx; /**< Enable/disable event batching */
} sensor_devctl_batching_u;

/** Device command to enable a sensor. */
#define DCMD_SENSOR_ENABLE           __DIOT(_DCMD_INPUT,  1, sensor_devctl_enable_u ) 

/** Device command to set a sensor's delay period. */
#define DCMD_SENSOR_DELAY            __DIOTF(_DCMD_INPUT, 2, sensor_devctl_delay_u ) 

/** Device command to set a sensor's update period rate (deprecated - use 
 *  DCMD_SENSOR_DELAY instead). */
#define DCMD_SENSOR_RATE             __DIOTF(_DCMD_INPUT, 2, sensor_devctl_rate_u ) 

/** Device command to get sensor information. */
#define DCMD_SENSOR_INFO             __DIOF(_DCMD_INPUT,  3, sensor_devctl_info_u ) 

/** Device command to enable/disable duplicate event filtering. */
#define DCMD_SENSOR_SKIPDUPEVENT     __DIOT(_DCMD_INPUT,  4, sensor_devctl_skipdupevent_u ) 

/** Device command to enable/disable background mode. */
#define DCMD_SENSOR_BKGRND           __DIOT(_DCMD_INPUT,  5, sensor_devctl_bkgrnd_u ) 

/** Device command to enable/disable sensor event queuing. */
#define DCMD_SENSOR_QUEUE            __DIOTF(_DCMD_INPUT, 6, sensor_devctl_queue_u ) 

/** Device command to calibrate a sensor. */
#define DCMD_SENSOR_CALIBRATE        __DIOT(_DCMD_INPUT,  7, sensor_devctl_calibrate_u ) 

/** Device command to get a sensor's name. */
#define DCMD_SENSOR_NAME             __DIOF(_DCMD_INPUT,  9, sensor_devctl_name_u ) 

/** Device command to unblock a blocked read of a sensor. */
#define DCMD_SENSOR_UNBLOCK          __DIOT(_DCMD_INPUT, 10, sensor_devctl_unblock_u ) 

/** Device command to enable/disable sensor batching. */
#define DCMD_SENSOR_BATCHING         __DIOT(_DCMD_INPUT, 11, sensor_devctl_batching_u )

__END_DECLS

#endif
