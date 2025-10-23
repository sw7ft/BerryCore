/* Copyright 2009, QNX Software Systems. All Rights Reserved.
 * 
 * You must obtain a written license from and pay applicable license fees to 
 * QNX Software Systems before you may reproduce, modify or distribute this 
 * software, or any work that includes all or part of this software.  Free 
 * development licenses are available for evaluation and non-commercial purposes.  
 * For more information visit http://licensing.qnx.com or email licensing@qnx.com.
 * 
 * This file may contain contributions from others.  Please review this entire 
 * file for other proprietary rights or license notices, as well as the QNX 
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 */
#ifndef __UFT8_H_INCLUDED
#define __UFT8_H_INCLUDED

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define UTF8_LEN_MAX 6
#define UTF8_CUR_MAX UTF8_LEN_MAX

extern int utf8len( const char *s, size_t n );
extern const unsigned char 	Pt_utf8skip[];
#define	UTF8LEN( s, n )		( 1 == Pt_utf8skip[ *(unsigned char*)s ] ? 1 : utf8len( s , n ) )

extern int utf8towc( wchar_t *pwc, const char *s, size_t n );
extern int wctoutf8( char *s, wchar_t wc );

extern char *utf8strirchr( char const *string_base, char const *start_char, char const *mbchar, int *count );
extern char *utf8strrchr( char const *string_base, char const *start_char, char const *mbchar, int *count );
extern char *utf8strichr( char const *string, char const *mbchar, int *count );
extern char *utf8strnichr( char const *string, char const *mbchar, int num, int *count );
extern char *utf8strchr( char const *string, char const *mbchar, int *count );
extern char *utf8strnchr( char const *string, char const *mbchar, int num, int *count );
extern int utf8strlen( char const *text, int *bytes );
extern int utf8strnlen( char const *text, int max_len, int *num );
extern int utf8strblen( char const *text, int max_bytes, int *bytes );
extern int utf8strncmp( char const *text, char const *text2, int len );
extern char *utf8strndup( char const *text, int count, int *bytes );
extern wchar_t wctolower( wchar_t );

#define mbstrirchr( base, start, mbc, count )       utf8strirchr( base, start, mbc, count )
#define mbstrrchr( base, start, mbc, count )        utf8strrchr( base, start, mbc, count )
#define mbstrichr( string, mbc, count )             utf8strichr( string, mbc, count )
#define mbstrnichr( string, mbc, num, count )       utf8strnichr( string, mbc, num, count )
#define mbstrchr( string, mbc, count )              utf8strchr( string, mbc, count )
#define mbstrnchr( string, mbc, num, count )        utf8strnchr( string, mbc, num, count )
#define mbstrlen( text, char_width, bytes )         ( (void)(char_width), utf8strlen( text, bytes ) )
#define mbstrnlen( text, max_len, char_width, num ) ( (void)(char_width), utf8strnlen( text, max_len, num ) )
#define mbstrblen( text, max_bytes, width, bytes )  ( (void)(width), utf8strblen( text, max_bytes, bytes ) )
#define mbstrncmp( str1, str2, len, char_width )    ( (void)(char_width), utf8strncmp( str1, str2, len ) )
#define mbstrndup( text, count, bytes )             utf8strndup( text, count, bytes )

#ifdef __cplusplus
}
#endif

#endif


#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/ph/public/utf8.h $ $Rev: 224590 $" )
#endif
