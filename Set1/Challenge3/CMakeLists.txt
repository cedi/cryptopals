cmake_minimum_required (VERSION 2.8.11)

add_executable (SingleByteXor main.cpp)

target_link_libraries (SingleByteXor LINK_PUBLIC cryptopals)

