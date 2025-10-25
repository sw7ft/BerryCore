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
* Various Interfaces for Addons
*/

#ifndef __AOINTERFACES_H__
#define __AOINTERFACES_H__

#include <inttypes.h>
#include <aoi/aoi_core.h>

__BEGIN_DECLS

#define AODEINITIALIZER_VERSION 100
/*
 * AODeInitializer: Init and Cleanup functions for
 * the addon after it's loaded and cleanup before unloading
 */
typedef struct
{
	int32_t (*Init)(const AOICtrl_t *interfaces );
	void (*Cleanup)(void);
} AODeInitializer;

#define AODECONSTRUCTOR_VERSION 100
/*
 * AODeConstuctor: Create and Destroy functions for creating/destroying a
 * unique context for this addon.
 */
typedef struct
{
	void *(*Create)(const AOICtrl_t *interfaces);
	int32_t (*Destroy)(void *ctx);
} AODeConstructor;

#define AOSTREAMINSPECTOR_VERSION 100
/*
 * If we need to sniff the stream and return a rating to see if we can
 * process it with one of our other interfaces, we use this interface.
 */
typedef struct
{
	int32_t (*RateStream)(AOIStream_t *stream);
} AOStreamInspector;

#define AOFORMATINSPECTOR_VERSION 100
/*
 * If we need to return a rating for a given AODataFormat, to see if we can
 * process it with one of our other interfaces, we use this interface.
 */
typedef struct
{
	int32_t (*RateFormat)(const AODataFormat_t *fmt);
} AOFormatInspector;


#define AOEXTINSPECTOR_VERSION 100
/*
 * If we need to return a rating for a given extension, to see if we can
 * process it with one of our other interfaces, we use this interface. (Usually
 * for any kind of loader, we use a stream inspector, and for a saver, we use
 * the extension inspector.)
 */
typedef struct
{
	int32_t (*RateExtension)(const char *ext);
} AOExtInspector;


#define AOMIMETYPEINSPECTOR_VERSION 100
/*
 * If we need to return a rating for a given mimetype, to see if we can
 * process it with one of our other interfaces, we use this interface.
 */
typedef struct
{
	int32_t (*RateMimetype)(const char *mimetype);
} AOMimetypeInspector;

#define AOMETADATAPARSER_VERSION 100

struct AOMetadataParser_t
{
	  AOMetadata_t *(*ParseMetadata)(AOIStream_t *sobj);
	  void (*FreeMetadata)(AOMetadata_t *metadata);
	  int32_t (*QueryMetadata)(AOMetadata_t *metadata,char *key,int32_t instance,void **data,int32_t *fourcc,int32_t *dsize);
	  int32_t (*IterateMetadata)(AOMetadata_t *metadata,int32_t *cookie,char **key,void **data,int32_t *fourcc,int32_t *dsize);
};

#define AOSTRINGS_VERSION 100


__END_DECLS

#endif




#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/aoi/public/aoi/aoi_interfaces.h $ $Rev: 732740 $" )
#endif
