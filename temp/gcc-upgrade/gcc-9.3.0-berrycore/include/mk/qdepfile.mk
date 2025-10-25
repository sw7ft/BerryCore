DEPFILE = depends.mk

-include $(DEPFILE)

DEPLIST=$(subst .o,.depends,$(OBJS))

.PHONY: initdepend depends

depends: initdepend $(DEPLIST)

initdepend:
	$(RM_HOST) $(DEPFILE)

%.depends: %.c
	$(CCPREF) -Wp,-MM -E $(CCFLAGS) $(FLAGS) $(CCVFLAGS) $(CCOPTS) $< >>$(DEPFILE)
