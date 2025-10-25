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
 *  sys/pccard_msg.h
 *

 *
 */

#ifndef __PCCARD_MSG_H_INCLUDED
#define __PCCARD_MSG_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
 #include <sys/types.h>
#endif

#ifndef __PCCARD_H_INCLUDED
 #include <sys/pccard.h>
#endif

#include	<inttypes.h>
#include	<sys/siginfo.h>

#define _PCCARD_BASE					0x0a00
#define _PCCARD_COMMON					_PCCARD_BASE
#define _PCCARD_COMMON_END				(_PCCARD_BASE+0x80)
#define _PCCARD_MEMORY					_PCCARD_COMMON_END
#define _PCCARD_MEMORY_END				(_PCCARD_MEMORY+0x10)
#define _PCCARD_IO						_PCCARD_MEMORY_END
#define _PCCARD_IO_END					(_PCCARD_IO+0x10)
#define _PCCARD_CONF					_PCCARD_IO_END
#define _PCCARD_CONF_END				(_PCCARD_CONF+0x10)

#define _PCCARD_ATTACH					(_PCCARD_COMMON+0x00)
#define _PCCARD_DETACH					(_PCCARD_COMMON+0x01)
#define _PCCARD_ARM						(_PCCARD_COMMON+0x02)
#define _PCCARD_INFO					(_PCCARD_COMMON+0x03)
#define _PCCARD_LOCK					(_PCCARD_COMMON+0x04)
#define _PCCARD_UNLOCK					(_PCCARD_COMMON+0x05)
#define _PCCARD_RAW_READ				(_PCCARD_COMMON+0x06)
#define _PCCARD_RECONFIGURE				(_PCCARD_COMMON+0x07)
#define _PCCARD_CLEAR_RESOURCES			(_PCCARD_COMMON+0x08)
#define _PCCARD_ADD_RESOURCES			(_PCCARD_COMMON+0x09)
#define _PCCARD_QUERY_RESOURCES			(_PCCARD_COMMON+0x0a)
#define _PCCARD_RAW_WRITE				(_PCCARD_COMMON+0x0b)
#define _PCCARD_RAW_ERASE				(_PCCARD_COMMON+0x0c)
#define _PCCARD_RECONFIG_SOCKET				(_PCCARD_COMMON+0x0d)
#define _PCCARD_READ_BYTE_ATTR				(_PCCARD_COMMON+0x0e)
#define _PCCARD_WRITE_BYTE_ATTR				(_PCCARD_COMMON+0x0f)

#define _PCCARD_MEM_READ				(_PCCARD_MEMORY+0x00)
#define _PCCARD_MEM_WRITE				(_PCCARD_MEMORY+0x01)
#define _PCCARD_MEM_ERASE				(_PCCARD_MEMORY+0x02)
#define _PCCARD_MEM_WINDOW_ALLOC		(_PCCARD_MEMORY+0x03)
#define _PCCARD_MEM_WINDOW_MAP			(_PCCARD_MEMORY+0x04)
#define _PCCARD_MEM_WINDOW_FREE			(_PCCARD_MEMORY+0x05)
#define _PCCARD_MEM_PARTITION_TYPE		(_PCCARD_MEMORY+0x06)
#define _PCCARD_MEM_WINDOW_ALLOC8			(_PCCARD_MEMORY+0x07)

#define _PCCARD_CONF_REREAD				(_PCCARD_CONF+0x00)

struct _pccard_attach {
	msg_t						type;
	int16_t						handle;
	int16_t						dummy;
	int16_t						filler;
	pid_t						pid;
	pthread_t					tid;
};

struct _pccard_attach_reply {
	msg_t						status;
};

struct _pccard_detach {			/* Should look like _IO_CLOSE */
	msg_t						type;
	int16_t						handle;
	int16_t						dummy;
	int16_t						filler;
	pid_t						pid;
};

struct _pccard_detach_reply {
	msg_t						status;
};

struct _pccard_arm {
	msg_t						type;
	int16_t						handle;
	int16_t						devtype;
	uint16_t					event;
	int16_t						event_value;
	int16_t						filler;
	pid_t						pid;
	struct sigevent				ntoevent;
};

struct _pccard_arm_reply {
	msg_t						status;
};

struct _pccard_information {
	msg_t						type;
	int16_t						handle;
	int16_t						socket;
	uint16_t					size;
	pid_t						pid;
};

struct _pccard_information_reply {
	msg_t						status;
	struct _pccard_info			info;
};

struct _pccard_lock	{
	msg_t						type;
	int16_t						handle;
	int16_t						socket;
	int16_t						index;
	int16_t						oflag;
	int16_t						filler;
	pid_t						pid;
};

struct _pccard_lock_reply {
	msg_t						status;
};

struct _pccard_unlock {
	msg_t						type;
	int16_t						handle;
	int16_t						socket;
	int16_t						index;
	pid_t						pid;
};

struct _pccard_unlock_reply {
	msg_t						status;
};

struct _pccard_raw_read {
	msg_t						type;
	int16_t						handle;
	int16_t						socket;
	uint16_t					size;
	uint32_t					addr;
	uint8_t						memtype;
	uint8_t						dummy1 [3];
	pid_t						pid;
};

struct _pccard_raw_read_reply {
	msg_t						status;
	uint16_t					size;
	uint8_t						data[1];		/* variable length */
};

struct _pccard_raw_write {
	msg_t						type;
	int16_t						handle;
	int16_t						socket;
	uint16_t					size;
	uint32_t					addr;
	uint8_t						memtype;
	uint8_t						dummy1 [3];
	pid_t						pid;
	uint8_t						data[1];		/* variable length */
};

struct _pccard_raw_write_reply {
	msg_t						status;
	uint16_t					size;
};

struct _pccard_raw_erase {
	msg_t						type;
	int16_t						handle;
	int16_t						socket;
	uint16_t					count;
	uint32_t					addr;
	pid_t						pid;
};

struct _pccard_raw_erase_reply {
	msg_t						status;
	uint16_t					count;
};

struct _pccard_reconfigure {
	msg_t						type;
	int16_t						handle;
	int16_t						socket;
	int16_t						filler;
	pid_t						pid;
};
	
struct _pccard_reconfigure_reply {
	msg_t						status;
};

struct _pccard_reconfig_socket {
	msg_t						type;
	int16_t						handle;
	int16_t						socket;
	int16_t						filler;
	int32_t						voltage;
	pid_t						pid;
};
	
struct _pccard_reconfig_socket_reply {
	msg_t						status;
};

struct _pccard_clear_resources {
	msg_t						type;
	int16_t						handle;
	pid_t						pid;
};

struct _pccard_clear_resources_reply {
	msg_t						status;
};

struct _pccard_add_resources {
	msg_t						type;
	int16_t						handle;
	int16_t						num;
	int8_t						which;			/* _PCCARD_RESOURCE_* */
	int8_t						priority;
	pid_t						pid;
	struct _pccard_resource 	resource [1];
};

struct _pccard_add_resources_reply {
	msg_t						status;
};

struct _pccard_query_resources {
	msg_t						type;
	int16_t						handle;
	int8_t						which;			/* _PCCARD_RESOURCE_* */
	int8_t						subtype;
	int16_t						filler;
	pid_t						pid;
};

struct _pccard_query_resources_reply {
	msg_t						status;
	int16_t						num;
	struct _pccard_resource 	resource [1];		/* may be more */
};

struct _pccard_read_write_byte_attr {
	msg_t						type;
	int16_t						handle;
	int16_t						socket;
	int16_t						filler;
	uint32_t					addr;
	uint8_t						val;
	uint8_t						dummy [3];
	pid_t						pid;
};

struct _pccard_read_write_byte_attr_reply {
	msg_t						status;
	uint8_t						val;
	uint8_t						filler;
};

/*
	memory client
*/

struct _pccard_mem_read {
	msg_t						type;
	int16_t						handle;
	int16_t						socket;
	int16_t						filler;
	uint32_t					addr;
	uint16_t					size;
	int16_t						index;
	pid_t						pid;
};

struct _pccard_mem_read_reply {
	msg_t						status;
	uint16_t					size;
	uint8_t						data[1];
};

struct _pccard_mem_write {
	msg_t						type;
	int16_t						handle;
	int16_t						socket;
	int16_t						filler;
	uint32_t					addr;
	int16_t						index;
	uint16_t					size;
	uint8_t						data[1];
};

struct _pccard_mem_write_reply {
	msg_t						status;
	uint16_t					size;
};

struct _pccard_mem_erase {
	msg_t						type;
	int16_t						handle;
	int16_t						socket;
	int16_t						index;
	long						start;
	long						count;
};

struct _pccard_mem_erase_reply {
	msg_t						status;
	int16_t						filler;
	long						count;
};

struct _pccard_mem_window_alloc {
	msg_t						type;
	int16_t						handle;
	int16_t						socket;
	int16_t						index;
	uint32_t					size;
	pid_t						pid;
};

struct _pccard_mem_window_alloc_reply {
	msg_t						status;
	int16_t						index;
	paddr_t						phys;
	uint32_t					size;
};

struct _pccard_mem_window_map {
	msg_t						type;
	int16_t						handle;
	int16_t						socket;
	int16_t						index;
	uint32_t					offset;
	pid_t						pid;
};

struct _pccard_mem_window_map_reply {
	msg_t						status;
	int16_t						filler;
	uint32_t					offset;
	uint32_t					size;
};

struct _pccard_mem_window_free {
	msg_t						type;
	int16_t						handle;
	int16_t						socket;
	int16_t						index;
	pid_t						pid;
};

struct _pccard_mem_window_free_reply {
	msg_t						status;
};

struct _pccard_mem_partition_type {
	msg_t						type;
	int16_t						handle;
	int16_t						socket;
	int16_t						index;
	int16_t						partition;
	int16_t						filler;
};

struct _pccard_mem_partition_type_reply {
	msg_t						status;
};

/*
	configuration client
*/

struct _pccard_conf_reread {
	msg_t						type;
	int16_t						handle;
	pid_t						pid;
};

struct _pccard_conf_reread_reply {
	msg_t						status;
};

#endif

__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/pccard/public/sys/pccard_msg.h $ $Rev: 219996 $" )
