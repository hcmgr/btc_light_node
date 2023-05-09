#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "block.h"
#include "crypto.h"

#define RECV_ERROR -1
#define SOCKET_CLOSED 0
#define TCP 0
#define BLOCK_HEADER_SIZE 80

int connect_to_server(std::string IP, int port) {
    // Create a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    // Prepare the sockaddr_in structure
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(IP.c_str());
    server.sin_port = htons(port);

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        std::cerr << "Connection failed" << std::endl;
        return -1;
    }
    return sock;
}

/**
 * Example method of converting different data types
 * into bytes we can send down a socket
*/
int send_net_msg(int socket) {
    // construct a bitcoin block header and send it down socket
    uint32_t version = 0x00000001;
    std::array<uint8_t, 32> prev_hash = crypto::sha256("bibby", 5);
    std::array<uint8_t, 32> merkle_hash = crypto::sha256("thing", 5);
    uint32_t time = 0x00000002;
    uint32_t nBits = 0x00000003;
    uint32_t nonce = 0x00000004;
    BlockHeader bh(version, prev_hash.data(), merkle_hash.data(), time, nBits, nonce);
    std::array<uint8_t, BLOCK_HEADER_SIZE> res = bh.serialise();

    return send(socket, res.data(), BLOCK_HEADER_SIZE, 0);
}

/**
 * Minimal example of a client connecting, sending some data, 
 * receiving some data and disconnecting.
*/
int minimal_client_conn(int socket) {

    std::cout << "connected to server" << std::endl;

    // send some data
    if (send_net_msg(socket) < 0) {
        std::cerr << "Send failed" << std::endl;
        return 1;
    }

    // receive some data
    char buffer[1024];
    int status = recv(socket, buffer, sizeof(buffer), 0);
    switch (status) {
        case SOCKET_CLOSED: // closed
            std::cerr << "server closed socket" << std::endl;
            return SOCKET_CLOSED;

        case RECV_ERROR: //error
            std::cerr << "receive failed" << std::endl;
            return RECV_ERROR;
    }
    std::cout << "data received from server: " << buffer << std::endl;
 
    // Close the socket
    close(socket);
    return 0;
}

int main() {
    int port = 8081;
    std::string pi_ip = "192.168.0.41";
    std::string localhost = "127.0.0.1";
    int socket = connect_to_server(localhost, port);
    if (socket >= 0) {
        int status = minimal_client_conn(socket);
    }
}
