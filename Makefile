#
#  glSpiders v. 0.0.1
#
#  Copyright (c) 2014, drmats
#  All rights reserved.
#
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions are met:
#
#  * Redistributions of source code must retain the above copyright notice,
#    this list of conditions and the following disclaimer.
#
#  * Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
#  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
#  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
#  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER
#  OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
#  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
#  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
#  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
#  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
#  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
#  IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

PNAME              = glSpiders
PLIBS              = glSpiders.o
ENVIRONMENT        =
CC                 = gcc
COMPILEFLAGS       = -Wall --std=c99 -O3
LINKLIBS           = -lm -lGL -lGLU -lglut
WINLINKLIBS        = -lm -lfreeglut -lopengl32 -lglu32
WINLINKLIBS_STATIC = -lm -lfreeglut_static -lopengl32 -lglu32 -lwinmm -lgdi32
WINLINKFLAGS       = -Wl,--subsystem,windows


.PHONY: default
default:
	@echo "Available targets:"
	@echo "  linux         build and link using gcc (linux)"
	@echo "  windows       build and link using MinGW (windows)"
	@echo "  win_static    build and link statically using MinGW (windows)"
	@echo "  clean         remove compiled objects and main program"

.PHONY: linux
linux:
ifeq ($(ENVIRONMENT),)
	@$(MAKE) gnu_execute ENVIRONMENT=dynamic
endif

.PHONY: windows
windows:
ifeq ($(ENVIRONMENT),)
	@$(MAKE) ms_execute ENVIRONMENT=dynamic
endif

.PHONY: win_static
win_static:
ifeq ($(ENVIRONMENT),)
	@$(MAKE) ms_static_execute ENVIRONMENT=static
endif

.PHONY: gnu_execute
gnu_execute:  $(PLIBS)
	@echo Linking project...
	@$(CC) $(PLIBS) $(LINKLIBS) -o $(PNAME)
	@echo $(PNAME) produced succesfully!

.PHONY: ms_execute
ms_execute:  $(PLIBS)
	@echo Linking project...
	@$(CC) $(PLIBS) $(WINLINKLIBS) $(WINLINKFLAGS) -o $(PNAME).exe
	@echo $(PNAME).exe produced succesfully!

.PHONY: ms_static_execute
ms_static_execute:  $(PLIBS)
	@echo Linking project...
	@$(CC) $(PLIBS) $(WINLINKLIBS_STATIC) $(WINLINKFLAGS) -o $(PNAME).exe
	@echo $(PNAME).exe produced succesfully!

.PHONY: clean
clean:
	@rm -v -f $(PNAME) $(PNAME).exe *.o

%.o:  %.c
	@echo Compiling: $<
ifeq ($(ENVIRONMENT),dynamic)
	@$(CC) $(COMPILEFLAGS) -c $< -o $@
endif
ifeq ($(ENVIRONMENT),static)
	@$(CC) $(COMPILEFLAGS) -DFREEGLUT_STATIC -c $< -o $@
endif
