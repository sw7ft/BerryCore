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



#ifndef __AOI_CORE_H__
#define __AOI_CORE_H__

#include <stdint.h>

struct AOICtrl;
typedef struct AOICtrl AOICtrl_t;
struct AOIStream;
typedef struct AOIStream AOIStream_t;
struct AODataFormat;
typedef struct AODataFormat AODataFormat_t;
struct AOMetadataParser_t;
typedef struct AOMetadataParser_t AOMetadataParser;
struct AOMetadata;
typedef struct AOMetadata AOMetadata_t;

#include <aoi/aoi_interfaces.h>

__BEGIN_DECLS

typedef struct
{
	char *name;
	int32_t version;
	void *interface;
} AOInterface_t;

typedef struct AOError 
{
    int64_t error;        /* error number according to the type_str field. */
    int64_t extra;        /* extra info stored according to the type_str field, some protocol library may store extra info*/
    char    type_str[16]; /* a short string describing the protocol/library reporting the error type. ex: "errno", "http","ftp","rtsp" */
    char    err_str[256]; /* a string describing the error. */
} AOError_t;

typedef struct AOParam
{
    const char *name;     /* string describing an option to be set */
    const char *value;    /* string containing the value of the option to be set */
} AOParam_t;

#define AO_ERRTYPESTR  "libaoi"
/*AO error number*/
typedef enum
{
	AO_EDLOP = 10000,   /* dlopen error */
	AO_EDLSYM,          /* dlsym error */
	AO_EDUP,            /* add a duplicate DLL */
	AO_EINIT,           /* DLL init call failed */
} AOErrNo_t;

typedef struct AOLoadedConfig AOLoadedConfig_t;

/* core functionality */
const AOICtrl_t *AoAdd(const char *dll);
const AOICtrl_t *AoAddStatic(AOInterface_t *interfaces);
int32_t AoAddDirectory(const char *path,const char *pattern);
int32_t AoRemove(const AOICtrl_t *ctrl);
int32_t AoHold(const AOICtrl_t *cctrl);
int32_t AoRelease(const AOICtrl_t *ctrl);
int32_t AoHoldAll(void);
int32_t AoReleaseAll(void);
AOInterface_t *AoGetAOInterface(const AOICtrl_t *ctrl, const int32_t nth);
void *AoGetInterface(const AOICtrl_t *ctrl,const char *ifname,const int32_t minver,const int32_t nth);
int32_t AoHasInterface(const AOICtrl_t *ctrl,const char *ifname,const int32_t minver,const int32_t nth);
const AOICtrl_t *AoIterate(const char *iname,const int32_t version,int32_t * const cookie);
const AOICtrl_t *AoIterateHoldGet(const char *iname,const int32_t version,int32_t *cookie,void **iface);
const AOICtrl_t *AoFindName(const char *name,const char *oiface,int32_t version);
int32_t AoAddUnloadSignal(int sig);
int32_t AoSaveConfig(const char *config_file);
int32_t AoLoadConfig(const char *config_file, AOLoadedConfig_t **cfg);
void AoUnloadConfig(AOLoadedConfig_t *cfg);
const char * const *AoGetStrings(const AOICtrl_t *ctrl);
const char * const *AoGetConfigs(const AOICtrl_t *ctrl);
const AOICtrl_t *AoAddDll(const char *dll, const char * const configs[], AOError_t *err);

/* convenience functions */
const AOICtrl_t *AoFindMime(const char *mimetype,int32_t *rating,const char *oiface,int32_t version);
const AOICtrl_t *AoFindExt(const char *ext,int32_t *rating,const char *oiface,int32_t version);
const AOICtrl_t *AoFindStreams(AOIStream_t *stream,int32_t *rating,const char *oiface,int32_t version);
const AOICtrl_t *AoFindFormats(const AODataFormat_t *fmt,int32_t *rating,const char *oiface,int32_t version);
AOIStream_t *AoOpenFilespec(const char *fspec,const char *mode);
AOMetadataParser *AoFindMetadataParser(AOIStream_t *sobj,AOMetadata_t **metadata);
AOIStream_t * AoOpenStream(const char *name,const char *mode,const AOParam_t *params,AOError_t *err);
void AoStreamClose(AOIStream_t *stream);
void AoSetError(AOError_t *err, int64_t error, const char *type, const char *description);

__END_DECLS

#endif


#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/aoi/public/aoi/aoi_core.h $ $Rev: 734501 $" )
#endif
