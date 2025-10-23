EXTRA_SRCVPATH += $(PROJECT_ROOT)/src

include $(MKFILES_ROOT)/qmacros.mk

include $(PROJECT_ROOT)/src/abWfiles
include $(PROJECT_ROOT)/src/abLfiles

#
# Get rid of any "-l" sequences
#
ablib_no_l := $(strip $(subst -l,,$(filter-out -lang-c++,$(ABLIB))))

#
# The LIBS variable can't handle -Bstatic or -Bdynamic, so filter them out.
# We will use the LIBPREF_ mechanism instead.
#
LIBS += $(filter-out -B%,$(ablib_no_l))

#
# This code handles up to 9 -Bstatic and 9 -Bdynamic options in the library list
# and sets the corresponding LIBPREF_<lib> variable. We also assume that default
# PhAB libraries will always follow any trailing -B option the user gives.
#
getlib = $(subst $(2)_,,$(word $(1),$(filter $(2)_%,$(subst $(2) ,$(2)_,$(3)))))

LIBPREF_$(call getlib,1,-Bstatic,$(ablib_no_l)) = -Bstatic
LIBPREF_$(call getlib,2,-Bstatic,$(ablib_no_l)) = -Bstatic
LIBPREF_$(call getlib,3,-Bstatic,$(ablib_no_l)) = -Bstatic
LIBPREF_$(call getlib,4,-Bstatic,$(ablib_no_l)) = -Bstatic
LIBPREF_$(call getlib,5,-Bstatic,$(ablib_no_l)) = -Bstatic
LIBPREF_$(call getlib,6,-Bstatic,$(ablib_no_l)) = -Bstatic
LIBPREF_$(call getlib,7,-Bstatic,$(ablib_no_l)) = -Bstatic
LIBPREF_$(call getlib,8,-Bstatic,$(ablib_no_l)) = -Bstatic
LIBPREF_$(call getlib,9,-Bstatic,$(ablib_no_l)) = -Bstatic
LIBPREF_$(call getlib,1,-Bdynamic,$(ablib_no_l)) = -Bdynamic
LIBPREF_$(call getlib,2,-Bdynamic,$(ablib_no_l)) = -Bdynamic
LIBPREF_$(call getlib,3,-Bdynamic,$(ablib_no_l)) = -Bdynamic
LIBPREF_$(call getlib,4,-Bdynamic,$(ablib_no_l)) = -Bdynamic
LIBPREF_$(call getlib,5,-Bdynamic,$(ablib_no_l)) = -Bdynamic
LIBPREF_$(call getlib,6,-Bdynamic,$(ablib_no_l)) = -Bdynamic
LIBPREF_$(call getlib,7,-Bdynamic,$(ablib_no_l)) = -Bdynamic
LIBPREF_$(call getlib,8,-Bdynamic,$(ablib_no_l)) = -Bdynamic
LIBPREF_$(call getlib,9,-Bdynamic,$(ablib_no_l)) = -Bdynamic

PHAB_MODULES = $(foreach mod,$(ABMOD),$(PROJECT_ROOT)/wgt/$(mod))
EXTRA_DEPS += $(PHAB_MODULES)
USEFILE = $(PROJECT_ROOT)/src/Usemsg
# Call phabbind post-build
POST_BUILD = $(PB_HOST) $(BUILDNAME) $(PHAB_MODULES)

include $(MKFILES_ROOT)/qtargets.mk
