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
* AODataFormat specifications
*/

#ifndef __AOIDATAFORMAT_H__
#define __AOIDATAFORMAT_H__

#include <inttypes.h>
#include <aoi/aoi_core.h>

__BEGIN_DECLS

#define AOIFOURCC4( C0, C1, C2, C3 ) ( ((uint32_t)C0<<24) | ((uint8_t)C1<<16) | ((uint8_t)C2<<8) | ((uint8_t)C3) )
#define AOIFOURCC( FCC ) AOIFOURCC4( FCC[0], FCC[1], FCC[2], FCC[3] )

/* Pre-defined metadata field types for use with AoFindMetadataParser */
#define AOIFOURCC_METADATA_ISO8859    "TXT1"
#define AOIFOURCC_METADATA_UTF16_LE   "TXT2"
#define AOIFOURCC_METADATA_UTF16_BE   "2TXT"
#define AOIFOURCC_METADATA_UTF16      "TX2T"
#define AOIFOURCC_METADATA_UTF32_LE   "TXT4"
#define AOIFOURCC_METADATA_UTF32_BE   "4TXT"  
#define AOIFOURCC_METADATA_UTF32      "TX4T"  
/* typo in commit of AOIFOURCC_METATATA_UTF8, to be removed when io-media take care of the metadata extraction */
#define AOIFOURCC_METATATA_UTF8       "UTF8"
#define AOIFOURCC_METADATA_UTF8       "UTF8"
#define AOIFOURCC_METADATA_ID3V1      "TXT0"

#define AOIFOURCC_METADATA_BINARY     "BINA"
#define AOIFOURCC_METADATA_BOOL       "BOOL"
#define AOIFOURCC_METADATA_WORD       "NUM2"
#define AOIFOURCC_METADATA_DWORD      "NUM4"
#define AOIFOURCC_METADATA_QWORD      "NUM8"

#define AOIFOURCC_METADATA_STORAGE    "TmpF" /* Temporary path for storing metadata payload into file system (ex: a picture). The filemane is in ASCII format. */

#define MEDIA_TYPE_COMPRESSED 0x80000000

/* image data specs */
#define MEDIA_TYPE_IMAGE 0x00000001
typedef struct
{
	uint32_t width;
	uint32_t height;
	uint16_t depth;

	/* if palettized */
	int16_t transparent;	/* transparency index+1, 0 if not transparent */
	uint8_t pal[256][3];
} AOImageFormat_t;

/* video data specs (image+) */
#define MEDIA_TYPE_VIDEO 0x00000002
typedef struct AOAspectRatio
{
	uint16_t n;      /* aspect ratio numerator (width)   */
	uint16_t d;      /* aspect ratio denominator (height) */
} AOAspectRatio_t;

typedef struct
{
	uint32_t width;
	uint32_t height;
	uint32_t depth;

	int32_t frame_rate;
	int32_t scale;
	int32_t duration;
	AOAspectRatio_t pixel_aspect_ratio;
	int32_t frame_rate_divisor;             // 0 Means 1
	int16_t rotation; /* rotation angle when rendering video frames. can be 0/90/180/270 */
	int16_t reserve2;
} AOVideoFormat_t;

/* audo data specs */
#define MEDIA_TYPE_AUDIO 0x00000004
typedef struct
{
	uint32_t channels;
	uint32_t depth;

	int32_t frame_rate;
	int32_t scale;
	int32_t duration;	/* in frames, 0 if not known */
} AOAudioFormat_t;

#define MEDIA_TYPE_TEXT 0x00000008
/* no structure for text... fourcc can tell us if its html/rtf/whatever. */

#define MEDIA_TYPE_UNKNOWN    0x00000000

#define MEDIA_TYPE_SUBPICTURE 0x00000010

/* users specified  data type  */
#define MEDIA_TYPE_USER1 0x01000000
#define MEDIA_TYPE_USER2 0x02000000
#define MEDIA_TYPE_USER3 0x04000000
#define MEDIA_TYPE_USER4 0x08000000

/* wrapper for all formats */
struct AODataFormat
{
	uint32_t mtype;
	uint32_t fourcc;

	union
	{
		AOImageFormat_t image;
		AOAudioFormat_t audio;
		AOVideoFormat_t video;
		int8_t padding[1024];	/* allow 1024 bytes max for other formats. */
	} u;
};

__END_DECLS

#endif



#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/aoi/public/aoi/aoi_dataformat.h $ $Rev: 748800 $" )
#endif
