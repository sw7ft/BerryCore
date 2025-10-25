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

#undef	TARGET_VERSION
#define	TARGET_VERSION fprintf(stderr, " (QNX/Neutrino/ARM ELF)");

#define	OBJECT_FORMAT_ELF

#undef TARGET_OS_CPP_BUILTINS
#define TARGET_OS_CPP_BUILTINS()                \
do {                                            \
 	TARGET_BPABI_CPP_BUILTINS(); 		\
	NTO_TARGET_OS_CPP_BUILTINS();		\
	builtin_define ("__ARM__");             \
} while (0)

#undef ASM_SPEC
#define ASM_SPEC \
"%{EB:-EB} %{!EB:-EL} %{EL:-EL} \
 %{fpic|fPIC:--defsym __PIC__=1} \
 %{mcpu=*:-mcpu=%*} \
 %{march=*:-march=%*} \
 %{mfloat-abi=*} %{mfpu=*} \
 %{mapcs-float:-mfloat} \
 %{!mfloat-abi=*: -mfloat-abi=softfp} \
 %{!march=*: -march=armv7-a} \
 %{!mfpu=*: -mfpu=vfpv3-d16} \
 -meabi=5" 

#define QNX_SYSTEM_LIBDIRS \
"-L %$QNX_TARGET/arm%{EB:be}%{!EB:le}-v7/lib/gcc/%v1.%v2.%v3 \
 -L %$QNX_TARGET/arm%{EB:be}%{!EB:le}-v7/lib \
 -L %$QNX_TARGET/arm%{EB:be}%{!EB:le}-v7/usr/lib \
 -L %$QNX_TARGET/arm%{EB:be}%{!EB:le}-v7/opt/lib \
 -rpath-link %$QNX_TARGET/arm%{EB:be}%{!EB:le}-v7/lib/gcc/%v1.%v2.%v3:\
%$QNX_TARGET/arm%{EB:be}%{!EB:le}-v7/lib:\
%$QNX_TARGET/arm%{EB:be}%{!EB:le}-v7/usr/lib:\
%$QNX_TARGET/arm%{EB:be}%{!EB:le}-v7/opt/lib "

#undef LIB_SPEC
#define LIB_SPEC \
  QNX_SYSTEM_LIBDIRS \
  "%{!symbolic: -lc -Bstatic %{static|nopie: -lc;:-lcS}}"

#undef LIBGCC_SPEC
#define LIBGCC_SPEC "-lgcc"

#undef STARTFILE_SPEC
#define STARTFILE_SPEC \
"%{!shared: %$QNX_TARGET/arm%{EB:be}%{!EB:le}-v7/lib/%{pg:m}%{p:mcrt1.o;pie:crt1S.o%s;static|nopie:crt1.o%s;:crt1S.o%s}\ } \
%$QNX_TARGET/arm%{EB:be}%{!EB:le}-v7/lib/crti.o crtbegin.o%s "

#undef ENDFILE_SPEC
#define ENDFILE_SPEC \
"crtend.o%s %$QNX_TARGET/arm%{EB:be}%{!EB:le}-v7/lib/crtn.o"

#undef LINK_SPEC
#define LINK_SPEC \
"%{h*} %{v:-V} \
 %{b} %{Wl,*:%*} \
 %{!r:--build-id=md5} \
 %{static:-Bstatic} \
 %{shared} \
 %{symbolic:-Bsymbolic} \
 %{G:-G} %{MAP:-Map mapfile} \
 %{!shared:-dynamic-linker /usr/lib/ldqnx.so.2} \
 -m armnto -X --hash-style=gnu \
 %{EB:-EB} %{!EB:-EL} %{EL:-EL}"

#undef CPP_APCS_PC_DEFAULT_SPEC
#define CPP_APCS_PC_DEFAULT_SPEC "-D__APCS_32__"

#undef	SUBTARGET_CPP_SPEC
#define	SUBTARGET_CPP_SPEC \
 QNX_SYSTEM_INCLUDES "\
 %(cpp_cpu) \
 %{!EB:-D__LITTLEENDIAN__ -D__ARMEL__} \
 %{EB:-D__BIGENDIAN__ -D__ARMEB__} \
 %{posix:-D_POSIX_SOURCE}"

#undef	CC1_SPEC
#define	CC1_SPEC " \
%{EB:-mbig-endian} %{!EB:-mlittle-endian}"

/* Call the function profiler with a given profile label. 
   This is _mcount on other nto's.  It is mcount on ntoarm.  Leave it,
   or make sure it is also changed in lib/c/prof/arm/profile.h.  */
#undef ARM_FUNCTION_PROFILER
#define ARM_FUNCTION_PROFILER(STREAM, LABELNO)  				\
{									\
  fprintf (STREAM, "\tpush {lr}\n");  	    			\
  fprintf (STREAM, "\tbl\tmcount%s\n", NEED_PLT_RELOC ? "(PLT)" : "");	\
}

#undef SUBTARGET_EXTRA_SPECS
#define SUBTARGET_EXTRA_SPECS                           \
  { "subtarget_asm_float_spec", SUBTARGET_ASM_FLOAT_SPEC }, \

#undef SUBTARGET_ASM_FLOAT_SPEC
#define SUBTARGET_ASM_FLOAT_SPEC "\
 %{mapcs-float:-mfloat} %{!mhard-float:-mfpu=softvfp} %{mhard-float:-mfpu=vfp}"

#undef CLEAR_INSN_CACHE
#define CLEAR_INSN_CACHE(BEG, END)                                      \
{                                                                       \
 register unsigned long _beg __asm ("a1") = (unsigned long) (BEG);      \
  register unsigned long _len __asm ("a2") = (unsigned long) (END) - (unsigned long) (BEG); \
  register unsigned long _flg __asm ("a3") = 0x1000000;			\
  __asm __volatile ("bl	msync"						\
                    : "=r" (_beg)					\
                    : "r" (_beg), "r" (_len), "r" (_flg));		\
}

#undef  DEFAULT_STRUCTURE_SIZE_BOUNDARY
#define DEFAULT_STRUCTURE_SIZE_BOUNDARY 8

#define USE_OLD_ATBASE
