/*
 * $QNXLicenseC:
 * Copyright 2007, QNX Software Systems. All Rights Reserved.
 * 
 * You must obtain a written license from and pay applicable license fees to QNX 
 * Software Systems before you may reproduce, modify or distribute this software, 
 * or any work that includes all or part of this software.   Free development 
 * licenses are available for evaluation and non-commercial purposes.  For more 
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *  
 * This file may contain contributions from others.  Please review this entire 
 * file for other proprietary rights or license notices, as well as the QNX 
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/ 
 * for other information.
 * $
 */





/*
 *
 */
#define KEYGRP(_g)					(((_g) & 0x0f) << 12)
#define KEY_MASK					0x03ff
#define KEYCAP						0x0400
#define KEYMOD						0x0800
#define KEYGRP_MAX					15

#define KEYINDICATOR_MAX			7

#define VKEYMODBIT					32

#define KEY_NOSYM_FLAG				0x40
#define KEY_DEAD_FLAG				0x80

struct extended_map {
	unsigned char				from;
	unsigned char				to;
};

/*
 * Used in "mods" table for defining keyboard modifiers
 */
#define KEYMOD_UP					0x00		/* if key is up */
#define KEYMOD_DOWN					0x40		/* if key is down */
#define KEYMOD_RELEASE				0x80		/* if key was released */
#define KEYMOD_PRESS				0xc0		/* if key was pressed */
#define KEYMODBIT_MASK				0x3f

#define KEYMOD_OR					0x00		/* logical or */
#define KEYMOD_AND					0x80		/* logical and */

/*
 * Codes used in COMPOSE table
 */
#define KEYCOMPOSE_CODE				0x0000
#define KEYCOMPOSE_TABLE			0x4000
#define KEYCOMPOSE_SIZE				0x3fff
#define KEYCOMPOSE_LAST				0x8000

/*
 * Keymap types used in .kbd files
 */
#define KEYMAP_NAME					 0
#define KEYMAP_EXTENDED_MAP			 1
#define KEYMAP_GROUPS				 2
#define KEYMAP_KEYS					 3
#define KEYMAP_MODIFIERS			 4
#define KEYMAP_COMPOSE				 5
#define KEYMAP_INDICATORS			 6
#define KEYMAP_GEOMETRY				 7
#define KEYMAP_GROUPNAMES			 8
#define KEYMAP_VMODNAMES			 9
#define KEYMAP_VMODSYMS				10
#define KEYMAP_DESCRIPTIONS			11

#define KEYMAP_MAGIC				0x2044424b

struct keymap_hdr {
	unsigned short					len;
	unsigned short					type;
};

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/ph/public/sys/keytable.h $ $REV$")
#endif
