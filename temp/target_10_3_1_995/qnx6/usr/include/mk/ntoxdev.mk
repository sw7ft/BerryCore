ifneq ($(OS),nto)
CCFLAGS += -D_NTO_HDR_DIR_=$(call FIND_HDR_DIR, nto, usr/include, sys/platform.h)
endif
