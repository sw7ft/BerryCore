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
 *  sys/link.h
 *

 */
#ifndef __LINK_H_INCLUDED
#define __LINK_H_INCLUDED

#ifndef __ELF_H_INCLUDED
#include <sys/elf.h>
#endif

#ifndef __ELF_DYN_H_INCLUDED
#include <sys/elf_dyn.h>
#endif

#include <inttypes.h>
#include <stddef.h>

_C_STD_BEGIN

#if defined(__TIME_T)
typedef __TIME_T	time_t;
#undef __TIME_T
#endif

typedef struct link_map	Link_map;
struct link_map {
	_Uintptrt		l_addr;		/* base address */
	char			*l_name;	/* full soname of lib */
#if __PTR_BITS__ == 32	
	Elf32_Dyn		*l_ld;		/* _DYNAMIC in lib */
#elif __PTR_BITS__ == 64
	Elf64_Dyn		*l_ld;		/* _DYNAMIC in lib */
#else
#error __PTR_BITS__ not defined
#endif
	Link_map		*l_next;
	Link_map		*l_prev;
	char			*l_refname;	/* matching soname of lib */
	time_t			l_loaded;	/* time lib was loaded */
	char			*l_path;	/* full pathname of lib */
};

typedef enum {
	RT_CONSISTENT,				/* link_maps are consistent */
	RT_ADD,						/* Adding to link_map */
	RT_DELETE					/* Removeing a link_map */
} r_state_e;

typedef enum {
	RD_FL_NONE =	0,
	RD_FL_DBG =		(1<<1)		/* process may be being debugged */
} rd_flags_e;

typedef enum {
	RD_NONE = 0,
	RD_PREINIT,					/* Before .init() */
	RD_POSTINIT,				/* After .init() */
	RD_DLACTIVITY				/* dlopen() or dlclose() occured */
} rd_event_e;

#define	R_DEBUG_VERSION	2

struct r_debug {
	int				r_version;	/* R_DEBUG_VERSION */
	Link_map		*r_map;		/* Global link_map */
	_Uintptrt		r_brk;		/* void (*r_brk)(void) */
	r_state_e		r_state;	/* RT_* */
	_Uintptrt		r_ldbase;	/* ldqnx.so.1 base address */
	Link_map		*r_ldsomap;	/* ldqnx.so.1 link map */
	rd_event_e		r_rdevent;	/* RD_* */
	rd_flags_e		r_flags;	/* RD_FL_* */
};

#define LDD_EH_DLL_REPLAY 0x0001

#define LDD_EH_DLL_LOAD   0x0002
#define LDD_EH_DLL_UNLOAD 0x0004

/* this is what is passed to the event handler */
typedef struct ldd_eh_data {
  Link_map *l_map;
  uintptr_t text_addr;
  size_t    text_size;
  ptrdiff_t data_offset;
  size_t    data_size;
} Ldd_Eh_Data_t;

/* this is the prototype for the event handler */
typedef int (*Ldd_Eh_t)(Ldd_Eh_Data_t *ehd, void *eh_d_handle, unsigned flags);

struct dl_phdr_info {
#if __PTR_BITS__ == 32
	Elf32_Addr			dlpi_addr;
	const char			*dlpi_name;
	const Elf32_Phdr	*dlpi_phdr;
	Elf32_Half			dlpi_phnum;
#elif __PTR_BITS__ == 64
	Elf64_Addr			dlpi_addr;
	const char			*dlpi_name;
	const Elf64_Phdr	*dlpi_phdr;
	Elf64_Half			dlpi_phnum;
#else
#error __PTR_BITS__ not set properly
#endif
};

_C_STD_END

__BEGIN_DECLS

/* register an event handler */
void *__ldd_register_eh(_CSTD Ldd_Eh_t eh, void *eh_d_handle, unsigned flags);
/* deregister an event handler */
int __ldd_deregister_eh(void *ehh);

int dl_iterate_phdr( int (*callback) (const struct dl_phdr_info *info, size_t size, void *data), void *data); 

__END_DECLS

#ifdef _STD_USING
using _CSTD Ldd_Eh_t;
using _CSTD Ldd_Eh_Data_t;
#endif /* _STD_USING */

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_3_1/lib/c/public/sys/link.h $ $REV$")
#endif
