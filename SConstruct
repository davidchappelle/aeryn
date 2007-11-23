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
import platform
import re

unameResult = platform.uname ( )
osName = unameResult[0]
archName = re.sub ( 'i.86' , 'ix86' , unameResult[4].replace ( 'sun4u' , 'sparc' ) )
discriminator = '_' + osName + '_' + archName

versionNumber = open ( 'VERSION' ).readline ( ).strip ( )

coreSrcDir = 'src'
testsSrcDir = 'aeryntests'
testrunnerSrcDir = 'testrunner'
mainSrcDir = 'extras/mainlib'
testrunner2SrcDir = 'extras/testrunner2'

buildDir = 'build' + discriminator
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
    sourceDirectory = Dir ( '.' ).srcnode ( ).abspath
    librarySource = [ file.replace ( sourceDirectory + '/' , '' ) for file in glob.glob ( sourceDirectory + '/*.cpp' ) ]
    staticLibrary = e.StaticLibrary ( os.path.join ( e [ 'LIB_DIR' ] , libraryName ) , librarySource )
    #  Linux appears to deliver posix as the platform.
    if e [ 'PLATFORM' ] in [ 'sunos' , 'posix' ] :
        versionNumber = e [ 'VERSION_NUMBER' ]
        baseName = e.subst ( '$SHLIBPREFIX' ) + libraryName + e [ 'SHLIBSUFFIX' ]
        basePath = os.path.join ( e [ 'LIB_DIR' ] , baseName )
        fullName = baseName + '.' + versionNumber
        fullPath = os.path.join ( e [ 'LIB_DIR' ] , fullName )
        soName = baseName + '.' + versionNumber.split ( '.' )[0]
        soPath = os.path.join ( e [ 'LIB_DIR' ] , soName )
        e.Append ( SHLINKFLAGS = '-Wl,-soname=' +  soName )
        #  SharedLibrary always appends e [ 'SHLIBSUFFIX' ] which is no good for a single step build.  Do
        #  things in two stages.
        sharedLibrary = e.SharedLibrary ( libraryName , librarySource )
        e.InstallAs ( fullPath , sharedLibrary )
        #
        #  There appears to be a problem in SCons 0.97 which means the second of the following fails to be
        #  executed -- which is a showstopper.  Hack round this for now by cheating.
        #
        #e.Command ( basePath , fullPath , 'cd ' + e [ 'LIB_DIR' ] [1:] + ' && ln -s ' + fullName + ' ' + baseName )
        #e.Command ( soPath , fullPath , 'cd ' + e [ 'LIB_DIR' ] [1:] + ' && ln -s ' + fullName + ' ' + soName )
        #
        e.Command ( [ basePath , soPath ] , fullPath , 'cd ' + e [ 'LIB_DIR' ] [1:] + ' && ln -s ' + fullName + ' ' + baseName + ' && ln -s ' + fullName + ' ' + soName)    
    elif e [ 'PLATFORM' ] == 'darwin' :
        e.Append ( SHLINKFLAGS = '-undefined dynamic_lookup' )
        e.SharedLibrary ( os.path.join ( e [ 'LIB_DIR' ] , libraryName ) , librarySource )
    elif e [ 'PLATFORM' ] in [ 'win32' , 'cygwin' ] :
        pass # For the moment ignore shared libraries on Windows.
    else :
        raise ValueError , "PLATFORM had value " + e [ 'PLATFORM' ] + " which is not catered for"

def constructExecutableDependencies ( name , sources , libraries , env ) :
    executable = env.Program ( os.path.join ( env [ 'BIN_DIR' ] , name ) , sources , LIBPATH = env [ 'LIB_DIR' ] , LIBS = libraries )
    if env [ 'PLATFORM' ] in [ 'sunos' , 'posix' ] :
        commandString = 'LD_LIBRARY_PATH=' + env [ 'LIB_DIR' ] [ 1: ] + ' $SOURCE'
    elif env [ 'PLATFORM' ] == 'darwin' :
        commandString = 'DYLD_LIBRARY_PATH=' + env [ 'LIB_DIR' ] [ 1: ] + ' $SOURCE'
    elif env [ 'PLATFORM' ] in [ 'win32' , 'cygwin' ] :
        commandString = './$SOURCE'
    else :
        raise ValueError , "PLATFORM had value " + env [ 'PLATFORM' ] + " which is not catered for"
    Command (  'test.execute' , executable , commandString )

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

env.SConsignFile ( '.sconsign' + discriminator )

Export ( 'env' )

SConscript ( os.path.join ( coreSrcDir, 'SConscript' ) , build_dir = coreBuildDir , duplicate = 0 )
SConscript ( os.path.join ( testsSrcDir, 'SConscript' ) , build_dir = testsBuildDir , duplicate = 0 )
SConscript ( os.path.join ( mainSrcDir , 'SConscript' ) , build_dir = mainBuildDir , duplicate = 0 )
SConscript ( os.path.join ( testrunnerSrcDir , 'SConscript' ) , build_dir = testrunnerBuildDir , duplicate = 0 )
SConscript ( os.path.join ( testrunner2SrcDir , 'SConscript' ) , build_dir = testrunner2BuildDir , duplicate = 0 )

def listEmacsSaveFiles ( ) :
    fileList = []
    for root , dirs , files in os.walk ( '.' ) :
        fileList = fileList + [ os.path.join ( root , f ) for f in files if re.compile ( ".*~" ).search ( f ) ]
    return fileList

Clean ( '.' , [ listEmacsSaveFiles ( ) , buildDir ] )
