#
#	Generally useful recursive makefile.
#
#	Finds any subdirectories with "Makefile" in them, and
#	recurses into them, issuing "make" with the specified
#	target. Do not recurse into a directory if there is 
#   a "Makefile.dnm" file present.
#

export
unexport PWD
unexport LIST
unexport makelist
unexport makefiles
unexport mkfile
unexport force_dirs
unexport qbdir
unexport firstdir
unexport restdir
unexport ignore
unexport sep
unexport makecmd
unexport inc_list
unexport exc_list
unexport tmp
unexport reallist
unexport MAKEFILE
unexport goal
unexport dnm_list

goals:=$(if $(MAKECMDGOALS),$(MAKECMDGOALS),all)

ifndef MAKEFILE
MAKEFILE=[Mm]akefile
endif

makefiles:=$(wildcard */$(MAKEFILE))
mkfile:=$(notdir $(firstword $(makefiles)))
makelist:=$(sort $(patsubst %/,%,$(dir $(makefiles))))

dnm_list:=$(patsubst %/,%/.$(firstword $(goals)),$(subst Makefile.dnm,,$(wildcard */[Mm]akefile.dnm*)))
x_list:=$(foreach tmp,$(dnm_list), $(subst ., ,$(notdir $tmp)))
dnm_list:=$(foreach tmp,$(dnm_list), $(if $(filter $(goals), $(subst ., ,$(notdir $(tmp)))),$(patsubst %/,%,$(dir $(tmp)))))

makelist:=$(filter-out $(dnm_list),$(makelist))

ifneq ($(filter CPU OS,$(LIST)),)
#
# If we're working on a CPU or OS list, figure out what target systems we 
# can actually build based on the host system we're running on.
#
ifndef QBUILDLIST
QBUILDLIST=buildlist.mk
ifdef QCONFIG
qbdir=$(dir $(QCONFIG))
endif
endif
-include $(qbdir)$(QBUILDLIST)
endif

ifneq (,$(LIST))
ifdef CHECKFORCE
force_dirs:=$(patsubst %/,%,$(dir $(wildcard */[Mm]akefile.force)))
endif

inc_list:=.BUGFIX. $(sort $(foreach var, $(LIST), $($(var)LIST)))
inc_list:=$(filter-out .BUGFIX., $(inc_list))
exc_list:=.BUGFIX. $(sort $(foreach var, $(LIST), $(EXCLUDE_$(var)LIST)))
exc_list:=$(filter-out .BUGFIX., $(exc_list))

ifneq (,$(exc_list))
makelist:=$(filter-out $(filter-out $(force_dirs), $(foreach dir,$(makelist),$(if $(filter $(subst ., ,$(subst -, ,$(dir))),$(subst /, ,$(exc_list))),$(dir)))),$(makelist))
endif

ifneq (,$(inc_list))
reallist:=$(foreach var,$(LIST),$(if $($(var)LIST),$(var),))
makelist:=$(filter-out $(filter-out $(force_dirs), $(foreach dir,$(makelist),$(foreach var,$(reallist),$(if $(filter $(subst ., ,$(subst -, ,$(dir))),$(subst /, ,$($(var)LIST))),,$(dir))))),$(makelist))
endif
endif

makelist:=$(foreach dir,$(EARLY_DIRS),$(filter $(dir),$(makelist))) $(filter-out $(EARLY_DIRS) $(LATE_DIRS), $(makelist)) $(foreach dir,$(LATE_DIRS),$(filter $(dir),$(makelist)))
firstdir:=$(firstword $(makelist))
restdir :=$(filter-out $(firstdir), $(makelist))

ifneq ($(findstring k,$(MFLAGS)),)
ignore=-
endif
# define the separator as a newline character - handles differences
# between Unix and Win32 style shells.
define sep


endef

makecmd = $(ignore)$(MAKE) -j $(firstword $(JLEVEL) 1) -C$(dir) -f$(mkfile) $(if $(MAKECMDGOALS),$@)

$(goals):
	+$(foreach dir, $(firstdir), $(makecmd))$(foreach dir, $(restdir), $(sep) $(makecmd))
