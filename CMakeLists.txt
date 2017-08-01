### CMakeList for Hydra.Python

cmake_minimum_required(VERSION 2.8)

# project name
project(Hydra.Python)


# warn user if system is not UNIX
if(NOT UNIX)
  message(FATAL_ERROR "This is an unsupported system.")
endif()

##====================================================
## some colors 

  string(ASCII 27 Esc)
  set(ColourReset "${Esc}[m")
  set(ColourBold  "${Esc}[1m")
  set(Red         "${Esc}[31m")
  set(Green       "${Esc}[32m")
  set(Yellow      "${Esc}[33m")
  set(Blue        "${Esc}[34m")
  set(Magenta     "${Esc}[35m")
  set(Cyan        "${Esc}[36m")
  set(White       "${Esc}[37m")
  set(BoldRed     "${Esc}[1;31m")
  set(BoldGreen   "${Esc}[1;32m")
  set(BoldYellow  "${Esc}[1;33m")
  set(BoldBlue    "${Esc}[1;34m")
  set(BoldMagenta "${Esc}[1;35m")
  set(BoldCyan    "${Esc}[1;36m")
  set(BoldWhite   "${Esc}[1;37m")

##====================================================

mark_as_advanced(HydraPython_VERSION_MAJOR HydraPython_VERSION_MINOR HydraPython_VERSION_PATCH)

SET(HydraPython_CMAKE_DIR "${PROJECT_SOURCE_DIR}/cmake")
SET(CMAKE_MODULE_PATH "${HydraPython_CMAKE_DIR}" ${CMAKE_MODULE_PATH})
SET(CMAKE_VERBOSE_MAKEFILE  ON)

#options to gcc
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("--std=c++11" COMPILER_SUPPORTS_CXX11)
if(NOT COMPILER_SUPPORTS_CXX11)
 message(FATAL "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

#options to gcc

set(CMAKE_CXX_FLAGS "-DTHRUST_VARIADIC_TUPLE --std=c++11  -march=native -fPIC -O4" CACHE STRING "compile flags" FORCE)

# get Hydra
find_package(Hydra 1.0.0 REQUIRED)
include_directories(${Hydra_INCLUDE_DIR})

# get THRUST
find_package(Thrust 1.8.3 REQUIRED)
include_directories(${THRUST_INCLUDE_DIR})

#get CUDA
find_package(CUDA 8.0) 
if(CUDA_FOUND)
include_directories("${CUDA_INCLUDE_DIRS}")
endif(CUDA_FOUND)

#get TBB
find_package(TBB )
if(TBB_FOUND)
include_directories(${TBB_INCLUDE_DIRS})
link_directories(${TBB_LIBRARY})
endif(TBB_FOUND)

#get OpenMP
find_package(OpenMP REQUIRED)
if(OPENMP_FOUND)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif(OPENMP_FOUND)

# get ROOT
find_package(ROOT)
if(ROOT_FOUND)
include_directories(${ROOT_INCLUDE_DIR})
link_directories(${ROOT_LIBRARY_DIR})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_ROOT_AVAILABLE_")
endif(ROOT_FOUND)

#generate API documentation with Doxygen
find_package(Doxygen)
option(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" NO)

find_package(pybind11 REQUIRED)
include_directories(${pybind11_INCLUDE_DIRS})


set(Python_ADDITIONAL_VERSIONS 3)
find_package(PythonLibs 3 REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
link_directories(${PYTHON_LIBRARIES})

#including directories
include_directories(${PROJECT_SOURCE_DIR}/include;  ${PROJECT_SOURCE_DIR})

if(CUDA_FOUND)

	#set cuda flags
	
	SET(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS} --cudart ;  static ; -O4 ;--expt-relaxed-constexpr; -ftemplate-backtrace-limit=0; --expt-extended-lambda;--relocatable-device-code=false ;
	-Xptxas -dlcm=ca; -Xptxas --opt-level=4 )

	SET(CUDA_SEPARABLE_COMPILATION OFF)
	SET(CUDA_VERBOSE_BUILD ON)
	
	if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 4.8)
	    LIST(APPEND CUDA_NVCC_FLAGS " -D_MWAITXINTRIN_H_INCLUDED ")
    	endif()
    	
    if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 5.4)
	    LIST(APPEND CUDA_NVCC_FLAGS " -Xcompiler -D__CORRECT_ISO_CPP11_MATH_H_PROTO ")
    	endif()
	# Detect CUDA architecture and get best NVCC flags
	
	INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindCudaArch.cmake)
	
	SELECT_NVCC_ARCH_FLAGS(NVCC_FLAGS_EXTRA)
	
	LIST(APPEND CUDA_NVCC_FLAGS ${NVCC_FLAGS_EXTRA})
		
endif(CUDA_FOUND)

if( OPENMP_FOUND )
	SET(BUILD_OPENMP_TARGETS  ON)
else()
	SET(BUILD_OPENMP_TARGETS  OFF)
endif(OPENMP_FOUND)

if( CUDA_FOUND )
	SET(BUILD_CUDA_TARGETS  ON)
else()
	SET(BUILD_CUDA_TARGETS  OFF)
endif(CUDA_FOUND)

if(TBB_FOUND)
    SET(BUILD_TBB_TARGETS  ON)
else()
    SET(BUILD_TBB_TARGETS  OFF)
endif(TBB_FOUND)

# messages
MESSAGE(STATUS "${BoldGreen}================================================================ ${ColourReset}")
MESSAGE(STATUS "${BoldGreen}=================   SUMMARY OF THE PATHS PROJECT =============== ${ColourReset}")
MESSAGE(STATUS "${BoldGreen}================================================================ ${ColourReset}")
if( OPENMP_FOUND )
MESSAGE(STATUS "${BoldYellow}OpenMP compiler flags: ${ColourReset}" ${OpenMP_CXX_FLAGS})
MESSAGE(STATUS "${BoldYellow}Build OpenMP-based targets:${ColourReset} ${BUILD_OPENMP_TARGETS}")
endif(OPENMP_FOUND)

if( CUDA_FOUND )
MESSAGE(STATUS "${BoldYellow}CUDA include: ${ColourReset}" ${CUDA_INCLUDE_DIRS})
MESSAGE(STATUS "${BoldYellow}CUDA libraries:${ColourReset} " ${CUDA_LIBRARIES}  )
MESSAGE(STATUS "${BoldYellow}Build CUDA/NVCC-based targets:${ColourReset} ${BUILD_CUDA_TARGETS}")
endif(CUDA_FOUND)

if( TBB_FOUND )
MESSAGE(STATUS "${BoldYellow}TBB include: ${ColourReset}" ${TBB_INCLUDE_DIRS})
MESSAGE(STATUS "${BoldYellow}TBB libraries:${ColourReset} " ${TBB_LIBRARIES}  )
MESSAGE(STATUS "${BoldYellow}Build TBB-based targets:${ColourReset} ${BUILD_TBB_TARGETS}")
endif(TBB_FOUND)

MESSAGE(STATUS "${BoldYellow}Hydra  include path:${ColourReset} ${Hydra_INCLUDE_DIR}")
MESSAGE(STATUS "${BoldYellow}Thrust include path:${ColourReset} ${THRUST_INCLUDE_DIR}")
MESSAGE(STATUS "${BoldYellow}pybind11 include path:${ColourReset} ${pybind11_INCLUDE_DIRS}")
MESSAGE(STATUS "${BoldYellow}Python include path:${ColourReset} ${PYTHON_INCLUDE_DIRS}")
MESSAGE(STATUS "${BoldYellow}Python libraries:${ColourReset} ${PYTHON_LIBRARIES}")
MESSAGE(STATUS "${BoldYellow}project source dir: ${ColourReset}" ${PROJECT_SOURCE_DIR} )
MESSAGE(STATUS "${BoldYellow}project build dir: ${ColourReset}" ${PROJECT_BINARY_DIR} )
MESSAGE(STATUS "${BoldYellow}nvcc cflags: ${ColourReset}" ${CUDA_NVCC_FLAGS} )
MESSAGE(STATUS "${BoldYellow}gcc cflags: ${ColourReset}" ${CMAKE_CXX_FLAGS} )
MESSAGE(STATUS "${BoldYellow}include directories:${ColourReset}")
get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "${Green}  dir = ${ColourReset}'${dir}'")
endforeach()
MESSAGE(STATUS "${BoldYellow}Install diretory: ${ColourReset}" ${CMAKE_INSTALL_PREFIX}  )
MESSAGE(STATUS "${BoldGreen}=============================================================== ${ColourReset}")



IF(OPENMP_FOUND)
add_library(HydraPython SHARED src/PyBindings.cpp)
set_target_properties(HydraPython PROPERTIES  PREFIX ""
    COMPILE_FLAGS "-fopenmp -DTHRUST_HOST_SYSTEM=THRUST_HOST_SYSTEM_CPP -DTHRUST_DEVICE_SYSTEM=THRUST_DEVICE_SYSTEM_OMP -lgomp")
target_link_libraries(HydraPython ${PYTHON_LIBRARIES})
ENDIF(OPENMP_FOUND)
