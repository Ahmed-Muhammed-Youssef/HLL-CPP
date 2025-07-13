#ifndef HLL_H
#define HLL_H

#include <array>
#include <vector>
#include <cstdint>
#include "constants.h"
#include <iostream>
#include <iomanip>
#include "hash_utils.h"

// HLL correction constants (empirically derived)
constexpr double HLL_ALPHA_16 = 0.673;
constexpr double HLL_ALPHA_32 = 0.697;
constexpr double HLL_ALPHA_64 = 0.709;
constexpr double HLL_ALPHA_LARGE = 0.7213;
constexpr double HLL_BIAS_CORRECTION = 1.079;

// HLL-related
constexpr double FLOAT_SCALING = 2.5;
constexpr double THRESHOLD = 30.0;

// Get alpha constant for HLL based on number of registers
double get_alpha(int numberOfRegisters);

// Extract prefix bits from hash
uint32_t extract_prefix(std::array<uint8_t, SHA256_DIGEST_BYTES>& hash, int prefixLength);

// Count leading zeros in hash starting from an index
int calculate_zeros(int startIndex, std::array<uint8_t, SHA256_DIGEST_BYTES> hash);

// HyperLogLog algorithm to estimate cardinality
template<std::size_t N>
static double hll(int prefixLength, const std::array<int, N>& data)
{
	int numberOfRegisters = 1 << prefixLength;
	std::vector<int> accumilator(numberOfRegisters, 0);

	for (int item : data)
	{
		auto hashed = calculate_hash(item);
		// Debug: Print hash as hex
		std::cout << item << " hashed values: ";
		for (uint8_t byte : hashed)
		{
			std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)byte;
		}
		std::cout << std::dec << "\n";

		uint32_t prefixIndex = extract_prefix(hashed, prefixLength);

		int numberOfZeros = calculate_zeros(prefixLength, hashed) + 1;


		accumilator[prefixIndex] = std::max(accumilator[prefixIndex], numberOfZeros);
	}

	// Calculate harmonic mean
	double harmonicMean = 0.0;
	for (int item : accumilator)
	{
		harmonicMean += 1.0 / (double)(1ULL << item); // 2^(-M[i])
	}
	double estimate = get_alpha(numberOfRegisters) * numberOfRegisters * numberOfRegisters / harmonicMean;

	// Small cardinality correction
	int64_t zeros = std::count(accumilator.begin(), accumilator.end(), 0);
	if (estimate <= FLOAT_SCALING * numberOfRegisters) {
		if (zeros > 0) {
			estimate = numberOfRegisters * std::log(static_cast<double>(numberOfRegisters) / static_cast<double>(zeros));
		}
	}
	// Large cardinality correction (optional, typically for very large datasets)
	else if (estimate > (1ULL << FOUR_BYTES) / THRESHOLD) {
		estimate = -static_cast<double>(1ULL << FOUR_BYTES) * std::log(1.0 - (estimate / (1ULL << FOUR_BYTES)));
	}

	return estimate;
}
#endif // HLL_H