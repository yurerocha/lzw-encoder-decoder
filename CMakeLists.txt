cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(LZW VERSION 0.1 LANGUAGES CXX)

# file(MAKE_DIRECTORY output)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(POSITION_INDEPENDENT_CODE OFF)
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG") # Full optimization and not using debug information, respectively.
set(CMAKE_CXX_FLAGS_DEBUG "-g") # Full optimization and not using debug information, respectively.

# Compileer options.
list(APPEND LZW_COMPILER_FLAGS
    "-Wall" # Recommended compiler warnings.
    "-Wextra" # This enables some extra warning flags that are not enabled by -Wall.
    "-Wpedantic" # Issue all the warnings demanded by strict ISO C and ISO C++.
    "-Werror" # Make all warnings into errors.
)

set(LZW_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

include_directories(include)

set(LZW_SOURCE_FILES
    ${LZW_SOURCE_DIR}/Data.cpp
    ${LZW_SOURCE_DIR}/LZW.cpp
)

set(LZW_MAIN
    ${LZW_SOURCE_DIR}/Encode.cpp
)

set(UNLZW_MAIN
    ${LZW_SOURCE_DIR}/Decode.cpp
)

add_executable(lzw ${LZW_SOURCE_FILES} ${LZW_MAIN})
add_executable(unlzw ${LZW_SOURCE_FILES} ${UNLZW_MAIN})