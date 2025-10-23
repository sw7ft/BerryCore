##
## If the [EXCLUDE_]OSLIST or [EXCLUDE_]CPULIST macros aren't set, figure out
## what target systems we can actually build based on the name of the
## host system.
##
## Used by the recurse.mk makefile.
##
# cd to "/" first so we don't get caught when building our uname utility.
ifndef HOST_SYSTEM
ifdef SYSNAME
HOST_SYSTEM:=$(SYSNAME)
else
# Extra space at end required under windows	
HOST_SYSTEM:=$(shell cd / && uname -s )
ifeq (QNX,$(HOST_SYSTEM))
# Extra space at end required under windows	
HOST_REVISION:=$(shell cd / && uname -r )
HOST_SYSTEM:=$(shell cd / && if test `printf %d $(HOST_REVISION)` -gt 0; then echo nto; else echo qnx4; fi)
endif
endif
endif

ifeq (qnx4,$(HOST_SYSTEM))
DEFEXCLUDE_CPULIST=sparc
DEFEXCLUDE_OSLIST=solaris
endif

ifeq (nto,$(HOST_SYSTEM))
OSLIST=nto
# find all the cpu's with processor support installed by looking in /etc/qcc
DEFCPULIST=$(sort $(patsubst %be,%,$(patsubst %le,%,$(notdir $(subst _nto,/,$(filter-out %++,$(basename $(notdir $(wildcard /etc/qcc/*_nto*.conf)))))))))
endif

ifeq (SunOS,$(HOST_SYSTEM))
DEFCPULIST=sparc x86 ppc mips sh arm
DEFOSLIST=solaris nto
endif

ifeq (Linux,$(HOST_SYSTEM))
DEFCPULIST=x86 ppc mips sh arm
DEFOSLIST=linux nto
endif

ifeq (Darwin,$(HOST_SYSTEM))
DEFCPULIST=x86 ppc mips sh arm
DEFOSLIST=darwin nto
endif

ifeq ($(CPULIST)$(EXCLUDE_CPULIST),)
CPULIST=$(DEFCPULIST)
EXCLUDE_CPULIST=$(DEFEXCLUDE_CPULIST)
endif

ifeq ($(OSLIST)$(EXCLUDE_OSLIST),)
OSLIST=$(DEFOSLIST)
EXCLUDE_OSLIST=$(DEFEXCLUDE_OSLIST)
endif
