Q ?= @

appname := hello_vector

rootdir                           := $(shell pwd)
BUILDDIR                          := $(rootdir)/build
OBJDIR                            := $(BUILDDIR)/obj
srcdir                            := $(rootdir)/src

src                               := $(wildcard $(srcdir)/*.c)

CXX                               := gcc

RM                                := rm -f
MKDIR                             := mkdir -p
SED                               := sed

inc_path                          := $(srcdir)

lib_path                          :=

lds                               := m

WARNING                           += -Wall
WARNING                           += -Wextra
WARNING                           += -Werror
WARNING                           += -Wfatal-errors
WARNING                           += -Wno-unused-local-typedefs
WARNING                           += -Wno-unused-variable
WARNING                           += -Wno-unused-function
WARNING                           += -Wno-unused-private-field
WARNING                           += -Wno-deprecated-declarations

OPTIMIZATION                      ?= -O0 -ggdb3

CXXFLAGS                          += $(WARNING)
CXXFLAGS                          += $(OPTIMIZATION)
CXXFLAGS                          += -std=c99

# If we are on the Apple computer
OS                                := $(shell uname)
ifeq ($(OS), Darwin)
    LDFLAGS                           += -framework OpenCL
else
    lds                               += OpenCL
    lds                               += dl
    lds                               += eocl
    lib_path                          += /usr/local/OpenCL/vendors/max
endif

CFLAGS                            := $(addprefix -I, $(inc_path))
CFLAGS                            += $(addprefix -L, $(lib_path))

obj                               := $(addprefix $(OBJDIR)/, $(notdir $(src)))
obj                               := $(obj:.c=.o)

lds                               := $(addprefix -l, $(lds))


empty :=
space := $(empty) $(empty)
vpath %.c $(subst $(space),:,$(sort $(dir $(src))))
vpath %.h $(subst $(space),:,$(inc_path))
vpath %.o $(OBJDIR)

.PHONY: all
all: $(appname)

$(appname): $(obj)
	$(Q) $(CXX) $^ $(CFLAGS) $(LDFLAGS) $(lds) -o $@

.PHONY: clean
clean:
	$(RM) -r $(BUILDDIR)

$(BUILDDIR):
	$(Q) $(MKDIR) $@

$(OBJDIR):
	$(Q) $(MKDIR) $@

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	@echo "$(CXX) $(notdir $<)"
	$(Q) $(CXX) $(CFLAGS) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.d: %.c | $(OBJDIR)
	@set -e; $(RM) $@; \
	$(CC) -MM -MT $(patsubst %$(suffix $<),$(dir $@)%.o,$(notdir $<)) $(CFLAGS) $(CXXFLAGS) $< > $@.$$$$; \
	$(SED) 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	$(RM) $@.$$$$

ifeq ($(filter clean,$(MAKECMDGOALS)),)
-include $(obj:.o=.d)
endif






