cmake_minimum_required (VERSION 2.8.11)
project (CryptoPals)

set (CC gcc)
set (CXX g++)
set (CMAKE_C_COMPILER gcc)
set (CMAKE_CXX_COMPILER g++)
set (CMAKE_BUILD_TYPE Debug)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/libcryptopals/include)

add_subdirectory (libcryptopals)
add_subdirectory (Set1)
