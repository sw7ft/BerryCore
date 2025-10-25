/*
 * $QNXLicenseC:
 * Copyright 2008, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable
 * license fees to QNX Software Systems before you may reproduce,
 * modify or distribute this software, or any work that includes
 * all or part of this software.   Free development licenses are
 * available for evaluation and non-commercial purposes.  For more
 * information visit http://licensing.qnx.com or email
 * licensing@qnx.com.
 *
 * This file may contain contributions from others.  Please review
 * this entire file for other proprietary rights or license notices,
 * as well as the QNX Development Suite License Guide at
 * http://licensing.qnx.com/license-guide/ for other information.
 * $
 */

#ifndef _WINMGR_IOW_H_
#define _WINMGR_IOW_H_

#include <stdint.h>

#define IOW_ERR_OK                       0x0000  /* no error */
#define IOW_ERR_GENERIC                  0x0001
#define IOW_ERR_MEM                      0x0002  /* memory allocation error */
#define IOW_ERR_WINMGR                   0x0003  /* error accessing io-winmgr */
#define IOW_ERR_PARAM                    0x0004  /* invalid parameter */
#define IOW_ERR_INVAL                    0x0005  /* invalid message or message parameter */
#define IOW_ERR_INUSE                    0x0006  /* already connected to io-winmgr */
#define IOW_ERR_NOSUPPORT                0x0007  /* unsupported operation */

#define IOW_EVENT_TYPE_NONE                   0
#define IOW_EVENT_TYPE_CREATE                 1
#define IOW_EVENT_TYPE_REALIZE                2
#define IOW_EVENT_TYPE_PROPERTY               3
#define IOW_EVENT_TYPE_FOCUS                  4
#define IOW_EVENT_TYPE_CLOSE                  6
#define IOW_EVENT_TYPE_STATE                  7
#define IOW_EVENT_TYPE_INPUT                  8
#define IOW_EVENT_TYPE_JOG                    9
#define IOW_EVENT_TYPE_POINTER               10
#define IOW_EVENT_TYPE_JOYSTICK              11
#define IOW_EVENT_TYPE_KEYBOARD              12
#define IOW_EVENT_TYPE_USER                  13

#define IOW_FORMAT_INVALID                    0
#define IOW_FORMAT_L8                    0x0008
#define IOW_FORMAT_R4_G4_B4_A4           0x100C
#define IOW_FORMAT_R5_G5_B5_A1           0x100F
#define IOW_FORMAT_R5_G6_B5              0x1010
#define IOW_FORMAT_R8_G8_B8              0x1018
#define IOW_FORMAT_R8_G8_B8_A8           0x1020
#define IOW_FORMAT_YVU9                  0x2009
#define IOW_FORMAT_YUV420                0x200C
#define IOW_FORMAT_NV12                  0x210C
#define IOW_FORMAT_YV12                  0x220C
#define IOW_FORMAT_UYVY                  0x2010
#define IOW_FORMAT_YUY2                  0x2110
#define IOW_FORMAT_YVYU                  0x2210
#define IOW_FORMAT_V422                  0x2310
#define IOW_FORMAT_AYUV                  0x2020
#define IOW_FORMAT_YVU9_INTERLACED       0x3009
#define IOW_FORMAT_YUV420_INTERLACED     0x300C
#define IOW_FORMAT_NV12_INTERLACED       0x310C
#define IOW_FORMAT_YV12_INTERLACED       0x320C
#define IOW_FORMAT_UYVY_INTERLACED       0x3010
#define IOW_FORMAT_YUY2_INTERLACED       0x3110
#define IOW_FORMAT_YVYU_INTERLACED       0x3210
#define IOW_FORMAT_V422_INTERLACED       0x3310
#define IOW_FORMAT_AYUV_INTERLACED       0x3020

#define IOW_PNAME_CLASS                       1
#define IOW_PNAME_ID_STRING                   2
#define IOW_PNAME_TITLE                       3
#define IOW_PNAME_DISPLAY                     4
#define IOW_PNAME_BUFFER_SIZE                 5
#define IOW_PNAME_SRC_POSITION                6
#define IOW_PNAME_SRC_SIZE                    7
#define IOW_PNAME_DST_POSITION                8
#define IOW_PNAME_DST_SIZE                    9
#define IOW_PNAME_FORMAT                     10
#define IOW_PNAME_USERPTR                    11
#define IOW_PNAME_DELEGPTR                   12
#define IOW_PNAME_GLOBAL_ALPHA               13
#define IOW_PNAME_SWAP_INTERVAL              14
#define IOW_PNAME_BRIGHTNESS                 15
#define IOW_PNAME_CONTRAST                   16
#define IOW_PNAME_HUE                        17
#define IOW_PNAME_SATURATION                 18
#define IOW_PNAME_LAYER                      19
#define IOW_PNAME_USAGE                      20
#define IOW_PNAME_DELEGATE                   21
#define IOW_PNAME_MANAGED                    22
#define IOW_PNAME_VISIBLE                    23
#define IOW_PNAME_FOCUS                      24
#define IOW_PNAME_SOURCE_ALPHA               25
#define IOW_PNAME_SENSITIVE                  26
#define IOW_PNAME_POINTER_FOCUS              27
#define IOW_PNAME_FREEZE                     28

#define IOW_TYPE_INVALID                      0
#define IOW_TYPE_INT32                        1
#define IOW_TYPE_INT64                        2
#define IOW_TYPE_FLOAT32                      3

#define IOW_USAGE_CPU                   (1 << 0)
#define IOW_USAGE_NATIVE                (1 << 1)
#define IOW_USAGE_OPENGL_ES1            (1 << 2)
#define IOW_USAGE_OPENGL_ES2            (1 << 3)
#define IOW_USAGE_OPENVG                (1 << 4)
#define IOW_USAGE_VIDEO                 (1 << 5)
#define IOW_USAGE_CAPTURE               (1 << 6)

#define IOW_ZORDER_BOTTOM                     0
#define IOW_ZORDER_LOWER                      1
#define IOW_ZORDER_HIGHER                     2
#define IOW_ZORDER_TOP                        3

typedef void *iow_context_t;
typedef void *iow_window_t;

typedef struct {
    int                   type;
    int                   delegate;
    uint64_t              timestamp;
    void                 *ptr;
    union {
        struct {
            int           wid;
        } close;
        struct {
            int           qid;
            unsigned int  wid;
        } create;
        struct {
            unsigned int  wid;
            int           sid;
        } realize;
        struct {
            unsigned int  wid;
            int           pname;
        } property;
        struct {
            unsigned int  wid;
            int           state;
        } focus;
        struct {
            int           index;
            union {
                int       i;
                int64_t   l;
                float     f;
            } value;
        } state;
        struct {
            int           index;
            union {
                int       i;
                int64_t   l;
                float     f;
            } value;
        } input;
        struct {
            int           index;
            int           count;
        } jog;
        struct {
            int           index;
            int           select;
            int           x;
            int           y;
        } pointer;
        struct {
            int           index;
            int           x;
            int           y;
            int           z;
        } joystick;
        struct {
            int           index;
            unsigned int  flags;
            unsigned int  modifiers;
            unsigned int  key_cap;
            unsigned int  key_scan;
            unsigned int  key_sym;
        } keyboard;
        struct {
            int           data[4];
        } user;
    } data;
} iow_event_t;

typedef struct {
    int          type;
    union {
        int32_t  i;
        int64_t  l;
        float    f;
    } u;
} iow_state_t;

/* core API function prototypes */

/* io-winmgr client connection */
int iow_attach(iow_context_t *pctx, int idx);
void iow_detach(iow_context_t ctx);
int iow_sidlist(iow_context_t ctx, int *sids, int size, int *nsids);

/* window related */

/* owned windows */
int iow_window_add_buffer(iow_window_t win, int *next_sid);
int iow_window_create(iow_window_t *win, iow_context_t ctx);
void iow_window_free(iow_window_t win);
int iow_window_post(iow_window_t win, int sid, int *next_sid, int dirty[4], int flags);
int iow_window_realize(iow_window_t win);

/* external windows */
int iow_window_attach(iow_window_t *win, iow_context_t ctx, int wid);
void iow_window_detach(iow_window_t win);

/* any type of window */
int iow_window_class(iow_window_t win, const char *str);
int iow_window_delegate(iow_window_t win, iow_window_t deleg);
int iow_window_get_brightness(iow_window_t win, int *pbrightness);
int iow_window_get_buffer_size(iow_window_t win, int *pw, int *ph);
int iow_window_get_class(iow_window_t win, char *str, size_t n);
int iow_window_get_contrast(iow_window_t win, int *pcontrast);
int iow_window_get_delegptr(iow_window_t win, void **pdelegptr);
int iow_window_get_display(iow_window_t win, int *pdisplay);
int iow_window_get_dst_position(iow_window_t win, int *px, int *py);
int iow_window_get_dst_size(iow_window_t win, int *pw, int *ph);
int iow_window_get_focus(iow_window_t win, int *penabled);
int iow_window_get_format(iow_window_t win, int *pformat);
int iow_window_get_freeze(iow_window_t win, int *pfreeze);
int iow_window_get_global_alpha(iow_window_t win, int *palpha);
int iow_window_get_hue(iow_window_t win, int *phue);
int iow_window_get_hwvsync(iow_window_t win, int *phwvsync);
int iow_window_get_id_string(iow_window_t win, char *str, size_t n);
int iow_window_get_layer(iow_window_t win, int *player);
int iow_window_get_multisampled(iow_window_t win, int *pmultisampled);
int iow_window_get_managed(iow_window_t win, int *pmanaged);
int iow_window_get_pointer_focus(iow_window_t win, int *penabled);
int iow_window_get_saturation(iow_window_t win, int *psaturation);
int iow_window_get_sensitive(iow_window_t win, int *psensitive);
int iow_window_get_source_alpha(iow_window_t win, int *penabled);
int iow_window_get_src_position(iow_window_t win, int *x, int *y);
int iow_window_get_src_size(iow_window_t win, int *w, int *h);
int iow_window_get_swap_interval(iow_window_t win, int *interval);
int iow_window_get_title(iow_window_t win, char *str, size_t n);
int iow_window_get_usage(iow_window_t win, int *pusage);
int iow_window_get_userptr(iow_window_t win, void **puserptr);
int iow_window_get_visible(iow_window_t win, int *pvisible);
int iow_window_set_brightness(iow_window_t win, int brightness);
int iow_window_set_buffer_size(iow_window_t win, int w, int h);
int iow_window_set_contrast(iow_window_t win, int contrast);
int iow_window_set_delegptr(iow_window_t win, void *delegptr);
int iow_window_set_display(iow_window_t win, int display);
int iow_window_set_dst_position(iow_window_t win, int x, int y);
int iow_window_set_dst_size(iow_window_t win, int w, int h);
int iow_window_set_focus(iow_window_t win, int enabled);
int iow_window_set_format(iow_window_t win, int format);
int iow_window_set_freeze(iow_window_t win, int freeze);
int iow_window_set_global_alpha(iow_window_t win, int alpha);
int iow_window_set_hue(iow_window_t win, int hue);
int iow_window_set_id_string(iow_window_t win, const char *str);
int iow_window_set_layer(iow_window_t win, int layer);
int iow_window_set_multisampled(iow_window_t win, int multisampled);
int iow_window_set_managed(iow_window_t win, int managed);
int iow_window_set_pointer_focus(iow_window_t win, int enabled);
int iow_window_set_saturation(iow_window_t win, int saturation);
int iow_window_set_sensitive(iow_window_t win, int sensitive);
int iow_window_set_source_alpha(iow_window_t win, int enabled);
int iow_window_set_src_position(iow_window_t win, int x, int y);
int iow_window_set_src_size(iow_window_t win, int w, int h);
int iow_window_set_swap_interval(iow_window_t win, int interval);
int iow_window_set_title(iow_window_t win, const char *str);
int iow_window_set_usage(iow_window_t win, int usage);
int iow_window_set_userptr(iow_window_t win, void *userptr);
int iow_window_set_visible(iow_window_t win, int visible);
int iow_window_sidlist(iow_window_t win, int *sids, int size, int *nsids);
int iow_window_update(iow_window_t win);
int iow_window_wid(iow_window_t win);
int iow_window_zorder(iow_window_t iow_win, int pos);

/* event related */
int iow_event_get(iow_context_t ctx, iow_event_t *ev, int ev_size, uint64_t timeout);
int iow_event_send(iow_window_t win, const iow_event_t *ev, int ev_size);

/* state related */
int iow_state_get(iow_context_t ctx, int index, iow_state_t *value);
int iow_state_set(iow_context_t ctx, int index, const iow_state_t *value);

/* to queue enable transact for set_properties and post */
int iow_lock_windows();
int iow_unlock_windows(iow_window_t win);

#endif /* _WINMGR_IOW_H_ */

__SRCVERSION( "$URL$ $Rev$" )
