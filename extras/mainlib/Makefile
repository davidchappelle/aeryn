#  Aeryn2 -- a unit test framework for C++.
#
# Copyright © 2005 Russel Winder
#  
#  This library is free software; you can redistribute it and/or modify it under the terms of
#  the GNU Lesser General Public License as published by the Free Software Foundation; either
#  version 2 of the License, or (at your option) any later version.
#  
#  This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
#  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#  See the GNU Lesser General Public License for more details.
# 
#  You should have received a copy of the GNU Lesser General Public License along with this
#  library; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330,
#  Boston, MA 02111-1307 USA

LIB_NAME = aeryn_main

ROOT_PATH = ../..

LIB_OBJS = \
	main.o

default : all

include ../../make/libraryBuild.mk

SRC = $(ROOT_PATH)/extras/mainlib

%.o : $(SRC)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o : $(AERYN_INCLUDE)/%.hpp

%.os : $(SRC)/%.cpp
ifeq (${PLATFORM},UNIX)
	$(CXX) -fPIC $(CXXFLAGS) -c -o $@ $<
else
	$(CXX) $(CXXFLAGS) -c -o $@ $<
endif

%.os : $(AERYN_INCLUDE)/%.hpp

