/*
 * $QNXLicenseC:
 * Copyright 2007, QNX Software Systems. All Rights Reserved.
 *
 * This source code may contain confidential information of QNX Software
 * Systems (QSS) and its licensors.  Any use, reproduction, modification,
 * disclosure, distribution or transfer of this software, or any software
 * that includes or is based upon any of this code, is prohibited unless
 * expressly authorized by QSS by written agreement.  For more information
 * (including whether this source code file has been published) please
 * email licensing@qnx.com. $
*/

#ifndef __MEDIA_OUTPUT_TYPE_H__
#define __MEDIA_OUTPUT_TYPE_H__

#include <stdint.h>


typedef enum
{
  MM_SF_ANALOG_VIDEO               = 0x01,
  MM_SF_UNCOMPRESSED_DIGITAL_AUDIO = 0x02,
  MM_SF_UNCOMPRESSED_DIGITAL_VIDEO = 0x04,
  MM_SF_COMPRESSED_DIGITAL_AUDIO   = 0x08,
  MM_SF_COMPRESSED_DIGITAL_VIDEO   = 0x10,
} MmStreamType_t;

typedef enum
{
  MM_OP_HDMI           = 0x01,  /* A connector following the High-Definition Media Interface (http://www.HDMI.org)                                  */
  MM_OP_TOSLINK        = 0x02,  /* An optical fiber connection system                                                                               */
  MM_OP_DISPLAYPORT    = 0x04,  /* A connector following the DisplayPort digital audio/video interface. (http://www.displayport.org)                */
  MM_OP_DVI            = 0x08,  /* A connector following the Standard Digital Video Interface.  (http://www.ddwg.org/)                              */
  MM_OP_INTERNAL_VIDEO = 0x10,  /* A display that is permanently internally connected to the device (example playbook lcd)                          */
  MM_OP_ANALOG_VIDEO   = 0x20,  /* VGA, SVGA, XGA, DVI Analog, YPrPb, S-Video, consumer RGB, and various non-standardized analog monitor connection */
  MM_OP_ANALOG_AUDIO   = 0x40,  /* A connector for an analog sound reproduction device such as a speaker or headphones                              */
  MM_OP_BLUETOOTH      = 0x80,  /* A radio frequency connector that delivers Audio Content using Bluetooth Audio Profiles: A2DP, Hands Free Profile (HFP), Headset Profile (HSP)  */
  MM_OP_WIRELESSHD     = 0x100, /* A radio frequency connector that delivers Content using WirelessHD ptotocol (http://www.wirelesshd.org)          */
  MM_OP_MIRACAST       = 0x200, /* A peer-to-peer wireless screencast standard formed via Wi-Fi Direct connections in a manner similar to Bluetooth */
} MmOutputPortType_t;

typedef enum
{
  MM_CP_SECURE_DRIVER   = 0x01,  /* cannot be upgraded by end user, replaced with his own version of it        */
  MM_CP_HDCP            = 0x02,  /* High-bandwidth Digital Content Protection                                  */
  MM_CP_DTCP            = 0x04,  /* Digital Transmission Content Protection                                    */
  MM_CP_ACP             = 0x08,  /* Macrovision ACP protection: sinfo set to 01-> ASP1, 02 -> ASP2, 03 -> ASP3 */
  MM_CP_CGMS            = 0x10,  /* Copy Generation Management System - Analog (CGMS-A) Television Signals     */
  MM_CP_SCMS            = 0x20,  /* Serial Copy Management System  Digital Audio Output                        */
  MM_CP_PVM_OPM         = 0x40,  /* Protected Video Path - Output Protection Management (PVP-OPM)              */
} MmContentProtectionType_t;

typedef struct MmContentProtection
{
  MmContentProtectionType_t  cpt;
  void                       *sinfo;  /* side info, cpt specific */
} MmContentProtection_t;

typedef struct MmOutputProtectionLevel
{
  MmStreamType_t        stype;
  MmOutputPortType_t    ptype;
  MmContentProtection_t content_protection;
  int32_t               ret;
} MmOutputProtectionLevel_t;

typedef struct MmOutputProtectionEventInfo
{
  uint32_t                   nstreams;
  MmOutputProtectionLevel_t  *opl;
  int32_t                    ret;
} MmOutputProtectionEventInfo_t;


typedef struct MmDTCPSideInfo
{
  uint8_t epn;
  uint8_t cci;
  uint8_t reserve[2];
} MmDTCPSideInfo_t;

typedef struct MmCGMSSideInfo
{
  uint8_t cgmsa;
  uint8_t reserve[3];
} MmCGMSSideInfo_t;

typedef struct MmSCMSSideInfo
{
  uint16_t     ctrl_bits;
  uint16_t     reserve;
} MmSCMSSideInfo_t;

typedef struct MmBluetoothSideInfo
{
  uint32_t sample_rate;      /* in Hz                                       */
  uint32_t bitrate;          /* data bitrate in bits /seconds               */
  uint32_t bits_per_sample;  /* bit depth of a sample (ex: 16)              */
  uint32_t max_bandwidth;    /* in bits per seconds                         */
  uint32_t nstreams;         /* number of simultaneous identicals streams   */
} MmBluetoothSideInfo_t;

#endif


#include <sys/srcversion.h>
__SRCVERSION( "$URL$ $Rev$" )
