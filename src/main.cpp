#include<iostream>
#include<array>
#include<vector>
#include <algorithm>

// digest size (32 bytes = 256 bits for SHA-256)
constexpr std::size_t SHA256_DIGEST_BYTES = 32;
constexpr int BYTE = 8;

static std::array<uint8_t, SHA256_DIGEST_BYTES> calculate_hash(int num)
{
	return std::array<uint8_t, SHA256_DIGEST_BYTES>{};
}

static uint32_t extract_prefix(std::array<uint8_t, SHA256_DIGEST_BYTES>& hash, int prefixLength)
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

static int calculate_zeros(int startIndex, std::array<uint8_t, SHA256_DIGEST_BYTES> hash)
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

template<std::size_t N>
static std::int64_t hll(int prefixLength, std::array<int, N> data)
{
	int size = 1 << prefixLength;
	std::vector<int> accumilator(size);

	std::int64_t result{};

	for(int item : data)
	{
		auto hashed = calculate_hash(item);

		uint32_t prefixIndex = extract_prefix(hashed, prefixLength);

		int numberOfZeros = calculate_zeros(prefixLength, hashed) + 1;


		accumilator[prefixIndex] = std::max(accumilator[prefixIndex], numberOfZeros);
	}

	for (int item : accumilator)
	{
		result += item;
	}

	return result;
}


int main()
{
	try 
	{
		const int testPrefixSize = 5;

		std::array<int, testPrefixSize> data = { 1, 2, 3, 4, 1 };

		auto sum = hll(testPrefixSize, data);

		std::cout << "number of unique records: " << sum << "\n";

		return 0;
	}
	catch (std::exception)
	{
		return 1;
	}
}