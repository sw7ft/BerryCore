/* Copyright 2013, QNX Software Systems. All Rights Reserved.
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
#ifndef _IMG_H_INCLUDED
#define _IMG_H_INCLUDED

#ifdef _MSC_VER
#include <gfpr/gfpr.h>
#else
#ifndef _UNISTD_H_INCLUDED
#include <unistd.h>
#endif
#endif

#ifndef _IO_H_INCLUDED
#include <io/io.h>
#endif

#define IMG_FMT_MASK_BPP	0x0000007f
#define IMG_FMT_PKLE		0x00000100
#define IMG_FMT_PKBE		0x00000200
#define IMG_FMT_PACK		(IMG_FMT_PKLE | IMG_FMT_PKBE)
#define IMG_FMT_ALPHA		0x00000400
#define IMG_FMT_PALETTE		0x00000800
#define IMG_FMT_RGB			0x00001000
#define IMG_FMT_YUV			0x00002000
#define IMG_FMT_RGB_ORDER	0x01000000
#define IMG_FMT_G6			0x01000000

#define IMG_FMT_BPP(_fmt)		((_fmt) & IMG_FMT_MASK_BPP)
#define IMG_FMT_BPL(_fmt,_w)	(((IMG_FMT_BPP(_fmt) * (_w)) + 7) >> 3)

#ifdef _MSC_VER // Win32 Visual C++
	#if defined(BMP_EXPORTS) || defined(TGA_EXPORTS) || defined(SGI_EXPORTS) || defined(PNG_EXPORTS) || defined(JPG_EXPORTS) || defined(GIF_EXPORTS) || defined(PCX_EXPORTS)
		#define CODEC_API __declspec(dllexport)
	#else
		#define CODEC_API __declspec(dllimport)
	#endif
#else // __QNXNTO__ and __MINGW32__
	#define CODEC_API
#endif

__BEGIN_DECLS

typedef struct _img_lib *img_lib_t;
typedef struct _img_codec *img_codec_t;

typedef enum {
	IMG_FMT_INVALID = 0,
	IMG_FMT_MONO = 1,
	IMG_FMT_G8 = 8,
	IMG_FMT_A8 = 8 | IMG_FMT_ALPHA,
	IMG_FMT_PAL1 = 1 | IMG_FMT_PALETTE,
	IMG_FMT_PAL4 = 4 | IMG_FMT_PALETTE,
	IMG_FMT_PAL8 = 8 | IMG_FMT_PALETTE,
	IMG_FMT_PKLE_RGB565 = 16 | IMG_FMT_PKLE | IMG_FMT_RGB | IMG_FMT_G6,
	IMG_FMT_PKBE_RGB565 = 16 | IMG_FMT_PKBE | IMG_FMT_RGB | IMG_FMT_G6,
	IMG_FMT_PKLE_ARGB1555 = 16 | IMG_FMT_PKLE | IMG_FMT_ALPHA | IMG_FMT_RGB,
	IMG_FMT_PKBE_ARGB1555 = 16 | IMG_FMT_PKBE | IMG_FMT_ALPHA | IMG_FMT_RGB,
	IMG_FMT_PKLE_XRGB1555 = 16 | IMG_FMT_PKLE | IMG_FMT_RGB,
	IMG_FMT_PKBE_XRGB1555 = 16 | IMG_FMT_PKBE | IMG_FMT_RGB,
	IMG_FMT_BGR888 = 24 | IMG_FMT_RGB,
	IMG_FMT_RGB888 = 24 | IMG_FMT_RGB | IMG_FMT_RGB_ORDER,
	IMG_FMT_PKLE_ABGR8888 = 32 | IMG_FMT_PKLE | IMG_FMT_ALPHA | IMG_FMT_RGB | IMG_FMT_RGB_ORDER,
	IMG_FMT_PKBE_ABGR8888 = 32 | IMG_FMT_PKBE | IMG_FMT_ALPHA | IMG_FMT_RGB | IMG_FMT_RGB_ORDER,
	IMG_FMT_PKLE_XBGR8888 = 32 | IMG_FMT_PKLE | IMG_FMT_RGB | IMG_FMT_RGB_ORDER,
	IMG_FMT_PKBE_XBGR8888 = 32 | IMG_FMT_PKBE | IMG_FMT_RGB | IMG_FMT_RGB_ORDER,
	IMG_FMT_PKLE_ARGB8888 = 32 | IMG_FMT_PKLE | IMG_FMT_ALPHA | IMG_FMT_RGB,
	IMG_FMT_PKBE_ARGB8888 = 32 | IMG_FMT_PKBE | IMG_FMT_ALPHA | IMG_FMT_RGB,
	IMG_FMT_PKLE_XRGB8888 = 32 | IMG_FMT_PKLE | IMG_FMT_RGB,
	IMG_FMT_PKBE_XRGB8888 = 32 | IMG_FMT_PKBE | IMG_FMT_RGB,
	IMG_FMT_YUV888 = 24 | IMG_FMT_YUV,
} img_format_t;

#if defined (__BIGENDIAN__)
#define IMG_FMT_PKHE			IMG_FMT_PKBE
#define IMG_FMT_PKHE_RGB565		IMG_FMT_PKBE_RGB565
#define IMG_FMT_PKHE_ARGB1555	IMG_FMT_PKBE_ARGB1555
#define IMG_FMT_PKHE_XRGB1555	IMG_FMT_PKBE_XRGB1555
#define IMG_FMT_PKHE_ABGR8888	IMG_FMT_PKBE_ABGR8888
#define IMG_FMT_PKHE_XBGR8888	IMG_FMT_PKBE_XBGR8888
#define IMG_FMT_PKHE_ARGB8888	IMG_FMT_PKBE_ARGB8888
#define IMG_FMT_PKHE_XRGB8888	IMG_FMT_PKBE_XRGB8888
#define IMG_FMT_PKOE			IMG_FMT_PKLE
#define IMG_FMT_PKOE_RGB565		IMG_FMT_PKLE_RGB565
#define IMG_FMT_PKOE_ARGB1555	IMG_FMT_PKLE_ARGB1555
#define IMG_FMT_PKOE_XRGB1555	IMG_FMT_PKLE_XRGB1555
#define IMG_FMT_PKOE_ABGR8888	IMG_FMT_PKLE_ABGR8888
#define IMG_FMT_PKOE_XBGR8888	IMG_FMT_PKLE_XBGR8888
#define IMG_FMT_PKOE_ARGB8888	IMG_FMT_PKLE_ARGB8888
#define IMG_FMT_PKOE_XRGB8888	IMG_FMT_PKLE_XRGB8888
#else
#define IMG_FMT_PKHE			IMG_FMT_PKLE
#define IMG_FMT_PKHE_RGB565		IMG_FMT_PKLE_RGB565
#define IMG_FMT_PKHE_ARGB1555	IMG_FMT_PKLE_ARGB1555
#define IMG_FMT_PKHE_XRGB1555	IMG_FMT_PKLE_XRGB1555
#define IMG_FMT_PKHE_ABGR8888	IMG_FMT_PKLE_ABGR8888
#define IMG_FMT_PKHE_XBGR8888	IMG_FMT_PKLE_XBGR8888
#define IMG_FMT_PKHE_ARGB8888	IMG_FMT_PKLE_ARGB8888
#define IMG_FMT_PKHE_XRGB8888	IMG_FMT_PKLE_XRGB8888
#define IMG_FMT_PKOE			IMG_FMT_PKBE
#define IMG_FMT_PKOE_RGB565		IMG_FMT_PKBE_RGB565
#define IMG_FMT_PKOE_ARGB1555	IMG_FMT_PKBE_ARGB1555
#define IMG_FMT_PKOE_XRGB1555	IMG_FMT_PKBE_XRGB1555
#define IMG_FMT_PKOE_ABGR8888	IMG_FMT_PKBE_ABGR8888
#define IMG_FMT_PKOE_XBGR8888	IMG_FMT_PKBE_XBGR8888
#define IMG_FMT_PKOE_ARGB8888	IMG_FMT_PKBE_ARGB8888
#define IMG_FMT_PKOE_XRGB8888	IMG_FMT_PKBE_XRGB8888
#endif

#define IMG_FMT_BGRA8888		IMG_FMT_PKLE_ARGB8888
#define IMG_FMT_RGBA8888		IMG_FMT_PKLE_ABGR8888

/* img_color_t encoding is IMG_FMT_PKHE_ARGB8888 unless otherwise noted */
typedef _uint32	img_color_t;

/* exif orientation standard */
typedef enum {
	IMG_ORIENTATION_TOPLEFT  = 1, //default orientation
	IMG_ORIENTATION_TOPRIGHT = 2,
	IMG_ORIENTATION_BOTTOMRIGHT = 3,
	IMG_ORIENTATION_BOTTOMLEFT  = 4,
	IMG_ORIENTATION_LEFTTOP  = 5,
	IMG_ORIENTATION_RIGHTTOP = 6,
	IMG_ORIENTATION_RIGHTBOTTOM = 7,
	IMG_ORIENTATION_LEFTBOTTOM  = 8,
} img_orientation_t;

typedef enum {
	IMG_FLIP_HORIZONTAL,
	IMG_FLIP_VERTICAL
} img_flip_t;

/* data transform handle */
typedef		struct _dtransform*	img_dtransform_t;

/* img_fixed_t encoding is 16.16 unless otherwise noted */
typedef	_uint32	img_fixed_t;

typedef void	(img_access_f)	(_Uintptrt data, unsigned x, unsigned y, unsigned n, _uint8 *pixels);
typedef void	(img_convert_f)	(const _uint8 *src, _uint8 *dst, unsigned n);
typedef void	(img_expand_f)	(const _uint8 *src, _uint8 *dst, unsigned n, const _uint8 *lut);
typedef void	(img_avg_f)		(const _uint8 *a, const _uint8 *b, _uint8 *dst, unsigned n);
typedef void	(img_copy_f)	(const _uint8 *src, _uint8 *dst, int stride, unsigned n);

typedef struct {
	union {
		struct {
			_uint8			*data;
			unsigned		stride;
		} direct;						/* valid when IMG_DIRECT flag is set */
		struct {
			img_access_f	*access_f;
			_Uintptrt		data;
		} indirect;						/* valid when IMG_INDIRECT flag is set */
	} access;
	unsigned				w, h;		/* valid when IMG_W/IMG_H flags are set */
	img_format_t			format;		/* valid when IMG_FORMAT flag is set */
	unsigned 				npalette;
	img_color_t				*palette;	/* valid when IMG_PALETTE flag is set */
	unsigned				flags;
	union {
		_uint8				index;		/* for 8bpp formats */
		_uint16				rgb16;		/* for 16bpp formats */
		img_color_t			rgb32;		/* for 24 and 32bpp formats */
	} transparency;						/* valid when IMG_TRANSPARENCY flag is set */
	unsigned				quality;
} img_t;

typedef img_t	img_info_t;

typedef unsigned	(img_decode_choose_format_f)	(_Uintptrt data, img_t *img, const img_format_t *formats, unsigned nformats);
typedef int			(img_decode_setup_f)			(_Uintptrt data, img_t *img, unsigned flags);
typedef void		(img_decode_abort_f)			(_Uintptrt data, img_t *img);
typedef int			(img_decode_scanline_f)			(_Uintptrt data, img_t *img, unsigned row, unsigned npass_line, unsigned npass_total);
typedef int			(img_decode_set_palette_f)		(_Uintptrt data, img_t *img, const _uint8 *palette, img_format_t format);
typedef void		(img_decode_set_transparency_f)	(_Uintptrt data, img_t *img, img_color_t color);
typedef void		(img_decode_frame_f)			(_Uintptrt data, img_t *img);
typedef int			(img_decode_set_value_f)		(_Uintptrt data, img_t *img, unsigned type, _Uintptrt value);

typedef struct {
	img_decode_choose_format_f		*choose_format_f;
	img_decode_setup_f				*setup_f;
	img_decode_abort_f				*abort_f;
	img_decode_scanline_f			*scanline_f;
	img_decode_set_palette_f		*set_palette_f;
	img_decode_set_transparency_f	*set_transparency_f;
	img_decode_frame_f				*frame_f;
	img_decode_set_value_f			*set_value_f;
	_Uintptrt data;
} img_decode_callouts_t;

typedef unsigned	(img_encode_choose_format_f)	(_Uintptrt data, img_t *img, const img_format_t *formats, unsigned nformats);
typedef int			(img_encode_setup_f)			(_Uintptrt data, img_t *img, unsigned flags);
typedef void		(img_encode_abort_f)			(_Uintptrt data, img_t *img);
typedef int			(img_encode_scanline_f)			(_Uintptrt data, img_t *img, unsigned row, unsigned npass_line, unsigned npass_total);
typedef int			(img_encode_get_palette_f)		(_Uintptrt data, img_t *img, _uint8 *palette, img_format_t format);
typedef int			(img_encode_get_transparency_f)	(_Uintptrt data, img_t *img, img_color_t *color);
typedef void		(img_encode_frame_f)			(_Uintptrt data, img_t *img);

typedef struct {
	img_encode_choose_format_f		*choose_format_f;
	img_encode_setup_f				*setup_f;
	img_encode_abort_f				*abort_f;
	img_decode_scanline_f			*scanline_f;
	img_encode_get_palette_f		*get_palette_f;
	img_encode_get_transparency_f	*get_transparency_f;
	img_encode_frame_f				*frame_f;
	_Uintptrt data;
} img_encode_callouts_t;

extern size_t img_codec_list_byext(img_lib_t ilib, const char *string, img_codec_t *buf, size_t nbuf);
extern size_t img_codec_list_bymime(img_lib_t ilib, const char *mime, img_codec_t *buf, size_t nbuf);
extern size_t img_codec_list(img_lib_t ilib, img_codec_t *buf, size_t nbuf, img_codec_t *exclude, size_t nexclude);
extern void img_codec_get_criteria(img_codec_t codec, const char **ext, const char **mime);

extern int img_lib_attach(img_lib_t *ilib);
extern void img_lib_detach(img_lib_t ilib);
extern int img_cfg_read(img_lib_t ilib, const char *path);

extern int img_load(img_lib_t ilib,
	io_stream_t *input,
	const img_decode_callouts_t *callouts,
	img_t *img);
extern int img_load_file(img_lib_t ilib,
	const char *path,
	const img_decode_callouts_t *callouts,
	img_t *img);
extern int img_load_resize_file(img_lib_t ilib,
	const char *path,
	const img_decode_callouts_t *callouts,
	img_t *img);
extern int img_load_resize(img_lib_t ilib,
	io_stream_t* input,
	const img_decode_callouts_t *callouts,
	img_t *img);
extern int img_write(img_lib_t ilib,
	io_stream_t *output,
	const img_encode_callouts_t *callouts,
	img_t *img, img_codec_t * codec);
extern int img_write_file(img_lib_t ilib,
	const char *path,
	const img_encode_callouts_t *callouts,
	img_t *img);
extern img_expand_f *img_expand_getfunc(img_format_t src, img_format_t lut);
extern img_convert_f *img_convert_getfunc(img_format_t src, img_format_t dst);
extern int img_convert_data(img_format_t sformat, const _uint8 *src,
	img_format_t dformat, _uint8 *dst,
	size_t n);
extern int img_dtransform(const img_t *src, img_t *dst);
extern int img_dtransform_create(const img_t *src, const img_t *dst, img_dtransform_t *xform);
extern void img_dtransform_apply(img_dtransform_t xform, const _uint8 *src, _uint8 *dst, unsigned n);
extern void img_dtransform_free(img_dtransform_t xform);
extern img_avg_f *img_avg_getfunc(img_format_t format);
extern img_copy_f *img_copy_getfunc(img_format_t format);
extern int img_resize_fs(const img_t *src, img_t *dst);
extern int img_rotate_ortho(const img_t *src, img_t *dst, img_fixed_t angle);
extern int img_decode_validate(const img_codec_t *codecs, size_t ncodecs,
	io_stream_t *input, unsigned *codec);
extern int img_decode_begin(img_codec_t codec, io_stream_t *input, _Uintptrt *decode_data);
extern int img_decode_frame(img_codec_t codec,
	io_stream_t *input,
	const img_decode_callouts_t *callouts,
	img_t *img,
	_Uintptrt *decode_data);
extern int img_decode_frame_resize(img_codec_t codec,
	io_stream_t* input,
	const img_decode_callouts_t *ext_callouts,
	img_t *img,
	_Uintptrt *decode_data);
extern int img_decode_get_frame_count(img_codec_t codec,
	io_stream_t *input,
	_Uintptrt *decode_data,
	unsigned * count);
extern int img_decode_set_frame_index(img_codec_t codec,
	io_stream_t *input,
	_Uintptrt *decode_data,
	unsigned index);
extern int img_decode_finish(img_codec_t codec, io_stream_t *input, _Uintptrt *decode_data);
extern int img_encode_begin(img_codec_t codec, io_stream_t *output, _Uintptrt *encode_data);
extern int img_encode_frame(img_codec_t codec,
	io_stream_t *output,
	const img_encode_callouts_t *callouts,
	img_t *img,
	_Uintptrt *encode_data);
extern int img_encode_finish(img_codec_t codec,
	io_stream_t *output,
	_Uintptrt *encode_data);
extern int
img_encode_set_value(img_codec_t codec, _Uintptrt *encode_data, unsigned type, _Uintptrt value );
extern int
img_crop(const img_t *src, img_t *dst, const unsigned x, const unsigned y);
extern int img_flip_horizontal(img_t *img);
extern int img_flip_vertical(img_t *img);
extern int img_flip(img_t * src, img_t * dst, img_flip_t flip);

extern int img_reset(img_t * img);

__END_DECLS

/* flag manifests for img_t */

#define IMG_TRANSPARENCY		0x00000001	/* 'transparency' field is valid */
#define IMG_FORMAT				0x00000002	/* 'format' field is valid */
#define IMG_W					0x00000004	/* 'w' field is valid */
#define IMG_H					0x00000008	/* 'h' field is valid */
#define IMG_DIRECT				0x00000010	/* direct access field is valid */
#define IMG_INDIRECT			0x00000020	/* indirect access field is valid */
#define IMG_PALETTE				0x00000080	/* 'palette' field is valid */
#define IMG_QUALITY				0x00000100	/* 'quality' field is valid */
#define IMG_PAL8_ALPHA			0x00000200	/* PAL8 image palette entries have alpha bits. */
#define	IMG_TRANSPARENCY_TO_ALPHA	0x00000400	/* If target format supports alpha, convert transparency into alpha. */
#define	IMG_SRC_FMT_TRANSPARENCY	0x00000800	/* The source format of this image specified transparency. */

#define IMG_RESIZE              0x00001000  /* 'h' and 'w' are the desired size (or zero) */

#define IMG_FLAGS_SET_ORIENTATION(img, ori) \
		(img)->flags |= (((((unsigned int)ori) - 1) & 0x7) << 14)
#define IMG_FLAGS_GET_ORIENTATION(img) \
		((img_orientation_t)((((img)->flags >> 14) & 0x7) + 1))

/* flag manifests for img_decode_setup_f */

#define IMG_SETUP_PAL_SHARED	0x00000001	/* palette is shared between frames */
#define IMG_SETUP_TOP_DOWN		0x00000002	/* scanlines will be delivered in topdown sequence */
#define IMG_SETUP_BOTTOM_UP		0x00000004	/* scanlines will be delivered in bottomup sequence */
#define IMG_SETUP_MULTIPASS		0x00000008	/* scanlines will be split across passes */

#define IMG_ANGLE_90CW			0x0001921f	/* 90 degrees clockwise */
#define IMG_ANGLE_90CCW			0x0004b65f	/* 90 degrees counterclockwise */
#define IMG_ANGLE_180			0x0003243f	/* 180 degrees */

/* Types for img_decode_set_value_f
 * There are no guarantees made as to when these values are reported by the codec
 */
enum img_value_type {
	IMG_VALUE_TYPE_INVALID = 0,       /* Not a valid type */
	IMG_VALUE_TYPE_PROGRESSIVE,       /* 0 for a non-progressive image, or 1 for progressive one. */
	IMG_VALUE_TYPE_ANIM_PLAY_COUNT,   /* The number of times the animation is meant to be played. 0 means play forever. */
	IMG_VALUE_TYPE_ANIM_FRAME_DELAY,  /* The minimum time for which the current frame must be displayed. */
	IMG_VALUE_TYPE_FRAME_COUNT,       /* The number of frames in the image, >0 */
};

#ifndef _IMG_ERRNO_H_INCLUDED
#include <img/img_errno.h>
#endif

#endif


#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/img/lib/public/img/img.h $ $Rev: 729025 $" )
#endif
