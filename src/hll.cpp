#include "hll.h"
#include <algorithm>
#include <cmath>


double get_alpha(int numberOfRegisters) {
	if (numberOfRegisters == TWO_BYTES)
	{
		return HLL_ALPHA_16;
	}
	if (numberOfRegisters == FOUR_BYTES)
	{
		return HLL_ALPHA_32;
	}
	if (numberOfRegisters == EIGHT_BYTES)
	{
		return HLL_ALPHA_64;
	}

	return HLL_ALPHA_LARGE / (1.0 + HLL_BIAS_CORRECTION / numberOfRegisters);
}
uint32_t extract_prefix(std::array<uint8_t, SHA256_DIGEST_BYTES>& hash, int prefixLength)
{
	uint32_t result = 0;

	int fullBytes = prefixLength / BYTE;
	int extraBits = prefixLength % BYTE;

	for (int i = 0; i < fullBytes; i++)
	{
		result = (result << BYTE) | hash[i];
	}

	if (extraBits > 0)
	{
		result = (result << extraBits) | (hash[fullBytes] >> (BYTE - extraBits));
	}

	return result;
}

int calculate_zeros(int startIndex, std::array<uint8_t, SHA256_DIGEST_BYTES> hash)
{
	int zerosCounter = 0;

	for (; startIndex < SHA256_DIGEST_BYTES * BYTE; startIndex++)
	{
		int byteIndex = startIndex / BYTE;
		int bitInByte = BYTE - 1 - (startIndex % BYTE);

		if (((hash[byteIndex] >> bitInByte) & 1) != 0)
		{
			return zerosCounter;
		}

		zerosCounter++;
	}

	return zerosCounter;
}

