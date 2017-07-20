cmake_minimum_required (VERSION 2.8.11)
project (FixedXOR)

set (CC gcc)
set (CXX g++)
set (CMAKE_C_COMPILER gcc)
set (CMAKE_CXX_COMPILER g++)
set (CMAKE_BUILD_TYPE Debug)

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable (fixedxor main.cpp)

target_link_libraries (fixedxor LINK_PUBLIC XOR Hexadecimal)

add_subdirectory (src)
