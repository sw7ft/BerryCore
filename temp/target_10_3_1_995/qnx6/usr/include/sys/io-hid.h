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
 *  sys/io-hid.h
 *
 */

#ifndef __NTO_IO_HID_H_INCLUDED
#define __NTO_IO_HID_H_INCLUDED

#include <sys/types.h>
#include <sys/queue.h>
#include <sys/dispatch.h>
#include <sys/iofunc.h>
#include <inttypes.h>
#include <sys/hiddi.h>

__BEGIN_DECLS


struct hiddi_device_instance;

/* defines for string callout 		*/
#define HIDD_STRING_MANUFACTURER 		0x01
#define HIDD_STRING_PRODUCT		 		0x02
#define HIDD_STRING_SERIAL_NUMBER 		0x03
#define HIDD_STRING_INTERFACE 		0x04
#define HIDD_VENDOR_UNKNOWN				0xFFFF
#define HIDD_PRODUCT_UNKNOWN			0xFFFF
#define HID_VERSION_UNKNOWN				0xFFFF

/* defines for bus types ( bits 16-19 of vendor ID when device is registered ) */

#define HIDD_BUS_TYPE_MASK 				0x00ff0000
#define HIDD_BUS_TYPE_SHIFT 			16
#define HIDD_BUS_TYPE_USB 			0x00
#define HIDD_BUS_TYPE_BLUETOOTH 	0x01
#define HIDD_BUS_TYPE_PS2 			0xff


/*
 * The following are entry points a module provides into itself
 * when it registers.  Will be called by io-hid.
 */

typedef struct _io_hid_registrant_funcs {
	_Uint32t	nfuncs;
	int     	(*client_attach)	(int reg_hdl, void *user);
	int     	(*client_detach)	(int reg_hdl, void *user);

	int			(*rbuffer_alloc)	(_Uint16t size, void **bptr);
	int			(*rbuffer_free)		(void *bptr);

	int     	(*report_read)  	(int reg_hdl, void *user, _Uint8t rid, _Uint16t rtype, void *data, _Uint16t dlen);
	int     	(*report_write)  	(int reg_hdl, void *user, _Uint8t rid, _Uint16t rtype, void *data, _Uint16t dlen);

	int     	(*get_idle)			(int reg_hdl, void *user, _Uint8t rid, _Uint16t *idle_rate);
	int     	(*set_idle)			(int reg_hdl, void *user, _Uint8t rid, _Uint16t idle_rate);

	int     	(*get_protocol)		(int reg_hdl, void *user, _Uint8t *protocol);
	int     	(*set_protocol)		(int reg_hdl, void *user, _Uint8t protocol);

	int			(*string)			(int reg_hdl, void *user, _Uint16t request, void **str);
	int			(*indexed_string)	(int reg_hdl, void *user, _Uint16t index, void **str);

	int     	(*reset)			(int reg_hdl, void *user);
	int			(*reserved)			(void *ptr);
} io_hid_registrant_funcs_t;

#define _IO_HID_REG_NFUNCS		((sizeof(io_hid_registrant_funcs_t)-sizeof(u_int))/sizeof(void *))


typedef struct _io_hid_registrant {
	_Uint32t                		flags;
	hidd_device_ident_t 			*device_ident;
	void							*desc;		/* describes device and data it sends/receives */
	_Uint16t						dlen;
	_Uint8t							reserved[2];
	void                      		*user_hdl;
	io_hid_registrant_funcs_t 		*funcs;
	_Uint8t                    		reserved2[4];
} io_hid_registrant_t;


/*
 * List of calls drivers can make into io-hid
 */

typedef struct _io_hid_self {
	_Uint32t	nfuncs;
	int			(*reg)     		(void *dll_hdl, io_hid_registrant_t *registrant, int *reg_hdlp );
	int			(*dereg)		(int registrant_hdl);
	int			(*get_buffer)	( int reg_hdlp, void **buffer );
	int			(*send_report)	(int registrant_hdl, void *data, _Uint32t dlen );
} io_hid_self_t;

#define _IO_HID_NFUNCS		((sizeof(io_hid_self_t)-sizeof(u_int))/sizeof(void *))


/*
 * Entry point for DLLs
 */

typedef struct _io_hid_dll_entry {
	char	*name;
	int 	nfuncs;
	int 	(*init) (void *dll_hdl, dispatch_t *dpp, io_hid_self_t *ioh, char *options);
	int 	(*shutdown) (void *dll_hdl);
} io_hid_dll_entry_t;

__END_DECLS

#endif

__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/services/hid/public/sys/io-hid.h $ $Rev: 734844 $" )
