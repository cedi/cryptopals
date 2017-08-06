cmake_minimum_required (VERSION 2.8.11)

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library (Hexadecimal src/Hexadecimal.cpp)
add_library (XOR src/XOR.cpp)
add_library (FrequencyCounter src/FrequencyCounter.cpp)

target_include_directories (Hexadecimal PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories (XOR PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories (FrequencyCounter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
