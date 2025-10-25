DEFCOMPILER_TYPE_x86=$(if $(filter qnx4,$(SYSNAME)),wcc,gcc)

USE_ROOT_INCLUDE_wcc=$(call mk_use_list, usr/include) /src/dos/watcom/h
USE_ROOT_LIB_wcc=$(call mk_use_list, $(CPUDIR)/lib $(CPUDIR)/usr/lib) /src/dos/watcom/lib386/nt /src/dos/watcom/lib386

#if WIN32_ENVIRON == mingw && use_install_root, then we need to specifically
#look in the INSTALL_ROOT_HDR, since mingw only searches /usr/include/mingw :-(
USE_ROOT_INCLUDE_gcc=$(if $(filter mingw,$(WIN32_ENVIRON)),$(if $(USE_INSTALL_ROOT),$(INSTALL_ROOT_HDR))) $(call mk_use_list, usr/include$(w32_env_inc_$(WIN32_ENVIRON)))
USE_ROOT_LIB_gcc=$(call mk_use_list, $(CPUDIR)/lib $(CPUDIR)/usr/lib $(if $(filter mingw,$(WIN32_ENVIRON)),lib lib/w32api))

USE_ROOT_INCLUDE=$(USE_ROOT_INCLUDE_$(COMPILER_TYPE))
USE_ROOT_LIB=$(USE_ROOT_LIB_$(COMPILER_TYPE))

INSTALL_ROOT_AR=$(INSTALL_ROOT_win32)/$(CPUDIR)
INSTALL_ROOT_EX=$(INSTALL_ROOT_win32)/$(CPUDIR)
INSTALL_ROOT_SO=$(INSTALL_ROOT_win32)/$(CPUDIR)
INSTALL_ROOT_HDR=$(INSTALL_ROOT_win32)/usr/include

IMAGE_PREF_AR_gcc=lib
IMAGE_PREF_AR_wcc=
IMAGE_PREF_AR=$(IMAGE_PREF_AR_$(COMPILER_TYPE))

IMAGE_SUFF_AR_gcc=.a
IMAGE_SUFF_AR_wcc=$(MEMMODEL_TAG).lib
IMAGE_SUFF_AR=$(IMAGE_SUFF_AR_$(COMPILER_TYPE))

IMAGE_PREF_EX=
IMAGE_SUFF_EX=.exe

IMAGE_PREF_SO=
IMAGE_SUFF_SO=.dll

CC_win32_x86_wcc += -w3
LD_win32_x86_wcc += -M

WIN32_DEFS += -D__X86__ -D__LITTLEENDIAN__
# Select between Cygwin & Mingw - default to mingw 
ifndef WIN32_ENVIRON
WIN32_ENVIRON=mingw
endif
w32_env_inc_cygwin=
w32_env_inc_mingw=
w32_env_gcc_cygwin=$(WIN32_DEFS)
w32_env_gcc_mingw=$(WIN32_DEFS)
w32_env_qcc_cygwin=-Vgcc_cygwin 
w32_env_qcc_mingw=-Vgcc_mingw
CC_win32_x86_gcc += $(w32_env_gcc_$(WIN32_ENVIRON)) 
AS_win32_x86_gcc += $(w32_env_gcc_$(WIN32_ENVIRON))
LR_win32_x86_gcc += $(w32_env_gcc_$(WIN32_ENVIRON))
LD_win32_x86_gcc += $(w32_env_gcc_$(WIN32_ENVIRON))
CC_win32_x86_gcc_qcc += $(w32_env_qcc_$(WIN32_ENVIRON))
AS_win32_x86_gcc_qcc += $(w32_env_qcc_$(WIN32_ENVIRON))
LR_win32_x86_gcc_qcc += $(w32_env_qcc_$(WIN32_ENVIRON))
LD_win32_x86_gcc_qcc += $(w32_env_qcc_$(WIN32_ENVIRON))

# So all Win32 apps get command line wildcarding.
#SRCVPATH__wcc=$(MKFILES_ROOT)
#SRCS__wcc=wildargv.c
SRCVPATH+=$(SRCVPATH_$(filter a so dll,$(VARIANT_LIST))_$(COMPILER_TYPE))
SRCS+=$(SRCS_$(filter a so dll,$(VARIANT_LIST))_$(COMPILER_TYPE))

SONAME=$(empty)

VERSION_TAG_SO=$(space)

# When doing a shared object, we also want to create/install an import library
BUILDNAME_IM=$(IMAGE_PREF_AR)$(NAME)$(VARIANT_TAG).dll.a
FULLNAME_IM=$(CURDIR)/$(BUILDNAME_IM)
INSTALLNAME_IM=$(INSTALL_ROOT_$(BUILD_TYPE))/lib/$(BUILDNAME_IM)
ld_SO=-Wl,--out-implib -Wl,$(FULLNAME_IM)
ld_DLL=$(ld_SO)
LD_win32_x86_gcc_gcc += $(ld_$(BUILD_TYPE))
LD_win32_x86_gcc_qcc += $(ld_$(BUILD_TYPE))
win32_install_extra_SO=-$(CP_HOST) $(BUILDNAME_IM) $(INSTALLNAME_IM) $(NEWLINE)
win32_install_extra_DLL=$(win32_install_extra_SO)
install_extra+=$(win32_install_extra_$(BUILD_TYPE))
