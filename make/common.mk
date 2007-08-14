#  Aeryn2 -- a unit test framework for C++.
#
#  Copyright © 2005 Russel Winder
#  
#  This library is free software; you can redistribute it and/or modify it under the terms of
#  the GNU Lesser General Public License as published by the Free Software Foundation; either
#  version 2.1 of the License, or (at your option) any later version.
#  
#  This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
#  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#  See the GNU Lesser General Public License for more details.
# 
#  You should have received a copy of the GNU Lesser General Public License along with this
#  library; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
#  Boston, MA 02111-1307, USA

PLATFORM := UNIX

ifdef ComSpec
ifneq ($(OSTYPE), cygwin) 
ifneq (${OSTYPE}, msys)
ifneq (${OSTYPE}, posix)
PLATFORM := WIN32
endif
endif
endif
endif

ifeq (${PLATFORM}, WIN32)
VERSION := ${shell copy ${ROOT_PATH}/VERSION CON}
else
VERSION := $(shell cat $(ROOT_PATH)/VERSION)
endif

BIN_DEST := $(ROOT_PATH)/build/bin/
LIB_DEST := $(ROOT_PATH)/build/lib/
INCLUDE := $(ROOT_PATH)/include
AERYN_INCLUDE := $(INCLUDE)/aeryn

ifeq (${PLATFORM},WIN32)
RM = cmd /C del /F
CP = copy
MKDIR = mkdir -p
BIN_DEST := $(subst /,\,$(BIN_DEST))
LIB_DEST := $(subst /,\,$(LIB_DEST))
INCLUDE := $(subst /,\,$(INCLUDE))
AERYN_INCLUDE := $(subst /,\,$(AERYN_INCLUDE))
else
ifeq (${PLATFORM},UNIX)
RM = rm -f
MKDIR = mkdir -p
else
$(error "Machine is neither Windows nor UNIX in style.  Can't cope.")
endif
endif

CXXFLAGS += \
	-W \
	-Wall \
	-Werror \
	-Wshadow \
	-pedantic \
	-Wcast-qual \
	-Wcast-align \
	-Wwrite-strings \
	-Winline \
	-finline-limit=1048576 \
	-g3 \
	-DNO_OUTPUT_OPERATOR_DETECTION \
	-I$(INCLUDE)
