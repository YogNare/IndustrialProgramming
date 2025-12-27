#pragma once

/**
 * @file libcompressor.hpp
 * @brief Заголовочный файл библиотеки сжатия.
 */

/**
 * @enum libcompressor_CompressionAlgorithm
 * @brief Перечисление алгоритмов сжатия.
 */
enum libcompressor_CompressionAlgorithm { libcompressor_Zlib, libcompressor_Bzip };

/**
 * @struct libcompressor_Buffer
 * @brief Структура буфера данных.
 */
struct libcompressor_Buffer {
    char* data;
    int size;
};

/**
 * @brief Сжимает входной буфер.
 *
 * @param algo Алгоритм сжатия.
 * @param input Входной буфер.
 * @return libcompressor_Buffer Выходной буфер (выделен через std::malloc).
 */
libcompressor_Buffer libcompressor_compress(libcompressor_CompressionAlgorithm algo,
                                            libcompressor_Buffer input);
