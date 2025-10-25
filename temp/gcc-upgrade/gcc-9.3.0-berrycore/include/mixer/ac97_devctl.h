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
 *      ac97_devclt.h
 *        
 */

#ifndef _AC97_DEVCTL_H_INCLUDED_
#define _AC97_DEVCTL_H_INCLUDED_

struct	ac97_reg_data
{
	uint16_t		reg;
	uint16_t		data;
};

#define		AC97_DEVCTL_REG_RD	_IOWR ('Z', 0x01, struct  ac97_reg_data)
#define		AC97_DEVCTL_REG_WR	_IOW ('Z', 0x02, struct  ac97_reg_data)

#endif

__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/services/audio/public/include/mixer/ac97_devctl.h $ $Rev: 219613 $" )
