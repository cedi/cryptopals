cmake_minimum_required (VERSION 2.8.11)

add_executable (hex2base64 main.cpp)

target_link_libraries (hex2base64 LINK_PUBLIC cryptopals)

