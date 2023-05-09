#include <array>
#include <openssl/sha.h>

namespace crypto {
    /**
     * Returns the sha256 hash of the given byte stream.
     *
     * NOTE: method acts more or less as a wrapper for
     *       openssl's less flexible implementation
     * 
     * Returns:
     *      std::array<uint8_t, 32> - hash digest in array
     *                                form
     *  
    */
    std::array<uint8_t, SHA256_DIGEST_LENGTH> sha256(const char* bytes, int len);

    /**
     * Returns the hexadecimal representation of the given
     * SHA256 hash digest
     * 
     * NOTE: we assume our hash (dig) is already in the 
     *       array<uint8_t, 32> form
     * 
     * Returns: 
     *      std::string - str repr
    */
    std::string sha256_hex_repr(uint8_t* dig);
}