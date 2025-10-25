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

#ifndef _CPT_H_INCLUDED
#define _CPT_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
#include <sys/types.h>
#endif


__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/hardware/devb/cam/public/sys/cpt.h $ $Rev: 219612 $" )

/* ---------------------------------------------------------------------- */

/* Defines for the CAM status field in the CCB header. */

#define CAM_REQ_INPROG          0x00  /* CCB request is in progress */
#define CAM_REQ_CMP             0x01  /* CCB request completed w/out error */
#define CAM_REQ_ABORTED         0x02  /* CCB request aborted by the host */
#define CAM_UA_ABORT            0x03  /* Unable to Abort CCB request */
#define CAM_REQ_CMP_ERR         0x04  /* CCB request completed with an err */
#define CAM_BUSY                0x05  /* CAM subsystem is busy */
#define CAM_REQ_INVALID         0x06  /* CCB request is invalid */
#define CAM_PATH_INVALID        0x07  /* Path ID supplied is invalid */
#define CAM_DEV_NOT_THERE       0x08  /* SCSI device not installed/there */
#define CAM_UA_TERMIO           0x09  /* Unable to Terminate I/O CCB req */
#define CAM_SEL_TIMEOUT         0x0A  /* Target selection timeout */
#define CAM_CMD_TIMEOUT         0x0B  /* Command timeout */
#define CAM_MSG_REJECT_REC      0x0D  /* Message reject received */
#define CAM_SCSI_BUS_RESET      0x0E  /* SCSI bus reset sent/received */
#define CAM_UNCOR_PARITY        0x0F  /* Uncorrectable parity err occurred */
#define CAM_AUTOSENSE_FAIL      0x10  /* Autosense: Request sense cmd fail */
#define CAM_NO_HBA              0x11  /* No HBA detected Error */
#define CAM_DATA_RUN_ERR        0x12  /* Data overrun/underrun error */
#define CAM_UNEXP_BUSFREE       0x13  /* Unexpected BUS free */
#define CAM_SEQUENCE_FAIL       0x14  /* Target bus phase sequence failure */
#define CAM_CCB_LEN_ERR         0x15  /* CCB length supplied is inadequate */
#define CAM_PROVIDE_FAIL        0x16  /* Unable to provide requ. capability */
#define CAM_BDR_SENT            0x17  /* A SCSI BDR msg was sent to target */
#define CAM_REQ_TERMIO          0x18  /* CCB request terminated by the host */

#define CAM_LUN_INVALID         0x38  /* LUN supplied is invalid */
#define CAM_TID_INVALID         0x39  /* Target ID supplied is invalid */
#define CAM_FUNC_NOTAVAIL       0x3A  /* The requ. func is not available */
#define CAM_NO_NEXUS            0x3B  /* Nexus is not established */
#define CAM_IID_INVALID         0x3C  /* The initiator ID is invalid */
#define CAM_CDB_RECVD           0x3E  /* The SCSI CDB has been received */
#define CAM_SCSI_BUSY           0x3F  /* SCSI bus busy */

#define CAM_SIM_QFRZN           0x40  /* The SIM queue is frozen w/this err */
#define CAM_AUTOSNS_VALID       0x80  /* Autosense data valid for target */

#define CAM_STATUS_MASK         0x3F  /* Mask bits for just the status # */

/* ---------------------------------------------------------------------- */

/* Defines for the CAM flags field. */

#define CAM_DIR_RESV       0x00000000 /* Data direction (00: reserved) */
#define CAM_SCATTER_VALID  0x00000010 /* Scatter/gather list is valid */
#define CAM_DIS_AUTOSENSE  0x00000020 /* Disable autosense feature */
#define CAM_DIR_IN         0x00000040 /* Data direction (01: DATA IN) */
#define CAM_DIR_OUT        0x00000080 /* Data direction (10: DATA OUT) */
#define CAM_DIR_NONE       0x000000C0 /* Data direction (11: no data) */
#define CAM_DIS_SYNC       0x00002000 /* Disable sync, go to async */
#define CAM_INITIATE_SYNC  0x00004000 /* Attempt Sync data xfer, and SDTR */
#define CAM_DIS_DISCONNECT 0x00008000 /* Disable disconnect */
#define CAM_SIM_QIMMED     0x00010000 /* Place CCB at the head of SIM Q/immediate */
#define CAM_DATA_PHYS      0x00200000 /* SG/Buffer data ptrs are physical */
#define CAM_DIS_AUTOSRP    0x01000000 /* Disable autosave/restore ptrs */
#define CAM_DIS_AUTODISC   0x02000000 /* Disable autodisconnect */
#define CAM_MSGB_VALID     0x20000000 /* Message buffer valid */
#define CAM_STATUS_VALID   0x40000000 /* Status buffer valid */
#define CAM_DATAB_VALID    0x80000000 /* Data buffer valid */

/* Defines for the CAM vu flags field. */
#define CAM_VUF_TIME_G1		0x01
#define CAM_VUF_TIME_G2		0x02
#define CAM_VUF_TIME_G3		0x04
#define CAM_VUF_DECRYPT		0x08

/* ---------------------------------------------------------------------- */

/* Defines for the timeout field in the SCSI I/O CCB.  At this time a value
of 0xF-F indicates a infinite timeout.  A value of 0x0-0 indicates that the
SIM's default timeout can take effect. */

#define CAM_TIME_DEFAULT        0x00000000      /* Use SIM default value */
#define CAM_TIME_INFINITY       0xFFFFFFFF      /* Infinite timeout for I/O */

#define XPT_SCSI_IO     0x01    /* Execute the requested SCSI IO */
#define XPT_SCAN_BUS    0x07    /* Scan SCSI bus */

typedef struct cam_pass_thru
{
	ulong_t		cam_flags;			/* Flags for operation of the subsystem */
	uchar_t		cam_path_id;		/* Path ID for the request */
	uchar_t		cam_target_id;		/* Target device ID */
	uchar_t		cam_target_lun;		/* Target LUN number */
	uchar_t		cam_status;			/* Returned CAM subsystem status */

	uchar_t		cam_scsi_status;	/* Returned scsi device status */
	uchar_t		cam_vu_flags;
	uchar_t		cam_func_code;

    uchar_t		cam_sense_resid;	/* Autosense resid length: 2's comp */
    ulong_t		cam_resid;			/* Transfer residual length: 2's comp */

	ulong_t		cam_timeout;		/* Timeout value */

	uchar_t		cam_sense_len;		/* Num of bytes in the Autosense buf */
	uchar_t		cam_cdb_len;		/* Number of bytes for the CDB */
	ushort_t	cam_sglist_cnt;		/* Num of scatter gather list entries */

	ulong_t		cam_sense_ptr;		/* Offset from start of struct to data */
	ulong_t		cam_data_ptr;		/* physical address of buffer, or offset */
									/* from start of struct to scatter gather */
									/* list */
	ulong_t		cam_dxfer_len;		/* Data transfer length */
	uchar_t		cam_cdb[16];		/* CDB bytes */
} CAM_PASS_THRU;

#ifndef _CAM_SG_ELEM_DEFINED
#define _CAM_SG_ELEM_DEFINED
/* Typedef for a scatter/gather list element. */
typedef struct sg_elem
{
    paddr_t cam_sg_address;             /* Scatter/Gather address */
    u_long cam_sg_count;                /* Scatter/Gather count */
} SG_ELEM;
#endif

#endif
