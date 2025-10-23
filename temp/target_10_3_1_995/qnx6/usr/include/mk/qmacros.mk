#
# Supported pieces
#
compilers=gcc mcc tcc wcc icc $(EXTRA_COMPILER_NAMES)
cpus=x86 mips ppc sh arm sparc $(EXTRA_CPU_NAMES)
oses=qnx4 nto solaris win32 linux unix darwin $(EXTRA_OS_NAMES)

#Using $(NEWLINE) will cause a single newline character to be added
define NEWLINE 


endef

ifeq ($(firstword $(origin CPU)),environment)
CPU=
endif

ifeq ($(origin DEBUG),undefined)
DEBUG=$(DEFDEBUG)
endif

ifeq ($(origin NDEBUG),undefined)
ifneq ($(origin DEFNDEBUG),undefined)
NDEBUG=$(DEFNDEBUG)
endif
endif

ifeq ($(origin DEFOS),undefined)
DEFOS:=nto
endif

ifndef CURDIR
ifdef PWD
CURDIR:=$(PWD) # backwards compatability
else
CURDIR:=$(shell $(PWD_HOST))
endif
endif

empty:=
space:=$(empty) $(empty)
comma:=,

defsrcvpath:=
all_variants:=
variant_levels:=1 2 3 4 5 6 7 8 9

current_dir:=$(CURDIR)

include $(MKFILES_ROOT)/qlevel.mk
ifeq ($(common),)
include $(MKFILES_ROOT)/qlevel.mk
ifeq ($(common),)
include $(MKFILES_ROOT)/qlevel.mk
ifeq ($(common),)
include $(MKFILES_ROOT)/qlevel.mk
ifeq ($(common),)
include $(MKFILES_ROOT)/qlevel.mk
ifeq ($(common),)
include $(MKFILES_ROOT)/qlevel.mk
endif
endif
endif
endif
endif

defsrcvpath+= $(current_dir)

PROJECT_ROOT:=$(current_dir)
PROJECT:=$(notdir $(current_dir))

PRODUCT_ROOT:=$(patsubst %/$(PROJECT),%,$(current_dir))
PRODUCT:=$(notdir $(PRODUCT_ROOT))

ifneq ($(filter $(PRODUCT), a b c d e f g h i j k l m n o p q r s t u v w z y z),)
# Hack for 'utils' tree.
current_dir:=$(patsubst %/$(PRODUCT)/$(PROJECT),%,$(current_dir))
PRODUCT_ROOT:=$(patsubst %/$(PROJECT),%,$(current_dir))
PRODUCT:=$(notdir $(PRODUCT_ROOT))
endif

ifndef NAME
NAME=$(PROJECT)
endif

ifndef OS
OS:=$(DEFOS)
endif


VARIANT_LIST:=$(filter-out o $(compilers) $(oses) $(cpus), $(all_variants))

#BACKWARDS compatability stuff
PWD:=$(CURDIR)
COMPOUND_VARIANT:=$(VARIANT1)
VARIANTS:=$(VARIANT_LIST)
SORTED_VARIANTS:=$(sort $(VARIANT1))
SECTION:=$(VARIANT$(curr_variant))
SECTION_ROOT:=$(VARIANT$(curr_variant)_ROOT)

CPUDIR=$(CPU)$(filter le be, $(VARIANT_LIST))
CPUVARDIR=$(CPUDIR)$(CPUVARDIR_SUFFIX)

###
### NYI - needs work, adding non-g variant to search path
###
ifeq ($(PRE_SRCVPATH)$(filter g, $(VARIANT_LIST)),g)
PRE_SRCVPATH:=$(CPU_ROOT)/$(firstword $(subst $(space),.,$(filter-out g,$(VARIANT_LIST))) o)
endif

ifndef SRCVPATH
# Use absolute paths so we don't have to set directories in gdb
SRCVPATH:=$(PRE_SRCVPATH) $(defsrcvpath)
endif

SRCVPATH+=$(EXTRA_SRCVPATH)

metasrcs=$(foreach dir, $1, $(addprefix $(dir)/*., s S c cc cpp cxx $(EXTRA_SUFFIXES)))
ifndef SRCS
SRCS := $(wildcard *.nda $(call metasrcs, $(CURDIR) $(SRCVPATH)))
endif
LATE_SRCS=$(if $(LATE_SRCVPATH),$(wildcard $(call metasrcs,$(LATE_SRCVPATH))))

ifdef DEFFILE
EXCLUDE_OBJS += $(basename $(DEFFILE)).o
EXTRA_ASDEPS += $(DEFFILE)
endif

raw_objs = $(sort $(addsuffix .o, $(basename $(notdir $(SRCS) $(LATE_SRCS)))))
OBJS = $(filter-out $(EXCLUDE_OBJS), $(raw_objs)) $(EXTRA_OBJS)

ifeq ($(BUILDENV),qss)
VFLAG_le=-EL
VFLAG_be=-EB
else
VFLAG_le=
VFLAG_be=
endif
VFLAG_g=-g
VFLAG_16=-2
CCVFLAG_shared=-shared
ASVFLAG_shared=-shared
LDVFLAG_dll=-Wl,-Bsymbolic

VFLAG_dll=$(VFLAG_shared)
CCVFLAG_dll=$(CCVFLAG_shared)
ASVFLAG_dll=$(ASVFLAG_shared)
VFLAG_so=$(VFLAG_shared)
CCVFLAG_so=$(CCVFLAG_shared)
ASVFLAG_so=$(ASVFLAG_shared)

VARIANT_NAMES=$(addprefix VARIANT_,$(VARIANT_LIST)) BUILDENV_$(BUILDENV)

VFLAGS=$(foreach var,$(VARIANT_LIST), $(VFLAG_$(var)) $(VFLAG_$(CPU)_$(var)))
ASVFLAGS=$(VFLAGS) $(foreach var,$(VARIANT_LIST), $(ASVFLAG_$(var)))
ARVFLAGS_qcc=$(VFLAGS)
CCVFLAGS=$(VFLAGS) $(foreach var,$(VARIANT_LIST), $(CCVFLAG_$(var))) $(addprefix -D,$(VARIANT_NAMES))
LDVFLAGS=$(VFLAGS) $(foreach var,$(VARIANT_LIST), $(LDVFLAG_$(var)))

# Special flags for code that is called from kernel mode

CCVFLAGS_ISR=-D_ISR_SOURCE $(CCFLAGS_ISR_$(CPU)) $(foreach var,$(VARIANT_LIST),$(CCFLAGS_ISR_$(var)) $(CCFLAGS_ISR_$(CPU)_$(var)))
CCVFLAGS_ISR_EXCLUDE=$(CCFLAGS_ISR_EXCLUDE_$(CPU)) $(foreach var,$(VARIANT_LIST),$(CCFLAGS_ISR_EXCLUDE_$(var)) $(CCFLAGS_ISR_EXCLUDE_$(CPU)_$(var)))

ifndef INCVPATH
INCVPATH=$(SRCVPATH)
endif
ifndef PUBLIC_INCVPATH
defpublic_incvpath := $(firstword $(wildcard $(PROJECT_ROOT)/public/include* $(PROJECT_ROOT)/public*))
PUBLIC_INCVPATH = $(defpublic_incvpath)
endif
orig_incvpath := $(INCVPATH)
INCVPATH = . $(orig_incvpath) $(EXTRA_INCVPATH) $(PUBLIC_INCVPATH) $(INCTEST) $(USE_ROOT_INCLUDE)

ifdef LIBVPATH
LIBVPATH += $(EXTRA_LIBVPATH) 
else
LIBVPATH = . $(EXTRA_LIBVPATH) $(USE_ROOT_LIB)
endif

ifndef CONFIG_PATH
ifneq ($(wildcard $(PROJECT_ROOT)/config/*),)
CONFIG_PATH := $(PROJECT_ROOT)/config
endif
endif

FLAGS += $(FLAGS_$(basename $@)_$(CPU)) $(FLAGS_$(basename $@)) $(addprefix -I, $(INCVPATH)) $(DEBUG) $(EXTRA_FLAGS)

COMPILER_TYPE=$(firstword $(COMPILER) $(DEFCOMPILER_TYPE_$(CPU)) $(DEFCOMPILER_TYPE))

one_use_list=$(if $(strip $(1)),$(patsubst %//,%/,$(addsuffix /,$(strip $(1)))),/)
USE_ROOT_LIST=$(if $(USE_INSTALL_ROOT),$(call one_use_list,$(INSTALL_ROOT_$(strip $(1))))) $(call one_use_list,$(USE_ROOT_$(strip $(1))))
mk_use_list=$(foreach use,$(call USE_ROOT_LIST,$(OS)),$(addprefix $(use), $(1)))

FIND_HDR_DIR=$(patsubst %$(strip $(3)),%,$(firstword $(wildcard $(addsuffix $(strip $(2))/$(strip $(3)),$(call USE_ROOT_LIST,$(1))))))

include $(MKFILES_ROOT)/os_$(OS).mk
-include $(MKFILES_ROOT)/prod_$(PRODUCT).mk
-include $(MKFILES_ROOT)/version.mk

ASSEMBLER_TYPE:=$(firstword $(ASSEMBLER_TYPE) $(ASSEMBLER_TYPE_$(CPU)) $(COMPILER_TYPE))

memmodels_qnx4 = 3r 3s ms mm mc ml mh
memmodels_win32 = $(memmodels_qnx4)
memmodel = $(filter $(memmodels_$(OS)), $(VARIANT_LIST))
VFLAG_$(memmodel) = -$(memmodel)
memmodel_tag=$(subst m,,$(memmodel))

build_extensions=a so dll

silent_variants=be le o shared g $(build_extensions) $(memmodel) $(oses) $(cpus) $(silent_variants_$(CPU))

VARIANT_TAG=$(subst $(space),,$(foreach var,$(filter-out $(silent_variants) $(EXTRA_SILENT_VARIANTS),$(all_variants)),-$(var)))$(foreach var,$(filter g, $(VARIANT_LIST)),_$(var))$(foreach var,$(filter shared, $(VARIANT_LIST)),S)

conditional_munge=$(if $(filter-out undefined,$(origin $(1))),$(call $(1),$(2)),$(2))

LIBNAMES=$(foreach lib, $(LIBS), $(IMAGE_PREF_AR)$(call conditional_munge,libmunge,$(lib))$(IMAGE_SUFF_AR))
only_objs=$(filter-out $(EXTRA_DEPS) $(EXCLUDE_OBJS_$(BUILD_TYPE)) $(addprefix %/, $(LIBNAMES)), $^)

select_assembler := $(subst $(space),,$(foreach i,$(OS) $(CPU) $(ASSEMBLER_TYPE) $(COMPILER_DRIVER),_$(i)))
select_compiler  := $(subst $(space),,$(foreach i,$(OS) $(CPU) $(COMPILER_TYPE)  $(COMPILER_DRIVER),_$(i)))
linktype_static  := -static
linktype_dynamic := 


ASPREF = $(AS$(select_assembler))
ASPOST = $(ASPOST$(select_assembler))

CCPREF = $(CC$(select_compiler))
CCPOST = $(CCPOST$(select_compiler))

LDPREF = $(LD$(LINKER_TYPE)$(EX_CLASS)$(select_compiler)) $(linktype_$(LTYPE))
LDPOST = $(LD$(LINKER_TYPE)POST$(select_compiler))

ARPREF = $(AR$(select_compiler))
ARPOST = $(ARPOST$(select_compiler))

UMPREF = $(UM$(select_compiler))
UMPOST = $(UMPOST$(select_compiler))

OCPREF = $(OC$(select_compiler))

objopts = $(foreach obj, $(only_objs), $(OBJPREF_$(notdir $(obj))) $(obj) $(OBJPOST_$(notdir $(obj))))
libopts = $(foreach lib, $(LIBS), $(LIBPREF_$(notdir $(lib))) -l$(call conditional_munge,libmunge,$(lib)) $(LIBPOST_$(notdir $(lib))))

ifneq ($(filter %.cc %.cpp %.cxx, $(SRCS)),)
cplus_ind_qcc= -lang-c++
LDPREF += $(cplus_ind_$(COMPILER_DRIVER))
endif

ifeq ($(COMPILER_DRIVER),qcc)
ifeq ($(filter v7 hf spe, $(VARIANTS)),)
QCC_CONF_VARIANT=$(CPUVARDIR)
else
QCC_CONF_VARIANT=$(if $(filter arm,$(CPU)),$(CPU)v7$(filter hf,$(VARIANTS)),$(if $(filter ppc,$(CPU)),$(CPUDIR)spe))
endif
ifeq ($(wildcard $(QNX_HOST)/etc/qcc/gcc/$(GCC_VERSION)*/*$(QCC_CONF_VARIANT)*.conf),)
ALL_DEPENDENCIES=$(PRE_TARGET)
TARGET_INSTALL=
endif
endif

#
# An archive
#
CREATE_TYPE_a=AR
DEFINSTDIR_a=lib

#
# A shared object
#
CREATE_TYPE_so=SO
DEFINSTDIR_so=lib
ifndef SONAME_SO
SONAME_SO=$(notdir $@)
endif

#
# A Dynamic Link Library
#
CREATE_TYPE_dll=DLL
DEFINSTDIR_dll=lib/dll
ifndef SONAME_DLL
SONAME_DLL=$(notdir $@)
endif

#
# An executable
#
CREATE_TYPE_=EX
DEFINSTDIR_=bin

VARIANT_BUILD_TYPE=$(filter $(build_extensions),$(VARIANT_LIST))

BUILD_TYPE=$(CREATE_TYPE_$(VARIANT_BUILD_TYPE))
INSTALL_DIRECTORY = $(INSTALL_ROOT_$(BUILD_TYPE))/$(word 1,$(INSTALLDIR) $(DEFINSTDIR_$(VARIANT_BUILD_TYPE)))

ifndef VERSION_TAG_SO
VERSION_TAG_SO=$(foreach ver,$(firstword $(SO_VERSION) 1),.$(ver))
endif
INSTALL_TAIL=$(VERSION_TAG_$(BUILD_TYPE))

ifndef BUILDNAME
BUILDNAME=$(IMAGE_PREF_$(BUILD_TYPE))$(NAME)$(VARIANT_TAG)$(IMAGE_SUFF_$(BUILD_TYPE))
endif
FULLNAME=$(CURDIR)/$(BUILDNAME)
INSTALLNAME=$(INSTALL_DIRECTORY)/$(BUILDNAME)$(INSTALL_TAIL)

BUILDNAME_SAR=$(IMAGE_PREF_AR)$(NAME)$(VARIANT_TAG)S$(IMAGE_SUFF_AR)
FULLNAME_SAR=$(CURDIR)/$(BUILDNAME_SAR)
INSTALLNAME_SAR=$(INSTALL_DIRECTORY)/$(BUILDNAME_SAR)
install_extra_SO+=-$(CP_HOST) $(BUILDNAME_SAR) $(INSTALLNAME_SAR) $(NEWLINE)

install_extra += $(install_extra_$(BUILD_TYPE))

metasrcs=$(foreach dir, $1, $(addprefix $(dir)/*., s S c cc cpp cxx $(EXTRA_SUFFIXES)))

ifneq (darwin,$(OS))
LIBPATH_SEP=$(space)
else
LIBPATH_SEP=
endif
lib_path = $(foreach path_opt, $(if $(LD$(LINKER_TYPE)_PATHOPT_$(COMPILER_DRIVER)),$(LD$(LINKER_TYPE)_PATHOPT_$(COMPILER_DRIVER)),-L), $(addprefix $(path_opt)$(LIBPATH_SEP), $(LIBVPATH)))

ifndef CREATE_AR
define CREATE_AR 
  $(PRECREATE_AR)
  $(ARPREF) $(AROPTS) $@ $(only_objs) $(ARVFLAGS_$(COMPILER_DRIVER)) $(ARPOST)
  $(POSTCREATE_AR)
endef
endif

ifndef CREATE_EX
define CREATE_EX
  $(PRECREATE_EX)
  $(LDPREF) $(LDFLAGS) -o $@ $(DEBUG) $(objopts) $(lib_path) $(libopts) $(LDVFLAGS) $(LDOPTS) $(LDPOST)
  $(POSTCREATE_EX)
endef
endif

ifndef SONAME
SONAME=$(SONAME_$(BUILD_TYPE))$(VERSION_TAG_$(BUILD_TYPE))
endif

ifndef CREATE_DLL
define CREATE_DLL
  $(PRECREATE_SO)
  $(LDPREF) -shared $(if $(SONAME),-Wl$(comma)-h$(SONAME)) $(LDFLAGS) -o $@ $(DEBUG) $(objopts) $(lib_path) $(libopts) $(LDVFLAGS) $(LDOPTS) $(LDPOST)
  $(POSTCREATE_SO)
endef
endif

ifndef CREATE_SO
define CREATE_SO
  $(CREATE_DLL)
endef
endif

pinfo_name=$(patsubst %$(IMAGE_SUFF_EX),%,$(@F)).pinfo

ADD_VERSIONING_EX_nto  = -f $(pinfo_name)
ADD_VERSIONING_SO_nto  = -f $(pinfo_name)
ADD_VERSIONING_DLL_nto = -f $(pinfo_name)
ADD_VERSIONING=$(ADD_VERSIONING_$(BUILD_TYPE)_$(OS))

# Get the list of all the tagnames in the PINFO block	
tag_list=VERSION TAGID $(subst PINFO-,,$(filter PINFO-%,$(subst =, ,$(subst PINFO ,PINFO-,$(subst $(NEWLINE), ,$(PINFO))))))

define ADD_USAGE
	$(if $(UMPREF),$(UMPREF) $(addprefix -i,$(tag_list)) $(ADD_VERSIONING) $@ $(USEFILE) $(UMPOST))
endef

ifndef PINFO_TAGID
PINFO_TAGID=$(word 2, $(subst _, ,$(BRANCH_TAG)))
endif	
ifndef PINFO_STATE
PINFO_STATE=Experimental
endif
ifndef PINFO_USER
PINFO_USER=$(shell $(USER_HOST))
endif
ifndef PINFO_HOST
PINFO_HOST=$(shell $(HOST_HOST))
endif
ifndef PINFO_DATE
PINFO_DATE=$(shell $(DATE_HOST))
endif

define ADD_PINFO
	@$(ECHO_HOST)  >$(pinfo_name) STATE=$(PINFO_STATE)
	@$(ECHO_HOST) >>$(pinfo_name) INSTALLDIR=$(patsubst $(INSTALL_ROOT_$(OS))/%,%,$(dir $(INSTALLNAME)))
	@$(ECHO_HOST) >>$(pinfo_name) INSTALLNAME=$(notdir $(INSTALLNAME))
	@$(ECHO_HOST) >>$(pinfo_name) NAME=$(@F)  
	@$(ECHO_HOST) >>$(pinfo_name) USER=$(PINFO_USER)
	@$(ECHO_HOST) >>$(pinfo_name) HOST=$(PINFO_HOST)
	@$(ECHO_HOST) >>$(pinfo_name) DATE=$(PINFO_DATE)
	@$(if $(VERSION_REL),$(ECHO_HOST) >>$(pinfo_name) VERSION=$(VERSION_REL))
	@$(if $(PINFO_TAGID),$(ECHO_HOST) >>$(pinfo_name) TAGID=$(PINFO_TAGID))
	@$(if $(FILE_INFO),$(ECHO_HOST) >>$(pinfo_name) FINFO=$(FILE_INFO))
	@$(foreach link, $(LINKS), $(ECHO_HOST) >>$(pinfo_name) SYMLINK=$(IMAGE_PREF_$(BUILD_TYPE))$(link)$(VARIANT_TAG)$(IMAGE_SUFF_$(BUILD_TYPE));)
	@$(foreach ver, $(VERSION_TAG_$(BUILD_TYPE)), $(ECHO_HOST) >>$(pinfo_name) SYMLINK=$(BUILDNAME))
    @$(subst PINFO, $(ECHO_HOST) >>$(pinfo_name), $(PINFO))
endef

define TARGET_BUILD
	$(PRE_BUILD)
	$(RM_HOST) $@
	$(CREATE_$(BUILD_TYPE))
	$(if $(filter-out undefined, $(origin PINFO)), $(ADD_PINFO))
	$(if $(filter-out AR, $(BUILD_TYPE)), $(ADD_USAGE))
	$(POST_BUILD)
endef

define TARGET_INSTALL_LINKS
	-$(foreach ver, $(VERSION_TAG_$(BUILD_TYPE)), $(LN_HOST) $(BUILDNAME)$(ver) $(INSTALL_DIRECTORY)/$(BUILDNAME))
	-$(foreach link, $(LINKS), $(LN_HOST) $(IMAGE_PREF_$(BUILD_TYPE))$(NAME)$(VARIANT_TAG)$(IMAGE_SUFF_$(BUILD_TYPE)) $(INSTALL_DIRECTORY)/$(IMAGE_PREF_$(BUILD_TYPE))$(link)$(VARIANT_TAG)$(IMAGE_SUFF_$(BUILD_TYPE));)
endef

define TARGET_INSTALL
	$(PRE_INSTALL)
	-$(CP_HOST) $(BUILDNAME) $(INSTALLNAME)
	-$(if $(FILE_INFO),$(MP_HOST) $(FILE_INFO) $(INSTALLNAME))
	$(install_extra)
	$(TARGET_INSTALL_LINKS)
	$(POST_INSTALL)
endef

define STRIP_INSTALL
	$(if $(OCPREF), $(OCPREF) -S -R.ident $(INSTALLNAME))
endef

define DEBUG_STRIP_INSTALL
	$(if $(OCPREF), $(OCPREF) --keep-file-symbols $(BUILDNAME) $(BUILDNAME)$(INSTALL_TAIL).sym)
	$(if $(OCPREF), $(OCPREF) --add-gnu-debuglink=$(BUILDNAME)$(INSTALL_TAIL).sym $(INSTALLNAME))
	$(if $(OCPREF), $(CP_HOST) $(BUILDNAME)$(INSTALL_TAIL).sym $(INSTALLNAME).sym)
	$(STRIP_INSTALL)
endef

define TARGET_INSTALL_STRIP
	$(if $(filter-out AR, $(BUILD_TYPE)), $(STRIP_INSTALL))
endef

define TARGET_INSTALL_DEBUG_STRIP
	$(if $(filter-out AR, $(BUILD_TYPE)), $(DEBUG_STRIP_INSTALL))
endef

define do_uninstall
	@-$(if $(1),$(ECHO_HOST) Uninstalling $(1))
	@-$(if $(1),$(RM_HOST) $(1))
endef

define TARGET_UNINSTALL
	$(PRE_UNINSTALL)
	$(call do_uninstall, $(INSTALLNAME))
	$(if $(filter SO, $(BUILD_TYPE)), $(call do_uninstall, $(INSTALLNAME_SAR)))
	$(call do_uninstall,$(foreach ver, $(VERSION_TAG_$(BUILD_TYPE)), $(call do_uninstall,$(INSTALL_DIRECTORY)/$(BUILDNAME))))
	$(call do_uninstall,$(foreach link, $(LINKS), $(INSTALL_DIRECTORY)/$(IMAGE_PREF_$(BUILD_TYPE))$(link)$(VARIANT_TAG)$(IMAGE_SUFF_$(BUILD_TYPE))))
	$(POST_UNINSTALL)
endef

INSTALL_HEADERS=$(foreach dir, $(PUBLIC_INCVPATH), $(patsubst $(dir)/%,$(INSTALL_ROOT_HDR)/%,$(shell $(FL_HOST) $(dir))))

.SECONDEXPANSION:
$(INSTALL_ROOT_HDR)/%: $$(firstword $$(wildcard $$(addsuffix $$(subst $$(INSTALL_ROOT_HDR),,$$@),$$(PUBLIC_INCVPATH))))
	$(if $(filter $@,$(INSTALL_HEADERS)),$(CP_HOST) $< $@)

define TARGET_HINSTALL
	$(PRE_HINSTALL)
	$(if $(INSTALL_HEADERS: =), @$(MAKE) $(INSTALL_HEADERS))
	$(POST_HINSTALL)
endef

define TARGET_HUNINSTALL
	$(PRE_HUNINSTALL)
	$(call do_uninstall, $(foreach dir, $(PUBLIC_INCVPATH), $(foreach file, $(shell $(FL_HOST) $(dir)), $(INSTALL_ROOT_HDR)/$(patsubst $(dir)/%,%,$(file)))))
	$(POST_HUNINSTALL)
endef

define TARGET_CINSTALL
	$(PRE_CINSTALL)
	@-$(foreach dir, $(CONFIG_PATH), $(foreach file, $(shell $(FL_HOST) $(dir)), $(CP_HOST) $(file) $(INSTALL_ROOT_$(OS))/$(patsubst $(dir)/%,%,$(file));))
	$(POST_CINSTALL)
endef

define TARGET_CUNINSTALL
	$(PRE_CUNINSTALL)
	$(call do_uninstall, $(foreach dir, $(CONFIG_PATH), $(foreach file, $(shell $(FL_HOST) $(dir)), $(INSTALL_ROOT_$(OS))/$(patsubst $(dir)/%,%,$(file)))))
	$(POST_CUNINSTALL)
endef

extra_buildnames_SO=$(BUILDNAME_SAR)

ifndef ICLEAN
ICLEAN=$(BUILDNAME) $(extra_buildnames_$(BUILD_TYPE)) *.pinfo
endif

define TARGET_ICLEAN
	$(PRE_ICLEAN)
	$(RM_HOST) $(ICLEAN) $(EXTRA_ICLEAN)
	$(POST_ICLEAN)
endef

ifndef CLEAN
CLEAN=*.o *.err *.map mapfile *.sym *.i $(DEFFILE)
endif

define TARGET_CLEAN
	$(PRE_CLEAN)
	$(RM_HOST) $(ICLEAN) $(CLEAN) $(EXTRA_CLEAN) $(EXTRA_ICLEAN)
	$(POST_CLEAN)
endef

post_target_SO = $(FULLNAME_SAR)
POST_TARGET += $(post_target_$(BUILD_TYPE))

define TARGET_SHOWVARS
	@$(foreach var, $(subst /, ,$(SHOWVARS_LIST)), $(ECHO_HOST) $(var) $($(var));)
endef

define TARGET_PINFO_FAILURE
	@$(TARGET_ICLEAN)
	@$(ECHO_HOST) Missing PINFO information!
	@false
endef


# With a case insensitive file system, the %.o:%.s implicit rule might
# be selected even if the actual file is .S.  So, check the actual
# file name and force -xassembler-with-cpp for .S.  Note also that
# qrules.mk must list the %.o:%.s before the %.o:%.S.
COMPILE_s_o=$(ASWRAP) $(ASPREF) $(ASFLAGS) $(FLAGS) $(ASVFLAGS) $(ASOPTS) $(if $(filter %.S,$(shell echo $(subst .s,.*,$<))),-xassembler-with-cpp) $< $(ASPOST)
COMPILE_S_o=$(ASWRAP) $(ASPREF) $(ASFLAGS) $(FLAGS) $(ASVFLAGS) $(ASOPTS) $< $(ASPOST)
COMPILE_c_o=$(CCWRAP) $(CCPREF) $(CCFLAGS) $(FLAGS) $(CCVFLAGS) $(CCOPTS) $< $(CCPOST)
COMPILE_cc_o=$(CCWRAP) $(CCPREF) $(CCFLAGS) $(CXXFLAGS) $(FLAGS) $(CCVFLAGS) $(CCOPTS) $(CXXOPTS) $< $(CCPOST)
COMPILE_nda=$(CP_HOST) $< $@

COMPILE_S_i=$(ASWRAP) $(ASPREF) -E $(ASFLAGS) $(FLAGS) $(ASVFLAGS) $(ASOPTS) $< >$@ $(ASPOST)
COMPILE_c_i=$(CCWRAP) $(CCPREF) -E $(CCFLAGS) $(FLAGS) $(CCVFLAGS) $(CCOPTS) $< >$@ $(CCPOST)
COMPILE_cc_i=$(CCWRAP) $(CCPREF) -E $(CCFLAGS) $(CXXFLAGS) $(FLAGS) $(CCVFLAGS) $(CCOPTS) $(CXXOPTS) $< >$@ $(CCPOST)

# Special recipes for code that is called from kernel mode

isr_prefix=$(filter-out $(CCFLAGS_ISR_EXCLUDE) $(CCVFLAGS_ISR_EXCLUDE),$(CCPREF))
isr_infix=$(filter-out $(CCFLAGS_ISR_EXCLUDE) $(CCVFLAGS_ISR_EXCLUDE),$(CCFLAGS) $(FLAGS) $(CCVFLAGS) $(CCOPTS) $(CCFLAGS_ISR) $(CCVFLAGS_ISR))
isr_postfix=$(filter-out $(CCFLAGS_ISR_EXCLUDE) $(CCVFLAGS_ISR_EXCLUDE),$(CCPOST))

COMPILE_ISR_c_o=$(CCWRAP) $(isr_prefix) $(isr_infix) $< $(isr_postfix)
COMPILE_ISR_cc_o=$(CCWRAP) $(isr_prefix) $(isr_infix) $< $(isr_postfix)
COMPILE_ISR_c_i=$(CCWRAP) $(isr_prefix) -E $(isr_infix) $< >$@ $(isr_postfix)
COMPILE_ISR_cc_i=$(CCWRAP) $(isr_prefix) -E $(isr_infix) $< >$@ $(isr_postfix)

ifneq ($(BUILDENV),qss)
# Include vendor-specific definitions
-include $(MKFILES_ROOT)/vendor.qmacros.mk
endif
