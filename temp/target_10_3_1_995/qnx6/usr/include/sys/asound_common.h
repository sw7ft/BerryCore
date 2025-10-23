/*
 * $QNXLicenseC:
 * Copyright 2012, QNX Software Systems.
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

#ifndef __ASOUND_COMMON_H__
#define __ASOUND_COMMON_H__

#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <inttypes.h>


#if defined(__LITTLEENDIAN__)
#define SND_LITTLE_ENDIAN
#elif defined(__BIGENDIAN__)
#define SND_BIG_ENDIAN
#endif


#define		SND_PROTOCOL_VERSION(t,a,b,c)	(t<<24|a<<16|b<<8|c)
#define		SND_PROTOCOL_INCOMPATIBLE(a,b)	((a)!=(b))




/*****************/
/*****************/
/***  SWITCH   ***/
/*****************/
/*****************/

#define SND_SW_TYPE_BOOLEAN			1
#define SND_SW_TYPE_BYTE			2
#define SND_SW_TYPE_WORD			3
#define SND_SW_TYPE_DWORD			4
#define SND_SW_TYPE_LIST			10
#define SND_SW_TYPE_STRING_11		100+11

#define SND_SW_SUBTYPE_DEC			0
#define SND_SW_SUBTYPE_HEXA			1

typedef struct snd_switch_list_item
{
	char		name[32];
	uint8_t		reserved[128];      /* must be filled with zero */
}		snd_switch_list_item_t;


typedef struct snd_switch_list
{
	int32_t		iface;
	int32_t		device;
	int32_t		channel;
	int32_t		switches_size;
	int32_t		switches;
	int32_t		switches_over;
	snd_switch_list_item_t *pswitches;
	void		*pzero;				/* align pointers on 64-bits --> point to NULL */
	uint8_t	 	reserved[128];      /* must be filled with zero */
}		snd_switch_list_t;

typedef struct snd_switch
{
	int32_t iface;
	int32_t device;
	int32_t channel;
	char	name[36];
	uint32_t type;
	uint32_t subtype;
	uint32_t zero[2];
	union
	{
		uint32_t enable:1;

		struct
		{
			uint8_t data;
			uint8_t low;
			uint8_t high;
		}
		byte;

		struct
		{
			uint16_t data;
			uint16_t low;
			uint16_t high;
		}
		word;

		struct
		{
			uint32_t data;
			uint32_t low;
			uint32_t high;
		}
		dword;

		struct
		{
			uint32_t data;
			uint32_t items[30];
			uint32_t items_cnt;
		}
		list;

		struct
		{
			uint8_t selection;
			char	strings[11][11];
			uint8_t strings_cnt;
		}
		string_11;

		uint8_t raw[32];
		uint8_t reserved[128];      /* must be filled with zero */
	}
	value;
	uint8_t reserved[128];      /* must be filled with zero */
}
snd_switch_t;



/*****************/
/*****************/
/***  CONTROL  ***/
/*****************/
/*****************/

#define		SND_CTL_VERSION		SND_PROTOCOL_VERSION('C',3,0,0)


#define 	SND_CTL_SW_JOYSTICK		"joystick"
#define 	SND_CTL_SW_JOYSTICK_ADDRESS	"joystick port address"


typedef struct snd_ctl_hw_info
{
	uint32_t	type;
	uint32_t	hwdepdevs;
	uint32_t	pcmdevs;
	uint32_t	mixerdevs;
	uint32_t	mididevs;
	uint32_t	timerdevs;
	char		id[16];
	char		abbreviation[16];
	char		name[32];
	char		longname[80];
	uint8_t	  	reserved[128];      /* must be filled with zero */
}		snd_ctl_hw_info_t;



#define SND_CTL_IFACE_CONTROL			100
#define SND_CTL_IFACE_MIXER				200
#define SND_CTL_IFACE_PCM_PLAYBACK		300
#define SND_CTL_IFACE_PCM_CAPTURE		301
#define SND_CTL_IFACE_RAWMIDI_OUTPUT	400
#define SND_CTL_IFACE_RAWMIDI_INPUT		401

#define		SND_CTL_READ_REBUILD		120
#define		SND_CTL_READ_SWITCH_VALUE	121
#define		SND_CTL_READ_SWITCH_CHANGE	122
#define		SND_CTL_READ_SWITCH_ADD		123
#define		SND_CTL_READ_SWITCH_REMOVE	124

typedef struct snd_ctl_read_s
{
	int32_t	cmd;
	uint8_t	zero[4];						/* alignment -- zero fill */
	union
	{
		struct
		{
			int32_t		iface;
			uint8_t		zero[4];			/* alignment -- zero fill */
			snd_switch_list_item_t switem;
			uint8_t		reserved[128];      /* must be filled with zero */
		}		sw;
		uint8_t		reserved[128];      /* must be filled with zero */
	}		data;
	uint8_t		reserved[128];      /* must be filled with zero */
}		snd_ctl_read_t;


#define		SND_CTL_IOCTL_DRVR_VER				_IOR ('C', 0x00, int)
#define		SND_CTL_IOCTL_PVERSION				_IOR ('C', 0x10, int)
#define		SND_CTL_IOCTL_HW_INFO				_IOR ('C', 0x20, snd_ctl_hw_info_t)
#define		SND_CTL_IOCTL_SWITCH_LIST			_IOWR('C', 0x30, snd_switch_list_t)
#define		SND_CTL_IOCTL_SWITCH_READ			_IOWR('C', 0x31, snd_switch_t)
#define		SND_CTL_IOCTL_SWITCH_WRITE			_IOWR('C', 0x32, snd_switch_t)
#define		SND_CTL_IOCTL_MIXER_DEVICE			_IOW ('C', 0x40, int)
#define		SND_CTL_IOCTL_MIXER_INFO			_IOR ('C', 0x41, snd_mixer_info_t)
#define		SND_CTL_IOCTL_MIXER_SWITCH_LIST		_IOWR('C', 0x42, snd_switch_list_t)
#define		SND_CTL_IOCTL_MIXER_SWITCH_READ		_IOWR('C', 0x43, snd_switch_t)
#define		SND_CTL_IOCTL_MIXER_SWITCH_WRITE	_IOWR('C', 0x44, snd_switch_t)
#define		SND_CTL_IOCTL_PCM_CHANNEL			_IOW ('C', 0x50, int)
#define		SND_CTL_IOCTL_PCM_CHANNEL_INFO		_IOR ('C', 0x51, snd_pcm_channel_info_t)
#define		SND_CTL_IOCTL_PCM_DEVICE			_IOW ('C', 0x52, int)
#define		SND_CTL_IOCTL_PCM_INFO				_IOR ('C', 0x53, snd_pcm_info_t)
#define		SND_CTL_IOCTL_PCM_PREFER_SUBDEVICE	_IOW ('C', 0x54, int)
#define		SND_CTL_IOCTL_PCM_SUBDEVICE			_IOW ('C', 0x55, int)
#define		SND_CTL_IOCTL_PCM_SWITCH_LIST		_IOWR('C', 0x56, snd_switch_list_t)
#define		SND_CTL_IOCTL_PCM_SWITCH_READ		_IOWR('C', 0x57, snd_switch_t)
#define		SND_CTL_IOCTL_PCM_SWITCH_WRITE		_IOWR('C', 0x58, snd_switch_t)
#define		SND_CTL_IOCTL_RAWMIDI_CHANNEL		_IOW ('C', 0x60, int)
#define		SND_CTL_IOCTL_RAWMIDI_DEVICE		_IOW ('C', 0x61, int)
#define		SND_CTL_IOCTL_RAWMIDI_INFO			_IOR ('C', 0x62, snd_rawmidi_info_t)
#define		SND_CTL_IOCTL_RAWMIDI_SWITCH_LIST	_IOWR('C', 0x63, snd_switch_list_t)
#define		SND_CTL_IOCTL_RAWMIDI_SWITCH_READ	_IOWR('C', 0x64, snd_switch_t)
#define		SND_CTL_IOCTL_RAWMIDI_SWITCH_WRITE	_IOWR('C', 0x65, snd_switch_t)



/*****************/
/*****************/
/***   MIXER   ***/
/*****************/
/*****************/

#define		SND_MIXER_VERSION		SND_PROTOCOL_VERSION('M',3,0,0)

#define		SND_TYPE_SPEAKER_OUT				0
#define		SND_TYPE_HEADPHONE_OUT				1
#define		SND_TYPE_LINE_OUT					2
#define		SND_TYPE_BLUETOOTH_OUT				3
#define		SND_TYPE_HDMI_OUT					4
#define		SND_TYPE_TOSLINK_OUT				5
#define		SND_TYPE_MIRACAST_OUT				6
#define		SND_TYPE_MIRRORLINK_OUT				7
#define		SND_TYPE_AUDIOSHARE_OUT				8

/* PLAYBACK_GROUP_NAMES */
#define		SND_MIXER_AUX_OUT					"Aux"
#define		SND_MIXER_CD_OUT					"CD"
#define		SND_MIXER_CENTER_OUT				"Center"
#define		SND_MIXER_DAC_OUT					"DAC"
#define		SND_MIXER_DSP_OUT					"DSP"
#define		SND_MIXER_FM_OUT					"FM"
#define		SND_MIXER_FRONT_OUT					"Front"
#define		SND_MIXER_HEADPHONE_OUT				"Headphone"
#define		SND_MIXER_LINE_OUT					"Line"
#define		SND_MIXER_MASTER_OUT				"Master"
#define		SND_MIXER_MASTER_DIGITAL_OUT		"Master Digital"
#define		SND_MIXER_MASTER_MONO_OUT			"Master Mono"
#define		SND_MIXER_MIC_OUT					"Mic"
#define		SND_MIXER_MONO_OUT					"Mono"
#define		SND_MIXER_PCM_OUT					"PCM"
#define		SND_MIXER_PCM_OUT_SUBCHN			"PCM Subchannel"
#define		SND_MIXER_PCM_OUT_MIXER				"PCM Mixer"
#define		SND_MIXER_PCM_OUT_UNIFIED			"PCM Unified"
#define		SND_MIXER_PHONE_OUT					"Phone"
#define		SND_MIXER_RADIO_OUT					"Radio"
#define		SND_MIXER_REAR_OUT					"Rear"
#define		SND_MIXER_SIDE_OUT					"Side Surr"
#define		SND_MIXER_SPDIF_OUT					"S/PDIF"
#define		SND_MIXER_SPEAKER_OUT				"PC Speaker"
#define		SND_MIXER_SURROUND_OUT				"Surround"
#define		SND_MIXER_SYNTHESIZER_OUT			"Synth"
#define		SND_MIXER_VIDEO_OUT					"Video"
#define		SND_MIXER_WOOFER_OUT				"Woofer"

/* CAPTURE_GROUP_NAMES */
#define		SND_MIXER_ADC_IN					"ADC In"
#define		SND_MIXER_AUX_IN					"Aux In"
#define		SND_MIXER_CD_IN						"CD In"
#define		SND_MIXER_DSP_IN					"DSP In"
#define		SND_MIXER_FM_IN						"FM In"
#define		SND_MIXER_LINE_IN					"Line In"
#define		SND_MIXER_MIC_IN					"Mic In"
#define		SND_MIXER_MONO_IN					"Mono In"
#define		SND_MIXER_PCM_IN					"PCM In"
#define		SND_MIXER_PCM_IN_SUBCHN				"PCM In Subchannel"
#define		SND_MIXER_PHONE_IN					"Phone In"
#define		SND_MIXER_RADIO_IN					"Radio In"
#define		SND_MIXER_SPDIF_IN					"S/PDIF In"
#define		SND_MIXER_SYNTHESIZER_IN			"Synth In"
#define		SND_MIXER_VIDEO_IN					"Video In"

#if 1 /* LEGACY GROUP_NAMES from GPL ALSA 0.5.x (DO NOT USE) */
#define		SND_MIXER_IN_AUX					SND_MIXER_AUX_OUT
#define		SND_MIXER_IN_CD						SND_MIXER_CD_OUT
#define		SND_MIXER_IN_CENTER					SND_MIXER_CENTER_OUT
#define		SND_MIXER_IN_DAC					SND_MIXER_DAC_OUT
#define		SND_MIXER_IN_DSP					SND_MIXER_DSP_OUT
#define		SND_MIXER_IN_FM						SND_MIXER_FM_OUT
#define		SND_MIXER_IN_LINE					SND_MIXER_LINE_OUT
#define		SND_MIXER_IN_MIC					SND_MIXER_MIC_OUT
#define		SND_MIXER_IN_MONO					SND_MIXER_MONO_OUT
#define		SND_MIXER_IN_PCM					SND_MIXER_PCM_OUT
#define		SND_MIXER_IN_PCM_SUBCHN				SND_MIXER_PCM_OUT_SUBCHN
#define		SND_MIXER_IN_PHONE					SND_MIXER_PHONE_OUT
#define		SND_MIXER_IN_RADIO					SND_MIXER_RADIO_OUT
#define		SND_MIXER_IN_SPDIF					SND_MIXER_SPDIF_OUT
#define		SND_MIXER_IN_SPEAKER				SND_MIXER_SPEAKER_OUT
#define		SND_MIXER_IN_SURROUND				SND_MIXER_SURROUND_OUT
#define		SND_MIXER_IN_SYNTHESIZER			SND_MIXER_SYNTHESIZER_OUT
#define		SND_MIXER_IN_VIDEO					SND_MIXER_VIDEO_OUT
#define		SND_MIXER_IN_WOOFER					SND_MIXER_WOOFER_OUT

#define		SND_MIXER_OUT_CENTER				SND_MIXER_CENTER_OUT
#define		SND_MIXER_OUT_DSP					SND_MIXER_DSP_OUT
#define		SND_MIXER_OUT_HEADPHONE				SND_MIXER_HEADPHONE_OUT
#define		SND_MIXER_OUT_MASTER				SND_MIXER_MASTER_OUT
#define		SND_MIXER_OUT_MASTER_DIGITAL		SND_MIXER_MASTER_DIGITAL_OUT
#define		SND_MIXER_OUT_MASTER_MONO			SND_MIXER_MASTER_MONO_OUT
#define		SND_MIXER_OUT_PHONE					SND_MIXER_PHONE_OUT
#define		SND_MIXER_OUT_SURROUND				SND_MIXER_SURROUND_OUT
#define		SND_MIXER_OUT_WOOFER				SND_MIXER_WOOFER_OUT
#endif

/* ELEMENT_NAMES */
#define 	SND_MIXER_ELEMENT_ADC				"Analog Digital Converter"
#define 	SND_MIXER_ELEMENT_CAPTURE			"Capture"
#define 	SND_MIXER_ELEMENT_DAC				"Digital Analog Converter"
#define 	SND_MIXER_ELEMENT_PLAYBACK			"Playback"
#define 	SND_MIXER_ELEMENT_DIGITAL_ACCU		"Digital Accumulator"
#define 	SND_MIXER_ELEMENT_INPUT_ACCU		"Input Accumulator"
#define 	SND_MIXER_ELEMENT_MONO_IN_ACCU		"Mono In Accumulator"
#define 	SND_MIXER_ELEMENT_MONO_OUT_ACCU		"Mono Out Accumulator"
#define 	SND_MIXER_ELEMENT_OUTPUT_ACCU		"Output Accumulator"
#define 	SND_MIXER_ELEMENT_INPUT_MUX			"Input MUX"
#define 	SND_MIXER_ELEMENT_TONE_CONTROL		"Tone Control"

/* SWITCH NAMES */
#define 	SND_MIXER_SW_MIC_BOOST				"Mic Gain Boost"
#define 	SND_MIXER_SW_SIM_STEREO				"Simulated Stereo Enhancement"
#define 	SND_MIXER_SW_LOUDNESS				"Loudness (Bass Boost)"
#define 	SND_MIXER_SW_IEC958_INPUT			"IEC958 (S/PDIF) Input"
#define 	SND_MIXER_SW_IEC958_OUTPUT			"IEC958 (S/PDIF) Output"
#define    SND_MIXER_SW_OUTPUT_ACQUIRE_PREFIX  "(P)"
#define    SND_MIXER_SW_OUTPUT_ACQUIRE         SND_MIXER_SW_OUTPUT_ACQUIRE_PREFIX"%s"
#define    SND_MIXER_SW_INPUT_ACQUIRE_PREFIX   "(C)"
#define    SND_MIXER_SW_INPUT_ACQUIRE          SND_MIXER_SW_INPUT_ACQUIRE_PREFIX"%s"

/* GROUP NAMES */
#define		SND_MIXER_GRP_ANALOG_LOOPBACK		"Analog Loopback"
#define		SND_MIXER_GRP_BASS					"Bass"
#define		SND_MIXER_GRP_DIGITAL_LOOPBACK		"Digital Loopback"
#define		SND_MIXER_GRP_EFFECT				"Effect"
#define		SND_MIXER_GRP_EFFECT_3D				"3D Effect"
#define		SND_MIXER_GRP_EQUALIZER				"Equalizer"
#define		SND_MIXER_GRP_FADER					"Fader"
#define		SND_MIXER_GRP_IGAIN					"Input Gain"
#define		SND_MIXER_GRP_MIC_GAIN				"Mic Gain"
#define		SND_MIXER_GRP_OGAIN					"Output Gain"
#define		SND_MIXER_GRP_TREBLE				"Treble"


#define 	SND_MIXER_OSS_ALTPCM			1
#define 	SND_MIXER_OSS_BASS				2
#define 	SND_MIXER_OSS_CD				3
#define 	SND_MIXER_OSS_DIGITAL1			4
#define 	SND_MIXER_OSS_IGAIN				5
#define 	SND_MIXER_OSS_LINE				6
#define 	SND_MIXER_OSS_LINE1				7
#define 	SND_MIXER_OSS_LINE2				8
#define 	SND_MIXER_OSS_LINE3				9
#define 	SND_MIXER_OSS_MIC				10
#define 	SND_MIXER_OSS_OGAIN				11
#define 	SND_MIXER_OSS_PCM				12
#define 	SND_MIXER_OSS_PHONEIN			13
#define 	SND_MIXER_OSS_PHONEOUT			14
#define 	SND_MIXER_OSS_SPEAKER			15
#define 	SND_MIXER_OSS_SYNTH				16
#define 	SND_MIXER_OSS_TREBLE			17
#define 	SND_MIXER_OSS_UNKNOWN			18
#define 	SND_MIXER_OSS_VIDEO				19
#define 	SND_MIXER_OSS_VOLUME			20


#define		SND_MIXER_ETYPE_INPUT			100
#define		SND_MIXER_ETYPE_ADC				101
#define		SND_MIXER_ETYPE_CAPTURE1		102
#define		SND_MIXER_ETYPE_CAPTURE2		103
#define		SND_MIXER_ETYPE_OUTPUT			104
#define		SND_MIXER_ETYPE_DAC				105
#define		SND_MIXER_ETYPE_PLAYBACK1		106
#define		SND_MIXER_ETYPE_PLAYBACK2		107
#define		SND_MIXER_ETYPE_SWITCH1			200
#define		SND_MIXER_ETYPE_SWITCH2			201
#define		SND_MIXER_ETYPE_SWITCH3			202
#define		SND_MIXER_ETYPE_VOLUME1			203
#define		SND_MIXER_ETYPE_VOLUME2			204
#define		SND_MIXER_ETYPE_ACCU1			205
#define		SND_MIXER_ETYPE_ACCU2			206
#define		SND_MIXER_ETYPE_ACCU3			207
#define		SND_MIXER_ETYPE_MUX1			208
#define		SND_MIXER_ETYPE_MUX2			209
#define		SND_MIXER_ETYPE_TONE_CONTROL1	210
#define		SND_MIXER_ETYPE_3D_EFFECT1		211
#define		SND_MIXER_ETYPE_EQUALIZER1		212
#define		SND_MIXER_ETYPE_PAN_CONTROL1	213
#define		SND_MIXER_ETYPE_PRE_EFFECT1		214


#define		SND_MIXER_VOICE_UNUSED			0
#define 	SND_MIXER_VOICE_MONO			1
#define 	SND_MIXER_VOICE_LEFT			2
#define 	SND_MIXER_VOICE_RIGHT			3
#define 	SND_MIXER_VOICE_CENTER			4
#define 	SND_MIXER_VOICE_REAR_LEFT		5
#define 	SND_MIXER_VOICE_REAR_RIGHT		6
#define 	SND_MIXER_VOICE_WOOFER			7
#define 	SND_MIXER_VOICE_SURR_LEFT		8
#define 	SND_MIXER_VOICE_SURR_RIGHT		9


typedef struct
{
	uint16_t  voice:15, vindex:1;
	uint8_t	 	reserved[124];
}		snd_mixer_voice_t;


typedef struct
{
	int32_t		type;
	char		name[36];
	int32_t		index;
	uint8_t	 	reserved[120];			/* must be filled with zero */
	int32_t		weight;					/* Reserved used for internal sorting oprations */
}		snd_mixer_eid_t;


#define 	SND_MIXER_EIO_DIGITAL		(0x0)

typedef struct snd_mixer_element_io_info
{
	uint32_t		attrib;
	int32_t			voices, voices_over, voices_size;
	snd_mixer_voice_t 	*pvoices;
	void			*pzero;				/* align pointers on 64-bits --> point to NULL */
	uint8_t			reserved[128];		/* must be filled with zero */
}		snd_mixer_element_io_info;


typedef struct snd_mixer_element_pcm1_info
{
	int32_t		devices, devices_over, devices_size;
	uint8_t		zero[4];				/* align on 64-bits */
	int32_t		*pdevices;
	void		*pzero;					/* align pointers on 64-bits --> point to NULL */
	uint8_t		reserved[128];			/* must be filled with zero */
}		snd_mixer_element_pcm1_info;


typedef struct snd_mixer_element_pcm2_info
{
	int32_t		device, subdevice;
	uint8_t	 	reserved[128];			/* must be filled with zero */
}		snd_mixer_element_pcm2_info;


typedef struct snd_mixer_element_converter_info
{
	uint32_t	resolution;
	uint8_t	 	reserved[124];			/* must be filled with zero */
}		snd_mixer_element_converter_info;


#define 	SND_SW_TYPE_BOOLEAN		1	/* 0 or 1 (enable) */

typedef struct snd_mixer_element_switch1
{
	int32_t		sw, sw_over, sw_size;
	uint8_t		zero[4];				/* align on 64-bits */
	uint32_t	*psw;
	void		*pzero;					/* align pointers on 64-bits --> point to NULL */
	uint8_t	 	reserved[128];			/* must be filled with zero */
}		snd_mixer_element_switch1;


typedef struct snd_mixer_element_switch2
{
	uint32_t	sw:1;
	uint8_t	 	reserved[124];			/* must be filled with zero */
}		snd_mixer_element_switch2;



#define 	SND_MIXER_SWITCH3_FULL_FEATURED				1
#define 	SND_MIXER_SWITCH3_ALWAYS_DESTINATION		2
#define 	SND_MIXER_SWITCH3_ALWAYS_ONE_DESTINATION	3
#define 	SND_MIXER_SWITCH3_ONE_DESTINATION			4

typedef struct snd_mixer_element_switch3_info
{
	uint32_t			type;
	int32_t				voices, voices_over, voices_size;
	snd_mixer_voice_t 	*pvoices;
	void				*pzero;			/* align pointers on 64-bits --> point to NULL */
	uint8_t	 			reserved[128];	/* must be filled with zero */
}		snd_mixer_element_switch3_info;

typedef struct snd_mixer_element_switch3
{
	int32_t				rsw, rsw_over, rsw_size;
	int32_t				zero[3];
	uint32_t			*prsw;
	void				*pzero;			/* align pointers on 64-bits --> point to NULL */
	uint8_t	 			reserved[128];	/* must be filled with zero */
}		snd_mixer_element_switch3;


typedef struct snd_mixer_element_volume1_range
{
	int32_t		min, max;
	int32_t		min_dB, max_dB;
	uint8_t	 	reserved[128];			/* must be filled with zero */
}		snd_mixer_element_volume1_range_t;

typedef struct snd_mixer_element_volume1_info
{
	int32_t		range, range_over, range_size;
	uint8_t		zero[4];				/* alignment -- zero fill */
	struct snd_mixer_element_volume1_range *prange;
	uint8_t	 	reserved[128];			/* must be filled with zero */
}		snd_mixer_element_volume1_info;

typedef struct snd_mixer_element_volume1
{
	int32_t		voices, voices_over, voices_size;
	uint8_t		zero[4];				/* align on 64-bits */
	uint32_t	*pvoices;
	void		*pzero;					/* align pointers on 64-bits --> point to NULL */
	uint8_t	 	reserved[128];			/* must be filled with zero */
}		snd_mixer_element_volume1;


typedef struct snd_mixer_element_volume2_range
{
	uint8_t	 	reserved[128];			/* must be filled with zero */
}		snd_mixer_element_volume2_range_t;

typedef struct snd_mixer_element_volume2_info
{
	int32_t				svoices, svoices_over, svoices_size;
	int32_t				range, range_over, range_size;
	snd_mixer_voice_t 	*psvoices;
	struct snd_mixer_element_volume2_range *prange;
	uint8_t	 			reserved[128];	/* must be filled with zero */
}		snd_mixer_element_volume2_info;

typedef struct snd_mixer_element_volume2
{
	int32_t		avoices, avoices_over, avoices_size;
	uint8_t		zero[4];				/* alignment -- zero fill */
	int32_t		*pavoices;
	void		*pzero;					/* align pointers on 64-bits --> point to NULL */
	uint8_t	 	reserved[128];			/* must be filled with zero */
}		snd_mixer_element_volume2;


typedef struct snd_mixer_element_accu1_info
{
	int32_t		attenuation;
	uint8_t	 	reserved[124];			/* must be filled with zero */
}		snd_mixer_element_accu1_info;


typedef struct snd_mixer_element_accu2_info
{
	int32_t		attenuation;
	uint8_t	 	reserved[124];			/* must be filled with zero */
}		snd_mixer_element_accu2_info;


typedef struct snd_mixer_element_accu3_range
{
	int32_t		min, max;
	int32_t		min_dB, max_dB;
	uint8_t	 	reserved[128];			/* must be filled with zero */
}		snd_mixer_element_accu3_range_t;

typedef struct snd_mixer_element_accu3_info
{
	int32_t		range, range_over, range_size;
	uint8_t		zero[4];				/* alignment -- zero fill */
	struct snd_mixer_element_accu3_range *prange;
	void		*pzero;					/* align pointers on 64-bits --> point to NULL */
	uint8_t	 	reserved[128];	  		/* must be filled with zero */
}		snd_mixer_element_accu3_info;

typedef struct snd_mixer_element_accu3
{
	int32_t		voices, voices_over, voices_size;
	uint8_t		zero[4];				/* alignment -- zero fill */
	int32_t		*pvoices;
	void		*pzero;					/* align pointers on 64-bits --> point to NULL */
	uint8_t	 	reserved[128];			/* must be filled with zero */
}		snd_mixer_element_accu3;


#define 	SND_MIXER_MUX1_NONE		(0x1)

typedef struct snd_mixer_element_mux1_info
{
	uint32_t		attrib;
	uint8_t	 	reserved[124];	  		/* must be filled with zero */
}		snd_mixer_element_mux1_info;

typedef struct snd_mixer_element_mux1
{
	int32_t		output, output_over, output_size;
	uint8_t		zero[4];				/* alignment -- zero fill */
	snd_mixer_eid_t	*poutput;
	void		*pzero;					/* align pointers on 64-bits --> point to NULL */
	uint8_t		reserved[128];	  		/* must be filled with zero */
}		snd_mixer_element_mux1;


#define 	SND_MIXER_MUX2_NONE	(0x1)

typedef struct snd_mixer_element_mux2_info
{
	uint32_t		attrib;
	uint8_t		reserved[124];			/* must be filled with zero */
}		snd_mixer_element_mux2_info;

typedef struct snd_mixer_element_mux2
{
	snd_mixer_eid_t output;
	uint8_t		reserved[128];			/* must be filled with zero */
}		snd_mixer_element_mux2;


#define 	SND_MIXER_TC1_SW		(0x1)
#define 	SND_MIXER_TC1_BASS		(0x2)
#define 	SND_MIXER_TC1_TREBLE	(0x4)

typedef struct snd_mixer_element_tone_control1_info
{
	uint32_t	tc;
	int32_t		min_bass, max_bass;
	int32_t		min_bass_dB, max_bass_dB;
	int32_t		min_treble, max_treble;
	int32_t		min_treble_dB, max_treble_dB;
	uint8_t		reserved[124];			/* must be filled with zero */
}		snd_mixer_element_tone_control1_info;

typedef struct snd_mixer_element_tone_control1
{
	uint32_t	tc;
	uint32_t	sw:1;
	int32_t		treble;
	int32_t		bass;
	uint8_t		reserved[128];			/* must be filled with zero */
}		snd_mixer_element_tone_control1;


#define 	SND_MIXER_EFF1_SW			(1<<0)
#define 	SND_MIXER_EFF1_MONO_SW		(1<<1)
#define 	SND_MIXER_EFF1_WIDE			(1<<2)
#define 	SND_MIXER_EFF1_VOLUME		(1<<3)
#define 	SND_MIXER_EFF1_CENTER		(1<<4)
#define 	SND_MIXER_EFF1_SPACE		(1<<5)
#define 	SND_MIXER_EFF1_DEPTH		(1<<6)
#define 	SND_MIXER_EFF1_DELAY		(1<<7)
#define 	SND_MIXER_EFF1_FEEDBACK		(1<<8)
#define 	SND_MIXER_EFF1_DEPTH_REAR	(1<<9)

typedef struct snd_mixer_element_3d_effect1_info
{
	uint32_t	effect;
	int32_t		min_depth, max_depth;
	int32_t		min_depth_rear, max_depth_rear;
	int32_t		min_wide, max_wide;
	int32_t		min_center, max_center;
	int32_t		min_volume, max_volume;
	int32_t		min_space, max_space;
	int32_t		min_delay, max_delay;
	int32_t		min_feedback, max_feedback;
	uint8_t		reserved[124];			/* must be filled with zero */
}		snd_mixer_element_3d_effect1_info;

typedef struct snd_mixer_element_3d_effect1
{
	uint32_t	effect;
	uint32_t	sw:1;
	uint32_t	mono_sw:1;
	int32_t		depth;
	int32_t		depth_rear;
	int32_t		wide;
	int32_t		center;
	int32_t		volume;
	int32_t		space;
	int32_t		delay;
	int32_t		feedback;
	uint8_t		reserved[124];			/* must be filled with zero */
}		snd_mixer_element_3d_effect1;

#define 	SND_MIXER_PAN_LEFT_RIGHT	1
#define 	SND_MIXER_PAN_FRONT_REAR	2
#define 	SND_MIXER_PAN_BOTTOM_UP		3

typedef struct snd_mixer_element_pan_control1_range
{
	int32_t		pan_type;
	int32_t		min, max;
	int32_t		min_dB, max_dB;
	uint8_t		reserved[124];			/* must be filled with zero */
}		snd_mixer_element_pan_control1_range_t;

typedef struct snd_mixer_element_pan_control1_info
{
	int32_t		range, range_over, range_size;
	uint8_t		zero[4];				/* alignment -- zero fill */
	struct snd_mixer_element_pan_control1_range *prange;
	void		*pzero;					/* align pointers on 64-bits --> point to NULL */
	uint8_t		reserved[128];	  		/* must be filled with zero */
}		snd_mixer_element_pan_control1_info;

typedef struct snd_mixer_element_pan_control1
{
	int32_t		pan, pan_over, pan_size;
	uint8_t		zero[4];				/* alignment -- zero fill */
	int32_t		*ppan;
	void		*pzero;					/* align pointers on 64-bits --> point to NULL */
	uint8_t		reserved[128];	  		/* must be filled with zero */
}		snd_mixer_element_pan_control1;


typedef struct snd_mixer_element_pre_effect1_info_item
{
	uint8_t		reserved[128];	  		/* must be filled with zero */
}		snd_mixer_element_pre_effect1_info_item_t;

typedef struct snd_mixer_element_pre_effect1_info_parameter
{
	uint8_t		reserved[128];			/* must be filled with zero */
}		snd_mixer_element_pre_effect1_info_parameter_t;

typedef struct snd_mixer_element_pre_effect1_info
{
	int32_t		items, items_over, items_size;
	int32_t		parameters, parameters_over, parameters_size;
	struct snd_mixer_element_pre_effect1_info_item *pitems;
	struct snd_mixer_element_pre_effect1_info_parameter *pparameters;
	uint8_t		reserved[128];			/* must be filled with zero */
}		snd_mixer_element_pre_effect1_info;

typedef struct snd_mixer_element_pre_effect1
{
	int32_t		item;
	int32_t		parameters, parameters_over, parameters_size;
	int32_t		*pparameters;
	void		*pzero;					/* align pointers on 64-bits --> point to NULL */
	uint8_t		reserved[128];			/* must be filled with zero */
}		snd_mixer_element_pre_effect1;


typedef struct snd_mixer_element_info
{
	snd_mixer_eid_t eid;
	union
	{
		snd_mixer_element_io_info 				io;
		snd_mixer_element_pcm1_info 			pcm1;
		snd_mixer_element_pcm2_info 			pcm2;
		snd_mixer_element_converter_info 		converter;
		snd_mixer_element_switch3_info 			switch3;
		snd_mixer_element_volume1_info 			volume1;
		snd_mixer_element_volume2_info 			volume2;
		snd_mixer_element_accu1_info 			accu1;
		snd_mixer_element_accu2_info 			accu2;
		snd_mixer_element_accu3_info 			accu3;
		snd_mixer_element_mux1_info 			mux1;
		snd_mixer_element_mux2_info 			mux2;
		snd_mixer_element_tone_control1_info 	tc1;
		snd_mixer_element_3d_effect1_info 		teffect1;
		snd_mixer_element_pan_control1_info 	pc1;
		snd_mixer_element_pre_effect1_info 		peffect1;
		uint8_t									reserved[128];	  /* must be filled with zero */
	}		data;
	uint8_t		reserved[128];			/* must be filled with zero */
}		snd_mixer_element_info_t;

typedef struct snd_mixer_element
{
	snd_mixer_eid_t eid;
	union
	{
		snd_mixer_element_switch1 			switch1;
		snd_mixer_element_switch2 			switch2;
		snd_mixer_element_switch3 			switch3;
		snd_mixer_element_volume1 			volume1;
		snd_mixer_element_volume2 			volume2;
		snd_mixer_element_accu3				accu3;
		snd_mixer_element_mux1				mux1;
		snd_mixer_element_mux2				mux2;
		snd_mixer_element_tone_control1		tc1;
		snd_mixer_element_3d_effect1		teffect1;
		snd_mixer_element_pan_control1		pc1;
		snd_mixer_element_pre_effect1		peffect1;
		uint8_t								reserved[128];	  /* must be filled with zero */
	}		data;
	uint8_t		reserved[128];			/* must be filled with zero */
}		snd_mixer_element_t;



typedef enum
{
	SND_MIXER_CHN_FRONT_LEFT,
	SND_MIXER_CHN_FRONT_RIGHT,
	SND_MIXER_CHN_FRONT_CENTER,
	SND_MIXER_CHN_REAR_LEFT,
	SND_MIXER_CHN_REAR_RIGHT,
	SND_MIXER_CHN_WOOFER,
	SND_MIXER_CHN_SURR_LEFT,
	SND_MIXER_CHN_SURR_RIGHT,
	SND_MIXER_CHN_LAST = 31,
}		snd_mixer_channel_t;

#define 	SND_MIXER_CHN_MASK_MONO				(1<<SND_MIXER_CHN_FRONT_LEFT)
#define 	SND_MIXER_CHN_MASK_FRONT_LEFT		(1<<SND_MIXER_CHN_FRONT_LEFT)
#define 	SND_MIXER_CHN_MASK_FRONT_RIGHT		(1<<SND_MIXER_CHN_FRONT_RIGHT)
#define 	SND_MIXER_CHN_MASK_FRONT_CENTER		(1<<SND_MIXER_CHN_FRONT_CENTER)
#define 	SND_MIXER_CHN_MASK_REAR_LEFT		(1<<SND_MIXER_CHN_REAR_LEFT)
#define 	SND_MIXER_CHN_MASK_REAR_RIGHT		(1<<SND_MIXER_CHN_REAR_RIGHT)
#define 	SND_MIXER_CHN_MASK_WOOFER			(1<<SND_MIXER_CHN_WOOFER)
#define 	SND_MIXER_CHN_MASK_SURR_LEFT		(1<<SND_MIXER_CHN_SURR_LEFT)
#define 	SND_MIXER_CHN_MASK_SURR_RIGHT		(1<<SND_MIXER_CHN_SURR_RIGHT)
#define 	SND_MIXER_CHN_MASK_STEREO			(SND_MIXER_CHN_MASK_FRONT_LEFT|SND_MIXER_CHN_MASK_FRONT_RIGHT)
#define 	SND_MIXER_CHN_MASK_4				(SND_MIXER_CHN_MASK_STEREO|SND_MIXER_CHN_MASK_REAR_LEFT|SND_MIXER_CHN_MASK_REAR_RIGHT)
#define 	SND_MIXER_CHN_MASK_5_1				(SND_MIXER_CHN_MASK_4|SND_MIXER_CHN_MASK_FRONT_CENTER|SND_MIXER_CHN_MASK_WOOFER)
#define 	SND_MIXER_CHN_MASK_7_1				(SND_MIXER_CHN_MASK_5_1|SND_MIXER_CHN_MASK_SURR_LEFT|SND_MIXER_CHN_MASK_SURR_RIGHT)

#define 	SND_MIXER_GRPCAP_VOLUME				(1<<0)
#define 	SND_MIXER_GRPCAP_JOINTLY_VOLUME		(1<<1)
#define 	SND_MIXER_GRPCAP_MUTE				(1<<2)
#define 	SND_MIXER_GRPCAP_JOINTLY_MUTE		(1<<3)
#define 	SND_MIXER_GRPCAP_CAPTURE			(1<<4)
#define 	SND_MIXER_GRPCAP_JOINTLY_CAPTURE	(1<<5)
#define 	SND_MIXER_GRPCAP_EXCL_CAPTURE		(1<<6)
#define 	SND_MIXER_GRPCAP_PLAY_GRP			(1<<29)
#define 	SND_MIXER_GRPCAP_CAP_GRP			(1<<30)
#define 	SND_MIXER_GRPCAP_SUBCHANNEL			(1<<31)
#define 	SND_MIXER_GRP_MAX_VOICES			32

typedef struct
{
	int32_t		type;
	char		name[32];
	int32_t		index;
	uint8_t		reserved[124];			/* must be filled with zero */
	int32_t		weight;			 		/* Reserved used for internal sorting oprations */
}		snd_mixer_gid_t;

typedef struct snd_mixer_group_s
{
	snd_mixer_gid_t gid;
	uint32_t	caps;
	uint32_t	channels;
	int32_t		min, max;
	union
	{
		uint32_t	values[32];
		struct
		{
			uint32_t	front_left;
			uint32_t	front_right;
			uint32_t	front_center;
			uint32_t	rear_left;
			uint32_t	rear_right;
			uint32_t	woofer;
			uint8_t		reserved[128];	/* must be filled with zero */
		}		names;
	}		volume;
	uint32_t	mute;
	uint32_t	capture;
	int32_t		capture_group;

	int32_t		elements_size, elements, elements_over;
	snd_mixer_eid_t *pelements;
	uint16_t	change_duration;		/* milliseconds */
	uint16_t	spare;
	int32_t		min_dB, max_dB;
	uint8_t		reserved[120];			/* must be filled with zero */
}		snd_mixer_group_t;



typedef struct snd_mixer_info_s
{
	uint32_t	type;
	uint32_t	attrib;
	uint32_t	elements;
	uint32_t	groups;
	char		id[64];
	char		name[64];
	uint8_t		reserved[128];			/* must be filled with zero */
}		snd_mixer_info_t;


/* Implied by.../ asound/lib/mixer/mixer.c */
typedef struct snd_mixer_elements_s
{
	int32_t		elements, elements_size, elements_over;
	uint8_t		zero[4];				/* alignment -- zero fill */
	snd_mixer_eid_t *pelements;
	void		*pzero;					/* align pointers on 64-bits --> point to NULL */
	uint8_t		reserved[128];			/* must be filled with zero */
}		snd_mixer_elements_t;


typedef struct snd_mixer_groups_s
{
	int32_t		groups, groups_size, groups_over;
	uint8_t		zero[4];				/* alignment -- zero fill */
	snd_mixer_gid_t *pgroups;
	void		*pzero;					/* align pointers on 64-bits --> point to NULL */
	uint8_t		reserved[128];			/* must be filled with zero */
}		snd_mixer_groups_t;


typedef struct snd_mixer_routes_s
{
	snd_mixer_eid_t eid;
	int32_t		routes, routes_size, routes_over;
	uint8_t		zero[4];				/* alignment -- zero fill */
	snd_mixer_eid_t *proutes;
	void		*pzero;					/* align pointers on 64-bits --> point to NULL */
	uint8_t		reserved[128];			/* must be filled with zero */
}		snd_mixer_routes_t;


#define		SND_MIXER_READ_REBUILD			0
#define		SND_MIXER_READ_ELEMENT_VALUE	1
#define		SND_MIXER_READ_ELEMENT_CHANGE	2
#define		SND_MIXER_READ_ELEMENT_ADD		3
#define		SND_MIXER_READ_ELEMENT_REMOVE	4
#define		SND_MIXER_READ_ELEMENT_ROUTE	5
#define		SND_MIXER_READ_GROUP_VALUE		6
#define		SND_MIXER_READ_GROUP_CHANGE		7
#define		SND_MIXER_READ_GROUP_ADD		8
#define		SND_MIXER_READ_GROUP_REMOVE		9

typedef struct snd_mixer_read
{
	int32_t	cmd;
	uint8_t		zero[4];				/* alignment -- zero fill */
	union
	{
		snd_mixer_eid_t eid;
		snd_mixer_gid_t gid;
		uint8_t		reserved[128];		/* must be filled with zero */
	}		data;
	uint8_t		reserved[128];			/* must be filled with zero */
}		snd_mixer_read_t;


#define		SND_MIXER_IOCTL_PVERSION		_IOR ('R', 0x10, int32_t)
#define		SND_MIXER_IOCTL_INFO			_IOR ('R', 0x20, snd_mixer_info_t)
#define		SND_MIXER_IOCTL_ELEMENTS		_IOWR('R', 0x30, snd_mixer_elements_t)
#define		SND_MIXER_IOCTL_ELEMENT_INFO	_IOWR('R', 0x31, snd_mixer_element_info_t)
#define		SND_MIXER_IOCTL_ELEMENT_READ	_IOWR('R', 0x32, snd_mixer_element_t)
#define		SND_MIXER_IOCTL_ELEMENT_WRITE	_IOWR('R', 0x33, snd_mixer_element_t)
#define		SND_MIXER_IOCTL_GROUPS			_IOWR('R', 0x40, snd_mixer_groups_t)
#define		SND_MIXER_IOCTL_GROUP_READ		_IOWR('R', 0x41, snd_mixer_group_t)
#define		SND_MIXER_IOCTL_GROUP_WRITE		_IOWR('R', 0x42, snd_mixer_group_t)
#define		SND_MIXER_IOCTL_ROUTES			_IOWR('R', 0x50, snd_mixer_routes_t)
#define		SND_MIXER_IOCTL_GET_FILTER		_IOR ('R', 0x60, snd_mixer_filter_t)
#define		SND_MIXER_IOCTL_SET_FILTER		_IOW ('R', 0x61, snd_mixer_filter_t)
#define		SND_MIXER_IOCTL_AUDIO_DUCKING	_IOC(IOC_INOUT, 'R', 0x62, 0)
#define		SND_MIXER_IOCTL_AUDIO_DUCKING_REFRESH	_IOC(IOC_INOUT, 'R', 0x63, (sizeof(uint8_t)+sizeof(uint64_t)))


typedef struct snd_mixer_filter
{
	uint32_t	enable;				/* bitfield of 1<<SND_MIXER_READ_* */
	uint8_t		reserved[124];		/* must be filled with zero */
}		snd_mixer_filter_t;



/*****************/
/*****************/
/***   PCM	 ***/
/*****************/
/*****************/

#define		SND_PCM_VERSION		SND_PROTOCOL_VERSION('P',3,0,0)


/*
 * Implied by.../ asound/lib/pcm/plugin/block.c(must be small as they
 * index into an array of fd 's)
 */
#define		SND_PCM_CHANNEL_PLAYBACK		0
#define		SND_PCM_CHANNEL_CAPTURE			1
#define		SND_PCM_CHANNEL_MAX				2


#define		SND_PCM_SFMT_U8						0
#define		SND_PCM_SFMT_S8						1
#define		SND_PCM_SFMT_U16_LE					2
#define		SND_PCM_SFMT_U16_BE					3
#define		SND_PCM_SFMT_S16_LE					4
#define		SND_PCM_SFMT_S16_BE					5
#define		SND_PCM_SFMT_U24_LE					6
#define		SND_PCM_SFMT_U24_BE					7
#define		SND_PCM_SFMT_S24_LE					8
#define		SND_PCM_SFMT_S24_BE					9
#define		SND_PCM_SFMT_U32_LE					10
#define		SND_PCM_SFMT_U32_BE					11
#define		SND_PCM_SFMT_S32_LE					12
#define		SND_PCM_SFMT_S32_BE					13
#define		SND_PCM_SFMT_A_LAW					14
#define		SND_PCM_SFMT_MU_LAW					15
#define		SND_PCM_SFMT_IEC958_SUBFRAME_LE		16
#define		SND_PCM_SFMT_IEC958_SUBFRAME_BE		17
#define		SND_PCM_SFMT_AC3					18
#define		SND_PCM_SFMT_FLOAT_LE				19
#define		SND_PCM_SFMT_FLOAT_BE				20
#define		SND_PCM_SFMT_FLOAT64_LE				22
#define		SND_PCM_SFMT_FLOAT64_BE				23
#define		SND_PCM_SFMT_IMA_ADPCM				24
#define		SND_PCM_SFMT_GSM					25
#define		SND_PCM_SFMT_MPEG					26
#define		SND_PCM_SFMT_SPECIAL				27

#ifdef		SND_LITTLE_ENDIAN
#define		SND_PCM_SFMT_U16					SND_PCM_SFMT_U16_LE
#define		SND_PCM_SFMT_S16					SND_PCM_SFMT_S16_LE
#define		SND_PCM_SFMT_U24					SND_PCM_SFMT_U24_LE
#define		SND_PCM_SFMT_S24					SND_PCM_SFMT_S24_LE
#define		SND_PCM_SFMT_U32					SND_PCM_SFMT_U32_LE
#define		SND_PCM_SFMT_S32					SND_PCM_SFMT_S32_LE
#define		SND_PCM_SFMT_IEC958_SUBFRAME		SND_PCM_SFMT_IEC958_SUBFRAME_LE
#define		SND_PCM_SFMT_FLOAT					SND_PCM_SFMT_FLOAT_LE
#define		SND_PCM_SFMT_FLOAT64				SND_PCM_SFMT_FLOAT64_LE
#else
#define		SND_PCM_SFMT_U16					SND_PCM_SFMT_U16_BE
#define		SND_PCM_SFMT_S16					SND_PCM_SFMT_S16_BE
#define		SND_PCM_SFMT_U24					SND_PCM_SFMT_U24_BE
#define		SND_PCM_SFMT_S24					SND_PCM_SFMT_S24_BE
#define		SND_PCM_SFMT_U32					SND_PCM_SFMT_U32_BE
#define		SND_PCM_SFMT_S32					SND_PCM_SFMT_S32_BE
#define		SND_PCM_SFMT_IEC958_SUBFRAME		SND_PCM_SFMT_IEC958_SUBFRAME_BE
#define		SND_PCM_SFMT_FLOAT					SND_PCM_SFMT_FLOAT_BE
#define		SND_PCM_SFMT_FLOAT64				SND_PCM_SFMT_FLOAT64_BE
#endif

#define		SND_PCM_FMT_U8						(1<<SND_PCM_SFMT_U8)
#define		SND_PCM_FMT_S8						(1<<SND_PCM_SFMT_S8)
#define		SND_PCM_FMT_U16_LE					(1<<SND_PCM_SFMT_U16_LE)
#define		SND_PCM_FMT_U16_BE					(1<<SND_PCM_SFMT_U16_BE)
#define		SND_PCM_FMT_S16_LE					(1<<SND_PCM_SFMT_S16_LE)
#define		SND_PCM_FMT_S16_BE					(1<<SND_PCM_SFMT_S16_BE)
#define		SND_PCM_FMT_U24_LE					(1<<SND_PCM_SFMT_U24_LE)
#define		SND_PCM_FMT_U24_BE					(1<<SND_PCM_SFMT_U24_BE)
#define		SND_PCM_FMT_S24_LE					(1<<SND_PCM_SFMT_S24_LE)
#define		SND_PCM_FMT_S24_BE					(1<<SND_PCM_SFMT_S24_BE)
#define		SND_PCM_FMT_U32_LE					(1<<SND_PCM_SFMT_U32_LE)
#define		SND_PCM_FMT_U32_BE					(1<<SND_PCM_SFMT_U32_BE)
#define		SND_PCM_FMT_S32_LE					(1<<SND_PCM_SFMT_S32_LE)
#define		SND_PCM_FMT_S32_BE					(1<<SND_PCM_SFMT_S32_BE)
#define		SND_PCM_FMT_A_LAW					(1<<SND_PCM_SFMT_A_LAW)
#define		SND_PCM_FMT_MU_LAW					(1<<SND_PCM_SFMT_MU_LAW)
#define		SND_PCM_FMT_IEC958_SUBFRAME_LE		(1<<SND_PCM_SFMT_IEC958_SUBFRAME_LE)
#define		SND_PCM_FMT_IEC958_SUBFRAME_BE		(1<<SND_PCM_SFMT_IEC958_SUBFRAME_BE)
#define		SND_PCM_FMT_AC3						(1<<SND_PCM_SFMT_AC3)
#define		SND_PCM_FMT_FLOAT_LE				(1<<SND_PCM_SFMT_FLOAT_LE)
#define		SND_PCM_FMT_FLOAT_BE				(1<<SND_PCM_SFMT_FLOAT_BE)
#define		SND_PCM_FMT_FLOAT64_LE				(1<<SND_PCM_SFMT_FLOAT64_LE)
#define		SND_PCM_FMT_FLOAT64_BE				(1<<SND_PCM_SFMT_FLOAT64_BE)
#define		SND_PCM_FMT_IMA_ADPCM				(1<<SND_PCM_SFMT_IMA_ADPCM)
#define		SND_PCM_FMT_GSM						(1<<SND_PCM_SFMT_GSM)
#define		SND_PCM_FMT_MPEG					(1<<SND_PCM_SFMT_MPEG)
#define		SND_PCM_FMT_SPECIAL					(1<<SND_PCM_SFMT_SPECIAL)

#ifdef		SND_LITTLE_ENDIAN
#define		SND_PCM_FMT_U16						SND_PCM_FMT_U16_LE
#define		SND_PCM_FMT_S16						SND_PCM_FMT_S16_LE
#define		SND_PCM_FMT_U24						SND_PCM_FMT_U24_LE
#define		SND_PCM_FMT_S24						SND_PCM_FMT_S24_LE
#define		SND_PCM_FMT_U32						SND_PCM_FMT_U32_LE
#define		SND_PCM_FMT_S32						SND_PCM_FMT_S32_LE
#define		SND_PCM_FMT_IEC958_SUBFRAME			SND_PCM_FMT_IEC958_SUBFRAME_LE
#define		SND_PCM_FMT_FLOAT						SND_PCM_FMT_FLOAT_LE
#define		SND_PCM_FMT_FLOAT64						SND_PCM_FMT_FLOAT64_LE
#else
#define		SND_PCM_FMT_U16						SND_PCM_FMT_U16_BE
#define		SND_PCM_FMT_S16						SND_PCM_FMT_S16_BE
#define		SND_PCM_FMT_U24						SND_PCM_FMT_U24_BE
#define		SND_PCM_FMT_S24						SND_PCM_FMT_S24_BE
#define		SND_PCM_FMT_U32						SND_PCM_FMT_U32_BE
#define		SND_PCM_FMT_S32						SND_PCM_FMT_S32_BE
#define		SND_PCM_FMT_IEC958_SUBFRAME			SND_PCM_FMT_IEC958_SUBFRAME_BE
#define		SND_PCM_FMT_FLOAT						SND_PCM_FMT_FLOAT_BE
#define		SND_PCM_FMT_FLOAT64						SND_PCM_FMT_FLOAT64_BE
#endif


#define		SND_PCM_INFO_PLAYBACK				0x001
#define		SND_PCM_INFO_CAPTURE				0x002
#define		SND_PCM_INFO_DUPLEX					0x010
#define		SND_PCM_INFO_DUPLEX_RATE			0x020
#define		SND_PCM_INFO_DUPLEX_MONO			0x040
#define		SND_PCM_INFO_SHARED					0x100
#define		SND_PCM_INFO_UNSECURE				0x200
#define		SND_PCM_INFO_RESTRICTED				0x400


#define		SND_PCM_MODE_UNKNOWN				0
#define		SND_PCM_MODE_BLOCK					1
#define		SND_PCM_MODE_STREAM					2
#define		SND_PCM_MODE_MASK					0x0000FFFF
#define		SND_PCM_MODE_FLAG_PROTECTED_CONTENT	(1<<16)
#define		SND_PCM_MODE_FLAG_ENABLE_PROTECTION	(1<<17)
#define		SND_PCM_MODE_FLAG_REQUIRE_PROTECTION (1<<18)

#define		SND_SRC_MODE_NORMAL					0
#define		SND_SRC_MODE_ACTUAL					1
#define		SND_SRC_MODE_ASYNC					2
#define		SND_SRC_MODE_PITCH					3

#define		SND_PCM_RATE_8000				(1<<1)
#define		SND_PCM_RATE_11025				(1<<2)
#define		SND_PCM_RATE_16000				(1<<3)
#define		SND_PCM_RATE_22050				(1<<4)
#define		SND_PCM_RATE_32000				(1<<5)
#define		SND_PCM_RATE_44100				(1<<6)
#define		SND_PCM_RATE_48000				(1<<7)
#define		SND_PCM_RATE_88200				(1<<8)
#define		SND_PCM_RATE_96000				(1<<9)
#define		SND_PCM_RATE_176400				(1<<10)
#define		SND_PCM_RATE_192000				(1<<11)

#define		SND_PCM_RATE_KNOT				(1<<30)
#define		SND_PCM_RATE_CONTINUOUS			(1<<31)

#define		SND_PCM_RATE_8000_44100			0x07E
#define		SND_PCM_RATE_8000_48000			0x0FE


#define		SND_PCM_CHNINFO_BLOCK			0x00001
#define		SND_PCM_CHNINFO_STREAM			0x00002
#define		SND_PCM_CHNINFO_MMAP			0x00010
#define		SND_PCM_CHNINFO_INTERLEAVE		0x00020
#define		SND_PCM_CHNINFO_NONINTERLEAVE	0x00040
#define 	SND_PCM_CHNINFO_BLOCK_TRANSFER	0x00080
#define		SND_PCM_CHNINFO_PAUSE			0x00100
#define		SND_PCM_CHNINFO_MMAP_VALID		0x00200
#define		SND_PCM_CHNINFO_PROTECTED		0x00400
#define		SND_PCM_CHNINFO_SECURE			0x00800
#define		SND_PCM_CHNINFO_RESTRICTED		0x01000 /* channel data could be muted in circumstances that the driver choose to */
#define		SND_PCM_CHNINFO_ROUTING			0x02000 /* channel may be redirected to a different transducer */
#define		SND_PCM_CHNINFO_PROTECTED_VOICE	0x04000 /* channel data contains only voice and is protected */

#define		SND_PCM_FILL_NONE				1
#define		SND_PCM_FILL_SILENCE			2

#define		SND_PCM_STATUS_NOTREADY			0
#define		SND_PCM_STATUS_READY			1
#define		SND_PCM_STATUS_PREPARED			2
#define		SND_PCM_STATUS_RUNNING			3
#define		SND_PCM_STATUS_UNDERRUN			4
#define		SND_PCM_STATUS_OVERRUN			5
#define		SND_PCM_STATUS_UNSECURE			6
#define		SND_PCM_STATUS_PAUSED			10
#define		SND_PCM_STATUS_ERROR			10000	/* HW error, need to prepare the stream */
#define		SND_PCM_STATUS_CHANGE			10001	/* stream change, need to param the stream */
#define		SND_PCM_STATUS_PREEMPTED		10002	/* stream was preempted by a higher priority stream */


#define		PCM_START_DATA					1
#define		PCM_START_FULL					2
#define		PCM_START_GO					3
#define		PCM_START_COUNT					4


#define		SND_PCM_STOP_STOP				1
#define		SND_PCM_STOP_ROLLOVER			2
#define		SND_PCM_STOP_ROLLOVER_RESET		3	/* allows underflow, overflow, but counters reset once resumed */
#define		SND_PCM_STOP_COUNT				4


#define 	SND_PCM_BOUNDARY			UINT_MAX


#define		SND_PCM_PARAMS_BAD_MODE			1
#define		SND_PCM_PARAMS_BAD_START		2
#define		SND_PCM_PARAMS_BAD_STOP			3
#define		SND_PCM_PARAMS_BAD_FORMAT		4
#define		SND_PCM_PARAMS_BAD_RATE			5
#define		SND_PCM_PARAMS_BAD_VOICES		6
#define		SND_PCM_PARAMS_NO_CHANNEL		10


struct snd_pcm_info
{
	uint32_t	type;					/* soundcard type */
	uint32_t	flags;					/* see SND_PCM_INFO_XXXX */
	uint8_t		id[64];					/* ID of this PCM device */
	char		name[80];				/* name of this device */
	int32_t		playback;				/* playback subdevices-1 */
	int32_t		capture;				/* capture subdevices-1 */
	int32_t		card;
	int32_t		device;
	int32_t		shared_card;
	int32_t		shared_device;
	uint8_t		reserved[128];			/* must be filled with zero */
};


typedef union snd_pcm_sync
{
	uint8_t		id[16];
	uint16_t	id16[8];
	uint32_t	id32[4];
	uint64_t	id64[2];
}		snd_pcm_sync_t;

typedef struct snd_pcm_digital
{
	uint8_t		dig_status[24];			/* AES/EBU/IEC958 channel status bits */
	uint8_t		dig_subcode[147];		/* AES/EBU/IEC958 subcode bits */
	uint8_t		dig_valid:1;			/* must be non-zero to accept these values */
	uint8_t		dig_subframe[4];		/* AES/EBU/IEC958 subframe bits */
	uint8_t		reserved[128];			/* must be filled with zero */
}		snd_pcm_digital_t;

typedef struct snd_pcm_channel_info
{
	int32_t		subdevice;				/* subdevice number */
	char		subname[36];			/* subdevice name */
	int32_t		channel;				/* channel information */
	int32_t		zero1;					/* filler */
	int32_t		zero2[4];				/* filler */
	uint32_t	flags;					/* see to SND_PCM_CHNINFO_XXXX */
	uint32_t	formats;				/* supported formats */
	uint32_t	rates;					/* hardware rates */
	int32_t		min_rate;				/* min rate (in Hz) */
	int32_t		max_rate;				/* max rate (in Hz) */
	int32_t		min_voices;				/* min voices */
	int32_t		max_voices;				/* max voices */
	int32_t		max_buffer_size;		/* max buffer size in bytes */
	int32_t		min_fragment_size;		/* min fragment size in bytes */
	int32_t		max_fragment_size;		/* max fragment size in bytes */
	int32_t		fragment_align;			/* align fragment value */
	int32_t		fifo_size;				/* stream FIFO size in bytes */
	int32_t		transfer_block_size;	/* bus transfer block size in bytes */
	uint8_t		zero3[4];				/* alignment -- zero fill */

	snd_pcm_digital_t dig_mask;			/* AES/EBU/IEC958 supported bits */
	uint32_t	zero4;					/* filler */
	int32_t		mixer_device;			/* mixer device */
	snd_mixer_eid_t mixer_eid;			/* mixer element identification */
	snd_mixer_gid_t mixer_gid;			/* mixer group identification */
	uint8_t		reserved[128];			/* must be filled with zero */
}		snd_pcm_channel_info_t;


struct snd_pcm_format
{
	uint32_t	interleave:1;
	int32_t		format;
	int32_t		rate;
	int32_t		voices;
	int32_t		special;
	uint8_t		reserved[124];			/* must be filled with zero */
};

typedef struct snd_pcm_voice_conversion
{
	uint32_t 	app_voices;
	uint32_t 	hw_voices;
	uint32_t 	matrix[32];
}		snd_pcm_voice_conversion_t;

#define PCM_PLUGIN_PAN_DIMENSIONS (4)  /* Number of supported dimensions; Should eventually become 3 */
typedef struct snd_pcm_pan {
   unsigned attack_window;    /* amount of time in milliseconds to allow panning change to complete */
   int      balance;          /* left/right balance/panning value on [-100,+100] */
} snd_pcm_pan_t;

typedef enum snd_pcm_eq {
   SND_PCM_EQ_PRESET_MV_OFF,
   SND_PCM_EQ_PRESET_MV_AIRPLANE,
   SND_PCM_EQ_PRESET_MV_BASSBOOST,
   SND_PCM_EQ_PRESET_MV_TREBLEBOOST,
   SND_PCM_EQ_PRESET_MV_VOICEBOOST,
   SND_PCM_EQ_PRESET_MV_BASSLOWER,
   SND_PCM_EQ_PRESET_MV_TREBLELOWER,
   SND_PCM_EQ_PRESET_MV_VOICELOWER,
   SND_PCM_EQ_PRESET_MO_ACOUSTIC,
   SND_PCM_EQ_PRESET_MO_DANCE,
   SND_PCM_EQ_PRESET_MO_ELECTRONIC,
   SND_PCM_EQ_PRESET_MO_HIPHOP,
   SND_PCM_EQ_PRESET_MO_JAZZ,
   SND_PCM_EQ_PRESET_MO_LOUNGE,
   SND_PCM_EQ_PRESET_MO_PIANO,
   SND_PCM_EQ_PRESET_MO_RANDB,
   SND_PCM_EQ_PRESET_MO_ROCK,
   SND_PCM_EQ_PRESET_MO_SPOKENWORD,
   SND_PCM_EQ_PRESET_MAX_PRESETS
} snd_pcm_eq_t;

typedef struct snd_pcm_channel_params
{
	int32_t				channel;
	int32_t				mode;
	snd_pcm_sync_t  	sync;				/* hardware synchronization ID */
	struct snd_pcm_format 	format;
	snd_pcm_digital_t 	digital;
	int32_t				start_mode;
	int32_t				stop_mode;
	int32_t				time:1, ust_time:1;
	uint32_t			why_failed;			/* SND_PCM_PARAMS_BAD_??? */
	union
	{
		struct
		{
			int32_t		queue_size;
			int32_t		fill;
			int32_t		max_fill;
			uint8_t		reserved[124];		/* must be filled with zero */
		}		stream;
		struct
		{
			int32_t		frag_size;
			int32_t		frags_min;
			int32_t		frags_max;
			uint32_t	frags_buffered_max; /* When set, as many as this fragments will be used in long buffered mode */
			uint8_t		reserved[120];		/* must be filled with zero */
		}		block;
		uint8_t		reserved[128];			/* must be filled with zero */
	}		buf;
	char		sw_mixer_subchn_name[32];	/* sw_mixer subchn name override */
	uint32_t	cross_core_handle;			/* Cross-core handle for the audio channel */
	uint8_t		reserved[92];				/* must be filled with zero */

}		snd_pcm_channel_params_t;


typedef struct snd_pcm_channel_setup
{
	int32_t				channel;
	int32_t				mode;
	struct snd_pcm_format 	format;
	snd_pcm_digital_t 	digital;
	union
	{
		struct
		{
			int32_t		queue_size;
			uint8_t		reserved[124];		/* must be filled with zero */
		}		stream;
		struct
		{
			int32_t		frag_size;
			int32_t		frags;
			int32_t		frags_min;
			int32_t		frags_max;
			uint32_t	max_frag_size;
			uint8_t		reserved[124];		/* must be filled with zero */
		}		block;
		uint8_t		reserved[128];			/* must be filled with zero */
	}		buf;
	int16_t		msbits_per_sample;
	int16_t		pad1;
	int32_t		mixer_device;			/* mixer device */
	snd_mixer_eid_t *mixer_eid;			/* pcm source mixer element */
	snd_mixer_gid_t *mixer_gid;			/* lowest level mixer group subchn specific */
	uint8_t		mmap_valid:1;			/* channel can use mmapped access */
	uint8_t		mmap_active:1;			/* channel is using mmaped transfers */
	int32_t		mixer_card;				/* mixer card */
	uint8_t		reserved[104];			/* must be filled with zero */
}		snd_pcm_channel_setup_t;

typedef union snd_pcm_status_data
{
	struct
	{
		uint8_t old_device;
		uint8_t new_device;
		uint8_t reserved[2];
	}		change_data;
	uint8_t reserved[4];
}		snd_pcm_status_data_t;

typedef struct snd_pcm_channel_status
{
	int32_t			channel;		/* channel information */
	int32_t			mode;			/* transfer mode */
	int32_t			status;			/* channel status-SND_PCM_STATUS_XXXX */
	uint32_t		scount;			/* number of bytes processed from playback/capture start */
	struct timeval	stime;			/* time when playback/capture was started */
	uint64_t		ust_stime;		/* UST time when playback/capture was started */
	int32_t			frag;			/* current fragment */
	int32_t			count;			/* number of bytes in queue/buffer */
	int32_t			free;			/* bytes in queue still free */
	int32_t			underrun;		/* count of underruns (playback) from last status */
	int32_t			overrun;		/* count of overruns (capture) from last status */
	int32_t			overrange;		/* count of ADC (capture) overrange detections from last status */
	uint32_t		subbuffered;	/* bytes sub buffered in the pluggin interface */
	snd_pcm_status_data_t	status_data;	/* Additional data relevant to a particular value for status */
	struct timeval	stop_time;		/* time when playback/capture was started */
	uint8_t			hw_device;		/* the hardware device the channel is on in @c audio_manager_device_t, AUDIO_DEVICE_COUNT indicates device info is unavailable */
	uint8_t			reserved[111];	/* must be filled with zero */

}		snd_pcm_channel_status_t;


#define	QNX_SHM_NAME_LEN	(4+8+1+4+1+6)	/* "/snd" + 8 pid in hex +
						 * "-" + 4 cntr in dex + null + alignment on 64-bit */
typedef struct snd_pcm_mmap_info_s
{
	char		dmabuf_name[QNX_SHM_NAME_LEN];
	char		dmactl_name[QNX_SHM_NAME_LEN];
	int32_t		size;
	int32_t		ctl_size;
	uint32_t	driver_flags;		/* SEE ADO_SHMBUF_DMA_???? */
	uint32_t	user_flags;			/* SEE ADO_SHMBUF_DMA_???? */
	uint8_t		reserved[112];		/* must be filled with zero */
}		snd_pcm_mmap_info_t;


typedef struct
{
	volatile int32_t	status;				/* read only */
	volatile uint32_t	frag_io;			/* read only */
	volatile uint32_t	block;				/* read only */
	volatile uint32_t	expblock;			/* read write */
	volatile int32_t	voices;				/* read only */
	volatile int32_t	frag_size;			/* read only */
	volatile int32_t	frags;				/* read only */
	uint8_t				reserved[124];		/* must be filled with zero */
}		snd_pcm_mmap_io_status_t;

typedef struct
{
	volatile uint32_t	number;				/* read only */
	volatile int32_t	addr;				/* read only */
	volatile int32_t	voice;				/* read only */
	volatile int8_t		data;				/* read write */
	volatile int8_t		io;					/* read only */
	uint8_t			res[2];
}		snd_pcm_mmap_fragment_t;

typedef struct
{
	snd_pcm_mmap_io_status_t	status;
	snd_pcm_mmap_fragment_t		fragments[0]; 	/* This array is dynamic. See the mmap_io_status.frags variable for its length. */
}		snd_pcm_mmap_control_t;


#define		SND_PCM_IOCTL_PVERSION			_IOR ('A', 0x10, int32_t)
#define		SND_PCM_IOCTL_INFO				_IOR ('A', 0x20, snd_pcm_info_t)
#define		SND_PCM_IOCTL_CHANNEL_DRAIN		_IO  ('A', 0x30)
#define		SND_PCM_IOCTL_CHANNEL_FLUSH		_IO  ('A', 0x31)
#define		SND_PCM_IOCTL_CHANNEL_GO		_IO  ('A', 0x32)
#define		SND_PCM_IOCTL_CHANNEL_INFO		_IOR ('A', 0x33, snd_pcm_channel_info_t)
#define		SND_PCM_IOCTL_CHANNEL_PARAMS	_IOWR('A', 0x34, snd_pcm_channel_params_t)
#define		SND_PCM_IOCTL_CHANNEL_PAUSE		_IOW ('A', 0x35, int)
#define		SND_PCM_IOCTL_CHANNEL_PREFER	_IO  ('A', 0x36)
#define		SND_PCM_IOCTL_CHANNEL_PREPARE	_IO  ('A', 0x37)
#define		SND_PCM_IOCTL_CHANNEL_SETUP		_IOC (IOC_OUT, 'A', 0x38, (sizeof(snd_pcm_channel_setup_t)+sizeof(snd_mixer_eid_t)+sizeof(snd_mixer_gid_t)))
#define		SND_PCM_IOCTL_CHANNEL_STATUS	_IOR ('A', 0x39, snd_pcm_channel_status_t)
#define		SND_PCM_IOCTL_CHANNEL_PARAM_FIT	_IOWR('A', 0x40, snd_pcm_channel_params_t)
#define		SND_PCM_IOCTL_MMAP_INFO			_IOR ('A', 0x50, snd_pcm_mmap_info_t)
#define		SND_PCM_IOCTL_SYNC_GO			_IOC (IOC_OUT, 'A', 0x60, 0)
#define		SND_PCM_IOCTL_CHANNEL_AUDIOMAN_HANDLE	_IOW  ('A', 0x70, uint32_t)
#define		SND_PCM_IOCTL_LOGGING			_IOC (IOC_INOUT, 'A', 0x71, 0)
#define		SND_PCM_IOCTL_NEW_LINK_GROUP	_IO  ('A', 0x72)
#define		SND_PCM_IOCTL_ADD_LINK_GROUP	_IO  ('A', 0x73)
#define		SND_PCM_IOCTL_REMOVE_LINK_GROUP	_IO  ('A', 0x74)
#define		SND_PCM_IOCTL_END_LINK_GROUP	_IO  ('A', 0x75)
#define		SND_PCM_IOCTL_CHANNEL_ROUTE_PATH _IOC(IOC_INOUT, 'A', 0x76, 1)
#define		SND_PCM_IOCTL_SYSTEM_ACCESS		_IO  ('A', 0x77)
#define		SND_PCM_IOCTL_CHANNEL_AUDIOMAN_HANDLE_REROUTE	_IOW  ('A', 0x78, uint32_t)
#define		SND_PCM_IOCTL_CHANNEL_HARDWARE_IDX _IOC (IOC_INOUT, 'A', 0x79, 1)
#define		SND_PCM_IOCTL_QUERY_CHANNEL_MAP	_IOC (IOC_INOUT, 'A', 0x7A, 4)
#define		SND_PCM_IOCTL_GET_CHANNEL_MAP	_IOC (IOC_INOUT, 'A', 0x7B, 4)
#define		SND_PCM_IOCTL_GET_SHARE_ABILITY	_IOR ('A', 0x7C, uint32_t)
#define		SND_PCM_IOCTL_SET_CHANNEL_MAP	_IOC (IOC_IN, 'A', 0x7D, 4)
#define		SND_PCM_IOCTL_GET_HANDLED_DEVICE	_IOC (IOC_INOUT, 'A', 0x7E, 1)
#define		SND_PCM_IOCTL_CHANNEL_DRAIN_ROUTING	_IO  ('A', 0x7F)


#define		SND_PCM_LB_VERSION		SND_PROTOCOL_VERSION('L',3,0,0)


#define		SND_PCM_LB_STREAM_MODE_PACKET	100
#define		SND_PCM_LB_STREAM_MODE_RAW		101

#define		SND_PCM_LB_TYPE_DATA			301
#define		SND_PCM_LB_TYPE_FORMAT			302
#define		SND_PCM_LB_TYPE_POSITION		303

#define		SND_PCM_LB_IOCTL_PVERSION		_IOR ('L', 0x10, int)
#define		SND_PCM_LB_IOCTL_FORMAT			_IOR ('L', 0x30, snd_pcm_format_t)
#define		SND_PCM_LB_IOCTL_STREAM_MODE	_IOW ('L', 0x40, int)

#define        SND_PCM_AUDIOMAN_NO_HANDLE      0x00000000
#define        SND_PCM_AUDIOMAN_SYSTEM_HANDLE  0xFF000000

typedef struct snd_pcm_loopback_header_s
{
	int32_t		size;
	int32_t		type;
	uint8_t		reserved[128];		/* must be filled with zero */
}		snd_pcm_loopback_header_t;


typedef struct snd_pcm_loopback_status
{
	snd_pcm_channel_status_t 	status;
	uint32_t			lost;
	uint8_t				reserved[124];		/* must be filled with zero */
}		snd_pcm_loopback_status_t;


#define		SND_PCM_LB_IOCTL_STATUS		212




/*****************/
/*****************/
/***  RAW MIDI ***/
/*****************/
/*****************/

#define		SND_RAWMIDI_VERSION		SND_PROTOCOL_VERSION('W',3,0,0)


#define		SND_RAWMIDI_CHANNEL_INPUT	0
#define		SND_RAWMIDI_CHANNEL_OUTPUT	1


#define 	SND_RAWMIDI_INFO_OUTPUT		0x00000001	/* device is capable
													 * rawmidi output */
#define 	SND_RAWMIDI_INFO_INPUT		0x00000002	/* device is capable
													 * rawmidi input */
#define 	SND_RAWMIDI_INFO_DUPLEX		0x00000004	/* device is capable the
													 * duplex module */

struct snd_rawmidi_info
{
	int32_t		type;			/* soundcard type */
	uint32_t	flags;			/* see SND_RAWMIDI_INFO_XXXX */
	uint8_t		id[64];			/* ID of this RawMidi device */
	char		name[80];		/* name of this RawMidi device */
	uint8_t		reserved[128];	/* must be filled with zero */
};


struct snd_rawmidi_params_s
{
	int32_t		channel;
	int32_t		size;
	int32_t		room;
	int32_t		max;
	int32_t		min;
	uint8_t		reserved[132];	/* must be filled with zero */
};


struct snd_rawmidi_status_s
{
	int32_t		channel;
	int32_t		size;
	int32_t		count;
	int32_t		queue;
	int32_t		free;
	int32_t		overrun;
	uint8_t		reserved[128];	/* must be filled with zero */
};


#define		SND_RAWMIDI_IOCTL_PVERSION			_IOR ('W', 0x10, int)
#define		SND_RAWMIDI_IOCTL_INFO				_IOR ('W', 0x20, snd_rawmidi_info_t)
#define		SND_RAWMIDI_IOCTL_CHANNEL_PARAMS	_IOW ('W', 0x30, snd_rawmidi_params_t)
#define		SND_RAWMIDI_IOCTL_CHANNEL_STATUS	_IOWR('W', 0x40, snd_rawmidi_status_t)
#define		SND_RAWMIDI_IOCTL_CHANNEL_DRAIN		_IOW ('W', 0x50, int)
#define		SND_RAWMIDI_IOCTL_CHANNEL_FLUSH		_IOW ('W', 0x51, int)



/*****************/
/*****************/
/** Vector Ops ***/
/*****************/
/*****************/

typedef struct snd_v_args_s
{
	/* .../ asound/lib/pcm/pcm.c:687 */
	int32_t		count;
	uint8_t		zero[4];					/* alignment -- zero fill */
	const struct iovec *vector;
	void		*pzero;						/* align pointers on 64-bits --> point to NULL */
}		snd_v_args_t;


#define		SND_IOCTL_READV			_IOW ('K', 0x20, snd_v_args_t)
#define		SND_IOCTL_WRITEV		_IOW ('K', 0x30, snd_v_args_t)


#endif /* __ASOUND_COMMON_H__ */
