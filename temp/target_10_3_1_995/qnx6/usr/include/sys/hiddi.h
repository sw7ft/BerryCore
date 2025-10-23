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
 *  sys/hiddi.h
 *

 */

#include <inttypes.h>
#include <sys/types.h>
#include <sys/queue.h>

#ifndef __HIDDI_SYS_H_INCLUDED
#define __HIDDI_SYS_H_INCLUDED

#define HIDD_VERSION				0x0100
#define HID_VERSION					0x0100
#define HIDD_CONNECT_WAIT			60
#define HIDD_CONNECT_WILDCARD		(-1)

#define HIDD_TIME_DEFAULT			0x00000000
#define HIDD_TIME_INFINITY			0xFFFFFFFF

/* flags for report attach		*/
#define HIDD_REPORT_EXCLUSIVE			0x02
#define HIDD_REPORT_FILTER				0x01

/* flags for  report callback	*/
#define HIDD_REPORT_FIRST				0x01
#define HIDD_REPORTS_RESUMED			0x02
#define HIDD_REPORT_BUFFER_OVERFLOW		0x04

#ifdef __QNXNTO__
__BEGIN_DECLS
#else
#ifdef __cplusplus
extern "C" {
#endif
#endif


/* Opaque structures			*/
struct hidd_connection;
struct hidd_device_instance;
struct hidd_report_instance;
struct hidd_report;
struct hidd_report_info;
struct hidd_collection;
struct hidd_field;

typedef struct hidd_button {
	_Uint16t	usage_page;
	_Uint16t	usage;

} hidd_button_t;

typedef struct hidd_device_ident {
	_Uint32t				vendor_id;
	_Uint32t				product_id;
	_Uint32t				version;
} hidd_device_ident_t;

typedef struct hidd_device_instance {
	TAILQ_ENTRY(hidd_device_instance)   link;
	_Uint32t							devno;
	hidd_device_ident_t					device_ident;
	struct hidd_report_info				*report_info;	/* preparsed report descriptor data */
	_Uint16t							report_desc_len;
	_Uint8t								reserved[2];
} hidd_device_instance_t;

typedef struct hidd_funcs {
	_Uint32t		nentries;
	void			(*insertion)(struct hidd_connection *, hidd_device_instance_t *instance);
	void			(*removal)(struct hidd_connection *, hidd_device_instance_t *instance);
	void			(*report)(struct hidd_connection *, struct hidd_report *handle, void *report_data, _Uint32t report_len, _Uint32t flags, void *user);
	void			(*event)(struct hidd_connection *, hidd_device_instance_t *instance, _Uint16t type);
} hidd_funcs_t;

#define _HIDDI_NFUNCS ((sizeof(hidd_funcs_t) - sizeof(_Uint32t)) / sizeof(void *))

typedef struct hidd_server_info {
	_Uint16t				vhid;
	_Uint16t				vhidd;
} hidd_server_info_t;

typedef struct hidd_connect_parm {
	const char					*path;
	_Uint16t					vhid;
	_Uint16t					vhidd;
	_Uint32t					flags;
	_Uint32t					evtbufsz;
	hidd_device_ident_t			*device_ident;
	hidd_funcs_t				*funcs;
	_Uint16t					connect_wait;
	_Uint16t					_reserved[5];
} hidd_connect_parm_t;

#define HIDD_CONNECT_FLAGS_PNP_MONITOR		0x80000000


typedef struct hidd_report_props {
	_Uint16t			usage_page;
	_Uint8t				report_id;
	_Uint8t				reserved[1];
	_Uint16t			report_size;
	_Uint16t			report_count;
	_Uint32t			data_properties;
	_Uint16t			unit_exponent;
	_Uint16t			unit;
	_Int16t				logical_min, 		logical_max;
	_Int16t				physical_min, 		physical_max;
	_Uint16t			usage_min, 			usage_max;
	_Uint16t			string_min, 		string_max;
	_Uint16t			designator_min, 	designator_max;
	_Uint8t				reserved2[2];
} hidd_report_props_t;

/* defines for data properties                      If bit not set then means */

#define HIDD_DATA_PROP_CONSTANT				0x00000001  /* DATA                */
#define HIDD_DATA_VARIABLE					0x00000002  /* ARRAY               */
#define HIDD_DATA_RELATIVE					0x00000004  /* ABSOLUTE            */
#define HIDD_DATA_WRAP						0x00000008  /* NO_WRAP             */
#define HIDD_DATA_NONLINEAR					0x00000010  /* LINEAR              */
#define HIDD_DATA_NO_PREFERRED_STATE		0x00000020  /* PREFERRED_STATE     */
#define HIDD_DATA_NULL_STATE				0x00000040  /* NO NULL STATE       */
#define HIDD_DATA_VOLITILE					0x00000080  /* NONVOLITILE         */
#define HIDD_DATA_BUFFER_BYTES				0x00000100  /* BIT_FIELD           */


/* macros to help interpret data properties flags */
#define HIDD_IS_CONSTANT			( flags )		(flags & HIDD_DATA_CONSTANT) 			? 1 : 0
#define HIDD_IS_DATA				( flags ) 		(flags & HIDD_DATA_CONSTANT) 			? 0 : 1
#define HIDD_IS_VARIABLE			( flags )		(flags & HIDD_DATA_VARIABLE) 			? 1 : 0
#define HIDD_IS_ARRAY				( flags )		(flags & HIDD_DATA_VARIABLE) 			? 0 : 1
#define HIDD_IS_RELATIVE			( flags )		(flags & HIDD_DATA_RELATIVE) 			? 1 : 0
#define HIDD_IS_ABSOLUTE			( flags )		(flags & HIDD_DATA_RELATIVE) 			? 0 : 1
#define HIDD_HAS_WRAP				( flags )		(flags & HIDD_DATA_WRAP) 	 			? 1 : 0
#define HIDD_HAS_NO_WRAP			( flags )		(flags & HIDD_DATA_WRAP)     			? 0 : 1
#define HIDD_IS_NON_LINEAR			( flags )		(flags & HIDD_DATA_NONLINEAR) 			? 1 : 0
#define HIDD_IS_LINEAR				( flags )		(flags & HIDD_DATA_NONLINEAR) 			? 0 : 1
#define HIDD_HAS_NO_PREFERRED_STATE	( flags )		(flags & HIDD_DATA_NO_PREFERRED_STATE) 	? 1 : 0
#define HIDD_HAS_PREFERRED_STATE	( flags )		(flags & HIDD_DATA_NO_PREFERRED_STATE) 	? 0 : 1
#define HIDD_IS_VOLITILE			( flags )		(flags & HIDD_DATA_VOLITILE) 			? 1 : 0
#define HIDD_IS_NONVOLITILE			( flags )		(flags & HIDD_DATA_VOLITILE) 			? 0 : 1
#define HIDD_IS_BUFFERED_BYTES		( flags )		(flags & HIDD_DATA_BUFFERED_BYTES) 		? 1 : 0
#define HIDD_IS_BIT_FIELD			( flags )		(flags & HIDD_DATA_BUFFERED_BYTES) 		? 0 : 1



/* connection functions */
extern int hidd_connect( hidd_connect_parm_t *parm, struct hidd_connection **connection);
extern int hidd_disconnect( struct hidd_connection *connection );

/* report locating */
extern int hidd_get_collections( struct hidd_device_instance *report_info, struct hidd_collection *search, struct hidd_collection ***found, _Uint16t *num);
extern int hidd_collection_usage( struct hidd_collection *collection, _Uint16t *usage_page, _Uint16t *usage);
extern int hidd_get_report_instance( struct hidd_collection *collection, _Uint16t report_index, _Uint16t report_type, struct hidd_report_instance **report_inst );
extern int hidd_report_collection( struct hidd_report_instance *report, struct hidd_collection **collection );
extern int hidd_get_num_props( struct hidd_report_instance *report_inst, _Uint16t *num );
extern int hidd_get_report_props( struct hidd_report_instance *report_inst, hidd_report_props_t *report_props, _Uint16t *len);

/* report registration */
extern int hidd_report_attach( struct hidd_connection *connection, struct hidd_device_instance *device,
	struct hidd_report_instance *report_inst, _Uint32t flags, size_t extra, struct hidd_report **report );
extern int hidd_report_detach( struct hidd_report *report );
extern int hidd_reports_detach( struct hidd_connection *connection, struct hidd_device_instance *device_instance);
extern void *hidd_report_extra(struct hidd_report *report);

extern int hidd_get_idle( struct hidd_report *handle, _Uint16t *idle_rate);
extern int hidd_set_idle( struct hidd_report *handle, _Uint16t idle_rate);

/* report retrieval/sending */
extern int hidd_get_report( struct hidd_report *report , _Uint8t *report_data );
extern int hidd_send_report( struct hidd_report *handle , void *report_data );

/* report buffer allocation */
extern int hidd_report_len( struct hidd_report_instance *report_inst, _Uint16t *report_len);
extern int hidd_num_buttons( struct hidd_report_instance *report_inst, _Uint16t *max_buttons);
extern int hidd_num_values( struct hidd_report_instance *report_inst, _Uint16t *max_values);

/*  data extraction/insertion for reports */
extern int hidd_get_buttons( struct hidd_report_instance *report , struct hidd_collection *col, _Uint16t usage_page , void *report_data , _Uint16t *usages , _Uint16t *len );
extern int hidd_get_all_buttons( struct hidd_report_instance *report , void *report_data , hidd_button_t *list , _Uint16t *len );
extern int hidd_button_list_diff(_Uint16t *list1 , _Uint16t *list2 , _Uint16t *diff , _Uint16t *len );
extern int hidd_button_list_same(_Uint16t *list1 , _Uint16t *list2 , _Uint16t *same , _Uint16t *len );
extern int hidd_get_usage_value( struct hidd_report_instance *report , struct hidd_collection *col , _Uint16t usage_page , _Uint16t usage , void *report_data , _Uint32t *usage_value);
extern int hidd_get_scaled_usage_value( struct hidd_report_instance *report , struct hidd_collection *col , _Uint16t usage_page , _Uint16t usage , void *report_data , _Int32t *usage_value );
extern int hidd_set_buttons( struct hidd_report_instance *report ,struct hidd_collection *col, _Uint16t usage_page , _Uint16t *usage_list , _Uint16t len , _Uint8t *report_data , _Uint16t buff_len );
extern int hidd_set_usage_value( struct hidd_report_instance *report, struct hidd_collection *col, _Uint16t usage_page, _Uint16t usage, _Uint32t usage_value, _Uint8t *report_data, _Uint16t len );

extern int hidd_server_info( struct hidd_connection *connnection, hidd_server_info_t *info );

/* Caution should be used when using hidd_device_reset, in the case where the HID device is part of composite USB device.
Issuing a device reset causes low level BUS reset for the entire device, which could potentially cause problems with
drivers managing the other interfaces of a composite device. */
extern int hidd_device_reset( struct hidd_connection *connnection, struct hidd_device_instance * dev_instance);

/* set device protocol  */
extern int hidd_get_protocol( struct hidd_connection *connnection, struct hidd_device_instance * dev_instance, _Uint8t *protocol_id);
extern int hidd_set_protocol( struct hidd_connection *connnection, struct hidd_device_instance * dev_instance, _Uint8t protocol_id);

/* device string functions */
extern int hidd_get_manufacturer_string( struct hidd_connection *connnection, struct hidd_device_instance *dinst, void *buffer, _Uint16t blen );
extern int hidd_get_product_string( struct hidd_connection *connnection, struct hidd_device_instance *dinst, void *buffer, _Uint16t blen );
extern int hidd_get_interface_string( struct hidd_connection *connnection, struct hidd_device_instance *dinst, void *buffer, _Uint16t blen );
extern int hidd_get_serial_number_string( struct hidd_connection *connnection, struct hidd_device_instance *dinst, void *buffer, _Uint16t blen );
extern int hidd_get_indexed_string( struct hidd_connection *connnection, struct hidd_device_instance *dinst, _Uint16t index, void *buffer, _Uint16t blen );

#ifdef __QNXNTO__
__END_DECLS
#else
#ifdef __cplusplus
};
#endif
#endif


#endif

__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/hiddi/public/sys/hiddi.h $ $Rev: 738873 $" )
