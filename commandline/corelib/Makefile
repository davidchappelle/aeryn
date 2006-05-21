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

LIB_NAME = aeryn_core

ROOT_PATH = ..

LIB_OBJS = \
	command_line_parser.o \
	command_line_test_set_builder.o \
	duplicate_test_name_found.o \
	duplicate_test_set_name_found.o \
	exception.o \
	failed.o \
	ireport.o \
	is_equal.o \
	is_false.o \
	is_not_equal.o \
	is_true.o \
	minimal_report.o \
	missing_test.o \
	noncopyable.o \
	terse_report.o \
	test_case.o \
	test_failure.o \
	test_funcs.o \
	test_name_not_found.o \
	test_set_cont.o \
	test_set_name_not_found.o \
	test_set_runner.o \
	test_registry.o \
	test_runner.o \
	use_name.o \
	verbose_report.o \
	xcode_report.o 
	
	

default : all

include ../make/libraryBuild.mk

SRC = $(ROOT_PATH)/src

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

test_runner.o : $(AERYN_INCLUDE)/test_failure.hpp
