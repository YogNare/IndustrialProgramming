set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(spdlog REQUIRED CONFIG)

add_executable(compressor
    src/compressor.cpp
)

target_link_libraries(compressor PRIVATE 
    libcompressor
    spdlog::spdlog
)

install(TARGETS compressor
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
