
#define HAVE_ATEXIT

/* We default to the "aapcs-linux" ABI so that enums are int-sized by
   default.  */
#undef  ARM_DEFAULT_ABI
#define ARM_DEFAULT_ABI ARM_ABI_AAPCS_LINUX

#undef SIZE_TYPE
#define SIZE_TYPE "unsigned int"

#undef PTRDIFF_TYPE
#define PTRDIFF_TYPE "int"

#undef DEFAULT_SIGNED_CHAR
#define DEFAULT_SIGNED_CHAR  1

#define	OBJECT_FORMAT_ELF

#undef TARGET_OS_CPP_BUILTINS
#define TARGET_OS_CPP_BUILTINS() \
do { \
 	TARGET_BPABI_CPP_BUILTINS(); \
	NTO_TARGET_OS_CPP_BUILTINS(); \
	builtin_define ("__ARM__"); \
	builtin_define ("__arm__"); \
} while (0)

#undef SUBTARGET_ASM_FLOAT_SPEC
#define SUBTARGET_ASM_FLOAT_SPEC \
"%{!mfloat-abi:-mfloat-abi=softfp} %{!mfpu:-mfpu=neon-vfpv3}"

#undef CPP_APCS_PC_DEFAULT_SPEC
#define CPP_APCS_PC_DEFAULT_SPEC "-D__APCS_32__"

#undef	SUBTARGET_CPP_SPEC
#define	SUBTARGET_CPP_SPEC \
QNX_CPP_SPEC \
"%{!mlittle-endian: %{!mbig-endian:-mlittle-endian}} \
 %{mlittle-endian:-D__ARMEL__ -U__ARMEB__} \
 %{mbig-endian:-D__ARMEB__ -U__ARMEL__} \
 -mthumb %{!mcpu:-mcpu=cortex-a9}"

 //%{restrict-it:-mrestrict-it} on by default
#undef	CC1_SPEC
#define	CC1_SPEC \
"-mrestrict-it"

/* Call the function profiler with a given profile label.
   This is _mcount on other nto's.  It is mcount on ntoarm.  Leave it,
   or make sure it is also changed in lib/c/prof/arm/profile.h.  */
#undef ARM_FUNCTION_PROFILER
#define ARM_FUNCTION_PROFILER(STREAM, LABELNO)				\
{									\
  fprintf (STREAM, "\tpush {lr}\n");					\
  fprintf (STREAM, "\tbl\tmcount%s\n", NEED_PLT_RELOC ? "(PLT)" : "");	\
}

#undef SUBTARGET_EXTRA_SPECS
#define SUBTARGET_EXTRA_SPECS                           \
{ "subtarget_asm_float_spec", SUBTARGET_ASM_FLOAT_SPEC }, \


#undef CLEAR_INSN_CACHE
#define CLEAR_INSN_CACHE(BEG, END)                                      \
{                                                                       \
 register unsigned long _beg __asm ("a1") = (unsigned long) (BEG);      \
  register unsigned long _len __asm ("a2") = (unsigned long) (END) - (unsigned long) (BEG); \
  register unsigned long _flg __asm ("a3") = 0x1000000;			\
  __asm __volatile ("bl	msync"						\
                    : "=r" (_beg)					\
                    : "r" (_beg), "r" (_len), "r" (_flg) : "lr");		\
}

#undef  DEFAULT_STRUCTURE_SIZE_BOUNDARY
#define DEFAULT_STRUCTURE_SIZE_BOUNDARY 8

#define USE_OLD_ATBASE

#define SUBTARGET_OVERRIDE_OPTIONS NTO_OVERRIDE_ALIGNED_ACCESS

#define NTO_OVERRIDE_ALIGNED_ACCESS
