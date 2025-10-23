/*
 * Copyright 2003, QNX Software Systems Ltd. All Rights Reserved.
 *
 * This source code may contain confidential information of QNX Software
 * Systems Ltd.  (QSSL) and its licensors. Any use, reproduction,
 * modification, disclosure, distribution or transfer of this software,
 * or any software which includes or is based upon any of this code, is
 * prohibited unless expressly authorized by QSSL by written agreement. For
 * more information (including whether this source code file has been
 * published) please email licensing@qnx.com.
 */

/*
 *
 *      hda_dll.h
 *        
 */

#ifndef _HDA_DLL_H_INCLUDED_
#define _HDA_DLL_H_INCLUDED_


#define		HDA_MINOR_VERSION		2


typedef
struct	ado_mixer_dll_params_hda
{
	HW_CONTEXT_T	*hw_context;
	uint8_t			codec_addr;
	int				(*write) ( HW_CONTEXT_T *hda , uint8_t codec , uint16_t nid , uint16_t verb , uint16_t param , uint32_t *responce );
	int32_t			(*init) (HW_CONTEXT_T *hda);
	char			*board_name;
	uint32_t		spare[29];
}
ado_mixer_dll_params_hda_t;

typedef
struct	ado_mixer_dll_callbacks_hda
{
	MIXER_CONTEXT_T 	*mix_context;
	int					(*play_stream_capabilities) (MIXER_CONTEXT_T *mix_context, uint8_t device, ado_pcm_cap_t *caps);
	int					(*play_stream_mixer_info) (MIXER_CONTEXT_T *mix_context, uint8_t device, ado_pcm_t *pcm);
	int					(*play_stream_setup) (MIXER_CONTEXT_T *mix_context, uint8_t device, uint32_t format, uint32_t voices, uint8_t stream, ado_pcm_subchn_t *subchn);
	int					(*play_stream_release) (MIXER_CONTEXT_T *mix_context, uint8_t device, uint8_t stream);
	int					(*cap_stream_capabilities) (MIXER_CONTEXT_T *mix_context, uint8_t device, ado_pcm_cap_t *caps);
	int					(*cap_stream_mixer_info) (MIXER_CONTEXT_T *mix_context, uint8_t device, ado_pcm_t *pcm);
	int					(*cap_stream_setup) (MIXER_CONTEXT_T *mix_context, uint8_t device, uint32_t format, uint32_t voices, uint8_t stream, ado_pcm_subchn_t *subchn);
	int					(*cap_stream_release) (MIXER_CONTEXT_T *mix_context, uint8_t device, uint8_t stream);
	uint32_t			spare[30];
}
ado_mixer_dll_callbacks_hda_t;

#endif

__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/services/audio/public/include/mixer/hda_dll.h $ $Rev: 219613 $" )
