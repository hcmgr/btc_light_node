#include <iostream>
#include <sstream>
#include <string>
#include <array>
#include <iomanip>

#include <openssl/sha.h>

namespace crypto {

    std::array<uint8_t, SHA256_DIGEST_LENGTH> sha256(const char* bytes, int len) {
        unsigned char text[len];
        std::memcpy(text, bytes, len);

        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256(text, len, hash);
        
        std::array<uint8_t, SHA256_DIGEST_LENGTH> digest;
        std::memcpy(digest.data(), hash, SHA256_DIGEST_LENGTH);

        return digest;
    }

    std::string sha256_hex_repr(uint8_t* dig) {
        std::stringstream ss;
        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
            ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(dig[i]);
        }
        return ss.str();
    }
}
