/*
 * BlackBerry Limited. Copyright (C) 2014.
 * BlackBerry Limited. All rights reserved.
 */

/**
 * @file nfc_gsma.h
 * This file provides functions for the Near Field Communication (NFC) API
 * as required by the GSMA NFC Handset Requirements (http://www.gsma.com/).
 *
 */
#ifndef NFC_GSMA_H_
#define NFC_GSMA_H_


#include <sys/types.h>
#include "nfc/nfc_types.h"

__BEGIN_DECLS

/**
 * @brief Retrieve the GSMA properties of the device
 * @details This function provides device properties that can be
 *          requested from GSMA.
 *
 * @param property_id   The id of the property to be queried.
 *        property      The location to store the value of the property retrieved.
 *                      If the device doesn't support this property, this parameter
 *                      is set to @c 0.
 *                      If the property is supported, this parameter is set to a
 *                      positive integer.
 *                      If @property_id is not defined, this function returns
 *                      @c #NFC_RESULT_INVALID_PARAMETER and leaves @c property untouched.
  *
 *
 * @return @c #NFC_RESULT_SUCCESS, or one of the following:
 *         - @c #NFC_RESULT_SERVICE_CONNECTION_ERROR: The application is not
 *           able to communicate with the NFC system.
 *         - @c #NFC_RESULT_INVALID_PARAMETER: A parameter is invalid.
 */
NFC_API nfc_result_t com_gsma_services_nfc_get_property(gsma_property_id_t property_id, int *property);

__END_DECLS

#endif /* NFC_GSMA_H_ */
