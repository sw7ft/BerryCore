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



#ifndef __AOI_ERRLOG_H__
#define __AOI_ERRLOG_H__

#include <stdarg.h>
#include <sys/slog.h>
#include <sys/slogcodes.h>

__BEGIN_DECLS

#if !defined(AO_LOGLVL_DELTA)
 #define AO_LOGLVL_DELTA 0
#endif

typedef enum AOErrorLevel {
	AO_LOG_SHUTDOWN = 0,  /* Shut down the system NOW. eg: for OEM use */
	AO_LOG_CRITICAL = 1,  /* Unexpected unrecoverable error. eg: hard disk error */
	AO_LOG_ERROR    = 2,  /* Unexpected recoverable error. eg: needed to reset a hw controller */
	AO_LOG_WARNING  = 3,  /* Expected error. eg: parity error on a serial port */
	AO_LOG_NOTICE   = 4,  /* Warnings. eg: Out of paper */
	AO_LOG_INFO     = 5,  /* Information. eg: Printing page 3 */
	AO_LOG_DEBUG1   = 6,  /* Debug messages eg: Normal detail */
	AO_LOG_DEBUG2   = 7,  /* Debug messages eg: Fine detail */
} AOErrorLevel_t;

#if ! defined(AO_LOGLVL)
 #if defined(NDEBUG)
  #define AO_LOGLVL AO_LOG_INFO
 #else
  #define AO_LOGLVL AO_LOG_DEBUG2
 #endif
#endif

#if ! defined(AO_BE_SENSITIVE)
 #if defined(NDEBUG)
  #define AO_BE_SENSITIVE 1
 #else
  #define AO_BE_SENSITIVE 0
 #endif
#endif

extern const char AoCensored[];

#if AO_BE_SENSITIVE
  #define AO_LOG_SENSITIVE 0x1000
  #define AO_SENSITIVE( string ) (AoCensored)
#else
  #define AO_LOG_SENSITIVE 0
  #define AO_SENSITIVE( string ) (string)
#endif

#define AO_LOGLVL_ENABLED( level ) ( (level) <= AO_LOGLVL + AO_LOGLVL_DELTA )

#if defined(__GNUC__)
  #define AO_IS_PRINTFLIKE( fmt, var ) __attribute__((format(__printf__,fmt,var)))
#else
  #define AO_IS_PRINTFLIKE( fmt, var )
#endif

void AO_IS_PRINTFLIKE(2,3) AoLog( AOErrorLevel_t level, const char *fmt, ... );
void AoLogv( AOErrorLevel_t level, const char *fmt, va_list ap );
void AoAssertFailed( const char *file, unsigned line, const char *cond );

#define AO_LOGV( level, fmt, ap ) ( AO_LOGLVL_ENABLED(level)  ? AoLogv( level, fmt, ap ) : (void)0 )
#if defined(__cplusplus)
 static inline void AO_LOG( AOErrorLevel_t level, const char *fmt, ... ) {
	if ( AO_LOGLVL_ENABLED(level) ) {
		va_list ap;
		va_start( ap, fmt );
		AoLogv( (AOErrorLevel_t)( (level) >= AO_LOGLVL_DELTA ? (level)-AO_LOGLVL_DELTA : 0 ), fmt, ap );
		va_end( ap );
    }
 }
#else
 #define AO_LOG( level, ... )     ( AO_LOGLVL_ENABLED(level) ? AoLog( (level) > AO_LOGLVL_DELTA ? (level)-AO_LOGLVL_DELTA : 0, __VA_ARGS__ ) : (void)0 )

 #define AO_STRINGIZE( arg ) #arg
 #define AO_EXPAND( arg ) AO_STRINGIZE( arg )

 #define AO_DEBUG1( ... )   AO_LOG( AO_LOG_DEBUG1, __FILE__ ":" AO_EXPAND(__LINE__) ": " __VA_ARGS__ )
 #define AO_DEBUG2( ... )   AO_LOG( AO_LOG_DEBUG2, __FILE__ ":" AO_EXPAND(__LINE__) ": " __VA_ARGS__ )
 #define AO_DEBUG           AO_DEBUG1
#endif

void AoAssertFailed( const char *file, unsigned line, const char *cond );
#if defined(NDEBUG)
 #define AO_ASSERT( cond ) ((void)0)
#else
 #define AO_ASSERT( cond ) ( (cond) ? (void)0 : AoAssertFailed( __FILE__, __LINE__, #cond ) )
#endif

typedef void AoLogger_t( AOErrorLevel_t level, const char *fmt, va_list ap );
typedef struct AoLoggerHandle AoLoggerHandle_t;

AoLoggerHandle_t *AoSetLogger( AoLogger_t *newlogger );
void AoUnsetLogger( AoLoggerHandle_t *handle );

__END_DECLS

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/aoi/public/aoi/aoi_errlog.h $ $Rev: 760506 $" )
#endif

