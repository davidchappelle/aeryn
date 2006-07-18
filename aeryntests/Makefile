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

LIB_NAME = aeryn_tests

ROOT_PATH = ..

LIB_OBJS = \
	add_tests.o \
	command_line_parser_test.o \
	context_object_test.o \
	minimal_report_test.o \
	simple_date.o \
	simple_date_test.o \
	terse_report_test.o \
	test_failure_test.o \
	test_func_test.o \
	test_runner_test.o \
	throws_exception_test.o \
	verbose_report_test.o

default : all

include ../make/libraryBuild.mk

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o : %.hpp

%.os : %.cpp
ifdef COMPSPEC
	$(CXX) $(CXXFLAGS) -c -o $@ $<
else
	$(CXX) -fPIC $(CXXFLAGS) -c -o $@ $<
endif

%.os : %.hpp
