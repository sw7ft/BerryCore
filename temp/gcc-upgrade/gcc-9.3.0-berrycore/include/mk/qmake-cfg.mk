ifneq ($(QNXBUILDCFG),)

include Makefile

else

export QNXBUILDCFG=1

KSH_HOST ?= $(QNX_HOST)/usr/bin/ksh

include $(MKFILES_ROOT)/qmacros.mk

exports += SYSNAME
exports += GCC_VERSION
exports += BRANCH_TAG
exports += VERSION_REL
exports += PINFO_%
exports += %_HOST
exports += INSTALL_ROOT_%

envvars += $(foreach v,$(sort $(filter $(exports),$(.VARIABLES))),$v='$($v)')
envvars += QNXVFLAGS='$(strip $(VFLAGS))'
envvars += QNXROOTINCS='$(addprefix -I,$(USE_ROOT_INCLUDE))'
envvars += QNXROOTLIBS='$(addprefix -L,$(USE_ROOT_LIB))'

$(filter-out all clean iclean distclean mostlyclean maintainer-clean hinstall, $(MAKECMDGOALS)) all:
	+$(envvars) $(KSH_HOST) $(MKFILES_ROOT)/build-cfg $(MAKECMDGOALS)

clean iclean distclean mostlyclean maintainer-clean:
	-$(MAKE) -fMakefile AUTOMAKE=: AUTOCONF=: AUTOHEADER=: AUTORECONF=: ACLOCAL=: $@

hinstall: # nothing to do

endif
