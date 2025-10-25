/**
 * @file bbmsp_messaging.h
 *
 * @brief Provides a function for sending invitations to download your
 * application.
 *
 * @copyright Copyright (C) Research In Motion Limited 2012. All rights
 * reserved.
 *
 */

#ifndef BBMSP_MESSAGING_H_
#define BBMSP_MESSAGING_H_

#include <sys/platform.h>

#include "bbmsp.h"
#include "bbmsp_contactlist.h"
#include "bbmsp_util.h"

__BEGIN_DECLS

/**
 * @brief Send an invitation to a user's BBM contacts to download your app.
 *
 * @details The contact picker displays for the user to select the contacts to
 * invite. Only those contacts who have not yet installed the app will be
 * displayed in the contact picker. The BBM Social Platform allows up to 10
 * download invitations per minute.
 *
 * @return @c BBMSP_SUCCESS if successful, @c BBMSP_FAILURE otherwise.
 * @see BBMSP_SUCCESS, BBMSP_FAILURE
 * @since BlackBerry 10.0.0
 */
BBMSP_API int bbmsp_send_download_invitation(void);

__END_DECLS

#endif /* BBMSP_MESSAGING_H_ */
