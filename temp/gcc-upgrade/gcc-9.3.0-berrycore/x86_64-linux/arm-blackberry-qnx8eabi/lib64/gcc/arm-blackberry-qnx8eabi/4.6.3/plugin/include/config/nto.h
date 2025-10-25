/* Base configuration for all QNX Neutrino targets 
   Copyright (C) 2006
   Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING.  If not, write to
the Free Software Foundation, 51 Franklin Street, Fifth Floor,
Boston, MA 02110-1301, USA.  */

#undef TARGET_NEUTRINO
#define TARGET_NEUTRINO 1

#undef GCC_DRIVER_HOST_INITIALIZATION
#define GCC_DRIVER_HOST_INITIALIZATION \
do { \
    char *qnx_host = getenv ("QNX_HOST"); \
    char *qnx_target = getenv ("QNX_TARGET"); \
    if (qnx_host == NULL && qnx_target == NULL) \
      fatal_error ("environment variables QNX_HOST and QNX_TARGET not defined"); \
    if (qnx_host == NULL) \
      fatal_error ("environment variable QNX_HOST not defined"); \
    if (qnx_target == NULL) \
      fatal_error ("environment variable QNX_TARGET not defined"); \
    standard_libexec_prefix = concat (qnx_host, "/usr/lib/gcc/", NULL); \
    standard_exec_prefix = concat (qnx_host, "/usr/lib/gcc/", NULL); \
    standard_startfile_prefix = concat (qnx_host, "/usr/lib/", NULL); \
    standard_bindir_prefix = concat (qnx_host, "/usr/bin/", NULL); \
    tooldir_base_prefix = concat (qnx_host, "/usr/", NULL); \
    add_prefix (&exec_prefixes, standard_bindir_prefix, NULL, PREFIX_PRIORITY_LAST, 0, 0); \
} while (0)

#define QNX_SYSTEM_INCLUDES \
"%{!nostdinc: \
-isystem %$QNX_HOST/usr/lib/gcc/" DEFAULT_TARGET_MACHINE "/%v1.%v2.%v3/include \
-isystem %$QNX_TARGET/usr/include/c++/%v1.%v2.%v3 \
-isystem %$QNX_TARGET/usr/include/c++/%v1.%v2.%v3/" DEFAULT_TARGET_MACHINE " \
-isystem %$QNX_TARGET/usr/include/c++/%v1.%v2.%v3/backward \
-isysroot %$QNX_TARGET/ }"

/* Don't assume anything about the header files.  */
#undef NO_IMPLICIT_EXTERN_C
#define NO_IMPLICIT_EXTERN_C

/* Allow stabs and dwarf, and make dwarf the default for Neutrino */
#undef PREFERRED_DEBUGGING_TYPE
#undef DBX_DEBUGGING_INFO
#undef DWARF_DEBUGGING_INFO
#undef DWARF2_DEBUGGING_INFO

#define PREFERRED_DEBUGGING_TYPE DWARF2_DEBUG
#define DBX_DEBUGGING_INFO
#define DWARF_DEBUGGING_INFO
#define DWARF2_DEBUGGING_INFO

#define SUPPORTS_WEAK 1

#undef MD_EXEC_PREFIX
#undef MD_STARTFILE_PREFIX

#define NTO_TARGET_OS_CPP_BUILTINS()		\
do {                                            \
        builtin_define ("__QNX__");             \
        builtin_define ("__QNXNTO__");          \
        builtin_define ("__ELF__");             \
        builtin_assert ("system=posix");        \
        builtin_assert ("system=qnx");          \
        builtin_assert ("system=nto");          \
        builtin_assert ("system=qnxnto");       \
	builtin_define ("__PRAGMA_PACK_PUSH_POP__");		\
	if (HAVE_GNU_INDIRECT_FUNCTION)				\
	   builtin_define ("__GNU_INDIRECT_FUNCTION__");	\
    } while (0)

/* Determine whether the entire c99 runtime
   is present in the runtime library.  */
#define TARGET_C99_FUNCTIONS 1

/* Don't set libgcc.a's gthread/pthread symbols to weak, as our
   libc has them as well, and we get problems when linking static,
   as libgcc.a will get a symbol value of 0.  */
#define GTHREAD_USE_WEAK 0

#undef THREAD_MODEL_SPEC
#define THREAD_MODEL_SPEC "posix"

/* Under Neutrino, there is one set of header files for all targets. wchar_t is
   defined as a 32 bit unsigned integer */
#undef WCHAR_TYPE
#define WCHAR_TYPE "unsigned int"

#undef WCHAR_TYPE_SIZE
#define WCHAR_TYPE_SIZE 32

#undef WINT_TYPE
#define WINT_TYPE "long int"

#undef WINT_TYPE_SIZE
#define WINT_TYPE_SIZE 32

#define TARGET_POSIX_IO

#undef GOMP_SELF_SPECS
#define GOMP_SELF_SPECS ""

#define MFLIB_SPEC " %{fmudflap: -export-dynamic -lmudflap -lsocket\
 %{static:%(link_gcc_c_sequence) -lmudflap -lsocket -lbacktrace}} \
 %{fmudflapth: -export-dynamic -lmudflapth -lsocket\
 %{static:%(link_gcc_c_sequence) -lmudflapth -lsocket -lbacktrace}} "

#undef LINK_GCC_C_SEQUENCE_SPEC
#define LINK_GCC_C_SEQUENCE_SPEC \
  "%{static:--start-group} %G %L %{static:--end-group}%{!static:%G}"

