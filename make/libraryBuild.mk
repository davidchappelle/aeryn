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
#  library; if not, write to the Free Software Foundation, Inc., 51 Franklin Street,Fifth Floor,
#  Boston, MA 02111-1307, USA

include $(ROOT_PATH)/make/common.mk

SHLIB_OBJS = $(subst .o,.os,$(LIB_OBJS))

RANLIB = ranlib

LIB_FILE = $(LIB_DEST)lib$(LIB_NAME).a

ifeq (${PLATFORM}, UNIX)
ifdef COMSPEC

SHLIB_FILE = $(LIB_DEST)lib$(LIB_NAME).dll
SHLIB_SONAME = $(LIB_DEST)lib$(LIB_NAME).dll

#  Building shared libraries on Windows seems vastly too complicated so don't.

all : initialize $(LIB_FILE)

else

LN_S = ln -s
SHLIB_FILE = $(LIB_DEST)lib$(LIB_NAME).so.$(VERSION)
SHLIB_SONAME = $(LIB_DEST)lib$(LIB_NAME).so.$(word 1,$(subst ., ,$(VERSION)))
SHLIB_LIBNAME = $(LIB_DEST)lib$(LIB_NAME).so

all : initialize $(LIB_FILE) $(SHLIB_FILE) $(SHLIB_SONAME) $(SHLIB_LIBNAME)

endif
endif

initialize :
	$(MKDIR) $(LIB_DEST)

$(LIB_FILE) : $(LIB_OBJS)
	$(AR) rc $(LIB_FILE) $(LIB_OBJS)
	$(RANLIB) $(LIB_FILE)

$(SHLIB_FILE) : $(SHLIB_OBJS) 
	$(CXX) -shared -Wl,-soname=$(notdir $(SHLIB_SONAME)) $(CXXFLAGS)  $(LDFLAGS) -o $@ $(SHLIB_OBJS) $(LDLIBS)

ifndef COMSPEC 

$(SHLIB_SONAME) : $(SHLIB_FILE)
	cd $(LIB_DEST) && $(LN_S) $(notdir $<) $(notdir $@)

$(SHLIB_LIBNAME) : $(SHLIB_FILE)
	cd $(LIB_DEST) && $(LN_S) $(notdir $<) $(notdir $@)

endif

rebuild : clean all

clean :
	$(RM) $(LIB_OBJS) $(SHLIB_OBJS) *~

reallyclean : clean
	$(RM) $(LIB_FILE) $(SHLIB_FILE) $(SHLIB_SONAME) $(SHLIB_LIBNAME)

.PHONY : all default initialize rebuild clean cleanall
