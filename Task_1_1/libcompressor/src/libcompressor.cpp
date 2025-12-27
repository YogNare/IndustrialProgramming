#include "libcompressor/libcompressor.hpp"

#include <bzlib.h>
#include <zlib.h>

#include <cstdlib>
#include <cstring>

libcompressor_Buffer libcompressor_compress(libcompressor_CompressionAlgorithm algo,
                                            libcompressor_Buffer input) {
    libcompressor_Buffer outBuffer{nullptr, 0};

    if (input.size <= 0 || input.data == nullptr) {
        return outBuffer;
    }

    size_t allocationSize = static_cast<size_t>(input.size) + 1024;

    void* mem = std::malloc(allocationSize);
    if (!mem) {
        return outBuffer;
    }

    char* dest = static_cast<char*>(mem);
    int result = -1;

    unsigned long destLenZlib = static_cast<unsigned long>(allocationSize);
    unsigned int destLenBzip = static_cast<unsigned int>(allocationSize);

    if (algo == libcompressor_Zlib) {
        result =
            ::compress(reinterpret_cast<Bytef*>(dest), &destLenZlib,
                       reinterpret_cast<const Bytef*>(input.data), static_cast<uLong>(input.size));

        if (result == Z_OK) {
            outBuffer.data = dest;
            outBuffer.size = static_cast<int>(destLenZlib);
        }

    } else if (algo == libcompressor_Bzip) {
        result = ::BZ2_bzBuffToBuffCompress(dest, &destLenBzip, input.data,
                                            static_cast<unsigned int>(input.size), 1, 0, 0);

        if (result == BZ_OK) {
            outBuffer.data = dest;
            outBuffer.size = static_cast<int>(destLenBzip);
        }
    }

    if (outBuffer.data == nullptr) {
        std::free(mem);
        outBuffer.size = 0;
    }

    return outBuffer;
}
