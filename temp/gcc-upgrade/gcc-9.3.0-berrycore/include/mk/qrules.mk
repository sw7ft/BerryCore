ifndef VARIANT_TAG
include $(MKFILES_ROOT)/qmacros.mk
endif

ifneq ($(origin NEED_VPATH_MUNGING),undefined)
# On win32 systems, some munging of the path names is sometimes necessary...

_native_drive_letters:=a b c d e f g h i j k l m n o p q r s t u v w x y z A B C D E F G H I J K L M N O P Q R S T U V W X Y Z

#
# convert to native path (e.g. /c/dir/file -> c:/dir/file) 
#
# Note: a relative path c/dir could well be d:/dir if CWD is /,
# however, _native_path does not deal with that special case.
_native_path=$(foreach e,$(1),$(firstword $(strip $(foreach p,$(_native_drive_letters),$(if $(filter /$(p)/%,$(e)),$(patsubst /$(p)%,$(p):%,$(e))))) $(e)))

#
# convert to vpath (e.g. c:/dir => /c/dir)
_vpath_normalize=$(foreach e,$(1),$(if $(filter $(addsuffix :/%,$(_native_drive_letters)),$(e)),$(subst //,/,/$(subst :,/,$(e))),$(e)))
else
# Non win32 systems (i.e. posix systems) do not need any file name manipulation...
_native_path=$(1)
_vpath_normalize=$(1)
endif


vpath %.h   $(call _vpath_normalize,$(INCVPATH))
ifeq ($(filter a,$(VARIANTS)),)
vpath %.lib $(call _vpath_normalize,$(LIBVPATH))
vpath %.a   $(call _vpath_normalize,$(LIBVPATH))
vpath %.so  $(call _vpath_normalize,$(LIBVPATH))
endif

ifeq ($(filter -g, $(CCFLAGS) $(FLAGS) $(CCVFLAGS) $(CXXFLAGS)),)
ifeq ($(origin NDEBUG),undefined)
NDEBUG = -DNDEBUG
endif
endif
CCFLAGS += $(NDEBUG)

vpath %.s $(call _vpath_normalize,$(SRCVPATH) $(LATE_SRCVPATH))

# NOTE: %.o:%.s must precede %.o:%.S (see qmacros.mk for details)
%.o: %.s $(EXTRA_ASDEPS)
	$(COMPILE_s_o)

vpath %.S $(call _vpath_normalize,$(SRCVPATH) $(LATE_SRCVPATH))

# NOTE: %.o:%.s must precede %.o:%.S (see qmacros.mk for details)
%.o: %.S $(EXTRA_ASDEPS)
	$(COMPILE_S_o)

%.i: %.S 
	$(COMPILE_S_i)

vpath %.c $(call _vpath_normalize,$(SRCVPATH) $(LATE_SRCVPATH))

%.o: %.c $(EXTRA_CCDEPS)
	$(COMPILE_c_o)

%.i: %.c
	$(COMPILE_c_i)

vpath %.cc $(call _vpath_normalize,$(SRCVPATH) $(LATE_SRCVPATH))

%.o: %.cc $(EXTRA_CCDEPS)
	$(COMPILE_cc_o)

%.i: %.cc
	$(COMPILE_cc_i)

vpath %.cpp $(call _vpath_normalize,$(SRCVPATH) $(LATE_SRCVPATH))

%.o: %.cpp $(EXTRA_CCDEPS)
	$(COMPILE_cc_o)

%.i: %.cpp
	$(COMPILE_cc_i)

vpath %.cxx $(call _vpath_normalize,$(SRCVPATH) $(LATE_SRCVPATH))

%.o: %.cxx $(EXTRA_CCDEPS)
	$(COMPILE_cc_o)

%.i: %.cxx
	$(COMPILE_cc_i)

externs.o: externs.c externs.h $(EXTRA_CCDEPS)
	$(COMPILE_c_o)

ifdef DEFFILE
$(DEFFILE): %.def: %.c 
	$(COMPILE_c_o)
	$(MKASMOFF_HOST) $(if $(ASMOFF_FORMAT_$(CPU)),-f $(ASMOFF_FORMAT_$(CPU))) $(basename $(<F)).o $@
	$(RM_HOST) $(basename $(<F)).o
endif

ifdef UPDATE_NDA_OBJECTS
# This first set of rules is when the NDA source is available
# and we want to update the *.?-nda files
%.o-nda: %.o 
	$(COMPILE_nda)

%.a-nda: %.a 
	$(COMPILE_nda)
else
# This set of rules is for when the NDA source is _not_ available
# and we need the *.?-nda files to create the objects/libraries
%.o: %.o-nda 
	$(COMPILE_nda)

%.a: %.a-nda 
	$(COMPILE_nda)
endif	

# Static pattern rules to compile kernel-mode modules specially

$(addsuffix .o,$(basename $(filter %.c,$(SRCS_ISR)))): %.o: %.c
	$(COMPILE_ISR_c_o)

$(addsuffix .o,$(basename $(filter %.cc,$(SRCS_ISR)))): %.o: %.cc
	$(COMPILE_ISR_cc_o)

$(addsuffix .o,$(basename $(filter %.cpp,$(SRCS_ISR)))): %.o: %.cpp
	$(COMPILE_ISR_cc_o)

$(addsuffix .o,$(basename $(filter %.cxx,$(SRCS_ISR)))): %.o: %.cxx
	$(COMPILE_ISR_cc_o)

$(addsuffix .i,$(basename $(filter %.c,$(SRCS_ISR)))): %.i: %.c
	$(COMPILE_ISR_c_i)

$(addsuffix .i,$(basename $(filter %.cc,$(SRCS_ISR)))): %.i: %.cc
	$(COMPILE_ISR_cc_i)

$(addsuffix .i,$(basename $(filter %.cpp,$(SRCS_ISR)))): %.i: %.cpp
	$(COMPILE_ISR_cc_i)

$(addsuffix .i,$(basename $(filter %.cxx,$(SRCS_ISR)))): %.i: %.cxx
	$(COMPILE_ISR_cc_i)

# Lint Support
#

-include $(MKFILES_ROOT)/qlint.mk
