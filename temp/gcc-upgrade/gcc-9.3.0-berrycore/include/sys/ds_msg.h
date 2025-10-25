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




#ifndef __DS_MSG_H__
#define __DS_MSG_H__

#ifndef __QNXNTO__
#include <sys/io_msg.h>
#else
#include <sys/types.h>
#endif

#include <signal.h>

#include <_pack64.h>

#define DS_CREATE 1
#define DS_CLEAR  2  
#define DS_GET    3
#define DS_SET    4
#define DS_FLAGS  5

struct ds_create{
  msg_t type;
  short int fd;
  int name_len;
  char flags;
  char zero[3];
  struct sigevent sigevent;
/*  char *name; */
};

struct ds_clear{
  msg_t type;
  short int zero;
  int name_len;
/*  char *name; */
};

struct ds_flags{
  msg_t type;
  short int zero;
  int name_len;
  char flags;
  char zero2[3];
/*  char *name; */
};

struct ds_set{
  msg_t type;
  short int zero;
  int name_len;
  int data_len;
/*  char *name; */
};

struct ds_get{
  msg_t type;
  short int zero;
  int name_len;
  int data_len;
/* char *name; */
};

struct ds_get_reply{
  msg_t status;
  short int zero;
  int data_len;
/* char *variable_data */
};

#ifdef __QNXNTO__

typedef union{
  msg_t type;
  struct ds_create ds_create;
  struct ds_clear ds_clear;
  struct ds_get ds_get;
  struct ds_set ds_set;
  struct ds_flags ds_flags;
} ds_msg;

#else

typedef union{
  msg_t type;
  struct _io_open io_open;
  struct _io_close io_close;
  struct _io_fstat io_stat;
  struct ds_create ds_create;
  struct ds_clear ds_clear;
  struct ds_get ds_get;
  struct ds_set ds_set;
  struct ds_flags ds_flags;
} ds_msg;

typedef union{
  msg_t status;
  struct ds_get_reply;
  struct _io_fstat_reply io_fstat_reply;
} ds_reply; 

#endif

#include <_packpop.h>

#endif


__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/socket/public/sys/ds_msg.h $ $Rev: 233581 $" )
