ifneq ($(COMPILER_DRIVER),qcc)
CCVFLAG_shared = -fpic -D__PIC__
ASVFLAG_shared = -D__PIC__ -Wa,--defsym -Wa,__PIC__=1
endif

OPTIMIZE_TIME_gcc=-O
OPTIMIZE_SIZE_gcc=-O
OPTIMIZE_NONE_gcc=
OPTIMIZE__gcc=$(OPTIMIZE_SIZE_gcc)

CC_linux_x86_gcc += -c -Wall -pipe $(DEBUG) $(OPTIMIZE_$(OPTIMIZE_TYPE)_gcc)
AS_linux_x86_gcc += -c -Wall -pipe -O $(addprefix -Wa$(comma)-I$, $(INCDIRS)) $(addprefix -D,$(VARIANT_NAMES)) 
# AR_linux_x86_gcc += -r
CC_linux_x86_gcc_qcc += -Wc,-Wall -Wc, $(DEBUG) $(OPTIMIZE_$(OPTIMIZE_TYPE)_gcc)
AS_linux_x86_gcc_qcc += -O $(addprefix -Wa$(comma)-I$, $(INCDIRS)) $(addprefix -D,$(VARIANT_NAMES)) 
