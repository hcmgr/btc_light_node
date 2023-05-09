#include <array>
#include <iostream>
#include <sstream>

#include "block.h"
#include "crypto.h"

#define BLOCK_HEADER_SIZE 80

BlockHeader::BlockHeader(){}

BlockHeader::BlockHeader(uint32_t version, uint8_t* prev_hash, uint8_t* merkle_hash,
                         uint32_t time, uint32_t nbits, uint32_t nonce)
                         : version(version), time(time), nBits(nbits), nonce(nonce) {

    std::memcpy(hash_prev_block.data(), prev_hash, 32);
    std::memcpy(hash_merkle_root.data(), merkle_hash, 32);
}

BlockHeader BlockHeader::from_serialised(std::array<uint8_t, BLOCK_HEADER_SIZE>& bytes) {
    if (bytes.size() != BLOCK_HEADER_SIZE) {
        std::cout << "Block headers must be 80 bytes" << std::endl;
    }
    BlockHeader header;
    int acc = 0;

    std::memcpy(&header.version, bytes.data() + acc, sizeof(header.version));
    acc += sizeof(header.version);

    std::memcpy(header.hash_prev_block.data(), bytes.data() + acc, sizeof(header.hash_prev_block));
    acc += sizeof(header.hash_prev_block);

    std::memcpy(header.hash_merkle_root.data(), bytes.data() + acc, sizeof(header.hash_merkle_root));
    acc += sizeof(header.hash_merkle_root);

    std::memcpy(&header.time, bytes.data() + acc, sizeof(header.time));
    acc += sizeof(header.time);

    std::memcpy(&header.nBits, bytes.data() + acc, sizeof(header.nBits));
    acc += sizeof(header.nBits);

    std::memcpy(&header.nonce, bytes.data() + acc, sizeof(header.nonce));
    acc += sizeof(header.nonce);

    return header;
}

std::array<uint8_t, BLOCK_HEADER_SIZE> BlockHeader::serialise() {
    std::array<uint8_t, BLOCK_HEADER_SIZE> serialized;
    int acc = 0;

    std::memcpy(serialized.data() + acc, &version, sizeof(version));
    acc += sizeof(version);

    std::memcpy(serialized.data() + acc, hash_prev_block.data(), sizeof(hash_prev_block));
    acc += sizeof(hash_prev_block);

    std::memcpy(serialized.data() + acc, hash_merkle_root.data(), sizeof(hash_merkle_root));
    acc += sizeof(hash_merkle_root);

    std::memcpy(serialized.data() + acc, &time, sizeof(time));
    acc += sizeof(time);

    std::memcpy(serialized.data() + acc, &nBits, sizeof(nBits));
    acc += sizeof(nBits);

    std::memcpy(serialized.data() + acc, &nonce, sizeof(nonce));
    acc += sizeof(nonce);

    return serialized;
}

std::string BlockHeader::pretty_repr() {
    std::stringstream ss;
    ss << "Block header: " << std::endl;
    ss << "----------" << std::endl;
    ss << "version: " << this->version << std::endl; 
    ss << "previous block hash: " << crypto::sha256_hex_repr(this->hash_prev_block.data()) << std::endl;
    ss << "merkle root hash: " << crypto::sha256_hex_repr(this->hash_merkle_root.data()) << std::endl;
    ss << "time: " << this->time << std::endl; 
    ss << "nBits: " << this->nBits << std::endl; 
    ss << "nonce: " << this->nonce << std::endl;
    ss << "----------";
    return ss.str();
}


