# VERSION 3.10...3.25 şeklinde üst sınırda verilebilir.
cmake_minimum_required(VERSION 3.10)

project(SimpleCProjects
    VERSION 1.0.0
    DESCRIPTION "Simple C Projects"
    LANGUAGES C CXX
)

list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_SOURCE_DIR}/cmake
)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ZLIB REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(SOURCE_FILES stdio_fundamentals.c)

file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

include(Git)
include(CustomTools)
include(SystemCheck)
include(DependencyCheck)

run_dependency_queue_check()

# CMake’in policy sisteminde belirli bir eski davranışı değiştirip yeni davranışı aktif eder.
cmake_policy(SET CMP0074 NEW)
option(ENABLE_FEATURE "Enable feature X" OFF)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Build Mode: Debug mode is active. Adding debug symbols...")
    add_compile_options(-g -O0)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Build Mode: Release mode is active. Enabling optimizations...")
    add_compile_options(-O3)
else()
    message(STATUS "Build Mode: Not specified. Using default configuration.")
endif()

filter_existing_files(SOURCE_FILES FILTERED_SOURCE_FILES)
message(STATUS "Verifying Filtered Source Files: ${FILTERED_SOURCE_FILES}")

include_directories(${CMAKE_SOURCE_DIR}/include)
# add_executable(SimpleCProjects ${FILTERED_SOURCE_FILES})

add_executable(stdio_test ${CMAKE_CURRENT_SOURCE_DIR}/src/stdio_fundamentals.c)
add_executable(file_test ${CMAKE_CURRENT_SOURCE_DIR}/src/file_operations.c)
add_executable(dynamic_memory_test ${CMAKE_CURRENT_SOURCE_DIR}/src/dynamic_memory.c)
add_executable(algorithm_lab_test ${CMAKE_CURRENT_SOURCE_DIR}/src/algorithm_lab.c)
add_executable(system_network_ip_reader ${CMAKE_CURRENT_SOURCE_DIR}/src/system_network_ip_reader.c)