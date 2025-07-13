#ifndef HASH_UTILS_H
#define HASH_UTILS_H

#include <array>
#include <string>
#include "constants.h"

// Calculate SHA-256 hash of an integer
std::array<uint8_t, SHA256_DIGEST_BYTES> calculate_hash(int num);

#endif // HASH_UTILS_H
