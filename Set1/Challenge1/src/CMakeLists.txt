cmake_minimum_required (VERSION 2.8.11)

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library (Base64 src/Base64.cpp)
add_library (Hexadecimal src/Hexadecimal.cpp)

target_include_directories (Base64 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories (Hexadecimal PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
