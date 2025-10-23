#ifndef _DRVR_COMMON_H_INCLUDED
#define _DRVR_COMMON_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#define DRVR_BUSTYPE_PCI       0x70636900  /* "pci" */
#define DRVR_BUSTYPE_ISA       0x69736100  /* "isa" */
#define DRVR_BUSTYPE_USB       0x75736200  /* "usb" */
#define DRVR_BUSTYPE_VME       0x766d6500  /* "vme" */
#define DRVR_BUSTYPE_PCCARD    0x70636300  /* "pcc" */
#define DRVR_BUSTYPE_IEEE1394  0x66697200  /* "fir" */

/* Miscellaneous utilities */
void nsec_delay(int nsec);
_Uint64t drvr_mphys(void *);

int nic_pic_irq(void *handle, int irr_mmask, int irr_smask,
    void (*irq_assert)(void *), void (*irq_clear)(void *));
void dma_cascade(int dchnl);

#endif

__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/drvr/public/drvr/common.h $ $Rev: 219996 $" )
