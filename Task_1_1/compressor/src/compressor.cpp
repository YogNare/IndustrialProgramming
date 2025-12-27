#include <spdlog/spdlog.h>

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "libcompressor/libcompressor.hpp"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        spdlog::error("Not enough arguments. Usage: compressor <zlib|bzip> <string>");
        return EXIT_FAILURE;
    }

    std::string algoStr = argv[1];
    std::string inputStr = argv[2];

    libcompressor_CompressionAlgorithm algo;

    if (algoStr == "zlib") {
        algo = libcompressor_Zlib;
    } else if (algoStr == "bzip") {
        algo = libcompressor_Bzip;
    } else {
        spdlog::error("Invalid compression algorithm: {}. Supported: zlib, bzip", algoStr);
        return EXIT_FAILURE;
    }

    libcompressor_Buffer inputBuf;
    inputBuf.data = inputStr.data();
    inputBuf.size = static_cast<int>(inputStr.size());

    libcompressor_Buffer outputBuf = libcompressor_compress(algo, inputBuf);

    if (outputBuf.data == nullptr || outputBuf.size == 0) {
        spdlog::error("Compression failed or returned empty buffer.");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < outputBuf.size; ++i) {
        std::fprintf(stdout, "%02hhx", static_cast<unsigned char>(outputBuf.data[i]));
    }
    std::fprintf(stdout, "\n");

    std::free(outputBuf.data);

    return EXIT_SUCCESS;
}
