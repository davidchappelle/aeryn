# -*- coding: UTF-8 -*-

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

import os.path
import re

versionNumber = open ( 'VERSION' ).readline ( ).strip ( )

coreSrcDir = 'src'
testsSrcDir = 'tests'
testrunnerSrcDir = 'testrunner'
testrunner2SrcDir = 'testrunner2'

buildDir = 'build'
includeDir = 'include'

binDir = os.path.join ( buildDir , 'bin' )
libDir = os.path.join ( buildDir , 'lib' )

coreBuildDir = os.path.join ( buildDir , 'core' )
testsBuildDir = os.path.join ( buildDir , 'tests' )
testrunnerBuildDir = os.path.join ( buildDir , 'testrunner' )
testrunner2BuildDir = os.path.join ( buildDir , 'testrunner2' )

env = Environment (
    CXXFLAGS = '-W -Wall -Werror -pedantic -Wcast-qual -Wcast-align -Wwrite-strings -Winline -finline-limit=1048576 -g3 -DNO_OUTPUT_OPERATOR_DETECTION' ,
    CPPPATH = '#' + includeDir ,
    BIN_DIR = '#' + binDir ,
    LIB_DIR = '#' + libDir ,
    VERSION_NUMBER = versionNumber
    )

#  Paul has a build system already for MSVC so this build is to use MinGW on Win32.

if env [ 'PLATFORM' ] == 'win32' :
    env.Tool ( 'mingw' )

Export ( 'env' )

#  Out of tree builds do not work.  First build is fine but after that it just does not do the
#  right thing.  Email sent to list 2005-10-29 07:25.  SourceForge Bug 1328881 relates.

#SConscript ( os.path.join ( coreSrcDir, 'SConscript' ) , build_dir = coreBuildDir , duplicate = 0 )
#SConscript ( os.path.join ( testsSrcDir , 'SConscript' ) , build_dir = testsBuildDir , duplicate = 0 )
#SConscript ( os.path.join ( testrunnerSrcDir , 'SConscript' ) , build_dir = testrunnerBuildDir , duplicate = 0 )
#SConscript ( os.path.join ( testrunner2SrcDir , 'SConscript' ) , build_dir = testrunner2BuildDir , duplicate = 0 )

SConscript ( os.path.join ( coreSrcDir, 'SConscript' ) )
SConscript ( os.path.join ( testsSrcDir , 'SConscript' ) )
SConscript ( os.path.join ( testrunnerSrcDir , 'SConscript' ) )
SConscript ( os.path.join ( testrunner2SrcDir , 'SConscript' ) )

def listEmacsSaveFiles ( ) :
    fileList = []
    for root , dirs , files in os.walk ( '.' ) :
        fileList = fileList + [ os.path.join ( root , f ) for f in files if re.compile ( ".*~" ).search ( f ) ]
    return fileList

Clean ( '.' , [ listEmacsSaveFiles ( ) , buildDir ] )
