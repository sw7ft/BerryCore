/*
 * $QNXLicenseC: 
 * Copyright 2008, QNX Software Systems.  
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
 *  cdrom.h
 *
 */
#ifndef _CDROM_H_INCLUDED
#define _CDROM_H_INCLUDED

#include <sys/platform.h>
#include <_pack64.h>


__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/hardware/devb/cam/public/sys/cdrom.h $ $Rev: 219612 $" )

typedef union _cdrom_absaddr {
    struct {
        _Uint8t   reserved1;
        _Uint8t   minute;
        _Uint8t   second;
        _Uint8t   frame;
    } msf;
    _Uint32t      lba;
} cdrom_absaddr_t;

typedef struct _cdrom_playmsf {
    _Uint8t       start_minute;       /* starting minute */
    _Uint8t       start_second;       /* starting second */
    _Uint8t       start_frame;        /* starting frame  */
    _Uint8t       end_minute;         /* ending minute */
    _Uint8t       end_second;         /* ending second */
    _Uint8t       end_frame;          /* ending frame  */
} cdrom_playmsf_t;

typedef struct _cdrom_playti {
    _Uint8t       start_track;        /* starting track */
    _Uint8t       start_index;        /* starting index */
    _Uint8t       end_track;          /* ending track */
    _Uint8t       end_index;          /* ending index */
} cdrom_playti_t;

#define CDROM_ADR_NOT_SUPPLIED      0x00
#define CDROM_ADR_CURRENT_POSITION  0x01
#define CDROM_ADR_MEDIA_CATALOGUE   0x02
#define CDROM_ADR_ISRC              0x03

#define CDROM_CTRL_AUDIO_PREEMPHASIS    0x01
#define CDROM_CTRL_COPY_PERMITTED       0x02
#define CDROM_CTRL_DATA_TRACK           0x04
#define CDROM_CTRL_FOUR_CHANNEL         0x08

#define CDROM_MAX_TRACKS    100

typedef struct _cdrom_tocentry {
    _Uint8t             reserved1;
    _Uint8t             control_adr;
    _Uint8t             track_number;
	_Uint8t             reserved2;
    cdrom_absaddr_t     addr;
} cdrom_tocentry_t;

typedef struct _cdrom_read_toc {
    _Uint16t            length;
    _Uint8t             first_track;
    _Uint8t             last_track;
    cdrom_tocentry_t    toc_entry[CDROM_MAX_TRACKS];
} cdrom_read_toc_t;

typedef struct _cdrom_read_multisession {
    _Uint16t            length;
    _Uint8t             first_session;
    _Uint8t             last_session;
    cdrom_tocentry_t    ms_entry;
} cdrom_read_multisession_t;

typedef struct _cdrom_raw_tocentry {
    _Uint8t       session_number;
    _Uint8t       control_adr;
    _Uint8t       tno;
    _Uint8t       point;
	_Uint8t       min;
	_Uint8t       sec;
	_Uint8t       frame;
	_Uint8t       zero;		// hour / phour
	_Uint8t       pmin;
	_Uint8t       psec;
	_Uint8t       pframe;
} cdrom_raw_tocentry_t;

typedef struct _cdrom_read_raw_toc {
    _Uint16t     	        length;
    _Uint8t               	first_session;
    _Uint8t          	    last_session;
    cdrom_raw_tocentry_t    toc_entry[CDROM_MAX_TRACKS];
} cdrom_read_raw_toc_t;

#define CDROM_LBA           0x01
#define CDROM_MSF           0x02

#define CDROM_DATA_TRACK    0x04

#define CDROM_LEADOUT       0xAA

#define CDROM_SUBCH_DATA                0x00
#define CDROM_SUBCH_CURRENT_POSITION    0x01
#define CDROM_SUBCH_MEDIA_CATALOG       0x02
#define CDROM_SUBCH_ISRC                0x03

typedef struct _cdrom_read_sub_channel {
    _Uint8t    data_format;
    _Uint8t    track_number;
} cdrom_read_subch_t;

/*
 * Definition for audio_status returned from Read Sub-channel
 */
#define CDROM_AUDIO_INVALID     0x00    /* audio status not supported */
#define CDROM_AUDIO_PLAY        0x11    /* audio play operation in progress */
#define CDROM_AUDIO_PAUSED      0x12    /* audio play operation paused */
#define CDROM_AUDIO_COMPLETED   0x13    /* audio play successfully completed */
#define CDROM_AUDIO_ERROR       0x14    /* audio play stopped due to error */
#define CDROM_AUDIO_NO_STATUS   0x15    /* no current audio status to return */

typedef struct _sub_channel_header {
    _Uint8t   reserved;
    _Uint8t   audio_status;
    _Uint16t  data_length;
} subch_header_t;

typedef struct _sub_channel_current_position {
    subch_header_t    header;
    _Uint8t           data_format;
    _Uint8t           control_adr;
    _Uint8t           track_number;
    _Uint8t           index_number;
    cdrom_absaddr_t   addr;              /* absolute address */
    cdrom_absaddr_t   raddr;             /* relative address */
} subch_current_position_t;

typedef struct _sub_channel_media_catalog {
    subch_header_t    header;
    _Uint8t           data_format;
    _Uint8t           reserved1;
    _Uint8t           reserved2;
    _Uint8t           reserved3;
#define SC_MC_VALID			0x80
    _Uint8t           mcval;             /* msb indicates MCN valid */
    char              media_catalog[15];
} subch_media_catalog_t;

typedef struct _sub_channel_track_isrc {
    subch_header_t    header;
    _Uint8t           data_format;
    _Uint8t           track_number;
    _Uint8t           reserved2;
    _Uint8t           reserved3;
#define SC_ISRC_VALID		0x80
    _Uint8t           tcval;             /* msb indicates ISRC valid */
    char              isrc[15];
} subch_track_isrc_t;

typedef union _cdrom_subch_data {
	cdrom_read_subch_t			subch_command;
    subch_current_position_t    current_position;
    subch_media_catalog_t       media_catalog;
    subch_track_isrc_t          track_isrc;
} cdrom_subch_data_t;
	
typedef struct _cdrom_volume {
	_Uint8t     volume[4];
} cdrom_volume_t;

typedef struct _cdrom_speed {
	_Uint16t       speed;
} cdrom_speed_t;

/*
 CDROM Raw Read Track modes                     Frame Layout
Red Book (CD-DA)              |                      Data                     |
                              |                      2352                     |

Yellow Book (Mode 1)          | Sync | Header |      Data     | EDC | 0 | ECC |
                              |  12  |   4    |      2048     |  4  | 8 | 276 |

Yellow Book (Mode 2)          | Sync | Header |            Data               |
                              |  12  |   4    |            2336               |

Green Book (XA Mode 2 Form 1) | Sync | Header | SubHeader | Data | EDC | ECC  |
                              |  12  |   4    |     8     | 2048 |  4  | 276  |

Green Book (XA Mode 2 Form 2) | Sync | Header | SubHeader |    Data   | Spare |
                              |  12  |   4    |     8     |    2324   |   4   |
*/

#define CDROM_SYNC_SIZE         12
#define CDROM_HEADER_SIZE        4
#define CDROM_SUBHEADER_SIZE     8
#define CDROM_EDC_SIZE           4
#define CDROM_ECC_SIZE         276
#define CDROM_ZERO_SIZE          8
#define CDROM_SPARE_SIZE         4

#define CDROM_CDDA_FRAME_SIZE			2352 /* Data */
#define CDROM_YELLOW_MODE2_FRAME_SIZE	2352 /* Sync + Header + Data */
#define CDROM_XA_FORM2_FRAME_SIZE		2352 /* Header + SubHeader + Data */
#define CDROM_RAW_FRAME_SIZE			2352
#define CDROM_COOKED_FRAME_SIZE			2048

#define CDROM_EST_CDDA			0x00
#define CDROM_EST_YELLOW_MODE2	0x02
#define CDROM_EST_XA_FORM2		0x04
#define CDROM_EST_MSK			0xffff
typedef struct _cdrom_raw_read {
    _Uint32t        lba;
    _Uint32t        nsectors;
    _Uint32t        est;           /* expected sector type */
} cdrom_raw_read_t;

#define MSF_S_DFLT		0x3C
#define MSF_F_DFLT		0x4B
/*
Inactivity Time    Minimum Time in     Inactivity Time    Minimum Time in
Multiplier Value   Hold Track State    Multiplier Value   Hold Track State
      0x0           Vendor-specific           0x8               16 s
      0x1               125 ms                0x9               32 s
      0x2               250 ms                0xa               1 min
      0x3               500 ms                0xb               2 min
      0x4               1 s                   0xc               4 min
      0x5               2 s                   0xd               8 min
      0x6               4 s                   0xe               16 min
      0x7               8 s                   0xf               32 min
*/
typedef struct _cdrom_param {
    _Uint8t       multiplier;		/* Inactivity Time Multiplier ( 0 - 0xf )*/
    _Uint16t      msf_s;			/* Number of MSF - S Units per MSF - M Unit */
    _Uint16t      msf_f;			/* Number of MSF - F Units per MSF - S Unit */
} cdrom_param_t;

#define CDROM_ADR(_x)                   (((_x) >> 4) & 0xf)
#define CDROM_CONTROL(_x)               ((_x) & 0xf)

#define MSF2LBA(_min, _sec, _frame)     (((_min) * 60 + (_sec)) * 75 + (_frame) - 150)
#define LBA2MIN(_lba)                   ((((_lba) + 150) / 75) / 60)
#define LBA2SEC(_lba)                   ((((_lba) + 150) / 75) % 60)
#define LBA2FRAME(_lba)                 (((_lba) + 150) % 75)

#define CDROM_EXCHANGE_EJECT        0x0
#define CDROM_EXCHANGE_RELOAD       0x1
#define CDROM_EXCHANGE_UNLOAD       0x2
#define CDROM_EXCHANGE_LOAD         0x3
#define CDROM_EXCHANGE_INITIALIZE   0xf
typedef struct _cdrom_exchange {
	_Uint32t	operation;
	_Uint32t	slot;
	_Uint32t	rsvd;
} cdrom_exchange_t;

#define CDROM_MAX_SLOTS		255
#define CDROM_MSH_CHANGER_FAULT			(0x1 << 7)
#define CDROM_MSH_CHANGER_READY			(0x0 << 5)
#define CDROM_MSH_CHANGER_LOADING		(0x1 << 5)
#define CDROM_MSH_CHANGER_UNLOADING		(0x2 << 5)
#define CDROM_MSH_CHANGER_INITIALIZING	(0x3 << 5)
#define CDROM_MSH_MECHANISM_DOOR_OPEN	(0x1 << 4)
#define CDROM_MSH_MECHANISM_IDLE		(0x0 << 5)
#define CDROM_MSH_MECHANISM_AUDIO		(0x1 << 5)
#define CDROM_MSH_MECHANISM_AUDIO_SCAN	(0x2 << 5)
#define CDROM_MSH_MECHANISM_HOST		(0x3 << 5)
#define CDROM_MSH_MECHANISM_UNKNOWN		(0x7 << 5)
typedef struct _cdrom_mechanism_status_header {
    _Uint8t       changer_state_slot;
    _Uint8t       mech_state;
    _Uint8t       current_lba[3];
    _Uint8t       num_slots_avail;
    _Uint16t      slot_table_len;
} cdrom_mechanism_status_header_t;

#define CDROM_STR_DISC_PRESENT  0x80
#define CDROM_STR_DISC_CHANGED  0x01
typedef struct _cdrom_slot_table_response {
    _Uint8t       flags;
    _Uint8t       rsvd[3];
} cdrom_slot_table_response_t;

typedef struct _cdrom_mechanism_status {
	cdrom_mechanism_status_header_t   hdr;
	cdrom_slot_table_response_t       str[CDROM_MAX_SLOTS];
} cdrom_mechanism_status_t;

#define CDROM_MAX_TEXT		255

/* Data pack types */
#define CDROM_DPT_TITLE       0x80    /* Title of album name or track titles */
#define CDROM_DPT_PERFORMER   0x81    /* Name(s) of performer(s) */
#define CDROM_DPT_SONGWRITER  0x82    /* Name(s) of songwriter(s) */
#define CDROM_DPT_COMPOSER    0x83    /* Name(s) of composer(s) */
#define CDROM_DPT_ARRANGER    0x84    /* Name(s) of arranger(s) */
#define CDROM_DPT_MESSAGE     0x85    /* Message(s) from content provider and or artist */
#define CDROM_DPT_IDENT       0x86    /* Disc identification information */
#define CDROM_DPT_GENRE       0x87    /* Genre identification and genre information */
#define CDROM_DPT_TOC         0x88    /* Table of content information */
#define CDROM_DPT_TOC2        0x89    /* Second Table of content information */
#define CDROM_DPT_UPCEAN      0x8e    /* UPC/EAN code of the album and ISRC code of each track */
#define CDROM_DPT_SIZEINFO    0x8f    /* Size information of the block */

#define CDROM_BC_DBCC         0x80    /* Double Byte Character Code */
#define CDROM_DATA_SIZE       12
#define CDROM_MAX_PACKS       255
typedef struct _cdrom_datapack {
	_Uint8t	pack_type;
	_Uint8t	trk;
	_Uint8t	seq;
	_Uint8t	blk_char;
	char	data[CDROM_DATA_SIZE];
	_Uint8t	crc0;
	_Uint8t	crc1;
} cdrom_datapack_t;

typedef struct _cdrom_cd_text {
    _Uint16t            npacks;               /* number of descriptors */
	char				rsvd[2];
 	cdrom_datapack_t	packs[CDROM_MAX_TEXT];
} cdrom_cd_text_t;

typedef struct _cdrom_scan {
    cdrom_absaddr_t     addr;
#define CDROM_SCAN_DIR_FORWARD		0x00
#define CDROM_SCAN_DIR_REVERSE		0x10
	_Uint8t		direction;
#define CDROM_SCAN_TYPE_LBA		0x00
#define CDROM_SCAN_TYPE_MSF		0x40
#define CDROM_SCAN_TYPE_TRK		0x80
#define CDROM_SCAN_TYPE_MSK		0xc0
	_Uint8t		type;
	_Uint8t		speed;
	_Uint8t		rsvd[9];
} cdrom_scan_t;

#include <_packpop.h>

#endif
