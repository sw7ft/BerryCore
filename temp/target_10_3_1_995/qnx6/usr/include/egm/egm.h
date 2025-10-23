/*
 * Blackberry Limited. Copyright (C) 2013.
 * Blackberry Limited. All rights reserved.
 */

#include <sys/cdefs.h>
/** @file egm.h
 *
 * @brief Functions to determine gravitationally derived quantities with
 *        respect to the device's location on Earth, in terms of the Earth
 *        reference frame. Values are in a tide-free system.
 */
#ifndef EGM_H_
#define EGM_H_

__BEGIN_DECLS

/**
 * @brief Geographic location type.
 *
 * This structure describes a spot on the Earth with respect to a reference
 * ellipsoid. Currently, the WGS84 ellipsoid is used. More precise ellipsoids
 * may be used in future models.
 */
typedef struct {
    double latitude_deg;    //!< Degrees north of equator (Geodetic) [-90,90].
    double longitude_deg;   //!< Degrees east of IERS Reference Meridian
                             //!< [-180,180].
    double altitude_meters; //!< Meters above earth reference ellipsoid.
} egm_location_t;

/**
 * @brief Gravitational field.
 *
 * This structure contains gravitational field information.
 */
typedef struct {
    double magnitude; //!< Gravitational field magnitude. [m/s^2]
} egm_gravity_field_t;

/** @brief Returns the earth's gravitational field for a location.
 *
 *  The gravitational field is returned in @c field. Currently the normal
 *  gravity above a uniform earth-like rotating ellipsoid is returned.
 *  More detailed models may be used in the future (EGM96, EGM2008 ...).
 *
 *  If the @c latitude_deg or @c longitude_deg values in @c loc exceed their
 *  ranges, they will be changed to fit into their respective range.
 *
 *  @param[in]  loc    The geographic location to be used in the calculation of
 *                     the gravitational field.
 *  @param[out] field  The geomagnetic field for the given location.
 *
 *  @return  0 if successful, -1 if an error occurred, 1 if @c loc was altered
 *           to fit into the model range.
 */
int egm_get_gravity_field(const egm_location_t * loc, egm_gravity_field_t * field);

/** @brief Returns the earth geoid undulation for a location.
 *
 *  The earth undulation is returned in @c undulation. The undulation
 *  represents the distance the geoid surface (MSL) is above the earth
 *  reference ellipsoid surface. Given a height above the earth reference
 *  ellipsoid, subtract the undulation to obtain the height above the geoid
 *  (AMSL). Currently undulation is from the EGM96 model. More detailed models
 *  may be used in the future. (EGM2008 ...).
 *
 *  If the @c latitude_deg or @c longitude_deg values in @c loc exceed their
 *  ranges, they will be changed to fit into their respective range.
 *
 *  @param[in]  loc         The geographic location to be used in the
 *                          calculation of the undulation.
 *  @param[out] undulation  The undulation for the given location in meters.
 *
 *  If the system is out of memory, the thread may get a SIGBUS with code
 *  BUS_ADRERR.
 *
 *  @return  0 if successful, -1 if an error occurred, 1 if @c loc was altered
 *           to fit into the model range.
 */
int egm_get_geoid_undulation(const egm_location_t * loc, double * undulation);

/** @brief Cleanup egm library memory.
 *
 *  To improve performance, the egm library caches some information between
 *  calls. Call this function to cleanup internal egm library memory once
 *  finished using the library.
 */
void egm_fini();

__END_DECLS

#endif
