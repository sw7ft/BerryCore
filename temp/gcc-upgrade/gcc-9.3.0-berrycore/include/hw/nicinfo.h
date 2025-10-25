/*
 * $QNXLicenseC: 
 * Copyright 2007,2008, QNX Software Systems.  
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







#ifndef _HW_NICINFO_H_INCLUDED
#define _HW_NICINFO_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

typedef enum nic_flags {
	NIC_FLAG_POWER_MANAGEMENT =	0x00000100,	/* Power management support enabled */
	NIC_FLAG_MULTICAST =		0x00000200,	/* multicast support enabled */
	NIC_FLAG_PROMISCUOUS =		0x00000400,	/* NIC currently in promiscuous mode */
	NIC_FLAG_BROADCAST =		0x00000800,	/* NIC is accepting broadcast frames */
	NIC_FLAG_WIRELESS =		0x00001000,	/* NIC is wireless */
	NIC_FLAG_LINK_DOWN =		0x00002000	/* link is down */
} nic_flags_t;

enum nic_media_types {
	NIC_MEDIA_802_3 =		0,
	NIC_MEDIA_802_5 =		1,
	NIC_MEDIA_FDDI =		2,
	NIC_MEDIA_ATM =			3,
	NIC_MEDIA_ARCNET =		4,
	NIC_MEDIA_CUSTOM =		6,
	NIC_MEDIA_802_11 =		7,
	NIC_MEDIA_MOST =		8
};

enum nic_connector_types {
	NIC_CONNECTOR_UNKNOWN =		0,
	NIC_CONNECTOR_UTP =		1,
	NIC_CONNECTOR_BNC =		2,
	NIC_CONNECTOR_FIBER =		3,
	NIC_CONNECTOR_AUI =		4,
	NIC_CONNECTOR_MII =		5,
	NIC_CONNECTOR_STP =		6
};

/* Flags to determine which of the ethernet-specific stats are valid */
enum nic_valid_ethernet_stats {
	NIC_ETHER_STAT_ALIGN_ERRORS =		0x00000001,
	NIC_ETHER_STAT_SINGLE_COLLISIONS =	0x00000002,
	NIC_ETHER_STAT_MULTI_COLLISIONS =	0x00000004,
	NIC_ETHER_STAT_FCS_ERRORS =		0x00000008,
	NIC_ETHER_STAT_TX_DEFERRED =		0x00000010,
	NIC_ETHER_STAT_LATE_COLLISIONS =	0x00000020,
	NIC_ETHER_STAT_XCOLL_ABORTED =		0x00000040,
	NIC_ETHER_STAT_INTERNAL_TX_ERRORS =	0x00000080,
	NIC_ETHER_STAT_NO_CARRIER =		0x00000100,
	NIC_ETHER_STAT_INTERNAL_RX_ERRORS =	0x00000200,
	NIC_ETHER_STAT_EXCESSIVE_DEFERRALS =	0x00000400,
	NIC_ETHER_STAT_LENGTH_FIELD_MISMATCH =	0x00000800,
	NIC_ETHER_STAT_LENGTH_FIELD_OUTRANGE =	0x00001000,
	NIC_ETHER_STAT_OVERSIZED_PACKETS =	0x00002000,
	NIC_ETHER_STAT_SQE_ERRORS =		0x00004000,
	NIC_ETHER_STAT_SYMBOL_ERRORS =		0x00008000,
	NIC_ETHER_STAT_JABBER_DETECTED =	0x00010000,
	NIC_ETHER_STAT_SHORT_PACKETS =		0x00020000,
	NIC_ETHER_STAT_TOTAL_COLLISION_FRAMES =	0x00040000,
	NIC_ETHER_STAT_DRIBBLE_BITS =		0x00080000
};

/* Ethernet specific statistics.  IEEE 802.3 names are given in comments */
typedef struct _nic_ethernet_stats {
	_Uint32t	valid_stats;		/* see NIC_ETHER_STAT_... */

	_Uint32t	align_errors;		/* AlignmentErrors */
	_Uint32t	single_collisions;	/* SingleCollisionFrames */
	_Uint32t	multi_collisions;	/* MultipleCollisionFrames */
	_Uint32t	fcs_errors;		/* FrameCheckSequenceErrors */
	_Uint32t	tx_deferred;		/* FramesWithDeferredXmissions */
	_Uint32t	late_collisions;	/* LateCollisions */
	_Uint32t	xcoll_aborted;		/* FramesAbortedDueToXSColls */
	_Uint32t	internal_tx_errors;	/* FramesLostDueToIntMACXmitError */
	_Uint32t	no_carrier;		/* CarrierSenseErrors */
	_Uint32t	internal_rx_errors;	/* FramesLostDueToIntMACRcvError */
	_Uint32t	excessive_deferrals;	/* FramesWithExcessiveDeferral */
	_Uint32t	length_field_mismatch;	/* InRangeLengthErrors */
	_Uint32t	length_field_outrange;	/* OutOfRangeLengthField */
	_Uint32t	oversized_packets;	/* FrameTooLongErrors */
	_Uint32t	sqe_errors;		/* SQETestErrors */
	_Uint32t	symbol_errors;		/* SymbolErrorDuringCarrier */
	_Uint32t	jabber_detected;	/* Jabber */
	_Uint32t	short_packets;		/* Runts */
	_Uint32t	total_collision_frames;
	_Uint32t	dribble_bits;
} nic_ethernet_stats_t;

/* Flags to determine which of the WiFi-specific stats are valid */
enum nic_valid_wifi_stats {
	NIC_WIFI_STAT_TX_FRAGMENT =		0x00000001,
	NIC_WIFI_STAT_TX_MULTICAST =		0x00000002,
	NIC_WIFI_STAT_TX_FAILED =		0x00000004,
	NIC_WIFI_STAT_TX_RETRY =		0x00000008,
	NIC_WIFI_STAT_TX_MULTI_RETRY =		0x00000010,
	NIC_WIFI_STAT_RTS_SUCCESS =		0x00000020,
	NIC_WIFI_STAT_RTS_FAILURE =		0x00000040,
	NIC_WIFI_STAT_ACK_FAILURE =		0x00000080,
	NIC_WIFI_STAT_DUPLICATE =		0x00000100,
	NIC_WIFI_STAT_RX_FRAGMENT =		0x00000200,
	NIC_WIFI_STAT_RX_MULTICAST =		0x00000400,
	NIC_WIFI_STAT_FCS_ERRORS =		0x00000800
};

/* WiFi specific statistics.  IEEE 802.11 names are given in comments */
typedef struct _nic_wifi_stats {
	_Uint32t	valid_stats;	/* see NIC_WIFI_STAT_... */

	_Uint32t	tx_fragment;	/* TransmittedFragmentCount */
	_Uint32t	tx_multicast;	/* MulticastTransmittedFrameCount */
	_Uint32t	tx_failed;	/* FailedCount */
	_Uint32t	tx_retry;	/* RetryCount */
	_Uint32t	tx_multi_retry;	/* MultipleRetryCount */
	_Uint32t	rts_success;	/* RTSSuccessCount */
	_Uint32t	rts_failure;	/* RTSFailureCount */
	_Uint32t	ack_failure;	/* ACKFailureCount */
	_Uint32t	duplicate;	/* FrameDuplicateCount */
	_Uint32t	rx_fragment; 	/* ReceivedFragmentCount */
	_Uint32t	rx_multicast; 	/* MulticastReceivedFrameCount */
	_Uint32t	fcs_errors;	/* FCSErrorCount */
} nic_wifi_stats_t;

/* Flags to determine which of the generic optional stats are valid */
enum nic_valid_stats {
	NIC_STAT_TXED_MULTICAST =	0x00000001,
	NIC_STAT_RXED_MULTICAST =	0x00000002,
	NIC_STAT_TXED_BROADCAST =	0x00000004,
	NIC_STAT_RXED_BROADCAST =	0x00000008,
	NIC_STAT_TX_FAILED_ALLOCS =	0x00000010,
	NIC_STAT_RX_FAILED_ALLOCS =	0x00000020
};

#define	NIC_STATS_REVISION		0

typedef struct _nic_stats {
	_Uint32t	revision;	/* Set to NIC_STATS_REVISION */
	_Uint32t	media;

	/* Media specific statistics */
	union {
		nic_ethernet_stats_t	estats;		/* NIC_MEDIA_802_3 */
		nic_wifi_stats_t	wstats;		/* NIC_MEDIA_802_11 */
		_Uint8t			bytes[1024];
	} un;

	/* Generic statistics follow */
	_Uint32t	valid_stats;	/* see NIC_STAT_... */

	/* Mandatory statistics - assumed to be valid */
	_Uint32t	txed_ok;
	_Uint32t	rxed_ok;
	_Uint64t	octets_txed_ok;
	_Uint64t	octets_rxed_ok;

	/* Optional statistics - "valid_stats" determines validity */
	_Uint32t	txed_multicast;
	_Uint32t	rxed_multicast;
	_Uint32t	txed_broadcast;
	_Uint32t	rxed_broadcast;
	_Uint32t	tx_failed_allocs;
	_Uint32t	rx_failed_allocs;

	_Uint32t	reserved[32];
} nic_stats_t;

/*
 * 802.11 (aka WiFi) DCMD_IO_NET_WIFI structure and defines.
 *
 * QSSL subcmd's will always start at 0x0F000000, others below are open
 */
#define NIC_WIFI_SUBCMD_SSID			0x0F000001    
#define NIC_WIFI_SUBCMD_BSS_TYPE		0x0F000002	
	#define NIC_WIFI_BSS_TYPE_BSS		  0
	#define NIC_WIFI_BSS_TYPE_IBSS		  1
	#define NIC_WIFI_BSS_TYPE_ADHOC		  2
	#define NIC_WIFI_BSS_TYPE_AP		  3
#define NIC_WIFI_SUBCMD_STATION_NAME	0x0F000003    
#define NIC_WIFI_SUBCMD_CHANNEL			0x0F000004    
	#define NIC_WIFI_SUBCMD_AUTH_TYPE	0x0F000005
	#define NIC_WIFI_AUTH_TYPE_OPEN		    0
	#define NIC_WIFI_AUTH_TYPE_SHARED_KEY	1
#define NIC_WIFI_SUBCMD_CRYPTO_TYPE		0x0F000006
	#define NIC_WIFI_CRYPTO_TYPE_NONE	  0
	#define NIC_WIFI_CRYPTO_TYPE_WEP	  1
	#define NIC_WIFI_CRYPTO_TYPE_AES	  2
#define NIC_WIFI_SUBCMD_CRYPTO_DATA		0x0F000007
#define NIC_WIFI_SUBCMD_CRYPTO_CFG		0x0F000008
#define NIC_WIFI_SUBCMD_SIGNAL_INFO		0x0F000009    
#define NIC_WIFI_SUBCMD_RTS_THRESH		0x0F00000A    
#define NIC_WIFI_SUBCMD_FRAG_THRESH		0x0F00000B    
#define NIC_WIFI_SUBCMD_SCAN_NETWORK	0x0F00000C
#define	NIC_WIFI_SUBCMD_BSSID			0x0F00000D
#define	NIC_WIFI_SUBCMD_BCM_IOCTL		0x0F00000E
#define NIC_WIFI_SUBCMD_CONFIGURE		0x0FFFFFFF    /* no payload */

#define NIC_WIFI_SUBCMD_MASK			0x0FFFFFFF

typedef	struct {		/* Broadcom ioctl interface */
	_Int32t		cmd;
	_Int32t		len;
	_Uint8t		data [8192];	/* was 4096 */
} nic_wifi_bcm_ioctl_t;

typedef struct {
	_Uint32t	num;	/* Keys are valued 1 thru 4 */
	_Uint32t	length;
	_Uint8t		data[128];
} nic_wifi_wep_key_t;

typedef struct {
	_Uint32t	active_key;    /* 0 to disable, 1-4 to pick active key */
} nic_wifi_wep_cfg_t;

typedef struct {
	_Uint32t	radio_freq;    /* 100's of MHz:    24 is 2.4Ghz */
	_Uint32t	tx_rate;	/* 100's of Kbit/s: 55 is 5.5Mbit/sec */
	_Uint16t	quality;
	_Uint16t	quality_max;
	_Uint16t	signal_level;
	_Uint16t	signal_level_max;
	_Uint16t	noise_level;
	_Uint16t	noise_level_max;
} nic_wifi_signal_info_t;

typedef	struct {
	_Uint8t		macaddr [6];
	_Uint16t	channel;
} nic_wifi_bssid_t;

typedef struct {
	_Uint32t	subcmd;
	_Uint32t	size;
	union {
		_Uint8t			ssid[32];	
		_Uint32t		bss_type;
		_Uint8t			station_name[256];
		_Uint32t		channel;
		_Uint32t		auth_type;
		_Uint32t		crypto_type;
		nic_wifi_wep_key_t	wep_key;
		nic_wifi_wep_cfg_t	wep_cfg;
		nic_wifi_bssid_t	bssid_cfg;
		_Uint32t		rts_thresh;
		_Uint32t		frag_thresh;
		nic_wifi_signal_info_t	signal_info;
		nic_wifi_bcm_ioctl_t	ioctl;
		_Uint8t			_padding[1024];
	} un;
} nic_wifi_dcmd_t;

#define	NIC_CONFIG_REVISION		0

typedef struct _nic_config {
	_Uint32t	revision;	/* Set to NIC_CONFIG_REVISION */
	_Uint32t	flags;		/* See NIC_FLAG_... */

	_Int32t		power_mode;	/* Current power mode (see sys/pm.h) */
	_Uint32t	tx_csum_active;	/* See IFCAP_CSUM_... */
	_Uint32t	rx_csum_active;	/* See IFCAP_CSUM_... */

	_Uint32t	mtu;		/* Maximum packet size that can be transmitted */
	_Uint32t	mru;		/* Maximum packet size that will be accepted from the medium */

	_Uint32t	verbose;	/* Verbosity level */
	_Int32t		lan;		/* 0 -> en0, 1 -> en1 etc. */

	_Uint8t		permanent_address[8];
	_Uint8t		current_address[8];
	_Uint32t	mac_length;

	_Uint32t	connector;	/* See NIC_CONNECTOR_... */
	_Int32t		phy_addr;	/* Address of currently active PHY (-1 if no active PHY) */
	_Uint32t	media;		/* See NIC_MEDIA_... */
	_Int32t		media_rate;	/* Current media rate in KBits/sec (ie: 10000 == 10Mbit); -1 means unknown */
	_Int32t		duplex;		/* -1 means unknown/not applicable */

	_Uint32t	bus_type;	/* See DRVR_BUSTYPE_... */
	_Uint32t	vendor_id;	/* e.g. PCI vendor ID */
	_Uint32t	device_id;	/* e.g. PCI vendor ID */
	_Uint32t	device_index;	/* e.g. PCI index, or slot number */
	_Uint32t	device_revision;
	_Uint32t	serial_number;	/* Device's unique serial ID (0 means undefined) */

	_Uint32t	num_mem_windows;
	_Uint32t	num_io_windows;
	_Uint32t	num_irqs;
	_Uint32t	num_dma_channels;

	_Uint64t	mem_window_base[8];
	_Uint64t	mem_window_size[8];

	_Uint64t	io_window_base[8];
	_Uint64t	io_window_size[8];

	_Uint64t	rom_base;
	_Uint64t	rom_size;

	_Uint32t	irq[8];
	_Uint32t	dma_channel[8];

	_Uint8t		device_description[64];

	_Uint8t		uptype[16];	/* e.g. "en" */
	_Int32t		iftype;		/* See IFT_... from net/if_types.h */

	_Int32t		priority;	/* Interrupt pulse priority */

	_Uint32t	rsvd[32];
} nic_config_t;

/* 802.3 DCMD_IO_NET_MIIPHY structure and defines */

/* PHY addresses on the chips can be from 00 to 0x1F */
#define NIC_MIIPHY_NOPHY		0xFF
#define NIC_MIIPHY_INVALID_REG		0xFE

/*
 * Standard reg_offsets, as defined by 802.3.
 * All registers are 16 bits wide.
 */
#define NIC_MIIPHY_BMCR			0x00 
#define NIC_MIIPHY_BMSR			0x01
#define NIC_MIIPHY_PHYIDR1		0x02
#define NIC_MIIPHY_PHYIDR2		0x03
#define NIC_MIIPHY_ANAR			0x04
#define NIC_MIIPHY_ANLPAR		0x05
#define NIC_MIIPHY_ANER			0x06
#define NIC_MIIPHY_ANNPTR		0x07

/* MII sub commands */
#define NIC_MIIPHY_GETCURRENT_PHY	0x0ABEAD01	/* get the driver's current PHY */
#define NIC_MIIPHY_PHY_SCAN		0x0ABEAD02	/* scans all PHY addresses */
#define NIC_MIIPHY_GET_REG		0x0ABEAD03	/* get reg value for the given PHY */
#define NIC_MIIPHY_SET_REG		0x0ABEAD04	/* set reg value for the given PHY */
#define NIC_MIIPHY_SUBCMD_MASK		0x0FFFFFFF

typedef struct
{
    _Uint32t subcmd;
    _Uint32t phy_addr;		/* Valid range is 0x00 to 0x1F */
    _Uint32t phy_reg_offset;	/* 0x00 to 0x07 are 802.3 standard regs */
				/* Valid range is 0x00 to 0x1F */
    _Uint32t phy_reg_value;	/* Only lower 16 bits are valid */
} nic_miiphy_dcmd_t;

typedef struct
{
    _Uint32t subcmd;             /* private sub command for individual driver */
    _Uint32t cmdlen;             /* the length of the sub command */
    /* variable length for different private sub command */
} nic_private_dcmd_t;

#endif

__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/hardware/devn/public/hw/nicinfo.h $ $Rev: 219612 $" )
