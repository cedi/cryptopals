cmake_minimum_required (VERSION 2.8.11)

add_executable (BreakRepeatingKeyXor main.cpp)

target_link_libraries (BreakRepeatingKeyXor LINK_PUBLIC cryptopals)
