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

ROOT_PATH = ..

include ../make/common.mk

LDLIBS = -L$(LIB_DEST) -laeryn_tests -laeryn_core

PROG = $(BIN_DEST)TestClient

OBJS = main.o

all default : initialize $(PROG) 
	LD_LIBRARY_PATH=$(LIB_DEST) $(PROG)

initialize : 
	$(MKDIR) $(BIN_DEST)

$(PROG) : $(OBJS) 
	$(CXX) $(LDFLAGS) -o $(PROG) $(OBJS) $(LDLIBS)

rebuild: clean all

clean:
	$(RM) $(OBJS) *~

reallyclean : clean
	$(RM) $(PROG)

.PHONY : all default initialize rebuild clean reallyclean
