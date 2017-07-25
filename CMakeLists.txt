### CMakeList for Hydra.Python

cmake_minimum_required(VERSION 2.8)

# project name
project(Hydra.Python)


# warn user if system is not UNIX
if(NOT UNIX)
  message(FATAL_ERROR "This is an unsupported system.")
endif()

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

#get TBB
find_package(TBB )
if(TBB_FOUND)
include_directories(${TBB_INCLUDE_DIRS})
link_directories(${TBB_LIBRARY})
endif(TBB_FOUND)

#get OpenMP
find_package(OpenMP)
if(OPENMP_FOUND)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif(OPENMP_FOUND)


#generate API documentation with Doxygen
find_package(Doxygen)
option(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" NO)

find_package(pybind11 REQUIRED)
include_directories(${pybind11_INCLUDE_DIRS})


set(Python_ADDITIONAL_VERSIONS 2.8 2.7 2.6)
find_package(PythonLibs 2.7 REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
link_directories(${PYTHON_LIBRARIES})

#including directories
include_directories(include;  ${PROJECT_SOURCE_DIR})

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

if( CUDA_FOUND )
	SET(BUILD_CUDA_TARGETS  ON)
else()
	SET(BUILD_CUDA_TARGETS  OFF)
endif()

if(TBB_FOUND)
    SET(BUILD_TBB_TARGETS  ON)
else()
    SET(BUILD_TBB_TARGETS  OFF)
endif(TBB_FOUND)

# messages
MESSAGE(STATUS "CUDA include: " ${CUDA_INCLUDE_DIRS})
MESSAGE(STATUS "CUDA libraries: " ${CUDA_LIBRARIES}  )
MESSAGE(STATUS "Build CUDA/NVCC-based targets: ${BUILD_CUDA_TARGETS}")
MESSAGE(STATUS "Hydra  include path: ${Hydra_INCLUDE_DIR}")
MESSAGE(STATUS "Thrust include path: ${THRUST_INCLUDE_DIR}")
MESSAGE(STATUS "project source dir: " ${PROJECT_SOURCE_DIR} )
MESSAGE(STATUS "project build dir: " ${PROJECT_BINARY_DIR} )
MESSAGE(STATUS "nvcc cflags: " ${CUDA_NVCC_FLAGS} )
MESSAGE(STATUS "gcc cflags: " ${CMAKE_CXX_FLAGS} )
MESSAGE(STATUS "include directories:")
get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "  dir = '${dir}'")
endforeach()
MESSAGE(STATUS "Install diretory: " ${CMAKE_INSTALL_PREFIX}  )

