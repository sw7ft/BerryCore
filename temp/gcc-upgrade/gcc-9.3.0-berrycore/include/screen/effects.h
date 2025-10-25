/*
 * $QNXLicenseC:
 * Copyright 2010, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable
 * license fees to QNX Software Systems before you may reproduce,
 * modify or distribute this software, or any work that includes
 * all or part of this software.   Free development licenses are
 * available for evaluation and non-commercial purposes.  For more
 * information visit http://licensing.qnx.com or email
 * licensing@qnx.com.
 *
 * This file may contain contributions from others.  Please review
 * this entire file for other proprietary rights or license notices,
 * as well as the QNX Development Suite License Guide at
 * http://licensing.qnx.com/license-guide/ for other information.
 * $
 */
/**
*   @file effects.h
*   @brief Enumerations related to effects for the UI Framework Library
*
*   This file effects enumerations that are supported by the UI Framework.
*/

#ifndef _SCREEN_EFFECTS_H_
#define _SCREEN_EFFECTS_H_

/**
*   @addtogroup screen_effects
*   @{
*/
/** @brief This enumeration specifies the types of effects which can be used.
 *  @anonenum Screen_Effect_Types Screen effect types
 */
enum {
	SCREEN_NO_EFFECT                = 0,    /**< No Effect */
	SCREEN_FLIP_EFFECT              = 1,    /**< Flip Effect */
	SCREEN_ROTATE_EFFECT            = 2,    /**< Rotate Effect */
	SCREEN_PAGE_CURL_EFFECT         = 3,    /**< Curl Effect */
	SCREEN_REVEAL_EFFECT            = 4,    /**< Reveal Effect */
};

/** @brief This enumeration specifies the property types of effects which can be used.
 *  @anonenum Screen_Effect_Property_Types Screen effect property types
 */
enum {
	SCREEN_FLIP_AXIS                = 1,    /**< Flip on axis */
	SCREEN_FLIP_DIRECTION           = 2,    /**< Flip on direction */

	SCREEN_ROTATE_DIRECTION         = 10,    /**< Rotate on direction */
	SCREEN_ROTATE_VIEWPORT_POSITION = 11,    /**< Position of the viewport after rotation */
	SCREEN_ROTATE_VIEWPORT_SIZE     = 12,    /**< Size of the viewport after rotation */

	SCREEN_PAGE_CURL_ORIGIN         = 20,    /**< Page Curl Origin */
	SCREEN_PAGE_CURL_POSITION       = 21,    /**< Page Curl Position */

	SCREEN_REVEAL_ORIGIN            = 30,    /**< Reveal Origin */
	SCREEN_REVEAL_POSITION          = 31,    /**< Reveal Position */
};

/** @brief This enumeration specifies the axis types of effects which can be used.
 *  @anonenum Screen_Effect_Axis_Types Screen effect axis types
 */
enum {
	SCREEN_FLIP_AXIS_HORIZONTAL     = 0,    /**< Flip on horizontal axis */
	SCREEN_FLIP_AXIS_VERTICAL       = 1,    /**< Flip on vertical axis*/
};

/** @brief This enumeration specifies the direction types of effects which can be used.
 *  @anonenum Screen_Effect_Direction_Types Screen effect direction types
 */
enum {
	SCREEN_FLIP_DIRECTION_CW        = 0, /**< Flip in clockwise direction */
	SCREEN_FLIP_DIRECTION_CCW       = 1, /**< Flip in counter-clockwise direction */
};

/** @brief This enumeration specifies the rotation types of effects which can be used.
 *  @anonenum Screen_Effect_Rotation_Types Screen effect rotation types
 */
enum {
	SCREEN_ROTATE_DIRECTION_CW      = 0, /**< Rotate in clockwise direction */
	SCREEN_ROTATE_DIRECTION_CCW     = 1, /**< Rotate in clockwise direction */
};

/** @brief This enumeration specifies the page curl types of effects which can be used.
 *  @anonenum Screen_Effect_Pagecurl_Types Screen effect page curl types
 */
enum {
	SCREEN_PAGE_CURL_BOTTOM_RIGHT   = 0, /**< Page curl from bottom right */
	SCREEN_PAGE_CURL_BOTTOM_LEFT    = 1, /**< Page curl from bottom left */
	SCREEN_PAGE_CURL_UPPER_RIGHT    = 2, /**< Page curl from upper right */
	SCREEN_PAGE_CURL_UPPER_LEFT     = 3, /**< Page curl from upper left */
};

/** @brief This enumeration specifies the reveal types of effects which can be used.
 *  @anonenum Screen_Effect_Reveal_Types Screen effect reveal types
 */
enum {
	SCREEN_REVEAL_TOP               = 0, /**< Reveal from top */
	SCREEN_REVEAL_RIGHT             = 1, /**< Reveal from right */
	SCREEN_REVEAL_BOTTOM            = 2, /**< Reveal from bottom */
	SCREEN_REVEAL_LEFT              = 3, /**< Reveal from left */
};
/** @} */   /* end of addtogroup screen_effects */

#endif /* _SCREEN_EFFECTS_H_ */

__SRCVERSION("$URL: http://community.qnx.com/svn/repos/vivante-driver/QNX/source/trunk/lib/iow/public/winmgr/iow.h $ $Rev: 375 $")
