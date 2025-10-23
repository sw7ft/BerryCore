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

#include <sys/srcversion.h>


/*
 *  sys/hidut.h
 *

 */

#ifndef __HIDD_USAGE_TABLES_INCLUDED
#define __HIDD_USAGE_TABLE_INCLUDED

/*
	Report Types
*/
#define HID_INPUT_REPORT            0x08
#define HID_OUTPUT_REPORT           0x09
#define HID_FEATURE_REPORT          0x0B

/*
	Device Report Protocol
*/

#define  HID_PROTOCOL_BOOT          0
#define  HID_PROTOCOL_REPORT        1

/*
	Collection Types
*/
#define HIDD_COLLECTION_TYPE_PHYSICAL		0x00
#define HIDD_COLLECTION_TYPE_APPLICATION	0x01
#define HIDD_COLLECTION_TYPE_LOGICAL		0x02
#define HIDD_COLLECTION_TYPE_RESERVED1		0x03
#define HIDD_COLLECTION_TYPE_RESERVED2		0x7F
#define HIDD_COLLECTION_TYPE_VENDOR1		0x80
#define HIDD_COLLECTION_TYPE_VENDOR2		0xFF

/*
	Data properties
*/
#define	HID_FIELD_DATA					0x00010000
#define	HID_FIELD_CONSTANT				0x00010001
#define	HID_FIELD_ARRAY					0x00020000
#define	HID_FIELD_VARIABLE				0x00020002
#define	HID_FIELD_ABSOLUTE				0x00040000
#define	HID_FIELD_RELATIVE				0x00040004
#define	HID_FIELD_NOWRAP				0x00080000
#define	HID_FIELD_WRAP					0x00080008
#define	HID_FIELD_LINEAR				0x00100000
#define	HID_FIELD_NONLINEAR 			0x00100010
#define	HID_FIELD_PREFERED				0x00200000
#define	HID_FIELD_NONPREFERED			0x00200020
#define	HID_FIELD_NONULL				0x00400000
#define	HID_FIELD_NULL					0x00400040
#define	HID_FIELD_BITFIELD				0x01000000
#define	HID_FIELD_BUFFERED				0x01000100

/*
	Usage Pages ( Page 4) of HID Usage Tables Ver 1.1
*/
#define	HIDD_PAGE_UNDEFINED					0x00
#define	HIDD_PAGE_DESKTOP					0x01
#define	HIDD_PAGE_SIMULATION				0x02
#define	HIDD_PAGE_VR_CONTROL				0x03
#define	HIDD_PAGE_SPORT_CONTROL				0x04
#define	HIDD_PAGE_GAME_CONTROL				0x05
#define	HIDD_PAGE_RESERVED1					0x06
#define	HIDD_PAGE_KEYBOARD					0x07
#define	HIDD_PAGE_LEDS						0x08
#define	HIDD_PAGE_BUTTONS					0x09
#define	HIDD_PAGE_ORDINAL					0x0A
#define	HIDD_PAGE_TELEPHONY					0x0B
#define	HIDD_PAGE_CONSUMER					0x0C
#define	HIDD_PAGE_DIGITIZER					0x0D
#define	HIDD_PAGE_RESERVED2					0x0E
#define	HIDD_PAGE_PID						0x0F
#define	HIDD_PAGE_UNICODE					0x10
#define	HIDD_PAGE_RESERVED3					0x11 /* 0x11--0x13 */
#define HIDD_PAGE_ALHANUMERIC_DISPLAY		0x14
#define	HIDD_PAGE_RESERVED4					0x15 /* 0x15--0x7F */
#define	HIDD_PAGE_MONITOR_PAGES				0x80 /* 0x80--0x83 */
#define	HIDD_PAGE_BAR_CODE_SCANNER			0x8C
#define	HIDD_PAGE_POINT_OF_SALE				0x8D
#define	HIDD_PAGE_POWER_PAGES				0x84
#define	HIDD_PAGE_CAMERA_CONTROL			0x90


/*
	Generic Desktop (Page 0x01)
*/
#define HIDD_USAGE_UNDEFINED				0x00
#define HIDD_USAGE_POINTER					0x01
#define HIDD_USAGE_MOUSE					0x02
#define HIDD_USAGE_RESERVED1				0x03
#define HIDD_USAGE_JOYSTICK					0x04
#define HIDD_USAGE_GAMEPAD					0x05
#define HIDD_USAGE_KEYBOARD					0x06
#define HIDD_USAGE_KEYPAD					0x07
#define HIDD_USAGE_MULTI_ACCESS				0x08
/*
 0x9-0x2f Reserved
*/
#define HIDD_USAGE_X						0x30
#define HIDD_USAGE_Y						0x31
#define HIDD_USAGE_Z						0x32
#define HIDD_USAGE_RX						0x33
#define HIDD_USAGE_RY						0x34
#define HIDD_USAGE_RZ						0x35
#define HIDD_USAGE_SLIDER					0x36
#define HIDD_USAGE_DIAL						0x37
#define HIDD_USAGE_WHEEL					0x38
#define HIDD_USAGE_HAT_SWITCH				0x39
#define HIDD_USAGE_MOTION_WAKEUP			0x3C
#define HIDD_USAGE_START					0x3D
#define HIDD_USAGE_SELECT					0x3E
#define HIDD_USAGE_SYSTEM_CONTROL			0x80
#define HIDD_USAGE_SYSTEM_POWER_DOWN		0x81
#define HIDD_USAGE_SYSTEM_SLEEP				0x82
#define HIDD_USAGE_SYSTEM_WAKE_UP			0x83
#define HIDD_USAGE_SYSTEM_CONTEXT_MENU		0x84
#define HIDD_USAGE_SYSTEM_MAIN_MENU			0x85
#define HIDD_USAGE_SYSTEM_APP_MENU			0x86
#define HIDD_USAGE_SYSTEM_MENU_HELP			0x87
#define HIDD_USAGE_SYSTEM_MENU_EXIT			0x88
#define HIDD_USAGE_SYSTEM_MENU_SELECT		0x89
#define HIDD_USAGE_SYSTEM_MENU_RIGHT		0x8A
#define HIDD_USAGE_SYSTEM_MENU_LEFT			0x8B
#define HIDD_USAGE_SYSTEM_MENU_UP			0x8C
#define HIDD_USAGE_SYSTEM_MENU_DOWN			0x8D


/*
 LED (Page 0x08)
*/
#define HIDD_USAGE_NUM_LOCK                  0x01
#define HIDD_USAGE_CAPS_LOCK                 0x02
#define HIDD_USAGE_SCROLL_LOCK               0x03


/*
 Consumer (Page 0x0C)
*/
#define HIDD_USAGE_CONSUMER_CONTROL			0x01
#define HIDD_USAGE_NUMERIC_KEYPAD			0x02
#define HIDD_USAGE_PROGRAMMABLE_BUTTONS		0x03
#define HIDD_USAGE_POWER                    0x30
#define HIDD_USAGE_RESET                    0x31
#define HIDD_USAGE_SLEEP                    0x32
#define HIDD_USAGE_SLEEP_AFTER              0x33
#define HIDD_USAGE_SLEEP_MODE               0x34
#define HIDD_USAGE_ILLUMINATION             0x35
#define HIDD_USAGE_FUNCTION_BUTTONS			0x36
#define HIDD_USAGE_MENU						0x40
#define HIDD_USAGE_MENU_PICK				0x41
#define HIDD_USAGE_MENU_UP					0x42
#define HIDD_USAGE_MENU_DOWN				0x43
#define HIDD_USAGE_MENU_LEFT				0x44
#define HIDD_USAGE_MENU_RIGHT				0x45
#define HIDD_USAGE_MENU_ESCAPE				0x46
#define HIDD_USAGE_MENU_VALUE_INCREASE		0x47
#define HIDD_USAGE_MENU_VALUE_DECREASE		0x48
#define HIDD_USAGE_SNAPSHOT					0x65
#define HIDD_USAGE_SELECTION				0x80
#define HIDD_USAGE_MEDIA_SELECTION			0x87

#define HIDD_USAGE_PLAY						0xB0
#define HIDD_USAGE_PAUSE					0xB1
#define HIDD_USAGE_RECORD					0xB2
#define HIDD_USAGE_FAST_FORWARD				0xB3
#define HIDD_USAGE_REWIND					0xB4
#define HIDD_USAGE_SCAN_NEXT_TRACK			0xB5
#define HIDD_USAGE_SCAN_PREVIOUS_TRACK		0xB6
#define HIDD_USAGE_STOP						0xB7
#define HIDD_USAGE_EJECT					0xB8
#define HIDD_USAGE_RANDOM_PLAY				0xB9

#define HIDD_USAGE_STOP_EJECT				0xCC
#define HIDD_USAGE_PLAY_PAUSE				0xCD
#define HIDD_USAGE_PLAY_SKIP				0xCE

#define HIDD_USAGE_VOLUME					0xE0
#define HIDD_USAGE_BALANCE					0xE1
#define HIDD_USAGE_MUTE						0xE2
#define HIDD_USAGE_BASS						0xE3
#define HIDD_USAGE_TREBLE					0xE4
#define HIDD_USAGE_BASS_BOOST				0xE5
#define HIDD_USAGE_SURROUND_MODE			0xE6
#define HIDD_USAGE_LOUDNESS					0xE7
#define HIDD_USAGE_MPX						0xE8
#define HIDD_USAGE_VOLUME_INCREMENT			0xE9
#define HIDD_USAGE_VOLUME_DECREMENT			0xEA

#define HIDD_USAGE_PLAYBACK_SPEED			0xF1
#define HIDD_USAGE_SPEAKER_SYSTEM			0x160
#define HIDD_USAGE_CHANNEL_LEFT				0x161
#define HIDD_USAGE_CHANNEL_RIGHT			0x162
#define HIDD_USAGE_CHANNEL_CENTRE			0x163
#define HIDD_USAGE_CHANNEL_FRONT			0x164
#define HIDD_USAGE_CHANNEL_CENTER_FRONT		0x165
#define HIDD_USAGE_CHANNEL_SIDE				0x166
#define HIDD_USAGE_CHANNEL_SURROUND			0x167
#define HIDD_USAGE_CHANNEL_LOW_FREQ_ENHANCE	0x168
#define HIDD_USAGE_CHANNEL_TOP				0x169
#define HIDD_USAGE_CHANNEL_UNKNOWN			0x16A
#define HIDD_USAGE_APP_LAUNCH_BUTTONS		0x180
#define HIDD_USAGE_AL_CONSUMER_CTRL_CONFIG	0x183
#define HIDD_USAGE_AL_EMAIL_READER			0x18A
#define HIDD_USAGE_AL_CALCULATOR			0x192
#define HIDD_USAGE_AL_INTERNET_BROWSER		0x196
#define HIDD_USAGE_GENERIC_APP_CONTROLS		0x200
#define HIDD_USAGE_AC_NEW					0x201
#define HIDD_USAGE_AC_OPEN					0x202
#define HIDD_USAGE_AC_CLOSE					0x203
#define HIDD_USAGE_AC_EXIT					0x204
#define HIDD_USAGE_AC_MAXIMIZE				0x205
#define HIDD_USAGE_AC_MINIMIZE				0x206
#define HIDD_USAGE_AC_SAVE					0x207
#define HIDD_USAGE_AC_PRINT					0x208
#define HIDD_USAGE_AC_PROPERTIES			0x209
#define HIDD_USAGE_AC_UNDO					0x21A
#define HIDD_USAGE_AC_COPY					0x21B
#define HIDD_USAGE_AC_CUT					0x21C
#define HIDD_USAGE_AC_PASTE					0x21D
#define HIDD_USAGE_AC_SELECT_ALL			0x21E
#define HIDD_USAGE_AC_FIND					0x21F
#define HIDD_USAGE_AC_FIND_AND_REPLACE		0x220
#define HIDD_USAGE_AC_SEARCH				0x221
#define HIDD_USAGE_AC_GO_TO					0x222
#define HIDD_USAGE_AC_HOME					0x223
#define HIDD_USAGE_AC_BACK					0x224
#define HIDD_USAGE_AC_FORWARD				0x225
#define HIDD_USAGE_AC_STOP					0x226
#define HIDD_USAGE_AC_REFRESH				0x227
#define HIDD_USAGE_AC_PREVIOUS_LINK			0x228
#define HIDD_USAGE_AC_NEXT_LINK				0x229
#define HIDD_USAGE_AC_BOOKMARKS				0x22A
#define HIDD_USAGE_AC_HISTORY				0x22B
#define HIDD_USAGE_AC_ZOOM_IN				0x22D
#define HIDD_USAGE_AC_ZOOM_OUT				0x22E
#define HIDD_USAGE_AC_ZOOM					0x22F
#define HIDD_USAGE_AC_FULL_SCREEN_VIEW		0x230
#define HIDD_USAGE_AC_NORMAL_VIEW			0x231
#define HIDD_USAGE_AC_VIEW_TOGGLE			0x232
#define HIDD_USAGE_AC_SCROLL_UP				0x233
#define HIDD_USAGE_AC_SCROLL_DOWN			0x234
#define HIDD_USAGE_AC_SCROLL				0x235
#define HIDD_USAGE_AC_PAN_LEFT				0x236
#define HIDD_USAGE_AC_PAN_RIGHT				0x237
#define HIDD_USAGE_AC_PAN					0x238

/*
	Digitizer (Page 0x0D)
*/
#define HIDD_USAGE_DIGITIZER				0x01
#define HIDD_USAGE_PEN						0x02
#define HIDD_USAGE_LIGHT_PEN				0x03
#define HIDD_USAGE_TOUCH_SCREEN				0x04
#define HIDD_USAGE_TOUCH_PAD				0x05
#define HIDD_USAGE_WHITE_BOARD				0x06
#define HIDD_USAGE_COORD_MEASURE			0x07
#define HIDD_USAGE_3D_DIGITIZER				0x08
#define HIDD_USAGE_STEREO_PLOTTER			0x09
#define HIDD_USAGE_ARTICULATED_ARM			0x0A
#define HIDD_USAGE_ARMATURE					0x0B
#define HIDD_USAGE_MULTIPOINT_DIGITIZER		0x0C
#define HIDD_USAGE_FREE_SPACE_WAND			0x0D

#define HIDD_USAGE_STYLUS					0x20
#define HIDD_USAGE_PUCK						0x21
#define HIDD_USAGE_FINGER					0x22

#define HIDD_USAGE_TABLET_FUNC_KEYS			0x39
#define HIDD_USAGE_PROGRAM_CHANGE_KEYS		0x3A

#define HIDD_USAGE_TIP_SWITCH				0x42

#endif


__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/hiddi/public/sys/hidut.h $ $Rev: 734844 $" )
