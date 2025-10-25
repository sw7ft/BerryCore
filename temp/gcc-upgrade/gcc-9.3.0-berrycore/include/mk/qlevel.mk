defsrcvpath+= $(current_dir)
level_name:=$(notdir $(current_dir))
split_names:=$(subst -, ,$(subst ., ,$(level_name)))

curr_variant:=$(firstword $(variant_levels))
variant_levels:=$(filter-out $(curr_variant),$(variant_levels))
VARIANT$(curr_variant):=$(level_name)
VARIANT$(curr_variant)_ROOT:=$(current_dir)

ifeq ($(OS),)
chk_os:=$(filter $(oses), $(split_names))
ifneq ($(chk_os),)
OS:=$(chk_os)
OS_ROOT:=$(current_dir)
endif
endif

ifeq ($(CPU),)
chk_cpu:=$(filter $(cpus), $(split_names))
ifneq ($(chk_cpu),)
CPU:=$(chk_cpu)
CPU_ROOT:=$(current_dir)
endif
endif

ifeq ($(COMPILER),)
chk_compiler:=$(filter $(compilers), $(split_names))
ifneq ($(chk_compiler),)
COMPILER:=$(chk_compiler)
COMPILER_ROOT:=$(current_dir)
endif
endif

all_variants+= $(split_names)

current_dir:=$(patsubst %/$(level_name),%,$(current_dir))
common:=$(wildcard $(current_dir)/common.mk*)
