/* Base configuration for all QNX Neutrino targets
 *   Copyright (C) 2006
 *   Free Software Foundation, Inc.
 *
 * This file is part of GCC.
 *
 * GCC is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * GCC is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GCC; see the file COPYING.  If not, write to
 * the Free Software Foundation, 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.  */

/**
 *  retrieve gcc version...when bootstrapping is enabled
 *  WARNING. --disable-bootstrap causes this to return the host's gcc version
 */
#define PREP_QUOTE(...) #__VA_ARGS__
#define QUOTE(...) PREP_QUOTE(__VA_ARGS__)
//#define GCC_VER QUOTE(__GNUC__.__GNUC_MINOR__.__GNUC_PATCHLEVEL__)

#define GCC_VER "9.3.0"

#undef GCC_DRIVER_HOST_INITIALIZATION
#define GCC_DRIVER_HOST_INITIALIZATION \
do { \
  const char *QNX_HOST = env.get ("QNX_HOST"); \
  if (!QNX_HOST) fatal_error (input_location, "$QNX_HOST not set."); \
  \
  const char *QNX_TARGET = env.get ("QNX_TARGET"); \
  if (!QNX_TARGET) fatal_error (input_location, "$QNX_TARGET not set.");\
  \
  const char *QNX_PREBUILT_GCCLIB = env.get ("QNX_PREBUILT_GCCLIB"); \
  if (!QNX_PREBUILT_GCCLIB) \
    fatal_error (input_location, "ERROR: $QNX_PREBUILT_GCCLIB not set.");\
  \
  const char *QNX_PREBUILT = env.get ("QNX_PREBUILT"); \
  if (!QNX_PREBUILT) fatal_error (input_location, "$QNX_PREBUILT not set.");\
  \
  const char *QNX_PREBUILT_BIN = concat (QNX_PREBUILT, "/bin", NULL); \
  const char *QNX_PREBUILT_SYSLIB = concat (QNX_PREBUILT, "/lib", NULL); \
  const char *QNX_PREBUILT_USRLIB = concat (QNX_PREBUILT, "/usr/lib", NULL); \
  \
  add_prefix (&exec_prefixes, \
    QNX_PREBUILT_BIN, NULL, PREFIX_PRIORITY_B_OPT, 0, 0); \
  \
  add_prefix (&exec_prefixes, \
    QNX_PREBUILT_GCCLIB, NULL, PREFIX_PRIORITY_B_OPT, 0, 0); \
  \
  add_prefix (&startfile_prefixes, \
    QNX_PREBUILT_USRLIB, NULL, PREFIX_PRIORITY_B_OPT, 0, 0); \
  \
  add_prefix (&startfile_prefixes, \
    QNX_PREBUILT_SYSLIB, NULL, PREFIX_PRIORITY_B_OPT, 0, 0); \
  \
  add_prefix (&startfile_prefixes, \
    QNX_PREBUILT_GCCLIB, NULL, PREFIX_PRIORITY_B_OPT, 0, 0); \
  \
} while (0)

#if QNX_ENABLE_RELRO
#define QNX_RELRO_SPEC "-zrelro -znow"
#else
#define QNX_RELRO_SPEC ""
#endif

/* Don't assume anything about the header files.  */
/* System headers are not C++-aware.  */
//#undef SYSTEM_IMPLICIT_EXTERN_C
//#define SYSTEM_IMPLICIT_EXTERN_C 0

/* Allow stabs and dwarf, and make dwarf the default for Neutrino */
#undef PREFERRED_DEBUGGING_TYPE
#undef DBX_DEBUGGING_INFO
#undef DWARF_DEBUGGING_INFO
#undef DWARF2_DEBUGGING_INFO

#define PREFERRED_DEBUGGING_TYPE DWARF2_DEBUG
#define DBX_DEBUGGING_INFO
#define DWARF_DEBUGGING_INFO 1
#define DWARF2_DEBUGGING_INFO 1

#define SUPPORTS_WEAK 1

#undef MD_EXEC_PREFIX
#undef MD_STARTFILE_PREFIX

#ifdef HAVE_GNU_INDIRECT_FUNCTION
#define GNU_INDIRECT_FUNCTION if (HAVE_GNU_INDIRECT_FUNCTION) \
builtin_define ("__GNU_INDIRECT_FUNCTION__");
#else
#define GNU_INDIRECT_FUNCTION
#endif

// Q_OS_BLACKBERRY is a BB10 Cascades symbol, now serves as BB10 id now

#define NTO_TARGET_OS_CPP_BUILTINS()           \
do {                                           \
	builtin_define ("__QNX__");                  \
	builtin_define ("__QNXNTO__");               \
	builtin_define ("__unix__");                 \
	builtin_define ("__unix");                   \
	builtin_define ("__ELF__");                  \
	builtin_assert ("system=posix");             \
	builtin_assert ("system=qnx");               \
	builtin_assert ("system=nto");               \
	builtin_assert ("system=qnxnto");            \
	builtin_define ("__PRAGMA_PACK_PUSH_POP__"); \
	GNU_INDIRECT_FUNCTION                        \
} while (0)

/* Don't set libgcc.a's gthread/pthread symbols to weak, as our
 *   libc has them as well, and we get problems when linking static,
 *   as libgcc.a will get a symbol value of 0.  */
#define GTHREAD_USE_WEAK 0

#undef THREAD_MODEL_SPEC
#define THREAD_MODEL_SPEC "posix"

/* Under Neutrino, there is one set of header files for all targets. wchar_t is
 *   defined as a 32 bit unsigned integer */
#undef WCHAR_TYPE
#define WCHAR_TYPE "unsigned int"

#undef WCHAR_TYPE_SIZE
#define WCHAR_TYPE_SIZE 32

#undef WINT_TYPE
#define WINT_TYPE "long int"
//#define WINT_TYPE "int"

#undef WINT_TYPE_SIZE
#define WINT_TYPE_SIZE 32

#define TARGET_POSIX_IO

/* Determine what functions are present at the runtime;
 *   all new versions of QNX have C99 functions.  */
#undef TARGET_LIBC_HAS_FUNCTION
#define TARGET_LIBC_HAS_FUNCTION default_libc_has_function

#undef GOMP_SELF_SPECS
#define GOMP_SELF_SPECS ""

#if defined(HAVE_LD_EH_FRAME_HDR)
#  if defined LINK_EH_SPEC
#    undef LINK_EH_SPEC
#  endif
#define LINK_EH_SPEC "%{!static|static-pie:--eh-frame-hdr} "
#endif

/* Remove the default C++ headers so we can select via -stdlib */
#undef GPLUSPLUS_INCLUDE_DIR
#undef GPLUSPLUS_TOOL_INCLUDE_DIR
#undef GPLUSPLUS_BACKWARD_INCLUDE_DIR

/* Define LIBSTDCXX so we can select the implementation based on -stdlib */
struct cl_decoded_option;
extern const char *nto_select_libstdcxx(struct cl_decoded_option* options, unsigned int options_count);
#define LIBSTDCXX nto_select_libstdcxx(new_decoded_options, j)
#define LIBSTDCXX_PROFILE LIBSTDCXX
extern const char *nto_select_libstdcxx_static(void);
#define LIBSTDCXX_STATIC nto_select_libstdcxx_static()


#define DEFAULT_STDLIB_SPEC "|!stdlib=*"
#if DEFAULT_STDLIB_LIBSTDCXX
#define NTO_EXTRA_LIBSTDCXX_SPEC DEFAULT_STDLIB_SPEC
#define NTO_EXTRA_LIBCXX_SPEC ""
#elif DEFAULT_STDLIB_LIBCXX
#define NTO_EXTRA_LIBCXX_SPEC DEFAULT_STDLIB_SPEC
#define NTO_EXTRA_LIBSTDCXX_SPEC ""
#else
#define NTO_EXTRA_LIBSTDCXX_SPEC ""
#define NTO_EXTRA_LIBCXX_SPEC ""
#endif

// C++11 threads depends on sysctl() in libsocket
// libcS has at least one get* function not in libc
// as-needed prevents multiple definitions but was preventing
// the weak sysctl symbol from being found. it required resetting no-as-needed
#undef LIB_SPEC
#define LIB_SPEC \
"-L=/lib -L=/usr/lib -L%:getenv(QNX_PREBUILT_GCCLIB /)\
%{shared|fpic|fPIC|fpie|fPIE: -rpath-link==/lib -rpath-link==/usr/lib \
 -rpath-link=%:getenv(QNX_PREBUILT_GCCLIB /)} \
 -lsocket -lc --as-needed -lcS"

#undef LIBGCC_SPEC
#define LIBGCC_SPEC \
"%{fpie|fPIE: \
  %{static*:%{!fno-exceptions:-lgcc_eh} -lgcc}\
  %{!static*:-lgcc_s } } \
%{!fpie:%{!fPIE:%{!fno-exceptions:-lgcc_eh} -lgcc} }"

// crt1 references main() and must be excluded when building shared libraries ?
#undef STARTFILE_SPEC
#define STARTFILE_SPEC \
"%{!shared: %{pg:mcrt1.o%s}%{!pg:%{p:mcrt1.o%s}%{!p:%{profile:mcrt1.o%s} } } \
  %{!pg: \
    %{!static:crt1S.o%s} \
    %{static:crt1.o%s} } \
} \
crti.o%s \
\
%{!static:crtbeginS.o%s}%{static: crtbegin.o%s}"

#undef ENDFILE_SPEC
#define ENDFILE_SPEC \
"%{Ofast|ffast-math|funsafe-math-optimizations:crtfastmath.o%s} \
\
 %{!static:crtendS.o%s} \
 %{static:crtend.o%s} \
\
crtn.o%s"

// -pie unless -static is requested
#undef LINK_SPEC
#define LINK_SPEC \
"%{h*} %{v:-V} \
%{b} %{Wl,*:%*} -X \
%{!r:--build-id=md5} \
--warn-shared-textrel \
--eh-frame-hdr \
" QNX_RELRO_SPEC " \
%{G:-G} %{MAP:-Map mapfile} \
%{!shared: \
  %{!static: \
    %{!fpic:%{!fPIC:-fPIC} } \
  } } \
%{shared|-fpic|fPIC|Bdynamic:--dynamic-linker=usr/lib/ldqnx.so.2} \
%{fpie|fPIE:-pie} \
%{!fuse-ld:-fuse-ld=gold} \
%{-mlittle-endian:-EL} %{-mbig-endian:-EB} \
--sysroot=%:getenv(QNX_PREBUILT /)"

#undef QNX_CPP_SPEC
#define QNX_CPP_SPEC \
"%{mlittle-endian:-D__LITTLEENDIAN__} \
%{mbig-endian:-D__BIGENDIAN__} \
%{!mlittle-endian:%{!mbig-endian:-D__LITTLEENDIAN__}} \
-DQ_OS_BLACKBERRY \
-D_REENTRANT \
-D_POSIX_SOURCE \
-D_POSIX_C_SOURCE=200809L \
-D_XOPEN_SOURCE=700 \
-D_QNX_SOURCE \
-D_C99 \
-D_FORTIFY_SOURCE=2 \
-D_LARGEFILE64_SOURCE \
%{shared:-D__SLIB -D__SLIB_DATA_INDIRECT} \
%{cpp_cpu}%{cpp_arch} \
%{!fpic:%{!fPIC:%{!fno-pic:%{!fno-PIC:-fPIC} } } } \
-D_NTO_HDR_DIR_=%:getenv(QNX_INC /) \
-isystem %:getenv(QNX_INC /)"

#undef CPP_SPEC
#define CPP_SPEC QNX_CPP_SPEC

// libstdc++ include tree is set at build time and gcc uses it internally
// modifications in nto-cxx.c do not prevent gcc from checking
//

#undef CPLUSPLUS_CPP_SPEC
#define CPLUSPLUS_CPP_SPEC \
"-D_NO_CPP_INLINES \
 %{!nostdinc++: \
%{stdlib=libcpp|stdlib=libcpp-ne: \
-isystem %:getenv(QNX_INC /libcpp/c) \
-isystem %:getenv(QNX_INC /libcpp)} \
\
%{stdlib=libcpp-ne: -D_NO_EX } \
%{stdlib=libc++" NTO_EXTRA_LIBCXX_SPEC ": \
-isystem %:getenv(QNX_INC /libc++)} \
\
%{stdlib=libstdc++" NTO_EXTRA_LIBSTDCXX_SPEC ": \
-isystem %:getenv(QNX_INC /libstdc++/" GCC_VER ") \
-isystem %:getenv(QNX_INC /libstdc++/" GCC_VER "/" DEFAULT_TARGET_MACHINE ") \
-isystem %:getenv(QNX_INC /libstdc++/" GCC_VER "/backward) } }" \
CPP_SPEC

// CPP_SPEC (/include (libc)) appearing after C++ includes is significant

#undef ASM_SPEC
#define ASM_SPEC \
"%{EB:-EB} %{!EB:-EL} %{EL:-EL} \
%(asm_cpu_spec) \
%{fpic|fPIC|fpie|fPIE:--defsym __PIC__=1} \
%{mcpu=*:-mcpu=%*} \
%{march=*:-march=%*} \
%{mfloat-abi=*} %{mfpu=*}"

