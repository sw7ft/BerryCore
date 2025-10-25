/*!
 * @copyright
 * Copyright BlackBerry Limited, 2012-2014
 * BlackBerry Limited. All rights reserved.
 */

/**
 * @file nfc_bps.h
 *
 * The functions available in this file enable applications to connect
 * with Near Field Communication (NFC) systems using the BlackBerry
 * Platform Services (BPS) event framework.
 *
 * The functions allow you to determine the status of the NFC. When
 * you connect to an NFC system using BPS, BPS events are used to
 * deliver events to your application.
 *
 * Note: When you want your application to connect to the NFC system
 * and receive NFC events using BPS, @b do @b not @b use these
 * functions from the nfc.h file:
 * - @c nfc_connect()
 * - @c nfc_disconnect()
 * - @c nfc_get_fd()
 * - @c nfc_read_event()
 * - @c nfc_free_event()
 */

#ifndef _NFC_BPS_H
#define _NFC_BPS_H

#include <stdbool.h>
#include <bps/event.h>
#include "nfc/nfc.h"

__BEGIN_DECLS

/**
 * @brief Start receiving NFC events
 * @details This function requests the NFC service to start delivering NFC
 *          events as they occur to the application.
 *
 * @return @c #BPS_SUCCESS upon success, otherwise @c #BPS_FAILURE with @c errno
 *         set to one of the following values:
 *         - @c #EIO: An IO error has occurred.
 *         - @c #EALREADY: This function has already been called.
 *         - @c #ECONNREFUSED: attempt at connecting to an NFC system has failed.
 */
NFC_API int nfc_request_events();

/**
 * @brief Stop receiving NFC events
 * @details This function indicates that the application wants to stop
 *          receiving NFC events.
 *
 * @return @c #BPS_SUCCESS upon success, otherwise @c #BPS_FAILURE with @c errno
 *         set to the following value:
 *         - @c #EIO: An IO error has occurred.
 */
NFC_API int nfc_stop_events();

/**
 * @brief Retrieve the unique domain ID for the NFC service
 * @details This function retrieves the unique domain ID for the NFC service.
 *          Use this function in your application to determine whether an event
 *          that you retrieve is an NFC event and then respond accordingly.
 *
 *          You use the @c bps_get_event() function from the BPS library to
 *          retrieve the event.
 *
 * @return The domain ID for the NFC service upon success, @c #BPS_FAILURE
 *         otherwise.
 */
NFC_API int nfc_get_domain();

/*****************************************************************************
 *                            Target retrieval                               *
 *****************************************************************************/

/**
 * @brief Retrieve the NFC event associated with the BPS event
 * @details This function retrieves the underlying NFC event that is delivered
 *          as part of the BPS event.
 *
 * @param bps_event A pointer to the BPS event to get the NFC event from.
 * @param nfc_event A pointer to the NFC event.
 *
 * @return @c #BPS_SUCCESS upon success, @c #BPS_FAILURE otherwise, with @c
 *         errno set to @c #EINVAL for one of the following errors:
 *         - NFC domain cannot be obtained.
 *         - Event passed into the NFC is not valid.
 *         - Event passed into the NFC is not part of the NFC domain.
 *         - Payload cannot be obtained from the BPS event.
 *         - BPS event does not carry a payload.
 */
NFC_API int nfc_get_nfc_event(bps_event_t *bps_event, nfc_event_t **nfc_event);

__END_DECLS

#endif // include guard
