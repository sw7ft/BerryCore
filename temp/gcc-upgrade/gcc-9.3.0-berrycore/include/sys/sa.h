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
 *  sa.h
 *
 */

#ifndef _SA_H_INCLUDED
#define _SA_H_INCLUDED

#include <_pack64.h>


__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/hardware/devb/cam/public/sys/sa.h $ $Rev: 219612 $" )

// we use errno for error indication ie ENOSPC, which should be followed by
// DCMD_CAM_TAPE_STATUS to determine that we hit EOM

#define SA_CMD_IMMEDIATE				0x01

#define SA_CAP_WRTOK		0x80		/* density writable */
#define SA_CAP_DUP			0x40		/* duplicate density support */
#define SA_CAP_DFLT			0x20		/* default density */
typedef struct _sa_density {
	_Uint8t		primary_density_code;
	_Uint8t		secondary_density_code;
	_Uint8t		capabilities;
	_Uint8t		rsvd;
	_Uint32t	bits_per_mm;
	_Uint16t	media_width;
	_Uint16t	tracks;
	_Uint32t	capacity;
	char		assigning_organization[8];
	char		density_name[8];
	char		description[20];
} SA_DENSITY;

#define SA_CAP_FIXED_BLOCK			0x00001
#define SA_CAP_VARIABLE_BLOCK		0x00002
#define SA_CAP_CAPACITY				0x00004
#define SA_CAP_CAPACITY_REMAINING	0x00008
#define SA_CAP_ECC					0x00010
#define SA_CAP_COMPRESSION			0x00020
#define SA_CAP_PADDING 				0x00040
#define SA_CAP_REPORT_SETMARKS		0x00080
#define SA_CAP_EOT_WARNING			0x00200

#define SA_CAP_WRITE_MRKS_IMMED 0x01000
#define SA_CAP_WRITE_SMRKS		0x02000
#define SA_CAP_WRITE_FMRKS		0x04000
// move to private sa.h
#define SA_CAP_WRITE_FMRKS_LNG	0x08000
#define SA_CAP_WRITE_FMRKS_SHRT	0x10000
#define SA_CAP_WRITE_RSVD		0x18000


#define SA_CAP_SET_ECC				0x00010
#define SA_CAP_SET_COMPRESSION		0x00020
#define SA_CAP_SET_PADDING 			0x00040
#define SA_CAP_SET_REPORT_SETMARKS	0x00080

#define SA_CAP_SET_BLOCK			0x00100
#define SA_CAP_SET_EOT_WARNING		0x00200

#define SA_CAP_ERASE_XXX
#define SA_CAP_ERASE_IMMED

#define SA_CAP_FORMAT
#define SA_CAP_FORMAT_IMMED

#define SA_CAP_REWIND_IMMED
#define SA_CAP_PREVENT
#define SA_CAP_PREVENT_IMMED
#define SA_CAP_LOAD
#define SA_CAP_LOAD_IMMED

#define SA_CAP_POS_REVERSE			0x0010000
#define SA_CAP_POS_EOD				0x0020000
#define SA_CAP_POS_REL_BLKS			0x0040000
#define SA_CAP_POS_FM				0x0080000
#define SA_CAP_POS_SEQ_FM			0x0100000
#define SA_CAP_POS_SM				0x0200000
#define SA_CAP_POS_SEQ_SM			0x0400000
#define SA_CAP_POS_ABS_BLK			0x0800000
#define SA_CAP_POS_LOG_BLK			0x1000000



////////////////

/* flags */
#define SA_DP_COMPRESSION		0x01
#define SA_DP_ECC				0x02
#define SA_DP_DATA_PADDING		0x04
#define SA_DP_REPORT_SETMARKS	0x08

#define SA_DP_CMPR_DFLT				0x01
#define SA_DP_CMPR_IBM_ALDC_512		0x03
#define SA_DP_CMPR_IBM_ALDC_1024	0x04
#define SA_DP_CMPR_IBM_ALDC_2048	0x05
#define SA_DP_CMPR_IBM_IDRC			0x10
#define SA_DP_CMPR_DCLZ				0x20
typedef struct _sa_get_drive_parm {
	_Uint8t		vend_id[8];                /* Vendor identification */
	_Uint8t		prod_id[16];               /* Product identification */
	_Uint8t		prod_rev[4];               /* Product revision level */
	_Uint32t	rsvd1;
	_Uint64t	capabilities;
	_Uint64t	rsvd2;
	_Uint32t	flags;
	_Uint32t	block_size;
	_Uint32t	block_size_min;
	_Uint32t	block_size_max;
	_Uint32t	partition_max;
	_Uint32t	eot_warning_zone_size;
	_Uint32t	compression_algorithm;
	_Uint32t	decompression_algorithm;
	_Uint32t	rsvd3[4];
	_Uint32t	densities;
	SA_DENSITY	density[1];               /* variable length */
} SA_GET_DRIVE_PARM;

typedef struct _sa_set_drive_parm {
	_Uint32t	flags;
	_Uint32t	eot_warning_zone_size;
	_Uint32t	compression_algorithm;
	_Uint32t	decompression_algorithm;
	_Uint32t	rsvd[6];
} SA_SET_DRIVE_PARM;

/* flags */
#define SA_MP_MEDIA             0x01       /* Media Present */
#define SA_MP_WP                0x02       /* Write Protected */

/* density */
#define SA_DENSITY_QIC_120		0x0f
#define SA_DENSITY_QIC_150		0x10
#define SA_DENSITY_QIC_320		0x11
#define SA_DENSITY_QIC_1350		0x12
#define SA_DENSITY_QIC_385		0x1c
#define SA_DENSITY_QIC_410		0x1d
#define SA_DENSITY_QIC_1000		0x1e
#define SA_DENSITY_QIC_2100		0x1f
#define SA_DENSITY_QIC_6GB		0x20
#define SA_DENSITY_QIC_20GB		0x21
#define SA_DENSITY_QIC_2GB		0x22
#define SA_DENSITY_QIC_875		0x23
#define SA_DENSITY_DDS2			0x24
#define SA_DENSITY_DDS3			0x25
#define SA_DENSITY_DDS4			0x26

typedef struct _sa_get_media_parm {
	_Uint32t	flags;
	_Uint32t	rsvd;
	_Uint64t	capacity;
	_Uint64t	capacity_unused;
	_Uint32t	block_size;                /* block size = 0 (variable), > 0 size in bytes */
	_Uint32t	partitions;                /* number of partitions */
	_Uint32t	density;
	_Uint32t	rsvd2[4];
} SA_GET_MEDIA_PARM;

#define SA_MP_DENSITY_NOCHNG	0x7f
typedef struct _sa_set_media_parm {
	_Uint32t	flags;                     /* none defined */
	_Uint32t	density_code;
	_Uint32t	block_size;                /* block size = 0 (variable), > 0 size in bytes */
	_Uint32t	rsvd[5];
} SA_SET_MEDIA_PARM;

#define SA_INIT_LOAD		0x00
#define SA_INIT_FORMAT		0x01
#define SA_INIT_RETENSION	0x02
typedef struct _sa_initialize {
	_Uint32t	action;
	_Uint32t	aflags;
	_Uint32t	rsvd[6];
} SA_INITIALIZE;

#define SA_GP_ABSOLUTE_POSITION     0x00
#define SA_GP_LOGICAL_POSITION      0x01
typedef struct _sa_get_position {
	_Uint32t	action;
	_Uint32t	partition;
	_Uint64t	offset;
	_Uint32t	rsvd[4];
} SA_GET_POSITION;

	// space command
#define SA_SP_SPACE_BLKS			0   /* space blocks */
#define SA_SP_SPACE_FM			 	1   /* filemarks */
#define SA_SP_SPACE_SEQ_FM		    2   /* sequential filemarks */
#define SA_SP_SPACE_EOD			    3   /* end of data */
#define SA_SP_SPACE_SM				4   /* setmarks */
#define SA_SP_SPACE_SEQ_SM		    5   /* sequential setmarks */
#define SA_SP_SPACE_MSK				7
     #define SA_SP_DIR_BWD          0x04
     #define SA_SP_DIR_FWD          0x02

	/* rewind command */
#define SA_SP_REWIND				8

	/* locate command */
#define SA_SP_ABS_BLK		        9	/* position relative to BOM */
#define SA_SP_LOG_BLK			   10	/* position relative to BOP */
typedef struct _sa_set_position {
	_Uint32t	action;
	_Uint32t	aflags;
	_Uint32t	partition;
	_Uint32t	rsvd[1];
	_Int64t		offset;
	_Uint32t	rsvd2[2];
} SA_SET_POSITION;

#define SA_ERASE_SHORT		0x00
#define SA_ERASE_LONG		0x01
typedef struct _sa_erase {
	_Uint32t	action;
	_Uint32t	aflags;
	_Uint32t	rsvd[6];
} SA_ERASE;

#define SA_CP_FIXED_PARTITION		0
typedef struct _sa_create_partition {
	_Uint32t	action;
	_Uint32t	size;
	_Uint32t	count;
	_Uint32t	rsvd[5];
} SA_CREATE_PARTITION;

#define SA_WM_SETMARKS			0x00
#define SA_WM_FILEMARKS			0x01
// move to local sa.h
#define SA_WM_SHORT_FILEMARKS	0x02
#define SA_WM_LONG_FILEMARKS	0x03
typedef struct _sa_write_marks {
	_Uint32t	mtype;
	_Uint32t	mflags;
	_Uint32t	count;
	_Uint32t	rsvd[5];
} SA_WRITE_MARKS;

#define SA_STATUS_OK		0x00
#define SA_STATUS_CLEAN		0x01
typedef struct _sa_drive_status {
	_Uint32t	status;
	_Uint32t	rsvd[7];
} SA_DRIVE_STATUS;

#include <_packpop.h>

#endif


__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/hardware/devb/cam/public/sys/sa.h $ $Rev: 219612 $" )
