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







#ifndef __NIC_H_INCLUDED
#define __NIC_H_INCLUDED

#ifdef _HW_NICINFO_H_INCLUDED
#error hw/nicinfo.h and sys/nic.h are mutually exclusive (sys/nic.h is obsolete)
#endif

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

__BEGIN_DECLS

#include <sys/types.h>
#include <stdint.h>

#include <sys/cfg.h>

#define NIC_FALSE				0x0
#define NIC_TRUE				0x1

#define NIC_FLAG_PIO			0x0001	/* NIC uses PIO Transfers */
#define NIC_FLAG_DMA			0x0002	/* NIC uses DMA (8237) Transfers */
#define NIC_FLAG_BMSTR			0x0004	/* NIC uses Busmaster Transfers */
#define NIC_FLAG_MMAP			0x0008	/* NIC uses Memory Mapped Transfers */
#define NIC_FLAG_FDX			0x0010	/* NIC supports full duplex operation */
#define NIC_FLAG_BNC			0x0020	/* NIC is using BNC */
#define NIC_FLAG_AUI			0x0040	/* NIC is using AUI */
#define NIC_FLAG_UTP			0x0080	/* NIC is using UTP */
#define NIC_FLAG_FIBRE			0x0100	/* NIC is using FIBRE */
#define NIC_FLAG_MULTICAST		0x0200	/* NIC accepts multicast */
#define NIC_FLAG_PROMISCUOUS	0x0400	/* NIC accepts all frames */
#define NIC_FLAG_BROADCAST		0x0800	/* NIC accepts broadcast frames */
#define NIC_FLAG_WIRELESS       0x1000  /* NIC is wireless */
#define NIC_FLAG_LINK_DOWN      0x2000  /* NIC link is down */

#define NIC_FILTER_MULTICAST		1
#define NIC_FILTER_ALL_MULTICAST	2
#define NIC_FILTER_BROADCAST		4
#define NIC_FILTER_PROMISCIOUS		8
#define NIC_FILTER_PROMISCUOUS		8 /* gkm */

#define NIC_MEDIA_802_3			0x0000
#define NIC_MEDIA_802_5			0x0001
#define NIC_MEDIA_FDDI			0x0002
#define NIC_MEDIA_ATM			0x0003
#define NIC_MEDIA_ARCNET		0x0004
#define NIC_MEDIA_RESERVED		0x0005
#define NIC_MEDIA_CUSTOM		0x0006
#define NIC_MEDIA_802_11        0x0007


/* Physical Layer Device Types */
#define PHY_NOT_INSTALLED		0x0000
#define PHY_INTEL_82553AB		0x0001	/* PHY 100, A or B step */
#define PHY_INTEL_82553C		0x0002	/* PHY 100, C step */
#define PHY_INTEL_82503			0x0003	/* 10Mbps */
#define PHY_NS_83840			0x0004	/* 100BASE-TX, C step */
#define PHY_SEEQ_80C240			0x0005	/* 100BASE-T4 */
#define PHY_SEEQ_80C24			0x0006	/* 10Mbps */
#define PHY_NS_DP83840A			0x000A

typedef uchar_t		mac_addr_t[8];
typedef struct _nic	Nic_t;
typedef void		Nic_Ext_t;

typedef struct _gen_stats {
	ulong_t		medium;
/* ------------------ Mandatory Statistics --------------------------- */
	ulong_t		xmit_ok;
	ulong_t		rcv_ok;
	ulong_t		xmit_error;
	ulong_t		rcv_error;
/* ------------------ Optional Statistics ---------------------------- */
	ulong_t		multicast_xmit;
	ulong_t		multicast_rcv;
	ulong_t		broadcast_xmit;
	ulong_t		broadcast_rcv;
} GenStats_t;

typedef struct _ethernet_stats {
/* ------------------ Mandatory Statistics --------------------------- */
	ulong_t		rcv_alignment_error;
	ulong_t		xmit_collisions;
	ulong_t		rcv_overrun;
	ulong_t		xmit_underrun;
	ulong_t		xmit_crs_lost;
/* ------------------ Optional Statistics ---------------------------- */
	ulong_t		rcv_crc_error;
	ulong_t		rcv_length_error;
	ulong_t		rcv_collisions;
	ulong_t		rcv_dribble;
	ulong_t		xmit_aborted;			/* aborted from collisions */
	ulong_t		xmit_cdh;				/* collision detect heartbeat */
	ulong_t		xmit_window;			/* out of window collision */
	ulong_t		xmit_deferred;
	ulong_t		xmit_jabber;
	ulong_t		xmit_sqe;
	ulong_t		link_failure;
} EthernetStats_t;

typedef struct _tokenring_stats {
/* ------------------ Mandatory Statistics --------------------------- */
	ulong_t		ring_status;
	ulong_t		line_errors;
	ulong_t		lost_frame_errors;
	ulong_t		burst_errors;
	ulong_t		ac_errors;
	ulong_t		abort_delimiters;
	ulong_t		frame_copied_errors;
	ulong_t		frequency_errors;
	ulong_t		token_errors;
	ulong_t		internal_errors;
/* ------------------ Optional Statistics ---------------------------- */
	ulong_t		rcv_overrun;
	ulong_t		xmit_underrun;
	ulong_t		rcv_congestion;
} TokenRingStats_t;

typedef struct _arcnet_stats {
/* ------------------ Mandatory Statistics --------------------------- */
	ulong_t		reconfig;
/* ------------------ Optional Statistics ---------------------------- */
} ArcnetStats_t;

typedef struct _fddi_stats {
	char tmp;
/* ------------------ Mandatory Statistics --------------------------- */
/* ------------------ Optional Statistics ---------------------------- */
} FddiStats_t;

typedef struct _atm_stats {
	char tmp;
/* ------------------ Mandatory Statistics --------------------------- */
/* ------------------ Optional Statistics ---------------------------- */
} AtmStats_t;



/* 
 * A "custom" interface.  Used to pass back arbitrary name/value pairs
 * from drivers that don't fall into the pre-defined categories.
 */

struct _custnic_stats_entry 
{
	char		name[28];
	_uint32		value;
};

typedef struct _custnic_stats 
{
	_uint32		num_used;
	struct		_custnic_stats_entry entry[31];
} CustNicStats_t;


/* 802.11 (aka Wi-Fi) Statistics */
typedef struct _wifi_stats_entry  {
    _uint32       tx_frag;
    _uint32       tx_mcast;
    _uint32       tx_retry;
    _uint32       rx_duplicate;
    _uint32       rx_ack_failure;
    _uint32       rx_frag;
    _uint32       rx_mcast;
    _uint32       rx_fcs_errors;
    _uint32       rx_wep_errors; 
} WiFiStats_t;


typedef struct _net_stats {
	GenStats_t	gstats;
	union {
		EthernetStats_t		estats;
		FddiStats_t			fstats;
		TokenRingStats_t	trstats;
		ArcnetStats_t		arcstats;
		AtmStats_t			atmstats;
        WiFiStats_t         wstats;
		CustNicStats_t		custstats;
		char				bytes[1024];
	}un;
} NetStats_t;

struct _nic {
	Nic_Ext_t		*ext;				/* pointer to adapter specific information */
	uint_t			flags;				/* see NIC_FLAG_... */
	uint_t			filter;
	uint_t			astate;				/* adapter state */
	uint_t			media;
	uint_t			media_rate;			/* in kbits/sec (ie: 10000 == 10Mbit)  */
	uint_t			mtu;
	uint_t			lan;
	uint_t			node;
	Config_Info_t	cfg;
	uint_t			phy;				/* Physical Layer Device */
	uint_t			rsvd[32];
	uint_t			mac_length;
	mac_addr_t		permanent_address;
	mac_addr_t		current_address;
	NetStats_t		nstats;
};

#define NIC_PCI_VENDOR_ID( a )   ( (a)->cfg.Device_ID.DevID & 0xFFFF )
#define NIC_PCI_DEVICE_ID( a )   ( ( (a)->cfg.Device_ID.DevID >> 16 ) & 0xFFFF )
#define NIC_PCI_INDEX( a )       ( (a)->cfg.Device_ID.SerialNum )

/* Used to pass back information via DCMD_IO_NET_TXRX_COUNT */
typedef struct
{
    _uint32 tx_bytes;
    _uint32 rx_bytes;
    _uint32 resv[8];
}  NicTxRxCount_t;

/* typedefs and structures for the new nettrap */

typedef int (*nettrap_detect_func_t)( int *count );

typedef struct
{
        nettrap_detect_func_t  detect_func;
} nettrap_callin_funcs_t;


/*==============================================================================
 *
 * 802.11 (aka WiFi) DCMD_IO_NET_WIFI structure and defines.
 */

/* QSSL subcmd's will always start at 0x0F000000, others below are open */
#define NIC_WIFI_SUBCMD_SSID            0x0F000001    
#define NIC_WIFI_SUBCMD_BSS_TYPE        0x0F000002    
  #define NIC_WIFI_BSS_TYPE_BSS           0
  #define NIC_WIFI_BSS_TYPE_IBSS          1
  #define NIC_WIFI_BSS_TYPE_ADHOC         2
  #define NIC_WIFI_BSS_TYPE_AP            3
#define NIC_WIFI_SUBCMD_STATION_NAME    0x0F000003    
#define NIC_WIFI_SUBCMD_CHANNEL         0x0F000004    
#define NIC_WIFI_SUBCMD_AUTH_TYPE       0x0F000005
  #define NIC_WIFI_AUTH_TYPE_OPEN         0
  #define NIC_WIFI_AUTH_TYPE_SHARED_KEY   1
#define NIC_WIFI_SUBCMD_CRYPTO_TYPE     0x0F000006
  #define NIC_WIFI_CRYPTO_TYPE_NONE       0
  #define NIC_WIFI_CRYPTO_TYPE_WEP        1
  #define NIC_WIFI_CRYPTO_TYPE_AES        2
#define NIC_WIFI_SUBCMD_CRYPTO_DATA     0x0F000007
#define NIC_WIFI_SUBCMD_CRYPTO_CFG      0x0F000008
#define NIC_WIFI_SUBCMD_SIGNAL_INFO     0x0F000009    
#define NIC_WIFI_SUBCMD_RTS_THRESH      0x0F00000A    
#define NIC_WIFI_SUBCMD_FRAG_THRESH     0x0F00000B    
#define NIC_WIFI_SUBCMD_SCAN_NETWORK    0x0F00000C
#define NIC_WIFI_SUBCMD_CONFIGURE       0x0FFFFFFF    /* no payload */

#define NIC_WIFI_SUBCMD_MASK            0x0FFFFFFF


typedef struct
{
    _uint32  num;           /* Keys are valued 1 thru 4 */
    _uint32  length;
    _uint8   data[128];
} nic_wifi_wep_key_t;

typedef struct
{
    _uint32 active_key;    /* 0 to disable, 1-4 to pick active key */
} nic_wifi_wep_cfg_t;

typedef struct
{
    uint32_t radio_freq;    /* 100's of MHz:    24 is 2.4Ghz */
    uint32_t tx_rate;       /* 100's of Kbit/s: 55 is 5.5Mbit/sec */
    uint16_t quality;       
    uint16_t signal_level;  
    uint16_t noise_level;   
} nic_wifi_signal_info_t;

typedef struct
{
    _uint32 subcmd;
    _uint32 size;
    union
    {
        _uint8                   ssid[32];           
        _uint32                  bss_type;
        _uint8                   station_name[256];
        _uint32                  channel;
        _uint32                  auth_type;
        _uint32                  crypto_type;
        nic_wifi_wep_key_t       wep_key;
        nic_wifi_wep_cfg_t       wep_cfg;
        _uint32                  rts_thresh;
        _uint32                  frag_thresh;
        nic_wifi_signal_info_t   signal_info;
        _uint8                   _padding[1024];
    } un;
} nic_wifi_dcmd_t;

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
    _uint32 subcmd;
    _uint32 phy_addr;		/* Valid range is 0x00 to 0x1F */
    _uint32 phy_reg_offset;	/* 0x00 to 0x07 are 802.3 standard regs */
				/* Valid range is 0x00 to 0x1F */
    _uint32 phy_reg_value;	/* Only lower 16 bits are valid */
} nic_miiphy_dcmd_t;

/* Obsolete devctl's */
#define DCMD_IO_NET_NICINFO        __DIOF(_DCMD_NET, 11, Nic_t)
#define DCMD_IO_NET_TXRX_COUNT     __DIOF(_DCMD_NET, 13, NicTxRxCount_t)

__END_DECLS

#endif

__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/hardware/devn/public/sys/nic.h $ $Rev: 219612 $" )
