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

#ifndef _OPENMAXAL_QNXCONFIGEXT_H_
#define _OPENMAXAL_QNXCONFIGEXT_H_

#define XAQ_CONFIGEXT_KEY_ENC_VAD                  ((const XAchar*) "mmf.VAD")
#define XAQ_CONFIGEXT_KEY_ENC_DTX                  ((const XAchar*) "mmf.DTX")
#define XAQ_CONFIGEXT_KEY_ENC_FRAMESIZE            ((const XAchar*) "mmf.EncodingFrameSize")
#define XAQ_CONFIGEXT_KEY_ENC_APPLICATION          ((const XAchar*) "mmf.EncodingApplication")
#define XAQ_CONFIGEXT_KEY_ENC_BANDWIDTH            ((const XAchar*) "mmf.EncodingBandwidth")
#define XAQ_CONFIGEXT_KEY_ENC_CBR                  ((const XAchar*) "mmf.EncodingCBR")
#define XAQ_CONFIGEXT_KEY_ENC_CVBR                 ((const XAchar*) "mmf.EncodingCvbr")
#define XAQ_CONFIGEXT_KEY_ENC_COMPLEXITY           ((const XAchar*) "mmf.EncodingComplexity")
#define XAQ_CONFIGEXT_KEY_ENC_ENCODINGDTX          ((const XAchar*) "mmf.EncodingDTX")
#define XAQ_CONFIGEXT_KEY_ENC_PCKTLOSS             ((const XAchar*) "mmf.EncodingPacket_loss_perc")
#define XAQ_CONFIGEXT_KEY_ENC_OPUS_MODE            ((const XAchar*) "mmf.EncodingOpus_mode")
#define XAQ_CONFIGEXT_KEY_ENC_MAX_PAYLOAD          ((const XAchar*) "mmf.EncodingMax_payload")
#define XAQ_CONFIGEXT_KEY_ENC_INBAND_FEC           ((const XAchar*) "mmf.EncodingInband_FEC")
#define XAQ_CONFIGEXT_KEY_ENC_INPUTBLOCKSIZE       ((const XAchar*) "mmf.InputBlockSize")
#define XAQ_CONFIGEXT_KEY_ENC_QUALITY              ((const XAchar*) "mmf.EncodingQuality")

#define XAQ_CONFIGEXT_KEY_DEC_OUTPUT_CHANNELS      ((const XAchar*) "mmf.DecodingOutputChannels")
#define XAQ_CONFIGEXT_KEY_DEC_SAMPLING_RATE        ((const XAchar*) "mmf.DecodingSamplingRate")
#define XAQ_CONFIGEXT_KEY_DEC_INBAD_FEC            ((const XAchar*) "mmf.DecodingInband_FEC")

//network parameters
#define XAQ_CONFIGEXT_KEY_VERBOSE                   ((const XAchar*) "OPT_VERBOSE")
#define XAQ_CONFIGEXT_KEY_CONNECTTIMEOUT_MS         ((const XAchar*) "OPT_CONNECTTIMEOUT_MS")
#define XAQ_CONFIGEXT_KEY_LOW_SPEED_LIMIT           ((const XAchar*) "OPT_LOW_SPEED_LIMIT")
#define XAQ_CONFIGEXT_KEY_LOW_SPEED_TIME            ((const XAchar*) "OPT_LOW_SPEED_TIME")
#define XAQ_CONFIGEXT_KEY_USERAGENT                 ((const XAchar*) "OPT_USERAGENT")
#define XAQ_CONFIGEXT_KEY_USERNAME                  ((const XAchar*) "OPT_USERNAME")
#define XAQ_CONFIGEXT_KEY_PASSWORD                  ((const XAchar*) "OPT_PASSWORD")
#define XAQ_CONFIGEXT_KEY_QNX_CREDMGR_HANDLE        ((const XAchar*) "OPT_QNX_CREDMGR_HANDLE")
#define XAQ_CONFIGEXT_KEY_PROXYUSERNAME             ((const XAchar*) "OPT_PROXYUSERNAME")
#define XAQ_CONFIGEXT_KEY_PROXYPASSWORD             ((const XAchar*) "OPT_PROXYPASSWORD")
#define XAQ_CONFIGEXT_KEY_QNX_PROXY_CREDMGR_HANDLE  ((const XAchar*) "OPT_QNX_PROXY_CREDMGR_HANDLE")
#define XAQ_CONFIGEXT_KEY_COOKIE                    ((const XAchar*) "OPT_COOKIE")
#define XAQ_CONFIGEXT_KEY_COOKIELIST                ((const XAchar*) "OPT_COOKIELIST")
#define XAQ_CONFIGEXT_KEY_COOKIEFILE                ((const XAchar*) "OPT_COOKIEFILE")
#define XAQ_CONFIGEXT_KEY_COOKIEJAR                 ((const XAchar*) "OPT_COOKIEJAR")
#define XAQ_CONFIGEXT_KEY_COOKIESESSION             ((const XAchar*) "OPT_COOKIESESSION")
#define XAQ_CONFIGEXT_KEY_CAINFO                    ((const XAchar*) "OPT_CAINFO")
#define XAQ_CONFIGEXT_KEY_CAPATH                    ((const XAchar*) "OPT_CAPATH")
#define XAQ_CONFIGEXT_KEY_SSL_VERIFYPEER            ((const XAchar*) "OPT_SSL_VERIFYPEER")
#define XAQ_CONFIGEXT_KEY_SSL_VERIFYHOST            ((const XAchar*) "OPT_SSL_VERIFYHOST")
#define XAQ_CONFIGEXT_KEY_PROXY                     ((const XAchar*) "OPT_PROXY")
#define XAQ_CONFIGEXT_KEY_NOPROXY                   ((const XAchar*) "OPT_NOPROXY")
#define XAQ_CONFIGEXT_KEY_HTTPPROXYTUNNEL           ((const XAchar*) "OPT_HTTPPROXYTUNNEL")
#define XAQ_CONFIGEXT_KEY_PROXYPORT                 ((const XAchar*) "OPT_PROXYPORT")
#define XAQ_CONFIGEXT_KEY_PROXYTYPE                 ((const XAchar*) "OPT_PROXYTYPE")
#define XAQ_CONFIGEXT_KEY_PROXYAUTH                 ((const XAchar*) "OPT_PROXYAUTH")
#define XAQ_CONFIGEXT_KEY_HTTPAUTH                  ((const XAchar*) "OPT_HTTPAUTH")
#define XAQ_CONFIGEXT_KEY_SO_RCVBUF                 ((const XAchar*) "OPT_SO_RCVBUF")
#define XAQ_CONFIGEXT_KEY_SO_SNDBUF                 ((const XAchar*) "OPT_SO_SNDBUF")
#define XAQ_CONFIGEXT_KEY_ACCEPT_ENCODING           ((const XAchar*) "OPT_ACCEPT_ENCODING")
#define XAQ_CONFIGEXT_KEY_HTTPHEADER                ((const XAchar*) "OPT_HTTPHEADER")
#define XAQ_CONFIGEXT_KEY_DNSCACHETIMEOUT           ((const XAchar*) "OPT_DNSCACHETIMEOUT")
#define XAQ_CONFIGEXT_KEY_HEADERFILE                ((const XAchar*) "OPT_HEADERFILE")

//for subtile
#define XAQ_CONFIGEXT_KEY_SUBTITLE_URL               ((const XAchar*) "sp.SubpictureUrl")
#define XAQ_CONFIGEXT_KEY_SUBTITLE_DISABLE           ((const XAchar*) "sp.SubpictureDisable")
#define XAQ_CONFIGEXT_KEY_SUBTITLE_TRACK             ((const XAchar*) "sp.SubpictureTrack")

/*
 * enable/disable, this can be applied for
 * XAQ_CONFIGEXT_KEY_ENC_VAD
 * XAQ_CONFIGEXT_KEY_ENC_DTX
 * XAQ_CONFIGEXT_KEY_DEC_INBAD_FEC
 */
#define XAQ_CONFIGEXT_VALUE_DISABLE ((const XAchar*) "0")
#define XAQ_CONFIGEXT_VALUE_ENABLE ((const XAchar*) "1")

//supported values for XAQ_CONFIGEXT_KEY_ENC_OPUS_MODE
#define XAQ_CONFIGEXT_VALUE_OPUS_MODE_AUTO ((const XAchar*) "0")
#define XAQ_CONFIGEXT_VALUE_OPUS_MODE_SILK_ONLY ((const XAchar*) "1000")
#define XAQ_CONFIGEXT_VALUE_OPUS_MODE_HYBRID ((const XAchar*) "1001")
#define XAQ_CONFIGEXT_VALUE_OPUS_MODE_CELT_ONLY ((const XAchar*) "1002")

//supported values for XAQ_CONFIGEXT_KEY_ENC_APPLICATION
#define XAQ_CONFIGEXT_VALUE_OPUS_APP_AUDIO ((const XAchar*) "0")              // Audio application for Opus
#define XAQ_CONFIGEXT_VALUE_OPUS_APP_VOIP  ((const XAchar*) "1")              // Voip application for Opus
#define XAQ_CONFIGEXT_VALUE_OPUS_APP_RESTRICTEDLOWDELAY ((const XAchar*) "2") // Restricted Low Delay application for Opus

//supported values for XAQ_CONFIGEXT_KEY_ENC_FRAMESIZE
#define XAQ_CONFIGEXT_VALUE_RDA_FRAMERATE_00MS ((const XAchar*) "0")
#define XAQ_CONFIGEXT_VALUE_RDA_FRAMERATE_10MS ((const XAchar*) "1")
#define XAQ_CONFIGEXT_VALUE_RDA_FRAMERATE_20MS ((const XAchar*) "2")
#define XAQ_CONFIGEXT_VALUE_RDA_FRAMERATE_30MS ((const XAchar*) "3")
#define XAQ_CONFIGEXT_VALUE_RDA_FRAMERATE_40MS ((const XAchar*) "4")
#define XAQ_CONFIGEXT_VALUE_RDA_FRAMERATE_50MS ((const XAchar*) "5")
#define XAQ_CONFIGEXT_VALUE_RDA_FRAMERATE_60MS ((const XAchar*) "6")
#define XAQ_CONFIGEXT_VALUE_RDA_FRAMERATE_16MS ((const XAchar*) "7")
#define XAQ_CONFIGEXT_VALUE_RDA_FRAMERATE_25MS ((const XAchar*) "8")
#define XAQ_CONFIGEXT_VALUE_RDA_FRAMERATE_5MS  ((const XAchar*) "9")

//supported values for XAQ_CONFIGEXT_KEY_ENC_BANDWIDTH
#define XAQ_CONFIGEXT_VALUE_OPUS_BANDWIDTH_AUTO ((const XAchar*) "0")               /* Auto Bandwidth */
#define XAQ_CONFIGEXT_VALUE_OPUS_BANDWIDTH_NARROWBAND ((const XAchar*) "1101")      /* 4 kHz bandpass */
#define XAQ_CONFIGEXT_VALUE_OPUS_BANDWIDTH_MEDIUMBAND ((const XAchar*) "1102")      /* 6 kHz bandpass */
#define XAQ_CONFIGEXT_VALUE_OPUS_BANDWIDTH_WIDEBAND ((const XAchar*) "1103")        /* 8 kHz bandpass */
#define XAQ_CONFIGEXT_VALUE_OPUS_BANDWIDTH_SUPERWIDEBAND ((const XAchar*) "1104")   /* 12 kHz bandpass */
#define XAQ_CONFIGEXT_VALUE_OPUS_BANDWIDTH_FULLBAND ((const XAchar*) "1105")        /* 20 kHz bandpass */

//supported values for XAQ_CONFIGEXT_KEY_ENC_COMPLEXITY
#define XAQ_CONFIGEXT_VALUE_COMPLEXITY_AUTO ((const XAchar*) "0")
#define XAQ_CONFIGEXT_VALUE_COMPLEXITY_0 ((const XAchar*) "1")
#define XAQ_CONFIGEXT_VALUE_COMPLEXITY_1 ((const XAchar*) "2")
#define XAQ_CONFIGEXT_VALUE_COMPLEXITY_2 ((const XAchar*) "3")
#define XAQ_CONFIGEXT_VALUE_COMPLEXITY_3 ((const XAchar*) "4")
#define XAQ_CONFIGEXT_VALUE_COMPLEXITY_4 ((const XAchar*) "5")
#define XAQ_CONFIGEXT_VALUE_COMPLEXITY_5 ((const XAchar*) "6")
#define XAQ_CONFIGEXT_VALUE_COMPLEXITY_6 ((const XAchar*) "7")
#define XAQ_CONFIGEXT_VALUE_COMPLEXITY_7 ((const XAchar*) "8")
#define XAQ_CONFIGEXT_VALUE_COMPLEXITY_8 ((const XAchar*) "9")
#define XAQ_CONFIGEXT_VALUE_COMPLEXITY_9 ((const XAchar*) "10")
#define XAQ_CONFIGEXT_VALUE_COMPLEXITY_10 ((const XAchar*) "11")

//supported values for XAQ_CONFIGEXT_KEY_DEC_OUTPUT_CHANNELS
#define XAQ_CONFIGEXT_VALUE_DEC_OUTPUT_CHANNEL_MONO ((const XAchar*) "1")
#define XAQ_CONFIGEXT_VALUE_DEC_OUTPUT_CHANNEL_STEREO ((const XAchar*) "2")

//supported values for XAQ_CONFIGEXT_KEY_DEC_SAMPLING_RATE
#define XAQ_CONFIGEXT_VALUE_DEC_SAMPLING_RATE_8000 ((const XAchar*) "8000")
#define XAQ_CONFIGEXT_VALUE_DEC_SAMPLING_RATE_12000 ((const XAchar*) "12000")
#define XAQ_CONFIGEXT_VALUE_DEC_SAMPLING_RATE_16000 ((const XAchar*) "16000")
#define XAQ_CONFIGEXT_VALUE_DEC_SAMPLING_RATE_24000 ((const XAchar*) "24000")
#define XAQ_CONFIGEXT_VALUE_DEC_SAMPLING_RATE_48000 ((const XAchar*) "48000")

//supported values for XAQ_CONFIGEXT_KEY_ENC_QUALITY
#define XAQ_CONFIGEXT_VALUE_QUALITY_0 ((const XAchar*) "0")
#define XAQ_CONFIGEXT_VALUE_QUALITY_1 ((const XAchar*) "1")
#define XAQ_CONFIGEXT_VALUE_QUALITY_2 ((const XAchar*) "2")
#define XAQ_CONFIGEXT_VALUE_QUALITY_3 ((const XAchar*) "3")
#define XAQ_CONFIGEXT_VALUE_QUALITY_4 ((const XAchar*) "4")
#define XAQ_CONFIGEXT_VALUE_QUALITY_5 ((const XAchar*) "5")
#define XAQ_CONFIGEXT_VALUE_QUALITY_6 ((const XAchar*) "6")
#define XAQ_CONFIGEXT_VALUE_QUALITY_7 ((const XAchar*) "7")
#define XAQ_CONFIGEXT_VALUE_QUALITY_8 ((const XAchar*) "8")
#define XAQ_CONFIGEXT_VALUE_QUALITY_9 ((const XAchar*) "9")
#define XAQ_CONFIGEXT_VALUE_QUALITY_10 ((const XAchar*) "10")

#endif

