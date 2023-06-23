#include <array>

#define COMMAND_SIZE 12

/**
 * Class to represent network headers
*/
class MessageHeader {
public:
    std::array<uint8_t, 12> command;
    uint32_t payload_size;
};

/**
 * Class to represent network messages
*/
class Message {
public:
    MessageHeader header;
    uint8_t* payload;
};