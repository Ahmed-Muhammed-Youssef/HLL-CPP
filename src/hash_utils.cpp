#include "hash_utils.h"
#include <openssl/evp.h>
#include <stdexcept>

std::array<uint8_t, SHA256_DIGEST_BYTES> calculate_hash(int num) {
	// Convert integer to string
	std::string input = std::to_string(num);

	// Initialize EVP context
	EVP_MD_CTX* ctx = EVP_MD_CTX_new();
	if (ctx == nullptr) {
		throw std::runtime_error("Failed to create EVP context");
	}

	// Initialize digest with SHA-256
	if (EVP_DigestInit_ex(ctx, EVP_sha256(), nullptr) == 0) {
		EVP_MD_CTX_free(ctx);
		throw std::runtime_error("Failed to initialize SHA-256");
	}

	// Update with input data
	if (EVP_DigestUpdate(ctx, input.c_str(), input.size()) == 0) {
		EVP_MD_CTX_free(ctx);
		throw std::runtime_error("Failed to update hash");
	}

	// Finalize hash
	std::array<uint8_t, SHA256_DIGEST_BYTES> hash;
	unsigned int hash_len;
	if (EVP_DigestFinal_ex(ctx, hash.data(), &hash_len) == 0) {
		EVP_MD_CTX_free(ctx);
		throw std::runtime_error("Failed to finalize hash");
	}

	// Clean up
	EVP_MD_CTX_free(ctx);

	// Verify hash length
	if (hash_len != SHA256_DIGEST_BYTES) {
		throw std::runtime_error("Unexpected hash length");
	}

	return hash;
}