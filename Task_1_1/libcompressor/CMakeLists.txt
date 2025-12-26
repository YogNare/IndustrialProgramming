project(libcompressor)

find_package(ZLIB REQUIRED CONFIG)
find_package(BZip2 REQUIRED CONFIG)

add_library(libcompressor STATIC
    src/libcompressor.cpp
)

target_include_directories(libcompressor PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(libcompressor PRIVATE 
    ZLIB::ZLIB 
    BZip2::BZip2
)

install(TARGETS libcompressor
    EXPORT libcompressorTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY include/libcompressor DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

add_subdirectory(tests)
