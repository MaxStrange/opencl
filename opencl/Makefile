Q ?= @

appname := libeocl

rootdir                           := $(shell pwd)
BUILDDIR                          := $(rootdir)/build
OBJDIR                            := $(BUILDDIR)/obj
srcdir                            := $(rootdir)/src
install_location                  := /usr/local/OpenCL/vendors/max

src                               := $(wildcard $(srcdir)/*.c)

CXX                               := gcc

RM                                := rm -f
MKDIR                             := mkdir -p
SED                               := sed

inc_path                          := $(srcdir)

lds                               := m

WARNING                           += -Wall
WARNING                           += -Werror
WARNING                           += -Wfatal-errors
WARNING                           += -Wno-unused-local-typedefs
WARNING                           += -Wno-unused-variable
WARNING                           += -Wno-unused-function
WARNING                           += -Wno-unused-private-field
WARNING                           += -Wno-return-type

OPTIMIZATION                      ?= -O0 -ggdb3

CXXFLAGS                          += $(WARNING)
CXXFLAGS                          += $(OPTIMIZATION)
CXXFLAGS                          += -std=c99

CFLAGS                            := $(addprefix -I, $(inc_path))

obj                               := $(addprefix $(OBJDIR)/, $(notdir $(src)))
obj                               := $(obj:.c=.o)

lds                               := $(addprefix -l, $(lds))


empty :=
space := $(empty) $(empty)
vpath %.c $(subst $(space),:,$(sort $(dir $(src))))
vpath %.h $(subst $(space),:,$(inc_path))
vpath %.o $(OBJDIR)

.PHONY: all
all: $(appname).so

.PHONY: install
install: $(appname).so
	$(Q) echo "Need root access to install .so file in install location."
	sudo cp $(appname).so $(install_location)

$(appname).so: $(obj)
	$(Q) $(LINK.c) -shared $^ $(CFLAGS) $(LDFLAGS) $(lds) -o $@

.PHONY: clean
clean:
	$(RM) -r $(BUILDDIR)

$(BUILDDIR):
	$(Q) $(MKDIR) $@

$(OBJDIR):
	$(Q) $(MKDIR) $@

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	@echo "$(CXX) $(notdir $<)"
	$(Q) $(CXX) $(CFLAGS) $(CXXFLAGS) -fpic -c $< -o $@

$(OBJDIR)/%.d: %.c | $(OBJDIR)
	@set -e; $(RM) $@; \
	$(CC) -MM -MT $(patsubst %$(suffix $<),$(dir $@)%.o,$(notdir $<)) $(CFLAGS) $(CXXFLAGS) $< > $@.$$$$; \
	$(SED) 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	$(RM) $@.$$$$

ifeq ($(filter clean,$(MAKECMDGOALS)),)
-include $(obj:.o=.d)
endif




