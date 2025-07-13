#include<iostream>
#include<array>
#include<vector>
#include <algorithm>
#include<string>
#include <iomanip>
#include <openssl/evp.h>
#include "constants.h"
#include "hll.h"

// testing 
constexpr int TEST_ARRAY_SIZE = 5;
constexpr int TEST_PREFIX_SIZE = 10;

int main()
{
	try 
	{
		std::array<int, TEST_ARRAY_SIZE> data = { 1, 2, 3, 4, 1 };

		double estimate = hll(TEST_PREFIX_SIZE, data);
		std::cout << "Estimated number of unique records: " << estimate << "\n";

		return 0;
	}
	catch (const std::exception&) 
	{
		return 1;
	}
}