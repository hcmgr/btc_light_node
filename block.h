#ifndef BLOCK_HEADER_H
#define BLOCK_HEADER_H

#include <array>

#define BLOCK_HEADER_SIZE 80

class BlockHeader {
public:
    uint32_t version;
    std::array<uint8_t, 32> hash_prev_block;
    std::array<uint8_t, 32> hash_merkle_root;
    uint32_t time;
    uint32_t nBits;
    uint32_t nonce;

    /**
     * Empty constructor
    */
    BlockHeader();

    /**
     * Regular constructor
    */
    BlockHeader(uint32_t version, char* prev_hash, char* merkle_hash,
                uint32_t time, uint32_t nbits, uint32_t nonce);

    /**
     * Construct BlockHeader instance from a serialised byte array
    */
    static BlockHeader from_serialised(std::array<uint8_t, BLOCK_HEADER_SIZE>& bytes);

    /**
     * Serialise BlockHeader to byte array
    */
    std::array<uint8_t, BLOCK_HEADER_SIZE> serialise();
};

#endif // BLOCK_HEADER_H
