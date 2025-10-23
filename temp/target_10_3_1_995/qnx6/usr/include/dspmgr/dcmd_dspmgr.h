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





/**
 * \file dcmd_dspmgr.h
 *
 * Non-portable low-level devctl definitions
 *

 */
#ifndef __DCMD_DSPMGR_H_INCLUDED
#define __DCMD_DSPMGR_H_INCLUDED

#ifndef _DEVCTL_H_INCLUDED
 #include <devctl.h>
#endif

#ifndef __SIGINFO_H_INCLUDED
 #include <sys/siginfo.h>
#endif

/**
 * Defines devctl code range.
 */
#define _DCMD_DSPMGR _DCMD_MISC

#include <_pack1.h>

/**
 * Runnel argument
 */
typedef struct dspmgr_tunnel_t
{
	_Uint8t		tunnel;			/**< Tunnel ID */
	_Uint8t		zero[3];		/**< Padding */

	_Uint32t	perf_pad[4];	/**< OPT: performance padding to > 16 bytes */
} dspmgr_tunnel_t;

/**
 * DSP general query
 */
typedef struct dspmgr_query_t
{
	_Uint8t		tunnels;	/**< Number of tunnels */
	_Uint8t		zero[3];	/**< Padding */
} dspmgr_query_t;

/**
 * DSP module
 *
 * Logical grouping of tunnels by DSP side functionality.
 */
enum MODULE_TYPES
{
	MODULE_UNKNOWN,				/**< Unknown module */
	MODULE_AUDIO,				/**< Audio module */
	MODULE_MP3_ENC,				/**< MP3 encoder */
	MODULE_MP3_DEC,				/**< MP3 decoder */
	MODULE_VOICE_REC,			/**< Voice recognition */
	MODULE_ATAPI,               /**< Virtual ATAPI module */
	MODULE_USER_DEFD = 255,		/**< User defined module */
};

/**
 * Tunnel data type
 *
 * Describes the type of data that will be transferred over a tunnel.
 * Depending on the type of data, supplementaion type specific data may be
 * included in the dspmgr_tunnelcap_t structure.
 */
enum DATA_TYPES
{
	DATA_UNKNOWN,				/**< Unknown data type */
	DATA_PCM,					/**< PCM encoded audio */
	DATA_MP3,					/**< MP3 encoded audio */
	DATA_VOICE_REC,				/**< Voice recognition */
	DATA_ATAPI_CNTL,            /**< ATAPI control     */
	DATA_ATAPI_DIN,             /**< ATAPI data in     */
	DATA_ATAPI_DOUT,            /**< ATAPI data out    */
	DATA_ATAPI_STATUS,          /**< ATAPI statas      */
	DATA_USER_DEFD = 255,		/**< User defined data */
};

/**
 * Tunnel direction
 *
 * Direction of data flow over a tunnel
 */
enum DIRECTION_TYPES
{
	DIR_UNKNOWN,
	DIR_GPP_TO_DSP,
	DIR_DSP_TO_GPP,
};

#define MODE_ASYNC	(1<<1)		/**< Asynchronous data transfer */
#define MODE_ISOCH	(1<<0)		/**< Isochronous data transfer */

/**
 * DSP tunnel capabilities
 *
 * /note if this structure's definition changes you must modify config.c to match 
 */
typedef struct dspmgr_tunnelcap_t
{
	_Uint8t		tunnel;			/**< Tunnel to query */
	_Uint8t		module;			/**< Module this channel is connected (MODULE_TYPES enum) */
	_Uint8t		type;			/**< Type of data (DATA_TYPES enum) */
	_Uint8t		direction;		/**< Tunnel direction (0 - gpp to dsp, 1 - dsp to gpp) */
	_Uint32t	segsize_max;	/**< Maximum size of each DSP side buffer (bytes) */
	_Uint32t	segsize_min;	/**< Minimum size of each DSP side buffer (bytes) */
	_Uint8t		modes;			/**< Operationg modes bitmap (MODE_*) */
	_Uint8t		buffer_depth;	/**< DSP buffering depth */
	_Uint8t		Reserved[2];

	/** Data type specific capabilities */
	union	{
		/** PCM data capabilities */
		struct	{
			_Uint8t		voices;		/**< Number of voices */
			_Uint32t	format;		/**< Data format <sys/asound.h> SND_PCM_SFMT_* */
		} pcm;

		/** MP3 data capabilities */
		struct	{
			_Uint32t	format;		/**< Data format */
		} mp3;
	} info;
} dspmgr_tunnelcap_t;

/** Name length for shared memory buffer */
#define DSPMGR_CONFIG_SHM_NAME_LEN	20

/**
 * Configure tunnel
 * 
 * \todo add a priority field for the tunnel's thread
 */
typedef struct dspmgr_config_t
{
	_Uint8t			tunnel;			/**< Tunnel to acquire */
	_Uint8t			mode;			/**< Requested operating mode (MODE_*) */
	_Uint16t 		initial_frags;	/**< initially full fragments (**Isoch Only**) */
	_Uint16t		fragnum;		/**< Total number of buffer fragments */
	_Uint16t		segsperfrag;	/**< Number of dsp segments that compose a fragment */
	_Uint32t		segsize;		/**< Size of each dsp buffer segnment */

	struct sigevent	event;			/**< Event notification (**Isoch Only**) */

	/** Name of shared memory buffer */
	char			shm_name[DSPMGR_CONFIG_SHM_NAME_LEN +1];
} dspmgr_config_t;


/**
 * Queries the dspmgr for general information
 *
 * \b Args: Pointer to a dspmgr_query_t structure
 *
 * \b From: tunnels
 */
#define DCMD_DSPMGR_QUERY	__DIOF(_DCMD_DSPMGR, 1, dspmgr_query_t)

/**
 * Queries the dspmgr for tunnel information
 *
 * \b Args: Pointer to a dspmgr_tunnelcap_t structure
 *
 * \b To:   tunnel
 *
 * \b From: info
 *
 * \note Clients usually loop through each tunnel number until they get an
 *       EINVAL error back.
 */
#define DCMD_DSPMGR_TUNNELCAP	__DIOTF(_DCMD_DSPMGR, 2, dspmgr_tunnelcap_t)

/**
 * Attempts to acquire exclusive access to a tunnel
 *
 * \b Args: Pointer to a dspmgr_tunnel_t structure
 *
 * \b To:   tunnel
 */
#define DCMD_DSPMGR_ACQUIRE	__DIOT(_DCMD_DSPMGR, 3, dspmgr_tunnel_t)

/**
 * Releases exclusive access to an acquired tunnel
 *
 * \b Args: Pointer to a dspmgr_tunnel_t structure
 *
 * \b To:   tunnel
 *
 * \note Releasing a tunnel immediately deconfigures the tunnel
 */
#define DCMD_DSPMGR_RELEASE	__DIOT(_DCMD_DSPMGR, 4, dspmgr_tunnel_t)

/**
 * Configures an acquired tunnel for use
 *
 * \b Args: Pointer to a dspmgr_config_t structure
 * 
 * \b To:   tunnel, mode, fragnum, segsize, segperfrag, event
 * 
 * \b From: shm_name
 */
#define DCMD_DSPMGR_CONFIG	__DIOTF(_DCMD_DSPMGR, 5, dspmgr_config_t)

/**
 * Releases tunnel resources allocated by config
 *
 * \b Args: Pointer to a dspmgr_tunnel_t structure
 * 
 * \b To:   tunnel
 *
 * \note Deconfiguring a tunnel immediately aborts any outstanding transfers
 *       and invalidates any allocated buffer fragments
 */
#define DCMD_DSPMGR_DECONFIG	__DIOT(_DCMD_DSPMGR, 6, dspmgr_tunnel_t)

/**
 * Isochronous Transfer API
 *
 * High-speed, low-latency, one-way flow control for timing sensitive data.
 */

/**
 * Activates a tunnel
 *
 * \b Args: Pointer to a dspmgr_tunnel_t structure
 * 
 * \b To:   tunnel
 *
 * \note Once complete, buffer fragments can be issued and reclaimed including
 *       outstanding fragments before an abort
 *       Blocks until above condition is met
 */
#define DCMD_DSPMGR_READY	__DIOT(_DCMD_DSPMGR, 7, dspmgr_tunnel_t)

/**
 * Deactivates a tunnel
 *
 * \b Args: Pointer to a dspmgr_tunnel_t structure
 * 
 * \b To:   tunnel
 *
 * \note tunnel will attempt to invalidate all outstanding buffer fragments
 *       Returns immediately, abort processing happens asynchronously
 */
#define DCMD_DSPMGR_ABORT	__DIOT(_DCMD_DSPMGR, 8, dspmgr_tunnel_t)

/**
 * Begin tunnel processing
 *
 * \b Args: Pointer to a dspmgr_tunnel_t structure
 * 
 * \b To:   tunnel
 *
 * \note It is up to the client to use the resulting pulses to keep the
 *       buffers full of valid data / drain them before they are clobbered.
 */
#define DCMD_DSPMGR_ACTIVE	__DIOT(_DCMD_DSPMGR, 9, dspmgr_tunnel_t)

/**
 * Asynchronous Transfer API
 *
 * Medium-speed, medium-latency, two-way flow control for reliable data
 * transfers.
 */

/**
 * dsp fragment argument
 */
typedef struct dspmgr_fragment_t
{
	_Uint8t		tunnel;		/**< Tunnel Id */
	_Uint8t		reserved;	/**< Reserved */
	_Uint16t	fragment;	/**< Buffer fragment ID */
	_Uint32t	size;		/**< Size */
} dspmgr_fragment_t;

/**
 * Enqueue a fragment to a tunnel
 *
 * \b Args: Pointer to a dspmgr_fragment_t structure
 * 
 * \b To:   tunnel, fragment size
 *
 * \note For playback tunnels, the buffer fragments contain data
 *       For recording tunnels, the buffer fragments are empty, size is ignored
 */
#define DCMD_DSPMGR_ENQUEUE	__DIOT(_DCMD_DSPMGR, 20, dspmgr_fragment_t)

/**
 * Dequeue a fragment from a tunnel
 *
 * \b Args: Pointer to a dspmgr_fragment_t structure
 * 
 * \b To:   tunnel
 * 
 * \b From: fragment, size
 *
 * \note Reclaims for the given channel
 *       For a playback tunnels, the buffer fragment is empty
 *       For a recording tunnels, the buffer fragment contains data
 */
#define DCMD_DSPMGR_DEQUEUE	__DIOTF(_DCMD_DSPMGR, 21, dspmgr_fragment_t)

#include <_packpop.h>

#endif


__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/services/dspmgr/public/dspmgr/dcmd_dspmgr.h $ $Rev: 219613 $" )
