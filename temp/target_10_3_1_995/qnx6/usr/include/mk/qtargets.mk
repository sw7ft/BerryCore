.PHONY: first all iclean clean spotless install install-debug-strip install-strip uninstall qinstall quninstall hinstall huninstall showvars pinfo_failure check

first: all

include $(MKFILES_ROOT)/qrules.mk

ifeq ($(BUILD_TYPE)$(origin USEFILE),EXundefined)
USEFILE=$(PROJECT_ROOT)/$(NAME).use
endif
EXTRA_DEPS += $(USEFILE)

ifeq ($(origin PINFO),undefined)
ifneq ($(ADD_VERSIONING),)	
ifneq ($(VERSION_REL),)
EXTRA_DEPS += pinfo_failure
endif
endif
ADD_VERSIONING=
ifeq ($(USEFILE),)
ADD_USAGE=
endif
endif

ifneq ($(BUILD_TYPE),AR)
ifeq ($(OS),qnx4)
CC_qnx4_x86_wcc += -g1
LD_qnx4_x86_wcc += -g1 "-Wl,opt symfile"
endif
endif

ifndef ALL_DEPENDENCIES
ALL_DEPENDENCIES = $(PRE_TARGET) $(FULLNAME) $(POST_TARGET)
endif

# needs to be here to get the expansions to come out right
all: $(ALL_DEPENDENCIES)

build_line=$(OBJS) $(if $(filter-out AR,$(BUILD_TYPE)),$(LIBNAMES)) $(EXTRA_DEPS)

#this next bit is to make sure pre/fullname/post get done in right order
#when doing parallel makes
ifneq ($(PRE_TARGET),)
$(FULLNAME) $(build_line): | $(PRE_TARGET) 
endif
ifneq ($(POST_TARGET),)
$(POST_TARGET): | $(FULLNAME)
endif

$(FULLNAME): $(build_line)
	$(TARGET_BUILD)

$(FULLNAME_SAR): INSTALLNAME=$(INSTALLNAME_SAR)
$(FULLNAME_SAR): BUILD_TYPE=AR
$(FULLNAME_SAR): $(OBJS) 
	$(TARGET_BUILD)

install: all
ifneq ($(PUBLIC_INCVPATH),)
	$(TARGET_HINSTALL)
endif
ifneq ($(CONFIG_PATH),)
	$(TARGET_CINSTALL)
endif
ifeq ($(findstring /dev/null, $(INSTALL_DIRECTORY)),)
	$(TARGET_INSTALL)
endif

qinstall: hinstall cinstall
ifeq ($(findstring /dev/null, $(INSTALL_DIRECTORY)),)
	$(TARGET_INSTALL)
endif

hinstall:
ifneq ($(PUBLIC_INCVPATH),)
	$(TARGET_HINSTALL)
endif

cinstall:
ifneq ($(CONFIG_PATH),)
	$(TARGET_CINSTALL)
endif

uninstall quninstall: huninstall cuninstall
ifeq ($(findstring /dev/null, $(INSTALL_DIRECTORY)),)
	$(TARGET_UNINSTALL)
endif

huninstall:
ifneq ($(PUBLIC_INCVPATH),)
	$(TARGET_HUNINSTALL)
endif

cuninstall:
ifneq ($(CONFIG_PATH),)
	$(TARGET_CUNINSTALL)
endif

install-debug-strip: install
	$(TARGET_INSTALL_DEBUG_STRIP)	

install-strip: install
	$(TARGET_INSTALL_STRIP)	

clean spotless: 
	$(TARGET_CLEAN)

iclean:
	$(TARGET_ICLEAN)

showvars:
	$(TARGET_SHOWVARS)

pinfo_failure:
	$(TARGET_PINFO_FAILURE)

ifdef TARGET_STUBS
stubs:
	$(TARGET_STUBS)
endif

check: install
	$(TARGET_PRE_CHECK)
	$(TARGET_CHECK)
	$(TARGET_POST_CHECK)
