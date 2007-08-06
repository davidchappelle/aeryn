# -*- mode:python encoding: UTF-8 -*-

#  Aeryn2 -- a unit test framework for C++.
#
#   Copyright © 2005,2007 Russel Winder
#  
#  This program is free software: you can redistribute it and/or modify it under the terms of the GNU
#  General Public License as published by the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
#   the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
#   License for more details.
#
#  You should have received a copy of the GNU General Public License along with this program.  If not, see
#  <http://www.gnu.org/licenses/>.

import glob
import os.path
import re

versionNumber = open ( 'VERSION' ).readline ( ).strip ( )

coreSrcDir = 'src'
testsSrcDir = 'aeryntests'
testrunnerSrcDir = 'testrunner'
mainSrcDir = 'extras/mainlib'
testrunner2SrcDir = 'extras/testrunner2'

buildDir = 'build'
includeDir = 'include'

binDir = os.path.join ( buildDir , 'bin' )
libDir = os.path.join ( buildDir , 'lib' )

coreBuildDir = os.path.join ( buildDir , coreSrcDir )
testsBuildDir = os.path.join ( buildDir , testsSrcDir )
testrunnerBuildDir = os.path.join ( buildDir , testrunnerSrcDir )
mainBuildDir = os.path.join ( buildDir , mainSrcDir )
testrunner2BuildDir = os.path.join ( buildDir , testrunner2SrcDir )

def constructLibraryDependencies ( libraryName , env ) :
    '''Create all the necessary SCons constructions to make the static and dynamic libraries.'''
    e = env.Copy ( )
    libDir = e [ 'LIB_DIR' ]
    sourceDirectory = Dir ( '.' ).srcnode ( ).abspath
    librarySource = [ file.replace ( sourceDirectory + '/' , '' ) for file in glob.glob ( sourceDirectory + '/*.cpp' ) ]
    staticLibrary = e.StaticLibrary ( libraryName , librarySource )
    e.Install ( libDir , staticLibrary )
    #  Building shared libraries on Windows is more trouble than it is worth.
    if e [ 'PLATFORM' ] != 'win32' and e [ 'PLATFORM' ] != 'cygwin' :
        versionNumber = e [ 'VERSION_NUMBER' ]
        if e [ 'PLATFORM' ] == 'darwin' :
            return
            libraryNameBase = e.subst ( '$SHLIBPREFIX' ) + libraryName
            baseName = libraryNameBase + e [ 'SHLIBSUFFIX' ]
            basePath = os.path.join ( libDir , baseName )
            fullName = libraryNameBase + '.' + versionNumber + e [ 'SHLIBSUFFIX' ]
            fullPath = os.path.join ( libDir , fullName )
            soName = libraryNameBase + '.' + versionNumber.split ( '.' )[0] + e [ 'SHLIBSUFFIX' ]
            soPath = os.path.join ( libDir , soName )
        else :
            baseName = e.subst ( '$SHLIBPREFIX' ) + libraryName + e [ 'SHLIBSUFFIX' ]
            basePath = os.path.join ( libDir , baseName )
            fullName = baseName + '.' + versionNumber
            fullPath = os.path.join ( libDir , fullName )
            soName = baseName + '.' + versionNumber.split ( '.' )[0]
            soPath = os.path.join ( libDir , soName )
        e.Append ( SHLINKFLAGS = '-Wl,-soname=' +  soName )
        sharedLibrary = e.SharedLibrary ( libraryName , librarySource )
        if str ( sharedLibrary[0] ) != baseName :
            print "******************************************** PANIC NOW *****************************"
            print 'produced = ' + str ( sharedLibrary[0] )
            print 'expected = ' + baseName
        e.InstallAs ( fullPath , sharedLibrary )
        #  There appears to be a problem in SCons 0.97 which means the second of the following fails to work
        #  -- which is a showstopper.  Hack round this for now by cheating.
        #
        #e.Command ( basePath , fullPath , 'cd ' + libDir[1:] + ' && ln -s ' + fullName + ' ' + baseName )
        #e.Command ( soPath , fullPath , 'cd ' + libDir[1:] + ' && ln -s ' + fullName + ' ' + soName )        
        e.Command ( [ basePath , soPath ] , fullPath , 'cd ' + libDir[1:] + ' && ln -s ' + fullName + ' ' + baseName + ' && ln -s ' + fullName + ' ' + soName)

def constructExecutableDependencies ( name , sources , libraries , env ) :
    e = env.Copy ( )
    e.Replace ( LIBPATH = env [ 'LIB_DIR' ] )
    e.Replace ( LIBS = libraries )
    executable = os.path.join ( e [ 'BIN_DIR' ] , name )
    main = e.Program ( 'main' , sources )
    e.InstallAs ( executable , main )
    if e [ 'PLATFORM' ] == 'darwin' :
        Command ( 'test.execute' , executable , 'DYLD_LIBRARY_PATH=' + e [ 'LIB_DIR' ] [ 1: ] + ' $SOURCE' )
    elif e [ 'PLATFORM' ] == 'win32' :
        Command ( 'test.execute' , executable , '$SOURCE' )
    else :
        Command ( 'test.execute' , executable , 'LD_LIBRARY_PATH=' + e [ 'LIB_DIR' ] [ 1: ] + ' $SOURCE' )

env = Environment (
    CXXFLAGS = '-W -Wall -Werror -pedantic -Wcast-qual -Wcast-align -Wwrite-strings -Winline -finline-limit=1048576 -g3 -DNO_OUTPUT_OPERATOR_DETECTION' ,
    CPPPATH = '#' + includeDir ,
    BIN_DIR = '#' + binDir ,
    LIB_DIR = '#' + libDir ,
    VERSION_NUMBER = versionNumber ,
    ConstructLibraryDependencies = constructLibraryDependencies ,
    ConstructExecutableDependencies = constructExecutableDependencies
    )

#if env [ 'PLATFORM' ] == 'win32' :
#    env.Tool ( 'mingw' )

Export ( 'env' )

SConscript ( os.path.join ( coreSrcDir, 'SConscript' ) , build_dir = coreBuildDir , duplicate = 0 )
SConscript ( os.path.join ( testsSrcDir, 'SConscript' ) , build_dir = testsBuildDir , duplicate = 0 )
SConscript ( os.path.join ( testrunnerSrcDir , 'SConscript' ) , build_dir = testrunnerBuildDir , duplicate = 0 )
SConscript ( os.path.join ( mainSrcDir , 'SConscript' ) , build_dir = mainBuildDir , duplicate = 0 )
SConscript ( os.path.join ( testrunner2SrcDir , 'SConscript' ) , build_dir = testrunner2BuildDir , duplicate = 0 )

def listEmacsSaveFiles ( ) :
    fileList = []
    for root , dirs , files in os.walk ( '.' ) :
        fileList = fileList + [ os.path.join ( root , f ) for f in files if re.compile ( ".*~" ).search ( f ) ]
    return fileList

Clean ( '.' , [ listEmacsSaveFiles ( ) , buildDir ] )
