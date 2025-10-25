ifneq ($(COMPILER_DRIVER),qcc)
ifneq ($(BUILDENV),iox)
CCVFLAG_shared = -fpic -D__PIC__
ASVFLAG_shared = -D__PIC__ -Wa,--defsym -Wa,__PIC__=1
else
CCVFLAG_shared = -D__SLIB_DATA_INDIRECT
ASVFLAG_shared = -D__SLIB_DATA_INDIRECT
CCVFLAG_sharedstaticlib = -D__SLIB_DATA_INDIRECT
ASVFLAG_sharedstaticlib = -D__SLIB_DATA_INDIRECT
CCVFLAG_be += -mbig-endian -D__BIGENDIAN__
ASVFLAG_be += -mbig-endian -D__BIGENDIAN__
CCVFLAG_le += -D__LITTLEENDIAN__
ASVFLAG_le += -D__LITTLEENDIAN__
CCVFLAG_a =
endif
endif

OPTIMIZE_TIME_gcc=-O2
OPTIMIZE_SIZE_gcc=-Os
OPTIMIZE_NONE_gcc=
OPTIMIZE__gcc=$(OPTIMIZE_SIZE_gcc)

CC_nto_x86_gcc += -c -Wall -pipe $(DEBUG) $(OPTIMIZE_$(OPTIMIZE_TYPE)_gcc)
AS_nto_x86_gcc += -c -Wall -pipe -O $(addprefix -Wa$(comma)-I$, $(INCDIRS)) $(addprefix -D,$(VARIANT_NAMES)) 
AR_nto_x86_gcc += -r
CC_nto_x86_gcc_qcc += -Wc,-Wall $(DEBUG) $(OPTIMIZE_$(OPTIMIZE_TYPE)_gcc)
AS_nto_x86_gcc_qcc += -O $(addprefix -Wa$(comma)-I$, $(INCDIRS)) $(addprefix -D,$(VARIANT_NAMES)) 
CC_nto_x86_icc_qcc += -Wc,-Wall $(DEBUG) $(OPTIMIZE_$(OPTIMIZE_TYPE)_gcc)
AS_nto_x86_icc_qcc += -O $(addprefix -Wa$(comma)-I$, $(INCDIRS)) $(addprefix -D,$(VARIANT_NAMES)) 

OPTIMIZE_TIME_wcc=-Otax
OPTIMIZE_SIZE_wcc=-Osax
OPTIMIZE_NONE_wcc=
OPTIMIZE__wcc=$(OPTIMIZE_SIZE_wcc)
CC_nto_x86_wcc += $(NTOQUIET) -mf -w6 -3  -Wc,-nt=".text" $(OPTIMIZE_$(OPTIMIZE_TYPE)_wcc) -Wc,-s
AS_nto_x86_wcc += $(NTOQUIET) -mf -w6 -3s -Ws,-nt=".text" $(addprefix -D,$(VARIANT_NAMES))
LD_nto_x86_wcc += -N32K $(NTOQUIET) -M
AR_nto_x86_wcc += -r
