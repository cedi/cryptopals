cmake_minimum_required (VERSION 2.8.11)
project (Hex2Base64)

set (CMAKE_C_COMPILER gcc)
set (CMAKE_CXX_COMPILER g++)

add_executable (hex2base64 main.cpp)

target_link_libraries (hex2base64 LINK_PUBLIC Base64 Hexadecimal)

add_subdirectory (src)
