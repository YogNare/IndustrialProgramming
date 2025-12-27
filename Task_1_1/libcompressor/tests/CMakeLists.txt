find_package(GTest REQUIRED CONFIG)

enable_testing()

add_executable(libcompressor_test libcompressortest.cpp)

target_link_libraries(libcompressor_test PRIVATE
    libcompressor
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(libcompressor_test 
    XML_OUTPUT_DIR ${CMAKE_BINARY_DIR} # Для отчета
)
