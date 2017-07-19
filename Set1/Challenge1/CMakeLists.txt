cmake_minimum_required (VERSION 2.8.11)
project (Hex2Base64)

set (CC gcc)
set (CXX g++)
set (CMAKE_C_COMPILER gcc)
set (CMAKE_CXX_COMPILER g++)
set (CMAKE_BUILD_TYPE Debug)

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable (hex2base64 main.cpp)

target_link_libraries (hex2base64 LINK_PUBLIC Base64 Hexadecimal)

add_subdirectory (src)
