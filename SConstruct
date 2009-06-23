# -*- mode:python; coding:utf-8; -*-

#  Aeryn2 -- a unit test framework for C++.
#
#   Copyright © 2005,2007-9 Russel Winder
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

import os.path
import platform
import re

try :
    versionNumber = file ( 'VERSION' ).readline ( ).strip ( )
except :
    print 'Version file not present, build will not be undertaken.'
    Exit ( 1 )

#  Support concurrent builds for different platforms in the same tree (i.e. shared fielstore) by creating a
#  discrminator that is used to provide platform specific names for the build directory and the SCons
#  control files.  This does not provide for concurrent builds using the same platform of course.

unameResult = platform.uname ( )
osName = unameResult[0]
archName = re.sub ( 'i.86' , 'ix86' , unameResult[4].replace ( 'sun4u' , 'sparc' ) )
discriminator = '_' + osName + '_' + archName

#  The project directory structure.

coreSrcDir = 'src'
incSrcDir = 'include'
testsSrcDir = 'aeryntests'
testrunnerSrcDir = 'testrunner'
mainSrcDir = os.path.join ( 'extras' , 'mainlib' )
testrunner2SrcDir = os.path.join ( 'extras' , 'testrunner2' )

buildDir = 'build' + discriminator
buildBinDir = os.path.join ( buildDir , 'bin' )
buildLibDir = os.path.join ( buildDir , 'lib' )

#  Deduce the installation locations.  There is a default.  This can be overridden using environment
#  variables.  This can be overwritten using the content of a file in the current directory.  This can be
#  overwritten using command line arguments.

defaultPrefix = '/usr/local'
defaultInstallIncDirSubdirectory = 'include'
defaultInstallLibDirSubdirectory = 'lib'
defaultInstallIncDir = os.path.join ( defaultPrefix , defaultInstallIncDirSubdirectory )
defaultInstallLibDir = os.path.join ( defaultPrefix , defaultInstallLibDirSubdirectory )
prefix = defaultPrefix
installIncDir = defaultInstallIncDir
installLibDir = defaultInstallLibDir
if os.environ.has_key ( 'PREFIX' ) :
    prefix = os.environ['PREFIX']
    installIncDir =  os.path.join ( prefix , defaultInstallIncDirSubdirectory )
    installLibDir =  os.path.join ( prefix , defaultInstallLibDirSubdirectory )
if os.environ.has_key ( 'INCDIR' ) : installIncDir = os.environ['INCDIR']
if os.environ.has_key ( 'LIBDIR' ) : installLibDir = os.environ['LIBDIR']
defaultPrefix = prefix
defaultInstallIncDir = installIncDir
defaultInstallLibDir = installLibDir
localBuildOptions = 'local.build.options'
if os.access ( localBuildOptions , os.R_OK ) :
    execfile ( localBuildOptions )
if prefix != defaultPrefix :
    if installIncDir == defaultInstallIncDir : installIncDir =  os.path.join ( prefix , defaultInstallIncDirSubdirectory )
    if installLibDir == defaultInstallLibDir : installLibDir =  os.path.join ( prefix , defaultInstallLibDirSubdirectory )
if ARGUMENTS.has_key ( 'prefix' ) :
    prefix = ARGUMENTS.get ( 'prefix' )
    installIncDir =  os.path.join ( prefix , defaultInstallIncDirSubdirectory )
    installLibDir =  os.path.join ( prefix , defaultInstallLibDirSubdirectory )
installIncDir = ARGUMENTS.get ( 'installIncDir' , installIncDir )
installLibDir = ARGUMENTS.get ( 'installLibDir' , installLibDir )


env = Environment (
    CXXFLAGS = '-W -Wall -Werror -pedantic -Wcast-qual -Wcast-align -Wwrite-strings -Winline -finline-limit=1048576 -g3 -DNO_OUTPUT_OPERATOR_DETECTION' ,
    CPPPATH = [ '#' + incSrcDir ] ,
    )

env.SConsignFile ( '.sconsign' + discriminator )

Export ( 'env' )

#  Dynamic libraries on Linux and Solaris have a full name.  There are symbolic links to this for the soname
#  and a basename with no version information.  This function creates and returns a list of Commands for
#  achieving the goal.  The way in which this and the following function are used in two entirely different
#  contexts leads to the rather bizarre code and parameter structure.

def commandsForLibraryLinks ( directory , ( baseName , basePath , soName , soPath , fullName , fullPath ) ) :
    '''Return the list of Commands for creating appropriate symbolic links to a dynamic library.'''
    return [ 
        env.Command ( basePath , fullPath , 'cd %s && rm -f %s && ln -s %s %s' %  ( directory , baseName , fullName , baseName ) ) ,
        env.Command ( soPath , fullPath , 'cd %s && rm -f %s && ln -s %s %s' %  ( directory , soName , fullName , soName ) ) ,
        ]
    
def createLibraryLinkNames ( path , libraryName ) :
    '''Return all the names and paths of the shared library and symbolic links for Solaris and Linux.'''
    baseName = env.subst ( '$SHLIBPREFIX' ) + libraryName + env['SHLIBSUFFIX' ]
    basePath = os.path.join ( path , baseName )
    fullName = baseName + '.' + versionNumber
    fullPath = os.path.join ( path , fullName )
    soName = baseName + '.' + versionNumber.split ( '.' )[0]
    soPath = os.path.join ( path , soName )
    return ( baseName , basePath , soName , soPath , fullName , fullPath )

def constructLibraryDependencies ( libraryName ) :
    '''Create all the necessary constructions to make the static and dynamic libraries.
    Return a tuple containing the build product list and the install product list.'''
    #  This will be called in subdirectories so ensure all paths are given # prefixes.
    e = env.Clone ( )
    librarySource = Glob ( '*.cpp' )
    buildProducts = [ ]
    installProducts = [ ]
    staticLibrary = e.StaticLibrary ( os.path.join ( '#' + buildLibDir , libraryName ) , librarySource )
    buildProducts += [ staticLibrary ]
    installProducts += [ staticLibrary ]
    #  Linux appears to deliver posix as the platform.
    if e['PLATFORM'] in [ 'sunos' , 'posix' ] :
        ( baseName , basePath , soName , soPath , fullName , fullPath ) = allTheNames = createLibraryLinkNames ( '#' + buildLibDir , libraryName )
        e.Append ( SHLINKFLAGS = '-Wl,-soname=' +  soName )
        #  SharedLibrary always appends e [ 'SHLIBSUFFIX' ] which is no good for a single step build.  Do
        #  things in two stages.
        sharedLibrary = e.InstallAs ( fullPath , e.SharedLibrary ( libraryName , librarySource ) )
        buildProducts += [ sharedLibrary ] + commandsForLibraryLinks ( buildLibDir , allTheNames )
        installProducts += [ sharedLibrary ]
    elif e['PLATFORM'] == 'darwin' :
        e.Append ( SHLINKFLAGS = '-undefined dynamic_lookup' )
        sharedLibrary = e.SharedLibrary ( os.path.join ( '#' + buildLibDir , libraryName ) , librarySource )
        buildProducts += [ sharedLibrary ] 
        installProducts += [ sharedLibrary ] 
    elif e['PLATFORM'] in [ 'win32' , 'cygwin' ] : pass # For the moment ignore shared libraries on Windows.
    else : raise ValueError , "PLATFORM had value " + e['PLATFORM'] + " which is not catered for."
    return ( buildProducts , installProducts )
env['ConstructLibraryDependencies'] = constructLibraryDependencies

def constructExecutableDependencies ( name , sources , libraries ) :
    '''Create all the necessary constructions to make the executables used for testing.
    Return the list of build products.'''
    #  This will be called in subdirectories so ensure all paths are given # prefixes.
    return env.Program ( os.path.join ( '#' + buildBinDir , name ) , sources , LIBPATH = '#' + buildLibDir , LIBS = libraries )
env['ConstructExecutableDependencies'] = constructExecutableDependencies

( buildProducts , installProducts ) = SConscript ( os.path.join ( coreSrcDir, 'SConscript' ) , variant_dir = os.path.join ( buildDir , coreSrcDir ) , duplicate = 0 )

Alias ( 'build' , buildProducts )

testBuildProducts = \
  SConscript ( os.path.join ( mainSrcDir , 'SConscript' ) , variant_dir = os.path.join ( buildDir , mainSrcDir ) , duplicate = 0 ) \
  + SConscript ( os.path.join ( testsSrcDir, 'SConscript' ) , variant_dir = os.path.join ( buildDir , testsSrcDir ) , duplicate = 0 )

testExecuteProducts = \
  SConscript ( os.path.join ( testrunnerSrcDir , 'SConscript' ) , variant_dir = os.path.join ( buildDir , testrunnerSrcDir ) , duplicate = 0 ) \
  + SConscript ( os.path.join ( testrunner2SrcDir , 'SConscript' ) , variant_dir = os.path.join ( buildDir , testrunner2SrcDir ) , duplicate = 0 )

Alias ( 'buildTests' , [ buildProducts , testBuildProducts , testExecuteProducts ] )

if env['PLATFORM'] in [ 'sunos' , 'posix' ] : commandPrefix = 'LD_LIBRARY_PATH=' + buildLibDir
elif env['PLATFORM'] == 'darwin' : commandPrefix = 'DYLD_LIBRARY_PATH=' + buildLibDir 
elif env['PLATFORM'] in [ 'win32' , 'cygwin' ] : commandPrefix = ''
else : raise ValueError , "PLATFORM had value " + env['PLATFORM'] + " which is not catered for"

Command ( 'runTests' , 'buildTests' , [ commandPrefix + ' ' + item.abspath for item in testExecuteProducts ] )

def installsOfIncludeFiles ( ) :
    installList = [ ]
    for root , dirs , files in os.walk ( incSrcDir ) :
        for f in files :
           installList += [ Install ( os.path.join ( installIncDir , '..' , root ) , os.path.join ( root , f ) ) ]
    return installList

Alias ( 'installWithoutTesting' , installsOfIncludeFiles ( ) + [ Install ( installLibDir , installProducts ) ] +
        ( commandsForLibraryLinks ( installLibDir , createLibraryLinkNames ( installLibDir , 'aeryn_core' ) ) if env['PLATFORM'] in [ 'sunos' , 'posix' ] else [ ] )
        )

Alias ( 'install' , [ 'runTests' , 'installWithoutTesting' ] )

def listEmacsSaveFiles ( ) :
    fileList = [ ]
    for root , dirs , files in os.walk ( '.' ) :
        fileList = fileList + [ os.path.join ( root , f ) for f in files if re.compile ( ".*~" ).search ( f ) ]
    return fileList

Clean ( '.' , [ listEmacsSaveFiles ( ) , buildDir ] )

Default ( 'runTests' )

Help ( '''
The possible targets are:

    build
    buildTests
    runTests
    install
    installWithoutTesting

The default target is test.
''' )
