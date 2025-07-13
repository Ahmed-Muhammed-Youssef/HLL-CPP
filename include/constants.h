#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cstddef>

// digest size (32 bytes = 256 bits for SHA-256)
constexpr std::size_t SHA256_DIGEST_BYTES = 32;

// Number of bits in bytes
constexpr int BYTE = 8;
constexpr int TWO_BYTES = 16;
constexpr int FOUR_BYTES = 32;
constexpr int EIGHT_BYTES = 64;

#endif // CONSTANTS_H
