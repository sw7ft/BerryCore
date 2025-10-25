ifndef DEFCOMPILER_TYPE
DEFCOMPILER_TYPE=gcc
endif

# The ICC compiler overrides some of our header files :-(, so we have
# to make sure their directories get included before our /usr/include.
URI_COMPILER_icc=$(IA32ROOT)/Include

USE_ROOT_INCLUDE=$(URI_COMPILER_$(COMPILER_TYPE)) $(call mk_use_list, usr/include)
USE_ROOT_LIB=$(call mk_use_list, $(ifeq (gcc,$(DEFCOMPILER_TYPE),if $(GCC_VERSION),$(CPUDIR)/lib/gcc/$(GCC_VERSION))) $(CPUVARDIR)/lib $(CPUVARDIR)/usr/lib)

INSTALL_ROOT_AR=$(INSTALL_ROOT_nto)/$(CPUVARDIR)
INSTALL_ROOT_ARSHR=$(INSTALL_ROOT_nto)/$(CPUVARDIR)
INSTALL_ROOT_EX=$(INSTALL_ROOT_nto)/$(CPUVARDIR)
INSTALL_ROOT_SO=$(INSTALL_ROOT_nto)/$(CPUVARDIR)
INSTALL_ROOT_DLL=$(INSTALL_ROOT_nto)/$(CPUVARDIR)
INSTALL_ROOT_HDR=$(INSTALL_ROOT_nto)/usr/include

IMAGE_PREF_AR=lib
IMAGE_SUFF_AR=.a

IMAGE_PREF_ARSHR=lib
IMAGE_SUFF_ARSHR=.a

IMAGE_PREF_EX=
IMAGE_SUFF_EX=

IMAGE_PREF_SO=lib
IMAGE_SUFF_SO=.so

ifneq ($(BUILDENV),iox)
IMAGE_PREF_DLL=
IMAGE_SUFF_DLL=.so
else
IMAGE_PREF_DLL=lib
IMAGE_SUFF_DLL=.dll
endif

LD_PATHOPT_qcc=-L -Wl,--rpath-link	

include $(MKFILES_ROOT)/$(OS)_$(CPU).mk
