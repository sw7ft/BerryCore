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
 *
 *      ac97_dll.h
 *        
 */

#ifndef _AC97_DLL_H_INCLUDED_
#define _AC97_DLL_H_INCLUDED_


#define		AC97_MINOR_VERSION		2


enum ac97_SRC
{
	AC97_FRONT_DAC_SRC,
	AC97_SURR_DAC_SRC,
	AC97_LFE_DAC_SRC,
	AC97_LR_ADC_SRC,
};


typedef
struct	ado_mixer_dll_params_ac97
{
	HW_CONTEXT_T	*hw_context;
	uint16_t		(*read) (HW_CONTEXT_T *hw_context, uint16_t reg);
	void			(*write) (HW_CONTEXT_T *hw_context, uint16_t reg, uint16_t val);
	int32_t			(*init) (HW_CONTEXT_T *hw_context);
	int32_t			spare1;
	void			(*warm_reset) (HW_CONTEXT_T *hw_context);
	void			(*cold_reset) (HW_CONTEXT_T *hw_context);
	uint32_t		spare[6];
}
ado_mixer_dll_params_ac97_t;

typedef
struct	ado_mixer_dll_callbacks_ac97
{
	MIXER_CONTEXT_T 	*mix_context;
	int32_t				(*SRC_test) (MIXER_CONTEXT_T * mix_context, enum ac97_SRC src, ado_pcm_cap_t * caps);
	int32_t				(*SRC_set) (MIXER_CONTEXT_T * mix_context, enum ac97_SRC src, int32_t * rate);
	/* limit of minor version 1 */
	uint16_t			power_modes;
	uint16_t			current_power_mode;
	int32_t				(*set_power_mode) (MIXER_CONTEXT_T * mix_context, uint16_t mode, uint8_t power_lost);
	uint32_t			reserved[11];
	/* limit of minor version 2 */
}
ado_mixer_dll_callbacks_ac97_t;

#endif

__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/services/audio/public/include/mixer/ac97_dll.h $ $Rev: 736302 $" )
