# - Find Hydra
# Find the Hydra headers
#
# Hydra_INCLUDE_DIR - where to find the TCLAP headers
# Hydra_FOUND       - True if TCLAP is found
#
# FindThrust
#
# This module finds the Thrust header files and extrats their version.  It
# sets the following variables.
#
# Hydra_INCLUDE_DIR -  Include directory for thrust header files.  (All header
#                       files will actually be in the thrust subdirectory.)
# Hydra_VERSION -      Version of thrust in the form "major.minor.patch".
#

find_path( Hydra_INCLUDE_DIR
  HINTS ${HYDRA_INSTALL_PATH}  
  NAMES hydra/Hydra.h
  DOC "Hydra headers"
  )

if( NOT("${Hydra_INCLUDE_DIR}" STREQUAL "Hydra_INCLUDE_DIR-NOTFOUND") )

if( Hydra_INCLUDE_DIR )
  list( REMOVE_DUPLICATES Hydra_INCLUDE_DIR )
endif( Hydra_INCLUDE_DIR )

# Find hydra version
file( STRINGS ${Hydra_INCLUDE_DIR}/hydra/Hydra.h
  version
  REGEX "#define Hydra_VERSION[ \t]+([0-9x]+)"
  )
string( REGEX REPLACE
  "#define Hydra_VERSION[ \t]+"
  ""
  version
  "${version}"
  )

string( REGEX MATCH "^[0-9]" major ${version} )
string( REGEX REPLACE "^${major}00" "" version "${version}" )
string( REGEX MATCH "^[0-9]" minor ${version} )
string( REGEX REPLACE "^${minor}0" "" version "${version}" )
set( Hydra_VERSION "${major}.${minor}.${version}")
set( Hydra_VERSION_MAJOR"${major}")
set( Hydra_VERSION_MINOR "${minor}")

endif(NOT("${Hydra_INCLUDE_DIR}" STREQUAL "Hydra_INCLUDE_DIR-NOTFOUND"))

# Check for required components
include( FindPackageHandleStandardArgs )
find_package_handle_standard_args( Hydra
  REQUIRED_VARS Hydra_INCLUDE_DIR
  VERSION_VAR Hydra_VERSION
  )

if(Hydra_FOUND)
set(Hydra_INCLUDE_DIRS ${Hydra_INCLUDE_DIR})
endif(Hydra_FOUND)

mark_as_advanced(Hydra_INCLUDE_DIR)
