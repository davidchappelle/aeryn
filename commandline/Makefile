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

ROOT_PATH := .

include make/common.mk

all :
	cd corelib && $(MAKE)
	cd tests && $(MAKE)
	cd testrunner && $(MAKE)
	cd testrunner2 && $(MAKE)

clean : cleanhere
	cd corelib && $(MAKE) clean
	cd tests && $(MAKE) clean
	cd testrunner && $(MAKE) clean
	cd testrunner2 && $(MAKE) clean

reallyclean : cleanhere
	cd corelib && $(MAKE) reallyclean
	cd tests && $(MAKE) reallyclean
	cd testrunner && $(MAKE) reallyclean
	cd testrunner2 && $(MAKE) reallyclean
	rm -rf build

rebuild : reallyclean all

cleanhere :
	$(RM) *~
	cd make && $(RM) *~
