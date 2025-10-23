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





#ifndef __PSMMSG_H_INCLUDED
#define __PSMMSG_H_INCLUDED

#include <sys/platform.h>
#include <sys/neutrino.h>
#include <inttypes.h>
#include <limits.h>

#define PSMDEV "/dev/psm"  /* where is the psm */
#define PSM_PREFIX_MAX_LENGTH 256

#define PS_OBJREALM_MIN          0x00
#define PS_OBJREALM_DRVR         0x01
#define PS_OBJREALM_SYS          0x02
#define PS_OBJREALM_USER         0x03
#define PS_OBJREALM_MAX          0x3f

#define PS_OBJTYPE_MIN           0x00
#define PS_OBJTYPE_PCI           0x01
#define PS_OBJTYPE_USB           0x02
#define PS_OBJTYPE_IO32          0x03
#define PS_OBJTYPE_ADDR32        0x04
#define PS_OBJTYPE_IO64          0x05
#define PS_OBJTYPE_ADDR64        0x06
#define PS_OBJTYPE_MAX           0x3f

/* open */
typedef struct _pobjopenmsg {
  uint16_t            type;
  uint16_t            zero;
  uint32_t            reserved1;
	ps_objid_t objid;
	uint32_t instance;
  size_t size;
  unsigned flags;
} PObjOpenMsg;

/* close */
typedef struct _pobjclosemsg {
  uint16_t            type;
  uint16_t            zero;
  uint32_t            reserved1;
	ps_objid_t objid;
	uint32_t instance;
  char *handle;
  unsigned flags;
} PObjCloseMsg;

/* unlink */
typedef struct _pobjunlinkmsg {
  uint16_t            type;
  uint16_t            zero;
  uint32_t            reserved1;
	ps_objid_t objid;
	uint32_t instance;
  unsigned flags;
} PObjUnlinkMsg;

/* read */
typedef struct _pobjreadmsg {
  uint16_t            type;
  uint16_t            zero;
  uint32_t            reserved1;
	ps_objid_t objid;
	uint32_t instance;
  char *handle;
  off_t offset;
  unsigned flags;
  size_t size;
} PObjReadMsg;

/* write */
typedef struct _pobjwritemsg {
  uint16_t            type;
  uint16_t            zero;
  uint32_t            reserved1;
	ps_objid_t objid;
	uint32_t instance;
  char *handle;
  off_t offset;
  unsigned flags;
  size_t size;
} PObjWriteMsg;

/* load */
typedef struct _pobjloadmsg {
  uint16_t            type;
  uint16_t            zero;
  uint32_t            reserved1;
	ps_objid_t objid;
	uint32_t instance;
  char *handle;
  unsigned flags;
  size_t size;
} PObjLoadMsg;

/* store */
typedef struct _pobjstoremsg {
  uint16_t            type;
  uint16_t            zero;
  uint32_t            reserved1;
	ps_objid_t objid;
	uint32_t instance;
  char *handle;
  unsigned flags;
  size_t size;
} PObjStoreMsg;

/* loadable */
typedef struct _pobjloadablemsg {
  uint16_t            type;
  uint16_t            zero;
  uint32_t            reserved1;
	ps_objid_t objid;
	uint32_t instance;
  char *handle;
  unsigned flags;
} PObjLoadableMsg;

struct ps_handle {
	char *handle;
	ps_objid_t objid;
	uint32_t instance;
};

/* store select */
typedef struct _pstoreselmsg {
  uint16_t   type;
  uint16_t   zero;
  uint32_t   reserved1;
	int        st_type;
	int        st_instance;
} PStoreSelMsg;

/* store num */
typedef struct _pstorenummsg {
  uint16_t   type;
  uint16_t   zero;
  uint32_t   reserved1;
} PStoreNumMsg;

/* get store descriptions */
typedef struct _pstoregetmsg {
  uint16_t   type;
  uint16_t   zero;
  uint32_t   reserved1;
	int number;
} PStoreGetMsg;

/* store delete */
typedef struct _pstoredelmsg {
  uint16_t   type;
  uint16_t   zero;
  uint32_t   reserved1;
	int        st_type;
	int        st_instance;
} PStoreDelMsg;

/* store add */
typedef struct _pstoreaddmsg {
  uint16_t   type;
  uint16_t   zero;
  uint32_t   reserved1;
	int        am_first;
	int        st_type;
	int        st_instance;
	char       prefix[PSM_PREFIX_MAX_LENGTH];
	uint32_t   size;
	uint32_t   addr;
	uint32_t   offset;
} PStoreAddMsg;

#define PSM_STORE_TYPE_SHMEM     1
#define PSM_STORE_TYPE_RAM       2
#define PSM_STORE_TYPE_FFS       3
#define PSM_STORE_TYPE_FFS_RAW   4


#define PSM_MSGCODE_BEGIN       0x5000
#define PSM_MSGCODE_OBJOPEN     0x5000 /* open */
#define PSM_MSGCODE_OBJCLOSE    0x5001 /* close */
#define PSM_MSGCODE_OBJUNLINK   0x5002 /* unlink */
#define PSM_MSGCODE_OBJREAD     0x5003 /* read */
#define PSM_MSGCODE_OBJWRITE    0x5004 /* write */
#define PSM_MSGCODE_OBJLOAD     0x5005 /* write */
#define PSM_MSGCODE_OBJSTORE    0x5006 /* write */
#define PSM_MSGCODE_OBJLOADABLE 0x5007 /* write */
#define PSM_MSGCODE_STOREADD    0x5008 /* store add */
#define PSM_MSGCODE_STOREDEL    0x5009 /* store del */
#define PSM_MSGCODE_STORESEL    0x500a /* store select */
#define PSM_MSGCODE_STORENUM    0x500b /* number of stores */
#define PSM_MSGCODE_STOREGET    0x500c /* get store descriptions */
#define PSM_MSGCODE_END         0x50ff

#endif

__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/ps/public/ps/psm_msg.h $ $Rev: 219996 $" )
