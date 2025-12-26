#include <gtest/gtest.h>

#include <cstdlib>
#include <string>
#include <vector>

#include "libcompressor/libcompressor.hpp"

// Тест: Пустой вход -> Пустой выход
TEST(LibCompressorTest, EmptyInputReturnsEmptyOutput) {
    libcompressor_Buffer input{nullptr, 0};

    libcompressor_Buffer outputZ = libcompressor_compress(libcompressor_Zlib, input);
    EXPECT_EQ(outputZ.data, nullptr);
    EXPECT_EQ(outputZ.size, 0);

    libcompressor_Buffer outputB = libcompressor_compress(libcompressor_Bzip, input);
    EXPECT_EQ(outputB.data, nullptr);
    EXPECT_EQ(outputB.size, 0);
}

// Тест: Непустой вход -> Непустой выход
TEST(LibCompressorTest, NonEmptyInputReturnsNonEmptyOutput) {
    std::string data = "raw data content";
    libcompressor_Buffer input{data.data(), static_cast<int>(data.size())};

    libcompressor_Buffer output = libcompressor_compress(libcompressor_Zlib, input);

    EXPECT_NE(output.data, nullptr);
    EXPECT_GT(output.size, 0);

    std::free(output.data);
}

// Тест: Zlib check exact bytes
TEST(LibCompressorTest, ZlibSpecificOutput) {
    std::string testStr = "test_string";
    libcompressor_Buffer input{testStr.data(), static_cast<int>(testStr.size())};

    libcompressor_Buffer output = libcompressor_compress(libcompressor_Zlib, input);

    // Ожидаемый результат из ТЗ
    std::vector<unsigned char> expected = {0x78, 0x9c, 0x2b, 0x49, 0x2d, 0x2e, 0x89,
                                           0x2f, 0x2e, 0x29, 0xca, 0xcc, 0x4b, 0x07,
                                           0x00, 0x1c, 0x79, 0x04, 0xb7};

    ASSERT_EQ(output.size, static_cast<int>(expected.size()));

    std::vector<unsigned char> actual(output.data, output.data + output.size);
    EXPECT_EQ(actual, expected);

    std::free(output.data);
}

// Тест: Bzip check exact bytes
TEST(LibCompressorTest, BzipSpecificOutput) {
    std::string testStr = "test_string";
    libcompressor_Buffer input{testStr.data(), static_cast<int>(testStr.size())};

    libcompressor_Buffer output = libcompressor_compress(libcompressor_Bzip, input);

    std::vector<unsigned char> expected = {
        0x42, 0x5a, 0x68, 0x31, 0x31, 0x41, 0x59, 0x26, 0x53, 0x59, 0x4a, 0x7c,
        0x69, 0x05, 0x00, 0x00, 0x04, 0x83, 0x80, 0x00, 0x00, 0x82, 0xa1, 0x1c,
        0x00, 0x20, 0x00, 0x22, 0x03, 0x68, 0x84, 0x30, 0x22, 0x50, 0xdf, 0x04,
        0x99, 0xe2, 0xee, 0x48, 0xa7, 0x0a, 0x12, 0x09, 0x4f, 0x8d, 0x20, 0xa0};

    ASSERT_EQ(output.size, static_cast<int>(expected.size()));

    std::vector<unsigned char> actual(output.data, output.data + output.size);
    EXPECT_EQ(actual, expected);

    std::free(output.data);
}
