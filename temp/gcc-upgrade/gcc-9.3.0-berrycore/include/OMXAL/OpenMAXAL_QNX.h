/*
 * $QNXLicenseC:
 * Copyright 2013, QNX Software Systems. All Rights Reserved.
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

#ifndef OPENMAX_AL_QNX_H_
#define OPENMAX_AL_QNX_H_

#ifdef __cplusplus
extern "C" {
#endif
#define XA_CONTAINERTYPE_QNX_MKV              ((XAuint32) 0x80000001)
#define XA_CONTAINERTYPE_QNX_QCP              ((XAuint32) 0x80000002)
#define XA_CONTAINERTYPE_QNX_FLAC             ((XAuint32) 0x80000003)

#define XA_AUDIOCODEC_QNX_OPUS                ((XAuint32) 0x80000001)
#define XA_AUDIOCODEC_QNX_TETRA               ((XAuint32) 0x80000002)
#define XA_AUDIOCODEC_QNX_QCP                 ((XAuint32) 0x80000003)
#define XA_AUDIOCODEC_QNX_FLAC                ((XAuint32) 0x80000004)
#define XA_AUDIOCODEC_QNX_CELT                ((XAuint32) 0x80000005)
#define XA_AUDIOCODEC_QNX_AC3                 ((XAuint32) 0x80000006)
#define XA_AUDIOCODEC_QNX_G711                ((XAuint32) 0x80000007)
#define XA_AUDIOCODEC_QNX_G722                ((XAuint32) 0x80000008)
#define XA_AUDIOCODEC_QNX_G729                ((XAuint32) 0x80000009)
#define XA_AUDIOCODEC_QNX_GSM610              ((XAuint32) 0x8000000A)
#define XA_AUDIOCODEC_QNX_SPEEX               ((XAuint32) 0x8000000B)

#define XA_AUDIOMODE_QNX_OPUS_AUTO            ((XAuint32) 0x80000001)
#define XA_AUDIOMODE_QNX_OPUS_SILK            ((XAuint32) 0x80000002)
#define XA_AUDIOMODE_QNX_OPUS_HYBRID          ((XAuint32) 0x80000003)
#define XA_AUDIOMODE_QNX_OPUS_CELT            ((XAuint32) 0x80000004)

#define XAQ_DATAFORMAT_ENCODED                ((XAuint32) 0x80000005)

#define XAQ_ITEMKEY_LOST_FRAME                ((XAuint32) 0x00000005)
#define XAQ_ITEMKEY_TIMESTAMP                 ((XAuint32) 0x00000006)
#define XAQ_ITEMKEY_DIRTY_RECTS               ((XAuint32) 0x00000007)

#define XAQ_COLORFORMAT_NV12                  ((XAuint32) 0x80000000)
/*---------------------------------------------------------------------------*/
/* QNX Screen Buffer Queue Data Locator                                      */
/*---------------------------------------------------------------------------*/

/** Addendum to Data locator macros  */
#define XAQ_DATALOCATOR_SCREENBUFFERQUEUE       ((XAuint32) 0x80000800)

/** Screen Buffer Queue-based data locator definition,
 *  locatorType must be XAQ_DATALOCATOR_SCREENBUFFERQUEUE
 *  screenContext: context for screen window, if it is NULL, OpenMAXAL will create a new one
 *  screenWindow: a handle to screen window, the buffers will be created from this window.
 *  if it is NULL, OpenMAX AL will create a new screen window.
 */
typedef struct XADataLocator_QNXScreenBufferQueue_ {
    XAuint32    locatorType;
    XANativeHandle hWindowContext;
    XANativeHandle hWindow;
} XADataLocator_QNXScreenBufferQueue;

/** Addendum to Data locator macros  */
#define XA_DATALOCATOR_QNXBUFFERQUEUE       ((XAuint32) 0x80000801)

/** Android Buffer Queue-based data locator definition,
 *  locatorType must be XA_DATALOCATOR_QNXBUFFERQUEUE */
typedef struct XADataLocator_QNXBufferQueue_ {
    XAuint32    locatorType;
    XAuint32    numBuffers;
} XADataLocator_QNXBufferQueue;


typedef struct XAAudioStreamInformation_QNX_ {
    XAuint32 codecId;
    XAuint32 channels;
    XAmilliHertz sampleRate;
    XAuint32 bitRate;
    XAuint32 bitsPerSample;
    XAmillisecond duration;
    XAuint32 profileSetting;
    XAuint32 modeSetting;
    XAuint32 streamFormat;
    XAuint8  *codecConfig;
    XAuint32 codecConfigSize;
} XAAudioStreamInformation_QNX;

typedef struct XAVideoStreamInformation_QNX_ {
    XAuint32 codecId;
    XAuint32 width;
    XAuint32 height;
    XAuint32 frameRate;
    XAuint32 bitRate;
    XAmillisecond duration;
    XAuint32 profileSetting;
    XAuint32 levelSetting;
    XAuint8  *codecConfig;
    XAuint32 codecConfigSize;
} XAVideoStreamInformation_QNX;

typedef struct XADataFormat_QNXEncoded_ {
    XAuint32 formatType;
    XAuint32 domainType;     // XA_DOMAINTYPE_AUDIO, XA_DOMAINTYPE_VIDEO, etc.
    XAAudioStreamInformation_QNX   audio_info;
    XAVideoStreamInformation_QNX   video_info;
} XADataFormat_QNXEncoded;

/*---------------------------------------------------------------------------*/
/* QNX Buffer Queue Sink                                                     */
/*---------------------------------------------------------------------------*/
extern XA_API const XAInterfaceID XA_IID_QNXBUFFERQUEUESINK;
extern XA_API const XAInterfaceID XA_IID_QNXAUDIOBUFFERQUEUESINK;
extern XA_API const XAInterfaceID XA_IID_QNXVIDEOBUFFERQUEUESINK;

struct XAQNXBufferQueueSinkItf_;
typedef const struct XAQNXBufferQueueSinkItf_ * const * XAQNXBufferQueueSinkItf;

typedef struct XAQNXBufferItem_
{
	void     *pBufferContext;
	void     *pBufferData;
	XAuint32 dataSize;
	XAuint32 dataUsed;
	const XAAndroidBufferItem *pItems;
	XAuint32 itemsLength;
} XAQNXBufferItem;

struct XAQNXBufferQueueSinkItf_ {
	/*
	 * can be encoded audio/video bitstream, or mp4 file data(mediarecorder), raw audio video(media player) or screen_buffer_t(media player)
	 */
	XAresult (*GetFormat) (
		XAQNXBufferQueueSinkItf self,
		XADataFormat_QNXEncoded *format
	);

	/*
	 * Pop one buffer non-block, the returned buffer may be NULL
	 */
	XAQNXBufferItem * (*Get) (
		XAQNXBufferQueueSinkItf self
	);

	/*
	 * Pop one buffer block, wait until buffer is available.
	 * the returned buffer may be NULL if playback/recorder is stopped.
	 */
	XAQNXBufferItem * (*GetAndWait) (
		XAQNXBufferQueueSinkItf self
	);

	/*
	 * return buffer after data is processed
	 */
	XAresult (*Done) (
		XAQNXBufferQueueSinkItf self,
		XAQNXBufferItem *item
	);
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

