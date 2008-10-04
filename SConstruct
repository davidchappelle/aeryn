# -*- coding:utf-8 mode:python -*-

#  Aeryn2 -- a unit test framework for C++.
#
#   Copyright © 2005,2007-8 Russel Winder
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
import sys

#  So as to support concurrent builds using different architectures in the same tree (i.e. shared
#  fielstore), we create a discrminator to be used for the build target directory and the SCons control
#  files.

unameResult = platform.uname ( )
osName = unameResult[0]
archName = re.sub ( 'i.86' , 'ix86' , unameResult[4].replace ( 'sun4u' , 'sparc' ) )
discriminator = '_' + osName + '_' + archName

try :
    versionNumber = file ( 'VERSION' ).readline ( ).strip ( )
except :
    print 'Version file not present, build will not be undertaken.'
    sys.exit ( 1 )

coreSrcDir = 'src'
incSrcDir = 'include'
testsSrcDir = 'aeryntests'
testrunnerSrcDir = 'testrunner'
mainSrcDir = os.path.join ( 'extras' , 'mainlib' )
testrunner2SrcDir = os.path.join ( 'extras' , 'testrunner2' )

buildDir = 'build' + discriminator
buildBinDir = os.path.join ( buildDir , 'bin' )
buildLibDir = os.path.join ( buildDir , 'lib' )

env = Environment (
    CXXFLAGS = '-W -Wall -Werror -pedantic -Wcast-qual -Wcast-align -Wwrite-strings -Winline -finline-limit=1048576 -g3 -DNO_OUTPUT_OPERATOR_DETECTION' ,
    CPPPATH = [ '#' + incSrcDir ] ,
    )

env.SConsignFile ( '.sconsign' + discriminator )

Export ( 'env' )

def createLibraryLinks ( ( directory , baseName , soName , fullName ) ) :
    return 'cd %s && rm -f %s %s && ln -s %s %s && ln -s %s %s' %  ( directory , baseName , soName , fullName , baseName , fullName , soName )
    
def libraryLinks ( path , libraryName ) :
    '''Return all the names and paths of the shared library and symbolic links for Solaris and Linux.
    Sets up the link command.'''
    baseName = env.subst ( '$SHLIBPREFIX' ) + libraryName + env['SHLIBSUFFIX' ]
    basePath = os.path.join ( path , baseName )
    fullName = baseName + '.' + versionNumber
    fullPath = os.path.join ( path , fullName )
    soName = baseName + '.' + versionNumber.split ( '.' )[0]
    soPath = os.path.join ( path , soName )
    env.Command ( [ basePath , soPath ] , fullPath , createLibraryLinks ( ( ( path[1:] if path[0] == '#' else path ) , baseName , soName , fullName ) ) )
    return ( baseName , basePath , soName , soPath , fullName , fullPath )

def constructLibraryDependencies ( libraryName ) :
    '''Create all the necessary constructions to make the static and dynamic libraries.
    Return a tuple containing the build product list, the test product list and the install product list.'''
    #  This will be called in subdirectories so ensure all paths are given # prefixes.
    e = env.Clone ( )
    librarySource = Glob ( '*.cpp' )
    buildProducts = [ ]
    testProducts = [ ]
    installProducts = [ ]
    staticLibrary = e.StaticLibrary ( os.path.join ( '#' + buildLibDir , libraryName ) , librarySource )
    buildProducts += [ staticLibrary ]
    installProducts += [ staticLibrary ]
    #  Linux appears to deliver posix as the platform.
    if e['PLATFORM'] in [ 'sunos' , 'posix' ] :
        ( baseName , basePath , soName , soPath , fullName , fullPath ) = libraryLinks ( '#' + buildLibDir , libraryName )
        e.Append ( SHLINKFLAGS = '-Wl,-soname=' +  soName )
        #  SharedLibrary always appends e [ 'SHLIBSUFFIX' ] which is no good for a single step build.  Do
        #  things in two stages.
        sharedLibrary = e.SharedLibrary ( libraryName , librarySource )
        e.InstallAs ( fullPath , sharedLibrary )
        buildProducts += [ basePath , soPath , fullPath ] 
        installProducts += [ fullPath ] 
    elif e['PLATFORM'] == 'darwin' :
        e.Append ( SHLINKFLAGS = '-undefined dynamic_lookup' )
        sharedLibrary = e.SharedLibrary ( os.path.join ( '#' + buildLibDir , libraryName ) , librarySource )
        buildProducts += [ sharedLibrary ] 
        installProducts += [ sharedLibrary ] 
    elif e['PLATFORM'] in [ 'win32' , 'cygwin' ] : pass # For the moment ignore shared libraries on Windows.
    else : raise ValueError , "PLATFORM had value " + e['PLATFORM'] + " which is not catered for."
    return ( buildProducts , testProducts , installProducts )
env['ConstructLibraryDependencies'] = constructLibraryDependencies

def constructExecutableDependencies ( name , sources , libraries ) :
    '''Create all the necessary constructions to make the executables used for testing.
    Return a tuple containing the build product list, the test product list and the install product list.'''
    #  This will be called in subdirectories so ensure all paths are given # prefixes.
    buildProducts = [ ]
    testProducts = [ ]
    installProducts = [ ]
    executable = env.Program ( os.path.join ( '#' + buildBinDir , name ) , sources , LIBPATH = '#' + buildLibDir , LIBS = libraries )
    buildProducts += [ executable ]
    if env['PLATFORM'] in [ 'sunos' , 'posix' ] : commandString = 'LD_LIBRARY_PATH=' + buildLibDir + ' $SOURCE'
    elif env['PLATFORM'] == 'darwin' : commandString = 'DYLD_LIBRARY_PATH=' + buildLibDir + ' $SOURCE'
    elif env['PLATFORM'] in [ 'win32' , 'cygwin' ] : commandString = os.path.join ( '.' , '$SOURCE' )
    else : raise ValueError , "PLATFORM had value " + env['PLATFORM'] + " which is not catered for"
    testProducts += [ Command (  'test.execute' , executable , commandString ) ]
    return  ( buildProducts , testProducts , installProducts )
env['ConstructExecutableDependencies'] = constructExecutableDependencies

buildProducts = [ ]
testProducts = [ ]
installProducts = [ ]

def processSConscript ( sconscript , buildDir , install = False ) :
    '''Issue the SConscript calls and process the return values.
    Each call returns a tuple of the build product list, the test product list and the install product list.
    Only install selected install products.'''
    global buildProducts
    global testProducts
    global installProducts
    ( b , t , i ) = SConscript ( sconscript , build_dir = buildDir , duplicate = 0 )
    buildProducts += b
    testProducts += t
    if install : installProducts += i

processSConscript ( os.path.join ( coreSrcDir, 'SConscript' ) , os.path.join ( buildDir , coreSrcDir ) , True )
processSConscript ( os.path.join ( testsSrcDir, 'SConscript' ) , os.path.join ( buildDir , testsSrcDir ) )
processSConscript ( os.path.join ( mainSrcDir , 'SConscript' ) , os.path.join ( buildDir , mainSrcDir ) )
processSConscript ( os.path.join ( testrunnerSrcDir , 'SConscript' ) , os.path.join ( buildDir , testrunnerSrcDir ) )
processSConscript ( os.path.join ( testrunner2SrcDir , 'SConscript' ) , os.path.join ( buildDir , testrunner2SrcDir ) )

def listEmacsSaveFiles ( ) :
    fileList = [ ]
    for root , dirs , files in os.walk ( '.' ) :
        fileList = fileList + [ os.path.join ( root , f ) for f in files if re.compile ( ".*~" ).search ( f ) ]
    return fileList

Clean ( '.' , [ listEmacsSaveFiles ( ) , buildDir ] )

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

Alias ( 'build' , buildProducts )
Alias ( 'test' , testProducts )

def includeFiles ( ) :
    installList = [ ]
    for root , dirs , files in os.walk ( incSrcDir ) :
        for f in files :
           installList += [ Install ( os.path.join ( installIncDir , '..' , root ) , os.path.join ( root , f ) ) ]
    return installList

def selectCommandParameters ( ) :
    ( baseName , basePath , soName , soPath , fullName , fullPath ) = libraryLinks ( installLibDir , 'aeryn_core' )
    return  ( installLibDir , baseName , soName , fullName )

Alias ( 'install' ,
        includeFiles ( ) + [ Install ( installLibDir , installProducts ) ] ,
        createLibraryLinks ( selectCommandParameters ( ) ) if env['PLATFORM'] in [ 'sunos' , 'posix' ] else None
        )

Default ( 'test' )

Help ( '''
The possible targets are:

    build
    test
    install

Default target is test.
''' )

