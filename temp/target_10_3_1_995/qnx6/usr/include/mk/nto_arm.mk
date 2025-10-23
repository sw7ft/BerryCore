ifneq ($(COMPILER_DRIVER),qcc)
CCVFLAG_shared = -fpic -D__PIC__
ASVFLAG_shared = -fpic -Wa,--defsym -Wa,__PIC__=1 -D__PIC__
endif

OPTIMIZE_TIME_gcc=-O2
OPTIMIZE_SIZE_gcc=-Os
OPTIMIZE_NONE_gcc=
OPTIMIZE__gcc=$(OPTIMIZE_SIZE_gcc)

ifneq ($(filter v7,$(VARIANT_LIST)),)
CC_nto_arm_gcc = $(CC_nto_arm_gcc_v7)
AS_nto_arm_gcc = $(AS_nto_arm_gcc_v7)
AR_nto_arm_gcc = $(AR_nto_arm_gcc_v7)
LR_nto_arm_gcc = $(LR_nto_arm_gcc_v7)
LD_nto_arm_gcc = $(LD_nto_arm_gcc_v7)
OC_nto_arm_gcc = $(OC_nto_arm_gcc_v7)

CC_nto_arm_gcc_qcc = $(CC_nto_arm_gcc_qcc_v7)
AS_nto_arm_gcc_qcc = $(AS_nto_arm_gcc_qcc_v7)
AR_nto_arm_gcc_qcc = $(AR_nto_arm_gcc_qcc_v7)
LR_nto_arm_gcc_qcc = $(LR_nto_arm_gcc_qcc_v7)
LD_nto_arm_gcc_qcc = $(LD_nto_arm_gcc_qcc_v7)
OC_nto_arm_gcc_qcc = $(OC_nto_arm_gcc_qcc_v7)
endif

ifneq ($(filter hf,$(VARIANT_LIST)),)
CC_nto_arm_gcc = $(CC_nto_arm_gcc_v7_hf)
AS_nto_arm_gcc = $(AS_nto_arm_gcc_v7_hf)
AR_nto_arm_gcc = $(AR_nto_arm_gcc_v7_hf)
LR_nto_arm_gcc = $(LR_nto_arm_gcc_v7_hf)
LD_nto_arm_gcc = $(LD_nto_arm_gcc_v7_hf)
OC_nto_arm_gcc = $(OC_nto_arm_gcc_v7_hf)

CC_nto_arm_gcc_qcc = $(CC_nto_arm_gcc_qcc_v7_hf)
AS_nto_arm_gcc_qcc = $(AS_nto_arm_gcc_qcc_v7_hf)
AR_nto_arm_gcc_qcc = $(AR_nto_arm_gcc_qcc_v7_hf)
LR_nto_arm_gcc_qcc = $(LR_nto_arm_gcc_qcc_v7_hf)
LD_nto_arm_gcc_qcc = $(LD_nto_arm_gcc_qcc_v7_hf)
OC_nto_arm_gcc_qcc = $(OC_nto_arm_gcc_qcc_v7_hf)
endif

CC_nto_arm_gcc += -pipe $(OPTIMIZE_$(OPTIMIZE_TYPE)_gcc) -Wall 
AS_nto_arm_gcc += -pipe $(OPTIMIZE_$(OPTIMIZE_TYPE)_gcc) $(addprefix -Wa$(comma)-I$, $(INCVPATH)) $(foreach var,$(VARIANT_NAMES), -Wa$(comma)--defsym$(comma)$(var)=1)
AR_nto_arm_gcc += -r
LD_nto_arm_gcc += -Wl,--no-keep-memory
LDBOOTSTRAP_nto_arm_gcc  = $(LR_nto_arm_gcc) -Wl,--no-keep-memory -nostartfiles -Wl,-u_start
LDBOOTSTRAPPOST_nto_arm_gcc  = $(LRPOST_nto_arm_gcc) 

CC_nto_arm_gcc_qcc += $(OPTIMIZE_$(OPTIMIZE_TYPE)_gcc) -Wc,-Wall
AS_nto_arm_gcc_qcc += $(OPTIMIZE_$(OPTIMIZE_TYPE)_gcc) $(addprefix -Wa$(comma)-I$, $(INCVPATH)) $(foreach var,$(VARIANT_NAMES), -Wa$(comma)--defsym$(comma)$(var)=1)
LD_nto_arm_gcc_qcc += -Wl,--no-keep-memory
LDBOOTSTRAP_nto_arm_gcc_qcc  = $(LR_nto_arm_gcc_qcc) -Wl,--no-keep-memory -nostartup -Wl,-u_start
LDBOOTSTRAPPOST_nto_arm_gcc_qcc  = $(LRPOST_nto_arm_gcc_qcc) 

silent_variants_arm += v7 hf
CPUVARDIR_SUFFIX = $(if $(filter armv7,$(CPU)$(filter v7,$(VARIANTS))),-v7$(filter hf,$(VARIANTS)))
