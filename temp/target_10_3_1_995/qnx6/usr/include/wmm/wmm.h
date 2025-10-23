/*
 * Research In Motion Limited. Copyright (C) 2013.
 * Research In Motion Limited. All rights reserved.
 */

#include <sys/cdefs.h>
/** @file wmm.h
 *
 * @brief Functions to determine the geomagnetic field with respect to the
 *        device's location on Earth, in terms of the Earth reference frame
 */
#ifndef WMM_H_
#define WMM_H_

__BEGIN_DECLS

#include <time.h>

/**
 * @brief Geographic location type
 *
 * This structure describes a spot on the Earth with respect to a reference
 * ellipsoid. Currently, the WGS84 ellipsoid is used. More precise ellipsoids
 * may be used in future models.
 *
 * Note that additional conversions are required to find AMSL (Above Mean Sea
 * Level) or AGL (Above Ground Level).
 */
typedef struct {
    double latitude_deg;    //!< Degrees north of equator (Geodetic) [-90,90].
    double longitude_deg;   //!< Degrees east of IERS Reference Meridian
                            //!< [-180,180].
    double altitude_meters; //!< Meters above earth reference ellipsoid.
} wmm_location_t;

/**
 * @brief Geomagnetic field
 *
 * This structure contains magnetic field information, which can be applied to
 * sensors.
 */
typedef struct {
    double declination_deg; //!< Geomagnetic declination (variation). Degrees
                            //!< that geomagnetic field points east of true
			    //!< north.
    double inclination_deg; //!< Geomagnetic inclination. Degrees that
                            //!< geomagnetic field points down from horizontal.
    double field_strength_tesla; //!< The total intensity of the geomagnetic
                                 //!< field.
    double x_tesla;         //!< The north component of the geomagnetic field.
    double y_tesla;         //!< The east component of the geomagnetic field.
    double z_tesla;         //!< The vertical component of the geomagnetic
                            //!< field.
} wmm_geomagnetic_field_t;

/** @brief Returns the geomagnetic field for a location at the specified date
 *
 *  The geomagnetic field is returned in @c field.
 *
 *  If the @c latitude_deg or @c longitude_deg values in @c loc exceed their
 *  ranges, they will be changed to fit into their respective range.
 *
 *  @param[in]  loc    The geographic location to be used in the calculation of
 *                     the magnetic field.
 *  @param[in]  date   The date to be used in the calculation of the magnetic
 *                     field.
 *  @param[out] field  The geomagnetic field for the given location and date.
 *
 *  @return  0 if successful, -1 if an error occurred, 1 if @c loc was altered
 *           to fit into the magnetic model range.
 */
int wmm_get_geomagnetic_field(const wmm_location_t * loc, const struct tm * date, wmm_geomagnetic_field_t * field);

__END_DECLS

#endif
