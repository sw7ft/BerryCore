#ifndef __SRCVERSION_H_GUARD
#define __SRCVERSION_H_GUARD

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
# define __SRCVERSION(__id)												\
	__asm__(".section .ident,\"SM\",%progbits,1; .asciz " #__id "; .previous");
#else
# define __SRCVERSION(__id)
#endif

#endif /* __SRCVERSION_H_GUARD */
