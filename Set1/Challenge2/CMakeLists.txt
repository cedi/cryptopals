cmake_minimum_required (VERSION 2.8.11)

add_executable (fixedxor main.cpp)

target_link_libraries (fixedxor LINK_PUBLIC cryptopals)
