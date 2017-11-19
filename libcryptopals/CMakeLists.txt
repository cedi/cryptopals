cmake_minimum_required (VERSION 2.8.11)

add_library (cryptopals
	${CMAKE_CURRENT_SOURCE_DIR}/src/Base64.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Hexadecimal.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/XOR.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/FrequencyCounter.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/TextScoring.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/HammingDistance.cpp
	)

target_include_directories (cryptopals PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
