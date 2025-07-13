# 📊 HyperLogLog (HLL) – C++ Implementation

A lightweight C++ implementation of the **HyperLogLog** algorithm to estimate the number of **distinct integers** in a dataset using fixed memory. Internally uses probabilistic counting with a hash-based register array—fully abstracted from the user.

## 🔧 Features

- Estimates cardinality from an input array of integers
- Internal register management (no user setup required)
- Templated for fixed-size input arrays
- Configurable accuracy via `prefixLength` parameter

## 🚀 Example Usage

```cpp
constexpr std::size_t TEST_ARRAY_SIZE = 6;
constexpr int TEST_PREFIX_SIZE = 5;

std::array<int, TEST_ARRAY_SIZE> data = { 1, 2, 3, 4, 1, 2 };

double estimate = HyperLogLog::hll(TEST_PREFIX_SIZE, data);

std::cout << "Estimated cardinality: " << estimate << std::endl;
```

## 🧠 Method Signature

```cpp
template<std::size_t N>
static double hll(int prefixLength, const std::array<int, N>& data);
```

- `prefixLength`: number of bits used for register indexing (`b`), e.g., 4 → 16 registers
- `data`: array of integers whose cardinality will be estimated

