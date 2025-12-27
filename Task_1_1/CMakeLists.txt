cmake_minimum_required(VERSION 3.15...4.1)
project(CompressorProject VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

include(GNUInstallDirs)
set(TEST_RESULTS_XML "${CMAKE_BINARY_DIR}/test_results.xml")

add_subdirectory(libcompressor)
add_subdirectory(compressor)
