/*
 * $QNXLicenseC:
 * Copyright 2007, QNX Software Systems.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"). You
 * may not reproduce, modify or distribute this software except in
 * compliance with the License. You may obtain a copy of the License
 * at: http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTIES OF ANY KIND, either express or implied.
 *
 * This file may contain contributions from others, either as
 * contributors under the License or as licensors under other terms.
 * Please review this entire file for other proprietary rights or license
 * notices, as well as the QNX Development Suite License Guide at
 * http://licensing.qnx.com/license-guide/ for other information.
 * $
 */


/*
 *	asound.h
 *
 *
 *	2000 05 04	R. Krten		created based on specifications implied by source code
 *
 *	THIS FILE IS COMPLETELY UNENCUMBERED BY THE GPL, AS IT WAS DEVELOPED
 *	IN A "CLEAN-ROOM" FASHION WITH NO KNOWLEDGE OF THE CONTENTS OF THE GPL-VERSION
 *	OF THE "asound.h" FILE, APART FROM ACCESS TO WWW.ALSA-PROJECT.ORG WHICH DOES
 *	NOT CONTAIN A GPL.  -- Robert Krten, PARSE Software Devices, May 5, 2000.
 *
 *	All structures in this file are 64-bit aligned.
*/

#ifndef __ASOUND_H
#define __ASOUND_H

#include <sys/asound_common.h>

typedef struct snd_pcm_info snd_pcm_info_t;
typedef struct snd_pcm_format snd_pcm_format_t;
typedef struct snd_rawmidi_info snd_rawmidi_info_t;
typedef struct snd_rawmidi_params_s snd_rawmidi_params_t;
typedef struct snd_rawmidi_status_s snd_rawmidi_status_t;

#define		SND_PCM_START_DATA				PCM_START_DATA
#define		SND_PCM_START_FULL				PCM_START_FULL
#define		SND_PCM_START_GO				PCM_START_GO
#define		SND_PCM_START_COUNT				PCM_START_COUNT

/** channel mapping API version number */
#define SND_CHMAP_API_VERSION	((1 << 16) | (0 << 8) | 1)

/** channel map list type */
enum snd_pcm_chmap_type {
	SND_CHMAP_TYPE_NONE = 0,/** unspecified channel position */
	SND_CHMAP_TYPE_FIXED,	/** fixed channel position */
	SND_CHMAP_TYPE_VAR,	/** freely swappable channel position */
	SND_CHMAP_TYPE_PAIRED,	/** pair-wise swappable channel position */
	SND_CHMAP_TYPE_LAST = SND_CHMAP_TYPE_PAIRED, /** last entry */
};

/** channel positions */
enum snd_pcm_chmap_position {
	SND_CHMAP_UNKNOWN = 0,	/** unspecified */
	SND_CHMAP_NA,		/** N/A, silent */
	SND_CHMAP_MONO,		/** mono stream */
	SND_CHMAP_FL,		/** front left */
	SND_CHMAP_FR,		/** front right */
	SND_CHMAP_RL,		/** rear left */
	SND_CHMAP_RR,		/** rear right */
	SND_CHMAP_FC,		/** front center */
	SND_CHMAP_LFE,		/** LFE */
	SND_CHMAP_SL,		/** side left */
	SND_CHMAP_SR,		/** side right */
	SND_CHMAP_RC,		/** rear center */
	SND_CHMAP_FLC,		/** front left center */
	SND_CHMAP_FRC,		/** front right center */
	SND_CHMAP_RLC,		/** rear left center */
	SND_CHMAP_RRC,		/** rear right center */
	SND_CHMAP_FLW,		/** front left wide */
	SND_CHMAP_FRW,		/** front right wide */
	SND_CHMAP_FLH,		/** front left high */
	SND_CHMAP_FCH,		/** front center high */
	SND_CHMAP_FRH,		/** front right high */
	SND_CHMAP_TC,		/** top center */
	SND_CHMAP_TFL,		/** top front left */
	SND_CHMAP_TFR,		/** top front right */
	SND_CHMAP_TFC,		/** top front center */
	SND_CHMAP_TRL,		/** top rear left */
	SND_CHMAP_TRR,		/** top rear right */
	SND_CHMAP_TRC,		/** top rear center */
	SND_CHMAP_TFLC,		/* top front left center */
	SND_CHMAP_TFRC,		/* top front right center */
	SND_CHMAP_TSL,		/* top side left */
	SND_CHMAP_TSR,		/* top side right */
	SND_CHMAP_LLFE,		/* left LFE */
	SND_CHMAP_RLFE,		/* right LFE */
	SND_CHMAP_BC,		/* bottom center */
	SND_CHMAP_BLC,		/* bottom left center */
	SND_CHMAP_BRC,		/* bottom right center */
	SND_CHMAP_LAST = SND_CHMAP_BRC,

	// BlackBerry extension positions
	SND_CHMAP_BB_SLU = 1000,    /* side left upper */
	SND_CHMAP_BB_SLL,           /* side left lower */
	SND_CHMAP_BB_SRU,           /* side right upper */
	SND_CHMAP_BB_SRL,           /* side right lower */
	SND_CHMAP_BB_BFC,           /* bottom front center */
	SND_CHMAP_BB_FCB=SND_CHMAP_BB_BFC,           /* deprecated */
	SND_CHMAP_BB_RCB,           /* rear center bottom */
	SND_CHMAP_BB_RCT,           /* rear center top */
	SND_CHMAP_BB_RRUC,          /* rear right upper center */
	SND_CHMAP_BB_RLUC,          /* rear left upper center */
	SND_CHMAP_BB_LAST = SND_CHMAP_BB_RLUC
};

/** bitmask for channel position */
#define SND_CHMAP_POSITION_MASK		0xffff

/** bit flag indicating the channel is phase inverted */
#define SND_CHMAP_PHASE_INVERSE		(0x01 << 16)
/** bit flag indicating the non-standard channel value */
#define SND_CHMAP_DRIVER_SPEC		(0x02 << 16)

/** the channel map header */
typedef struct snd_pcm_chmap {
	unsigned int channels;	/** number of channels */
	unsigned int pos[0];	/** channel position array */
} snd_pcm_chmap_t;

/** the header of array items returned from snd_pcm_query_chmaps() */
typedef struct snd_pcm_chmap_query {
	enum snd_pcm_chmap_type type;	/** channel map type */
	snd_pcm_chmap_t map;		/** available channel map */
} snd_pcm_chmap_query_t;



#endif


__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/asound/public/include/sys/asound.h $ $Rev: 742554 $" )
